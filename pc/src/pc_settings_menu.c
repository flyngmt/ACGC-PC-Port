#include "pc_settings_menu.h"
#include "pc_settings.h"
#include "pc_text_draw.h"

#include "graph.h"
#include "m_font.h"
#include "m_rcp.h"
#include "main.h" /* SCREEN_WIDTH_F */

#include <stdio.h>
#include <string.h>

/* --- Item IDs (stable across tabs — used by the dispatch switches) --- */
enum {
    ITEM_DISPLAY,
    ITEM_VSYNC,
    ITEM_MSAA,
    ITEM_RES,
    ITEM_TEXTURES,
    ITEM_RESETTI,
    ITEM_NES_ASPECT,
    ITEM_MASTER_VOLUME,
};

/* Per-item static metadata. restart=1 appends " *" and folds into the
 * "requires restart" hint at the bottom of the page. */
typedef struct {
    const char* label;
    int         id;
    int         restart;
} Item;

static const Item tab_video_items[] = {
    { "Display",    ITEM_DISPLAY,  0 },
    { "VSync",      ITEM_VSYNC,    0 },
    { "MSAA",       ITEM_MSAA,     1 },
    { "Resolution", ITEM_RES,      0 },
    { "Textures",   ITEM_TEXTURES, 1 },
};

static const Item tab_gameplay_items[] = {
    { "Resetti",    ITEM_RESETTI,    0 },
    { "NES aspect", ITEM_NES_ASPECT, 0 },
};

static const Item tab_audio_items[] = {
    { "Master volume", ITEM_MASTER_VOLUME, 0 },
};

typedef struct {
    const char* name;
    const Item* items;
    int         count;
} Tab;

#define TAB_ITEMS(a) (a), (int)(sizeof(a) / sizeof((a)[0]))
static const Tab s_tabs[] = {
    { "Video",    TAB_ITEMS(tab_video_items) },
    { "Audio",    TAB_ITEMS(tab_audio_items) },
    { "Gameplay", TAB_ITEMS(tab_gameplay_items) },
};
#define TAB_COUNT ((int)(sizeof(s_tabs) / sizeof(s_tabs[0])))

/* --- Sub-pages --- */
typedef enum {
    SUB_SETTINGS = 0,
    SUB_CONFIRM_RES = 1,
    SUB_CONFIRM_BACK = 2,
} SubPage;

static int     s_active = 0;
static SubPage s_sub    = SUB_SETTINGS;
static int     s_tab    = 0;
static int     s_sel    = -1; /* start on the tab row */

/* Pending edits — only committed to g_pc_settings on Apply. */
static PCSettings s_pending;
static int        s_pending_dirty = 0;

/* Resolution-change confirmation state. */
#define RES_CONFIRM_MS 15000u
static int    s_res_old_w = 0;
static int    s_res_old_h = 0;
static Uint32 s_res_deadline = 0;
static int    s_res_sel = 1;

/* Back-confirm state (Discard vs Keep editing when Back hit while dirty). */
static int    s_back_sel = 0; /* 0 = Keep editing (safe default), 1 = Discard */

/* Startup snapshot + restart-required flag. Some settings (MSAA, texture
 * pack preload mode) only take effect on process restart. More might appear.*/
static PCSettings s_startup;
static int        s_startup_captured = 0;
static int        s_pending_restart = 0;

/* --- Dirty + helpers --- */

static void recompute_dirty(void) {
    s_pending_dirty =
        (s_pending.fullscreen       != g_pc_settings.fullscreen) ||
        (s_pending.vsync            != g_pc_settings.vsync) ||
        (s_pending.msaa             != g_pc_settings.msaa) ||
        (s_pending.window_width     != g_pc_settings.window_width) ||
        (s_pending.window_height    != g_pc_settings.window_height) ||
        (s_pending.preload_textures != g_pc_settings.preload_textures) ||
        (s_pending.disable_resetti  != g_pc_settings.disable_resetti) ||
        (s_pending.nes_aspect       != g_pc_settings.nes_aspect) ||
        (s_pending.master_volume    != g_pc_settings.master_volume);
}

static void snapshot(void) {
    s_pending = g_pc_settings;
    s_pending_dirty = 0;
}

/* Per-item dispatch: cycle, format, changed. Add cases here when a
 * new setting row is added to any tab. */

static void item_cycle(int id, int dir) {
    switch (id) {
        case ITEM_DISPLAY: {
            int v = s_pending.fullscreen + (dir > 0 ? 1 : 2);
            s_pending.fullscreen = v % 3;
        } break;
        case ITEM_VSYNC:
            s_pending.vsync = !s_pending.vsync;
            break;
        case ITEM_MSAA: {
            static const int steps[] = { 0, 2, 4, 8 };
            int idx = 0;
            for (int i = 0; i < 4; i++) if (s_pending.msaa == steps[i]) { idx = i; break; }
            idx = (idx + (dir > 0 ? 1 : 3)) % 4;
            s_pending.msaa = steps[idx];
        } break;
        case ITEM_RES:
            pc_settings_cycle_resolution(&s_pending.window_width, &s_pending.window_height, dir);
            break;
        case ITEM_TEXTURES: {
            int v = s_pending.preload_textures + (dir > 0 ? 1 : -1);
            if (v < 0) v = 2;
            if (v > 2) v = 0;
            s_pending.preload_textures = v;
        } break;
        case ITEM_RESETTI:
            s_pending.disable_resetti = !s_pending.disable_resetti;
            break;
        case ITEM_NES_ASPECT:
            s_pending.nes_aspect = !s_pending.nes_aspect;
            break;
        case ITEM_MASTER_VOLUME: {
            int v = s_pending.master_volume + (dir > 0 ? 10 : -10);
            if (v < 0)   v = 0;
            if (v > 100) v = 100;
            s_pending.master_volume = v;
        } break;
    }
    recompute_dirty();
}

static void item_format(int id, char* buf, size_t n) {
    switch (id) {
        case ITEM_DISPLAY:
            snprintf(buf, n, "%s",
                s_pending.fullscreen == 0 ? "< Windowed >" :
                s_pending.fullscreen == 1 ? "< Fullscreen >" :
                                            "< Borderless >");
            break;
        case ITEM_VSYNC:
            snprintf(buf, n, "%s", s_pending.vsync ? "< On >" : "< Off >");
            break;
        case ITEM_MSAA:
            if (s_pending.msaa > 0) snprintf(buf, n, "< %dx >", s_pending.msaa);
            else                    snprintf(buf, n, "< Off >");
            break;
        case ITEM_RES:
            snprintf(buf, n, "< %dx%d >", s_pending.window_width, s_pending.window_height);
            break;
        case ITEM_TEXTURES:
            snprintf(buf, n, "%s",
                s_pending.preload_textures == 0 ? "< On Demand >" :
                s_pending.preload_textures == 1 ? "< Preload >"   :
                                                  "< Preload&Cache >");
            break;
        case ITEM_RESETTI:
            /* disable_resetti flips the polarity — show the user-facing side. */
            snprintf(buf, n, "%s", s_pending.disable_resetti ? "< Disabled >" : "< Enabled >");
            break;
        case ITEM_NES_ASPECT:
            snprintf(buf, n, "%s", s_pending.nes_aspect ? "< 4:3 >" : "< Stretch >");
            break;
        case ITEM_MASTER_VOLUME:
            snprintf(buf, n, "< %d%% >", s_pending.master_volume);
            break;
        default:
            buf[0] = '\0';
            break;
    }
}

static int item_changed(int id) {
    switch (id) {
        case ITEM_DISPLAY:    return s_pending.fullscreen       != g_pc_settings.fullscreen;
        case ITEM_VSYNC:      return s_pending.vsync            != g_pc_settings.vsync;
        case ITEM_MSAA:       return s_pending.msaa             != g_pc_settings.msaa;
        case ITEM_RES:        return (s_pending.window_width  != g_pc_settings.window_width) ||
                                     (s_pending.window_height != g_pc_settings.window_height);
        case ITEM_TEXTURES:   return s_pending.preload_textures != g_pc_settings.preload_textures;
        case ITEM_RESETTI:    return s_pending.disable_resetti  != g_pc_settings.disable_resetti;
        case ITEM_NES_ASPECT:    return s_pending.nes_aspect    != g_pc_settings.nes_aspect;
        case ITEM_MASTER_VOLUME: return s_pending.master_volume != g_pc_settings.master_volume;
    }
    return 0;
}

/* For items flagged restart=1. Does the live g_pc_settings value differ
 * from what the process booted with? Used after Apply to decide whether
 * the "restart required" banner should show. */
static int item_differs_from_startup(int id) {
    switch (id) {
        case ITEM_MSAA:     return g_pc_settings.msaa             != s_startup.msaa;
        case ITEM_TEXTURES: return g_pc_settings.preload_textures != s_startup.preload_textures;
    }
    return 0;
}

static void recompute_restart_needed(void) {
    s_pending_restart = 0;
    for (int t = 0; t < TAB_COUNT; t++) {
        const Tab* tab = &s_tabs[t];
        for (int i = 0; i < tab->count; i++) {
            if (tab->items[i].restart && item_differs_from_startup(tab->items[i].id)) {
                s_pending_restart = 1;
                return;
            }
        }
    }
}

/* --- Nav helpers --- */

static int cur_item_count(void) { return s_tabs[s_tab].count; }
static int idx_apply(void)      { return cur_item_count(); }
static int idx_back(void)       { return cur_item_count() + 1; }
static int idx_last(void)       { return cur_item_count() + 1; }

/* --- Apply / res-confirm finalisers --- */

static void res_confirm_keep(void) {
    pc_settings_save();
    printf("[SETTINGS] resolution kept: %dx%d\n",
           g_pc_settings.window_width, g_pc_settings.window_height);
}

static void res_confirm_revert(void) {
    g_pc_settings.window_width  = s_res_old_w;
    g_pc_settings.window_height = s_res_old_h;
    s_pending.window_width      = s_res_old_w;
    s_pending.window_height     = s_res_old_h;
    pc_settings_apply();
    pc_settings_save();
    recompute_dirty();
    printf("[SETTINGS] resolution reverted to %dx%d\n", s_res_old_w, s_res_old_h);
}

static void res_confirm_finish(void) {
    if (s_res_sel == 0) res_confirm_keep();
    else                res_confirm_revert();
    s_res_deadline = 0;
    s_sub = SUB_SETTINGS;
}

static void apply_pending(void) {
    if (!s_pending_dirty) return;

    int res_changed = (s_pending.window_width  != g_pc_settings.window_width) ||
                      (s_pending.window_height != g_pc_settings.window_height);
    if (res_changed) {
        s_res_old_w = g_pc_settings.window_width;
        s_res_old_h = g_pc_settings.window_height;
    }

    g_pc_settings = s_pending;
    pc_settings_apply();
    s_pending_dirty = 0;
    recompute_restart_needed();

    if (res_changed) {
        s_sub = SUB_CONFIRM_RES;
        s_res_sel = 1;
        s_res_deadline = SDL_GetTicks() + RES_CONFIRM_MS;
        printf("[SETTINGS] resolution changed, awaiting confirmation (15s)\n");
    } else {
        pc_settings_save();
        printf("[SETTINGS] applied\n");
    }
}

/* =========================================================================
 * Public API
 * ========================================================================= */

void pc_settings_menu_enter(void) {
    /* First-time entry captures what the process actually booted with.
     * Anything that changes from here and can't live-apply gets flagged
     * as "restart required". */
    if (!s_startup_captured) {
        s_startup = g_pc_settings;
        s_startup_captured = 1;
    }
    snapshot();
    s_tab = 0;
    s_sel = -1;           /* start cursor on the tab row */
    s_sub = SUB_SETTINGS;
    s_res_deadline = 0;
    s_active = 1;
}

int pc_settings_menu_active(void) {
    return s_active;
}

/* --- Navigation --- */

int pc_settings_menu_nav_up(void) {
    if (!s_active) return 0;
    if (s_sub != SUB_SETTINGS) return 1;
    /* Clamp at the top — no wrap. */
    if (s_sel == 0)      s_sel = -1;            /* first item → tab row */
    else if (s_sel > 0)  s_sel--;
    return 1;
}

int pc_settings_menu_nav_down(void) {
    if (!s_active) return 0;
    if (s_sub != SUB_SETTINGS) return 1;
    /* Clamp at the bottom — no wrap. */
    if (s_sel == -1)             s_sel = 0;     /* tab row → first item */
    else if (s_sel < idx_last()) s_sel++;
    return 1;
}

int pc_settings_menu_nav_left(void) {
    if (!s_active) return 0;
    if (s_sub == SUB_CONFIRM_RES) {
        s_res_sel = (s_res_sel + 1) % 2;
        return 1;
    }
    if (s_sub == SUB_CONFIRM_BACK) {
        s_back_sel = (s_back_sel + 1) % 2;
        return 1;
    }
    if (s_sel == -1) {
        /* Clamp at the first tab — no wrap. */
        if (s_tab > 0) s_tab--;
    } else if (s_sel < cur_item_count()) {
        item_cycle(s_tabs[s_tab].items[s_sel].id, -1);
    }
    return 1;
}

int pc_settings_menu_nav_right(void) {
    if (!s_active) return 0;
    if (s_sub == SUB_CONFIRM_RES) {
        s_res_sel = (s_res_sel + 1) % 2;
        return 1;
    }
    if (s_sub == SUB_CONFIRM_BACK) {
        s_back_sel = (s_back_sel + 1) % 2;
        return 1;
    }
    if (s_sel == -1) {
        /* Clamp at the last tab — no wrap. */
        if (s_tab < TAB_COUNT - 1) s_tab++;
    } else if (s_sel < cur_item_count()) {
        item_cycle(s_tabs[s_tab].items[s_sel].id, +1);
    }
    return 1;
}

int pc_settings_menu_confirm(void) {
    if (!s_active) return 0;
    if (s_sub == SUB_CONFIRM_RES) {
        res_confirm_finish();
        return 1;
    }
    if (s_sub == SUB_CONFIRM_BACK) {
        if (s_back_sel == 1) {
            /* Discard — close the menu; pending edits drop on the floor. */
            s_active = 0;
            return 0;
        }
        s_sub = SUB_SETTINGS;
        return 1;
    }
    if (s_sel == -1) {
        /* Confirm on the tab row — just hop into the first item. */
        s_sel = 0;
    } else if (s_sel < cur_item_count()) {
        item_cycle(s_tabs[s_tab].items[s_sel].id, +1);
    } else if (s_sel == idx_apply()) {
        apply_pending();
    } else if (s_sel == idx_back()) {
        if (s_pending_dirty) {
            s_sub = SUB_CONFIRM_BACK;
            s_back_sel = 0;
            return 1;
        }
        s_active = 0;
        return 0;
    }
    return 1;
}

int pc_settings_menu_cancel(void) {
    if (!s_active) return 0;
    if (s_sub == SUB_CONFIRM_RES) {
        s_res_sel = 1; /* safer default on Esc/B */
        res_confirm_finish();
        return 1;
    }
    if (s_sub == SUB_CONFIRM_BACK) {
        /* Esc = cancel the confirm — snap back to the settings page. */
        s_sub = SUB_SETTINGS;
        return 1;
    }
    if (s_pending_dirty) {
        s_sub = SUB_CONFIRM_BACK;
        s_back_sel = 0;
        return 1;
    }
    s_active = 0;
    return 0;
}

void pc_settings_menu_tick(void) {
    if (!s_active) return;
    if (s_sub == SUB_CONFIRM_RES && s_res_deadline != 0) {
        if (SDL_GetTicks() >= s_res_deadline) {
            s_res_sel = 1;
            res_confirm_finish();
        }
    }
}

/* =========================================================================
 * Drawing
 * ========================================================================= */

static void draw_dim_rect(GRAPH* graph) {
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
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 180);
    gfx = gfx_gSPTextureRectangle1(gfx,
        0, 0, 320 << 2, 240 << 2, 0, 0, 0, 0, 0);
    gDPPipeSync(gfx++);
    gDPNoOpTag(gfx++, PC_NOOP_WIDESCREEN_STRETCH_OFF);
    SET_FONT_DISP(gfx);
    CLOSE_DISP(graph);
}

/* Selected row gets a small scale bump — the font atlas has no bold
 * variant, so this is how we highlight the cursor position. */
#define SETTINGS_SCALE_SELECTED 1.15f

static void draw_centered(struct game_s* game, const char* s, f32 y,
                          int r, int g, int b, int a, f32 scale) {
    f32 w = (f32)pc_text_width(s) * scale;
    f32 x = (SCREEN_WIDTH_F - w) * 0.5f;
    pc_text_draw(game, s, x, y, r, g, b, a, scale);
}

static void draw_left(struct game_s* game, const char* s, f32 x, f32 y,
                      int r, int g, int b, int a, f32 scale) {
    pc_text_draw(game, s, x, y, r, g, b, a, scale);
}

static void row_colors(int selected, int* r, int* g, int* b, int* a) {
    if (selected) { *r = 255; *g = 235; *b = 120; *a = 255; }
    else          { *r = 200; *g = 200; *b = 200; *a = 200; }
}

static void value_colors(int selected, int changed, int* r, int* g, int* b, int* a) {
    if (changed) {
        *r = 255; *g = 215; *b = 90;
        *a = selected ? 255 : 200;
    } else {
        row_colors(selected, r, g, b, a);
    }
}

/* Tab row rendering: tabs are evenly spaced around the screen centre.
 * Active tab is highlighted; when the nav cursor is on the tab row, the
 * active tab also gets the bracketed "> name <" decoration. */
static void draw_tab_row(struct game_s* game, f32 y) {
    int on_tab_row = (s_sel == -1);

    /* Pre-measure widths and total horizontal extent so we can centre. */
    int widths[TAB_COUNT];
    int total = 0;
    const int gap_px = 18;
    for (int t = 0; t < TAB_COUNT; t++) {
        widths[t] = pc_text_width(s_tabs[t].name);
        total += widths[t];
    }
    total += gap_px * (TAB_COUNT - 1);

    f32 x = (SCREEN_WIDTH_F - (f32)total) * 0.5f;
    for (int t = 0; t < TAB_COUNT; t++) {
        const char* name = s_tabs[t].name;
        int active = (t == s_tab);
        int r, g, b, a;
        if (active && on_tab_row) { r = 255; g = 235; b = 120; a = 255; }
        else if (active)          { r = 255; g = 255; b = 255; a = 230; }
        else                      { r = 160; g = 160; b = 160; a = 180; }

        /* Active tab + cursor-on-tab-row gets the full bump; active but
         * cursor-off-tab-row stays normal size (the white color already
         * marks it). Inactive tabs render normal too. */
        f32 s = (active && on_tab_row) ? SETTINGS_SCALE_SELECTED : 1.0f;
        pc_text_draw(game, name, x, y, r, g, b, a, s);
        x += (f32)widths[t] + (f32)gap_px;
    }
}

static void draw_settings_page(struct game_s* game) {
    char buf[64];
    int r, g, b, a;
    f32 lx = 70.0f;
    f32 vx = 200.0f;
    f32 y_tab = 50.0f;
    f32 y0    = 78.0f;
    f32 line_h = 16.0f;

    draw_centered(game, "- Settings -", 30.0f, 255, 255, 255, 255, 1.0f);
    draw_tab_row(game, y_tab);

    const Tab* tab = &s_tabs[s_tab];
    for (int i = 0; i < tab->count; i++) {
        const Item* it = &tab->items[i];
        int selected = (s_sel == i);

        char value_buf[64];
        item_format(it->id, value_buf, sizeof(value_buf));

        int changed = item_changed(it->id);
        f32 y = y0 + i * line_h;

        f32 s = selected ? SETTINGS_SCALE_SELECTED : 1.0f;
        row_colors(selected, &r, &g, &b, &a);
        draw_left(game, it->label, lx, y, r, g, b, a, s);
        value_colors(selected, changed, &r, &g, &b, &a);
        draw_left(game, value_buf, vx, y, r, g, b, a, s);
    }

    /* Anchor Apply/Back to the tallest tab's footprint so they don't
     * shift up when the user moves to a tab with fewer items. */
    int max_items = 0;
    for (int t = 0; t < TAB_COUNT; t++) {
        if (s_tabs[t].count > max_items) max_items = s_tabs[t].count;
    }

    /* Apply — coloured green when there's something to apply. */
    f32 apy = y0 + max_items * line_h + 10.0f;
    int sel_apply = (s_sel == idx_apply());
    if (sel_apply && s_pending_dirty) {
        r = 120; g = 255; b = 140; a = 255;
    } else if (sel_apply) {
        r = 160; g = 160; b = 160; a = 220;
    } else if (s_pending_dirty) {
        r = 120; g = 220; b = 140; a = 200;
    } else {
        r = 120; g = 120; b = 120; a = 160;
    }
    draw_centered(game, "Apply", apy, r, g, b, a,
                  sel_apply ? SETTINGS_SCALE_SELECTED : 1.0f);

    /* Back */
    f32 bky = apy + line_h;
    int sel_back = (s_sel == idx_back());
    row_colors(sel_back, &r, &g, &b, &a);
    draw_centered(game, "Back", bky, r, g, b, a,
                  sel_back ? SETTINGS_SCALE_SELECTED : 1.0f);

    /* Persistent "restart required" banner. Stays up until the process
     * actually restarts — survives closing and re-opening the menu. Sits
     * below Back so it never competes with the row cursor. */
    if (s_pending_restart) {
        draw_centered(game, "Restart the game to apply all changes",
                      bky + line_h + 6.0f, 255, 195, 85, 230, 1.0f);
    }

    (void)buf;
    (void)bky;
}

static void draw_res_confirm_page(struct game_s* game) {
    int r, g, b, a;
    char buf[48];

    draw_centered(game, "- Keep this resolution? -", 70.0f, 255, 255, 255, 255, 1.0f);

    snprintf(buf, sizeof(buf), "%dx%d",
             g_pc_settings.window_width, g_pc_settings.window_height);
    draw_centered(game, buf, 95.0f, 230, 230, 230, 255, 1.0f);

    Uint32 now = SDL_GetTicks();
    Uint32 ms_left = (now < s_res_deadline) ? s_res_deadline - now : 0;
    int secs = (int)((ms_left + 999) / 1000);
    snprintf(buf, sizeof(buf), "Reverting in %d...", secs);
    draw_centered(game, buf, 125.0f, 230, 200, 110, 255, 1.0f);

    f32 y = 160.0f;
    f32 gap = 70.0f;
    int lw_keep = pc_text_width("Keep");
    f32 cx = SCREEN_WIDTH_F * 0.5f;
    f32 keep_x   = cx - gap - (f32)lw_keep;
    f32 revert_x = cx + gap;

    row_colors(s_res_sel == 0, &r, &g, &b, &a);
    draw_left(game, "Keep",   keep_x,   y, r, g, b, a,
              s_res_sel == 0 ? SETTINGS_SCALE_SELECTED : 1.0f);
    row_colors(s_res_sel == 1, &r, &g, &b, &a);
    draw_left(game, "Revert", revert_x, y, r, g, b, a,
              s_res_sel == 1 ? SETTINGS_SCALE_SELECTED : 1.0f);
}

/* Discard-changes confirmation shown when the user tries to Back out
 * while s_pending_dirty. Mirrors the res-confirm layout but with no
 * auto-timer (the user must pick). */
static void draw_back_confirm_page(struct game_s* game) {
    int r, g, b, a;

    draw_centered(game, "- Discard changes? -", 80.0f, 255, 255, 255, 255, 1.0f);
    draw_centered(game, "You have unapplied changes.",
                  115.0f, 230, 230, 230, 255, 1.0f);

    f32 y = 160.0f;
    f32 gap = 70.0f;
    int lw_keep = pc_text_width("Keep editing");
    f32 cx = SCREEN_WIDTH_F * 0.5f;
    f32 keep_x    = cx - gap - (f32)lw_keep;
    f32 discard_x = cx + gap;

    row_colors(s_back_sel == 0, &r, &g, &b, &a);
    draw_left(game, "Keep editing", keep_x,    y, r, g, b, a,
              s_back_sel == 0 ? SETTINGS_SCALE_SELECTED : 1.0f);
    row_colors(s_back_sel == 1, &r, &g, &b, &a);
    draw_left(game, "Discard",      discard_x, y, r, g, b, a,
              s_back_sel == 1 ? SETTINGS_SCALE_SELECTED : 1.0f);
}

void pc_settings_menu_draw(struct game_s* game, int with_dim_backdrop) {
    if (!s_active || !game || !game->graph) return;
    if (with_dim_backdrop) draw_dim_rect(game->graph);
    if (s_sub == SUB_SETTINGS)          draw_settings_page(game);
    else if (s_sub == SUB_CONFIRM_RES)  draw_res_confirm_page(game);
    else                                draw_back_confirm_page(game);
}
