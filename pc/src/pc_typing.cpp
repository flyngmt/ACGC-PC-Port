#include "pc_typing.h"

#include "acgc/game_input_block.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>

#include <array>
#include <cstddef>
#include <cstring>
#include <deque>

namespace {

constexpr int kGameCharTilde = 42;
constexpr int kGameCharForwardSlash = 174;
constexpr int kGameCharPlus = 180;
constexpr int kGameCharSemicolon = 208;
constexpr int kGameCharHashtag = 209;
constexpr int kGameCharBackslash = 222;

SDL_Window* s_window = nullptr;
bool s_editor_active = false;
bool s_typing_active = false;
std::deque<int> s_queue;

void clear_queue()
{
    s_queue.clear();
}

void push_queue(int value)
{
    s_queue.push_back(value);
}

void stop_typing()
{
    if (!s_typing_active) {
        return;
    }

    s_typing_active = false;
    if (s_window != nullptr && SDL_TextInputActive(s_window)) {
        SDL_StopTextInput(s_window);
    }
    acgc::set_input_blocked(acgc::InputBlockReason::GameTyping, false);
    clear_queue();
}

void start_typing()
{
    if (s_typing_active || !s_editor_active || s_window == nullptr) {
        return;
    }
    if (!SDL_StartTextInput(s_window)) {
        return;
    }

    clear_queue();
    s_typing_active = true;
    acgc::set_input_blocked(acgc::InputBlockReason::GameTyping, true);
}

int utf8_to_game_code(const char* text, std::size_t& consumed)
{
    consumed = 1;
    const unsigned char lead = static_cast<unsigned char>(text[0]);

    if (lead < 0x80) {
        static constexpr std::array<int, 128> ascii_map = {
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
            ' ', '!', '"', kGameCharHashtag, -1, '%', '&', 0x27, '(', ')', -1, kGameCharPlus, ',', '-', '.',
            kGameCharForwardSlash,
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', kGameCharSemicolon, '<', '=', '>', '?',
            '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', -1, kGameCharBackslash, -1, -1, '_',
            -1,  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
            'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', -1, -1, -1, kGameCharTilde, -1,
        };
        return ascii_map[lead];
    }

    if (lead < 0xC2 || lead > 0xDF || text[1] == '\0') {
        return -1;
    }

    const unsigned char continuation = static_cast<unsigned char>(text[1]);
    if ((continuation & 0xC0) != 0x80) {
        return -1;
    }
    consumed = 2;
    const int codepoint = ((lead & 0x1F) << 6) | (continuation & 0x3F);

    if (codepoint == 0xA1) {
        return 0;
    }
    if (codepoint == 0xBF) {
        return 1;
    }
    if (codepoint >= 0xC0 && codepoint <= 0xDF) {
        // Animal Crossing font codes corresponding to U+00C0 through U+00DF.
        static constexpr std::array<int, 32> uppercase = {
            3, 4, 5, 6, 2, 7, 162, 8, 9, 10, 11, 12, 13, 14, 15, 16,
            17, 18, 19, 20, 21, 22, 23, -1, 24, 25, 26, 27, 28, 150, 30, 29,
        };
        return uppercase[codepoint - 0xC0];
    }
    if (codepoint >= 0xE0 && codepoint <= 0xFF) {
        // Animal Crossing font codes corresponding to U+00E0 through U+00FF.
        static constexpr std::array<int, 32> lowercase = {
            31, 35, 36, 91, 93, 94, 163, 96, 123, 124, 125, 126, 129, 130, 131, 132,
            134, 135, 136, 137, 138, 139, 140, -1, 141, 142, 143, 145, 146, 147, 149, 148,
        };
        return lowercase[codepoint - 0xE0];
    }

    return -1;
}

} // namespace

extern "C" {

void pc_typing_initialize(SDL_Window* window)
{
    s_window = window;
}

void pc_typing_shutdown(void)
{
    stop_typing();
    s_editor_active = false;
    s_window = nullptr;
}

void pc_typing_handle_event(const SDL_Event* event)
{
    if (event == nullptr) {
        return;
    }

    if (event->type == SDL_EVENT_WINDOW_FOCUS_LOST) {
        stop_typing();
        return;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (!event->key.repeat && event->key.key == SDLK_TAB && s_editor_active) {
            if (s_typing_active) {
                stop_typing();
            } else {
                start_typing();
            }
            return;
        }

        if (!s_typing_active) {
            return;
        }
        switch (event->key.key) {
        case SDLK_BACKSPACE:
            push_queue(PC_TYPING_CMD_BACKSPACE);
            break;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
            push_queue(PC_TYPING_CMD_ENTER);
            break;
        case SDLK_LEFT:
            push_queue(PC_TYPING_CMD_LEFT);
            break;
        case SDLK_RIGHT:
            push_queue(PC_TYPING_CMD_RIGHT);
            break;
        case SDLK_UP:
            push_queue(PC_TYPING_CMD_UP);
            break;
        case SDLK_DOWN:
            push_queue(PC_TYPING_CMD_DOWN);
            break;
        default:
            break;
        }
        return;
    }

    if (event->type != SDL_EVENT_TEXT_INPUT || !s_typing_active || event->text.text == nullptr) {
        return;
    }

    const char* text = event->text.text;
    while (*text != '\0') {
        std::size_t consumed = 1;
        const int code = utf8_to_game_code(text, consumed);
        if (code >= 0) {
            push_queue(code);
        }
        text += consumed;
    }
}

void pc_typing_cancel(void)
{
    stop_typing();
}

void pc_typing_set_editor_active(int active)
{
    s_editor_active = active != 0;
    if (!s_editor_active) {
        stop_typing();
    }
}

int pc_typing_is_active(void)
{
    return s_typing_active ? 1 : 0;
}

int pc_typing_is_editor_active(void)
{
    return s_editor_active ? 1 : 0;
}

int pc_typing_queue_pop(int* output)
{
    if (output == nullptr || s_queue.empty()) {
        return 0;
    }

    *output = s_queue.front();
    s_queue.pop_front();
    return 1;
}

int pc_typing_game_code_to_utf8(int code, char* output, int output_size)
{
    static const auto table = [] {
        std::array<std::array<char, 3>, 256> result{};
        for (int codepoint = 0xFF; codepoint >= 0x20; --codepoint) {
            if (codepoint > 0x7E && codepoint < 0xA1) {
                continue;
            }
            char encoded[3] = {};
            if (codepoint < 0x80) {
                encoded[0] = static_cast<char>(codepoint);
            } else {
                encoded[0] = static_cast<char>(0xC0 | (codepoint >> 6));
                encoded[1] = static_cast<char>(0x80 | (codepoint & 0x3F));
            }
            std::size_t consumed = 0;
            const int game_code = utf8_to_game_code(encoded, consumed);
            if (game_code >= 0 && game_code < 256) {
                std::memcpy(result[game_code].data(), encoded, sizeof(encoded));
            }
        }
        return result;
    }();

    if (output == nullptr || output_size <= 0 || code < 0 || code >= 256 || table[code][0] == '\0') {
        return 0;
    }
    const std::size_t length = std::strlen(table[code].data());
    if (length + 1 > static_cast<std::size_t>(output_size)) {
        return 0;
    }
    std::memcpy(output, table[code].data(), length + 1);
    return static_cast<int>(length);
}

} // extern "C"
