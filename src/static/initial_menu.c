#include "initial_menu.h"
#include "PR/mbi.h"
#include "libforest/gbi_extensions.h"
#include "m_nmibuf.h"
#include "dolphin/dvd.h"
#include "jsyswrap.h"
#include "boot.h"
#include "dolphin/os/OSFont.h"
#include "bootdata.h"
#include "libultra/libultra.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "dolphin/vi.h"
// #include "dolphin/os/OSRtc.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSResetSW.h"
#include "dolphin/os/OSReset.h"
#include "dolphin/os.h"
#include "m_controller.h"
#include "dvderr.h"

#define G_CC_LOGO 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0

static Mtx model_cursor;
static u8 progressive_mode;

static Gfx gam_win1_cursor_setup[] = {
  gsSPTexture(0, 0, 0, 0, G_OFF),
  gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
  gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
  gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  gsSPEndDisplayList(),
};

static Gfx gam_win1_moji_setup[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_BLENDPRIMDECALA),
  gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
  gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
  gsSPEndDisplayList(),
};

static Vp viewport = {
  1280, 960, 511, 0,
  1280, 960, 511, 0
};

static Mtx projection = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0xFFFF0000, 0x00000000, 0xFFFF0001,
  0x00CC0000, 0x00000000, 0x00000111, 0x00000000,
  0x00000000, 0xFFFF0000, 0x00000000, 0x00000000
};

static Mtx lookat = {
  0x10000, 0x00000, 0x00001, 0x00000,
  0x00000, 0x10000, 0x00000, 0x00001,
  0x00000, 0x00000, 0x00000, 0x00000,
  0x00000, 0x00000, 0x00000, 0x00000
};

static Mtx default_model_scale = {
  0x20000, 0x00000, 0x00002, 0x00000,
  0x00000, 0x10000, 0x00000, 0x00001,
  0x00000, 0x00000, 0x00000, 0x00000,
  0x00000, 0x00000, 0x00000, 0x00000
};

static Mtx logo_projection = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000,
  0x00000000, 0xFFFF0000, 0x00000000, 0x00000001,
  0x00CC0000, 0x00000000, 0x000000F9, 0x00000000,
  0x00000000, 0x00000000, 0x0000007C, 0x00000000
};

static Mtx logo_model_scale = {
  0x10000, 0x00000, 0x00001, 0x00000,
  0x00000, 0x10000, 0x00000, 0x00001,
  0x00000, 0x00000, 0x00000, 0x00000,
  0x00000, 0x00000, 0x00000, 0x00000
};

static Gfx initial_dl[] = {
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
  gsSPClipRatio(FRUSTRATIO_2),
  gsSPViewport(&viewport),
  gsSPMatrix(&projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION),
  gsSPMatrix(&lookat, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION),
  gsSPMatrix(&default_model_scale, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
  gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
  gsSPEndDisplayList(),
};

static Gfx logo_initial_dl[] = {
  gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
  gsSPClipRatio(FRUSTRATIO_2),
  gsSPViewport(&viewport),
  gsSPMatrix(&logo_projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION),
  gsSPMatrix(&lookat, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION),
  gsSPMatrix(&default_model_scale, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
  gsDPSetOtherMode(G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
  gsSPEndDisplayList(),
};

static Gfx logo_draw_dl[] = {
  gsSPDisplayList(logo_initial_dl),
  gsSPDisplayList(gam_win1_moji_setup),
  gsDPSetPrimColor(0, 255, 220, 0, 0, 255),
  gsSPMatrix(&logo_model_scale, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
  gsSPDisplayList(logo_ninT_model),
  gsSPPopMatrix(G_MTX_MODELVIEW),
  gsSPEndDisplayList(),
};

static Gfx step1_draw_dl[] = {
  gsSPDisplayList(initial_dl),
  gsSPDisplayList(gam_win1_moji_setup),
  gsSPDisplayList(gam_win1_winT_model),
  gsSPDisplayList(gam_win1_moji_model),
  gsDPSetPrimColor(0, 255, 90, 90, 155, 255),
  gsSPDisplayList(0x08000000),
  gsDPSetPrimColor(0, 255, 50, 30, 150, 255),
  gsSPDisplayList(0x09000000),
  gsSPDisplayList(gam_win1_cursor_setup),
  gsSPMatrix(&model_cursor, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW),
  gsSPDisplayList(gam_win1_cursor_model),
  gsSPPopMatrix(G_MTX_MODELVIEW),
  gsSPEndDisplayList(),
};

static Gfx step2_draw_dl[] = {
  gsSPDisplayList(initial_dl), /* call initial dl */
  gsSPDisplayList(gam_win1_moji_setup), /* call gam_win1_moji_setup */
  gsDPSetPrimColor(0, 255, 225, 255, 255, 255), /* set primitive color to off-white */
  gsSPDisplayList(gam_win2_winT_model), /* call gam_win2_winT_model */
  gsDPSetPrimColor(0, 255, 50, 50, 60, 255), /* set primitive color to dark blue-gray */
  gsSPDisplayList(0x08000000), /* call progressive mode model set in step2_make_dl */
  gsSPEndDisplayList(),
};

static int pad_good_frame_count = -1;

static void step0_make_dl(Gfx** gpp) {
  Gfx* g = *gpp;

  if (APPNMI_TESTMODE_GET()) {
    DVDDiskID* diskId = DVDGetCurrentDiskID();
    if (boot_copyDate != NULL) {
      JW_JUTReport(150, 400, 1, "COPYDATE: %.17s", boot_copyDate);
    }

    if (diskId != NULL) {
      JW_JUTReport(150, 330, 1, "<DISK ID>");
      JW_JUTReport(150, 342, 1, "GAMENAME: %.4s", diskId->gameName);
      JW_JUTReport(150, 354, 1, " COMPANY: %.2s", diskId->company);
      JW_JUTReport(150, 366, 1, " VERSION: 0x%02X(%d)", diskId->gameVersion, diskId->gameVersion);
    }

    JW_JUTReport(150, 330, 1, "<DISK ID>"); /* I belive the above <DISK ID> is a 'bug', because this is the exact same print */
    JW_JUTReport(150, 50, 1, "SDK VERSION: 12Dec2001 Patch4");

    if (OSGetFontEncode() == OS_FONT_ENCODE_SJIS) {
      JW_JUTReport(150, 100, 1, " ****** WARNING ******");
      JW_JUTReport(150, 112, 1, "The DISP SW is JAPAN MODE now");
      JW_JUTReport(150, 124, 1, "but this GAME is NES version");
    }
  }

  if (APPNMI_SHOPPROMOVERSION_GET()) {
    JW_JUTReport(150, 410, 1, "SHOP PROMOTE VERSION");
  }

  gSPDisplayList(g++, logo_draw_dl);
  *gpp = g;
}

extern void make_dl_nintendo_logo(Gfx** gpp, u32 alpha) {
  Gfx* g = *gpp;

  gSPSegment(g++, G_MWO_SEGMENT_8, logo_initial_dl); /* segment 8 = logo_initial_dl */
  gSPSegment(g++, G_MWO_SEGMENT_9, gam_win1_moji_setup); /* segment 9 = gam_win1_moji_setup */
  gSPDisplayList(g++, SEGMENT_ADDR(8, 0)); /* call to segment 8 (logo_initial_dl) */
  gSPDisplayList(g++, SEGMENT_ADDR(9, 0)); /* call to segment 9 (gam_win1_moji_setup) */
  gSPMatrix(g++, &logo_model_scale, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW); /* set logo model scale */
  gDPSetCombineMode(g++, G_CC_LOGO, G_CC_LOGO); /* set color combiner for logo */
  gDPSetPrimColor(g++, 0, 255, LOGO_COLOR_R, LOGO_COLOR_G, LOGO_COLOR_B, alpha); /* set logo color */
  gSPDisplayList(g++, logo_ninT_model); /* call logo display list (logo_ninT_model) */
  gSPPopMatrix(g++, G_MTX_MODELVIEW); /* remove logo model scale */

  *gpp = g;
}

static void step1_make_dl(Gfx** gpp) {
  static Gfx* yes_no_model[2] = {
    gam_win1_moji2_model,
    gam_win1_moji3_model
  };

  Gfx* g = *gpp;

  guTranslate(&model_cursor, progressive_mode != 0 ? -42 : 0, -86.0f, 0.0f);
  
  gSPSegment(g++, G_MWO_SEGMENT_8, yes_no_model[progressive_mode]); /* segment 8 is yes/no */
  gSPSegment(g++, G_MWO_SEGMENT_9, yes_no_model[progressive_mode ^ 1]); /* segment 9 is inverse yes/no */
  gSPDisplayList(g++, step1_draw_dl); /* call step1 display list  */

  *gpp = g;
}

static void step2_make_dl(Gfx** gpp) {
  Gfx* g = *gpp;

  gSPSegment(g++, G_MWO_SEGMENT_8, progressive_mode != 0 ? gam_win2_moji_model : gam_win3_moji_model);
  gSPDisplayList(g++, step2_draw_dl);

  *gpp = g;
}

static u8 menu_step;

static void make_dl(Gfx* gfx, int size) {
  Gfx* g = gfx;

  step0_make_dl(&g);
  if (menu_step == 1 || menu_step == 11) {
    step1_make_dl(&g);
  }
  else if (menu_step == 2) {
    step2_make_dl(&g);
  }

  gDPFullSync(g++);
  gSPEndDisplayList(g++);
}

extern void exec_dl(Gfx* gfx) {
  emu64_init();
  emu64_taskstart(gfx);
  emu64_cleanup();
}

static Z_OSTime start_time;
static u32 button;
static u32 trigger;
static int frame_count;
static Z_OSTime limit_time;
static int select_done;
static u8 menu_sub_frame;

extern void keycheck() {
  Z_OSTime now = osGetTime();
  Z_OSTime delta = now - start_time;
  u32 t;
  u32 error;

  JC_JUTGamePad_read();
  button = JW_JUTGamepad_getButton();
  t = JW_JUTGamepad_getTrigger();
  trigger = t;
  trigger |= (((t >> 16) | (t >> 24)) & 0xF);
  error = JW_JUTGamepad_getErrorStatus();

  if (pad_good_frame_count < 0 && error == 0) {
    pad_good_frame_count = frame_count;
  }

  if (menu_step == 0) {
    if ((button == B || OSGetProgressiveMode()) && VIGetDTVStatus()) {
      progressive_mode = VIGetDTVStatus();
      menu_step = 1;
      start_time = now;
      limit_time = button == B ? INITIAL_MENU_LIMIT_TIME : INITIAL_MENU_LIMIT_TIME; // 10 second limit
    }
    else {
      if (limit_time < delta) {
        menu_step = 3;
        select_done = TRUE;
        start_time = now;
      }
    }
  }
  else if (menu_step == 1) {
    if ((trigger & A) != 0 || limit_time < delta) {
      OSSetProgressiveMode(progressive_mode);
      start_time = now;
      menu_step = 11;
      menu_sub_frame = 0;
    }
    else {
    if ((trigger & DPAD_LEFT)) {
        progressive_mode = TRUE;
        start_time = now;
        limit_time = INITIAL_MENU_LIMIT_TIME;
      }
      else {
        if ((trigger & DPAD_RIGHT)) {
          progressive_mode = FALSE;
          start_time = now;
          limit_time = INITIAL_MENU_LIMIT_TIME;
        }
      }
    }
  }
  else if (menu_step == 11) {
    switch (menu_sub_frame) {
      case 0:
      {
        JC_JFWDisplay_startFadeOut(JC_JFWDisplay_getManager(), 10);
        break;
      }

      case 5:
      {
        JW_SetProgressiveMode(progressive_mode);
        break;
      }

      case 105:
      {
        JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 15);
        start_time = now;
        menu_step = 2;
        break;
      }
    }

    menu_sub_frame++;
  }
  else {
    if (menu_step == 2 && INITIAL_MENU_SELECT_WAIT_TIME < delta) {
      menu_step = 3;
      select_done = TRUE;
      start_time = now;
    }
  }
}

static OSMessageQueue commandQ;
static int fadeout_step;
static int load_game_done;
static Gfx gfxbuf[16];
static OSMessageQueue statusQ;
static OSThread* Thread_p;
static void* initialMenuStack;
static OSMessage commandMsgBuf[2];
static OSMessage statusMsgBuf[1];

extern void proc(void* arg) {
  u32 msg;
  int proc_done;
  OSTimer timer;

  osRecvMesg(&commandQ, (OSMessage*)&msg, OS_MESSAGE_BLOCK);
  progressive_mode = FALSE;
  fadeout_step = 0;
  menu_step = 0;
  select_done = FALSE;
  load_game_done = FALSE;
  start_time = osGetTime();
  limit_time = OSMicrosecondsToTicks(5000000ull);
  pad_good_frame_count = -1;
  frame_count = 0;

  do {
    if (OSGetResetSwitchState()) {
      __osResetSwitchPressed = TRUE;
    }
    else {
      if (__osResetSwitchPressed) {
        osShutdownStart(OS_RESET_RESTART);
      }
    }

    if (!osRecvMesg(&commandQ, (OSMessage*)&msg, OS_MESSAGE_NOBLOCK)) {
      if (msg == INITIAL_MENU_OSMESG_FADEOUT_STEP) {
        fadeout_step = 2;
      }

      if (msg == INITIAL_MENU_OSMESG_LOAD_GAME_DONE) {
        load_game_done = TRUE;
      }
    }

    if (fadeout_step == 0 && select_done && load_game_done) {
      fadeout_step = 1;
      osSetTimer(&timer, OSMicrosecondsToTicks(533312ull), 0, &commandQ, (OSMessage)INITIAL_MENU_OSMESG_FADEOUT_STEP);
      JC_JFWDisplay_startFadeOut(JC_JFWDisplay_getManager(), 32);
    }

    if ((menu_step != 0 && menu_step != 3) || dvderr_draw() == FALSE) {
      JW_BeginFrame();
      keycheck();
      make_dl(gfxbuf, 16);
      exec_dl(gfxbuf);
      JW_EndFrame();
      frame_count++;
    }

    proc_done = FALSE;
    if (fadeout_step == 2 && select_done && load_game_done) {
      proc_done = TRUE;
    }
  } while (!proc_done);

  osSendMesg(&statusQ, (OSMessage)msg, OS_MESSAGE_NOBLOCK); // signal done
}

static void* my_alloc(size_t size) {
  return JW_Alloc(size, 32);
}

static void my_free(void* ptr) {
  JW_Free(ptr);
}

extern void initial_menu_init() {
  Thread_p = (OSThread*)my_alloc(sizeof(OSThread));
  initialMenuStack = my_alloc(INITIAL_MENU_STACK_SIZE);
  if (Thread_p == NULL || initialMenuStack == NULL) {
    OSReport("initial_menu_init: Memory insufficiency.\n");
    my_free(Thread_p);
    Thread_p = NULL;
    my_free(initialMenuStack);
    initialMenuStack = NULL;
  }
  else {
    osCreateMesgQueue(&commandQ, commandMsgBuf, 2);
    osCreateMesgQueue(&statusQ, statusMsgBuf, 1);
    osCreateThread2(Thread_p, 1, &proc, NULL, (void*)((int)initialMenuStack + INITIAL_MENU_STACK_SIZE), INITIAL_MENU_STACK_SIZE, 1);
    osStartThread(Thread_p);
    JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 32);
    osSendMesg(&commandQ, (OSMessage)INITIAL_MENU_OSMESG_INIT_DONE, OS_MESSAGE_NOBLOCK);
  }
}

extern void initial_menu_cleanup() {
  OSMessage msg;

  if (Thread_p != NULL) {
    if (!osRecvMesg(&commandQ, (OSMessage*)&msg, OS_MESSAGE_NOBLOCK)) {
      osSendMesg(&commandQ, (OSMessage)INITIAL_MENU_OSMESG_LOAD_GAME_DONE, OS_MESSAGE_NOBLOCK);
      osRecvMesg(&statusQ, (OSMessage*)&msg, OS_MESSAGE_BLOCK);
    }

    osDestroyThread(Thread_p);
  }

  JW_SetLogoMode(0);
  JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 32);
  my_free(Thread_p);
  Thread_p = NULL;
  my_free(initialMenuStack);
  initialMenuStack = NULL;
}
