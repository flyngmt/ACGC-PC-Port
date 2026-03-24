/* pc_typing.c - Keyboard typing mode for the in-game text editor.
 * When the editor overlay is active, Tab toggles typing mode.
 * SDL_TEXTINPUT events are mapped to game character codes and queued.
 * The editor overlay (m_editor_ovl.c) consumes from the queue each frame. */
#include "pc_typing.h"

#ifdef KEYBOARD_TYPING
#include "m_font.h"

int           g_pc_typing_mode = 0;
int           g_pc_editor_active = 0;
PCTypingQueue g_pc_typing_queue = {0};

void pc_typing_queue_clear(void) {
    g_pc_typing_queue.head = 0;
    g_pc_typing_queue.tail = 0;
    g_pc_typing_queue.count = 0;
}

void pc_typing_queue_push(int code) {
    if (g_pc_typing_queue.count >= PC_TYPING_QUEUE_SIZE) return;
    g_pc_typing_queue.entries[g_pc_typing_queue.tail] = code;
    g_pc_typing_queue.tail = (g_pc_typing_queue.tail + 1) % PC_TYPING_QUEUE_SIZE;
    g_pc_typing_queue.count++;
}

int pc_typing_queue_pop(int* out) {
    if (g_pc_typing_queue.count <= 0) return 0;
    *out = g_pc_typing_queue.entries[g_pc_typing_queue.head];
    g_pc_typing_queue.head = (g_pc_typing_queue.head + 1) % PC_TYPING_QUEUE_SIZE;
    g_pc_typing_queue.count--;
    return 1;
}

/* Map a UTF-8 character from SDL_TEXTINPUT to an AC game character code.
 * Returns -1 for unmappable characters. */
int pc_utf8_to_game_code(const char* text) {
    unsigned char c = (unsigned char)text[0];

    if (c < 0x80) {
        static const int ascii_map[128] = {
            -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
            ' ','!','"', -1, -1,'%','&','\'','(',')','*','+',',','-','.','/',
            '0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?',
            '@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
            'P','Q','R','S','T','U','V','W','X','Y','Z', -1,'\\', -1, -1,'_',
             -1,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
            'p','q','r','s','t','u','v','w','x','y','z', -1, -1, -1, -1, -1,
        };
        return ascii_map[c];
    }

    /* 2-byte UTF-8: accented characters (see m_font.h for CHAR_* defines) */
    if (c >= 0xC0 && c <= 0xDF) {
        unsigned char c2 = (unsigned char)text[1];
        if ((c2 & 0xC0) != 0x80) return -1;
        int cp = ((c & 0x1F) << 6) | (c2 & 0x3F);

        if (cp == 0xA1) return CHAR_INVERT_EXCLAMATION;
        if (cp == 0xBF) return CHAR_INVERT_QUESTIONMARK;

        /* U+00C0..U+00DF: uppercase accented */
        if (cp >= 0xC0 && cp <= 0xDF) {
            static const int upper[] = {
                CHAR_GRAVE_A, CHAR_ACUTE_A, CHAR_CIRCUMFLEX_A, CHAR_TILDE_A,
                CHAR_DIAERESIS_A, CHAR_ANGSTROM_A, CHAR_ASH, CHAR_CEDILLA,
                CHAR_GRAVE_E, CHAR_ACUTE_E, CHAR_CIRCUMFLEX_E, CHAR_DIARESIS_E,
                CHAR_GRAVE_I, CHAR_ACUTE_I, CHAR_CIRCUMFLEX_I, CHAR_DIARESIS_I,
                CHAR_ETH, CHAR_TILDE_N,
                CHAR_GRAVE_O, CHAR_ACUTE_O, CHAR_CIRCUMFLEX_O, CHAR_TILDE_O,
                CHAR_DIARESIS_O, -1,
                CHAR_OE, CHAR_GRAVE_U, CHAR_ACUTE_U, CHAR_CIRCUMFLEX_U,
                CHAR_DIARESIS_U, CHAR_ACUTE_Y, CHAR_THORN, CHAR_LOWER_BETA
            };
            return upper[cp - 0xC0];
        }
        /* U+00E0..U+00FF: lowercase accented */
        if (cp >= 0xE0 && cp <= 0xFF) {
            static const int lower[] = {
                CHAR_GRAVE_a, CHAR_ACUTE_a, CHAR_CIRCUMFLEX_a, CHAR_TILDE_a,
                CHAR_DIARESIS_a, CHAR_ANGSTROM_a, CHAR_LOWER_ASH, CHAR_LOWER_CEDILLA,
                CHAR_GRAVE_e, CHAR_ACUTE_e, CHAR_CIRCUMFLEX_e, CHAR_DIARESIS_e,
                CHAR_GRAVE_i, CHAR_ACUTE_i, CHAR_CIRCUMFLEX_i, CHAR_DIARESIS_i,
                CHAR_LOWER_ETH, CHAR_TILDE_n,
                CHAR_GRAVE_o, CHAR_ACUTE_o, CHAR_CIRCUMFLEX_o, CHAR_TILDE_o,
                CHAR_DIARESIS_o, -1,
                CHAR_oe, CHAR_GRAVE_u, CHAR_ACUTE_u, CHAR_CIRCUMFLEX_u,
                CHAR_DIARESIS_u, CHAR_ACUTE_y, CHAR_LOWER_THORN, CHAR_DIARESIS_y
            };
            return lower[cp - 0xE0];
        }
        return -1;
    }

    return -1;
}

void pc_typing_handle_event(const SDL_Event* event) {
    if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_TAB && !event->key.repeat && g_pc_editor_active) {
            g_pc_typing_mode ^= 1;
            if (g_pc_typing_mode) {
                SDL_StartTextInput();
                pc_typing_queue_clear();
            } else {
                SDL_StopTextInput();
            }
        }

        if (g_pc_typing_mode && g_pc_editor_active) {
            switch (event->key.keysym.sym) {
                case SDLK_BACKSPACE: pc_typing_queue_push(PC_TYPING_CMD_BACKSPACE); break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:  pc_typing_queue_push(PC_TYPING_CMD_ENTER); break;
                case SDLK_LEFT:      pc_typing_queue_push(PC_TYPING_CMD_LEFT); break;
                case SDLK_RIGHT:     pc_typing_queue_push(PC_TYPING_CMD_RIGHT); break;
                case SDLK_UP:        pc_typing_queue_push(PC_TYPING_CMD_UP); break;
                case SDLK_DOWN:      pc_typing_queue_push(PC_TYPING_CMD_DOWN); break;
                default: break;
            }
        }
    }

    if (event->type == SDL_TEXTINPUT && g_pc_typing_mode && g_pc_editor_active) {
        const char* p = event->text.text;
        while (*p) {
            int code = pc_utf8_to_game_code(p);
            if (code >= 0)
                pc_typing_queue_push(code);
            unsigned char lead = (unsigned char)*p;
            if (lead < 0x80) p += 1;
            else if (lead < 0xE0) p += 2;
            else if (lead < 0xF0) p += 3;
            else p += 4;
        }
    }
}

void pc_typing_update(void) {
    if (g_pc_typing_mode && !g_pc_editor_active) {
        g_pc_typing_mode = 0;
        SDL_StopTextInput();
        pc_typing_queue_clear();
    }
}

#endif /* KEYBOARD_TYPING */
