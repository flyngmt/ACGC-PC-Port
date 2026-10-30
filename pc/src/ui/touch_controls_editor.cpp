#include "acgc/ui/touch_controls_editor.hpp"

#include "acgc/settings.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"

#include <aurora/rmlui.hpp>
#include <borealis/ui/ui.hpp>

#include <RmlUi/Core/Context.h>

#include <algorithm>
#include <cmath>

namespace acgc::ui {
using namespace borealis::ui;

namespace {

constexpr float kDragThresholdDp = 6.0f;

struct HandleBinding {
    const char* id;
    int handle;
};

constexpr std::array<HandleBinding, 4> kHandles = { {
    { "handle-top-left", 1 },
    { "handle-top-right", 2 },
    { "handle-bottom-left", 3 },
    { "handle-bottom-right", 4 },
} };

constexpr std::array<const char*, 3> kCommandIds = { "editor-save", "editor-reset", "editor-cancel" };

Rml::String document_source() {
    return R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/theme.rcss" />
    <link type="text/rcss" href="res/rml/touch_controls.rcss" />
    <link type="text/rcss" href="res/rml/touch_controls_editor.rcss" />
</head>
<body class="touch-editor">
    <touch-area id="area">)RML" +
           touch_controls_markup() + R"RML(
        <selection-frame id="selection">
            <resize-handle id="handle-top-left" class="top left" />
            <resize-handle id="handle-top-right" class="top right" />
            <resize-handle id="handle-bottom-left" class="bottom left" />
            <resize-handle id="handle-bottom-right" class="bottom right" />
        </selection-frame>
    </touch-area>
    <editor-toolbar>
        <button id="editor-save" class="editor-command primary"><span>)RML" +
           escape(localization::get("common.save")) + R"RML(</span></button>
        <button id="editor-reset" class="editor-command"><span>)RML" +
           escape(localization::get("common.reset")) + R"RML(</span></button>
        <button id="editor-cancel" class="editor-command"><span>)RML" +
           escape(localization::get("common.cancel")) + R"RML(</span></button>
    </editor-toolbar>
</body>
</rml>
)RML";
}

SDL_FingerID finger_id(const Rml::Event& event) {
    return event.GetParameter<SDL_FingerID>("finger_id", 0);
}

Rml::Vector2f finger_position(const Rml::Event& event) {
    return { event.GetParameter("x", 0.0f), event.GetParameter("y", 0.0f) };
}

Rml::Vector2f mouse_position(const Rml::Event& event) {
    return { event.GetParameter("mouse_x", 0.0f), event.GetParameter("mouse_y", 0.0f) };
}

bool primary_button(const Rml::Event& event) {
    return event.GetParameter("button", -1) == 0;
}

} // namespace

TouchControlsEditor::TouchControlsEditor()
    : Document(document_source(), false, kScopeTouchControls),
      mArea(mDocument != nullptr ? mDocument->GetElementById("area") : nullptr),
      mSelection(mDocument != nullptr ? mDocument->GetElementById("selection") : nullptr),
      mWorking(settings().input.touchLayout.get()) {
    if (mDocument == nullptr) {
        return;
    }
    mLayout.bind(mDocument);

    const auto controls = touch_layout_controls();
    for (size_t i = 0; i < controls.size(); ++i) {
        auto* element = mLayout.element(i);
        if (element == nullptr) {
            continue;
        }
        listen(element, aurora::rmlui::TouchStartEvent, [this, i](Rml::Event& event) {
            begin_edit(i, Handle::Move, finger_position(event), true, finger_id(event));
            event.StopPropagation();
        });
        listen(element, Rml::EventId::Mousedown, [this, i](Rml::Event& event) {
            if (primary_button(event)) {
                begin_edit(i, Handle::Move, mouse_position(event), false, 0);
                event.StopPropagation();
            }
        });
    }

    for (const auto& binding : kHandles) {
        auto* element = mDocument->GetElementById(binding.id);
        const auto handle = static_cast<Handle>(binding.handle);
        listen(element, aurora::rmlui::TouchStartEvent, [this, handle](Rml::Event& event) {
            if (mSelected < touch_layout_controls().size()) {
                begin_edit(mSelected, handle, finger_position(event), true, finger_id(event));
            }
            event.StopPropagation();
        });
        listen(element, Rml::EventId::Mousedown, [this, handle](Rml::Event& event) {
            if (primary_button(event) && mSelected < touch_layout_controls().size()) {
                begin_edit(mSelected, handle, mouse_position(event), false, 0);
                event.StopPropagation();
            }
        });
    }

    for (size_t i = 0; i < kCommandIds.size(); ++i) {
        mCommands[i] = mDocument->GetElementById(kCommandIds[i]);
        listen(mCommands[i], Rml::EventId::Click, [this, i](Rml::Event& event) {
            if (active()) {
                activate(i);
            }
            event.StopPropagation();
        });
        listen(mCommands[i], aurora::rmlui::TouchEndEvent, [this, i](Rml::Event& event) {
            if (active()) {
                activate(i);
            }
            event.StopPropagation();
        });
        listen(mCommands[i], Rml::EventId::Focus, [this, i](Rml::Event&) { mFocusedCommand = i; });
    }

    listen(mDocument, aurora::rmlui::TouchStartEvent, [this](Rml::Event&) {
        if (!mEdit.active) {
            select(SIZE_MAX);
        }
    });
    listen(mDocument, Rml::EventId::Mousedown, [this](Rml::Event& event) {
        if (primary_button(event) && !mEdit.active) {
            select(SIZE_MAX);
        }
    });
    listen(mDocument, aurora::rmlui::TouchMoveEvent,
           [this](Rml::Event& event) { continue_edit(finger_position(event)); });
    listen(mDocument, Rml::EventId::Mousemove, [this](Rml::Event& event) {
        if (!mEdit.touch) {
            continue_edit(mouse_position(event));
        }
    });
    listen(mDocument, aurora::rmlui::TouchEndEvent,
           [this](Rml::Event& event) { end_edit(true, finger_id(event), false); });
    listen(mDocument, aurora::rmlui::TouchCancelEvent,
           [this](Rml::Event& event) { end_edit(true, finger_id(event), true); });
    listen(mDocument, Rml::EventId::Mouseup, [this](Rml::Event&) { end_edit(false, 0, false); });
    listen(mDocument, Rml::EventId::Transitionend, [this](Rml::Event& event) {
        if (event.GetTargetElement() == mDocument && !mDocument->HasAttribute("open") && Document::visible()) {
            Document::hide(mPendingClose);
        }
    });
}

void TouchControlsEditor::show() {
    Document::show();
    if (mDocument != nullptr) {
        mDocument->SetAttribute("open", "");
    }
}

void TouchControlsEditor::hide(bool close) {
    mEdit = {};
    if (mDocument != nullptr) {
        mDocument->RemoveAttribute("open");
        mPendingClose = close;
    } else {
        Document::hide(close);
    }
}

void TouchControlsEditor::update() {
    if (mDocument != nullptr && mArea != nullptr) {
        const auto insets = safe_area_insets(mDocument->GetContext());
        if (insets != mInsets) {
            mInsets = insets;
            mArea->SetProperty(Rml::PropertyId::Top, Rml::Property(insets.top, Rml::Unit::PX));
            mArea->SetProperty(Rml::PropertyId::Right, Rml::Property(insets.right, Rml::Unit::PX));
            mArea->SetProperty(Rml::PropertyId::Bottom, Rml::Property(insets.bottom, Rml::Unit::PX));
            mArea->SetProperty(Rml::PropertyId::Left, Rml::Property(insets.left, Rml::Unit::PX));
        }
    }
    mLayout.apply(mWorking, touch_area_size(mDocument, mInsets));
    sync_selection();
    Document::update();
}

bool TouchControlsEditor::focus() {
    auto* command = mCommands[std::min(mFocusedCommand, mCommands.size() - 1)];
    return command != nullptr && command->Focus(true);
}

bool TouchControlsEditor::handle_nav_command(Rml::Event& event, NavCommand cmd) {
    switch (cmd) {
    case NavCommand::Cancel:
    case NavCommand::Menu:
        cancel();
        return true;
    case NavCommand::Confirm:
        activate(mFocusedCommand);
        return true;
    case NavCommand::Left:
    case NavCommand::Right: {
        const int step = cmd == NavCommand::Left ? -1 : 1;
        const int next = std::clamp(static_cast<int>(mFocusedCommand) + step, 0, static_cast<int>(mCommands.size()) - 1);
        if (mCommands[next] != nullptr && mCommands[next]->Focus(true)) {
            mFocusedCommand = static_cast<size_t>(next);
            play_nav_sound(NavSound::ItemFocus);
        }
        return true;
    }
    default:
        return Document::handle_nav_command(event, cmd);
    }
}

bool TouchControlsEditor::begin_edit(size_t index, Handle handle, Rml::Vector2f position, bool touch,
                                     SDL_FingerID finger) {
    const auto controls = touch_layout_controls();
    const auto area = touch_area_size(mDocument, mInsets);
    if (mEdit.active || index >= controls.size() || area.w <= 0.0f || area.h <= 0.0f) {
        return false;
    }
    const auto placement = placement_for(mWorking, controls[index]);
    mBeforeEdit = mWorking;
    mEdit = {
        .index = index,
        .finger = finger,
        .startPointer = area_position(position),
        .startVisual = resolve_visual(controls[index], placement, area),
        .startPlacement = placement,
        .handle = handle,
        .active = true,
        .touch = touch,
    };
    select(index);
    return true;
}

bool TouchControlsEditor::continue_edit(Rml::Vector2f position) {
    if (!mEdit.active) {
        return false;
    }
    const auto pointer = area_position(position);
    if (!mEdit.dragging) {
        const auto delta = pointer - mEdit.startPointer;
        if (delta.x * delta.x + delta.y * delta.y < kDragThresholdDp * kDragThresholdDp) {
            return true;
        }
        mEdit.dragging = true;
    }
    float scale = mEdit.startPlacement.scale;
    const auto rect = edited_rect(pointer, scale);
    const auto area = touch_area_size(mDocument, mInsets);
    mWorking.controls[std::string(touch_layout_controls()[mEdit.index].id)] = encode_placement(rect, scale, area);
    return true;
}

bool TouchControlsEditor::end_edit(bool touch, SDL_FingerID finger, bool cancelled) {
    if (!mEdit.active || mEdit.touch != touch || (touch && mEdit.finger != finger)) {
        return false;
    }
    if (cancelled && mEdit.dragging) {
        mWorking = mBeforeEdit;
    }
    mEdit = {};
    return true;
}

void TouchControlsEditor::select(size_t index) {
    mSelected = index < touch_layout_controls().size() ? index : SIZE_MAX;
    sync_selection();
}

void TouchControlsEditor::sync_selection() {
    const bool selected = mSelected < touch_layout_controls().size();
    for (size_t i = 0; i < touch_layout_controls().size(); ++i) {
        if (auto* element = mLayout.element(i)) {
            element->SetClass("editor-selected", selected && i == mSelected);
        }
    }
    if (mSelection == nullptr) {
        return;
    }
    mSelection->SetClass("visible", selected);
    if (!selected) {
        return;
    }
    const auto& visual = mLayout.visual(mSelected);
    mSelection->SetProperty(Rml::PropertyId::Left, Rml::Property(visual.l, Rml::Unit::DP));
    mSelection->SetProperty(Rml::PropertyId::Top, Rml::Property(visual.t, Rml::Unit::DP));
    mSelection->SetProperty(Rml::PropertyId::Width, Rml::Property(visual.w, Rml::Unit::DP));
    mSelection->SetProperty(Rml::PropertyId::Height, Rml::Property(visual.h, Rml::Unit::DP));
}

Rml::Vector2f TouchControlsEditor::area_position(Rml::Vector2f position) const {
    auto* context = mDocument != nullptr ? mDocument->GetContext() : nullptr;
    const float scale = context != nullptr ? std::max(context->GetDensityIndependentPixelRatio(), 1.0f) : 1.0f;
    return { (position.x - mInsets.left) / scale, (position.y - mInsets.top) / scale };
}

TouchRect TouchControlsEditor::edited_rect(Rml::Vector2f pointer, float& scale) const {
    const auto area = touch_area_size(mDocument, mInsets);
    const auto& start = mEdit.startVisual;
    auto rect = start;
    if (mEdit.handle == Handle::Move) {
        const auto delta = pointer - mEdit.startPointer;
        rect.l = std::clamp(start.l + delta.x, 0.0f, std::max(0.0f, area.w - rect.w));
        rect.t = std::clamp(start.t + delta.y, 0.0f, std::max(0.0f, area.h - rect.h));
        return rect;
    }

    const bool left = mEdit.handle == Handle::TopLeft || mEdit.handle == Handle::BottomLeft;
    const bool top = mEdit.handle == Handle::TopLeft || mEdit.handle == Handle::TopRight;
    const float fixedX = left ? start.l + start.w : start.l;
    const float fixedY = top ? start.t + start.h : start.t;
    const float desiredW = left ? fixedX - pointer.x : pointer.x - fixedX;
    const float desiredH = top ? fixedY - pointer.y : pointer.y - fixedY;
    const float startW = std::max(start.w, 1.0f);
    const float startH = std::max(start.h, 1.0f);
    const float startScale = std::max(mEdit.startPlacement.scale, kTouchMinScale);
    const float minRatio = kTouchMinScale / startScale;
    const float roomW = left ? fixedX : area.w - fixedX;
    const float roomH = top ? fixedY : area.h - fixedY;
    const float maxRatio = std::max(minRatio, std::min({ kTouchMaxScale / startScale, roomW / startW, roomH / startH }));
    const float ratio = std::clamp(std::max(desiredW / startW, desiredH / startH), minRatio, maxRatio);

    rect.w = start.w * ratio;
    rect.h = start.h * ratio;
    rect.l = left ? fixedX - rect.w : fixedX;
    rect.t = top ? fixedY - rect.h : fixedY;
    scale = startScale * ratio;
    return rect;
}

void TouchControlsEditor::activate(size_t command) {
    switch (command) {
    case 0:
        save();
        break;
    case 1:
        reset_layout();
        break;
    default:
        cancel();
        break;
    }
}

void TouchControlsEditor::save() {
    settings().input.touchLayout.set(mWorking);
    play_nav_sound(NavSound::Click);
    pop();
}

void TouchControlsEditor::reset_layout() {
    mWorking = {};
    mEdit = {};
    select(SIZE_MAX);
    play_nav_sound(NavSound::ItemChange);
}

void TouchControlsEditor::cancel() {
    play_nav_sound(NavSound::WindowClose);
    pop();
}

} // namespace acgc::ui
