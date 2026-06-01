#include "jaudio_NES/channel.h"

#include "jaudio_NES/system.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/os.h"
#include "jaudio_NES/effect.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/audioheaders.h"
#include <dolphin/os.h>

static void Nas_smzSetPitch(channel* chan, f32 pitch);
static void Nas_AddListHead(link* list, link* l);

static void Nas_smzSetParam(channel* chan, drvparam* param) {
    f32 volL;
    f32 volR;
    s32 strongL;
    s32 strongR;
    s32 halfPanIdx;
    f32 velocity;
    u8 pan;
    u8 panScale;
    u8 reverbVol;
    phase stereoPhase;
    s32 phaseEffects;

    phaseEffects = chan->playback_ch.stereo_headset_effects;
    Nas_smzSetPitch(chan, param->playback.pitch);

    velocity = param->playback.velocity;
    pan = param->playback.pan;
    reverbVol = param->playback.target_reverb_volume;
    stereoPhase = param->playback.stereo_phase;
    panScale = pan & 0x7F;
    chan->common_ch.strong_right = FALSE;
    chan->common_ch.strong_left = FALSE;
    chan->common_ch.strong_reverb_right = stereoPhase.strong_reverb_right;
    chan->common_ch.strong_reverb_left = stereoPhase.strong_reverb_left;


    if (phaseEffects && AG.sound_mode == SOUND_OUTPUT_HEADSET) {
        halfPanIdx = panScale >> 1;
        if (halfPanIdx > 0x3F) {
            halfPanIdx = 0x3F;
        }

        chan->common_ch.haas_effect_right_delay_size = CDELAYTABLE[halfPanIdx];
        chan->common_ch.haas_effect_left_delay_size = CDELAYTABLE[0x3F - halfPanIdx];
        chan->common_ch.use_haas_effect = TRUE;

        volL = PhoneLeft[panScale];
        volR = PhoneLeft[0x7F - panScale];
    } else if (phaseEffects && AG.sound_mode == SOUND_OUTPUT_STEREO) {
        strongL = strongR = FALSE;
        chan->common_ch.haas_effect_left_delay_size = 0;
        chan->common_ch.haas_effect_right_delay_size = 0;
        chan->common_ch.use_haas_effect = FALSE;
        volL = WideLeft[panScale];
        volR = WideLeft[0x7F - panScale];

        if (panScale < 0x20) {
            strongL = TRUE;
        } else if (panScale > 0x60) {
            strongR = TRUE;
        }

        chan->common_ch.strong_right = strongR;
        chan->common_ch.strong_left = strongL;

        switch (stereoPhase.type) {
            case PHASE_TYPE_0:
                break;
            case PHASE_TYPE_1:
                chan->common_ch.strong_right = stereoPhase.strong_right;
                chan->common_ch.strong_left = stereoPhase.strong_left;
                break;
            case PHASE_TYPE_2:
                chan->common_ch.strong_right = strongR | stereoPhase.strong_right;
                chan->common_ch.strong_left = strongL | stereoPhase.strong_left;
                break;
            case PHASE_TYPE_3:
                chan->common_ch.strong_right = strongR ^ stereoPhase.strong_right;
                chan->common_ch.strong_left = strongL ^ stereoPhase.strong_left;
                break;
        }
    } else {
        switch (AG.sound_mode) {
            case SOUND_OUTPUT_MONO:
                chan->common_ch.strong_reverb_right = FALSE;
                chan->common_ch.strong_reverb_left = FALSE;
                volL = 0.707f;
                volR = 0.707f;
                break;
            default:
                chan->common_ch.strong_right = stereoPhase.strong_right;
                chan->common_ch.strong_left = stereoPhase.strong_left;
                volL = StereoLeft[panScale];
                volR = StereoLeft[0x7F - panScale];
                break;
        }
    }

    if (velocity < 0.0f) {
        velocity = 0.0f;
    }

    if (velocity > 1.0f) {
        velocity = 1.0f;
    }
    
    chan->common_ch.target_volume_left = (s32)((velocity * volL) * (0x1000 - 0.001f));
    chan->common_ch.target_volume_right = (s32)((velocity * volR) * (0x1000 - 0.001f));

    chan->common_ch.gain = param->playback.gain;
    chan->common_ch.filter = param->playback.filter_buf;
    chan->common_ch.comb_filter_size = param->comb_filter_size;
    chan->common_ch.comb_filter_gain = param->comb_filter_gain;
    chan->common_ch.target_reverb_volume = reverbVol;
    chan->common_ch.surround_effect_idx = param->playback.surround_effect_idx;
}

static void Nas_smzSetPitch(channel* chan, f32 pitch) {
    f32 rate = 0.0f;

    if (pitch < 2.0f) {
        chan->common_ch.has_two_parts = FALSE;
        if (pitch > 1.99998f) {
            rate = 1.99998f;
        } else {
            rate = pitch;
        }
    } else {
        chan->common_ch.has_two_parts = TRUE;
        if (pitch > 3.99996f) {
            rate = 1.99998f;
        } else {
            rate = pitch / 2.0f;
        }
    }

    chan->common_ch.frequency_fixed_point = (s32)(rate * 32768.0f);
}

extern void Nas_StartVoice(channel* chan) {
    if (chan->playback_ch.current_parent_note->adsr_env.decay_idx == 0) {
        Nas_EnvInit(&chan->playback_ch.adsr_envp, chan->playback_ch.current_parent_note->sub_track->adsr_env.envelope, &chan->playback_ch.adsr_volume_scale_unused);
    } else {
        Nas_EnvInit(&chan->playback_ch.adsr_envp, chan->playback_ch.current_parent_note->adsr_env.envelope, &chan->playback_ch.adsr_volume_scale_unused);
    }

    chan->playback_ch.status = 0;
    chan->playback_ch.adsr_envp.state.flags.status = ADSR_STATUS_INITIAL;
    chan->common_ch = NA_SVCINIT_TABLE[0];
}

extern void Nas_StopVoice(channel* chan) {
    if (chan->common_ch.needs_init == TRUE) {
        chan->common_ch.needs_init = FALSE;
    }

    chan->common_ch.enabled = FALSE;
    chan->common_ch.finished = FALSE;
    chan->playback_ch.priority = 0;
    chan->playback_ch.status = 0;
    chan->playback_ch.current_parent_note = NA_NO_NOTE;
    chan->playback_ch.previous_parent_note = NA_NO_NOTE;
    chan->playback_ch.adsr_envp.state.flags.status = ADSR_STATUS_DISABLED;
    chan->playback_ch.adsr_envp.current = 0;
}

// TODO: this needs to be checked to see if we can cleanup the control flow,
// the excessive gotos may be unnecessary
extern void Nas_UpdateChannel(void) {
    playbackparams* main_param_p;
    channel* chan;
    commonch* common_chan;
    playbackch* playback_chan;
    drvparam param;
    u8 bookOfs;
    f32 scale;
    s32 i;

    for (i = 0; i < AG.num_channels; i++) {
        chan = &AG.channels[i];
        playback_chan = &chan->playback_ch;

        if (playback_chan->current_parent_note != NA_NO_NOTE) {

            if (chan != playback_chan->current_parent_note->channel && playback_chan->status == 0) {
                playback_chan->adsr_envp.state.flags.release = TRUE;
                playback_chan->adsr_envp.fadeout_velocity = AG.audio_params.updates_per_frame_inverse;
                playback_chan->priority = 1;
                playback_chan->status = 2;
                goto skip;
            } else if (!playback_chan->current_parent_note->enabled && playback_chan->status == 0 && playback_chan->priority != 0) {
                // nothing
            } else if (playback_chan->current_parent_note->sub_track->group == NULL) {
                Nas_ReleaseSubTrack(playback_chan->current_parent_note->sub_track);
                playback_chan->priority = 1;
                playback_chan->status = 1;
                continue;
            } else if ((!playback_chan->current_parent_note->sub_track->muted && (!playback_chan->current_parent_note->sub_track->group->flags.muted || (playback_chan->current_parent_note->sub_track->mute_flags & AUDIO_MUTE_FLAG_STOP_NOTE) == 0))) {
                goto skip;
            }

            Nas_Release_Channel_Force(playback_chan->current_parent_note);
            Nas_CutList(&chan->link);
            Nas_AddListHead(&chan->link.pNode->releaseList, &chan->link);
            playback_chan->priority = 1;
            playback_chan->status = 2;
            goto skip;
        } else if (playback_chan->status == 0) {
            if (playback_chan->priority != 0) {
                continue;
            } else {
                goto skip;
            }
        } else {
            goto skip;
        }

    step2:
        {
            common_chan = &chan->common_ch;

            if (playback_chan->status >= 1 || common_chan->finished) {
                if (playback_chan->adsr_envp.state.flags.status == ADSR_STATUS_DISABLED || common_chan->finished) {
                    if (playback_chan->wanted_parent_note != NA_NO_NOTE) {
                        Nas_StopVoice(chan);

                        if (playback_chan->wanted_parent_note->sub_track != NULL) {
                            Nas_EntryTrack(chan, playback_chan->wanted_parent_note);
                            Nas_ChannelModInit(chan);
                            Nas_SweepInit(chan);
                            Nas_CutList(&chan->link);
                            Nas_AddList(&chan->link.pNode->useList, &chan->link);
                            playback_chan->wanted_parent_note = NA_NO_NOTE;
                        } else {
                            Nas_StopVoice(chan);
                            Nas_CutList(&chan->link);
                            Nas_AddList(&chan->link.pNode->freeList, &chan->link);
                            playback_chan->wanted_parent_note = NA_NO_NOTE;
                            continue;
                        }
                    } else {
                        if (playback_chan->current_parent_note != NA_NO_NOTE) {
                            playback_chan->current_parent_note->continuous_channel_released = TRUE;
                        }

                        Nas_StopVoice(chan);
                        Nas_CutList(&chan->link);
                        Nas_AddList(&chan->link.pNode->freeList, &chan->link);
                        continue;
                    }
                }
            } else if (playback_chan->adsr_envp.state.flags.status == ADSR_STATUS_DISABLED) {
                if (playback_chan->current_parent_note != NA_NO_NOTE) {
                    playback_chan->current_parent_note->continuous_channel_released = TRUE;
                }

                Nas_StopVoice(chan);
                Nas_CutList(&chan->link);
                Nas_AddList(&chan->link.pNode->freeList, &chan->link);
                continue;
            }

            scale = Nas_EnvProcess(&playback_chan->adsr_envp);
            Nas_ChannelModulation(chan);
            main_param_p = &playback_chan->params;
            
            switch (playback_chan->status) {
                case 1:
                case 2:
                    param.playback.pitch = main_param_p->pitch;
                    param.playback.velocity = main_param_p->velocity;
                    param.playback.pan = main_param_p->pan;
                    param.playback.target_reverb_volume = main_param_p->target_reverb_volume;
                    param.playback.stereo_phase = main_param_p->stereo_phase;
                    param.playback.gain = main_param_p->gain;
                    param.playback.filter_buf = main_param_p->filter;
                    param.comb_filter_size = main_param_p->comb_filter_size;
                    param.comb_filter_gain = main_param_p->comb_filter_gain;
                    param.playback.surround_effect_idx = main_param_p->surround_effect_idx;
                    bookOfs = common_chan->book_ofs;
                    break;
                default: {
                    note* n = playback_chan->current_parent_note;
                    sub* subtrack = n->sub_track;

                    param.playback.pitch = n->note_frequency_scale;
                    param.playback.velocity = n->note_velocity;
                    param.playback.pan = n->note_pan;

                    if (n->surround_effect_idx == 128) {
                        param.playback.surround_effect_idx = subtrack->surround_effect_idx;
                    } else {
                        param.playback.surround_effect_idx = n->surround_effect_idx;
                    }

                    if (n->stereo_phase.type == 0) {
                        param.playback.stereo_phase = subtrack->stereo_phase;
                    } else {
                        param.playback.stereo_phase = n->stereo_phase;
                    }

                    if (n->_0A.flags.bit2 == TRUE) {
                        param.playback.target_reverb_volume = subtrack->target_reverb_vol;
                    } else {
                        param.playback.target_reverb_volume = n->target_reverb_volume;
                    }

                    if (n->_0A.flags.bit9 == TRUE) {
                        param.playback.gain = subtrack->gain;
                    } else {
                        param.playback.gain = 0;
                    }

                    param.playback.filter_buf = subtrack->filter;
                    param.comb_filter_size = subtrack->comb_filter_size;
                    param.comb_filter_gain = subtrack->comb_filter_gain;
                    bookOfs = subtrack->book_ofs;

                    if (subtrack->group->flags.muted && (subtrack->mute_flags & AUDIO_MUTE_FLAG_STOP_SAMPLES)) {
                        param.playback.pitch = 0.0f;
                        param.playback.velocity = 0.0f;
                    }

                    break;
                }
            }

            param.playback.pitch *= playback_chan->vibrato_frequency_scale * playback_chan->portamento_frequency_scale;
            param.playback.pitch *= AG.audio_params.resample_rate;
            param.playback.velocity *= scale;
            Nas_smzSetParam(chan, &param);
            common_chan->book_ofs = bookOfs;
            continue;
        }

    skip:
        if (playback_chan->priority != 0) {
            goto step2;
        }
    }
}

extern wtstr* NoteToVoice(voicetable* vtbl, s32 note) {
    wtstr* voice_p;

    if (note < vtbl->normal_range_low) {
        voice_p = &vtbl->low_pitch_tuned_sample;
    } else if (note <= vtbl->normal_range_high) {
        voice_p = &vtbl->normal_pitch_tuned_sample;
    } else {
        voice_p = &vtbl->high_pitch_tuned_sample;
    }

    return voice_p;
}

extern voicetable* ProgToVp(s32 prog, s32 inst) {
    voicetable* vtbl;

    if (prog == 0xFF) {
        return NULL;
    }

    if (!Nas_CheckIDbank(prog)) {
        AG.audio_error_flags = 0x10000000 + prog;
#ifdef TARGET_PC
        {
            static u32 ptv_nobank = 0;
            if (ptv_nobank < 20) {
                printf("[ProgToVp] FAIL bank_not_loaded prog=%d inst=%d\n", prog, inst);
                ptv_nobank++;
            }
        }
#endif
        return NULL;
    }

    if (inst >= AG.voice_info[prog].num_instruments) {
        AG.audio_error_flags = 0x03000000 + (prog << 8) + inst;
#ifdef TARGET_PC
        {
            static u32 ptv_oob = 0;
            if (ptv_oob < 20) {
                printf("[ProgToVp] FAIL inst_oob prog=%d inst=%d num=%d\n",
                    prog, inst, AG.voice_info[prog].num_instruments);
                ptv_oob++;
            }
        }
#endif
        return NULL;
    }

    vtbl = AG.voice_info[prog].instruments[inst];
    if (vtbl == NULL) {
        AG.audio_error_flags = 0x01000000 + (prog << 8) + inst;
#ifdef TARGET_PC
        {
            static u32 ptv_null = 0;
            if (ptv_null < 20) {
                printf("[ProgToVp] FAIL inst_null prog=%d inst=%d\n", prog, inst);
                ptv_null++;
            }
        }
#endif
        return vtbl;
    }

    return vtbl;
}

extern perctable* PercToPp(s32 prog, s32 drum) {
    perctable* vtbl;

    if (prog == 0xFF) {
        return NULL;
    }

    if (!Nas_CheckIDbank(prog)) {
        AG.audio_error_flags = 0x10000000 + prog;
#ifdef TARGET_PC
        { static u32 c=0; if(c++<20) printf("[PercToPp] FAIL bank prog=%d drum=%d\n",prog,drum); }
#endif
        return NULL;
    }

    if (drum >= AG.voice_info[prog].num_drums) {
        AG.audio_error_flags = 0x04000000 + (prog << 8) + drum;
#ifdef TARGET_PC
        { static u32 c=0; if(c++<20) printf("[PercToPp] FAIL drum_oob prog=%d drum=%d num=%d\n",prog,drum,AG.voice_info[prog].num_drums); }
#endif
        return NULL;
    }


    vtbl = AG.voice_info[prog].percussion[drum];
    if (vtbl == NULL) {
        AG.audio_error_flags = 0x05000000 + (prog << 8) + drum;
#ifdef TARGET_PC
        { static u32 c=0; if(c++<20) printf("[PercToPp] FAIL perc_null prog=%d drum=%d\n",prog,drum); }
#endif
        return vtbl;
    }

    return vtbl;
}

extern percvoicetable* VpercToVep(s32 prog, s32 sfx) {
    percvoicetable* vtbl;

    if (prog == 0xFF) {
        return NULL;
    }

    if (!Nas_CheckIDbank(prog)) {
        AG.audio_error_flags = 0x10000000 + prog;
        return NULL;
    }

    if (sfx >= AG.voice_info[prog].num_sfx) {
        AG.audio_error_flags = 0x04000000 + (prog << 8) + sfx;
        return NULL;
    }


    vtbl = &AG.voice_info[prog].effects[sfx];
    if (vtbl == NULL) {
        // this should be impossible to trigger
        AG.audio_error_flags = 0x05000000 + (prog << 8) + sfx;
    }

    if (vtbl->tuned_sample.wavetable == NULL) {
        return NULL;
    }

    return vtbl;
}

extern s32 OverwriteBank(s32 type, s32 bankId, s32 idx, s32 table) {
    if (bankId == 0xFF) {
        return -1;
    }

    if (!Nas_CheckIDbank(bankId)) {
        return -2;
    }

    switch (type) {
        case VOICE_TYPE_PERCUSSION:
            if (idx >= AG.voice_info[bankId].num_drums) {
                return -3;
            }

            AG.voice_info[bankId].percussion[idx] = (perctable*)table;
            break;
        case VOICE_TYPE_SOUND_EFF:
            if (idx >= AG.voice_info[bankId].num_sfx) {
                return -3;
            }

            AG.voice_info[bankId].effects[idx] = *(percvoicetable*)table;
            break;
        default:
            if (idx >= AG.voice_info[bankId].num_instruments) {
                return -3;
            }

            AG.voice_info[bankId].instruments[idx] = (voicetable*)table;
            break;
    }

    return 0;
}

static void __Nas_Release_Channel_Main(note* n, int target) {
    channel* chan;
    playbackparams* param;
    sub* subtrack;
    s32 i;

    if (n == NA_NO_NOTE) {
        return;
    }

    n->channel_attached = FALSE;

    if (n->channel == NULL) {
        return;
    }

    chan = n->channel;
    param = &chan->playback_ch.params;

    if (chan->playback_ch.wanted_parent_note == n) {
        chan->playback_ch.wanted_parent_note = NA_NO_NOTE;
    }

    if (chan->playback_ch.current_parent_note != n) {
        if (chan->playback_ch.current_parent_note != NA_NO_NOTE || chan->playback_ch.wanted_parent_note != NA_NO_NOTE ||
            chan->playback_ch.previous_parent_note != n || target == ADSR_STATUS_DECAY) {
            return;
        }

        chan->playback_ch.adsr_envp.fadeout_velocity = AG.audio_params.updates_per_frame_inverse;
        chan->playback_ch.adsr_envp.state.flags.release = TRUE;
        return;
    }

    if (chan->playback_ch.adsr_envp.state.flags.status != ADSR_STATUS_DECAY) {
        param->pitch = n->note_frequency_scale;
        param->velocity = n->note_velocity;
        param->pan = n->note_pan;

        if (n->sub_track != NULL) {
            subtrack = n->sub_track;
            if (n->_0A.flags.bit2 == TRUE) {
                param->target_reverb_volume = subtrack->target_reverb_vol;
            } else {
                param->target_reverb_volume = n->target_reverb_volume;
            }

            if (n->surround_effect_idx == 128) {
                param->surround_effect_idx = subtrack->surround_effect_idx;
            } else {
                param->surround_effect_idx = n->surround_effect_idx;
            }

            if (n->_0A.flags.bit9 == TRUE) {
                param->gain = subtrack->gain;
            } else {
                param->gain = 0;
            }
            
            param->filter = subtrack->filter;
            if (param->filter != NULL) {
                for (i = 0; i < 8; i++) {
                    param->filter_buf[i] = param->filter[i];
                }

                param->filter = param->filter_buf;
            }

            param->comb_filter_gain = subtrack->comb_filter_gain;
            param->comb_filter_size = subtrack->comb_filter_size;

            if (subtrack->group->flags.muted && (subtrack->mute_flags & AUDIO_MUTE_FLAG_STOP_SAMPLES)) {
                chan->common_ch.finished = TRUE;
            }

            if (*(u8*)&n->stereo_phase == 0) {
                param->stereo_phase = subtrack->stereo_phase;
            } else {
                param->stereo_phase = n->stereo_phase;
            }

            chan->playback_ch.priority = subtrack->priority2;
        } else {
            param->stereo_phase = n->stereo_phase;
            chan->playback_ch.priority = 1;
        }

        chan->playback_ch.previous_parent_note = chan->playback_ch.current_parent_note;
        chan->playback_ch.current_parent_note = NA_NO_NOTE;
        if (target == ADSR_STATUS_RELEASE) {
            chan->playback_ch.adsr_envp.fadeout_velocity = AG.audio_params.updates_per_frame_inverse;
            chan->playback_ch.adsr_envp.state.flags.release = TRUE;
            chan->playback_ch.status = 2;
        } else {
            chan->playback_ch.status = 1;
            chan->playback_ch.adsr_envp.state.flags.decay = TRUE;
            if (n->adsr_env.decay_idx == 0) {
                chan->playback_ch.adsr_envp.fadeout_velocity = AG.adsr_decay_table[n->sub_track->adsr_env.decay_idx];
            } else {
                chan->playback_ch.adsr_envp.fadeout_velocity = AG.adsr_decay_table[n->adsr_env.decay_idx];
            }

            chan->playback_ch.adsr_envp.sustain = (f32)(s32)n->sub_track->adsr_env.sustain * chan->playback_ch.adsr_envp.current / 256.0f;
        }
    }

    if (target == ADSR_STATUS_DECAY) {
        Nas_CutList(&chan->link);
        Nas_AddListHead(&chan->link.pNode->releaseList, &chan->link);
    }
}

extern void Nas_Release_Channel(note* n) {
    __Nas_Release_Channel_Main(n, ADSR_STATUS_DECAY);
}

extern void Nas_Release_Channel_Force(note* n) {
    __Nas_Release_Channel_Main(n, ADSR_STATUS_RELEASE);
}

static void __Nas_InitList(link* l) {
    l->prev = l;
    l->next = l;
    l->numAfter = 0;
}

extern void Nas_InitChNode(chnode* node) {
    __Nas_InitList(&node->freeList);
    __Nas_InitList(&node->releaseList);
    __Nas_InitList(&node->relwaitList);
    __Nas_InitList(&node->useList);

    node->freeList.pNode = node;
    node->releaseList.pNode = node;
    node->relwaitList.pNode = node;
    node->useList.pNode = node;
}

extern void Nas_InitChannelList(void) {
    s32 i;

    Nas_InitChNode(&AG.channel_node);
    for (i = 0; i < AG.num_channels; i++) {
        AG.channels[i].link.pData = &AG.channels[i];
        AG.channels[i].link.prev = NULL;
        Nas_AddList(&AG.channel_node.freeList, &AG.channels[i].link);
    }
}

extern void Nas_DeAllocAllVoices(chnode* node) {
    s32 i;
    link* src;
    link* cur;
    link* dst;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                src = &node->freeList;
                dst = &AG.channel_node.freeList;
                break;
            case 1:
                src = &node->releaseList;
                dst = &AG.channel_node.releaseList;
                break;
            case 2:
                src = &node->relwaitList;
                dst = &AG.channel_node.relwaitList;
                break;
            case 3:
                src = &node->useList;
                dst = &AG.channel_node.useList;
                break;
        }

        while (TRUE) {
            cur = src->next;
            if ((s32)cur == (s32)src || cur == NULL) {
                break;
            }

            Nas_CutList(cur);
            Nas_AddList(dst, cur);
        }
    }
}

extern void Nas_AllocVoices(chnode* node, s32 count) {
    s32 i;
    s32 j;
    channel* chan;
    link* src;
    link* dst;
    
    Nas_DeAllocAllVoices(node);
    
    for (i = 0, j = 0; j < count; i++) {
        if (i == 4) {
            return;
        }

        switch (i) {
            case 0:
                src = &AG.channel_node.freeList;
                dst = &node->freeList;
                break;
            case 1:
                src = &AG.channel_node.releaseList;
                dst = &node->releaseList;
                break;
            case 2:
                src = &AG.channel_node.relwaitList;
                dst = &node->relwaitList;
                break;
            case 3:
                src = &AG.channel_node.useList;
                dst = &node->useList;
                break;
        }

        while (j < count) {
            chan = (channel*)Nas_GetList(src);
            if (chan == NULL) {
                break;
            }

            Nas_AddList(dst, &chan->link);
            j++;
        }
    }
}

static void Nas_AddListHead(link* list, link* l) {
    if (l->prev == NULL) {
        l->prev = list;
        l->next = list->next;
        list->next->prev = l;
        list->next = l;
        list->numAfter++;
        l->pNode = list->pNode;
    }
}

extern void Nas_CutList(link* l) {
    if (l->prev != NULL) {
        l->prev->next = l->next;
        l->next->prev = l->prev;
        l->prev = NULL;
    }
}

static channel* __Nas_GetLowerPrio(link* l, s32 prio) {
    link* cur = l->next;
    link* best;

    if (cur == l) {
        return NULL;
    }

    for (best = cur; cur != l; cur = cur->next) {
        if (((channel*)cur->pData)->playback_ch.priority <= ((channel*)best->pData)->playback_ch.priority) {
            best = cur;
        }
    }

    if (best == NULL) {
        return NULL;
    }

    if (((channel*)best->pData)->playback_ch.priority >= prio) {
        return NULL;
    }

    return (channel*)best->pData;
}

extern void Nas_EntryTrack(channel* chan, note* n) {
    s32 instId;
    sub* subtrack = n->sub_track;
    playbackch* playback = &chan->playback_ch;
    commonch* common = &chan->common_ch;

    playback->previous_parent_note = NA_NO_NOTE;
    playback->current_parent_note = n;
    playback->priority = subtrack->note_priority;
    n->note_properties_need_init = TRUE;
    n->channel_attached = TRUE;
    n->channel = chan;
    subtrack->channel = chan;
    subtrack->note = n;
    n->note_velocity = 0.0f;
    Nas_StartVoice(chan);
    instId = n->inst_or_wave;

    if (instId == 0xFF) {
        instId = subtrack->inst_or_wave;
    }

    common->tuned_sample = n->tuned_sample;
    if (instId >= 0x80 && instId < 0xC0) {
        common->is_synth_wave = TRUE;
    } else {
        common->is_synth_wave = FALSE;
    }

    if (subtrack->sample_start_pos == 1) {
        playback->start_sample_pos = common->tuned_sample->wavetable->loop->loop_start;
    } else {
        playback->start_sample_pos = subtrack->sample_start_pos;
        if (playback->start_sample_pos >= common->tuned_sample->wavetable->loop->loop_end) {
            playback->start_sample_pos = 0;
        }
    }

    playback->vel_conv_table_idx = (int)(n->velocity_square2 * 11.5f);
    if (playback->vel_conv_table_idx > 15) {
        playback->vel_conv_table_idx = 15;
    }

    playback->bank_id = subtrack->bank_id;
    playback->stereo_headset_effects = subtrack->stereo_effects;
    common->reverb_idx = subtrack->reverb_idx & 3;
}

static void __Nas_InterTrack(channel* chan, note* n) {
    playbackch* playback = &chan->playback_ch;

    Nas_Release_Channel_Force(playback->current_parent_note);
    playback->wanted_parent_note = n;
}

static void __Nas_InterReleaseTrack(channel* chan, note* n) {
    playbackch* playback = &chan->playback_ch;

    playback->wanted_parent_note = n;
    playback->priority = n->sub_track->note_priority;
    playback->adsr_envp.fadeout_velocity = AG.audio_params.updates_per_frame_inverse;
    playback->adsr_envp.state.flags.release = TRUE;
}

static channel* __Nas_ChLookFree(chnode* node, note* n) {
    channel* chan = (channel*)Nas_GetList(&node->freeList);

    if (chan != NULL) {
        Nas_EntryTrack(chan, n);
        Nas_AddListHead(&node->useList, &chan->link);
    }

    return chan;
}

static channel* __Nas_ChLookRelease(chnode* node, note* n) {
    channel* chan = __Nas_GetLowerPrio(&node->releaseList, n->sub_track->note_priority);

    if (chan != NULL) {
        __Nas_InterReleaseTrack(chan, n);
        Nas_CutList(&chan->link);
        Nas_AddList(&node->relwaitList, &chan->link);
    }

    return chan;
}

static channel* __Nas_ChLookRelWait(chnode* node, note* n) {
    channel* relWaitChan;
    channel* useChan;
    s32 relWaitPrio;
    s32 usePrio;

    relWaitPrio = usePrio = 16;

    relWaitChan = __Nas_GetLowerPrio(&node->relwaitList, n->sub_track->note_priority);
    if (relWaitChan != NULL) {
        relWaitPrio = relWaitChan->playback_ch.priority;
    }

    useChan = __Nas_GetLowerPrio(&node->useList, n->sub_track->note_priority);
    if (useChan != NULL) {
        usePrio = useChan->playback_ch.priority;
    }

    if (relWaitChan == NULL && useChan == NULL) {
        return NULL;
    }

    if (usePrio < relWaitPrio) {
        Nas_CutList(&useChan->link);
        __Nas_InterTrack(useChan, n);
        Nas_AddList(&node->relwaitList, &useChan->link);
        useChan->playback_ch.priority = n->sub_track->note_priority;
        return useChan;
    } else {
        relWaitChan->playback_ch.wanted_parent_note = n;
        relWaitChan->playback_ch.priority = n->sub_track->note_priority;
        return relWaitChan;
    }
}

extern channel* Nas_AllocationOnRequest(note* n) {
    channel* chan;
    u32 policy = n->sub_track->note_alloc_policy;

    if (policy & 1) {
        chan = n->channel;
        if (chan != NULL && chan->playback_ch.previous_parent_note == n &&
            chan->playback_ch.wanted_parent_note == NA_NO_NOTE) {
            __Nas_InterReleaseTrack(chan, n);
            Nas_CutList(&chan->link);
            Nas_AddList(&chan->link.pNode->relwaitList, &chan->link);
            return chan;
        }
    }

    if (policy & 2) {
        if (!(chan = __Nas_ChLookFree(&n->sub_track->channel_node, n)) &&
            !(chan = __Nas_ChLookRelease(&n->sub_track->channel_node, n)) &&
            !(chan = __Nas_ChLookRelWait(&n->sub_track->channel_node, n))) {
            goto null_return;
        }
        return chan;
    }

    if (policy & 4) {
        if (!(chan = __Nas_ChLookFree(&n->sub_track->channel_node, n)) &&
            !(chan = __Nas_ChLookFree(&n->sub_track->group->channel_node, n)) &&
            !(chan = __Nas_ChLookRelease(&n->sub_track->channel_node, n)) &&
            !(chan = __Nas_ChLookRelease(&n->sub_track->group->channel_node, n)) &&
            !(chan = __Nas_ChLookRelWait(&n->sub_track->channel_node, n)) &&
            !(chan = __Nas_ChLookRelWait(&n->sub_track->group->channel_node, n))) {
            goto null_return;
        }
        return chan;
    }

    if (policy & 8) {
        if (!(chan = __Nas_ChLookFree(&AG.channel_node, n)) &&
            !(chan = __Nas_ChLookRelease(&AG.channel_node, n)) &&
            !(chan = __Nas_ChLookRelWait(&AG.channel_node, n))) {
            goto null_return;
        }
        return chan;
    }

    if (!(chan = __Nas_ChLookFree(&n->sub_track->channel_node, n)) &&
        !(chan = __Nas_ChLookFree(&n->sub_track->group->channel_node, n)) &&
        !(chan = __Nas_ChLookFree(&AG.channel_node, n)) &&
        !(chan = __Nas_ChLookRelease(&n->sub_track->channel_node, n)) &&
        !(chan = __Nas_ChLookRelease(&n->sub_track->group->channel_node, n)) &&
        !(chan = __Nas_ChLookRelease(&AG.channel_node, n)) &&
        !(chan = __Nas_ChLookRelWait(&n->sub_track->channel_node, n)) &&
        !(chan = __Nas_ChLookRelWait(&n->sub_track->group->channel_node, n)) &&
        !(chan = __Nas_ChLookRelWait(&AG.channel_node, n))) {
        goto null_return;
    }
    
    return chan;

null_return:
    n->channel_attached = TRUE;
    return NULL;
}

extern void Nas_ChannelInit(void) {
    s32 i;
    channel* chan;

    for (i = 0; i < AG.num_channels; i++) {
        chan = &AG.channels[i];
        chan->common_ch = NA_CHINIT_TABLE[0];
        chan->playback_ch.priority = 0;
        chan->playback_ch.status = 0;
        chan->playback_ch.current_parent_note = NA_NO_NOTE;
        chan->playback_ch.wanted_parent_note = NA_NO_NOTE;
        chan->playback_ch.previous_parent_note = NA_NO_NOTE;
        chan->playback_ch.wave_id = 0;
        chan->playback_ch.params.velocity = 0.0f;
        chan->playback_ch.adsr_volume_scale_unused = 0;
        chan->playback_ch.adsr_envp.state.as_byte = 0;
        chan->playback_ch.vibrato_tmtable.active = FALSE;
        chan->playback_ch.portamento_sweep.current = 0;
        chan->playback_ch.portamento_sweep.speed = 0;
        chan->playback_ch.stereo_headset_effects = FALSE;
        chan->playback_ch.start_sample_pos = 0;
        chan->driver_ch.synth_params = (synthparams*)Nas_NcHeapAlloc(&AG.misc_heap, sizeof(synthparams));
        chan->playback_ch.params.filter_buf = (s16*)Nas_NcHeapAlloc(&AG.misc_heap, 8 * sizeof(s16));
    }
}
