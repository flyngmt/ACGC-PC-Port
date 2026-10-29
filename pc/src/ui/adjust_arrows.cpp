#include "acgc/ui/adjust_arrows.hpp"

#include <utility>

namespace acgc::ui {
using borealis::ui::NavCommand;

AdjustArrows::AdjustArrows(borealis::ui::Component& owner, Rml::Element* value) : mValue(value)
{
    auto* root = owner.root();
    auto* doc = root->GetOwnerDocument();
    root->SetClass("adjustable", true);
    auto* group = root->InsertBefore(doc->CreateElement("adjust-value"), value);
    group->AppendChild(root->RemoveChild(value));

    const auto make_arrow = [doc](const char* glyph) {
        auto arrow = doc->CreateElement("span");
        arrow->SetClass("adjust-arrow", true);
        arrow->SetInnerRML(glyph);
        return arrow;
    };
    mLeft = group->InsertBefore(make_arrow("&#xe5de;"), value);
    mRight = group->AppendChild(make_arrow("&#xe5df;"));

    owner.listen(root, Rml::EventId::Mouseup, [this](Rml::Event& event) {
        auto* target = event.GetTargetElement();
        mReleased = nullptr;
        for (auto* arrow : { mLeft, mRight }) {
            if (target != nullptr && arrow->Contains(target)) {
                mReleased = arrow;
            }
        }
    });
}

void AdjustArrows::update(bool left, bool right, bool visible)
{
    mReleased = nullptr;
    const bool modified = mValue->IsClassSet("modified");
    for (const auto& [arrow, enabled] : { std::pair{ mLeft, left }, std::pair{ mRight, right } }) {
        arrow->SetClass("unavailable", !enabled);
        arrow->SetClass("modified", modified);
        if (visible) {
            arrow->RemoveProperty(Rml::PropertyId::Display);
        } else {
            arrow->SetProperty(Rml::PropertyId::Display, Rml::Style::Display::None);
        }
    }
}

NavCommand AdjustArrows::click_command(NavCommand cmd)
{
    auto* arrow = std::exchange(mReleased, nullptr);
    if (cmd != NavCommand::Confirm || arrow == nullptr) {
        return cmd;
    }
    if (arrow->IsClassSet("unavailable")) {
        return NavCommand::None;
    }
    return arrow == mLeft ? NavCommand::Left : NavCommand::Right;
}

} // namespace acgc::ui
