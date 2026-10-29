#pragma once

#include <borealis/ui/number_button.hpp>

namespace acgc::ui {

class NumberButton : public borealis::ui::NumberButton {
public:
    using borealis::ui::NumberButton::NumberButton;

protected:
    bool handle_nav_command(borealis::ui::NavCommand cmd) override;
};

} // namespace acgc::ui
