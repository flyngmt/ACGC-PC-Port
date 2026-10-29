#pragma once

#include "game_pointer.h"

#include <aurora/binding.hpp>
#include <aurora/input.hpp>
#include <memory>
#include <SDL3/SDL_events.h>

namespace acgc::input {
struct PointerViewport {
    int width = 0;
    int height = 0;
    int pixelWidth = 0;
    int pixelHeight = 0;
    int renderWidth = 0;
    int renderHeight = 0;
    float aspect = 1.f;

    bool operator==(const PointerViewport&) const = default;
};

class GamePointer {
  public:
    GamePointer() = default;
    ~GamePointer();
    GamePointer(const GamePointer&) = delete;
    GamePointer& operator=(const GamePointer&) = delete;

    void initialize();
    void shutdown();
    void set_viewport(PointerViewport viewport);
    void set_running(bool running);
    void cancel();
    void keyboard_activity();
    void begin_tick(uint32_t tick, uint64_t nowNs);

    [[nodiscard]] const GamePointerFrame& frame() const {
        return mFrame;
    }

  private:
    void process(const aurora::input::InputEvent&);
    void sync_bindings();
    void position(SDL_FPoint point);
    void activity();

    aurora::input::LayerId mLayer = 0;
    PointerViewport mViewport;
    GamePointerFrame mFrame{ .x = -1.f, .y = -1.f };
    aurora::binding::State mPad;
    std::shared_ptr<const aurora::binding::BindingSet> mBindings;
    uint32_t mCButtons = 0;
    uint32_t mReserved = 0;
    uint32_t mHeld = 0;
    uint32_t mPressed = 0;
    uint32_t mSuppressed = 0;
    float mX = -1.f;
    float mY = -1.f;
    float mScrollX = 0;
    float mScrollY = 0;
    float mScrollRemainder = 0;
    float mReferenceX = 0;
    float mReferenceY = 0;
    uint64_t mLastActivity = 0;
    GamePointerOwner mOwner = GAME_POINTER_NONE;
    bool mRunning = false;
    bool mInside = false;
    bool mMoved = false;
    bool mActivity = false;
    bool mKeyboardActivity = false;
    bool mPadActivity = false;
    bool mCancelled = false;
    bool mHasTick = false;

    static aurora::input::EventResult event(const aurora::input::InputEvent&, void*);
    static aurora::input::PointerMode pointer_mode(void*);
};

GamePointer& game_pointer();

void pointer_window_event(const SDL_Event& event);
void update_pointer_viewport();
} // namespace acgc::input
