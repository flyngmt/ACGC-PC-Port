#include "acgc/settings.hpp"

#include "acgc/config.hpp"
#include "ac_birth_control.h"
#include "dolphin/pad.h"
#include "m_player_lib.h"
#include "pc_settings.h"
#include "port/logging.h"

#include <algorithm>
#include <charconv>
#include <fstream>
#include <optional>
#include <set>
#include <string_view>

extern "C" {
void pc_audio_set_master_volume(int volume);

PCSettings g_pc_settings = {
    1280, 960, 0, 1, 60, 1, 0, 0, 0, 1, 1, 100, 12, 12,
};
}

namespace acgc {
namespace {

std::string path_string(const std::filesystem::path& path)
{
    const std::u8string utf8 = path.u8string();
    return {reinterpret_cast<const char*>(utf8.data()), utf8.size()};
}

std::string_view trim(std::string_view value)
{
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string_view::npos) {
        return {};
    }
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

std::optional<int> parse_integer(std::string_view value)
{
    value = trim(value);
    int result = 0;
    const auto [end, error] = std::from_chars(value.data(), value.data() + value.size(), result);
    if (error != std::errc{} || end != value.data() + value.size()) {
        return std::nullopt;
    }
    return result;
}

bool set_legacy_value(std::string_view key, int value)
{
    auto& current = settings();
    if (key == "window_width" && value >= 640) current.video.windowWidth.set_value(value);
    else if (key == "window_height" && value >= 480) current.video.windowHeight.set_value(value);
    else if (key == "fullscreen" && value >= 0 && value <= 2) current.video.windowMode.set_value(value);
    else if (key == "vsync" && (value == 0 || value == 1)) current.video.vsync.set_value(value != 0);
    else if (key == "max_fps" && value >= 0 && value <= 1000) current.video.maxFrameRate.set_value(value);
    else if (key == "msaa" && (value == 0 || value == 1 || value == 2 || value == 4 || value == 8))
        current.video.msaa.set_value(value == 0 ? 1 : value);
    else if (key == "preload_textures" && value >= 0 && value <= 2) current.enhancements.preloadTextures.set_value(value);
    else if (key == "disable_resetti" && (value == 0 || value == 1)) current.enhancements.disableResetti.set_value(value != 0);
    else if (key == "disable_shop_visitor_req" && (value == 0 || value == 1))
        current.enhancements.disableShopVisitorRequirement.set_value(value != 0);
    else if (key == "borderless_acres" && (value == 0 || value == 1)) current.enhancements.borderlessAcres.set_value(value != 0);
    else if (key == "nes_aspect" && (value == 0 || value == 1)) current.enhancements.pillarboxNes.set_value(value != 0);
    else if (key == "master_volume" && value >= 0 && value <= 100) current.audio.masterVolume.set_value(value);
    else if (key == "stick_deadzone" && value >= 0 && value <= 40) current.input.stickDeadzone.set_value(value);
    else if (key == "cstick_deadzone" && value >= 0 && value <= 40) current.input.cstickDeadzone.set_value(value);
    else return false;
    return true;
}

bool import_legacy_file(const std::filesystem::path& path)
{
    std::ifstream stream(path);
    if (!stream) {
        return false;
    }

    int imported = 0;
    std::string line;
    while (std::getline(stream, line)) {
        const std::string_view stripped = trim(line);
        if (stripped.empty() || stripped.front() == '#' || stripped.front() == ';' || stripped.front() == '[') {
            continue;
        }
        const auto equals = stripped.find('=');
        if (equals == std::string_view::npos) {
            continue;
        }
        const std::string_view key = trim(stripped.substr(0, equals));
        const auto value = parse_integer(stripped.substr(equals + 1));
        if (value && set_legacy_value(key, *value)) {
            ++imported;
        }
    }

    if (imported == 0) {
        port_log_printf(LOG_WARNING, "acgc::config", "Legacy settings file '%s' contained no recognized values",
                        path_string(path).c_str());
        return false;
    }
    port_log_printf(LOG_INFO, "acgc::config", "Imported %d settings from legacy file %s",
                    imported, path_string(path).c_str());
    return true;
}

void sanitize_settings()
{
    auto& current = settings();
    current.video.windowWidth.set_value(std::clamp(current.video.windowWidth.value(), 320, 16384));
    current.video.windowHeight.set_value(std::clamp(current.video.windowHeight.value(), 240, 16384));
    current.video.windowMode.set_value(std::clamp(current.video.windowMode.value(), 0, 2));
    current.video.maxFrameRate.set_value(std::clamp(current.video.maxFrameRate.value(), 0, 1000));
    const int msaa = current.video.msaa.value();
    current.video.msaa.set_value(msaa == 2 || msaa == 4 || msaa == 8 ? msaa : 1);
    current.enhancements.preloadTextures.set_value(std::clamp(current.enhancements.preloadTextures.value(), 0, 2));
    current.audio.masterVolume.set_value(std::clamp(current.audio.masterVolume.value(), 0, 100));
    current.input.stickDeadzone.set_value(std::clamp(current.input.stickDeadzone.value(), 0, 40));
    current.input.cstickDeadzone.set_value(std::clamp(current.input.cstickDeadzone.value(), 0, 40));
}

} // namespace

UserSettings::Video::Video()
    : windowWidth("video.windowWidth", 1280)
    , windowHeight("video.windowHeight", 960)
    , windowMode("video.windowMode", 0)
    , vsync("video.vsync", true)
    , maxFrameRate("video.maxFrameRate", 60)
    , msaa("video.msaa", 1)
{
}

UserSettings::Enhancements::Enhancements()
    : preloadTextures("enhancements.preloadTextures", 0)
    , disableResetti("gameplay.disableResetti", false)
    , disableShopVisitorRequirement("gameplay.disableShopVisitorRequirement", false)
    , borderlessAcres("gameplay.borderlessAcres", true)
    , pillarboxNes("gameplay.pillarboxNes", true)
{
}

UserSettings::Audio::Audio()
    : masterVolume("audio.masterVolume", 100)
{
}

UserSettings::Input::Input()
    : stickDeadzone("input.stickDeadzone", 12)
    , cstickDeadzone("input.cstickDeadzone", 12)
{
}

UserSettings& settings()
{
    static UserSettings value;
    return value;
}

void register_settings()
{
    auto& current = settings();
    config::register_var(current.video.windowWidth);
    config::register_var(current.video.windowHeight);
    config::register_var(current.video.windowMode);
    config::register_var(current.video.vsync);
    config::register_var(current.video.maxFrameRate);
    config::register_var(current.video.msaa);
    config::register_var(current.enhancements.preloadTextures);
    config::register_var(current.enhancements.disableResetti);
    config::register_var(current.enhancements.disableShopVisitorRequirement);
    config::register_var(current.enhancements.borderlessAcres);
    config::register_var(current.enhancements.pillarboxNes);
    config::register_var(current.audio.masterVolume);
    config::register_var(current.input.stickDeadzone);
    config::register_var(current.input.cstickDeadzone);
}

SettingsLoadResult load_settings(const std::filesystem::path& userDirectory,
                                 const std::vector<std::filesystem::path>& legacyCandidates)
{
    register_settings();
    config::set_user_directory(userDirectory);

    SettingsLoadResult result{.canonicalResult = config::load()};
    if (result.canonicalResult == config::LoadResult::Missing) {
        std::set<std::filesystem::path> visited;
        for (const auto& candidate : legacyCandidates) {
            std::error_code error;
            const auto normalized = std::filesystem::weakly_canonical(candidate, error);
            const auto key = error ? candidate.lexically_normal() : normalized;
            if (!visited.insert(key).second) {
                continue;
            }
            if (import_legacy_file(candidate)) {
                result.importedLegacy = true;
                result.legacyPath = candidate;
                break;
            }
        }
    }

    sanitize_settings();
    apply_settings_bridge(false);
    if (result.canonicalResult == config::LoadResult::Missing) {
        config::save();
    }
    return result;
}

void apply_settings_bridge(bool refreshGameplay)
{
    const auto& current = settings();
    const bool borderlessWasEnabled = g_mPlib_wade_disabled != 0;
    g_pc_settings.window_width = current.video.windowWidth.value();
    g_pc_settings.window_height = current.video.windowHeight.value();
    g_pc_settings.fullscreen = current.video.windowMode.value();
    g_pc_settings.vsync = current.video.vsync.value() ? 1 : 0;
    g_pc_settings.max_fps = current.video.maxFrameRate.value();
    g_pc_settings.msaa = current.video.msaa.value() == 1 ? 0 : current.video.msaa.value();
    g_pc_settings.preload_textures = current.enhancements.preloadTextures.value();
    g_pc_settings.disable_resetti = current.enhancements.disableResetti.value() ? 1 : 0;
    g_pc_settings.disable_shop_visitor_req = current.enhancements.disableShopVisitorRequirement.value() ? 1 : 0;
    g_pc_settings.borderless_acres = current.enhancements.borderlessAcres.value() ? 1 : 0;
    g_pc_settings.nes_aspect = current.enhancements.pillarboxNes.value() ? 1 : 0;
    g_pc_settings.master_volume = current.audio.masterVolume.value();
    g_pc_settings.stick_deadzone = current.input.stickDeadzone.value();
    g_pc_settings.cstick_deadzone = current.input.cstickDeadzone.value();
    g_mPlib_wade_disabled = g_pc_settings.borderless_acres;
    if (refreshGameplay && g_mPlib_wade_disabled && !borderlessWasEnabled) {
        aBC_RequestNearbyRefresh();
    }
    pc_audio_set_master_volume(g_pc_settings.master_volume);
}

void apply_runtime_settings(bool refreshGameplay)
{
    apply_settings_bridge(refreshGameplay);

    constexpr int kAxisMaximum = 32767;
    for (u32 port = 0; port < PAD_MAX_CONTROLLERS; ++port) {
        PADDeadZones* deadZones = PADGetDeadZones(port);
        if (deadZones == nullptr) {
            continue;
        }
        deadZones->stickDeadZone = static_cast<u16>(
            settings().input.stickDeadzone.value() * kAxisMaximum / 100);
        deadZones->substickDeadZone = static_cast<u16>(
            settings().input.cstickDeadzone.value() * kAxisMaximum / 100);
        deadZones->useDeadzones = deadZones->stickDeadZone != 0 || deadZones->substickDeadZone != 0;
    }
}

bool save_settings()
{
    apply_settings_bridge(false);
    return config::save();
}

void shutdown_settings()
{
    config::shutdown();
}

} // namespace acgc
