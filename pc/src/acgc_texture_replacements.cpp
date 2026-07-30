#include "acgc/texture_replacements.hpp"

#include <dolphin/gx/GXStruct.h>
#include <aurora/texture.hpp>

#include "port/logging.h"

#include <system_error>

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
    // Preserve the retired port's boundary exactly: packs live beside the
    // process working directory, not under the per-user config directory.
    static const std::filesystem::path path = std::filesystem::current_path() / "texture_pack";
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
            port_log_printf(LOG_WARNING, "acgc::textures", "Could not inspect %s: %s",
                            root.string().c_str(), ec.message().c_str());
        } else {
            port_log_printf(LOG_INFO, "acgc::textures", "Texture pack directory not found: %s",
                            root.string().c_str());
        }
        return;
    }

    aurora::texture::reload_replacement_directory(root, s_directoryGroup);
    port_log_printf(LOG_INFO, "acgc::textures", "Loaded %zu texture replacement(s) from %s",
                    registration_count(), root.string().c_str());
}

void shutdown()
{
    unload();
}

} // namespace acgc::texture_replacements
