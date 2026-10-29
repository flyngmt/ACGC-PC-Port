#include "acgc/ui/bool_button.hpp"

#include <utility>

namespace acgc::ui {

BoolButton::BoolButton(Rml::Element* parent, Props props)
    : borealis::ui::BoolButton(parent, std::move(props))
    , mArrows(*this, mValueElem)
{
}

void BoolButton::update()
{
    borealis::ui::BoolButton::update();
    mArrows.update(true, true, true);
}

} // namespace acgc::ui
