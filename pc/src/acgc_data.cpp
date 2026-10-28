#include "acgc/data.hpp"

#include "acgc/app_info.hpp"

#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <cstddef>
#include <cstring>
#include <string>

namespace acgc::data {
namespace {

constexpr borealis::Log Log{ "acgc::data" };

std::string status_message(const borealis::data::Status& status) {
    using enum borealis::data::ErrorCode;

    std::string message;
    switch (status.code) {
        case None:
            return {};
        case NotInitialized:
            message = "Data folders have not been initialized.";
            break;
        case PreferencePathUnavailable:
            message = "The system data folder is unavailable.";
            break;
        case EmptyPath:
            message = "Choose a folder.";
            break;
        case CreateDirectoryFailed:
            message = "The selected folder could not be created.";
            break;
        case NotDirectory:
            message = "The selected path is not a folder.";
            break;
        case WriteProbeFailed:
            message = "The selected folder is not writable.";
            break;
        case WriteProbeCleanupFailed:
            message = "The selected folder could not be validated.";
            break;
        case DescriptorWriteFailed:
            message = "The data folder setting could not be saved.";
            break;
        case MigrationIncomplete:
            message = "Data migration could not be completed.";
            break;
        case OverrideActive:
            message = "The data folder is fixed by --user-dir for this session.";
            break;
        case Unsupported:
            message = "Changing the data folder is not supported on this platform.";
            break;
        case OpenFolderFailed:
            message = "The data folder could not be opened.";
            break;
    }

    if (!status.path.empty()) {
        message += " (" + borealis::io::fs_path_to_string(status.path) + ")";
    }
    if (status.systemError) {
        message += ": " + status.systemError.message();
    }
    return message;
}

bool operation_succeeded(const borealis::data::Status& status) {
    if (status) {
        return true;
    }
    const auto message = status_message(status);
    Log.warn("{}", message);
    return false;
}

} // namespace

borealis::data::Manager& manager() {
    static borealis::data::Manager instance{
        AppInfo,
        {
            .defaultPath =
                {
                    .useDocumentsOnIOS = true,
                    .useExecutableDirectoryOnWindows = true,
                },
            .legacyApps = {{.orgName = {}, .appName = "Animal Crossing"}},
            .migration =
                {
                    .directories = {"save", "texture_pack", "nes_roms"},
                    .files =
                        {
                            "config.json",
                            "settings.ini",
                            "keybindings.ini",
                            "controller_ports.dat",
                            "gamecontrollerdb.txt",
                            "imgui.ini",
                            "keyboard_bindings.dat",
                        },
                    .extensions = {".controller", ".gci"},
                },
        },
    };
    return instance;
}

Paths initialize(const std::filesystem::path& userDirectoryOverride) {
    const auto status = manager().initialize(userDirectoryOverride);
    if (!status && status.code != borealis::data::ErrorCode::MigrationIncomplete) {
        Log.fatal("Failed to initialize data folders: {}", status_message(status));
    }
    if (!status) {
        Log.warn("{} Migration will be retried on the next launch.", status_message(status));
    }
    Log.info("Data directory: {}", borealis::io::fs_path_to_string(manager().active_data_path()));
    return manager().paths();
}

std::filesystem::path cache_path() {
    return manager().paths().cachePath;
}

std::filesystem::path base_path_relative(const std::filesystem::path& path) {
    return manager().base_path_relative(path);
}

std::filesystem::path configured_data_path() {
    return manager().configured_data_path();
}

bool open_data_path() {
    return operation_succeeded(manager().open_active_data_path());
}

borealis::data::Status set_custom_data_path(const std::filesystem::path& path) {
    auto status = manager().set_custom_data_path(path);
    operation_succeeded(status);
    return status;
}

bool reset_data_path() {
    return operation_succeeded(manager().reset_data_path());
}

bool is_default_data_path() {
    return manager().is_default_data_path();
}

bool is_data_path_restart_pending() {
    return manager().is_data_path_restart_pending();
}

std::string abbreviated_path_string(const std::filesystem::path& path) {
    return manager().abbreviated_path_string(path);
}

extern "C" int pc_platform_base_path(const char* relativePath, char* output, size_t outputSize) {
    if (relativePath == nullptr || output == nullptr || outputSize == 0) {
        return 0;
    }

    const auto path = base_path_relative(std::filesystem::path{ relativePath });
    if (path.empty() || path.is_relative()) {
        return 0;
    }
    const auto utf8 = path.u8string();
    if (utf8.size() + 1 > outputSize) {
        return 0;
    }
    std::memcpy(output, utf8.data(), utf8.size());
    output[utf8.size()] = '\0';
    return 1;
}

} // namespace acgc::data
