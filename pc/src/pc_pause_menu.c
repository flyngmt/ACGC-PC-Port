#include "pc_platform.h"
#include "pc_pause_menu.h"
#include "pc_settings_menu.h"
#include "pc_text_draw.h"

#include "m_font.h"
#include "m_rcp.h"
#include "graph.h"
#include "main.h"       /* SCREEN_WIDTH_F */

#include <stdio.h>
#include <string.h>

int g_pc_paused = 0;

/* Set by ac_animal_logo. Can't pause on the main menu. */
int g_pc_title_main_menu_visible = 0;

/* Don't allow pausing while NES is running. Crashes the game, also NES games has their own pause. */
int g_pc_nes_active = 0;

/* When the menu closes, the keys/buttons used to confirm Resume are usually
 * still physically held. Just drains those. */
int g_pc_pause_input_drain = 0;

/* Pause menu pages */
typedef enum {
    PAGE_MAIN = 0,
    PAGE_SETTINGS = 1,
    PAGE_CONFIRM_QUIT = 2,
} PauseMenuPage;

#define MAIN_ITEM_COUNT     3
#define CONFIRM_ITEM_COUNT  2

static PauseMenuPage cur_page = PAGE_MAIN;
static int main_sel = 0;    /* 0=Resume, 1=Settings, 2=Quit Game */
static int confirm_sel = 0; /* 0=No (default), 1=Yes */

void pc_pause_menu_toggle(void) {
    if (!g_pc_paused && g_pc_title_main_menu_visible && g_pc_nes_active) return;

    g_pc_paused = !g_pc_paused;
    if (g_pc_paused) {
        cur_page = PAGE_MAIN;
        main_sel = 0;
    } else {
        g_pc_pause_input_drain = 1;
    }
}

/* Input */

static void main_activate(void) {
    switch (main_sel) {
        case 0: /* Resume */
            pc_pause_menu_toggle();
            break;
        case 1: /* Settings */
            cur_page = PAGE_SETTINGS;
            pc_settings_menu_enter();
            break;
        case 2: /* Quit Game -> confirm page (default to No) */
            cur_page = PAGE_CONFIRM_QUIT;
            confirm_sel = 0;
            break;
    }
}

static void confirm_activate(void) {
    if (confirm_sel == 1) {
        printf("[PAUSE] Quit confirmed\n");
        g_pc_running = 0;
    } else {
        cur_page = PAGE_MAIN;
        main_sel = 0;
    }
}

int pc_pause_menu_handle_event(const SDL_Event* e) {
    if (!g_pc_paused) return 0;
    if (e->type != SDL_KEYDOWN) return 0;
    if (e->key.repeat) return 1;

    SDL_Keycode k = e->key.keysym.sym;

    /* Settings page is driven by pc_settings_menu. */
    if (cur_page == PAGE_SETTINGS) {
        switch (k) {
            case SDLK_UP:
            case SDLK_w:     pc_settings_menu_nav_up();   return 1;
            case SDLK_DOWN:
            case SDLK_s:     pc_settings_menu_nav_down(); return 1;
            case SDLK_LEFT:
            case SDLK_a:     pc_settings_menu_nav_left(); return 1;
            case SDLK_RIGHT:
            case SDLK_d:     pc_settings_menu_nav_right(); return 1;
            case SDLK_RETURN:
            case SDLK_KP_ENTER:
            case SDLK_SPACE:
                if (!pc_settings_menu_confirm()) cur_page = PAGE_MAIN;
                return 1;
            case SDLK_ESCAPE:
                if (!pc_settings_menu_cancel()) cur_page = PAGE_MAIN;
                return 1;
            default: return 1;
        }
    }

    /* Pages owned here (Main, Quit-confirm). */
    int item_count = (cur_page == PAGE_MAIN) ? MAIN_ITEM_COUNT : CONFIRM_ITEM_COUNT;
    int* sel       = (cur_page == PAGE_MAIN) ? &main_sel : &confirm_sel;

    switch (k) {
        case SDLK_UP:
        case SDLK_w:
        case SDLK_LEFT:
        case SDLK_a:
            *sel = (*sel + item_count - 1) % item_count;
            return 1;
        case SDLK_DOWN:
        case SDLK_s:
        case SDLK_RIGHT:
        case SDLK_d:
            *sel = (*sel + 1) % item_count;
            return 1;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
        case SDLK_SPACE:
            if (cur_page == PAGE_MAIN)            main_activate();
            else if (cur_page == PAGE_CONFIRM_QUIT) confirm_activate();
            return 1;
        case SDLK_ESCAPE:
            if (cur_page == PAGE_CONFIRM_QUIT) cur_page = PAGE_MAIN;
            else                                pc_pause_menu_toggle();
            return 1;
        default:
            return 1; /* swallow all keys while paused */
    }
}

/* Drawing */

/* TODO: Merge with settings dim later */
static void draw_dim_rect(GRAPH* graph, int alpha) {
    Gfx* gfx;
    OPEN_DISP(graph);
    gfx = NOW_FONT_DISP;
    gDPNoOpTag(gfx++, PC_NOOP_WIDESCREEN_STRETCH);
    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
        G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT |
        G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP |
        G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
        G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, alpha);
    gfx = gfx_gSPTextureRectangle1(gfx,
        0, 0, 320 << 2, 240 << 2, 0, 0, 0, 0, 0);
    gDPPipeSync(gfx++);
    gDPNoOpTag(gfx++, PC_NOOP_WIDESCREEN_STRETCH_OFF);
    SET_FONT_DISP(gfx);
    CLOSE_DISP(graph);
}

/* Selected option gets scaled up */
#define PC_MENU_SCALE_SELECTED 1.15f

static void draw_centered_text(struct game_s* game, const char* s,
                               f32 y, int r, int g, int b, int a, f32 scale) {
    f32 w = (f32)pc_text_width(s) * scale;
    f32 x = (SCREEN_WIDTH_F - w) * 0.5f;
    pc_text_draw(game, s, x, y, r, g, b, a, scale);
}

static void draw_left_text(struct game_s* game, const char* s,
                           f32 x, f32 y, int r, int g, int b, int a,
                           f32 scale) {
    pc_text_draw(game, s, x, y, r, g, b, a, scale);
}

static void row_colors(int selected, int* r, int* g, int* b, int* a) {
    if (selected) { *r = 255; *g = 235; *b = 120; *a = 255; }
    else          { *r = 200; *g = 200; *b = 200; *a = 200; }
}

static void draw_main_page(struct game_s* game) {
    static const char* items[MAIN_ITEM_COUNT] = { "Resume", "Settings", "Quit Game" };

    draw_centered_text(game, "- Paused -", 80.0f, 255, 255, 255, 255, 1.0f);

    f32 y = 110.0f;
    f32 line_h = 18.0f;
    for (int i = 0; i < MAIN_ITEM_COUNT; i++) {
        int r, g, b, a;
        int selected = (i == main_sel);
        row_colors(selected, &r, &g, &b, &a);
        draw_centered_text(game, items[i], y + i * line_h, r, g, b, a,
                           selected ? PC_MENU_SCALE_SELECTED : 1.0f);
    }
}

static void draw_confirm_page(struct game_s* game) {
    int r, g, b, a;

    draw_centered_text(game, "- Quit Game -", 80.0f, 255, 255, 255, 255, 1.0f);
    draw_centered_text(game, "Are you sure you want to quit?",
                       115.0f, 230, 230, 230, 255, 1.0f);

    f32 y = 150.0f;
    f32 gap = 70.0f;
    int lw_no = pc_text_width("No");
    f32 cx = SCREEN_WIDTH_F * 0.5f;
    f32 no_x  = cx - gap - (f32)lw_no;
    f32 yes_x = cx + gap;

    row_colors(confirm_sel == 0, &r, &g, &b, &a);
    draw_left_text(game, "No",  no_x,  y, r, g, b, a,
                   confirm_sel == 0 ? PC_MENU_SCALE_SELECTED : 1.0f);
    row_colors(confirm_sel == 1, &r, &g, &b, &a);
    draw_left_text(game, "Yes", yes_x, y, r, g, b, a,
                   confirm_sel == 1 ? PC_MENU_SCALE_SELECTED : 1.0f);
}

void pc_pause_menu_draw(struct game_s* game) {
    if (!g_pc_paused || game == NULL || game->graph == NULL) return;

    /* Load the font ortho projection + identity modelview for the overlay.
     * Without this, whatever projection the scene ended its frame with
     * (e.g. the inventory's pillarbox/perspective projection) would still
     * be active and our screen-space quads would render skewed. */
    mFont_SetMatrix(game->graph, mFont_MODE_FONT);
    pc_settings_menu_tick();

    if (cur_page == PAGE_SETTINGS) {
        /* Settings module owns its own dim backdrop. Will fix/improve later. */
        pc_settings_menu_draw(game, /*with_dim_backdrop=*/1);
        /* The user may have closed it from inside (Back). */
        if (!pc_settings_menu_active()) cur_page = PAGE_MAIN;
    } else {
        draw_dim_rect(game->graph, 180);
        if (cur_page == PAGE_MAIN)              draw_main_page(game);
        else if (cur_page == PAGE_CONFIRM_QUIT) draw_confirm_page(game);
    }

    mFont_UnSetMatrix(game->graph, mFont_MODE_FONT);
}
