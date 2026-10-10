#include "controller_config.hpp"

#include "bool_button.hpp"
#include "button.hpp"
#include "number_button.hpp"
#include "pane.hpp"
#include "acgc/ui/localization.hpp"
#include "ui.hpp"

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <array>
#include <string>
#include <utility>
#include <vector>

#include "acgc/config.hpp"
#include "acgc/controller_ports.hpp"
#include "acgc/settings.hpp"

namespace acgc::ui {
namespace {

constexpr int kPort = PAD_CHAN0;

Rml::String current_controller_name(int port)
{
	const char* name = PADGetName(port);
	if (name != nullptr) {
		return name;
	}
	return controller_ports::auto_assign() ? localization::get("controller.device.waiting")
	                                       : localization::get("controller.device.none");
}

Rml::String controller_index_name(u32 index)
{
	const char* name = PADGetNameForControllerIndex(index);
	if (name == nullptr) {
		return localization::format("controller.device.numbered", index + 1);
	}
	return name;
}

SDL_Gamepad* gamepad_for_port(int port)
{
	const s32 index = PADGetIndexForPort(port);
	if (index < 0) {
		return nullptr;
	}
	return PADGetSDLGamepadForIndex(static_cast<u32>(index));
}

SDL_JoystickID controller_id_for_port(int port)
{
	SDL_Gamepad* gamepad = gamepad_for_port(port);
	return gamepad != nullptr ? SDL_GetGamepadID(gamepad) : 0;
}

struct SpecificButtonName {
	SDL_GamepadType type;
	const char* name;
	bool translatable = false;
};

struct ButtonNames {
	SDL_GamepadButton button;
	std::vector<SpecificButtonName> names;
};

// clang-format off
const std::vector<ButtonNames> kGamepadButtonNames = {
    { SDL_GAMEPAD_BUTTON_LEFT_STICK, {
        {SDL_GAMEPAD_TYPE_PS3, "L3"},
        {SDL_GAMEPAD_TYPE_PS4, "L3"},
        {SDL_GAMEPAD_TYPE_PS5, "L3"},
        {SDL_GAMEPAD_TYPE_XBOX360, "controller.input.left_stick", true},
        {SDL_GAMEPAD_TYPE_XBOXONE, "controller.input.left_stick", true},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "controller.input.control_stick", true},
    }},
    { SDL_GAMEPAD_BUTTON_RIGHT_STICK, {
        {SDL_GAMEPAD_TYPE_PS3, "R3"},
        {SDL_GAMEPAD_TYPE_PS4, "R3"},
        {SDL_GAMEPAD_TYPE_PS5, "R3"},
        {SDL_GAMEPAD_TYPE_XBOX360, "controller.input.right_stick", true},
        {SDL_GAMEPAD_TYPE_XBOXONE, "controller.input.right_stick", true},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "controller.input.c_stick", true},
    }},
    { SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, {
        {SDL_GAMEPAD_TYPE_PS3, "L1"},
        {SDL_GAMEPAD_TYPE_PS4, "L1"},
        {SDL_GAMEPAD_TYPE_PS5, "L1"},
        {SDL_GAMEPAD_TYPE_XBOX360, "LB"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "LB"},
    }},
    { SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, {
        {SDL_GAMEPAD_TYPE_PS3, "R1"},
        {SDL_GAMEPAD_TYPE_PS4, "R1"},
        {SDL_GAMEPAD_TYPE_PS5, "R1"},
        {SDL_GAMEPAD_TYPE_XBOX360, "RB"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "RB"},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "Z"},
    }},
    { SDL_GAMEPAD_BUTTON_BACK, {
        {SDL_GAMEPAD_TYPE_PS3, "controller.input.select", true},
        {SDL_GAMEPAD_TYPE_PS4, "controller.input.share", true},
        {SDL_GAMEPAD_TYPE_PS5, "controller.input.create", true},
        {SDL_GAMEPAD_TYPE_XBOX360, "controller.input.back", true},
        {SDL_GAMEPAD_TYPE_XBOXONE, "controller.input.view", true},
    }},
    { SDL_GAMEPAD_BUTTON_START, {
        {SDL_GAMEPAD_TYPE_PS3, "controller.input.start", true},
        {SDL_GAMEPAD_TYPE_PS4, "controller.input.options", true},
        {SDL_GAMEPAD_TYPE_PS5, "controller.input.options", true},
        {SDL_GAMEPAD_TYPE_XBOX360, "controller.input.start", true},
        {SDL_GAMEPAD_TYPE_XBOXONE, "controller.input.menu", true},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "controller.input.start_pause", true},
    }},
};
// clang-format on

Rml::String stick_name(SDL_GamepadType type, bool right)
{
	if (type == SDL_GAMEPAD_TYPE_GAMECUBE) {
		return localization::get(right ? "controller.input.c_stick" : "controller.input.control_stick");
	}
	return localization::get(right ? "controller.input.right_stick" : "controller.input.left_stick");
}

Rml::String trigger_name(SDL_GamepadType type, bool right)
{
	switch (type) {
	case SDL_GAMEPAD_TYPE_PS3:
	case SDL_GAMEPAD_TYPE_PS4:
	case SDL_GAMEPAD_TYPE_PS5:
		return right ? "R2" : "L2";
	case SDL_GAMEPAD_TYPE_XBOX360:
	case SDL_GAMEPAD_TYPE_XBOXONE:
		return right ? "RT" : "LT";
	case SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_PRO:
		return right ? "ZR" : "ZL";
	case SDL_GAMEPAD_TYPE_GAMECUBE:
		return right ? "R" : "L";
	default:
		return localization::get(right ? "controller.input.right_trigger" : "controller.input.left_trigger");
	}
}

Rml::String stick_direction(SDL_GamepadType type, bool right, const char* direction)
{
	return localization::format("controller.input.stick_direction", stick_name(type, right), localization::get(direction));
}

Rml::String native_axis_label(SDL_Gamepad* gamepad, PADSignedNativeAxis axis)
{
	const SDL_GamepadType type = gamepad != nullptr ? SDL_GetGamepadType(gamepad) : SDL_GAMEPAD_TYPE_UNKNOWN;
	const bool positive        = axis.sign == AXIS_SIGN_POSITIVE;
	switch (static_cast<SDL_GamepadAxis>(axis.nativeAxis)) {
	case SDL_GAMEPAD_AXIS_LEFTX:
		return stick_direction(type, false, positive ? "controller.input.right" : "controller.input.left");
	case SDL_GAMEPAD_AXIS_LEFTY:
		return stick_direction(type, false, positive ? "controller.input.down" : "controller.input.up");
	case SDL_GAMEPAD_AXIS_RIGHTX:
		return stick_direction(type, true, positive ? "controller.input.right" : "controller.input.left");
	case SDL_GAMEPAD_AXIS_RIGHTY:
		return stick_direction(type, true, positive ? "controller.input.down" : "controller.input.up");
	case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
		return trigger_name(type, false);
	case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
		return trigger_name(type, true);
	default:
		return PADGetNativeAxisName(axis);
	}
}

Rml::String native_axis_name(const PADAxisMapping& mapping, SDL_Gamepad* gamepad)
{
	if (mapping.nativeAxis.nativeAxis != -1) {
		return native_axis_label(gamepad, mapping.nativeAxis);
	}

	if (mapping.nativeButton != -1) {
		return native_button_name(gamepad, static_cast<u32>(mapping.nativeButton));
	}

	return localization::get("controller.binding.not_bound");
}

bool is_dpad_button(PADButton button)
{
	return button == PAD_BUTTON_UP || button == PAD_BUTTON_DOWN || button == PAD_BUTTON_LEFT || button == PAD_BUTTON_RIGHT;
}

bool is_action_button(PADButton button)
{
	return button == PAD_BUTTON_A || button == PAD_BUTTON_B || button == PAD_BUTTON_X || button == PAD_BUTTON_Y
	    || button == PAD_BUTTON_START || button == PAD_TRIGGER_Z;
}

bool input_neutral(int port)
{
	if (port < 0) {
		return true;
	}
	return PADGetNativeButtonPressed(port) == -1 && PADGetNativeAxisPulled(port).nativeAxis == -1;
}

// A Keydown event with KI_ESCAPE may have been dispatched from the controller bindings,
// so instead poll the keyboard input directly for Escape-to-unbind
bool keyboard_escape_pressed()
{
	int keyCount     = 0;
	const bool* keys = SDL_GetKeyboardState(&keyCount);
	if (keys == nullptr || SDL_SCANCODE_ESCAPE >= keyCount || !keys[SDL_SCANCODE_ESCAPE]) {
		return false;
	}
	for (int i = 0; i < keyCount; ++i) {
		if (i != SDL_SCANCODE_ESCAPE && keys[i]) {
			return false;
		}
	}
	return true;
}

Rml::String keyboard_key_name(s32 scancode)
{
	if (scancode == PAD_KEY_INVALID) {
		return localization::get("controller.binding.not_bound");
	}
	switch (scancode) {
	case PAD_KEY_MOUSE_LEFT:
		return localization::get("controller.input.mouse_left");
	case PAD_KEY_MOUSE_MIDDLE:
		return localization::get("controller.input.mouse_middle");
	case PAD_KEY_MOUSE_RIGHT:
		return localization::get("controller.input.mouse_right");
	case PAD_KEY_MOUSE_X1:
		return localization::get("controller.input.mouse_x1");
	case PAD_KEY_MOUSE_X2:
		return localization::get("controller.input.mouse_x2");
	default:
		break;
	}
	if (scancode < 0) {
		return localization::get("common.unknown");
	}
	const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(scancode));
	if (name == nullptr || name[0] == '\0') {
		return localization::get("common.unknown");
	}
	return name;
}

bool keyboard_neutral()
{
	int keyCount     = 0;
	const bool* keys = SDL_GetKeyboardState(&keyCount);
	if (keys != nullptr) {
		for (int i = 0; i < keyCount; ++i) {
			if (keys[i]) {
				return false;
			}
		}
	}
	float x, y;
	if (SDL_GetMouseState(&x, &y) != 0) {
		return false;
	}
	return true;
}

s32 keyboard_key_pressed()
{
	int keyCount     = 0;
	const bool* keys = SDL_GetKeyboardState(&keyCount);
	if (keys != nullptr) {
		for (int i = 1; i < keyCount; ++i) {
			if (i == SDL_SCANCODE_ESCAPE || i == SDL_SCANCODE_F1) {
				continue;
			}
			if (keys[i]) {
				return static_cast<s32>(i);
			}
		}
	}
	float x, y;
	const auto mouseButtons = SDL_GetMouseState(&x, &y);
	for (int btn = 1; btn <= 5; ++btn) {
		if (mouseButtons & (1u << (btn - 1))) {
			return -(btn + 1); // maps to PAD_KEY_MOUSE_LEFT (-2), etc.
		}
	}
	return PAD_KEY_INVALID;
}

u16 percent_to_raw(int percent)
{
	return static_cast<u16>((static_cast<float>(percent) / 100.f) * 32767.f);
}

int deadzone_raw_to_percent(u16 raw)
{
	return static_cast<int>((static_cast<float>(raw) * 100.f) / 32767.f + 0.5f);
}

int rumble_raw_to_percent(u16 raw)
{
	return static_cast<int>((static_cast<float>(raw) / 32767.f) * 100.f + 0.5f);
}

} // namespace

ControllerConfigWindow::ControllerConfigWindow()
{
	listen(
	    Rml::EventId::Keydown,
	    [this](Rml::Event& event) {
		    if (capture_active() || mSuppressNavigationUntilNeutral) {
			    event.StopPropagation();
		    }
	    },
	    true);

	if (auto* context = mDocument != nullptr ? mDocument->GetContext() : nullptr) {
		if (auto* root = context->GetRootElement()) {
			mListeners.emplace_back(
			    std::make_unique<ScopedEventListener>(root, "controllerchange", [this](Rml::Event&) { refresh_controller_page(); }));
		}
	}

	add_tab(localization::get("menu.controls"), [this](Rml::Element* content) { build_tab(content); });
}

bool ControllerConfigWindow::is_keyboard_page(Page page)
{
	return page == Page::KeyboardButtons || page == Page::KeyboardTriggers || page == Page::KeyboardSticks;
}

void ControllerConfigWindow::hide(bool close)
{
	stop_rumble_test();
	cancel_pending_binding();
	config::save();
	Window::hide(close);
}

void ControllerConfigWindow::update()
{
	if (const SDL_JoystickID controller = controller_id_for_port(kPort); controller != mPortController) {
		mPortController = controller;
		if (mPage != Page::Controller) {
			refresh_controller_page();
		}
	}
	poll_pending_binding();
	Window::update();
}

void ControllerConfigWindow::build_tab(Rml::Element* content)
{
	const int port = kPort;
	stop_rumble_test();
	auto& leftPane  = add_child<Pane>(content, Pane::Type::Controlled);
	auto& rightPane = add_child<Pane>(content, Pane::Type::Uncontrolled);
	mRightPane      = &rightPane;
	mActivePort     = port;
	mPortController = controller_id_for_port(port);

	auto addPageButton = [this, &leftPane, &rightPane, port](Page page, Rml::String key, auto getValue, auto isDisabled) {
		leftPane.register_control(leftPane.add_select_button({
		                              .key        = std::move(key),
		                              .getValue   = std::move(getValue),
		                              .isDisabled = std::move(isDisabled),
		                          }),
		                          rightPane, [this, port, page](Pane& pane) {
			                          if (is_keyboard_page(page) != is_keyboard_page(mPage)) {
				                          cancel_pending_binding();
			                          }
			                          mPage = page;
			                          render_page(pane, port, page);
		                          });
	};
	auto pageValue   = [] { return Rml::String(">"); };
	auto notDisabled = [] { return false; };

	leftPane.add_section(localization::get("controller.section.controller"));
	addPageButton(Page::Controller, localization::get("controller.page.device"),
	              [port] { return current_controller_name(port); }, notDisabled);
	addPageButton(Page::Buttons, localization::get("controller.page.buttons"), pageValue, notDisabled);
	addPageButton(Page::Triggers, localization::get("controller.page.triggers"), pageValue, notDisabled);
	addPageButton(Page::Sticks, localization::get("controller.page.sticks"), pageValue, notDisabled);
	addPageButton(Page::Rumble, localization::get("controller.page.rumble"), pageValue,
	              [port] { return !PADSupportsRumbleIntensity(static_cast<u32>(port)); });

	leftPane.add_section(localization::get("controller.options.section"));
	leftPane.register_control(leftPane.add_child<BoolButton>(BoolButton::Props {
	                              .key = localization::get("controller.options.emulate_triggers"),
	                              .getValue =
	                                  [port] {
		                                  PADDeadZones* deadZones = PADGetDeadZones(port);
		                                  return deadZones != nullptr && deadZones->emulateTriggers;
	                                  },
	                              .setValue =
	                                  [port](bool value) {
		                                  if (PADDeadZones* deadZones = PADGetDeadZones(port)) {
			                                  deadZones->emulateTriggers = value;
			                                  PADSerializeMappings();
		                                  }
	                                  },
	                              .isDisabled = [port] { return PADGetDeadZones(port) == nullptr; },
	                          }),
	                          rightPane,
	                          [](Pane& pane) { pane.add_text(localization::get("controller.options.emulate_triggers_help")); });
	leftPane.register_control(leftPane.add_button(localization::get("controller.options.restore_defaults")).on_pressed([port] {
		play_menu_sound(kSoundClick);
		PADRestoreDefaultMapping(port);
	}),
	                          rightPane, [](Pane& pane) {
		                          pane.clear();
		                          pane.add_text(localization::get("controller.options.restore_defaults_help"));
	                          });

	if (SDL_HasKeyboard()) {
		leftPane.add_section(localization::get("controller.section.keyboard"));
		addPageButton(Page::KeyboardButtons, localization::get("controller.page.buttons"), pageValue, notDisabled);
		addPageButton(Page::KeyboardTriggers, localization::get("controller.page.triggers"), pageValue, notDisabled);
		addPageButton(Page::KeyboardSticks, localization::get("controller.page.sticks"), pageValue, notDisabled);
	} else if (is_keyboard_page(mPage)) {
		mPage = Page::Controller;
	}
	render_page(rightPane, port, mPage);
}

void ControllerConfigWindow::render_page(Pane& pane, int port, Page page)
{
	pane.clear();
	const bool keyboard = is_keyboard_page(page);

	switch (page) {
	case Page::Controller:
	{
		pane.add_button({
		                    .text       = localization::get("controller.device.automatic"),
		                    .isSelected = [port] { return PADGetIndexForPort(port) < 0 && controller_ports::auto_assign(); },
		                })
		    .on_pressed([this] {
			    play_menu_sound(kSoundClick);
			    cancel_pending_binding();
			    controller_ports::select_automatic();
		    });

		const bool hasKeyboard = SDL_HasKeyboard();
		if (hasKeyboard) {
			pane.add_button({
			                    .text       = localization::get("controller.device.none"),
			                    .isSelected = [port] { return PADGetIndexForPort(port) < 0 && !controller_ports::auto_assign(); },
			                })
			    .on_pressed([this] {
				    play_menu_sound(kSoundClick);
				    cancel_pending_binding();
				    controller_ports::select_none();
			    });
		}

		const u32 controllerCount = PADCount();
		for (u32 i = 0; i < controllerCount; ++i) {
			pane.add_button({
			                    .text       = controller_index_name(i),
			                    .isSelected = [port, i] { return PADGetIndexForPort(port) == static_cast<s32>(i); },
			                })
			    .on_pressed([this, i] {
				    play_menu_sound(kSoundClick);
				    cancel_pending_binding();
				    controller_ports::select_controller(i);
			    });
		}

		if (controllerCount == 0) {
			pane.add_text(localization::get("controller.device.none_detected"));
		}
		pane.add_text(localization::get("controller.device.automatic_help"));
		if (hasKeyboard) {
			pane.add_text(localization::get("controller.device.keyboard_help"));
		}
		break;
	}
	case Page::Buttons:
	case Page::KeyboardButtons:
	{
		if (keyboard) {
			auto addKeyButton = [&](PADButton button) {
				pane.add_select_button({
				                           .key = PADGetButtonName(button),
				                           .getValue =
				                               [this, port, button] {
					                               if (mPendingKeyButton == static_cast<int>(button)) {
						                               return pending_key_label();
					                               }
					                               u32 count                     = 0;
					                               PADKeyButtonBinding* bindings = PADGetKeyButtonBindings(static_cast<u32>(port), &count);
					                               if (bindings == nullptr) {
						                               return localization::get("controller.binding.not_bound");
					                               }
					                               for (u32 i = 0; i < PAD_BUTTON_COUNT; ++i) {
						                               if (bindings[i].padButton == button) {
							                               return keyboard_key_name(bindings[i].scancode);
						                               }
					                               }
					                               return localization::get("controller.binding.not_bound");
				                               },
				                       })
				    .on_pressed([this, port, button] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort         = port;
					    mPendingBindingArmed = false;
					    mPendingKeyButton    = static_cast<int>(button);
				    });
			};

			pane.add_section(localization::get("controller.page.buttons"));
			addKeyButton(PAD_BUTTON_A);
			addKeyButton(PAD_BUTTON_B);
			addKeyButton(PAD_BUTTON_X);
			addKeyButton(PAD_BUTTON_Y);
			addKeyButton(PAD_BUTTON_START);
			addKeyButton(PAD_TRIGGER_Z);

			pane.add_section(localization::get("controller.section.d_pad"));
			addKeyButton(PAD_BUTTON_UP);
			addKeyButton(PAD_BUTTON_DOWN);
			addKeyButton(PAD_BUTTON_LEFT);
			addKeyButton(PAD_BUTTON_RIGHT);
			break;
		}

		u32 buttonCount            = 0;
		PADButtonMapping* mappings = PADGetButtonMappings(port, &buttonCount);
		if (mappings == nullptr) {
			pane.add_text(localization::get("controller.device.none_selected"));
			break;
		}

		SDL_Gamepad* gamepad = gamepad_for_port(port);
		pane.add_section(localization::get("controller.page.buttons"));
		for (u32 i = 0; i < buttonCount; ++i) {
			PADButtonMapping& mapping = mappings[i];
			if (!is_action_button(mapping.padButton)) {
				continue;
			}

			pane.add_select_button({
			                           .key = PADGetButtonName(mapping.padButton),
			                           .getValue =
			                               [this, &mapping, gamepad] {
				                               if (mPendingButtonMapping == &mapping) {
					                               return pending_button_label();
				                               }
				                               return native_button_name(gamepad, mapping.nativeButton);
			                               },
			                       })
			    .on_pressed([this, port, &mapping] {
				    play_menu_sound(kSoundClick);
				    cancel_pending_binding();
				    mPendingPort          = port;
				    mPendingBindingArmed  = false;
				    mPendingButtonMapping = &mapping;
			    });
		}

		pane.add_section(localization::get("controller.section.d_pad"));
		for (u32 i = 0; i < buttonCount; ++i) {
			PADButtonMapping& mapping = mappings[i];
			if (!is_dpad_button(mapping.padButton)) {
				continue;
			}

			pane.add_select_button({
			                           .key = PADGetButtonName(mapping.padButton),
			                           .getValue =
			                               [this, &mapping, gamepad] {
				                               if (mPendingButtonMapping == &mapping) {
					                               return pending_button_label();
				                               }
				                               return native_button_name(gamepad, mapping.nativeButton);
			                               },
			                       })
			    .on_pressed([this, port, &mapping] {
				    play_menu_sound(kSoundClick);
				    cancel_pending_binding();
				    mPendingPort          = port;
				    mPendingBindingArmed  = false;
				    mPendingButtonMapping = &mapping;
			    });
		}
		break;
	}
	case Page::Triggers:
	case Page::KeyboardTriggers:
	{
		if (keyboard) {
			auto addKeyButton = [&](PADButton button) {
				pane.add_select_button({
				                           .key = PADGetButtonName(button),
				                           .getValue =
				                               [this, port, button] {
					                               if (mPendingKeyButton == static_cast<int>(button)) {
						                               return pending_key_label();
					                               }
					                               u32 count                     = 0;
					                               PADKeyButtonBinding* bindings = PADGetKeyButtonBindings(static_cast<u32>(port), &count);
					                               if (bindings == nullptr) {
						                               return localization::get("controller.binding.not_bound");
					                               }
					                               for (u32 i = 0; i < PAD_BUTTON_COUNT; ++i) {
						                               if (bindings[i].padButton == button) {
							                               return keyboard_key_name(bindings[i].scancode);
						                               }
					                               }
					                               return localization::get("controller.binding.not_bound");
				                               },
				                       })
				    .on_pressed([this, port, button] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort         = port;
					    mPendingBindingArmed = false;
					    mPendingKeyButton    = static_cast<int>(button);
				    });
			};

			auto addKeyAxis = [&](PADAxis axis) {
				pane.add_select_button({
				                           .key = PADGetAxisName(axis),
				                           .getValue =
				                               [this, port, axis] {
					                               if (mPendingKeyAxis == static_cast<int>(axis)) {
						                               return pending_key_label();
					                               }
					                               u32 count                   = 0;
					                               PADKeyAxisBinding* bindings = PADGetKeyAxisBindings(static_cast<u32>(port), &count);
					                               if (bindings == nullptr) {
						                               return localization::get("controller.binding.not_bound");
					                               }
					                               for (u32 i = 0; i < PAD_AXIS_COUNT; ++i) {
						                               if (bindings[i].padAxis == axis) {
							                               return keyboard_key_name(bindings[i].scancode);
						                               }
					                               }
					                               return localization::get("controller.binding.not_bound");
				                               },
				                       })
				    .on_pressed([this, port, axis] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort         = port;
					    mPendingBindingArmed = false;
					    mPendingKeyAxis      = static_cast<int>(axis);
				    });
			};

			pane.add_section(localization::get("controller.section.analog"));
			addKeyAxis(PAD_AXIS_TRIGGER_L);
			addKeyAxis(PAD_AXIS_TRIGGER_R);

			pane.add_section(localization::get("controller.section.digital"));
			addKeyButton(PAD_TRIGGER_L);
			addKeyButton(PAD_TRIGGER_R);
			break;
		}

		u32 axisCount             = 0;
		PADAxisMapping* axes      = PADGetAxisMappings(port, &axisCount);
		u32 buttonCount           = 0;
		PADButtonMapping* buttons = PADGetButtonMappings(port, &buttonCount);
		if (axes == nullptr && buttons == nullptr) {
			pane.add_text(localization::get("controller.device.none_selected"));
			break;
		}

		SDL_Gamepad* gamepad = gamepad_for_port(port);
		pane.add_section(localization::get("controller.section.analog"));
		constexpr std::array<PADAxis, 2> kTriggerAxes = { PAD_AXIS_TRIGGER_L, PAD_AXIS_TRIGGER_R };
		if (axes != nullptr) {
			for (PADAxis axis : kTriggerAxes) {
				if (axis >= axisCount) {
					continue;
				}
				PADAxisMapping& mapping = axes[axis];
				pane.add_select_button({
			                           .key = PADGetAxisName(mapping.padAxis),
				                           .getValue =
				                               [this, &mapping, gamepad] {
					                               if (mPendingAxisMapping == &mapping) {
						                               return pending_axis_label();
					                               }
					                               return native_axis_name(mapping, gamepad);
				                               },
				                       })
				    .on_pressed([this, port, &mapping] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort         = port;
					    mPendingBindingArmed = false;
					    mPendingAxisMapping  = &mapping;
				    });
			}
		}

		pane.add_section(localization::get("controller.section.digital"));
		if (buttons != nullptr) {
			for (u32 i = 0; i < buttonCount; ++i) {
				PADButtonMapping& mapping = buttons[i];
				if (mapping.padButton != PAD_TRIGGER_L && mapping.padButton != PAD_TRIGGER_R) {
					continue;
				}
				pane.add_select_button({
			                           .key = PADGetButtonName(mapping.padButton),
				                           .getValue =
				                               [this, &mapping, gamepad] {
					                               if (mPendingButtonMapping == &mapping) {
						                               return pending_button_label();
					                               }
					                               return native_button_name(gamepad, mapping.nativeButton);
				                               },
				                       })
				    .on_pressed([this, port, &mapping] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort          = port;
					    mPendingBindingArmed  = false;
					    mPendingButtonMapping = &mapping;
				    });
			}
		}

		if (PADDeadZones* deadZones = PADGetDeadZones(port)) {
			pane.add_section(localization::get("controller.section.trigger_thresholds"));
			pane.add_child<NumberButton>(NumberButton::Props {
			    .key      = localization::get("controller.trigger.left_threshold"),
			    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->leftTriggerActivationZone); },
			    .setValue =
			        [deadZones](int value) {
				        deadZones->leftTriggerActivationZone = percent_to_raw(value);
				        PADSerializeMappings();
			        },
			    .isDisabled = [deadZones] { return !deadZones->emulateTriggers; },
			    .min        = 0,
			    .max        = 100,
			    .step       = 1,
			    .suffix     = "%",
			});
			pane.add_child<NumberButton>(NumberButton::Props {
			    .key      = localization::get("controller.trigger.right_threshold"),
			    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->rightTriggerActivationZone); },
			    .setValue =
			        [deadZones](int value) {
				        deadZones->rightTriggerActivationZone = percent_to_raw(value);
				        PADSerializeMappings();
			        },
			    .isDisabled = [deadZones] { return !deadZones->emulateTriggers; },
			    .min        = 0,
			    .max        = 100,
			    .step       = 1,
			    .suffix     = "%",
			});
		}
		break;
	}
	case Page::Sticks:
	case Page::KeyboardSticks:
	{
		if (keyboard) {
			auto addKeyAxis = [&](PADAxis axis) {
				pane.add_select_button({
				                           .key = PADGetAxisDirectionLabel(axis),
				                           .getValue =
				                               [this, port, axis] {
					                               if (mPendingKeyAxis == static_cast<int>(axis)) {
						                               return pending_key_label();
					                               }
					                               u32 count                   = 0;
					                               PADKeyAxisBinding* bindings = PADGetKeyAxisBindings(static_cast<u32>(port), &count);
					                               if (bindings == nullptr) {
						                               return localization::get("controller.binding.not_bound");
					                               }
					                               for (u32 i = 0; i < PAD_AXIS_COUNT; ++i) {
						                               if (bindings[i].padAxis == axis) {
							                               return keyboard_key_name(bindings[i].scancode);
						                               }
					                               }
					                               return localization::get("controller.binding.not_bound");
				                               },
				                       })
				    .on_pressed([this, port, axis] {
					    play_menu_sound(kSoundClick);
					    cancel_pending_binding();
					    mPendingPort         = port;
					    mPendingBindingArmed = false;
					    mPendingKeyAxis      = static_cast<int>(axis);
				    });
			};

			pane.add_section(localization::get("controller.section.control_stick"));
			addKeyAxis(PAD_AXIS_LEFT_Y_POS);
			addKeyAxis(PAD_AXIS_LEFT_Y_NEG);
			addKeyAxis(PAD_AXIS_LEFT_X_NEG);
			addKeyAxis(PAD_AXIS_LEFT_X_POS);

			pane.add_section(localization::get("controller.section.c_stick"));
			addKeyAxis(PAD_AXIS_RIGHT_Y_POS);
			addKeyAxis(PAD_AXIS_RIGHT_Y_NEG);
			addKeyAxis(PAD_AXIS_RIGHT_X_NEG);
			addKeyAxis(PAD_AXIS_RIGHT_X_POS);
			break;
		}

		u32 axisCount        = 0;
		PADAxisMapping* axes = PADGetAxisMappings(port, &axisCount);
		if (axes == nullptr) {
			pane.add_text(localization::get("controller.device.none_selected"));
		}

		SDL_Gamepad* gamepad = gamepad_for_port(port);
		auto addAxis         = [&](PADAxis axis) {
            if (axes == nullptr || axis >= axisCount) {
                return;
            }
            PADAxisMapping& mapping = axes[axis];
            pane.add_select_button({
			                                   .key = PADGetAxisDirectionLabel(mapping.padAxis),
			                                   .getValue =
                                           [this, &mapping, gamepad] {
                                               if (mPendingAxisMapping == &mapping) {
                                                   return pending_axis_label();
                                               }
                                               return native_axis_name(mapping, gamepad);
                                           },
                                   })
                .on_pressed([this, port, &mapping] {
                    play_menu_sound(kSoundClick);
                    cancel_pending_binding();
                    mPendingPort         = port;
                    mPendingBindingArmed = false;
                    mPendingAxisMapping  = &mapping;
                });
		};

		auto addDeadzone = [&pane](config::ConfigVar<int>& deadzone) {
			pane.add_child<NumberButton>(NumberButton::Props {
			    .key      = localization::get("controller.deadzone"),
			    .getValue = [&deadzone] { return deadzone.value(); },
			    .setValue =
			        [&deadzone](int value) {
				        deadzone.set_value(value);
				        apply_runtime_settings(false);
				        save_settings();
			        },
			    .min    = 0,
			    .max    = 40,
			    .step   = 2,
			    .suffix = "%",
			});
		};

		pane.add_section(localization::get("controller.section.control_stick"));
		addAxis(PAD_AXIS_LEFT_Y_POS);
		addAxis(PAD_AXIS_LEFT_Y_NEG);
		addAxis(PAD_AXIS_LEFT_X_NEG);
		addAxis(PAD_AXIS_LEFT_X_POS);
		addDeadzone(settings().input.stickDeadzone);

		pane.add_section(localization::get("controller.section.c_stick"));
		addAxis(PAD_AXIS_RIGHT_Y_POS);
		addAxis(PAD_AXIS_RIGHT_Y_NEG);
		addAxis(PAD_AXIS_RIGHT_X_NEG);
		addAxis(PAD_AXIS_RIGHT_X_POS);
		addDeadzone(settings().input.cstickDeadzone);
		break;
	}
	case Page::Rumble:
	{
		if (PADCanForceDeviceRumble(static_cast<u32>(port))) {
			pane.add_child<BoolButton>(BoolButton::Props {
			    .key      = localization::get("controller.rumble.use_device_haptics"),
			    .getValue = [port] { return PADGetForceDeviceRumble(static_cast<u32>(port)); },
			    .setValue =
			        [port](bool value) {
				        PADSetForceDeviceRumble(static_cast<u32>(port), value ? TRUE : FALSE);
				        PADSerializeMappings();
			        },
			    .isDisabled = [this] { return mRumbleTestActive; },
			});
			pane.add_text(localization::get("controller.rumble.use_device_haptics_help"));
		}
		auto& rumbleTest = pane.add_select_button({
		    .key = localization::get("controller.rumble.test"),
		    .getValue
		    = [this, port] { return (mRumbleTestActive && mRumbleTestPort == port)
		                                 ? localization::get("common.stop")
		                                 : localization::get("common.start"); },
		});
		rumbleTest.on_pressed([this, port] {
			if (!PADSupportsRumbleIntensity(static_cast<u32>(port))) {
				return;
			}
			play_menu_sound(kSoundItemChange);
			if (mRumbleTestActive && mRumbleTestPort == port) {
				PADControlMotor(port, PAD_MOTOR_STOP_HARD);
				mRumbleTestActive = false;
				mRumbleTestPort   = -1;
			} else {
				if (mRumbleTestActive) {
					PADControlMotor(mRumbleTestPort, PAD_MOTOR_STOP_HARD);
				}
				PADControlMotor(port, PAD_MOTOR_RUMBLE);
				mRumbleTestActive = true;
				mRumbleTestPort   = port;
			}
		});
		pane.add_child<NumberButton>(NumberButton::Props {
		    .key = localization::get("controller.rumble.low_frequency"),
		    .getValue =
		        [port] {
			        u16 low  = 0;
			        u16 high = 0;
			        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
			        return rumble_raw_to_percent(low);
		        },
		    .setValue =
		        [port](int value) {
			        u16 low  = 0;
			        u16 high = 0;
			        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
			        PADSetRumbleIntensity(static_cast<u32>(port), percent_to_raw(value), high);
			        PADSerializeMappings();
		        },
		    .isDisabled = [this] { return mRumbleTestActive; },
		    .min        = 0,
		    .max        = 100,
		    .step       = 1,
		    .suffix     = "%",
		});
		pane.add_child<NumberButton>(NumberButton::Props {
		    .key = localization::get("controller.rumble.high_frequency"),
		    .getValue =
		        [port] {
			        u16 low  = 0;
			        u16 high = 0;
			        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
			        return rumble_raw_to_percent(high);
		        },
		    .setValue =
		        [port](int value) {
			        u16 low  = 0;
			        u16 high = 0;
			        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
			        PADSetRumbleIntensity(static_cast<u32>(port), low, percent_to_raw(value));
			        PADSerializeMappings();
		        },
		    .isDisabled = [this] { return mRumbleTestActive; },
		    .min        = 0,
		    .max        = 100,
		    .step       = 1,
		    .suffix     = "%",
		});
		pane.add_text(localization::get("controller.rumble.help"));
		break;
	}
	}
}

void ControllerConfigWindow::refresh_controller_page()
{
	if (!visible() || mRightPane == nullptr || is_keyboard_page(mPage)) {
		return;
	}
	if (mPendingButtonMapping != nullptr || mPendingAxisMapping != nullptr) {
		cancel_pending_binding();
	}
	stop_rumble_test();
	render_page(*mRightPane, mActivePort, mPage);
}

void ControllerConfigWindow::poll_pending_binding()
{
	if (mSuppressNavigationUntilNeutral && input_neutral(mSuppressNavigationPort)) {
		mSuppressNavigationUntilNeutral = false;
		mSuppressNavigationPort         = -1;
	}

	if (!capture_active()) {
		return;
	}

	if (keyboard_escape_pressed()) {
		unmap_pending_binding();
		return;
	}

	if (!mPendingBindingArmed) {
		if (pending_input_neutral()) {
			mPendingBindingArmed = true;
		}
		return;
	}

	if (mPendingKeyButton >= 0 || mPendingKeyAxis >= 0) {
		const s32 scancode = keyboard_key_pressed();
		if (scancode != PAD_KEY_INVALID) {
			if (mPendingKeyButton >= 0) {
				PADSetKeyButtonBinding(static_cast<u32>(mPendingPort), { scancode, static_cast<PADButton>(mPendingKeyButton) });
			} else {
				PADSetKeyAxisBinding(static_cast<u32>(mPendingPort), { scancode, static_cast<PADAxis>(mPendingKeyAxis), 0 });
			}
			finish_pending_key_binding();
		}
		return;
	}

	if (mPendingButtonMapping != nullptr) {
		const s32 nativeButton = PADGetNativeButtonPressed(mPendingPort);
		if (nativeButton != -1) {
			const int completedPort = mPendingPort;
			if (mPendingButtonMapping->nativeButton == static_cast<u32>(nativeButton)
			    && (mPendingButtonMapping->padButton != PAD_BUTTON_A && mPendingButtonMapping->padButton != PAD_BUTTON_B)) {
				unmap_pending_binding();
				return;
			}
			mPendingButtonMapping->nativeButton = static_cast<u32>(nativeButton);
			finish_pending_binding(completedPort);
		}
		return;
	}

	if (mPendingAxisMapping != nullptr) {
		const PADSignedNativeAxis nativeAxis = PADGetNativeAxisPulled(mPendingPort);
		if (nativeAxis.nativeAxis != -1) {
			const int completedPort = mPendingPort;
			if (mPendingAxisMapping->nativeAxis.nativeAxis == nativeAxis.nativeAxis) {
				unmap_pending_binding();
				return;
			}
			mPendingAxisMapping->nativeAxis   = nativeAxis;
			mPendingAxisMapping->nativeButton = -1;
			finish_pending_binding(completedPort);
			return;
		}

		const s32 nativeButton = PADGetNativeButtonPressed(mPendingPort);
		if (nativeButton != -1) {
			const int completedPort           = mPendingPort;
			mPendingAxisMapping->nativeAxis   = { -1, AXIS_SIGN_POSITIVE };
			mPendingAxisMapping->nativeButton = nativeButton;
			finish_pending_binding(completedPort);
		}
		return;
	}
}

void ControllerConfigWindow::finish_pending_binding(int completedPort)
{
	play_menu_sound(kSoundBindingChanged);
	mPendingButtonMapping           = nullptr;
	mPendingAxisMapping             = nullptr;
	mPendingPort                    = -1;
	mPendingBindingArmed            = false;
	mSuppressNavigationUntilNeutral = true;
	mSuppressNavigationPort         = completedPort;
	PADSerializeMappings();
}

void ControllerConfigWindow::unmap_pending_binding()
{
	if (mPendingButtonMapping == nullptr && mPendingAxisMapping == nullptr && mPendingKeyButton < 0 && mPendingKeyAxis < 0) {
		return;
	}

	const int completedPort = mPendingPort;
	if (mPendingButtonMapping != nullptr) {
		mPendingButtonMapping->nativeButton = PAD_NATIVE_BUTTON_INVALID;
		finish_pending_binding(completedPort);
	} else if (mPendingAxisMapping != nullptr) {
		mPendingAxisMapping->nativeAxis   = { -1, AXIS_SIGN_POSITIVE };
		mPendingAxisMapping->nativeButton = -1;
		finish_pending_binding(completedPort);
	} else if (mPendingKeyButton >= 0) {
		PADSetKeyButtonBinding(static_cast<u32>(completedPort), { PAD_KEY_INVALID, static_cast<PADButton>(mPendingKeyButton) });
		finish_pending_key_binding();
	} else if (mPendingKeyAxis >= 0) {
		PADSetKeyAxisBinding(static_cast<u32>(completedPort), { PAD_KEY_INVALID, static_cast<PADAxis>(mPendingKeyAxis), 0 });
		finish_pending_key_binding();
	}
}

bool ControllerConfigWindow::capture_active() const
{
	return mPendingButtonMapping != nullptr || mPendingAxisMapping != nullptr || mPendingKeyButton >= 0 || mPendingKeyAxis >= 0;
}

bool ControllerConfigWindow::pending_input_neutral() const
{
	if (mPendingKeyButton >= 0 || mPendingKeyAxis >= 0) {
		return keyboard_neutral();
	}
	return input_neutral(mPendingPort);
}

Rml::String ControllerConfigWindow::pending_button_label() const
{
	return mPendingBindingArmed ? localization::get("controller.binding.press_key_or_button")
	                            : localization::get("controller.binding.waiting");
}

Rml::String ControllerConfigWindow::pending_axis_label() const
{
	return mPendingBindingArmed ? localization::get("controller.binding.move_axis_or_press")
	                            : localization::get("controller.binding.waiting");
}

void ControllerConfigWindow::cancel_pending_binding()
{
	if (mPendingButtonMapping == nullptr && mPendingAxisMapping == nullptr && !mSuppressNavigationUntilNeutral && mPendingKeyButton < 0
	    && mPendingKeyAxis < 0) {
		return;
	}
	mPendingButtonMapping           = nullptr;
	mPendingAxisMapping             = nullptr;
	mPendingKeyButton               = -1;
	mPendingKeyAxis                 = -1;
	mPendingPort                    = -1;
	mPendingBindingArmed            = false;
	mSuppressNavigationUntilNeutral = false;
	mSuppressNavigationPort         = -1;
}

void ControllerConfigWindow::finish_pending_key_binding()
{
	mPendingKeyButton    = -1;
	mPendingKeyAxis      = -1;
	mPendingPort         = -1;
	mPendingBindingArmed = false;
	PADSerializeMappings();
}

Rml::String ControllerConfigWindow::pending_key_label() const
{
	return mPendingBindingArmed ? localization::get("controller.binding.press_key_or_mouse")
	                            : localization::get("controller.binding.waiting");
}

void ControllerConfigWindow::stop_rumble_test()
{
	if (!mRumbleTestActive) {
		return;
	}
	if (mRumbleTestPort >= PAD_CHAN0 && mRumbleTestPort < PAD_CHANMAX) {
		PADControlMotor(mRumbleTestPort, PAD_MOTOR_STOP_HARD);
	}
	mRumbleTestActive = false;
	mRumbleTestPort   = -1;
}

Rml::String native_button_name(SDL_Gamepad* gamepad, u32 buttonUntyped)
{
	if (buttonUntyped == PAD_NATIVE_BUTTON_INVALID) {
		return localization::get("controller.binding.not_bound");
	}

	auto button = static_cast<SDL_GamepadButton>(buttonUntyped);
	if (gamepad != nullptr) {
		switch (SDL_GetGamepadButtonLabel(gamepad, button)) {
		case SDL_GAMEPAD_BUTTON_LABEL_A:
			return "A";
		case SDL_GAMEPAD_BUTTON_LABEL_B:
			return "B";
		case SDL_GAMEPAD_BUTTON_LABEL_X:
			return "X";
		case SDL_GAMEPAD_BUTTON_LABEL_Y:
			return "Y";
		case SDL_GAMEPAD_BUTTON_LABEL_CROSS:
			return localization::get("controller.input.cross");
		case SDL_GAMEPAD_BUTTON_LABEL_CIRCLE:
			return localization::get("controller.input.circle");
		case SDL_GAMEPAD_BUTTON_LABEL_TRIANGLE:
			return localization::get("controller.input.triangle");
		case SDL_GAMEPAD_BUTTON_LABEL_SQUARE:
			return localization::get("controller.input.square");
		default:
			break;
		}
	}

	const SDL_GamepadType type = gamepad != nullptr ? SDL_GetGamepadType(gamepad) : SDL_GAMEPAD_TYPE_UNKNOWN;
	for (const auto& buttonNames : kGamepadButtonNames) {
		if (buttonNames.button != button) {
			continue;
		}

		for (const auto& name : buttonNames.names) {
			if (name.type == type) {
				return name.translatable ? localization::get(name.name) : name.name;
			}
		}
	}

	switch (button) {
	case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
		return localization::get("controller.input.d_pad_left");
	case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
		return localization::get("controller.input.d_pad_right");
	case SDL_GAMEPAD_BUTTON_DPAD_UP:
		return localization::get("controller.input.d_pad_up");
	case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
		return localization::get("controller.input.d_pad_down");
	default:
		break;
	}

	if (const char* name = PADGetNativeButtonName(buttonUntyped)) {
		return name;
	}
	return localization::get("common.unknown");
}

} // namespace acgc::ui
