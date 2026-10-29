#include "acgc/ui/bool_button.hpp"

#include "acgc/ui/localization.hpp"

#include <utility>

namespace acgc::ui {
namespace {

BoolButton::Props localized(BoolButton::Props props)
{
    props.valueOverride = [getValue = props.getValue, valueOverride = std::move(props.valueOverride)]() -> Rml::String {
        if (valueOverride) {
            if (Rml::String value = valueOverride(); !value.empty()) {
                return value;
            }
        }
        return localization::get(getValue() ? "common.on" : "common.off");
    };
    return props;
}

} // namespace

BoolButton::BoolButton(Rml::Element* parent, Props props)
    : borealis::ui::BoolButton(parent, localized(std::move(props)))
    , mArrows(*this, mValueElem)
{
}

void BoolButton::update()
{
    borealis::ui::BoolButton::update();
    mArrows.update(true, true, true);
}

} // namespace acgc::ui
