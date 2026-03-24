/* pc_typing.h - Keyboard typing mode for the in-game text editor */
#ifndef PC_TYPING_H
#define PC_TYPING_H

#include "pc_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KEYBOARD_TYPING

#define PC_TYPING_QUEUE_SIZE 32

/* Command signals for the typing queue (above 255 to avoid collision with character codes) */
#define PC_TYPING_CMD_BACKSPACE 256
#define PC_TYPING_CMD_LEFT      257
#define PC_TYPING_CMD_RIGHT     258
#define PC_TYPING_CMD_UP        259
#define PC_TYPING_CMD_DOWN      260
#define PC_TYPING_CMD_ENTER     261

typedef struct {
    int entries[PC_TYPING_QUEUE_SIZE];
    int head;
    int tail;
    int count;
} PCTypingQueue;

extern int g_pc_typing_mode;
extern int g_pc_editor_active;
extern PCTypingQueue g_pc_typing_queue;

void pc_typing_queue_clear(void);
void pc_typing_queue_push(int code);
int  pc_typing_queue_pop(int* out);
int  pc_utf8_to_game_code(const char* text);
void pc_typing_handle_event(const SDL_Event* event);
void pc_typing_update(void);

#else

#define g_pc_typing_mode   0
#define g_pc_editor_active 0
static inline void pc_typing_handle_event(const SDL_Event* event) { (void)event; }
static inline void pc_typing_update(void) {}

#endif /* KEYBOARD_TYPING */

#ifdef __cplusplus
}
#endif

#endif /* PC_TYPING_H */
