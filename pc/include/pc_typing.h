#ifndef PC_TYPING_H
#define PC_TYPING_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;

enum PCTypingCommand {
    PC_TYPING_CMD_BACKSPACE = 256,
    PC_TYPING_CMD_LEFT,
    PC_TYPING_CMD_RIGHT,
    PC_TYPING_CMD_UP,
    PC_TYPING_CMD_DOWN,
    PC_TYPING_CMD_ENTER,
};

void pc_typing_initialize(SDL_Window* window);
void pc_typing_shutdown(void);
void pc_typing_handle_event(const SDL_Event* event);
void pc_typing_cancel(void);

void pc_typing_set_editor_active(int active);
int pc_typing_is_editor_active(void);
int pc_typing_is_active(void);
int pc_typing_queue_pop(int* output);
int pc_typing_game_code_to_utf8(int code, char* output, int output_size);

#ifdef __cplusplus
}
#endif

#endif
