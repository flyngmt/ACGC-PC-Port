#pragma once

#include <filesystem>
#include <string>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(_WIN32) ||                                                                             \
    (defined(__APPLE__) && !TARGET_OS_IOS && !TARGET_OS_TV && !TARGET_OS_MACCATALYST) ||           \
    (defined(__linux__) && !defined(__ANDROID__))
#define ACGC_CAN_OPEN_DATA_FOLDER 1
#else
#define ACGC_CAN_OPEN_DATA_FOLDER 0
#endif

#if (defined(__APPLE__) && TARGET_OS_IOS && !TARGET_OS_MACCATALYST)
#define ACGC_CAN_CHANGE_DATA_FOLDER 0
#else
#define ACGC_CAN_CHANGE_DATA_FOLDER 1
#endif

namespace acgc::data {

struct Paths {
    std::filesystem::path userPath;
    std::filesystem::path cachePath;
};

/* Resolves the data (user) and cache directories, performing any pending
 * migration recorded in the location descriptor. `userDirOverride` is the
 * --user-dir argument; when non-null it wins over the descriptor and no
 * descriptor is read or written. */
Paths initialize(const char* userDirOverride);

/* The cache directory (the SDL pref path). Unlike the data path this needs no
 * descriptor resolution, so it is safe to call before initialize() — e.g. to
 * pick the log directory before logging starts. */
std::filesystem::path cache_path();

std::filesystem::path base_path_relative(const std::filesystem::path& path);
/* The data path recorded by the descriptor (or the platform default). May
 * differ from the active path until the game restarts. */
std::filesystem::path configured_data_path();
bool open_data_path();
bool set_custom_data_path(const char* path, std::string* errorOut);
bool set_custom_data_path(const std::filesystem::path& path, std::string* errorOut);
bool reset_data_path();
bool is_default_data_path();
bool is_data_path_restart_pending();
std::string abbreviated_path_string(const std::filesystem::path& path);

} // namespace acgc::data
