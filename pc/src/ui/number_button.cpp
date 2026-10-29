#include "acgc/ui/number_button.hpp"

#include "acgc/ui/ui.hpp"

namespace acgc::ui {

bool NumberButton::handle_nav_command(borealis::ui::NavCommand cmd)
{
    if (cmd == borealis::ui::NavCommand::Confirm && !is_editing() && dispatching_controller_input()) {
        return true;
    }
    return borealis::ui::NumberButton::handle_nav_command(cmd);
}

} // namespace acgc::ui
