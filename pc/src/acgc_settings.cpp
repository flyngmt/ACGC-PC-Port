#include "acgc/settings.hpp"
#include <aurora/pad.hpp>
#include <aurora/gfx.h>
#include <borealis/config_codec.hpp>

#include "ac_birth_control.h"
#include "dolphin/pad.h"
#include "m_player_lib.h"
#include "pc_settings.h"
#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <borealis/ui/ui.hpp>
#include "extern/aurora/lib/window.hpp"

#include <algorithm>
#include <charconv>
#include <fstream>
#include <optional>
#include <memory>
#include <set>
#include <string_view>

constexpr auto config_enum_values(AuroraBackend)
{
    return borealis::config::enum_table<AuroraBackend>({
        { BACKEND_AUTO, "auto" },
        { BACKEND_D3D11, "d3d11" },
        { BACKEND_D3D12, "d3d12" },
        { BACKEND_METAL, "metal" },
        { BACKEND_VULKAN, "vulkan" },
        { BACKEND_OPENGL, "opengl" },
        { BACKEND_OPENGLES, "opengles" },
        { BACKEND_WEBGPU, "webgpu" },
        { BACKEND_NULL, "null" },
    });
}

constexpr borealis::Log Log{ "acgc::config" };

extern "C" {
void pc_audio_set_master_volume(int volume);
extern int g_pc_frame_limit_override;
int mEv_CheckFirstIntro(void);

PCSettings g_pc_settings = {
    1280,
    960,
    0,
    1,
    60,
    0,
    0,
    0,
    1,
    1,
    100,
    12,
    12,
    1,
};
}

namespace acgc {
namespace {

std::unique_ptr<UserSettings> s_settings;
std::vector<borealis::config::Connection> s_runtimeConnections;
bool s_windowSizeChanged = false;

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
    if (key == "window_width" && value >= 640) {
        current.video.windowWidth.set(value);
    } else if (key == "window_height" && value >= 480) {
        current.video.windowHeight.set(value);
    } else if (key == "fullscreen" && value >= 0 && value <= 2) {
        current.video.windowMode.set(value);
    } else if (key == "vsync" && (value == 0 || value == 1)) {
        current.video.vsync.set(value != 0);
    } else if (key == "max_fps" && value >= 0 && value <= 1000) {
        current.video.maxFrameRate.set(value);
    } else if (key == "preload_textures" && value >= 0 && value <= 2) {
        current.enhancements.preloadTextures.set(value);
    } else if (key == "disable_resetti" && (value == 0 || value == 1)) {
        current.enhancements.disableResetti.set(value != 0);
    } else if (key == "disable_shop_visitor_req" && (value == 0 || value == 1)) {
        current.enhancements.disableShopVisitorRequirement.set(value != 0);
    } else if (key == "borderless_acres" && (value == 0 || value == 1)) {
        current.enhancements.borderlessAcres.set(value != 0);
    } else if (key == "nes_aspect" && (value == 0 || value == 1)) {
        current.enhancements.pillarboxNes.set(value != 0);
    } else if (key == "master_volume" && value >= 0 && value <= 100) {
        current.audio.masterVolume.set(value);
    } else if (key == "stick_deadzone" && value >= 0 && value <= 40) {
        current.input.stickDeadzone.set(value);
    } else if (key == "cstick_deadzone" && value >= 0 && value <= 40) {
        current.input.cstickDeadzone.set(value);
    } else {
        return false;
    }
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
        Log.warn(
            "Legacy settings file '{}' contained no recognized values", borealis::io::fs_path_to_string(path).c_str());
        return false;
    }
    Log.info("Imported {} settings from legacy file {}", imported, borealis::io::fs_path_to_string(path).c_str());
    return true;
}

AuroraBackend sanitize_renderer(AuroraBackend value)
{
    const auto renderers = available_renderer_backends();
    return std::find(renderers.begin(), renderers.end(), value) != renderers.end() ? value : BACKEND_AUTO;
}

int sanitize_ui_scale(int value)
{
    return value == 0 ? 0 : std::clamp(value, 50, 200);
}

template <typename T> void migrate_enum(nlohmann::json& root, const char* key)
{
    const auto value = root.find(key);
    if (value == root.end() || !value->is_number()) {
        return;
    }
    try {
        *value = borealis::config::Codec<T>::encode(borealis::config::Codec<T>::decode(*value));
    } catch (const std::exception&) {
        // The registry reports invalid values and preserves them for a future correction.
    }
}

void migrate_settings(nlohmann::json& root, int)
{
    migrate_enum<DiscVerificationState>(root, "backend.discVerification");
    migrate_enum<InterfaceTheme>(root, "video.theme");
    migrate_enum<AuroraBackend>(root, "video.renderer");
}

void apply_controller_settings()
{
    if (const auto source = aurora::pad::port_controller(0)) {
        const auto target = aurora::pad::ProfileTarget::controller(source);
        if (const auto* profile = aurora::pad::profile(target)) {
            auto values = profile->settings;
            values.leftStickDeadZone = settings().input.stickDeadzone.get() / 100.f;
            values.rightStickDeadZone = settings().input.cstickDeadzone.get() / 100.f;
            values.useDeadzones = values.leftStickDeadZone != 0.f || values.rightStickDeadZone != 0.f;
            if (values != profile->settings) {
                aurora::pad::set_settings(target, values);
            }
        }
    }
}

} // namespace

UserSettings::Backend::Backend(borealis::config::Registry& registry)
    : discPath(registry, "backend.discPath", std::string("game.rvz")),
      discVerification(registry, "backend.discVerification", DiscVerificationState::Unknown),
      skipPrelaunch(registry, "backend.skipPrelaunch", false),
      checkForUpdates(registry, "backend.checkForUpdates", true)
{
}

UserSettings::Video::Video(borealis::config::Registry& registry)
    : renderer(registry, "video.renderer", BACKEND_AUTO, { .sanitize = sanitize_renderer }),
      windowWidth(registry, "video.windowWidth", 1280, { .min = 320, .max = 16384 }),
      windowHeight(registry, "video.windowHeight", 960, { .min = 240, .max = 16384 }),
      windowMode(registry, "video.windowMode", 0, { .min = 0, .max = 2 }),
      uiScale(registry, "video.uiScale", 0, { .sanitize = sanitize_ui_scale }),
      theme(registry, "video.theme", InterfaceTheme::Dynamic), vsync(registry, "video.vsync", true),
      maxFrameRate(registry, "video.maxFrameRate", 60, { .min = 0, .max = 1000 }),
      hudAtEdges(registry, "video.hudAtEdges", false)
{
}

UserSettings::Enhancements::Enhancements(borealis::config::Registry& registry)
    : preloadTextures(registry, "enhancements.preloadTextures", 0, { .min = 0, .max = 2 }),
      disableResetti(registry, "gameplay.disableResetti", false),
      disableShopVisitorRequirement(registry, "gameplay.disableShopVisitorRequirement", false),
      borderlessAcres(registry, "gameplay.borderlessAcres", true),
      pillarboxNes(registry, "gameplay.pillarboxNes", true), fastText(registry, "gameplay.fastText", true),
      reduceTravelMoveOut(registry, "gameplay.reduceTravelMoveOut", false)
{
}

UserSettings::Audio::Audio(borealis::config::Registry& registry)
    : masterVolume(registry, "audio.masterVolume", 100, { .min = 0, .max = 100 })
{
}

UserSettings::Input::Input(borealis::config::Registry& registry)
    : stickDeadzone(registry, "input.stickDeadzone", 12, { .min = 0, .max = 40 }),
      cstickDeadzone(registry, "input.cstickDeadzone", 12, { .min = 0, .max = 40 }),
      autoAssignController(registry, "input.autoAssignController", true),
      singlePortMigrated(registry, "input.singlePortMigrated", false)
{
}

UserSettings::UserSettings()
    : backend(registry), video(registry), enhancements(registry), audio(registry), input(registry)
{
}

UserSettings& settings()
{
    if (!s_settings) {
        s_settings = std::make_unique<UserSettings>();
    }
    return *s_settings;
}

std::vector<AuroraBackend> available_renderer_backends()
{
    std::vector<AuroraBackend> result{ BACKEND_AUTO };
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

SettingsLoadResult load_settings(
    const std::filesystem::path& userDirectory, const std::vector<std::filesystem::path>& legacyCandidates)
{
    s_runtimeConnections.clear();
    s_windowSizeChanged = false;
    s_settings = std::make_unique<UserSettings>();
    SettingsLoadResult result{
        .canonicalResult = settings().registry.load({
            .path = userDirectory / "config.json",
            .version = 1,
            .migrate = migrate_settings,
        }),
    };
    if (result.canonicalResult.code == borealis::config::ErrorCode::FileMissing) {
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

    apply_settings_bridge(false);
    if (result.canonicalResult.code == borealis::config::ErrorCode::FileMissing) {
        settings().registry.save();
    }
    return result;
}

void apply_settings_bridge(bool refreshGameplay)
{
    const auto& current = settings();
    const bool borderlessWasEnabled = g_mPlib_wade_disabled != 0;
    g_pc_settings.window_width = current.video.windowWidth.get();
    g_pc_settings.window_height = current.video.windowHeight.get();
    g_pc_settings.fullscreen = current.video.windowMode.get();
    g_pc_settings.vsync = current.video.vsync.get() ? 1 : 0;
    g_pc_settings.max_fps = current.video.maxFrameRate.get();
    g_pc_settings.hud_at_edges = current.video.hudAtEdges.get() ? 1 : 0;
    g_pc_settings.preload_textures = current.enhancements.preloadTextures.get();
    g_pc_settings.disable_resetti = current.enhancements.disableResetti.get() ? 1 : 0;
    g_pc_settings.disable_shop_visitor_req = current.enhancements.disableShopVisitorRequirement.get() ? 1 : 0;
    g_pc_settings.borderless_acres = current.enhancements.borderlessAcres.get() ? 1 : 0;
    g_pc_settings.nes_aspect = current.enhancements.pillarboxNes.get() ? 1 : 0;
    g_pc_settings.fast_text = current.enhancements.fastText.get() ? 1 : 0;
    g_pc_settings.reduce_travel_move_out = current.enhancements.reduceTravelMoveOut.get() ? 1 : 0;
    g_pc_settings.master_volume = current.audio.masterVolume.get();
    g_pc_settings.stick_deadzone = current.input.stickDeadzone.get();
    g_pc_settings.cstick_deadzone = current.input.cstickDeadzone.get();
    // Keep the introduction's acre restriction when unrelated settings are applied. Otherwise softlocks the intro.
    g_mPlib_wade_disabled = g_pc_settings.borderless_acres && !mEv_CheckFirstIntro() && !g_mPlib_wade_suspended;
    if (refreshGameplay && g_mPlib_wade_disabled && !borderlessWasEnabled) {
        aBC_RequestNearbyRefresh();
    }
    pc_audio_set_master_volume(g_pc_settings.master_volume);
}

void apply_ui_scale()
{
    borealis::ui::set_user_scale(settings().video.uiScale.get());
}

void apply_runtime_settings(bool refreshGameplay)
{
    apply_settings_bridge(refreshGameplay);
    apply_ui_scale();
    apply_controller_settings();
}

void observe_runtime_settings()
{
    s_runtimeConnections.clear();
    auto& current = settings();
    current.registry.for_each([](borealis::config::VarBase& var) {
        s_runtimeConnections.push_back(var.on_change([] {
            apply_settings_bridge(true);
        }));
    });
    s_runtimeConnections.push_back(current.video.windowMode.on_change([](int mode) {
        aurora::window::set_fullscreen(mode != 0);
    }));
    s_runtimeConnections.push_back(current.video.windowWidth.on_change([] {
        s_windowSizeChanged = true;
    }));
    s_runtimeConnections.push_back(current.video.windowHeight.on_change([] {
        s_windowSizeChanged = true;
    }));
    s_runtimeConnections.push_back(current.video.uiScale.on_change(apply_ui_scale));
    s_runtimeConnections.push_back(current.video.vsync.on_change([](bool value) {
        aurora_enable_vsync(value);
    }));
    s_runtimeConnections.push_back(current.video.maxFrameRate.on_change([](int value) {
        g_pc_frame_limit_override = value;
    }));
    s_runtimeConnections.push_back(current.input.stickDeadzone.on_change(apply_controller_settings));
    s_runtimeConnections.push_back(current.input.cstickDeadzone.on_change(apply_controller_settings));
    apply_runtime_settings(false);
}

void set_window_size(int width, int height)
{
    auto& video = settings().video;
    video.windowWidth.set(width);
    video.windowHeight.set(height);
    // Apply also replaces a temporary --window-size, even if the saved dimensions did not change.
    s_windowSizeChanged = true;
}

void set_frame_limit(int value)
{
    settings().video.maxFrameRate.set(value);
    // An explicit edit replaces --framelimit even when it equals the saved value.
    g_pc_frame_limit_override = settings().video.maxFrameRate.get();
}

void update_settings()
{
    if (s_windowSizeChanged) {
        s_windowSizeChanged = false;
        const auto& video = settings().video;
        aurora::window::set_window_size(video.windowWidth.get(), video.windowHeight.get());
    }
    settings().registry.update();
}

bool save_settings()
{
    const auto status = settings().registry.flush();
    if (!status) {
        Log.warn("Could not save settings: {}", status.message);
    }
    return static_cast<bool>(status);
}

void shutdown_settings()
{
    s_runtimeConnections.clear();
    s_windowSizeChanged = false;
    if (s_settings) {
        save_settings();
        s_settings.reset();
    }
}

} // namespace acgc
