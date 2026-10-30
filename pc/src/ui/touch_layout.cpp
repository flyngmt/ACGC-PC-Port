#include "acgc/ui/touch_layout.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <array>
#include <cmath>

namespace acgc::ui {
namespace {

constexpr int kLayoutVersion = 1;

constexpr std::array kControls = {
    TouchControlInfo{ "triggerL", "trigger-l", 78.0f, 46.0f, { 24.0f, 18.0f, 1.0f, TouchAnchor::TopLeft } },
    TouchControlInfo{ "triggerR", "trigger-r", 78.0f, 46.0f, { 24.0f, 18.0f, 1.0f, TouchAnchor::TopRight } },
    TouchControlInfo{ "buttonZ", "button-z", 78.0f, 46.0f, { 24.0f, 72.0f, 1.0f, TouchAnchor::TopRight } },
    TouchControlInfo{ "buttonStart", "button-start", 78.0f, 46.0f, { 0.0f, 18.0f, 1.0f, TouchAnchor::Top } },
    TouchControlInfo{ "buttonMenu", "button-menu", 46.0f, 46.0f, { 70.0f, 18.0f, 1.0f, TouchAnchor::Top } },
    TouchControlInfo{ "dpad", "dpad", 102.0f, 102.0f, { 14.0f, 74.0f, 1.0f, TouchAnchor::TopLeft } },
    TouchControlInfo{ "cStick", "c-stick", 58.0f, 58.0f, { 8.0f, 6.0f, 1.0f, TouchAnchor::BottomRight } },
    TouchControlInfo{ "buttonA", "button-a", 74.0f, 74.0f, { 62.0f, 64.0f, 1.0f, TouchAnchor::BottomRight } },
    TouchControlInfo{ "buttonB", "button-b", 58.0f, 58.0f, { 158.0f, 48.0f, 1.0f, TouchAnchor::BottomRight } },
    TouchControlInfo{ "buttonX", "button-x", 58.0f, 58.0f, { 28.0f, 144.0f, 1.0f, TouchAnchor::BottomRight } },
    TouchControlInfo{ "buttonY", "button-y", 58.0f, 58.0f, { 124.0f, 138.0f, 1.0f, TouchAnchor::BottomRight } },
};

constexpr std::array<std::pair<TouchAnchor, std::string_view>, 6> kAnchorNames = { {
    { TouchAnchor::TopLeft, "topLeft" },
    { TouchAnchor::Top, "top" },
    { TouchAnchor::TopRight, "topRight" },
    { TouchAnchor::BottomLeft, "bottomLeft" },
    { TouchAnchor::Bottom, "bottom" },
    { TouchAnchor::BottomRight, "bottomRight" },
} };

bool anchor_left(TouchAnchor anchor) {
    return anchor == TouchAnchor::TopLeft || anchor == TouchAnchor::BottomLeft;
}

bool anchor_right(TouchAnchor anchor) {
    return anchor == TouchAnchor::TopRight || anchor == TouchAnchor::BottomRight;
}

bool anchor_bottom(TouchAnchor anchor) {
    return anchor == TouchAnchor::BottomLeft || anchor == TouchAnchor::Bottom || anchor == TouchAnchor::BottomRight;
}

float round_to(float value, float step) {
    return std::round(value / step) * step;
}

} // namespace

void to_json(nlohmann::json& json, const TouchLayout& layout) {
    auto controls = nlohmann::json::object();
    for (const auto& [id, placement] : layout.controls) {
        const auto name = std::ranges::find(kAnchorNames, placement.anchor, &std::pair<TouchAnchor, std::string_view>::first);
        controls[id] = {
            { "x", placement.x },
            { "y", placement.y },
            { "scale", placement.scale },
            { "anchor", name != kAnchorNames.end() ? std::string(name->second) : std::string("topLeft") },
        };
    }
    json = { { "version", kLayoutVersion }, { "controls", std::move(controls) } };
}

void from_json(const nlohmann::json& json, TouchLayout& layout) {
    layout = {};
    const auto controls = json.find("controls");
    if (controls == json.end() || !controls->is_object()) {
        return;
    }
    for (const auto& [id, entry] : controls->items()) {
        if (!entry.is_object()) {
            continue;
        }
        const auto anchorName = entry.value("anchor", std::string{});
        const auto anchor =
            std::ranges::find(kAnchorNames, anchorName, &std::pair<TouchAnchor, std::string_view>::second);
        if (anchor == kAnchorNames.end()) {
            continue;
        }
        layout.controls[id] = {
            .x = entry.value("x", 0.0f),
            .y = entry.value("y", 0.0f),
            .scale = std::clamp(entry.value("scale", 1.0f), kTouchMinScale, kTouchMaxScale),
            .anchor = anchor->first,
        };
    }
}

std::span<const TouchControlInfo> touch_layout_controls() {
    return kControls;
}

TouchPlacement placement_for(const TouchLayout& layout, const TouchControlInfo& info) {
    const auto found = layout.controls.find(info.id);
    return found != layout.controls.end() ? found->second : info.defaults;
}

TouchRect resolve_visual(const TouchControlInfo& info, TouchPlacement placement, TouchSize area) {
    TouchRect rect{ .w = info.w * placement.scale, .h = info.h * placement.scale };
    if (anchor_left(placement.anchor)) {
        rect.l = placement.x;
    } else if (anchor_right(placement.anchor)) {
        rect.l = area.w - placement.x - rect.w;
    } else {
        rect.l = area.w * 0.5f + placement.x - rect.w * 0.5f;
    }
    rect.t = anchor_bottom(placement.anchor) ? area.h - placement.y - rect.h : placement.y;
    return rect;
}

TouchPlacement encode_placement(TouchRect visual, float scale, TouchSize area) {
    const float centerX = visual.l + visual.w * 0.5f;
    const bool bottom = visual.t + visual.h * 0.5f >= area.h * 0.5f;
    TouchPlacement placement{ .scale = round_to(scale, 0.01f) };
    if (centerX < area.w / 3.0f) {
        placement.anchor = bottom ? TouchAnchor::BottomLeft : TouchAnchor::TopLeft;
        placement.x = visual.l;
    } else if (centerX > area.w * 2.0f / 3.0f) {
        placement.anchor = bottom ? TouchAnchor::BottomRight : TouchAnchor::TopRight;
        placement.x = area.w - visual.l - visual.w;
    } else {
        placement.anchor = bottom ? TouchAnchor::Bottom : TouchAnchor::Top;
        placement.x = centerX - area.w * 0.5f;
    }
    placement.y = bottom ? area.h - visual.t - visual.h : visual.t;
    placement.x = round_to(placement.x, 0.1f);
    placement.y = round_to(placement.y, 0.1f);
    return placement;
}

} // namespace acgc::ui
