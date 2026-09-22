/* pc_mouse.c - Mouse input mode for menus and misc interfaces.
 * When an interface is active, mouse can be used to interact with it.
 * There's helpers to see when a mouse is moved, wheel movement and clicks. */

#include "pc_mouse.h"

#ifdef MOUSE_INPUT
#include "pc_platform.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

static SDL_Window* g_mouse_window = NULL;
static f32 g_mouse_x = 0, g_mouse_y = 0;
static s32 g_mouse_dx = 0, g_mouse_dy = 0;
static s32 g_mouse_locked = 0;
static s32 g_mouse_moved = 0;
static u32 g_mouse_buttons_current = 0;
static u32 g_mouse_buttons_pressed = 0;
static u32 g_mouse_buttons_released = 0;
static int g_mouse_active_this_frame = 0;

static s32 g_mouse_wheel_delta = 0;
static s32 g_pending_mouse_wheel_delta = 0;
static u32 g_pending_mouse_pressed = 0;
static u32 g_pending_mouse_released = 0;

static u32 pc_mouse_buttons_from_sdl(SDL_MouseButtonFlags buttons) {
    u32 result = 0;
    if (buttons & SDL_BUTTON_LMASK)  result |= PC_MOUSE_BUTTON_LEFT;
    if (buttons & SDL_BUTTON_MMASK)  result |= PC_MOUSE_BUTTON_MIDDLE;
    if (buttons & SDL_BUTTON_RMASK)  result |= PC_MOUSE_BUTTON_RIGHT;
    if (buttons & SDL_BUTTON_X1MASK) result |= PC_MOUSE_BUTTON_X1;
    if (buttons & SDL_BUTTON_X2MASK) result |= PC_MOUSE_BUTTON_X2;
    return result;
}

void pc_mouse_initialize(SDL_Window* window) {
    pc_mouse_shutdown();
    g_mouse_window = window;
    if (g_mouse_window != NULL) {
        g_mouse_buttons_current = pc_mouse_buttons_from_sdl(SDL_GetMouseState(&g_mouse_x, &g_mouse_y));
        SDL_GetRelativeMouseState(NULL, NULL);
    }
}

void pc_mouse_shutdown(void) {
    pc_mouse_lock(0);
    g_mouse_window = NULL;
    g_mouse_x = g_mouse_y = 0;
    g_mouse_dx = g_mouse_dy = 0;
    g_mouse_locked = g_mouse_moved = 0;
    g_mouse_buttons_current = g_mouse_buttons_pressed = g_mouse_buttons_released = 0;
    g_mouse_active_this_frame = 0;
    g_mouse_wheel_delta = 0;
    g_pending_mouse_wheel_delta = 0;
    g_pending_mouse_pressed = g_pending_mouse_released = 0;
}

void pc_mouse_handle_event(const SDL_Event* event) {
    if (g_mouse_window == NULL || event == NULL) {
        return;
    }
    if (event->type == SDL_EVENT_MOUSE_WHEEL && event->wheel.windowID == SDL_GetWindowID(g_mouse_window)) {
        s32 delta = event->wheel.integer_y;
        if (event->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
            delta = -delta;
        }
        g_pending_mouse_wheel_delta += delta;
    } else if ((event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP) &&
               event->button.windowID == SDL_GetWindowID(g_mouse_window) &&
               event->button.button >= SDL_BUTTON_LEFT && event->button.button <= SDL_BUTTON_X2) {
        const u32 button = pc_mouse_buttons_from_sdl(SDL_BUTTON_MASK(event->button.button));
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            g_pending_mouse_pressed |= button;
        } else {
            g_pending_mouse_released |= button;
        }
    }
}

u32 pc_mouse_button_held(void) {
    return g_mouse_buttons_current;
}

u32 pc_mouse_button_pressed(void) {
    return g_mouse_buttons_pressed;
}

u32 pc_mouse_button_released(void) {
    return g_mouse_buttons_released;
}

void pc_mouse_lock(s32 lock) {
    if (g_mouse_window != NULL && SDL_SetWindowRelativeMouseMode(g_mouse_window, lock != 0)) {
        g_mouse_locked = SDL_GetWindowRelativeMouseMode(g_mouse_window);
    }
}

int pc_mouse_is_locked(void) {
    return g_mouse_locked;
}

s32 pc_mouse_scroll_wheel(void) {
    return g_mouse_wheel_delta;
}

void pc_mouse_get_position(s32 *x, s32 *y) {
    if (x) *x = (s32)g_mouse_x;
    if (y) *y = (s32)g_mouse_y;
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

/* Scale mouse position to the native's game window.
 * Makes it easier to interact with menus. */
void pc_mouse_get_native_position(s32 *x, s32 *y) {
    s32 mouse_x, mouse_y;
    f32 scaled_x, scaled_y;
    
    pc_mouse_get_position(&mouse_x, &mouse_y);
    
    if (g_pc_window_w > 0 && g_pc_window_h > 0) {
#ifdef PC_ENHANCEMENTS
        const f32 aspect_factor = pc_widescreen_get_aspect_factor();
        if (aspect_factor < 1.0f) {
            const f32 aspect_offset = (1.0f - aspect_factor) * 0.5f * PC_GC_WIDTH;
            scaled_x = ((f32)mouse_x * PC_GC_WIDTH) / g_pc_window_w;
            scaled_x = (scaled_x - aspect_offset) / aspect_factor;

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
    if (g_mouse_window == NULL) {
        return;
    }
    const u32 previous_buttons = g_mouse_buttons_current;
    const u32 wheel_buttons = PC_MOUSE_WHEEL_UP | PC_MOUSE_WHEEL_DOWN;

    float mx, my;
    g_mouse_buttons_current = pc_mouse_buttons_from_sdl(SDL_GetMouseState(&mx, &my));

    g_mouse_wheel_delta = g_pending_mouse_wheel_delta;
    g_pending_mouse_wheel_delta = 0;
    if (g_mouse_wheel_delta > 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_UP;
    } else if (g_mouse_wheel_delta < 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_DOWN;
    }

    g_mouse_buttons_pressed = g_pending_mouse_pressed | (g_mouse_buttons_current & ~previous_buttons) |
                              (g_mouse_buttons_current & wheel_buttons);
    g_mouse_buttons_released = g_pending_mouse_released | (previous_buttons & ~g_mouse_buttons_current);
    g_pending_mouse_pressed = g_pending_mouse_released = 0;
    
    float mdx = 0, mdy = 0;
    SDL_GetRelativeMouseState(&mdx, &mdy);
    
    if (g_mouse_locked) {
        g_mouse_dx = (s32)mdx;
        g_mouse_dy = (s32)mdy;
        g_mouse_moved = (mdx != 0.0f || mdy != 0.0f);
    } else {
        g_mouse_dx = (s32)(mx - g_mouse_x);
        g_mouse_dy = (s32)(my - g_mouse_y);
        g_mouse_moved = (mx != g_mouse_x || my != g_mouse_y);
    }

    g_mouse_x = mx;
    g_mouse_y = my;

    g_mouse_active_this_frame = g_mouse_moved ||
        ((g_mouse_buttons_current | g_mouse_buttons_pressed | g_mouse_buttons_released) & ~wheel_buttons) ||
        g_mouse_wheel_delta != 0;
}

#endif /* MOUSE_INPUT */
