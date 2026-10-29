#include "acgc/ui/overlay.hpp"
#include "acgc/ui/ui.hpp"

#include "acgc/ui/localization.hpp"

#include "acgc/game_editor.hpp"

#include <algorithm>
#include <cmath>

namespace acgc::ui {
using namespace borealis::ui;

namespace {

constexpr float kMarginDp = 20.0f;

Rml::String document_source() {
    return R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/theme.rcss" />
    <link type="text/rcss" href="res/rml/controls.rcss" />
    <link type="text/rcss" href="res/rml/overlay.rcss" />
</head>
<body>
    <typing-status id="typing-status">
        <label>)RML" +
           escape(localization::get("overlay.keyboard_typing")) + R"RML(</label>
        <key>Tab</key>
        <state id="typing-state">)RML" +
           escape(localization::get("common.off")) + R"RML(</state>
    </typing-status>
</body>
</rml>
)RML";
}

} // namespace

Overlay::Overlay()
    : Document(document_source(), true, kScopeOverlay),
      mTypingStatus(mDocument ? mDocument->GetElementById("typing-status") : nullptr),
      mTypingState(mDocument ? mDocument->GetElementById("typing-state") : nullptr) {
}

void Overlay::show() {
    if (mDocument != nullptr) {
        mDocument->Show(Rml::ModalFlag::None, Rml::FocusFlag::None, Rml::ScrollFlag::None);
    }
}

void Overlay::update() {
    update_layout();

    const bool editorActive = acgc::input::game_editor().available();
    const auto typingState = acgc::input::game_editor().state();
    const bool typingActive = typingState == GAME_EDITOR_ACTIVE;

    if (mTypingStatus != nullptr && editorActive != mWasEditorActive) {
        if (editorActive) {
            mTypingStatus->SetAttribute("open", "");
        } else {
            mTypingStatus->RemoveAttribute("open");
        }
        mWasEditorActive = editorActive;
    }

    if (mTypingStatus != nullptr && typingState != mPreviousTypingState) {
        if (typingActive) {
            mTypingStatus->SetAttribute("active", "");
        } else {
            mTypingStatus->RemoveAttribute("active");
        }
        if (mTypingState != nullptr) {
            const char* label = typingActive                           ? "common.on"
                                : typingState == GAME_EDITOR_FAILED    ? "overlay.typing_unavailable"
                                : typingState == GAME_EDITOR_SUSPENDED ? "overlay.typing_suspended"
                                                                       : "common.off";
            mTypingState->SetInnerRML(escape(localization::get(label)));
        }
        mPreviousTypingState = typingState;
    }
}

void Overlay::update_layout() {
    if (mDocument == nullptr || mTypingStatus == nullptr) {
        return;
    }

    Rml::Context* context = mDocument->GetContext();
    if (context == nullptr) {
        return;
    }

    const Rml::Vector2i dimensions = context->GetDimensions();
    const float dpRatio = context->GetDensityIndependentPixelRatio();
    if (dimensions.x <= 0 || dimensions.y <= 0 || dpRatio <= 0.0f) {
        return;
    }

    const Insets safeInsets = safe_area_insets(context);
    const float margin = kMarginDp * dpRatio;
    const float top = std::round(std::max(margin, safeInsets.top));
    const float width = mTypingStatus->GetBox().GetSize(Rml::BoxArea::Border).x;
    const float safeAreaCenter = (safeInsets.left + static_cast<float>(dimensions.x) - safeInsets.right) * 0.5f;
    const float left = safeAreaCenter - width * 0.5f;

    if (top != mAppliedTop) {
        mTypingStatus->SetProperty(Rml::PropertyId::Top, Rml::Property(top, Rml::Unit::PX));
        mAppliedTop = top;
    }
    if (left != mAppliedLeft) {
        mTypingStatus->SetProperty(Rml::PropertyId::Left, Rml::Property(left, Rml::Unit::PX));
        mAppliedLeft = left;
    }
}

} // namespace acgc::ui
