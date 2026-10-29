#include "acgc/ui/number_button.hpp"

#include "acgc/ui/ui.hpp"

namespace acgc::ui {

NumberButton::NumberButton(Rml::Element* parent, Props props)
    : borealis::ui::NumberButton(parent, props)
    , mGetValue(props.getValue)
    , mMin(props.min)
    , mMax(props.max)
    , mAdjustable(props.setValue && props.step > 0)
    , mArrows(*this, mValueElem)
{
}

void NumberButton::update()
{
    borealis::ui::NumberButton::update();
    const int value = mGetValue ? mGetValue() : mMin;
    mArrows.update(mAdjustable && value > mMin, mAdjustable && value < mMax, !is_editing());
}

bool NumberButton::handle_nav_command(borealis::ui::NavCommand cmd)
{
    cmd = mArrows.click_command(cmd);
    if (cmd == borealis::ui::NavCommand::None) {
        return true;
    }
    if (cmd == borealis::ui::NavCommand::Confirm && !is_editing() && dispatching_controller_input()) {
        return true;
    }
    return borealis::ui::NumberButton::handle_nav_command(cmd);
}

} // namespace acgc::ui
