#pragma once

#include "acgc/ui/adjust_arrows.hpp"

#include <borealis/ui/bool_button.hpp>

namespace acgc::ui {

class BoolButton : public borealis::ui::BoolButton {
public:
    BoolButton(Rml::Element* parent, Props props);

    void update() override;

private:
    AdjustArrows mArrows;
};

} // namespace acgc::ui
