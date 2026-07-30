#include "acgc/config.hpp"

#include "pc_platform.h"
#include "port/logging.h"

#include <cstring>
#include <fstream>
#include <map>
#include <system_error>

namespace acgc::config {
namespace {

std::map<std::string, ConfigVarBase*, std::less<>> s_registered;
std::filesystem::path s_userDirectory;
nlohmann::json s_root = nlohmann::json::object();

std::string path_string(const std::filesystem::path& path) {
    const std::u8string utf8 = path.u8string();
    return { reinterpret_cast<const char*>(utf8.data()), utf8.size() };
}

} // namespace

ConfigVarBase::ConfigVarBase(std::string name, const ConfigImplBase* implementation)
    : m_name(std::move(name)), m_implementation(implementation) {
}

ConfigVarBase::~ConfigVarBase() {
    if (m_registered) {
        s_registered.erase(m_name);
    }
}

const char* ConfigVarBase::name() const noexcept {
    return m_name.c_str();
}
const ConfigImplBase* ConfigVarBase::implementation() const noexcept {
    return m_implementation;
}
ConfigVarLayer ConfigVarBase::layer() const noexcept {
    return m_layer;
}
void ConfigVarBase::mark_registered() noexcept {
    m_registered = true;
}
void ConfigVarBase::unmark_registered() noexcept {
    m_registered = false;
}

void ConfigVarBase::check_registered() const noexcept {
    if (!m_registered) {
        std::abort();
    }
}

void set_user_directory(std::filesystem::path directory) {
    s_userDirectory = std::move(directory);
}

const std::filesystem::path& user_directory() noexcept {
    return s_userDirectory;
}
std::filesystem::path config_path() {
    return s_userDirectory / "config.json";
}

void register_var(ConfigVarBase& var) {
    const auto [it, inserted] = s_registered.emplace(var.name(), &var);
    if (!inserted && it->second != &var) {
        port_log_printf(LOG_ERROR, "acgc::config", "Duplicate configuration variable '%s'", var.name());
        return;
    }
    var.mark_registered();
}

extern "C" int pc_platform_user_path(const char* relative_path, char* output, size_t output_size) {
    if (relative_path == nullptr || output == nullptr || output_size == 0) {
        return 0;
    }

    const auto path = acgc::config::user_directory() / std::filesystem::path(relative_path);
    const auto utf8 = path.u8string();
    if (utf8.size() + 1 > output_size) {
        return 0;
    }
    std::memcpy(output, utf8.data(), utf8.size());
    output[utf8.size()] = '\0';
    return 1;
}

LoadResult load() {
    const auto path = config_path();
    std::ifstream stream(path);
    if (!stream) {
        std::error_code error;
        if (!std::filesystem::exists(path, error)) {
            return LoadResult::Missing;
        }
        port_log_printf(LOG_WARNING, "acgc::config", "Could not open configuration '%s'", path_string(path).c_str());
        return LoadResult::Invalid;
    }

    try {
        s_root = nlohmann::json::parse(stream);
        if (!s_root.is_object()) {
            throw std::runtime_error("root must be an object");
        }
        for (auto& [name, var] : s_registered) {
            const auto value = s_root.find(name);
            if (value == s_root.end()) {
                continue;
            }
            try {
                var->implementation()->load(*var, *value);
            } catch (const std::exception& error) {
                port_log_printf(LOG_WARNING, "acgc::config", "Ignoring invalid setting '%s': %s", name.c_str(),
                                error.what());
            }
        }
    } catch (const std::exception& error) {
        port_log_printf(LOG_WARNING, "acgc::config", "Could not parse configuration '%s': %s",
                        path_string(path).c_str(), error.what());
        s_root = nlohmann::json::object();
        return LoadResult::Invalid;
    }

    port_log_printf(LOG_INFO, "acgc::config", "Loaded %s", path_string(path).c_str());
    return LoadResult::Loaded;
}

bool save() {
    const auto path = config_path();
    std::error_code error;
    std::filesystem::create_directories(path.parent_path(), error);
    if (error) {
        port_log_printf(LOG_WARNING, "acgc::config", "Could not create configuration directory '%s': %s",
                        path_string(path.parent_path()).c_str(), error.message().c_str());
        return false;
    }

    if (!s_root.is_object()) {
        s_root = nlohmann::json::object();
    }
    for (const auto& [name, var] : s_registered) {
        s_root[name] = var->implementation()->dump(*var);
    }

    auto temporary = path;
    temporary += ".tmp";
    {
        std::ofstream stream(temporary, std::ios::trunc);
        if (!stream) {
            port_log_printf(LOG_WARNING, "acgc::config", "Could not write configuration '%s'",
                            path_string(temporary).c_str());
            return false;
        }
        stream << s_root.dump(2) << '\n';
        if (!stream) {
            port_log_printf(LOG_WARNING, "acgc::config", "Failed while writing configuration '%s'",
                            path_string(temporary).c_str());
            return false;
        }
    }

    std::filesystem::rename(temporary, path, error);
    if (error) {
        error.clear();
        std::filesystem::remove(path, error);
        error.clear();
        std::filesystem::rename(temporary, path, error);
    }
    if (error) {
        port_log_printf(LOG_WARNING, "acgc::config", "Could not replace configuration '%s': %s",
                        path_string(path).c_str(), error.message().c_str());
        std::filesystem::remove(temporary, error);
        return false;
    }
    return true;
}

void shutdown() {
    for (auto& [name, var] : s_registered) {
        (void)name;
        var->unmark_registered();
    }
    s_registered.clear();
    s_root = nlohmann::json::object();
    s_userDirectory.clear();
}

} // namespace acgc::config
