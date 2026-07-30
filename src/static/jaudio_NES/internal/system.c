#include "jaudio_NES/system.h"

#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/os.h"
#include "jaudio_NES/channel.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/audioheaders.h"
#include <dolphin/os.h>
#ifdef TARGET_PC
#include <dolphin/ar.h>
#include <stdlib.h>
#endif

#define MK_BGLOAD_MSG(retData, tableType, id, loadStatus) \
    (((retData) << 24) | ((tableType) << 16) | ((id) << 8) | (loadStatus))
#define BGLOAD_TBLTYPE(v) ((v >> 16) & 0xFF)
#define BGLOAD_ID(v) ((v >> 8) & 0xFF)
#define BGLOAD_LOAD_STATUS(v) ((v >> 0) & 0xFF)

#ifdef TARGET_PC
#include "pc_bswap.h"
#define BSWAP16(x) pc_bswap16(x)
#define BSWAP32(x) pc_bswap32(x)

/* Swap a u32 in-place at a given address */
static inline void swap32_inplace(void* p) {
    u32* pp = (u32*)p;
    *pp = pc_bswap32(*pp);
}

/* Swap a s16 in-place */
static inline void swap16_inplace(void* p) {
    u16* pp = (u16*)p;
    *pp = pc_bswap16(*pp);
}

/**
 * Byte-swap the bank control block's u32 pointer-offset table.
 * The first (2 + n_instruments) u32s are offsets to perc table, sfx table,
 * and each instrument entry.
 */
static void pc_swap_bank_ctrl_offsets(u8* ctrl_p, s32 n_entries) {
    u32* p = (u32*)ctrl_p;
    for (s32 i = 0; i < n_entries; i++) {
        p[i] = BSWAP32(p[i]);
    }
}

/**
 * Byte-swap a perctable's multi-byte fields in-place.
 * Layout: u8 decay_idx, u8 pan, u8 is_relocated, u8 pad,
 *         wtstr tuned_sample {smzwavetable* wavetable(4), f32 tuning(4)},
 *         envdat* envelope(4)
 */
static void pc_swap_perctable(perctable* pt) {
    /* tuned_sample.wavetable pointer (offset before relocation) */
    swap32_inplace(&pt->tuned_sample.wavetable);
    /* tuned_sample.tuning (f32) */
    swap32_inplace(&pt->tuned_sample.tuning);
    /* envelope pointer (offset before relocation) */
    swap32_inplace(&pt->envelope);
}

/**
 * Byte-swap a voicetable's multi-byte fields in-place.
 * Layout: u8 is_relocated, u8 normal_range_low, u8 normal_range_high,
 *         u8 adsr_decay_idx, envdat* envelope(4),
 *         wtstr low{ptr(4), f32(4)}, wtstr normal{ptr(4), f32(4)},
 *         wtstr high{ptr(4), f32(4)}
 */
static void pc_swap_voicetable(voicetable* vt) {
    swap32_inplace(&vt->envelope);
    swap32_inplace(&vt->low_pitch_tuned_sample.wavetable);
    swap32_inplace(&vt->low_pitch_tuned_sample.tuning);
    swap32_inplace(&vt->normal_pitch_tuned_sample.wavetable);
    swap32_inplace(&vt->normal_pitch_tuned_sample.tuning);
    swap32_inplace(&vt->high_pitch_tuned_sample.wavetable);
    swap32_inplace(&vt->high_pitch_tuned_sample.tuning);
}

/**
 * Byte-swap a percvoicetable (sfx entry) — just wtstr {ptr(4), f32(4)}.
 */
static void pc_swap_percvoicetable(percvoicetable* pvt) {
    swap32_inplace(&pvt->tuned_sample.wavetable);
    swap32_inplace(&pvt->tuned_sample.tuning);
}

/**
 * Byte-swap a smzwavetable's fields. The first u32 is a bitfield
 * (bit31, codec, medium, bit26, is_relocated, size) that must be
 * swapped as a whole u32 so the bits shift to LE layout.
 */
static void pc_swap_smzwavetable(smzwavetable* wt) {
    swap32_inplace(wt);           /* first u32: bitfield */
    swap32_inplace(&wt->sample);  /* sample ptr/offset */
    swap32_inplace(&wt->loop);    /* loop ptr/offset */
    swap32_inplace(&wt->book);    /* book ptr/offset */
}

/**
 * Visited sets for adpcmbook/adpcmloop — prevents double-swap when
 * multiple wavetables share the same book or loop pointer.
 */
#define PC_BOOK_VISITED_MAX 256
static void* pc_book_visited[PC_BOOK_VISITED_MAX];
static u32 pc_book_visited_count = 0;
static void* pc_loop_visited[PC_BOOK_VISITED_MAX];
static u32 pc_loop_visited_count = 0;

/**
 * Byte-swap adpcmloop fields.
 */
static void pc_swap_adpcmloop(adpcmloop* lp) {
    for (u32 v = 0; v < pc_loop_visited_count; v++) {
        if (pc_loop_visited[v] == lp) return;
    }
    if (pc_loop_visited_count < PC_BOOK_VISITED_MAX) {
        pc_loop_visited[pc_loop_visited_count++] = lp;
    }
    lp->loop_start = BSWAP32(lp->loop_start);
    lp->loop_end = BSWAP32(lp->loop_end);
    lp->count = BSWAP32(lp->count);
    lp->sample_end = BSWAP32(lp->sample_end);
    if (lp->count > 0) {
        for (s32 i = 0; i < 16; i++) {
            lp->predictor_state[i] = BSWAP16(lp->predictor_state[i]);
        }
    }
}

/**
 * Byte-swap adpcmbook fields.
 */
static void pc_swap_adpcmbook(adpcmbook* bk) {
    for (u32 v = 0; v < pc_book_visited_count; v++) {
        if (pc_book_visited[v] == bk) return;
    }
    if (pc_book_visited_count < PC_BOOK_VISITED_MAX) {
        pc_book_visited[pc_book_visited_count++] = bk;
    }
    bk->order = BSWAP32(bk->order);
    bk->n_predictors = BSWAP32(bk->n_predictors);
    s32 n_entries = bk->order * bk->n_predictors * 8;
    for (s32 i = 0; i < n_entries; i++) {
        bk->codebook[i] = BSWAP16(bk->codebook[i]);
    }
}

/**
 * Byte-swap envdat array. envdat is {s16 delay, s16 value} pairs.
 * The array is terminated by delay <= 0.
 */
/* Track which envelope addresses have already been byte-swapped to prevent double-swap.
   Multiple instruments in a bank can share the same envelope pointer, so we must not
   swap the same data twice.
   - bank_visited: bank-embedded envelopes, reset for each bank relocation
   - seq_visited:  sequence-script envelopes, intentionally preserved across bank relocations */
#define PC_ENVDAT_VISITED_MAX 512
static void* pc_envdat_bank_visited[PC_ENVDAT_VISITED_MAX];
static u32 pc_envdat_bank_visited_count = 0;
static void* pc_envdat_seq_visited[PC_ENVDAT_VISITED_MAX];
static u32 pc_envdat_seq_visited_count = 0;

static void pc_reset_envdat_bank_visited(void) {
    pc_envdat_bank_visited_count = 0;
    pc_book_visited_count = 0;
    pc_loop_visited_count = 0;
}

static void pc_reset_envdat_seq_visited(void) {
    pc_envdat_seq_visited_count = 0;
}

static void pc_reset_envdat_visited_all(void) {
    pc_reset_envdat_bank_visited();
    pc_reset_envdat_seq_visited();
}

/**
 * Swap envdat array entries. Special delay values (from audiocommon.h):
 *   ADSR_DISABLE  =  0  (array terminator)
 *   ADSR_HANG     = -1  (hang forever, no entries after)
 *   ADSR_GOTO     = -2  (jump to index in value field, no entries after)
 *   ADSR_RESTART  = -3  (loop to start, no entries after)
 *   ADSR_SPECIAL4 = -4  (reads value, increments idx, CONTINUES to next entry)
 * Must continue past SPECIAL4 since it has sequential entries following it.
 */
static void pc_swap_envdat_entries(envdat* env) {
    for (s32 i = 0; ; i++) {
        env[i].delay = BSWAP16(env[i].delay);
        env[i].value = BSWAP16(env[i].value);
        /* ADSR_DISABLE (0) is the true array terminator */
        if (env[i].delay == 0) break;
        /* HANG (-1), GOTO (-2), RESTART (-3) are logical endpoints */
        if (env[i].delay == -1 || env[i].delay == -2 || env[i].delay == -3) break;
        /* SPECIAL4 (-4) continues to next entry — don't break */
        if (i > 64) break; /* safety limit */
    }
}

/* Swap envdat array from bank data (called during bank relocation) */
void pc_swap_envdat(envdat* env) {
    /* Check if already swapped */
    for (u32 v = 0; v < pc_envdat_bank_visited_count; v++) {
        if (pc_envdat_bank_visited[v] == env) return;
    }
    if (pc_envdat_bank_visited_count < PC_ENVDAT_VISITED_MAX) {
        pc_envdat_bank_visited[pc_envdat_bank_visited_count++] = env;
    }
    pc_swap_envdat_entries(env);
}

/* Swap envdat array from sequence data (called when script sets envelope pointer) */
void pc_swap_envdat_seq(envdat* env) {
    /* Check if already swapped */
    for (u32 v = 0; v < pc_envdat_seq_visited_count; v++) {
        if (pc_envdat_seq_visited[v] == env) return;
    }
    if (pc_envdat_seq_visited_count < PC_ENVDAT_VISITED_MAX) {
        pc_envdat_seq_visited[pc_envdat_seq_visited_count++] = env;
    }
    pc_swap_envdat_entries(env);
}

/**
 * Byte-swap the percussion pointer-offset array within the bank data.
 * After the perc table base offset is resolved, the perc table itself
 * is an array of u32 pointers to individual perctable entries.
 */
static void pc_swap_perc_ptr_array(u32* perc_tbl, s32 n_perc) {
    for (s32 i = 0; i < n_perc; i++) {
        perc_tbl[i] = BSWAP32(perc_tbl[i]);
    }
}

static u32 pc_swap_bank_init_count = 0;
#endif /* TARGET_PC */

static uintptr_t Nas_GetSyncDummy(u8* param0, s32 param1);

BOOL AUDIO_SYSTEM_READY = FALSE;
static void* FASTDMA_BUFFER = NULL;
Na_DmaProc NA_DMA_PROC = Z_osEPiStartDma;
Na_SyncProc NA_SYNC_PROC = Nas_GetSyncDummy;

static s32 Nas_StartDma(OSIoMesg* ioMsg, s32 priority, s32 direction, u32 device_addr, void* dram_addr, u32 size,
                        OSMesgQueue* mq, s32 medium, s8* dma_type);
s32 Nas_BankOfsToAddr(s32 bank_id, u8* ctrl_p, WaveMedia* wave_media, s32 async);

static s32 __Link_BankNum(s32 type, s32 id);
static u8* __Load_Ctrl(s32 id);
static u8* __Load_Seq(s32 id);
static u8* __Load_Bank_BG(s32 table_type, s32 id, s32 n_chunks, s32 ret_data, OSMesgQueue* ret_queue);
static s32 __Kill_Bank(s32 bank_id);
static ArcHeader* __Get_ArcHeader(s32 table_type);
static s32 __Nas_StartSeq(s32 group_idx, s32 seq_id, s32 param);
static u8* __Load_Bank(s32 table_type, s32 id, s32* did_alloc);
static uintptr_t __Load_Wave(s32 wave_id, u32* medium, s32 no_load);
static void* __Check_Cache(s32 table_type, s32 id);
#ifndef TARGET_PC
static void __WaveTouch(wtstr* wavetouch_str, u32 ram_addr, WaveMedia* wave_media);
#endif
static Bgload* Nas_BgCopyDisk(s32 dev_medium, u8* src, u8* dst, u32 size, s32 medium, s32 n_chunks, OSMesgQueue* mq,
                              s32 msg);
static Bgload* Nas_BgCopyReq(u8* src, u8* dst, u32 size, s32 medium, s32 n_chunks, OSMesgQueue* mq, s32 msg);
static smzwavetable* __GetWaveTable(s32 bank_id, s32 inst_id);
static void __Nas_SlowDiskCopy(u8* dev_addr, u8* ram_addr, u32 size, s32 medium);
static void __Nas_SlowCopy(lpscache* cache, s32 size);
static void __BgCopyDisk(Bgload* bgload, s32 reset_status);
static void __BgCopySub(Bgload* bgload, s32 reset_status);
static void __Nas_BgDiskCopy(u8* src, u8* dst, u32 size, s32 param);
static void __Nas_ExCopy(Bgload* bgload, s32 size);
static void __Nas_BgCopy(Bgload* bgload, s32 size);

u8 Nas_MapHeaderReadByte(s32 byteIndex) {
#ifdef TARGET_PC
    u16 word = AG.map_header[(u32)byteIndex >> 1];

    if (byteIndex & 1) {
        return word & 0xFF;
    }
    return word >> 8;
#else
    return ((u8*)AG.map_header)[byteIndex];
#endif
}

void Nas_WaveDmaFrameWork(void) {
    WaveLoad* wl;
    WaveLoad* wl2;
    u32 i;

    for (i = 0; i < AG.waveload_count; i++) {
        wl = &AG.waveload_list[i];

        if (wl->time_to_live != 0) {
            wl->time_to_live--;

            if (wl->time_to_live == 0) {
                wl->reuse_idx = AG.waveload_dma_queue0_wpos;
                AG.waveload_dma_queue0[AG.waveload_dma_queue0_wpos] = i;
                AG.waveload_dma_queue0_wpos++;
            }
        }
    }

    for (i = AG.waveload_count; i < AG.num_waveloads; i++) {
        wl2 = &AG.waveload_list[i];

        if (wl2->time_to_live != 0) {
            wl2->time_to_live--;

            if (wl2->time_to_live == 0) {
                wl2->reuse_idx = AG.waveload_dma_queue1_wpos;
                AG.waveload_dma_queue1[AG.waveload_dma_queue1_wpos] = i;
                AG.waveload_dma_queue1_wpos++;
            }
        }
    }

    AG._2648 = 0;
}

void* Nas_WaveDmaCallBack(u32 device_addr, u32 size, s32 arg2, u8* waveload_idx, s32 medium) {
    WaveLoad* waveload;
    s32 hasWaveload = FALSE;
    u32 waveloadDevAddr;
    u32 pad2;
    u32 waveloadIndex;
    u32 transfer;
    s32 bufferPos;
    u32 i;

    if (arg2 != 0 || *waveload_idx >= AG.waveload_count) {
        for (i = AG.waveload_count; i < AG.num_waveloads; i++) {
            waveload = &AG.waveload_list[i];
            bufferPos = device_addr - waveload->device_addr;
            if (0 <= bufferPos && (u32)bufferPos <= waveload->size - size) {
                // We already have a WAVELOAD request for this memory range.
                if (waveload->time_to_live == 0 && AG.waveload_dma_queue1_rpos != AG.waveload_dma_queue1_wpos) {
                    // Move the WAVELOAD out of the reuse queue, by swapping it with the
                    // read pos, and then incrementing the read pos.
                    if (waveload->reuse_idx != AG.waveload_dma_queue1_rpos) {
                        AG.waveload_dma_queue1[waveload->reuse_idx] =
                            AG.waveload_dma_queue1[AG.waveload_dma_queue1_rpos];
                        AG.waveload_list[AG.waveload_dma_queue1[AG.waveload_dma_queue1_rpos]].reuse_idx =
                            waveload->reuse_idx;
                    }
                    AG.waveload_dma_queue1_rpos++;
                }
                waveload->time_to_live = 32;
                *waveload_idx = (u8)i;
                return &waveload->ram_addr[device_addr - waveload->device_addr];
            }
        }

        if (arg2 == 0) {
            goto search_short_lived;
        }

        if (AG.waveload_dma_queue1_rpos != AG.waveload_dma_queue1_wpos && arg2 != 0) {
            // Allocate a WAVELOAD from reuse queue 2, unless full.
            waveloadIndex = AG.waveload_dma_queue1[AG.waveload_dma_queue1_rpos];
            AG.waveload_dma_queue1_rpos++;
            waveload = AG.waveload_list + waveloadIndex;
            hasWaveload = TRUE;
        }
    } else {
    search_short_lived:
        waveload = AG.waveload_list + *waveload_idx;
        for (i = 0; i <= AG.waveload_count; waveload = AG.waveload_list + i++) {
            bufferPos = device_addr - waveload->device_addr;
            if (0 <= bufferPos && (u32)bufferPos <= waveload->size - size) {
                // We already have WAVELOAD for this memory range.
                if (waveload->time_to_live == 0) {
                    // Move the WAVELOAD out of the reuse queue, by swapping it with the
                    // read pos, and then incrementing the read pos.
                    if (waveload->reuse_idx != AG.waveload_dma_queue0_rpos) {
                        AG.waveload_dma_queue0[waveload->reuse_idx] =
                            AG.waveload_dma_queue0[AG.waveload_dma_queue0_rpos];
                        AG.waveload_list[AG.waveload_dma_queue0[AG.waveload_dma_queue0_rpos]].reuse_idx =
                            waveload->reuse_idx;
                    }
                    AG.waveload_dma_queue0_rpos++;
                }
                waveload->time_to_live = 2;
                return waveload->ram_addr + (device_addr - waveload->device_addr);
            }
            waveload++;
        }
    }

    if (!hasWaveload) {
        if (AG.waveload_dma_queue0_rpos == AG.waveload_dma_queue0_wpos) {
            return NULL;
        }
        // Allocate a WAVELOAD from reuse queue 1.
        waveloadIndex = AG.waveload_dma_queue0[AG.waveload_dma_queue0_rpos];
        AG.waveload_dma_queue0_rpos++;
        waveload = AG.waveload_list + waveloadIndex;
        hasWaveload = TRUE;
    }

    transfer = waveload->size;
    waveloadDevAddr = ALIGN_PREV(device_addr, 32);
    waveload->time_to_live = 3;
    waveload->device_addr = waveloadDevAddr;
    waveload->size_unused = transfer;
    Nas_StartDma(&AG.cur_adio_frame_dma_io_mesg_buf[AG.current_frame_dma_count++], 0 /* OS_MESG_PRI_NORMAL */,
                 0 /* OS_READ */, waveloadDevAddr, waveload->ram_addr, transfer, &AG.cur_audio_frame_dma_queue, medium,
                 (s8*)"SUPERDMA");
    *waveload_idx = waveloadIndex;
    return (device_addr - waveloadDevAddr) + waveload->ram_addr;
}

void Nas_WaveDmaNew(s32 n_channels) {
    WaveLoad* waveload;
    s32 i;
    s32 t2;

    AG.waveload_dma_cur_buf_size = AG.waveload_dma_buf0_size;
    AG.waveload_list =
        (WaveLoad*)Nas_HeapAlloc(&AG.misc_heap, 4 * AG.num_channels * sizeof(WaveLoad) * AG.audio_params.spec);
    t2 = 3 * AG.num_channels * AG.audio_params.spec;
    for (i = 0; i < t2; i++) {
        waveload = &AG.waveload_list[AG.num_waveloads];
        // waveload->ram_addr = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, AG.waveload_dma_cur_buf_size);
        if ((waveload->ram_addr = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, AG.waveload_dma_cur_buf_size)) == NULL) {
            break;
        }

        Nas_CacheOff(waveload->ram_addr, AG.waveload_dma_cur_buf_size);
        waveload->size = AG.waveload_dma_cur_buf_size;
        waveload->device_addr = 0;
        waveload->size_unused = 0;
        waveload->unused = 0;
        waveload->time_to_live = 0;
        AG.num_waveloads++;
    }

    for (i = 0; (u32)i < AG.num_waveloads; i++) {
        AG.waveload_dma_queue0[i] = i;
        AG.waveload_list[i].reuse_idx = i;
    }

    for (i = AG.num_waveloads; i < 0x100; i++) {
        AG.waveload_dma_queue0[i] = 0;
    }

    AG.waveload_dma_queue0_rpos = 0;
    AG.waveload_dma_queue0_wpos = AG.num_waveloads;
    AG.waveload_count = AG.num_waveloads;
    AG.waveload_dma_cur_buf_size = AG.waveload_dma_buf1_size;

    for (i = 0; i < AG.num_channels; i++) {
        waveload = &AG.waveload_list[AG.num_waveloads];
        // waveload->ram_addr = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, AG.waveload_dma_cur_buf_size);
        if ((waveload->ram_addr = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, AG.waveload_dma_cur_buf_size)) == NULL) {
            break;
        }

        Nas_CacheOff(waveload->ram_addr, AG.waveload_dma_cur_buf_size);
        waveload->size = AG.waveload_dma_cur_buf_size;
        waveload->device_addr = 0U;
        waveload->size_unused = 0;
        waveload->unused = 0;
        waveload->time_to_live = 0;
        AG.num_waveloads++;
    }

    for (i = AG.waveload_count; (u32)i < AG.num_waveloads; i++) {
        AG.waveload_dma_queue1[i - AG.waveload_count] = i;
        AG.waveload_list[i].reuse_idx = i - AG.waveload_count;
    }

    for (i = AG.num_waveloads; i < 0x100; i++) {
        AG.waveload_dma_queue1[i] = AG.waveload_count;
    }

    AG.waveload_dma_queue1_rpos = 0;
    AG.waveload_dma_queue1_wpos = AG.num_waveloads - AG.waveload_count;
}

BOOL Nas_CheckIDbank(s32 id) {
    if (id == 0xFF) {
        return TRUE;
    }

    if (AG.bank_load_status[id] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    if (AG.bank_load_status[__Link_BankNum(BANK_TABLE, id)] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    return FALSE;
}

BOOL Nas_CheckIDseq(s32 id) {
    if (id == 0xFF) {
        return TRUE;
    }

    if (AG.sequence_load_status[id] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    if (AG.sequence_load_status[__Link_BankNum(SEQUENCE_TABLE, id)] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    return FALSE;
}

// @unused
BOOL Nas_CheckIDwave(s32 id) {
    if (id == 0xFF) {
        return TRUE;
    }

    if (AG.wave_load_status[id] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    if (AG.wave_load_status[__Link_BankNum(WAVE_TABLE, id)] >= LOAD_STATUS_COMPLETE) {
        return TRUE;
    }

    return FALSE;
}

void Nas_WriteIDbank(s32 id, s32 status) {
    if (id != 0xFF && AG.bank_load_status[id] != LOAD_STATUS_PERMANENT) {
        AG.bank_load_status[id] = status;
    }
}

void Nas_WriteIDseq(s32 id, s32 status) {
    if (id != 0xFF && AG.sequence_load_status[id] != LOAD_STATUS_PERMANENT) {
        AG.sequence_load_status[id] = status;
    }
}

void Nas_WriteIDwave(s32 id, s32 status) {
    if (id != 0xFF) {
        if (AG.wave_load_status[id] != LOAD_STATUS_PERMANENT) {
            AG.wave_load_status[id] = status;
        }

        if (AG.wave_load_status[id] == LOAD_STATUS_PERMANENT || AG.wave_load_status[id] == LOAD_STATUS_COMPLETE) {
            EntryWave(id);
        }
    }
}

void Nas_WriteIDwaveOnly(s32 id, s32 status) {
    if (id != 0xFF && AG.wave_load_status[id] != LOAD_STATUS_PERMANENT) {
        AG.wave_load_status[id] = status;
    }
}

void Nas_BankHeaderInit(ArcHeader* header, u8* data, u16 medium) {
    s32 i;

    header->medium = medium;
    header->pData = data;

    for (i = 0; i < header->numEntries; i++) {
        if (header->entries[i].size != 0 && header->entries[i].medium == MEDIUM_CART) {
            header->entries[i].addr += (u32)(uintptr_t)data;
        }
    }
}

void* Nas_PreLoadBank(s32 seq_id, s32* bank_id) {
    s32 l_bank_id;
    s32 i;
    s32 idx;
    void* ctrl;

    l_bank_id = 0xFF;
    idx = AG.map_header[seq_id];
    for (i = Nas_MapHeaderReadByte(idx++); i > 0; i--) {
        l_bank_id = Nas_MapHeaderReadByte(idx++);
        ctrl = __Load_Ctrl(l_bank_id);
    }

    *bank_id = l_bank_id;
    return ctrl;
}

void Nas_PreLoadSeq(s32 seq_id, s32 flags, s32 cmd, OSMesgQueue* mq) {
    s32 bank_id;

    if ((flags & AUDIO_PRELOAD_BANK)) {
        Nas_PreLoadBank(seq_id, &bank_id);
    }

    if ((flags & AUDIO_PRELOAD_SEQ)) {
        __Load_Seq(seq_id);
    }

    if (cmd != 0) {
        Z_osSendMesg(mq, (void*)(uintptr_t)(u32)(cmd << 24), OS_MESG_NOBLOCK);
    }
}

static s32 __Nas_LoadVoice_Inner(smzwavetable* wavetable, s32 bank_id) {
    u8* sample_addr;

    if (wavetable->is_relocated == TRUE) {
        if (wavetable->medium != MEDIUM_RAM) {
            sample_addr =
                (u8*)Nas_Alloc_Single(wavetable->size, bank_id, wavetable->sample, wavetable->medium, CACHE_PERSISTENT);
            if (sample_addr == NULL) {
                return -1;
            }

            if (wavetable->medium == MEDIUM_DISK) {
                Nas_FastDiskCopy(wavetable->sample, sample_addr, wavetable->size, AG.wave_header->medium);
            } else {
                Nas_FastCopy((uintptr_t)wavetable->sample, sample_addr, wavetable->size, wavetable->medium);
            }

            wavetable->medium = MEDIUM_RAM;
            wavetable->sample = sample_addr;
        }
    }

    return 0;
}

s32 Nas_LoadVoice(s32 bank_id, s32 instId, s32 drumId) {
    if (instId < 0x7F) {
        voicetable* voice = ProgToVp(bank_id, instId);

        if (voice == NULL) {
            return -1;
        }
        if (voice->normal_range_low != 0) {
            __Nas_LoadVoice_Inner(voice->low_pitch_tuned_sample.wavetable, bank_id);
        }
        __Nas_LoadVoice_Inner(voice->normal_pitch_tuned_sample.wavetable, bank_id);
        if (voice->normal_range_high != 0x7F) {
            __Nas_LoadVoice_Inner(voice->high_pitch_tuned_sample.wavetable, bank_id);
        }
    } else if (instId == 0x7F) {
        perctable* perc = PercToPp(bank_id, drumId);

        if (perc == NULL) {
            return -1;
        }
        __Nas_LoadVoice_Inner(perc->tuned_sample.wavetable, bank_id);
        return 0;
    }

    return 0;
}

s32 Nas_PreLoad_BG(s32 table_type, s32 id, s32 n_chunks, s32 ret_data, OSMesgQueue* ret_queue) {
    if (__Load_Bank_BG(table_type, id, n_chunks, ret_data, ret_queue) == NULL) {
        Z_osSendMesg(ret_queue, (OSMesg)-1, OS_MESG_NOBLOCK);
    }

    return 0;
}

s32 Nas_PreLoadSeq_BG(s32 id, s32 param_2, s32 ret_data, OSMesgQueue* ret_queue) {
    Nas_PreLoad_BG(SEQUENCE_TABLE, id, 0, ret_data, ret_queue);

    return 0;
}

s32 Nas_PreLoadWave_BG(s32 id, s32 param_2, s32 ret_data, OSMesgQueue* ret_queue) {
    Nas_PreLoad_BG(WAVE_TABLE, id, 0, ret_data, ret_queue);

    return 0;
}

s32 Nas_PreLoadBank_BG(s32 id, s32 param_2, s32 ret_data, OSMesgQueue* ret_queue) {
    Nas_PreLoad_BG(BANK_TABLE, id, 0, ret_data, ret_queue);

    return 0;
}

// @unused
u8* Nas_SeqToBank(s32 seq_id, s32* num_banks) {
    s32 index = AG.map_header[seq_id];
    s32 i;

    *num_banks = Nas_MapHeaderReadByte(index++);
    if (*num_banks == 0) {
        return NULL;
    }
#ifdef TARGET_PC
    static u8 seq_to_bank_ids[0x100];

    if (*num_banks > 0x100) {
        *num_banks = 0x100;
    }

    for (i = 0; i < *num_banks; i++) {
        seq_to_bank_ids[i] = Nas_MapHeaderReadByte(index++);
    }

    return seq_to_bank_ids;
#else
    return &((u8*)AG.map_header)[index];
#endif
}

void Nas_FlushBank(s32 seq_id) {
    s32 bank_id;
    s32 bank_count;
    s32 index = AG.map_header[seq_id];

    bank_count = Nas_MapHeaderReadByte(index++);
    while (bank_count > 0) {
        bank_count--;
        bank_id = Nas_MapHeaderReadByte(index++);
        bank_id = __Link_BankNum(BANK_TABLE, bank_id);
        if (EmemOnCheck(BANK_TABLE, bank_id) == NULL) {
            __Kill_Bank(bank_id);
            Nas_WriteIDbank(bank_id, LOAD_STATUS_NOT_LOADED);
        }
    }
}

static s32 __Kill_Bank(s32 bank_id) {
    u32 i;
    SZHeap* heap = &AG.bank_heap;
    SZAuto* auto_;
    SZStay* stay;

    auto_ = &heap->auto_heap;
    if (auto_->entries[0].id == bank_id) {
        auto_->entries[0].id = -1;
    } else if (auto_->entries[1].id == bank_id) {
        auto_->entries[1].id = -1;
    }

    stay = &heap->stay_heap;
    for (i = 0; i < stay->num_entries; i++) {
        if (bank_id == stay->entries[i].id) {
            stay->entries[i].id = -1;
        }
    }

    Nas_ForceStopChannel(bank_id);
    return 0;
}

void Nas_SetExtPointer(s32 table_type, s32 idx, s32 param_3, s32 data) {
    ArcHeader* header = __Get_ArcHeader(table_type);

    if (header->entries[idx].medium == MEDIUM_RAM_UNLOADED) {
        switch (param_3) {
            case EXT_TYPE_DATA:
                header->entries[idx].addr = (u32)data;
                break;
            case EXT_TYPE_SIZE:
                header->entries[idx].size = data;
                break;
        }
    }
}

s32 Nas_StartMySeq(s32 group_idx, s32 seq_id, s32 param) {
    if (AG.reset_timer != 0) {
        return 0;
    }

    AG.groups_p[group_idx]->skip_ticks = 0;
    return __Nas_StartSeq(group_idx, seq_id, param);
}

s32 Nas_StartSeq_Skip(s32 group_idx, s32 seq_id, s32 skip_ticks) {
    if (AG.reset_timer != 0) {
        return 0;
    }

    AG.groups_p[group_idx]->skip_ticks = skip_ticks;
    return __Nas_StartSeq(group_idx, seq_id, 0);
}

static s32 __Nas_StartSeq(s32 group_idx, s32 seq_id, s32 param) {
    group* group = AG.groups_p[group_idx];
    u8* seq_p;
    s32 bank_id;
    s32 i;
    s32 idx;

    Nas_ReleaseGroup(group);
    bank_id = 0xFF;
    idx = AG.map_header[seq_id];
    for (i = Nas_MapHeaderReadByte(idx++); i > 0; i--) {
        bank_id = Nas_MapHeaderReadByte(idx++);
        __Load_Ctrl(bank_id);
    }

    seq_p = __Load_Seq(seq_id);
    if (seq_p == NULL) {
        return 0;
    }

    Nas_InitMySeq(group);
    group->seq_id = seq_id;

    if (bank_id != 0xFF) {
        bank_id = __Link_BankNum(BANK_TABLE, bank_id);
        group->bank_id = bank_id;
    } else {
        group->bank_id = 0xFF;
    }

    group->seq_data = seq_p;
    group->macro_player.pc = seq_p;
    group->macro_player.depth = 0;
    group->delay = 0;
    group->flags.enabled = TRUE;
    group->flags.finished = FALSE;
    group->group_idx = group_idx;

    return 0;
}

static u8* __Load_Seq(s32 seq_id) {
    s32 did_alloc;
    s32 link_id;

    link_id = __Link_BankNum(SEQUENCE_TABLE, seq_id);
    if (AG.sequence_load_status[link_id] == LOAD_STATUS_IN_PROGRESS) {
        return NULL;
    }

    return (u8*)__Load_Bank(SEQUENCE_TABLE, seq_id, &did_alloc);
}

static uintptr_t __Load_Wave_Check(s32 wave_id, u32* medium) {
    return __Load_Wave(wave_id, medium, TRUE);
}

static uintptr_t __Load_Wave(s32 wave_id, u32* medium, s32 no_load) {
    void* ram_p;
    s32 link_id = __Link_BankNum(WAVE_TABLE, wave_id);
    ArcHeader* header = __Get_ArcHeader(WAVE_TABLE);

    ram_p = __Check_Cache(WAVE_TABLE, link_id);
    if (ram_p != NULL) {
        if (AG.wave_load_status[link_id] != LOAD_STATUS_IN_PROGRESS) {
            Nas_WriteIDwaveOnly(link_id, LOAD_STATUS_COMPLETE);
        }

        *medium = MEDIUM_RAM;
        return (uintptr_t)ram_p;
    }

    if (header->entries[wave_id].cacheType == CACHE_LOAD_EITHER_NOSYNC || no_load == TRUE) {
        *medium = header->entries[wave_id].medium;
        return header->entries[link_id].addr;
    }

    ram_p = __Load_Bank(WAVE_TABLE, wave_id, &no_load);
    if (ram_p != NULL) {
        *medium = MEDIUM_RAM;
        return (uintptr_t)ram_p;
    }

    *medium = header->entries[wave_id].medium;
    return header->entries[link_id].addr;
}

static u8* __Load_Ctrl(s32 bank_id) {
    u8* ctrl_p;
    s32 wave_id0;
    s32 wave_id1;
    s32 did_alloc;
    WaveMedia wave_media;
    s32 link_id = __Link_BankNum(BANK_TABLE, bank_id);

    if (AG.bank_load_status[link_id] == LOAD_STATUS_IN_PROGRESS) {
        return NULL;
    }

    wave_id0 = AG.voice_info[link_id].wave_bank_id0;
    wave_id1 = AG.voice_info[link_id].wave_bank_id1;

    wave_media.wave0_bank_id = wave_id0;
    wave_media.wave1_bank_id = wave_id1;

    if (wave_id0 != 0xFF) {
        wave_media.wave0_p = (void*)__Load_Wave(wave_id0, &wave_media.wave0_media, FALSE);
    } else {
        wave_media.wave0_p = NULL;
    }

    if (wave_id1 != 0xFF) {
        wave_media.wave1_p = (void*)__Load_Wave(wave_id1, &wave_media.wave1_media, FALSE);
    } else {
        wave_media.wave1_p = NULL;
    }

    ctrl_p = __Load_Bank(BANK_TABLE, bank_id, &did_alloc);
    if (ctrl_p == NULL) {
        return NULL;
    }

    if (did_alloc == TRUE) {
        Nas_BankOfsToAddr(link_id, ctrl_p, &wave_media, FALSE);
    }

    return ctrl_p;
}

static u8* __Load_Bank(s32 table_type, s32 id, s32* did_alloc) {
    u32 size;
    ArcHeader* header;
    s32 medium;
    s32 load_status;
    u8* ram_addr;
    s32 cache_type;
    u8* rom_addr;
    s32 link_id;

    link_id = __Link_BankNum(table_type, id);
    ram_addr = (u8*)__Check_Cache(table_type, link_id);
    if (ram_addr != NULL) {
        *did_alloc = FALSE;
        load_status = LOAD_STATUS_COMPLETE;
    } else {
        header = __Get_ArcHeader(table_type);
        size = header->entries[link_id].size;
        size = ALIGN_NEXT(size, 32);
        medium = header->entries[id].medium;
        cache_type = header->entries[id].cacheType;
        rom_addr = (u8*)(uintptr_t)header->entries[link_id].addr;
        switch (cache_type) {
            case CACHE_LOAD_PERMANENT:
                ram_addr = (u8*)EmemAlloc(table_type, link_id, size);
                if (ram_addr == NULL) {
                    return ram_addr;
                }
                break;

            case CACHE_LOAD_PERSISTENT:
                ram_addr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_PERSISTENT, link_id);
                if (ram_addr == NULL) {
                    return ram_addr;
                }
                break;

            case CACHE_LOAD_TEMPORARY:
                ram_addr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_TEMPORARY, link_id);
                if (ram_addr == NULL) {
                    return ram_addr;
                }
                break;

            case CACHE_LOAD_EITHER:
            case CACHE_LOAD_EITHER_NOSYNC:
                ram_addr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_EITHER, link_id);
                if (ram_addr == NULL) {
                    return ram_addr;
                }
                break;
        }

        *did_alloc = TRUE;

        if (medium == MEDIUM_RAM_UNLOADED) {
            voiceinfo* vinfo;

            if (rom_addr == NULL) {
                return NULL;
            }

            if (table_type == BANK_TABLE) {
                size -= sizeof(ArcEntry);
                vinfo = &AG.voice_info[link_id];
                vinfo->num_instruments = ((u16*)rom_addr)[0];
                vinfo->num_drums = ((u16*)rom_addr)[1];
                vinfo->num_sfx = ((u16*)rom_addr)[2];
                rom_addr += sizeof(ArcEntry);
            }

            Z_bcopy(rom_addr, ram_addr, size);
        } else if (medium == MEDIUM_DISK) {
            Nas_FastDiskCopy(rom_addr, ram_addr, size, header->medium);
        } else {
            Nas_FastCopy((uintptr_t)rom_addr, ram_addr, size, medium);
        }

        if (cache_type == CACHE_LOAD_PERMANENT) {
            load_status = LOAD_STATUS_PERMANENT;
        } else {
            load_status = LOAD_STATUS_COMPLETE;
        }
    }

    switch (table_type) {
        case SEQUENCE_TABLE:
            Nas_WriteIDseq(link_id, load_status);
            break;

        case BANK_TABLE:
            Nas_WriteIDbank(link_id, load_status);
            break;

        case WAVE_TABLE:
            Nas_WriteIDwave(link_id, load_status);
            break;

        default:
            break;
    }

    return ram_addr;
}

static s32 __Link_BankNum(s32 type, s32 id) {
    ArcHeader* header = __Get_ArcHeader(type);

    if (header->entries[id].size == 0) {
        id = header->entries[id].addr;
    }

    return id;
}

static void* __Check_Cache(s32 table_type, s32 id) {
    void* ram_p;

    ram_p = EmemOnCheck(table_type, id);
    if (ram_p) {
        return ram_p;
    }

    ram_p = Nas_SzCacheCheck(table_type, CACHE_EITHER, id);
    if (ram_p) {
        return ram_p;
    }

    return NULL;
}

static ArcHeader* __Get_ArcHeader(s32 table_type) {
    switch (table_type) {
        case SEQUENCE_TABLE:
            return AG.seq_header;
        case BANK_TABLE:
            return AG.bank_header;
        case WAVE_TABLE:
            return AG.wave_header;
        default:
            return NULL;
    }
}

#ifdef TARGET_PC
/* Serialized bank pointers are 32-bit BE offsets. Decode to a native graph. */
enum {
    PC_BANK_MAP_WAVE = 1,
    PC_BANK_MAP_ENV,
    PC_BANK_MAP_LOOP,
    PC_BANK_MAP_BOOK,
    PC_BANK_MAP_VOICE,
    PC_BANK_MAP_PERC,
};

typedef struct PCBankAllocation {
    void* ptr;
    struct PCBankAllocation* next;
} PCBankAllocation;

typedef struct PCBankMapEntry {
    u32 offset;
    u8 kind;
    void* ptr;
} PCBankMapEntry;

typedef struct PCBankParseContext {
    const u8* data;
    u32 size;
    s32 bank_id;
    WaveMedia* wave_media;
    PCBankMapEntry* map;
    u32 map_count;
    u32 map_capacity;
    BOOL failed;
} PCBankParseContext;

#define PC_NATIVE_BANK_MAX 256
#define PC_BANK_MAP_CAPACITY 2048

static PCBankAllocation* pc_native_bank_allocations[PC_NATIVE_BANK_MAX];

static u16 pc_bank_read_be16(const u8* p) {
    return ((u16)p[0] << 8) | p[1];
}

static u32 pc_bank_read_be32(const u8* p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
}

static f32 pc_bank_read_be_f32(const u8* p) {
    union {
        u32 word;
        f32 value;
    } value;
    value.word = pc_bank_read_be32(p);
    return value.value;
}

static BOOL pc_bank_range_valid(const PCBankParseContext* ctx, u32 offset, u32 length) {
    return offset <= ctx->size && length <= ctx->size - offset;
}

static void pc_bank_release_native_graph(s32 bank_id) {
    PCBankAllocation* allocation;

    if (bank_id < 0 || bank_id >= PC_NATIVE_BANK_MAX) {
        return;
    }
    allocation = pc_native_bank_allocations[bank_id];
    while (allocation != NULL) {
        PCBankAllocation* next = allocation->next;
        free(allocation->ptr);
        free(allocation);
        allocation = next;
    }
    pc_native_bank_allocations[bank_id] = NULL;
}

static void* pc_bank_alloc(PCBankParseContext* ctx, size_t size) {
    PCBankAllocation* allocation;
    void* ptr;

    if (ctx->bank_id < 0 || ctx->bank_id >= PC_NATIVE_BANK_MAX || size == 0) {
        ctx->failed = TRUE;
        return NULL;
    }
    ptr = calloc(1, size);
    allocation = (PCBankAllocation*)malloc(sizeof(*allocation));
    if (ptr == NULL || allocation == NULL) {
        free(ptr);
        free(allocation);
        ctx->failed = TRUE;
        return NULL;
    }
    allocation->ptr = ptr;
    allocation->next = pc_native_bank_allocations[ctx->bank_id];
    pc_native_bank_allocations[ctx->bank_id] = allocation;
    return ptr;
}

static void* pc_bank_map_find(const PCBankParseContext* ctx, u8 kind, u32 offset) {
    u32 i;
    for (i = 0; i < ctx->map_count; i++) {
        if (ctx->map[i].kind == kind && ctx->map[i].offset == offset) {
            return ctx->map[i].ptr;
        }
    }
    return NULL;
}

static void pc_bank_map_add(PCBankParseContext* ctx, u8 kind, u32 offset, void* ptr) {
    if (ctx->map_count >= ctx->map_capacity) {
        ctx->failed = TRUE;
        return;
    }
    ctx->map[ctx->map_count].kind = kind;
    ctx->map[ctx->map_count].offset = offset;
    ctx->map[ctx->map_count].ptr = ptr;
    ctx->map_count++;
}

static envdat* pc_bank_parse_envelope(PCBankParseContext* ctx, u32 offset) {
    envdat* result;
    u32 count;
    u32 i;

    if (offset == 0) {
        return NULL;
    }
    result = (envdat*)pc_bank_map_find(ctx, PC_BANK_MAP_ENV, offset);
    if (result != NULL) {
        return result;
    }

    for (count = 0; count < 65; count++) {
        s16 delay;
        if (!pc_bank_range_valid(ctx, offset + count * 4, 4)) {
            ctx->failed = TRUE;
            return NULL;
        }
        delay = (s16)pc_bank_read_be16(ctx->data + offset + count * 4);
        if (delay == 0 || delay == -1 || delay == -2 || delay == -3) {
            count++;
            break;
        }
    }
    if (count == 0 || count > 65) {
        ctx->failed = TRUE;
        return NULL;
    }

    result = (envdat*)pc_bank_alloc(ctx, count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_ENV, offset, result);
    for (i = 0; i < count; i++) {
        result[i].delay = (s16)pc_bank_read_be16(ctx->data + offset + i * 4);
        result[i].value = (s16)pc_bank_read_be16(ctx->data + offset + i * 4 + 2);
    }
    return result;
}

static adpcmloop* pc_bank_parse_loop(PCBankParseContext* ctx, u32 offset) {
    adpcmloop* result;
    u32 count;
    u32 size;
    u32 i;

    if (offset == 0) {
        return NULL;
    }
    result = (adpcmloop*)pc_bank_map_find(ctx, PC_BANK_MAP_LOOP, offset);
    if (result != NULL) {
        return result;
    }
    if (!pc_bank_range_valid(ctx, offset, 16)) {
        ctx->failed = TRUE;
        return NULL;
    }
    count = pc_bank_read_be32(ctx->data + offset + 8);
    size = count == 0 ? 16 : 48;
    if (!pc_bank_range_valid(ctx, offset, size)) {
        ctx->failed = TRUE;
        return NULL;
    }

    result = (adpcmloop*)pc_bank_alloc(ctx, size);
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_LOOP, offset, result);
    result->loop_start = pc_bank_read_be32(ctx->data + offset);
    result->loop_end = pc_bank_read_be32(ctx->data + offset + 4);
    result->count = count;
    result->sample_end = pc_bank_read_be32(ctx->data + offset + 12);
    if (count != 0) {
        for (i = 0; i < 16; i++) {
            result->predictor_state[i] = (s16)pc_bank_read_be16(ctx->data + offset + 16 + i * 2);
        }
    }
    return result;
}

static adpcmbook* pc_bank_parse_book(PCBankParseContext* ctx, u32 offset) {
    adpcmbook* result;
    s32 order;
    s32 predictors;
    u32 entry_count;
    u32 size;
    u32 i;

    if (offset == 0) {
        return NULL;
    }
    result = (adpcmbook*)pc_bank_map_find(ctx, PC_BANK_MAP_BOOK, offset);
    if (result != NULL) {
        return result;
    }
    if (!pc_bank_range_valid(ctx, offset, 8)) {
        ctx->failed = TRUE;
        return NULL;
    }
    order = (s32)pc_bank_read_be32(ctx->data + offset);
    predictors = (s32)pc_bank_read_be32(ctx->data + offset + 4);
    if (order <= 0 || predictors <= 0 || order > 64 || predictors > 64) {
        ctx->failed = TRUE;
        return NULL;
    }
    entry_count = (u32)order * (u32)predictors * 8;
    size = 8 + entry_count * sizeof(s16);
    if (!pc_bank_range_valid(ctx, offset, size)) {
        ctx->failed = TRUE;
        return NULL;
    }

    result = (adpcmbook*)pc_bank_alloc(ctx, size);
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_BOOK, offset, result);
    result->order = order;
    result->n_predictors = predictors;
    for (i = 0; i < entry_count; i++) {
        result->codebook[i] = (s16)pc_bank_read_be16(ctx->data + offset + 8 + i * 2);
    }
    return result;
}

static smzwavetable* pc_bank_parse_wavetable(PCBankParseContext* ctx, u32 offset) {
    smzwavetable* result;
    u32 flags;
    u32 sample_offset;
    u32 loop_offset;
    u32 book_offset;

    if (offset == 0) {
        return NULL;
    }
    result = (smzwavetable*)pc_bank_map_find(ctx, PC_BANK_MAP_WAVE, offset);
    if (result != NULL) {
        return result;
    }
    if (!pc_bank_range_valid(ctx, offset, 16)) {
        ctx->failed = TRUE;
        return NULL;
    }

    result = (smzwavetable*)pc_bank_alloc(ctx, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_WAVE, offset, result);
    flags = pc_bank_read_be32(ctx->data + offset);
    sample_offset = pc_bank_read_be32(ctx->data + offset + 4);
    loop_offset = pc_bank_read_be32(ctx->data + offset + 8);
    book_offset = pc_bank_read_be32(ctx->data + offset + 12);
    result->bit31 = (flags >> 31) & 1;
    result->codec = (flags >> 28) & 7;
    result->medium = (flags >> 26) & 3;
    result->bit26 = (flags >> 25) & 1;
    result->size = flags & 0xFFFFFF;
    if (result->size != 0) {
        result->loop = pc_bank_parse_loop(ctx, loop_offset);
        result->book = pc_bank_parse_book(ctx, book_offset);
    }

    switch (result->medium) {
        case MEDIUM_RAM:
            result->sample = (u8*)((uintptr_t)ctx->wave_media->wave0_p + sample_offset);
            result->medium = ctx->wave_media->wave0_media;
            break;
        case MEDIUM_DISK:
            result->sample = (u8*)((uintptr_t)ctx->wave_media->wave1_p + sample_offset);
            result->medium = ctx->wave_media->wave1_media;
            break;
        default:
            result->sample = (u8*)(uintptr_t)sample_offset;
            break;
    }
    result->is_relocated = TRUE;
    if (result->bit26 && result->medium != MEDIUM_RAM &&
        AG.num_used_samples < ARRAY_COUNT(AG.used_samples)) {
        AG.used_samples[AG.num_used_samples++] = result;
    }
    return result;
}

static wtstr pc_bank_parse_tuned_sample(PCBankParseContext* ctx, u32 offset) {
    wtstr result = { NULL, 0.0f };
    if (!pc_bank_range_valid(ctx, offset, 8)) {
        ctx->failed = TRUE;
        return result;
    }
    result.wavetable = pc_bank_parse_wavetable(ctx, pc_bank_read_be32(ctx->data + offset));
    result.tuning = pc_bank_read_be_f32(ctx->data + offset + 4);
    return result;
}

static voicetable* pc_bank_parse_voice(PCBankParseContext* ctx, u32 offset) {
    voicetable* result;
    if (offset == 0) {
        return NULL;
    }
    result = (voicetable*)pc_bank_map_find(ctx, PC_BANK_MAP_VOICE, offset);
    if (result != NULL) {
        return result;
    }
    if (!pc_bank_range_valid(ctx, offset, 32)) {
        ctx->failed = TRUE;
        return NULL;
    }
    result = (voicetable*)pc_bank_alloc(ctx, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_VOICE, offset, result);
    result->is_relocated = TRUE;
    result->normal_range_low = ctx->data[offset + 1];
    result->normal_range_high = ctx->data[offset + 2];
    result->adsr_decay_idx = ctx->data[offset + 3];
    result->envelope = pc_bank_parse_envelope(ctx, pc_bank_read_be32(ctx->data + offset + 4));
    result->low_pitch_tuned_sample = pc_bank_parse_tuned_sample(ctx, offset + 8);
    result->normal_pitch_tuned_sample = pc_bank_parse_tuned_sample(ctx, offset + 16);
    result->high_pitch_tuned_sample = pc_bank_parse_tuned_sample(ctx, offset + 24);
    return result;
}

static perctable* pc_bank_parse_percussion(PCBankParseContext* ctx, u32 offset) {
    perctable* result;
    if (offset == 0) {
        return NULL;
    }
    result = (perctable*)pc_bank_map_find(ctx, PC_BANK_MAP_PERC, offset);
    if (result != NULL) {
        return result;
    }
    if (!pc_bank_range_valid(ctx, offset, 16)) {
        ctx->failed = TRUE;
        return NULL;
    }
    result = (perctable*)pc_bank_alloc(ctx, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    pc_bank_map_add(ctx, PC_BANK_MAP_PERC, offset, result);
    result->adsr_decay_idx = ctx->data[offset];
    result->pan = ctx->data[offset + 1];
    result->is_relocated = TRUE;
    result->tuned_sample = pc_bank_parse_tuned_sample(ctx, offset + 4);
    result->envelope = pc_bank_parse_envelope(ctx, pc_bank_read_be32(ctx->data + offset + 12));
    return result;
}

static BOOL pc_bank_parse_native_graph(s32 bank_id, const u8* ctrl_p, WaveMedia* wave_media) {
    PCBankParseContext ctx;
    voiceinfo* info;
    u32 percussion_offset;
    u32 effects_offset;
    u32 i;

    if (bank_id < 0 || bank_id >= AG.bank_header->numEntries || bank_id >= PC_NATIVE_BANK_MAX) {
        return FALSE;
    }
    pc_bank_release_native_graph(bank_id);
    memset(&ctx, 0, sizeof(ctx));
    ctx.data = ctrl_p;
    ctx.size = AG.bank_header->entries[bank_id].size;
    ctx.bank_id = bank_id;
    ctx.wave_media = wave_media;
    ctx.map_capacity = PC_BANK_MAP_CAPACITY;
    ctx.map = (PCBankMapEntry*)calloc(ctx.map_capacity, sizeof(*ctx.map));
    if (ctx.map == NULL || !pc_bank_range_valid(&ctx, 0, 8)) {
        free(ctx.map);
        return FALSE;
    }

    info = &AG.voice_info[bank_id];
    percussion_offset = pc_bank_read_be32(ctrl_p);
    effects_offset = pc_bank_read_be32(ctrl_p + 4);
    if (info->num_instruments > 126) {
        info->num_instruments = 126;
    }
    if (!pc_bank_range_valid(&ctx, 8, info->num_instruments * 4) ||
        (percussion_offset != 0 && !pc_bank_range_valid(&ctx, percussion_offset, info->num_drums * 4)) ||
        (effects_offset != 0 && !pc_bank_range_valid(&ctx, effects_offset, info->num_sfx * 8))) {
        ctx.failed = TRUE;
    }

    info->instruments = NULL;
    info->percussion = NULL;
    info->effects = NULL;
    if (!ctx.failed && info->num_instruments != 0) {
        info->instruments = (voicetable**)pc_bank_alloc(&ctx, info->num_instruments * sizeof(*info->instruments));
        for (i = 0; i < info->num_instruments && !ctx.failed; i++) {
            info->instruments[i] = pc_bank_parse_voice(&ctx, pc_bank_read_be32(ctrl_p + 8 + i * 4));
        }
    }
    if (!ctx.failed && info->num_drums != 0 && percussion_offset != 0) {
        info->percussion = (perctable**)pc_bank_alloc(&ctx, info->num_drums * sizeof(*info->percussion));
        for (i = 0; i < info->num_drums && !ctx.failed; i++) {
            info->percussion[i] = pc_bank_parse_percussion(
                &ctx, pc_bank_read_be32(ctrl_p + percussion_offset + i * 4));
        }
    }
    if (!ctx.failed && info->num_sfx != 0 && effects_offset != 0) {
        info->effects = (percvoicetable*)pc_bank_alloc(&ctx, info->num_sfx * sizeof(*info->effects));
        for (i = 0; i < info->num_sfx && !ctx.failed; i++) {
            info->effects[i].tuned_sample = pc_bank_parse_tuned_sample(&ctx, effects_offset + i * 8);
        }
    }

    free(ctx.map);
    if (ctx.failed) {
        info->instruments = NULL;
        info->percussion = NULL;
        info->effects = NULL;
        pc_bank_release_native_graph(bank_id);
        OSReport("[PC] Failed to decode audio bank %d (size=%u)\n", bank_id, ctx.size);
        return FALSE;
    }
    return TRUE;
}
#endif

#define OFS2RAM(base, ofs) ((u32)(ofs) + (u32)base)
#define BANK_ENTRY(ctrl, idx) (((u32*)((u32)ctrl)) + idx)

static void Nas_BankOfsToAddr_Inner(s32 bank_id, u8* ctrl_p, WaveMedia* wave_media) {
#ifdef TARGET_PC
    pc_bank_parse_native_graph(bank_id, ctrl_p, wave_media);
    return;
#else
    u32 ofs;
    u32 inst_ofs;
    voicetable* inst;
    perctable* percvt;
    percvoicetable* sfx;
    s32 i;
    s32 n_perc_inst, n_voice_inst, n_sfx_inst;
    n_voice_inst = AG.voice_info[bank_id].num_instruments;
    n_perc_inst = AG.voice_info[bank_id].num_drums;
    n_sfx_inst = AG.voice_info[bank_id].num_sfx;
    // u32* data_p = (u32*)ctrl_p;

#ifdef TARGET_PC
    /* Byte-swap the u32 offset table at the start of the bank ctrl block.
     * Entries: [0]=perc_tbl_ofs, [1]=sfx_tbl_ofs, [2..2+n_voice-1]=inst_ofs */
    {
        s32 n_ctrl_entries = 2 + (n_voice_inst > 126 ? 126 : n_voice_inst);
        pc_swap_bank_ctrl_offsets(ctrl_p, n_ctrl_entries);
        pc_swap_bank_init_count++;
    }
#endif

    ofs = *BANK_ENTRY(ctrl_p, 0);
    if (ofs != 0 && n_perc_inst != 0) {
        *BANK_ENTRY(ctrl_p, 0) = OFS2RAM(ctrl_p, ofs);

#ifdef TARGET_PC
        /* Swap the percussion pointer array (u32 offsets to each perctable) */
        pc_swap_perc_ptr_array((u32*)*BANK_ENTRY(ctrl_p, 0), n_perc_inst);
#endif

        for (i = 0; i < n_perc_inst; i++) {
            inst_ofs = (u32)((perctable**)*BANK_ENTRY(ctrl_p, 0))[i];
            if (inst_ofs == 0) {
                continue; // empty percussion/drum entry
            }

            inst_ofs += (u32)ctrl_p; // OFS2RAM(ctrl_p, ofs);
            percvt = (perctable*)inst_ofs;
            ((perctable**)*BANK_ENTRY(ctrl_p, 0))[i] = percvt;

            // Percussion may already have been relocated since percussion
            // can appear in list multiple times
            if (percvt->is_relocated) {
                continue;
            }

#ifdef TARGET_PC
            pc_swap_perctable(percvt);
#endif
            __WaveTouch(&percvt->tuned_sample, (u32)ctrl_p, wave_media);
            inst_ofs = (u32)percvt->envelope;
            percvt->envelope = (envdat*)OFS2RAM(ctrl_p, inst_ofs);
#ifdef TARGET_PC
            pc_swap_envdat(percvt->envelope);
#endif
            percvt->is_relocated = TRUE;
        }
    }

    // Sound effects
    ofs = *BANK_ENTRY(ctrl_p, 1);
    if (ofs != 0 && n_sfx_inst != 0) {
        *BANK_ENTRY(ctrl_p, 1) = OFS2RAM(ctrl_p, ofs);

#ifdef TARGET_PC
        /* Swap all sfx entries (percvoicetable = wtstr = {ptr, f32}) */
        for (i = 0; i < n_sfx_inst; i++) {
            percvoicetable* sfx_entry = ((percvoicetable*)*BANK_ENTRY(ctrl_p, 1)) + i;
            pc_swap_percvoicetable(sfx_entry);
        }
#endif

        for (i = 0; i < n_sfx_inst; i++) {
            inst_ofs = (u32)(((percvoicetable*)*BANK_ENTRY(ctrl_p, 1)) + i);
            sfx = (percvoicetable*)inst_ofs;

            // check for null sfx or null sample wave table pointer
            if (sfx == NULL || sfx->tuned_sample.wavetable == NULL) {
                continue;
            }

            __WaveTouch(&sfx->tuned_sample, (u32)ctrl_p, wave_media);
        }
    }

    // Instruments
    if (n_voice_inst > 126) {
        n_voice_inst = 126; // max 126 instruments
    }

    for (i = 2; i <= 2 + n_voice_inst - 1; i++) {
        ofs = *BANK_ENTRY(ctrl_p, i);
        if (ofs != 0) {
            *BANK_ENTRY(ctrl_p, i) = OFS2RAM(ctrl_p, ofs);
            inst = (voicetable*)*BANK_ENTRY(ctrl_p, i);

            // instrument may appear multiple times in the list
            if (!inst->is_relocated) {
#ifdef TARGET_PC
                pc_swap_voicetable(inst);
#endif
                // Optional low pitch sample
                if (inst->normal_range_low != 0) {
                    __WaveTouch(&inst->low_pitch_tuned_sample, (u32)ctrl_p, wave_media);
                }

                // Standard sample, required by all instruments
                __WaveTouch(&inst->normal_pitch_tuned_sample, (u32)ctrl_p, wave_media);

                // Optional high pitch sample
                if (inst->normal_range_high != 0x7F) {
                    __WaveTouch(&inst->high_pitch_tuned_sample, (u32)ctrl_p, wave_media);
                }

                inst_ofs = (u32)inst->envelope;
                inst->envelope = (envdat*)OFS2RAM(ctrl_p, inst_ofs);
#ifdef TARGET_PC
                pc_swap_envdat(inst->envelope);
#endif

                inst->is_relocated = TRUE;
            }
        }
    }

    AG.voice_info[bank_id].percussion = (perctable**)*BANK_ENTRY(ctrl_p, 0);
    AG.voice_info[bank_id].effects = (percvoicetable*)*BANK_ENTRY(ctrl_p, 1);
    AG.voice_info[bank_id].instruments = (voicetable**)BANK_ENTRY(ctrl_p, 2);
#endif
}

#undef OFS2RAM
#undef BANK_ENTRY

void Nas_FastCopy(uintptr_t SrcAddr, u8* DestAdd, size_t Length, s32 medium) {
    u8* unalign_src_copy;
    u32 unalign_copy_len;

    Length = ALIGN_NEXT(Length, 32);
    osInvalDCache2(DestAdd, (u32)Length);

    // This is unnecessary because we've already ensured length is aligned to 32
    if ((Length & 0x1F) != 0) {
        OSReport("DMA Warning: Length %zu is not align32\n", Length);
    }

    if ((SrcAddr & 0x1F) != 0) {
        OSReport("DMA Warning: SrcAddr %p is not align32\n", (void*)SrcAddr);
    }

    if (((uintptr_t)DestAdd & 0x1F) != 0) {
        OSReport("DMA Warning: DestAdd %p is not align32\n", DestAdd);
    }

    if ((SrcAddr & 0x1F) != 0) {
        unalign_src_copy = (u8*)FASTDMA_BUFFER;

        // DMA the first non-align32 bytes
        // @BUG - FASTDMA_BUFFER is always NULL
        Nas_StartDma(&AG.sync_dma_io_mesg, 1, 0, (u32)(SrcAddr - (SrcAddr & 0x1F)), FASTDMA_BUFFER, 0x20,
                     &AG.sync_dma_queue, medium, (s8*)"FastCopy");
        Z_osRecvMesg(&AG.sync_dma_queue, NULL, OS_MESG_BLOCK);
        unalign_copy_len = 32 - (SrcAddr & 0x1F);
        Z_bcopy(unalign_src_copy + (SrcAddr & 0x1F), DestAdd, 32 - (SrcAddr & 0x1F));
        SrcAddr += unalign_copy_len;
        DestAdd += unalign_copy_len;
        Length -= unalign_copy_len;

        while (Length != 0) {
            Nas_StartDma(&AG.sync_dma_io_mesg, 1, 0, (u32)SrcAddr, unalign_src_copy, 0x400, &AG.sync_dma_queue, medium,
                         (s8*)"FastCopy");
            Z_osRecvMesg(&AG.sync_dma_queue, NULL, OS_MESG_BLOCK);

            if (Length < 0x400) {
                unalign_copy_len = (u32)Length;
            } else {
                unalign_copy_len = 0x400;
            }

            Z_bcopy(unalign_src_copy, DestAdd, unalign_copy_len);
            Length -= unalign_copy_len;
            SrcAddr += unalign_copy_len;
            DestAdd += unalign_copy_len;
        }
    } else {
        while (TRUE) {
            if (Length < 0x400) {
                break;
            }

            Nas_StartDma(&AG.sync_dma_io_mesg, 1, 0, (u32)SrcAddr, DestAdd, 0x400, &AG.sync_dma_queue, medium,
                         (s8*)"FastCopy");
            Z_osRecvMesg(&AG.sync_dma_queue, NULL, OS_MESG_BLOCK);
            Length -= 0x400;
            SrcAddr += 0x400;
            DestAdd += 0x400;
        }

        if (Length != 0) {
            Nas_StartDma(&AG.sync_dma_io_mesg, 1, 0, (u32)SrcAddr, DestAdd, (u32)Length, &AG.sync_dma_queue, medium,
                         (s8*)"FastCopy");
            Z_osRecvMesg(&AG.sync_dma_queue, NULL, OS_MESG_BLOCK);
        }
    }
}

extern void Nas_FastDiskCopy(u8* SrcAddr, u8* DestAdd, size_t Length, s32 medium) {
    // empty
}

static s32 Nas_StartDma(OSIoMesg* ioMsg, s32 priority, s32 direction, u32 device_addr, void* dram_addr, u32 size,
                        OSMesgQueue* mq, s32 medium, s8* dma_type) {
#ifdef TARGET_PC
    /* On PC, ARAM is a flat memory buffer. Do the copy synchronously
     * and send the completion message immediately. The GC path goes through
     * Z_osEPiStartDma → DVDT_AddTaskHigh (queued) which deadlocks because
     * the task queue is drained outside the current call path. */
    extern u32 GetNeosRomTop(void);

    if (AG.reset_timer > 16) {
        return -1;
    }

    if (medium != MEDIUM_CART && medium != MEDIUM_DISK_DRIVE) {
        return 0;
    }

    if ((size & 0x1F) != 0) {
        size = ALIGN_NEXT(size, 32);
    }

    /* device_addr is an ARAM offset (relative to audiorom start).
     * GetNeosRomTop() gives the base ARAM address for audiorom data. */
    u32 aram_offset = device_addr + GetNeosRomTop();
    u8* aram_storage = (u8*)ARGetStorageAddress();
    if (aram_storage != NULL && dram_addr != NULL) {
        memcpy(dram_addr, aram_storage + aram_offset, size);
    }

    /* Send completion message so callers that do Z_osRecvMesg(BLOCK) unblock */
    if (mq != NULL) {
        Z_osSendMesg(mq, NULL, OS_MESG_NOBLOCK);
    }

    return 0;
#else
    OSPiHandle* handle;

    osInvalDCache2(dram_addr, size);
    if (AG.reset_timer > 16) {
        return -1;
    }

    switch (medium) {
        case MEDIUM_CART:
            handle = AG.cart_handle;
            break;
        case MEDIUM_DISK_DRIVE:
            handle = AG.drive_handle;
            break;
        default:
            return 0;
    }

    if ((size & 0x1F) != 0) {
        size = ALIGN_NEXT(size, 32);
    }

    ioMsg->hdr.pri = priority;
    ioMsg->hdr.retQueue = mq;
    ioMsg->dramAddr = dram_addr;
    ioMsg->devAddr = device_addr;
    ioMsg->size = size;
    (*NA_DMA_PROC)(handle, ioMsg, direction);
    return 0;
#endif
}

// @unused void? __OfsToLbaOfs(s32 ofs?, s32* lba_ofs?);
// AudioLoad_Unused1 in OoT decomp

// @unused
void EmemLoad(s32 table_type, s32 id) {
    s32 did_alloc;

    __Load_Bank(table_type, id, &did_alloc);
}

static u8* __Load_Bank_BG(s32 table_type, s32 id, s32 n_chunks, s32 ret_data, OSMesgQueue* ret_queue) {
    u32 size;
    ArcHeader* header;
    u8* ramAddr;
    s32 medium;
    u32 devAddr;
    s32 loadStatus;
    s8 cachePolicy;
    s32 asyncLoadStatus;
    s32 link_id = __Link_BankNum(table_type, id);
    voiceinfo* vinfo;

    switch (table_type) {
        case SEQUENCE_TABLE:
            if (AG.sequence_load_status[link_id] == LOAD_STATUS_IN_PROGRESS) {
                return NULL;
            }
            break;

        case BANK_TABLE:
            if (AG.bank_load_status[link_id] == LOAD_STATUS_IN_PROGRESS) {
                return NULL;
            }
            break;

        case WAVE_TABLE:
            if (AG.wave_load_status[link_id] == LOAD_STATUS_IN_PROGRESS) {
                return NULL;
            }
            break;
    }

    ramAddr = (u8*)__Check_Cache(table_type, link_id);
    if (ramAddr != NULL) {
        loadStatus = LOAD_STATUS_COMPLETE;
        Z_osSendMesg(ret_queue, (OSMesg)(uintptr_t)MK_BGLOAD_MSG(ret_data, SEQUENCE_TABLE, 0, LOAD_STATUS_NOT_LOADED),
                     OS_MESG_NOBLOCK);
    } else {
        header = __Get_ArcHeader(table_type);
        size = header->entries[link_id].size;
        size = ALIGN_NEXT(size, 32);
        medium = header->entries[id].medium;
        cachePolicy = header->entries[id].cacheType;
        devAddr = header->entries[link_id].addr;
        asyncLoadStatus = LOAD_STATUS_COMPLETE;

        switch (cachePolicy) {
            case CACHE_LOAD_PERMANENT:
                ramAddr = (u8*)EmemAlloc(table_type, link_id, size);
                if (ramAddr == NULL) {
                    return ramAddr;
                }
                asyncLoadStatus = LOAD_STATUS_PERMANENT;
                break;

            case CACHE_LOAD_PERSISTENT:
                ramAddr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_PERSISTENT, link_id);
                if (ramAddr == NULL) {
                    return ramAddr;
                }
                break;

            case CACHE_LOAD_TEMPORARY:
                ramAddr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_TEMPORARY, link_id);
                if (ramAddr == NULL) {
                    return ramAddr;
                }
                break;

            case CACHE_LOAD_EITHER:
            case CACHE_LOAD_EITHER_NOSYNC:
                ramAddr = (u8*)Nas_SzHeapAlloc(table_type, size, CACHE_EITHER, link_id);
                if (ramAddr == NULL) {
                    return ramAddr;
                }
                break;
        }

        if (medium == MEDIUM_RAM_UNLOADED) {
            if (devAddr == 0) {
                return NULL;
            }

            if (table_type == BANK_TABLE) {
                size -= 0x10;
                vinfo = &AG.voice_info[link_id];
                vinfo->num_instruments = ((u16*)(uintptr_t)devAddr)[0];
                vinfo->num_drums = ((u16*)(uintptr_t)devAddr)[1];
                vinfo->num_sfx = ((u16*)(uintptr_t)devAddr)[2];
                devAddr += 0x10;
            }
        }

        if (medium == MEDIUM_DISK) {
            Nas_BgCopyDisk(header->medium, (u8*)(uintptr_t)devAddr, ramAddr, size, medium, n_chunks, ret_queue,
                           MK_BGLOAD_MSG(ret_data, table_type, link_id, asyncLoadStatus));
        } else {
            Nas_BgCopyReq((u8*)(uintptr_t)devAddr, ramAddr, size, medium, n_chunks, ret_queue,
                          MK_BGLOAD_MSG(ret_data, table_type, link_id, asyncLoadStatus));
        }
        loadStatus = LOAD_STATUS_IN_PROGRESS;
    }

    switch (table_type) {
        case SEQUENCE_TABLE:
            Nas_WriteIDseq(link_id, loadStatus);
            break;

        case BANK_TABLE:
            Nas_WriteIDbank(link_id, loadStatus);
            break;

        case WAVE_TABLE:
            Nas_WriteIDwave(link_id, loadStatus);
            break;

        default:
            break;
    }

    return ramAddr;
}

void Nas_BgDmaFrameWork(s32 reset_status) {
    LpsDma(reset_status);
    Nas_CheckBgWave(reset_status);
    Nas_BgCopyMain(reset_status);
}

// @unused Nas_SetRomHandler__FPFv_l -> void Nas_SetRomHandler(void (*rom_handler)(s32));
// @unused Nas_SetDiskHandler__FPFv_l -> void Nas_SetRomHandler(void (*disk_handler)(s32));
// @unused Nas_SetRomHandler__FPFv_l -> void Nas_SetSyncHandler__FPFv_PUc(void (*rom_handler)(u8*));

static uintptr_t Nas_GetSyncDummy(u8* param0, s32 param1) {
    return 0;
}

static void __SetVlute(s32 bank_id) {
    voiceinfo* vinfo = &AG.voice_info[bank_id];
    ArcEntry* entry = &AG.bank_header->entries[bank_id];

    vinfo->wave_bank_id0 = (entry->param0 >> 8) & 0xFF;
    vinfo->wave_bank_id1 = (entry->param0 >> 0) & 0xFF;
    vinfo->num_instruments = (entry->param1 >> 8) & 0xFF;
    vinfo->num_drums = (entry->param1 >> 0) & 0xFF;
    vinfo->num_sfx = entry->param2;
}

void Nas_InitAudio(u64* heap_p, s32 heap_size) {
    s32 i;
    u8* seq_p;
    u8* bank_p;
    u8* wave_p;
    s32 bank_count;
    u8* emem_heap;

    NA_VFRAME_CALLBACK = NULL;
    NA_SOUND_CALLBACK = NULL;
    NA_DACOUT_CALLBACK = NULL;

    for (i = 0; i < ARRAY_COUNT(AG.seq_callbacks); i++) {
        AG.seq_callbacks[i] = NULL;
    }

    AG.reset_timer = 0;
    AG._2A14 = 0;
    AG._29D8 = 1000 * REFRESH_RATE_DEVIATION_NTSC / REFRESH_RATE_NTSC;
    AG.refresh_rate = REFRESH_RATE_NTSC;
    Nas_InitGAudio();
    for (i = 0; i < ARRAY_COUNT(AG.num_samples_per_frame); i++) {
        AG.num_samples_per_frame[i] = 160;
    }

    AG.frame_audio_task_count = 0;
    AG.rsp_task_idx = 0;
    AG.current_ai_buffer_idx = 0;
    AG.sound_mode = SOUND_OUTPUT_STEREO;
    AG.unused_current_audio_task = NULL;
    *(u32*)&AG.unused_rsp_tasks[0][56] = 0; // OSTask.t.data_size = 0;
    *(u32*)&AG.unused_rsp_tasks[1][56] = 0; // OSTask.t.data_size = 0;
    Z_osCreateMesgQueue(&AG.sync_dma_queue, AG.sync_dma_queue_msg, ARRAY_COUNT(AG.sync_dma_queue_msg));
    Z_osCreateMesgQueue(&AG.cur_audio_frame_dma_queue, AG.cur_audio_frame_dma_mesg_buf,
                        ARRAY_COUNT(AG.cur_audio_frame_dma_mesg_buf));
    Z_osCreateMesgQueue(&AG.external_load_queue, AG.external_load_mesg_buf, ARRAY_COUNT(AG.external_load_mesg_buf));
    Z_osCreateMesgQueue(&AG.preload_sample_queue, AG.preload_sample_mesg_buf, ARRAY_COUNT(AG.preload_sample_mesg_buf));
    AG.current_frame_dma_count = 0;
    AG.num_waveloads = 0;

#ifdef TARGET_PC
    /* Fresh process-wide swap tracking state at audio boot. */
    pc_reset_envdat_visited_all();
#endif

    AG.audio_heap_p = heap_p;
    AG.audio_heap_size = heap_size;
    OSReport("AUDIOHEAP SET ADDR %p (SIZE %xh) \n", (void*)heap_p, heap_size);
    OSReport(" FIXSIZE  %x \n", AGC.fixSize);
    OSReport(" EMEMSIZE %x \n", AGC.ememSize);
    OSReport(" MAXCHAN  %d \n", AGC.maxChan);
    OSReport(" TIMEBASE %d \n", AGC.timeBase);

    for (i = 0; i < AG.audio_heap_size / (s32)sizeof(u64); i++) {
        AG.audio_heap_p[i] = 0;
    }

    OSReport(" Cleaedr Memory \n");

    Nas_SzHeapReset(AGC.fixSize + 0x400);
    for (i = 0; i < ARRAY_COUNT(AG.ai_buffers); i++) {
        AG.ai_buffers[i] = (s16*)Nas_HeapAlloc_CL(&AG.init_heap, 0xF80);
    }

    AG.seq_header = &AudioseqHeaderStart;
    AG.bank_header = &AudiobankHeaderStart;
    AG.wave_header = &AudiowaveHeaderStart;
    AG.map_header = AudiomapHeaderStart;

    AG.num_sequences = AG.seq_header->numEntries;
    AG.spec_id = 0;
    AG.reset_status = 1;
    Nas_SpecChange();
    AG.data_header = &AudiodataHeaderStart;

    seq_p = NULL;
    bank_p = NULL;
    wave_p = NULL;

    if (AG.data_header->numEntries != 0) {
        seq_p = (u8*)(uintptr_t)AG.data_header->entries[SEQUENCE_TABLE].addr;
        bank_p = (u8*)(uintptr_t)AG.data_header->entries[BANK_TABLE].addr;
        wave_p = (u8*)(uintptr_t)AG.data_header->entries[WAVE_TABLE].addr;
    }

    Nas_BankHeaderInit(AG.seq_header, seq_p, MEDIUM_RAM);
    Nas_BankHeaderInit(AG.bank_header, bank_p, MEDIUM_RAM);
    Nas_BankHeaderInit(AG.wave_header, wave_p, MEDIUM_RAM);

    bank_count = AG.bank_header->numEntries;
    AG.voice_info = (voiceinfo*)Nas_HeapAlloc(&AG.init_heap, bank_count * sizeof(voiceinfo));
    for (i = 0; i < bank_count; i++) {
        __SetVlute(i);
    }

    emem_heap = (u8*)Nas_HeapAlloc(&AG.init_heap, AGC.ememSize);
    if (emem_heap == NULL) {
        AGC.ememSize = 0;
    }

    Nas_HeapInit(&AG.emem_heap, emem_heap, AGC.ememSize);

    AUDIO_SYSTEM_READY = TRUE;
    Z_osSendMesg(AG.task_start_mq_p, (OSMesg)(uintptr_t)AG.frame_audio_task_count, OS_MESG_NOBLOCK);
}

void LpsInit(void) {
    AG.lps_cache[0].status = 0;
    AG.lps_cache[1].status = 0;
}

s32 VoiceLoad(s32 bank_id, u32 inst_id, s8* done_p) {
    smzwavetable* wavetable = __GetWaveTable(bank_id, inst_id);
    lpscache* cache;

    if (wavetable == NULL) {
#ifdef TARGET_PC
        printf("[VoiceLoad] FAIL: wavetable NULL bank=%d inst=%u\n", bank_id, inst_id);
#endif
        *done_p = 0;
        return -1;
    }

    if (wavetable->medium == MEDIUM_RAM) {
        *done_p = 2;
        return 0;
    }

#ifdef TARGET_PC
    printf("[VoiceLoad] NEED DMA: bank=%d inst=%u medium=%d size=%u\n",
        bank_id, inst_id, wavetable->medium, wavetable->size);
#endif

    cache = &AG.lps_cache[AG.slow_load_pos];
    if (cache->status == 3) {
        cache->status = 0;
    }

    cache->sample = *wavetable;
    cache->is_done = done_p;
    cache->current_ram_addr =
        (u8*)Nas_Alloc_Single(wavetable->size, bank_id, wavetable->sample, wavetable->medium, CACHE_TEMPORARY);

    if (cache->current_ram_addr == NULL) {
#ifdef TARGET_PC
        printf("[VoiceLoad] ALLOC FAIL: bank=%d inst=%u size=%u medium=%d\n",
            bank_id, inst_id, wavetable->size, wavetable->medium);
#endif
        if (wavetable->medium == MEDIUM_DISK || wavetable->codec == CODEC_S16_INMEMORY) {
            *done_p = 0;
        } else {
            *done_p = 3;
        }
        return -1;
    }

    cache->status = LPS_CACHE_STATE_START;
    cache->bytes_remaining = ALIGN_NEXT(wavetable->size, 32);
    cache->ram_addr = cache->current_ram_addr;
    cache->current_device_addr = (NaLoadAddress)(uintptr_t)wavetable->sample;
    cache->medium = wavetable->medium;
    cache->seq_or_bank_id = bank_id;
    cache->inst_id = inst_id;

    if (cache->medium == MEDIUM_DISK) {
        cache->unk_medium_param = AG.wave_header->medium;
    }

    AG.slow_load_pos ^= 1;
    return 0;
}

static smzwavetable* __GetWaveTable(s32 bank_id, s32 inst_id) {
    if (inst_id < 128) {
        voicetable* vt = ProgToVp(bank_id, inst_id);

        if (vt == NULL) {
            return NULL;
        }

        return vt->normal_pitch_tuned_sample.wavetable;
    } else if (inst_id <= 255) {
        perctable* pvt = PercToPp(bank_id, inst_id - 128);

        if (pvt == NULL) {
            return NULL;
        }

        return pvt->tuned_sample.wavetable;
    } else {
        percvoicetable* evt = VpercToVep(bank_id, inst_id - 256);

        if (evt == NULL) {
            return NULL;
        }

        return evt->tuned_sample.wavetable;
    }
}

static void __SwapLoadLps(lpscache* cache) {
    if (cache->sample.sample != NULL) {
        smzwavetable* wavetable = __GetWaveTable(cache->seq_or_bank_id, cache->inst_id);

        if (wavetable != NULL) {
            cache->sample = *wavetable;
            wavetable->sample = cache->ram_addr;
            wavetable->medium = MEDIUM_RAM;
        }
    }
}

void LpsDma(s32 reset_status) {
    s32 i;
    lpscache* cache;

    for (i = 0; i < ARRAY_COUNT(AG.lps_cache); i++) {
        cache = &AG.lps_cache[i];

        switch (cache->status) {
            case LPS_CACHE_STATE_LOADING:
                if (cache->medium != MEDIUM_DISK) {
                    Z_osRecvMesg(&cache->mq, NULL, OS_MESG_BLOCK);
                }

                if (reset_status != 0) {
                    cache->status = LPS_CACHE_STATE_DONE;
                    continue;
                }
                // fallthrough
            case LPS_CACHE_STATE_START:
                cache->status = LPS_CACHE_STATE_LOADING;
                if (cache->bytes_remaining == 0) {
                    __SwapLoadLps(cache);
                    cache->status = LPS_CACHE_STATE_DONE;
                    *cache->is_done = TRUE;
                } else if (cache->bytes_remaining < 0x400) {
                    if (cache->medium == MEDIUM_DISK) {
                        __Nas_SlowDiskCopy((u8*)cache->current_device_addr, cache->current_ram_addr,
                                           cache->bytes_remaining, cache->unk_medium_param);
                    } else {
                        __Nas_SlowCopy(cache, cache->bytes_remaining);
                    }

                    cache->bytes_remaining = 0;
                } else {
                    if (cache->medium == MEDIUM_DISK) {
                        __Nas_SlowDiskCopy((u8*)cache->current_device_addr, cache->current_ram_addr, 0x400,
                                           cache->unk_medium_param);
                    } else {
                        __Nas_SlowCopy(cache, 0x400);
                    }

                    cache->bytes_remaining -= 0x400;
                    cache->current_ram_addr += 0x400;
                    cache->current_device_addr += 0x400;
                }

                break;
        }
    }
}

static void __Nas_SlowCopy(lpscache* cache, s32 size) {
    osInvalDCache2(cache->current_ram_addr, size);
    Z_osCreateMesgQueue(&cache->mq, cache->msg, ARRAY_COUNT(cache->msg));
    Nas_StartDma(&cache->io_mesg, 0, 0, (u32)cache->current_device_addr, cache->current_ram_addr, size, &cache->mq,
                 cache->medium, (s8*)"SLOWCOPY");
}

static void __Nas_SlowDiskCopy(u8* dev_addr, u8* ram_addr, u32 size, s32 medium) {
    // nothing
}

s32 SeqLoad(s32 seq_id, u8* ram_addr, s8* is_done) {
    s32 link_id = __Link_BankNum(SEQUENCE_TABLE, seq_id);
    ArcHeader* header = __Get_ArcHeader(SEQUENCE_TABLE);
    lpscache* cache = &AG.lps_cache[AG.slow_load_pos];
    u32 size;

    if (cache->status == LPS_CACHE_STATE_DONE) {
        cache->status = LPS_CACHE_STATE_WAITING;
    }

    cache->sample.sample = NULL;
    cache->is_done = is_done;

    size = header->entries[link_id].size;
    size = ALIGN_NEXT(size, 32);

    cache->current_ram_addr = ram_addr;
    cache->status = LPS_CACHE_STATE_START;
    cache->bytes_remaining = size;
    cache->ram_addr = cache->current_ram_addr;
    cache->current_device_addr = header->entries[link_id].addr;
    cache->medium = header->entries[link_id].medium;
    cache->seq_or_bank_id = link_id;

    if (cache->medium == MEDIUM_DISK) {
        cache->unk_medium_param = header->medium;
    }

    AG.slow_load_pos ^= 1;
    return 0;
}

void Nas_BgCopyInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(AG.bgloads); i++) {
        AG.bgloads[i].status = LOAD_STATUS_NOT_LOADED;
    }
}

static Bgload* Nas_BgCopyDisk(s32 dev_medium, u8* src, u8* dst, u32 size, s32 medium, s32 n_chunks, OSMesgQueue* mq,
                              s32 msg) {
    Bgload* bgload = Nas_BgCopyReq(src, dst, size, medium, n_chunks, mq, msg);

    if (bgload == NULL) {
        return NULL;
    }

    Z_osSendMesg(&AG.bgload_mq, (OSMesg)bgload, OS_MESG_NOBLOCK);
    bgload->unk_medium_param = dev_medium;
    return bgload;
}

static Bgload* Nas_BgCopyReq(u8* src, u8* dst, u32 size, s32 medium, s32 n_chunks, OSMesgQueue* mq, s32 msg) {
    Bgload* bgload;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(AG.bgloads); i++) {
        if (AG.bgloads[i].status == LOAD_STATUS_NOT_LOADED) {
            bgload = &AG.bgloads[i];
            break;
        }
    }

    if (i == ARRAY_COUNT(AG.bgloads)) {
        return NULL;
    }

    bgload->status = LOAD_STATUS_IN_PROGRESS;
    bgload->current_device_addr = (NaLoadAddress)(uintptr_t)src;
    bgload->ram_addr = dst;
    bgload->current_ram_addr = dst;
    bgload->bytes_remaining = size;

    if (n_chunks == 0) {
        bgload->chunk_size = 0x1000;
    } else if (n_chunks == 1) {
        bgload->chunk_size = size;
    } else {
        bgload->chunk_size = ALIGN_NEXT((s32)size / n_chunks, 256);

        if (bgload->chunk_size < 256) {
            bgload->chunk_size = 256;
        }
    }

    bgload->ret_mq = mq;
    bgload->delay = 3;
    bgload->medium = medium;
    bgload->ret_msg = msg;
    Z_osCreateMesgQueue(&bgload->mq, bgload->msg, ARRAY_COUNT(bgload->msg));
    return bgload;
}

void Nas_BgCopyMain(s32 reset_status) {
    Bgload* bgload;
    s32 i;

    if (AG.reset_timer == 1) {
        return;
    }

    if (AG.current_bgload == NULL) {
        if (reset_status != 0) {
            while (TRUE) {
                if (Z_osRecvMesg(&AG.bgload_mq, (OSMesg*)&bgload, OS_MESG_NOBLOCK) == -1) {
                    break;
                }
            }
        } else if (Z_osRecvMesg(&AG.bgload_mq, (OSMesg*)&bgload, OS_MESG_NOBLOCK) == -1) {
            AG.current_bgload = NULL;
        } else {
            AG.current_bgload = bgload;
        }
    }

    if (AG.current_bgload != NULL) {
        __BgCopyDisk(AG.current_bgload, reset_status);
    }

    for (i = 0; i < ARRAY_COUNT(AG.bgloads); i++) {
        if (AG.bgloads[i].status == LOAD_STATUS_IN_PROGRESS) {
            bgload = &AG.bgloads[i];

            if (bgload->medium != MEDIUM_DISK) {
                __BgCopySub(bgload, reset_status);
            }
        }
    }
}

static void __BgCopyDisk(Bgload* bgload, s32 reset_status) {
    // nothing
}

static void __BgCopyFinishProcess(Bgload* bgload) {
    u32 msg = bgload->ret_msg;
    s32 id;
    s32 type;
    s32 status;
    OSMesg ret_msg;
    s32 wave0;
    s32 wave1;
    WaveMedia wavemedia;

    type = BGLOAD_TBLTYPE(msg);
    status = BGLOAD_LOAD_STATUS(msg);
    id = BGLOAD_ID(msg);
    switch (type) {
        case SEQUENCE_TABLE:
            Nas_WriteIDseq(id, status);
            break;
        case WAVE_TABLE:
            Nas_WriteIDwave(id, status);
            break;
        case BANK_TABLE:
            wave0 = AG.voice_info[id].wave_bank_id0;
            wave1 = AG.voice_info[id].wave_bank_id1;

            wavemedia.wave0_bank_id = wave0;
            wavemedia.wave1_bank_id = wave1;

            if (wave0 != 0xFF) {
                wavemedia.wave0_p = (void*)__Load_Wave_Check(wave0, &wavemedia.wave0_media);
            } else {
                wavemedia.wave0_p = NULL;
            }

            if (wave1 != 0xFF) {
                wavemedia.wave1_p = (void*)__Load_Wave_Check(wave1, &wavemedia.wave1_media);
            } else {
                wavemedia.wave1_p = NULL;
            }

            Nas_WriteIDbank(id, status);
            Nas_BankOfsToAddr(id, bgload->ram_addr, &wavemedia, TRUE);
            break;
    }

    bgload->status = LOAD_STATUS_NOT_LOADED;
    ret_msg = (OSMesg)(uintptr_t)bgload->ret_msg;
    Z_osSendMesg(bgload->ret_mq, ret_msg, OS_MESG_NOBLOCK);
}

static void __BgCopySub(Bgload* bgload, s32 reset_status) {
    ArcHeader* header = AG.wave_header;

    if (bgload->delay > 1) {
        bgload->delay--;
        return;
    }

    if (bgload->delay == 1) {
        bgload->delay = 0;
    } else if (reset_status != 0) {
        Z_osRecvMesg(&bgload->mq, NULL, OS_MESG_BLOCK);
        bgload->status = LOAD_STATUS_NOT_LOADED;
        return;
    } else if (Z_osRecvMesg(&bgload->mq, NULL, OS_MESG_NOBLOCK) == -1) {
        return;
    }

    if (bgload->bytes_remaining == 0) {
        __BgCopyFinishProcess(bgload);
        return;
    }

    if (bgload->bytes_remaining < bgload->chunk_size) {
        if (bgload->medium == MEDIUM_DISK) {
            __Nas_BgDiskCopy((u8*)bgload->current_device_addr, bgload->current_ram_addr, (u32)bgload->bytes_remaining,
                             header->medium);
        } else if (bgload->medium == MEDIUM_RAM_UNLOADED) {
            __Nas_ExCopy(bgload, (s32)bgload->bytes_remaining);
        } else {
            __Nas_BgCopy(bgload, (s32)bgload->bytes_remaining);
        }

        bgload->bytes_remaining = 0;
    } else {
        if (bgload->medium == MEDIUM_DISK) {
            __Nas_BgDiskCopy((u8*)bgload->current_device_addr, bgload->current_ram_addr, (u32)bgload->chunk_size,
                             header->medium);
        } else if (bgload->medium == MEDIUM_RAM_UNLOADED) {
            __Nas_ExCopy(bgload, (s32)bgload->chunk_size);
        } else {
            __Nas_BgCopy(bgload, (s32)bgload->chunk_size);
        }

        bgload->bytes_remaining -= bgload->chunk_size;
        bgload->current_device_addr += bgload->chunk_size;
        bgload->current_ram_addr += bgload->chunk_size;
    }
}

static void __Nas_BgCopy(Bgload* bgload, s32 size) {
    size = ALIGN_NEXT(size, 32);
    osInvalDCache2(bgload->current_ram_addr, size);
    Z_osCreateMesgQueue(&bgload->mq, bgload->msg, ARRAY_COUNT(bgload->msg));
    Nas_StartDma(&bgload->io_mesg, 0, 0, (u32)bgload->current_device_addr, bgload->current_ram_addr, size, &bgload->mq,
                 bgload->medium, (s8*)"BGCOPY");
}

static void __Nas_ExCopy(Bgload* bgload, s32 size) {
    size = ALIGN_NEXT(size, 32);
    osInvalDCache2(bgload->current_ram_addr, size);
    Z_osCreateMesgQueue(&bgload->mq, bgload->msg, ARRAY_COUNT(bgload->msg));
    Z_bcopy((u8*)bgload->current_device_addr, bgload->current_ram_addr, size);
    Z_osSendMesg(&bgload->mq, NULL, OS_MESG_NOBLOCK);
}

static void __Nas_BgDiskCopy(u8* src, u8* dst, u32 size, s32 param) {
    // nothing
}

#ifndef TARGET_PC
static void __WaveTouch(wtstr* wavetouch_str, u32 ram_addr, WaveMedia* wave_media) {
    smzwavetable* wavetable;
    void* reloc;

#ifdef TARGET_PC
    /* The wavetable pointer in wtstr was already byte-swapped in
     * pc_swap_perctable/pc_swap_voicetable/pc_swap_percvoicetable.
     * It's still a BE offset that was byte-swapped to LE — now a valid
     * LE u32 offset value. Check if it needs relocation. On PC, all
     * pointers are < OS_BASE_CACHED (0x80000000), so use a simpler check:
     * if the offset is small enough to be a valid offset, relocate it. */
    {
        u32 wt_ofs = (u32)wavetouch_str->wavetable;
        if (wt_ofs != 0 && wt_ofs < 0x10000000) {
            /* Not yet relocated — relocate now */
            reloc = (void*)(wt_ofs + ram_addr);
            wavetouch_str->wavetable = (smzwavetable*)reloc;
            wavetable = wavetouch_str->wavetable;

            /* Check if this wavetable was already byte-swapped and relocated
             * by a previous entry (e.g. another percussion sharing the same wavetable).
             * We need to read the raw u32 and check the is_relocated bit.
             * In BE (original data): bit layout = bit31(1)|codec(3)|medium(2)|bit26(1)|is_relocated(1)|size(24)
             * is_relocated is bit 25 of the BE u32.
             * After pc_swap_smzwavetable: the u32 is byte-swapped to LE, and the
             * struct bitfield layout on LE puts is_relocated at the correct C-level position.
             * Before swap: we need to check the raw BE byte. Bit 25 of a BE u32
             * is bit 1 of byte[0]. As raw LE u32, that's bit 25 of BSWAP32(raw). */
            {
                u32 raw_first_u32 = *(u32*)wavetable;
                u32 be_first_u32 = BSWAP32(raw_first_u32);
                BOOL already_relocated_be = (be_first_u32 >> 25) & 1;
                /* Also check the LE-swapped is_relocated field in case it was already swapped */
                BOOL already_relocated_le = wavetable->is_relocated;
                if (already_relocated_be || already_relocated_le) {
                    /* Already processed — just update the pointer, skip swap/reloc */
                    goto wavetouch_done;
                }
            }

            /* Swap smzwavetable fields (bitfield u32, sample, loop, book) */
            pc_swap_smzwavetable(wavetable);

            if (wavetable->size != 0) {
                reloc = (void*)((u32)wavetable->loop + ram_addr);
                wavetable->loop = (adpcmloop*)reloc;
                pc_swap_adpcmloop(wavetable->loop);

                reloc = (void*)((u32)wavetable->book + ram_addr);
                wavetable->book = (adpcmbook*)reloc;
                pc_swap_adpcmbook(wavetable->book);

                switch (wavetable->medium) {
                    case MEDIUM_RAM:
                        reloc = (void*)((u32)wavetable->sample + (u32)wave_media->wave0_p);
                        wavetable->sample = (u8*)reloc;
                        wavetable->medium = wave_media->wave0_media;
                        break;
                    case MEDIUM_DISK:
                        reloc = (void*)((u32)wavetable->sample + (u32)wave_media->wave1_p);
                        wavetable->sample = (u8*)reloc;
                        wavetable->medium = wave_media->wave1_media;
                        break;
                    case MEDIUM_CART:
                    case MEDIUM_DISK_DRIVE:
                        break;
                }

                wavetable->is_relocated = TRUE;
                if (wavetable->bit26 && wavetable->medium != MEDIUM_RAM &&
                    AG.num_used_samples < ARRAY_COUNT(AG.used_samples)) {
                    AG.used_samples[AG.num_used_samples++] = wavetable;
                }
            }
        }
    wavetouch_done:
        (void)0; /* label needs a statement */
    }
#else /* !TARGET_PC */
    if ((u32)wavetouch_str->wavetable <= OS_BASE_CACHED) {
        // wave is not relocated
        reloc = (void*)((u32)wavetouch_str->wavetable + ram_addr);
        wavetouch_str->wavetable = (smzwavetable*)reloc;
        wavetable = wavetouch_str->wavetable;

        if (wavetable->size != 0 && wavetable->is_relocated != TRUE) {
            reloc = (void*)((u32)wavetable->loop + ram_addr);
            wavetable->loop = (adpcmloop*)reloc;

            reloc = (void*)((u32)wavetable->book + ram_addr);
            wavetable->book = (adpcmbook*)reloc;

            switch (wavetable->medium) {
                case MEDIUM_RAM:
                    reloc = (void*)((u32)wavetable->sample + (u32)wave_media->wave0_p);
                    wavetable->sample = (u8*)reloc;
                    wavetable->medium = wave_media->wave0_media;
                    break;
                case MEDIUM_DISK:
                    reloc = (void*)((u32)wavetable->sample + (u32)wave_media->wave1_p);
                    wavetable->sample = (u8*)reloc;
                    wavetable->medium = wave_media->wave1_media;
                    break;
                case MEDIUM_CART:
                case MEDIUM_DISK_DRIVE:
                    break;
            }

            wavetable->is_relocated = TRUE;
            if (wavetable->bit26 && wavetable->medium != MEDIUM_RAM &&
                AG.num_used_samples < ARRAY_COUNT(AG.used_samples)) {
                AG.used_samples[AG.num_used_samples++] = wavetable;
            }
        }
    }
#endif /* TARGET_PC */
}
#endif

s32 Nas_BankOfsToAddr(s32 bank_id, u8* ctrl_p, WaveMedia* wave_media, s32 async) {
    Bgloadreq* preload;
    Bgloadreq* top_preload;
    smzwavetable* wavetable;
    s32 size = 0;
    s32 n_chunks = 1;
    u8* wave_ram_p = NULL;
    s32 preloading = FALSE;
    static ALHeap awheap;
    s32 i;
    s8 medium = 0;

    // u8 __stack_pad[12];
    // s32* i_p = &i; // this feels wrong but w/e

#ifdef TARGET_PC
    /* Only bank relocation data is guaranteed fresh here.
     * Sequence envelopes may still be live and already swapped. */
    pc_reset_envdat_bank_visited();
#endif

    if (AG.num_requested_samples != 0) {
        preloading = TRUE;
    } else {
        awheap.base = NULL;
    }

    AG.num_used_samples = 0;
    Nas_BankOfsToAddr_Inner(bank_id, ctrl_p, wave_media);

    size = 0;
    for (i = 0; i < AG.num_used_samples; i++) {
        size += ALIGN_NEXT(AG.used_samples[i]->size & 0xFFFFFF, 16);
    }

    for (i = 0; i < AG.num_used_samples; i++) {
        if (AG.num_requested_samples == 120) {
            break;
        }

        wavetable = AG.used_samples[i];
        wave_ram_p = NULL;

        switch (async) {
            case FALSE: {
                u8 medium = wavetable->medium;
                if (wavetable->medium == wave_media->wave0_media) {
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size, wave_media->wave0_bank_id, wavetable->sample,
                        (s8)(wavetable->medium & 0xFF), CACHE_PERSISTENT);
                } else if (wavetable->medium == wave_media->wave1_media) {
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size, wave_media->wave1_bank_id, wavetable->sample,
                        (s8)(wavetable->medium & 0xFF), CACHE_PERSISTENT);
                } else if (wavetable->medium == MEDIUM_DISK_DRIVE) {
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size, 0xFE, wavetable->sample, (s8)(wavetable->medium & 0xFF),
                                                       CACHE_PERSISTENT);
                }
            } break;
            case TRUE: {
                u8 medium = wavetable->medium;
                if ((u8)wavetable->medium == wave_media->wave0_media) {
                    // the size & 0xFFFFFF is necessary... but only once...
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size & 0xFFFFFF, wave_media->wave0_bank_id, wavetable->sample,
                        (u8)wavetable->medium, CACHE_TEMPORARY);
                } else if ((u8)wavetable->medium == wave_media->wave1_media) {
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size, wave_media->wave1_bank_id, wavetable->sample,
                        (u8)wavetable->medium, CACHE_TEMPORARY);
                } else if ((u8)wavetable->medium == MEDIUM_DISK_DRIVE) {
                    wave_ram_p = (u8*)Nas_Alloc_Single(wavetable->size, 0xFE, wavetable->sample, (u8)wavetable->medium,
                        CACHE_TEMPORARY);
                }
            } break;
        }

        if (wave_ram_p == NULL) {
            continue;
        }

        switch (async) {
            case FALSE:
                if (wavetable->medium == MEDIUM_DISK) {
                    Nas_FastDiskCopy(wavetable->sample, wave_ram_p, wavetable->size, AG.wave_header->medium);
                    wavetable->medium = MEDIUM_RAM;
                    wavetable->sample = wave_ram_p;
                } else {
                    Nas_FastCopy((uintptr_t)wavetable->sample, wave_ram_p, wavetable->size, wavetable->medium);
                    wavetable->medium = MEDIUM_RAM;
                    wavetable->sample = wave_ram_p;
                }
                break;
            case TRUE:
                preload = &AG.requested_samples[AG.num_requested_samples];
                preload->sample = wavetable;
                preload->ram_addr = wave_ram_p;
                preload->encoded_info = (AG.num_requested_samples << 24) | 0x00FFFFFF;
                preload->is_free = FALSE;
                preload->end_and_medium_key =
                    (NaLoadAddress)(uintptr_t)wavetable->sample + wavetable->size + wavetable->medium;
                AG.num_requested_samples++;
                break;
        }
    }

    AG.num_used_samples = 0;
    if (AG.num_requested_samples != 0 && !preloading) {
        i = AG.num_requested_samples - 1;
        top_preload = &AG.requested_samples[i];
        wavetable = top_preload->sample;
        // n_chunks = 1;
        n_chunks += (wavetable->size / 0x1000);
        Nas_BgCopyReq(wavetable->sample, top_preload->ram_addr, wavetable->size, wavetable->medium, n_chunks,
                      &AG.preload_sample_queue, top_preload->encoded_info);
    }

    // @BUG - this function clearly has no return value
    // it must have been declared with a return value because
    // mwcceppc has prevented r3 as a temp where possible
}

s32 Nas_CheckBgWave(s32 reset_status) {
    smzwavetable* wavetable;
    Bgloadreq* preload;
    u32 preload_idx;
    OSMesg preload_msg;
    NaLoadAddress key;
    s32 n_chunks;

    if (AG.num_requested_samples > 0) {
        if (reset_status != 0) {
            Z_osRecvMesg(&AG.preload_sample_queue, &preload_msg, OS_MESG_NOBLOCK);
            AG.num_requested_samples = 0;
            return FALSE;
        }

        if (Z_osRecvMesg(&AG.preload_sample_queue, &preload_msg, OS_MESG_NOBLOCK) == -1) {
            return FALSE;
        }

        preload_idx = (u32)(uintptr_t)preload_msg;

        preload_idx >>= 24;
        preload = &AG.requested_samples[preload_idx];

        if (!preload->is_free) {
            wavetable = preload->sample;
            key = (NaLoadAddress)(uintptr_t)wavetable->sample + wavetable->size + wavetable->medium;

            if (preload->end_and_medium_key == key) {
                wavetable->sample = preload->ram_addr;
                wavetable->medium = MEDIUM_RAM;
            }

            preload->is_free = TRUE;
        }

        while (TRUE) {
            if (AG.num_requested_samples <= 0) {
                break;
            }

            preload = &AG.requested_samples[AG.num_requested_samples - 1];
            if (preload->is_free == TRUE) {
                AG.num_requested_samples--;
                continue;
            }

            wavetable = preload->sample;
            n_chunks = 1;
            n_chunks += (wavetable->size / 0x1000);
            key = (NaLoadAddress)(uintptr_t)wavetable->sample + wavetable->size + wavetable->medium;
            if (preload->end_and_medium_key != key) {
                preload->is_free = TRUE;
                AG.num_requested_samples--;
            } else {
                Nas_BgCopyReq(wavetable->sample, preload->ram_addr, wavetable->size, wavetable->medium, n_chunks,
                              &AG.preload_sample_queue, preload->encoded_info);
                break;
            }
        }
    }

    return TRUE;
}

// @unused static s32 __AddList(smzwavetable* wavetable, s32 n_samples, Loadlist* loadlist)

// @unused s32 MakeWaveList(s32 bank_id, Loadlist* loadlist);

static void __Reload(wtstr* wavetouch_str) {
    smzwavetable* wavetable = wavetouch_str->wavetable;

    if (wavetable->size != 0 && wavetable->bit26 && wavetable->medium != MEDIUM_RAM) {
        AG.used_samples[AG.num_used_samples++] = wavetable;
    }
}

void WaveReload(s32 bank_id, s32 async, WaveMedia* wavemedia) {
    s32 n_drums;
    s32 n_instruments;
    s32 n_sfx;
    perctable* percussion;
    voicetable* instrument;
    percvoicetable* sfx;
    Bgloadreq* preload;
    Bgloadreq* top_preload;
    smzwavetable* wavetable;
    u8* addr;
    s32 size;
    s32 i;
    s32 preloading;
    s32 n_chunks;

    preloading = FALSE;
    if (AG.num_requested_samples != 0) {
        preloading = TRUE;
    }

    AG.num_used_samples = 0;
    n_drums = AG.voice_info[bank_id].num_drums;
    n_instruments = AG.voice_info[bank_id].num_instruments;
    n_sfx = AG.voice_info[bank_id].num_sfx;

    for (i = 0; i < n_instruments; i++) {
        instrument = ProgToVp(bank_id, i);

        if (instrument != NULL) {
            if (instrument->normal_range_low != 0) {
                __Reload(&instrument->low_pitch_tuned_sample);
            }

            if (instrument->normal_range_high != 0x7F) {
                __Reload(&instrument->high_pitch_tuned_sample);
            }

            __Reload(&instrument->normal_pitch_tuned_sample);
        }
    }

    for (i = 0; i < n_drums; i++) {
        percussion = PercToPp(bank_id, i);

        if (percussion != NULL) {
            __Reload(&percussion->tuned_sample);
        }
    }

    for (i = 0; i < n_sfx; i++) {
        sfx = VpercToVep(bank_id, i);

        if (sfx != NULL) {
            __Reload(&sfx->tuned_sample);
        }
    }

    if (AG.num_used_samples == 0) {
        return;
    }

    size = 0;
    for (i = 0; i < AG.num_used_samples; i++) {
        size += ALIGN_NEXT(AG.used_samples[i]->size, 32);
    }

    for (i = 0; i < AG.num_used_samples; i++) {
        if (AG.num_requested_samples == 120) {
            break;
        }

        wavetable = AG.used_samples[i];
        if (wavetable->medium == MEDIUM_RAM) {
            continue;
        }

        switch (async) {
            case FALSE:
                if (wavetable->medium == wavemedia->wave0_media) {
                    addr = (u8*)Nas_Alloc_Single(wavetable->size, wavemedia->wave0_bank_id, wavetable->sample,
                                                 wavetable->medium, CACHE_PERSISTENT);
                } else if (wavetable->medium == wavemedia->wave1_media) {
                    addr = (u8*)Nas_Alloc_Single(wavetable->size, wavemedia->wave1_bank_id, wavetable->sample,
                                                 wavetable->medium, CACHE_PERSISTENT);
                }
                break;
            case TRUE:
                if (wavetable->medium == wavemedia->wave0_media) {
                    addr = (u8*)Nas_Alloc_Single(wavetable->size, wavemedia->wave0_bank_id, wavetable->sample,
                                                 wavetable->medium, CACHE_TEMPORARY);
                } else if (wavetable->medium == wavemedia->wave1_media) {
                    addr = (u8*)Nas_Alloc_Single(wavetable->size, wavemedia->wave1_bank_id, wavetable->sample,
                                                 wavetable->medium, CACHE_TEMPORARY);
                }
                break;
        }

        if (addr == NULL) {
            continue;
        }

        switch (async) {
            case FALSE:
                if (wavetable->medium == MEDIUM_DISK) {
                    Nas_FastDiskCopy(wavetable->sample, addr, wavetable->size, AG.wave_header->medium);
                    wavetable->medium = MEDIUM_RAM;
                    wavetable->sample = addr;
                } else {
                    Nas_FastCopy((uintptr_t)wavetable->sample, addr, wavetable->size, wavetable->medium);
                    wavetable->medium = MEDIUM_RAM;
                    wavetable->sample = addr;
                }
                break;
            case TRUE:
                preload = &AG.requested_samples[AG.num_requested_samples];
                preload->sample = wavetable;
                preload->ram_addr = addr;
                preload->encoded_info = (AG.num_requested_samples << 24) | 0x00FFFFFF;
                preload->is_free = FALSE;
                preload->end_and_medium_key =
                    (NaLoadAddress)(uintptr_t)wavetable->sample + wavetable->size + wavetable->medium;
                AG.num_requested_samples++;
                break;
        }
    }

    AG.num_used_samples = 0;
    if (AG.num_requested_samples != 0 && !preloading) {
        top_preload = &AG.requested_samples[AG.num_requested_samples - 1];
        wavetable = top_preload->sample;
        n_chunks = 1;
        n_chunks += (wavetable->size / 0x1000);
        Nas_BgCopyReq(wavetable->sample, top_preload->ram_addr, wavetable->size, wavetable->medium, n_chunks,
                      &AG.preload_sample_queue, top_preload->encoded_info);
    }
}

void EmemReload(void) {
    s32 i;
    s32 bank_id;
    ArcHeader* header;

    header = __Get_ArcHeader(WAVE_TABLE);
    for (i = 0; i < AG.emem_heap.count; i++) {
        WaveMedia wavemedia;

        if (AG.emem_entries[i].table_type == BANK_TABLE) {
            bank_id = __Link_BankNum(BANK_TABLE, AG.emem_entries[i].id);
            wavemedia.wave0_bank_id = AG.voice_info[bank_id].wave_bank_id0;
            wavemedia.wave1_bank_id = AG.voice_info[bank_id].wave_bank_id1;

            if (wavemedia.wave0_bank_id != 0xFF) {
                wavemedia.wave0_bank_id = __Link_BankNum(WAVE_TABLE, wavemedia.wave0_bank_id);
                wavemedia.wave0_media = header->entries[wavemedia.wave0_bank_id].medium;
            }

            if (wavemedia.wave1_bank_id != 0xFF) {
                wavemedia.wave1_bank_id = __Link_BankNum(WAVE_TABLE, wavemedia.wave1_bank_id);
                wavemedia.wave1_media = header->entries[wavemedia.wave1_bank_id].medium;
            }

            WaveReload(bank_id, FALSE, &wavemedia);
        }
    }
}

// @unused static ? __ExtDiskFinishCheck(Extdisk* extdisk);

// @unused static ? __ExtDiskInit(Extdisk* extdisk, s32 param0, s32 param1, u8* param2, s32 param3);

// @unused static ? __ExtDiskLoad(Extdisk* extdisk);

#define MK_ENTRIES 16

OSMesgQueue MK_QUEUE;
OSMesg MK_QBUF[MK_ENTRIES];
u8* MK_RMES[MK_ENTRIES];

void MK_load(s32 table_type, s32 id, u8* done_p) {
    static s32 use = 0;

    MK_RMES[use] = done_p;
    Nas_PreLoad_BG(table_type, id, 0, use, &MK_QUEUE);
    use++;
    if (use == MK_ENTRIES) {
        use = 0;
    }
}

void MK_FrameWork(void) {
    s32 idx;
    u32 ret;
    OSMesg msg;
    u8* rmes;

    if (Z_osRecvMesg(&MK_QUEUE, &msg, OS_MESG_NOBLOCK) != -1) {
        ret = (u32)(uintptr_t)msg;
        idx = ret >> 24;
        rmes = MK_RMES[idx];
        if (rmes != NULL) {
            *rmes = 0;
        }
    }
}

void MK_Init(void) {
    Z_osCreateMesgQueue(&MK_QUEUE, MK_QBUF, MK_ENTRIES);
}
