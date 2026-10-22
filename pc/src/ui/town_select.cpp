#include "acgc/ui/button.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"
#include "acgc/ui/window.hpp"

#include "pc_town_select.h"
#include "pc_typing.h"

#include <SDL3/SDL_timer.h>

#include <memory>
#include <vector>

namespace acgc::ui {
namespace {

constexpr int kGameCharSpace = 0x20;
constexpr Uint64 kConfirmDelayMs = 400;

class TownSelectModal;

int sResult              = PC_TOWN_SELECT_CANCELLED;
int sIndex               = -1;
TownSelectModal* sActive = nullptr;

Rml::String town_name(const pc_card_town_entry& town)
{
	if (!town.usable) {
		return localization::get("town_select.damaged");
	}

	int length = PC_CARD_TOWN_NAME_SIZE;
	while (length > 0 && town.name[length - 1] == kGameCharSpace) {
		--length;
	}
	Rml::String result;
	for (int i = 0; i < length; ++i) {
		char encoded[4] = {};
		if (pc_typing_game_code_to_utf8(town.name[i], encoded, sizeof(encoded)) > 0) {
			result += encoded;
		} else {
			result += '?';
		}
	}
	return result.empty() ? localization::get("common.unknown") : result;
}

class TownSelectModal final : public WindowSmall {
public:
	explicit TownSelectModal(int count)
	    : WindowSmall({
	          .windowClass         = "modal",
	          .dialogClass         = "modal-dialog",
	          .styleSheets         = { "res/rml/town_select.rcss" },
	          .scrollingBackground = true,
	      })
	{
		mRoot->SetClass("light", true);
		mRoot->SetClass("town-select", true);

		auto* header = append(mDialog, "div");
		header->SetClass("modal-header", true);
		auto* title = append(header, "div");
		title->SetClass("modal-title", true);
		title->SetInnerRML(escape(localization::get("town_select.title")));
		append(header, "icon")->SetClass("train", true);

		auto* body = append(mDialog, "div");
		body->SetClass("modal-body", true);
		body->SetInnerRML(escape(localization::get("town_select.prompt")));

		auto* list = append(mDialog, "div");
		list->SetClass("town-list", true);
		for (int i = 0; i < count; ++i) {
			const pc_card_town_entry* town = pc_card_b_town(i);
			if (town == nullptr) {
				continue;
			}
			auto button = std::make_unique<Button>(list, Rml::String { });
			auto* name  = append(button->root(), "div");
			name->SetClass("town-name", true);
			name->SetInnerRML(escape(town_name(*town)));
			auto* file = append(button->root(), "div");
			file->SetClass("town-file", true);
			file->SetInnerRML(escape(town->file));
			button->set_disabled(!town->usable);
			button->on_pressed([this, i] {
				if (SDL_GetTicks() - mOpenedAt >= kConfirmDelayMs) {
					finish(PC_TOWN_SELECT_CHOSEN, i);
				}
			});
			mButtons.push_back(std::move(button));
		}

		auto* actions = append(mDialog, "div");
		actions->SetClass("modal-actions", true);
		auto cancel = std::make_unique<Button>(actions, localization::get("common.cancel"));
		cancel->root()->SetClass("modal-btn", true);
		cancel->on_pressed([this] { finish(PC_TOWN_SELECT_CANCELLED, -1); });
		mButtons.push_back(std::move(cancel));

		sResult   = PC_TOWN_SELECT_PENDING;
		sIndex    = -1;
		sActive   = this;
		mOpenedAt = SDL_GetTicks();
		play_menu_sound(kSoundWindowOpen);
	}

	~TownSelectModal() override
	{
		if (sActive == this) {
			sResult = PC_TOWN_SELECT_CANCELLED;
			sIndex  = -1;
			sActive = nullptr;
		}
	}

	bool focus() override
	{
		for (auto& button : mButtons) {
			if (button->focus()) {
				return true;
			}
		}
		return false;
	}

protected:
	bool handle_nav_command(Rml::Event& event, NavCommand cmd) override
	{
		if (cmd == NavCommand::Cancel || cmd == NavCommand::Menu) {
			play_menu_sound(kSoundWindowClose);
			finish(PC_TOWN_SELECT_CANCELLED, -1);
			return true;
		}

		int direction = 0;
		if (cmd == NavCommand::Up) {
			direction = -1;
		} else if (cmd == NavCommand::Down) {
			direction = 1;
		} else {
			return cmd == NavCommand::Left || cmd == NavCommand::Right;
		}

		auto* target = event.GetTargetElement();
		for (int i = 0; i < static_cast<int>(mButtons.size()); ++i) {
			if (mButtons[i]->contains(target)) {
				for (int next = i + direction; next >= 0 && next < static_cast<int>(mButtons.size()); next += direction) {
					if (mButtons[next]->focus()) {
						play_menu_sound(kSoundItemFocus);
						break;
					}
				}
				return true;
			}
		}
		return focus();
	}

private:
	void finish(int result, int index)
	{
		if (sActive != this) {
			return;
		}
		sResult = result;
		sIndex  = index;
		sActive = nullptr;
		pop();
	}

	std::vector<std::unique_ptr<Button>> mButtons;
	Uint64 mOpenedAt = 0;
};

} // namespace
} // namespace acgc::ui

extern "C" int pc_town_select_open(void)
{
	using namespace acgc::ui;
	const int count = pc_card_b_town_count();
	if (sActive != nullptr) {
		return 0;
	}
	sResult = PC_TOWN_SELECT_CANCELLED;
	sIndex  = -1;
	if (count <= 0 || !initialized()) {
		return 0;
	}
	push_document(std::make_unique<TownSelectModal>(count));
	return 1;
}

extern "C" int pc_town_select_poll(int* index)
{
	using namespace acgc::ui;
	if (sResult == PC_TOWN_SELECT_PENDING) {
		return PC_TOWN_SELECT_PENDING;
	}
	const int result = sResult;
	if (index != nullptr) {
		*index = result == PC_TOWN_SELECT_CHOSEN ? sIndex : -1;
	}
	sResult = PC_TOWN_SELECT_CANCELLED;
	sIndex  = -1;
	return result;
}
