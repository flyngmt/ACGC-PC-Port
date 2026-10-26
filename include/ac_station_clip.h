#ifndef AC_STATION_CLIP_H
#define AC_STATION_CLIP_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aSTM_TALK_CHK_LEAVE_TALK,
    aSTM_TALK_CHK_LEAVE_TALK2,
    aSTM_TALK_SAYONARA,
    aSTM_TALK_CHK_TRAIN_TALK,
    aSTM_TALK_CHK_TRAIN2_TALK,
    aSTM_TALK_BEFORE_SAVE_TALK,
    aSTM_TALK_SAVE_TALK,
    aSTM_TALK_CHK_OVER_SAVE_TALK,
    aSTM_TALK_SAVE_TALK_END,
    aSTM_TALK_SAVE_ERROR,
    aSTM_TALK_CHK_REPAIRID,
    aSTM_TALK_REPAIRID_BF,
    aSTM_TALK_REPAIRID,
    aSTM_TALK_REPAIRID_AFTER,
    aSTM_TALK_CARDPROC,
    aSTM_TALK_END_WAIT,
#ifdef TARGET_PC
    aSTM_TALK_SELECT_TOWN,
#endif

    aSTM_TALK_NUM
};

typedef int (*aSTC_CHANGE_TALK_PROC)(ACTOR*, int);

typedef struct station_clip_s {
    aSTC_CHANGE_TALK_PROC change_talk_proc;
} aSTC_clip_c;

#ifdef __cplusplus
}
#endif

#endif
