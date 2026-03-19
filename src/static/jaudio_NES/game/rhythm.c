#include "jaudio_NES/rhythm.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/game64.h"
#include "jaudio_NES/audiowork.h"

typedef struct NA_RHYTHM_BUFFER {
    /* 0x0 */ u8 state;
    /* 0x1 */ s8 current_subtrack;
    /* 0x2 */ u8 unk2[0x2];
    /* 0x4 */ u32 current_buffer_id;
    /* 0x8 */ s8 unk8;
    /* 0x9 */ s8 unk9;
    /* 0xA */ u8 unkA[0x2];
} NA_RHYTHM_BUFFER;

typedef enum RythmBuffer_State {
    NA_RHYTHM_BUFFER_STOPPED,
    NA_RHYTHM_BUFFER_ALLOC,
    NA_RHYTHM_BUFFER_STARTED,
} RythmBuffer_State;

static s16 rhythm_beat_type = -1;

static NA_RHYTHM_BUFFER rhythm_buffer[14];

static s8 Na_GetRhythmSeNum(s8 num, sub* sub);
static s8 Na_RhythmGrpProcess(s8 arg0, group* group);

extern void Na_RhythmInit() {
    int i;

    for (i = 0; i < 14; i++) {
        rhythm_buffer[i].state = NA_RHYTHM_BUFFER_STOPPED;
        rhythm_buffer[i].current_subtrack = i;
    }

#ifdef TARGET_PC
    Nap_SetPtr(NA_MAKE_COMMAND(228, 0, 0, 0), (void*)Na_GetRhythmSeNum);
    Nap_SetPtr(NA_MAKE_COMMAND(228, 0, 0, 1), (void*)Na_RhythmGrpProcess);
#else
    Nap_SetS32(NA_MAKE_COMMAND(228, 0, 0, 0), (s32)Na_GetRhythmSeNum);
    Nap_SetS32(NA_MAKE_COMMAND(228, 0, 0, 1), (s32)Na_RhythmGrpProcess);
#endif
}

static NA_RHYTHM_BUFFER* rhythm_buffer_alloc() {
    int i;

    NA_RHYTHM_BUFFER* buf;

    for (i = 0; i < 14; i++) {
        buf = &rhythm_buffer[i];

        if (buf->state == NA_RHYTHM_BUFFER_STOPPED) {
            buf->state = NA_RHYTHM_BUFFER_ALLOC;
            return buf;
        }
    }

    return nullptr;
}

static NA_RHYTHM_BUFFER* get_rhythm_buffer(u32 idx) {
    int i;
    NA_RHYTHM_BUFFER* buf;

    for (i = 0; i < 14; i++) {
        buf = &rhythm_buffer[i];

        if (buf->state != NA_RHYTHM_BUFFER_STOPPED && idx == buf->current_buffer_id) {
            return buf;
        }
    }

    return nullptr;
}

extern s8 Na_GetRhythmSubTrack(u32 idx) {
    NA_RHYTHM_BUFFER* buf;

    buf = get_rhythm_buffer(idx);
    if (buf == nullptr) {
        return -1;
    }
    return buf->current_subtrack;
}

static void rhythm_start(NA_RHYTHM_BUFFER* buffer) {
    if (buffer != nullptr) {
        Nap_SetS8(NA_MAKE_COMMAND(6, 2, buffer->current_subtrack, 0), 0);
        Nap_SetS8(NA_MAKE_COMMAND(6, 2, buffer->current_subtrack, 3), buffer->unk8);
        Nap_SetS8(NA_MAKE_COMMAND(6, 2, buffer->current_subtrack, 7), buffer->unk9);
        buffer->state = NA_RHYTHM_BUFFER_STARTED;
    }
}

static void rhythm_stop(NA_RHYTHM_BUFFER* buffer) {
    if (buffer != nullptr) {
        if (buffer->state == NA_RHYTHM_BUFFER_STARTED) {
            Nap_SetS8(NA_MAKE_COMMAND(6, 2, buffer->current_subtrack, 0), 1);
        }

        buffer->state = NA_RHYTHM_BUFFER_STOPPED;
    }
}

extern void Na_RhythmStart(u32 idx, s8 arg1, s8 arg2) {
    NA_RHYTHM_BUFFER* buf;

    buf = get_rhythm_buffer(idx);
    if (buf == nullptr) {
        buf = rhythm_buffer_alloc();
    }
    if (buf != nullptr) {
        buf->current_buffer_id = idx;
        buf->unk8 = arg1;
        buf->unk9 = arg2;
        rhythm_start(buf);
    }
}

extern void Na_RhythmStop(u32 idx) {
    NA_RHYTHM_BUFFER* buf;

    buf = get_rhythm_buffer(idx);
    if (buf != nullptr) {
        rhythm_stop(buf);
    }
}

extern void Na_RhythmAllStop() {
    int i;
    NA_RHYTHM_BUFFER* buf;

    for (i = 0; i < 14; i++) {
        buf = &rhythm_buffer[i];

        if (buf->state != NA_RHYTHM_BUFFER_STOPPED) {
            rhythm_stop(buf);
        }
    }
}

static s16 Na_GetRhythmBeatType(void) {
    if (AG.groups[sou_now_bgm_handle].flags.enabled != 0) {
        rhythm_beat_type = Nap_ReadGrpPort(sou_now_bgm_handle, 1);
    }
    return rhythm_beat_type;
}

extern f32 Na_GetRhythmAnimCounter(u32 idx) {
    f32 f31 = 0.0f;
    NA_RHYTHM_BUFFER* buf = get_rhythm_buffer(idx);
    s16 r30;
    s16 r29;
    int r28;
    s16 r27;

    if (buf == nullptr) {
        return -2.0f;
    }

    if (Nap_ReadSubPort(2, buf->current_subtrack, 1) == 0) {
        if (Nap_ReadSubPort(2, buf->current_subtrack, 6) <= 1) {
            return -1.0f;
        }
        return -2.0f;
    }

    r30 = Nap_ReadSubPort(2, buf->current_subtrack, 4);
    r29 = Nap_ReadSubPort(2, buf->current_subtrack, 5);
    r27 = Nap_ReadGrpPort(2, 3);
    if (r30 == 0) {
        return 0.0f;
    }

    if (Na_GetRhythmBeatType() == 0) {
        if (Nap_ReadGrpPort(2, 2) % 2 != 0) {
            r28 = 32;
        } else {
            r28 = 16;
        }
    } else {
        r28 = 24;
    }

    r30 = (r29 - r30) * r28;
    r30 += r27;
    r29 *= r28;
    f31 = (f32)r30 / (f32)r29;
    return f31;
}

extern s8 Na_GetRhythmDelay(u32 idx) {
    NA_RHYTHM_BUFFER* buf;
    s8 delay = 0;

    buf = get_rhythm_buffer(idx);
    if (buf == nullptr) {
        return -1;
    }
    delay = Nap_ReadSubPort(2, buf->current_subtrack, 7);

    return delay;
}

static s8 Na_GetRhythmSeNum(s8 num, sub* sub) {
    u32 rand;

    if (num == 0) {
        num = 16 - sub->port[4];
        if (num == 16) {
            num = 0;
        }
    } else {
        rand = Nap_GetRandom();
        switch (sub->port[3]) {
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x50:
            case 0x51:
            case 0x52:
            case 0x5A:
                num = rand & 7;
                break;
            case 0xC:
            case 0xD:
            case 0xE:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1A:
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x21:
            case 0x22:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x27:
            case 0x28:
            case 0x29:
            case 0x2A:
            case 0x2B:
            case 0x2C:
            case 0x2D:
            case 0x2E:
            case 0x37:
            case 0x38:
            case 0x39:
            case 0x3A:
            case 0x3B:
            case 0x3E:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x43:
            case 0x4C:
            case 0x4D:
            case 0x4E:
            case 0x4F:
            case 0x58:
            case 0x59:
            case 0x5E:
            case 0x5F:
            case 0x60:
            case 0x61:
            case 0x62:
            case 0x63:
            case 0x64:
            case 0x65:
            case 0x66:
            case 0x67:
            case 0x68:
            case 0x69:
            case 0x6A:
            case 0x6B:
            case 0x6C:
            case 0x6D:
            case 0x6E:
            case 0x6F:
            case 0x70:
            case 0x71:
            case 0x72:
            case 0x73:
            case 0x74:
            case 0x75:
            case 0x76:
            case 0x77:
            case 0x78:
            case 0x79:
            case 0x7A:
            case 0x7B:
            case 0x7C:
                num = (rand % 6);
                break;
            case 0x53:
            case 0x54:
            case 0x55:
            case 0x56:
            case 0x57:
                num = (rand % 5);
                break;
            case 0x3C:
            case 0x3D:
            case 0x5D:
                num = rand & 3;
                break;
            case 0x5:
            case 0xF:
            case 0x2F:
            case 0x44:
            case 0x45:
            case 0x46:
            case 0x47:
            case 0x48:
            case 0x49:
            case 0x4A:
            case 0x4B:
                num = (rand % 3);
                break;
            default:
                num = 0;
                break;
        }
    }
    return num;
}

extern void Na_GetRhythmInfo(TempoBeat_c* tempo) {
    if (tempo != nullptr) {
        tempo->tempo = (AG.groups[2].tempo / AUDIO_TATUMS_PER_BEAT);
        tempo->beat = Na_GetRhythmBeatType();
    }
}

extern void Na_SetRhythmInfo(TempoBeat_c* tempo) {
    (tempo != nullptr);
    if ((tempo == nullptr) || (tempo->tempo == 0)) {
        Nap_SetS32(NA_MAKE_COMMAND(71, 2, 0, 0), 120);
        rhythm_beat_type = -1;
    } else {
        Nap_SetS32(NA_MAKE_COMMAND(71, 2, 0, 0), tempo->tempo);
        rhythm_beat_type = tempo->beat;
    }
}

static void tempo_adjust(group* group) {
    int tempo = (AG.groups[2].tempo / AUDIO_TATUMS_PER_BEAT);
    int newTempo;
    if (AG.groups[sou_now_bgm_handle].flags.enabled != 0) {
        newTempo = (AG.groups[sou_now_bgm_handle].tempo / AUDIO_TATUMS_PER_BEAT);

        if (tempo > newTempo) {
            tempo--;
        } else if (tempo < newTempo) {
            tempo++;
        }
    }
    group->tempo = tempo * AUDIO_TATUMS_PER_BEAT;
}

static s8 Na_RhythmGrpProcess(s8 arg0, group* group) {
    int r29;
    int r27;
    int r30;
    int r31;
    int ret = 1;
    r29 = AUDIO_TATUMS_PER_BEAT / 2;
    static int pre_beat_type = -1;
    static int pre_frame_per_step = -1;

    tempo_adjust(group);
    if (Na_GetRhythmBeatType() == 0) {
        if (Nap_ReadGrpPort(2, 2) % 2 != 0) {
            r29 = 32;
        } else {
            r29 = 16;
        }
    } else {
        r29 = AUDIO_TATUMS_PER_BEAT / 2;
    }

    /* random call to arg0 so it is stored on the stack, can also do (void)arg0 */
    if (arg0) {}

    r31 = Nap_ReadGrpPort(2, 3);
    if (Nap_ReadGrpPort(2, 2) % 2 != 0) {
        r27 = r31;
    } else if (Na_GetRhythmBeatType() == 0) {
        r27 = r31 + 32;
    } else {
        r27 = r31 + AUDIO_TATUMS_PER_BEAT / 2;
    }

    if (pre_beat_type != rhythm_beat_type) {
        if (pre_frame_per_step > 0) {
            r31 = (r31 * (r29 / (f32)pre_frame_per_step));
        }
        pre_beat_type = rhythm_beat_type;
    }
    pre_frame_per_step = r29;

    if (AG.groups[sou_now_bgm_handle].flags.enabled != 0) {
        int r25 = Nap_ReadGrpPort(sou_now_bgm_handle, 0);
        r30 = r25 - r27;
    } else {
        r30 = 0;
    }

    if (r30 > (AUDIO_TATUMS_PER_BEAT / 2)) {
        r30 -= AUDIO_TATUMS_PER_BEAT;
    }
    if (r30 < (-AUDIO_TATUMS_PER_BEAT / 2)) {
        r30 += AUDIO_TATUMS_PER_BEAT;
    }

    if (r30 > 1 || r30 < -1) {
        if (AG.groups[2].script_counter % 2 != 0) {
            r31++;
        }
    } else {
        r31++;
    }

    if (r31 >= r29) {
        r31 -= r29;
        ret = 0;
    }

    group->port[3] = r31;
    group->port[4] = (s8)((s32)(r31 * 0x64) / r29);

    return ret;
}
