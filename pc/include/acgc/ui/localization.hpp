#pragma once

#include <RmlUi/Core/Types.h>
#include <fmt/format.h>

#include <string_view>

namespace acgc::ui::localization {

// Loads res/lang/en.json. Automatic OS-locale selection is currently disabled.
void load() noexcept;
void shutdown() noexcept;

[[nodiscard]] Rml::String get(std::string_view key) noexcept;

template <typename... Args>
[[nodiscard]] Rml::String format(std::string_view key, Args&&... args) noexcept
{
    try {
        return fmt::vformat(get(key), fmt::make_format_args(args...));
    } catch (const fmt::format_error&) {
        return get(key);
    }
}

} // namespace acgc::ui::localization
