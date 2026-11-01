#pragma once

#include "acgc/ui/touch_layout.hpp"

#include <borealis/config.hpp>

#include <aurora/aurora.h>

#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS && !TARGET_OS_MACCATALYST) || defined(__ANDROID__)
#define ACGC_HAS_WINDOW_CONTROLS 0
#else
#define ACGC_HAS_WINDOW_CONTROLS 1
#endif

namespace acgc {

enum class DiscVerificationState : std::uint8_t {
    Unknown = 0,
    Success,
    HashMismatch,
};

enum class InterfaceTheme : std::uint8_t {
    Dynamic = 0,
    Day,
    Night,
};

enum class TravelMoveOutChance : std::uint8_t {
    Ten = 0,
    Fifty,
    Default,
};

constexpr auto config_enum_values(DiscVerificationState)
{
    using enum DiscVerificationState;
    return borealis::config::enum_table<DiscVerificationState>({
        { Unknown, "unknown" },
        { Success, "success" },
        { HashMismatch, "hash_mismatch" },
    });
}

constexpr auto config_enum_values(InterfaceTheme)
{
    using enum InterfaceTheme;
    return borealis::config::enum_table<InterfaceTheme>({
        { Dynamic, "dynamic" },
        { Day, "day" },
        { Night, "night" },
    });
}

constexpr auto config_enum_values(TravelMoveOutChance)
{
    using enum TravelMoveOutChance;
    return borealis::config::enum_table<TravelMoveOutChance>({
        { Ten, "10" },
        { Fifty, "50" },
        { Default, "default" },
    });
}

struct UserSettings {
    borealis::config::Registry registry;

    struct Backend {
        borealis::config::Var<std::string> discPath;
        borealis::config::Var<DiscVerificationState> discVerification;
        borealis::config::Var<bool> skipPrelaunch;
        borealis::config::Var<bool> checkForUpdates;

        explicit Backend(borealis::config::Registry& registry);
    } backend;

    struct Video {
        borealis::config::Var<AuroraBackend> renderer;
        borealis::config::Var<int> windowWidth;
        borealis::config::Var<int> windowHeight;
        borealis::config::Var<int> windowMode;
        borealis::config::Var<int> uiScale;
        borealis::config::Var<InterfaceTheme> theme;
        borealis::config::Var<bool> vsync;
        borealis::config::Var<int> maxFrameRate;
        borealis::config::Var<bool> hudAtEdges;

        explicit Video(borealis::config::Registry& registry);
    } video;

    struct Enhancements {
        borealis::config::Var<int> preloadTextures;
        borealis::config::Var<bool> disableResetti;
        borealis::config::Var<bool> disableShopVisitorRequirement;
        borealis::config::Var<bool> borderlessAcres;
        borealis::config::Var<bool> pillarboxNes;
        borealis::config::Var<bool> fastText;
        borealis::config::Var<TravelMoveOutChance> travelMoveOutChance;

        explicit Enhancements(borealis::config::Registry& registry);
    } enhancements;

    struct Audio {
        borealis::config::Var<int> masterVolume;

        explicit Audio(borealis::config::Registry& registry);
    } audio;

    struct Input {
        borealis::config::Var<int> stickDeadzone;
        borealis::config::Var<int> cstickDeadzone;
        borealis::config::Var<bool> autoAssignController;
        borealis::config::Var<bool> singlePortMigrated;
        borealis::config::Var<bool> allowBackgroundInput;
        borealis::config::Var<bool> touchControls;
        borealis::config::Var<bool> touchHaptics;
        borealis::config::Var<bool> keyboardTyping;
        borealis::config::Var<ui::TouchLayout> touchLayout;

        explicit Input(borealis::config::Registry& registry);
    } input;

    UserSettings();
};

struct SettingsLoadResult {
    borealis::config::Status canonicalResult;
    bool importedLegacy = false;
    std::filesystem::path legacyPath;
};

struct WindowResolution {
    int width;
    int height;
};

inline constexpr std::array kWindowResolutions = {
    WindowResolution{ 640, 480 },   WindowResolution{ 800, 600 },   WindowResolution{ 960, 720 },
    WindowResolution{ 1024, 768 },  WindowResolution{ 1152, 864 },  WindowResolution{ 1280, 960 },
    WindowResolution{ 1400, 1050 }, WindowResolution{ 1600, 1200 }, WindowResolution{ 1280, 720 },
    WindowResolution{ 1366, 768 },  WindowResolution{ 1600, 900 },  WindowResolution{ 1920, 1080 },
    WindowResolution{ 2560, 1440 }, WindowResolution{ 3840, 2160 },
};

UserSettings& settings();
std::vector<AuroraBackend> available_renderer_backends();
void observe_runtime_settings();
void update_settings();
void set_window_size(int width, int height);
void set_frame_limit(int value);
SettingsLoadResult load_settings(
    const std::filesystem::path& userDirectory, const std::vector<std::filesystem::path>& legacyCandidates);
void apply_settings_bridge(bool refreshGameplay);
void apply_runtime_settings(bool refreshGameplay);
void apply_ui_scale();
bool save_settings();
void shutdown_settings();

} // namespace acgc
