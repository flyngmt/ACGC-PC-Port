#pragma once

#include <aurora/input.hpp>
#include <borealis/ui/document.hpp>

#include <SDL3/SDL_touch.h>

#include <array>
#include <chrono>
#include <cstddef>

namespace acgc::ui {

class TouchControls final : public borealis::ui::Document {
public:
    static constexpr size_t kButtonCount = 12;

    TouchControls();
    ~TouchControls() override;

    void show() override;
    void hide(bool close) override;
    void update() override;
    bool claims_pointer(Rml::Element* element) const override;

private:
    using Clock = std::chrono::steady_clock;

    struct StickTouch {
        SDL_FingerID id = 0;
        Rml::Vector2f start;
        Rml::Vector2f current;
        Clock::time_point pressedAt{};
        bool active = false;
        bool releasePending = false;
    };

    struct ButtonTouch {
        SDL_FingerID id = 0;
        Clock::time_point pressedAt{};
        bool active = false;
        bool releasePending = false;
    };

    void press_button(size_t index, SDL_FingerID id);
    bool release_button(SDL_FingerID id);
    void handle_touch_down(Rml::Event& event);
    void handle_touch_move(Rml::Event& event);
    void handle_touch_up(Rml::Event& event);
    void clear_input();
    void sync_visibility();
    void sync_safe_area();
    void sync_buttons();
    void sync_stick();
    void sync_c_stick();
    void sync_pad();
    void observe_input(const aurora::input::InputEvent& event);

    static aurora::input::EventResult on_input(const aurora::input::InputEvent& event, void* userdata);

    Rml::Element* mArea = nullptr;
    Rml::Element* mStickElement = nullptr;
    Rml::Element* mKnob = nullptr;
    Rml::Element* mCStickElement = nullptr;
    Rml::Element* mCKnob = nullptr;
    Rml::Element* mDpad = nullptr;
    Rml::Element* mMenuButton = nullptr;
    std::array<Rml::Element*, kButtonCount> mButtons{};
    std::array<ButtonTouch, kButtonCount> mTouches{};
    StickTouch mStick;
    StickTouch mCStick;
    borealis::ui::Insets mInsets;
    aurora::input::LayerId mLayer = aurora::input::kInvalidLayerId;
    SDL_FingerID mMenuFinger = 0;
    bool mMenuPressed = false;
    bool mDeviceInput = false;
    bool mShown = false;
    bool mPadActive = false;
};

} // namespace acgc::ui
