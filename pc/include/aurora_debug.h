#ifndef ACGC_AURORA_DEBUG_H
#define ACGC_AURORA_DEBUG_H

#include <aurora/aurora.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int g_pc_debug_ui_visible;

void ac_debug_imgui_init(const AuroraWindowSize* size);
void ac_debug_imgui_draw(void);

#ifdef __cplusplus
}
#endif

#endif
