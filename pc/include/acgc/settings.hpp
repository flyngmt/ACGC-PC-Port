#pragma once

#include <borealis/config.hpp>

#include <aurora/aurora.h>

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
        borealis::config::Var<bool> reduceTravelMoveOut;

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

        explicit Input(borealis::config::Registry& registry);
    } input;

    UserSettings();
};

struct SettingsLoadResult {
    borealis::config::Status canonicalResult;
    bool importedLegacy = false;
    std::filesystem::path legacyPath;
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
