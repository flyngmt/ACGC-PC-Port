/* pc_mouse.c - Mouse input mode for menus and misc interfaces.
 * When an interface is active, mouse can be used to interact with it.
 * There's helpers to see when a mouse is moved, wheel movement and clicks. */

#include "pc_mouse.h"

#ifdef MOUSE_INPUT
static s32 g_mouse_x = 0, g_mouse_y = 0;
static s32 g_mouse_dx = 0, g_mouse_dy = 0;
static s32 g_mouse_locked = 0;
static s32 g_prev_mouse_x = 0, g_prev_mouse_y = 0;
static s32 g_mouse_moved = 0;
static u32 g_mouse_buttons_current = 0;
static u32 g_mouse_buttons_previous = 0;
static int g_mouse_active_this_frame = 0;

s32 g_mouse_wheel_delta = 0;

u32 pc_mouse_button_held(void) {
    return g_mouse_buttons_current;
}

u32 pc_mouse_button_pressed(void) {
    return (g_mouse_buttons_current & ~g_mouse_buttons_previous);
}

u32 pc_mouse_button_released(void) {
    return (~g_mouse_buttons_current & g_mouse_buttons_previous);
}

void pc_mouse_lock(s32 lock) {
    g_mouse_locked = !!lock;
    SDL_SetRelativeMouseMode(g_mouse_locked);
}

int pc_mouse_is_locked(void) {
    return g_mouse_locked;
}

s32 pc_mouse_scroll_wheel(void) {
    s32 wheel = g_mouse_wheel_delta;
    if (g_mouse_wheel_delta) g_mouse_wheel_delta = 0;
    return wheel;
}

void pc_mouse_get_position(s32 *x, s32 *y) {
    if (x) *x = g_mouse_x;
    if (y) *y = g_mouse_y;
}

void pc_mouse_get_delta(s32 *dx, s32 *dy) {
    if (dx) *dx = g_mouse_dx;
    if (dy) *dy = g_mouse_dy;
}

int pc_mouse_moved(void) {
    return g_mouse_moved;
}

int pc_mouse_active(void) {
    return g_mouse_active_this_frame;
}

#ifdef PC_ENHANCEMENTS
extern float g_aspect_factor;
extern float g_aspect_offset;
extern int   g_aspect_active;
#endif

/* Scale mouse position to the native's game window.
 * Makes it easier to interact with menus. */
void pc_mouse_get_native_position(s32 *x, s32 *y) {
    s32 mouse_x, mouse_y;
    f32 scaled_x, scaled_y;
    
    pc_mouse_get_position(&mouse_x, &mouse_y);
    
    if (g_pc_window_w > 0 && g_pc_window_h > 0) {
#ifdef PC_ENHANCEMENTS
        if (g_aspect_active) {
            scaled_x = ((f32)mouse_x * PC_GC_WIDTH) / g_pc_window_w;
            scaled_x = (scaled_x - g_aspect_offset) / g_aspect_factor;

            scaled_y = ((f32)mouse_y * PC_GC_HEIGHT) / g_pc_window_h;
        } else
#endif
        {
            scaled_x = ((f32)mouse_x * PC_GC_WIDTH) / g_pc_window_w;
            scaled_y = ((f32)mouse_y * PC_GC_HEIGHT) / g_pc_window_h;
        }
    } else {
        scaled_x = (f32)mouse_x;
        scaled_y = (f32)mouse_y;
    }
    
    if (x) *x = (s32)scaled_x;
    if (y) *y = (s32)scaled_y;
}

void pc_mouse_update(void) {
    g_mouse_buttons_previous = g_mouse_buttons_current;

    s32 mx, my;
    u32 sdl_buttons = SDL_GetMouseState((int*)&mx, (int*)&my);
    g_mouse_buttons_current = 0;

    /* Convert each SDL button to our bitflag system */
    if (sdl_buttons & SDL_BUTTON(SDL_BUTTON_LEFT))   g_mouse_buttons_current |= PC_MOUSE_BUTTON_LEFT;
    if (sdl_buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) g_mouse_buttons_current |= PC_MOUSE_BUTTON_MIDDLE;
    if (sdl_buttons & SDL_BUTTON(SDL_BUTTON_RIGHT))  g_mouse_buttons_current |= PC_MOUSE_BUTTON_RIGHT;
    if (sdl_buttons & SDL_BUTTON(SDL_BUTTON_X1))     g_mouse_buttons_current |= PC_MOUSE_BUTTON_X1;
    if (sdl_buttons & SDL_BUTTON(SDL_BUTTON_X2))     g_mouse_buttons_current |= PC_MOUSE_BUTTON_X2;

    int wheel_active = 0;
    if (g_mouse_wheel_delta > 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_UP;
        wheel_active = 1;
    } else if (g_mouse_wheel_delta < 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_DOWN;
        wheel_active = 1;
    }

    g_mouse_moved = (mx != g_prev_mouse_x || my != g_prev_mouse_y);

    g_mouse_active_this_frame = (g_mouse_moved || 
                                 (g_mouse_buttons_current & ~(PC_MOUSE_WHEEL_UP | PC_MOUSE_WHEEL_DOWN)) ||
                                 wheel_active);
    
    s32 mdx = 0, mdy = 0;
    SDL_GetRelativeMouseState((int*)&mdx, (int*)&mdy);
    
    if (g_mouse_locked) {
        g_mouse_dx = mdx;
        g_mouse_dy = mdy;
    } else {
        g_mouse_dx = mx - g_mouse_x;
        g_mouse_dy = my - g_mouse_y;
    }

    g_prev_mouse_x = g_mouse_x;
    g_prev_mouse_y = g_mouse_y;
    g_mouse_x = mx;
    g_mouse_y = my;
}

#endif /* MOUSE_INPUT */
