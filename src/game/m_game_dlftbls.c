#include "m_game_dlftbls.h"
#include "types.h"

#include "first_game.h"
#include "m_select.h"
#include "m_play.h"
#include "second_game.h"
#include "m_trademark.h"
#include "player_select.h"
#include "save_menu.h"
#include "famicom_emu.h"
#include "m_prenmi.h"

#define DLFTBL_MAKE(name, class) \
    { NULL, 0, 0, NULL, NULL, NULL, name##_init, name##_cleanup, NULL, NULL, NULL, sizeof(GAME_##class) }
#define DLFTBL_NULL() \
    { NULL, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 }

DLFTBL_GAME game_dlftbls[] = {
  DLFTBL_MAKE(first_game, FIRST),
  DLFTBL_MAKE(select, SELECT),
  DLFTBL_MAKE(play, PLAY),
  DLFTBL_MAKE(second_game, SECOND),
  DLFTBL_NULL(), /* removed & unused _GAME entry */
  DLFTBL_MAKE(trademark, TRADEMARK),
  DLFTBL_MAKE(player_select, PLAYER_SELECT),
  DLFTBL_MAKE(save_menu, SAVE_MENU),
  DLFTBL_MAKE(famicom_emu, FAMICOM_EMU),
  DLFTBL_MAKE(prenmi, PRENMI),
};
