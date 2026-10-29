#ifndef ACGC_GAME_POINTER_H
#define ACGC_GAME_POINTER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GamePointerButton {
    GAME_POINTER_LEFT = 1u << 0,
    GAME_POINTER_MIDDLE = 1u << 1,
    GAME_POINTER_RIGHT = 1u << 2,
    GAME_POINTER_X1 = 1u << 3,
    GAME_POINTER_X2 = 1u << 4,
} GamePointerButton;

typedef enum GamePointerOwner {
    GAME_POINTER_NONE,
    GAME_POINTER_MOUSE,
    GAME_POINTER_PAD,
    GAME_POINTER_KEYBOARD,
} GamePointerOwner;

typedef struct GamePointerFrame {
    uint32_t tick;
    float x, y; /* Menu coordinates (320x240, including widescreen margins). */
    uint32_t held, pressed;
    float scroll_x, scroll_y; /* Aurora convention: positive Y scrolls down. */
    int scroll_steps_y;       /* Whole detents; fractional deltas accumulate across ticks. */
    int inside, moved, active, visible, cancelled;
    GamePointerOwner owner;
} GamePointerFrame;

/* All consumers see this same immutable snapshot until the next game input tick. */
const GamePointerFrame* acgc_pointer_frame(void);
void acgc_pointer_begin_tick(uint32_t tick);

#ifdef __cplusplus
}
#endif
#endif
