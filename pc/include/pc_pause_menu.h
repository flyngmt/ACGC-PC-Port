/* In game pause menu, because at this point it feels weird to not have it. */
#ifndef PC_PAUSE_MENU_H
#define PC_PAUSE_MENU_H

#include <SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

struct game_s; /* matches typedef in game_h.h */

extern int g_pc_paused;

/* Set by ac_animal_logo. Can't pause on the main menu. You can actually pause before the main menu appears, but it is what it is. */
extern int g_pc_title_main_menu_visible;

/* Don't allow pausing while NES is running. Crashes the game, also NES games has their own pause. */
extern int g_pc_nes_active;

/* ESC handler in pc_main calls this. Also needed if I reintroduce the audio pause on game pause. */
void pc_pause_menu_toggle(void);

/* Forward an SDL event for menu navigation. Returns 1 if consumed. 
*  Doesn't do anything if not paused. */
int  pc_pause_menu_handle_event(const SDL_Event* e);

/* Append the pause overlay to the GAME's font display list. Call from
 * graph_main right after game_main() returns. 
 * Doesn't do anything if not paused. */
void pc_pause_menu_draw(struct game_s* game);

#ifdef __cplusplus
}
#endif

#endif /* PC_PAUSE_MENU_H */
