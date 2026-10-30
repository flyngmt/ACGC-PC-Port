#include "acgc/game_editor.hpp"
#include "acgc/game_text.hpp"
#include <algorithm>
#include <cmath>

namespace acgc::input {
namespace routed = aurora::input;
using Event = routed::InputEvent;

GameEditor::~GameEditor() {
    shutdown();
}

void GameEditor::initialize(std::function<void()> keyboardActivity) {
    shutdown();
    mKeyboardActivity = std::move(keyboardActivity);
    mLayer = routed::register_layer({
        .label = "acgc.game-editor",
        .priority = 50,
        .onEvent = event,
        .capturesSource = captures,
        .userdata = this,
    });
}

void GameEditor::shutdown() {
    mAvailable = false;
    stop();
    if (mLayer) {
        routed::unregister_layer(mLayer);
    }
    mLayer = 0;
    mOptions = {};
    mKeyboardActivity = {};
}

void GameEditor::clear() {
    mQueue.clear();
    mComposition = {};
}

void GameEditor::stop() {
    mTyping = false;
    mSession.reset();
    clear();
    routed::reconcile();
}

void GameEditor::update_options(routed::TextInputOptions options) {
    if (options == mOptions) {
        return;
    }
    mOptions = std::move(options);
    if (mSession.id()) {
        mSession.update(mOptions);
    }
}

void GameEditor::set_available(bool available, bool multiline) {
    if (!available) {
        mAvailable = false;
        stop();
        mOptions.area.reset();
        return;
    }
    if (mOptions.multiline != multiline) {
        clear(); // A field switch cannot inherit queued commands.
    }
    const bool opened = !mAvailable;
    mAvailable = true;
    auto options = mOptions;
    options.multiline = multiline;
    update_options(std::move(options));
    if (opened) {
        set_typing(true);
    }
}

void GameEditor::set_typing(bool typing) {
    if (!mAvailable || typing == mTyping) {
        return;
    }
    if (typing) {
        clear();
        mTyping = true;
        mSession = routed::TextInputSession(mLayer, mOptions);
    } else {
        stop();
    }
}

void GameEditor::set_area(std::optional<routed::TextInputArea> area) {
    auto options = mOptions;
    options.area = std::move(area);
    update_options(std::move(options));
}

GameEditorState GameEditor::state() const {
    if (!mTyping) {
        return GAME_EDITOR_OFF;
    }
    switch (mSession.state()) {
        case routed::TextInputState::Pending:
            return GAME_EDITOR_PENDING;
        case routed::TextInputState::Suspended:
            return GAME_EDITOR_SUSPENDED;
        case routed::TextInputState::Active:
            return GAME_EDITOR_ACTIVE;
        case routed::TextInputState::Failed:
            return GAME_EDITOR_FAILED;
        default:
            return GAME_EDITOR_OFF;
    }
}

size_t GameEditor::drain(std::span<GameEditorEvent> output) {
    if (state() != GAME_EDITOR_ACTIVE) {
        return 0;
    }
    const auto count = std::min(output.size(), mQueue.size());
    for (size_t i = 0; i < count; ++i) {
        output[i] = mQueue.front();
        mQueue.pop_front();
    }
    return count;
}

bool GameEditor::captures(const routed::InputSource& source, void* userdata) {
    const auto& self = *static_cast<GameEditor*>(userdata);
    using Kind = routed::InputSource::Kind;
    return self.mAvailable && self.mTyping && (source.kind == Kind::Keyboard || source.kind == Kind::Controller);
}

routed::EventResult GameEditor::event(const Event& input, void* userdata) {
    return static_cast<GameEditor*>(userdata)->process(input);
}

routed::EventResult GameEditor::process(const Event& input) {
    if (const auto* change = input.payload.get_if<Event::TextInputStateChanged>()) {
        if (change->session == mSession.id() && change->state != routed::TextInputState::Active) {
            clear();
        }
        return routed::EventResult::Pass;
    }
    if (input.payload.is<Event::Cancelled>()) {
        clear();
        return routed::EventResult::Pass;
    }
    if (!mAvailable) {
        return routed::EventResult::Pass;
    }
    if (mTyping && input.source.kind == routed::InputSource::Kind::Controller) {
        const auto* button = input.payload.get_if<Event::ButtonChanged>();
        const auto* axis = input.payload.get_if<Event::AxisChanged>();
        if ((button && button->pressed) || (axis && std::abs(axis->value) >= 0.5f)) {
            stop();
        }
        return routed::EventResult::Pass;
    }
    if (const auto* key = input.payload.get_if<Event::KeyChanged>(); key && key->pressed) {
        if (key->keycode == SDLK_TAB && !key->repeat) {
            set_typing(!mTyping);
            if (mKeyboardActivity) {
                mKeyboardActivity();
            }
            return routed::EventResult::Consume;
        }
        if (state() != GAME_EDITOR_ACTIVE) {
            return routed::EventResult::Pass;
        }
        if (mKeyboardActivity) {
            mKeyboardActivity();
        }
        // Arrow/backspace repeats are commands; Tab repeat never toggles the mode.
        // During composition these keys belong to the IME, not the game editor.
        if (!mComposition.text.empty()) {
            return routed::EventResult::Consume;
        }
        switch (key->keycode) {
            case SDLK_BACKSPACE:
                mQueue.push_back({ GAME_EDITOR_BACKSPACE, {} });
                break;
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
                mQueue.push_back({ GAME_EDITOR_SUBMIT, {} });
                break;
            case SDLK_LEFT:
                mQueue.push_back({ GAME_EDITOR_MOVE_CURSOR, { .direction = GAME_EDITOR_LEFT } });
                break;
            case SDLK_RIGHT:
                mQueue.push_back({ GAME_EDITOR_MOVE_CURSOR, { .direction = GAME_EDITOR_RIGHT } });
                break;
            case SDLK_UP:
                mQueue.push_back({ GAME_EDITOR_MOVE_CURSOR, { .direction = GAME_EDITOR_UP } });
                break;
            case SDLK_DOWN:
                mQueue.push_back({ GAME_EDITOR_MOVE_CURSOR, { .direction = GAME_EDITOR_DOWN } });
                break;
            default:
                break;
        }
        return routed::EventResult::Consume;
    }
    if (state() != GAME_EDITOR_ACTIVE) {
        return routed::EventResult::Pass;
    }
    if (const auto* editing = input.payload.get_if<Event::TextEditing>()) {
        mComposition = *editing;
        return routed::EventResult::Consume;
    }
    if (const auto* committed = input.payload.get_if<Event::TextInput>()) {
        mComposition = {};
        if (mKeyboardActivity) {
            mKeyboardActivity();
        }
        std::string_view text = committed->text;
        while (!text.empty()) {
            size_t consumed = 0;
            const int code = acgc::text::decode(text, consumed);
            if (code >= 0) {
                mQueue.push_back({ GAME_EDITOR_INSERT_CHARACTER, { .character = static_cast<uint8_t>(code) } });
            }
            text.remove_prefix(consumed);
        }
        return routed::EventResult::Consume;
    }
    return routed::EventResult::Pass;
}

} // namespace acgc::input
