#include "jaudio_NES/track.h"

#include "jaudio_NES/audiotable.h"
#include "jaudio_NES/channel.h"
#include "jaudio_NES/effect.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/system.h"
#include "dolphin/os.h"

#define COMMON_SCRIPT_END -1

/**
 * SCOM_TABLE is a table for each sequence instruction
 * that contains both how many arguments an instruction takes, as well
 * as the type of each argument
 *
 * SCOM_TABLE is bitpacked as follows:
 * abcUUUnn
 *
 * n - number of arguments that the sequence instruction takes
 *
 * a - bitFlag for the type of arg0 if it exists
 * b - bitFlag for the type of arg1 if it exists
 * c - bitFlag for the type of arg2 if it exists
 *
 * bitFlag on - argument is s16
 * bitFlag off - argument is u8
 *
 * U - Unused
 */

// CMD_ARGS_(NUMBER_OF_ARGS)
#define CMD_ARGS_0() 0
#define CMD_ARGS_1(arg0Type) (((sizeof(arg0Type) - 1) << 7) | 1)
#define CMD_ARGS_2(arg0Type, arg1Type) (((sizeof(arg0Type) - 1) << 7) | ((sizeof(arg1Type) - 1) << 6) | 2)
#define CMD_ARGS_3(arg0Type, arg1Type, arg2Type) \
    (((sizeof(arg0Type) - 1) << 7) | ((sizeof(arg1Type) - 1) << 6) | ((sizeof(arg2Type) - 1) << 5) | 3)

#define SCOM_TYPE_U8 0
#define SCOM_TYPE_S16 1

static u8 SCOM_TABLE[] = {
    CMD_ARGS_1(s16),        // 0xA0 (channel:)
    CMD_ARGS_0(),           // 0xA1 (channel:)
    CMD_ARGS_1(s16),        // 0xA2 (channel:)
    CMD_ARGS_0(),           // 0xA3 (channel:)
    CMD_ARGS_1(u8),         // 0xA4 (channel:)
    CMD_ARGS_0(),           // 0xA5 (channel:)
    CMD_ARGS_2(u8, s16),    // 0xA6 (channel:)
    CMD_ARGS_1(u8),         // 0xA7 (channel:)
    CMD_ARGS_0(),           // 0xA8 (channel: random range large) THIS ONE
    CMD_ARGS_0(),           // 0xA9 ()
    CMD_ARGS_0(),           // 0xAA ()
    CMD_ARGS_0(),           // 0xAB ()
    CMD_ARGS_0(),           // 0xAC ()
    CMD_ARGS_0(),           // 0xAD ()
    CMD_ARGS_0(),           // 0xAE ()
    CMD_ARGS_0(),           // 0xAF ()
    CMD_ARGS_1(s16),        // 0xB0 (channel: set filter)
    CMD_ARGS_0(),           // 0xB1 (channel: clear filter)
    CMD_ARGS_1(s16),        // 0xB2 (channel: dynread sequence large)
    CMD_ARGS_1(u8),         // 0xB3 (channel: load filter)
    CMD_ARGS_0(),           // 0xB4 (channel: set dyntable large)
    CMD_ARGS_0(),           // 0xB5 (channel: read dyntable large)
    CMD_ARGS_0(),           // 0xB6 (channel: read dyntable)
    CMD_ARGS_1(s16),        // 0xB7 (channel: random large)
    CMD_ARGS_1(u8),         // 0xB8 (channel: random)
    CMD_ARGS_1(u8),         // 0xB9 (channel: set velocity random variance)
    CMD_ARGS_1(u8),         // 0xBA (channel: set gatetime random variance)
    CMD_ARGS_2(u8, s16),    // 0xBB (channel:)
    CMD_ARGS_1(s16),        // 0xBC (channel: add large)
    CMD_ARGS_1(s16),        // 0xBD (channel:)
    CMD_ARGS_1(u8),         // 0xBE (channel:)
    CMD_ARGS_0(),           // 0xBF ()
    CMD_ARGS_0(),           // 0xC0 ()
    CMD_ARGS_1(u8),         // 0xC1 (channel: set instrument)
    CMD_ARGS_1(s16),        // 0xC2 (channel: set dyntable)
    CMD_ARGS_0(),           // 0xC3 (channel: large notes off)
    CMD_ARGS_0(),           // 0xC4 (channel: large notes on)
    CMD_ARGS_0(),           // 0xC5 (channel: dyn set dyntable)
    CMD_ARGS_1(u8),         // 0xC6 (channel: set soundFont)
    CMD_ARGS_2(u8, s16),    // 0xC7 (channel: write into sequence script)
    CMD_ARGS_1(u8),         // 0xC8 (channel: subtract -> set value)
    CMD_ARGS_1(u8),         // 0xC9 (channel: `bit and` -> set value)
    CMD_ARGS_1(u8),         // 0xCA (channel: set mute behavior)
    CMD_ARGS_1(s16),        // 0xCB (channel: read sequence -> set value)
    CMD_ARGS_1(u8),         // 0xCC (channel: set value)
    CMD_ARGS_1(u8),         // 0xCD (channel: disable channel)
    CMD_ARGS_1(s16),        // 0xCE (channel:)
    CMD_ARGS_1(s16),        // 0xCF (channel: write large into sequence script)
    CMD_ARGS_1(u8),         // 0xD0 (channel: stereo headset effects)
    CMD_ARGS_1(u8),         // 0xD1 (channel: set note allocation policy)
    CMD_ARGS_1(u8),         // 0xD2 (channel: set sustain)
    CMD_ARGS_1(u8),         // 0xD3 (channel: large bend pitch)
    CMD_ARGS_1(u8),         // 0xD4 (channel: set reverb)
    CMD_ARGS_1(u8),         // 0xD5 ()
    CMD_ARGS_1(u8),         // 0xD6 ()
    CMD_ARGS_1(u8),         // 0xD7 (channel: set vibrato rate)
    CMD_ARGS_1(u8),         // 0xD8 (channel: set vibrato depth)
    CMD_ARGS_1(u8),         // 0xD9 (channel: set decay index)
    CMD_ARGS_1(s16),        // 0xDA (channel: set envelope)
    CMD_ARGS_1(u8),         // 0xDB (channel: transpose)
    CMD_ARGS_1(u8),         // 0xDC (channel: set pan mix)
    CMD_ARGS_1(u8),         // 0xDD (channel: set pan)
    CMD_ARGS_1(s16),        // 0xDE (channel: set freqscale)
    CMD_ARGS_1(u8),         // 0xDF (channel: set volume)
    CMD_ARGS_1(u8),         // 0xE0 (channel: set volume scale)
    CMD_ARGS_3(u8, u8, u8), // 0xE1 (channel: set vibratorate linear)
    CMD_ARGS_3(u8, u8, u8), // 0xE2 (channel: set vibrato depth linear)
    CMD_ARGS_1(u8),         // 0xE3 (channel: set vibrato delay)
    CMD_ARGS_0(),           // 0xE4 (channel: dyncall)
    CMD_ARGS_1(u8),         // 0xE5 (channel: set reverb index)
    CMD_ARGS_1(u8),         // 0xE6 (channel: set book offset)
    CMD_ARGS_1(s16),        // 0xE7 (channel:)
    CMD_ARGS_3(u8, u8, u8), // 0xE8 (channel:)
    CMD_ARGS_1(u8),         // 0xE9 (channel: set note priority)
    CMD_ARGS_0(),           // 0xEA (channel: stop script)
    CMD_ARGS_2(u8, u8),     // 0xEB (channel: set soundFont and instrument)
    CMD_ARGS_0(),           // 0xEC (channel: reset vibrato)
    CMD_ARGS_1(u8),         // 0xED (channel: set hilo gain)
    CMD_ARGS_1(u8),         // 0xEE (channel: small bend pitch)
    CMD_ARGS_2(s16, u8),    // 0xEF ()
    CMD_ARGS_0(),           // 0xF0 (channel: unreserve notes)
    CMD_ARGS_1(u8),         // 0xF1 (channel: reserve notes)
    // Control flow instructions (>= 0xF2) can only have 0 or 1 args
    CMD_ARGS_1(u8),  // 0xF2 (branch relative if less than zero)
    CMD_ARGS_1(u8),  // 0xF3 (branch relative if equal to zero)
    CMD_ARGS_1(u8),  // 0xF4 (jump relative)
    CMD_ARGS_1(s16), // 0xF5 (branch if greater than or equal to zero)
    CMD_ARGS_0(),    // 0xF6 (break)
    CMD_ARGS_0(),    // 0xF7 (loop end)
    CMD_ARGS_1(u8),  // 0xF8 (loop)
    CMD_ARGS_1(s16), // 0xF9 (branch if less than zero)
    CMD_ARGS_1(s16), // 0xFA (branch if equal to zero)
    CMD_ARGS_1(s16), // 0xFB (jump)
    CMD_ARGS_1(s16), // 0xFC (call and jump to a function)
    CMD_ARGS_0(),    // 0xFD (delay n frames)
    CMD_ARGS_0(),    // 0xFE (delay 1 frame)
    CMD_ARGS_0(),    // 0xFF (end script)
};

#define SCOM_GET_ARG_NUM(cmd) (SCOM_TABLE[(cmd)] & 3)
#define SCOM_GET_TYPE(cmd, argno) (SCOM_TABLE[(cmd)] & (1 << (7 - (argno & 3))))

static u8 Nas_ReadByteData(macro* macro);
static s16 Nas_ReadWordData(macro* macro);
static u16 Nas_ReadLengthData(macro* macro);
static void __Stop_Note(note* n);
static s32 __SetNote(note* n, s32 cmd);
static s32 __Command_Seq(note* n);
static s32 __SetVoice(note* n, s32 cmd);
static s32 __SetChannel(note* n, s32 cmd);
static u8 Nas_ProgramChanger(sub* subtrack, u8 prog_id, voicetable** inst_pp, env* adsr_env);

static u16 Convert_Com(macro* macro, u8 cmd) {
    u16 val = 0;

    if ((u8)SCOM_GET_ARG_NUM(cmd - 0xA0) == 1) {
        if (SCOM_GET_TYPE(cmd - 0xA0, 0) == SCOM_TYPE_U8) {
            val = Nas_ReadByteData(macro);
        } else {
            val = Nas_ReadWordData(macro);
        }
    }

    return val;
}

static s32 Common_Com(group* group, macro* macro, s32 cmd, s32 arg) {
    u8 iters;
    u16 abs;
    s8 rel;

    switch (cmd) {
        case COMMON_CMD_STOP_SCRIPT:
            if (macro->depth == 0) {
                return COMMON_SCRIPT_END;
            }

            macro->pc = macro->stack[--macro->depth];
            break;
        case COMMON_CMD_DELAY_N_FRAMES:
            return Nas_ReadLengthData(macro);
        case COMMON_CMD_DELAY_1_FRAME:
            return 1;
        case COMMON_CMD_CALL:
            macro->stack[macro->depth++] = macro->pc;
            macro->pc = group->seq_data + (arg & 0xFFFF);
            break;
        case COMMON_CMD_LOOP:
            macro->remaining_loop_iters[macro->depth] = arg & 0xFF;
            macro->stack[macro->depth++] = macro->pc;
            break;
        case COMMON_CMD_LOOP_END:
            iters = macro->remaining_loop_iters[macro->depth - 1];
            iters--;
            macro->remaining_loop_iters[macro->depth - 1] = iters;
            if (iters != 0) {
                macro->pc = macro->stack[macro->depth - 1];
            } else {
                macro->depth--;
            }
            break;
        case COMMON_CMD_BREAK:
            macro->depth--;
            break;
        case COMMON_CMD_BRANCH_ABS_GREQ_ZERO:
        case COMMON_CMD_BRANCH_ABS_NOT_EQ_ZERO:
        case COMMON_CMD_BRANCH_ABS_EQ_ZERO:
        case COMMON_CMD_BRANCH_ABS:
            abs = arg & 0xFFFF;
            if (cmd == COMMON_CMD_BRANCH_ABS_EQ_ZERO && macro->value != 0) {
                break;
            } else if (cmd == COMMON_CMD_BRANCH_ABS_NOT_EQ_ZERO && macro->value >= 0) {
                break;
            } else if (cmd == COMMON_CMD_BRANCH_ABS_GREQ_ZERO && macro->value < 0) {
                break;
            } else {
                macro->pc = group->seq_data + abs;
            }
            break;
        case COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO:
        case COMMON_CMD_BRANCH_REL_EQ_ZERO:
        case COMMON_CMD_BRANCH_REL:
            rel = (s8)(arg & 0xFF);
            if (cmd == COMMON_CMD_BRANCH_REL_EQ_ZERO && macro->value != 0) {
                break;
            } else if (cmd == COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO && macro->value >= 0) {
                break;
            } else {
                macro->pc += rel;
            }
            break;
    }

    return 0;
}

static void Nas_InitSubTrack(sub* subtrack) {
    s32 i;

    if (subtrack != &AG.null_sub_track) {
        subtrack->transposition = 0;
        subtrack->enabled = FALSE;
        subtrack->finished = FALSE;
        subtrack->stop_script = FALSE;
        // subtrack->muted = FALSE;
        subtrack->has_instrument = FALSE;
        subtrack->stereo_effects = FALSE;
        subtrack->large_notes = FALSE;
        subtrack->book_ofs = 0;
        *(u8*)&subtrack->stereo_phase = 0;
        subtrack->changes.as_byte = 0xFF;
        subtrack->macro_player.depth = 0;
        subtrack->volume = 1.0f;
        subtrack->volume_scale = 1.0f;
        subtrack->new_pan = 64;
        subtrack->frequency_scale = 1.0f;
        subtrack->pan_channel_weight = 128;
        subtrack->surround_effect_idx = 0xFF;
        subtrack->velocity_random_variance = 0;
        subtrack->gate_time_random_variance = 0;
        subtrack->channel = nullptr;
        subtrack->reverb_idx = 0;
        subtrack->target_reverb_vol = 0;
        subtrack->gain = 0;
        subtrack->note_priority = 3;
        subtrack->priority2 = 1;
        subtrack->delay = 0;

        subtrack->adsr_env.envelope = DEFAULT_ENV;
        subtrack->adsr_env.decay_idx = 240;
        subtrack->adsr_env.sustain = 0;

        subtrack->vibrato_params.rate_target = 2048;
        subtrack->vibrato_params.rate_start = 2048;
        subtrack->vibrato_params.depth_target = 0;
        subtrack->vibrato_params.depth_start = 0;
        subtrack->vibrato_params.rate_change_delay = 0;
        subtrack->vibrato_params.depth_change_delay = 0;
        subtrack->vibrato_params.delay = 0;

        subtrack->filter = nullptr;
        subtrack->comb_filter_gain = 0;
        subtrack->comb_filter_size = 0;

        for (i = 0; i < ARRAY_COUNT(subtrack->port); i++) {
            subtrack->port[i] = -1;
        }

        subtrack->unused = FALSE;
        Nas_InitChNode(&subtrack->channel_node);
        subtrack->sample_start_pos = 0;
        subtrack->_E0 = 0;
        subtrack->sfx_state = nullptr;
    }
}

static s32 Nas_EntryNoteTrack(sub* subtrack, int note_idx) {
    note* entry_note;

    if (subtrack->note_layers[note_idx] == nullptr) {
        entry_note = (note*)Nas_GetList(&AG.note_link);
        subtrack->note_layers[note_idx] = entry_note;
        if (entry_note == nullptr) {
            subtrack->note_layers[note_idx] = nullptr;
            return -1;
        }
    } else {
        Nas_Release_Channel(subtrack->note_layers[note_idx]);
    }

    entry_note = subtrack->note_layers[note_idx];
    entry_note->sub_track = subtrack;
    entry_note->adsr_env = subtrack->adsr_env;
    entry_note->adsr_env.decay_idx = 0;
    entry_note->target_reverb_volume = subtrack->target_reverb_vol;
    entry_note->enabled = TRUE;
    entry_note->finished = FALSE;
    entry_note->muted = FALSE;
    entry_note->continuous = FALSE;
    entry_note->channel_attached = FALSE;
    entry_note->ignore_drum_pan = FALSE;
    entry_note->continuous_channel_released = FALSE;
    entry_note->note_properties_need_init = FALSE;
    *(u8*)&entry_note->stereo_phase = 0;
    entry_note->portamento_sweep.mode = 0;
    entry_note->macro_player.depth = 0;
    entry_note->gate_time = 128;

    entry_note->frequency_scale = 1.0f;
    entry_note->bend = 1.0f;
    entry_note->velocity_square2 = 0.0f;

    entry_note->pan = 64;
    entry_note->surround_effect_idx = 128;
    entry_note->transposition = 0;
    entry_note->delay = 0;
    entry_note->gate_delay = 0;
    entry_note->delay2 = 0;
    entry_note->channel = nullptr;
    entry_note->instrument = nullptr;
    entry_note->inst_or_wave = -1;
    entry_note->_0A.asU16 = 0xFFFF;

    entry_note->vibrato_params.rate_target = 2048;
    entry_note->vibrato_params.rate_start = 2048;
    entry_note->vibrato_params.depth_target = 0;
    entry_note->vibrato_params.depth_start = 0;
    entry_note->vibrato_params.rate_change_delay = 0;
    entry_note->vibrato_params.depth_change_delay = 0;
    entry_note->vibrato_params.delay = 0;

    return 0;
}

extern void Nas_ReleaseNoteTrack(note* note) {
    if (note != nullptr) {
        if (note->sub_track != &AG.null_sub_track && note->sub_track->group->flags.finished == TRUE) {
            Nas_Release_Channel_Force(note);
        } else {
            Nas_Release_Channel(note);
        }

        note->enabled = FALSE;
        note->finished = TRUE;
    }
}

static void Nas_CloseNoteTrack(sub* subtrack, s32 note_idx) {
    note* note = subtrack->note_layers[note_idx];

    if (note != nullptr) {
        Nas_AddList(&AG.note_link, &note->link);
        Nas_ReleaseNoteTrack(note);
        subtrack->note_layers[note_idx] = nullptr;
    }
}

extern void Nas_ReleaseSubTrack(sub* subtrack) {
    s32 i;

    subtrack->finished = TRUE;
    for (i = 0; i < ARRAY_COUNT(subtrack->note_layers); i++) {
        Nas_CloseNoteTrack(subtrack, i);
    }

    Nas_DeAllocAllVoices(&subtrack->channel_node);
    subtrack->enabled = FALSE;
}

static void Nas_AllocSub(group* grp, u16 subtrack_enable_flags) {
    s32 i;

    for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
        if ((subtrack_enable_flags & 1) != 0) {
            sub* subtrack = grp->subtracks[i];

            subtrack->bank_id = grp->bank_id;
            subtrack->mute_flags = grp->mute_flags;
            subtrack->note_alloc_policy = grp->note_alloc_policy;
        }

        subtrack_enable_flags = subtrack_enable_flags >> 1;
    }
}

static void Nas_DeAllocSub(group* grp, u16 subtrack_dealloc_flags) {
    s32 i;

    for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
        sub* subtrack = grp->subtracks[i];

        if (subtrack != &AG.null_sub_track) {
            Nas_ReleaseSubTrack(subtrack);
        }
    }
}

static void Nas_OpenSub(group* grp, u8 subtrack_idx, u8* script) {
    sub* subtrack = grp->subtracks[subtrack_idx];
    s32 i;

    subtrack->enabled = TRUE;
    subtrack->finished = FALSE;
    subtrack->macro_player.depth = 0;
    subtrack->macro_player.pc = script;
    subtrack->delay = 0;

    for (i = 0; i < ARRAY_COUNT(subtrack->note_layers); i++) {
        if (subtrack->note_layers[i] != nullptr) {
            Nas_CloseNoteTrack(subtrack, i);
        }
    }
}

extern void Nas_ReleaseGroup_Force(group* grp) {
    grp->flags.finished = TRUE;
    Nas_ReleaseGroup(grp);
}

extern void Nas_ReleaseGroup(group* grp) {
    Nas_DeAllocSub(grp, AUDIO_GROUP_ALL_SUBTRACKS);
    Nas_DeAllocAllVoices(&grp->channel_node);
    if (grp->flags.enabled) {
        grp->flags.enabled = FALSE;
        grp->flags.finished = TRUE;

        if (Nas_CheckIDseq(grp->seq_id)) {
            Nas_WriteIDseq(grp->seq_id, LOAD_STATUS_DISCARDABLE);
        }

        if (Nas_CheckIDbank(grp->bank_id)) {
            Nas_WriteIDbank(grp->bank_id, LOAD_STATUS_MAYBE_DISCARDABLE);
        }

        if (AG.bank_heap.auto_heap.entries[0].id == grp->bank_id) {
            AG.bank_heap.auto_heap.use_entry_idx = 1;
        } else if (AG.bank_heap.auto_heap.entries[1].id == grp->bank_id) {
            AG.bank_heap.auto_heap.use_entry_idx = 0;
        }
    }
}

extern void Nas_AddList(link* root, link* list) {
    if (list->prev != nullptr) {
        static BOOL first = TRUE;

        if (first) {
            OSReport("GLOBAL USE %x\n", &AG.channel_node.useList);
            OSReport("GLOBAL FREE %x\n", &AG.channel_node.freeList);
            OSReport("GLOBAL RELEASE %x\n", &AG.channel_node.releaseList);
            OSReport("GLOBAL RELWAIT %x\n", &AG.channel_node.relwaitList);
            first = FALSE;
        }

        OSReport("List %x\n", list);
        OSReport("Root %x\n", root);
    } else {
        root->prev->next = list;
        list->prev = root->prev;
        list->next = root;
        root->prev = list;
        root->numAfter++;
        list->pNode = root->pNode;
    }
}

extern void* Nas_GetList(link* root) {
    link* list = root->prev;

    if (list == root) {
        return nullptr;
    }

    list->prev->next = root;
    root->prev = list->prev;
    list->prev = nullptr;
    root->numAfter--;
    return list->pData;
}

static void Nas_InitNoteList(void) {
    s32 i;

    AG.note_link.prev = &AG.note_link;
    AG.note_link.next = &AG.note_link;
    AG.note_link.numAfter = 0;
    AG.note_link.pNode = nullptr;

    for (i = 0; i < AUDIO_NOTE_MAX; i++) {
        AG.notes[i].link.pData = &AG.notes[i];
        AG.notes[i].link.prev = nullptr;
        Nas_AddList(&AG.note_link, &AG.notes[i].link);
    }
}

static u8 Nas_ReadByteData(macro* m) {
    return *m->pc++;
}

static s16 Nas_ReadWordData(macro* m) {
    s16 data = (*m->pc++) << 8;

    data = data | (*m->pc++);
    return data;
}

#define Nas_LENGTH_IS_U16(d) ((d) & 0x80)
static u16 Nas_ReadLengthData(macro* m) {
    u16 data = (*m->pc++);

    if (Nas_LENGTH_IS_U16(data)) {
        data = (data << 8) & 0x7F00;
        data = (*m->pc++) | data;
    }

    return data;
}
#undef Nas_LENGTH_IS_U16

static void Nas_NoteSeq(note* n) {
    if (n->enabled) {
        if (n->delay > 1) {
            n->delay--;

            if (n->muted == FALSE && n->delay <= n->gate_delay) {
                Nas_Release_Channel(n);
                n->muted = TRUE;
            }
        } else {
            s32 cmd;

            __Stop_Note(n);

            do {
                cmd = __Command_Seq(n);
                if (cmd == COMMON_SCRIPT_END) {
                    return;
                }

                cmd = __SetNote(n, cmd);
            } while (cmd == COMMON_SCRIPT_END && n->delay == 0);

            if (cmd != COMMON_SCRIPT_END) {
                cmd = __SetVoice(n, cmd);
            }

            if (cmd != COMMON_SCRIPT_END) {
                __SetChannel(n, cmd);
            }

            if (n->muted == TRUE) {
                if (n->channel != nullptr || n->continuous) {
                    Nas_Release_Channel(n);
                }
            }
        }
    }
}

static void __Stop_Note(note* n) {
    s32 mode;

    if (n->continuous == FALSE) {
        Nas_Release_Channel(n);
    } else if (n->channel != nullptr && n->channel->playback_ch.wanted_parent_note == n) {
        Nas_Release_Channel(n);
    }

    switch (AUDIO_SWEEP_MODE(n->portamento_sweep)) {
        case PORTAMENTO_MODE_1:
        case PORTAMENTO_MODE_2:
        case PORTAMENTO_MODE_6:
            n->portamento_sweep.mode = 0;
            break;
    }

    n->note_properties_need_init = TRUE;
}

static s32 __SetChannel(note* n, s32 same_sample) {
    if (n->continuous == TRUE && n->continuous_channel_released == TRUE) {
        return 0;
    }

    if (n->continuous != TRUE || n->channel == nullptr || n->channel_attached == FALSE || same_sample != TRUE ||
        n->channel->playback_ch.current_parent_note != n) {
        if (same_sample == FALSE) {
            Nas_Release_Channel(n);
        }

        n->channel = Nas_AllocationOnRequest(n);
        if (n->channel != nullptr) {
            if (n->channel->playback_ch.current_parent_note == n) {
                Nas_ChannelModInit(n->channel);
            }
        }
    }

    if (n->channel != nullptr && n->channel->playback_ch.current_parent_note == n) {
        Nas_SweepInit(n->channel);
    }

    return 0;
}

static s32 __Command_Seq(note* n) {
    macro* m = &n->macro_player;
    sub* subtrack = n->sub_track;
    group* grp = subtrack->group;
    sweep* port_sweep;
    u8 cmd;
    u8 cmdArgU8;
    u32 tmp;
    u16 cmdArgU16;
    u16 velocity;

    while (TRUE) {
        cmd = Nas_ReadByteData(m);

        if (cmd <= NOTE_CMD_MUTE) {
            return cmd;
        }

        if (cmd >= COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO) {
            cmdArgU16 = Convert_Com(m, cmd);

            if (Common_Com(grp, m, cmd, cmdArgU16) == 0) {
                continue; // keep processing
            }

            /* stop processing script */
            Nas_ReleaseNoteTrack(n);
            return COMMON_SCRIPT_END;
        }

        switch (cmd) {
            case NOTE_CMD_SET_VELOCITY_SQ:
            case NOTE_CMD_SET_PAN:
                cmdArgU8 = *m->pc++;
                if (cmd == NOTE_CMD_SET_VELOCITY_SQ) {
                    n->velocity_square = (f32)(cmdArgU8 * cmdArgU8) / (f32)(127 * 127);
                } else {
                    n->pan = cmdArgU8;
                }
                break;
            case NOTE_CMD_SET_TRANSPOSITION:
            case NOTE_CMD_SET_GATE_TIME:
                cmdArgU8 = *m->pc++;
                if (cmd == NOTE_CMD_SET_GATE_TIME) {
                    n->gate_time = cmdArgU8;
                } else {
                    n->transposition = cmdArgU8;
                }
                break;
            case NOTE_CMD_CONTINUOUS_ON:
            case NOTE_CMD_CONTINUOUS_OFF:
                n->continuous = cmd == NOTE_CMD_CONTINUOUS_ON;
                n->continuous_channel_released = FALSE;
                Nas_Release_Channel(n);
                break;
            case NOTE_CMD_SET_SHORT_NOTE_DEFAULT_DELAY:
                n->short_note_default_delay = Nas_ReadLengthData(m);
                break;
            case NOTE_CMD_SET_INSTRUMENT:
                cmdArgU8 = Nas_ReadByteData(m);
                if (cmdArgU8 >= 0x7E) {
                    if (cmdArgU8 == 0x7E) {
                        // effect/sfx
                        n->inst_or_wave = VOICE_TYPE_SOUND_EFF;
                    } else if (cmdArgU8 == 0x7F) {
                        // percussion/drum
                        n->inst_or_wave = VOICE_TYPE_PERCUSSION;
                    } else {
                        // synth wave
                        n->inst_or_wave = cmdArgU8;
                        n->instrument = nullptr;
                    }

                    if (cmdArgU8 == 0xFF) {
                        n->adsr_env.decay_idx = 0;
                    }
                } else {
                    // voice/instrument
                    cmd = Nas_ProgramChanger(subtrack, cmdArgU8, &n->instrument, &n->adsr_env);
                    n->inst_or_wave = cmd;
                    if (cmd == 0) {
                        n->inst_or_wave = 0xFF;
                    }
                }
                break;
            case NOTE_CMD_ENABLE_SWEEP:
                n->portamento_sweep.mode = Nas_ReadByteData(m);
                cmdArgU8 = Nas_ReadByteData(m);
                cmdArgU8 = cmdArgU8 + subtrack->transposition;
                cmdArgU8 = cmdArgU8 + n->transposition;
                cmdArgU8 = cmdArgU8 + grp->transposition;

                switch (AUDIO_SWEEP_MODE(n->portamento_sweep)) {
                    case PORTAMENTO_MODE_6:
                    case PORTAMENTO_MODE_7:
                        break;
                    default:
                        if ((u8)cmdArgU8 > 127) {
                            cmdArgU8 = (u8)0;
                        }
                        break;
                }

                n->portamento_target_note = (u8)cmdArgU8;
                if (AUDIO_SWEEP_IS_SPECIAL(n->portamento_sweep)) {
                    n->portamento_time = *m->pc++;
                } else {
                    n->portamento_time = Nas_ReadLengthData(m);
                }
                break;
            case NOTE_CMD_DISABLE_SWEEP:
                n->portamento_sweep.mode = PORTAMENTO_MODE_OFF;
                break;
            case NOTE_CMD_SET_ADSR_ENVELOPE_DECAY_IDX:
                n->adsr_env.envelope = (envdat*)(grp->seq_data + (Nas_ReadWordData(m) & 0xFFFF));
#ifdef TARGET_PC
                pc_swap_envdat_seq(n->adsr_env.envelope);
#endif
                // fallthrough 0xCB -> 0xCF
            case NOTE_CMD_SET_ADSR_DECAY_IDX:
                n->adsr_env.decay_idx = Nas_ReadByteData(m);
                break;
            case NOTE_CMD_IGNORE_DRUM_PAN:
                n->ignore_drum_pan = TRUE;
                break;
            case NOTE_CMD_SET_STEREO_PHASE:
                *(u8*)&n->stereo_phase = Nas_ReadByteData(m);
                break;
            case NOTE_CMD_SET_BEND:
                cmdArgU8 = 128 + Nas_ReadByteData(m);
                n->bend = PCENTTABLE2[cmdArgU8];
                break;
            case NOTE_CMD_DISABLE_FLAGS:
                cmdArgU16 = Nas_ReadWordData(m);
                n->_0A.asU16 &= cmdArgU16 ^ 0xFFFF;
                break;
            case NOTE_CMD_SET_SURROUND_EFFECT_IDX:
                n->surround_effect_idx = Nas_ReadByteData(m);
                break;
            default:
                switch (cmd & 0xF0) {
                    case NOTE_CMD_SHORT_NOTE_VELOCITY_SQ_MASK:
                        velocity = grp->short_note_velocity_tbl[cmd & 0xF];
                        n->velocity_square = (f32)(velocity * velocity) / (f32)(127 * 127);
                        break;
                    case NOTE_CMD_SET_SHORT_NOTE_GATE_TIME_MASK:
                        n->gate_time = grp->short_note_gate_time_tbl[cmd & 0xF];
                        break;
                }
        }
    }

    return cmd;
}

static s32 __SetVoice(note* n, s32 arg) {
    u8 semitone;
    s32 same_sample;
    s32 inst_or_wave;
    sweep* port_sweep;
    f32 freq_scale;
    f32 freq_scale2;
    wtstr* tuned_sample;
    voicetable* instrument;
    perctable* percussion;
    percvoicetable* effect;
    sub* subtrack;
    group* grp;
    u16 effect_id;
    s32 velocity;
    s32 semitone2;
    s32 speed;
    s32 speed2;
    f32 tuning;
    f32 t0;
    f32 t1;
    f32 freq0;
    f32 freq1;
    f32 time;

    semitone = arg;
    same_sample = TRUE;
    inst_or_wave = n->inst_or_wave;
    subtrack = n->sub_track;
    grp = subtrack->group;

    if (inst_or_wave == 0xFF) {
        if (subtrack->has_instrument == FALSE) {
            return COMMON_SCRIPT_END;
        }

        inst_or_wave = subtrack->inst_or_wave;
    }

    switch (inst_or_wave) {
        case VOICE_TYPE_PERCUSSION:
            semitone = semitone + n->transposition;
            if (n->_0A.flags.add_subtrack_transposition) {
                semitone = semitone + subtrack->transposition;
            }

            n->semitone = semitone;
            percussion = PercToPp(subtrack->bank_id, semitone);

            /* Mute note and exit if percussion doesn't exist or the subtrack is muted */
            if (percussion == nullptr || subtrack->muted) {
                n->muted = TRUE;
                n->delay2 = n->delay;
                return COMMON_SCRIPT_END;
            }

            n->adsr_env.envelope = percussion->envelope;
            n->adsr_env.decay_idx = percussion->adsr_decay_idx;
            if (n->ignore_drum_pan == FALSE) {
                n->pan = percussion->pan;
            }
            n->tuned_sample = &percussion->tuned_sample;
            n->frequency_scale = n->tuned_sample->tuning;
            break;
        case VOICE_TYPE_SOUND_EFF:
            effect_id = (semitone + (n->transposition << 6));
            n->semitone = semitone;
            effect = VpercToVep(subtrack->bank_id, effect_id);

            /* Mute note and exit if sfx doesn't exist or the subtrack is muted */
            if (effect == nullptr || subtrack->muted) {
                n->muted = TRUE;
                n->delay2 = n->delay + 1;
                return COMMON_SCRIPT_END;
            }

            n->tuned_sample = &effect->tuned_sample;
            n->frequency_scale = n->tuned_sample->tuning;
            break;
        default: // voices/instruments
            semitone = semitone + grp->transposition + n->transposition;
            if (n->_0A.flags.add_subtrack_transposition) {
                semitone = semitone + subtrack->transposition;
            }

            n->semitone = semitone;
            if (semitone > 127 || subtrack->muted) {
                n->muted = TRUE;
                if (subtrack->muted) {
                    subtrack->note_semitone = n->semitone;
                }

                return COMMON_SCRIPT_END;
            }

            if (n->inst_or_wave == 0xFF) {
                instrument = subtrack->voicetable;
            } else {
                instrument = n->instrument;
            }

            if (n->portamento_sweep.mode != PORTAMENTO_MODE_OFF) {
                port_sweep = &n->portamento_sweep;

                switch (AUDIO_SWEEP_MODE(*port_sweep)) {
                    case PORTAMENTO_MODE_6:
                    case PORTAMENTO_MODE_7:
                        velocity = semitone;
                        break;
                    default:
                        velocity = semitone > n->portamento_target_note ? semitone : n->portamento_target_note;
                        break;
                }

                // velocity =
                if (instrument != nullptr) {
                    tuned_sample = NoteToVoice(instrument, velocity);
                    same_sample = n->tuned_sample == tuned_sample;
                    n->tuned_sample = tuned_sample;
                    tuning = n->tuned_sample->tuning;
                } else {
                    n->tuned_sample = nullptr;
                    tuning = 1.0f;
                    if (inst_or_wave >= 0xC0) {
                        n->tuned_sample = &AG.synth_delay[inst_or_wave - 0xC0].tuned_sample;
                    }
                }

                t0 = tuning * PITCHTABLE[semitone];
                semitone2 = (s8)n->portamento_target_note;
                switch (AUDIO_SWEEP_MODE(*port_sweep)) {
                    case PORTAMENTO_MODE_6:
                    case PORTAMENTO_MODE_7:
                        semitone2 += semitone;
                        break;
                }
                if (semitone2 < 0) {
                    semitone2 = 0;
                }
                if (semitone2 > 127) {
                    semitone2 = 127;
                }

                t1 = tuning * PITCHTABLE[semitone2];

                switch (AUDIO_SWEEP_MODE(*port_sweep)) {
                    case PORTAMENTO_MODE_1:
                    case PORTAMENTO_MODE_3:
                    case PORTAMENTO_MODE_5:
                    case PORTAMENTO_MODE_6:
                    case PORTAMENTO_MODE_7:
                        freq_scale2 = t0;
                        freq_scale = t1;
                        break;
                    case PORTAMENTO_MODE_2:
                    case PORTAMENTO_MODE_4:
                        freq_scale = t0;
                        freq_scale2 = t1;
                        break;
                    default:
                        freq_scale = t0;
                        freq_scale2 = t0;
                        break;
                }

                port_sweep->extent = (freq_scale2 / freq_scale) - 1.0f;

                if (AUDIO_SWEEP_IS_SPECIAL(*port_sweep)) {
                    speed = (grp->tempo * 0x8000) / AG.max_tempo;

                    if (n->delay != 0) {
                        speed = (speed * 0x100) / (n->delay * n->portamento_time);
                    }
                } else {
                    speed = (2 * 0x10000) / (n->portamento_time * AG.audio_params.updates_per_frame);
                }

                if (speed >= 0x7FFF) {
                    speed = 0x7FFF;
                } else if (speed <= 0) {
                    speed = 1;
                }

                port_sweep->speed = speed;
                port_sweep->current = 0;
                n->frequency_scale = freq_scale;
                if (AUDIO_SWEEP_MODE(*port_sweep) == PORTAMENTO_MODE_5) {
                    n->portamento_target_note = semitone;
                }
            } else {
                if (instrument != nullptr) {
                    tuned_sample = NoteToVoice(instrument, semitone);
                    same_sample = n->tuned_sample == tuned_sample;
                    n->tuned_sample = tuned_sample;
                    n->frequency_scale = PITCHTABLE[semitone] * n->tuned_sample->tuning;
                } else {
                    n->tuned_sample = nullptr;
                    n->frequency_scale = PITCHTABLE[semitone];
                    if (inst_or_wave >= 0xC0) {
                        n->tuned_sample = &AG.synth_delay[inst_or_wave - 0xC0].tuned_sample;
                    }
                }
            }

            break;
    }

    n->delay2 = n->delay;
    n->frequency_scale *= n->bend;

    if (n->delay == 0) {
        if (n->tuned_sample != nullptr) {
            time = n->tuned_sample->wavetable->loop->loop_end;
        } else {
            time = 0.0f;
        }

        time *= grp->tempo;
        time *= AG._2894;
        time /= n->frequency_scale;

        if (time > (f32)0x7FFE) {
            time = (f32)0x7FFE;
        }

        n->delay = (u16)(s32)time + 1;
        n->gate_delay = 0;

        if (n->portamento_sweep.mode != PORTAMENTO_MODE_OFF) {
            if (AUDIO_SWEEP_IS_SPECIAL(*port_sweep)) {
                speed2 = (grp->tempo * 0x8000) / AG.max_tempo;
                speed2 = (speed2 * 0x100) / (n->delay * n->portamento_time);
                if (speed2 >= 0x7FFF) {
                    speed2 = 0x7FFF;
                } else if (speed2 <= 0) {
                    speed2 = 1;
                }

                port_sweep->speed = speed2;
            }
        }
    }

    subtrack->note_semitone = n->semitone;

    return same_sample;
}

static s32 __SetNote(note* n, s32 cmd) {
    macro* m = &n->macro_player;
    u16 delay;
    s32 velocity;
    sub* subtrack = n->sub_track;
    group* grp = subtrack->group;
    s32 int_delta;
    f32 float_delta;

    if (cmd == 0xC0) {
        n->delay = Nas_ReadLengthData(m);
        n->muted = TRUE;
        n->continuous_channel_released = FALSE;
        return COMMON_SCRIPT_END;
    }

    n->muted = FALSE;
    if (subtrack->large_notes == TRUE) {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = Nas_ReadLengthData(m);
                velocity = *m->pc++;
                n->gate_time = *m->pc++;
                n->last_delay = delay;
                break;
            case 0x40:
                delay = Nas_ReadLengthData(m);
                velocity = *m->pc++;
                n->gate_time = 0;
                n->last_delay = delay;
                break;
            case 0x80:
                delay = n->last_delay;
                velocity = *m->pc++;
                n->gate_time = *m->pc++;
                break;
        }

        if (velocity > 127 || velocity < 0) {
            velocity = 127;
        }

        n->velocity_square = ((f32)velocity * (f32)velocity) / ((f32)127 * (f32)127);
        cmd -= (cmd & 0xC0);
    } else {
        switch (cmd & 0xC0) {
            case 0x00:
                delay = Nas_ReadLengthData(m);
                n->last_delay = delay;
                break;
            case 0x40:
                delay = n->short_note_default_delay;
                break;
            case 0x80:
                delay = n->last_delay;
                break;
        }

        cmd -= (cmd & 0xC0);
    }

    if (subtrack->velocity_random_variance != 0) {
        float_delta = n->velocity_square * (AG.audio_random_seed % subtrack->velocity_random_variance) / 100.0f;
        if (AG.audio_random_seed & 0x8000) {
            float_delta = -float_delta;
        }

        n->velocity_square2 = n->velocity_square + float_delta;
        if (n->velocity_square2 < 0.0f) {
            n->velocity_square2 = 0.0f;
        } else if (n->velocity_square2 > 1.0f) {
            n->velocity_square2 = 1.0f;
        }
    } else {
        n->velocity_square2 = n->velocity_square;
    }

    n->delay = delay;
    n->gate_delay = (n->gate_time * delay) >> 8;

    if (subtrack->gate_time_random_variance != 0) {
        /* @BUG - should be gate_time_random_variance (longstanding bug) */
        int_delta = (n->gate_delay * (AG.audio_random_seed % subtrack->velocity_random_variance)) / 100;
        if (AG.audio_random_seed & 0x4000) {
            int_delta = -int_delta;
        }

        n->gate_delay += int_delta;
        if (n->gate_delay < 0) {
            n->gate_delay = 0;
        } else if (n->gate_delay > n->delay) {
            n->gate_delay = n->delay;
        }
    }

    if (grp->flags.muted && (subtrack->mute_flags & (AUDIO_MUTE_FLAG_STOP_SUBTRACK | AUDIO_MUTE_FLAG_STOP_NOTE))) {
        n->muted = TRUE;
        return COMMON_SCRIPT_END;
    }

    if (grp->skip_ticks != 0) {
        n->muted = TRUE;
        return COMMON_SCRIPT_END;
    }

    return cmd;
}

static void Nas_PriorityChanger(sub* subtrack, u8 prio) {
    u8 prio0 = prio & 0xF;
    u8 prio1;

    if (prio0) {
        subtrack->note_priority = prio0;
    }

    prio1 = (u8)(prio >> 4);
    if (prio1) {
        subtrack->priority2 = prio1;
    }

    if (subtrack->note_priority < 2) {
        subtrack->note_priority = 2;
    }

    if (subtrack->priority2 < 1) {
        subtrack->note_priority = 1;
    }
}

static u8 Nas_ProgramChanger(sub* subtrack, u8 prog_id, voicetable** inst_pp, env* adsr_env) {
    voicetable* inst_p = ProgToVp(subtrack->bank_id, prog_id);

    if (inst_p == nullptr) {
        *inst_pp = nullptr;
        return 0;
    } else {
        adsr_env->envelope = inst_p->envelope;
        adsr_env->decay_idx = inst_p->adsr_decay_idx;
        *inst_pp = inst_p;

        prog_id += VOICE_TYPE_INSTRUMENT_START;
        return prog_id;
    }
}

static void Nas_SubVoiceSet(sub* subtrack, u8 inst_id) {
    if (inst_id >= 128) {
        /* synth waves */
        subtrack->inst_or_wave = inst_id;
        subtrack->voicetable = nullptr;
    } else if (inst_id == 0x7F) {
        /* percussion */
        subtrack->inst_or_wave = VOICE_TYPE_PERCUSSION;
        subtrack->voicetable = (voicetable*)1;
    } else if (inst_id == 0x7E) {
        /* sound effect */
        subtrack->inst_or_wave = VOICE_TYPE_SOUND_EFF;
        subtrack->voicetable = (voicetable*)2;
    } else {
        u8 inst_or_wave;

        /* instrument */
        inst_or_wave = Nas_ProgramChanger(subtrack, inst_id, &subtrack->voicetable, &subtrack->adsr_env);
        subtrack->inst_or_wave = inst_or_wave;
        if (inst_or_wave == 0) {
            /* failed to load the instrument */
            subtrack->has_instrument = FALSE;
            return;
        }
    }

    subtrack->has_instrument = TRUE;
}

static void Nas_SubVolumeSet(sub* subtrack, u8 volume) {
    subtrack->volume = (f32)(s32)volume / 127.0f;
}

static void Nas_SubSeq(sub* subtrack) {
    u8 cmd;
    u8 cmdArgU8;
    s32 i;
    u8* data;
    group* grp;
    macro* m;
    s16 temp1;
    u16 cmdArgU16;
    u32 cmdArgs[3];
    s8 cmdArgS8;
    u8 lo_bits;
    u8 hi_bits;
    u8* seq_data;
    u32 new_var2;
    s32 new_var3;

    if (subtrack->stop_script == FALSE) {
        grp = subtrack->group;

        if (grp->flags.muted && (subtrack->mute_flags & AUDIO_MUTE_FLAG_STOP_SCRIPT)) {
            return;
        }

        if (subtrack->delay > 1) {
            subtrack->delay--;
        } else {
            /* Sub-Track sequence command process loop */
            while (TRUE) {
                m = &subtrack->macro_player;
                cmd = Nas_ReadByteData(m);
                if (cmd >= 0xA0) {
                    /* Load command arguments */
                    hi_bits = SCOM_TABLE[(u8)cmd - 0xA0];
                    lo_bits = hi_bits & 3;

                    for (i = 0; i < lo_bits; i++) {
                        if ((hi_bits & 0x80) == SCOM_TYPE_U8) {
                            cmdArgs[i] = Nas_ReadByteData(m);
                        } else {
                            cmdArgs[i] = Nas_ReadWordData(m);
                        }

                        hi_bits = hi_bits << 1;
                    }

                    if (cmd >= COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO) {
                        s32 delay = Common_Com(grp, m, cmd, cmdArgs[0]);

                        if (delay != 0) {
                            if (delay == COMMON_SCRIPT_END) {
                                Nas_ReleaseSubTrack(subtrack);
                            } else {
                                subtrack->delay = delay;
                            }

                            break;
                        }
                    } else {
                        switch ((u8)cmd) {
                            case SUBTRACK_CMD_STOP: // stop subtrack seq script
                                subtrack->stop_script = TRUE;
                                goto note_seq;
                            case SUBTRACK_CMD_ALLOC_VOICES: // alloc voices
                                Nas_DeAllocAllVoices(&subtrack->channel_node);
                                Nas_AllocVoices(&subtrack->channel_node, cmdArgs[0] & 0xFF);
                                break;
                            case SUBTRACK_CMD_DEALLOC_VOICES: // dealloc voices
                                Nas_DeAllocAllVoices(&subtrack->channel_node);
                                break;
                            case SUBTRACK_CMD_SET_DYNTBL: // set dynamic table
                                subtrack->dyn_tbl = (unsigned char(*)[][2])&grp->seq_data[(uintptr_t)cmdArgs[0]];
                                break;
                            case SUBTRACK_CMD_JMP_DYNTBL: // jump to entry in dynamic table
                                if (m->value != -1) {
                                    data = (*subtrack->dyn_tbl)[m->value];
                                    cmdArgU16 = (u16)((data[0] << 8) + data[1]);
                                    m->pc = (u8*)&grp->seq_data[(uintptr_t)cmdArgU16];
                                }
                                break;
                            case SUBTRACK_CMD_INIT_INSTRUMENTS: // Load subtrack bank and set instruments
                                cmdArgU8 = cmdArgs[0];
                                if (grp->bank_id != 0xFF) {
                                    cmdArgU16 = AG.map_header[(uintptr_t)grp->seq_id];
                                    lo_bits = Nas_MapHeaderReadByte(cmdArgU16);
                                    cmdArgU8 = Nas_MapHeaderReadByte(cmdArgU16 + lo_bits - cmdArgU8);
                                }

                                if (Nas_SzCacheCheck(BANK_TABLE, CACHE_EITHER, cmdArgU8)) {
                                    subtrack->bank_id = cmdArgU8;
                                }

                                cmdArgs[0] = cmdArgs[1];
                                // fallthrough 0xEB -> 0xC1
                            case SUBTRACK_CMD_VOICE_SET: // Set subtrack voice
                                Nas_SubVoiceSet(subtrack, cmdArgs[0]);
                                break;
                            case SUBTRACK_CMD_LARGE_NOTE_ON: // turn off large notes
                                subtrack->large_notes = FALSE;
                                break;
                            case SUBTRACK_CMD_LARGE_NOTE_OFF: // turn on large notes
                                subtrack->large_notes = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_VOL: // set volume
                                cmdArgU8 = (u8)cmdArgs[0];
                                Nas_SubVolumeSet(subtrack, cmdArgU8);
                                subtrack->changes.flags.volume = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_VOL_SCALE: // set volume scale
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->volume_scale = (f32)(s32)cmdArgU8 / 128.0f;
                                subtrack->changes.flags.volume = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_FREQ_SCALE: // set frequency scale
                                cmdArgU16 = (u16)cmdArgs[0];
                                subtrack->frequency_scale = (f32)(s32)cmdArgU16 / (f32)0x8000;
                                subtrack->changes.flags.frequency_scale = TRUE;
                                break;
                            case SUBTRACK_CMD_LARGE_BEND_PITCH: // large bend pitch
                                cmdArgU8 = (u8)cmdArgs[0];
                                cmdArgU8 += 128;
                                subtrack->frequency_scale = PCENTTABLE[cmdArgU8];
                                subtrack->changes.flags.frequency_scale = TRUE;
                                break;
                            case SUBTRACK_CMD_SMALL_BEND_PITCH: // small bend pitch
                                cmdArgU8 = 128 + (u8)cmdArgs[0];
                                subtrack->frequency_scale = PCENTTABLE2[cmdArgU8];
                                subtrack->changes.flags.frequency_scale = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_PAN: // set pan
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->new_pan = cmdArgU8;
                                subtrack->changes.flags.pan = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_PAN_WEIGHT: // set pan mix/channel weight
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->pan_channel_weight = cmdArgU8;
                                subtrack->changes.flags.pan = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_TRANSPOSITION: // set transposition
                                cmdArgS8 = (s8)cmdArgs[0];
                                subtrack->transposition = cmdArgS8;
                                break;
                            case SUBTRACK_CMD_SET_ENVELOPE: // set envelope
                                cmdArgU16 = (u16)cmdArgs[0];
                                subtrack->adsr_env.envelope = (envdat*)&grp->seq_data[(uintptr_t)cmdArgU16];
#ifdef TARGET_PC
                                pc_swap_envdat_seq(subtrack->adsr_env.envelope);
#endif
                                break;
                            case SUBTRACK_CMD_SET_DECAY_IDX: // set decay index
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->adsr_env.decay_idx = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_VIBRATO_DEPTH: // set vibrato depth
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->vibrato_params.depth_target = cmdArgU8 * 8;
                                subtrack->vibrato_params.depth_start = 0;
                                subtrack->vibrato_params.depth_change_delay = 0;
                                break;
                            case SUBTRACK_CMD_SET_VIBRATO_RATE: // set vibrato rate
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->vibrato_params.rate_target = cmdArgU8 * 32;
                                subtrack->vibrato_params.rate_start = cmdArgU8 * 32;
                                subtrack->vibrato_params.rate_change_delay = 0;
                                break;
                            case SUBTRACK_CMD_SET_VIBRATO_DEPTH_LINEAR: // set vibrato depth linear
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->vibrato_params.depth_start = cmdArgU8 * 8;
                                cmdArgU8 = (u8)cmdArgs[1];
                                subtrack->vibrato_params.depth_target = cmdArgU8 * 8;
                                cmdArgU8 = (u8)cmdArgs[2];
                                subtrack->vibrato_params.depth_change_delay = cmdArgU8 * 16;
                                break;
                            case SUBTRACK_CMD_SET_VIBRATO_RATE_LINEAR: // set vibrato rate linear
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->vibrato_params.rate_start = cmdArgU8 * 32;
                                cmdArgU8 = (u8)cmdArgs[1];
                                subtrack->vibrato_params.rate_target = cmdArgU8 * 32;
                                cmdArgU8 = (u8)cmdArgs[2];
                                subtrack->vibrato_params.rate_change_delay = cmdArgU8 * 16;
                                break;
                            case SUBTRACK_CMD_SET_VIBRATO_DELAY: // set vibrato delay
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->vibrato_params.delay = cmdArgU8 * 16;
                                break;
                            case SUBTRACK_CMD_SET_REVERB_VOL: // set reverb volume
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->target_reverb_vol = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_INSTRUMENT_BANK: // set bank
                                cmdArgU8 = cmdArgs[0];
                                if (grp->bank_id != 0xFF) {
                                    cmdArgU16 = AG.map_header[(uintptr_t)grp->seq_id]; // get offset for bank info for seq
                                    lo_bits = Nas_MapHeaderReadByte(cmdArgU16); // read number of banks
                                    cmdArgU8 = Nas_MapHeaderReadByte(cmdArgU16 + lo_bits - cmdArgU8); // get bank id from inverse?
                                }

                                if (Nas_SzCacheCheck(BANK_TABLE, CACHE_EITHER, cmdArgU8)) {
                                    subtrack->bank_id = cmdArgU8;
                                }
                                break;
                            case SUBTRACK_CMD_WRITE_GROUP_SEQ: // write to sequence script
                                cmdArgU8 = (u8)cmdArgs[0];
                                cmdArgU16 = (u16)cmdArgs[1];
                                seq_data = &grp->seq_data[(uintptr_t)cmdArgU16];
                                seq_data[0] = (u8)m->value + cmdArgU8;
                                break;
                            case SUBTRACK_CMD_MACRO_SUBTRACT: // subtract macro value
                            case SUBTRACK_CMD_MACRO_SET: // set macro value
                            case SUBTRACK_CMD_MACRO_AND: // bit& macro value
                                cmdArgS8 = (s8)cmdArgs[0];
                                if (cmd == SUBTRACK_CMD_MACRO_SUBTRACT) {
                                    m->value -= cmdArgS8;
                                } else if (cmd == SUBTRACK_CMD_MACRO_SET) {
                                    m->value = cmdArgS8;
                                } else {
                                    m->value &= cmdArgS8;
                                }
                                break;
                            case SUBTRACK_CMD_DISABLE_SUBTRACK: // disable subtrack
                                cmdArgU8 = (u8)cmdArgs[0];
                                Nas_ReleaseSubTrack(grp->subtracks[cmdArgU8]);
                                break;
                            case SUBTRACK_CMD_SET_MUTE_FLAGS: // set mute flags
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->mute_flags = cmdArgU8;
                                subtrack->changes.flags.volume = TRUE;
                                break;
                            case SUBTRACK_CMD_MACRO_LOAD_FROM_GROUP_SEQ: // load macro register value from table
                                cmdArgU16 = (u16)cmdArgs[0];
                                m->value = grp->seq_data[(uintptr_t)(cmdArgU16 + m->value)];
                                break;
                            case SUBTRACK_CMD_SET_DYNVAL: // set stored sequence data index
                                cmdArgU16 = (u16)cmdArgs[0];
                                subtrack->dynamic_value = cmdArgU16;
                                break;
                            case SUBTRACK_CMD_WRITE_DYNVAL_TO_GROUP_SEQ: // write u16 into sequence script
                                cmdArgU16 = (u16)cmdArgs[0];
                                seq_data = &grp->seq_data[(uintptr_t)cmdArgU16];
                                seq_data[0] = (subtrack->dynamic_value >> 8) & 0xFF;
                                seq_data[1] = subtrack->dynamic_value & 0xFF;
                                break;
                            case SUBTRACK_CMD_STEREO_PHASE_SET: // stereo phase effects
                                cmdArgU8 = (u8)cmdArgs[0];
                                if (cmdArgU8 & 0x80) {
                                    subtrack->stereo_effects = TRUE;
                                } else {
                                    subtrack->stereo_effects = FALSE;
                                }

                                *(u8*)&subtrack->stereo_phase = cmdArgU8 & 0x7F;
                                break;
                            case SUBTRACK_CMD_SET_NOTE_ALLOC_POLICY: // set note allocation policy
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->note_alloc_policy = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_SUSTAIN: // set sustain
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->adsr_env.sustain = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_REVERB_IDX: // set reverb index
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->reverb_idx = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_DYNTBL_CALL: // dynamic call
                                if (m->value != -1 && m->depth < ARRAY_COUNT(m->stack)) {
                                    data = (*subtrack->dyn_tbl)[m->value];
                                    /* @BUG - missing stack depth bounds check */
                                    m->stack[m->depth++] = m->pc;
                                    cmdArgU16 = (u16)((data[0] << 8) + data[1]);
                                    m->pc = &grp->seq_data[cmdArgU16];
                                }
                                break;
                            case SUBTRACK_CMD_SET_BOOK_OFS: // set book ofs
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->book_ofs = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_ENV_PARAMS_FROM_GROUP_SEQ: //
                                cmdArgU16 = (u16)cmdArgs[0];
                                data = &grp->seq_data[cmdArgU16];
                                subtrack->mute_flags = data[0];
                                subtrack->note_alloc_policy = data[1];
                                Nas_PriorityChanger(subtrack, data[2]);
                                subtrack->transposition = (s8)data[3];
                                subtrack->new_pan = data[4];
                                subtrack->pan_channel_weight = data[5];
                                subtrack->target_reverb_vol = data[6];
                                subtrack->reverb_idx = data[7];
                                /* @BUG - didn't update reverb state as changed */
                                subtrack->changes.flags.pan = TRUE;
                                break;
                            case SUBTRACK_CMD_SET_ENV_PARAMS: //
                                subtrack->mute_flags = cmdArgs[0];
                                subtrack->note_alloc_policy = cmdArgs[1];
                                cmdArgU8 = (u8)cmdArgs[2];
                                Nas_PriorityChanger(subtrack, cmdArgU8);
                                subtrack->transposition = (s8)Nas_ReadByteData(m);
                                subtrack->new_pan = Nas_ReadByteData(m);
                                subtrack->pan_channel_weight = Nas_ReadByteData(m);
                                subtrack->target_reverb_vol = Nas_ReadByteData(m);
                                subtrack->reverb_idx = Nas_ReadByteData(m);
                                /* @BUG - didn't update reverb state as changed */
                                subtrack->changes.flags.pan = TRUE;
                                break;
                            case SUBTRACK_CMD_RESET_VIBRATO: // reset vibrato
                                subtrack->frequency_scale = 1.0f;
                                subtrack->vibrato_params.depth_target = 0;
                                subtrack->vibrato_params.depth_start = 0;
                                subtrack->vibrato_params.depth_change_delay = 0;
                                subtrack->vibrato_params.rate_target = 0;
                                subtrack->vibrato_params.rate_start = 0;
                                subtrack->vibrato_params.rate_change_delay = 0;
                                subtrack->filter = nullptr;
                                subtrack->gain = 0;
                                subtrack->adsr_env.sustain = 0;
                                subtrack->velocity_random_variance = 0;
                                subtrack->gate_time_random_variance = 0;
                                subtrack->comb_filter_size = 0;
                                subtrack->comb_filter_gain = 0;
                                subtrack->book_ofs = 0;
                                subtrack->sample_start_pos = 0;
                                subtrack->_E0 = 0;
                                break;
                            case SUBTRACK_CMD_SET_PRIORITY: // set priority
                                cmdArgU8 = (u8)cmdArgs[0];
                                Nas_PriorityChanger(subtrack, cmdArgU8);
                                break;
                            case SUBTRACK_CMD_SET_GAIN: // set gain
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->gain = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_FILTER: // set filter
                                cmdArgU16 = (u16)cmdArgs[0];
                                data = &grp->seq_data[cmdArgU16];
                                subtrack->filter = (s16*)data;
                                break;
                            case SUBTRACK_CMD_CLEAR_FILTER: // clear filter
                                subtrack->filter = nullptr;
                                break;
                            case SUBTRACK_CMD_LOAD_FILTER: // load filter
                                cmdArgU8 = (u8)cmdArgs[0];
                                if (subtrack->filter != nullptr) {
                                    lo_bits = (cmdArgU8 >> 4) & 0xF;
                                    cmdArgU8 &= 0xF;
                                    Nas_SetBPFilter(subtrack->filter, lo_bits, cmdArgU8);
                                }
                                break;
                            case SUBTRACK_CMD_LOAD_DYNVAL_FROM_GROUP_SEQ: // load dynamic idx
                                cmdArgU16 = (u16)cmdArgs[0];
                                new_var3 = cmdArgU16 + (m->value * 2);
                                subtrack->dynamic_value =
                                    (grp->seq_data[(uintptr_t)new_var3] << 8) | grp->seq_data[(uintptr_t)new_var3 + 1];
                                break;
                            case SUBTRACK_CMD_SET_DYNTBL_FROM_GROUP_SEQ: // set dynamic table
                                subtrack->dyn_tbl = (unsigned char(*)[][2]) & grp->seq_data[subtrack->dynamic_value];
                                break;
                            case SUBTRACK_CMD_LOAD_DYNVAL_FROM_DYNTBL: // read from dynamic table
                                data = (u8*)subtrack->dyn_tbl;
                                new_var3 = m->value * 2;
                                subtrack->dynamic_value = (data[new_var3] << 8) | data[new_var3 + 1];
                                break;
                            case SUBTRACK_CMD_MACRO_LOAD_FROM_DYNTBL: // read to macro register from dynamic table
                                m->value = (*subtrack->dyn_tbl)[0][m->value];
                                break;
                            case SUBTRACK_CMD_RANDOM_DYNVAL: // random dynamic value
                                if (cmdArgs[0] == 0) {
                                    subtrack->dynamic_value = Nap_GetRandom();
                                } else {
                                    subtrack->dynamic_value = Nap_GetRandom() % cmdArgs[0];
                                }
                                break;
                            case SUBTRACK_CMD_MACRO_RANDOM_VAL: // macro register random value
                                if (cmdArgs[0] == 0) {
                                    m->value = Nap_GetRandom();
                                } else {
                                    m->value = Nap_GetRandom() % cmdArgs[0];
                                }
                                break;
                            case SUBTRACK_CMD_SET_VEL_RANDOM_VARIANCE: // set velocity random variance
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->velocity_random_variance = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_GATE_TIME_RANDOM_VARIANCE: // set gate time random variance
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->gate_time_random_variance = cmdArgU8;
                                break;
                            case SUBTRACK_CMD_SET_COMB_FILTER_SIZE_GAIN: // set comb filter size & gain
                                cmdArgU8 = (u8)cmdArgs[0];
                                subtrack->comb_filter_size = cmdArgU8;
                                cmdArgU16 = (u16)cmdArgs[1];
                                subtrack->comb_filter_gain = cmdArgU16;
                                break;
                            case SUBTRACK_CMD_ADD_DYNVAL: // Add to dynamic value
                                subtrack->dynamic_value += cmdArgs[0];
                                break;
                            case SUBTRACK_CMD_DYNVAL_SPECIAL: // Dynamic value bit shift & negate (when s16), differs from OoT and MM
                                new_var2 = (subtrack->dynamic_value & 0x7F);
                                new_var2 |= 0x8000 | ((subtrack->dynamic_value & 0x7FC0) << 1);
                                subtrack->dynamic_value = new_var2;
                                break;
                            case SUBTRACK_CMD_SET_SAMPLE_START_POS: // set sample start pos
                                subtrack->sample_start_pos = cmdArgs[0];
                                break;
                            case SUBTRACK_CMD_MACRO_SET_FROM_CALLBACK: // call custom sequence callback and update macro register value
                                if (cmdArgs[0] <= 4) {
                                    if (AG.seq_callbacks[cmdArgs[0]] != nullptr) {
                                        NA_CALLBACK = AG.seq_callbacks[cmdArgs[0]];
                                        m->value = (*NA_CALLBACK)(m->value, subtrack);
                                    }
                                }
                                break;
                            case SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE: // read from sfx state using macro register value as index
                            case SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE_DYNVAL: // read from sfx state using dynamic value as index
                            case SUBTRACK_CMD_SFX_STATE_SET: // write to sfx state using macro register value as index
                            case SUBTRACK_CMD_SFX_STATE_SET_DYNVAL: // write to sfx state using dynamic value as index
                                if (cmd == SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE || cmd == SUBTRACK_CMD_SFX_STATE_SET) {
                                    cmdArgU16 = cmdArgs[0];
                                } else {
                                    cmdArgU16 = subtrack->dynamic_value;
                                }

                                if (subtrack->sfx_state != nullptr) {
                                    if (cmd == SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE || cmd == SUBTRACK_CMD_MACRO_LOAD_FROM_SFX_STATE_DYNVAL) {
                                        m->value = subtrack->sfx_state[cmdArgU16];
                                    } else {
                                        subtrack->sfx_state[cmdArgU16] = m->value;
                                    }
                                }
                                break;
                            case SUBTRACK_CMD_SURROUND_EFFECT_IDX_SET: // set surround effect index
                                subtrack->surround_effect_idx = cmdArgs[0];
                                break;
                            case SUBTRACK_CMD_MACRO_ADD_SUBTRACK_IDX: // add subtrack index to macro register value
                                m->value += subtrack->subtrack_idx;
                                break;
                            case SUBTRACK_CMD_WRITE_GOUP_SEQ_OFFSET_BY_SUBTRACK: // Set value in sequence data to macro register value plus arg value
                                cmdArgU8 = (u8)cmdArgs[0];
                                cmdArgU16 = (u16)cmdArgs[1];
                                seq_data = &grp->seq_data[(uintptr_t)(cmdArgU16 + subtrack->subtrack_idx)];
                                *seq_data = (u8)m->value + cmdArgU8;
                                break;
                            case SUBTRACK_CMD_MACRO_BIT_MOD: // manipulate macro register value
                                u32 shift = (cmdArgs[0] & 0xF);
                                lo_bits = (m->value & 0x80);
                                new_var2 = (cmdArgs[0] & 0x80);
                                new_var3 = (cmdArgs[0] & 0x40);

                                if (new_var2 == 0) {
                                    cmdArgU8 = m->value << shift;
                                } else {
                                    cmdArgU8 = m->value >> shift;
                                }

                                if (new_var3) {
                                    cmdArgU8 &= (u8)~0x80;
                                    cmdArgU8 |= lo_bits;
                                }

                                m->value = cmdArgU8;
                                break;
                        }
                    }
                    // continue;
                } else if (cmd >= SUBTRACK_CMD_PORT_WRITE_MACRO_REG_MASK) {
                    s32 hi_bits = (cmd & (u8)~7);
                    lo_bits = cmd;
                    lo_bits &= ~0xF8;

                    /* if command is not in range [0x70, 0x77] and the lower 4 bits are >= 4, set them to be 0xY0*/
                    if (hi_bits != SUBTRACK_CMD_PORT_WRITE_MACRO_REG_MASK && lo_bits >= ARRAY_COUNT(subtrack->note_layers)) {
                        lo_bits = 0;
                    }

                    switch (hi_bits) {
                        // [0x80 - 0x83]
                        case SUBTRACK_CMD_READ_NOTE_FINISHED_MASK: // macro register value = subtrack->note_layers[idx]->finished
                            if (subtrack->note_layers[lo_bits] != nullptr) {
                                m->value = subtrack->note_layers[lo_bits]->finished;
                            } else {
                                m->value = -1;
                            }
                            break;
                        // [0x88 - 0x8B]
                        case SUBTRACK_CMD_NOTE_SET_PC_MASK: // start note layer and initialize note macro pc
                            cmdArgU16 = Nas_ReadWordData(m);
                            if (Nas_EntryNoteTrack(subtrack, lo_bits) == 0) {
                                    subtrack->note_layers[lo_bits]->macro_player.pc = &grp->seq_data[(uintptr_t)cmdArgU16];
                            }
                            break;
                        // [0x90 - 0x97] NOTE: 0x94-0x97 are invalid and will be changed to 0x90.
                        case SUBTRACK_CMD_NOTE_STOP_MASK: // stop note layer
                            Nas_CloseNoteTrack(subtrack, lo_bits);
                            break;
                        // [0x98 - 0x9B]
                        case SUBTRACK_CMD_NOTE_START_DYNTBL_MASK: // start note layer and initialize note macro pc from data at macro register offset
                            if (m->value != -1) {
                                if (Nas_EntryNoteTrack(subtrack, lo_bits) != -1) {
                                    data = (*subtrack->dyn_tbl)[m->value];
                                    cmdArgU16 = (u16)((data[0] << 8) + data[1]);
                                    subtrack->note_layers[lo_bits]->macro_player.pc = &grp->seq_data[(uintptr_t)cmdArgU16];
                                }
                            }
                            break;
                        // [0x70 - 0x77]
                        case SUBTRACK_CMD_PORT_WRITE_MACRO_REG_MASK: // write macro register value into subtrack port
                            subtrack->port[lo_bits] = m->value;
                            break;
                        // [0x78 - 0x7B]
                        case SUBTRACK_CMD_NOTE_START_MASK: // start note layer and initialize note macro pc from subtrack pc and rel offset
                            temp1 = Nas_ReadWordData(m);
                            if (Nas_EntryNoteTrack(subtrack, lo_bits) == 0) {
                                subtrack->note_layers[lo_bits]->macro_player.pc = m->pc + temp1;
                            }
                            break;
                    }
                } else {
                    /* Process commands 0x00 - 0x6F */
                    lo_bits = cmd & 0xF; // each command has 16 indicies which come from the lower 4 bits
                    switch (cmd & 0xF0) {
                        // [0x00, 0x0F]
                        case SUBTRACK_CMD_DELAY_MASK: // set delay
                            subtrack->delay = lo_bits;
                            if (lo_bits == 0) {
                                break; /* clear delay, continue processing */
                            } else {
                                goto note_seq; /* delay > 0 so stop processing subtrack commands for now */
                            }
                        // [0x10, 0x17] & [0x18, 0x1F]
                        case SUBTRACK_CMD_VOICELOAD_MASK: // load new wave samples
                            if (lo_bits < 8) {
                                subtrack->port[lo_bits] = -1; // clear port
                                /* Load samples from bank with inst id being macro's register value, load result in
                                 * port[lo_bits] */
                                VoiceLoad(subtrack->bank_id, m->value, &subtrack->port[lo_bits]);
                            } else {
                                lo_bits -= 8;
                                subtrack->port[lo_bits] = -1;
                                /* Load synth? samples based on dynamic value */
                                VoiceLoad(subtrack->bank_id, 0x100 + subtrack->dynamic_value, &subtrack->port[lo_bits]);
                            }
                            break;
                        // [0x60, 0x6F] (only 0x60, 0x67 are valid)
                        case SUBTRACK_CMD_MACRO_READ_PORT0_MASK: // read port value into macro register value
                            m->value = subtrack->port[lo_bits];
                            if (lo_bits < 2) {
                                subtrack->port[lo_bits] = -1;
                            }
                            break;
                        // [0x50, 0x5F] (only 0x50, 0x57 are valid)
                        case SUBTRACK_CMD_MACRO_SUBTRACT_MASK: // subtrack port value from macro register value
                            m->value -= subtrack->port[lo_bits];
                            break;
                        // [0x20, 0x2F]
                        case SUBTRACK_CMD_START_SUBTRACK_MASK: // start subtrack
                            cmdArgU16 = (u16)Nas_ReadWordData(m);
                            Nas_OpenSub(grp, lo_bits, &grp->seq_data[(uintptr_t)cmdArgU16]);
                            break;
                        // [0x30, 0x3F]
                        case SUBTRACK_CMD_WRITE_SUBTRACK_PORT_MASK: // set subtrack port to this subtrack's macro register value
                            cmdArgU8 = Nas_ReadByteData(m);
                            grp->subtracks[lo_bits]->port[cmdArgU8] = m->value;
                            break;
                        // [0x40, 0x4F]
                        case SUBTRACK_CMD_READ_SUBTRACK_PORT_MASK: // set this subtrack's macro register value to other subtrack's port
                            cmdArgU8 = Nas_ReadByteData(m);
                            m->value = grp->subtracks[lo_bits]->port[cmdArgU8];
                            break;
                    }
                }
            }
        }
    }

note_seq:
    for (i = 0; i < ARRAY_COUNT(subtrack->note_layers); i++) {
        if (subtrack->note_layers[i] != nullptr) {
            Nas_NoteSeq(subtrack->note_layers[i]);
        }
    }
}

static void Nas_GroupSeq(group* grp) {
    u8 cmd;
    u8 cmd_lo_bits;
    macro* m;
    s16 tempS;
    u16 temp;
    s32 i;
    s32 value;
    u8* data1;
    u8* data2;
    u8* data3;
    u8* data4;
    s32 tempo_change;
    sub* subtrack;
    s32 delay;
    f32 tempf32;
    s8 argS8;
    s16 argS16;
    u8 argU8;

    if (grp->flags.enabled) {
        if (Nas_CheckIDseq(grp->seq_id) == FALSE || Nas_CheckIDbank(grp->bank_id) == FALSE) {
            Nas_CheckIDseq(grp->seq_id);
            Nas_CheckIDseq(grp->bank_id);
            Nas_ReleaseGroup(grp);
        } else {
            Nas_WriteIDseq(grp->seq_id, LOAD_STATUS_COMPLETE);
            Nas_WriteIDbank(grp->bank_id, LOAD_STATUS_COMPLETE);

            if (grp->flags.muted && (grp->mute_flags & AUDIO_MUTE_FLAG_STOP_SCRIPT)) {
                return;
            }

            grp->script_counter++;
            tempo_change = grp->tempo + grp->tempo_change;
            if (tempo_change > AG.max_tempo) {
                tempo_change = AG.max_tempo;
            }

            grp->tempo_acceleration += tempo_change;
            if (grp->tempo_acceleration < AG.max_tempo) {
                return;
            }

            grp->tempo_acceleration -= (u16)AG.max_tempo;
            grp->counter++;

            if (grp->flags.stop_seq_script == TRUE) {
                return;
            }

            if (grp->delay > 1) {
                grp->delay--;
            } else {
                m = &grp->macro_player;
                grp->flags.recalculate_volume = TRUE;

                /* Sequence group commands processing loop */
                while (TRUE) {
                    cmd = Nas_ReadByteData(m);
                    if (cmd >= COMMON_CMD_BRANCH_REL_NOT_EQ_ZERO) {
                        u16 arg = Convert_Com(m, cmd);
                        delay = Common_Com(grp, m, cmd, arg);

                        if (delay != 0) {
                            /* Group is on delay or script has exited */
                            if (delay == COMMON_SCRIPT_END) {
                                Nas_ReleaseGroup(grp);
                            } else {
                                grp->delay = delay;
                            }

                            break;
                        }
                    } else if (cmd >= 0xC0) {
                        switch (cmd) {
                            case GRP_CMD_RESERVE_VOICES: // reserve voices
                                Nas_DeAllocAllVoices(&grp->channel_node);
                                cmd = Nas_ReadByteData(m);
                                Nas_AllocVoices(&grp->channel_node, (u8)cmd);
                                break;
                            case GRP_CMD_RELEASE_VOICES: // release voices
                                Nas_DeAllocAllVoices(&grp->channel_node);
                                break;
                            case GRP_CMD_TRANSPOSITION_ABSOLUTE: // absolute transposition
                                grp->transposition = 0;
                                // fallthrough 0xDF -> 0xDE
                            case GRP_CMD_TRANSPOSITION_RELATIVE: // relative transposition
                                argU8 = Nas_ReadByteData(m);
                                grp->transposition = grp->transposition + (s8)argU8;
                                break;
                            case GRP_CMD_SET_TEMPO: // set tempo
                                grp->tempo = Nas_ReadByteData(m) * AUDIO_TATUMS_PER_BEAT;
                                if (grp->tempo > AG.max_tempo) {
                                    grp->tempo = AG.max_tempo;
                                }
                                if ((s16)grp->tempo < 1) {
                                    grp->tempo = 1;
                                }
                                break;
                            case GRP_CMD_SET_TEMPO_CHANGE: // adjust tempo relative
                                grp->tempo_change = (s8)Nas_ReadByteData(m) * AUDIO_TATUMS_PER_BEAT;
                                break;
                            case GRP_CMD_CHANGE_VOLUME: // change volume
                                cmd = Nas_ReadByteData(m);
                                temp = Nas_ReadWordData(m);
                                switch (cmd) {
                                    case GROUP_STATE_0:
                                    case GROUP_STATE_FADE_IN:
                                        if (grp->state != GROUP_STATE_FADE_OUT) {
                                            grp->stored_fade_timer = temp;
                                            grp->state = cmd;
                                        }
                                        break;
                                    case GROUP_STATE_FADE_OUT:
                                        grp->fade_timer = temp;
                                        grp->state = cmd;
                                        grp->fade_velocity = -grp->fade_volume / (f32)(s32)grp->fade_timer;
                                        break;
                                }
                                break;
                            case GRP_CMD_SET_VOLUME: // set volume
                                tempf32 = (s32)Nas_ReadByteData(m) / 127.0f;
                                switch (grp->state) {
                                    case GROUP_STATE_FADE_IN:
                                        grp->fade_volume = 0.0f;
                                        grp->state = GROUP_STATE_0;
                                        // fallthrough GROUP_STATE_FADE_IN
                                    case GROUP_STATE_0:
                                        temp = grp->stored_fade_timer;
                                        grp->fade_timer = temp;
                                        if (temp != 0) {
                                            grp->fade_velocity =
                                                (tempf32 - grp->fade_volume) / (f32)(s32)grp->fade_timer;
                                        } else {
                                            grp->fade_volume = tempf32;
                                        }
                                        break;

                                    case GROUP_STATE_FADE_OUT:
                                        break;
                                }
                                break;
                            case GRP_CMD_SET_VOLUME_SCALE: // set volume scale
                                grp->fade_volume_scale = (s8)Nas_ReadByteData(m) / 127.0f;
                                break;
                            case GRP_CMD_ALLOC_SUBTRACKS: // initialize subtracks
                                temp = Nas_ReadWordData(m);
                                Nas_AllocSub(grp, temp);
                                break;
                            case GRP_CMD_DISABLE_SUBTRACKS: // [ineffective] - disable subtracks
                                Nas_ReadWordData(m);
                                break;
                            case GRP_CMD_SET_MUTE_SCALE: // set mute scale
                                grp->mute_volume_scale = (s8)Nas_ReadByteData(m) / 127.0f;
                                break;
                            case GRP_CMD_MUTE: // mute
                                grp->flags.muted = TRUE;
                                break;
                            case GRP_CMD_SET_MUTE_BEHAVIOR: // set mute behaivor
                                grp->mute_flags = Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_SET_SHORT_NOTE_GATE_TIME_TBL: // set short note gate-time table
                            case GRP_CMD_SET_SHORT_NOTE_VELOCITY_TBL: // set short note velocity table
                                temp = Nas_ReadWordData(m);
                                data3 = &grp->seq_data[(uintptr_t)temp];
                                if (cmd == GRP_CMD_SET_SHORT_NOTE_VELOCITY_TBL) {
                                    grp->short_note_velocity_tbl = data3;
                                } else {
                                    grp->short_note_gate_time_tbl = data3;
                                }
                                break;
                            case GRP_CMD_SET_NOTE_ALLOC_POLICY: // set note allocation policy
                                grp->note_alloc_policy = Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_MACRO_VALUE_RANDOM: // set macro register value to random value
                                cmd = Nas_ReadByteData(m);
                                if (cmd == 0) {
                                    /* 0-255 */
                                    m->value = (AG.audio_random_seed >> 2) & 0xFF;
                                } else {
                                    /* 0-N */
                                    m->value = (AG.audio_random_seed >> 2) % cmd;
                                }
                                break;
                            case GRP_CMD_DYN_TBL_CALL: // dynamic look-up table call
                                temp = Nas_ReadWordData(m);
                                if (m->value != -1 && m->depth != 3) {
                                    data1 = &grp->seq_data[(uintptr_t)(temp + (m->value << 1))];
                                    m->stack[m->depth++] = m->pc;
                                    temp = (data1[0] << 8) + data1[1];
                                    m->pc = &grp->seq_data[temp];
                                }
                                break;
                            case GRP_CMD_MACRO_VALUE_LOAD: // set macro register value
                                m->value = Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_MACRO_VALUE_BIT_AND: // macro register bit mask
                                m->value &= Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_MACRO_VALUE_SUBTRACT: // macro register subtraction
                                m->value -= Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_MACRO_VALUE_STORE: // write macro register value to sequence data
                                cmd = Nas_ReadByteData(m);
                                temp = Nas_ReadWordData(m);
                                data2 = &grp->seq_data[(uintptr_t)temp];
                                data2[0] = (u8)m->value + cmd;
                                break;
                            case GRP_CMD_DYNAMIC_BRANCH: // dynamic lookup branch (no return)
                                temp = Nas_ReadWordData(m);
                                if (m->value != -1) {
                                    data4 = &grp->seq_data[(uintptr_t)(temp + (m->value << 1))];
                                    temp = (data4[0] << 8) + data4[1];
                                    m->pc = &grp->seq_data[temp];
                                }
                                break;
                            case GRP_CMD_STOP_SEQ: // stop script
                                grp->flags.stop_seq_script = TRUE;
                                return;
                            case GRP_CMD_UPDATE_COUNTER: // update counter
                                grp->counter = Nas_ReadWordData(m);
                                break;
                            case GRP_CMD_EF: //
                                Nas_ReadWordData(m);
                                Nas_ReadByteData(m);
                                break;
                            case GRP_CMD_START_SEQ: // start sequence script
                                /* Get sequence group index */
                                cmd = Nas_ReadByteData(m);
                                if (cmd == 0xFF) {
                                    cmd = grp->group_idx;
                                }

                                Nas_StartMySeq(cmd, Nas_ReadByteData(m), 0);
                                if (cmd == (u8)grp->group_idx) {
                                    return; // stop processing since we just used this group for a new sequence
                                }
                                break;
                            case GRP_CMD_MUTE_SUBTRACKS: // mute subtracks from u16 bitfield
                                temp = Nas_ReadWordData(m);
                                if (m->value != -1) {
                                    uintptr_t mask_idx = (uintptr_t)temp + (uintptr_t)m->value * 2;
                                    temp = (grp->seq_data[mask_idx] << 8) | grp->seq_data[mask_idx + 1];
                                    for (i = 0; i < (s32)ARRAY_COUNT(grp->subtracks); i++) {
                                        grp->subtracks[i]->muted = temp & 1;
                                        temp = temp >> 1;
                                    }
                                }
                                break;
                        }
                    } else if (cmd == GRP_CMD_CALLBACK) {
                        cmd = Nas_ReadByteData(m);
                        if (cmd <= 4) {
                            if (AG.seq_callbacks[cmd] != nullptr) {
                                NA_GRP_CALLBACK = (GRP_CALLBACK)AG.seq_callbacks[cmd];
                                m->value = (*(GRP_CALLBACK)AG.seq_callbacks[cmd])(m->value, grp);
                            }
                        } else {
                            break;
                        }
                    } else {
                        /* Commands 0x00 - 0xBD & 0xBF */
                        cmd_lo_bits = cmd & 0x0F;
                        switch (cmd & 0xF0) {
                            // [0x00, 0x0F]
                            case GRP_CMD_MACRO_VALUE_LOAD_SUBTRACK_DISABLED_MASK: // macro register value = !subtrack->enabled
                                m->value = grp->subtracks[cmd_lo_bits]->enabled ^ TRUE;
                                break;
                            // [0x50, 0x57] @BUG - ([0x58, 0x5F] end here but would result in undefined behavior)
                            case GRP_CMD_MACRO_VALUE_SUBTRACT_FROM_PORT_MASK: // macro register subtract port value
                                m->value -= grp->port[cmd_lo_bits];
                                break;
                            // [0x70, 0x77] @BUG - ([0x78, 0x7F] end here but would result in undefined behavior)
                            case GRP_CMD_MACRO_VALUE_WRITE_PORT_MASK: // write macro register value into port
                                grp->port[cmd_lo_bits] = m->value;
                                break;
                            // [0x80, 0x87] @BUG - ([0x88, 0x8F] end here but would result in undefined behavior)
                            case GRP_CMD_MACRO_VALUE_READ_PORT_MASK: // read macro register value from port
                                m->value = grp->port[cmd_lo_bits];
                                if (cmd_lo_bits < 2) {
                                    grp->port[cmd_lo_bits] = -1;
                                }
                                break;
                            // [0x40, 0x4F]
                            case GRP_CMD_DISABLE_SUBTRACK_MASK: // disable subtrack
                                Nas_ReleaseSubTrack(grp->subtracks[cmd_lo_bits]);
                                break;
                            // [0x90, 0x9F]
                            case GRP_CMD_START_SUBTRACK_MASK: // start subtrack w/ absolute script address
                                temp = Nas_ReadWordData(m);
                                Nas_OpenSub(grp, cmd_lo_bits, &grp->seq_data[(uintptr_t)temp]);
                                break;
                            // [0xA0, 0xAF]
                            case GRP_CMD_START_RELATIVE_SUBTRACK_MASK: // start subtrack w/ relative script address
                                tempS = Nas_ReadWordData(m);
                                Nas_OpenSub(grp, cmd_lo_bits, &m->pc[tempS]);
                                break;
                            // [0xB0, 0xB7] @BUG - ([0xB8, 0xBF] end here but would result in undefined behavior)
                            case GRP_CMD_SEQ_LOAD_MASK: // load sequence
                                cmd = Nas_ReadByteData(m);
                                temp = Nas_ReadWordData(m);
                                data2 = &grp->seq_data[(uintptr_t)temp];
                                SeqLoad(cmd, data2, &grp->port[cmd_lo_bits]);
                                break;
                            // [0x60, 0x67] @BUG - ([0x68, 0x6F] end here but would result in undefined behavior)
                            case GRP_CMD_ASYNC_LOAD_MASK: // async load
                                cmd = (u8)Nas_ReadByteData(m);
                                argU8 = Nas_ReadByteData(m);
                                MK_load(cmd, argU8, (u8*)&grp->port[cmd_lo_bits]);
                                break;
                        }
                    }
                }
            }

            for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
                subtrack = grp->subtracks[i];
                if (subtrack->enabled) {
                    Nas_SubSeq(subtrack);
                }
            }

        }
    }
}

extern void Nas_MySeqMain(u32 frames_left) {
    group* grp;
    group* main_grp;
    u32 i;

    AG.sample_state_offset = (AG.audio_params.updates_per_frame - (frames_left + 1)) * AG.num_channels;
    for (i = 0; i < AG.audio_params.num_groups; i++) {
        grp = &AG.groups[i];

        if (grp->flags.enabled == TRUE) {
            Nas_GroupSeq(grp);
            Nas_MainCtrl(grp);
        }
    }

    main_grp = &AG.main_group;
    Nas_GroupSeq(main_grp);
    Nas_MainCtrl(main_grp);

    Nas_UpdateChannel();
}

extern void Nas_SeqSkip(group* grp) {
    while (grp->skip_ticks > 0) {
        Nas_GroupSeq(grp);
        Nas_MainCtrl(grp);
        grp->skip_ticks--;
    }
}

extern void Nas_InitMySeq(group* grp) {
    s32 i;

    Nas_ReleaseGroup(grp);
    grp->flags.stop_seq_script = FALSE;
    grp->delay = 0;
    grp->state = GROUP_STATE_FADE_IN;
    grp->fade_timer = 0;
    grp->stored_fade_timer = 0;
    grp->tempo_acceleration = 0;
    grp->tempo = 120 * AUDIO_TATUMS_PER_BEAT;
    grp->tempo_change = 0;
    grp->fade_volume = 1.0f;
    grp->fade_velocity = 0.0f;
    grp->volume = 0.0f;
    grp->mute_volume_scale = 0.5f;
    grp->transposition = 0;
    grp->note_alloc_policy = 0;
    grp->short_note_velocity_tbl = DEFAULT_VTABLE;
    grp->short_note_gate_time_tbl = DEFAULT_GTABLE;
    grp->script_counter = 0;
    grp->counter = 0;

    for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
        Nas_InitSubTrack(grp->subtracks[i]);
    }
}

extern void Nas_AssignSubTrack(s32 group_idx) {
    sub* subtrack;
    group* grp = &AG.groups[group_idx];
    s32 i;
    s32 j;

    for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
        grp->subtracks[i] = (sub*)Nas_HeapAlloc_CL(&AG.misc_heap, sizeof(sub));
        if (grp->subtracks[i] == nullptr) {
            grp->subtracks[i] = &AG.null_sub_track;
        } else {
            subtrack = grp->subtracks[i];
            subtrack->group = grp;
            subtrack->subtrack_idx = i;
            subtrack->enabled = FALSE;

            for (j = 0; j < ARRAY_COUNT(subtrack->note_layers); j++) {
                subtrack->note_layers[j] = nullptr;
            }
        }

        Nas_InitSubTrack(grp->subtracks[i]);
    }
}

static void __InitGroup(group* grp) {
    s32 i;
    s32 j;

    for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
        grp->subtracks[i] = &AG.null_sub_track;
    }

    grp->flags.enabled = FALSE;
    grp->flags.muted = FALSE;
    grp->flags.bank_dma_in_progress = FALSE;
    grp->flags.sequence_dma_in_progress = FALSE;
    grp->flags.apply_bend = FALSE;

    for (j = 0; j < ARRAY_COUNT(grp->port); j++) {
        grp->port[j] = -1;
    }

    grp->mute_flags = AUDIO_MUTE_FLAG_SOFTEN | AUDIO_MUTE_FLAG_STOP_NOTE;
    grp->fade_volume_scale = 1.0f;
    grp->bend = 1.0f;

    Nas_InitChNode(&grp->channel_node);
    Nas_InitMySeq(grp);
}

extern void Nas_InitPlayer(void) {
    group* grp;
    sub* subtrack;
    s32 i;

    Nas_InitNoteList();
    for (i = 0; i < AUDIO_NOTE_MAX; i++) {
        AG.notes[i].sub_track = nullptr;
        AG.notes[i].enabled = FALSE;
    }

    for (i = 0; i < AUDIO_GROUP_MAX; i++) {
        AG.groups_p[i] = &AG.groups[i];
        __InitGroup(&AG.groups[i]);
    }

    grp = &AG.main_group;
    __InitGroup(grp);

    subtrack = &AG.main_sub;
    subtrack->group = grp;
    subtrack->enabled = FALSE;
    for (i = 0; i < ARRAY_COUNT(subtrack->note_layers); i++) {
        subtrack->note_layers[i] = nullptr;
    }
    Nas_InitSubTrack(&AG.main_sub);

    grp->subtracks[0] = &AG.main_sub;
    grp->seq_id = 0xFF;
    grp->bank_id = 0xFF;
    grp->seq_data = BDB_SEQDATA;
    grp->macro_player.pc = BDB_SEQDATA;
    grp->macro_player.depth = 0;
    grp->delay = 0;
    grp->flags.enabled = TRUE;
    grp->flags.finished = FALSE;
    grp->skip_ticks = 0;
}
