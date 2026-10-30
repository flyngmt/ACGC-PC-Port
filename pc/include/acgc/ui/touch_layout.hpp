#pragma once

#include <nlohmann/json_fwd.hpp>

#include <cstdint>
#include <functional>
#include <map>
#include <span>
#include <string>
#include <string_view>

namespace acgc::ui {

enum class TouchAnchor : std::uint8_t {
    TopLeft,
    Top,
    TopRight,
    BottomLeft,
    Bottom,
    BottomRight,
};

struct TouchPlacement {
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    TouchAnchor anchor = TouchAnchor::TopLeft;

    bool operator==(const TouchPlacement&) const = default;
};

struct TouchLayout {
    std::map<std::string, TouchPlacement, std::less<>> controls;

    bool operator==(const TouchLayout&) const = default;
};

void to_json(nlohmann::json& json, const TouchLayout& layout);
void from_json(const nlohmann::json& json, TouchLayout& layout);

struct TouchRect {
    float l = 0.0f;
    float t = 0.0f;
    float w = 0.0f;
    float h = 0.0f;
};

struct TouchSize {
    float w = 0.0f;
    float h = 0.0f;
};

struct TouchControlInfo {
    std::string_view id;
    const char* elementId = nullptr;
    float w = 0.0f;
    float h = 0.0f;
    TouchPlacement defaults;
};

inline constexpr float kTouchMinScale = 0.5f;
inline constexpr float kTouchMaxScale = 2.5f;

std::span<const TouchControlInfo> touch_layout_controls();
TouchPlacement placement_for(const TouchLayout& layout, const TouchControlInfo& info);
TouchRect resolve_visual(const TouchControlInfo& info, TouchPlacement placement, TouchSize area);
TouchPlacement encode_placement(TouchRect visual, float scale, TouchSize area);

} // namespace acgc::ui
