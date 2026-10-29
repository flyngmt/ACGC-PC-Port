#include "acgc/settings.hpp"
#include <aurora/pad.hpp>

#include "acgc/config.hpp"
#include "ac_birth_control.h"
#include "dolphin/pad.h"
#include "m_player_lib.h"
#include "pc_settings.h"
#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <aurora/rmlui.hpp>
#include "extern/aurora/lib/window.hpp"

#include <algorithm>
#include <charconv>
#include <fstream>
#include <optional>
#include <set>
#include <string_view>

constexpr borealis::Log Log{"acgc::config"};

extern "C" {
void pc_audio_set_master_volume(int volume);
int mEv_CheckFirstIntro(void);

PCSettings g_pc_settings = {
    1280, 960, 0, 1, 60, 0, 0, 0, 1, 1, 100, 12, 12, 1,
};
}

namespace acgc {
namespace {

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
        Log.warn("Legacy settings file '{}' contained no recognized values",
                        borealis::io::fs_path_to_string(path).c_str());
        return false;
    }
    Log.info("Imported {} settings from legacy file {}",
                    imported, borealis::io::fs_path_to_string(path).c_str());
    return true;
}

void sanitize_settings()
{
    auto& current = settings();
    const auto verification = static_cast<int>(current.backend.discVerification.value());
    if (verification < static_cast<int>(DiscVerificationState::Unknown) ||
        verification > static_cast<int>(DiscVerificationState::HashMismatch)) {
        current.backend.discVerification.set_value(DiscVerificationState::Unknown);
    }
    const auto theme = static_cast<int>(current.video.theme.value());
    if (theme < static_cast<int>(InterfaceTheme::Dynamic) || theme > static_cast<int>(InterfaceTheme::Night)) {
        current.video.theme.set_value(InterfaceTheme::Dynamic);
    }
    const auto renderers = available_renderer_backends();
    if (std::find(renderers.begin(), renderers.end(), current.video.renderer.value()) == renderers.end()) {
        current.video.renderer.set_value(BACKEND_AUTO);
    }
    current.video.windowWidth.set_value(std::clamp(current.video.windowWidth.value(), 320, 16384));
    current.video.windowHeight.set_value(std::clamp(current.video.windowHeight.value(), 240, 16384));
    current.video.windowMode.set_value(std::clamp(current.video.windowMode.value(), 0, 2));
    const int uiScale = current.video.uiScale.value();
    current.video.uiScale.set_value(uiScale == 0 ? 0 : std::clamp(uiScale, 50, 200));
    current.video.maxFrameRate.set_value(std::clamp(current.video.maxFrameRate.value(), 0, 1000));
    current.enhancements.preloadTextures.set_value(std::clamp(current.enhancements.preloadTextures.value(), 0, 2));
    current.audio.masterVolume.set_value(std::clamp(current.audio.masterVolume.value(), 0, 100));
    current.input.stickDeadzone.set_value(std::clamp(current.input.stickDeadzone.value(), 0, 40));
    current.input.cstickDeadzone.set_value(std::clamp(current.input.cstickDeadzone.value(), 0, 40));
}

} // namespace

UserSettings::Backend::Backend()
    : discPath("backend.discPath", std::string("game.rvz"))
    , discVerification("backend.discVerification", DiscVerificationState::Unknown)
    , skipPrelaunch("backend.skipPrelaunch", false)
    , checkForUpdates("backend.checkForUpdates", true)
{
}

UserSettings::Video::Video()
    : renderer("video.renderer", BACKEND_AUTO)
    , windowWidth("video.windowWidth", 1280)
    , windowHeight("video.windowHeight", 960)
    , windowMode("video.windowMode", 0)
    , uiScale("video.uiScale", 0)
    , theme("video.theme", InterfaceTheme::Dynamic)
    , vsync("video.vsync", true)
    , maxFrameRate("video.maxFrameRate", 60)
    , hudAtEdges("video.hudAtEdges", false)
{
}

UserSettings::Enhancements::Enhancements()
    : preloadTextures("enhancements.preloadTextures", 0)
    , disableResetti("gameplay.disableResetti", false)
    , disableShopVisitorRequirement("gameplay.disableShopVisitorRequirement", false)
    , borderlessAcres("gameplay.borderlessAcres", true)
    , pillarboxNes("gameplay.pillarboxNes", true)
    , fastText("gameplay.fastText", true)
    , reduceTravelMoveOut("gameplay.reduceTravelMoveOut", false)
{
}

UserSettings::Audio::Audio()
    : masterVolume("audio.masterVolume", 100)
{
}

UserSettings::Input::Input()
    : stickDeadzone("input.stickDeadzone", 12)
    , cstickDeadzone("input.cstickDeadzone", 12)
    , autoAssignController("input.autoAssignController", true)
    , singlePortMigrated("input.singlePortMigrated", false)
{
}

UserSettings& settings()
{
    static UserSettings value;
    return value;
}

std::vector<AuroraBackend> available_renderer_backends()
{
    std::vector<AuroraBackend> result{BACKEND_AUTO};
    size_t count = 0;
    const AuroraBackend* backends = aurora_get_available_backends(&count);
    for (size_t i = 0; i < count; ++i) {
        const AuroraBackend backend = backends[i];
        if (backend != BACKEND_AUTO && backend != BACKEND_NULL &&
            std::find(result.begin(), result.end(), backend) == result.end()) {
            result.push_back(backend);
        }
    }
    return result;
}

void register_settings()
{
    auto& current = settings();
    config::register_var(current.backend.discPath);
    config::register_var(current.backend.discVerification);
    config::register_var(current.backend.skipPrelaunch);
    config::register_var(current.backend.checkForUpdates);
    config::register_var(current.video.renderer);
    config::register_var(current.video.windowWidth);
    config::register_var(current.video.windowHeight);
    config::register_var(current.video.windowMode);
    config::register_var(current.video.uiScale);
    config::register_var(current.video.theme);
    config::register_var(current.video.vsync);
    config::register_var(current.video.maxFrameRate);
    config::register_var(current.video.hudAtEdges);
    config::register_var(current.enhancements.preloadTextures);
    config::register_var(current.enhancements.disableResetti);
    config::register_var(current.enhancements.disableShopVisitorRequirement);
    config::register_var(current.enhancements.borderlessAcres);
    config::register_var(current.enhancements.pillarboxNes);
    config::register_var(current.enhancements.fastText);
    config::register_var(current.enhancements.reduceTravelMoveOut);
    config::register_var(current.audio.masterVolume);
    config::register_var(current.input.stickDeadzone);
    config::register_var(current.input.cstickDeadzone);
    config::register_var(current.input.autoAssignController);
    config::register_var(current.input.singlePortMigrated);
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
    g_pc_settings.hud_at_edges = current.video.hudAtEdges.value() ? 1 : 0;
    g_pc_settings.preload_textures = current.enhancements.preloadTextures.value();
    g_pc_settings.disable_resetti = current.enhancements.disableResetti.value() ? 1 : 0;
    g_pc_settings.disable_shop_visitor_req = current.enhancements.disableShopVisitorRequirement.value() ? 1 : 0;
    g_pc_settings.borderless_acres = current.enhancements.borderlessAcres.value() ? 1 : 0;
    g_pc_settings.nes_aspect = current.enhancements.pillarboxNes.value() ? 1 : 0;
    g_pc_settings.fast_text = current.enhancements.fastText.value() ? 1 : 0;
    g_pc_settings.reduce_travel_move_out = current.enhancements.reduceTravelMoveOut.value() ? 1 : 0;
    g_pc_settings.master_volume = current.audio.masterVolume.value();
    g_pc_settings.stick_deadzone = current.input.stickDeadzone.value();
    g_pc_settings.cstick_deadzone = current.input.cstickDeadzone.value();
    // Keep the introduction's acre restriction when unrelated settings are applied. Otherwise softlocks the intro.
    g_mPlib_wade_disabled = g_pc_settings.borderless_acres && !mEv_CheckFirstIntro();
    if (refreshGameplay && g_mPlib_wade_disabled && !borderlessWasEnabled) {
        aBC_RequestNearbyRefresh();
    }
    pc_audio_set_master_volume(g_pc_settings.master_volume);
}

void apply_ui_scale()
{
    const int uiScale = settings().video.uiScale.value();
    float scale = 0.0f;
    if (uiScale != 0) {
        const float displayScale = aurora::window::get_window_size().scale;
        scale = static_cast<float>(uiScale) / 100.0f * (displayScale > 0.0f ? displayScale : 1.0f);
    }
    aurora::rmlui::set_ui_scale(scale);
}

void apply_runtime_settings(bool refreshGameplay)
{
    apply_settings_bridge(refreshGameplay);
    apply_ui_scale();

    if (const auto source = aurora::pad::port_controller(0)) {
        const auto target = aurora::pad::ProfileTarget::controller(source);
        if (const auto* profile = aurora::pad::profile(target)) {
            auto values = profile->settings;
            values.leftStickDeadZone = settings().input.stickDeadzone.value() / 100.f;
            values.rightStickDeadZone = settings().input.cstickDeadzone.value() / 100.f;
            values.useDeadzones = values.leftStickDeadZone != 0.f || values.rightStickDeadZone != 0.f;
            if (values != profile->settings) aurora::pad::set_settings(target, values);
        }
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
