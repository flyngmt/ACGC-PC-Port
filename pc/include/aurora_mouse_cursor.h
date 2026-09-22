#ifndef AURORA_MOUSE_CURSOR_H
#define AURORA_MOUSE_CURSOR_H

#define AURORA_MOUSE_CURSOR_TEXTURE_SIZE 128
#define PC_NOOP_MOUSE_CAPTURE_BEGIN 0xAC5800u
#define PC_NOOP_MOUSE_CAPTURE_END   0xAC5801u
#define PC_NOOP_MOUSE_CURSOR_DRAW   0xAC5802u

#ifdef __cplusplus
extern "C" {
#endif

int aurora_mouse_cursor_needs_capture(void);
void aurora_mouse_cursor_invalidate(void);
void aurora_mouse_cursor_capture_begin(void);
void aurora_mouse_cursor_capture_end(void);
void aurora_mouse_cursor_draw(void);

#ifdef __cplusplus
}
#endif

#endif
