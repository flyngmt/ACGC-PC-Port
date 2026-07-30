#pragma once

#include "acgc/config_var.hpp"

#include <filesystem>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <type_traits>

namespace acgc::config {

enum class LoadResult {
    Missing,
    Loaded,
    Invalid,
};

class ConfigImplBase {
public:
    virtual ~ConfigImplBase() = default;
    virtual void load(ConfigVarBase& var, const nlohmann::json& value) const = 0;
    [[nodiscard]] virtual nlohmann::json dump(const ConfigVarBase& var) const = 0;
};

template <ConfigValue T>
class ConfigImpl final : public ConfigImplBase {
public:
    void load(ConfigVarBase& base, const nlohmann::json& value) const override
    {
        auto& var = static_cast<ConfigVar<T>&>(base);
        if constexpr (std::is_enum_v<T>) {
            using Underlying = std::underlying_type_t<T>;
            var.load_value(static_cast<T>(value.get<Underlying>()));
        } else {
            var.load_value(value.get<T>());
        }
    }

    [[nodiscard]] nlohmann::json dump(const ConfigVarBase& base) const override
    {
        const auto& var = static_cast<const ConfigVar<T>&>(base);
        if constexpr (std::is_enum_v<T>) {
            return static_cast<std::underlying_type_t<T>>(var.value());
        } else {
            return var.value();
        }
    }
};

template <ConfigValue T>
const ConfigImplBase* implementation_for()
{
    static const ConfigImpl<T> implementation;
    return &implementation;
}

void set_user_directory(std::filesystem::path directory);
[[nodiscard]] const std::filesystem::path& user_directory() noexcept;
[[nodiscard]] std::filesystem::path config_path();

void register_var(ConfigVarBase& var);
LoadResult load();
bool save();
void shutdown();

} // namespace acgc::config
