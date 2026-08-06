#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

ATTRIBUTE_ALIGN(32) u8 cKF_ckcb_r_act_mus_angel_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_angel_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_angel_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_angel_a1_tbl[] = { 1,   8,    261, 11,  58, -3,  24,   -1,  -244, 37,  -56,  1,   50,   0,  205, 1,
                                      -12, -131, 12,  -37, -5, 37,  37,   2,   50,   -7,  -121, 1,   699,  0,  9,   699,
                                      0,   19,   699, 0,   31, 699, 0,    41,  699,  0,   50,   699, 0,    1,  0,   0,
                                      50,  0,    0,   1,   68, 335, 9,    110, -6,   31,  -98,  2,   50,   57, 354, 1,
                                      0,   0,    50,  0,   0,  1,   -272, 175, 22,   243, -2,   50,  -276, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_angel_a1 = { cKF_ckcb_r_act_mus_angel_a1_tbl,
                                                cKF_ds_act_mus_angel_a1_tbl,
                                                cKF_kn_act_mus_angel_a1_tbl,
                                                cKF_c_act_mus_angel_a1_tbl,
                                                -1,
                                                50 };
