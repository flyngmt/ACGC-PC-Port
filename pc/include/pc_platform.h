/* pc_platform.h - SDL2/OpenGL platform layer, global state, crash protection */
#ifndef PC_PLATFORM_H
#define PC_PLATFORM_H

#include <stdint.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <glad/gl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "pc_types.h"

/* --- Configuration --- */
#define PC_GC_WIDTH       640
#define PC_GC_HEIGHT      480
#define PC_SCREEN_WIDTH   PC_GC_WIDTH
#define PC_SCREEN_HEIGHT  PC_GC_HEIGHT
#define PC_WINDOW_TITLE   "Animal Crossing"

#if UINTPTR_MAX > 0xFFFFFFFFu
/* 64-bit: structs with pointer fields are larger, need more arena space */
#define PC_MAIN_MEMORY_SIZE   (48 * 1024 * 1024)
#else
#define PC_MAIN_MEMORY_SIZE   (24 * 1024 * 1024)
#endif
#define PC_ARAM_SIZE          (16 * 1024 * 1024)
#define PC_FIFO_SIZE          (256 * 1024)

#define PC_PI  3.14159265358979323846
#define PC_PIf 3.14159265358979323846f
#define PC_DEG_TO_RAD (PC_PI / 180.0)
#define PC_DEG_TO_RADf (PC_PIf / 180.0f)

/* GC hardware clocks */
#define GC_BUS_CLOCK          162000000u
#define GC_CORE_CLOCK         486000000u
#define GC_TIMER_CLOCK        (GC_BUS_CLOCK / 4)

/* --- Platform headers --- */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#undef near
#undef far
#elif defined(__APPLE__)
#include <signal.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <mach-o/dyld.h>
#else
#include <signal.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <elf.h>
#endif
#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

/* --- Global state --- */
extern SDL_Window*   g_pc_window;
extern SDL_GLContext  g_pc_gl_context;
extern int           g_pc_running;
extern int           g_pc_verbose;
extern int           g_pc_no_framelimit;
extern int           g_pc_fast_forward;
extern int           g_pc_time_override;
extern int           g_pc_min_override;
extern int           g_pc_sec_override;

extern int g_pc_window_w;
extern int g_pc_window_h;
void pc_platform_update_window_size(void);

/* --- Widescreen mode (3-state) ---
 * 0 = hor+ (default): full-window viewport, FOV-corrected projection. Resets each frame.
 * 1 = stretch: full-window, no correction. For transitions/inventory BG.
 * 2 = pillarbox: centered 4:3 with black bars. For inventory UI alignment.
 *
 * m_play.c inserts NOOPTag markers in POLY_OPA to switch between states:
 *   ON (0xAC5701) -> 1, OFF (0xAC5700) -> 2. emu64 reads these during DL processing. */
#define PC_NOOP_WIDESCREEN_STRETCH     0xAC5701u
#define PC_NOOP_WIDESCREEN_STRETCH_OFF 0xAC5700u
extern int g_pc_widescreen_stretch;

/* --- Functions --- */
void pc_platform_init(void);
void pc_platform_shutdown(void);
void pc_platform_swap_buffers(void);
int  pc_platform_poll_events(void);

/* --- Crash protection (VEH + setjmp/longjmp) --- */
void pc_crash_protection_init(void);
void pc_crash_set_jmpbuf(jmp_buf* buf);  /* NULL to disable */
uintptr_t pc_crash_get_addr(void);
uintptr_t pc_crash_get_data_addr(void);

/* EXE image range for seg2k0 pointer disambiguation (vs N64 segment addresses) */
extern uintptr_t pc_image_base;
extern uintptr_t pc_image_end;

/* Compile-time type validation */
#ifdef __cplusplus
static_assert(sizeof(u32) == 4, "u32 must be 4 bytes");
static_assert(sizeof(u16) == 2, "u16 must be 2 bytes");
static_assert(sizeof(uintptr_t) == sizeof(void*), "uintptr_t must match pointer size");
#else
_Static_assert(sizeof(u32) == 4, "u32 must be 4 bytes");
_Static_assert(sizeof(u16) == 2, "u16 must be 2 bytes");
_Static_assert(sizeof(uintptr_t) == sizeof(void*), "uintptr_t must match pointer size");
#endif

/* --- Model viewer --- */
extern int g_pc_model_viewer;
extern int g_pc_model_viewer_start;
extern int g_pc_model_viewer_no_cull;

/* --- Per-frame diagnostics --- */
extern int pc_emu64_frame_cmds;
extern int pc_emu64_frame_crashes;
extern int pc_emu64_frame_noop_cmds;
extern int pc_emu64_frame_tri_cmds;
extern int pc_emu64_frame_vtx_cmds;
extern int pc_emu64_frame_dl_cmds;
extern int pc_emu64_frame_cull_visible;
extern int pc_emu64_frame_cull_rejected;
extern int pc_gx_draw_call_count;

/* --- Audio --- */
extern int pc_save_loaded;
int  pc_audio_get_buffer_fill(void);
int  pc_audio_is_active(void);
void pc_audio_shutdown(void);
void pc_audio_start_producer_thread(void);
void pc_audio_mq_init(void);
void pc_audio_mq_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* PC_PLATFORM_H */
