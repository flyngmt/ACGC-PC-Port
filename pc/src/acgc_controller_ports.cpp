#include "acgc/controller_ports.hpp"

#include "acgc/config.hpp"
#include "acgc/settings.hpp"
#include "borealis/log.hpp"

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <dolphin/pad.h>

#include <algorithm>
#include <vector>

namespace acgc::controller_ports {
namespace {

constexpr borealis::Log Log{"acgc::input"};

struct TrackedController {
	SDL_JoystickID id = 0;
	Uint64 buttons    = 0;
};

std::vector<TrackedController> sTracked;

Uint64 held_buttons(SDL_Gamepad* gamepad)
{
	Uint64 buttons = 0;
	for (int button = 0; button < SDL_GAMEPAD_BUTTON_COUNT; ++button) {
		if (SDL_GetGamepadButton(gamepad, static_cast<SDL_GamepadButton>(button))) {
			buttons |= Uint64 { 1 } << button;
		}
	}
	return buttons;
}

bool keyboard_has_bindings()
{
	u32 buttonCount                    = 0;
	u32 axisCount                      = 0;
	const PADKeyButtonBinding* buttons = PADGetKeyButtonBindings(PAD_CHAN0, &buttonCount);
	const PADKeyAxisBinding* axes      = PADGetKeyAxisBindings(PAD_CHAN0, &axisCount);
	for (u32 i = 0; buttons != nullptr && i < buttonCount; ++i) {
		if (buttons[i].scancode != PAD_KEY_INVALID) {
			return true;
		}
	}
	for (u32 i = 0; axes != nullptr && i < axisCount; ++i) {
		if (axes[i].scancode != PAD_KEY_INVALID) {
			return true;
		}
	}
	return false;
}

void restore_keyboard()
{
	u32 count = 0;
	if (PADGetKeyButtonBindings(PAD_CHAN0, &count) != nullptr) {
		return;
	}
	PADSetKeyboardActive(PAD_CHAN0, TRUE);
	if (!keyboard_has_bindings()) {
		PADSetKeyboardActive(PAD_CHAN0, FALSE);
	}
}

void assign(u32 index)
{
	PADSetPortForIndex(index, PAD_CHAN0);
	apply_runtime_settings(false);
}

} // namespace

void initialize()
{
	for (u32 port = PAD_CHAN1; port < PAD_CHANMAX; ++port) {
		PADSetKeyboardActive(port, FALSE);
	}
	restore_keyboard();

	auto& input = settings().input;
	if (!input.singlePortMigrated.value()) {
		for (u32 port = PAD_CHAN0; port < PAD_CHANMAX; ++port) {
			PADClearPort(port);
		}
		input.singlePortMigrated.set_value(true);
		config::save();
	}
}

void enforce_single_port()
{
	for (u32 index = 0; index < PADCount(); ++index) {
		SDL_Gamepad* gamepad = PADGetSDLGamepadForIndex(index);
		if (gamepad != nullptr && SDL_GetGamepadPlayerIndex(gamepad) > PAD_CHAN0) {
			SDL_SetGamepadPlayerIndex(gamepad, -1);
		}
	}
}

void update()
{
	const bool canAssign = auto_assign() && PADGetIndexForPort(PAD_CHAN0) < 0;
	s32 pressedIndex     = -1;

	std::vector<TrackedController> current;
	for (u32 index = 0; index < PADCount(); ++index) {
		SDL_Gamepad* gamepad = PADGetSDLGamepadForIndex(index);
		if (gamepad == nullptr) {
			continue;
		}
		const SDL_JoystickID id = SDL_GetGamepadID(gamepad);
		const Uint64 buttons    = held_buttons(gamepad);
		const auto tracked
		    = std::find_if(sTracked.begin(), sTracked.end(), [id](const TrackedController& entry) { return entry.id == id; });
		const Uint64 previous = tracked != sTracked.end() ? tracked->buttons : buttons;
		if (canAssign && pressedIndex < 0 && (buttons & ~previous) != 0) {
			pressedIndex = static_cast<s32>(index);
		}
		current.push_back({ id, buttons });
	}
	sTracked = std::move(current);

	if (pressedIndex >= 0) {
		const char* name = PADGetNameForControllerIndex(static_cast<u32>(pressedIndex));
		Log.info("Assigned controller '{}' to player 1", name != nullptr ? name : "unknown");
		assign(static_cast<u32>(pressedIndex));
	}
}

bool auto_assign()
{
	return settings().input.autoAssignController.value() || !SDL_HasKeyboard();
}

void select_automatic()
{
	PADClearPort(PAD_CHAN0);
	settings().input.autoAssignController.set_value(true);
	config::save();
}

void select_none()
{
	PADClearPort(PAD_CHAN0);
	settings().input.autoAssignController.set_value(false);
	config::save();
}

void select_controller(u32 index)
{
	assign(index);
	settings().input.autoAssignController.set_value(true);
	config::save();
}

} // namespace acgc::controller_ports
