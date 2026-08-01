#include "acgc/data.hpp"

#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <optional>
#include <ranges>
#include <sstream>
#include <string_view>
#include <system_error>
#include <vector>

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_misc.h>
#include <SDL3/SDL_stdinc.h>

#include <nlohmann/json.hpp>

/* Data-directory resolution, ported from Dusklight's dusk::data module.
 *
 * The active data directory holds saves, configuration, input mappings, and
 * replacement assets. Its location comes from, in priority order: the
 * --user-dir argument, a data_location.json descriptor (searched next to the
 * executable first, then in the SDL pref path), or the platform default.
 *
 * The platform default is the SDL pref path everywhere except Windows, where
 * it is the executable directory when writable so that layouts produced by
 * the pre-Aurora port keep working unchanged. Caches always stay in the SDL
 * pref path so redirected/portable data directories never accumulate
 * regenerable files. */

namespace acgc::data {
namespace {

constexpr borealis::Log Log{"acgc::data"};
constexpr const char* kOrgName = nullptr; /* No vendor directory (pending final port name). */
constexpr const char* kAppName = "Animal Crossing";
constexpr const char* kLocationDescriptorName = "data_location.json";

constexpr std::array<std::string_view, 3> kUserDataDirectories = {
    "save",
    "texture_pack",
    "nes_roms",
};
constexpr std::array<std::string_view, 7> kUserDataFiles = {
    "config.json",
    "settings.ini",
    "keybindings.ini",
    "controller_ports.dat",
    "gamecontrollerdb.txt",
    "imgui.ini",
    "keyboard_bindings.dat",
};

enum class LocationMode {
    Default,
    Custom,
};

struct LocationDescriptor {
    LocationMode mode = LocationMode::Default;
    std::filesystem::path customPath;
    std::filesystem::path previousPath;
};

struct LocatedDescriptor {
    LocationDescriptor descriptor;
    std::filesystem::path path;
};

struct MigrationStats {
    std::uintmax_t directoriesCreated = 0;
    std::uintmax_t filesCopied = 0;
    std::uintmax_t symlinksCopied = 0;
    std::uintmax_t sourcesRemoved = 0;
    std::uintmax_t emptyDirectoriesRemoved = 0;
    std::uintmax_t skippedExistingTargets = 0;
    std::uintmax_t skippedDescriptorFiles = 0;
    std::uintmax_t skippedNestedTargets = 0;
    std::uintmax_t skippedUnsupportedEntries = 0;
    std::uintmax_t failures = 0;
};

std::optional<std::filesystem::path> sConfiguredDataPath;
std::optional<std::filesystem::path> sActiveDescriptorPath;
std::optional<std::filesystem::path> sActivePrefPath;
std::filesystem::path sActiveDataPath;
bool sUserDirOverrideActive = false;

std::filesystem::path get_pref_path() {
    char* prefPath = SDL_GetPrefPath(kOrgName, kAppName);
    if (!prefPath) {
        Log.error("Unable to get the SDL pref path: {}",
                        SDL_GetError());
        return {};
    }

    std::filesystem::path result = borealis::io::fs_path_from_utf8(prefPath);
    SDL_free(prefPath);
    return result;
}

std::filesystem::path active_pref_path() {
    if (!sActivePrefPath) {
        sActivePrefPath = get_pref_path();
    }
    return *sActivePrefPath;
}

bool probe_writable_path(const std::filesystem::path& path) {
    std::error_code ec;
    std::filesystem::create_directories(path, ec);
    if (ec || !std::filesystem::is_directory(path, ec) || ec) {
        return false;
    }

    const auto probePath =
        path / (".write-probe-" +
                std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) +
                ".tmp");
    {
        std::ofstream stream(probePath, std::ios::binary | std::ios::trunc);
        stream << "acgc";
        if (!stream) {
            std::filesystem::remove(probePath, ec);
            return false;
        }
    }
    std::filesystem::remove(probePath, ec);
    return !ec;
}

std::filesystem::path default_data_path(const std::filesystem::path& prefPath) {
#if defined(__APPLE__) && TARGET_OS_IOS && !TARGET_OS_TV
    const char* documentsPath = SDL_GetUserFolder(SDL_FOLDER_DOCUMENTS);
    if (!documentsPath) {
        Log.error("Unable to get the iOS Documents path: {}",
                        SDL_GetError());
        return prefPath;
    }
    return borealis::io::fs_path_from_utf8(documentsPath);
#elif defined(_WIN32)
    /* The pre-Aurora port resolved every path against the executable
     * directory; keep that the default so existing installations continue to
     * find their saves, settings, and texture packs. Installations in
     * unwritable locations fall back to the pref path. */
    static const std::filesystem::path resolved = [&]() -> std::filesystem::path {
        const auto basePath = base_path_relative({});
        if (!basePath.empty() && probe_writable_path(basePath)) {
            return basePath;
        }
        Log.warn("Executable directory '{}' is not writable; storing data in '{}' instead",
                        borealis::io::fs_path_to_string(basePath).c_str(), borealis::io::fs_path_to_string(prefPath).c_str());
        return prefPath;
    }();
    return resolved;
#else
    return prefPath;
#endif
}

std::vector<std::filesystem::path> descriptor_paths(const std::filesystem::path& prefPath) {
    std::vector<std::filesystem::path> paths;
    if (const auto basePath = base_path_relative(kLocationDescriptorName); !basePath.empty()) {
        paths.push_back(basePath);
    }
    if (!prefPath.empty()) {
        paths.push_back(prefPath / kLocationDescriptorName);
    }
    return paths;
}

std::optional<LocationDescriptor> read_location_descriptor_file(const std::filesystem::path& path) {
    if (path.empty()) {
        return std::nullopt;
    }
    if (std::error_code ec; !std::filesystem::exists(path, ec)) {
        return std::nullopt;
    }

    try {
        std::ifstream stream(path, std::ios::binary);
        if (!stream) {
            return std::nullopt;
        }
        const auto json = nlohmann::json::parse(stream);
        if (!json.is_object()) {
            Log.warn("Ignoring data location descriptor '{}': root is not an object",
                            borealis::io::fs_path_to_string(path).c_str());
            return std::nullopt;
        }

        LocationDescriptor descriptor;
        const auto mode = json.value<std::string>("mode", "default");
        if (mode == "custom") {
            descriptor.mode = LocationMode::Custom;
        } else if (mode != "default") {
            Log.warn("Ignoring unknown data location mode '{}'",
                            mode.c_str());
        }

        if (const auto customPath = json.find("customPath");
            customPath != json.end() && customPath->is_string())
        {
            descriptor.customPath = borealis::io::fs_path_from_utf8(customPath->get<std::string>());
        }
        if (const auto previousPath = json.find("previousPath");
            previousPath != json.end() && previousPath->is_string())
        {
            descriptor.previousPath = borealis::io::fs_path_from_utf8(previousPath->get<std::string>());
        }

        return descriptor;
    } catch (const std::exception& e) {
        Log.warn("Ignoring data location descriptor '{}': {}",
                        borealis::io::fs_path_to_string(path).c_str(), e.what());
        return std::nullopt;
    }
}

std::optional<LocatedDescriptor> read_location_descriptor(const std::filesystem::path& prefPath) {
    for (const auto& path : descriptor_paths(prefPath)) {
        if (auto descriptor = read_location_descriptor_file(path)) {
            return LocatedDescriptor{
                .descriptor = *descriptor,
                .path = path,
            };
        }
    }
    return std::nullopt;
}

std::filesystem::path resolve_data_path(const std::filesystem::path& prefPath,
                                        const LocationDescriptor* descriptor) {
    if (!descriptor) {
        return default_data_path(prefPath);
    }

    switch (descriptor->mode) {
    case LocationMode::Default:
        return default_data_path(prefPath);
    case LocationMode::Custom:
        if (!descriptor->customPath.empty()) {
            return descriptor->customPath;
        }
        Log.warn("Data location descriptor requested custom mode without a path");
        return default_data_path(prefPath);
    }

    return default_data_path(prefPath);
}

const char* location_mode_id(LocationMode mode) {
    switch (mode) {
    case LocationMode::Default:
        return "default";
    case LocationMode::Custom:
        return "custom";
    }

    return "default";
}

std::filesystem::path normalized_path(const std::filesystem::path& path) {
    std::error_code ec;
    auto normalized = std::filesystem::weakly_canonical(path, ec);
    if (!ec) {
        return normalized;
    }

    normalized = std::filesystem::absolute(path, ec);
    if (!ec) {
        return normalized.lexically_normal();
    }

    return path.lexically_normal();
}

std::filesystem::path absolute_path(const std::filesystem::path& path) {
    std::error_code ec;
    const auto absolute = std::filesystem::absolute(path, ec);
    if (ec) {
        return path;
    }
    return absolute.lexically_normal();
}

bool is_same_or_inside(const std::filesystem::path& root, const std::filesystem::path& path) {
    const auto normalizedRoot = normalized_path(root);
    const auto normalizedPath = normalized_path(path);
    const auto relativePath = normalizedPath.lexically_relative(normalizedRoot);
    if (relativePath.empty()) {
        return normalizedPath == normalizedRoot;
    }
    if (relativePath == ".") {
        return true;
    }
    if (relativePath.is_absolute()) {
        return false;
    }

    const auto it = relativePath.begin();
    return it == relativePath.end() || *it != "..";
}

bool should_skip_migration_path(const std::filesystem::path& path,
                                const std::filesystem::path& from,
                                const std::filesystem::path& to, MigrationStats& stats) {
    if (is_same_or_inside(to, path)) {
        ++stats.skippedNestedTargets;
        return true;
    }

    const auto relativePath = path.lexically_relative(from);
    if (relativePath == kLocationDescriptorName) {
        ++stats.skippedDescriptorFiles;
        return true;
    }

    return false;
}

bool matches_name(std::string_view name, const auto& names) {
    return std::ranges::find(names, name) != names.end();
}

/* Only recognized user data moves between locations; regenerable files
 * (caches, logs) and unrelated files sharing the directory stay behind. */
bool should_migrate_user_data_path(const std::filesystem::path& sourcePath,
                                   const std::filesystem::path& from) {
    const auto relativePath = sourcePath.lexically_relative(from);
    if (relativePath.empty() || relativePath.is_absolute()) {
        return false;
    }

    auto it = relativePath.begin();
    if (it == relativePath.end() || *it == "..") {
        return false;
    }

    const auto first = borealis::io::fs_path_to_string(*it);
    if (matches_name(first, kUserDataDirectories)) {
        return true;
    }

    ++it;
    if (it != relativePath.end()) {
        return false;
    }

    const auto filename = borealis::io::fs_path_to_string(relativePath.filename());
    if (matches_name(filename, kUserDataFiles)) {
        return true;
    }

    return relativePath.extension() == ".controller" || relativePath.extension() == ".gci";
}

std::vector<std::filesystem::path> descriptor_write_paths(const std::filesystem::path& prefPath) {
    if (sActiveDescriptorPath && !sActiveDescriptorPath->empty()) {
        return {*sActiveDescriptorPath};
    }

    std::vector<std::filesystem::path> paths;
#if defined(_WIN32)
    if (const auto basePath = base_path_relative(kLocationDescriptorName); !basePath.empty()) {
        paths.push_back(basePath);
    }
#endif
    if (!prefPath.empty()) {
        paths.push_back(prefPath / kLocationDescriptorName);
    }
    return paths;
}

bool write_descriptor_json(const std::filesystem::path& path, const nlohmann::json& json) {
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    if (ec) {
        Log.warn("Failed to create data location descriptor directory '{}': {}",
                        borealis::io::fs_path_to_string(path.parent_path()).c_str(), ec.message().c_str());
        return false;
    }
    std::ofstream stream(path, std::ios::binary | std::ios::trunc);
    stream << json.dump(4);
    if (!stream) {
        Log.warn("Failed to write data location descriptor '{}'",
                        borealis::io::fs_path_to_string(path).c_str());
        return false;
    }
    return true;
}

std::filesystem::path current_data_path() {
    if (!sActiveDataPath.empty()) {
        return sActiveDataPath;
    }
    return configured_data_path();
}

bool write_location_descriptor(LocationMode mode, const std::filesystem::path& targetPath) {
    LocationDescriptor descriptor;
    descriptor.mode = mode;
    if (mode == LocationMode::Custom) {
        descriptor.customPath = absolute_path(targetPath);
    }

    const auto currentPath = current_data_path();
    const auto resolvedTargetPath =
        mode == LocationMode::Custom ? descriptor.customPath : targetPath;
    if (!currentPath.empty() && normalized_path(currentPath) != normalized_path(resolvedTargetPath))
    {
        descriptor.previousPath = currentPath;
    }

    nlohmann::json json;
    json["version"] = 1;
    json["mode"] = location_mode_id(descriptor.mode);
    if (descriptor.mode == LocationMode::Custom && !descriptor.customPath.empty()) {
        json["customPath"] = borealis::io::fs_path_to_string(descriptor.customPath);
    }
    if (!descriptor.previousPath.empty()) {
        json["previousPath"] = borealis::io::fs_path_to_string(descriptor.previousPath);
    }

    const auto prefPath = active_pref_path();
    for (const auto& path : descriptor_write_paths(prefPath)) {
        if (write_descriptor_json(path, json)) {
            sActiveDescriptorPath = path;
            sConfiguredDataPath = resolvedTargetPath;
            return true;
        }
    }

    return false;
}

void set_error(std::string* errorOut, std::string error) {
    if (errorOut != nullptr) {
        *errorOut = std::move(error);
    }
}

bool validate_writable_data_path(const std::filesystem::path& path, std::string* errorOut) {
    if (path.empty()) {
        set_error(errorOut, "Choose a folder.");
        return false;
    }

    std::error_code ec;
    std::filesystem::create_directories(path, ec);
    if (ec) {
        set_error(errorOut, "The selected folder could not be created.");
        Log.warn("Failed to create custom data folder '{}': {}",
                        borealis::io::fs_path_to_string(path).c_str(), ec.message().c_str());
        return false;
    }

    if (!std::filesystem::is_directory(path, ec)) {
        set_error(errorOut, "The selected path is not a folder.");
        if (ec) {
            Log.warn("Failed to inspect custom data folder '{}': {}",
                            borealis::io::fs_path_to_string(path).c_str(), ec.message().c_str());
        }
        return false;
    }

    if (!probe_writable_path(path)) {
#if defined(__ANDROID__)
        set_error(errorOut, "The selected folder is not writable. On Android, allow "
                            "\"All files access\" and try again.");
#else
        set_error(errorOut, "The selected folder is not writable.");
#endif
        Log.warn("Failed write probe for custom data folder '{}'",
                        borealis::io::fs_path_to_string(path).c_str());
        return false;
    }

    return true;
}

std::uintmax_t remove_empty_directories(const std::filesystem::path& root, bool includeRoot) {
    std::error_code ec;
    std::vector<std::filesystem::path> directories;
    for (std::filesystem::recursive_directory_iterator it(
             root, std::filesystem::directory_options::skip_permission_denied, ec);
         it != std::filesystem::recursive_directory_iterator(); it.increment(ec))
    {
        if (ec) {
            Log.warn("Failed to scan empty directories under '{}': {}",
                            borealis::io::fs_path_to_string(root).c_str(), ec.message().c_str());
            return 0;
        }
        const auto status = it->symlink_status(ec);
        if (ec) {
            ec.clear();
            continue;
        }
        if (std::filesystem::is_directory(status)) {
            directories.push_back(it->path());
        }
    }

    std::uintmax_t removed = 0;
    for (auto& dir : std::views::reverse(directories)) {
        if (!std::filesystem::is_empty(dir, ec)) {
            ec.clear();
            continue;
        }
        if (std::filesystem::remove(dir, ec)) {
            ++removed;
        }
        ec.clear();
    }

    if (includeRoot) {
        if (std::filesystem::is_empty(root, ec) && std::filesystem::remove(root, ec)) {
            ++removed;
        }
        ec.clear();
    }

    return removed;
}

bool ensure_parent_directory(const std::filesystem::path& targetPath, MigrationStats& stats) {
    std::error_code ec;
    std::filesystem::create_directories(targetPath.parent_path(), ec);
    if (ec) {
        ++stats.failures;
        Log.warn("Failed to create migration target parent '{}': {}",
                        borealis::io::fs_path_to_string(targetPath.parent_path()).c_str(), ec.message().c_str());
        return false;
    }
    return true;
}

bool remove_migrated_source(const std::filesystem::path& sourcePath, MigrationStats& stats) {
    std::error_code ec;
    std::filesystem::remove(sourcePath, ec);
    if (ec) {
        ++stats.failures;
        Log.warn("Migrated '{}' but failed to remove source: {}",
                        borealis::io::fs_path_to_string(sourcePath).c_str(), ec.message().c_str());
        return false;
    }

    ++stats.sourcesRemoved;
    return true;
}

bool try_rename_migration_entry(const std::filesystem::path& sourcePath,
                                const std::filesystem::path& targetPath) {
    std::error_code ec;
    if (std::filesystem::exists(targetPath, ec) || std::filesystem::is_symlink(targetPath, ec)) {
        return false;
    }
    ec.clear();

    if (!std::filesystem::exists(sourcePath, ec)) {
        return false;
    }
    ec.clear();

    std::filesystem::create_directories(targetPath.parent_path(), ec);
    if (ec) {
        return false;
    }

    std::filesystem::rename(sourcePath, targetPath, ec);
    return !ec;
}

void migrate_symlink(const std::filesystem::path& sourcePath,
                     const std::filesystem::path& targetPath, MigrationStats& stats) {
    std::error_code ec;
    if (std::filesystem::exists(targetPath, ec) || std::filesystem::is_symlink(targetPath, ec)) {
        ++stats.skippedExistingTargets;
        return;
    }
    ec.clear();

    const auto linkTarget = std::filesystem::read_symlink(sourcePath, ec);
    if (ec) {
        ++stats.failures;
        Log.warn("Failed to read migration symlink '{}': {}",
                        borealis::io::fs_path_to_string(sourcePath).c_str(), ec.message().c_str());
        return;
    }

    if (!ensure_parent_directory(targetPath, stats)) {
        return;
    }

    const bool targetIsDirectory = std::filesystem::is_directory(sourcePath, ec);
    ec.clear();

    if (targetIsDirectory) {
        std::filesystem::create_directory_symlink(linkTarget, targetPath, ec);
    } else {
        std::filesystem::create_symlink(linkTarget, targetPath, ec);
    }
    if (ec) {
        ++stats.failures;
        Log.warn("Failed to migrate symlink '{}' to '{}': {}",
                        borealis::io::fs_path_to_string(sourcePath).c_str(), borealis::io::fs_path_to_string(targetPath).c_str(),
                        ec.message().c_str());
        return;
    }

    ++stats.symlinksCopied;
    remove_migrated_source(sourcePath, stats);
}

void migrate_regular_file(const std::filesystem::path& sourcePath,
                          const std::filesystem::path& targetPath, MigrationStats& stats) {
    std::error_code ec;
    if (std::filesystem::exists(targetPath, ec)) {
        ++stats.skippedExistingTargets;
        return;
    }
    ec.clear();

    if (try_rename_migration_entry(sourcePath, targetPath)) {
        ++stats.filesCopied;
        ++stats.sourcesRemoved;
        return;
    }

    if (!ensure_parent_directory(targetPath, stats)) {
        return;
    }

    std::filesystem::copy_file(sourcePath, targetPath, std::filesystem::copy_options::skip_existing,
                               ec);
    if (ec) {
        ++stats.failures;
        Log.warn("Failed to migrate file '{}' to '{}': {}",
                        borealis::io::fs_path_to_string(sourcePath).c_str(), borealis::io::fs_path_to_string(targetPath).c_str(),
                        ec.message().c_str());
        return;
    }

    ++stats.filesCopied;
    remove_migrated_source(sourcePath, stats);
}

void migrate_directory(const std::filesystem::path& from, const std::filesystem::path& to,
                       const std::filesystem::path& prefPath) {
    if (from.empty() || to.empty() || normalized_path(from) == normalized_path(to)) {
        return;
    }

    MigrationStats stats;

    std::error_code ec;
    if (!std::filesystem::exists(from, ec)) {
        return;
    }

    std::filesystem::create_directories(to, ec);
    if (ec) {
        Log.warn("Failed to create data directory '{}' for migration: {}",
                        borealis::io::fs_path_to_string(to).c_str(), ec.message().c_str());
        return;
    }

    std::filesystem::recursive_directory_iterator it(
        from, std::filesystem::directory_options::skip_permission_denied, ec);
    if (ec) {
        Log.warn("Failed to begin migration scan for '{}': {}",
                        borealis::io::fs_path_to_string(from).c_str(), ec.message().c_str());
        return;
    }

    const std::filesystem::recursive_directory_iterator end;
    while (it != end) {
        if (ec) {
            ++stats.failures;
            Log.warn("Migration scan error under '{}': {}",
                            borealis::io::fs_path_to_string(from).c_str(), ec.message().c_str());
            ec.clear();
        }

        const auto sourcePath = it->path();
        const auto status = it->symlink_status(ec);
        if (ec) {
            ++stats.failures;
            ec.clear();
            it.increment(ec);
            continue;
        }

        if (should_skip_migration_path(sourcePath, from, to, stats)) {
            if (std::filesystem::is_directory(status)) {
                it.disable_recursion_pending();
            }
            ec.clear();
            it.increment(ec);
            continue;
        }

        if (!should_migrate_user_data_path(sourcePath, from)) {
            ++stats.skippedUnsupportedEntries;
            if (std::filesystem::is_directory(status)) {
                it.disable_recursion_pending();
            }
            ec.clear();
            it.increment(ec);
            continue;
        }

        const auto relativePath = sourcePath.lexically_relative(from);
        if (relativePath.empty() || relativePath.is_absolute()) {
            ++stats.failures;
            it.increment(ec);
            continue;
        }

        const auto targetPath = to / relativePath;
        if (std::filesystem::is_symlink(status)) {
            migrate_symlink(sourcePath, targetPath, stats);
        } else if (std::filesystem::is_directory(status)) {
            if (try_rename_migration_entry(sourcePath, targetPath)) {
                ++stats.directoriesCreated;
                ++stats.sourcesRemoved;
                it.disable_recursion_pending();
            } else {
                std::filesystem::create_directories(targetPath, ec);
                if (ec) {
                    ++stats.failures;
                    ec.clear();
                    it.disable_recursion_pending();
                } else {
                    ++stats.directoriesCreated;
                }
            }
        } else if (std::filesystem::is_regular_file(status)) {
            migrate_regular_file(sourcePath, targetPath, stats);
        } else {
            ++stats.skippedUnsupportedEntries;
        }

        it.increment(ec);
    }

    const bool includeRoot = normalized_path(from) != normalized_path(prefPath);
    stats.emptyDirectoriesRemoved = remove_empty_directories(from, includeRoot);

    const bool migratedAnything = stats.filesCopied > 0 || stats.symlinksCopied > 0 ||
                                  stats.sourcesRemoved > 0 || stats.emptyDirectoriesRemoved > 0 ||
                                  stats.failures > 0;
    if (migratedAnything) {
        std::ostringstream summary;
        summary << "Finished data migration from '" << borealis::io::fs_path_to_string(from) << "' to '"
                << borealis::io::fs_path_to_string(to) << "': " << stats.filesCopied << " files copied, "
                << stats.symlinksCopied << " symlinks copied, " << stats.sourcesRemoved
                << " sources removed, " << stats.emptyDirectoriesRemoved
                << " empty directories removed, " << stats.skippedExistingTargets
                << " existing targets skipped, " << stats.skippedUnsupportedEntries
                << " unsupported entries skipped, " << stats.failures << " failures";
        Log.info("{}", summary.str().c_str());
    }
}

void ensure_data_directory(const std::filesystem::path& dataPath) {
    std::error_code ec;
    std::filesystem::create_directories(dataPath, ec);
    if (ec) {
        Log.error("Failed to create data directory '{}': {}",
                        borealis::io::fs_path_to_string(dataPath).c_str(), ec.message().c_str());
    }
}

std::filesystem::path user_home_path() {
    const char* homePath = SDL_GetUserFolder(SDL_FOLDER_HOME);
    if (homePath == nullptr || homePath[0] == '\0') {
        return {};
    }
    return borealis::io::fs_path_from_utf8(homePath);
}

} // namespace

std::filesystem::path base_path_relative(const std::filesystem::path& path) {
    const auto* basePath = SDL_GetBasePath();
    if (!basePath) {
        return path;
    }
    return borealis::io::fs_path_from_utf8(basePath) / path;
}

bool open_data_path() {
#if ACGC_CAN_OPEN_DATA_FOLDER
    std::error_code ec;
    std::filesystem::path path = std::filesystem::absolute(sActiveDataPath, ec);
    if (ec) {
        path = sActiveDataPath;
    }

#if defined(_WIN32)
    const std::string url = "file:///" + borealis::io::fs_path_to_generic_string(path);
#else
    const std::string url = "file://" + borealis::io::fs_path_to_generic_string(path);
#endif
    if (!SDL_OpenURL(url.c_str())) {
        Log.warn("Failed to open data folder '{}': {}",
                        borealis::io::fs_path_to_string(path).c_str(), SDL_GetError());
        return false;
    }
    return true;
#else
    return false;
#endif
}

bool set_custom_data_path(const std::filesystem::path& path, std::string* errorOut) {
    if (sUserDirOverrideActive) {
        set_error(errorOut, "The data folder is fixed by --user-dir for this session.");
        return false;
    }
    if (!validate_writable_data_path(path, errorOut)) {
        return false;
    }

    if (!write_location_descriptor(LocationMode::Custom, path)) {
        set_error(errorOut, "The data folder setting could not be saved.");
        return false;
    }

    return true;
}

bool set_custom_data_path(const char* path, std::string* errorOut) {
    if (path == nullptr) {
        set_error(errorOut, "Choose a folder.");
        return false;
    }
    return set_custom_data_path(borealis::io::fs_path_from_utf8(path), errorOut);
}

bool reset_data_path() {
    if (sUserDirOverrideActive) {
        return false;
    }
    const auto prefPath = active_pref_path();
    return write_location_descriptor(LocationMode::Default, default_data_path(prefPath));
}

bool is_default_data_path() {
    const auto prefPath = active_pref_path();
    return normalized_path(configured_data_path()) == normalized_path(default_data_path(prefPath));
}

std::filesystem::path configured_data_path() {
    if (sConfiguredDataPath) {
        return *sConfiguredDataPath;
    }

    const auto prefPath = active_pref_path();
    const auto descriptor = read_location_descriptor(prefPath);
    if (descriptor) {
        sActiveDescriptorPath = descriptor->path;
    }
    sConfiguredDataPath =
        resolve_data_path(prefPath, descriptor ? &descriptor->descriptor : nullptr);
    return *sConfiguredDataPath;
}

bool is_data_path_restart_pending() {
    if (sActiveDataPath.empty()) {
        return false;
    }

    return normalized_path(sActiveDataPath) != normalized_path(configured_data_path());
}

std::filesystem::path cache_path() {
    return active_pref_path();
}

Paths initialize(const char* userDirOverride) {
    const auto prefPath = active_pref_path();

    if (userDirOverride != nullptr && userDirOverride[0] != '\0') {
        sUserDirOverrideActive = true;
        const auto dataPath = absolute_path(borealis::io::fs_path_from_utf8(userDirOverride));
        sActiveDataPath = dataPath;
        sConfiguredDataPath = dataPath;
        ensure_data_directory(dataPath);
        Log.info("Data directory (--user-dir): {}",
                        borealis::io::fs_path_to_string(dataPath).c_str());
        return Paths{
            .userPath = dataPath,
            .cachePath = prefPath.empty() ? dataPath : prefPath,
        };
    }

    const auto descriptor = read_location_descriptor(prefPath);
    if (descriptor) {
        sActiveDescriptorPath = descriptor->path;
    } else {
        sActiveDescriptorPath.reset();
    }
    auto dataPath = resolve_data_path(prefPath, descriptor ? &descriptor->descriptor : nullptr);
    if (dataPath.empty()) {
        std::error_code ec;
        dataPath = std::filesystem::current_path(ec);
    }
    sConfiguredDataPath = dataPath;
    sActiveDataPath = dataPath;

    if (descriptor && !descriptor->descriptor.previousPath.empty()) {
        migrate_directory(descriptor->descriptor.previousPath, dataPath, prefPath);
    }
    ensure_data_directory(dataPath);
    if (!prefPath.empty()) {
        ensure_data_directory(prefPath);
    }

    Log.info("Data directory: {}", borealis::io::fs_path_to_string(dataPath).c_str());
    return Paths{
        .userPath = dataPath,
        .cachePath = prefPath.empty() ? dataPath : prefPath,
    };
}

extern "C" int pc_platform_base_path(const char* relative_path, char* output, size_t output_size) {
    if (relative_path == nullptr || output == nullptr || output_size == 0) {
        return 0;
    }

    const auto path = base_path_relative(std::filesystem::path(relative_path));
    if (path.empty() || path.is_relative()) {
        return 0;
    }
    const auto utf8 = path.u8string();
    if (utf8.size() + 1 > output_size) {
        return 0;
    }
    std::memcpy(output, utf8.data(), utf8.size());
    output[utf8.size()] = '\0';
    return 1;
}

std::string abbreviated_path_string(const std::filesystem::path& path) {
    const auto homePath = user_home_path();
    if (path.empty() || homePath.empty()) {
        return borealis::io::fs_path_to_string(path);
    }

    const auto normalizedPath = normalized_path(path);
    const auto normalizedHome = normalized_path(homePath);
    if (normalizedPath == normalizedHome) {
        return "~";
    }

    const auto relativePath = normalizedPath.lexically_relative(normalizedHome);
    if (!relativePath.empty() && !relativePath.is_absolute()) {
        const auto it = relativePath.begin();
        if (it == relativePath.end() || *it != "..") {
            return borealis::io::fs_path_to_string(std::filesystem::path{"~"} / relativePath);
        }
    }

    return borealis::io::fs_path_to_string(path);
}

} // namespace acgc::data
