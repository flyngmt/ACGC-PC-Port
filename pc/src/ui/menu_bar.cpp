#include "acgc/ui/menu_bar.hpp"

#include "acgc/ui/controller_config.hpp"
#include "acgc/ui/modal.hpp"
#include "acgc/ui/settings.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"

extern "C" int g_pc_running;

namespace acgc::ui {
namespace {

const Rml::String kDocumentSource = R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/tabbing.rcss" />
    <link type="text/rcss" href="res/rml/popup.rcss" />
</head>
<body>
    <popup id="popup" />
</body>
</rml>
)RML";

} // namespace

MenuBar::MenuBar()
    : Document(kDocumentSource, false, DocumentScope::MenuBar)
    , mRoot(mDocument ? mDocument->GetElementById("popup") : nullptr)
{
    if (!mRoot) {
        return;
    }

    mTabBar = std::make_unique<TabBar>(mRoot, TabBar::Props{
        .onClose = [this] { hide(false); },
        .autoSelect = false,
    });
    mTabBar->add_tab(localization::get("common.settings"),
                     [this] { push(std::make_unique<SettingsWindow>()); });
    mTabBar->add_tab(localization::get("menu.controllers"),
                     [this] { push(std::make_unique<ControllerConfigWindow>()); });
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
                }},
            },
            .onDismiss = [](Modal& modal) { modal.pop(); },
        }));
    });

    listen(mRoot, Rml::EventId::Transitionend, [this](Rml::Event& event) {
        if (event.GetTargetElement() == mRoot && !mRoot->HasAttribute("open") && Document::visible()) {
            Document::hide(mPendingClose);
        }
    });
}

void MenuBar::show()
{
    Document::show();
    if (mRoot) {
        mRoot->SetAttribute("open", "");
    }
    if (mTabBar) {
        mTabBar->set_active_tab(-1);
        mTabBar->focus();
    }
}

void MenuBar::hide(bool close)
{
    if (mRoot) {
        mRoot->RemoveAttribute("open");
    }
    mPendingClose |= close;
}

bool MenuBar::focus()
{
    return mTabBar && mTabBar->focus();
}

bool MenuBar::visible() const
{
    return mRoot && mRoot->HasAttribute("open");
}

bool MenuBar::handle_nav_command(Rml::Event& event, NavCommand command)
{
    if ((command == NavCommand::Cancel || command == NavCommand::Menu) && visible()) {
        hide(false);
        return true;
    }
    return Document::handle_nav_command(event, command);
}

} // namespace acgc::ui
