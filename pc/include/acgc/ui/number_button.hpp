#pragma once

#include "acgc/ui/adjust_arrows.hpp"

#include <borealis/ui/number_button.hpp>

#include <functional>

namespace acgc::ui {

class NumberButton : public borealis::ui::NumberButton {
public:
    NumberButton(Rml::Element* parent, Props props);

    void update() override;

protected:
    bool handle_nav_command(borealis::ui::NavCommand cmd) override;

private:
    std::function<int()> mGetValue;
    int mMin;
    int mMax;
    bool mAdjustable;
    AdjustArrows mArrows;
};

} // namespace acgc::ui
