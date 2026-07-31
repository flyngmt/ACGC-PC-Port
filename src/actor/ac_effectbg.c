#include "ac_effectbg.h"

#include "m_name_table.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "sys_matrix.h"
#include "m_rcp.h"

#define EffectBg_STATUS_ACTIVE (1 << 0)
#define EffectBg_STATUS_1 (1 << 1)
#define EffectBg_STATUS_XMAS (1 << 2)
#define EffectBg_STATUS_PALM (1 << 3)
#define EffectBg_STATUS_CEDAR (1 << 4)
#define EffectBg_STATUS_GOLD (1 << 5)
#define EffectBg_STATUS_6 (1 << 6)
#define EffectBg_STATUS_7 (1 << 7)

#define EffectBG_IS_SHAKE(t) \
    ((t) == EffectBG_EFFECT_SHAKE || (t) == EffectBG_EFFECT_SHAKE_SMALL || (t) == EffectBG_EFFECT_SHAKE_LARGE)

// tree, cherry
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_f_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_f_tree5_shakeL;

// tree, summer
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_tree5_shakeL;

// tree, winter
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_tree4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_x_tree5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_x_tree5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_x_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_x_tree5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_x_tree5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_x_tree5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_x_tree5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_x_tree5_shakeL;

// palm, summer
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_palm5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_palm5_shakeL;

// palm, winter
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_palm5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_palm5_shakeL;

// cedar, summer
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_s_cedar5_shakeL;

// cedar, winter
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar3_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar3_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar4_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar4_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_w_cedar4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar4_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar4_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar4_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar4_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_w_cedar4_shakeL;

extern cKF_Skeleton_R_c cKF_bs_r_ef_x_cedar5_shake;
extern cKF_Skeleton_R_c cKF_bs_r_ef_x_cedar5_cutR;
extern cKF_Skeleton_R_c cKF_bs_r_ef_x_cedar5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_x_cedar5_shake;
extern cKF_Animation_R_c cKF_ba_r_ef_x_cedar5_cutR;
extern cKF_Animation_R_c cKF_ba_r_ef_x_cedar5_cutL;
extern cKF_Animation_R_c cKF_ba_r_ef_x_cedar5_shakeS;
extern cKF_Animation_R_c cKF_ba_r_ef_x_cedar5_shakeL;

static cKF_Skeleton_R_c* cherry_tree_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_f_tree3_shake,
        &cKF_bs_r_ef_f_tree3_cutR,
        &cKF_bs_r_ef_f_tree3_cutL,
        &cKF_bs_r_ef_f_tree3_shake,
        &cKF_bs_r_ef_f_tree3_shake,
    },
    {
        &cKF_bs_r_ef_f_tree4_shake,
        &cKF_bs_r_ef_f_tree4_cutR,
        &cKF_bs_r_ef_f_tree4_cutL,
        &cKF_bs_r_ef_f_tree4_shake,
        &cKF_bs_r_ef_f_tree4_shake,
    },
    {
        &cKF_bs_r_ef_f_tree5_shake,
        &cKF_bs_r_ef_f_tree5_cutR,
        &cKF_bs_r_ef_f_tree5_cutL,
        &cKF_bs_r_ef_f_tree5_shake,
        &cKF_bs_r_ef_f_tree5_shake,
    },
};

static cKF_Animation_R_c* cherry_tree_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_f_tree3_shake,
        &cKF_ba_r_ef_f_tree3_cutR,
        &cKF_ba_r_ef_f_tree3_cutL,
        &cKF_ba_r_ef_f_tree3_shakeS,
        &cKF_ba_r_ef_f_tree3_shakeL,
    },
    {
        &cKF_ba_r_ef_f_tree4_shake,
        &cKF_ba_r_ef_f_tree4_cutR,
        &cKF_ba_r_ef_f_tree4_cutL,
        &cKF_ba_r_ef_f_tree4_shakeS,
        &cKF_ba_r_ef_f_tree4_shakeL,
    },
    {
        &cKF_ba_r_ef_f_tree5_shake,
        &cKF_ba_r_ef_f_tree5_cutR,
        &cKF_ba_r_ef_f_tree5_cutL,
        &cKF_ba_r_ef_f_tree5_shakeS,
        &cKF_ba_r_ef_f_tree5_shakeL,
    },
};

static cKF_Skeleton_R_c* summer_tree_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_s_tree3_shake,
        &cKF_bs_r_ef_s_tree3_cutR,
        &cKF_bs_r_ef_s_tree3_cutL,
        &cKF_bs_r_ef_s_tree3_shake,
        &cKF_bs_r_ef_s_tree3_shake,
    },
    {
        &cKF_bs_r_ef_s_tree4_shake,
        &cKF_bs_r_ef_s_tree4_cutR,
        &cKF_bs_r_ef_s_tree4_cutL,
        &cKF_bs_r_ef_s_tree4_shake,
        &cKF_bs_r_ef_s_tree4_shake,
    },
    {
        &cKF_bs_r_ef_s_tree5_shake,
        &cKF_bs_r_ef_s_tree5_cutR,
        &cKF_bs_r_ef_s_tree5_cutL,
        &cKF_bs_r_ef_s_tree5_shake,
        &cKF_bs_r_ef_s_tree5_shake,
    },
};

static cKF_Animation_R_c* summer_tree_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_s_tree3_shake,
        &cKF_ba_r_ef_s_tree3_cutR,
        &cKF_ba_r_ef_s_tree3_cutL,
        &cKF_ba_r_ef_s_tree3_shakeS,
        &cKF_ba_r_ef_s_tree3_shakeL,
    },
    {
        &cKF_ba_r_ef_s_tree4_shake,
        &cKF_ba_r_ef_s_tree4_cutR,
        &cKF_ba_r_ef_s_tree4_cutL,
        &cKF_ba_r_ef_s_tree4_shakeS,
        &cKF_ba_r_ef_s_tree4_shakeL,
    },
    {
        &cKF_ba_r_ef_s_tree5_shake,
        &cKF_ba_r_ef_s_tree5_cutR,
        &cKF_ba_r_ef_s_tree5_cutL,
        &cKF_ba_r_ef_s_tree5_shakeS,
        &cKF_ba_r_ef_s_tree5_shakeL,
    },
};

static cKF_Skeleton_R_c* winter_tree_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_w_tree3_shake,
        &cKF_bs_r_ef_w_tree3_cutR,
        &cKF_bs_r_ef_w_tree3_cutL,
        &cKF_bs_r_ef_w_tree3_shake,
        &cKF_bs_r_ef_w_tree3_shake,
    },
    {
        &cKF_bs_r_ef_w_tree4_shake,
        &cKF_bs_r_ef_w_tree4_cutR,
        &cKF_bs_r_ef_w_tree4_cutL,
        &cKF_bs_r_ef_w_tree4_shake,
        &cKF_bs_r_ef_w_tree4_shake,
    },
    {
        &cKF_bs_r_ef_x_tree5_shake,
        &cKF_bs_r_ef_x_tree5_cutR,
        &cKF_bs_r_ef_x_tree5_cutL,
        &cKF_bs_r_ef_x_tree5_shake,
        &cKF_bs_r_ef_x_tree5_shake,
    },
};

static cKF_Animation_R_c* winter_tree_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_w_tree3_shake,
        &cKF_ba_r_ef_w_tree3_cutR,
        &cKF_ba_r_ef_w_tree3_cutL,
        &cKF_ba_r_ef_w_tree3_shakeS,
        &cKF_ba_r_ef_w_tree3_shakeL,
    },
    {
        &cKF_ba_r_ef_w_tree4_shake,
        &cKF_ba_r_ef_w_tree4_cutR,
        &cKF_ba_r_ef_w_tree4_cutL,
        &cKF_ba_r_ef_w_tree4_shakeS,
        &cKF_ba_r_ef_w_tree4_shakeL,
    },
    {
        &cKF_ba_r_ef_x_tree5_shake,
        &cKF_ba_r_ef_x_tree5_cutR,
        &cKF_ba_r_ef_x_tree5_cutL,
        &cKF_ba_r_ef_x_tree5_shakeS,
        &cKF_ba_r_ef_x_tree5_shakeL,
    },
};

static cKF_Skeleton_R_c* summer_palm_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_s_palm3_shake,
        &cKF_bs_r_ef_s_palm3_cutR,
        &cKF_bs_r_ef_s_palm3_cutL,
        &cKF_bs_r_ef_s_palm3_shake,
        &cKF_bs_r_ef_s_palm3_shake,
    },
    {
        &cKF_bs_r_ef_s_palm4_shake,
        &cKF_bs_r_ef_s_palm4_cutR,
        &cKF_bs_r_ef_s_palm4_cutL,
        &cKF_bs_r_ef_s_palm4_shake,
        &cKF_bs_r_ef_s_palm4_shake,
    },
    {
        &cKF_bs_r_ef_s_palm5_shake,
        &cKF_bs_r_ef_s_palm5_cutR,
        &cKF_bs_r_ef_s_palm5_cutL,
        &cKF_bs_r_ef_s_palm5_shake,
        &cKF_bs_r_ef_s_palm5_shake,
    },
};

static cKF_Animation_R_c* summer_palm_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_s_palm3_shake,
        &cKF_ba_r_ef_s_palm3_cutR,
        &cKF_ba_r_ef_s_palm3_cutL,
        &cKF_ba_r_ef_s_palm3_shakeS,
        &cKF_ba_r_ef_s_palm3_shakeL,
    },
    {
        &cKF_ba_r_ef_s_palm4_shake,
        &cKF_ba_r_ef_s_palm4_cutR,
        &cKF_ba_r_ef_s_palm4_cutL,
        &cKF_ba_r_ef_s_palm4_shakeS,
        &cKF_ba_r_ef_s_palm4_shakeL,
    },
    {
        &cKF_ba_r_ef_s_palm5_shake,
        &cKF_ba_r_ef_s_palm5_cutR,
        &cKF_ba_r_ef_s_palm5_cutL,
        &cKF_ba_r_ef_s_palm5_shakeS,
        &cKF_ba_r_ef_s_palm5_shakeL,
    },
};

static cKF_Skeleton_R_c* winter_palm_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_w_palm3_shake,
        &cKF_bs_r_ef_w_palm3_cutR,
        &cKF_bs_r_ef_w_palm3_cutL,
        &cKF_bs_r_ef_w_palm3_shake,
        &cKF_bs_r_ef_w_palm3_shake,
    },
    {
        &cKF_bs_r_ef_w_palm4_shake,
        &cKF_bs_r_ef_w_palm4_cutR,
        &cKF_bs_r_ef_w_palm4_cutL,
        &cKF_bs_r_ef_w_palm4_shake,
        &cKF_bs_r_ef_w_palm4_shake,
    },
    {
        &cKF_bs_r_ef_w_palm5_shake,
        &cKF_bs_r_ef_w_palm5_cutR,
        &cKF_bs_r_ef_w_palm5_cutL,
        &cKF_bs_r_ef_w_palm5_shake,
        &cKF_bs_r_ef_w_palm5_shake,
    },
};

static cKF_Animation_R_c* winter_palm_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_w_palm3_shake,
        &cKF_ba_r_ef_w_palm3_cutR,
        &cKF_ba_r_ef_w_palm3_cutL,
        &cKF_ba_r_ef_w_palm3_shakeS,
        &cKF_ba_r_ef_w_palm3_shakeL,
    },
    {
        &cKF_ba_r_ef_w_palm4_shake,
        &cKF_ba_r_ef_w_palm4_cutR,
        &cKF_ba_r_ef_w_palm4_cutL,
        &cKF_ba_r_ef_w_palm4_shakeS,
        &cKF_ba_r_ef_w_palm4_shakeL,
    },
    {
        &cKF_ba_r_ef_w_palm5_shake,
        &cKF_ba_r_ef_w_palm5_cutR,
        &cKF_ba_r_ef_w_palm5_cutL,
        &cKF_ba_r_ef_w_palm5_shakeS,
        &cKF_ba_r_ef_w_palm5_shakeL,
    },
};

static cKF_Skeleton_R_c* summer_cedar_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_s_cedar3_shake,
        &cKF_bs_r_ef_s_cedar3_cutR,
        &cKF_bs_r_ef_s_cedar3_cutL,
        &cKF_bs_r_ef_s_cedar3_shake,
        &cKF_bs_r_ef_s_cedar3_shake,
    },
    {
        &cKF_bs_r_ef_s_cedar4_shake,
        &cKF_bs_r_ef_s_cedar4_cutR,
        &cKF_bs_r_ef_s_cedar4_cutL,
        &cKF_bs_r_ef_s_cedar4_shake,
        &cKF_bs_r_ef_s_cedar4_shake,
    },
    {
        &cKF_bs_r_ef_s_cedar5_shake,
        &cKF_bs_r_ef_s_cedar5_cutR,
        &cKF_bs_r_ef_s_cedar5_cutL,
        &cKF_bs_r_ef_s_cedar5_shake,
        &cKF_bs_r_ef_s_cedar5_shake,
    },
};

static cKF_Animation_R_c* summer_cedar_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_s_cedar3_shake,
        &cKF_ba_r_ef_s_cedar3_cutR,
        &cKF_ba_r_ef_s_cedar3_cutL,
        &cKF_ba_r_ef_s_cedar3_shakeS,
        &cKF_ba_r_ef_s_cedar3_shakeL,
    },
    {
        &cKF_ba_r_ef_s_cedar4_shake,
        &cKF_ba_r_ef_s_cedar4_cutR,
        &cKF_ba_r_ef_s_cedar4_cutL,
        &cKF_ba_r_ef_s_cedar4_shakeS,
        &cKF_ba_r_ef_s_cedar4_shakeL,
    },
    {
        &cKF_ba_r_ef_s_cedar5_shake,
        &cKF_ba_r_ef_s_cedar5_cutR,
        &cKF_ba_r_ef_s_cedar5_cutL,
        &cKF_ba_r_ef_s_cedar5_shakeS,
        &cKF_ba_r_ef_s_cedar5_shakeL,
    },
};

static cKF_Skeleton_R_c* winter_cedar_model_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_bs_r_ef_w_cedar3_shake,
        &cKF_bs_r_ef_w_cedar3_cutR,
        &cKF_bs_r_ef_w_cedar3_cutL,
        &cKF_bs_r_ef_w_cedar3_shake,
        &cKF_bs_r_ef_w_cedar3_shake,
    },
    {
        &cKF_bs_r_ef_w_cedar4_shake,
        &cKF_bs_r_ef_w_cedar4_cutR,
        &cKF_bs_r_ef_w_cedar4_cutL,
        &cKF_bs_r_ef_w_cedar4_shake,
        &cKF_bs_r_ef_w_cedar4_shake,
    },
    {
        &cKF_bs_r_ef_x_cedar5_shake,
        &cKF_bs_r_ef_x_cedar5_cutR,
        &cKF_bs_r_ef_x_cedar5_cutL,
        &cKF_bs_r_ef_x_cedar5_shake,
        &cKF_bs_r_ef_x_cedar5_shake,
    },
};

static cKF_Animation_R_c* winter_cedar_anime_tbl[][EffectBG_EFFECT_NUM] = {
    {
        &cKF_ba_r_ef_w_cedar3_shake,
        &cKF_ba_r_ef_w_cedar3_cutR,
        &cKF_ba_r_ef_w_cedar3_cutL,
        &cKF_ba_r_ef_w_cedar3_shakeS,
        &cKF_ba_r_ef_w_cedar3_shakeL,
    },
    {
        &cKF_ba_r_ef_w_cedar4_shake,
        &cKF_ba_r_ef_w_cedar4_cutR,
        &cKF_ba_r_ef_w_cedar4_cutL,
        &cKF_ba_r_ef_w_cedar4_shakeS,
        &cKF_ba_r_ef_w_cedar4_shakeL,
    },
    {
        &cKF_ba_r_ef_x_cedar5_shake,
        &cKF_ba_r_ef_x_cedar5_cutR,
        &cKF_ba_r_ef_x_cedar5_cutL,
        &cKF_ba_r_ef_x_cedar5_shakeS,
        &cKF_ba_r_ef_x_cedar5_shakeL,
    },
};

static void Effectbg_actor_ct(ACTOR* actorx, GAME* game);
static void Effectbg_actor_dt(ACTOR* actorx, GAME* game);
static void Effectbg_actor_move(ACTOR* actorx, GAME* game);
static void Effectbg_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Effectbg_Profile = {
    mAc_PROFILE_EFFECTBG,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EFFECTBG_ACTOR),
    &Effectbg_actor_ct,
    &Effectbg_actor_dt,
    &Effectbg_actor_move,
    &Effectbg_actor_draw,
    NULL,
};
// clang-format on

static void Make_EffectBG(GAME* game, s16 type, s16 variant, xyz_t* pos);

static void EffectBG_object_dt(EffectBg_c* efbg, GAME* game);

static EffectBg_c* efbg_start_p = NULL;

static void Effectbg_actor_ct(ACTOR* actorx, GAME* game) {
    EFFECTBG_ACTOR* effect_actor = (EFFECTBG_ACTOR*)actorx;
    mFM_field_pal_c* field_pal = mFI_GetFieldPal();
    EffectBg_c* efbg;
    int i;

    if (field_pal != NULL) {
        effect_actor->tree_pal = field_pal->cedar_tree_pal;
        effect_actor->palm_pal = field_pal->palm_tree_pal;
        effect_actor->palm_pal2 = field_pal->palm_tree_pal;
        effect_actor->gold_pal = field_pal->golden_tree_pal;
    }

    efbg_start_p = effect_actor->effect;
    efbg = effect_actor->effect;
    for (i = 0; i < EffectBg_ENTRY_NUM; i++) {
        EffectBG_object_dt(efbg, game);
        efbg++;
    }

    CLIP(make_effect_bg_proc) = &Make_EffectBG;
}

static void Effectbg_actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static int EfbgBgitemTreeCheck(xyz_t pos) {
    mActor_name_t* fg_p = mFI_GetUnitFG(pos);
    mActor_name_t item;
    int stump;
    int tree;

    if (fg_p != NULL) {
        item = *fg_p;
    } else {
        return FALSE;
    }

    stump = IS_ITEM_TREE_STUMP(item);
    tree = IS_ITEM_COLLIDEABLE_TREE(item);
    return (stump | tree) ? TRUE : FALSE;
}

static void EffectBG_Make_Leafs(EffectBg_c* efbg, GAME* game, xyz_t pos, s16 count, s16 type) {
    xyz_t effect_pos;
    u32 season = Common_Get(time).season;
    s16 bush_happa_type;
    s16 bush_yuki_type;

    if (EffectBG_IS_SHAKE(type)) {
        bush_yuki_type = 1;

        if (Common_Get(time).term_idx == mTM_TERM_4) {
            bush_happa_type = 6;
        } else {
            bush_happa_type = 4;
        }
    } else if (type == EffectBG_EFFECT_CUT_RIGHT) {
        bush_yuki_type = 0;

        if (Common_Get(time).term_idx == mTM_TERM_4) {
            bush_happa_type = 6;
        } else {
            bush_happa_type = 4;
        }
    } else if (type == EffectBG_EFFECT_CUT_RIGHT_PALM) {
        bush_yuki_type = 0;
        bush_happa_type = eEC_BUSH_HAPPA_PALM | 4;
    } else if (type == EffectBG_EFFECT_CUT_RIGHT_CEDAR) {
        bush_yuki_type = 0;
        bush_happa_type = eEC_BUSH_HAPPA_CEDAR | 4;
    } else if (type == EffectBG_EFFECT_CUT_RIGHT_GOLD) {
        bush_yuki_type = 0;

        if (Common_Get(time).term_idx == mTM_TERM_4) {
            bush_happa_type = eEC_BUSH_HAPPA_GOLD | 6;
        } else {
            bush_happa_type = eEC_BUSH_HAPPA_GOLD | 4;
        }
    } else {
        if (Common_Get(time).term_idx == 4) {
            bush_happa_type = 7;
        } else {
            bush_happa_type = 5;
        }

        bush_yuki_type = 0;
    }

    if ((efbg->status & EffectBg_STATUS_GOLD) != 0 || efbg->variant == EffectBG_VARIANT_GOLD_SMALL) {
        bush_happa_type |= eEC_BUSH_HAPPA_GOLD;
    } else if ((efbg->status & EffectBg_STATUS_PALM) != 0 || efbg->variant == EffectBG_VARIANT_PALM_SMALL) {
        bush_happa_type |= eEC_BUSH_HAPPA_PALM;
    } else if ((efbg->status & EffectBg_STATUS_CEDAR) != 0 || efbg->variant == EffectBG_VARIANT_CEDAR_SMALL) {
        bush_happa_type |= eEC_BUSH_HAPPA_CEDAR;
    }

    while (count-- != 0) {
        effect_pos = pos;

        if (type != EffectBG_EFFECT_CUT_RIGHT && type != EffectBG_EFFECT_CUT_RIGHT_PALM &&
            type != EffectBG_EFFECT_CUT_RIGHT_CEDAR && type != EffectBG_EFFECT_CUT_RIGHT_GOLD) {
            if ((efbg->status & EffectBg_STATUS_CEDAR) != 0 && efbg->variant == EffectBG_VARIANT_TREE_MED) {
                effect_pos.x += RANDOM2_F(30.0f);
                effect_pos.y += RANDOM2_F(30.0f);
                effect_pos.z += RANDOM2_F(30.0f);
            } else {
                effect_pos.x += RANDOM2_F(40.0f);
                effect_pos.y += RANDOM2_F(40.0f);
                effect_pos.z += RANDOM2_F(40.0f);
            }
        } else {
            effect_pos.y += 60.0f;
        }

        if (type != 3) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, effect_pos, 2, 0, game, RSV_NO, 0, bush_happa_type);
        }

        if (season == mTM_SEASON_WINTER) {
            effect_pos = pos;

            if ((efbg->status & EffectBg_STATUS_CEDAR) != 0 && efbg->variant == EffectBG_VARIANT_TREE_MED) {
                effect_pos.x += RANDOM2_F(30.0f);
                effect_pos.y += RANDOM2_F(30.0f);
                effect_pos.z += RANDOM2_F(30.0f);
            } else {
                effect_pos.x += RANDOM2_F(40.0f);
                effect_pos.y += RANDOM2_F(40.0f);
                effect_pos.z += RANDOM2_F(40.0f);
            }

            eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, effect_pos, 2, 0, game, RSV_NO, 0, bush_yuki_type);
        }
    }
}

static void EffectBG_object_ct(EffectBg_c* efbg, GAME* game, s16 type, s16 variant) {
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;
    u32 season = Common_Get(time).season;

    if (variant == EffectBG_VARIANT_TREE_XMAS || variant == EffectBG_VARIANT_CEDAR_XMAS) {
        variant -= 1; // convert to the full size
        efbg->status |= EffectBg_STATUS_XMAS;
    }

    // convert to the equivalent 'normal tree' type
    if (variant >= EffectBG_VARIANT_GOLD_SMALL) {
        variant -= (EffectBG_VARIANT_GOLD_SMALL - EffectBG_VARIANT_TREE_SMALL);
        efbg->status |= EffectBg_STATUS_GOLD;
    } else if (variant >= EffectBG_VARIANT_CEDAR_SMALL) {
        variant -= (EffectBG_VARIANT_CEDAR_SMALL - EffectBG_VARIANT_TREE_SMALL);
        efbg->status |= EffectBg_STATUS_CEDAR;
    } else if (variant >= EffectBG_VARIANT_PALM_SMALL) {
        variant -= (EffectBG_VARIANT_PALM_SMALL - EffectBG_VARIANT_TREE_SMALL);
        efbg->status |= EffectBg_STATUS_PALM;
    }

    if ((efbg->status & EffectBg_STATUS_CEDAR) != 0) {
        if (season == mTM_SEASON_WINTER) {
            skeleton = winter_cedar_model_tbl[variant][type];
            animation = winter_cedar_anime_tbl[variant][type];
        } else {
            skeleton = summer_cedar_model_tbl[variant][type];
            animation = summer_cedar_anime_tbl[variant][type];
        }
    } else if ((efbg->status & EffectBg_STATUS_PALM) != 0) {
        if (season == mTM_SEASON_WINTER) {
            skeleton = winter_palm_model_tbl[variant][type];
            animation = winter_palm_anime_tbl[variant][type];
        } else {
            skeleton = summer_palm_model_tbl[variant][type];
            animation = summer_palm_anime_tbl[variant][type];
        }
    } else {
        if (season == mTM_SEASON_WINTER) {
            skeleton = winter_tree_model_tbl[variant][type];
            animation = winter_tree_anime_tbl[variant][type];
        } else if (Common_Get(time).term_idx == mTM_TERM_4) {
            skeleton = cherry_tree_model_tbl[variant][type];
            animation = cherry_tree_anime_tbl[variant][type];
        } else {
            skeleton = summer_tree_model_tbl[variant][type];
            animation = summer_tree_anime_tbl[variant][type];
        }
    }

    cKF_SkeletonInfo_R_ct(&efbg->keyframe, skeleton, animation, efbg->work, efbg->morph);
    cKF_SkeletonInfo_R_init_standard_stop(&efbg->keyframe, animation, NULL);
    cKF_SkeletonInfo_R_play(&efbg->keyframe);
    efbg->keyframe.frame_control.speed = 0.5f;

    efbg->status |= EffectBg_STATUS_ACTIVE;
    efbg->type = type;
    efbg->variant = variant;
    if (type == EffectBG_EFFECT_SHAKE_SMALL) {
        efbg->timer_max = 18;
        efbg->base_pos.y += 1.0f;
    } else if (type == EffectBG_EFFECT_SHAKE_LARGE) {
        efbg->timer_max = 82;
        efbg->base_pos.y += 1.0f;
    } else if (type == EffectBG_EFFECT_SHAKE) {
        efbg->timer_max = 22;
        efbg->base_pos.y += 1.0f;
    } else {
        efbg->base_pos.y += 2.0f;

        switch (variant) {
            case EffectBG_VARIANT_TREE_MED:
                sAdo_OngenTrgStart(NA_SE_63, &efbg->base_pos);
                break;
            case EffectBG_VARIANT_TREE_LARGE:
                sAdo_OngenTrgStart(NA_SE_65, &efbg->base_pos);
                break;
            case EffectBG_VARIANT_TREE_FULL:
                sAdo_OngenTrgStart(NA_SE_67, &efbg->base_pos);
                break;
        }

        efbg->timer_max = 98;
    }

    if ((efbg->status & EffectBg_STATUS_PALM) != 0 && efbg->variant == EffectBG_VARIANT_TREE_FULL) {
        efbg->base_pos.y += (f32)(int)GETREG(TAKREG, 50) * 0.1f;
        efbg->base_pos.z += -2.0f + (f32)(int)GETREG(TAKREG, 51) * 0.1f;
    } else if ((efbg->status & EffectBg_STATUS_CEDAR) != 0) {
        efbg->base_pos.y += 0.5f;
        efbg->base_pos.z += 0.5f;
    }

    if (Common_Get(time).term_idx == mTM_TERM_16 || Common_Get(time).term_idx == mTM_TERM_15) {
        mFI_Wpos2UtNum_inBlock(&efbg->block_ux, &efbg->block_uz, efbg->base_pos);
    } else {
        efbg->block_ux = 0;
        efbg->block_uz = 0;
    }

    efbg->timer = 0;
    efbg->timer_accum = 0.0f;
}

static void EffectBG_object_dt(EffectBg_c* efbg, GAME* game) {
    efbg->status = 0;
}

static int EffectBG_object_timer_step(EffectBg_c* efbg, GAME* game) {
    if ((efbg->status & 0x02) != 0) {
        efbg->add_angle += 0xDAC;
    }

    if (efbg->timer == 70 && (efbg->type == EffectBG_EFFECT_CUT_RIGHT || efbg->type == EffectBG_EFFECT_CUT_LEFT) &&
        (efbg->status & 0x02) == 0) {
        s16 count;

        switch (efbg->variant) {
            case EffectBG_VARIANT_TREE_MED:
                count = 5;
                break;
            case EffectBG_VARIANT_TREE_LARGE:
                count = 7;
                break;
            case EffectBG_VARIANT_TREE_FULL:
                count = 9;
                break;
            default:
                count = 5;
                break;
        }

        EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, count, 1);
        sAdo_OngenTrgStart(NA_SE_108, &efbg->base_pos);
    } else if (efbg->timer == 2 && efbg->type != EffectBG_EFFECT_SHAKE_SMALL &&
               efbg->type != EffectBG_EFFECT_SHAKE_LARGE) {
        EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, 3, 0);
    } else if ((efbg->timer & 0xF) == 0 && efbg->timer != 0 && efbg->timer < 70 &&
               efbg->type != EffectBG_EFFECT_SHAKE_SMALL && efbg->type != EffectBG_EFFECT_SHAKE_LARGE) {
        EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, 1, 0);
    } else if ((efbg->timer & 0xF) == 0 && efbg->type == EffectBG_EFFECT_SHAKE_SMALL) {
        EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, 1, 3);
    } else if ((efbg->timer & 0xF) == 0 && efbg->timer != 0 && efbg->type == EffectBG_EFFECT_SHAKE_LARGE) {
        EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, 1, 4);
    }

    if (efbg->timer >= efbg->timer_max) {
        EffectBG_object_dt(efbg, game);
        return FALSE;
    }

    efbg->timer++;
    return TRUE;
}

static void EffectBG_object_move(EffectBg_c* efbg, GAME* game) {
    xyz_t check_pos = efbg->effect_pos;
    f32 ground_y;
    int ticks;
    int i;

    if (efbg->type == EffectBG_EFFECT_CUT_RIGHT) {
        check_pos.x -= 21.0f;
    } else if (efbg->type == EffectBG_EFFECT_CUT_LEFT) {
        check_pos.x += 21.0f;
    }

    ground_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, check_pos, 0.0f);
    if ((efbg->status & 0x02) == 0 && !EffectBG_IS_SHAKE(efbg->type) && efbg->effect_pos.y < ground_y) {
        if (!EfbgBgitemTreeCheck(check_pos)) {
            s16 count;

            switch (efbg->variant) {
                case EffectBG_VARIANT_TREE_MED:
                    count = 5;
                    break;
                case EffectBG_VARIANT_TREE_LARGE:
                    count = 7;
                    break;
                case EffectBG_VARIANT_TREE_FULL:
                    count = 9;
                    break;
                default:
                    count = 5;
                    break;
            }

            EffectBG_Make_Leafs(efbg, game, efbg->effect_pos, count, 1);
            efbg->leaf_angle = 0x2BC;
            sAdo_OngenTrgStart(NA_SE_108, &efbg->base_pos);
            efbg->status |= 0x02;
        }
    }

    if ((efbg->status & 0x02) == 0) {
        cKF_SkeletonInfo_R_play(&efbg->keyframe);
    } else {
        add_calc_short_angle2(&efbg->leaf_angle, 0, 1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.9f))), 125, 0);
    }

    ticks = graph_dt_60hz_ticks(game, &efbg->timer_accum);
    for (i = 0; i < ticks; i++) {
        if (!EffectBG_object_timer_step(efbg, game)) {
            break;
        }
    }
}

static void Effectbg_actor_move(ACTOR* actorx, GAME* game) {
    EffectBg_c* efbg = efbg_start_p;
    int i;

    for (i = 0; i < EffectBg_ENTRY_NUM; i++, efbg++) {
        if ((efbg->status & EffectBg_STATUS_ACTIVE) != 0) {
            EffectBG_object_move(efbg, game);
        }
    }
}

static int EffectBG_object_before_display(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                          u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    EffectBg_c* efbg = (EffectBg_c*)arg;

    if (joint_idx == 3) {
        joint_rot->y += (int)((f32)efbg->leaf_angle * sin_s(efbg->add_angle));
        joint_rot->z += (int)((f32)efbg->leaf_angle * cos_s(efbg->add_angle));
    }

    if (efbg->variant == EffectBG_VARIANT_TREE_FULL && Common_Get(time).season == mTM_SEASON_WINTER &&
        ((!EffectBG_IS_SHAKE(efbg->type) && joint_idx == 4) || (EffectBG_IS_SHAKE(efbg->type) && joint_idx == 2))) {
        if ((Common_Get(time).term_idx != mTM_TERM_16 && Common_Get(time).term_idx != mTM_TERM_15) ||
            ((efbg->status & EffectBg_STATUS_XMAS) == 0)) {
            *joint_shape = NULL;
        } else {
            GAME_PLAY* play = (GAME_PLAY*)game;
            int type = ((play->game_frame & ~0x1F) + efbg->block_ux + efbg->block_uz) % 3;

            OPEN_DISP(game->graph);
            if (type == 0) {
                gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 255, 255, 255, 100, 1);
            } else if (type == 1) {
                gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 255, 100, 255, 255, 1);
            } else {
                gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 255, 255, 100, 255, 1);
            }

            CLOSE_DISP(game->graph);
        }
    }

    return TRUE;
}

static int EffectBG_object_before_display_xlu(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx,
                                              Gfx** joint_shape, u8* joint_flags, void* arg, s_xyz* joint_rot,
                                              xyz_t* joint_pos) {
    EffectBg_c* efbg = (EffectBg_c*)arg;

    if (joint_idx == 3) {
        joint_rot->y += (int)((f32)efbg->leaf_angle * sin_s(efbg->add_angle));
        joint_rot->z += (int)((f32)efbg->leaf_angle * cos_s(efbg->add_angle));
    }

    if (efbg->variant == EffectBG_VARIANT_TREE_FULL && Common_Get(time).season == mTM_SEASON_WINTER &&
        ((!EffectBG_IS_SHAKE(efbg->type) && joint_idx == 4) || (EffectBG_IS_SHAKE(efbg->type) && joint_idx == 2))) {
        if ((Common_Get(time).term_idx != mTM_TERM_16 && Common_Get(time).term_idx != mTM_TERM_15) ||
            ((efbg->status & EffectBg_STATUS_XMAS) == 0)) {
            *joint_shape = NULL;
        } else {
            GAME_PLAY* play = (GAME_PLAY*)game;
            int type = ((play->game_frame & ~0x1F) + efbg->block_ux + efbg->block_uz) % 3;
            f32 remain = efbg->timer_max - efbg->timer;
            f32 divisor = efbg->timer_max - 70;
            u8 alpha = (u8)(255.0f * (remain / divisor));

            OPEN_DISP(game->graph);
            if (type == 0) {
                gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, alpha, 255, 255, 100, 0);
            } else if (type == 1) {
                gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, alpha, 100, 255, 255, 0);
            } else {
                gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, alpha, 255, 100, 255, 0);
            }

            CLOSE_DISP(game->graph);
        }
    }

    *joint_flags = TRUE;
    return TRUE;
}

static int EffectBG_object_after_display(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                         u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    EffectBg_c* efbg = (EffectBg_c*)arg;

    if ((joint_idx == 3 && !EffectBG_IS_SHAKE(efbg->type)) || (joint_idx == 0 && EffectBG_IS_SHAKE(efbg->type))) {
        f32 x;

        if ((efbg->status & EffectBg_STATUS_CEDAR) != 0) {
            x = GETREG(TAKREG, 41) + 1000.0f;
        } else {
            x = 2000.0f;
        }

        Matrix_Position_VecX(x, &efbg->effect_pos);
    }

    return FALSE;
}

static void EffectBG_object_draw(EffectBg_c* efbg, GAME* game) {
    N64Mtx* mtx;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    if (game->frame_counter & 1) {
        mtx = efbg->mtx[0];
    } else {
        mtx = efbg->mtx[1];
    }

    OPEN_DISP(game->graph);

    Matrix_translate(efbg->base_pos.x, efbg->base_pos.y, efbg->base_pos.z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    if (efbg->timer < 70) {
        gDPSetRenderMode(NEXT_POLY_OPA_DISP, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2);
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 255, 255, 255, 255, 1);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        cKF_Si3_draw_R_SV(game, &efbg->keyframe, mtx, &EffectBG_object_before_display, &EffectBG_object_after_display,
                          efbg);
    } else {
        gDPSetRenderMode(NEXT_POLY_XLU_DISP, G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2);

        if (efbg->type == EffectBG_EFFECT_CUT_RIGHT || efbg->type == EffectBG_EFFECT_CUT_LEFT) {
            f32 remain = efbg->timer_max - efbg->timer;
            f32 divisor = efbg->timer_max - 70;
            u8 alpha = (u8)(255.0f * (remain / divisor));

            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, alpha, 255, 255, 255, 0);
        } else {
            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, 1);
        }

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        cKF_Si3_draw_R_SV(game, &efbg->keyframe, mtx, &EffectBG_object_before_display_xlu,
                          &EffectBG_object_after_display, efbg);
    }

    CLOSE_DISP(game->graph);
}

static void Effectbg_actor_draw(ACTOR* actorx, GAME* game) {
    EFFECTBG_ACTOR* effectbg_actor = (EFFECTBG_ACTOR*)actorx;
    EffectBg_c* efbg;
    int i;

    OPEN_DISP(game->graph);

    gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, effectbg_actor->tree_pal);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, effectbg_actor->tree_pal);
    gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, effectbg_actor->palm_pal);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, effectbg_actor->palm_pal);

    efbg = efbg_start_p;

    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);
    for (i = 0; i < EffectBg_ENTRY_NUM; i++, efbg++) {
        if ((efbg->status & EffectBg_STATUS_ACTIVE) != 0) {
            if ((efbg->status & EffectBg_STATUS_PALM) != 0) {
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, effectbg_actor->palm_pal);
                gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, effectbg_actor->palm_pal);
            } else if ((efbg->status & EffectBg_STATUS_CEDAR) != 0) {
                // There must be a misunderstanding for the various palettes, why else would it load this, unless it's a
                // mistake
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, effectbg_actor->palm_pal2);
                gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, effectbg_actor->palm_pal2);
            } else if ((efbg->status & EffectBg_STATUS_GOLD) != 0) {
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, effectbg_actor->gold_pal);
                gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, effectbg_actor->gold_pal);
            } else {
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, effectbg_actor->tree_pal);
                gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, effectbg_actor->tree_pal);
            }

            EffectBG_object_draw(efbg, game);
        }
    }

    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);

    CLOSE_DISP(game->graph);
}

static void Make_EffectBG(GAME* game, s16 type, s16 variant, xyz_t* pos) {
    EffectBg_c* efbg = efbg_start_p;
    s16 timer_max = 0;
    int idx = 0;
    int i;

    if (variant == EffectBG_VARIANT_TREE_SMALL || variant == EffectBG_VARIANT_PALM_SMALL ||
        variant == EffectBG_VARIANT_CEDAR_SMALL || variant == EffectBG_VARIANT_GOLD_SMALL) {
        xyz_t small_pos = *pos;
        s16 arg;

        if (type == EffectBG_EFFECT_CUT_RIGHT || type == EffectBG_EFFECT_CUT_LEFT) {
            if (variant == EffectBG_VARIANT_TREE_SMALL) {
                EffectBG_Make_Leafs(efbg, game, small_pos, 4, EffectBG_EFFECT_CUT_RIGHT);
            } else if (variant == EffectBG_VARIANT_PALM_SMALL) {
                EffectBG_Make_Leafs(efbg, game, small_pos, 4, 5);
            } else if (variant == EffectBG_VARIANT_CEDAR_SMALL) {
                EffectBG_Make_Leafs(efbg, game, small_pos, 4, 6);
            } else if (variant == EffectBG_VARIANT_GOLD_SMALL) {
                EffectBG_Make_Leafs(efbg, game, small_pos, 4, 7);
            }

            sAdo_OngenTrgStart(NA_SE_61, &small_pos);
        }

        if (variant == EffectBG_VARIANT_PALM_SMALL) {
            small_pos.y += 19.0f + (f32)(int)GETREG(TAKREG, 50) * 0.1f;
            small_pos.z += -2.0f + (f32)(int)GETREG(TAKREG, 51) * 0.1f;
            arg = 1;
        } else if (variant == EffectBG_VARIANT_CEDAR_SMALL) {
            small_pos.y += 0.5f + (f32)(int)GETREG(TAKREG, 50) * 0.1f;
            small_pos.z += -2.0f + (f32)(int)GETREG(TAKREG, 51) * 0.1f;
            arg = 2;
        } else if (variant == EffectBG_VARIANT_GOLD_SMALL) {
            small_pos.y += 26.8f + (f32)(int)GETREG(TAKREG, 50) * 0.1f;
            arg = 3;
        } else {
            small_pos.y += 26.8f;
            arg = 0;
        }

        eEC_CLIP->effect_make_proc(eEC_EFFECT_YOUNG_TREE, small_pos, 2, 0, game, RSV_NO, type, arg);
    } else {
        efbg = efbg_start_p;
        for (i = 0; i < EffectBg_ENTRY_NUM; i++) {
            if ((efbg->status & EffectBg_STATUS_ACTIVE) == 0) {
                efbg->base_pos = efbg->effect_pos = *pos;
                efbg->effect_pos.y += 90.0f;
                EffectBG_object_ct(efbg, game, type, variant);
                return;
            }

            if (efbg->timer >= timer_max) {
                timer_max = efbg->timer;
                idx = i;
            }

            efbg++;
        }

        efbg_start_p[idx].base_pos = *pos;
        EffectBG_object_ct(&efbg_start_p[idx], game, type, variant);
    }
}
