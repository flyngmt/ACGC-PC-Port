#ifndef M_TRADEMARK_H
#define M_TRADEMARK_H

#include "types.h"
#include "game.h"
#include "m_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_trademark_s) == 0x25A70 */
typedef struct game_trademark_s {
  /* 0x000000 */ GAME game;
  /* 0x0000E0 */ View view;
  /* 0x000200 */ xyz_t unused_200; // n64
  /* 0x00020C */ f32 unused_20c; // n64
  /* 0x000210 */ u32 unused_210; // n64
  /* 0x000214 */ int unused_214; // n64
  /* 0x000218 */ int unused_218[15]; // n64
  /* 0x000254 */ int unused_254; // n64
  /* 0x000258 */ int unused_258[38400]; // n64 texture
  /* 0x025A58 */ float alpha;
  /* 0x025A5C */ float logo_timer;
  /* 0x025A5E */ float alpha2;
  /* 0x025A60 */ float move_timer;
  /* 0x025A62 */ s16 unused_25a62; // n64
  /* 0x025A64 */ s16 unused_25a64; // n64
  /* 0x025A66 */ u8 stage;
  /* 0x025A67 */ u8 unused_25a67; // n64
  /* 0x025A68 */ u8 cancel;
  /* 0x025A69 */ u8 check;
  /* 0x025A6C */ int unused_25a6c; // n64
} GAME_TRADEMARK;

extern void trademark_init(GAME* game);
extern void trademark_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
