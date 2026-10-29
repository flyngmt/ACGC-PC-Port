#pragma once

#include <borealis/ui/component.hpp>

namespace acgc::ui {

class AdjustArrows {
public:
    AdjustArrows(borealis::ui::Component& owner, Rml::Element* value);

    void update(bool left, bool right, bool visible);
    borealis::ui::NavCommand click_command(borealis::ui::NavCommand cmd);

private:
    Rml::Element* mValue = nullptr;
    Rml::Element* mLeft = nullptr;
    Rml::Element* mRight = nullptr;
    Rml::Element* mReleased = nullptr;
};

} // namespace acgc::ui
