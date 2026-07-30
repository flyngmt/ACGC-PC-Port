#pragma once

#include "document.hpp"
#include "tab_bar.hpp"

#include <memory>

namespace acgc::ui {

class MenuBar final : public Document {
public:
    MenuBar();

    void show() override;
    void hide(bool close) override;
    bool focus() override;
    bool visible() const override;

protected:
    bool handle_nav_command(Rml::Event& event, NavCommand command) override;

private:
    Rml::Element* mRoot = nullptr;
    std::unique_ptr<TabBar> mTabBar;
};

} // namespace acgc::ui
