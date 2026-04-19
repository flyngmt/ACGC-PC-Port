#ifndef PC_MOUSE_H
#define PC_MOUSE_H

#include "pc_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MOUSE_INPUT

/* mouse constants */
#define PC_MOUSE_BUTTON_LEFT    (1 << 0)
#define PC_MOUSE_BUTTON_MIDDLE  (1 << 1)
#define PC_MOUSE_BUTTON_RIGHT   (1 << 2)
#define PC_MOUSE_BUTTON_X1      (1 << 3)
#define PC_MOUSE_BUTTON_X2      (1 << 4)
#define PC_MOUSE_WHEEL_UP       (1 << 5)
#define PC_MOUSE_WHEEL_DOWN     (1 << 6)

extern s32 g_mouse_wheel_delta;

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
void pc_mouse_get_native_position(s32 *x, s32 *y);
void pc_mouse_update(void);

#else

#define g_mouse_wheel_delta   0

u32 pc_mouse_button_held(void) { return 0; }
u32 pc_mouse_button_pressed(void) { (return 0; }
u32 pc_mouse_button_released(void) { return 0; }
void pc_mouse_lock(s32 lock) { (void)lock; }
int pc_mouse_is_locked(void) { return 0; }
s32 pc_mouse_scroll_wheel(void) { return 0; }
void pc_mouse_get_position(s32 *x, s32 *y) { (void)x; (void)y; }
void pc_mouse_get_delta(s32 *dx, s32 *dy)  { (void)dx; (void)dy; }
int pc_mouse_moved(void) { return 0; }
int pc_mouse_active(void) { return 0; }
void pc_mouse_get_native_position(s32 *x, s32 *y)  { (void)x; (void)y; }
void pc_mouse_update(void) {}

#endif /* MOUSE_INPUT */

#ifdef __cplusplus
}
#endif

#endif /* PC_MOUSE_H */
