#include "acgc/texture_replacements.hpp"

#include <dolphin/gx/GXStruct.h>
#include <aurora/texture.hpp>

#include "acgc/data.hpp"
#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <system_error>

constexpr borealis::Log Log{"acgc::textures"};

namespace acgc::texture_replacements {
namespace {

aurora::texture::ReplacementGroup s_directoryGroup;

void unload()
{
    aurora::texture::unregister_replacements(s_directoryGroup);
    s_directoryGroup = {};
}

} // namespace

const std::filesystem::path& directory()
{
    // Packs live in the data directory. Pre-Aurora installs resolved
    // texture_pack/ against the CWD (usually the executable directory), so
    // fall back to those roots while the data directory has no pack.
    static const std::filesystem::path path = [] {
        std::error_code ec;
        const std::filesystem::path primary = acgc::data::manager().active_data_path() / "texture_pack";
        if (std::filesystem::is_directory(primary, ec)) {
            return primary;
        }
        ec.clear();
        if (const auto legacy = std::filesystem::current_path(ec) / "texture_pack";
            !ec && std::filesystem::is_directory(legacy, ec)) {
            return legacy;
        }
        ec.clear();
        if (const auto legacy = acgc::data::base_path_relative("texture_pack");
            std::filesystem::is_directory(legacy, ec)) {
            return legacy;
        }
        return primary;
    }();
    return path;
}

std::size_t registration_count()
{
    return s_directoryGroup.registrations.size();
}

void reload()
{
    std::error_code ec;
    const auto& root = directory();
    if (!std::filesystem::is_directory(root, ec)) {
        unload();
        if (ec) {
            Log.warn("Could not inspect {}: {}",
                            borealis::io::fs_path_to_string(root).c_str(), ec.message().c_str());
        } else {
            Log.info("Texture pack directory not found: {}",
                            borealis::io::fs_path_to_string(root).c_str());
        }
        return;
    }

    aurora::texture::reload_replacement_directory(root, s_directoryGroup);
    Log.info("Loaded {} texture replacement(s) from {}",
                    registration_count(), borealis::io::fs_path_to_string(root).c_str());
}

void shutdown()
{
    unload();
}

} // namespace acgc::texture_replacements
