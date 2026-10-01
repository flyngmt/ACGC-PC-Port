#pragma once

#include "window.hpp"
#include <SDL3/SDL_joystick.h>
#include <dolphin/pad.h>

namespace acgc::ui {

class ControllerConfigWindow : public Window {
public:
	ControllerConfigWindow();

	void update() override;
	void hide(bool close) override;

private:
	enum class Page {
		Controller,
		Buttons,
		Triggers,
		Sticks,
		Rumble,
		KeyboardButtons,
		KeyboardTriggers,
		KeyboardSticks,
	};

	static bool is_keyboard_page(Page page);
	void build_tab(Rml::Element* content);
	void render_page(class Pane& pane, int port, Page page);
	void refresh_controller_page();
	void poll_pending_binding();
	void finish_pending_binding(int completedPort);
	void unmap_pending_binding();
	bool capture_active() const;
	bool pending_input_neutral() const;
	Rml::String pending_button_label() const;
	Rml::String pending_axis_label() const;
	void cancel_pending_binding();
	void finish_pending_key_binding();
	Rml::String pending_key_label() const;
	void stop_rumble_test();

	Page mPage                              = Page::Controller;
	Pane* mRightPane                        = nullptr;
	int mActivePort                         = 0;
	SDL_JoystickID mPortController          = 0;
	int mPendingPort                        = -1;
	bool mPendingBindingArmed               = false;
	bool mSuppressNavigationUntilNeutral    = false;
	int mSuppressNavigationPort             = -1;
	PADButtonMapping* mPendingButtonMapping = nullptr;
	PADAxisMapping* mPendingAxisMapping     = nullptr;
	int mPendingKeyButton                   = -1;
	int mPendingKeyAxis                     = -1;
	bool mRumbleTestActive                  = false;
	int mRumbleTestPort                     = -1;
};

Rml::String native_button_name(SDL_Gamepad* gamepad, u32 buttonUntyped);

} // namespace acgc::ui
