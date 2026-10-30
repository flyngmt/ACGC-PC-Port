#include "acgc/ui/touch_controls.hpp"

#include "acgc/game_editor.hpp"
#include "acgc/settings.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"

#include "extern/aurora/lib/device.hpp"

#include <aurora/rmlui.hpp>
#include <borealis/ui/ui.hpp>
#include <dolphin/pad.h>

#include <RmlUi/Core/Context.h>

#include <algorithm>
#include <cmath>

extern "C" u32 pc_frame_counter;

namespace acgc::ui {
using namespace borealis::ui;

namespace {

constexpr u32 kPort = PAD_CHAN0;
constexpr float kStickRadiusDp = 62.0f;
constexpr float kKnobRadiusDp = 24.0f;
constexpr float kCStickRadiusDp = 40.0f;
constexpr float kCKnobTravelDp = 14.0f;
constexpr float kStickZoneTopDp = 92.0f;
constexpr float kStickZoneBottomDp = 30.0f;
constexpr float kStickZoneWidth = 0.46f;
constexpr u8 kTriggerAnalog = 180;
constexpr u32 kMinPressFrames = 2;
constexpr uint16_t kHapticStrength = 0x8000;
constexpr uint16_t kHapticDurationMs = 20;
constexpr float kPressedScale = 0.94f;

struct ButtonInfo {
    const char* id;
    u16 padButton;
};

constexpr std::array<ButtonInfo, TouchControls::kButtonCount> kButtons = { {
    { "button-a", PAD_BUTTON_A },
    { "button-b", PAD_BUTTON_B },
    { "button-x", PAD_BUTTON_X },
    { "button-y", PAD_BUTTON_Y },
    { "button-z", PAD_TRIGGER_Z },
    { "trigger-l", PAD_TRIGGER_L },
    { "trigger-r", PAD_TRIGGER_R },
    { "button-start", PAD_BUTTON_START },
    { "dpad-up", PAD_BUTTON_UP },
    { "dpad-down", PAD_BUTTON_DOWN },
    { "dpad-left", PAD_BUTTON_LEFT },
    { "dpad-right", PAD_BUTTON_RIGHT },
} };

Rml::String document_source() {
    return R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/theme.rcss" />
    <link type="text/rcss" href="res/rml/touch_controls.rcss" />
</head>
<body>
    <touch-stick id="stick">
        <stick-ring />
        <stick-knob id="knob" />
    </touch-stick>
    <touch-area id="area">)RML" +
           touch_controls_markup() + R"RML(</touch-area>
</body>
</rml>
)RML";
}

void haptic_tap() {
    if (settings().input.touchHaptics.get()) {
        aurora::device::rumble(kHapticStrength, kHapticStrength, kHapticDurationMs);
    }
}

SDL_FingerID finger_id(const Rml::Event& event) {
    return event.GetParameter<SDL_FingerID>("finger_id", 0);
}

Rml::Vector2f finger_position(const Rml::Event& event) {
    return { event.GetParameter("x", 0.0f), event.GetParameter("y", 0.0f) };
}

float dp_scale(Rml::ElementDocument* document) {
    const auto* context = document != nullptr ? document->GetContext() : nullptr;
    return context != nullptr ? std::max(context->GetDensityIndependentPixelRatio(), 1.0f) : 1.0f;
}

s8 stick_value(float value) {
    return static_cast<s8>(std::clamp(std::lround(value * 127.0f), -127L, 127L));
}

Rml::Vector2f clamped_delta(Rml::Vector2f start, Rml::Vector2f current, float radius) {
    Rml::Vector2f delta = current - start;
    const float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (length > radius) {
        delta *= radius / length;
    }
    return delta;
}

} // namespace

Rml::String touch_controls_markup() {
    return R"RML(
        <button id="trigger-l" class="control trigger l"><span>L</span></button>
        <button id="trigger-r" class="control trigger r"><span>R</span></button>
        <button id="button-z" class="control trigger z"><span>Z</span></button>
        <button id="button-start" class="control trigger start"><span>)RML" +
           escape(localization::get("controller.input.start")) + R"RML(</span></button>
        <button id="button-menu" class="control menu"><glyph>&#xe5d2;</glyph></button>
        <button id="button-y" class="control face y"><span>Y</span></button>
        <button id="button-x" class="control face x"><span>X</span></button>
        <button id="button-b" class="control face b"><span>B</span></button>
        <button id="button-a" class="control face a"><span>A</span></button>
        <c-stick id="c-stick" class="control">
            <c-knob id="c-knob"><span>C</span></c-knob>
        </c-stick>
        <d-pad id="dpad" class="control">
            <button id="dpad-up" class="dpad up"><glyph>&#xe5c7;</glyph></button>
            <button id="dpad-left" class="dpad left"><glyph>&#xe5de;</glyph></button>
            <button id="dpad-right" class="dpad right"><glyph>&#xe5df;</glyph></button>
            <button id="dpad-down" class="dpad down"><glyph>&#xe5c5;</glyph></button>
        </d-pad>
)RML";
}

TouchSize touch_area_size(Rml::ElementDocument* document, const Insets& insets) {
    auto* context = document != nullptr ? document->GetContext() : nullptr;
    if (context == nullptr) {
        return {};
    }
    const float scale = dp_scale(document);
    const auto dimensions = context->GetDimensions();
    return {
        .w = std::max(0.0f, static_cast<float>(dimensions.x) - insets.left - insets.right) / scale,
        .h = std::max(0.0f, static_cast<float>(dimensions.y) - insets.top - insets.bottom) / scale,
    };
}

void TouchLayoutView::bind(Rml::ElementDocument* document) {
    const auto controls = touch_layout_controls();
    for (size_t i = 0; i < mEntries.size() && i < controls.size(); ++i) {
        mEntries[i] = Entry{};
        mEntries[i].element = document != nullptr ? document->GetElementById(controls[i].elementId) : nullptr;
    }
}

void TouchLayoutView::apply(const TouchLayout& layout, TouchSize area) {
    if (area.w <= 0.0f || area.h <= 0.0f) {
        return;
    }
    const auto controls = touch_layout_controls();
    for (size_t i = 0; i < mEntries.size() && i < controls.size(); ++i) {
        auto& entry = mEntries[i];
        const auto& info = controls[i];
        const auto placement = placement_for(layout, info);
        entry.visual = resolve_visual(info, placement, area);
        if (entry.element == nullptr) {
            continue;
        }
        const TouchRect box{
            .l = entry.visual.l + (entry.visual.w - info.w) * 0.5f,
            .t = entry.visual.t + (entry.visual.h - info.h) * 0.5f,
            .w = info.w,
            .h = info.h,
        };
        if (box.l != entry.box.l || box.t != entry.box.t || box.w != entry.box.w || box.h != entry.box.h) {
            entry.element->SetProperty(Rml::PropertyId::Left, Rml::Property(box.l, Rml::Unit::DP));
            entry.element->SetProperty(Rml::PropertyId::Top, Rml::Property(box.t, Rml::Unit::DP));
            entry.element->SetProperty(Rml::PropertyId::Width, Rml::Property(box.w, Rml::Unit::DP));
            entry.element->SetProperty(Rml::PropertyId::Height, Rml::Property(box.h, Rml::Unit::DP));
            entry.box = box;
        }
        const float scale = placement.scale * (entry.element->IsClassSet("pressed") ? kPressedScale : 1.0f);
        if (scale != entry.scale) {
            entry.element->SetProperty(Rml::PropertyId::Transform,
                                       Rml::Transform::MakeProperty({ Rml::Transforms::Scale2D{ scale } }));
            entry.scale = scale;
        }
    }
}

void TouchLayoutView::reset() {
    for (auto& entry : mEntries) {
        entry.box = { -1.0f, -1.0f, -1.0f, -1.0f };
        entry.scale = -1.0f;
    }
}

TouchControls::TouchControls()
    : Document(document_source(), true, kScopeTouchControls),
      mArea(mDocument != nullptr ? mDocument->GetElementById("area") : nullptr),
      mStickElement(mDocument != nullptr ? mDocument->GetElementById("stick") : nullptr),
      mKnob(mDocument != nullptr ? mDocument->GetElementById("knob") : nullptr),
      mCStickElement(mDocument != nullptr ? mDocument->GetElementById("c-stick") : nullptr),
      mCKnob(mDocument != nullptr ? mDocument->GetElementById("c-knob") : nullptr),
      mDpad(mDocument != nullptr ? mDocument->GetElementById("dpad") : nullptr),
      mMenuButton(mDocument != nullptr ? mDocument->GetElementById("button-menu") : nullptr) {
    mLayer = aurora::input::register_layer({
        .label = "acgc.touch-controls",
        .priority = aurora::input::kRmlUiLayerPriority + 2,
        .onEvent = on_input,
        .userdata = this,
    });
    if (mDocument == nullptr) {
        return;
    }
    mLayout.bind(mDocument);
    for (size_t i = 0; i < kButtons.size(); ++i) {
        auto* element = mDocument->GetElementById(kButtons[i].id);
        mButtons[i] = element;
        if (element == nullptr) {
            continue;
        }
        listen(element, aurora::rmlui::TouchStartEvent, [this, i](Rml::Event& event) {
            if (mShown) {
                press_button(i, finger_id(event));
            }
            event.StopPropagation();
        });
        listen(element, aurora::rmlui::TouchEndEvent, [this](Rml::Event& event) {
            release_button(finger_id(event));
            event.StopPropagation();
        });
        listen(element, aurora::rmlui::TouchCancelEvent, [this](Rml::Event& event) {
            release_button(finger_id(event));
            event.StopPropagation();
        });
    }

    listen(mCStickElement, aurora::rmlui::TouchStartEvent, [this](Rml::Event& event) {
        if (mShown && (!mCStick.active || mCStick.releasePending)) {
            const auto position = finger_position(event);
            acgc::input::game_editor().set_typing(false);
            mCStick = { .id = finger_id(event),
                        .start = position,
                        .current = position,
                        .pressFrame = pc_frame_counter,
                        .active = true };
            haptic_tap();
        }
        event.StopPropagation();
    });
    listen(mDpad, aurora::rmlui::TouchStartEvent, [](Rml::Event& event) { event.StopPropagation(); });
    listen(mMenuButton, aurora::rmlui::TouchStartEvent, [this](Rml::Event& event) {
        if (mShown && !mMenuPressed) {
            mMenuFinger = finger_id(event);
            mMenuPressed = true;
            mMenuButton->SetClass("pressed", true);
            haptic_tap();
        }
        event.StopPropagation();
    });
    listen(mMenuButton, aurora::rmlui::TouchEndEvent, [this](Rml::Event& event) {
        if (mMenuPressed && mMenuFinger == finger_id(event)) {
            mMenuPressed = false;
            mMenuButton->SetClass("pressed", false);
            const auto position = finger_position(event);
            const auto offset = mMenuButton->GetAbsoluteOffset(Rml::BoxArea::Border);
            const auto size = mMenuButton->GetBox().GetSize(Rml::BoxArea::Border);
            if (position.x >= offset.x && position.y >= offset.y && position.x <= offset.x + size.x &&
                position.y <= offset.y + size.y) {
                if (auto* document = top_document()) {
                    document->element()->DispatchEvent(
                        kNavCommandEvent, { { "command", Rml::Variant{ static_cast<int>(NavCommand::Menu) } } });
                }
            }
        }
        event.StopPropagation();
    });
    listen(mMenuButton, aurora::rmlui::TouchCancelEvent, [this](Rml::Event& event) {
        if (mMenuPressed && mMenuFinger == finger_id(event)) {
            mMenuPressed = false;
            mMenuButton->SetClass("pressed", false);
        }
        event.StopPropagation();
    });

    listen(mDocument, aurora::rmlui::TouchStartEvent, [this](Rml::Event& event) { handle_touch_down(event); });
    listen(mDocument, aurora::rmlui::TouchMoveEvent, [this](Rml::Event& event) { handle_touch_move(event); });
    listen(mDocument, aurora::rmlui::TouchEndEvent, [this](Rml::Event& event) { handle_touch_up(event); });
    listen(mDocument, aurora::rmlui::TouchCancelEvent, [this](Rml::Event& event) { handle_touch_up(event); });
    listen(mDocument, Rml::EventId::Transitionend, [this](Rml::Event& event) {
        if (event.GetTargetElement() == mDocument && !mShown && Document::visible()) {
            Document::hide(mPendingClose);
        }
    });
}

TouchControls::~TouchControls() {
    clear_input();
    aurora::input::unregister_layer(mLayer);
}

void TouchControls::show() {
    mShown = true;
    if (mDocument != nullptr) {
        mDocument->Show(Rml::ModalFlag::None, Rml::FocusFlag::None, Rml::ScrollFlag::None);
        mDocument->SetAttribute("open", "");
    }
    mPendingClose = false;
}

void TouchControls::hide(bool close) {
    mShown = false;
    clear_input();
    if (mDocument != nullptr) {
        mDocument->RemoveAttribute("open");
        mPendingClose = close;
    } else {
        Document::hide(close);
    }
}

void TouchControls::update() {
    sync_visibility();
    sync_safe_area();
    mLayout.apply(settings().input.touchLayout.get(), touch_area_size(mDocument, mInsets));
    sync_buttons();
    sync_stick();
    sync_pad();
    Document::update();
}

bool TouchControls::claims_pointer(Rml::Element* element) const {
    if (!mShown || element == nullptr) {
        return false;
    }
    const auto contains = [element](Rml::Element* owner) {
        return owner != nullptr && (owner == element || owner->Contains(element));
    };
    return contains(mCStickElement) || contains(mDpad) || contains(mMenuButton) ||
           std::ranges::any_of(mButtons, contains);
}

void TouchControls::press_button(size_t index, SDL_FingerID id) {
    auto& touch = mTouches[index];
    if (touch.active && !touch.releasePending) {
        return;
    }
    acgc::input::game_editor().set_typing(false);
    touch = { .id = id, .pressFrame = pc_frame_counter, .active = true };
    if (mButtons[index] != nullptr) {
        mButtons[index]->SetClass("pressed", true);
    }
    haptic_tap();
}

bool TouchControls::release_button(SDL_FingerID id) {
    for (size_t i = 0; i < mTouches.size(); ++i) {
        auto& touch = mTouches[i];
        if (touch.active && !touch.releasePending && touch.id == id) {
            touch.releasePending = true;
            if (mButtons[i] != nullptr) {
                mButtons[i]->SetClass("pressed", false);
            }
            return true;
        }
    }
    return false;
}

void TouchControls::handle_touch_down(Rml::Event& event) {
    if (!mShown || mStick.active) {
        return;
    }
    const auto* context = mDocument->GetContext();
    if (context == nullptr) {
        return;
    }
    const auto position = finger_position(event);
    const auto dimensions = context->GetDimensions();
    const float scale = dp_scale(mDocument);
    const float top = mInsets.top + kStickZoneTopDp * scale;
    const float bottom = static_cast<float>(dimensions.y) - mInsets.bottom - kStickZoneBottomDp * scale;
    const float right = mInsets.left + (static_cast<float>(dimensions.x) - mInsets.left - mInsets.right) * kStickZoneWidth;
    if (position.y < top || position.y > bottom || position.x > right) {
        return;
    }
    mStick = { .id = finger_id(event), .start = position, .current = position, .active = true };
}

void TouchControls::handle_touch_move(Rml::Event& event) {
    const auto id = finger_id(event);
    if (mStick.active && mStick.id == id) {
        mStick.current = finger_position(event);
    }
    if (mCStick.active && !mCStick.releasePending && mCStick.id == id) {
        mCStick.current = finger_position(event);
    }
}

void TouchControls::handle_touch_up(Rml::Event& event) {
    const auto id = finger_id(event);
    if (mStick.active && mStick.id == id) {
        mStick = {};
    }
    if (mCStick.active && !mCStick.releasePending && mCStick.id == id) {
        mCStick.releasePending = true;
    }
}

void TouchControls::clear_input() {
    mStick = {};
    mCStick = {};
    mMenuPressed = false;
    if (mMenuButton != nullptr) {
        mMenuButton->SetClass("pressed", false);
    }
    for (size_t i = 0; i < mTouches.size(); ++i) {
        mTouches[i] = {};
        if (mButtons[i] != nullptr) {
            mButtons[i]->SetClass("pressed", false);
        }
    }
    if (mStickElement != nullptr) {
        mStickElement->SetClass("active", false);
    }
    sync_c_stick();
    if (mPadActive) {
        PADClearVirtualStatus(kPort);
        mPadActive = false;
    }
}

void TouchControls::sync_visibility() {
    const bool wanted = settings().input.touchControls.get() && !mDeviceInput && !any_document_visible();
    if (wanted && !mShown) {
        show();
    } else if (!wanted && mShown) {
        hide(false);
    }
}

void TouchControls::sync_safe_area() {
    if (mDocument == nullptr || mArea == nullptr) {
        return;
    }
    const auto insets = safe_area_insets(mDocument->GetContext());
    if (insets == mInsets) {
        return;
    }
    mInsets = insets;
    mArea->SetProperty(Rml::PropertyId::Top, Rml::Property(insets.top, Rml::Unit::PX));
    mArea->SetProperty(Rml::PropertyId::Right, Rml::Property(insets.right, Rml::Unit::PX));
    mArea->SetProperty(Rml::PropertyId::Bottom, Rml::Property(insets.bottom, Rml::Unit::PX));
    mArea->SetProperty(Rml::PropertyId::Left, Rml::Property(insets.left, Rml::Unit::PX));
}

void TouchControls::sync_buttons() {
    const u32 frame = pc_frame_counter;
    for (auto& touch : mTouches) {
        if (touch.active && touch.releasePending && frame - touch.pressFrame >= kMinPressFrames) {
            touch = {};
        }
    }
    if (mCStick.active && mCStick.releasePending && frame - mCStick.pressFrame >= kMinPressFrames) {
        mCStick = {};
    }
    sync_c_stick();
}

void TouchControls::sync_c_stick() {
    if (mCStickElement == nullptr || mCKnob == nullptr) {
        return;
    }
    const bool held = mCStick.active && !mCStick.releasePending;
    mCStickElement->SetClass("pressed", held);
    if (!held) {
        mCKnob->SetProperty(Rml::PropertyId::Left, Rml::Property(0.0f, Rml::Unit::PX));
        mCKnob->SetProperty(Rml::PropertyId::Top, Rml::Property(0.0f, Rml::Unit::PX));
        return;
    }
    const float scale = dp_scale(mDocument);
    const auto delta = clamped_delta(mCStick.start, mCStick.current, kCStickRadiusDp * scale);
    const float travel = kCKnobTravelDp / kCStickRadiusDp;
    mCKnob->SetProperty(Rml::PropertyId::Left, Rml::Property(delta.x * travel, Rml::Unit::PX));
    mCKnob->SetProperty(Rml::PropertyId::Top, Rml::Property(delta.y * travel, Rml::Unit::PX));
}

void TouchControls::sync_stick() {
    if (mStickElement == nullptr || mKnob == nullptr) {
        return;
    }
    mStickElement->SetClass("active", mStick.active);
    if (!mStick.active) {
        return;
    }
    const float scale = dp_scale(mDocument);
    const float radius = kStickRadiusDp * scale;
    const float knob = kKnobRadiusDp * scale;
    const auto delta = clamped_delta(mStick.start, mStick.current, radius);
    mStickElement->SetProperty(Rml::PropertyId::Left, Rml::Property(mStick.start.x - radius, Rml::Unit::PX));
    mStickElement->SetProperty(Rml::PropertyId::Top, Rml::Property(mStick.start.y - radius, Rml::Unit::PX));
    mKnob->SetProperty(Rml::PropertyId::Left, Rml::Property(radius + delta.x - knob, Rml::Unit::PX));
    mKnob->SetProperty(Rml::PropertyId::Top, Rml::Property(radius + delta.y - knob, Rml::Unit::PX));
}

void TouchControls::sync_pad() {
    if (!mShown) {
        return;
    }
    PADStatus status{};
    status.err = PAD_ERR_NONE;
    for (size_t i = 0; i < mTouches.size(); ++i) {
        if (mTouches[i].active) {
            status.button |= kButtons[i].padButton;
        }
    }
    if ((status.button & PAD_TRIGGER_L) != 0) {
        status.triggerLeft = kTriggerAnalog;
    }
    if ((status.button & PAD_TRIGGER_R) != 0) {
        status.triggerRight = kTriggerAnalog;
    }
    if (mStick.active) {
        const float radius = kStickRadiusDp * dp_scale(mDocument);
        const auto delta = clamped_delta(mStick.start, mStick.current, radius);
        status.stickX = stick_value(delta.x / radius);
        status.stickY = stick_value(-delta.y / radius);
    }
    if (mCStick.active) {
        const float radius = kCStickRadiusDp * dp_scale(mDocument);
        const auto delta = clamped_delta(mCStick.start, mCStick.current, radius);
        status.substickX = stick_value(delta.x / radius);
        status.substickY = stick_value(-delta.y / radius);
    }

    const bool active = status.button != 0 || status.stickX != 0 || status.stickY != 0 || status.substickX != 0 ||
                        status.substickY != 0;
    if (active) {
        PADSetVirtualStatus(kPort, &status);
        mPadActive = true;
    } else if (mPadActive) {
        PADClearVirtualStatus(kPort);
        mPadActive = false;
    }
}

aurora::input::EventResult TouchControls::on_input(const aurora::input::InputEvent& event, void* userdata) {
    static_cast<TouchControls*>(userdata)->observe_input(event);
    return aurora::input::EventResult::Pass;
}

void TouchControls::observe_input(const aurora::input::InputEvent& event) {
    using Event = aurora::input::InputEvent;
    using Kind = aurora::input::InputSource::Kind;
    switch (event.source.kind) {
    case Kind::Touch:
        if (const auto* pointer = event.payload.get_if<Event::PointerChanged>();
            pointer != nullptr && pointer->phase == Event::PointerChanged::Phase::Down) {
            mDeviceInput = false;
        }
        break;
    case Kind::Controller:
        if (const auto* button = event.payload.get_if<Event::ButtonChanged>(); button != nullptr && button->pressed) {
            mDeviceInput = true;
        } else if (const auto* axis = event.payload.get_if<Event::AxisChanged>();
                   axis != nullptr && std::abs(axis->value) >= 0.5f) {
            mDeviceInput = true;
        }
        break;
    case Kind::Keyboard:
        if (const auto* key = event.payload.get_if<Event::KeyChanged>(); key != nullptr && key->pressed && !key->repeat) {
            mDeviceInput = true;
        }
        break;
    default:
        break;
    }
}

} // namespace acgc::ui
