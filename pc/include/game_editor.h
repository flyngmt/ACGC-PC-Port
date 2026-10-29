#ifndef ACGC_GAME_EDITOR_H
#define ACGC_GAME_EDITOR_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GameEditorEventType {
    GAME_EDITOR_INSERT_CHARACTER,
    GAME_EDITOR_BACKSPACE,
    GAME_EDITOR_MOVE_CURSOR,
    GAME_EDITOR_SUBMIT
} GameEditorEventType;

typedef enum GameEditorDirection {
    GAME_EDITOR_LEFT,
    GAME_EDITOR_RIGHT,
    GAME_EDITOR_UP,
    GAME_EDITOR_DOWN,
} GameEditorDirection;

typedef enum GameEditorState {
    GAME_EDITOR_OFF,
    GAME_EDITOR_PENDING,
    GAME_EDITOR_SUSPENDED,
    GAME_EDITOR_ACTIVE,
    GAME_EDITOR_FAILED
} GameEditorState;

typedef struct GameEditorEvent {
    GameEditorEventType type;
    union {
        uint8_t character;
        GameEditorDirection direction;
    } value;
} GameEditorEvent;

/* Availability follows the game editor's lifetime. Tab toggles keyboard typing. */
void acgc_editor_set_available(int available, int multiline);
GameEditorState acgc_editor_state(void);
/* Drain at most capacity commands; the game deliberately requests one per update. */
size_t acgc_editor_drain(GameEditorEvent* output, size_t capacity);
/* Caret in the game's 320x240 menu coordinates, including widescreen margins. */
void acgc_editor_set_caret(float x, float y, float height);

#ifdef __cplusplus
}
#endif
#endif
