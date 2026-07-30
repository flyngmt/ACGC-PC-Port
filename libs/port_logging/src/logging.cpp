#include "port/logging.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <mutex>
#include <string>
#include <string_view>
#include <vector>

#if defined(__ANDROID__)
#include <android/log.h>
#endif

#if defined(_WIN32)
#include <io.h>
#define PORT_FILENO _fileno
#else
#include <unistd.h>
#define PORT_FILENO fileno
#endif

namespace {

constexpr uint32_t kDefaultRetainedFiles = 10;
constexpr uint64_t kDefaultRetainedBytes = 100ull * 1024ull * 1024ull;

struct LogFileCandidate {
    std::filesystem::path path;
    std::string filename;
    uintmax_t size;
};

struct LogState {
    std::mutex mutex;
    FILE* file = nullptr;
    std::string file_path;
    std::string filename_prefix = "port";
    AuroraLogLevel minimum_level = LOG_INFO;
    bool write_console = true;

    void close_file_locked()
    {
        if (file == nullptr) {
            return;
        }
        std::fflush(file);
        std::fclose(file);
        file = nullptr;
    }
};

/* Deliberately process-lifetime storage. Explicit shutdown closes the file,
 * while avoiding static-destruction order races from late Aurora logging. */
LogState& state()
{
    static LogState* value = new LogState;
    return *value;
}

const char* level_name(AuroraLogLevel level)
{
    switch (level) {
    case LOG_DEBUG:
        return "DEBUG";
    case LOG_INFO:
        return "INFO";
    case LOG_WARNING:
        return "WARNING";
    case LOG_ERROR:
        return "ERROR";
    case LOG_FATAL:
        return "FATAL";
    }
    return "UNKNOWN";
}

#if defined(__ANDROID__)
int android_priority(AuroraLogLevel level)
{
    switch (level) {
    case LOG_DEBUG:
        return ANDROID_LOG_DEBUG;
    case LOG_INFO:
        return ANDROID_LOG_INFO;
    case LOG_WARNING:
        return ANDROID_LOG_WARN;
    case LOG_ERROR:
        return ANDROID_LOG_ERROR;
    case LOG_FATAL:
        return ANDROID_LOG_FATAL;
    }
    return ANDROID_LOG_UNKNOWN;
}
#endif

std::string sanitize_prefix(const char* prefix)
{
    std::string result = prefix != nullptr ? prefix : "port";
    if (result.empty()) {
        result = "port";
    }
    for (char& character : result) {
        const unsigned char value = static_cast<unsigned char>(character);
        if (std::isalnum(value) == 0 && character != '-' && character != '_') {
            character = '-';
        }
    }
    return result;
}

std::string path_to_utf8(const std::filesystem::path& path)
{
    const std::u8string value = path.u8string();
    return std::string(reinterpret_cast<const char*>(value.data()), value.size());
}

FILE* open_log_file(const std::filesystem::path& path)
{
#if defined(_WIN32)
    return _wfopen(path.c_str(), L"wb");
#else
    return std::fopen(path.c_str(), "wb");
#endif
}

std::string timestamped_name(const std::string& prefix)
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time {};
#if defined(_WIN32)
    localtime_s(&local_time, &now_time);
#else
    localtime_r(&now_time, &local_time);
#endif
    std::array<char, 32> timestamp {};
    std::strftime(timestamp.data(), timestamp.size(), "%Y%m%d-%H%M%S", &local_time);
    return prefix + "-" + timestamp.data() + ".log";
}

bool generated_log_name(std::string_view filename, std::string_view prefix)
{
    const std::string expected_prefix = std::string(prefix) + "-";
    if (!filename.starts_with(expected_prefix) || !filename.ends_with(".log")) {
        return false;
    }
    const std::string_view stamp = filename.substr(expected_prefix.size());
    if (stamp.size() != 19 || stamp[8] != '-' || stamp.substr(15) != ".log") {
        return false;
    }
    for (size_t index = 0; index < 15; ++index) {
        if (index == 8) {
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(stamp[index])) == 0) {
            return false;
        }
    }
    return true;
}

void raw_warning(const char* action, const std::filesystem::path& path,
                 const std::error_code& error)
{
    std::fprintf(stderr, "[WARNING | logging] Failed to %s '%s': %s\n", action,
                 path_to_utf8(path).c_str(), error.message().c_str());
}

void prune_logs(const std::filesystem::path& directory, const std::string& prefix,
                uint32_t retained_files, uint64_t retained_bytes)
{
    std::error_code error;
    std::filesystem::directory_iterator entries(directory, error);
    if (error) {
        raw_warning("inspect log directory", directory, error);
        return;
    }

    std::vector<LogFileCandidate> candidates;
    for (const auto& entry : entries) {
        const auto path = entry.path();
        const std::string filename = path.filename().string();
        if (!generated_log_name(filename, prefix)) {
            continue;
        }
        error.clear();
        if (!entry.is_regular_file(error)) {
            if (error) {
                raw_warning("inspect log file", path, error);
            }
            continue;
        }
        error.clear();
        const uintmax_t size = entry.file_size(error);
        if (error) {
            raw_warning("inspect log size", path, error);
            continue;
        }
        candidates.push_back({path, filename, size});
    }

    std::sort(candidates.begin(), candidates.end(),
              [](const LogFileCandidate& left, const LogFileCandidate& right) {
                  return left.filename > right.filename;
              });

    const size_t old_file_limit = retained_files > 0 ? retained_files - 1 : 0;
    size_t keep = std::min(candidates.size(), old_file_limit);
    uintmax_t kept_bytes = 0;
    for (size_t index = 0; index < keep; ++index) {
        kept_bytes += candidates[index].size;
    }
    while (keep > 0 && kept_bytes > retained_bytes) {
        --keep;
        kept_bytes -= candidates[keep].size;
    }
    for (size_t index = keep; index < candidates.size(); ++index) {
        error.clear();
        std::filesystem::remove(candidates[index].path, error);
        if (error) {
            raw_warning("remove old log", candidates[index].path, error);
        }
    }
}

template <typename Callback>
void for_each_line(const char* message, size_t length, Callback&& callback)
{
    size_t offset = 0;
    while (offset < length) {
        size_t end = offset;
        while (end < length && message[end] != '\n') {
            ++end;
        }
        size_t line_length = end - offset;
        if (line_length > 0 && message[offset + line_length - 1] == '\r') {
            --line_length;
        }
        callback(message + offset, line_length);
        offset = end < length ? end + 1 : end;
    }
    if (length == 0) {
        callback("", 0);
    }
}

void write_stream_line(FILE* stream, const char* level, const char* module,
                       const char* message, size_t length)
{
    if (stream == nullptr) {
        return;
    }
    std::fprintf(stream, "[%s | %s] ", level, module);
    std::fwrite(message, 1, length, stream);
    std::fputc('\n', stream);
}

void write_locked(LogState& log, AuroraLogLevel level, const char* module,
                  const char* message, size_t length)
{
    const char* safe_module = module != nullptr && module[0] != '\0' ? module : "app";
    const char* level_text = level_name(level);
    for_each_line(message != nullptr ? message : "", message != nullptr ? length : 0,
                  [&](const char* line, size_t line_length) {
#if defined(__ANDROID__)
                      std::string android_line(line, line_length);
                      __android_log_write(android_priority(level), safe_module,
                                          android_line.c_str());
#else
                      if (log.write_console) {
                          FILE* stream = level >= LOG_ERROR ? stderr : stdout;
                          write_stream_line(stream, level_text, safe_module, line, line_length);
                          std::fflush(stream);
                      }
#endif
                      if (log.file != nullptr) {
                          write_stream_line(log.file, level_text, safe_module, line, line_length);
                      }
                  });
    if (log.file != nullptr) {
        std::fflush(log.file);
    }
}

} // namespace

extern "C" bool port_log_initialize(const PortLogConfig* config)
{
    LogState& log = state();
    std::lock_guard lock(log.mutex);
    log.close_file_locked();
    log.file_path.clear();
    log.filename_prefix = sanitize_prefix(config != nullptr ? config->filename_prefix : nullptr);
    log.minimum_level = config != nullptr ? config->minimum_level : LOG_INFO;
    log.write_console = config == nullptr || config->write_console;

    if (config == nullptr || config->log_directory == nullptr ||
        config->log_directory[0] == '\0') {
        return true;
    }

    const auto* directory_utf8 = reinterpret_cast<const char8_t*>(config->log_directory);
    const std::filesystem::path directory(directory_utf8);
    std::error_code error;
    std::filesystem::create_directories(directory, error);
    if (error) {
        raw_warning("create log directory", directory, error);
        return false;
    }

    const uint32_t retained_files = config->max_retained_files != 0
        ? config->max_retained_files
        : kDefaultRetainedFiles;
    const uint64_t retained_bytes = config->max_retained_bytes != 0
        ? config->max_retained_bytes
        : kDefaultRetainedBytes;
    prune_logs(directory, log.filename_prefix, retained_files, retained_bytes);

    const std::filesystem::path path = directory / timestamped_name(log.filename_prefix);
    log.file = open_log_file(path);
    if (log.file == nullptr) {
        std::fprintf(stderr, "[WARNING | logging] Failed to open log file '%s'\n",
                     path_to_utf8(path).c_str());
        return false;
    }
    log.file_path = path_to_utf8(path);
    constexpr char initialized[] = "File logging initialized";
    write_locked(log, LOG_INFO, "logging", initialized, sizeof(initialized) - 1);
    return true;
}

extern "C" void port_log_shutdown(void)
{
    LogState& log = state();
    std::lock_guard lock(log.mutex);
    log.close_file_locked();
    log.file_path.clear();
}

extern "C" const char* port_log_file_path(void)
{
    LogState& log = state();
    std::lock_guard lock(log.mutex);
    return log.file_path.empty() ? nullptr : log.file_path.c_str();
}

extern "C" int port_log_file_descriptor(void)
{
    LogState& log = state();
    std::lock_guard lock(log.mutex);
    return log.file != nullptr ? PORT_FILENO(log.file) : -1;
}

extern "C" void port_log_message(AuroraLogLevel level, const char* module,
                                  const char* message, unsigned int length)
{
    LogState& log = state();
    {
        std::lock_guard lock(log.mutex);
        if (level >= log.minimum_level || level == LOG_FATAL) {
            write_locked(log, level, module, message, length);
        }
    }
    if (level == LOG_FATAL) {
        std::abort();
    }
}

extern "C" void port_log_callback(AuroraLogLevel level, const char* module,
                                   const char* message, unsigned int length)
{
    port_log_message(level, module, message, length);
}

extern "C" void port_log_vprintf(AuroraLogLevel level, const char* module,
                                  const char* format, va_list arguments)
{
    if (format == nullptr) {
        port_log_message(level, module, "", 0);
        return;
    }

    va_list count_arguments;
    va_copy(count_arguments, arguments);
    const int length = std::vsnprintf(nullptr, 0, format, count_arguments);
    va_end(count_arguments);
    if (length < 0) {
        constexpr char failure[] = "Log message formatting failed";
        port_log_message(LOG_ERROR, "logging", failure, sizeof(failure) - 1);
        return;
    }

    std::vector<char> buffer(static_cast<size_t>(length) + 1);
    va_list write_arguments;
    va_copy(write_arguments, arguments);
    const int written = std::vsnprintf(buffer.data(), buffer.size(), format, write_arguments);
    va_end(write_arguments);
    if (written < 0) {
        constexpr char failure[] = "Log message formatting failed";
        port_log_message(LOG_ERROR, "logging", failure, sizeof(failure) - 1);
        return;
    }
    port_log_message(level, module, buffer.data(), static_cast<unsigned int>(written));
}

extern "C" void port_log_printf(AuroraLogLevel level, const char* module,
                                 const char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    port_log_vprintf(level, module, format, arguments);
    va_end(arguments);
}
