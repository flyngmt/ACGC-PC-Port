#include "jaudio_NES/sub_sys.h"

#include "jaudio_NES/system.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/channel.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/os.h"
#include "jaudio_NES/audiomacro.h"
#include "jaudio_NES/driver.h"
#include "dolphin/os.h"

static void __Nas_GroupFadeOut(s32 group, s32 fadeout_timer);
static void __Nas_GroupFadeIn(s32 group, s32 fadein_timer);
static s32 Nap_SilenceCheck_Inner(s32 flags);
static void __SetGrpParam(group* group, AudioPort* port);
static void __SetSubParam(sub* subtrack, AudioPort* port);

static void Nap_AudioSysProcess(AudioPort* port) {
    group* group = AG.groups_p[port->command.arg0];
    s32 i;

    switch (port->command.opcode) {
        case AUDIOCMD_PRELOAD_SEQ:
            Nas_PreLoadSeq(port->command.arg1, port->command.arg2, port->param.asS32, &AG.external_load_queue);
            break;
        case AUDIOCMD_START_SEQ:
            Nas_StartMySeq(port->command.arg0, port->command.arg1, port->command.arg2);
            __Nas_GroupFadeIn(port->command.arg0, port->param.asS32);
            break;
        case AUDIOCMD_START_SEQ_SKIP:
            Nas_StartSeq_Skip(port->command.arg0, port->command.arg1, port->param.asS32);
            Nas_SeqSkip(group);
            break;
        case AUDIOCMD_STOP_SEQ:
            if (group->flags.enabled) {
                if (port->param.asS32 == 0) {
                    Nas_ReleaseGroup_Force(group);
                } else {
                    __Nas_GroupFadeOut(port->command.arg0, port->param.asS32);
                }
            }
            break;
        case AUDIOCMD_SET_SOUND_MODE:
            AG.sound_mode = (s8)port->param.asS32;
            break;
        case AUDIOCMD_MUTE:
            if (port->command.arg0 == AUDIOCMD_ALL_GROUPS) {
                for (i = 0; i < AG.audio_params.num_groups; i++) {
                    AG.groups[i].flags.muted = TRUE;
                    AG.groups[i].flags.recalculate_volume = TRUE;
                }
            } else {
                group->flags.muted = TRUE;
                group->flags.recalculate_volume = TRUE;
            }
            break;
        case AUDIOCMD_UNMUTE:
            if (port->param.asS32 == 1) {
                for (i = 0; i < AG.num_channels; i++) {
                    channel* channel = &AG.channels[i];
                    commonch* common_state = &channel->common_ch;

                    if (common_state->enabled && channel->playback_ch.status == 0 &&
                        (channel->playback_ch.current_parent_note->sub_track->mute_flags &
                         AUDIO_MUTE_FLAG_STOP_SAMPLES)) {
                        common_state->finished = TRUE;
                    }
                }
            }

            if (port->command.arg0 == AUDIOCMD_ALL_GROUPS) {
                for (i = 0; i < AG.audio_params.num_groups; i++) {
                    AG.groups[i].flags.muted = FALSE;
                    AG.groups[i].flags.recalculate_volume = TRUE;
                }
            } else {
                group->flags.muted = FALSE;
                group->flags.recalculate_volume = TRUE;
            }
            break;
        case AUDIOCMD_LOAD_VOICE_INSTRUMENT:
            /* Synchronous load for voice (instrument) */
            Nas_LoadVoice(port->command.arg0, port->command.arg1, port->command.arg2);
            break;
        case AUDIOCMD_PRELOADWAVE_BG:
            /* Async preload wave (samples) */
            Nas_PreLoadWave_BG(port->command.arg0, port->command.arg1, port->command.arg2, &AG.external_load_queue);
            break;
        case AUDIOCMD_PRELOADBANK_BG:
            /* Async preload bank (instrument/sfx/percussion) */
            Nas_PreLoadBank_BG(port->command.arg0, port->command.arg1, port->command.arg2, &AG.external_load_queue);
            break;
        case AUDIOCMD_PRELOADSEQ_BG:
            /* Async preload sequence */
            Nas_PreLoadSeq_BG(port->command.arg0, port->command.arg1, port->command.arg2, &AG.external_load_queue);
            break;
        case AUDIOCMD_FLUSH_BANKS:
            /* Flush instrument banks */
            Nas_FlushBank(port->command.arg1);
            break;
        case AUDIOCMD_SET_GROUP_MASK:
            AG.thread_cmd_group_mask[port->command.arg0] = port->param.asU16;
            break;
        case AUDIOCMD_RESET_AUDIO_HEAP:
            AG.reset_status = 5;
            AG.spec_id = port->param.asU32;
            break;
        case AUDIOCMD_MAIN_GROUP_SUBPORT_CMD:
            if (port->param.asS32 == 0) {
                AG.main_group.subtracks[0]->port[4] = -1;
            } else {
                AG.main_group.subtracks[0]->port[2] = port->command.arg1;
                AG.main_group.subtracks[0]->port[1] = port->command.arg0;
                AG.main_group.subtracks[0]->port[0] = port->command.arg2;
            }
            break;
        case AUDIOCMD_MAIN_GROUP_SET_FREQ_SCALE:
            s32 idx = 128 + port->param.asS32;

            AG.main_group.subtracks[0]->frequency_scale = PCENTTABLE2[idx];
            AG.main_group.subtracks[0]->changes.flags.frequency_scale = TRUE;
            AG.main_group.subtracks[0]->vibrato_params.depth_target = port->command.arg2 * 4;
            AG.main_group.subtracks[0]->vibrato_params.depth_change_delay = 32;
            break;
        case AUDIOCMD_MAIN_GROUP_SET_VOL_SCALE:
            AG.main_group.subtracks[0]->volume_scale = port->param.asF32;
            AG.main_group.subtracks[0]->changes.flags.volume = TRUE;
            break;
        case AUDIOCMD_SET_VFRAME_CALLBACK:
            NA_VFRAME_CALLBACK = (VFRAME_CALLBACK)port->param.asVoidPtr;
            break;
        case AUDIOCMD_SET_CALLBACK:
            if (port->command.arg2 == AUDIO_CALLBACK_SOUND) {
                NA_SOUND_CALLBACK = (SOUND_CALLBACK)port->param.asVoidPtr;
            } else if (port->command.arg2 == AUDIO_CALLBACK_DACOUT) {
                NA_DACOUT_CALLBACK = (DACOUT_CALLBACK)port->param.asVoidPtr;
            } else {
                AG.seq_callbacks[port->command.arg2] = (SequenceCallback)port->param.asVoidPtr;
            }
            break;
        case AUDIOCMD_SET_PERC_BANK:
        case AUDIOCMD_SET_EFFECT_BANK:
        case AUDIOCMD_SET_VOICE_BANK:
            OverwriteBank(port->command.opcode - AUDIOCMD_SET_PERC_BANK, port->command.arg1, port->command.arg2,
                          port->param.asS32);
            break;
        case AUDIOCMD_FORCE_STOP_ALL_GROUPS:
            s32 flags = port->param.asS32;

            if (flags == AUDIO_NOTE_RELEASE) {
                for (i = 0; i < AG.audio_params.num_groups; i++) {
                    if (AG.groups[i].flags.enabled) {
                        Nas_ReleaseGroup_Force(&AG.groups[i]);
                    }
                }
            }

            Nap_SilenceCheck_Inner(flags);
            break;
        case AUDIOCMD_CLEAR_STAY_CACHE:
            Nas_SzStayDelete(port->param.asS32);
            break;
        case AUDIOCMD_SET_EXTERNAL_POINTER:
            Nas_SetExtPointer(port->command.arg0, port->command.arg1, port->command.arg2, port->param.asS32);
            break;
        case AUDIOCMD_SET_DELAY_LINE_PARAM:
            Nas_SetDelayLineParam(port->command.arg1, port->command.arg0, port->param.asS32, FALSE);
            break;
        default:
            break;
    }
}

static void __Nas_GroupFadeOut(s32 groupId, s32 fadeout_time) {
    group* group = AG.groups_p[groupId];

    if (fadeout_time == 0) {
        fadeout_time = 1;
    }

    group->fade_velocity = -(group->fade_volume / (f32)fadeout_time);
    group->state = GROUP_STATE_FADE_OUT;
    group->fade_timer = fadeout_time;
}

static void __Nas_GroupFadeIn(s32 groupId, s32 fadein_time) {

    if (fadein_time != 0) {
        group* group = AG.groups_p[groupId];
        group->fade_volume = 0.0f;
        group->fade_velocity = 0.0f;
        group->state = GROUP_STATE_FADE_IN;
        group->stored_fade_timer = fadein_time;
        group->fade_timer = fadein_time;
    }
}

extern void Nap_AudioPortInit(void) {
    AG.thread_cmd_write_pos = 0;
    AG.thread_cmd_read_pos = 0;
    AG.thread_cmd_queue_finished = FALSE;

    AG.task_start_mq_p = &AG.task_start_mq;
    AG.thread_cmd_proc_mq_p = &AG.thread_cmd_proc_mq;
    AG.spec_change_mq_p = &AG.spec_change_mq;

    Z_osCreateMesgQueue(AG.task_start_mq_p, AG.task_start_msg_buf, ARRAY_COUNT(AG.task_start_msg_buf));
    Z_osCreateMesgQueue(AG.thread_cmd_proc_mq_p, AG.thread_cmd_proc_msg_buf, ARRAY_COUNT(AG.thread_cmd_proc_msg_buf));
    Z_osCreateMesgQueue(AG.spec_change_mq_p, AG.spec_change_msg_buf, ARRAY_COUNT(AG.spec_change_msg_buf));
    AG.spec_change_mq_p->validCount;
}

static void Nap_PortSet(u32 data, s32* param_p) {
    AudioPort* port_p = &AG.audio_port_cmds[AG.thread_cmd_write_pos & 0xFF];

    port_p->raw_cmd = data;
#ifdef TARGET_PC
    port_p->param.asVoidPtr = NULL; /* Clear full pointer-width before writing 4-byte param */
#endif
    port_p->param.asS32 = *param_p;

    AG.thread_cmd_write_pos++;
    if (AG.thread_cmd_write_pos == AG.thread_cmd_read_pos) {
        AG.thread_cmd_write_pos--;
    }
}

extern void Nap_SetF32(u32 cmd, f32 param) {
    Nap_PortSet(cmd, (s32*)&param);
}

extern void Nap_SetS32(u32 cmd, s32 param) {
    Nap_PortSet(cmd, (s32*)&param);
}

#ifdef TARGET_PC
extern void Nap_SetPtr(u32 cmd, void* ptr) {
    AudioPort* port_p = &AG.audio_port_cmds[AG.thread_cmd_write_pos & 0xFF];

    port_p->raw_cmd = cmd;
    port_p->param.asVoidPtr = ptr;

    AG.thread_cmd_write_pos++;
    if (AG.thread_cmd_write_pos == AG.thread_cmd_read_pos) {
        AG.thread_cmd_write_pos--;
    }
}
#endif

extern void Nap_SetS8(u32 cmd, s8 param) {
    u32 mod_param;
#ifdef TARGET_PC
    /* AudioPort.param is read through asS8/asU8 on LE, so keep value in low byte. */
    mod_param = (u8)param;
#else
    mod_param = (param << 24);
#endif

    Nap_PortSet(cmd, (s32*)&mod_param);
}

extern void Nap_SetU16(u32 cmd, u16 param) {
    u32 mod_param;
#ifdef TARGET_PC
    /* AudioPort.param is read through asU16 on LE, so keep value in low 16 bits. */
    mod_param = param;
#else
    mod_param = (param << 16);
#endif

    Nap_PortSet(cmd, (s32*)&mod_param);
}

extern s32 Nap_SendStart(void) {
    static u8 worst = 0;
    s32 msg;
    s32 res;

    if (AUDIO_SYSTEM_READY != TRUE) {
        return -1;
    }

    msg = ((AG.thread_cmd_read_pos & 0xFF) << 8) | (AG.thread_cmd_write_pos & 0xFF);
    res = Z_osSendMesg(AG.thread_cmd_proc_mq_p, (OSMesg)msg, OS_MESG_NOBLOCK);

    if (res != -1) {
        AG.thread_cmd_read_pos = AG.thread_cmd_write_pos;
    } else {
        OSReport("SendStart::Mesg Full Queue\n");
        return -1;
    }

    return 0;
}

extern void Nap_FlushPort(void) {
    AG.thread_cmd_read_pos = AG.thread_cmd_write_pos;
    AG.thread_cmd_queue_finished = FALSE;
}

#define AUDIOCMD_GRP_PARAM_MASK 0x40
#define AUDIOCMD_SYS_SEQ_MASK 0x80
#define AUDIOCMD_SYS_MASK 0xF0

extern void Nap_Process1Command(AudioPort* port) {
    group* group;
    u16 mask;
    s32 i;
    if ((port->command.opcode & AUDIOCMD_SYS_MASK) >= AUDIOCMD_SET_PERC_BANK) {
        Nap_AudioSysProcess(port);
    } else if (port->command.arg0 < AG.audio_params.num_groups) {
        group = AG.groups_p[port->command.arg0];

        if ((port->command.opcode & AUDIOCMD_SYS_SEQ_MASK) != 0) {
            Nap_AudioSysProcess(port);
        } else if ((port->command.opcode & AUDIOCMD_GRP_PARAM_MASK) != 0) {
            __SetGrpParam(group, port);
        } else if (port->command.arg1 < AUDIO_SUBTRACK_NUM) {
            __SetSubParam(group->subtracks[port->command.arg1], port);
        } else if (port->command.arg1 == AUDIOCMD_ALL_SUBTRACKS) {
            mask = AG.thread_cmd_group_mask[port->command.arg0];

            /* Apply to all active subtracks */
            for (i = 0; i < AUDIO_SUBTRACK_NUM; i++) {
                if ((mask & 1)) {
                    __SetSubParam(group->subtracks[i], port);
                }

                mask = mask >> 1;
            }
        }
    }
}

extern void Nap_AudioPortProcess(u32 msg) {
    static u8 begin = 0;

    if (AG.thread_cmd_queue_finished == FALSE) {
        begin = (msg >> 8) & 0xFF;
    }

    while (TRUE) {
        u32 now = begin;
        AudioPort* port;

        if (now == (msg & 0xFF)) {
            AG.thread_cmd_queue_finished = FALSE;
            return;
        }

        port = &AG.audio_port_cmds[now];
        begin++;
        if (port->command.opcode == AUDIOCMD_SYS_STOP_PROCESSING) {
            AG.thread_cmd_queue_finished = TRUE;
            break;
        }

        Nap_Process1Command(port);
        port->command.opcode = AUDIOCMD_NOOP;
    }
}

extern s32 Nap_CheckSpecChange(void) {
    s32 msg;
    s32 res;

    /* Spec-change is not complete until reset pipeline fully settles. */
    if (AG.reset_status != 0) {
        return 0;
    }

    res = Z_osRecvMesg(AG.spec_change_mq_p, (OSMesg*)&msg, OS_MESG_NOBLOCK);

    if (res == -1) {
        return 0;
    } else if (msg != AG.spec_id) {
        return -1;
    } else {
        return 1;
    }
}

static void __ClearSpecChangeQ(void) {
    s32 msg;
    s32 res;

    do {
        res = Z_osRecvMesg(AG.spec_change_mq_p, (OSMesg*)&msg, OS_MESG_NOBLOCK);
    } while (res != -1);
}

extern s32 Nap_StartSpecChange(s32 spec_id) {
    s32 reset_status;
    OSMesg msg;
    s32 res;

    __ClearSpecChangeQ();
    reset_status = AG.reset_status;

    if (reset_status != 0) {
        Nap_FlushPort();
        if (AG.spec_id == spec_id) {
            return -2;
        }

        if (reset_status >= 3) {
            AG.spec_id = spec_id & 0xFF;
            return -3;
        }

#ifndef TARGET_PC
        Z_osRecvMesg(AG.spec_change_mq_p, &msg, OS_MESG_BLOCK);
#endif
    }

    __ClearSpecChangeQ();
    AUDIOCMD_RESET_AUDIO_HEAP_CMD(spec_id);
    return Nap_SendStart();
}

extern s32 Nap_StartReset(void) {
    AG.reset_timer = 1;
    if (AUDIO_SYSTEM_READY) {
        Nap_StartSpecChange(0);
        AG.reset_status = 0;
    }

    return 0;
}

extern s8 Nap_ReadSubPort(s32 groupId, s32 subtrackId, s32 portId) {
    group* group = AG.groups_p[groupId];
    if (group == NULL) {
        return -1;
    }

    if (group->flags.enabled) {
        return group->subtracks[subtrackId]->port[portId];
    }

    return -1;
}

extern s8 Nap_ReadGrpPort(s32 groupId, s32 portId) {
    return AG.groups_p[groupId]->port[portId];
}

static void __SetGrpParam(group* group, AudioPort* port) {
    f32 fade_vol;

    switch (port->command.opcode) {
        case AUDIOCMD_OP_GRP_FADE_VOLUME_SCALE:
            if (group->fade_volume_scale != port->param.asF32) {
                group->fade_volume_scale = port->param.asF32;
                group->flags.recalculate_volume = TRUE;
            }
            break;
        case AUDIOCMD_OP_GRP_SET_TEMPO:
            group->tempo = port->param.asS32 * AUDIO_TATUMS_PER_BEAT;
            break;
        case AUDIOCMD_OP_GRP_CHANGE_TEMPO:
            group->tempo_change = port->param.asS32 * AUDIO_TATUMS_PER_BEAT;
            break;
        case AUDIOCMD_OP_GRP_CHANGE_TEMPO_TICKS:
            group->tempo_change = port->param.asS32;
            break;
        case AUDIOCMD_OP_GRP_SET_TRANSPOSITION:
            group->transposition = port->param.asS8;
            break;
        case AUDIOCMD_OP_GRP_SET_PORT:
            group->port[port->command.arg2] = port->param.asS8;
            break;
        case AUDIOCMD_OP_GRP_FADE_TO_SET_VOLUME:
            fade_vol = (s32)port->command.arg1 / 127.0f;
            goto apply_fade;
        case AUDIOCMD_OP_GRP_FADE_TO_SCALED_VOLUME:
            fade_vol = ((s32)port->command.arg1 / 100.0f) * group->fade_volume;

        /* dev chose to make this a goto label */
        apply_fade:
            if (group->state != GROUP_STATE_FADE_OUT) {
                group->volume = group->fade_volume;
                if (port->param.asS32 == 0) {
                    group->fade_volume = fade_vol;
                } else {
                    s32 fade_timer = port->param.asS32;

                    group->fade_velocity = (fade_vol - group->fade_volume) / fade_timer;
                    group->state = GROUP_STATE_0;
                    group->fade_timer = fade_timer;
                }
            }
            break;
        case AUDIOCMD_OP_GRP_RESET_VOLUME:
            if (group->state != GROUP_STATE_FADE_OUT) {
                if (port->param.asS32 == 0) {
                    group->fade_volume = group->volume;
                } else {
                    s32 fade_timer = port->param.asS32;

                    group->fade_velocity = (group->volume - group->fade_volume) / fade_timer;
                    group->state = GROUP_STATE_0;
                    group->fade_timer = fade_timer;
                }
            }
            break;
        case AUDIOCMD_OP_GRP_SET_BEND:
            group->bend = port->param.asF32;
            if (group->bend == 1.0f) {
                group->flags.apply_bend = FALSE;
            } else {
                group->flags.apply_bend = TRUE;
            }
            break;
        default:
            break;
    }
}

static void __SetSubParam(sub* subtrack, AudioPort* port) {
    u8 filter_cutoff;

    switch (port->command.opcode) {
        case AUDIOCMD_OP_SUB_SET_VOL_SCALE:
            if (subtrack->volume_scale != port->param.asF32) {
                subtrack->volume_scale = port->param.asF32;
                subtrack->changes.flags.volume = TRUE;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_VOL:
            if (subtrack->volume != port->param.asF32) {
                subtrack->volume = port->param.asF32;
                subtrack->changes.flags.volume = TRUE;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_PAN:
            if (subtrack->new_pan != port->param.asS8) {
                subtrack->new_pan = port->param.asS8;
                subtrack->changes.flags.pan = TRUE;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_PAN_WEIGHT:
            if (subtrack->new_pan != port->param.asS8) {
                subtrack->pan_channel_weight = port->param.asS8;
                subtrack->changes.flags.pan = TRUE;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_FREQ_SCALE:
            if (subtrack->frequency_scale != port->param.asF32) {
                subtrack->frequency_scale = port->param.asF32;
                subtrack->changes.flags.frequency_scale = TRUE;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_REVERB_VOLUME:
            if (subtrack->target_reverb_vol != port->param.asS8) {
                subtrack->target_reverb_vol = port->param.asS8;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_REVERB_INDEX:
            if (subtrack->reverb_idx != port->param.asS8) {
                subtrack->reverb_idx = port->param.asS8;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_SURROUND_EFFECT_INDEX:
            subtrack->surround_effect_idx = port->param.asS8;
            break;
        case AUDIOCMD_OP_SUB_SET_PORT:
            if (port->command.arg2 < ARRAY_COUNT(subtrack->port)) {
                subtrack->port[port->command.arg2] = port->param.asS8;
            }
            break;
        case AUDIOCMD_OP_SUB_SET_MUTE:
            subtrack->muted = port->param.asS8;
            break;
        case AUDIOCMD_OP_SUB_SET_MUTE_FLAGS:
            subtrack->mute_flags = port->param.asS8;
            break;
        case AUDIOCMD_OP_SUB_SET_VIBRATO_DEPTH:
            subtrack->vibrato_params.depth_target = port->param.asU8 * 8;
            subtrack->vibrato_params.depth_change_delay = 1;
            break;
        case AUDIOCMD_OP_SUB_SET_VIBRATO_RATE:
            subtrack->vibrato_params.rate_target = port->param.asU8 * 32;
            subtrack->vibrato_params.rate_change_delay = 1;
            break;
        case AUDIOCMD_OP_SUB_SET_COMB_FILTER_SIZE:
            subtrack->comb_filter_size = port->param.asU8;
            break;
        case AUDIOCMD_OP_SUB_SET_COMB_FILTER_GAIN:
            subtrack->comb_filter_gain = port->param.asU16;
            break;
        case AUDIOCMD_OP_SUB_SET_STEREO:
            *(u8*)&subtrack->stereo_phase = port->param.asU8;
            break;
        case AUDIOCMD_OP_SUB_SET_SET_START_POS:
            subtrack->sample_start_pos = port->param.asS32;
            break;
        case AUDIOCMD_OP_SUB_SET_SFX_STATE:
            subtrack->sfx_state = (u8*)port->param.asVoidPtr;
            break;
        case AUDIOCMD_OP_SUB_SET_FILTER:
            filter_cutoff = port->command.arg2;
            if (port->param.asS32 != 0) {
                subtrack->filter = (s16*)port->param.asVoidPtr;
            }

            if (subtrack->filter != nullptr) {
                Nas_SetBPFilter(subtrack->filter, filter_cutoff >> 4, filter_cutoff & 0xF);
            }
            break;
        case AUDIOCMD_OP_SUB_SET_GAIN:
            subtrack->gain = port->param.asU8;
            break;
        case AUDIOCMD_OP_SUB_SET_TRANSPOSITION:
            subtrack->transposition = port->param.asU8;
            break;
        default:
            break;
    }
}

extern void Nap_WaitVsync(void) {
#ifdef TARGET_PC
    /* On PC, audio runs synchronously on the main thread.
       Blocking on task_start_mq would deadlock since no separate
       audio thread is posting messages. */
    return;
#else
    Z_osRecvMesg(AG.task_start_mq_p, (OSMesg*)0, OS_MESG_NOBLOCK);
    Z_osRecvMesg(AG.task_start_mq_p, (OSMesg*)0, OS_MESG_BLOCK);
#endif
}

static s32 Nap_SilenceCheck_Inner(s32 flags) {
    playbackch* playback_chan;
    commonch* common_chan;
    s32 i;
    s32 channelCount;
    channel* channel;
    wtstr* tuned_sample;

    channelCount = 0;
    for (i = 0; i < AG.num_channels; i++) {
        channel = &AG.channels[i];
        playback_chan = &channel->playback_ch;
        if (channel->common_ch.enabled) {
            common_chan = &channel->common_ch;
            if (playback_chan->adsr_envp.state.flags.status != ADSR_STATUS_DISABLED) {
                if (flags >= AUDIO_NOTE_SAMPLE_NOTES) {
                    tuned_sample = common_chan->tuned_sample;
                    if ((tuned_sample == nullptr) || common_chan->is_synth_wave) {
                        continue;
                    }

                    if (tuned_sample->wavetable->medium == MEDIUM_RAM) {
                        continue;
                    }
                }

                if ((flags & AUDIO_NOTE_RELEASE) == AUDIO_NOTE_RELEASE) {
                    playback_chan->adsr_envp.fadeout_velocity = AG.audio_params.updates_per_frame_inverse;
                    playback_chan->adsr_envp.state.flags.release = TRUE;
                }

                channelCount++;
            }
        }
    }
    return channelCount;
}

extern u32 Nap_GetRandom(void) {
    static u32 get = 0x12345678;
    static u32 oldGetCount = 0x11111111;
    u32 tick = OSGetTick();

    get = (get + AG.frame_audio_task_count + tick) * (AG.audio_random_seed + 0x01234567);
    get = (get << 1) + oldGetCount + (get & 1);
    oldGetCount = tick;
    return get;
}

extern void Nas_InitGAudio(void) {
    Nap_AudioPortInit();
}

extern s32 CreateAudioTask(Acmd* cmds, s16* pSamples, u32 nSamples, s32 param_4) {
    s32 i;
    s32 max;

    AG.audio_random_seed = (AG.audio_random_seed + AG.frame_audio_task_count) * OSGetTick();
    AG.frame_audio_task_count++;

    Z_osSendMesg(AG.task_start_mq_p, (OSMesg)AG.frame_audio_task_count, OS_MESG_NOBLOCK);

    if (NA_VFRAME_CALLBACK != nullptr) {
        (*NA_VFRAME_CALLBACK)();
    }

    for (i = 0; i < AG.current_frame_dma_count; i++) {
        Z_osRecvMesg(&AG.cur_audio_frame_dma_queue, nullptr, OS_MESG_NOBLOCK);
    }

    max = AG.cur_audio_frame_dma_queue.validCount;
    if (max != 0) {
        for (i = 0; i < max; i++) {
            Z_osRecvMesg(&AG.cur_audio_frame_dma_queue, nullptr, OS_MESG_NOBLOCK);
        }
    }

    AG.current_frame_dma_count = 0;
    Nas_WaveDmaFrameWork();
    Nas_BgDmaFrameWork(AG.reset_status);
    MK_FrameWork();

    if (AG.reset_status != 0 && Nas_SpecChange() == 0) {
        if (AG.reset_status == 0) {
            Z_osSendMesg(AG.spec_change_mq_p, (OSMesg)AG.spec_id, OS_MESG_NOBLOCK);
        }

        return 0;
    } else if (AG.reset_timer > 16) {
        return 0;
    } else {
        s32 port_cmds;
        s32 processed_cmds;

        if (AG.reset_timer != 0) {
            AG.reset_timer++;
        }

        port_cmds = 0;
        if (AG.reset_status == 0) {
            u32 msg;

            while (Z_osRecvMesg(AG.thread_cmd_proc_mq_p, (OSMesg*)&msg, OS_MESG_NOBLOCK) != -1) {
                Nap_AudioPortProcess(msg);
                port_cmds++;
            }

            if (port_cmds == 0 && AG.thread_cmd_queue_finished) {
                Nap_SendStart();
            }
        }

        Nas_smzAudioFrame(cmds, &processed_cmds, pSamples, nSamples);

        return processed_cmds;
    }
}
