#include "acgc/ui/menu_bar.hpp"

#include "acgc/ui/controller_config.hpp"
#include <borealis/ui/modal.hpp>
#include "acgc/ui/settings.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"

extern "C" int g_pc_running;

namespace acgc::ui {
using namespace borealis::ui;

MenuBar::MenuBar() {
    build_tabs();
}

void MenuBar::build_tabs() {
    mTabBar->add_tab(localization::get("common.settings"), [this] { push(std::make_unique<SettingsWindow>()); });
    mTabBar->add_tab(localization::get("menu.controls"), [this] { push(std::make_unique<ControllerConfigWindow>()); });
    mTabBar->add_tab(localization::get("common.quit"), [this] {
        mTabBar->set_active_tab(-1);
        push(std::make_unique<Modal>(Modal::Props{
            .title = escape(localization::get("menu.quit.title")),
            .bodyRml = escape(localization::get("menu.quit.warning")),
            .actions = {
                {localization::get("common.cancel"), [](Modal& modal) { modal.pop(); }},
                {localization::get("common.quit"), [](Modal& modal) {
                    modal.pop();
                    g_pc_running = 0;
                },},
            },
            .onDismiss = [](Modal& modal) { modal.pop(); },
            .variant = "light",
            .icon = "warning",
        }));
    });
}
} // namespace acgc::ui
