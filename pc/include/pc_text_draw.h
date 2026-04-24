/* I assume people will be confused by why this even exists.
 * Text heavy menus get a heavy FPS penalty otherwise.
 * Draws ASCII strings using the same font atlas as mFont, but with all
 * glyphs of a call coalesced into one gSPVertex + one gSPNTriangles chain
 * per 7-char chunk. This bypasses mFont's per-character sub-DL emission
 * (one draw call per glyph) and the control-code machinery none of the PC
 * UI needs. mFont itself stays untouched for dialogs and scenes that do
 * need control codes / streaming reveal / voice-SE. */

#ifndef PC_TEXT_DRAW_H
#define PC_TEXT_DRAW_H

#include "pc_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

struct game_s;

/* Pixel width of a null-terminated string at scale=1. */
int  pc_text_width(const char* s);

/* Same convention as mFont_SetLineStrings. 
 * The string renders into font_thaga so the caller
 * must already be inside a font draw phase. */
void pc_text_draw(struct game_s* game, const char* s, f32 x, f32 y,
                  int r, int g, int b, int a, f32 scale);

#ifdef __cplusplus
}
#endif

#endif /* PC_TEXT_DRAW_H */
