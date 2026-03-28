#include "jaudio_NES/memory.h"

#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/channel.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/os.h"
#include "jaudio_NES/system.h"
#include "dolphin/os.h"

void DirtyWave(s32);
void* __Nas_SzCacheCheck_Inner(s32 a, s32 b, s32 c);
void __RomAddrSet(SwMember*, smzwavetable*);
SwMember* __Nas_Alloc_Single_Stay_Inner(s32 a);
SwMember* __Nas_Alloc_Single_Auto_Inner(s32 a);
void __ExchangeWave(s32, s32);
void __KillSwMember(SwMember* a);
void __Nas_MemoryReconfig();
void Emem_KillSwMember();
void Dirty_AllWave();
void Nas_SetDelayLine(s32 a, fxconfig* b, s32 c);
int Nas_Init_Single(s32, s32);
/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
f32 __CalcRelf(f32 val) {
    return (AG.audio_params.updates_per_frame_inverse_scaled * 256.f) / val;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000170
 */
void MakeReleaseTable() {
    int i;
    AG.adsr_decay_table[0xff] = __CalcRelf(0.25f);
    AG.adsr_decay_table[0xfe] = __CalcRelf(0.33f);
    AG.adsr_decay_table[0xfd] = __CalcRelf(0.5f);
    AG.adsr_decay_table[0xfc] = __CalcRelf(0.66f);
    AG.adsr_decay_table[0xfb] = __CalcRelf(0.75f);
    for (i = 0x80; i < 0xfb; i++) {
        AG.adsr_decay_table[i] = __CalcRelf(0xfb - i);
    }
    for (i = 0x10; i < 0x80; i++) {
        AG.adsr_decay_table[i] = __CalcRelf((0x80 - i) * 4 + 0x3c);
    }
    for (i = 1; i < 0x10; i++) {
        AG.adsr_decay_table[i] = __CalcRelf((0xf - i) * 0x3c + 0x1e0);
    }
    AG.adsr_decay_table[0] = 0.f;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void Nas_ResetIDtable() {
    int i;
    for (i = 0; i < ARRAY_COUNT(AG.bank_load_status); i++) {
        if (AG.bank_load_status[i] != 5)
            AG.bank_load_status[i] = 0;
    }
    for (i = 0; i < ARRAY_COUNT(AG.wave_load_status); i++) {
        if (AG.wave_load_status[i] != 5)
            AG.wave_load_status[i] = 0;
    }
    for (i = 0; i < ARRAY_COUNT(AG.sequence_load_status); i++) {
        if (AG.sequence_load_status[i] != 5)
            AG.sequence_load_status[i] = 0;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000E0
 */
void Nas_ForceStopChannel(s32 bankID) {
    int i;
    for (i = 0; i < AG.num_channels; i++) {
        channel* channel = &AG.channels[i];
        if (channel->playback_ch.bank_id == bankID) {
            if (channel->playback_ch.status == 0 && channel->playback_ch.priority != 0) {
                channel->playback_ch.current_parent_note->enabled = FALSE;
                channel->playback_ch.current_parent_note->finished = TRUE;
            }
            Nas_StopVoice(channel);
            Nas_CutList(&channel->link);
            Nas_AddList(&AG.channel_node.freeList, &channel->link);
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void Nas_ForceReleaseChannel(s32 param_1) {
    // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000084
 */
void Nas_ForceStopSeq(s32 id) {
    int i;
    for (i = 0; i < AG.audio_params.num_groups; i++) {
        if (AG.groups[i].flags.enabled && AG.groups[i].seq_id == id) {
            Nas_ReleaseGroup(AG.groups_p[i]);
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void* Nas_CacheOff(u8* vaddr, s32 nbytes) {
    osWritebackDCache2(vaddr, nbytes);
    return vaddr;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void* Nas_2ndHeapAlloc_CL(ALHeap* heap, s32 size) {
    void* ret = NULL;
    if (AG.external_heap.base != NULL) {
        ret = Nas_HeapAlloc_CL(&AG.external_heap, size);
    }
    if (ret == NULL) {
        ret = Nas_HeapAlloc_CL(heap, size);
    }
    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void* Nas_2ndHeapAlloc(ALHeap* heap, s32 size) {
    void* ret = NULL;
    if (AG.external_heap.base != NULL) {
        ret = Nas_HeapAlloc(&AG.external_heap, size);
    }
    if (ret == NULL) {
        ret = Nas_HeapAlloc(heap, size);
    }
    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void* Nas_NcHeapAlloc(ALHeap* heap, s32 size) {
    void* ret = Nas_HeapAlloc(heap, size);
    if (ret != NULL) {
        ret = Nas_CacheOff((u8*)ret, size);
    }
    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void* Nas_NcHeapAlloc_CL(ALHeap* heap, s32 size) {
    void* ret = Nas_HeapAlloc_CL(heap, size);
    if (ret != NULL) {
        ret = Nas_CacheOff((u8*)ret, size);
    }
    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000054
 */
void* Nas_HeapAlloc_CL(ALHeap* heap, s32 size) {
    // int i;
    void* ret = Nas_HeapAlloc(heap, size);
    if (ret != NULL) {
        u8* i = (u8*)ret;
        while (i < heap->current) {
            *i++ = 0;
        }
    }
    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Nas_TmpAlloc(ALHeap* param_1, s32 param_2) {
    // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void Nas_HeapFree(ALHeap* param_1) {
    // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80005640
 * Size:	00006C
 */
void* Nas_HeapAlloc(ALHeap* heap, s32 size) {
    s32* REF_size;

    REF_size = &size;
    u32 roundedSize = ALIGN_NEXT(size, 32);
    if (!heap->base) {
        OSReport("Warning: Not Allocated Heap\n");
        return NULL;
    }

    u8* prev = heap->current;
    if (prev + roundedSize <= heap->base + heap->length) {
        heap->current = prev + roundedSize;
    } else {
        return NULL;
    }

    heap->count++;
    heap->last = prev;
    return prev;
}

/*
 * --INFO--
 * Address:	800056C0
 * Size:	000058
 */
void Nas_HeapInit(ALHeap* heap, u8* p2, s32 p3) {
    ALHeap** REF_heap;

    int length;

    REF_heap = &heap;
    heap->count = 0;
    if (!p2) {
        OSReport("Warning: 0 base heap.\n");
        heap->length = 0;
        heap->current = NULL;
        heap->last = NULL;
    } else {
#ifdef TARGET_PC
        length = p3 - ((uintptr_t)p2 & 0x1F);
        heap->base = (u8*)ALIGN_NEXT((uintptr_t)p2, 32);
#else
        length = p3 - ((u32)p2 & 0x1F);
        heap->base = (u8*)ALIGN_NEXT((u32)p2, 32);
#endif
        heap->current = heap->base;
        heap->length = length;
        heap->last = NULL;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Nas_SzStayClear(SZStay* p1) {
    p1->heap.current = p1->heap.base;
    p1->heap.count = NULL;
    p1->num_entries = 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Nas_SzAutoClear(SZAuto* p1) {
    p1->heap.current = p1->heap.base;
    p1->heap.count = 0;
    p1->use_entry_idx = 0;
    p1->entries[0].addr = p1->heap.base;
    p1->entries[1].addr = p1->heap.base + p1->heap.length;
    p1->entries[0].id = -1;
    p1->entries[1].id = -1;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
// void Nas_SzCustomClear(SZCustom*)
// {
// 	// UNUSED FUNCTION
// }

/*
 * --INFO--
 * Address:	........
 * Size:	00010C
 */
void Nas_SzStayDelete(s32 a) {
    SZHeap* r31;
    u8* r30;
    switch (a) {
        case SEQUENCE_TABLE: {
            r31 = &AG.seq_heap;
            r30 = AG.sequence_load_status;
        } break;
        case BANK_TABLE: {
            r31 = &AG.bank_heap;
            r30 = AG.bank_load_status;
        } break;
        case WAVE_TABLE: {
            r31 = &AG.wave_heap;
            r30 = AG.wave_load_status;
        } break;
    }
    ALHeap* heap = &r31->stay_heap.heap;
    if (r31->stay_heap.num_entries != 0) {
        heap->current = r31->stay_heap.entries[r31->stay_heap.num_entries - 1].addr;
        heap->count--;
        if (a == 2) {
            DirtyWave(r31->stay_heap.entries[r31->stay_heap.num_entries - 1].id);
        }
        if (a == 1) {
            Nas_ForceStopChannel(r31->stay_heap.entries[r31->stay_heap.num_entries - 1].id);
        }
        r30[r31->stay_heap.entries[r31->stay_heap.num_entries - 1].id] = 0;
        r31->stay_heap.num_entries--;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void Nas_SzHeapReset(u32 fixSize) {
    OSReport("FixSIZE is %x\n", fixSize);
    Nas_HeapInit(&AG.init_heap, (u8*)AG.audio_heap_p, fixSize);
    Nas_HeapInit(&AG.session_heap, (u8*)AG.audio_heap_p + fixSize, AG.audio_heap_size - fixSize);
    AG.external_heap.base = NULL;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void Nas_SzHeapDivide(AudioHeapstrc* param_1) {
    AG.session_heap.current = AG.session_heap.base;
    Nas_HeapInit(&AG.misc_heap, (u8*)Nas_HeapAlloc(&AG.session_heap, param_1->misc_heap_size), param_1->misc_heap_size);
    Nas_HeapInit(&AG.sz_data_heap, (u8*)Nas_HeapAlloc(&AG.session_heap, param_1->cache_heap_size),
                 param_1->cache_heap_size);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
void Nas_SzDataDivide(DataHeapstrc* param_1) {
    AG.sz_data_heap.current = AG.sz_data_heap.base;
    Nas_HeapInit(&AG.data_heap, (u8*)Nas_HeapAlloc(&AG.sz_data_heap, param_1->data_size), param_1->data_size);
    Nas_HeapInit(&AG.sz_auto_heap, (u8*)Nas_HeapAlloc(&AG.sz_data_heap, param_1->auto_size), param_1->auto_size);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Nas_SzStayDivide(StayHeapstrc* param_1) {
    AG.data_heap.current = AG.data_heap.base;
    Nas_HeapInit(&AG.seq_heap.stay_heap.heap, (u8*)Nas_HeapAlloc(&AG.data_heap, param_1->seq_heap_size),
                 param_1->seq_heap_size);
    Nas_HeapInit(&AG.bank_heap.stay_heap.heap, (u8*)Nas_HeapAlloc(&AG.data_heap, param_1->bank_heap_size),
                 param_1->bank_heap_size);
    Nas_HeapInit(&AG.wave_heap.stay_heap.heap, (u8*)Nas_HeapAlloc(&AG.data_heap, param_1->wave_heap_size),
                 param_1->wave_heap_size);
    Nas_SzStayClear(&AG.seq_heap.stay_heap);
    Nas_SzStayClear(&AG.bank_heap.stay_heap);
    Nas_SzStayClear(&AG.wave_heap.stay_heap);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Nas_SzAutoDivide(AutoHeapstrc* param_1) {
    AG.sz_auto_heap.current = AG.sz_auto_heap.base;
    Nas_HeapInit(&AG.seq_heap.auto_heap.heap, (u8*)Nas_HeapAlloc(&AG.sz_auto_heap, param_1->seqLen), param_1->seqLen);
    Nas_HeapInit(&AG.bank_heap.auto_heap.heap, (u8*)Nas_HeapAlloc(&AG.sz_auto_heap, param_1->bankLen),
                 param_1->bankLen);
    Nas_HeapInit(&AG.wave_heap.auto_heap.heap, (u8*)Nas_HeapAlloc(&AG.sz_auto_heap, param_1->waveLen),
                 param_1->waveLen);
    Nas_SzAutoClear(&AG.seq_heap.auto_heap);
    Nas_SzAutoClear(&AG.bank_heap.auto_heap);
    Nas_SzAutoClear(&AG.wave_heap.auto_heap);
}

/*
 * --INFO--
 * Address:	........
 * Size:	0006CC
 */
void* Nas_SzHeapAlloc(s32 tableType, s32 size, s32 param_3, s32 id) {
    SZAuto* auto_heap;
    SZHeap* sound_heap;
    void* alloc;
    ALHeap* heap;
    u8 status0;
    u8 status1;
    int end;
    ALHeapEntry* entry;
    int checkId;
    u8* outStatus;
    int idx;

    switch (tableType) {
        case SEQUENCE_TABLE: {
            sound_heap = &AG.seq_heap;
            outStatus = AG.sequence_load_status;
        } break;
        case BANK_TABLE: {
            sound_heap = &AG.bank_heap;
            outStatus = AG.bank_load_status;
        } break;
        case WAVE_TABLE: {
            sound_heap = &AG.wave_heap;
            outStatus = AG.wave_load_status;
        } break;
    }

    if (param_3 == 0) {
        auto_heap = &sound_heap->auto_heap;
        heap = &auto_heap->heap;
        if (auto_heap->heap.length < size) {
            return NULL;
        }

        if (auto_heap->entries[0].id == HEAP_INVALID_INDEX) {
            status0 = 0;
        } else {
            status0 = outStatus[auto_heap->entries[0].id];
        }

        if (auto_heap->entries[1].id == HEAP_INVALID_INDEX) {
            status1 = 0;
        } else {
            status1 = outStatus[auto_heap->entries[1].id];
        }

        if (tableType == BANK_TABLE) {
            if (status0 == 4) {
                int i;
                end = AG.num_channels;
                checkId = auto_heap->entries[0].id;
                for (i = 0; i < end; i++) {
                    if (checkId == AG.channels[i].playback_ch.bank_id && AG.channels[i].common_ch.enabled) {
                        break;
                    }
                }

                if (i == AG.num_channels) {
                    Nas_WriteIDbank(auto_heap->entries[0].id, 3);
                    status0 = 3;
                }
            }

            if (status1 == 4) {
                int i;
                end = AG.num_channels;
                for (i = 0; i < end; i++) {
                    if (auto_heap->entries[1].id == AG.channels[i].playback_ch.bank_id &&
                        AG.channels[i].common_ch.enabled) {
                        break;
                    }
                }

                if (i == AG.num_channels) {
                    Nas_WriteIDbank(auto_heap->entries[1].id, 3);
                    status1 = 3;
                }
            }
        }

        if (status0 == 0) {
            auto_heap->use_entry_idx = FALSE;
            goto aftretnull;
        }

        if (status1 == 0) {
            auto_heap->use_entry_idx = TRUE;
            goto aftretnull;
        }

        if (status0 != 3 || status1 != 3) {
            if (status0 == 3) {
                auto_heap->use_entry_idx = FALSE;
                goto aftretnull;
            } else if (status1 == 3) {
                auto_heap->use_entry_idx = TRUE;
                goto aftretnull;
            } else if (tableType == SEQUENCE_TABLE) {
                if (status0 == 2) {
                    int i;
                    end = AG.audio_params.num_groups;
                    for (i = 0; i < end; i++) {
                        if (AG.groups[i].flags.enabled && AG.groups[i].seq_id == auto_heap->entries[0].id) {
                            break;
                        }
                    }
                    if (i == end) {
                        auto_heap->use_entry_idx = FALSE;
                        goto aftretnull;
                    }
                }
                if (status1 == 2) {
                    int i;
                    end = AG.audio_params.num_groups;
                    for (i = 0; i < end; i++) {
                        if (AG.groups[i].flags.enabled && AG.groups[i].seq_id == auto_heap->entries[1].id) {
                            break;
                        }
                    }
                    if (i == end) {
                        auto_heap->use_entry_idx = TRUE;
                        goto aftretnull;
                    }
                }
            } else if (tableType == BANK_TABLE) {
                if (status0 == 2) {
                    int i;
                    end = AG.num_channels;
                    for (i = 0; i < end; i++) {
                        if (auto_heap->entries[0].id == AG.channels[i].playback_ch.bank_id &&
                            AG.channels[i].common_ch.enabled) {
                            break;
                        }
                    }
                    if (i == end) {
                        auto_heap->use_entry_idx = FALSE;
                        goto aftretnull;
                    }
                }
                if (status1 == 2) {
                    int i;
                    end = AG.num_channels;
                    checkId = auto_heap->entries[1].id;
                    for (i = 0; i < end; i++) {
                        if (auto_heap->entries[1].id == AG.channels[i].playback_ch.bank_id &&
                            AG.channels[i].common_ch.enabled) {
                            break;
                        }
                    }
                    if (i == end) {
                        auto_heap->use_entry_idx = TRUE;
                        goto aftretnull;
                    }
                }
            }
        } else {
            goto aftretnull;
        }

        if (auto_heap->use_entry_idx == FALSE) {
            if (status0 == 1) {
                if (status1 == 1) {
                    goto retnull;
                }
                auto_heap->use_entry_idx = TRUE;
            }
        } else {
            if (status1 == 1) {
                if (status0 == 1) {
                    goto retnull;
                }
                auto_heap->use_entry_idx = FALSE;
            }
        }
        goto aftretnull;

    retnull:
        return NULL;
    aftretnull:

        idx = auto_heap->use_entry_idx;
        // entry = &auto_heap->entries[idx];
        if (auto_heap->entries[idx].id != HEAP_INVALID_INDEX) {
            if (tableType == WAVE_TABLE) {
                DirtyWave(auto_heap->entries[idx].id);
            }
            outStatus[auto_heap->entries[idx].id] = 0;
            if (tableType == BANK_TABLE) {
                Nas_ForceStopChannel(auto_heap->entries[idx].id);
            }
        }

        switch (idx) {
            case FALSE: {
                auto_heap->entries[0].addr = heap->base;
                auto_heap->entries[0].id = id;
                auto_heap->entries[0].size = size;
                heap->current = heap->base + size;
                if (auto_heap->entries[1].id != HEAP_INVALID_INDEX && heap->current > auto_heap->entries[1].addr) {
                    if (tableType == WAVE_TABLE) {
                        DirtyWave(auto_heap->entries[1].id);
                    }
                    outStatus[auto_heap->entries[1].id] = 0;
                    switch (tableType) {
                        case SEQUENCE_TABLE: {
                            Nas_ForceStopSeq(auto_heap->entries[1].id);
                        } break;
                        case BANK_TABLE: {
                            Nas_ForceStopChannel(auto_heap->entries[1].id);
                        } break;
                    }
                    auto_heap->entries[1].id = -1;
                    auto_heap->entries[1].addr = heap->base + heap->length;
                }
                alloc = auto_heap->entries[0].addr;
            } break;
            case TRUE: {
                auto_heap->entries[1].addr = (u8*)OSRoundDown32B(heap->base + heap->length - size);
                auto_heap->entries[1].id = id;
                auto_heap->entries[1].size = size;
                if (auto_heap->entries[0].id != HEAP_INVALID_INDEX && heap->current > auto_heap->entries[1].addr) {
                    if (tableType == WAVE_TABLE) {
                        DirtyWave(auto_heap->entries[0].id);
                    }
                    outStatus[auto_heap->entries[0].id] = 0;
                    switch (tableType) {
                        case SEQUENCE_TABLE: {
                            Nas_ForceStopSeq(auto_heap->entries[0].id);
                        } break;
                        case BANK_TABLE: {
                            Nas_ForceStopChannel(auto_heap->entries[0].id);
                        } break;
                    }
                    auto_heap->entries[0].id = HEAP_INVALID_INDEX;
                    heap->current = heap->base;
                }
                alloc = auto_heap->entries[1].addr;
            } break;
            default: {
                return NULL;
            } break;
        }

        // heap->use_entry_idx = !heap->use_entry_idx;
        auto_heap->use_entry_idx ^= TRUE;
        return alloc;
    } else { // param_3 != 0
        alloc = Nas_HeapAlloc(&sound_heap->stay_heap.heap, size);
        sound_heap->stay_heap.entries[sound_heap->stay_heap.num_entries].addr = (u8*)alloc;
        if (alloc == NULL) {
            switch (param_3) {
                case 2: {
                    return Nas_SzHeapAlloc(tableType, size, 0, id);
                } break;
                case 0:
                case 1: {
                    return NULL;
                } break;
            }
        }
        sound_heap->stay_heap.entries[sound_heap->stay_heap.num_entries].id = id;
        sound_heap->stay_heap.entries[sound_heap->stay_heap.num_entries].size = size;
        return sound_heap->stay_heap.entries[sound_heap->stay_heap.num_entries++].addr;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */
void* Nas_SzCacheCheck(s32 tabletype, s32 audioCacheType, s32 id) {
    void* v = EmemOnCheck(tabletype, id);
    if (v) {
        return v;
    }
    if (audioCacheType == CACHE_PERMANENT) {
        return NULL;
    }
    return __Nas_SzCacheCheck_Inner(tabletype, audioCacheType, id);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000114
 */
void* __Nas_SzCacheCheck_Inner(s32 tabletype, s32 audioCacheType, s32 id) {
    SZHeap* heap;
    switch (tabletype) {
        case SEQUENCE_TABLE: {
            heap = &AG.seq_heap;
        } break;
        case BANK_TABLE: {
            heap = &AG.bank_heap;
        } break;
        case WAVE_TABLE: {
            heap = &AG.wave_heap;
        } break;
        default:
            return NULL;
    }
    SZAuto* autoHeap = &heap->auto_heap;
    if (audioCacheType == 0) {
        if (autoHeap->entries[0].id == id) {
            autoHeap->use_entry_idx = TRUE;
            return autoHeap->entries[0].addr;
        }
        if (autoHeap->entries[1].id == id) {
            autoHeap->use_entry_idx = FALSE;
            return autoHeap->entries[1].addr;
        }
        return NULL;
    }
    for (int i = 0; i < heap->stay_heap.num_entries; i++) {
        if (id == heap->stay_heap.entries[i].id) {
            return heap->stay_heap.entries[i].addr;
        }
    }
    if (audioCacheType == 2) {
        return Nas_SzCacheCheck(tabletype, 0, id);
    }
    return NULL;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000D4
 */
void Nas_InitFilterCoef(f32 param_1, f32 param_2, u16* param_3) {
    // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
void Nas_ClearFilter(s16* param_1) {
    // UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
extern s16 LSF_TABLE[];
void Nas_SetLPFilter(s16* a, s32 b) {
    int i;
    int c = b * 8;
    for (i = 0; i < 8; i++) {
        a[i] = LSF_TABLE[c + i];
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
extern s16 HSF_TABLE[];
void Nas_SetHPFilter(s16* a, s32 b) {
    int i;
    int c = (b - 1) * 8;
    for (i = 0; i < 8; i++) {
        a[i] = HSF_TABLE[c + i];
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000134
 */
extern s16 EL_FILTER[];
extern s16 BP_FILTER[];
void Nas_SetBPFilter(s16* a, s32 b, s32 c) {
    int i;
    int k;
    int ind;
    int constant;
    if (b == 0 && c == 0) {
        Nas_SetLPFilter(a, 0);
        return;
    } else if (c == 0) {
        Nas_SetLPFilter(a, b);
        return;
    } else if (b == 0) {
        Nas_SetLPFilter(a, c);
        return;
    }
    k = 0;
    constant = 14;
    if (c > b) {
        for (i = b; i > 1; i--) {
            k += constant;
            constant--;
        }
        ind = (c - b) - 1 + k;
        for (i = 0; i < 8; i++) {
            a[i] = EL_FILTER[i + ind];
        }
    } else if (c < b) {
        for (i = c; i > 1; i--) {
            k += constant;
            constant--;
        }
        ind = (b - c) - 1 + k;
        for (i = 0; i < 8; i++) {
            a[i] = BP_FILTER[i + ind];
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000004
 */
void __DownDelay(delay* unused) {
    return;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void __Nas_DelayDown() {
    int i;
    int j;
    delay* delay_p;
    int c;

    if (AG.audio_params.spec == 2) {
        c = 2;
    } else {
        c = 1;
    }

    for (i = 0; i < AG.num_synth_reverbs; i++) {
        delay_p = &AG.synth_delay[i];
        for (j = 0; j < c; j++) {
            __DownDelay(delay_p);
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void __Nas_DacClear() {
    int i;
    int bufferIdx = AG.current_ai_buffer_idx;
    AG.num_samples_per_frame[bufferIdx] = AG.audio_params.num_samples_per_frame_min;
    for (i = 0; i < 0x7c0; i++) {
        AG.ai_buffers[bufferIdx][i] = 0;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000258
 */
s32 Nas_SpecChange() {
    int i;
    int j;
    int c = AG.audio_params.spec == 2 ? 2 : 1;
    switch (AG.reset_status) {
        case 5: {
            for (i = 0; i < AG.audio_params.num_groups; i++) {
                Nas_ReleaseGroup_Force(AG.groups_p[i]);
            }
            AG.audio_reset_fadeout_frames_left = 2 / c;
            AG.reset_status--;
        } break;
        case 4: {
            if (AG.audio_reset_fadeout_frames_left != 0) {
                AG.audio_reset_fadeout_frames_left--;
                __Nas_DelayDown();
            } else {
                for (i = 0; i < AG.num_channels; i++) {
                    if (AG.channels[i].common_ch.enabled && AG.channels[i].playback_ch.adsr_envp.state.flags.status) {
                        AG.channels[i].playback_ch.adsr_envp.fadeout_velocity =
                            AG.audio_params.updates_per_frame_inverse;
                        AG.channels[i].playback_ch.adsr_envp.state.flags.release = TRUE;
                    }
                }
                AG.audio_reset_fadeout_frames_left = 8 / c;
                AG.reset_status--;
            }
        } break;
        case 3: {
            if (AG.audio_reset_fadeout_frames_left) {
                AG.audio_reset_fadeout_frames_left--;
                __Nas_DelayDown();
            } else {
                AG.audio_reset_fadeout_frames_left = 2 / c;
                AG.reset_status--;
            }
        } break;
        case 2: {
            __Nas_DacClear();
            if (AG.audio_reset_fadeout_frames_left) {
                AG.audio_reset_fadeout_frames_left--;
            } else {
                AG.reset_status--;
                Emem_KillSwMember();
                Dirty_AllWave();
            }
        } break;
        case 1: {
            __Nas_MemoryReconfig();
            AG.reset_status = 0;
            for (i = 0; i < ARRAY_COUNT(AG.ai_buffers) - 1; i++) {
                AG.num_samples_per_frame[i] = AG.audio_params.num_samples_per_frame_max;
                for (j = 0; j < 0x7c0; j++) {
                    AG.ai_buffers[i][j] = 0;
                }
            }
        } break;
    }
    return AG.reset_status > 2;
}

/*
 * --INFO--
 * Address:	........
 * Size:	0006B4
 */
void __Nas_MemoryReconfig() {
    s32 j;
    s32 i;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    na_spec_config* spec = &NA_SPEC_CONFIG[AG.spec_id];

    /*0x2640*/ AG.num_waveloads = 0;
    /*0x286E*/ AG.audio_params.sampling_frequency = spec->_00;
    /*0x2872*/ AG.audio_params.num_samples_per_frame_target = spec->_00 / AG.refresh_rate;
    /*0x2878*/ AG.audio_params.updates_per_frame = 4;
    /*0x2876*/ AG.audio_params.num_samples_per_frame_min = AG.audio_params.num_samples_per_frame_target - 0x10;
    /*0x2874*/ AG.audio_params.num_samples_per_frame_max = AG.audio_params.num_samples_per_frame_target + 0x10;
    /*0x287A*/ AG.audio_params.num_samples_per_update =
        (AG.audio_params.num_samples_per_frame_target / AG.audio_params.updates_per_frame) & ~7;
    /*0x2870*/ AG.audio_params.ai_sampling_frequency = AG.audio_params.sampling_frequency;
    OSReport("----------------------------- SFS_NORMAL = %d\n", AG.audio_params.num_samples_per_update);
    /*
       order is
       287c
       287e
       2884
       2898
       289c
       28b8
       2888
       2880
       288c
       2890
    */
    /*0x287C*/ AG.audio_params.num_samples_per_update_max = AG.audio_params.num_samples_per_update + 8;
    /*0x287E*/ AG.audio_params.num_samples_per_update_min = AG.audio_params.num_samples_per_update - 8;
    /*0x2884*/ AG.audio_params.resample_rate = 33476.156f / (s32)AG.audio_params.sampling_frequency;
    /*0x288C*/ AG.audio_params.updates_per_frame_inverse_scaled = (1.f / 256.f) / AG.audio_params.updates_per_frame;
    /*0x2890*/ AG.audio_params.updates_per_frame_scaled = AG.audio_params.updates_per_frame / 4.0f;
    /*0x2888*/ AG.audio_params.updates_per_frame_inverse = 1.f / AG.audio_params.updates_per_frame;

    /*0x2898*/ AG.waveload_dma_buf0_size = spec->_10;
    /*0x289C*/ AG.waveload_dma_buf1_size = spec->_12;

    /*0x28B8*/ AG.num_channels = spec->_05;
    /*0x2880*/ AG.audio_params.num_groups = spec->_06;
    if (AG.audio_params.num_groups > 5) {
        /*0x2880*/ AG.audio_params.num_groups = 5;
    }

    /*0x2A18*/ AG.num_abi_cmds_max = 8;
    /*0x0002*/ AG._0002 = spec->_14;

    s32 tmp = AG.audio_params.updates_per_frame;
    /*0x28BC*/ AG.max_tempo = ((((60.0f * 1000.0f * AUDIO_TATUMS_PER_BEAT) * tmp) / AGC.timeBase) / AG._29D8) / 1.04613;

    /*0x2894*/ AG._2894 = (f32)AG.refresh_rate * (f32)tmp / AG.audio_params.ai_sampling_frequency / AG.max_tempo;

    /*0x286C*/ AG.audio_params.spec = spec->_04;
    /*0x2894*/ AG._2894 = AG.refresh_rate;
    /*0x2894*/ AG._2894 *= tmp;
    /*0x2894*/ AG._2894 /= AG.audio_params.ai_sampling_frequency;
    /*0x2894*/ AG._2894 /= AG.max_tempo;
    /*0x2876*/ AG.audio_params.num_samples_per_frame_min *= AG.audio_params.spec;
    /*0x2878*/ AG.audio_params.updates_per_frame *= AG.audio_params.spec;
    /*0x2872*/ AG.audio_params.num_samples_per_frame_target *= AG.audio_params.spec;
    /*0x2874*/ AG.audio_params.num_samples_per_frame_max *= AG.audio_params.spec;

    if (AG.audio_params.spec > 1) {
        /*0x2874*/ AG.audio_params.num_samples_per_frame_max -= 0x10;
    }
    // int c = (a + b);
    /*0x28B4*/ AG.max_audio_cmds = (AG.num_channels * 20 * AG.audio_params.updates_per_frame) + (spec->_09 * 30) + 400;
    a = (spec->_18 + spec->_1C + spec->_20 + 0x40);
    b = (spec->_24 + spec->_28 + spec->_2C + 0x40);
    c = a + b;
    d = AG.session_heap.length - c - 0x100;
    if (/*0x2A34*/ AG.external_heap.base != NULL) {
        /*0x2A38*/ AG.external_heap.current = AG.external_heap.base;
    }
    /*0x34EC*/ AG.audio_heap_info.misc_heap_size = d;
    /*0x34F8*/ AG.audio_heap_info.cache_heap_size = c;
    Nas_SzHeapDivide(&AG.audio_heap_info);
    /*0x34FC*/ AG.cache_heap.data_size = a;
    /*0x3500*/ AG.cache_heap.auto_size = b;
    Nas_SzDataDivide(&AG.cache_heap);

    /*0x3504*/ AG.persistent_common_heap_info.seq_heap_size = spec->_18;
    /*0x3508*/ AG.persistent_common_heap_info.bank_heap_size = spec->_1C;
    /*0x350C*/ AG.persistent_common_heap_info.wave_heap_size = spec->_20;
    Nas_SzStayDivide(&AG.persistent_common_heap_info);
    AG.temporary_common_heap_info.seq_heap_size = spec->_24;
    AG.temporary_common_heap_info.bank_heap_size = spec->_28;
    AG.temporary_common_heap_info.wave_heap_size = spec->_2C;
    // fake? maybe temporary_common_heap_info is wrong type?
    Nas_SzAutoDivide((AutoHeapstrc*)&AG.temporary_common_heap_info);
    Nas_ResetIDtable();
    AG.channels = (channel*)Nas_HeapAlloc_CL(&AG.misc_heap, AG.num_channels * sizeof(channel));
    Nas_ChannelInit();
    Nas_InitChannelList();
    AG.common_channel = (commonch*)Nas_HeapAlloc_CL(&AG.misc_heap, AG.audio_params.updates_per_frame * AG.num_channels *
                                                                       sizeof(commonch));

    for (i = 0; i < ARRAY_COUNT(AG.abi_cmd_bufs); i++) {
        AG.abi_cmd_bufs[i] = (Acmd*)Nas_NcHeapAlloc_CL(&AG.misc_heap, AG.max_audio_cmds * sizeof(Acmd));
    }
    AG.adsr_decay_table = (f32*)Nas_HeapAlloc(&AG.misc_heap, sizeof(f32) * 0x100);
    MakeReleaseTable();
    for (i = 0; i < ARRAY_COUNT(AG.synth_delay); i++) {
        AG.synth_delay[i].use_reverb = FALSE;
    }
    AG.num_synth_reverbs = spec->_09;
    for (i = 0; i < AG.num_synth_reverbs; i++) {
        Nas_SetDelayLine(i, &spec->_0C[i], 1);
    }
    Nas_InitPlayer();
    for (j = 0; j < AG.audio_params.num_groups; j++) {
        Nas_AssignSubTrack(j);
        Nas_InitMySeq(AG.groups_p[j]);
    }
    Nas_Init_Single(spec->_30, spec->_34);
    Nas_WaveDmaNew(AG.num_channels);
    AG.num_requested_samples = 0;
    LpsInit();
    MK_Init();
    Nas_BgCopyInit();
    AG._0004 = 0x1000;
    EmemReload();
    Z_osWritebackDCacheAll();
}

/*
 * --INFO--
 * Address:	........
 * Size:	00005C
 */
void* EmemOnCheck(s32 tableType, s32 id) {
    int i;
    for (i = 0; i < AG.emem_heap.count; i++) {
        if (tableType == AG.emem_entries[i].table_type && id == AG.emem_entries[i].id) {
            return AG.emem_entries[i].addr;
        }
    }
    return NULL;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00007C
 */
void* EmemAlloc(s32 tableType, s32 id, s32 size) {
    u32 heapCount = AG.emem_heap.count;
    u8* p = (u8*)Nas_HeapAlloc(&AG.emem_heap, size);
    AG.emem_entries[heapCount].addr = p;
    if (p == NULL) {
        return NULL;
    }
    AG.emem_entries[heapCount].table_type = tableType;
    AG.emem_entries[heapCount].id = id;
    AG.emem_entries[heapCount].size = size;
    return p;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000064
 */

void* Nas_Alloc_Single(s32 a, s32 sampleBankID, u8* sampleAddr, s8 originalMedium, s32 e) {
    SwMember* alloc;
    if (e == 0) {
        alloc = __Nas_Alloc_Single_Auto_Inner(a);
    } else {
        alloc = __Nas_Alloc_Single_Stay_Inner(a);
    }
    if (alloc != NULL) {
        SwMember* entry = (SwMember*)alloc;
        entry->sample_bank_id = sampleBankID;
        entry->sample_addr = sampleAddr;
        entry->original_medium = originalMedium;
        return entry->allocated_addr;
    } else {
        return NULL;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000C4
 */
int Nas_Init_Single(s32 a, s32 b) {
    u8* alloc = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, a);
    if (alloc == NULL) {
        AG.emem_persistent_wave_heap.heap.length = 0;
    } else {
        Nas_HeapInit(&AG.emem_persistent_wave_heap.heap, alloc, a);
    }

    alloc = (u8*)Nas_2ndHeapAlloc(&AG.misc_heap, b);
    if (alloc == NULL) {
        AG.emem_temporary_wave_heap.heap.length = 0;
    } else {
        Nas_HeapInit(&AG.emem_temporary_wave_heap.heap, alloc, b);
    }
    AG.emem_persistent_wave_heap.num_entries = 0;
    AG.emem_temporary_wave_heap.num_entries = 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000200
 */
SwMember* __Nas_Alloc_Single_Auto_Inner(s32 size) {
    SwHeap* heap = &AG.emem_temporary_wave_heap;
    void* alloc;
    u8* oldCurrent = heap->heap.current;
    u8* nowCurrent;
    alloc = Nas_HeapAlloc(&heap->heap, size);
    int i;

    if (!alloc) {
        u8* nowCurrent = heap->heap.current;
        heap->heap.current = heap->heap.base;
        alloc = Nas_HeapAlloc(&heap->heap, size);
        if (!alloc) {
            heap->heap.current = nowCurrent;
            return NULL;
        }
        oldCurrent = heap->heap.base;
    }
    nowCurrent = heap->heap.current;

    int s = -1;
    for (i = 0; i < AG.num_requested_samples; i++) {
        Bgloadreq* loadReq = &AG.requested_samples[i];
        if (loadReq->is_free == FALSE) {
            u8* p = loadReq->ram_addr + loadReq->sample->size - 1;
            if ((p >= oldCurrent || loadReq->ram_addr >= oldCurrent) &&
                (p < nowCurrent || loadReq->ram_addr < nowCurrent)) {
                loadReq->is_free = TRUE;
            }
        }
    }
    for (i = 0; i < heap->num_entries; i++) {
        s8 inUse = heap->entries[i].in_use;
        if (inUse) {
            u8* p = heap->entries[i].allocated_addr + heap->entries[i].size - 1;
            if ((p >= oldCurrent || heap->entries[i].allocated_addr >= oldCurrent) &&
                (p < nowCurrent || heap->entries[i].allocated_addr < nowCurrent)) {
                __KillSwMember(&heap->entries[i]);
                heap->entries[i].in_use = 0;
                if (s == -1) {
                    s = i;
                }
            }
        }
    }
    if (s == -1) {
        for (i = 0; i < heap->num_entries; i++) {
            s8 inUse = heap->entries[i].in_use;
            if (inUse == 0) {
                break;
            }
        }
        s = i;
        if (s == heap->num_entries) {
            if (heap->num_entries == ARRAY_COUNT(heap->entries)) {
                return NULL;
            }
            heap->num_entries++;
        }
    }
    SwMember* entry = &heap->entries[s];
    entry->in_use = TRUE;
    entry->allocated_addr = (u8*)alloc;
    entry->size = size;
    return entry;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00012C
 */
void __SearchBank(SwMember* entry, s32 bank) {
    perctable* pt;
    percvoicetable* pv;
    voicetable* vt;
    for (int i = 0; i < AG.voice_info[bank].num_instruments; i++) {
        vt = ProgToVp(bank, i);
        if (vt) {
            if (vt->normal_range_low != 0) {
                __RomAddrSet(entry, vt->low_pitch_tuned_sample.wavetable);
            }
            if (vt->normal_range_high != 0x7f) {
                __RomAddrSet(entry, vt->high_pitch_tuned_sample.wavetable);
            }
            __RomAddrSet(entry, vt->normal_pitch_tuned_sample.wavetable);
        }
    }
    for (int i = 0; i < AG.voice_info[bank].num_drums; i++) {
        pt = PercToPp(bank, i);
        if (pt) {
            __RomAddrSet(entry, pt->tuned_sample.wavetable);
        }
    }
    for (int i = 0; i < AG.voice_info[bank].num_sfx; i++) {
        pv = VpercToVep(bank, i);
        if (pv) {
            __RomAddrSet(entry, pv->tuned_sample.wavetable);
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000EC
 */
void __KillSwMember(SwMember* a) {
    for (int i = 0, end = AG.bank_header->numEntries; i < end; i++) {
        int bank0 = AG.voice_info[i].wave_bank_id0;
        int bank1 = AG.voice_info[i].wave_bank_id1;
        if (((bank0 != 0xff && bank0 == a->sample_bank_id) || (bank1 != 0xff && bank1 == a->sample_bank_id) ||
             (a->sample_bank_id == 0 || a->sample_bank_id == 0xfe)) &&
            Nas_SzCacheCheck(1, 2, i) && Nas_CheckIDbank(i)) {
            __SearchBank(a, i);
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void __RomAddrSet(SwMember* a, smzwavetable* b) {
    if (b != NULL && b->sample == a->allocated_addr) {
        b->sample = (u8*)a->sample_addr;
        b->medium = a->original_medium;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000094
 */
SwMember* __Nas_Alloc_Single_Stay_Inner(s32 a) {
    SwHeap* heap = &AG.emem_persistent_wave_heap;
    u8* alloc = (u8*)Nas_HeapAlloc(&heap->heap, a);
    if (alloc == NULL) {
        return NULL;
    }
    if (heap->num_entries == ARRAY_COUNT(heap->entries)) {
        return NULL;
    }
    SwMember* entry = &heap->entries[heap->num_entries];
    entry->in_use = TRUE;
    entry->allocated_addr = (u8*)alloc;
    entry->size = a;
    heap->num_entries++;
    return entry;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000040
 */
void __Do_EmemKill(SwMember* entry, s32 id0, s32 id1, s32 bank) {
    if (id0 == entry->sample_bank_id || id1 == entry->sample_bank_id || entry->sample_bank_id == 0) {
        __SearchBank(entry, bank);
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000128
 */
void Emem_KillSwMember() {
    s32 i, j, end;
    for (i = 0, end = AG.bank_header->numEntries; i < end; i++) {
        s32 id0 = AG.voice_info[i].wave_bank_id0;
        s32 id1 = AG.voice_info[i].wave_bank_id1;
        if ((id0 != 0xff || id1 != 0xff) && Nas_SzCacheCheck(1, 3, i) && Nas_CheckIDbank(i)) {
            for (j = 0; j < AG.emem_persistent_wave_heap.num_entries; j++) {
                __Do_EmemKill(&AG.emem_persistent_wave_heap.entries[j], id0, id1, i);
            }
            for (j = 0; j < AG.emem_temporary_wave_heap.num_entries; j++) {
                __Do_EmemKill(&AG.emem_temporary_wave_heap.entries[j], id0, id1, i);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
s32 EXGTYPE;
void __RestoreAddr(Wavelookuptable* a, smzwavetable* b) {
    if (b != NULL && (b->medium == a->medium || EXGTYPE != 1) && (b->medium == 0 || EXGTYPE != 0)) {

        u8* a_sample = a->sample;
        u8* b_sample = b->sample;
        u8* o = a_sample + a->_08;
        if (b_sample >= a_sample && b_sample < o) {
            // fakematch?
#ifdef TARGET_PC
            b->sample = (u8*)((uintptr_t)a->_04 + (b->sample - (uintptr_t)a->sample));
#else
            b->sample = (u8*)((u32)a->_04 + (b->sample - (u32)a->sample));
#endif
            if (EXGTYPE == 0) {
                b->medium = a->medium;
            } else {
                b->medium = 0;
            }
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void DirtyWave(s32 id) {
    EXGTYPE = 0;
    __ExchangeWave(0, id);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void EntryWave(s32 id) {
    EXGTYPE = 1;
    __ExchangeWave(1, id);
}

/*
 * --INFO--
 * Address:	........
 * Size:	000238
 */
void __ExchangeWave(s32 a, s32 b) {
    s32 i;
    Wavelookuptable wavetable;
    voiceinfo* voiceinfo;
    s32 bVar1;
    s32 bVar2;
    ArcHeader* wave_header = AG.wave_header;
    s16 numEntries = AG.bank_header->numEntries;
    Wavelookuptable* pWaveTable = &wavetable;
    u8* alloc = (u8*)Nas_SzCacheCheck(2, 2, b);
    pWaveTable->sample = alloc;
    if (pWaveTable->sample) {
        pWaveTable->_08 = (s32)wave_header[b].entries[0].size;
        pWaveTable->medium = wave_header[b].entries[0].medium;
        pWaveTable->_04 = (u8*)wave_header[b].entries[0].addr;
        switch (a) {
            case 1: {
                pWaveTable->_04 = alloc;
                pWaveTable->sample = (u8*)wave_header[b].entries[0].addr;
            } break;
            case 0:
            default:
                break;
        }
        for (i = 0; i < numEntries; i++) {
            voiceinfo = &AG.voice_info[i];
            bVar1 = voiceinfo->wave_bank_id0;
            bVar2 = voiceinfo->wave_bank_id1;
            if ((bVar1 != 0xff || bVar2 != 0xff) && Nas_CheckIDbank(i) && Nas_SzCacheCheck(1, 2, i) &&
                (bVar1 == b || bVar2 == b)) {
                for (int j = 0; j < AG.voice_info[i].num_instruments; j++) {
                    voicetable* voicetable = ProgToVp(i, j);
                    if (voicetable) {
                        if (voicetable->normal_range_low) {
                            __RestoreAddr(pWaveTable, voicetable->low_pitch_tuned_sample.wavetable);
                        }
                        if (voicetable->normal_range_high != 0x7f) {
                            __RestoreAddr(pWaveTable, voicetable->high_pitch_tuned_sample.wavetable);
                        }
                        __RestoreAddr(pWaveTable, voicetable->normal_pitch_tuned_sample.wavetable);
                    }
                }
                for (int j = 0; j < AG.voice_info[i].num_drums; j++) {
                    perctable* pTable = PercToPp(i, j);
                    if (pTable) {
                        __RestoreAddr(pWaveTable, pTable->tuned_sample.wavetable);
                    }
                }
                for (int j = 0; j < AG.voice_info[i].num_sfx; j++) {
                    percvoicetable* pTable = VpercToVep(i, j);
                    if (pTable) {
                        __RestoreAddr(pWaveTable, pTable->tuned_sample.wavetable);
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	000088
 */
void Dirty_AllWave() {
    int i;
    SZHeap* heap = &AG.wave_heap;
    if (heap->auto_heap.entries[0].id != HEAP_INVALID_INDEX) {
        DirtyWave(heap->auto_heap.entries[0].id);
    }
    if (heap->auto_heap.entries[1].id != HEAP_INVALID_INDEX) {
        DirtyWave(heap->auto_heap.entries[1].id);
    }
    for (i = 0; i < heap->stay_heap.num_entries; i++) {
        DirtyWave(heap->stay_heap.entries[i].id);
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000AC
 */
int __Nas_GetCompressBuffer(delay* a) {
    if (a->left_load_resample_buf != NULL && a->right_save_resample_buf != NULL) {
        return 0;
    }
    a->left_load_resample_buf = (s16*)Nas_HeapAlloc_CL(&AG.misc_heap, 0x20);
    a->right_load_resample_buf = (s16*)Nas_HeapAlloc_CL(&AG.misc_heap, 0x20);
    a->left_save_resample_buf = (s16*)Nas_HeapAlloc_CL(&AG.misc_heap, 0x20);
    a->right_save_resample_buf = (s16*)Nas_HeapAlloc_CL(&AG.misc_heap, 0x20);
    if (a->right_save_resample_buf == NULL) {
        return -1;
    }
    return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00028C
 */
void Nas_SetDelayLineParam(s32 a, s32 b, s32 c, s32 d) {
    delay* delay = &AG.synth_delay[a];
    switch (b) {
        case 0: {
            Nas_SetDelayLine(a, (fxconfig*)c, 0);
        } break;
        case 1: {
            if (c < 4) {
                c = 4;
            }

            int delay_num_samples = c * 0x40;
            if (c * 0x40 < 0x100) {
                delay_num_samples = 0x100;
            }

            delay_num_samples /= delay->downsample_rate;

            if (d == 0) {
                if (delay->delay_num_samples_after_downsampling < c / delay->downsample_rate) {
                    return;
                }
                if (delay_num_samples <= delay->next_reverb_buf_pos ||
                    delay_num_samples <= delay->delay_num_samples_unk) {
                    delay->next_reverb_buf_pos = 0;
                    delay->delay_num_samples_unk = 0;
                }
            }
            delay->delay_num_samples = delay_num_samples;
            if (delay->downsample_rate != 1 || delay->resample_effect_on) {
                delay->downsample_pitch = 0x8000 / delay->downsample_rate;
                if (__Nas_GetCompressBuffer(delay) == -1) {
                    delay->downsample_rate = 1;
                }
            }
        } break;
        case 2: {
            delay->decay_ratio = c;
        } break;
        case 3: {
            delay->sub_volume = c;
        } break;
        case 4: {
            delay->volume = c;
        } break;
        case 5: {
            delay->leak_rtl = c;
        } break;
        case 6: {
            delay->leak_ltl = c;
        } break;
        case 7: {
            if (c) {
                if (d || delay->filter_left_init == NULL) {
                    delay->filter_left_state = (s16*)Nas_NcHeapAlloc_CL(&AG.misc_heap, 0x20 * sizeof(s16));
                    delay->filter_left_init = (s16*)Nas_NcHeapAlloc(&AG.misc_heap, 0x8 * sizeof(s16));
                }
                delay->filter_left = delay->filter_left_init;
                if (delay->filter_left) {
                    Nas_SetLPFilter(delay->filter_left, c);
                }
            } else {
                delay->filter_left = NULL;
                if (d) {
                    delay->filter_left_init = NULL;
                }
            }
        } break;
        case 8: {
            if (c) {
                if (d || delay->filter_right_init == NULL) {
                    delay->filter_right_state = (s16*)Nas_NcHeapAlloc_CL(&AG.misc_heap, 0x20 * sizeof(s16));
                    delay->filter_right_init = (s16*)Nas_NcHeapAlloc(&AG.misc_heap, 0x8 * sizeof(s16));
                }
                delay->filter_right = delay->filter_right_init;
                if (delay->filter_right) {
                    Nas_SetLPFilter(delay->filter_right, c);
                }
            } else {
                delay->filter_right = NULL;
                if (d) {
                    delay->filter_right_init = NULL;
                }
            }
        } break;
        case 9: {
            delay->resample_effect_extra_samples = c;
            if (c == 0) {
                delay->resample_effect_on = FALSE;
            } else {
                delay->resample_effect_on = TRUE;
            }
            if (__Nas_GetCompressBuffer(delay) == -1) {
                delay->resample_effect_on = FALSE;
                delay->resample_effect_extra_samples = FALSE;
            }
        } break;
    }
}

/*
 * --INFO--
 * Address:	........
 * Size:	0001E0
 */
void Nas_SetDelayLine(s32 a, fxconfig* b, s32 c) {
    delay* d = &AG.synth_delay[a];
    if (c) {
        d->delay_num_samples_after_downsampling = b->_02 / b->downsample_rate;
        d->left_load_resample_buf = NULL;
    } else if (d->delay_num_samples_after_downsampling < b->_02 / b->downsample_rate) {
        return;
    }
    d->downsample_rate = b->downsample_rate;
    d->resample_effect_on = 0;
    d->resample_effect_extra_samples = 0;
    d->resample_effect_load_unk = 0;
    d->resample_effect_save_unk = 0;
    Nas_SetDelayLineParam(a, 1, b->_02, c);
    d->decay_ratio = b->decay_ratio;
    d->volume = b->volume;
    d->sub_delay = b->sub_delay * 64;
    d->sub_volume = b->sub_volume;
    d->leak_rtl = b->leak_rtl;
    d->leak_ltl = b->leak_ltl;
    d->mix_reverb_idx = b->mix_reverb_idx;
    d->mix_reverb_strength = b->mix_reverb_strength;
    d->use_reverb = 8;
    if (c) {
        d->left_reverb_buf = (s16*)Nas_2ndHeapAlloc_CL(&AG.misc_heap, d->delay_num_samples * sizeof(s16));
        d->right_reverb_buf = (s16*)Nas_2ndHeapAlloc_CL(&AG.misc_heap, d->delay_num_samples * sizeof(s16));
        d->resample_flags = 1;
        d->next_reverb_buf_pos = 0;
        d->delay_num_samples_unk = 0;
        d->cur_frame = 0;
        d->frames_to_ignore = 2;
    }
    d->tuned_sample.wavetable = &d->sample;
    d->sample.loop = &d->adpcm_loop;
    d->tuned_sample.tuning = 1.f;
    d->sample.codec = 4;
    d->sample.medium = 0;
    d->sample.size = d->delay_num_samples * sizeof(s16);
    d->sample.sample = (u8*)d->left_reverb_buf;
    d->adpcm_loop.loop_start = 0;
    d->adpcm_loop.loop_end = d->delay_num_samples;
    d->adpcm_loop.count = 1;
    Nas_SetDelayLineParam(a, 7, b->_14, c);
    Nas_SetDelayLineParam(a, 8, b->_16, c);
}
