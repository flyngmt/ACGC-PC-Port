/* pc_save_bswap.h - Bidirectional LE<->BE byte-swap for GCI save data */
#ifndef PC_SAVE_BSWAP_H
#define PC_SAVE_BSWAP_H

#include "m_common_data.h"
#include "m_card.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Direction matters for bitfield structs where bswap is not self-inverse */
typedef enum {
    PC_BSWAP_TO_BE,   /* LE in-memory -> BE for disk */
    PC_BSWAP_FROM_BE  /* BE from disk -> LE in-memory */
} pc_bswap_dir_t;

void pc_save_bswap(Save_t* save, pc_bswap_dir_t dir);

void pc_save_bswap_keep_mail(mCD_keep_mail_c* mail, pc_bswap_dir_t dir);
void pc_save_bswap_keep_original(mCD_keep_original_c* orig, pc_bswap_dir_t dir);
void pc_save_bswap_keep_diary(mCD_keep_diary_c* diary, pc_bswap_dir_t dir);

/* Round-trip verification: swap BE->LE->BE and compare.
 * Returns 0 on match, >0 = mismatch count, -1 = error. */
int pc_save_bswap_verify_roundtrip(const u8* original_be, u32 size);
int pc_save_bswap_verify_roundtrip_mail(const u8* original_be, u32 size);
int pc_save_bswap_verify_roundtrip_original(const u8* original_be, u32 size);
int pc_save_bswap_verify_roundtrip_diary(const u8* original_be, u32 size);

/* Byte-swap foreigner (passport) data for Card B travel */
void pc_save_bswap_foreigner(mCD_foreigner_c* f, pc_bswap_dir_t dir);

/* Compute BE checksum matching mFRm_GetFlatCheckSum on real GC */
u16 pc_checksum_be(const u8* data, u32 size, u16 old_checksum);

#ifdef __cplusplus
}
#endif

#endif /* PC_SAVE_BSWAP_H */
