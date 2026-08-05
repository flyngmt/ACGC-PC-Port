#pragma once

#include "document.hpp"

namespace acgc::ui {

class Overlay final : public Document {
public:
    Overlay();

    void show() override;
    void update() override;

private:
    void update_layout();

    Rml::Element* mTypingStatus = nullptr;
    Rml::Element* mTypingState = nullptr;
    float mAppliedFontSize = -1.0f;
    float mAppliedTop = -1.0f;
    float mAppliedLeft = -1.0f;
    bool mWasEditorActive = false;
    bool mWasTypingActive = false;
};

} // namespace acgc::ui
