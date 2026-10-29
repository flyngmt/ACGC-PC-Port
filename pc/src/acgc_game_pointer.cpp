#include "acgc/game_pointer.hpp"
#include <aurora/pad.hpp>
#include <algorithm>
#include <cmath>

namespace acgc::input {
namespace {
namespace routed = aurora::input;
using Event = routed::InputEvent;

constexpr int kPriority = routed::kGameLayerPriority + 2;
// The game's STICK_MIN, measured after PADClamp. A stationary deflection cannot
// steal ownership again after pointer movement establishes a new reference.
constexpr float kStickThresholdSquared = 98.f;
constexpr uint64_t kHandTimeoutNs = 5'000'000'000;

uint32_t button_mask(uint8_t button) {
    return button >= 1 && button <= 5 ? 1u << (button - 1) : 0;
}
} // namespace

GamePointer::~GamePointer() {
    shutdown();
}

void GamePointer::initialize() {
    shutdown();
    mLayer = routed::register_layer({
        .label = "acgc.game-pointer",
        .priority = kPriority,
        .onEvent = event,
        .pointerMode = pointer_mode,
        .userdata = this,
    });
    mRunning = true;
    sync_bindings();
}

void GamePointer::shutdown() {
    if (mLayer) {
        routed::unregister_layer(mLayer);
    }
    mLayer = 0;
    mRunning = false;
    cancel();
    mBindings.reset();
    (void)mPad.reset();
    mFrame = { .x = -1.f, .y = -1.f };
    mHasTick = false;
}

void GamePointer::set_running(bool running) {
    if (mRunning == running) {
        return;
    }
    mRunning = running;
    cancel();
    if (mLayer) {
        routed::set_layer_enabled(mLayer, running);
    }
}

void GamePointer::set_viewport(PointerViewport viewport) {
    if (mViewport == viewport) {
        return;
    }
    mViewport = viewport;
    cancel();
}

void GamePointer::cancel() {
    mSuppressed |= mHeld;
    mHeld = mPressed = mCButtons = 0;
    mScrollX = mScrollY = mScrollRemainder = 0;
    mInside = mMoved = mActivity = mKeyboardActivity = mPadActivity = false;
    mX = mY = -1.f;
    mOwner = GAME_POINTER_NONE;
    mCancelled = true;
}

void GamePointer::keyboard_activity() {
    mKeyboardActivity = true;
}

routed::PointerMode GamePointer::pointer_mode(void* userdata) {
    return static_cast<GamePointer*>(userdata)->mRunning ? routed::PointerMode::Hidden : routed::PointerMode::None;
}

routed::EventResult GamePointer::event(const Event& input, void* userdata) {
    static_cast<GamePointer*>(userdata)->process(input);
    return routed::EventResult::Pass;
}

void GamePointer::sync_bindings() {
    const auto bindings = aurora::pad::binding_set(0);
    if (bindings == mBindings) {
        return;
    }
    mBindings = bindings;
    (void)mPad.set_bindings(bindings);
    uint32_t reserved = 0;
    const auto reserve = [&](const aurora::binding::PhysicalInput& physical) {
        if (const auto* mouse = physical.control.get_if<aurora::binding::PhysicalInput::MouseButton>()) {
            reserved |= button_mask(mouse->button);
        }
    };
    if (bindings) {
        for (const auto& binding : bindings->bindings) {
            reserve(binding.input);
            for (const auto& held : binding.held) {
                reserve(held.input);
            }
        }
    }
    mSuppressed |= mHeld & (reserved ^ mReserved);
    mReserved = reserved;
    mPressed &= ~reserved;
}

void GamePointer::position(SDL_FPoint point) {
    const auto& v = mViewport;
    const bool wasInside = mInside;
    mInside = false;
    mX = mY = -1.f;
    if (v.width <= 0 || v.height <= 0 || v.pixelWidth <= 0 || v.pixelHeight <= 0 || v.renderWidth <= 0 ||
        v.renderHeight <= 0 || v.aspect <= 0.f) {
        return;
    }
    int width = v.pixelWidth;
    int height = std::min(v.pixelHeight,
                          std::max(1, static_cast<int>(std::lround(double(width) * v.renderHeight / v.renderWidth))));
    if (height == v.pixelHeight) {
        width = std::min(v.pixelWidth,
                         std::max(1, static_cast<int>(std::lround(double(height) * v.renderWidth / v.renderHeight))));
    }
    const int left = (v.pixelWidth - width) / 2, top = (v.pixelHeight - height) / 2;
    const float x = point.x * v.pixelWidth / v.width, y = point.y * v.pixelHeight / v.height;
    const float nativeX = (x - left) * 640.f / width, nativeY = (y - top) * 480.f / height;
    mX = (nativeX - (1.f - v.aspect) * 320.f) / (2.f * v.aspect);
    mY = nativeY * .5f;
    mInside = x >= left && x < left + width && y >= top && y < top + height;
    if (!mInside) {
        mCancelled = mCancelled || wasInside;
        mSuppressed |= mHeld;
        mPressed = 0;
        mScrollX = mScrollY = mScrollRemainder = 0;
        mOwner = GAME_POINTER_NONE;
    }
}

void GamePointer::activity() {
    if (mInside) {
        mActivity = true;
    }
}

void GamePointer::process(const Event& input) {
    sync_bindings();
    if (input.payload.is<Event::Cancelled>()) {
        (void)mPad.process(input);
        cancel();
        return;
    }
    if (!mRunning) {
        return;
    }
    if (input.source.kind == routed::InputSource::Kind::Keyboard) {
        if (const auto* key = input.payload.get_if<Event::KeyChanged>(); key && key->pressed) {
            keyboard_activity();
        }
    }
    if (input.source.kind == routed::InputSource::Kind::Keyboard ||
        input.source.kind == routed::InputSource::Kind::Controller) {
        for (const auto& change : mPad.process(input).changes) {
            const auto* control = aurora::binding::describe_control(change.control);
            if (change.reason == aurora::binding::ControlChange::Reason::Input && control &&
                control->kind == aurora::binding::ControlKind::Button && change.value >= .5f &&
                change.previousValue < .5f) {
                mPadActivity = true;
            }
        }
    }
    if (input.source.kind != routed::InputSource::Kind::Mouse) {
        return;
    }
    if (const auto* pointer = input.payload.get_if<Event::PointerChanged>()) {
        using Phase = Event::PointerChanged::Phase;
        if (pointer->phase == Phase::Cancel) {
            cancel();
            return;
        }
        const float oldX = mX, oldY = mY;
        position(pointer->position);
        const auto mask = button_mask(pointer->button);
        if (pointer->phase == Phase::Move) {
            if (mInside && (oldX != mX || oldY != mY || pointer->delta.x != 0 || pointer->delta.y != 0)) {
                mMoved = true;
                activity();
            }
        } else if (pointer->phase == Phase::Down) {
            mHeld |= mask;
            if (!mInside || (mReserved & mask)) {
                mSuppressed |= mask;
            } else {
                mSuppressed &= ~mask;
                mPressed |= mask;
                activity();
            }
        } else if (pointer->phase == Phase::Up) {
            mHeld &= ~mask;
            mSuppressed &= ~mask;
        }
    } else if (const auto* scroll = input.payload.get_if<Event::Scroll>()) {
        position(scroll->position);
        if (mInside) {
            mScrollX += scroll->delta.x;
            mScrollY += scroll->delta.y;
            activity();
        }
    }
}

void GamePointer::begin_tick(uint32_t tick, uint64_t nowNs) {
    if (mHasTick && tick == mFrame.tick) {
        return;
    }
    mHasTick = true;
    sync_bindings();
    // Use the same clamping and deflection threshold as the game, without a
    // second PADRead or polling physical devices outside the router.
    const auto& controls = aurora::pad::controls();
    PADStatus pads[PAD_MAX_CONTROLLERS]{};
    pads[0].stickX = static_cast<s8>(std::lround(mPad.value(controls.leftX) * 127.f));
    pads[0].stickY = static_cast<s8>(std::lround(mPad.value(controls.leftY) * 127.f));
    pads[0].substickX = static_cast<s8>(std::lround(mPad.value(controls.rightX) * 127.f));
    pads[0].substickY = static_cast<s8>(std::lround(mPad.value(controls.rightY) * 127.f));
    PADClamp(pads);
    const uint32_t cButtons = (pads[0].substickX >= 29 ? 1u : 0u) | (pads[0].substickX <= -29 ? 2u : 0u) |
                              (pads[0].substickY >= 29 ? 4u : 0u) | (pads[0].substickY <= -29 ? 8u : 0u);
    mPadActivity = mPadActivity || (cButtons & ~mCButtons) != 0;
    mCButtons = cButtons;
    const float x = pads[0].stickX, y = pads[0].stickY;
    const bool deflected = x * x + y * y > kStickThresholdSquared;
    if (!deflected) {
        mReferenceX = mReferenceY = 0;
    } else if (mActivity) {
        mReferenceX = x;
        mReferenceY = y;
    }
    const float dx = x - mReferenceX, dy = y - mReferenceY;
    const bool takeover = mPadActivity || (deflected && dx * dx + dy * dy > kStickThresholdSquared);
    if (takeover || mKeyboardActivity) {
        mOwner = mKeyboardActivity ? GAME_POINTER_KEYBOARD : GAME_POINTER_PAD;
        mSuppressed |= mHeld;
        mPressed = 0;
        mScrollX = mScrollY = mScrollRemainder = 0;
        mActivity = false;
    } else if (mActivity) {
        mOwner = GAME_POINTER_MOUSE;
    }
    const uint32_t held = mInside ? mHeld & ~(mSuppressed | mReserved) : 0;
    if (mActivity || (mOwner == GAME_POINTER_MOUSE && held)) {
        mLastActivity = nowNs;
    }
    const bool visible = mRunning && mInside && mOwner == GAME_POINTER_MOUSE && nowNs - mLastActivity < kHandTimeoutNs;
    mScrollRemainder += mScrollY;
    const int steps = static_cast<int>(mScrollRemainder);
    mScrollRemainder -= steps;
    mFrame = {
        .tick = tick,
        .x = mX,
        .y = mY,
        .held = held,
        .pressed = mInside ? mPressed & ~mReserved : 0,
        .scroll_x = mScrollX,
        .scroll_y = mScrollY,
        .scroll_steps_y = steps,
        .inside = mInside,
        .moved = mMoved,
        .active = mActivity,
        .visible = visible,
        .cancelled = mCancelled,
        .owner = mOwner,
    };
    mPressed = 0;
    mScrollX = mScrollY = 0;
    mMoved = mActivity = mPadActivity = mKeyboardActivity = mCancelled = false;
}
} // namespace acgc::input
