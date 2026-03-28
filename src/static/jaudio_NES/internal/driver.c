#include "jaudio_NES/driver.h"

#include <stdbool.h>
#include "PR/abi.h"
#include "jaudio_NES/audiocommon.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/astest.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/system.h"
#include "dolphin/os/OSCache.h"
#include "types.h"

#define DMEM_TEMP 0x380
#define DMEM_WET_TEMP 0x3A0
#define DMEM_COMB_TEMP 0x720
#define DMEM_LEFT_CH 0x900
#define DMEM_RIGHT_CH 0xAA0
#define DMEM_WET_LEFT_CH 0xC40
#define DMEM_WET_RIGHT_CH 0xDE0
#define DMEM_UNCOMPRESSED_NOTE 0x540
#define DMEM_COMPRESSED_ADPCM_DATA 0x900
#define DMEM_HAAS_TEMP 0x580
#define DMEM_SURROUND_TEMP 0x480

typedef enum {
    /* 0 */ HAAS_EFFECT_DELAY_NONE,
    /* 1 */ HAAS_EFFECT_DELAY_LEFT, // Delay left channel so that right channel is heard first
    /* 2 */ HAAS_EFFECT_DELAY_RIGHT // Delay right channel so that left channel is heard first
} HaasEffectDelaySide;

static u16 NOISE_TABLE[] = { 0, 1, 2, 4, 8, 12, 16, 20, 24, 32, 36, 40, 46, 52, 56, 64 };
static dspch_ DSPCH[64];
static s32 STOP_VELOCONV = 0;

static u32 Env_DataH = (A_CMD_ENVMIXER << 24) | (0x00 << 16) | (0x00 << 8) | (0x00);
static u32 Env_Data_L1 = 0x58AAC4DE;
static u32 Env_Data_L2 = 0x9058C4DE;
static u32 Env_Data_L3 = 0x90AAC4DE;

static Acmd* __LoadAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);
static Acmd* __SaveAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);
static Acmd* Nas_SaveBufferAuto(Acmd* cmd, u16 ofs, u16 size, s32 startAddr);

static void Nas_CpuFX(s32 chunkLen, s32 updateIdx, s32 reverbIdx) {
    delayparam* param_p;
    s32 count;
    delay* del_p;
    s32 t;
    s32 i;
    s32 sample2;
    s32 next_buf_pos;
    s32 t2;
    s32 idx;
    s32 t3;
    s32 sample;
    s32 n;
    s32 s;

    del_p = &AG.synth_delay[reverbIdx];
    param_p = &del_p->params[del_p->cur_frame][updateIdx];
    count = chunkLen / AG.synth_delay[reverbIdx].downsample_rate;
    if (AG.synth_delay[reverbIdx].resample_effect_on && AG.synth_delay[reverbIdx].downsample_rate == 1 && del_p->right_save_resample_buf != NULL) {
        count += del_p->resample_effect_extra_samples;
        param_p->save_resample_num_samples = count;
        param_p->load_resample_pitch = (param_p->save_resample_num_samples << 15) / chunkLen;
        param_p->save_resample_pitch = (chunkLen << 15) / param_p->save_resample_num_samples;
        
        n = 10;
        s = 10;
        for (i = 0; i < 10; i++) {
            n--;
            sample = del_p->resample_effect_load_unk + param_p->load_resample_pitch * chunkLen * SAMPLE_SIZE;
            sample2 = (sample >> 16);
            if (sample2 != count && n == 0) {
                param_p->load_resample_pitch = (count * 0x10000 - del_p->resample_effect_load_unk) / (chunkLen * SAMPLE_SIZE);
            } else if (sample2 > count) {
                param_p->load_resample_pitch--;
            } else if (sample2 < count) {
                param_p->load_resample_pitch++;
            } else {
                break;
            }
        }

        del_p->resample_effect_load_unk = sample;

        for (i = 0; i < 10; i++) {            
            s--;
            sample = del_p->resample_effect_save_unk + param_p->save_resample_pitch * count * SAMPLE_SIZE;
            sample2 = (sample >> 16);
            if (sample2 != chunkLen && s == 0) {
                param_p->save_resample_pitch = (chunkLen * 0x10000 - del_p->resample_effect_save_unk) / (count * SAMPLE_SIZE);
            } else if (sample2 > chunkLen) {
                param_p->save_resample_pitch--;
            } else if (sample2 < chunkLen) {
                param_p->save_resample_pitch++;
            } else {
                break;
            }
        }

        del_p->resample_effect_save_unk = sample;
    }

    next_buf_pos = del_p->next_reverb_buf_pos;
    t = del_p->next_reverb_buf_pos + count - del_p->delay_num_samples;

    if (t < 0) {
        param_p->size = count * SAMPLE_SIZE;
        param_p->wrapped_size = 0;
        param_p->start_pos = del_p->next_reverb_buf_pos;
        del_p->next_reverb_buf_pos += count;
    } else {
        param_p->size = (count - t) * SAMPLE_SIZE;
        param_p->wrapped_size = t * SAMPLE_SIZE;
        param_p->start_pos = del_p->next_reverb_buf_pos;
        del_p->next_reverb_buf_pos = t;
    }

    param_p->n_samples_after_downsampling = count;
    param_p->n_samples = chunkLen;

    if (del_p->sub_delay != 0) {
        t = del_p->delay_num_samples;
        idx = next_buf_pos + del_p->sub_delay;
        while (idx >= t) {
            idx -= t;
        }

        param_p = del_p->sub_params[del_p->cur_frame] + updateIdx;
        t2 = chunkLen / del_p->downsample_rate;
        t3 = idx + t2 - t;

        if (t3 < 0) {
            param_p->size = t2 * SAMPLE_SIZE;
            param_p->wrapped_size = 0;
            param_p->start_pos = idx;
        } else {
            param_p->size = (t2 - t3) * SAMPLE_SIZE;
            param_p->wrapped_size = t3 * SAMPLE_SIZE;
            param_p->start_pos = idx;
        }

        param_p->n_samples_after_downsampling = t2;
        param_p->n_samples = chunkLen;
    }
}

static void __Nas_PushDrvReg(s32 updateIdx) {
    s32 i;
    commonch* common0;
    commonch* common1;
    s32 baseIdx = updateIdx * AG.num_channels;

    for (i = 0; i < AG.num_channels; i++) {
        common0 = &AG.channels[i].common_ch;
        common1 = &AG.common_channel[baseIdx + i];

        if (common0->enabled) {
            CopyStc(common1, common0);
            common0->needs_init = FALSE;
        } else {
            common1->enabled = FALSE;
        }

        common0->harmonic_idx_cur_and_prev = 0;
    }
}

extern Acmd* Nas_smzAudioFrame(Acmd* cmdStart, s32* cmdCount, s16* aiStart, s32 aiBufLen) {
    Acmd* cmdP;
    s16* aiBufP;
    s32 chunkLen;
    s32 i;
    s32 j;

    cmdP = cmdStart;
    for (i = AG.audio_params.updates_per_frame; i > 0; i--) {
        Nas_MySeqMain(i - 1);
        __Nas_PushDrvReg(AG.audio_params.updates_per_frame - i);
    }

    aiBufP = aiStart;
    AG.adpcm_code_book = NULL;

    for (i = AG.audio_params.updates_per_frame; i > 0; i--) {
        chunkLen = AG.audio_params.num_samples_per_update;

        for (j = 0; j < AG.num_synth_reverbs; j++) {
            if (AG.synth_delay[j].use_reverb) {
                Nas_CpuFX(chunkLen, AG.audio_params.updates_per_frame - i, j);
            }
        }

        cmdP = Nas_DriveRsp(aiBufP, chunkLen, cmdP, AG.audio_params.updates_per_frame - i);
        aiBufLen -= chunkLen;
        aiBufP += (JAC_FRAMESAMPLES >> 1) & ~1;
    }

    for (j = 0; j < AG.num_synth_reverbs; j++) {
        if (AG.synth_delay[j].frames_to_ignore != 0) {
            AG.synth_delay[j].frames_to_ignore--;
        }
        AG.synth_delay[j].cur_frame ^= 1;
    }

    *cmdCount = cmdP - cmdStart;
    return cmdP;
}

static void __Nas_WaveTerminateProcess(s32 updateIdx, s32 chanIdx) {
    commonch* common;
    s32 i;

    for (i = updateIdx + 1; i < AG.audio_params.updates_per_frame; i++) {
        common = &AG.common_channel[i * AG.num_channels + chanIdx];
        if (!common->needs_init) {
            common->enabled = FALSE;
        } else {
            break;
        }
    }
}

static Acmd* Nas_LoadAux2nd(Acmd* cmd, const delay* del_p, s16 updateIdx) {
    const delayparam* param = &del_p->params[del_p->cur_frame][updateIdx];

    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos, param->size, (delay*)del_p);
    if (param->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0x3A0 + param->size, 0, param->wrapped_size, (delay*)del_p);
    }

    return cmd;
}

static Acmd* Nas_SaveAux2nd(Acmd* cmd, const delay* del_p, s16 updateIdx) {
    const delayparam* param = &del_p->params[del_p->cur_frame][updateIdx];

    cmd = __SaveAuxBuf(cmd, 0x3A0, param->start_pos, param->size, (delay*)del_p);
    if (param->wrapped_size != 0) {
        cmd = __SaveAuxBuf(cmd, 0x3A0 + param->size, 0, param->wrapped_size, (delay*)del_p);
    }

    return cmd;
}

static void Nas_ClearBuffer(Acmd* cmd, s32 dmem, s32 size) {
    aClearBuffer(cmd, dmem, size);
}

static void Nas_Mix(Acmd* cmd, s32 flags, s32 gain, s32 dmem_in, s32 dmem_out) {
    aMix(cmd, flags, gain, dmem_in, dmem_out);
}

static void Nas_SetBuffer(Acmd* cmd, s32 flags, s32 dmem_in, s32 dmem_out, s32 count) {
    aSetBuffer(cmd, flags, dmem_in, dmem_out, count);
}

static void Nas_DMEMMove(Acmd* cmd, s32 dmem_in, s32 dmem_out, s32 count) {
    aDMEMMove(cmd, dmem_in, dmem_out, count);
}

static void Nas_HalfCut(Acmd* cmd, s32 src, s32 dst, s32 len) {
    aHalfCut(cmd, src, dst, len);
}

static void Nas_SetEnvParam(Acmd* cmd, s32 reverbVol, s32 rampReverb, s32 rampL, s32 rampR) {
    aSetEnvParam(cmd, reverbVol, rampReverb, rampL, rampR);
}

static void Nas_LoadBuffer2(Acmd* cmd, s32 dst, s32 len, s32 src) {
    aLoadBuffer2(cmd, src, dst, len);
}

static void Nas_SaveBuffer2(Acmd* cmd, s32 src, s32 len, s32 dst) {
    aSaveBuffer2(cmd, dst, src, len);
}

static void Nas_SetEnvParam2(Acmd* cmd, s32 volL, s32 volR) {
    aSetEnvParam2(cmd, volL, volR);
}

static void Nas_PCM8dec(Acmd* cmd, s32 flags, s32 state) {
    aPCM8dec(cmd, flags, state);
}

static void Nas_DistFilter(Acmd* cmd, s32 gain, s32 dmem_in, s32 dmem_out, s32 len) {
    aDistFilter(cmd, gain, dmem_in, dmem_out, len);
}

// TODO: check params
static void Nas_NoiseFilter(Acmd* cmd, s32 buf, s32 flags, s32 addr, s32 len) {
    aNoiseFilter(cmd, buf, flags, addr, len);
}

static void Nas_FirFilter(Acmd* cmd, s32 flags, s32 buf, s16* filter) {
    aFirFilter(cmd, flags, buf, filter);
}

static void Nas_FirLoadTable(Acmd* cmd, s32 size, s16* filter) {
    aFirLoadTable(cmd, size, filter);
}

static Acmd* Nas_CrossMix(Acmd* cmd, delay* del_p) {
    aDMEMMove(cmd++, 0xC40, 0x6E0, 0x1A0);
    aMix(cmd++, 0x1A, del_p->leak_rtl, 0xDE0, 0xC40);
    aMix(cmd++, 0x1A, del_p->leak_ltl, 0x6E0, 0xDe0);
    return cmd;
}

static Acmd* Nas_LoadAuxBufferC(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 ofs_size = (param->start_pos & 7) * SAMPLE_SIZE;
    
    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos - (ofs_size / SAMPLE_SIZE), 0x1A0, del_p);
    if (param->wrapped_size != 0) {
        s16 wrapped_ofs_size = ALIGN_NEXT(ofs_size + param->size, 16);
        
        cmd = __LoadAuxBuf(cmd, 0x3A0 + wrapped_ofs_size, 0, 0x1A0 - wrapped_ofs_size, del_p);
    }

    aSetBuffer(cmd++, 0, 0x3A0 + ofs_size, 0xC40, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, del_p->downsample_pitch, del_p->left_load_resample_buf);
    aSetBuffer(cmd++, 0, 0x3A0 + 0x1A0 + ofs_size, 0xDE0, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, del_p->downsample_pitch, del_p->right_load_resample_buf);
    return cmd;
}

static Acmd* Nas_SaveAuxBufferCH(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 samples = param->n_samples;
    u32 size = samples * SAMPLE_SIZE;

    aDMEMMove(cmd++, 0xC40, 0x3A0, size);
    aSetBuffer(cmd++, 0, 0x3A0, 0x6E0, param->save_resample_num_samples * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->save_resample_pitch, del_p->left_save_resample_buf);
    cmd = Nas_SaveBufferAuto(cmd, 0x6E0, param->size, (s32)&del_p->left_reverb_buf[param->start_pos]);
    if (param->wrapped_size != 0) {
        cmd = Nas_SaveBufferAuto(cmd, 0x6E0 + param->size, param->wrapped_size, (s32)&del_p->left_reverb_buf[0]);
    }

    aDMEMMove(cmd++, 0xDE0, 0x3A0, size);
    aSetBuffer(cmd++, 0, 0x3A0, 0x6E0, param->save_resample_num_samples * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->save_resample_pitch, del_p->right_save_resample_buf);
    cmd = Nas_SaveBufferAuto(cmd, 0x6E0, param->size, (s32)&del_p->right_reverb_buf[param->start_pos]);
    if (param->wrapped_size != 0) {
        cmd = Nas_SaveBufferAuto(cmd, 0x6E0 + param->size, param->wrapped_size, (s32)&del_p->right_reverb_buf[0]);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBufferCH(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 ofs_size = (param->start_pos & 7) * SAMPLE_SIZE;
    
    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos - (ofs_size / SAMPLE_SIZE), 0x1A0, del_p);
    if (param->wrapped_size != 0) {
        s16 wrapped_ofs_size = ALIGN_NEXT(ofs_size + param->size, 16);
        s32 load_size = 0x1A0 - wrapped_ofs_size;

        if (load_size > 0) {
            cmd = __LoadAuxBuf(cmd, 0x3A0 + wrapped_ofs_size, 0, load_size, del_p);
        }
    }

    aSetBuffer(cmd++, 0, 0x3A0 + ofs_size, 0xC40, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->load_resample_pitch, del_p->left_load_resample_buf);
    aSetBuffer(cmd++, 0, 0x3A0 + 0x1A0 + ofs_size, 0xDE0, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->load_resample_pitch, del_p->right_load_resample_buf);
    return cmd;
}

static Acmd* Nas_DelayFilter(Acmd* cmd, s32 size, delay* del_p) {
    if (del_p->filter_left != NULL) {
        aFirLoadTable(cmd++, size, del_p->filter_left);
        aFirFilter(cmd++, del_p->resample_flags, 0xC40, del_p->filter_left_state);
    }

    if (del_p->filter_right != NULL) {
        aFirLoadTable(cmd++, size, del_p->filter_right);
        aFirFilter(cmd++, del_p->resample_flags, 0xDE0, del_p->filter_right_state);
    }

    return cmd;
}

static Acmd* Nas_SendLine(Acmd* cmd, delay* del_p, s32 update_idx) {
    delay* mix_delay;

    if (del_p->mix_reverb_idx >= AG.num_synth_reverbs) {
        return cmd;
    }

    mix_delay = &AG.synth_delay[del_p->mix_reverb_idx];
    if (mix_delay->downsample_rate == 1) {
        cmd = Nas_LoadAux2nd(cmd, mix_delay, update_idx);
        aMix(cmd++, 0x34, del_p->mix_reverb_strength, 0xC40, 0x3A0);
        cmd = Nas_LoadAux2nd(cmd, mix_delay, update_idx);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer1(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param_p = &del_p->params[del_p->cur_frame][update_idx];
    
    cmd = __LoadAuxBuf(cmd, 0xC40, param_p->start_pos, param_p->size, del_p);
    if (param_p->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0xC40 + param_p->size, 0, param_p->wrapped_size, del_p);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer1_B(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param_p = &del_p->sub_params[del_p->cur_frame][update_idx];
    
    cmd = __LoadAuxBuf(cmd, 0xC40, param_p->start_pos, param_p->size, del_p);
    if (param_p->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0xC40 + param_p->size, 0, param_p->wrapped_size, del_p);
    }

    return cmd;
}

static Acmd* Nas_SaveBufferAuto(Acmd* cmd, u16 dmem, u16 size, s32 startAddr) {
    s32 startUnaligned = startAddr & 15;
    s32 endAddr = startAddr + size;
    s32 endUnaligned = endAddr & 15;

    if (endUnaligned != 0) {
        aLoadBuffer2(cmd++, (endAddr - endUnaligned), 0x380, 16);
        aDMEMMove(cmd++, dmem, 0x390, size);
        aDMEMMove(cmd++, 0x380 + endUnaligned, 0x390 + size, 16 - endUnaligned);
        size += 16 - endUnaligned;
        dmem = 0x390;
    }
    
    if (startUnaligned != 0) {
        aLoadBuffer2(cmd++, (startAddr - startUnaligned), 0x380, 16);
        aDMEMMove(cmd++, dmem, 0x380 + startUnaligned, size);

        size += startUnaligned;
        dmem = 0x380;
    }

    aSaveBuffer2(cmd++, startAddr - startUnaligned, dmem, size);
    return cmd;
}

static Acmd* __LoadAuxBuf(Acmd* cmd, u16 dmem, u16 startPos, s32 size, delay* del_p) {
    aLoadBuffer2(cmd++, &del_p->left_reverb_buf[startPos], dmem, size);
    aLoadBuffer2(cmd++, &del_p->right_reverb_buf[startPos], dmem + 0x1A0, size);
    return cmd;
}

static Acmd* __SaveAuxBuf(Acmd* cmd, u16 dmem, u16 startPos, s32 size, delay* del_p) {
    aSaveBuffer2(cmd++, &del_p->left_reverb_buf[startPos], dmem, size);
    aSaveBuffer2(cmd++, &del_p->right_reverb_buf[startPos], dmem + 0x1A0, size);
    return cmd;
}

static Acmd* Nas_LoadAuxBuffer_B(Acmd* cmd, s32 numSamplesPerUpdate, delay* del_p, s16 updateIdx) {
    if (del_p->downsample_rate == 1) {
        cmd = Nas_LoadAuxBuffer1_B(cmd, numSamplesPerUpdate, del_p, updateIdx);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer(Acmd* cmd, s32 numSamplesPerUpdate, delay* del_p, s16 updateIdx) {
    if (del_p->downsample_rate == 1) {
        if (del_p->resample_effect_on) {
            cmd = Nas_LoadAuxBufferCH(cmd, numSamplesPerUpdate, del_p, updateIdx);
        } else {
            cmd = Nas_LoadAuxBuffer1(cmd, numSamplesPerUpdate, del_p, updateIdx);
        }
    } else {
        cmd = Nas_LoadAuxBufferC(cmd, numSamplesPerUpdate, del_p, updateIdx);
    }

    return cmd;
}

static Acmd* Nas_SaveAuxBuffer(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s32 downsample_rate;
    s32 n_samples;

    switch (del_p->downsample_rate) {
        case 1:
            if (del_p->resample_effect_on) {
                cmd = Nas_SaveAuxBufferCH(cmd, del_p, update_idx);
            } else {
                cmd = __SaveAuxBuf(cmd, 0xC40, param->start_pos, param->size, del_p);
                if (param->wrapped_size != 0) {
                    cmd = __SaveAuxBuf(cmd, 0xC40 + param->size, 0, param->wrapped_size, del_p);
                }
            }
            break;
        default:
            downsample_rate = del_p->downsample_rate;
            n_samples = 13 * 16; // 16 = SAMPLES_PER_FRAME

            while (downsample_rate > 1) {
                aHalfCut(cmd++, 0xC40, 0xC40, n_samples);
                aHalfCut(cmd++, 0xDE0, 0xDE0, n_samples);
                n_samples >>= 1;
                downsample_rate >>= 1;
            }

            if (param->size != 0) {
                cmd = Nas_SaveBufferAuto(cmd, 0xC40, (u16)param->size, (s32)&del_p->left_reverb_buf[param->start_pos]);
                cmd = Nas_SaveBufferAuto(cmd, 0xDE0, (u16)param->size, (s32)&del_p->right_reverb_buf[param->start_pos]);
            }

            if (param->wrapped_size != 0) {
                cmd = Nas_SaveBufferAuto(cmd, 0xC40 + param->size, (u16)param->wrapped_size, (s32)&del_p->left_reverb_buf[0]);
                cmd = Nas_SaveBufferAuto(cmd, 0xDE0 + param->size, (u16)param->wrapped_size, (s32)&del_p->right_reverb_buf[0]);
            }
            break;
    }

    del_p->resample_flags = 0;
    return cmd;
}

static Acmd* Nas_SaveAuxBuffer_B(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->sub_params[del_p->cur_frame][update_idx];
    
    cmd = __SaveAuxBuf(cmd, 0xC40, param->start_pos, param->size, del_p);
    if (param->wrapped_size != 0) {
        cmd = __SaveAuxBuf(cmd, 0xC40 + param->size, 0, param->wrapped_size, del_p);
    }

    return cmd;
}

extern Acmd* Nas_DriveRsp(s16* aiBuf, s32 aiBufLen, Acmd* cmd, s32 updateIndex) {
    s32 size = aiBufLen * SAMPLE_SIZE;
    u8 noteIndices[64];
    s32 noteCount = 0;
    s32 reverbIndex;
    delay* reverb;
    s32 useReverb;
    s32 sampleStateOffset = updateIndex * AG.num_channels;
    s32 i;
    commonch* sampleState;
    
    if (AG.num_synth_reverbs == 0) {
        int idx = sampleStateOffset;
        for (i = 0; i < AG.num_channels; i++) {
            if (AG.common_channel[idx++].enabled) {
                noteIndices[noteCount++] = i;
            }
        }
    } else {
        for (reverbIndex = 0; reverbIndex < AG.num_synth_reverbs; reverbIndex++) {
            for (i = 0; i < AG.num_channels; i++) {
                sampleState = &AG.common_channel[sampleStateOffset + i];
                if (sampleState->enabled && (sampleState->reverb_idx == reverbIndex)) {
                    noteIndices[noteCount++] = i;
                }
            }
        }

        for (i = 0; i < AG.num_channels; i++) {
            sampleState = &AG.common_channel[sampleStateOffset + i];
            if (sampleState->enabled && (sampleState->reverb_idx >= AG.num_synth_reverbs)) {
                noteIndices[noteCount++] = i;
            }
        }
    }

    aClearBuffer(cmd++, DMEM_LEFT_CH, DMEM_2CH_SIZE);

    i = 0;
    for (reverbIndex = 0; reverbIndex < AG.num_synth_reverbs; reverbIndex++) {
        s32 subDelay;
        // commonch* sampleState;

        reverb = &AG.synth_delay[reverbIndex];
        useReverb = reverb->use_reverb;
        if (useReverb) {
            cmd = Nas_LoadAuxBuffer(cmd, aiBufLen, reverb, updateIndex);
            aMix(cmd++, DMEM_2CH_SIZE >> 4, reverb->volume, DMEM_WET_LEFT_CH, DMEM_LEFT_CH);

            subDelay = reverb->sub_delay;
            if (subDelay != 0) {
                aDMEMMove(cmd++, DMEM_WET_LEFT_CH, DMEM_WET_TEMP, DMEM_2CH_SIZE);
            }

            // Decays reverb over time. The (+ 0x8000) here is -100%
            aMix(cmd++, DMEM_2CH_SIZE >> 4, reverb->decay_ratio + 0x8000, DMEM_WET_LEFT_CH, DMEM_WET_LEFT_CH);

            if (((reverb->leak_rtl != 0) || (reverb->leak_ltl != 0)) && (AG.sound_mode != SOUND_OUTPUT_MONO)) {
                cmd = Nas_CrossMix(cmd, reverb);
            }

            if (subDelay != 0) {
                if (reverb->mix_reverb_idx != -1) {
                    cmd = Nas_SendLine(cmd, reverb, updateIndex);
                }

                cmd = Nas_SaveAuxBuffer(cmd, reverb, updateIndex);
                cmd = Nas_LoadAuxBuffer_B(cmd, aiBufLen, reverb, updateIndex);
                aMix(cmd++, DMEM_2CH_SIZE >> 4, reverb->sub_volume, DMEM_WET_TEMP, DMEM_WET_LEFT_CH);
            }
        }

        while (i < noteCount) {
            sampleState = &AG.common_channel[sampleStateOffset + noteIndices[i]];
            if (sampleState->reverb_idx != reverbIndex) {
                break;
            }
            cmd = Nas_SynthMain(noteIndices[i], sampleState, &AG.channels[noteIndices[i]].driver_ch,
                                           aiBuf, aiBufLen, cmd, updateIndex);
            i++;
        }

        if (useReverb) {
            if ((reverb->filter_left != NULL) || (reverb->filter_right != NULL)) {
                cmd = Nas_DelayFilter(cmd, size, reverb);
            }

            // Saves the wet channel sample from DMEM (DMEM_WET_LEFT_CH) into (ringBuffer) DRAM for future use
            if (subDelay != 0) {
                cmd = Nas_SaveAuxBuffer_B(cmd, reverb, updateIndex);
            } else {
                if (reverb->mix_reverb_idx != -1) {
                    cmd = Nas_SendLine(cmd, reverb, updateIndex);
                }
                cmd = Nas_SaveAuxBuffer(cmd, reverb, updateIndex);
            }
        }
    }

    while (i < noteCount) {
        cmd = Nas_SynthMain(noteIndices[i], &AG.common_channel[sampleStateOffset + noteIndices[i]],
                                       &AG.channels[noteIndices[i]].driver_ch, aiBuf, aiBufLen, cmd,
                                       updateIndex);
        i++;
    }

    // size = aiBufLen * SAMPLE_SIZE;
    aInterleave2(cmd++, DMEM_TEMP, DMEM_LEFT_CH, DMEM_RIGHT_CH, size);

    if (NA_DACOUT_CALLBACK != NULL) {
        cmd = (Acmd*)((u32)NA_DACOUT_CALLBACK(cmd, 2 * size, updateIndex) & 0xFF); // ?? what is this? this has to be a bug
    }

    aSaveBuffer2(cmd++, aiBuf, DMEM_TEMP, JAC_FRAMESAMPLES);

    return cmd;
}

extern Acmd* Nas_SynthMain(s32 chan_id, commonch* common, driverch* driver, s16* samples, s32 samples_per_update, Acmd* cmd, s32 update_idx) {
    s32 pad1[1];
    s32 size;
    void* reverbAddrSrc;
    smzwavetable* sample;
    adpcmloop* loopInfo;
    s32 numSamplesUntilEnd;
    s32 flags;
    s32 skipBytes;
    s32 dmemUncompressedAddrOffset1;
    s32 numSamplesToLoadAdj;
    s32 numSamplesProcessed;
    s32 numFirstFrameSamplesToIgnore;
    s32 numSamplesToDecode;
    s32 numSamplesInThisIteration;
    s32 sampleFinished;
    s32 loopToPoint;
    u16 frequencyFixedPoint;
    s32 gain;
    s32 frameIndex;
    u32 numSamplesToLoadFixedPoint;
    s32 numSamplesToLoad;
    u8* sampleAddr;
    s32 sampleEndPos;
    s32 numSamplesToProcess;
    s32 dmemUncompressedAddrOffset2;
    s32 pad2[3];
    s32 numSamplesInFirstFrame;
    s32 numTrailingSamplesToIgnore;
    s32 pad3[3];
    s16 sampleDataDmemAddr;
    s32 frameSize;
    s32 numFramesToDecode;
    u8* samplesToLoadAddr;
    s32 numParts;
    s32 curPart;
    s32 sampleDataChunkAlignPad;
    s32 haasEffectDelaySide;
    s32 sampleDataChunkSize;
    s32 skipInitialSamples;
    s32 zeroOffset;
    s32 sampleAddrOffset;
    s32 combFilterDmem;
    channel* chan;
    u32 combFilterSize;
    u32 combFilterGain;
    void* combFilterState;
    s16* filter;
    s32 numSamplesToLoadFirstPart;
    u16 sampleDmemBeforeResampling;
    u16 something_unused_from_sm64;
    u32 stack_chan_id;
    u32 stack_update_idx;
    u8* tmpSamplesToLoadAddr;
    s32 bookOffset = common->book_ofs;
    s32 finished = common->finished;

    something_unused_from_sm64 = 0;
    chan = &AG.channels[chan_id];
    DCTouchRange(chan, sizeof(channel));
    size = SAMPLE_SIZE * samples_per_update;
    
    // Deviation from MM: Ensure that the wavetable isn't null
    if (common->tuned_sample != NULL) {
        flags = A_CONTINUE;

        // Initialize the synthesis state
        if (common->needs_init == true) {
            flags = A_INIT;
            driver->at_loop_point = false;
            driver->stop_loop = false;
            driver->sample_pos_integer_part = chan->playback_ch.start_sample_pos;
            driver->sample_pos_fractional_part = 0;

            // deviation from MM
            if (chan->playback_ch.adsr_envp.state.flags.unused == TRUE) {
                // previously unused ADSR state bit seems to be used for preserving volume
                driver->current_volume_left = common->target_volume_left << 4;
                driver->current_volume_right = common->target_volume_right << 4;
            } else {
                driver->current_volume_left = 0;
                driver->current_volume_right = 0;
            }

            driver->prev_haas_effect_left_delay_size = 0;
            driver->prev_haas_effect_right_delay_size = 0;
            driver->cur_reverb_vol = common->target_reverb_volume;
            driver->num_parts = 0;
            driver->comb_filter_needs_init = true;
            chan->common_ch.finished = false;
            driver->vel_conv_table_idx = chan->playback_ch.vel_conv_table_idx;
            finished = false;
        }

        // Process the sample in either one or two parts
        numParts = common->has_two_parts + 1;

        // Determine number of samples to load based on samples_per_update and relative frequency
        frequencyFixedPoint = common->frequency_fixed_point;
        numSamplesToLoadFixedPoint = (frequencyFixedPoint * samples_per_update * SAMPLE_SIZE) + driver->sample_pos_fractional_part;
        numSamplesToLoad = (u16)(numSamplesToLoadFixedPoint >> 16);

        if (numSamplesToLoad == 0) {
            skipBytes = false;
        }

        driver->sample_pos_fractional_part = numSamplesToLoadFixedPoint & 0xFFFF;

        // Partially-optimized out no-op ifs required for matching. SM64 decomp
        // makes it clear that this is how it should look.
        if (((driver->num_parts == 1) && (numParts == 2))) {
        } else if (((driver->num_parts == 2) && (numParts == 1))) {
        } else {
            something_unused_from_sm64 = 0;
        }
        
        driver->num_parts = numParts;
        
        // deviation from MM here, no synth wave check
        
        sample = common->tuned_sample->wavetable;
        loopInfo = sample->loop;

        if (chan->playback_ch.status != 0) {
            driver->stop_loop = true;
        }

        if ((loopInfo->count == 2) && driver->stop_loop) {
            sampleEndPos = loopInfo->sample_end;
        } else {
            sampleEndPos = loopInfo->loop_end;
        }

        stack_chan_id = chan_id;
        stack_update_idx = update_idx;
        sampleAddr = sample->sample;
        numSamplesToLoadFirstPart = 0;

        // If the frequency requested is more than double that of the raw sample,
        // then the sample processing is split into two parts.
        for (curPart = 0; curPart < numParts; curPart++) {
            numSamplesProcessed = 0;
            dmemUncompressedAddrOffset1 = 0;

            // Adjust the number of samples to load only if there are two parts and an odd number of samples
            if (numParts == 1) {
                numSamplesToLoadAdj = numSamplesToLoad;
            } else if ((s32)numSamplesToLoad & 1) {
                // round down for the first part
                // round up for the second part
                numSamplesToLoadAdj = (numSamplesToLoad & ~1) + (curPart * 2);
            } else {
                numSamplesToLoadAdj = numSamplesToLoad;
            }

            // Load the ADPCM codeBook
            if ((sample->codec == CODEC_ADPCM) || (sample->codec == CODEC_SMALL_ADPCM)) {
                if (AG.adpcm_code_book != sample->book->codebook) {
                    u32 numEntries;

                    switch (bookOffset) {
                        case 1:
                            // AG.adpcm_code_book = &gInvalidAdpcmCodeBook[1];
                            // break;

                        case 2:
                        case 3:
                        default:
                            AG.adpcm_code_book = sample->book->codebook;
                            break;
                    }

                    numEntries = SAMPLE_SIZE * sample->book->order * sample->book->n_predictors;
                    numEntries *= 8; // deviation from MM: multiply numEntries by 8
                    if (numEntries != 0) {
                        aLoadADPCM(cmd++, numEntries, AG.adpcm_code_book);
                    }
                }
            }

            // Continue processing samples until the number of samples needed to load is reached
            while (numSamplesProcessed != numSamplesToLoadAdj) {
                sampleFinished = false;
                loopToPoint = false;
                dmemUncompressedAddrOffset2 = 0;

                numFirstFrameSamplesToIgnore = driver->sample_pos_integer_part & 0xF;
                numSamplesUntilEnd = sampleEndPos - driver->sample_pos_integer_part;

                // Calculate number of samples to process this loop
                numSamplesToProcess = numSamplesToLoadAdj - numSamplesProcessed;

                if ((numFirstFrameSamplesToIgnore == 0) && !driver->at_loop_point) {
                    numFirstFrameSamplesToIgnore = SAMPLES_PER_FRAME;
                }
                numSamplesInFirstFrame = SAMPLES_PER_FRAME - numFirstFrameSamplesToIgnore;

                // Determine the number of samples to decode based on whether the end will be reached or not.
                if (numSamplesUntilEnd > numSamplesToProcess) {
                    // The end will not be reached.
                    numFramesToDecode =
                        (s32)(numSamplesToProcess + SAMPLES_PER_FRAME - 1 - numSamplesInFirstFrame) / SAMPLES_PER_FRAME;
                    numSamplesToDecode = numFramesToDecode * SAMPLES_PER_FRAME;
                    numTrailingSamplesToIgnore = numSamplesInFirstFrame + numSamplesToDecode - numSamplesToProcess;
                } else {
                    // The end will be reached.
                    numSamplesToDecode = numSamplesUntilEnd - numSamplesInFirstFrame;
                    if (numSamplesToDecode <= 0) {
                        numSamplesToDecode = 0;
                        numSamplesInFirstFrame = numSamplesUntilEnd;
                    }
                    numTrailingSamplesToIgnore = 0;
                    numFramesToDecode = (numSamplesToDecode + SAMPLES_PER_FRAME - 1) / SAMPLES_PER_FRAME;
                    if (loopInfo->count != 0) {
                        if ((loopInfo->count == 2) && driver->stop_loop) {
                            sampleFinished = true;
                        } else {
                            // Loop around and restart
                            loopToPoint = true;
                        }
                    } else {
                        sampleFinished = true;
                    }
                }

                // Set parameters based on compression type
                switch (sample->codec) {
                    case CODEC_ADPCM:
                        // 16 2-byte samples (32 bytes) compressed into 4-bit samples (8 bytes) + 1 header byte
                        frameSize = 9;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        zeroOffset = 0;
                        break;

                    case CODEC_SMALL_ADPCM:
                        // 16 2-byte samples (32 bytes) compressed into 2-bit samples (4 bytes) + 1 header byte
                        frameSize = 5;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        zeroOffset = 0;
                        break;

                    case CODEC_UNK7:
                        // 2 2-byte samples (4 bytes) processed without decompression
                        frameSize = 4;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        zeroOffset = 0;
                        break;

                    case CODEC_S8:
                        // 16 2-byte samples (32 bytes) compressed into 8-bit samples (16 bytes)
                        frameSize = 16;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        zeroOffset = 0;
                        break;

                    case CODEC_REVERB:
                        reverbAddrSrc = (void*)0xFFFFFFFF;
                        if (NA_SOUND_CALLBACK != NULL) {
                            // ???
                            reverbAddrSrc = (void*)((u32)NA_SOUND_CALLBACK(sample, numSamplesToLoadAdj, flags, chan_id) & 0xFF);
                        }

                        if ((s32)reverbAddrSrc == 0xFFFFFFFF) {
                            sampleFinished = true;
                        } else if ((s32)reverbAddrSrc == 0) {
                            return cmd;
                        } else {
                            Nas_LoadBuffer2(cmd++, DMEM_UNCOMPRESSED_NOTE,
                                numSamplesToLoadAdj * SAMPLE_SIZE + SAMPLES_PER_FRAME * SAMPLE_SIZE,
                                (s32)reverbAddrSrc);
                            // deviation from MM:
                            goto codec_continue_and_skip;
                            // flags = A_CONTINUE;
                            // skipBytes = 0;
                            // numSamplesProcessed = numSamplesToLoadAdj;
                            // dmemUncompressedAddrOffset1 = numSamplesToLoadAdj;
                        }
                        goto skip;

                    case CODEC_S16_INMEMORY:
                    case CODEC_UNK6:
                        Nas_ClearBuffer(cmd++, DMEM_UNCOMPRESSED_NOTE,
                            numSamplesToLoadAdj * SAMPLE_SIZE + SAMPLES_PER_FRAME * SAMPLE_SIZE);
codec_continue_and_skip:
                        skipBytes = 0;
                        flags = A_CONTINUE;
                        numSamplesProcessed = numSamplesToLoadAdj;
                        dmemUncompressedAddrOffset1 = numSamplesToLoadAdj;
                        goto skip;

                    case CODEC_S16:
                        Nas_ClearBuffer(cmd++, DMEM_UNCOMPRESSED_NOTE,
                            numSamplesToLoadAdj * SAMPLE_SIZE + SAMPLES_PER_FRAME * SAMPLE_SIZE);
                        skipBytes = 0;
                        flags = A_CONTINUE;
                        numSamplesProcessed = numSamplesToLoadAdj;
                        dmemUncompressedAddrOffset1 = numSamplesToLoadAdj;
                        goto skip;

                    default:
                        break;
                }

                sampleDataChunkSize = ALIGN_PREV((numFramesToDecode * frameSize) + 31, 16);
                sampleDataDmemAddr = DMEM_COMPRESSED_ADPCM_DATA - sampleDataChunkSize;

                // Move the compressed raw sample data from ram into the rsp (DMEM)
                if (numFramesToDecode != 0) {
                    // Get the offset from the start of the sample to where the sample is currently playing from
                    frameIndex = (skipInitialSamples + driver->sample_pos_integer_part  - numFirstFrameSamplesToIgnore) /
                                    SAMPLES_PER_FRAME;
                    sampleAddrOffset = frameIndex * frameSize;
                    tmpSamplesToLoadAddr = sampleAddr + sampleAddrOffset;
                    tmpSamplesToLoadAddr += zeroOffset;

                    // Get the ram address of the requested sample chunk
                    if (sample->medium == MEDIUM_RAM) {
                        // Sample is already loaded into ram
                        if (sample->bit31 == TRUE) {
                            samplesToLoadAddr = (u8*)(*NA_SYNC_PROC)(tmpSamplesToLoadAddr, numFramesToDecode * frameSize);
                        } else {
                            samplesToLoadAddr = tmpSamplesToLoadAddr;
                        }
                    } else if (AG._2A14) { // always false
                        return cmd;
                    } else if (sample->medium == MEDIUM_DISK) {
                        // This medium is unsupported so terminate processing this chan
                        return cmd;
                    } else {
                        // This medium is not in ram, so dma the requested sample into ram
#ifdef TARGET_PC
                        samplesToLoadAddr = (u8*)Nas_WaveDmaCallBack((uintptr_t)(tmpSamplesToLoadAddr),
#else
                        samplesToLoadAddr = (u8*)Nas_WaveDmaCallBack((u32)(tmpSamplesToLoadAddr),
#endif
                        sampleDataChunkSize, flags,
                            &driver->sample_dma_idx, sample->medium);
                    }

                    if (samplesToLoadAddr == NULL) {
                        // The ram address was unsuccessfully allocated
                        return cmd;
                    }


                    // Move the raw sample chunk from ram to the rsp
                    // DMEM at the addresses before DMEM_COMPRESSED_ADPCM_DATA
                    sampleDataChunkAlignPad = (u32)samplesToLoadAddr & 0xF;
                    aLoadCache(cmd++, samplesToLoadAddr - sampleDataChunkAlignPad, sampleDataDmemAddr,
                                sampleDataChunkSize);
                } else {
                    numSamplesToDecode = 0;
                    sampleDataChunkAlignPad = 0;
                }

                if (driver->at_loop_point) {
                    aSetLoop(cmd++, sample->loop->predictor_state);
                    flags = A_LOOP;
                    driver->at_loop_point = false;
                }

                numSamplesInThisIteration = numSamplesToDecode + numSamplesInFirstFrame - numTrailingSamplesToIgnore;

                if (numSamplesProcessed == 0) {
                    //! FAKE:
                    if (1) {}
                    skipBytes = numFirstFrameSamplesToIgnore * SAMPLE_SIZE;
                } else {
                    dmemUncompressedAddrOffset2 = ALIGN_NEXT(dmemUncompressedAddrOffset1 + 8 * SAMPLE_SIZE, 16);
                }

                // Decompress the raw sample chunks in the rsp
                // Goes from adpcm (compressed) sample data to pcm (uncompressed) sample data
                switch (sample->codec) {
                    case CODEC_ADPCM:
                        aSetBuffer(cmd++, 0, sampleDataDmemAddr + sampleDataChunkAlignPad,
                                    DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset2,
                                    numSamplesToDecode * SAMPLE_SIZE);
                        aADPCMdec(cmd++, flags, driver->synth_params->adpcm_state);
                        break;

                    case CODEC_SMALL_ADPCM:
                        aSetBuffer(cmd++, 0, sampleDataDmemAddr + sampleDataChunkAlignPad,
                                    DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset2,
                                    numSamplesToDecode * SAMPLE_SIZE);
                        aADPCMdec(cmd++, flags | A_ADPCM_SHORT, driver->synth_params->adpcm_state);
                        break;

                    case CODEC_S8:
                        Nas_SetBuffer(cmd++, 0, sampleDataDmemAddr + sampleDataChunkAlignPad,
                                                DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset2,
                                                numSamplesToDecode * SAMPLE_SIZE);
                        Nas_PCM8dec(cmd++, flags, (s32)driver->synth_params->adpcm_state);
                        break;

                    case CODEC_UNK7:
                    default:
                        // No decompression
                        break;
                }

                if (numSamplesProcessed != 0) {
                    aDMEMMove(cmd++,
                                DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset2 +
                                    (numFirstFrameSamplesToIgnore * SAMPLE_SIZE),
                                DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset1,
                                numSamplesInThisIteration * SAMPLE_SIZE);
                }

                numSamplesProcessed += numSamplesInThisIteration;

                switch (flags) {
                    case A_INIT:
                        skipBytes = SAMPLES_PER_FRAME * SAMPLE_SIZE;
                        dmemUncompressedAddrOffset1 = numSamplesToDecode * SAMPLE_SIZE + SAMPLES_PER_FRAME * SAMPLE_SIZE;
                        break;

                    case A_LOOP:
                        dmemUncompressedAddrOffset1 =
                            numSamplesInThisIteration * SAMPLE_SIZE + dmemUncompressedAddrOffset1;
                        break;

                    default:
                        if (dmemUncompressedAddrOffset1 != 0) {
                            dmemUncompressedAddrOffset1 =
                                numSamplesInThisIteration * SAMPLE_SIZE + dmemUncompressedAddrOffset1;
                        } else {
                            dmemUncompressedAddrOffset1 =
                                (numFirstFrameSamplesToIgnore + numSamplesInThisIteration) * SAMPLE_SIZE;
                        }
                        break;
                }

                flags = A_CONTINUE;

            skip:

                // Update what to do with the samples next
                if (sampleFinished) {
                    s32 dmemClearCount = numSamplesToLoadAdj - numSamplesProcessed;
                    if (dmemClearCount != 0) {
                        Nas_ClearBuffer(cmd++, DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset1,
                            dmemClearCount * SAMPLE_SIZE);
                    }
                    finished = true;
                    chan->common_ch.finished = true;
                    __Nas_WaveTerminateProcess(stack_update_idx, stack_chan_id);
                    break; // break out of the for-loop
                } else if (loopToPoint) {
                    driver->at_loop_point = true;
                    driver->sample_pos_integer_part = loopInfo->loop_start;
                } else {
                    driver->sample_pos_integer_part += numSamplesToProcess;
                }
            }

            switch (numParts) {
                case 1:
                    sampleDmemBeforeResampling = DMEM_UNCOMPRESSED_NOTE + skipBytes;
                    break;

                case 2:
                    switch (curPart) {
                        case 0:
                            Nas_HalfCut(cmd++, DMEM_UNCOMPRESSED_NOTE + skipBytes,
                                                DMEM_TEMP + (SAMPLES_PER_FRAME * SAMPLE_SIZE),
                                                ALIGN_NEXT(numSamplesToLoadAdj / 2, 8));
                            numSamplesToLoadFirstPart = numSamplesToLoadAdj;
                            sampleDmemBeforeResampling = DMEM_TEMP + (SAMPLES_PER_FRAME * SAMPLE_SIZE);
                            if (finished) {
                                Nas_ClearBuffer(cmd++, sampleDmemBeforeResampling + numSamplesToLoadFirstPart,
                                                        numSamplesToLoadAdj + SAMPLES_PER_FRAME);
                            }
                            break;

                        case 1:
                            Nas_HalfCut(cmd++, DMEM_UNCOMPRESSED_NOTE + skipBytes,
                                                DMEM_TEMP + (SAMPLES_PER_FRAME * SAMPLE_SIZE) + numSamplesToLoadFirstPart,
                                                ALIGN_NEXT(numSamplesToLoadAdj / 2, 8));
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            if (finished) {
                break;
            }
        }

        // Update the flags for the signal processing below
        flags = A_CONTINUE;
        if (common->needs_init == true) {
            flags = A_INIT;
            common->needs_init = false;
        }

        // Resample the decompressed mono-signal to the correct pitch
        cmd = Nas_Synth_Resample(cmd, driver, size, frequencyFixedPoint,
                                    sampleDmemBeforeResampling, flags | something_unused_from_sm64);

        // Not present in MM
        if (bookOffset != 0) {
            Nas_NoiseFilter(cmd++, DMEM_TEMP, samples_per_update, NOISE_TABLE[(bookOffset >> 4) & 0xF], NOISE_TABLE[bookOffset & 0xF]);
        }

        // Apply the gain to the mono-signal to adjust the volume
        gain = common->gain;
        if (gain != 0) {
            // A gain of 0x10 (a UQ4.4 number) is equivalent to 1.0 and represents no volume change
            if (gain < 0x10) {
                gain = 0x10;
            }
            Nas_DistFilter(cmd++, gain, DMEM_TEMP, 0, size + SAMPLES_PER_FRAME * SAMPLE_SIZE);
        }

        // Not in MM
        if (!STOP_VELOCONV) {
            // Load the velocity convolution table into DMEM_0x800
            s32 vel_conv_idx = driver->vel_conv_table_idx;
#ifdef TARGET_PC
            aLoadBuffer2(cmd++, VELOCONV_TABLE[vel_conv_idx], 0x800, sizeof(VELOCONV_TABLE[vel_conv_idx]));
#else
            aLoadBuffer2(cmd++, (u32)VELOCONV_TABLE[vel_conv_idx], 0x800, sizeof(VELOCONV_TABLE[vel_conv_idx]));
#endif
            aUnkCmd3(cmd++, DMEM_TEMP, 0x800, samples_per_update);
        }

        // Apply the filter to the mono-signal
        filter = common->filter;
        if (filter != 0) {
            Nas_FirLoadTable(cmd++, size, filter);
            Nas_FirFilter(cmd++, flags, DMEM_TEMP, driver->synth_params->filter_state);
        }

        // Apply the comb filter to the mono-signal by taking the signal with a small temporal offset,
        // and adding it back to itself
        combFilterSize = common->comb_filter_size;
        combFilterGain = common->comb_filter_gain;
        combFilterState = driver->synth_params->comb_filter_state;
        if ((common->comb_filter_size != 0) && (common->comb_filter_gain != 0)) {
            Nas_DMEMMove(cmd++, DMEM_TEMP, DMEM_COMB_TEMP, size);
            // combFilterDmem = DMEM_COMB_TEMP - combFilterSize;
            if (driver->comb_filter_needs_init) {
                Nas_ClearBuffer(cmd++, DMEM_COMB_TEMP - combFilterSize, combFilterSize);
                driver->comb_filter_needs_init = false;
            } else {
                Nas_LoadBuffer2(cmd++, DMEM_COMB_TEMP - combFilterSize, combFilterSize, (s32)combFilterState);
            }
            Nas_SaveBuffer2(cmd++, DMEM_TEMP - combFilterSize + size, combFilterSize, (s32)combFilterState);
            Nas_Mix(cmd++, size >> 4, combFilterGain, DMEM_COMB_TEMP, DMEM_COMB_TEMP - combFilterSize);
            Nas_DMEMMove(cmd++, DMEM_COMB_TEMP - combFilterSize, DMEM_TEMP, size);
        } else {
            driver->comb_filter_needs_init = true;
        }

        // Determine the behavior of the audio processing that leads to the haas effect
        if ((common->haas_effect_left_delay_size != 0) || (driver->prev_haas_effect_left_delay_size != 0)) {
            haasEffectDelaySide = HAAS_EFFECT_DELAY_LEFT;
        } else if ((common->haas_effect_right_delay_size != 0) || (driver->prev_haas_effect_right_delay_size != 0)) {
            haasEffectDelaySide = HAAS_EFFECT_DELAY_RIGHT;
        } else {
            haasEffectDelaySide = HAAS_EFFECT_DELAY_NONE;
        }

        // Apply an unknown effect based on the surround sound-mode
        if (AG.sound_mode == SOUND_OUTPUT_DOLBY_SURROUND) {
            // common->target_volume_left = common->target_volume_left >> 1;
            // common->target_volume_right = common->target_volume_right >> 1;
            if (common->surround_effect_idx != 0xFF) {
                cmd = Nas_DolbySurround(cmd, common, driver, samples_per_update, DMEM_TEMP, flags);
            }
        }

        // Split the mono-signal into left and right channels:
        // Both for dry signal (to go to the speakers now)
        // and for wet signal (to go to a reverb buffer to be stored, and brought back later to produce an echo)
        cmd = Nas_Synth_Envelope(cmd, common, driver, samples_per_update, DMEM_TEMP, haasEffectDelaySide, flags);

        // Apply the haas effect by delaying either the left or the right channel by a small amount
        if (common->use_haas_effect) {
            if (!(flags & A_INIT)) {
                flags = A_CONTINUE;
            }
            cmd = Nas_Synth_Delay(cmd, common, driver, size, flags, haasEffectDelaySide);
        }
    }

    return cmd;
}

Acmd* Nas_DolbySurround(Acmd* cmd, commonch* common, driverch* driver, s32 num_samples_per_update, s32 haas_dmem, s32 flags) {
    s32 size;
    u16 wetGain;
    u16 dryGain;
    s64 dmem = DMEM_SURROUND_TEMP;
    f32 decayGain;

    size = num_samples_per_update * SAMPLE_SIZE;
    Nas_DMEMMove(cmd++, haas_dmem, DMEM_HAAS_TEMP, size);
    dryGain = driver->surround_effect_gain;

    if (flags == A_INIT) {
        aClearBuffer(cmd++, dmem, sizeof(driver->synth_params->surround_effect_state));
        driver->surround_effect_gain = 0;
    } else {
        wetGain = (driver->surround_effect_gain * driver->cur_reverb_vol) >> 7;
        
        aLoadBuffer2(cmd++, driver->synth_params->surround_effect_state, dmem, sizeof(driver->synth_params->surround_effect_state));
        
        aMix(cmd++, size >> 4, dryGain, dmem, DMEM_LEFT_CH);
        aMix(cmd++, size >> 4, (u16)(dryGain ^ 0xFFFF), dmem, DMEM_RIGHT_CH);
        
        aMix(cmd++, size >> 4, wetGain, dmem, DMEM_WET_LEFT_CH);
        aMix(cmd++, size >> 4, (wetGain ^ 0xFFFF), dmem, DMEM_WET_RIGHT_CH);
    }

    aSaveBuffer2(cmd++, driver->synth_params->surround_effect_state, DMEM_SURROUND_TEMP + size, sizeof(driver->synth_params->surround_effect_state));
    
    decayGain = (common->target_volume_left + common->target_volume_right) / 8192.0f;
    if (decayGain > 1.0f) {
        decayGain = 1.0f;
    }

    decayGain = decayGain * StereoLeft[127 - common->surround_effect_idx];
    driver->surround_effect_gain = ((decayGain * 0x7FFF) + driver->surround_effect_gain) / 2;

    Nas_DMEMMove(cmd++, DMEM_HAAS_TEMP, haas_dmem, size);

    return cmd;
}

extern Acmd* Nas_Synth_Resample(Acmd* cmd, const driverch* driver, s32 size, u16 pitch, u16 sampleDmemBeforeResampling, s32 flags) {
    if (pitch == 0) {
        Nas_ClearBuffer(cmd++, DMEM_TEMP, size);
    } else {
        aSetBuffer(cmd++, 0, sampleDmemBeforeResampling, DMEM_TEMP, size);
        aResample(cmd++, flags, pitch, driver->synth_params->final_resample_state);
    }

    return cmd;
}

// @non-matching - issues with aSetEnvParam2 macro
extern Acmd* Nas_Synth_Envelope(Acmd* cmd, commonch* common, driverch* driver, s32 samples_per_update, u16 dmem, s32 haasEffectDelaySide, s32 flags) {
    s32 targetReverbVol = common->target_reverb_volume;
    u32 curVolLeft = driver->current_volume_left & 0xFFFF;
    u32 curVolRight = driver->current_volume_right & 0xFFFF;
    u16 targetVolLeft = common->target_volume_left << 4;
    u16 targetVolRight = common->target_volume_right << 4;
    u32 dmemDests;
    s32 curReverbVolAndFlags;
    u16 curReverbVol;
    s16 rampLeft;
    s16 rampRight;
    s16 rampReverb;
    f32 defaultPanVolume;

    
    // targetReverbVol = common->target_reverb_volume;
    // curVolLeft = driver->current_volume_left;
    // curVolRight = driver->current_volume_right;

    // targetVolLeft = common->target_volume_left << 4;
    // targetVolRight = common->target_volume_right << 4;

    if (AG.sound_mode == SOUND_OUTPUT_DOLBY_SURROUND) {
        u8 idx = common->surround_effect_idx;
        
        if (idx != 0xFF) {
            defaultPanVolume = StereoLeft[idx];
            targetVolLeft *= defaultPanVolume;
            targetVolRight *= defaultPanVolume;
        }
    }

    if (targetVolLeft != (u32)curVolLeft) {
        rampLeft = (targetVolLeft - (s32)curVolLeft) / (samples_per_update >> 3);
    } else {
        rampLeft = 0;
    }

    if (targetVolRight != (u32)curVolRight) {
        rampRight = (targetVolRight - (s32)curVolRight) / (samples_per_update >> 3);
    } else {
        rampRight = 0;
    }

    curReverbVolAndFlags = (s16)driver->cur_reverb_vol;
    if (targetReverbVol != curReverbVolAndFlags) {
        curReverbVol = curReverbVolAndFlags & 0x7F;
        rampReverb = (((targetReverbVol & 0x7F) - (curReverbVol)) << 9) / (samples_per_update >> 3);
        driver->cur_reverb_vol = targetReverbVol;
    } else {
        rampReverb = 0;
    }

    driver->current_volume_left = curVolLeft + (rampLeft * (samples_per_update >> 3));
    driver->current_volume_right = curVolRight + (rampRight * (samples_per_update >> 3));

    if (common->use_haas_effect) {
        // curReverbVol = curReverbVolAndFlags & 0x7F;
        Nas_ClearBuffer(cmd++, DMEM_HAAS_TEMP, DMEM_1CH_SIZE);
        Nas_SetEnvParam(cmd++, (curReverbVolAndFlags & 0x7F) * 2, rampReverb, rampLeft, rampRight);
        Nas_SetEnvParam2(cmd++, curVolLeft, curVolRight);

        switch (haasEffectDelaySide) {
            case HAAS_EFFECT_DELAY_LEFT:
                // Store the left dry channel in a temp space to be delayed to produce the haas effect
                dmemDests = Env_Data_L1;
                break;

            case HAAS_EFFECT_DELAY_RIGHT:
                // Store the right dry channel in a temp space to be delayed to produce the haas effect
                dmemDests = Env_Data_L2;
                break;

            default: // HAAS_EFFECT_DELAY_NONE
                dmemDests = Env_Data_L3;
                break;
        }
    } else {
        curReverbVol = (curReverbVolAndFlags << 1) & 0xFE;
        aSetEnvParam(cmd++, (curReverbVol), rampReverb, rampLeft, rampRight);

        {
            cmd->words.w0 = _SHIFTL(A_CMD_SETENVPARAM2, 24, 8);
            curVolLeft = _SHIFTL(curVolLeft, 16, 16);
            curVolLeft |= _SHIFTL(curVolRight, 0, 16);
            cmd->words.w1 = curVolLeft;
            // cmd->words.w1 = ((curVolLeft & 0xFFFF) << 16) | (curVolRight & 0xFFFF);
            cmd++;
        }
        // aSetEnvParam2(cmd++, curVolLeft & 0xFFFF, curVolRight & 0xFFFF);
        dmemDests = Env_Data_L3;
    }

    aEnvMixer2(cmd++, dmem, samples_per_update, (curReverbVolAndFlags & 0x80) >> 7,
              common->strong_reverb_right, common->strong_reverb_left,
              common->strong_right, common->strong_left, dmemDests, Env_DataH);

    return cmd;
}

extern Acmd* Nas_Synth_Delay(Acmd* cmd, commonch* common, driverch* driver, s32 size, s32 flags, s32 haasEffectDelaySide) {
    u16 haasEffectDelaySize;
    u16 prevHaasEffectDelaySize;
    u16 dmemDest;
    u16 pitch;

    switch (haasEffectDelaySide) {
        case HAAS_EFFECT_DELAY_LEFT:
            // Delay the sample on the left channel
            // This allows the right channel to be heard first
            dmemDest = DMEM_LEFT_CH;
            haasEffectDelaySize = common->haas_effect_left_delay_size;
            prevHaasEffectDelaySize = driver->prev_haas_effect_left_delay_size;
            driver->prev_haas_effect_left_delay_size = haasEffectDelaySize;
            driver->prev_haas_effect_right_delay_size = 0;
            break;

        case HAAS_EFFECT_DELAY_RIGHT:
            // Delay the sample on the right channel
            // This allows the left channel to be heard first
            dmemDest = DMEM_RIGHT_CH;
            haasEffectDelaySize = common->haas_effect_right_delay_size;
            prevHaasEffectDelaySize = driver->prev_haas_effect_right_delay_size;
            driver->prev_haas_effect_right_delay_size = haasEffectDelaySize;
            driver->prev_haas_effect_left_delay_size = 0;
            break;

        default: // HAAS_EFFECT_DELAY_NONE
            return cmd;
    }

    if (flags != A_INIT) {
        // Slightly adjust the sample rate in order to fit a change in sample delay
        if (haasEffectDelaySize != prevHaasEffectDelaySize) {
            pitch = pitch = (((size << 0xF) / 2) - 1) / ((size + haasEffectDelaySize - prevHaasEffectDelaySize - 2) / 2);
            aSetBuffer(cmd++, 0, DMEM_HAAS_TEMP, DMEM_TEMP, size + haasEffectDelaySize - prevHaasEffectDelaySize);
            aResampleZoh(cmd++, pitch, 0);
        } else {
            aDMEMMove(cmd++, DMEM_HAAS_TEMP, DMEM_TEMP, size);
        }

        if (prevHaasEffectDelaySize != 0) {
            aLoadBuffer2(cmd++, driver->synth_params->haas_effect_delay_state, DMEM_HAAS_TEMP,
                        ALIGN_NEXT(prevHaasEffectDelaySize, 16));
            aDMEMMove(cmd++, DMEM_TEMP, DMEM_HAAS_TEMP + prevHaasEffectDelaySize,
                      size + haasEffectDelaySize - prevHaasEffectDelaySize);
        } else {
            aDMEMMove(cmd++, DMEM_TEMP, DMEM_HAAS_TEMP, size + haasEffectDelaySize);
        }
    } else {
        // Just apply a delay directly
        aDMEMMove(cmd++, DMEM_HAAS_TEMP, DMEM_TEMP, size);
        if (haasEffectDelaySize) { // != 0
            aClearBuffer(cmd++, DMEM_HAAS_TEMP, haasEffectDelaySize);
        }
        aDMEMMove(cmd++, DMEM_TEMP, DMEM_HAAS_TEMP + haasEffectDelaySize, size);
    }

    if (haasEffectDelaySize) { // != 0
        // Save excessive samples for next iteration
        aSaveBuffer2(cmd++, driver->synth_params->haas_effect_delay_state, DMEM_HAAS_TEMP + size,
                    ALIGN_NEXT(haasEffectDelaySize, 16));
    }

    aAddMixer(cmd++, ALIGN_NEXT(size, 64), DMEM_HAAS_TEMP, dmemDest, 0x7FFF);

    return cmd;
}
