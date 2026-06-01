#include "m_scene_ftr.h"

#include "m_scene.h"
#include "m_play.h"

/* @unused ? mScn_Dma2Bank(...) */

static void mScn_KeepMyRoomBankNew(Object_Exchange_c* exchange, s16 bank_id, size_t size) {
  Object_Bank_c* bank = exchange->banks + exchange->bank_idx;
  
  bank->bank_id = bank_id;
  bank->dma_start = exchange->next_bank_ram_address;
  bank->ram_start = exchange->next_bank_ram_address;
  bank->size = size;

  if (exchange->bank_idx < (mSc_OBJECT_BANK_NUM - 1)) {
    exchange->next_bank_ram_address = (char*)ALIGN_NEXT((uintptr_t)exchange->next_bank_ram_address + size, 16);
    exchange->bank_idx++;
  }
}

extern void mScn_ObtainCarpetBank(GAME_PLAY* play) {
  Object_Exchange_c* exchange = &play->object_exchange;
  int i;

  for (i = 0; i < 2; i++) {
    mScn_KeepMyRoomBankNew(exchange, 18, 0x2020); // carpet tex + pal
  }

  for (i = 0; i < 2; i++) {
    mScn_KeepMyRoomBankNew(exchange, 19, 0x1020); // wall tex + pal
  }
}

/* @unused extern ? mScn_ObtainFurnitureBank(...) */

extern void mScn_ObtainMyRoomBank(GAME_PLAY* play) {
  mScn_ObtainCarpetBank(play);
}
