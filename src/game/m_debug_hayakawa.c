/**
 * @file m_debug_hayakawa.c
 * @brief Debug module for handling various debug features for Kenzo Hayakawa.
 *
 * This module provides functions related to debugging in the application.
 * The functions support displaying pad inputs, drawing safety frames, and handling
 * hreg state index changes.
 *
 * Functions in this module:
 * - debug_hayakawa_bitset(): Creates or restores a bitset representation of hreg arguments for a given state.
 * - debug_hayakawa_draw(): Main function for handling various debug features.
 * - pad_disp(): Displays pad input on the screen.
 * - debug_hayakawa_draw_safetyframe(): Draws safety frames on the screen.
 * - hreg_init_check(): Checks if the hreg state index has changed and initializes the hreg state arguments if it has.
 */

#include "m_debug_hayakawa.h"

#include "m_debug.h"
#include "libu64/u64types.h"
#include "dolphin/os.h"
#include "jsyswrap.h"
#include "libc64/__osMalloc.h"
#include "m_rcp.h"
#include "main.h"
#include "m_lib.h"
#include "libforest/osreport.h"
#include "libforest/emu64.h"
#include "gfxalloc.h"
#include "dolphin/vi.h"
#include "libu64/gfxprint.h"

/**
 * @brief Set or retrieve bits of a Hayakawa register based on the current state.
 *
 * This function updates the bits of a Hayakawa register if the current state
 * matches the given state. If the state matches and the Hayakawa register has
 * been initialized, the bits are set according to the given register.
 * Otherwise, the bits are saved to the given register.
 *
 * @param n The Hayakawa state to check against the current state.
 * @param reg The index of the Hayakawa register to set or retrieve bits from.
 */
static void debug_hayakawa_bitset(const int n, const int reg) {
    // Check if the current Hayakawa state matches the given state.
    if (GETREG(HREG, HREG_STATE_IDX) == n) {
        // If the Hayakawa register has been initialized, set its bits.
        if (hreg_init_check(n)) {
            int set;
            int i;
            int setbit = GETREG(HREG, reg);
            int bit = 1;

            // Loop through each bit in the register, setting the corresponding flag.
            for (i = 0; i < HREG_STATE_ARGS_COUNT; i++) {
                set = (setbit & bit) != 0;
                bit <<= 1;

                SETREG(HREG, HREG_STATE_ARGS_START + i, set);
            }
        }
        // If the Hayakawa register hasn't been initialized, save its bits.
        else {
            int savebit = 0;
            int bit = 1;
            int i;

            // Loop through each bit in the register, saving the corresponding flag.
            for (i = 0; i < HREG_STATE_ARGS_COUNT; i++) {
                if (GETREG(HREG, HREG_STATE_ARGS_START + i) != 0) {
                    savebit |= bit;
                }

                bit <<= 1;
            }

            SETREG(HREG, reg, savebit);
        }
    }
}

/**
 * @brief Executes a series of debug-related functions based on the HREG register state.
 *
 * This function provides various debugging features such as loading and storing
 * HREG settings, modifying video settings, and toggling debug drawing features.
 * It performs different actions based on the values set in the HREG register.
 *
 * @param pad Pointer to the pad_t structure, representing the input gamepad.
 */
extern void debug_hayakawa_move(pad_t* pad) {
    int i;

    debug_hayakawa_bitset(116, 16);
    debug_hayakawa_bitset(117, 17);
    debug_hayakawa_bitset(139, 39);
    debug_hayakawa_bitset(140, 40);
    debug_hayakawa_bitset(141, 41);
    debug_hayakawa_bitset(142, 42);
    debug_hayakawa_bitset(143, 43);
    debug_hayakawa_bitset(144, 44);
    debug_hayakawa_bitset(145, 45);
    debug_hayakawa_bitset(146, 46);
    debug_hayakawa_bitset(147, 47);
    debug_hayakawa_bitset(10, 46);

    switch ((int)GETREG(HREG, HREG_STATE_IDX)) {
        /**
         * Loads/Stores HREG settings into emu64 aflags.
         * HREG[81] = saved emu64 aflag load/store start index
         * HREG[95] = now emu64 aflag load/store start index
         *
         * HREG[81] == HREG[95]: Store 12 HREG values (82 - 93) into aflags
         * HREG[81] != HREG[95]: Load 12 HREG values (82 - 93) from aflags
         */
        case 1: {
            if (hreg_init_check(1)) {
                SETREG(HREG, 95, -1);
            }

            if (GETREG(HREG, HREG_STATE_ARGS_START) != GETREG(HREG, 95)) {
                SETREG(HREG, 95, GETREG(HREG, HREG_STATE_ARGS_START));
                for (i = 0; i < 12; i++) {
                    SETREG(HREG, 82 + i, emu64_get_aflags(GETREG(HREG, HREG_STATE_ARGS_START) + i));
                }
            } else {
                for (i = 0; i < 12; i++) {
                    emu64_set_aflags(GETREG(HREG, HREG_STATE_ARGS_START) + i, GETREG(HREG, 82 + i));
                }
            }
        }
        /* Fallthrough 1 -> 2 -> 3 -> 4 -> 6 */
        /**
         * Loads the active thread count into HREG.
         * HREG[81] = < 0, load threads
         * HREG[82] = current active thread count
         */
        case 2: {
            hreg_init_check(2);
            if (GETREG(HREG, HREG_STATE_ARGS_START) < 0) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);
                SETREG(HREG, 82, OSCheckActiveThreads());
            }
        }
        /* Fallthrough 2 -> 3 -> 4 -> 6 */
        /**
         * Dumps the root heap info to console along with free size of the heap.
         * HREG[81] = < 0, check should dump
         * HREG[82] = 1, print dump
         */
        case 3: {
            hreg_init_check(3);
            if (GETREG(HREG, HREG_STATE_ARGS_START) < 0) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);

                switch (GETREG(HREG, 82)) {
                    case 1: {
                        OSReport("*** RootHeapDump ***\n");
                        JC_JKRHeap_dump(JC_JFWSystem_getRootHeap());
                        OSReport("RootHeapFree=%08x\n", JC_JKRHeap_getTotalFreeSize(JC_JFWSystem_getRootHeap()));
                    } break;
                }
            }
        }
        /* Fallthrough 3 -> 4 -> 6 */
        // break;

        /**
         * Modifies video settings
         * HREG[81] = < 0, switch mode
         * HREG[82]:
         *  1: Disable progressive mode
         *  2: Enable progressive mode
         *  3: Disable low resolution mode
         *  4: Enable low resolution mode
         */
        case 4: {
            hreg_init_check(4);
            if (GETREG(HREG, HREG_STATE_ARGS_START) < 0) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);
                switch (GETREG(HREG, 82)) {
                    case 1:
                        JW_SetProgressiveMode(FALSE);
                        break;

                    case 2:
                        JW_SetProgressiveMode(TRUE);
                        break;

                    case 3:
                        JW_SetLowResoMode(FALSE);
                        break;

                    case 4:
                        JW_SetLowResoMode(TRUE);
                        break;
                }
            }
        }
        /* Fallthrough 4 -> 6 */
        case 6: {
            if (hreg_init_check(6)) {
                SETREG(HREG, HREG_STATE_ARGS_START, 1);
                SETREG(HREG, 82, 1);
            }
        } break;

        case 7:
            break;

        case 8: {
            hreg_init_check(8);
            if (GETREG(HREG, HREG_STATE_ARGS_START) < 0) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);
            }
        } break;

        /**
         * Unknown function, but may relate to toggling some debug
         * drawing feature which is removed.
         *
         * HREG[81]:
         *   1: Set bit 3 (enable)
         *   2: Clear bit 3 (disable)
         *
         * HREG[47] = modified register
         */
        case 15: {
            hreg_init_check(15);
            if (GETREG(HREG, HREG_STATE_ARGS_START) == 1) {
                SETREG(HREG, 47, GETREG(HREG, 47) | 8);
            } else if (GETREG(HREG, HREG_STATE_ARGS_START) == 2) {
                SETREG(HREG, 47, GETREG(HREG, 47) & (~8));
            }
        } break;

        /**
         * Toggles 'FreeBlockTest' mode for __osMalloc.
         * HREG[82] = BOOL enable
         */
        case 20: {
            hreg_init_check(20);
            __osMalloc_FreeBlockTest_Enable = GETREG(HREG, 82);
        } break;

        /**
         * Safety frame bounds
         * Sets the bounds for drawing saftey frame boundary in
         * debug_hayakawa_draw. Minimum bounds are (0, 0) and
         * maximum bounds are (ScreenWidth, ScreenHeight).
         *
         * HREG[81]:
         *    1: Bounds set to [(0, 0), (SCREEN_WIDTH, SCREEN_HEIGHT)]
         *    2: Bounds set to [(0, 0), (ScreenWidth, ScreenHeight)]
         *
         * HREG[82]: upper left y (uly)
         * HREG[83]: lower right y (lry)
         * HREG[84]: upper left x (ulx)
         * HREG[85]: lower right x (lrx)
         */
        case 25: {
            if (hreg_init_check(25)) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);
                SETREG(HREG, 82, 0);
                SETREG(HREG, 83, ScreenHeight);
                SETREG(HREG, 84, 0);
                SETREG(HREG, 85, ScreenWidth);
            }

            switch (GETREG(HREG, HREG_STATE_ARGS_START)) {
                case 1: {
                    SETREG(HREG, 82, 0);
                    SETREG(HREG, 83, SCREEN_HEIGHT);
                    SETREG(HREG, 84, 0);
                    SETREG(HREG, 85, SCREEN_WIDTH);
                } break;

                case 2: {
                    SETREG(HREG, 82, 0);
                    SETREG(HREG, 83, ScreenHeight);
                    SETREG(HREG, 84, 0);
                    SETREG(HREG, 85, ScreenWidth);
                } break;
            }

            if (GETREG(HREG, 82) < 0) {
                SETREG(HREG, 82, 0);
            }

            if (GETREG(HREG, 83) > ScreenHeight) {
                SETREG(HREG, 83, ScreenHeight);
            }

            if (GETREG(HREG, 84) < 0) {
                SETREG(HREG, 84, 0);
            }

            if (GETREG(HREG, 85) > ScreenWidth) {
                SETREG(HREG, 85, ScreenWidth);
            }
        } break;

        /**
         * Unknown function.
         * HREG[82], HREG[83], HREG[84] all contain bytes. Two of which are concatenated
         * depending on value in HREG[81]. Result is stored in HREG[48] or HREG[49].
         *
         * HREG[81] = Mode
         * HREG[82] = byte0
         * HREG[83] = byte1
         * HREG[84] = byte2
         * HREG[48] = result_byte0_byte1
         * HREG[49] = result_byte1_byte2
         */
        case 39: {
            hreg_init_check(39);

            switch (GETREG(HREG, HREG_STATE_ARGS_START)) {
                case 0:
                    break;

                case 1: {
                    u16 v = ((GETREG(HREG, 82) & 0xFF) << 8) | (GETREG(HREG, 83) & 0xFF);
                    if (GETREG(HREG, 48) != v) {
                        SETREG(HREG, 48, v);
                    }
                } break;

                case 2: {
                    if (GETREG(HREG, 48) != 0) {
                        SETREG(HREG, 48, 0);
                    }
                } break;

                case 3: {
                    u16 v = ((GETREG(HREG, 83) & 0xFF) << 8) | (GETREG(HREG, 84) & 0xFF);
                    if (GETREG(HREG, 49) != v) {
                        SETREG(HREG, 49, v);
                    }
                } break;
            }
        } break;

        /* Clear state arg for memory block (1MB blocks) */
        case 600: {
            hreg_init_check(600);

            if (GETREG(HREG, HREG_STATE_ARGS_START) < 0) {
                SETREG(HREG, HREG_STATE_ARGS_START, 0);
            }
        }
        /* Fallthrough 600 -> 666 */
        /* Get/Set byte at beginning of 1MB boundary blocks */
        case 666: {
            /**
             * HREG[82] = index of 1MB block
             * HREG[83] = byte to get/set for block
             */
            hreg_init_check(666);

            switch (GETREG(HREG, HREG_STATE_ARGS_START)) {
                /* Load */
                case 1: {
#ifndef TARGET_PC
                    SETREG(HREG, 83, *(u8*)(GETREG(HREG, 82) * 0x100000 - 0x80000000));
#endif
                } break;

                /* Store */
                case 2: {
#ifndef TARGET_PC
                    *(u8*)(GETREG(HREG, 82) * 0x100000 - 0x80000000) = (u8)GETREG(HREG, 83);
#endif
                } break;
            }
        } break;
    }

    hreg_init_check(667);
    hreg_init_check(34);
    hreg_init_check(35);
    hreg_init_check(38);

    if (GETREG(SREG, 21)) {
        if (GETREG(SREG, 21) & 1) {
            OSReportDisable();
        } else {
            if (OS_CONSOLE_IS_DEV()) {
                OSReportEnable();
            }
        }

        JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), !(GETREG(SREG, 21) & 2));
        JC_JUTProcBar_setVisible(JC_JUTProcBar_getManager(), !(GETREG(SREG, 21) & 4));
        JC_JUTProcBar_setVisibleHeapBar(JC_JUTProcBar_getManager(), !(GETREG(SREG, 21) & 4));
    }
}

typedef union {
    rgba_t color;
    u32 raw;
} rgba_u;

/**
 * @brief Displays a visualization of the input device state, including button press indicators.
 *
 * This function creates a visualization of the input device state by drawing colored rectangles
 * for each button press. The display is organized by input device and button index.
 * Colors are defined in the pad_color2 array, with specific colors for each button group.
 *
 * @param pad       The index of the input device (controller) to display state for.
 * @param button    A 16-bit value representing the button state (1 = pressed, 0 = not pressed).
 * @param gfx_pp    Pointer to a pointer of Gfx type, which will be used to draw the button states.
 */
static void pad_disp(u8 pad, u16 button, Gfx** gfx_pp) {
    static const rgba_u pad_color2[16] = {
        /* Yellow for C-Stick */
        { 255, 255, 0, 255 }, /* C-Stick Right */
        { 255, 255, 0, 255 }, /* C-Stick Left */
        { 255, 255, 0, 255 }, /* C-Stick Down */
        { 255, 255, 0, 255 }, /* C-Stick Up */
        /* Gray for L, R, X, Y, D-Pad, & Start */
        { 127, 127, 127, 255 }, /* R */
        { 127, 127, 127, 255 }, /* L */
        { 127, 127, 127, 255 }, /* X */
        { 127, 127, 127, 255 }, /* Y */
        { 127, 127, 127, 255 }, /* D-Pad Right */
        { 127, 127, 127, 255 }, /* D-Pad Left */
        { 127, 127, 127, 255 }, /* D-Pad Down */
        { 127, 127, 127, 255 }, /* D-Pad Up */
        { 127, 127, 127, 255 }, /* Start */
        /* Blue for Z */
        { 0, 0, 255, 255 }, /* Z */
        /* Red for B */
        { 255, 0, 0, 255 }, /* B */
        /* Green for A */
        { 0, 255, 0, 255 }, /* A */
    };

    const int pad_start_x = pad * 70 + 20;
    Gfx* gfx = *gfx_pp;
    int i;
    int x0;
    int x1;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 0);
    gfx = gfx_gDPFillRectangle1(gfx, pad_start_x - 1, 225, pad_start_x + 65, 231);

    for (i = 0; i < 16; i++) {
        if (button & (1 << i)) {
            gDPSetColor(gfx++, G_SETPRIMCOLOR, pad_color2[i].raw);
            x0 = pad_start_x + (int)(i * 4);
            x1 = pad_start_x + (int)((i + 1) * 4);
            gfx = gfx_gDPFillRectangle1(gfx, x0, 226, x1 - 1, 229);
        }
    }

    gDPPipeSync(gfx++);
    *gfx_pp = gfx;
}

/**
 * @brief Draws a safety frame around the specified screen region.
 *
 * This function creates a white frame around the specified region on the screen.
 * The frame is one pixel wide and is drawn along the edges of the specified region.
 * The frame is not drawn outside the screen boundaries.
 *
 * @param gfx_pp  Pointer to a pointer of Gfx type, which will be used to draw the safety frame.
 * @param ulx     Upper-left x coordinate of the region.
 * @param uly     Upper-left y coordinate of the region.
 * @param lrx     Lower-right x coordinate of the region.
 * @param lry     Lower-right y coordinate of the region.
 */
static void debug_hayakawa_draw_safetyframe(Gfx** gfx_pp, u32 ulx, u32 uly, u32 lrx, u32 lry) {
    Gfx* gfx = *gfx_pp;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gDPSetFillColor(gfx++, 0xFFFFFFFF);

    if (uly > 1) {
        gfx = gfx_gDPFillRectangleF(gfx, ulx, uly - 1, lrx + 1, uly);
    }

    if (ulx > 1) {
        gfx = gfx_gDPFillRectangleF(gfx, ulx - 1, uly, ulx, lry + 1);
    }

    if (lry < SCREEN_HEIGHT - 1) {
        gfx = gfx_gDPFillRectangleF(gfx, ulx, lry, lrx + 1, lry + 1);
    }

    if (lrx < SCREEN_WIDTH - 1) {
        gfx = gfx_gDPFillRectangleF(gfx, lrx, uly, lrx + 1, lry + 1);
    }

    gDPPipeSync(gfx++);
    *gfx_pp = gfx;
}

#define DRAW_MAX_X (u32)(SCREEN_WIDTH - 1)
#define DRAW_MAX_Y (u32)(SCREEN_HEIGHT - 1)

/**
 * @brief Debug drawing function for various graphical elements and overlays.
 *
 * @param graph Pointer to the GRAPH struct which will be drawn to.
 */
extern void debug_hayakawa_draw(GRAPH* graph) {
    Gfx* poly_opa_gfx;
    Gfx* opened_gfx;
    gfxprint_t gfxprint;
    gfxprint_t* gfxprint_p = &gfxprint;

    OPEN_DISP(graph);

    poly_opa_gfx = NOW_POLY_OPA_DISP;
    opened_gfx = gfxopen(poly_opa_gfx);

    gSPDisplayList(NOW_OVERLAY_DISP++, opened_gfx);

    /* Draw pad input */
    if (GETREG(HREG, 47) & 1) {
        int i;
        for (i = 0; i < MAXCONTROLLERS; i++) {
            s16 button = GETREG(HREG, 40 + i);
            if (button != 0) {
                pad_disp(i, button, &opened_gfx);
            }
        }
    }

    if (GETREG(HREG, HREG_STATE_IDX) == 41 && hreg_init_check(41)) {
        SETREG(HREG, HREG_STATE_ARGS_START, (GETREG(HREG, 39) >> 1) & 1);
        SETREG(HREG, 82, 31);
        SETREG(HREG, 83, 22);
        SETREG(HREG, 84, 289);
        SETREG(HREG, 85, 218);
    }

    /* Safety frame drawing check */
    if ((GETREG(HREG, 39) & 2) || (GETREG(HREG, HREG_STATE_IDX) == 41 && GETREG(HREG, HREG_STATE_ARGS_START) != 0)) {
        u32 a = 31;
        u32 b = 22;
        u32 c = 289;
        u32 d = 218;

        u32 ulx, uly, lrx, lry;

        if (GETREG(HREG, HREG_STATE_IDX) == 41) {
            a = GETREG(HREG, 82);
            b = GETREG(HREG, 83);
            c = GETREG(HREG, 84);
            d = GETREG(HREG, 85);
        }

        ulx = a <= DRAW_MAX_X ? a : DRAW_MAX_X;
        uly = b <= DRAW_MAX_Y ? b : DRAW_MAX_Y;
        lrx = c < ulx ? ulx : (c <= DRAW_MAX_X - 1 ? c : DRAW_MAX_X - 1);
        lry = d < uly ? uly : (d <= DRAW_MAX_Y - 1 ? d : DRAW_MAX_Y - 1);

        debug_hayakawa_draw_safetyframe(&opened_gfx, ulx, uly, lrx, lry);
    }

    /* Vertical Interrupt Pan Configuration */
    if (GETREG(HREG, HREG_STATE_IDX) == 42) {
        if (hreg_init_check(42) || (GETREG(HREG, HREG_STATE_IDX) == 42 && GETREG(HREG, HREG_STATE_ARGS_START) != 0)) {
            SETREG(HREG, HREG_STATE_ARGS_START, 0);
            /* 4:5 aspect ratio? */
            SETREG(HREG, 82, 30);  /* Pan x origin */
            SETREG(HREG, 83, 6);   /* Pan y origin */
            SETREG(HREG, 84, 580); /* Pan width */
            SETREG(HREG, 85, 464); /* Pan height */
        }

        VIConfigurePan(GETREG(HREG, 82) & ~1, GETREG(HREG, 83) & ~1, GETREG(HREG, 84) & ~1, GETREG(HREG, 85) & ~1);
    }

    /* Initialize display list segment at specific 1MB region */
    if (GETREG(HREG, HREG_STATE_IDX) == 667 && GETREG(HREG, HREG_STATE_ARGS_START)) {
        int block = GETREG(HREG, 82) * 0x100000 + 0x80000000;
        /* TODO: segment id 8 definitely needs a definition somewhere */
        gSPSegment(opened_gfx++, 8, block);
    }

    gfxprint_init(gfxprint_p);
    gfxprint_open(gfxprint_p, opened_gfx);
    /* removed/debug code I guess? */
    opened_gfx = gfxprint_close(gfxprint_p);
    gSPEndDisplayList(opened_gfx++);
    gfxclose(poly_opa_gfx, opened_gfx);
    SET_POLY_OPA_DISP(opened_gfx);
    gfxprint_cleanup(gfxprint_p);

    CLOSE_DISP(graph);
}

/**
 * @brief Checks if the hreg state index has changed and initializes the hreg state arguments if it has.
 *
 * This function checks if the hreg state index (n) is different from the previous one. If it is,
 * the function initializes the hreg state arguments to 0 and returns TRUE. Otherwise, it returns FALSE.
 *
 * @param n The hreg state index to check.
 * @return TRUE if the hreg state index has changed and the hreg state arguments have been initialized, FALSE otherwise.
 */

extern int hreg_init_check(const int n) {
    // Check if the current hreg state index is different from the previous one
    if (GETREG(HREG, HREG_STATE_IDX) == n && GETREG(HREG, 55) != n) {
        int i;

        // Set the previous hreg state index to the current one
        SETREG(HREG, 55, n);

        // Initialize the hreg state arguments to 0
        for (i = HREG_STATE_ARGS_START; i < HREG_STATE_ARGS_START + 15; i++) {
            SETREG(HREG, i, 0);
        }

        // Return TRUE if the hreg state index has changed and arguments have been initialized
        return TRUE;
    }

    // Return FALSE if the hreg state index has not changed
    return FALSE;
}
