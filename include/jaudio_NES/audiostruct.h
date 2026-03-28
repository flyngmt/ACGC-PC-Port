#ifndef AUDIOSTRUCT_H
#define AUDIOSTRUCT_H

#include "types.h"
#include "jaudio_NES/audiocommon.h"
#include "PR/abi.h"
#include "libultra/libultra.h"
#include "jaudio_NES/bx.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct chnode_ chnode;
typedef struct link_ link;

/* sizeof(struct link_) == 0x10 */
struct link_ {
    /* 0x00 */ link* prev;
    /* 0x04 */ link* next;
    union {
        /* 0x08 */ s32 numAfter; /* when link is head */
        /* 0x08 */ void* pData;  /* when link is node */
    };
    /* 0x0C */ chnode* pNode;
};

/* sizeof(struct chnode_) == 0x40 */
struct chnode_ {
    /* 0x00 */ link freeList;
    /* 0x10 */ link releaseList;
    /* 0x20 */ link relwaitList;
    /* 0x30 */ link useList;
};

/* forward declared */
typedef struct note_ note;
typedef struct channel_ channel;
typedef struct group_ group;

/* sizeof(struct AudioPort_) == 0x8 */
typedef struct AudioPort_ {
    union {
        struct {
#ifdef TARGET_PC
            /* On LE, reverse field order so u32 overlay matches
             * NA_MAKE_COMMAND which puts opcode in bits 31-24. */
            /* 0x03 */ u8 arg2;
            /* 0x02 */ u8 arg1;
            /* 0x01 */ u8 arg0;
            /* 0x00 */ u8 opcode;
#else
            /* 0x00 */ u8 opcode;
            /* 0x01 */ u8 arg0;
            /* 0x02 */ u8 arg1;
            /* 0x03 */ u8 arg2;
#endif
        } command;
        /* 0x00 */ u32 raw_cmd;
    };
    union audioparam_ {
        /* 0x04 */ s8 asS8;
        /* 0x04 */ u8 asU8;
        /* 0x04 */ s16 asS16;
        /* 0x04 */ u16 asU16;
        /* 0x04 */ u32 asU32;
        /* 0x04 */ s32 asS32;
        /* 0x04 */ f32 asF32;
        /* 0x04 */ void* asVoidPtr;
    } param;
} AudioPort;

/* sizeof(ALHeap) == 0x14 */
typedef struct ALHeap {
    /* 0x00 */ u8* base;
    /* 0x04 */ u8* current;
    /* 0x08 */ int length;
    /* 0x0C */ s32 count;
    /* 0x10 */ u8* last;
} ALHeap;

/* sizeof(ArcEntry) == 0x10.
 * Fixed-width 32-bit fields to match Big-Endian binary headers in ROM assets.
 * On 64-bit PC, uintptr_t addresses for relocated RAM/ARAM assets are stored
 * in a separate host-side parallel array to avoid corrupting header stride. */
typedef struct ArcEntry_ {
    /* 0x00 */ u32 addr;
    /* 0x04 */ s32 size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cacheType;
    /* 0x0A */ s16 param0;
    /* 0x0C */ s16 param1;
    /* 0x0E */ s16 param2;
} ArcEntry;

/* sizeof(ArcHeader) == [0x10, 0x10+entries*0x10] */
typedef struct ArcHeader_ {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 medium;
    /* 0x04 */ u8* pData;
    /* 0x08 */ u8 copy;
    /* 0x09 */ u8 pad[7];
    /* 0x10 */ ArcEntry entries[]; /* variable size */
} ArcHeader;

/* sizeof(adpcmloop) == 0x10|0x30*/
typedef struct adpcmloop_ {
    /* 0x00 */ u32 loop_start;
    /* 0x04 */ u32 loop_end;
    /* 0x08 */ u32 count;
    /* 0x0C */ u32 sample_end;
    /* 0x10 */ s16 predictor_state[16]; /* exists count > 0*/
} adpcmloop;

/* sizeof(adpcmbook) == [0x8, 0x8+n]*/
typedef struct adpcmbook_ {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 n_predictors;
    /* 0x08 */ s16 codebook[0]; /* variable length, length = order * n_predictors * 8 (VADPCM) */
} adpcmbook;

typedef struct smzwavetable_ {
#ifdef TARGET_PC
    /*
     * LE compiler bitfields allocate from low bits first. The bank word is
     * byte-swapped to host order in pc_swap_smzwavetable(), so declare fields
     * from low->high bit positions to preserve BE semantic names.
     */
    /* 0x00 */ u32 size : 24;
    /* 0x00 */ u32 is_relocated : 1;
    /* 0x00 */ u32 bit26 : 1;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 codec : 3;
    /* 0x00 */ u32 bit31 : 1;
#else
    /* 0x00 */ u32 bit31 : 1;
    /* 0x00 */ u32 codec : 3;
    /* 0x00 */ u32 medium : 2;
    /* 0x00 */ u32 bit26 : 1;
    /* 0x00 */ u32 is_relocated : 1;
    /* 0x00 */ u32 size : 24;
#endif
    /* 0x04 */ u8* sample;
    /* 0x08 */ adpcmloop* loop;
    /* 0x0C */ adpcmbook* book;
} smzwavetable;

/* sizeof(wtstr) == 0x08 */
typedef struct wtstr_ {
    /* 0x00 */ smzwavetable* wavetable;
    /* 0x04 */ f32 tuning;
} wtstr;

/* sizeof(phase) == 0x01 */
typedef struct phase_ {
#ifdef TARGET_PC
    /* x86 GCC: LSB-first bitfields. Reverse order so raw byte from
       GC sequence data (MSB-first layout) maps to correct fields. */
    /* 0x00 */ u8 strong_reverb_left : 1;
    /* 0x00 */ u8 strong_reverb_right : 1;
    /* 0x00 */ u8 strong_left : 1;
    /* 0x00 */ u8 strong_right : 1;
    /* 0x00 */ u8 type : 2;
    /* 0x00 */ u8 _unused : 2;
#else
    /* 0x00 */ u8 _unused : 2;
    /* 0x00 */ u8 type : 2;
    /* 0x00 */ u8 strong_right : 1;
    /* 0x00 */ u8 strong_left : 1;
    /* 0x00 */ u8 strong_reverb_right : 1;
    /* 0x00 */ u8 strong_reverb_left : 1;
#endif
} phase;

/* sizeof(sweep) == 0x0C */
typedef struct sweep_ {
    /* 0x00 */ u8 mode;
    /* 0x02 */ u16 current;
    /* 0x04 */ u16 speed;
    /* 0x08 */ f32 extent;
} sweep;

/* sizeof(vibparam) == 0x0E */
typedef struct vibparam_ {
    /* 0x00 */ u16 rate_start;
    /* 0x02 */ u16 depth_start;
    /* 0x04 */ u16 rate_target;
    /* 0x06 */ u16 depth_target;
    /* 0x08 */ u16 rate_change_delay;
    /* 0x0A */ u16 depth_change_delay;
    /* 0x0C */ u16 delay;
} vibparam;

/* sizeof(tmtable) == 0x1C */
typedef struct tmtable_ {
    /* 0x00 */ vibparam* vibrato_params;
    /* 0x04 */ u32 time;
    /* 0x08 */ s16* curve;
    /* 0x0C */ f32 depth;
    /* 0x10 */ f32 rate;
    /* 0x14 */ u8 active;
    /* 0x16 */ u16 rate_change_timer;
    /* 0x18 */ u16 depth_change_timer;
    /* 0x1A */ u16 delay;
} tmtable;

/* sizeof(envdat) == 0x04 */
typedef struct envdat_ {
    /* 0x00 */ s16 delay;
    /* 0x02 */ s16 value;
} envdat;

/* sizeof(envp) == 0x20 */
typedef struct envp_ {
    union {
        struct {
            /* 0x00 */ u8 unused : 1;
            /* 0x00 */ u8 hang : 1;
            /* 0x00 */ u8 decay : 1;
            /* 0x00 */ u8 release : 1;
            /* 0x00 */ u8 status : 4;
        } flags;
        u8 as_byte;
    } state;

    /* 0x01 */ u8 envelope_idx;
    /* 0x02 */ s16 delay;
    /* 0x04 */ f32 sustain;
    /* 0x08 */ f32 velocity;
    /* 0x0C */ f32 fadeout_velocity;
    /* 0x10 */ f32 current;
    /* 0x14 */ f32 target;
    /* 0x18 */ f32 _18;
    /* 0x1C */ envdat* pEnvData;
} envp;

/* sizeof(env) == 0x08 */
typedef struct env_ {
    /* 0x00 */ u8 decay_idx;
    /* 0x01 */ u8 sustain;
    /* 0x04 */ envdat* envelope;
} env;

/* sizeof(commonch) == 0x20 */
typedef struct commonch_ {
    /* 0x00 */ vu8 enabled : 1;
    /* 0x00 */ u8 needs_init : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 unused : 1;
    /* 0x00 */ u8 strong_right : 1;
    /* 0x00 */ u8 strong_left : 1;
    /* 0x00 */ u8 strong_reverb_right : 1;
    /* 0x00 */ u8 strong_reverb_left : 1;

    /* 0x01 */ u8 reverb_idx : 3;
    /* 0x01 */ u8 __book_ofs : 2;
    /* 0x01 */ u8 is_synth_wave : 1;
    /* 0x01 */ u8 has_two_parts : 1;
    /* 0x01 */ u8 use_haas_effect : 1;

    /* 0x02 */ u8 gain;
    /* 0x03 */ u8 haas_effect_left_delay_size;
    /* 0x04 */ u8 haas_effect_right_delay_size;
    /* 0x05 */ u8 target_reverb_volume;
    /* 0x06 */ u8 harmonic_idx_cur_and_prev;
    /* 0x07 */ u8 comb_filter_size;
    /* 0x08 */ u16 target_volume_left;
    /* 0x0A */ u16 target_volume_right;
    /* 0x0C */ u16 frequency_fixed_point;
    /* 0x0E */ u16 comb_filter_gain;
    union {
        /* 0x10 */ wtstr* tuned_sample;
        /* 0x10 */ s16* wave_sample_addr; // for synth waves
    };
    /* 0x14 */ s16* filter;
    /* 0x18 */ u8 _18;
    /* 0x19 */ u8 surround_effect_idx;
    /* 0x1A */ u8 book_ofs;
    /* 0x1B */ u8 _1B[4];
} commonch;

/* TODO: see if this has a name anywhere */
/* sizeof(synthparams) == 0x2E0 */
typedef struct synthparams_ {
    /* 0x000 */ s16 adpcm_state[16];
    /* 0x020 */ s16 final_resample_state[16];
    /* 0x040 */ s16 filter_state[32];
    /* 0x080 */ s16 unused_state[16];
    /* 0x0A0 */ s16 haas_effect_delay_state[32];
    /* 0x0E0 */ s16 comb_filter_state[128];
    /* 0x1E0 */ s16 surround_effect_state[128];
} synthparams;

/* sizeof(driverch) == 0x20 */
typedef struct driverch_ {
    /* 0x00 */ u8 at_loop_point : 1;
    /* 0x00 */ u8 stop_loop : 1;
    /* 0x01 */ u8 sample_dma_idx;
    /* 0x02 */ u8 prev_haas_effect_left_delay_size;
    /* 0x03 */ u8 prev_haas_effect_right_delay_size;
    /* 0x04 */ u8 cur_reverb_vol;
    /* 0x05 */ u8 num_parts;
    /* 0x06 */ u8 comb_filter_needs_init;
    /* 0x07 */ u8 vel_conv_table_idx;
    /* 0x08 */ u16 sample_pos_fractional_part;
    /* 0x0A */ u16 surround_effect_gain;
    /* 0x0C */ s32 sample_pos_integer_part;
    /* 0x10 */ synthparams* synth_params;
    /* 0x14 */ s16 current_volume_left;
    /* 0x16 */ s16 current_volume_right;
    /* 0x18 */ u8 _18[8]; // unused?
} driverch;

/* TODO: madeup name, see if there's an exposde one */
/* sizeof(playbackparams) == 0x18 */
typedef struct playbackparams_ {
    /* 0x00 */ u8 target_reverb_volume;
    /* 0x01 */ u8 gain;
    /* 0x02 */ u8 pan;
    /* 0x03 */ u8 surround_effect_idx;
    /* 0x04 */ phase stereo_phase;
    /* 0x05 */ u8 comb_filter_size;
    /* 0x06 */ u16 comb_filter_gain;
    /* 0x08 */ f32 pitch;
    /* 0x0C */ f32 velocity;
    /* 0x10 */ s16* filter;
    /* 0x14 */ s16* filter_buf;
} playbackparams;

/* TODO: madeup name, see if there's an exposed one */
/* sizeof(playbackch) == 0xA0 */
typedef struct playbackch_ {
    /* 0x00 */ u8 priority;
    /* 0x01 */ u8 wave_id;
    /* 0x02 */ u8 harmonic_index;
    /* 0x03 */ u8 bank_id;
    /* 0x04 */ u8 status;
    /* 0x05 */ u8 stereo_headset_effects;
    /* 0x06 */ s16 adsr_volume_scale_unused;
    /* 0x08 */ f32 portamento_frequency_scale;
    /* 0x0C */ f32 vibrato_frequency_scale;
    /* 0x10 */ note* previous_parent_note;
    /* 0x14 */ note* current_parent_note;
    /* 0x18 */ note* wanted_parent_note;
    /* 0x1C */ playbackparams params;
    /* 0x34 */ envp adsr_envp;
    /* 0x54 */ sweep portamento_sweep;
    /* 0x60 */ tmtable vibrato_tmtable;
    /* 0x7C */ s32 _7C;
    /* 0x80 */ u8 vel_conv_table_idx;
    /* 0x84 */ u32 start_sample_pos;
    /* 0x88 */ u8 _88[0x18];
} playbackch;

/* sizeof(channel) == 0x100 */
struct channel_ {
    /* 0x00 */ link link;
    /* 0x10 */ driverch driver_ch;
    /* 0x30 */ playbackch playback_ch;
    /* 0xD0 */ commonch common_ch;
    /* 0xF0 */ u8 _F0[0x10];
};

/* sizeof(drvparam) == 0x1C */
typedef struct drvparam_ {
    /* 0x00 */ playbackparams playback;
    /* 0x18 */ u8 comb_filter_size;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u16 comb_filter_gain;
} drvparam;

/* sizeof(voicetable) == 0x20 */
typedef struct voicetable_ {
    /* 0x00 */ u8 is_relocated;
    /* 0x01 */ u8 normal_range_low;
    /* 0x02 */ u8 normal_range_high;
    /* 0x03 */ u8 adsr_decay_idx;
    /* 0x04 */ envdat* envelope;
    /* 0x08 */ wtstr low_pitch_tuned_sample;
    /* 0x10 */ wtstr normal_pitch_tuned_sample;
    /* 0x18 */ wtstr high_pitch_tuned_sample;
} voicetable;

/* sizeof(perctable) == 0x10 */
typedef struct perctable_ {
    /* 0x00 */ u8 adsr_decay_idx;
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 is_relocated;
    /* 0x04 */ wtstr tuned_sample;
    /* 0x0C */ envdat* envelope;
} perctable;

/* sizeof(percvoicetable) == 0x08 */
typedef struct percvoicetable_ {
    /* 0x00 */ wtstr tuned_sample;
} percvoicetable;

/* sizeof(voiceinfo) == 0x14 */
typedef struct voiceinfo_ {
    /* 0x00 */ u8 num_instruments;
    /* 0x01 */ u8 num_drums;
    /* 0x02 */ u8 wave_bank_id0;
    /* 0x03 */ u8 wave_bank_id1;
    /* 0x04 */ u16 num_sfx;
    /* 0x08 */ voicetable** instruments;
    /* 0x0C */ perctable** percussion;
    /* 0x10 */ percvoicetable* effects;
} voiceinfo;

/* sizeof(delayparam) == 0x1C */
typedef struct delayparam_ {
    /* 0x00 */ s16 n_samples_after_downsampling;
    /* 0x02 */ s16 n_samples;
    /* 0x04 */ s16* to_down_sample_left;
    /* 0x08 */ s16* to_down_sample_right;
    /* 0x0C */ s32 start_pos;
    /* 0x10 */ s16 size;
    /* 0x12 */ s16 wrapped_size;
    /* 0x14 */ u16 load_resample_pitch;
    /* 0x16 */ u16 save_resample_pitch;
    /* 0x18 */ u16 save_resample_num_samples;
} delayparam;

/* sizeof(delay) == 0x2D0 */
typedef struct delay_ {
    /* 0x000 */ u8 resample_flags;
    /* 0x001 */ u8 use_reverb;
    /* 0x002 */ u8 frames_to_ignore;
    /* 0x003 */ u8 cur_frame;
    /* 0x004 */ u8 downsample_rate;
    /* 0x005 */ s8 mix_reverb_idx;
    /* 0x006 */ u16 delay_num_samples;
    /* 0x008 */ s16 mix_reverb_strength;
    /* 0x00A */ s16 volume;
    /* 0x00C */ u16 decay_ratio;
    /* 0x00E */ u16 downsample_pitch;
    /* 0x010 */ s16 leak_rtl;
    /* 0x012 */ s16 leak_ltl;
    /* 0x014 */ u16 sub_delay;
    /* 0x016 */ s16 sub_volume;
    /* 0x018 */ u8 resample_effect_on;
    /* 0x019 */ s8 resample_effect_extra_samples;
    /* 0x01A */ u16 resample_effect_load_unk;
    /* 0x01C */ u16 resample_effect_save_unk;
    /* 0x01E */ u8 delay_num_samples_after_downsampling;
    /* 0x020 */ s32 next_reverb_buf_pos;
    /* 0x024 */ s32 delay_num_samples_unk;
    /* 0x028 */ s16* left_reverb_buf;
    /* 0x02C */ s16* right_reverb_buf;
    /* 0x030 */ s16* left_load_resample_buf;
    /* 0x034 */ s16* right_load_resample_buf;
    /* 0x038 */ s16* left_save_resample_buf;
    /* 0x03C */ s16* right_save_resample_buf;
    /* 0x040 */ delayparam params[2][AUDIO_GROUP_MAX];
    /* 0x158 */ delayparam sub_params[2][AUDIO_GROUP_MAX];
    /* 0x270 */ s16* filter_left;
    /* 0x274 */ s16* filter_right;
    /* 0x278 */ s16* filter_left_init;
    /* 0x27C */ s16* filter_right_init;
    /* 0x280 */ s16* filter_left_state;
    /* 0x284 */ s16* filter_right_state;
    /* 0x288 */ wtstr tuned_sample;
    /* 0x290 */ smzwavetable sample;
    /* 0x2A0 */ adpcmloop adpcm_loop;
} delay;

/* sizeof(macro) == 0x1C */
typedef struct macro_ {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remaining_loop_iters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} macro;

typedef union subtrack_updates {
    struct {
        /* 0x01 */ u8 frequency_scale : 1;
        /* 0x01 */ u8 volume : 1;
        /* 0x01 */ u8 pan : 1;
    } flags;
    /* 0x01 */ u8 as_byte;
} subtrack_updates;

/* SubTrack struct */
/* sizeof(sub) == 0xE0 */
typedef struct sub_ {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stop_script : 1;
    /* 0x00 */ u8 muted : 1;
    /* 0x00 */ u8 has_instrument : 1;
    /* 0x00 */ u8 stereo_effects : 1;
    /* 0x00 */ u8 large_notes : 1;
    /* 0x00 */ u8 unused : 1;
    /* 0x01 */ subtrack_updates changes;
    /* 0x02 */ u8 note_alloc_policy;
    /* 0x03 */ u8 mute_flags;
    /* 0x04 */ u8 target_reverb_vol;
    /* 0x05 */ u8 note_priority;
    /* 0x06 */ u8 priority2;
    /* 0x07 */ u8 bank_id;
    /* 0x08 */ u8 reverb_idx;
    /* 0x09 */ u8 book_ofs;
    /* 0x0A */ u8 new_pan;
    /* 0x0B */ u8 pan_channel_weight;
    /* 0x0C */ u8 gain;
    /* 0x0D */ u8 velocity_random_variance;
    /* 0x0E */ u8 gate_time_random_variance;
    /* 0x0F */ u8 comb_filter_size;
    /* 0x10 */ u8 surround_effect_idx;
    /* 0x11 */ u8 subtrack_idx;
    /* 0x12 */ u8 note_semitone;
    /* 0x14 */ vibparam vibrato_params;
    /* 0x22 */ u16 delay;
    /* 0x24 */ u16 comb_filter_gain;
    /* 0x26 */ u16 dynamic_value;
    /* 0x28 */ s16 inst_or_wave;
    /* 0x2A */ s16 transposition;
    /* 0x2C */ f32 volume_scale;
    /* 0x30 */ f32 volume;
    /* 0x34 */ s32 pan;
    /* 0x38 */ f32 applied_volume;
    /* 0x3C */ f32 frequency_scale;
    /* 0x40 */ u8 (*dyn_tbl)[][2];
    /* 0x44 */ channel* channel;
    /* 0x48 */ note* note;
    /* 0x4C */ voicetable* voicetable;
    /* 0x50 */ group* group;
    /* 0x54 */ struct note_* note_layers[4];
    /* 0x64 */ macro macro_player;
    /* 0x80 */ env adsr_env;
    /* 0x88 */ chnode channel_node;
    /* 0xC8 */ s8 port[8];
    /* 0xD0 */ u8* sfx_state;
    /* 0xD4 */ s16* filter;
    /* 0xD8 */ phase stereo_phase;
    /* 0xDC */ s32 sample_start_pos;
    /* 0xE0 */ s32 _E0;
    /* 0xE4 */ u8 _unk[0x100 - 0x0E4];
} sub;

/* sizeof(group) == 0x160 */
struct group_ {
    struct flags_ {
        /* 0x000 */ u8 enabled : 1;
        /* 0x000 */ u8 finished : 1;
        /* 0x000 */ u8 muted : 1;
        /* 0x000 */ u8 sequence_dma_in_progress : 1;
        /* 0x000 */ u8 bank_dma_in_progress : 1;
        /* 0x000 */ u8 recalculate_volume : 1;
        /* 0x000 */ u8 stop_seq_script : 1;
        /* 0x000 */ u8 apply_bend : 1;
    } flags;

    /* 0x001 */ u8 state;
    /* 0x002 */ u8 note_alloc_policy;
    /* 0x003 */ u8 mute_flags;
    /* 0x004 */ u8 seq_id;
    /* 0x005 */ u8 bank_id;
    /* 0x006 */ u8 unk006;
    /* 0x007 */ s8 group_idx;
    /* 0x008 */ u16 tempo;
    /* 0x00A */ u16 tempo_acceleration;
    /* 0x00C */ s16 tempo_change;
    /* 0x00E */ s16 transposition;
    /* 0x010 */ u16 delay;
    /* 0x012 */ u16 fade_timer;
    /* 0x014 */ u16 stored_fade_timer;
    /* 0x016 */ u16 counter;
    /* 0x018 */ u8* seq_data;
    /* 0x01C */ f32 fade_volume;
    /* 0x020 */ f32 fade_velocity;
    /* 0x024 */ f32 volume;
    /* 0x028 */ f32 mute_volume_scale;
    /* 0x02C */ f32 fade_volume_scale;
    /* 0x030 */ f32 applied_fade_volume;
    /* 0x034 */ f32 bend;
    /* 0x038 */ sub* subtracks[AUDIO_SUBTRACK_NUM];
    /* 0x078 */ macro macro_player;
    /* 0x094 */ u8* short_note_velocity_tbl;
    /* 0x098 */ u8* short_note_gate_time_tbl;
    /* 0x09C */ chnode channel_node;
    /* 0x0DC */ s32 skip_ticks;
    /* 0x0E0 */ s32 script_counter; /* is u32 in MM decomp */
    /* 0x0E4 */ u8 unkE4[0x158 - 0x0E4];
    /* 0x158 */ s8 port[8];
};

/* sizeof(note) == 0x90 */
struct note_ {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 muted : 1;
    /* 0x00 */ u8 continuous : 1;
    /* 0x00 */ u8 channel_attached : 1;
    /* 0x00 */ u8 ignore_drum_pan : 1;
    /* 0x00 */ u8 continuous_channel_released : 1;
    /* 0x00 */ u8 note_properties_need_init : 1;
    /* 0x01 */ phase stereo_phase;
    /* 0x02 */ u8 inst_or_wave;
    /* 0x03 */ u8 gate_time;
    /* 0x04 */ u8 semitone;
    /* 0x05 */ u8 portamento_target_note;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 note_pan;
    /* 0x08 */ u8 surround_effect_idx;
    /* 0x09 */ u8 target_reverb_volume;

    union {
        struct {
            /* 0x0A */ u16 skip_volume_update : 1;
            /* 0x0A */ u16 skip_freq_scale_update : 1;
            /* 0x0A */ u16 bit2 : 1;
            /* 0x0A */ u16 use_vibrato : 1;
            /* 0x0A */ u16 add_subtrack_transposition : 1;
            /* 0x0A */ u16 bit5 : 1;
            /* 0x0A */ u16 bit6 : 1;
            /* 0x0A */ u16 bit7 : 1;
            /* 0x0B */ u16 skip_pan_update : 1;
            /* 0x0B */ u16 bit9 : 1;
            /* 0x0B */ u16 bitA : 1;
            /* 0x0B */ u16 bitB : 1;
            /* 0x0B */ u16 bitC : 1;
            /* 0x0B */ u16 bitD : 1;
            /* 0x0B */ u16 bitE : 1;
            /* 0x0B */ u16 bitF : 1;
        } flags;
        /* 0x0A */ u16 asU16;
    } _0A;

    /* 0x0C */ vibparam vibrato_params;
    /* 0x1A */ s16 delay;
    /* 0x1C */ s16 gate_delay;
    /* 0x1E */ s16 delay2;
    /* 0x20 */ u16 portamento_time;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ s16 short_note_default_delay;
    /* 0x26 */ s16 last_delay;
    /* 0x28 */ env adsr_env;
    /* 0x30 */ sweep portamento_sweep;
    /* 0x3C */ channel* channel;
    /* 0x40 */ f32 frequency_scale;
    /* 0x44 */ f32 bend;
    /* 0x48 */ f32 velocity_square2;
    /* 0x4C */ f32 velocity_square;
    /* 0x50 */ f32 note_velocity;
    /* 0x54 */ f32 note_frequency_scale;
    /* 0x58 */ voicetable* instrument;
    /* 0x5C */ wtstr* tuned_sample;
    /* 0x60 */ sub* sub_track;
    /* 0x64 */ macro macro_player;
    /* 0x80 */ link link;
};

/* sizeof(Bgloadreq) == 0x14 */
typedef struct Bgloadreq_ {
    /* 0x00 */ u32 end_and_medium_key;
    /* 0x04 */ smzwavetable* sample;
    /* 0x08 */ u8* ram_addr;
    /* 0x0C */ u32 encoded_info;
    /* 0x10 */ s32 is_free;
} Bgloadreq;

/* sizeof(Bgload) == 0x58 */
typedef struct Bgload_ {
    /* 0x00 */ s8 status;
    /* 0x01 */ s8 delay;
    /* 0x02 */ s8 medium;
    /* 0x04 */ u8* ram_addr;
    /* 0x08 */ uintptr_t current_device_addr;
    /* 0x0C */ u8* current_ram_addr;
    /* 0x10 */ size_t bytes_remaining;
    /* 0x14 */ size_t chunk_size;
    /* 0x18 */ s32 unk_medium_param;
    /* 0x1C */ u32 ret_msg;
    /* 0x20 */ OSMesgQueue* ret_mq;
    /* 0x24 */ OSMesgQueue mq;
    /* 0x3C */ OSMesg msg[1];
    /* 0x40 */ OSIoMesg io_mesg;
} Bgload;

/* sizeof(lpscache) == 0x64 */
typedef struct lpscache_ {
    /* 0x00 */ u8 medium;
    /* 0x01 */ u8 seq_or_bank_id;
    /* 0x02 */ u16 inst_id;
    /* 0x04 */ s32 unk_medium_param;
    /* 0x08 */ uintptr_t current_device_addr;
    /* 0x0C */ u8* current_ram_addr;
    /* 0x10 */ u8* ram_addr;
    /* 0x14 */ s32 status;
    /* 0x18 */ s32 bytes_remaining;
    /* 0x1C */ s8* is_done;
    /* 0x20 */ smzwavetable sample;
    /* 0x30 */ OSMesgQueue mq;
    /* 0x48 */ OSMesg msg[1];
    /* 0x4C */ OSIoMesg io_mesg;
} lpscache;

/* sizeof(WaveLoad) == 0x10 */
typedef struct WaveLoad_ {
    /* 0x00 */ u8* ram_addr;
    /* 0x04 */ uintptr_t device_addr;
    /* 0x08 */ u16 size_unused;
    /* 0x0A */ u16 size;
    /* 0x0C */ u8 unused;
    /* 0x0D */ u8 reuse_idx;
    /* 0x0E */ u8 time_to_live;
} WaveLoad;

/* sizeof(WaveMedia) == 0x18 */
typedef struct WaveMedia_ {
    /* 0x00 */ u32 wave0_bank_id;
    /* 0x04 */ u32 wave1_bank_id;
    /* 0x08 */ void* wave0_p;
    /* 0x0C */ void* wave1_p;
    /* 0x10 */ u32 wave0_media;
    /* 0x14 */ u32 wave1_media;
} WaveMedia;

/* sizeof(audioparams) == 0x28 */
typedef struct audioparams_ {
    /* 0x00 */ s16 spec;
    /* 0x02 */ u16 sampling_frequency;
    /* 0x04 */ u16 ai_sampling_frequency;
    /* 0x06 */ s16 num_samples_per_frame_target;
    /* 0x08 */ s16 num_samples_per_frame_max;
    /* 0x0A */ s16 num_samples_per_frame_min;
    /* 0x0C */ s16 updates_per_frame;
    /* 0x0E */ s16 num_samples_per_update;
    /* 0x10 */ s16 num_samples_per_update_max;
    /* 0x12 */ s16 num_samples_per_update_min;
    /* 0x14 */ s16 num_groups;
    /* 0x18 */ f32 resample_rate;
    /* 0x1C */ f32 updates_per_frame_inverse;
    /* 0x20 */ f32 updates_per_frame_inverse_scaled;
    /* 0x24 */ f32 updates_per_frame_scaled;
} audioparams;

/* sizeof(StayHeapstrc) == 0x0C */
typedef struct StayHeapstrc_ {
    /* 0x00 */ size_t seq_heap_size;
    /* 0x04 */ size_t bank_heap_size;
    /* 0x08 */ size_t wave_heap_size;
} StayHeapstrc;

/* sizeof(DataHeapstrc) == 0x08 */
typedef struct DataHeapstrc_ {
    /* 0x00 */ size_t data_size;
    /* 0x04 */ size_t auto_size;
} DataHeapstrc;

/* sizeof(AutoHeapstrc) == 0xC */
typedef struct AutoHeapstrc_ {
    /* 0x00 */ size_t seqLen;
    /* 0x04 */ size_t bankLen;
    /* 0x08 */ size_t waveLen;
} AutoHeapstrc;

/* sizeof(AudioHeapstrc) == 0x10 */
typedef struct AudioHeapstrc_ {
    /* 0x00 */ size_t misc_heap_size;
    /* 0x04 */ size_t unused0;
    /* 0x08 */ size_t unused1;
    /* 0x0C */ size_t cache_heap_size;
} AudioHeapstrc;

/* sizeof(SwMember) == 0x14 */
typedef struct SwMember_ {
    /* 0x00 */ u8 in_use;
    /* 0x01 */ s8 original_medium;
    /* 0x02 */ u8 sample_bank_id;
    /* 0x03 */ u8 _pad[5];
    /* 0x08 */ u8* allocated_addr;
    /* 0x0C */ void* sample_addr;
    /* 0x10 */ size_t size;
} SwMember;

/* sizeof(SwHeap) == 0x298 */
typedef struct SwHeap_ {
    /* 0x000 */ ALHeap heap;
    /* 0x004 */ SwMember entries[32];
    /* 0x294 */ s32 num_entries;
} SwHeap;

/* TODO: this needs a better name, I don't see any functions which reference it */
/* sizeof(ALHeapEntry) == 0xC */
#define HEAP_INVALID_INDEX (0xffffffff)
typedef struct ALHeapEntry_ {
    /* 0x00 */ u8* addr;
    /* 0x04 */ size_t size;
    /* 0x08 */ s16 table_type;
    /* 0x0A */ s16 id;
} ALHeapEntry;

/* sizeof(SZStay) == 0xD8 */
typedef struct SZStay_ {
    /* 0x00 */ u32 num_entries;
    /* 0x04 */ ALHeap heap;
    /* 0x18 */ ALHeapEntry entries[16];
} SZStay;

/* sizeof(SZAuto) == 0x30 */
typedef struct SZAuto_ {
    /* 0x00 */ u32 use_entry_idx;
    /* 0x04 */ ALHeap heap;
    /* 0x18 */ ALHeapEntry entries[2];
} SZAuto;

/* sizeof(SZHeap) == 0x11C */
typedef struct SZHeap_ {
    /* 0x000 */ SZStay stay_heap;
    /* 0x0D8 */ SZAuto auto_heap;
    /* 0x108 */ ALHeap unused_heap; /* Might be another struct with a heap, its size matches ALHeap in MM and AC */
} SZHeap;

typedef u32 (*SequenceCallback)(s8, sub*);

/* sizeof(AudioGlobals) == 0x92b0 */
typedef struct AudioGlobals {
    /* 0x0000 */ u8 _0000;
    /* 0x0001 */ s8 num_synth_reverbs;
    /* 0x0002 */ u16 _0002;
    /* 0x0004 */ u16 _0004;
    /* 0x0006 */ u8 _0006[10];
    /* 0x0010 */ s16* adpcm_code_book;
    /* 0x0014 */ commonch* common_channel;
    /* 0x0018 */ delay synth_delay[4];
    /* 0x0B58 */ u8 _0B58[0x30];
    /* 0x0B88 */ smzwavetable* used_samples[128];
    /* 0x0D88 */ Bgloadreq requested_samples[128];
    /* 0x1788 */ s32 num_used_samples;
    /* 0x178C */ s32 num_requested_samples;
    /* 0x1790 */ Bgload bgloads[16];
    /* 0x1D10 */ OSMesgQueue bgload_mq;
    /* 0x1D28 */ u8 _1D28[0x40];
    /* 0x1D68 */ Bgload* current_bgload;
    /* 0x1D6C */ u32 slow_load_pos;
    /* 0x1D70 */ lpscache lps_cache[2];
    /* 0x1E38 */ OSPiHandle* cart_handle;
    /* 0x1E3C */ OSPiHandle* drive_handle;
    /* 0x1E40 */ OSMesgQueue external_load_queue;
    /* 0x1E58 */ OSMesg external_load_mesg_buf[16];
    /* 0x1E98 */ OSMesgQueue preload_sample_queue;
    /* 0x1EB0 */ OSMesg preload_sample_mesg_buf[16];
    /* 0x1EF0 */ OSMesgQueue cur_audio_frame_dma_queue;
    /* 0x1F08 */ OSMesg cur_audio_frame_dma_mesg_buf[64];
    /* 0x2008 */ OSIoMesg cur_adio_frame_dma_io_mesg_buf[64];
    /* 0x2608 */ OSMesgQueue sync_dma_queue;
    /* 0x2620 */ OSMesg sync_dma_queue_msg[1];
    /* 0x2624 */ OSIoMesg sync_dma_io_mesg;
    /* 0x263C */ WaveLoad* waveload_list;
    /* 0x2640 */ u32 num_waveloads;
    /* 0x2644 */ u32 waveload_count;
    /* 0x2648 */ s32 _2648;
    /* 0x264C */ u8 waveload_dma_queue0[256];
    /* 0x274C */ u8 waveload_dma_queue1[256];
    /* 0x284C */ u8 waveload_dma_queue0_rpos; /* read pos */
    /* 0x284D */ u8 waveload_dma_queue1_rpos; /* read pos */
    /* 0x284E */ u8 waveload_dma_queue0_wpos; /* write pos */
    /* 0x284F */ u8 waveload_dma_queue1_wpos; /* write pos */
    /* 0x2850 */ ArcHeader* seq_header;
    /* 0x2854 */ ArcHeader* bank_header;
    /* 0x2858 */ ArcHeader* wave_header;
    /* 0x285C */ ArcHeader* data_header;
#ifdef TARGET_PC
    /* Parallel arrays for 64-bit relocated pointers from archive headers */
    /* 0x2860 */ uintptr_t* seq_relocs;
    /* 0x2868 */ uintptr_t* bank_relocs;
    /* 0x2870 */ uintptr_t* wave_relocs;
    /* 0x2878 */ u16* map_header;
#else
    /* 0x2860 */ u16* map_header;
#endif
    /* 0x2864 */ u16 num_sequences;
    /* 0x2868 */ voiceinfo* voice_info;
    /* 0x286C */ audioparams audio_params;
    /* 0x2894 */ f32 _2894; /* tempo scale? */
    /* 0x2898 */ s32 waveload_dma_buf0_size;
    /* 0x289C */ s32 waveload_dma_buf1_size;
    /* 0x28A0 */ u8 _28A0[16];
    /* 0x28B0 */ s32 waveload_dma_cur_buf_size;
    /* 0x28B4 */ s32 max_audio_cmds;
    /* 0x28B8 */ s32 num_channels;
    /* 0x28BC */ s16 max_tempo;
    /* 0x28BE */ s8 sound_mode;
    /* 0x28C0 */ s32 frame_audio_task_count;
    /* 0x28C4 */ s32 current_frame_dma_count;
    /* 0x28C8 */ s32 rsp_task_idx;
    /* 0x28CC */ s32 current_ai_buffer_idx;
    /* 0x28D0 */ Acmd* abi_cmd_bufs[3];
    /* 0x28DC */ Acmd* unused_current_abi_cmd_buf;
    /* 0x28E0 */ void* unused_current_audio_task;
    /* 0x28E4 */ u8 unused_rsp_tasks[2][0x50]; // Actually a struct but we don't need it
    /* 0x2984 */ u8 _2984[0x54];               // unsure what this is, new to DnM+/AC?
    /* 0x29D8 */ f32 _29D8;
    /* 0x29DC */ s32 refresh_rate;
    /* 0x29E0 */ s16* ai_buffers[4];
    /* 0x29F0 */ s16 num_samples_per_frame[4];
    /* 0x29F8 */ u32 audio_random_seed;
    /* 0x29FC */ s32 audio_error_flags; // unsure about the name, from MM
    /* 0x2A00 */ vu32 reset_timer;
    /* 0x2A04 */ SequenceCallback seq_callbacks[4];
    /* 0x2A14 */ s8 _2A14;
    /* 0x2A18 */ s32 num_abi_cmds_max;
    /* 0x2A1C */ s32 _2A1C;
    /* 0x2A20 */ ALHeap session_heap;
    /* 0x2A34 */ ALHeap external_heap;
    /* 0x2A48 */ ALHeap init_heap;
    /* 0x2A5C */ ALHeap misc_heap;
    /* 0x2A70 */ ALHeap unused_heap0;
    /* 0x2A84 */ ALHeap unused_heap1;
    /* 0x2A98 */ ALHeap sz_data_heap;
    /* 0x2AAC */ ALHeap data_heap;
    /* 0x2AC0 */ ALHeap sz_auto_heap;
    /* 0x2AD4 */ SZHeap seq_heap;
    /* 0x2BF0 */ SZHeap bank_heap;
    /* 0x2D0C */ SZHeap wave_heap;
    /* 0x2E28 */ ALHeap emem_heap;
    /* 0x2E3C */ ALHeapEntry emem_entries[32];
    /* 0x2FBC */ SwHeap emem_persistent_wave_heap;
    /* 0x3254 */ SwHeap emem_temporary_wave_heap;
    /* 0x34EC */ AudioHeapstrc audio_heap_info;
    /* 0x34FC */ DataHeapstrc cache_heap;
    /* 0x3504 */ StayHeapstrc persistent_common_heap_info;
    /* 0x3510 */ StayHeapstrc temporary_common_heap_info;
    /* 0x351C */ u8 wave_load_status[172];
    /* 0x35C8 */ u8 bank_load_status[172];
    /* 0x3674 */ u8 sequence_load_status[252];
    /* 0x3770 */ volatile u8 reset_status;
    /* 0x3771 */ u8 spec_id;
    /* 0x3774 */ s32 audio_reset_fadeout_frames_left;
    /* 0x3778 */ f32* adsr_decay_table;
    /* 0x377C */ u64* audio_heap_p;
    /* 0x3780 */ s32 audio_heap_size;
    /* 0x3784 */ channel* channels;
    /* 0x3788 */ struct group_ groups[AUDIO_GROUP_MAX];
    /* 0x3E68 */ note notes[AUDIO_NOTE_MAX];
    /* 0x8668 */ sub null_sub_track; /* used for 'null' sub tracks */
    /* 0x8748 */ group* groups_p[AUDIO_GROUP_MAX];
    /* 0x877C */ s32 sample_state_offset;
    /* 0x8780 */ link note_link;
    /* 0x8790 */ chnode channel_node; /* main chnode */
    /* 0x87D0 */ struct group_ main_group;
    /* 0x8930 */ sub main_sub;
    /* 0x8A30 */ u8 thread_cmd_write_pos;
    /* 0x8A31 */ u8 thread_cmd_read_pos;
    /* 0x8A32 */ u8 thread_cmd_queue_finished;
    /* 0x8A34 */ u16 thread_cmd_group_mask[AUDIO_GROUP_MAX];
    /* 0x8A40 */ OSMesgQueue* spec_change_mq_p;
    /* 0x8A44 */ OSMesgQueue* task_start_mq_p;
    /* 0x8A48 */ OSMesgQueue* thread_cmd_proc_mq_p;
    /* 0x8A4C */ OSMesgQueue task_start_mq;
    /* 0x8A64 */ OSMesgQueue thread_cmd_proc_mq;
    /* 0x8A7C */ OSMesgQueue spec_change_mq;
    /* 0x8A94 */ OSMesg task_start_msg_buf[1];
    /* 0x8A98 */ OSMesg spec_change_msg_buf[1];
#ifdef TARGET_PC
    /* On PC (synchronous), port commands are only consumed once per frame
     * in CreateAudioTask. During spec changes (reset_status!=0), consumption
     * pauses for ~14 frames while the game keeps sending 55 cmds/frame.
     * Need more queue slots to avoid overflow. */
    /* 0x8A9C */ OSMesg thread_cmd_proc_msg_buf[64];
#else
    /* 0x8A9C */ OSMesg thread_cmd_proc_msg_buf[4];
#endif
    /* 0x8AAC */ AudioPort audio_port_cmds[256];
    /* 0x92AC */ s32 _92AC;
} AudioGlobals;

#define NA_NO_NOTE ((note*)-1)

// typedef union SOUNDID_ {
//     struct {
//         u8 wave_id;
//         u8 inst_id;
//         u8 _02;
//         u8 _03;
//     };

//     u32 uint32;
// } SOUNDID;

// typedef s32 (*PlayerCallBack)(void*);

// typedef struct PLAYER_CALL_ {
//     PlayerCallBack callback;
//     void* arg;
//     u32 DSP_mode;
// } PLAYER_CALL;

// typedef struct Bank_ {
//     u32 magic; // 'BANK'
//     u8* part0[128];
//     u8* part1[100];
//     u8* part2[12];
//     // more?
// } Bank;

// typedef struct InstBank_ {
//     u32 magic; // 'IBNK'
//     u32 _04;
//     u32 vid;
//     u8 pad[32 - 3 * sizeof(u32)];
//     Bank bank;
//     // more
// } InstBank;

typedef union SOUNDID_ SOUNDID;
typedef struct PLAYER_CALL_ PLAYER_CALL;
typedef struct Bank_ Bank;
typedef struct Ibnk_ InstBank;

// C++ JAudio1
typedef enum JCSTATUS {
    JCSTAT_Unk0 = 0,
    JCSTAT_Unk1 = 1,
    JCSTAT_Unk2 = 2,
    JCSTAT_Unk6 = 6,
} JCSTATUS;

typedef struct dspch_ dspch_; // TODO: Figure out why there is another struct named `DSPChannel_` in syncstream.c.
typedef struct Jac_MessageQueue Jac_MessageQueue;
typedef struct JCMgr JCMgr;
typedef struct jc_ jc_;
typedef struct jcs_ jcs_;
typedef struct Wave_ Wave_;

typedef BOOL (*DSPChannelCallback)(dspch_*, u32);

/**
 * @brief TODO.
 */
struct dspch_ {
    u8 buffer_idx; // _00
    u8 _01;        // _01
    u8 _02;        // _02
    u8 _03;        // _03
    u16 _04;       // _04
    u16 _06;       // _06
    // u32 _08;               // _08
    jc_* _08;               // _08
    DSPChannelCallback _0C; // _0C

    // DSPchannel_* _0C; // TODO: SMS says this exists, Pikmin 1 disagrees.
};

typedef struct PanMatrix_ {
    f32 values[3];
} PanMatrix_;

/**
 * @brief TODO
 *
 * @note Size: 0x74.
 */
struct jcs_ {
    u32 chanCount;          // _00, Number of channels in this system
    u32 chanAllocCount;     // _04, Total channel allocation counter
    jc_* freeChannels;      // _08, Linked list of free channels
    jc_* activeChannels;    // _0C, Linked list of active channels
    jc_* releasingChannels; // _10, Linked list of releasing channels
    jc_* waitingChannels;   // _14, Linked list of channels waiting for DSP
    f32 volume;             // _18, Master volume (default 1.0)
    f32 pitch;              // _1C, Master pitch/cent adjustment (default 1.0)
    f32 pan;                // _20, Master pan position (default 0.5)
    f32 fxmix;              // _24, Effects mix level (default 0.0)
    f32 dolby;              // _28, Dolby surround level (default 0.0)

    s16 firCoefficients[8]; // _2C, FIR filter coefficients (8 taps)
    s16 iirCoefficients[4]; // _3C, IIR filter coefficients

    char _44[8];           // _44
    s16 distFilter;        // _4C, Distance filter parameter (default 0)
    u16 busConnect[6];     // _4E, Bus routing configuration for 6 outputs
    u8 masterLevels[6];    // _5A
    u8 maxDelay;           // _60, Maximum delay setting (default 0)
    u8 filterMode;         // _61, Filter enable flags (bit 5=IIR, bits 0-4=FIR taps)
    u8 panCalcTypes[3];    // _62, Pan calculation types (default [26,1,1])
    u32 channelPriority;   // _68
    u16 releaseTime;       // _6C, Release/fade time in samples (default 600)
    int voiceStealingMode; // _70, Voice stealing enabled (0=off, 1=on)
};

// needed to match UpdateEffecterParam
typedef union MixConfig {
    u16 whole;
    struct {
        u8 upper;
        u8 lower0 : 4;
        u8 lower1 : 4;
    } parts;
} MixConfig;

typedef BOOL (*JCUpdateCallback)(jc_*, JCSTATUS);

/**
 * @brief TODO.
 */
struct jc_ {
    u8 velocity;                        // _00
    u8 note;                            // _01
    u8 pauseFlag;                       // _02
    u8 toFlush;                         // _03
    jcs_* mMgr;                         // _04
    struct jc_** chanListHead;          // _08
    u8 logicalChanType;                 // _0C, 0 = Wave, 1 = ??, 2 = Oscillator
    Wave_* waveData;                    // _10
    u32 _14;                            // _14
    u32 _18;                            // _18
    u32 _1C;                            // _1C
    dspch_* dspChannel;                 // _20
    void* mNext;                        // _24
    JCUpdateCallback updateCallback;    // _28
    JCUpdateCallback pitchSweepUpdater; // _2C
    s32 playId;                         // _30
    s32 savedPlayId;                    // _34
    struct Osc_* mOscillators[4];       // _38
    struct Oscbuf_ mOscBuffers[2];      // _48
    f32 _78;                            // _78
    char _7C[8];                        // _7C
    f32 _84;                            // _84
    char _88[4];                        // _88
    f32 _8C;                            // _8C
    f32 _90;                            // _90
    f32 _94;                            // _94
    u16 _98;                            // _98
    u16 _9A;                            // _9A
    void* _9C;                          // _9C
    char _A0[8];                        // _A0
    f32 basePitch;                      // _A8
    f32 baseVolume;                     // _AC
    f32 currentPitch;                   // _B0
    f32 currentVolume;                  // _B4
    u8 panCalcTypes[3];                 // _B8
    PanMatrix_ panMatrices[4]; // _BC, 0 = Power distribution, 1 = Pan, 2 = Effects send (fxmix), 3 = Dolby surround
    f32 pitchModifier;         // _EC
    f32 volumeModifier;        // _F0
    f32 targetPitch;           // _F4
    u16 finalPitch;            // _F8
    u16 pitchSweepSteps;       // _FA
    jcs_* lastManager;         // _FC
    f32 managerPitch;          // _100
    f32 managerVolume;         // _104
    MixConfig busRouting[6];   // _108
    u16 mixerLevels[6];        // _114
    u32 channelPriority;       // _120
    u16 releaseTime;           // _124
    u16 channelId;             // _126
    int soundId;               // _128
    u8 polyphonyCounter;       // _12C
    char _12D[3];              // _12D
    int _130;                  // _130
    int _134;                  // _134
    int _138;                  // _138
    int _13C;                  // _13C
};

typedef struct Wavelookuptable_ {
    u8* sample;
    u8* _04;
    u32 _08;
    u8 medium;
} Wavelookuptable;

typedef struct fxconfig_ {
    u8 downsample_rate;
    u16 _02;
    u16 decay_ratio;
    u16 sub_delay;
    u16 sub_volume;
    u16 volume;
    u16 leak_rtl;
    u16 leak_ltl;
    s8 mix_reverb_idx;
    u16 mix_reverb_strength;
    s16 _14;
    s16 _16;
} fxconfig;

#ifdef __cplusplus
}
#endif

#endif
