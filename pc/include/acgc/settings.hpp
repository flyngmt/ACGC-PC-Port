#pragma once

#include "acgc/config.hpp"

#include <aurora/aurora.h>

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace acgc {

using config::ConfigVar;

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

struct UserSettings {
    struct Backend {
        ConfigVar<std::string> discPath;
        ConfigVar<DiscVerificationState> discVerification;
        ConfigVar<bool> skipPrelaunch;
        ConfigVar<bool> checkForUpdates;

        Backend();
    } backend;

    struct Video {
        ConfigVar<AuroraBackend> renderer;
        ConfigVar<int> windowWidth;
        ConfigVar<int> windowHeight;
        ConfigVar<int> windowMode;
        ConfigVar<int> uiScale;
        ConfigVar<InterfaceTheme> theme;
        ConfigVar<bool> vsync;
        ConfigVar<int> maxFrameRate;

        Video();
    } video;

    struct Enhancements {
        ConfigVar<int> preloadTextures;
        ConfigVar<bool> disableResetti;
        ConfigVar<bool> disableShopVisitorRequirement;
        ConfigVar<bool> borderlessAcres;
        ConfigVar<bool> pillarboxNes;
        ConfigVar<bool> fastText;
        ConfigVar<bool> reduceTravelMoveOut;

        Enhancements();
    } enhancements;

    struct Audio {
        ConfigVar<int> masterVolume;

        Audio();
    } audio;

    struct Input {
        ConfigVar<int> stickDeadzone;
        ConfigVar<int> cstickDeadzone;
        ConfigVar<bool> autoAssignController;
        ConfigVar<bool> singlePortMigrated;

        Input();
    } input;
};

struct SettingsLoadResult {
    config::LoadResult canonicalResult;
    bool importedLegacy = false;
    std::filesystem::path legacyPath;
};

UserSettings& settings();
std::vector<AuroraBackend> available_renderer_backends();
void register_settings();
SettingsLoadResult load_settings(const std::filesystem::path& userDirectory,
                                 const std::vector<std::filesystem::path>& legacyCandidates);
void apply_settings_bridge(bool refreshGameplay);
void apply_runtime_settings(bool refreshGameplay);
void apply_ui_scale();
bool save_settings();
void shutdown_settings();

} // namespace acgc
