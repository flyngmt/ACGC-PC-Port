#pragma once

#include "game_editor.h"

#include <aurora/input.hpp>
#include <deque>
#include <functional>
#include <span>

namespace acgc::input {

class GameEditor {
  public:
    ~GameEditor();
    GameEditor() = default;
    GameEditor(const GameEditor&) = delete;
    GameEditor& operator=(const GameEditor&) = delete;

    void initialize(std::function<void()> keyboardActivity = {});
    void shutdown();
    void set_available(bool available, bool multiline = false);
    void set_typing(bool typing);
    void set_area(std::optional<aurora::input::TextInputArea> area);
    size_t drain(std::span<GameEditorEvent> output);

    [[nodiscard]] bool available() const {
        return mAvailable;
    }
    [[nodiscard]] GameEditorState state() const;
    [[nodiscard]] const aurora::input::InputEvent::TextEditing& composition() const {
        return mComposition;
    }

  private:
    aurora::input::EventResult process(const aurora::input::InputEvent&);
    void clear();
    void stop();
    void update_options(aurora::input::TextInputOptions options);

    aurora::input::LayerId mLayer = 0;
    aurora::input::TextInputSession mSession;
    aurora::input::TextInputOptions mOptions;
    aurora::input::InputEvent::TextEditing mComposition;
    std::deque<GameEditorEvent> mQueue;
    std::function<void()> mKeyboardActivity;
    bool mAvailable = false;
    bool mTyping = false;

    static aurora::input::EventResult event(const aurora::input::InputEvent&, void*);
    static bool captures(const aurora::input::InputSource&, void*);
};

GameEditor& game_editor();

} // namespace acgc::input
