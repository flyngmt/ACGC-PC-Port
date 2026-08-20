#pragma once

#include <borealis/data.hpp>

#include <filesystem>
#include <string>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(_WIN32) || (defined(__APPLE__) && !TARGET_OS_IOS && !TARGET_OS_TV && !TARGET_OS_MACCATALYST) || \
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

using Paths = borealis::data::Paths;

borealis::data::Manager& manager();
Paths initialize(const std::filesystem::path& userDirectoryOverride = {});
std::filesystem::path cache_path();
std::filesystem::path base_path_relative(const std::filesystem::path& path);
std::filesystem::path configured_data_path();
bool open_data_path();
borealis::data::Status set_custom_data_path(const std::filesystem::path& path);
bool reset_data_path();
bool is_default_data_path();
bool is_data_path_restart_pending();
std::string abbreviated_path_string(const std::filesystem::path& path);

} // namespace acgc::data
