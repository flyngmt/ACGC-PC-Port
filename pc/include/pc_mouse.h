#ifndef PC_MOUSE_H
#define PC_MOUSE_H

#include "pc_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;

/* mouse constants */
#define PC_MOUSE_BUTTON_LEFT    (1 << 0)
#define PC_MOUSE_BUTTON_MIDDLE  (1 << 1)
#define PC_MOUSE_BUTTON_RIGHT   (1 << 2)
#define PC_MOUSE_BUTTON_X1      (1 << 3)
#define PC_MOUSE_BUTTON_X2      (1 << 4)
#define PC_MOUSE_WHEEL_UP       (1 << 5)
#define PC_MOUSE_WHEEL_DOWN     (1 << 6)

enum PCMouseBlockReason {
    PC_MOUSE_BLOCK_HOST_UI = 1 << 0,
    PC_MOUSE_BLOCK_IMGUI = 1 << 1,
    PC_MOUSE_BLOCK_PAUSED = 1 << 2,
};

#ifdef MOUSE_INPUT

void pc_mouse_initialize(SDL_Window* window);
void pc_mouse_shutdown(void);
void pc_mouse_handle_event(const SDL_Event* event);
void pc_mouse_set_blocked(u32 reason, int blocked);
void pc_mouse_cancel(void);

u32 pc_mouse_button_held(void);
u32 pc_mouse_button_pressed(void);
u32 pc_mouse_button_released(void);
void pc_mouse_lock(s32 lock);
int pc_mouse_is_locked(void);
s32 pc_mouse_scroll_wheel(void);
void pc_mouse_get_position(s32 *x, s32 *y);
void pc_mouse_get_delta(s32 *dx, s32 *dy);
int pc_mouse_moved(void);
int pc_mouse_active(void);
/* Returns viewport containment in menu coordinates, including widescreen margins. */
int pc_mouse_get_ui_position(f32* x, f32* y);
void pc_mouse_get_native_position(s32 *x, s32 *y);
void pc_mouse_update(void);

#else

static inline void pc_mouse_initialize(SDL_Window* window) { (void)window; }
static inline void pc_mouse_shutdown(void) {}
static inline void pc_mouse_handle_event(const SDL_Event* event) { (void)event; }
static inline void pc_mouse_set_blocked(u32 reason, int blocked) { (void)reason; (void)blocked; }
static inline void pc_mouse_cancel(void) {}
static inline u32 pc_mouse_button_held(void) { return 0; }
static inline u32 pc_mouse_button_pressed(void) { return 0; }
static inline u32 pc_mouse_button_released(void) { return 0; }
static inline void pc_mouse_lock(s32 lock) { (void)lock; }
static inline int pc_mouse_is_locked(void) { return 0; }
static inline s32 pc_mouse_scroll_wheel(void) { return 0; }
static inline void pc_mouse_get_position(s32 *x, s32 *y) {
    if (x) *x = 0;
    if (y) *y = 0;
}
static inline void pc_mouse_get_delta(s32 *dx, s32 *dy) { pc_mouse_get_position(dx, dy); }
static inline int pc_mouse_moved(void) { return 0; }
static inline int pc_mouse_active(void) { return 0; }
static inline int pc_mouse_get_ui_position(f32* x, f32* y) {
    if (x) *x = -1.0f;
    if (y) *y = -1.0f;
    return 0;
}
static inline void pc_mouse_get_native_position(s32 *x, s32 *y) { pc_mouse_get_position(x, y); }
static inline void pc_mouse_update(void) {}

#endif /* MOUSE_INPUT */

#ifdef __cplusplus
}
#endif

#endif /* PC_MOUSE_H */
