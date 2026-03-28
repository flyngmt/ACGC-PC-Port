#ifndef AUDIOCOMMON_H
#define AUDIOCOMMON_H

#include "types.h"
#include "PR/abi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define S16_MIN (-0x8000)
#define S16_MAX (0x7FFF)

#define AUDIO_PRELOAD_SEQ (1 << 0)
#define AUDIO_PRELOAD_BANK (1 << 1)

#define AUDIO_ARAM_SIZE 0x400000 /* 4MB */
#define AUDIO_ARAM_HEAP_SIZE 0xC000

#define AUDIO_GROUP_MAX 5
#define AUDIO_SUBTRACK_NUM 16
#define AUDIO_NOTE_MAX 128
#define AUDIO_SUBTRACK_NOTE_NUM 4

#define AUDIO_TATUMS_PER_BEAT 48

#define AUDIO_GROUP_ALL_SUBTRACKS (0xFFFF)

#define AUDIO_MUTE_FLAG_STOP_SAMPLES (1 << 3)
#define AUDIO_MUTE_FLAG_STOP_SUBTRACK (1 << 4)
#define AUDIO_MUTE_FLAG_SOFTEN (1 << 5)
#define AUDIO_MUTE_FLAG_STOP_NOTE (1 << 6)
#define AUDIO_MUTE_FLAG_STOP_SCRIPT (1 << 7)

#define ADSR_DISABLE 0
#define ADSR_HANG -1
#define ADSR_GOTO -2
#define ADSR_RESTART -3
#define ADSR_SPECIAL4 -4 // TODO: figure this out

#define A_ADPCM_SHORT 0x04

// Audio ABI commands
#define A_CMD_SPNOOP        0
#define A_CMD_ADPCM         1
#define A_CMD_CLEARBUFF     2
#define A_CMD_UNK3          3
#define A_CMD_ADDMIXER      4
#define A_CMD_RESAMPLE      5
#define A_CMD_RESAMPLE_ZOH  6
#define A_CMD_FIRFILTER     7
#define A_CMD_SETBUFF       8
#define A_CMD_DUPLICATE     9
#define A_CMD_DMEMMOVE      10
#define A_CMD_LOADADPCM     11
#define A_CMD_MIXER         12
#define A_CMD_INTERLEAVE    13
#define A_CMD_DISTFILTER    14
#define A_CMD_SETLOOP       15
#define A_CMD_UNK16         16
#define A_CMD_HALFCUT       17
#define A_CMD_SETENVPARAM   18
#define A_CMD_ENVMIXER      19
#define A_CMD_LOADBUFFER2   20
#define A_CMD_SAVEBUFFER2   21
#define A_CMD_SETENVPARAM2  22
#define A_CMD_PCM8DEC       23
#define A_CMD_LOADCACHE     24
#define A_CMD_EXIT          25

#define aUnkCmd3(pkt, a1, a2, a3)                                       \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = _SHIFTL(A_CMD_UNK3, 24, 8) | _SHIFTL(a3, 0, 16);     \
        _a->words.w1 = _SHIFTL(a1, 16, 16) | _SHIFTL(a2, 0, 16);        \
}

#define	aHalfCut(pkt, src, dst, len)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_HALFCUT, 24, 8) | _SHIFTL(len, 0, 16);    		\
	_a->words.w1 = _SHIFTL(src, 16, 16) | _SHIFTL(dst, 0, 16);		\
}

#define	aSetEnvParam(pkt, revVol, rampRev, rampL, rampR)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_SETENVPARAM, 24, 8) | _SHIFTL(revVol, 16, 8) | _SHIFTL(rampRev, 0, 16);    		\
	_a->words.w1 = _SHIFTL(rampL, 16, 16) | _SHIFTL(rampR, 0, 16);		\
}

#define	aLoadCache(pkt, dst, src, len)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_LOADCACHE, 24, 8) | _SHIFTL((len) >> 4, 16, 8) | _SHIFTL(src, 0, 16);    		\
	_a->words.w1 = (u32)(uintptr_t)(dst);	\
}

#define	aLoadBuffer2(pkt, dst, src, len)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_LOADBUFFER2, 24, 8) | _SHIFTL((len) >> 4, 16, 8) | _SHIFTL(src, 0, 16);    		\
	_a->words.w1 = (u32)(uintptr_t)(dst);	\
}

#define	aSaveBuffer2(pkt, dst, src, len)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_SAVEBUFFER2, 24, 8) | _SHIFTL((len) >> 4, 16, 8) | _SHIFTL(src, 0, 16);    		\
	_a->words.w1 = (u32)(uintptr_t)(dst);	\
}

#define	aInterleave2(pkt, o, l, r, c)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
    _a->words.w0 = (_SHIFTL(A_INTERLEAVE, 24, 8) | _SHIFTL(c >> 4, 16, 8) | _SHIFTL(o, 0, 16));            \
    _a->words.w1 = _SHIFTL(l, 16, 16) | _SHIFTL(r, 0, 16);          \
}

#define	aSetEnvParam2(pkt, volL, volR)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_SETENVPARAM2, 24, 8);    		\
	_a->words.w1 = _SHIFTL(volL, 16, 16) | _SHIFTL(volR, 0, 16);		\
}

#define aPCM8dec(pkt, flags, state)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_PCM8DEC, 24, 8) | _SHIFTL(flags, 16, 8);    		\
	_a->words.w1 = (u32)(state);		\
}

#define aDistFilter(pkt, gain, dmem_in, dmem_out, len)						\
{									\
	Acmd *_a = (Acmd *)pkt;						\
									\
	_a->words.w0 = _SHIFTL(A_CMD_DISTFILTER, 24, 8) | _SHIFTL(gain, 16, 8) | _SHIFTL(len, 0, 16);    		\
	_a->words.w1 = _SHIFTL(dmem_in, 16, 16) | _SHIFTL(dmem_out, 0, 16);		\
}

#define aNoiseFilter(pkt, buf, f, addr, len)                               \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = _SHIFTL(A_CMD_SPNOOP, 24, 8) | _SHIFTL(f, 16, 8) |   \
                    _SHIFTL(addr, 0, 16);                         \
        _a->words.w1 = _SHIFTL(len, 16, 16) | _SHIFTL(buf, 0, 16);                            \
}

#define aFirFilter(pkt, f, bufSize, addr)                               \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = _SHIFTL(A_CMD_FIRFILTER, 24, 8) | _SHIFTL(f, 16, 8) |   \
                    _SHIFTL(bufSize, 0, 16);                         \
        _a->words.w1 = (unsigned int)(addr);                            \
}

#define aFirLoadTable(pkt, size, addr) aFirFilter(pkt, 2, size, addr)

#define aEnvMixer2(pkt, dmemi, count, swapLR, x0, x1, x2, x3, m, bits)   \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = (bits | _SHIFTL(dmemi >> 4, 16, 8) |             \
                _SHIFTL(count, 8, 8) | _SHIFTL(swapLR, 4, 1) |          \
                _SHIFTL(x0, 3, 1) | _SHIFTL(x1, 2, 1) |                 \
                _SHIFTL(x2, 1, 1) | _SHIFTL(x3, 0, 1));                 \
        _a->words.w1 = (unsigned int)(m);                               \
}

#define aAddMixer(pkt, count, dmemi, dmemo, a4)                         \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = (_SHIFTL(A_CMD_ADDMIXER, 24, 8) |                    \
                _SHIFTL(count >> 4, 16, 8) | _SHIFTL(a4, 0, 16));       \
        _a->words.w1 = _SHIFTL(dmemi, 16, 16) | _SHIFTL(dmemo, 0, 16);  \
}

// from MM
#define aResampleZoh(pkt, pitch, pitchAccu)                             \
{                                                                       \
        Acmd *_a = (Acmd *)pkt;                                         \
                                                                        \
        _a->words.w0 = (_SHIFTL(A_CMD_RESAMPLE_ZOH, 24, 8) |                \
                _SHIFTL(pitch, 0, 16));                                 \
        _a->words.w1 = _SHIFTL(pitchAccu, 0, 16);                       \
}

#define NA_MAKE_COMMAND(a0, a1, a2, a3) \
    (u32)((((a0) & 0xFF) << 24) | (((a1) & 0xFF) << 16) | (((a2) & 0xFF) << 8) | (((a3) & 0xFF) << 0))

typedef enum DSPBUF_EVENTS {
    DSPBUF_EVENT_INIT = 0,
    DSPBUF_EVENT_FRAME_END = 1,
    DSPBUF_EVENT_MIX = 2,
} DSPBUF_EVENTS;

typedef enum SampleMedium {
    /* 0 */ MEDIUM_RAM,
    /* 1 */ MEDIUM_DISK,
    /* 2 */ MEDIUM_CART,
    /* 3 */ MEDIUM_DISK_DRIVE,
    /* 5 */ MEDIUM_RAM_UNLOADED = 5
} SampleMedium;

typedef enum AudioCacheType {
    /* 0 */ CACHE_TEMPORARY,
    /* 1 */ CACHE_PERSISTENT,
    /* 2 */ CACHE_EITHER,
    /* 3 */ CACHE_PERMANENT
} AudioCacheType;

typedef enum AudioCacheLoadType {
    /* 0 */ CACHE_LOAD_PERMANENT,
    /* 1 */ CACHE_LOAD_PERSISTENT,
    /* 2 */ CACHE_LOAD_TEMPORARY,
    /* 3 */ CACHE_LOAD_EITHER,
    /* 4 */ CACHE_LOAD_EITHER_NOSYNC
} AudioCacheLoadType;

typedef enum AudioLoadStatus {
    /* 0 */ LOAD_STATUS_NOT_LOADED,
    /* 1 */ LOAD_STATUS_IN_PROGRESS,
    /* 2 */ LOAD_STATUS_COMPLETE,
    /* 3 */ LOAD_STATUS_DISCARDABLE,
    /* 4 */ LOAD_STATUS_MAYBE_DISCARDABLE,
    /* 5 */ LOAD_STATUS_PERMANENT
} AudioLoadStatus;

typedef enum AdsrStatus {
    /* 0 */ ADSR_STATUS_DISABLED,
    /* 1 */ ADSR_STATUS_INITIAL,
    /* 2 */ ADSR_STATUS_START_LOOP,
    /* 3 */ ADSR_STATUS_LOOP,
    /* 4 */ ADSR_STATUS_FADE,
    /* 5 */ ADSR_STATUS_HANG,
    /* 6 */ ADSR_STATUS_DECAY,
    /* 7 */ ADSR_STATUS_RELEASE,
    /* 8 */ ADSR_STATUS_SUSTAIN
} AdsrStatus;

typedef enum PortamentoMode {
    /* 0 */ PORTAMENTO_MODE_OFF,
    /* 1 */ PORTAMENTO_MODE_1,
    /* 2 */ PORTAMENTO_MODE_2,
    /* 3 */ PORTAMENTO_MODE_3,
    /* 4 */ PORTAMENTO_MODE_4,
    /* 5 */ PORTAMENTO_MODE_5,
    /* 6 */ PORTAMENTO_MODE_6,
    /* 7 */ PORTAMENTO_MODE_7,
    /* 8 */ PORTAMENTO_MODE_8, // might be PORTAMENTO_MODE_NUM
} PortamentoMode;

typedef enum SampleBankTableType {
    /* 0 */ SEQUENCE_TABLE,
    /* 1 */ BANK_TABLE,
    /* 2 */ WAVE_TABLE
} SampleBankTableType;

typedef enum ExtDataType {
    EXT_TYPE_DATA,
    EXT_TYPE_SIZE,

    EXT_TYPE_NUM
} ExtDataType;

typedef enum SoundOutputMode {
    /* 0 */ SOUND_OUTPUT_STEREO,
    /* 1 */ SOUND_OUTPUT_HEADSET,
    /* 2 */ SOUND_OUTPUT_SURROUND,
    /* 3 */ SOUND_OUTPUT_MONO,
    /* 4 */ SOUND_OUTPUT_DOLBY_SURROUND
} SoundOutputMode;

typedef enum SampleCodec {
    /* 0 */ CODEC_ADPCM, // 16 2-byte samples (32 bytes) compressed into 4-bit samples (8 bytes) + 1 header byte
    /* 1 */ CODEC_S8,    // 16 2-byte samples (32 bytes) compressed into 8-bit samples (16 bytes)
    /* 2 */ CODEC_S16_INMEMORY,
    /* 3 */ CODEC_SMALL_ADPCM, // 16 2-byte samples (32 bytes) compressed into 2-bit samples (4 bytes) + 1 header byte
    /* 4 */ CODEC_REVERB,
    /* 5 */ CODEC_S16,
    /* 6 */ CODEC_UNK6,
    /* 7 */ CODEC_UNK7,
} SampleCodec;

typedef enum LpsCacheState {
    /* 0 */ LPS_CACHE_STATE_WAITING,
    /* 1 */ LPS_CACHE_STATE_START,
    /* 2 */ LPS_CACHE_STATE_LOADING,
    /* 3 */ LPS_CACHE_STATE_DONE
} LpsCacheState;

typedef enum PhaseType {
    PHASE_TYPE_0,
    PHASE_TYPE_1,
    PHASE_TYPE_2,
    PHASE_TYPE_3,

    PHASE_TYPE_NUM
} PhaseType;

#define VOICE_TYPE_PERCUSSION 0
#define VOICE_TYPE_SOUND_EFF 1
#define VOICE_TYPE_INSTRUMENT_START 2

#define AUDIO_SWEEP_IS_SPECIAL(s) ((s).mode & 0x80)
#define AUDIO_SWEEP_MODE(s) ((s).mode & ~0x80)

#define AUDIO_NOTE_RELEASE (1 << 0)
#define AUDIO_NOTE_SAMPLE_NOTES (1 << 1)

#define AUDIOCMD_ALL_GROUPS 0xFF
#define AUDIOCMD_ALL_SUBTRACKS 0xFF

typedef enum GroupState {
    /* 0 */ GROUP_STATE_0,
    /* 1 */ GROUP_STATE_FADE_IN,
    /* 2 */ GROUP_STATE_FADE_OUT
} GroupState;

/* Most of these are from the MM decomp */
typedef enum AudioCmd {
    /* 0x00 */ AUDIOCMD_NOOP,

    // SubTrack Commands
    /* 0x01 */ AUDIOCMD_OP_SUB_SET_VOL_SCALE,
    /* 0x02 */ AUDIOCMD_OP_SUB_SET_VOL,
    /* 0x03 */ AUDIOCMD_OP_SUB_SET_PAN,
    /* 0x04 */ AUDIOCMD_OP_SUB_SET_FREQ_SCALE,
    /* 0x05 */ AUDIOCMD_OP_SUB_SET_REVERB_VOLUME,
    /* 0x06 */ AUDIOCMD_OP_SUB_SET_PORT,
    /* 0x07 */ AUDIOCMD_OP_SUB_SET_PAN_WEIGHT,
    /* 0x08 */ AUDIOCMD_OP_SUB_SET_MUTE,
    /* 0x09 */ AUDIOCMD_OP_SUB_SET_MUTE_FLAGS,
    /* 0x0A */ AUDIOCMD_OP_SUB_SET_VIBRATO_DEPTH,
    /* 0x0B */ AUDIOCMD_OP_SUB_SET_VIBRATO_RATE,
    /* 0x0C */ AUDIOCMD_OP_SUB_SET_COMB_FILTER_SIZE,
    /* 0x0D */ AUDIOCMD_OP_SUB_SET_COMB_FILTER_GAIN,
    /* 0x0E */ AUDIOCMD_OP_SUB_SET_STEREO,
    /* 0x0F */ AUDIOCMD_OP_SUB_SET_SET_START_POS,
    /* 0x10 */ AUDIOCMD_OP_SUB_SET_SFX_STATE,
    /* 0x11 */ AUDIOCMD_OP_SUB_SET_REVERB_INDEX,
    /* 0x12 */ AUDIOCMD_OP_SUB_SET_SURROUND_EFFECT_INDEX,
    /* 0x13 */ AUDIOCMD_OP_SUB_SET_FILTER,
    /* 0x14 */ AUDIOCMD_OP_SUB_SET_GAIN,
    /* 0x15 */ AUDIOCMD_OP_SUB_SET_TRANSPOSITION,

    // Group Commands
    /* 0x41 */ AUDIOCMD_OP_GRP_FADE_VOLUME_SCALE = 0x41,
    /* 0x46 */ AUDIOCMD_OP_GRP_SET_PORT = 0x46,
    /* 0x47 */ AUDIOCMD_OP_GRP_SET_TEMPO,
    /* 0x48 */ AUDIOCMD_OP_GRP_SET_TRANSPOSITION,
    /* 0x49 */ AUDIOCMD_OP_GRP_CHANGE_TEMPO,
    /* 0x4A */ AUDIOCMD_OP_GRP_FADE_TO_SET_VOLUME,
    /* 0x4B */ AUDIOCMD_OP_GRP_FADE_TO_SCALED_VOLUME,
    /* 0x4C */ AUDIOCMD_OP_GRP_RESET_VOLUME,
    /* 0x4D */ AUDIOCMD_OP_GRP_SET_BEND,
    /* 0x4E */ AUDIOCMD_OP_GRP_CHANGE_TEMPO_TICKS,

    // System Commands
    /* 0x81 */ AUDIOCMD_PRELOAD_SEQ = 0x81,
    /* 0x82 */ AUDIOCMD_START_SEQ,
    /* 0x83 */ AUDIOCMD_STOP_SEQ,
    /* 0x85 */ AUDIOCMD_START_SEQ_SKIP = 0x85,
    /* 0x90 */ AUDIOCMD_SET_GROUP_MASK = 0x90,

    /* 0xE0 */ AUDIOCMD_SET_PERC_BANK = 0xE0,
    /* 0xE1 */ AUDIOCMD_SET_EFFECT_BANK,
    /* 0xE2 */ AUDIOCMD_SET_VOICE_BANK,
    /* 0xE3 */ AUDIOCMD_CLEAR_STAY_CACHE,
    /* 0xE4 */ AUDIOCMD_SET_CALLBACK,
    /* 0xE5 */ AUDIOCMD_SET_EXTERNAL_POINTER,
    /* 0xE6 */ AUDIOCMD_SET_DELAY_LINE_PARAM,

    /* 0xF0 */ AUDIOCMD_SET_SOUND_MODE = 0xF0,
    /* 0xF1 */ AUDIOCMD_MUTE,
    /* 0xF2 */ AUDIOCMD_UNMUTE,
    /* 0xF3 */ AUDIOCMD_LOAD_VOICE_INSTRUMENT,
    /* 0xF4 */ AUDIOCMD_PRELOADWAVE_BG,
    /* 0xF5 */ AUDIOCMD_PRELOADBANK_BG,
    /* 0xF6 */ AUDIOCMD_FLUSH_BANKS,
    /* 0xF8 */ AUDIOCMD_SYS_STOP_PROCESSING = 0xF8,
    /* 0xF9 */ AUDIOCMD_RESET_AUDIO_HEAP,
    /* 0xFA */ AUDIOCMD_MAIN_GROUP_SUBPORT_CMD,
    /* 0xFB */ AUDIOCMD_SET_VFRAME_CALLBACK,
    /* 0xFC */ AUDIOCMD_PRELOADSEQ_BG,
    /* 0xFD */ AUDIOCMD_MAIN_GROUP_SET_FREQ_SCALE,
    /* 0xFE */ AUDIOCMD_FORCE_STOP_ALL_GROUPS,
    /* 0xFF */ AUDIOCMD_MAIN_GROUP_SET_VOL_SCALE
} AudioCmd;

typedef enum CommonCmd {
    COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO = 0xF2,
    COMMON_CMD_BRANCH_REL_EQ_ZERO = 0xF3,
    COMMON_CMD_BRANCH_REL = 0xF4,
    COMMON_CMD_BRANCH_ABS_GREQ_ZERO = 0xF5,
    COMMON_CMD_BREAK = 0xF6,
    COMMON_CMD_LOOP_END = 0xF7,
    COMMON_CMD_LOOP = 0xF8,
    COMMON_CMD_BRANCH_ABS_NOT_EQ_ZERO = 0xF9,
    COMMON_CMD_BRANCH_ABS_EQ_ZERO = 0xFA,
    COMMON_CMD_BRANCH_ABS = 0xFB,
    COMMON_CMD_CALL = 0xFC,
    COMMON_CMD_DELAY_N_FRAMES = 0xFD,
    COMMON_CMD_DELAY_1_FRAME = 0xFE,
    COMMON_CMD_STOP_SCRIPT = 0xFF,
} CommonCmd;

typedef enum GroupCmd {
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK_DISABLED_MASK = 0x00,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK0_DISABLED = 0x00,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK1_DISABLED = 0x01,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK2_DISABLED = 0x02,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK3_DISABLED = 0x03,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK4_DISABLED = 0x04,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK5_DISABLED = 0x05,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK6_DISABLED = 0x06,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK7_DISABLED = 0x07,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK8_DISABLED = 0x08,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK9_DISABLED = 0x09,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK10_DISABLED = 0x0A,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK11_DISABLED = 0x0B,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK12_DISABLED = 0x0C,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK13_DISABLED = 0x0D,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK14_DISABLED = 0x0E,
    GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK15_DISABLED = 0x0F,

    GRP_CMD_DISABLE_SUBTRACK_MASK = 0x40,
    GRP_CMD_DISABLE_SUBTRACK0 = 0x40,
    GRP_CMD_DISABLE_SUBTRACK1 = 0x41,
    GRP_CMD_DISABLE_SUBTRACK2 = 0x42,
    GRP_CMD_DISABLE_SUBTRACK3 = 0x43,
    GRP_CMD_DISABLE_SUBTRACK4 = 0x44,
    GRP_CMD_DISABLE_SUBTRACK5 = 0x45,
    GRP_CMD_DISABLE_SUBTRACK6 = 0x46,
    GRP_CMD_DISABLE_SUBTRACK7 = 0x47,
    GRP_CMD_DISABLE_SUBTRACK8 = 0x48,
    GRP_CMD_DISABLE_SUBTRACK9 = 0x49,
    GRP_CMD_DISABLE_SUBTRACK10 = 0x4A,
    GRP_CMD_DISABLE_SUBTRACK11 = 0x4B,
    GRP_CMD_DISABLE_SUBTRACK12 = 0x4C,
    GRP_CMD_DISABLE_SUBTRACK13 = 0x4D,
    GRP_CMD_DISABLE_SUBTRACK14 = 0x4E,
    GRP_CMD_DISABLE_SUBTRACK15 = 0x4F,

    GRP_CMD_MACRO_VALUE_SUBTRACT_FROM_PORT_MASK = 0x50,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT0 = 0x50,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT1 = 0x51,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT2 = 0x52,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT3 = 0x53,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT4 = 0x54,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT5 = 0x55,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT6 = 0x56,
    GRP_CMD_MACRO_VALUE_SUBTRACT_BY_PORT7 = 0x57,

    GRP_CMD_ASYNC_LOAD_MASK = 0x60,
    GRP_CMD_ASYNC_LOAD_PORT0 = 0x60,
    GRP_CMD_ASYNC_LOAD_PORT1 = 0x61,
    GRP_CMD_ASYNC_LOAD_PORT2 = 0x62,
    GRP_CMD_ASYNC_LOAD_PORT3 = 0x63,
    GRP_CMD_ASYNC_LOAD_PORT4 = 0x64,
    GRP_CMD_ASYNC_LOAD_PORT5 = 0x65,
    GRP_CMD_ASYNC_LOAD_PORT6 = 0x66,
    GRP_CMD_ASYNC_LOAD_PORT7 = 0x67,

    GRP_CMD_MACRO_VALUE_WRITE_PORT_MASK = 0x70,
    GRP_CMD_MACRO_VALUE_WRITE_PORT0 = 0x70,
    GRP_CMD_MACRO_VALUE_WRITE_PORT1 = 0x71,
    GRP_CMD_MACRO_VALUE_WRITE_PORT2 = 0x72,
    GRP_CMD_MACRO_VALUE_WRITE_PORT3 = 0x73,
    GRP_CMD_MACRO_VALUE_WRITE_PORT4 = 0x74,
    GRP_CMD_MACRO_VALUE_WRITE_PORT5 = 0x75,
    GRP_CMD_MACRO_VALUE_WRITE_PORT6 = 0x76,
    GRP_CMD_MACRO_VALUE_WRITE_PORT7 = 0x77,

    GRP_CMD_MACRO_VALUE_READ_PORT_MASK = 0x80,
    GRP_CMD_MACRO_VALUE_READ_PORT0 = 0x80, // cleared to 0xFF on read
    GRP_CMD_MACRO_VALUE_READ_PORT1 = 0x81, // cleared to 0xFF on read
    GRP_CMD_MACRO_VALUE_READ_PORT2 = 0x82,
    GRP_CMD_MACRO_VALUE_READ_PORT3 = 0x83,
    GRP_CMD_MACRO_VALUE_READ_PORT4 = 0x84,
    GRP_CMD_MACRO_VALUE_READ_PORT5 = 0x85,
    GRP_CMD_MACRO_VALUE_READ_PORT6 = 0x86,
    GRP_CMD_MACRO_VALUE_READ_PORT7 = 0x87,

    // Absolute address
    GRP_CMD_START_SUBTRACK_MASK = 0x90,
    GRP_CMD_START_SUBTRACK0 = 0x90,
    GRP_CMD_START_SUBTRACK1 = 0x91,
    GRP_CMD_START_SUBTRACK2 = 0x92,
    GRP_CMD_START_SUBTRACK3 = 0x93,
    GRP_CMD_START_SUBTRACK4 = 0x94,
    GRP_CMD_START_SUBTRACK5 = 0x95,
    GRP_CMD_START_SUBTRACK6 = 0x96,
    GRP_CMD_START_SUBTRACK7 = 0x97,
    GRP_CMD_START_SUBTRACK8 = 0x98,
    GRP_CMD_START_SUBTRACK9 = 0x99,
    GRP_CMD_START_SUBTRACK10 = 0x9A,
    GRP_CMD_START_SUBTRACK11 = 0x9B,
    GRP_CMD_START_SUBTRACK12 = 0x9C,
    GRP_CMD_START_SUBTRACK13 = 0x9D,
    GRP_CMD_START_SUBTRACK14 = 0x9E,
    GRP_CMD_START_SUBTRACK15 = 0x9F,

    // Relative address
    GRP_CMD_START_RELATIVE_SUBTRACK_MASK = 0xA0,
    GRP_CMD_START_RELATIVE_SUBTRACK0 = 0xA0,
    GRP_CMD_START_RELATIVE_SUBTRACK1 = 0xA1,
    GRP_CMD_START_RELATIVE_SUBTRACK2 = 0xA2,
    GRP_CMD_START_RELATIVE_SUBTRACK3 = 0xA3,
    GRP_CMD_START_RELATIVE_SUBTRACK4 = 0xA4,
    GRP_CMD_START_RELATIVE_SUBTRACK5 = 0xA5,
    GRP_CMD_START_RELATIVE_SUBTRACK6 = 0xA6,
    GRP_CMD_START_RELATIVE_SUBTRACK7 = 0xA7,
    GRP_CMD_START_RELATIVE_SUBTRACK8 = 0xA8,
    GRP_CMD_START_RELATIVE_SUBTRACK9 = 0xA9,
    GRP_CMD_START_RELATIVE_SUBTRACK10 = 0xAA,
    GRP_CMD_START_RELATIVE_SUBTRACK11 = 0xAB,
    GRP_CMD_START_RELATIVE_SUBTRACK12 = 0xAC,
    GRP_CMD_START_RELATIVE_SUBTRACK13 = 0xAD,
    GRP_CMD_START_RELATIVE_SUBTRACK14 = 0xAE,
    GRP_CMD_START_RELATIVE_SUBTRACK15 = 0xAF,

    // Result is placed in port[X]
    GRP_CMD_SEQ_LOAD_MASK = 0xB0,
    GRP_CMD_SEQ_LOAD_PORT0 = 0xB0,
    GRP_CMD_SEQ_LOAD_PORT1 = 0xB1,
    GRP_CMD_SEQ_LOAD_PORT2 = 0xB2,
    GRP_CMD_SEQ_LOAD_PORT3 = 0xB3,
    GRP_CMD_SEQ_LOAD_PORT4 = 0xB4,
    GRP_CMD_SEQ_LOAD_PORT5 = 0xB5,
    GRP_CMD_SEQ_LOAD_PORT6 = 0xB6,
    GRP_CMD_SEQ_LOAD_PORT7 = 0xB7,

    GRP_CMD_CALLBACK = 0xBE,

    GRP_CMD_C1 = 0xC1, // unused
    GRP_CMD_DYNAMIC_BRANCH = 0xC2,
    GRP_CMD_MUTE_SUBTRACKS = 0xC3,
    GRP_CMD_START_SEQ = 0xC4,
    GRP_CMD_UPDATE_COUNTER = 0xC5,
    GRP_CMD_STOP_SEQ = 0xC6,
    GRP_CMD_MACRO_VALUE_STORE = 0xC7,
    GRP_CMD_MACRO_VALUE_SUBTRACT = 0xC8,
    GRP_CMD_MACRO_VALUE_BIT_AND = 0xC9,
    GRP_CMD_CA = 0xCA, // unused
    GRP_CMD_CB = 0xCB, // unused
    GRP_CMD_MACRO_VALUE_LOAD = 0xCC,
    GRP_CMD_DYN_TBL_CALL = 0xCD,
    GRP_CMD_MACRO_VALUE_RANDOM = 0xCE,
    GRP_CMD_CF = 0xCF, // unused

    GRP_CMD_SET_NOTE_ALLOC_POLICY = 0xD0,
    GRP_CMD_SET_SHORT_NOTE_GATE_TIME_TBL = 0xD1,
    GRP_CMD_SET_SHORT_NOTE_VELOCITY_TBL = 0xD2,
    GRP_CMD_SET_MUTE_BEHAVIOR = 0xD3,
    GRP_CMD_MUTE = 0xD4,
    GRP_CMD_SET_MUTE_SCALE = 0xD5,
    GRP_CMD_DISABLE_SUBTRACKS = 0xD6, // non-functional
    GRP_CMD_ALLOC_SUBTRACKS = 0xD7,
    GRP_CMD_D8 = 0xD8, // unused?
    GRP_CMD_SET_VOLUME_SCALE = 0xD9,
    GRP_CMD_CHANGE_VOLUME = 0xDA,
    GRP_CMD_SET_VOLUME = 0xDB,
    GRP_CMD_SET_TEMPO_CHANGE = 0xDC,
    GRP_CMD_SET_TEMPO = 0xDD,
    GRP_CMD_TRANSPOSITION_RELATIVE = 0xDE,
    GRP_CMD_TRANSPOSITION_ABSOLUTE = 0xDF,

    GRP_CMD_EF = 0xEF, // non-functional

    GRP_CMD_RELEASE_VOICES = 0xF0,
    GRP_CMD_RESERVE_VOICES = 0xF1,
} GroupCmd;

typedef enum SubtrackCmd {
    SUBTRACK_CMD_DELAY_MASK = 0x00,
    SUBTRACK_CMD_DELAY_CLEAR = 0x00, // remove delay
    SUBTRACK_CMD_DELAY_1 = 0x01, // delay 1 frame
    SUBTRACK_CMD_DELAY_2 = 0x02, // delay 2 frames
    SUBTRACK_CMD_DELAY_3 = 0x03, // delay 3 frames
    SUBTRACK_CMD_DELAY_4 = 0x04, // delay 4 frames
    SUBTRACK_CMD_DELAY_5 = 0x05, // delay 5 frames
    SUBTRACK_CMD_DELAY_6 = 0x06, // delay 6 frames
    SUBTRACK_CMD_DELAY_7 = 0x07, // delay 7 frames
    SUBTRACK_CMD_DELAY_8 = 0x08, // delay 8 frames
    SUBTRACK_CMD_DELAY_9 = 0x09, // delay 9 frames
    SUBTRACK_CMD_DELAY_10 = 0x0A, // delay 10 frames
    SUBTRACK_CMD_DELAY_11 = 0x0B, // delay 11 frames
    SUBTRACK_CMD_DELAY_12 = 0x0C, // delay 12 frames
    SUBTRACK_CMD_DELAY_13 = 0x0D, // delay 13 frames
    SUBTRACK_CMD_DELAY_14 = 0x0E, // delay 14 frames
    SUBTRACK_CMD_DELAY_15 = 0x0F, // delay 15 frames

    SUBTRACK_CMD_VOICELOAD_MASK = 0x10,
    SUBTRACK_CMD_VOICELOAD_PORT0 = 0x10, // loads instrument samples using the subtrack's instrument bank id and the instrument id from macro->value, result in subrack->port[cmd & 7]
    SUBTRACK_CMD_VOICELOAD_PORT1 = 0x11,
    SUBTRACK_CMD_VOICELOAD_PORT2 = 0x12,
    SUBTRACK_CMD_VOICELOAD_PORT3 = 0x13,
    SUBTRACK_CMD_VOICELOAD_PORT4 = 0x14,
    SUBTRACK_CMD_VOICELOAD_PORT5 = 0x15,
    SUBTRACK_CMD_VOICELOAD_PORT6 = 0x16,
    SUBTRACK_CMD_VOICELOAD_PORT7 = 0x17,
    SUBTRACK_CMD_SYNTHLOAD_PORT0 = 0x18, // loads synth instrument samples? from subtrack bank id and 0x100 + subtrack->dynamic_value, result is placed in subtrack->port[cmd & 7]
    SUBTRACK_CMD_SYNTHLOAD_PORT1 = 0x19,
    SUBTRACK_CMD_SYNTHLOAD_PORT2 = 0x1A,
    SUBTRACK_CMD_SYNTHLOAD_PORT3 = 0x1B,
    SUBTRACK_CMD_SYNTHLOAD_PORT4 = 0x1C,
    SUBTRACK_CMD_SYNTHLOAD_PORT5 = 0x1D,
    SUBTRACK_CMD_SYNTHLOAD_PORT6 = 0x1E,
    SUBTRACK_CMD_SYNTHLOAD_PORT7 = 0x1F,

    // These commands start a new subtrack with its PC set to group->seq_data[param]
    SUBTRACK_CMD_START_SUBTRACK_MASK = 0x20,
    SUBTRACK_CMD_START_SUBTRACK0 = 0x20,
    SUBTRACK_CMD_START_SUBTRACK1 = 0x21,
    SUBTRACK_CMD_START_SUBTRACK2 = 0x22,
    SUBTRACK_CMD_START_SUBTRACK3 = 0x23,
    SUBTRACK_CMD_START_SUBTRACK4 = 0x24,
    SUBTRACK_CMD_START_SUBTRACK5 = 0x25,
    SUBTRACK_CMD_START_SUBTRACK6 = 0x26,
    SUBTRACK_CMD_START_SUBTRACK7 = 0x27,
    SUBTRACK_CMD_START_SUBTRACK8 = 0x28,
    SUBTRACK_CMD_START_SUBTRACK9 = 0x29,
    SUBTRACK_CMD_START_SUBTRACK10 = 0x2A,
    SUBTRACK_CMD_START_SUBTRACK11 = 0x2B,
    SUBTRACK_CMD_START_SUBTRACK12 = 0x2C,
    SUBTRACK_CMD_START_SUBTRACK13 = 0x2D,
    SUBTRACK_CMD_START_SUBTRACK14 = 0x2E,
    SUBTRACK_CMD_START_SUBTRACK15 = 0x2F,

    // These commands write to another subtrack's input/output ports at subtrack[cmd & 0xF]->ports[param]
    SUBTRACK_CMD_WRITE_SUBTRACK_PORT_MASK = 0x30,
    SUBTRACK_CMD_WRITE_SUBTRACK0_PORT = 0x30,
    SUBTRACK_CMD_WRITE_SUBTRACK1_PORT = 0x31,
    SUBTRACK_CMD_WRITE_SUBTRACK2_PORT = 0x32,
    SUBTRACK_CMD_WRITE_SUBTRACK3_PORT = 0x33,
    SUBTRACK_CMD_WRITE_SUBTRACK4_PORT = 0x34,
    SUBTRACK_CMD_WRITE_SUBTRACK5_PORT = 0x35,
    SUBTRACK_CMD_WRITE_SUBTRACK6_PORT = 0x36,
    SUBTRACK_CMD_WRITE_SUBTRACK7_PORT = 0x37,
    SUBTRACK_CMD_WRITE_SUBTRACK8_PORT = 0x38,
    SUBTRACK_CMD_WRITE_SUBTRACK9_PORT = 0x39,
    SUBTRACK_CMD_WRITE_SUBTRACK10_PORT = 0x3A,
    SUBTRACK_CMD_WRITE_SUBTRACK11_PORT = 0x3B,
    SUBTRACK_CMD_WRITE_SUBTRACK12_PORT = 0x3C,
    SUBTRACK_CMD_WRITE_SUBTRACK13_PORT = 0x3D,
    SUBTRACK_CMD_WRITE_SUBTRACK14_PORT = 0x3E,
    SUBTRACK_CMD_WRITE_SUBTRACK15_PORT = 0x3F,

    // These commands read another subtrack's input/output port value into this subtrack's macro->value register, same logic as writing
    SUBTRACK_CMD_READ_SUBTRACK_PORT_MASK = 0x40,
    SUBTRACK_CMD_READ_SUBTRACK0_PORT = 0x40,
    SUBTRACK_CMD_READ_SUBTRACK1_PORT = 0x41,
    SUBTRACK_CMD_READ_SUBTRACK2_PORT = 0x42,
    SUBTRACK_CMD_READ_SUBTRACK3_PORT = 0x43,
    SUBTRACK_CMD_READ_SUBTRACK4_PORT = 0x44,
    SUBTRACK_CMD_READ_SUBTRACK5_PORT = 0x45,
    SUBTRACK_CMD_READ_SUBTRACK6_PORT = 0x46,
    SUBTRACK_CMD_READ_SUBTRACK7_PORT = 0x47,
    SUBTRACK_CMD_READ_SUBTRACK8_PORT = 0x48,
    SUBTRACK_CMD_READ_SUBTRACK9_PORT = 0x49,
    SUBTRACK_CMD_READ_SUBTRACK10_PORT = 0x4A,
    SUBTRACK_CMD_READ_SUBTRACK11_PORT = 0x4B,
    SUBTRACK_CMD_READ_SUBTRACK12_PORT = 0x4C,
    SUBTRACK_CMD_READ_SUBTRACK13_PORT = 0x4D,
    SUBTRACK_CMD_READ_SUBTRACK14_PORT = 0x4E,
    SUBTRACK_CMD_READ_SUBTRACK15_PORT = 0x4F,

    // These commands subtract the value in port[X] from the subtrack's macro value register
    SUBTRACK_CMD_MACRO_SUBTRACT_MASK = 0x50,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT0 = 0x50,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT1 = 0x51,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT2 = 0x52,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT3 = 0x53,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT4 = 0x54,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT5 = 0x55,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT6 = 0x56,
    SUBTRACK_CMD_MACRO_SUBTRACT_PORT7 = 0x57,

    // These commands read the value in port[X] into the subtrack's macro value register
    // When the port is 0 or 1, the port value is set to -1
    SUBTRACK_CMD_MACRO_READ_PORT0_MASK = 0x60,
    SUBTRACK_CMD_MACRO_READ_PORT0 = 0x60,
    SUBTRACK_CMD_MACRO_READ_PORT1 = 0x61,
    SUBTRACK_CMD_MACRO_READ_PORT2 = 0x62,
    SUBTRACK_CMD_MACRO_READ_PORT3 = 0x63,
    SUBTRACK_CMD_MACRO_READ_PORT4 = 0x64,
    SUBTRACK_CMD_MACRO_READ_PORT5 = 0x65,
    SUBTRACK_CMD_MACRO_READ_PORT6 = 0x66,
    SUBTRACK_CMD_MACRO_READ_PORT7 = 0x67,

    SUBTRACK_CMD_PORT_WRITE_MACRO_REG_MASK = 0x70,
    SUBTRACK_CMD_PORT0_WRITE_MACRO_REG = 0x70,
    SUBTRACK_CMD_PORT1_WRITE_MACRO_REG = 0x71,
    SUBTRACK_CMD_PORT2_WRITE_MACRO_REG = 0x72,
    SUBTRACK_CMD_PORT3_WRITE_MACRO_REG = 0x73,
    SUBTRACK_CMD_PORT4_WRITE_MACRO_REG = 0x74,
    SUBTRACK_CMD_PORT5_WRITE_MACRO_REG = 0x75,
    SUBTRACK_CMD_PORT6_WRITE_MACRO_REG = 0x76,
    SUBTRACK_CMD_PORT7_WRITE_MACRO_REG = 0x77,

    // Notes start at current subtrack PC + param
    SUBTRACK_CMD_NOTE_START_MASK = 0x78, // not really the mask but w/e
    SUBTRACk_CMD_NOTE0_START = 0x78,
    SUBTRACk_CMD_NOTE1_START = 0x79,
    SUBTRACk_CMD_NOTE2_START = 0x7A,
    SUBTRACk_CMD_NOTE3_START = 0x7B,

    SUBTRACK_CMD_READ_NOTE_FINISHED_MASK = 0x80,
    SUBTRACK_CMD_READ_NOTE0_FINISHED = 0x80,
    SUBTRACK_CMD_READ_NOTE1_FINISHED = 0x81,
    SUBTRACK_CMD_READ_NOTE2_FINISHED = 0x82,
    SUBTRACK_CMD_READ_NOTE3_FINISHED = 0x83,

    SUBTRACK_CMD_NOTE_SET_PC_MASK = 0x88, // not really the mask but w/e
    SUBTRACK_CMD_NOTE0_SET_PC = 0x88,
    SUBTRACK_CMD_NOTE1_SET_PC = 0x89,
    SUBTRACK_CMD_NOTE2_SET_PC = 0x8A,
    SUBTRACK_CMD_NOTE3_SET_PC = 0x8B,

    SUBTRACK_CMD_NOTE_STOP_MASK = 0x90,
    SUBTRACK_CMD_NOTE0_STOP = 0x90,
    SUBTRACK_CMD_NOTE1_STOP = 0x91,
    SUBTRACK_CMD_NOTE2_STOP = 0x92,
    SUBTRACK_CMD_NOTE3_STOP = 0x93,

    // Notes start at group sequence + dyn_tbl[macro->value]
    SUBTRACK_CMD_NOTE_START_DYNTBL_MASK = 0x98, // not really the mask but w/e
    SUBTRACK_CMD_NOTE0_START_DYNTBL = 0x98,
    SUBTRACK_CMD_NOTE1_START_DYNTBL = 0x99,
    SUBTRACK_CMD_NOTE2_START_DYNTBL = 0x9A,
    SUBTRACK_CMD_NOTE3_START_DYNTBL = 0x9B,

    SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE = 0xA0, // loads a macro register value from the SFX state using the command param as the offset
    SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE_DYNVAL = 0xA1, // loads the macro register value from the SFX state using the dynamic value as the offset
    SUBTRACK_CMD_SFX_STATE_SET = 0xA2, // sets the SFX state using the command param as the offset
    SUBTRACK_CMD_SFX_STATE_SET_DYNVAL = 0xA3, // sets the SFX state using the dynamic value as the offset
    SUBTRACK_CMD_SURROUND_EFFECT_IDX_SET = 0xA4, // sets the surround effect index
    SUBTRACK_CMD_MACRO_ADD_SUBTRACK_IDX = 0xA5, // adds the subtrack index to the macro register value
    SUBTRACK_CMD_WRITE_GOUP_SEQ_OFFSET_BY_SUBTRACK = 0xA6, // writes a value into the parent group sequence with the offset being a param plus the subtrack id
    SUBTRACK_CMD_MACRO_BIT_MOD = 0xA7, // performs a bitwise operation on the macro register value
    SUBTRACK_CMD_DYNVAL_SPECIAL = 0xA8, // performs a special operation on the dynamic value

    SUBTRACK_CMD_SET_FILTER = 0xB0, // sets the subtrack filter
    SUBTRACK_CMD_CLEAR_FILTER = 0xB1, // clears the subtrack filter
    SUBTRACK_CMD_LOAD_DYNVAL_FROM_GROUP_SEQ = 0xB2, // loads the dynamic value from an offset into the parent group sequence
    SUBTRACK_CMD_LOAD_FILTER = 0xB3, // loads filter from subtrack filter pointer with lowpass & hipass cutoff vals
    SUBTRACK_CMD_SET_DYNTBL_FROM_GROUP_SEQ = 0xB4, // sets the dynamic table address relative to the parent group sequence
    SUBTRACK_CMD_LOAD_DYNVAL_FROM_DYNTBL = 0xB5, // loads the dynamic value from the dynamic table
    SUBTRACK_CMD_MACRO_LOAD_FROM_DYNTBL = 0xB6, // loads a macro register value from the dynamic table
    SUBTRACK_CMD_RANDOM_DYNVAL = 0xB7, // generates a random value for the dynamic value, optionally constrained when param is non-zero
    SUBTRACK_CMD_MACRO_RANDOM_VAL = 0xB8, // generates a random value for the macro register value, optionally constrained when param is non-zero
    SUBTRACK_CMD_SET_VEL_RANDOM_VARIANCE = 0xB9, // sets the velocity random variance
    SUBTRACK_CMD_SET_GATE_TIME_RANDOM_VARIANCE = 0xBA, // sets the gate time random variance
    SUBTRACK_CMD_SET_COMB_FILTER_SIZE_GAIN = 0xBB, // sets the comb filter size and gain
    SUBTRACK_CMD_ADD_DYNVAL = 0xBC, // adds the param to the current dynamic value
    SUBTRACK_CMD_SET_SAMPLE_START_POS = 0xBD, // sets the sample start position
    SUBTRACK_CMD_MACRO_SET_FROM_CALLBACK = 0xBE, // sets the macro register value from a callback

    SUBTRACK_CMD_VOICE_SET = 0xC1,
    SUBTRACK_CMD_SET_DYNTBL = 0xC2,
    SUBTRACK_CMD_LARGE_NOTE_ON = 0xC3,
    SUBTRACK_CMD_LARGE_NOTE_OFF = 0xC4,
    SUBTRACK_CMD_JMP_DYNTBL = 0xC5,
    SUBTRACK_CMD_SET_INSTRUMENT_BANK = 0xC6,
    SUBTRACK_CMD_WRITE_GROUP_SEQ = 0xC7,
    SUBTRACK_CMD_MACRO_SUBTRACT = 0xC8,
    SUBTRACK_CMD_MACRO_AND = 0xC9,
    SUBTRACK_CMD_SET_MUTE_FLAGS = 0xCA,
    SUBTRACK_CMD_MACRO_LOAD_FROM_GROUP_SEQ = 0xCB,
    SUBTRACK_CMD_MACRO_SET = 0xCC,
    SUBTRACK_CMD_DISABLE_SUBTRACK = 0xCD,
    SUBTRACK_CMD_SET_DYNVAL = 0xCE,
    SUBTRACK_CMD_WRITE_DYNVAL_TO_GROUP_SEQ = 0xCF,
    
    SUBTRACK_CMD_STEREO_PHASE_SET = 0xD0,
    SUBTRACK_CMD_SET_NOTE_ALLOC_POLICY = 0xD1,
    SUBTRACK_CMD_SET_SUSTAIN = 0xD2,
    SUBTRACK_CMD_LARGE_BEND_PITCH = 0xD3,
    SUBTRACK_CMD_SET_REVERB_VOL = 0xD4,

    SUBTRACK_CMD_SET_VIBRATO_RATE = 0xD7,
    SUBTRACK_CMD_SET_VIBRATO_DEPTH = 0xD8,
    SUBTRACK_CMD_SET_DECAY_IDX = 0xD9,
    SUBTRACK_CMD_SET_ENVELOPE = 0xDA,
    SUBTRACK_CMD_SET_TRANSPOSITION = 0xDB,
    SUBTRACK_CMD_SET_PAN_WEIGHT = 0xDC,
    SUBTRACK_CMD_SET_PAN = 0xDD,
    SUBTRACK_CMD_SET_FREQ_SCALE = 0xDE,
    SUBTRACK_CMD_SET_VOL = 0xDF,

    SUBTRACK_CMD_SET_VOL_SCALE = 0xE0,
    SUBTRACK_CMD_SET_VIBRATO_RATE_LINEAR = 0xE1,
    SUBTRACK_CMD_SET_VIBRATO_DEPTH_LINEAR = 0xE2,
    SUBTRACK_CMD_SET_VIBRATO_DELAY = 0xE3,
    SUBTRACK_CMD_DYNTBL_CALL = 0xE4,
    SUBTRACK_CMD_SET_REVERB_IDX = 0xE5,
    SUBTRACK_CMD_SET_BOOK_OFS = 0xE6,
    SUBTRACK_CMD_SET_ENV_PARAMS_FROM_GROUP_SEQ = 0xE7, // offset into the parent group sequence is provided for data ofs
    SUBTRACK_CMD_SET_ENV_PARAMS = 0xE8, // data is pulled from subtrack sequence
    SUBTRACK_CMD_SET_PRIORITY = 0xE9,
    SUBTRACK_CMD_STOP = 0xEA,
    SUBTRACK_CMD_INIT_INSTRUMENTS = 0xEB,
    SUBTRACK_CMD_RESET_VIBRATO = 0xEC,
    SUBTRACK_CMD_SET_GAIN = 0xED,
    SUBTRACK_CMD_SMALL_BEND_PITCH = 0xEE,

    SUBTRACK_CMD_DEALLOC_VOICES = 0xF0,
    SUBTRACK_CMD_ALLOC_VOICES = 0xF1
} SubtrackCmd;

typedef enum NoteCmd {

    NOTE_CMD_MUTE = 0xC0, // mute for N frames
    NOTE_CMD_SET_VELOCITY_SQ = 0xC1,
    NOTE_CMD_SET_TRANSPOSITION = 0xC2,
    NOTE_CMD_SET_SHORT_NOTE_DEFAULT_DELAY = 0xC3,
    NOTE_CMD_CONTINUOUS_ON = 0xC4,
    NOTE_CMD_CONTINUOUS_OFF = 0xC5,
    NOTE_CMD_SET_INSTRUMENT = 0xC6,
    NOTE_CMD_ENABLE_SWEEP = 0xC7,
    NOTE_CMD_DISABLE_SWEEP = 0xC8,
    NOTE_CMD_SET_GATE_TIME = 0xC9,
    NOTE_CMD_SET_PAN = 0xCA,
    NOTE_CMD_SET_ADSR_ENVELOPE_DECAY_IDX = 0xCB,
    NOTE_CMD_IGNORE_DRUM_PAN = 0xCC,
    NOTE_CMD_SET_STEREO_PHASE = 0xCD,
    NOTE_CMD_SET_BEND = 0xCE,
    NOTE_CMD_SET_ADSR_DECAY_IDX = 0xCF,
    
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ_MASK = 0xD0,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ0 = 0xD0,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ1 = 0xD1,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ2 = 0xD2,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ3 = 0xD3,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ4 = 0xD4,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ5 = 0xD5,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ6 = 0xD6,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ7 = 0xD7,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ8 = 0xD8,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ9 = 0xD9,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ10 = 0xDA,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ11 = 0xDB,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ12 = 0xDC,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ13 = 0xDD,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ14 = 0xDE,
    NOTE_CMD_SHORT_NOTE_VELOCITY_SQ15 = 0xDF,

    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME_MASK = 0xE0,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME0 = 0xE0,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME1 = 0xE1,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME2 = 0xE2,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME3 = 0xE3,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME4 = 0xE4,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME5 = 0xE5,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME6 = 0xE6,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME7 = 0xE7,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME8 = 0xE8,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME9 = 0xE9,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME10 = 0xEA,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME11 = 0xEB,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME12 = 0xEC,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME13 = 0xED,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME14 = 0xEE,
    NOTE_CMD_SET_SHORT_NOTE_GATE_TIME15 = 0xEF,

    NOTE_CMD_DISABLE_FLAGS = 0xF0,
    NOTE_CMD_SET_SURROUND_EFFECT_IDX = 0xF1,
} NoteCmd;

typedef enum AUDIO_CALLBACKS {
    /* 0x00 */ AUDIO_CALLBACK_SEQ_0,
    /* 0x01 */ AUDIO_CALLBACK_SEQ_1,
    /* 0x02 */ AUDIO_CALLBACK_SEQ_2,
    /* 0x03 */ AUDIO_CALLBACK_SEQ_3,
    /* 0xFE */ AUDIO_CALLBACK_DACOUT = 0xFE,
    /* 0xFF */ AUDIO_CALLBACK_SOUND
} AUDIO_CALLBACKS;

typedef enum NAGroup {
    NA_GROUP0,
    NA_GROUP1,
    NA_GROUP2,
    NA_GROUP3,
    NA_GROUP4,
    NA_GROUP5,
    NA_GROUP6,
    NA_GROUP7,
    NA_GROUP8,
    NA_GROUP9,
    NA_GROUP10,
    NA_GROUP11,
    NA_GROUP12,
    NA_GROUP13,
    NA_GROUP14,
    NA_GROUP15,

    NA_GROUP_NUM
} NAGroup;

typedef enum NASubtrack {
    NA_SUBTRACK0,
    NA_SUBTRACK1,
    NA_SUBTRACK2,
    NA_SUBTRACK3,
    NA_SUBTRACK4,
    NA_SUBTRACK5,
    NA_SUBTRACK6,
    NA_SUBTRACK7,
    NA_SUBTRACK8,
    NA_SUBTRACK9,
    NA_SUBTRACK10,
    NA_SUBTRACK11,
    NA_SUBTRACK12,
    NA_SUBTRACK13,
    NA_SUBTRACK14,
    NA_SUBTRACK15,

    NA_SUBTRACK_NUM
} NASubtrack;

#define NA_COMMAND_AUDIO_START_SEQ(groupID, seqID, fadeinTime) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_START_SEQ, groupID, seqID, 0), fadeinTime)

#define NA_COMMAND_AUDIO_STOP_SEQ(groupID, fadeoutTime) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_STOP_SEQ, groupID, 0, 0), fadeoutTime)

#define NA_COMMAND_AUDIO_GRP_FADE_VOLUME_SCALE(groupID, volumeScale) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_FADE_VOLUME_SCALE, groupID, 0, 0), volumeScale)

#define NA_COMMAND_AUDIO_SET_SOUND_MODE(mode) Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_SET_SOUND_MODE, 0, 0, 0), mode)

#define NA_COMMAND_AUDIO_CLEAR_STAY_CACHE(type) Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_CLEAR_STAY_CACHE, 0, 0, 0), type)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_MUTE(groupMask, subtrack, muted) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_MUTE, groupMask, subtrack, 0), muted)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_VOL_SCALE(group, subtrack, volume) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_VOL_SCALE, group, subtrack, 0), volume)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_FREQ_SCALE(group, subtrack, freqScale) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_FREQ_SCALE, group, subtrack, 0), freqScale)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_PAN(group, subtrack, pan) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_PAN, group, subtrack, 0), pan)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_PORT(group, subtrack, port, value) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_PORT, group, subtrack, port), value)

#define NA_COMMAND_AUDIO_SUBTRACK_REVERB_VOLUME(group, subtrack, reverb) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_REVERB_VOLUME, group, subtrack, 0), reverb)

#define NA_COMMAND_AUDIO_GROUP_SET_PORT(group, port, value) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_SET_PORT, group, 0, port), value)

#define NA_COMMAND_AUDIO_GROUP_SET_APPLY_SUBTRACK_MASK(group, mask) \
    Nap_SetU16(NA_MAKE_COMMAND(AUDIOCMD_SET_GROUP_MASK, group, 0, 0), mask)

#ifdef TARGET_PC
#define NA_COMMAND_AUDIO_SUBTRACK_SET_FILTER(group, subtrack, filterCutoff, pFilter) \
    Nap_SetPtr(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_FILTER, group, subtrack, filterCutoff), (void*)pFilter)
#else
#define NA_COMMAND_AUDIO_SUBTRACK_SET_FILTER(group, subtrack, filterCutoff, pFilter) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_FILTER, group, subtrack, filterCutoff), (s32)pFilter)
#endif

#ifdef __cplusplus
}
#endif

#endif
