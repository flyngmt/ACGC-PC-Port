#include "evw_anime.h"

/* @HACK - this is probably aligned to 32 bytes because it and the other data were compiled into a single object file
   the other TU has things aligned to 32 bytes */
ATTRIBUTE_ALIGN(32) static EVW_ANIME_SCROLL grd_player_select_evw_anime_1[] = { { 1, 1, 32, 32 }, { 0, 0, 32, 64 } };

extern EVW_ANIME_DATA grd_player_select_evw_anime[] = {
    { -1, EVW_ANIME_TYPE_SCROLL2, grd_player_select_evw_anime_1 },
};
