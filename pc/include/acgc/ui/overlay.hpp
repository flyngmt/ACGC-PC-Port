#pragma once

#include <borealis/ui/document.hpp>
#include "game_editor.h"

namespace acgc::ui {

class Overlay final : public borealis::ui::Document {
public:
    Overlay();

    void show() override;
    void update() override;

private:
    void update_layout();

    Rml::Element* mTypingStatus = nullptr;
    Rml::Element* mTypingState = nullptr;
    float mAppliedTop = -1.0f;
    float mAppliedLeft = -1.0f;
    bool mWasEditorActive = false;
    GameEditorState mPreviousTypingState = GAME_EDITOR_OFF;
};

} // namespace acgc::ui
