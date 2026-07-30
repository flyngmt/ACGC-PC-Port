#pragma once

#include <concepts>
#include <cstdlib>
#include <string>
#include <type_traits>
#include <utility>

namespace acgc::config {

enum class ConfigVarLayer {
    Default,
    Value,
};

class ConfigImplBase;

class ConfigVarBase {
public:
    ConfigVarBase(const ConfigVarBase&) = delete;
    ConfigVarBase& operator=(const ConfigVarBase&) = delete;
    virtual ~ConfigVarBase();

    [[nodiscard]] const char* name() const noexcept;
    [[nodiscard]] const ConfigImplBase* implementation() const noexcept;
    [[nodiscard]] ConfigVarLayer layer() const noexcept;

protected:
    ConfigVarBase(std::string name, const ConfigImplBase* implementation);
    void check_registered() const noexcept;

    ConfigVarLayer m_layer = ConfigVarLayer::Default;

private:
    friend void register_var(ConfigVarBase& var);
    friend void shutdown();

    void mark_registered() noexcept;
    void unmark_registered() noexcept;

    std::string m_name;
    const ConfigImplBase* m_implementation;
    bool m_registered = false;
};

template <typename T>
concept ConfigValue = !std::is_const_v<T> && !std::is_volatile_v<T> &&
    std::equality_comparable<T> &&
    (std::is_arithmetic_v<T> || std::is_enum_v<T> || std::is_same_v<T, std::string>);

template <ConfigValue T>
class ConfigImpl;

template <ConfigValue T>
const ConfigImplBase* implementation_for();

template <ConfigValue T>
class ConfigVar final : public ConfigVarBase {
public:
    template <typename... Args>
    ConfigVar(std::string name, Args&&... args)
        : ConfigVarBase(std::move(name), implementation_for<T>())
        , m_default(std::forward<Args>(args)...)
    {
    }

    [[nodiscard]] const T& value() const noexcept
    {
        check_registered();
        return m_layer == ConfigVarLayer::Value ? m_value : m_default;
    }

    [[nodiscard]] const T& default_value() const noexcept
    {
        check_registered();
        return m_default;
    }

    void set_value(T value)
    {
        check_registered();
        m_value = std::move(value);
        m_layer = ConfigVarLayer::Value;
    }

    void reset()
    {
        check_registered();
        m_layer = ConfigVarLayer::Default;
    }

    operator const T&() const noexcept { return value(); }

private:
    friend class ConfigImpl<T>;

    void load_value(T value)
    {
        check_registered();
        m_value = std::move(value);
        m_layer = ConfigVarLayer::Value;
    }

    T m_default;
    T m_value{};
};

} // namespace acgc::config
