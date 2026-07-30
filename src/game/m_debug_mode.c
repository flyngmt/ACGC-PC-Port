#include "m_debug_mode.h"

#include "libu64/gfxprint.h"
#include "m_lib.h"
#include "m_malloc.h"
#include "THA_GA.h"
#include "gfxalloc.h"
#include "graph.h"
#include "game.h"
#include "m_debug_hayakawa.h"
#include "m_fuusen.h"
#include "m_field_info.h"
#include "m_private.h"
#include "m_quest.h"
#include "m_event.h"
#include "m_msg.h"
#include "m_shop.h"
#include "zurumode.h"
#include "m_nmibuf.h"
#include "m_room_type.h"
#include "m_npc.h"
#include "m_field_assessment.h"
#include "m_all_grow.h"
#include "m_card.h"
#include "m_flashrom.h"
#include "dolphin/dvd.h"
#include "jsyswrap.h"
#include "boot.h"
#include "m_common_data.h"

#define DEBUG_MODE_PRINT_BUF_COUNT 6
#define DEBUG_MODE_PRINT_OUTPUT_X 26
#define DEBUG_MODE_PRINT_OUTPUT_Y 20
#define DEBUG_MODE_PRINT_OUTPUT_Y_LAST (DEBUG_MODE_PRINT_OUTPUT_Y + DEBUG_MODE_PRINT_BUF_COUNT)

#define DEBUG_MODE_PRINT_FLAG 1
#define DEBUG_MODE_PRINT2_FLAG 2

static int debug_print_flg;
static s16 debug_print2_count;

typedef struct debug_mode_print_buffer_s {
    u8 color;
    u8 msg[11];
} debug_mode_print_buf_t;

static debug_mode_print_buf_t debug_print_buffer[DEBUG_MODE_PRINT_BUF_COUNT] = {
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
    {
        DEBUG_PRINT_COLOR_BLACK,
        "          \0",
    },
};

void Debug_Print_reset() {
    debug_print_flg = 0;
}

void Debug_Print_write() {
    debug_print2_count = 0;
}

static void Debug_Print_output(gfxprint_t* gfxprint) {
    static rgba_t print_color[8] = {
        { 0, 0, 0, 64 },       /* Black */
        { 0, 0, 255, 64 },     /* Blue */
        { 255, 0, 0, 64 },     /* Red */
        { 255, 0, 255, 64 },   /* Magenta */
        { 0, 255, 0, 64 },     /* Green */
        { 0, 255, 255, 64 },   /* Cyan */
        { 255, 255, 0, 64 },   /* Yellow */
        { 255, 255, 255, 64 }, /* White */
    };

    debug_mode_print_buf_t* print_buf = debug_print_buffer;
    int y;

    for (y = DEBUG_MODE_PRINT_OUTPUT_Y; y < DEBUG_MODE_PRINT_OUTPUT_Y_LAST;) {
        rgba_t* color;
        gfxprint_locate8x8(gfxprint, DEBUG_MODE_PRINT_OUTPUT_X, y);
        color = print_color + print_buf->color;
        gfxprint_color(gfxprint, color->r, color->g, color->b, color->a);
        gfxprint_printf(gfxprint, "%s", print_buf->msg);

        y++;
        print_buf->msg[0] = '\0';
        print_buf++;
    }
}

#define DEBUG_MODE_PRINT2_BUF_COUNT 80

typedef struct debug_mode_print2_buffer_s {
    u8 x;
    u8 y;
    u8 color;
    u8 msg[41];
} debug_mode_print2_buf_t;

static debug_mode_print2_buf_t debug_print2_buffer[DEBUG_MODE_PRINT2_BUF_COUNT];

static void Debug_Print2_output(gfxprint_t* gfxprint) {
    static rgba_t print_color[8] = {
        { 255, 255, 32, 192 },  /* Yellow */
        { 255, 150, 128, 192 }, /* Pink */
        { 128, 96, 0, 64 },     /* Brown */
        { 192, 128, 16, 128 },  /* Dark Orange */
        { 255, 192, 32, 128 },  /* Light Orange */
        { 230, 230, 220, 64 },  /* White/Gray */
        { 128, 150, 255, 128 }, /* Lilac */
        { 128, 255, 32, 128 }   /* Lime green */
    };

    int i;
    for (i = 0; i < debug_print2_count; i++) {
        gfxprint_color(gfxprint, print_color[debug_print2_buffer[i].color].r,
                       print_color[debug_print2_buffer[i].color].g, print_color[debug_print2_buffer[i].color].b,
                       print_color[debug_print2_buffer[i].color].a);

        gfxprint_locate8x8(gfxprint, debug_print2_buffer[i].x, debug_print2_buffer[i].y);
        gfxprint_printf(gfxprint, "%s", debug_print2_buffer[i].msg);
    }
}

#define PAD_BUTTON_IS_DOWN(buttons, button) (((int)(buttons) | (~(int)(button))) == -1)

static int Debug_console(pad_t* pad) {
    static f32 console_scroll;
    static f32 console_offset_x;
    static f32 font_scale_x[] = {
        1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f,
    };
    static f32 font_scale_y[] = {
        1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f,
    };

    void* sys_console = JC_JFWSystem_getSystemConsole();

    if (sys_console != NULL) {
        /* Toggle console visiblity when Z button is released */
        if (PAD_BUTTON_IS_DOWN(pad->on.button, BUTTON_Z) && (pad->now.button & (~BUTTON_Z)) == 0) {
            JC_JUTConsole_setVisible(sys_console, !JC_JUTConsole_isVisible(sys_console));
        }

        if (JC_JUTConsole_isVisible(sys_console)) {
            int scroll_x, scroll_y;
            f32 log_stick_x = (f32)pad->off.stick_x / 60.0f;
            f32 log_stick_y = (f32)pad->off.stick_y / 60.0f;

            /* B button clears console */
            if (PAD_BUTTON_IS_DOWN(pad->on.button, BUTTON_B)) {
                JC_JUTConsole_clear(sys_console);
            }

            /* L button to scroll */
            if (PAD_BUTTON_IS_DOWN(pad->now.button, BUTTON_L)) {
                console_scroll -= log_stick_y;

                if (console_scroll > 1.0f) {
                    scroll_y = (int)console_scroll;
                } else if (console_scroll < -1.0f) {
                    scroll_y = -(int)-console_scroll; /* nice double neg */
                } else {
                    scroll_y = 0;
                }

                if (scroll_y != 0) {
                    console_scroll -= scroll_y;
                    JC_JUTConsole_scroll(sys_console, scroll_y);
                }

                console_offset_x -= log_stick_x;
                if (console_offset_x > 1.0f) {
                    scroll_x = (int)console_offset_x;
                } else if (console_offset_x < -1.0f) {
                    scroll_x = -(int)-console_offset_x; /* nice double neg */
                } else {
                    scroll_x = 0;
                }

                if (scroll_x != 0) {
                    console_offset_x -= scroll_x;
                    JC_JUTConsole_setPosition(sys_console, scroll_x + JC_JUTConsole_getPositionX(sys_console), 42);
                }

                JW_JUTReport(30, 440, 1, "SCROLL：%3d %3d Output=%1x", JC_JUTConsole_getLineOffset(sys_console),
                             JC_JUTConsole_getPositionX(sys_console), JC_JUTConsole_getOutput(sys_console));
            }

            /* R button re-prints console */
            if (PAD_BUTTON_IS_DOWN(pad->on.button, BUTTON_R)) {
                JC_JUTConsole_dumpToTerminal(sys_console, -1); /* -1 is probably a define */
                JC_JUTConsole_setOutput(sys_console, 3);       /* Again, 3 is probably a define */
            }

            return TRUE;
        }
    }

    return FALSE;
}

static u32 draw_status = 0;
static u32 bg_draw_status = 0;
static u32 bg_draw_status2 = 0;
static u32 quest_draw_status = 0;
static u32 shop_draw_status = 0;
static u32 event_status = 0;
static u32 zelda_malloc_status = 0;
static u32 famicom_status = 0;
static u32 npc_draw_status = 0;
static u32 field_assessment_status = 0;

typedef struct debug_reg_keycombo_s {
    u16 held;    /* Previously held */
    u16 pressed; /* Pressed this frame */
} debug_reg_keycombo_t;

extern void Debug_mode_input(pad_t* pad) {
    int r_ofs = (-1 + debug_mode->mode + debug_mode->type * DEBUG_REG_GROUP) * DEBUG_REG_SIZE;

    if (famicom_status != 0 || Debug_console(pad) == 0) {
        u16 now_button = pad->now.button;
        int dpad = now_button & (BUTTON_DRIGHT | BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP);

        /* L + R held shows the disk info, copy date, and zurumode/appNMI buffer state */
        if (PAD_BUTTON_IS_DOWN(now_button, BUTTON_L) && PAD_BUTTON_IS_DOWN(now_button, BUTTON_R)) {
            DVDDiskID* diskid = DVDGetCurrentDiskID();
            if (diskid != NULL) {
                JW_JUTReport(50, 50, 1, "%.4s %.2s 0x%02x(%d)", diskid->gameName, diskid->company, diskid->gameVersion,
                             diskid->gameVersion);
            }

            if (boot_copyDate != NULL) {
                JW_JUTReport(320, 50, 1, "%.19s", boot_copyDate);
            }

            JW_JUTReport(50, 60, 1, "Z=%d Z2=%d ANB=%08x", zurumode_flag != 0, zurumode_flag >= 2, APPNMI_GETVAL());

            /* Additionally, pressing Z after L + R will print out each bit in debug appNMI buffer */
            if (PAD_BUTTON_IS_DOWN(pad->now.button, BUTTON_Z)) {
                int i;
                for (i = 0; i < 32; i++) {
                    JW_JUTReport(50 + i * 12, 70, 1, "%1x", (APPNMI_GETVAL() >> (31 - i)) & 1);
                }
            }
        }

        if (zurumode_flag >= 2 &&
            (PAD_BUTTON_IS_DOWN(pad->now.button, BUTTON_L) || PAD_BUTTON_IS_DOWN(pad->now.button, BUTTON_R) ||
             PAD_BUTTON_IS_DOWN(pad->now.button, BUTTON_START))) {
            /* Button combos to get to each register */
            static debug_reg_keycombo_t key_data[DEBUG_REG_MAX] = {
                { BUTTON_L, BUTTON_CUP },        /* REG */
                { BUTTON_L, BUTTON_CLEFT },      /* SREG */
                { BUTTON_L, BUTTON_CDOWN },      /* OREG */
                { BUTTON_L, BUTTON_A },          /* PREG */
                { BUTTON_R, BUTTON_CDOWN },      /* QREG */
                { BUTTON_L, BUTTON_CRIGHT },     /* MREG */
                { BUTTON_L, BUTTON_R },          /* SBREG */
                { BUTTON_L, BUTTON_DLEFT },      /* DREG */
                { BUTTON_L, BUTTON_DRIGHT },     /* UREG */
                { BUTTON_L, BUTTON_DUP },        /* IREG */
                { BUTTON_L, BUTTON_B },          /* ZREG */
                { BUTTON_L, BUTTON_Z },          /* CRV */
                { BUTTON_L, BUTTON_DDOWN },      /* NS1 */
                { BUTTON_R, BUTTON_A },          /* SND */
                { BUTTON_R, BUTTON_B },          /* XREG */
                { BUTTON_R, BUTTON_Z },          /* CRV2 */
                { BUTTON_R, BUTTON_L },          /* DEMOREG */
                { BUTTON_R, BUTTON_CUP },        /* TREG */
                { BUTTON_R, BUTTON_CRIGHT },     /* WREG */
                { BUTTON_R, BUTTON_DLEFT },      /* AREG */
                { BUTTON_R, BUTTON_CLEFT },      /* VREG */
                { BUTTON_R, BUTTON_START },      /* HREG */
                { BUTTON_L, BUTTON_START },      /* GREG */
                { BUTTON_R, BUTTON_DRIGHT },     /* mREG */
                { BUTTON_R, BUTTON_DUP },        /* nREG */
                { BUTTON_START, BUTTON_R },      /* BREG */
                { BUTTON_START, BUTTON_A },      /* DORO */
                { BUTTON_START, BUTTON_Y },      /* kREG */
                { BUTTON_START, BUTTON_CRIGHT }, /* BAK */
                { BUTTON_START, BUTTON_CLEFT },  /* PLAYERREG */
                { BUTTON_START, BUTTON_CDOWN },  /* NMREG */
                { BUTTON_START, BUTTON_L },      /* NIIREG */
                { BUTTON_START, BUTTON_Z },      /* GENREG */
                { BUTTON_START, BUTTON_CUP },    /* MYKREG */
                { BUTTON_START, BUTTON_DUP },    /* CAMREG */
                { BUTTON_START, BUTTON_DRIGHT }, /* SAKREG */
                { BUTTON_START, BUTTON_DLEFT },  /* TAKREG */
                { BUTTON_START, BUTTON_DDOWN }   /* PL2REG */
            };

            int i;

            for (i = 0; i < DEBUG_REG_MAX; i++) {
                if (PAD_BUTTON_IS_DOWN(pad->now.button, key_data[i].held) &&
                    PAD_BUTTON_IS_DOWN(pad->on.button, key_data[i].pressed)) {
                    break;
                }
            }

            if (i < DEBUG_REG_MAX) {
                if (i == debug_mode->type) {
                    /* Switch register group */
                    debug_mode->mode = (debug_mode->mode + 1) % (DEBUG_REG_GROUP + 1);
                } else {
                    /* Switch registers */
                    debug_mode->type = i;
                    debug_mode->mode = 0;
                }
            }
        } else {
            int increment;
            switch ((int)debug_mode->mode) {
                default:
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6: {
                    if (dpad == debug_mode->old_key) {
                        if (debug_mode->key_wait <= 0) {
                            debug_mode->key_wait = 1;
                        } else {
                            debug_mode->key_wait--;
                            dpad ^= debug_mode->old_key;
                        }
                    } else {
                        debug_mode->key_wait = 16;
                        debug_mode->old_key = dpad;
                    }

                    /**
                     * Register increment key combos:
                     *  - D-Pad Right: positive
                     *  - D-Pad Left: negative
                     *
                     * Increment modifiers (held)
                     *  - C-Stick Up: 0x1000
                     *  - C-Stick Down: 0x100
                     *  - A + B: 1000
                     *  - A: 100
                     *  - B: 10
                     *  - Default: 1
                     **/
                    if (dpad & BUTTON_DRIGHT) {
                        u16 btn = pad->now.button;
                        if (PAD_BUTTON_IS_DOWN(btn, BUTTON_CUP)) {
                            increment = 0x1000;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_CDOWN)) {
                            increment = 0x100;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_A | BUTTON_B)) {
                            increment = 1000;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_A)) {
                            increment = 100;
                        } else {
                            increment = 1;
                            if (PAD_BUTTON_IS_DOWN(btn, BUTTON_B)) {
                                increment = 10;
                            }
                        }
                    } else if (dpad & BUTTON_DLEFT) {
                        u16 btn = pad->now.button;
                        if (PAD_BUTTON_IS_DOWN(btn, BUTTON_CUP)) {
                            increment = -0x1000;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_CDOWN)) {
                            increment = -0x100;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_A | BUTTON_B)) {
                            increment = -1000;
                        }
                        /* lol the missed duplicated case */
                        else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_A | BUTTON_B)) {
                            increment = -1000;
                        } else if (PAD_BUTTON_IS_DOWN(btn, BUTTON_A)) {
                            increment = -100;
                        } else {
                            increment = -1;
                            if (PAD_BUTTON_IS_DOWN(btn, BUTTON_B)) {
                                increment = -10;
                            }
                        }
                    } else {
                        increment = 0;
                    }

                    /* Adjust selected register value */
                    debug_mode->r[debug_mode->input_r + r_ofs] += increment;

                    /* Adjust selected register index */
                    if (dpad & BUTTON_DUP) {
                        if (debug_mode->input_r <= 0) {
                            debug_mode->input_r = (DEBUG_REG_SIZE - 1);
                        } else {
                            debug_mode->input_r--;
                        }
                    } else if (dpad & BUTTON_DDOWN) {
                        if (debug_mode->input_r >= (DEBUG_REG_SIZE - 1)) {
                            debug_mode->input_r = 0;
                        } else {
                            debug_mode->input_r++;
                        }
                    }
                } break;
            }
        }

        /* Hayakawa debug functions controlled by previous controller */
        debug_hayakawa_move(pad - 1);

        /**
         * Summary of display toggle buttons
         *   A:
         *    - bg_draw_status
         *    - quest_draw_status
         *    - event_status (non-special)
         *    - draw_status
         *   D-Pad Left:
         *    - event_status (special)
         *   D-Pad Up:
         *    - shop_draw_status
         *   C-Stick Up
         *    - zelda_malloc_status
         *   D-Pad Down (zurumode 2 enabled):
         *    - famicom_status
         *   (missing: C-Stick Down, perhaps for bg_draw_status2)
         *   D-Pad Right:
         *    - npc_draw_status
         *   C-Stick Right:
         *    - field_assessment_status
         **/

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_A)) {
            bg_draw_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_A)) {
            quest_draw_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_A)) {
            event_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_DLEFT)) {
            event_status ^= 2;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_A)) {
            draw_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_DUP)) {
            shop_draw_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_CUP)) {
            zelda_malloc_status ^= 1;
        }

        if (zurumode_flag >= 2 && DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_DDOWN)) {
            famicom_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_DRIGHT)) {
            npc_draw_status ^= 1;
        }

        if (DEBUG_MODE_CHECK_TRIGGER_GAME(BUTTON_CRIGHT)) {
            field_assessment_status ^= 1;
        }
    }
}

static void Debug_mode_output_sub(gfxprint_t* gfxprint) {
    static u8 reg_name_data[38] = " SOPQMYDUIZCNKXcsiWAVHGmnBdkb*********";
    // clang-format off
    static char* long_reg_name_data[] = {
        "REG",
        "SREG",
        "OREG",
        "PREG",
        "QREG",
        "MREG",
        "SBREG",
        "DREG",
        "UREG",
        "IREG",
        "ZREG",
        "CRV",
        "NS1",
        "SND",
        "XREG",
        "CRV2",
        "DEMOREG",
        "TREG",
        "WREG",
        "AREG",
        "VREG",
        "HREG",
        "GREG",
        "mREG",
        "nREG",
        "BREG",
        "DORO",
        "kREG",
        "BAK",
        "PLAYERREG",
        "NMREG",
        "NIIREG",
        "GENREG",
        "MYKREG",
        "CAMREG",
        "SAKREG",
        "TAKREG",
        "PL2REG",
    };
    // clang-format on

    int i;
    int mode;
    int adj;
    int ofs;

    mode = (debug_mode->mode - 1);
    adj = mode * DEBUG_REG_SIZE;
    ofs = (mode + debug_mode->type * DEBUG_REG_GROUP) * DEBUG_REG_SIZE;

    gfxprint_color(gfxprint, 0, 128, 128, 128); /* Color -> xlu dark cyan */
    gfxprint_locate8x8(gfxprint, 3, 8);
    gfxprint_printf(gfxprint, "%c(%s)", reg_name_data[debug_mode->type], long_reg_name_data[debug_mode->type]);
    gfxprint_color(gfxprint, 0, 128, 128, 128); /* Reset color... back to dark cyan? */

    for (i = 0; i < DEBUG_REG_SIZE; i++) {
        if (i == debug_mode->input_r) {
            gfxprint_color(gfxprint, 0, 255, 255, 255); /* Color -> opaque cyan */
        }

        gfxprint_locate8x8(gfxprint, 3, i + 9);
        gfxprint_printf(gfxprint, "%02d%6d", i + adj, debug_mode->r[i + ofs]);

        if (i == debug_mode->input_r) {
            gfxprint_color(gfxprint, 0, 128, 128, 128); /* Color -> xlu dark cyan */
        }
    }
}

static void Debug_mode_zelda_malloc_info_output(gfxprint_t* gfxprint) {
    u32 max, free, alloc;
    u32 graph_alloc;

    if (zelda_MallocIsInitalized()) {
        graph_alloc = THA_GA_getFreeBytes(&gamePT->graph->polygon_opaque_thaga);
        zelda_GetFreeArena(&max, &free, &alloc);

        gfxprint_color(gfxprint, 200, 200, 250, 255); /* color -> opaque lilac */
        gfxprint_locate8x8(gfxprint, 3, 23);
        gfxprint_printf(gfxprint, "zelda_malloc ｻｲﾀﾞｲｱｷ%x", max);
        gfxprint_locate8x8(gfxprint, 3, 24);
        gfxprint_printf(gfxprint, "                  ｱｷ%x", free);
        gfxprint_locate8x8(gfxprint, 3, 25);
        gfxprint_printf(gfxprint, "graph_alloc ﾉｺﾘ     %x", graph_alloc);
    }
}

/* sizeof(haniwa_tempo_data) == 6 */
typedef struct {
    /* 0x00 */ TempoBeat_c Gt;
    /* 0x02 */ TempoBeat_c BS;
    /* 0x04 */ TempoBeat_c AS;
} haniwa_tempo_data;

static haniwa_tempo_data tempo_data[PLAYER_NUM] = {
    { { 0, 0 }, { 0, 0 }, { 0, 0 } }, /* House 0 */
    { { 0, 0 }, { 0, 0 }, { 0, 0 } }, /* House 1 */
    { { 0, 0 }, { 0, 0 }, { 0, 0 } }, /* House 2 */
    { { 0, 0 }, { 0, 0 }, { 0, 0 } }, /* House 3 */
};

static void DebugHaniwaTempo(gfxprint_t* gfxprint) {
    int i;
    for (i = 0; i < PLAYER_NUM; i++) {
        gfxprint_color(gfxprint, 250, 200, 200, 255);
        gfxprint_locate8x8(gfxprint, 3, 23 + i);
        gfxprint_printf(gfxprint, "S%d,%dGt%d,%dBS%d,%dAS%d,%d", Save_Get(homes[i].haniwa_tempo.tempo),
                        Save_Get(homes[i].haniwa_tempo.beat), tempo_data[i].Gt.tempo, tempo_data[i].Gt.beat,
                        tempo_data[i].BS.tempo, tempo_data[i].BS.beat, tempo_data[i].AS.tempo, tempo_data[i].AS.beat);
    }
}

#define GFXLIST_RESERVED_SIZE (int)(512 * sizeof(Gfx)) /* requires 0x1000 bytes, or 512 free Gfx */

extern void Debug_mode_output(GRAPH* graph) {
    static int glist_used_bytes;
    static int console_position_x;
    static int console_position_y;
    static int font_scale_select;

    Gfx* start_gfx;
    Gfx* last_gfx;
    int poly_free_bytes;
    int d_col_r;
    int d_col_g;
    gfxprint_t gfxprint;
    gfxprint_t* print_p = &gfxprint;

    debug_hayakawa_draw(graph);
    poly_free_bytes = THA_GA_getFreeBytes(&graph->polygon_opaque_thaga);
    if (poly_free_bytes >= glist_used_bytes + GFXLIST_RESERVED_SIZE) {
        Gfx* gfx;
        gfxprint_init(print_p);

        OPEN_DISP(graph);

        start_gfx = NOW_POLY_OPA_DISP;
        gfx = gfxopen(start_gfx);
        gSPDisplayList(NOW_OVERLAY_DISP++, gfx);

        gfxprint_open(print_p, gfx);

        if (debug_print_flg & DEBUG_MODE_PRINT2_FLAG) {
            Debug_Print2_output(print_p);
        }

        if (debug_mode->mode != 0) {
            Debug_mode_output_sub(print_p);
        }

        debug_print2_count = 0;

        if (debug_print_flg & DEBUG_MODE_PRINT_FLAG) {
            Debug_Print_output(print_p);
        }

        if (debug_mode->mode == 0) {
            fuusen_DEBUG_mode_flag = 1;

            if (bg_draw_status & 1) {
                mFI_PrintNowBGNum(print_p);
                mFI_PrintFgAttr(print_p);
                gfxprint_color(print_p, 200, 200, 250, 255); /* color -> lilac */
                gfxprint_locate8x8(print_p, 3, 9);
                gfxprint_printf(print_p, "%3d %3d", mPr_GetMoneyPower(), mPr_GetGoodsPower());
            }

            if (quest_draw_status & 1) {
                mQst_PrintQuestInfo(print_p);
            }

            if (event_status & 1) {
                mEv_debug_print4f(print_p);
            }

            if (event_status & 2) {
                mEv_sp_debug_print4f(print_p);
            }

            if (draw_status & 1) {
                mMsg_debug_draw(print_p);
            }

            if (zurumode_flag >= 2) {
                mItemDebug_ItemDebugMain();
                mItemDebug_ItemDebugDraw(print_p);
            }

            if (shop_draw_status & 1) {
                mSP_PrintNowShopSalesSum(print_p);
                DebugHaniwaTempo(print_p);
            }

            if (zelda_malloc_status & 1) {
                Debug_mode_zelda_malloc_info_output(print_p);
            }

            if (zurumode_flag >= 2 && (famicom_status & 1)) {
                mRmTp_DrawFamicomInfo(print_p);
                mRmTp_MakeFamicom_Fdebug();
            }

            d_col_g = APPNMI_RESETEXEMPT_GET() ? 125 : 250;
            d_col_r = zurumode_flag >= 2 ? 125 : 250;

            /**
             * debug 'D' colors:
             *  Base: Yellow
             *  ResetExempt: Pink
             *  Zurumode2/Zurumode3: Green
             *  ResetExempt & Zurumode2/Zurumode3: Blue-gray
             */
            gfxprint_color(print_p, d_col_r, d_col_g, 140, 255);
            gfxprint_locate8x8(print_p, 36, 3);
            gfxprint_printf(print_p, "D");

            if (npc_draw_status & 1) {
                mNpc_PrintRemoveInfo(print_p);
            }

            if (field_assessment_status & 1) {
                mFAs_PrintFieldAssessment(print_p);
                mAGrw_PrintFossilHaniwa_debug(print_p);

                /* Maybe a macro like 'IS_FDEBUG()' */
                if (zurumode_flag >= 2) {
                    mNpc_PrintFriendship_fdebug(print_p);
                }

                mPr_PrintMapInfo_debug(print_p);
            }

            mFRm_PrintSavedDebug(print_p);
            mCD_PrintErrInfo(print_p);
            mFRm_display_errInfo(print_p);
        }

        last_gfx = gfxprint_close(print_p);
        gSPEndDisplayList(last_gfx++);

        glist_used_bytes = (int)((u8*)last_gfx - (u8*)start_gfx);
        gfxclose(start_gfx, last_gfx);
        SET_POLY_OPA_DISP(last_gfx);
        gfxprint_cleanup(print_p);

        CLOSE_DISP(graph);
    }
}
