#pragma once
#include <borealis/ui/menu_bar.hpp>
#include "ui.hpp"
namespace acgc::ui {
class MenuBar final : public borealis::ui::MenuBar {
public:
    MenuBar();
protected:
    void build_tabs() override;
};
} // namespace acgc::ui
