#include "second_game.h"

#include "m_trademark.h"
#include "jaudio_NES/game64.h"
#include "padmgr.h"
#include "m_common_data.h"
#include "zurumode.h"
#include "libultra/libultra.h"
#include "dolphin/vi.h"
#include "dolphin/dvd.h"
#include "boot.h"
#include "sys_math.h"
#include "m_nmibuf.h"

static u8 sound_ok;
static u8 contpad_ok;
static u8 frame_count;

static void second_game_main(GAME* game) {
  if (sound_ok == 0) {
    sound_ok = 1;
    Na_RestartPrepare();
  }

  if (Na_CheckRestartReady() == TRUE) {
    sound_ok = 2;
  }

  if (sound_ok == 2) {
    Na_Restart();
  }

  if (padmgr_isConnectedController(PAD0)) {
    contpad_ok = TRUE;
  }

  if (sound_ok == 2 && (contpad_ok || frame_count > 3)) {
    GAME_GOTO_NEXT(game, trademark, TRADEMARK);
  }

  frame_count++;
}

extern void second_game_cleanup(GAME* game) {
  Common_Set(pad_connected, contpad_ok);
}

extern void second_game_init(GAME* game) {
  if (zurumode_flag != 0 && osShutdown >= 3) {
    VISetBlack(TRUE);
    VIFlush();
    VIWaitForRetrace();

    switch (osShutdown) {
      case 3:
      {
        osShutdownStart(OS_RESET_SHUTDOWN);
        break;
      }

      case 4:
      {
        HotResetIplMenu();
        break;
      }

      default:
      {
        osShutdownStart(OS_RESET_RESTART);
        break;
      }
    }
  }

  if (osShutdown != 0) {
    if (APPNMI_HOTRESET_GET()) {
      osShutdownStart(OS_RESET_SHUTDOWN);
    }
    else {
      if (DVDCheckDisk() == FALSE) {
        osShutdownStart(OS_RESET_RESTART);
      }
    }
  }

  sound_ok = 0;
  contpad_ok = TRUE;
  frame_count = 0;

  game->exec = &second_game_main;
  game->cleanup = &second_game_cleanup;
  init_rnd();
  __osInitialize_common();

}