#ifndef ACGC_PC_DOLPHIN_CARD_H
#define ACGC_PC_DOLPHIN_CARD_H

#include_next <dolphin/card.h>

/* Two physical card slots are part of the original SDK API contract. */
#ifndef CARD_NUM_CHANS
#define CARD_NUM_CHANS 2
#endif

#endif
