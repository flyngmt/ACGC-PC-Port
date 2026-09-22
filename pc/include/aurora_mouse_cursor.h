#ifndef AURORA_MOUSE_CURSOR_H
#define AURORA_MOUSE_CURSOR_H

#define AURORA_MOUSE_CURSOR_VIEW_SIZE 128
#define AURORA_MOUSE_CURSOR_FRAME_COUNT 60
#define PC_NOOP_MOUSE_CAPTURE_BEGIN 0xAC5800u
#define PC_NOOP_MOUSE_CAPTURE_END   0xAC5900u
#define PC_NOOP_MOUSE_CURSOR_DRAW   0xAC5A00u

#ifdef __cplusplus
extern "C" {
#endif

int aurora_mouse_cursor_needs_capture(int frame);
int aurora_mouse_cursor_texture_size(void);
void aurora_mouse_cursor_invalidate(void);
void aurora_mouse_cursor_capture_begin(void);
void aurora_mouse_cursor_capture_end(int frame);
void aurora_mouse_cursor_draw(int frame);

#ifdef __cplusplus
}
#endif

#endif
