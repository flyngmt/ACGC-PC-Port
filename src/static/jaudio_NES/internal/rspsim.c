#include "jaudio_NES/rspsim.h"

#include <dolphin/os.h>
#include "jaudio_NES/sample.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/audiocommon.h"

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))
#define CLAMP_S16(x) CLAMP(x, -0x8000, 0x7FFF)

static u8 DMEM[0x1000] ATTRIBUTE_ALIGN(32);
static u32 ADPCM_BOOKBUF_SIZE = 0;
static s16 ADPCM_BOOKBUF[8][16] ATTRIBUTE_ALIGN(32);
static s16 FINALR_STATE_BUF[16] ATTRIBUTE_ALIGN(32);

static s16 RES_FILTER[64][4] ATTRIBUTE_ALIGN(32) = {
    0x0C39, 0x66AD, 0x0D46, 0xFFDF, 0x0B39, 0x6696, 0x0E5F, 0xFFD8, 0x0A44, 0x6669, 0x0F83, 0xFFD0, 0x095A, 0x6626,
    0x10B4, 0xFFC8, 0x087D, 0x65CD, 0x11F0, 0xFFBF, 0x07AB, 0x655E, 0x1338, 0xFFB6, 0x06E4, 0x64D9, 0x148C, 0xFFAC,
    0x0628, 0x643F, 0x15EB, 0xFFA1, 0x0577, 0x638F, 0x1756, 0xFF96, 0x04D1, 0x62CB, 0x18CB, 0xFF8A, 0x0435, 0x61F3,
    0x1A4C, 0xFF7E, 0x03A4, 0x6106, 0x1BD7, 0xFF71, 0x031C, 0x6007, 0x1D6C, 0xFF64, 0x029F, 0x5EF5, 0x1F0B, 0xFF56,
    0x022A, 0x5DD0, 0x20B3, 0xFF48, 0x01BE, 0x5C9A, 0x2264, 0xFF3A, 0x015B, 0x5B53, 0x241E, 0xFF2C, 0x0101, 0x59FC,
    0x25E0, 0xFF1E, 0x00AE, 0x5896, 0x27A9, 0xFF10, 0x0063, 0x5720, 0x297A, 0xFF02, 0x001F, 0x559D, 0x2B50, 0xFEF4,
    0xFFE2, 0x540D, 0x2D2C, 0xFEE8, 0xFFAC, 0x5270, 0x2F0D, 0xFEDB, 0xFF7C, 0x50C7, 0x30F3, 0xFED0, 0xFF53, 0x4F14,
    0x32DC, 0xFEC6, 0xFF2E, 0x4D57, 0x34C8, 0xFEBD, 0xFF0F, 0x4B91, 0x36B6, 0xFEB6, 0xFEF5, 0x49C2, 0x38A5, 0xFEB0,
    0xFEDF, 0x47ED, 0x3A95, 0xFEAC, 0xFECE, 0x4611, 0x3C85, 0xFEAB, 0xFEC0, 0x4430, 0x3E74, 0xFEAC, 0xFEB6, 0x424A,
    0x4060, 0xFEAF, 0xFEAF, 0x4060, 0x424A, 0xFEB6, 0xFEAC, 0x3E74, 0x4430, 0xFEC0, 0xFEAB, 0x3C85, 0x4611, 0xFECE,
    0xFEAC, 0x3A95, 0x47ED, 0xFEDF, 0xFEB0, 0x38A5, 0x49C2, 0xFEF5, 0xFEB6, 0x36B6, 0x4B91, 0xFF0F, 0xFEBD, 0x34C8,
    0x4D57, 0xFF2E, 0xFEC6, 0x32DC, 0x4F14, 0xFF53, 0xFED0, 0x30F3, 0x50C7, 0xFF7C, 0xFEDB, 0x2F0D, 0x5270, 0xFFAC,
    0xFEE8, 0x2D2C, 0x540D, 0xFFE2, 0xFEF4, 0x2B50, 0x559D, 0x001F, 0xFF02, 0x297A, 0x5720, 0x0063, 0xFF10, 0x27A9,
    0x5896, 0x00AE, 0xFF1E, 0x25E0, 0x59FC, 0x0101, 0xFF2C, 0x241E, 0x5B53, 0x015B, 0xFF3A, 0x2264, 0x5C9A, 0x01BE,
    0xFF48, 0x20B3, 0x5DD0, 0x022A, 0xFF56, 0x1F0B, 0x5EF5, 0x029F, 0xFF64, 0x1D6C, 0x6007, 0x031C, 0xFF71, 0x1BD7,
    0x6106, 0x03A4, 0xFF7E, 0x1A4C, 0x61F3, 0x0435, 0xFF8A, 0x18CB, 0x62CB, 0x04D1, 0xFF96, 0x1756, 0x638F, 0x0577,
    0xFFA1, 0x15EB, 0x643F, 0x0628, 0xFFAC, 0x148C, 0x64D9, 0x06E4, 0xFFB6, 0x1338, 0x655E, 0x07AB, 0xFFBF, 0x11F0,
    0x65CD, 0x087D, 0xFFC8, 0x10B4, 0x6626, 0x095A, 0xFFD0, 0x0F83, 0x6669, 0x0A44, 0xFFD8, 0x0E5F, 0x6696, 0x0B39,
    0xFFDF, 0x0D46, 0x66AD, 0x0C39,
};

static s16 AD2[4] = { 0x0000, 0x0001, 0xFFFE, 0xFFFF };

static s16 AD4[16] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
    0xFFF8, 0xFFF9, 0xFFFA, 0xFFFB, 0xFFFC, 0xFFFD, 0xFFFE, 0xFFFF,
};

static void Jac_Resample16(s16* input_L_channel, s16* input_R_channel, s16* output_interleaved, s32 input_sample_count,
                           s32 output_sample_count, s16* history_buffer, u16* position_p, s32 is_first_block);

extern void RspStart2(void* task, s32 tasks, s32 mode) {
    static Acmd* taskp;
    static s32 alltasks;
    static s32 consumes;

    if (mode == RSPSIM_MODE_INIT) {
        taskp = (Acmd*)task;
        alltasks = tasks;
    }

    if (alltasks > 0) {
        consumes = RspStart(taskp, alltasks);
        alltasks -= consumes;
        taskp += consumes;
    }
}

#define DMEM_OFS(ofs) ((s16*)&((u8*)DMEM)[(ofs)])

/*
 * Discrete per-command implementations of the RSP audio ABI, used by RspStart below.
 * These mirror the behavior of the equivalent `case` blocks in RspStart exactly. The state
 * that RspStart keeps as locals shared across cases within a single call (DMEM in/out/count,
 * the loadcache source/offset, the loop point, the envelope ramp params, and the FIR
 * coefficient table set up by aFirLoadTable) is kept here as file static state instead,
 * since it must persist across the discrete per-command calls.
 */
static u16 sDMEMIn;
static u16 sDMEMOut;
static u16 sDMEMCount;
static void* sLoopPoint;
static u8* sLoadCacheSrc;
static u16 sLoadCacheOffset;
static s16 sEnvRampRev;
static s16 sEnvRampL;
static s16 sEnvRampR;
static u16 sEnvRevVol;
static u16 sEnvVolL;
static u16 sEnvVolR;
static s16* sFirCoefTable;
static s32 sFirCoefCount;

// A_LOADCACHE (special to GC?): prefetches `len` bytes from `src` into the data cache and
// remembers (src, offset) so a later A_ADPCM/A_S8DEC command can compute its input pointer
// as src + DMEMIn - offset.
// cmdHi: [31:24] cmd, [23:16] len>>4, [15:0] offset
// cmdLo: src address
static void Rsp_LoadCache(u32 cmdHi, uintptr_t cmdAddr) {
    sLoadCacheSrc = (u8*)cmdAddr;
    sLoadCacheOffset = cmdHi & 0xFFFF;
    DCTouchRange((void*)cmdAddr, ((cmdHi >> 16) & 0xFF) * 16);
}

// A_ADPCM: decodes ADPCM-compressed input bytes (from the LOADCACHE source, or looped/history
// history when flagged) into 16-bit PCM samples written to DMEM at sDMEMOut+32, one 16-sample
// block at a time. Each block starts with a header byte selecting a 16-entry predictor/filter
// table from ADPCM_BOOKBUF and a shift amount, decodes 8 nibbles (or 4 crumbs) per half-block,
// and predicts each sample from the two prior decoded samples plus a weighted sum of the
// still-undecoded residuals in the same half-block. The last decoded block is copied back to
// cmdAddr as history for the next call.
// cmdHi: [31:24] cmd, [23:16] flags (1=clear history, 2=loop point, 4=4-bit/crumb samples)
// cmdAddr: source address (ignored when flags&1 or flags&2), also the history save destination
static void Rsp_Adpcm(u32 cmdHi, uintptr_t cmdAddr) {
    u8 flags = cmdHi >> 16;
    s16 block[16];
    s32 stage1[8];
    s32 stage2[8];
    s32 j;
    s16 header;
    s32 shift;
    u16 outOffset = sDMEMOut + 32;
    u8* inPtr;
    s16* outPtr = (s16*)&DMEM[outOffset];
    s16* coefTable;
    s16 prev1;
    s16 prev2;
    u16 blockCount = (sDMEMCount + 31) / 32;
    s32 acc;
    s32 k;
    s16* lastBlock;

    if (flags & 1) {
        // clear history
        Jac_bzero(&DMEM[sDMEMOut], 16 * sizeof(s16));
    } else if (flags & 2) {
        // copy from loop_point
        Jac_bcopy(sLoopPoint, &DMEM[sDMEMOut], 16 * sizeof(s16));
    } else {
        // copy from address in command
        Jac_bcopy((void*)cmdAddr, &DMEM[sDMEMOut], 16 * sizeof(s16));
    }

    // prev1/prev2 must be read after the history block above is (re)written, since they seed
    // the predictor from its last two samples.
    prev1 = outPtr[-1];
    prev2 = outPtr[-2];
    inPtr = sLoadCacheSrc + sDMEMIn - sLoadCacheOffset;
    for (j = 0; j < blockCount; j++) {
        coefTable = ADPCM_BOOKBUF[0];
        header = (s16)*inPtr++;
        shift = (header >> 4);

        header &= 0xF;
        coefTable += header * 16;
        if (flags & 4) {
            for (k = 0; k < 4; k++) {
                s16 nibbles = *inPtr++;
                block[k * 4 + 0] = AD2[(nibbles >> 6) & 3];
                block[k * 4 + 1] = AD2[(nibbles >> 4) & 3];
                block[k * 4 + 2] = AD2[(nibbles >> 2) & 3];
                block[k * 4 + 3] = AD2[(nibbles >> 0) & 3];
            }
        } else {
            for (k = 0; k < 8; k++) {
                s16 nibbles = *inPtr++;
                block[k * 2 + 0] = AD4[(nibbles >> 4) & 0xF];
                block[k * 2 + 1] = AD4[(nibbles >> 0) & 0xF];
            }
        }
        for (k = 0; k < 8; k++) {
            stage1[k] = block[k] << shift;
            s32 l;
#ifdef TARGET_PC
            acc = stage1[k] << 11;
            acc += prev1 * coefTable[k + 8];
            acc += prev2 * coefTable[k];
            for (l = 0; l < k; l++) {
                acc += stage1[l] * coefTable[k - l + 7];
            }
            acc >>= 11;
#else
            acc = (prev1 * coefTable[k + 8] / 0x800) + (prev2 * coefTable[k] / 0x800) + stage1[k];
            for (l = 0; l < k; l++) {
                acc += stage1[l] * coefTable[k - l + 7] / 0x800;
            }
#endif
            block[k] = CLAMP_S16(acc);
        }
        prev1 = block[7];
        prev2 = block[6];
        for (k = 0; k < 8; k++) {
            stage2[k] = block[k + 8] << shift;
            s32 l;
#ifdef TARGET_PC
            acc = stage2[k] << 11;
            acc += prev1 * coefTable[k + 8];
            acc += prev2 * coefTable[k];
            for (l = 0; l < k; l++) {
                acc += stage2[l] * coefTable[k - l + 7];
            }
            acc >>= 11;
#else
            acc = (prev1 * coefTable[k + 8] / 0x800) + (prev2 * coefTable[k] / 0x800) + stage2[k];
            for (l = 0; l < k; l++) {
                acc += stage2[l] * coefTable[k - l + 7] / 0x800;
            }
#endif
            block[k + 8] = CLAMP_S16(acc);
        }
        prev1 = block[15];
        prev2 = block[14];
        for (k = 0; k < 16; k++) {
            *outPtr++ = block[k];
        }
    }
    lastBlock = outPtr - 16;
    Jac_bcopy(lastBlock, (void*)cmdAddr, 16 * sizeof(s16));
}

// A_CLEARBUFF: zeroes `size` bytes of DMEM starting at `addr`.
// cmdHi: [31:24] cmd, [15:0] addr
// cmdLo: [15:0] size
static void Rsp_ClearBuff(u32 cmdHi, u32 cmdLo) {
    u16 addr = cmdHi & 0xFFFF;
    u16 size = cmdLo & 0xFFFF;
    Jac_bzero(&DMEM[addr], size);
}

// A_RESAMPLE: resamples mono audio from DMEM sDMEMIn to DMEM sDMEMOut using a 4-tap FIR
// polyphase filter (RES_FILTER), stepping the input position by a fixed-point `pitch` per
// output sample. `pitchAccu` and the 4-sample circular history buffer are persisted in the
// command's state block (cmdLo) across calls so the resample position/filter history carries
// over between audio frames.
// cmdHi: [31:24] cmd, [15:0] pitch (16.16 fixed-point step)
// cmdLo: state block address: history[8] + pitchAccu (or zero to reset state), also the save destination
static void Rsp_Resample(u32 cmdHi, uintptr_t cmdAddr) {
    s16 history[8];
    s16* inPtr;
    s32 j;
    s16* outPtr;
    u32 pitchAccu;
    s32 circularBufIdx;
    s16* filterCoefs;
    s32 sampleA;
    s32 pitch;
    s32 sampleB;
    u16 sampleCount;

    sampleCount = sDMEMCount >> 1;
    pitch = cmdHi & 0xFFFF;
    if ((cmdHi >> 16) & 1) {
        Jac_bzero(history, 8 * sizeof(s16));
        pitchAccu = 0;
    } else {
        Jac_bcopy((void*)cmdAddr, history, 8 * sizeof(s16));
        pitchAccu = history[4] & 0x7FFF;
    }
    inPtr = (s16*)&DMEM[sDMEMIn];
    outPtr = (s16*)&DMEM[sDMEMOut];
    circularBufIdx = 4;

    for (j = 0; j < sampleCount >> 1; j++) {
        filterCoefs = RES_FILTER[(pitchAccu >> 9) & 0x7FFFFF];
        sampleA = filterCoefs[3] * history[circularBufIdx - 1] + filterCoefs[2] * history[circularBufIdx - 2] + filterCoefs[1] * history[circularBufIdx - 3] + filterCoefs[0] * history[circularBufIdx - 4];
        pitchAccu += pitch;
        while (pitchAccu >= 0x8000) {
            history[circularBufIdx] = *inPtr++;
            history[circularBufIdx - 4] = history[circularBufIdx];
            circularBufIdx++;
            pitchAccu -= 0x8000;
            if (circularBufIdx == 8) {
                circularBufIdx = 4;
            }
        }
        filterCoefs = RES_FILTER[(pitchAccu >> 9) & 0x7FFFFF];
        sampleB = filterCoefs[3] * history[circularBufIdx - 1] + filterCoefs[2] * history[circularBufIdx - 2] + filterCoefs[1] * history[circularBufIdx - 3] + filterCoefs[0] * history[circularBufIdx - 4];
        pitchAccu += pitch;
        while (pitchAccu >= 0x8000) {
            history[circularBufIdx] = *inPtr++;
            history[circularBufIdx - 4] = history[circularBufIdx];
            circularBufIdx++;
            pitchAccu -= 0x8000;
            if (circularBufIdx == 8) {
                circularBufIdx = 4;
            }
        }
        sampleA >>= 15;
        *outPtr++ = CLAMP_S16(sampleA);
        sampleB >>= 15;
        *outPtr++ = CLAMP_S16(sampleB);
    }
    history[circularBufIdx] = pitchAccu & 0x7FFF;
    Jac_bcopy(&history[circularBufIdx - 4], (void*)cmdAddr, 8 * sizeof(s16));
}

// A_SETBUFF: sets the shared DMEM input offset, output offset, and sample count consumed by
// later ADPCM/RESAMPLE/PCM8DEC commands in this batch.
// cmdHi: [31:24] cmd, [15:0] DMEMIn
// cmdLo: [31:16] DMEMOut, [15:0] DMEMCount
static void Rsp_SetBuff(u32 cmdHi, u32 cmdLo) {
    sDMEMIn = cmdHi & 0xFFFF;
    sDMEMOut = (cmdLo >> 16) & 0xFFFF;
    sDMEMCount = cmdLo & 0xFFFF;
}

// A_DUPLICATE: copies `count` chunks of 0x80 bytes each from `src` to `dst` within DMEM,
// advancing both pointers by 0x80 after each chunk.
// cmdHi: [31:24] cmd, [23:16] count, [15:0] src
// cmdLo: [31:16] dst
static void Rsp_Duplicate(u32 cmdHi, u32 cmdLo) {
    s32 j;
    u16 src = cmdHi & 0xFFFF;
    u16 dst = cmdLo >> 16;
    s32 count = (cmdHi >> 16) & 0xFF;

    for (j = 0; j < count; j++) {
        Jac_bcopy(&DMEM[src], &DMEM[dst], 0x80);
        src += 0x80;
        dst += 0x80;
    }
}

// A_DMEMMOVE: copies `size` bytes within DMEM from `src` to `dst`.
// cmdHi: [31:24] cmd, [15:0] src
// cmdLo: [31:16] dst, [15:0] size
static void Rsp_DmemMove(u32 cmdHi, u32 cmdLo) {
    u16 src = cmdHi & 0xFFFF;
    u16 dst = cmdLo >> 16;
    u16 size = cmdLo & 0xFFFF;
    Jac_bcopy(&DMEM[src], &DMEM[dst], size);
}

// A_LOADADPCM: loads the ADPCM predictor/filter table used by Rsp_Adpcm from `src` into
// ADPCM_BOOKBUF.
// cmdHi: [31:24] cmd, [15:0] size (bytes)
// cmdLo: src address
static void Rsp_LoadAdpcm(u32 cmdHi, uintptr_t cmdAddr) {
    Jac_bcopy((void*)cmdAddr, ADPCM_BOOKBUF, cmdHi & 0xFFFF);
    ADPCM_BOOKBUF_SIZE = cmdHi & 0xFFFF;
}

// A_ADDMIXER / A_MIXER: mixes `count*8` samples from `src` into `dst` in DMEM, scaling each
// source sample by a Q15 `gain` before accumulating (dst[i] += (src[i] * gain) >> 15).
// cmdHi: [31:24] cmd, [23:16] count (in units of 8 samples), [15:0] gain (Q15)
// cmdLo: [31:16] src offset, [15:0] dst offset
static void Rsp_Mixer(u32 cmdHi, u32 cmdLo) {
    s16* src = DMEM_OFS(cmdLo >> 16);
    s16* dst = DMEM_OFS(cmdLo & 0xFFFF);
    s32 count = (cmdHi >> 16) & 0xFF;
    s16 gain = cmdHi & 0xFFFF;
    s32 j;

    for (j = 0; j < count * 8; j++) {
        s16 sample = *src++;
        s32 mixed = *dst;
        mixed += (sample * gain) >> 15;
        *dst++ = CLAMP_S16(mixed);
    }
}

// A_INTERLEAVE: resamples/interleaves the two mono DMEM buffers `inL`/`inR` into a stereo
// output buffer via Jac_Resample16 (a separate, unrelated resampler from Rsp_Resample's
// RES_FILTER one). `isFirstBlock` is true only for the very first call ever, to reset the
// resampler's persistent phase/history state.
// cmdHi: [31:24] cmd, [23:16] count>>3, [15:0] out
// cmdLo: [31:16] inL, [15:0] inR
static void Rsp_Interleave(u32 cmdHi, u32 cmdLo) {
    u16 inL = cmdLo >> 16;
    u16 inR = cmdLo & 0xFFFF;
    u16 out = cmdHi & 0xFFFF;
    u16 count = ((cmdHi >> 16) & 0xFF) << 3;
    s16* pInL;
    s16* pInR;
    s16* pOut;
    static s32 isFirstBlock = TRUE;
    static u16 finalr_phase;
    static s16* finalr_state;

    if (isFirstBlock == TRUE) {
        finalr_state = FINALR_STATE_BUF;
    }

    pInL = DMEM_OFS(inL);
    pInR = DMEM_OFS(inR);
    pOut = DMEM_OFS(out);
    Jac_Resample16(pInR, pInL, pOut, count, JAC_FRAMESAMPLES >> 2, finalr_state, &finalr_phase, isFirstBlock);
    isFirstBlock = FALSE;
}

// A_SETLOOP: remembers the sample loop point later A_ADPCM/A_S8DEC commands copy their
// history from when their "loop point" flag bit is set.
// cmdLo: loop point address
static void Rsp_SetLoop(uintptr_t cmdAddr) {
    sLoopPoint = (void*)cmdAddr;
}

// ??? (unnamed/unidentified command): repeatedly copies `stride`-byte chunks within DMEM
// from `src` to `dst`, `count` times, advancing both pointers by `stride` each time.
// cmdHi: [31:24] cmd, [23:16] count, [15:0] dst
// cmdLo: [31:16] src, [15:0] stride
static void Rsp_Unk16(u32 cmdHi, u32 cmdLo) {
    s32 stride;
    u32 dst;
    u32 src;
    s32 j;
    s32 count;
    dst = cmdHi & 0xFFFF;
    src = cmdLo >> 16;
    stride = cmdLo & 0xFFFF;
    count = (cmdHi >> 16) & 0xFF;
    for (j = 0; j < count; j++) {
        Jac_bcopy(&DMEM[(u16)dst], &DMEM[(u16)src], stride);
        dst += stride;
        src += stride;
    }
}

// A_INTERL: downsamples by discarding every other 16-bit sample, copying `count` samples
// from `src` to `dst` while advancing src by 2 samples per dst sample.
// cmdHi: [31:24] cmd, [15:0] count
// cmdLo: [31:16] src, [15:0] dst
static void Rsp_HalfCut(u32 cmdHi, u32 cmdLo) {
    s16* src = (s16*)&DMEM[cmdLo >> 16];
    s16* dst = (s16*)&DMEM[cmdLo & 0xFFFF];
    s32 count = cmdHi & 0xFFFF;
    s32 j;

    for (j = 0; j < count; j++) {
        *dst = *src;
        src += 2;
        dst += 1;
    }
}

// A_LOADBUFF2: copies `count*16` bytes from `src` into DMEM at `dst`.
// cmdHi: [31:24] cmd, [23:16] count, [15:0] dst
// cmdLo: src address
static void Rsp_LoadBuffer2(u32 cmdHi, uintptr_t cmdAddr) {
    u16 size = ((cmdHi >> 16) & 0xFF) * 16;
    Jac_bcopy((void*)cmdAddr, (s16*)&DMEM[cmdHi & 0xFFFF], size);
}

// A_SAVEBUFF2: copies `count*16` bytes from DMEM at `src` to `dst`. Inverse of Rsp_LoadBuffer2.
// cmdHi: [31:24] cmd, [23:16] count, [15:0] src
// cmdAddr: dst address
static void Rsp_SaveBuffer2(u32 cmdHi, uintptr_t cmdAddr) {
    u16 size = ((cmdHi >> 16) & 0xFF) * 16;
    Jac_bcopy(DMEM_OFS(cmdHi & 0xFFFF), (void*)cmdAddr, size);
}

// A_ENVSETUP1 (aSetEnvParam): sets the reverb volume and the per-4-samples ramp rates that
// Rsp_EnvMixer applies to the reverb volume and the L/R envelope volumes.
// cmdHi: [31:24] cmd, [23:16] revVol, [15:0] rampRev
// cmdLo: [31:16] rampL, [15:0] rampR
static void Rsp_SetEnvParam(u32 cmdHi, u32 cmdLo) {
    u8 revVol = cmdHi >> 16;
    sEnvRampRev = cmdHi & 0xFFFF;
    sEnvRampL = cmdLo >> 16;
    sEnvRampR = cmdLo & 0xFFFF;
    sEnvRevVol = revVol << 8;
}

// A_ENVSETUP2 (aSetEnvParam2): sets the current L/R envelope volumes that Rsp_EnvMixer scales
// dry samples by before ramping them via A_ENVSETUP1's rates.
// cmdLo: [31:16] volL, [15:0] volR
static void Rsp_SetEnvParam2(u32 cmdLo) {
    sEnvVolL = cmdLo >> 16;
    sEnvVolR = cmdLo & 0xFFFF;
}

// A_ENVMIXER: applies the envelope set up by A_ENVSETUP1/A_ENVSETUP2 to `sampleCount` mono dry
// samples read from `dryPtr`, mixing each sample scaled by the current L/R volume into the
// `outL`/`outR` dry accumulators, and additionally scaled by the reverb volume into the
// `wetL`/`wetR` accumulators. Every 4 samples, the L/R volumes and reverb volume are advanced
// by their configured ramp rates. `negateVolL`/`negateVolR` optionally invert the polarity of
// the L-/R-scaled contributions (e.g. for out-of-phase reverb sends).
// cmdHi: [31:24] cmd, [23:16] dry buffer offset>>4, [15:8] sampleCount, [1] negateVolL, [0] negateVolR
// cmdLo: [31:24] outL offset>>4, [23:16] outR offset>>4, [15:8] wetL offset>>4, [7:0] wetR offset>>4
static void Rsp_EnvMixer(u32 cmdHi, u32 cmdLo) {
    s32 touchSize;
    s16* dryPtr;
    s16* outL;
    s16* outR;
    s16* wetL;
    s16* wetR;
    s32 j;
    u16 pairCount;
    u8 negateVolL;
    u8 negateVolR;
    u8 sampleCount;
    // Cached locally so the loop below can keep them in registers instead of reloading from
    // static storage every sample pair; written back to the shared state once at the end.
    u16 volL = sEnvVolL;
    u16 volR = sEnvVolR;
    u16 revVol = sEnvRevVol;

    negateVolL = cmdHi & 2;
    negateVolR = cmdHi & 1;
    sampleCount = (u8)(cmdHi >> 8);

    touchSize = sampleCount << 1;
    dryPtr = (s16*)&DMEM[((cmdHi >> 16) & 0xFF) * 16];
    outL = (s16*)&DMEM[((cmdLo >> 24) & 0xFF) * 16];
    outR = (s16*)&DMEM[((cmdLo >> 16) & 0xFF) * 16];
    DCTouchRange(outL, touchSize);
    DCTouchRange(outR, touchSize);
    wetL = (s16*)&DMEM[(cmdLo >> 4) & 0xFF0];
    wetR = (s16*)&DMEM[(cmdLo << 4) & 0xFF0];
    DCTouchRange(wetL, touchSize);
    DCTouchRange(wetR, touchSize);

    pairCount = sampleCount >> 1;
    for (j = 0; j < pairCount; j++) {
        s16 sample0 = *dryPtr++;
        s32 sample1 = *dryPtr++;

        s32 sample0ByVolL = (sample0 * volL) >> 16;
        s32 sample0ByVolR = (sample0 * volR) >> 16;
        s32 sample1ByVolL = (sample1 * volL) >> 16;
        s32 sample1ByVolR = (sample1 * volR) >> 16;
        if (negateVolL) {
            sample0ByVolL = -sample0ByVolL;
            sample1ByVolL = -sample1ByVolL;
        }
        if (negateVolR) {
            sample0ByVolR = -sample0ByVolR;
            sample1ByVolR = -sample1ByVolR;
        }

        s32 outL0 = outL[0] + sample0ByVolL;
        s32 outL1 = outL[1] + sample1ByVolL;
        s32 outR0 = outR[0] + sample0ByVolR;
        s32 outR1 = outR[1] + sample1ByVolR;

        *outL++ = CLAMP_S16(outL0);
        *outL++ = CLAMP_S16(outL1);
        *outR++ = CLAMP_S16(outR0);
        *outR++ = CLAMP_S16(outR1);

        s32 wetRawL0 = sample0ByVolL * revVol;
        s32 wetRawR0 = sample0ByVolR * revVol;
        s32 wetRawL1 = sample1ByVolL * revVol;
        s32 wetRawR1 = sample1ByVolR * revVol;
        f32 wet0FromVolL = (wetRawL0 >> 16) + (wetRawL0 >> 18) + (wetRawL0 >> 19);
        f32 wet0FromVolR = (wetRawR0 >> 16) + (wetRawR0 >> 18) + (wetRawR0 >> 19);
        f32 wet1FromVolL = (wetRawL1 >> 16) + (wetRawL1 >> 18) + (wetRawL1 >> 19);
        f32 wet1FromVolR = (wetRawR1 >> 16) + (wetRawR1 >> 18) + (wetRawR1 >> 19);

        s32 wetL0 = wetL[0] + wet0FromVolL;
        s32 wetL1 = wetL[1] + wet1FromVolL;
        s32 wetR0 = wetR[0] + wet0FromVolR;
        s32 wetR1 = wetR[1] + wet1FromVolR;
        *wetL++ = CLAMP_S16(wetL0);
        *wetL++ = CLAMP_S16(wetL1);
        *wetR++ = CLAMP_S16(wetR0);
        *wetR++ = CLAMP_S16(wetR1);
        if ((j & 3) == 3) {
            volL += sEnvRampL;
            volR += sEnvRampR;
            revVol += sEnvRampRev;
        }
    }

    sEnvVolL = volL;
    sEnvVolR = volR;
    sEnvRevVol = revVol;
}

// A_S8DEC: decodes 8-bit PCM input bytes (from the LOADCACHE source, or looped/cleared history
// when flagged) into 16-bit samples by shifting each byte left 8, writing them to DMEM at
// sDMEMOut+32. The untouched history block at sDMEMOut is copied back to cmdLo unchanged, for
// symmetry with Rsp_Adpcm's history save (though here it's just the setup block, not the
// newly decoded tail).
// cmdHi: [31:24] cmd, [23:16] flags (1=clear history, 2=loop point)
// cmdLo: source address (ignored when flags&1 or flags&2), also the history save destination
static void Rsp_Pcm8Dec(u32 cmdHi, uintptr_t cmdAddr) {
    u8 flags = cmdHi >> 16;

    if (flags & 1) {
        // clear history
        Jac_bzero(DMEM_OFS(sDMEMOut), 16 * sizeof(s16));
    } else if (flags & 2) {
        // copy from loop_point
        Jac_bcopy(sLoopPoint, DMEM_OFS(sDMEMOut), 16 * sizeof(s16));
    } else {
        // copy from address in command
        Jac_bcopy((void*)cmdAddr, DMEM_OFS(sDMEMOut), 16 * sizeof(s16));
    }

    u16 decodeOffset = sDMEMOut + 32;
    s16* dst = (s16*)&DMEM[decodeOffset];
    u8* src = sLoadCacheSrc + sDMEMIn - sLoadCacheOffset;
    u16 count = sDMEMCount >> 1;
    s32 j;

    for (j = 0; j < count; j++) {
        *dst++ = (*src++) << 8;
    }

    Jac_bcopy(&DMEM[sDMEMOut], (void*)cmdAddr, 32);
}

// A_FILTER: an 8-tap FIR filter applied in place to DMEM samples at `dst`, using the
// coefficient table most recently loaded via aFirLoadTable (flags&2). The filter keeps an
// 8-sample circular history buffer, seeded from `cmdAddr` (or cleared, if flagged) and saved
// back to `cmdAddr` afterward.
// cmdHi: [31:24] cmd, [23:16] flags (2=load coefficient table instead of filtering,
//        1=clear history when filtering), [15:0] dst offset (filtering) or coefficient count*2 (loading)
// cmdAddr: history seed/save address (filtering) or coefficient table address (loading)
static void Rsp_FirFilter(u32 cmdHi, uintptr_t cmdAddr) {
    s16 history[16];
    s16 taps[16];
    u8 flags;
    s16* dst;
    s32 circularIdx;
    s16 oldSample;
    s32 acc;
    s32 j;
    s32 k;

    flags = cmdHi >> 16;
    if (flags & 2) {
        // aFirLoadTable: stash the coefficient table for later A_FILTER commands to use
        sFirCoefTable = (s16*)cmdAddr;
        sFirCoefCount = (cmdHi & 0xFFFF) >> 1;
    } else {
        dst = (s16*)&DMEM[cmdHi & 0xFFFF];
        if (flags & 1) {
            for (j = 0; j < 16; j++) {
                history[j] = 0;
            }
        } else {
            Jac_bcopy((void*)cmdAddr, history, 16 * sizeof(s16));
        }
        for (j = 0; j < 8; j++) {
            taps[j] = sFirCoefTable[j] >> 3;
            taps[j + 8] = taps[j];
        }
        circularIdx = 0;
        for (j = 0; j < sFirCoefCount; j++) {
            acc = 0;
            for (k = 0; k < 8; k++) {
                acc += history[k] * taps[k + 8 - circularIdx];
            }
            acc >>= 12;
            oldSample = *dst;
            *dst++ = CLAMP_S16(acc);
            history[circularIdx++] = oldSample;
            if (circularIdx == 8) {
                circularIdx = 0;
            }
        }
        Jac_bcopy(history, (void*)cmdAddr, 16 * sizeof(s16));
    }
}

extern s32 RspStart(void* task_commands, s32 allTasks) {
    Acmd* pTaskCmds = (Acmd*)task_commands;
    s32 i;
    u32 cmdLo;
    u32 cmdHi;
    uintptr_t cmdAddr;

    for (i = 0; i < allTasks; i++) {
        cmdLo = pTaskCmds->words.w1;
        cmdHi = pTaskCmds->words.w0;
#ifdef TARGET_PC
        cmdAddr = pTaskCmds->host.address;
#else
        cmdAddr = cmdLo;
#endif
        pTaskCmds++;

        switch (cmdHi >> 24) {
            case A_CMD_LOADCACHE:
                Rsp_LoadCache(cmdHi, cmdAddr);
                break;

            case A_CMD_SPNOOP:
                break;

            case A_CMD_ADPCM:
                Rsp_Adpcm(cmdHi, cmdAddr);
                break;

            case A_CMD_CLEARBUFF:
                Rsp_ClearBuff(cmdHi, cmdLo);
                break;

            case A_CMD_RESAMPLE:
                Rsp_Resample(cmdHi, cmdAddr);
                break;

            case A_CMD_SETBUFF:
                Rsp_SetBuff(cmdHi, cmdLo);
                break;

            case A_CMD_DUPLICATE:
                Rsp_Duplicate(cmdHi, cmdLo);
                break;

            case A_CMD_DMEMMOVE:
                Rsp_DmemMove(cmdHi, cmdLo);
                break;

            case A_CMD_LOADADPCM:
                Rsp_LoadAdpcm(cmdHi, cmdAddr);
                break;

            case A_CMD_ADDMIXER:
            case A_CMD_MIXER:
                Rsp_Mixer(cmdHi, cmdLo);
                break;

            case A_CMD_INTERLEAVE:
                Rsp_Interleave(cmdHi, cmdLo);
                break;

            case A_CMD_SETLOOP:
                Rsp_SetLoop(cmdAddr);
                break;

            case A_CMD_UNK16:
                Rsp_Unk16(cmdHi, cmdLo);
                break;

            case A_CMD_HALFCUT:
                Rsp_HalfCut(cmdHi, cmdLo);
                break;

            case A_CMD_LOADBUFFER2:
                Rsp_LoadBuffer2(cmdHi, cmdAddr);
                break;

            case A_CMD_SAVEBUFFER2:
                Rsp_SaveBuffer2(cmdHi, cmdAddr);
                break;

            case A_CMD_SETENVPARAM:
                Rsp_SetEnvParam(cmdHi, cmdLo);
                break;

            case A_CMD_SETENVPARAM2:
                Rsp_SetEnvParam2(cmdLo);
                break;

            case A_CMD_ENVMIXER:
                Rsp_EnvMixer(cmdHi, cmdLo);
                break;

            case A_CMD_PCM8DEC:
                Rsp_Pcm8Dec(cmdHi, cmdAddr);
                break;

            case A_CMD_FIRFILTER:
                Rsp_FirFilter(cmdHi, cmdAddr);
                break;

            case A_CMD_EXIT:
                return i + 1;
        }
    }
    return allTasks;
}

static void Jac_Resample16(
    s16* input_L_channel,
    s16* input_R_channel,
    s16* output_interleaved,
    s32 input_sample_count,
    s32 output_sample_count,
    s16* history_buffer,
    u16* position_p,
    s32 is_first_block
) {
    u32 current_pos_fract;
    s32 circular_buf_idx;
    s16* history_write_ptr;
    u32 next_pos_fract;
    s32 interpolated_sample_L, interpolated_sample_R;
    s32 step_increment;
    s32 i;

    // Calculate the resampling ratio as a 16.16 fixed-point number.
    // This determines how much to step through the input for each output sample.
    step_increment = (input_sample_count << 16) / output_sample_count;

    if ((is_first_block & 1) != 0) {
        // FIrst block, clear the history buffer and reset the position.
        Jac_bzero(history_buffer, 16 * sizeof(s16)); // Zero out 32 bytes (16 samples)
        current_pos_fract = 0;
    } else {
        // If this is not the first block of audio, load the last fractional position.
        current_pos_fract = (u16)*position_p;
    }

    // This loop appears to be a safeguard, possibly to handle edge cases where the
    // step increment is very large. It adjusts the step value to prevent over-reading.
    while (TRUE) {
        // Predict the position after processing all output samples.
        next_pos_fract = current_pos_fract + step_increment * output_sample_count;
        // The position is stored in 16.16 fixed point, so we shift to get the integer part.
        if ((next_pos_fract >> 16) < input_sample_count) {
            step_increment++;
        } else if ((next_pos_fract >> 16) > input_sample_count + 1) {
            // If we'd read past the end of the input, reduce the step slightly and re-check.
            step_increment--;
        } else {
            break;
        }
    }

    // Initialize the index for our circular history buffer.
    circular_buf_idx = 4;
    while (output_sample_count-- > 0) {
        // --- Polyphase FIR Filter Calculation ---
        // Use the top bits of the fractional position to look up coefficients from the filter table.
        s16* filter_table = RES_FILTER[current_pos_fract >> 10];

        // LEFT CHANNEL: Apply 4-tap FIR filter (multiply-accumulate)
        // It multiplies 4 historical samples by 4 filter coefficients.
        interpolated_sample_L =
            filter_table[3] * history_buffer[circular_buf_idx - 1] +
            filter_table[2] * history_buffer[circular_buf_idx - 2] +
            filter_table[1] * history_buffer[circular_buf_idx - 3] +
            filter_table[0] * history_buffer[circular_buf_idx - 4];
        interpolated_sample_L >>= 15;

        // RIGHT CHANNEL: Apply 4-tap FIR filter
        // The history buffer stores L and R channels interleaved. We access the R samples at an offset of +4.
        interpolated_sample_R =
            filter_table[3] * history_buffer[circular_buf_idx + 7] +
            filter_table[2] * history_buffer[circular_buf_idx + 6] +
            filter_table[1] * history_buffer[circular_buf_idx + 5] +
            filter_table[0] * history_buffer[circular_buf_idx + 4];
        interpolated_sample_R >>= 15;

        // --- Clamping and Output ---
        // Clamp the Left sample to the valid 16-bit range [-32768, 32767].
        if (interpolated_sample_L > 0x7fff) interpolated_sample_L = 0x7fff;
        if (interpolated_sample_L < -0x8000) interpolated_sample_L = -0x8000;

        // Clamp the Right sample.
        if (interpolated_sample_R > 0x7fff) interpolated_sample_R = 0x7fff;
        if (interpolated_sample_R < -0x8000) interpolated_sample_R = -0x8000;

        // Write the interleaved stereo pair to the output buffer.
        *output_interleaved++ = (short)interpolated_sample_L;
        *output_interleaved++ = (short)interpolated_sample_R;

        // Advance the fractional position and the output pointer.
        current_pos_fract += step_increment;

        // --- History Buffer Management ---
        // If the integer part of our position has advanced, we need to pull new samples
        // from the input buffers into our circular history buffer.
        while (current_pos_fract >= 0x10000) {
            s16 read;
            
            history_write_ptr = &history_buffer[circular_buf_idx++];

            // Load next sample from Left channel input.
            read = *input_L_channel++;
            history_write_ptr[0] = read;
            history_write_ptr[-4] = history_write_ptr[0]; // Part of circular buffer logic

            // Load next sample from Right channel input.
            read = *input_R_channel++;
            history_write_ptr[8] = read;
            history_write_ptr[4] = history_write_ptr[8]; // Part of circular buffer logic

            // Decrement the fractional part of the position tracker.
            current_pos_fract -= 0x10000;

            // Wrap the circular buffer index. It holds 4 stereo pairs (8 samples total).
            if (circular_buf_idx == 8) {
                circular_buf_idx = 4;
            }
        }
    }

    // --- State Saving ---
    // Save the final fractional position for the next call.
    *position_p = (u16)current_pos_fract;

    // Re-arrange the history buffer so the last 4 samples are at the beginning,
    // ready for the next call to the function. This preserves the state.
    {
        s16* src_ptr;
        s16* dest_ptr;
        s32 i;

        for (i = 0; i < 4; i++) {
            src_ptr = &history_buffer[circular_buf_idx - 4 + i];
            dest_ptr = &history_buffer[i];
    
            dest_ptr[0] = src_ptr[0]; // Copy Left channel sample
            dest_ptr[8] = src_ptr[8]; // Copy Right channel sample
        }
    }
}
