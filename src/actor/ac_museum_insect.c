#include "ac_museum_insect_priv.h"
// clang-format off
extern Gfx
    act_m_mu_monshiro1T_model,
    act_m_mu_monshiro2T_model,
    act_m_mu_monki1T_model,
    act_m_mu_monki2T_model,
    act_m_mu_kiageha1T_model,
    act_m_mu_kiageha2T_model,
    act_m_mu_ohmurasaki1T_model,
    act_m_mu_ohmurasaki2T_model,
    act_m_mu_minmin1_1T_model,
    act_m_mu_minmin1_2T_model,
    act_m_mu_tukutuku1_1T_model,
    act_m_mu_tukutuku1_2T_model,
    act_m_mu_higurashi1_1T_model,
    act_m_mu_higurashi1_2T_model,
    act_m_mu_abura1_1T_model,
    act_m_mu_abura1_2T_model,
    act_m_mu_shiokara1_1T_model,
    act_m_mu_shiokara1_2T_model,
    act_m_mu_shiokara2_2T_model,
    act_m_mu_akiakane1_1T_model,
    act_m_mu_akiakane1_2T_model,
    act_m_mu_akiakane2_2T_model,
    act_m_mu_ginyanma1_1T_model,
    act_m_mu_ginyanma1_2T_model,
    act_m_mu_ginyanma2_2T_model,
    act_m_mu_oniyanma1_1T_model,
    act_m_mu_oniyanma1_2T_model,
    act_m_mu_oniyanma2_2T_model,
    act_m_mu_syouryou1T_model,
    act_m_mu_syouryou2_2T_model,
    act_m_mu_tonosama1T_model,
    act_m_mu_tonosama2_2T_model,
    act_m_mu_koorogi1T_model,
    act_m_mu_koorogi2_2T_model,
    act_m_mu_kirigirisu1T_model,
    act_m_mu_kirigirisu2_2T_model,
    act_m_mu_suzumushi1T_model,
    act_m_mu_suzumushi2_2T_model,
    act_m_mu_matumushi1T_model,
    act_m_mu_matumushi2_2T_model,
    act_m_mu_tentou1T_model,
    act_m_mu_tentou2T_model,
    act_m_mu_nanahoshi1T_model,
    act_m_mu_nanahoshi2T_model,
    act_m_mu_kamakiri1T_model,
    act_m_mu_kamakiri2_2T_model,
    act_m_mu_maimaiT_model,
    act_m_mu_hachi1_1T_model,
    act_m_mu_hachi1_2T_model,
    act_m_mu_hachi2_2T_model,
    act_m_mu_kanabun1T_model,
    act_m_mu_kabuto1T_model,
    act_m_mu_hirata1T_model,
    act_m_mu_tamamushi1T_model,
    act_m_mu_gomadara1T_model,
    act_m_mu_nokogiri1T_model,
    act_m_mu_miyama1T_model,
    act_m_mu_okuwa1T_model,
    act_m_mu_amenbo1T_model,
    act_m_mu_amenbo2T_model,
    act_m_mu_mino1_1T_model,
    act_m_mu_mino1_2T_model,
    act_m_mu_mino2T_model,
    act_m_mu_kumo1_1T_mode,
    act_m_mu_kumo1_2T_mode,
    act_m_mu_kumo2T_model,
    act_m_mu_kumo1_1T_model,
    act_m_mu_kumo1_2T_model,
    act_m_mu_danna1T_model,
    act_m_mu_danna2T_model,
    act_m_mu_genji2_a_model,
    act_m_mu_genji2_b_model,
    act_m_mu_genji2_c_model,
    act_m_mu_genji2_d_model,
    act_m_mu_dango1T_model,
    act_m_mu_dango2T_model,
    act_m_mu_ariT_model,
    act_m_mu_keraT_model,
    act_m_mu_ka1T_model,
    act_m_mu_ka2_1T_model,
    act_m_mu_ka2_2T_model;

ACTOR_PROFILE Museum_Insect_Profile = {
    mAc_PROFILE_MUSEUM_INSECT,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_408,
    sizeof(MUSEUM_INSECT_ACTOR),
    Museum_Insect_Actor_ct,
    Museum_Insect_Actor_dt,
    Museum_Insect_Actor_move,
    Museum_Insect_Actor_draw,
    NULL,
};

rgba_t window_color = { 
    0xff, 0xff, 0xcd, 0xff 
};

Gfx *m_monshiro_disp_tbl[] = {
    &act_m_mu_monshiro1T_model,
    &act_m_mu_monshiro2T_model,
    NULL
};

Gfx *m_monki_disp_tbl[] = {
    &act_m_mu_monki1T_model,
    &act_m_mu_monki2T_model,
    NULL
};

Gfx *m_ageha_disp_tbl[] = {
    &act_m_mu_kiageha1T_model,
    &act_m_mu_kiageha2T_model,
    NULL
};

Gfx *m_ohmurasaki_disp_tbl[] = {
    &act_m_mu_ohmurasaki1T_model,
    &act_m_mu_ohmurasaki2T_model,
    NULL
};

Gfx *m_minmin_disp_tbl[] = {
    &act_m_mu_minmin1_1T_model,
    &act_m_mu_minmin1_2T_model,
    NULL
};

Gfx *m_tukutuku_disp_tbl[] = {
    &act_m_mu_tukutuku1_1T_model,
    &act_m_mu_tukutuku1_2T_model,
    NULL
};

Gfx *m_higurashi_disp_tbl[] = {
    &act_m_mu_higurashi1_1T_model,
    &act_m_mu_higurashi1_2T_model,
    NULL
};

Gfx *m_abura_disp_tbl[] = {
    &act_m_mu_abura1_1T_model,
    &act_m_mu_abura1_2T_model,
    NULL
};

Gfx *m_shiokara_disp_tbl[] = {
    &act_m_mu_shiokara1_1T_model,
    &act_m_mu_shiokara1_2T_model,
    &act_m_mu_shiokara2_2T_model,
    NULL
};

Gfx *m_akiakane_disp_tbl[] = {
    &act_m_mu_akiakane1_1T_model,
    &act_m_mu_akiakane1_2T_model,
    &act_m_mu_akiakane2_2T_model,
    NULL
};

Gfx *m_ginyanma_disp_tbl[] = {
    &act_m_mu_ginyanma1_1T_model,
    &act_m_mu_ginyanma1_2T_model,
    &act_m_mu_ginyanma2_2T_model,
    NULL
};

Gfx *m_oniyanma_disp_tbl[] = {
    &act_m_mu_oniyanma1_1T_model,
    &act_m_mu_oniyanma1_2T_model,
    &act_m_mu_oniyanma2_2T_model,
    NULL
};

Gfx *m_syouryou_disp_tbl[] = {
    &act_m_mu_syouryou1T_model,
    &act_m_mu_syouryou2_2T_model,
    NULL
};

Gfx *m_tonosama_disp_tbl[] = {
    &act_m_mu_tonosama1T_model,
    &act_m_mu_tonosama2_2T_model,
    NULL
};

Gfx *m_koorogi_disp_tbl[] = {
    &act_m_mu_koorogi1T_model,
    &act_m_mu_koorogi2_2T_model,
    NULL
};

Gfx *m_kirigirisu_disp_tbl[] = {
    &act_m_mu_kirigirisu1T_model,
    &act_m_mu_kirigirisu2_2T_model,
    NULL
};

Gfx *m_suzumushi_disp_tbl[] = {
    &act_m_mu_suzumushi1T_model,
    &act_m_mu_suzumushi2_2T_model,
    NULL
};

Gfx *m_matumushi_disp_tbl[] = {
    &act_m_mu_matumushi1T_model,
    &act_m_mu_matumushi2_2T_model,
    NULL
};

Gfx *m_tentou_disp_tbl[] = {
    &act_m_mu_tentou1T_model,
    &act_m_mu_tentou2T_model,
    NULL
};

Gfx *m_nanahoshi_disp_tbl[] = {
    &act_m_mu_nanahoshi1T_model,
    &act_m_mu_nanahoshi2T_model,
    NULL
};

Gfx *m_kamakiri_disp_tbl[] = {
    &act_m_mu_kamakiri1T_model,
    &act_m_mu_kamakiri2_2T_model,
    NULL
};

Gfx *m_maimai_disp_tbl[] = {
    &act_m_mu_maimaiT_model,
    NULL
};

Gfx *m_hachi_disp_tbl[] = {
    &act_m_mu_hachi1_1T_model,
    &act_m_mu_hachi1_2T_model,
    &act_m_mu_hachi2_2T_model,
    NULL
};

Gfx *m_kanabun_disp_tbl[] = {
    &act_m_mu_kanabun1T_model,
    NULL
};

Gfx *m_kabuto_disp_tbl[] = {
    &act_m_mu_kabuto1T_model,
    NULL
};

Gfx *m_hirata_disp_tbl[] = {
    &act_m_mu_hirata1T_model,
    NULL
};

Gfx *m_tamamushi_disp_tbl[] = {
    &act_m_mu_tamamushi1T_model,
    NULL
};

Gfx *m_gomadara_disp_tbl[] = {
    &act_m_mu_gomadara1T_model,
    NULL
};

Gfx *m_nokogiri_disp_tbl[] = {
    &act_m_mu_nokogiri1T_model,
    NULL
};

Gfx *m_miyama_disp_tbl[] = {
    &act_m_mu_miyama1T_model,
    NULL
};

Gfx *m_okuwa_disp_tbl[] = {
    &act_m_mu_okuwa1T_model,
    NULL
};

Gfx *m_amenbo_disp_tbl[] = {
    &act_m_mu_amenbo1T_model,
    &act_m_mu_amenbo2T_model,
    NULL
};

Gfx *m_mino_disp_tbl[] = {
    &act_m_mu_mino1_1T_model,
    &act_m_mu_mino1_2T_model,
    &act_m_mu_mino2T_model,
    NULL
};

Gfx *m_kumo_disp_tbl[] = {
    &act_m_mu_kumo1_1T_model,
    &act_m_mu_kumo1_2T_model,
    &act_m_mu_kumo2T_model,
    NULL
};

Gfx *m_goki_disp_tbl[] = {
    &act_m_mu_danna1T_model,
    &act_m_mu_danna2T_model,
    NULL
};

Gfx *m_genji_disp_tbl[] = {
    &act_m_mu_genji2_a_model,
    &act_m_mu_genji2_b_model,
    &act_m_mu_genji2_c_model,
    &act_m_mu_genji2_d_model,
    NULL
};

Gfx *m_dango_disp_tbl[] = {
    &act_m_mu_dango1T_model,
    &act_m_mu_dango2T_model,
    NULL
};

Gfx *m_ari_disp_tbl[] = {
    &act_m_mu_ariT_model,
    NULL
};

Gfx *m_okera_disp_tbl[] = {
    &act_m_mu_keraT_model,
    NULL
};

Gfx *m_ka_disp_tbl[] = {
    &act_m_mu_ka1T_model,
    &act_m_mu_ka2_1T_model,
    &act_m_mu_ka2_2T_model,
    NULL
};

Gfx **minsect_mdl[] = {
    m_monshiro_disp_tbl,
    m_monki_disp_tbl,
    m_ageha_disp_tbl,
    m_ohmurasaki_disp_tbl,
    m_minmin_disp_tbl,
    m_tukutuku_disp_tbl,
    m_higurashi_disp_tbl,
    m_abura_disp_tbl,
    m_hachi_disp_tbl,
    m_shiokara_disp_tbl,
    m_akiakane_disp_tbl,
    m_ginyanma_disp_tbl,
    m_oniyanma_disp_tbl,
    m_syouryou_disp_tbl,
    m_tonosama_disp_tbl,
    m_koorogi_disp_tbl,
    m_kirigirisu_disp_tbl,
    m_suzumushi_disp_tbl,
    m_matumushi_disp_tbl,
    m_kanabun_disp_tbl,
    m_kabuto_disp_tbl,
    m_hirata_disp_tbl,
    m_tamamushi_disp_tbl,
    m_gomadara_disp_tbl,
    m_tentou_disp_tbl,
    m_nanahoshi_disp_tbl,
    m_kamakiri_disp_tbl,
    m_genji_disp_tbl,
    m_goki_disp_tbl,
    m_nokogiri_disp_tbl,
    m_miyama_disp_tbl,
    m_okuwa_disp_tbl,
    m_maimai_disp_tbl,
    m_okera_disp_tbl,
    m_amenbo_disp_tbl,
    m_mino_disp_tbl,
    m_dango_disp_tbl,
    m_kumo_disp_tbl,
    m_ari_disp_tbl,
    m_ka_disp_tbl
};

PRIV_INSECT_PROCESS minsect_ct[] = {
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_chou_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_semi_ct,
    minsect_hachi_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_tonbo_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_batta_ct,
    minsect_kabuto_ct,
    minsect_kabuto_ct,
    minsect_kuwagata_ct,
    minsect_kabuto_ct,
    minsect_kabuto_ct,
    minsect_tentou_ct,
    minsect_tentou_ct,
    minsect_tentou_ct,
    minsect_genji_ct,
    minsect_goki_ct,
    minsect_kuwagata_ct,
    minsect_kuwagata_ct,
    minsect_kuwagata_ct,
    minsect_tentou_ct,
    minsect_okera_ct,
    minsect_amenbo_ct,
    minsect_mino_ct,
    minsect_dango_ct,
    minsect_kumo_ct,
    minsect_ari_ct,
    minsect_ka_ct
};

PRIV_INSECT_PROCESS minsect_mv[] = {
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_chou_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_semi_mv,
    minsect_hachi_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_tonbo_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_batta_mv,
    minsect_kabuto_mv,
    minsect_kabuto_mv,
    minsect_kuwagata_mv,
    minsect_kabuto_mv,
    minsect_kabuto_mv,
    minsect_tentou_mv,
    minsect_tentou_mv,
    minsect_tentou_mv,
    minsect_genji_mv,
    minsect_goki_mv,
    minsect_kuwagata_mv,
    minsect_kuwagata_mv,
    minsect_kuwagata_mv,
    minsect_tentou_mv,
    minsect_okera_mv,
    minsect_amenbo_mv,
    minsect_mino_mv,
    minsect_dango_mv,
    minsect_kumo_mv,
    minsect_ari_mv,
    minsect_ka_mv
};

PRIV_INSECT_PROCESS minsect_dw[] = {
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_chou_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_semi_dw,
    minsect_hachi_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_tonbo_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_batta_dw,
    minsect_kabuto_dw,
    minsect_kabuto_dw,
    minsect_kuwagata_dw,
    minsect_kabuto_dw,
    minsect_kabuto_dw,
    minsect_tentou_dw,
    minsect_tentou_dw,
    minsect_tentou_dw,
    minsect_genji_dw,
    minsect_goki_dw,
    minsect_kuwagata_dw,
    minsect_kuwagata_dw,
    minsect_kuwagata_dw,
    minsect_tentou_dw,
    minsect_okera_dw,
    minsect_amenbo_dw,
    minsect_mino_dw,
    minsect_dango_dw,
    minsect_kumo_dw,
    minsect_ari_dw,
    minsect_ka_dw
};

f32 minsect_shadow_scale_tbl[] = {
    1.0f,
    1.0f,
    1.5f,
    1.5f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    1.0f,
    1.0f,
    1.5f,
    1.5f,
    1.8f,
    1.0f,
    1.5f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    1.0f,
    0.0f,
    1.0f,
    0.6f,
    0.7f,
    0.0f,
    0.0f
};

int active_time_tbl[] = {
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 4, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0)
};

int relax_time_tbl[] = {
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC(16, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(17, 0, 0),
    mTM_TIME2SEC(4, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 8, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC(19, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0),
    mTM_TIME2SEC( 0, 0, 0)
};

xyz_t flower_pos[8] = {
    { 147.0f, 66.f, 169.f },
    { 238.0f, 66.f, 201.f },
    { 264.0f, 66.f, 164.f },
    { 165.0f, 66.f, 219.f },
    { 181.0f, 66.f, 235.f },
    { 199.0f, 66.f, 188.f },
    { 327.5f, 66.f, 154.f },
    { 410.0f, 66.f, 190.f }
};

xyz_t ohmurasaki_tree_pos = {
    360.f, 85.f, 265.f
};

xyz_t tree_pos[8] = {
    {  92.f, 0.f, -15.f },
    { 168.f, 0.f,   5.f },
    { 244.f, 0.f, -15.f },
    { 316.f, 0.f,   5.f },
    { 392.f, 0.f, -15.f },
    { 468.f, 0.f,   5.f },
    { 360.f, 0.f, 245.f },
    { 165.f, 0.f, 485.f }
};

xyz_t rock_pos[] = {
    { 225.f, 0.f, 388.5f },
    { 385.f, 0.f, 485.0f }
};

// rodata
const s16 aim_angle_tbl[6] = {
    DEG2SHORT_ANGLE(45 + 0),
    DEG2SHORT_ANGLE(45 + 90),
    DEG2SHORT_ANGLE(45 + 180),
    DEG2SHORT_ANGLE(45 + 270),
    DEG2SHORT_ANGLE(45 + 180),
    DEG2SHORT_ANGLE(45 + 90)
};

const f32 base_high_tbl[4] = {
    85.f, 95.f, 90.f, 90.f
};

// clang-format on
MUSEUM_INSECT_ACTOR* MI_Control_Actor = NULL;
static MUSEUM_INSECT_PRIVATE_DATA* MI_Draw_1894 = NULL;
static MUSEUM_INSECT_PRIVATE_DATA* MI_Draw_1CA0 = NULL;

#include "../src/actor/ac_museum_insect_base.c_inc"

int Museum_Insect_GetMsgNo(ACTOR* actorx) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int insect_caught_by = actor->_2F80[actor->_2F7C].insectInfo;
    s16 insect_no = ITM_INSECT_START + actor->_2F80[actor->_2F7C].insectName;
    int msgNo;
    mIN_copy_name_str(item_name, insect_no);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), mMsg_ITEM_STR0, item_name, ARRAY_COUNT(item_name),
                          mIN_get_item_article(insect_no));

    if (insect_caught_by >= 1 && insect_caught_by <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0,
                          common_data.save.save.private_data[insect_caught_by - 1].player_ID.player_name, 8);
    }

    if (actor->_2F7C < actor->_2F78 - 1) {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = MSG_12194;
        } else {
            msgNo = MSG_12195;
        }
    } else {
        if (insect_caught_by >= 1 && insect_caught_by <= 4) {
            msgNo = MSG_12191;
        } else {
            msgNo = MSG_12192;
        }
    }

    return msgNo;
}

f32 minsect_scale_tbl[40] = { 0.01f, 0.01f, 0.01f,  0.01f,  0.008f, 0.008f, 0.008f, 0.008f, 0.01f, 0.01f,
                              0.01f, 0.01f, 0.01f,  0.01f,  0.01f,  0.01f,  0.01f,  0.01f,  0.01f, 0.01f,
                              0.01f, 0.01f, 0.009f, 0.009f, 0.009f, 0.009f, 0.01f,  0.01f,  0.01f, 0.01f,
                              0.01f, 0.01f, 0.01f,  0.01f,  0.007f, 0.01f,  0.01f,  0.01f,  0.01f, 0.01f };

int Museum_Insect_Check_Talk_Distance(GAME* game, int i) {
    static xyz_t kanban_pos[6] = { { 140.f, 40.f, 60.f },  { 420.f, 40.f, 60.f },  { 220.f, 40.f, 300.f },
                                   { 380.f, 40.f, 300.f }, { 180.f, 40.f, 540.f }, { 340.f, 40.f, 540.f } };
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t p;
    PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);
    s16 newAngle = player_actor->actor_class.world.angle.y + DEG2SHORT_ANGLE(-180);
    xyz_t_sub(&player_actor->actor_class.world.position, &kanban_pos[i], &p);

    if (ABS(p.x) < 20.f && ABS(p.z) < 20.f && ABS(newAngle) < DEG2SHORT_ANGLE(67.5f)) {
        return TRUE;
    }
    return FALSE;
}

void Museum_Insect_Set_MsgInsectInfo(ACTOR* actorx, int groupNum) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int i;
    static int group_max_num[6] = { 7, 6, 6, 6, 7, 7 };
    static int group_1_insect_name[7] = { 22, 4, 21, 29, 38, 20, 7 };
    static int group_2_insect_name[6] = { 31, 30, 19, 5, 23, 6 };
    static int group_3_insect_name[6] = { 0, 25, 26, 1, 27, 2 };
    static int group_4_insect_name[6] = { 32, 34, 37, 3, 24, 39 };
    static int group_5_insect_name[7] = { 35, 8, 33, 9, 10, 11, 12 };
    static int group_6_insect_name[7] = { 15, 16, 18, 17, 13, 14, 36 };
    static int* group_insect_name[6] = { group_1_insect_name, group_2_insect_name, group_3_insect_name,
                                         group_4_insect_name, group_5_insect_name, group_6_insect_name };
    actor->_2F78 = 0;
    actor->_2F7C = 0;
    for (i = 0; i < group_max_num[groupNum]; i++) {
        s16 insectName = group_insect_name[groupNum][i];
        s16 s = mMmd_InsectInfo(insectName);
        if (s) {
            actor->_2F80[actor->_2F78].insectName = insectName;
            actor->_2F80[actor->_2F78].insectInfo = s;
            actor->_2F78++;
        }
    }
}

void Museum_Insect_set_talk_info(ACTOR* actorx) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int msg_no;
    if (actor->_2F78 > 0) {
        msg_no = Museum_Insect_GetMsgNo(actorx);
        actor->_2F7C++;
    } else {
        msg_no = MSG_12193;
    }
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_msg_num(msg_no);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

void Museum_Insect_Talk_process(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        s_xyz rot = get_player_actor_withoutCheck((GAME_PLAY*)game)->actor_class.shape_info.rotation;
        add_calc_short_angle2(&rot.y, DEG2SHORT_ANGLE(-180), 0.3f, DEG2SHORT_ANGLE(22.5), DEG2SHORT_ANGLE(0));
        get_player_actor_withoutCheck((GAME_PLAY*)gamePT)
            ->Set_force_position_angle_proc(gamePT, NULL, &rot, mPlayer_FORCE_POSITION_ANGLE_ROTY);
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p())) {
            int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            if (choice != -1) {
                if (choice == 0) {
                    int msgNum = Museum_Insect_GetMsgNo(actorx);
                    actor->_2F7C++;
                    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), msgNum);
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                } else {
                    mMsg_Set_CancelNormalContinue(mMsg_Get_base_window_p());
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                }
            }
        }
    } else if (chkTrigger(BUTTON_A) && !mDemo_Get_talk_actor()) {
        int i;
        for (i = 0; i < 6; i++) {
            if (Museum_Insect_Check_Talk_Distance(game, i)) {
                Museum_Insect_Set_MsgInsectInfo(actorx, i);
                mDemo_Request(mDemo_TYPE_SPEAK, actorx, Museum_Insect_set_talk_info);
            }
        }
    }
}

static f32 Museum_Insect_LerpF(f32 from, f32 to, f32 alpha) {
    return from + ((to - from) * alpha);
}

static s16 Museum_Insect_LerpAngle(s16 from, s16 to, f32 alpha) {
    s16 diff = (s16)(to - from);
    return from + (s16)((f32)diff * alpha);
}

static xyz_t Museum_Insect_LerpXYZ(xyz_t from, xyz_t to, f32 alpha) {
    xyz_t out;

    out.x = Museum_Insect_LerpF(from.x, to.x, alpha);
    out.y = Museum_Insect_LerpF(from.y, to.y, alpha);
    out.z = Museum_Insect_LerpF(from.z, to.z, alpha);

    return out;
}

static s_xyz Museum_Insect_LerpSXYZ(s_xyz from, s_xyz to, f32 alpha) {
    s_xyz out;

    out.x = Museum_Insect_LerpAngle(from.x, to.x, alpha);
    out.y = Museum_Insect_LerpAngle(from.y, to.y, alpha);
    out.z = Museum_Insect_LerpAngle(from.z, to.z, alpha);

    return out;
}

static BOOL Museum_Insect_ShouldInterpolateMotion(s16 type) {
    switch (type) {
        case aINS_INSECT_TYPE_COMMON_BUTTERFLY:
        case aINS_INSECT_TYPE_YELLOW_BUTTERFLY:
        case aINS_INSECT_TYPE_TIGER_BUTTERFLY:
        case aINS_INSECT_TYPE_PURPLE_BUTTERFLY:
        case aINS_INSECT_TYPE_ROBUST_CICADA:
        case aINS_INSECT_TYPE_WALKER_CICADA:
        case aINS_INSECT_TYPE_EVENING_CICADA:
        case aINS_INSECT_TYPE_BROWN_CICADA:
        case aINS_INSECT_TYPE_BEE:
        case aINS_INSECT_TYPE_COMMON_DRAGONFLY:
        case aINS_INSECT_TYPE_RED_DRAGONFLY:
        case aINS_INSECT_TYPE_DARNER_DRAGONFLY:
        case aINS_INSECT_TYPE_BANDED_DRAGONFLY:
        case aINS_INSECT_TYPE_FIREFLY:
        case aINS_INSECT_TYPE_BAGWORM:
        case aINS_INSECT_TYPE_SPIDER:
        case aINS_INSECT_TYPE_MOSQUITO:
            return TRUE;
        default:
            return FALSE;
    }
}

static void Museum_Insect_CopyLogicState(MUSEUM_INSECT_ACTOR* actor) {
    int i;

    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        actor->prevPrivInsects[i] = actor->privInsects[i];
    }

    for (i = 0; i < 6; i++) {
        actor->prev_1894[i] = actor->_1894[i];
    }

    for (i = 0; i < 15; i++) {
        actor->prev_1CA0[i] = actor->_1CA0[i];
    }
}

static void Museum_Insect_RefreshPosSounds(MUSEUM_INSECT_ACTOR* actor, GAME* game) {
    static u8 batta_sound_data[4] = { 0x9f, 0x9e, 0xa0, 0x9d };
    static const u8 semi_sound_data[4] = { 0x9b, 0x9a, 0x98, 0x97 };
    PLAYER_ACTOR* player = get_player_actor_withoutCheck((GAME_PLAY*)game);
    xyz_t player_pos = player->actor_class.world.position;
    MUSEUM_INSECT_PRIVATE_DATA* insect;
    f32 dist;

    insect = &actor->privInsects[aINS_INSECT_TYPE_COCKROACH];
    if ((insect->_8C & 1) && insect->_72 == 0 && insect->_40 > 0.0f) {
        sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, 0xa8, &insect->_1C);
    }

    insect = &actor->privInsects[aINS_INSECT_TYPE_MOSQUITO];
    if ((insect->_8C & 1) && search_position_distanceXZ(&insect->_1C, &player_pos) < 300.0f) {
        sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, 0xcf, &insect->_1C);
    }

    insect = &actor->privInsects[aINS_INSECT_TYPE_MOLE_CRICKET];
    if (insect->_8C & 1) {
        dist = search_position_distance(&insect->_1C, &player_pos);
        if (insect->_04 == okera_dig_wait_process && dist < 200.0f) {
            sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, 68, &insect->_1C);
        } else if (insect->_04 == okera_dig_up_process && dist < 200.0f) {
            sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, 69, &insect->_1C);
        }
    }

    {
        int i;

        for (i = aINS_INSECT_TYPE_ROBUST_CICADA; i <= aINS_INSECT_TYPE_BROWN_CICADA; i++) {
            insect = &actor->privInsects[i];
            if ((insect->_8C & 1) && insect->_8E && insect->_78 == 1 && insect->_72 == insect->_74 &&
                search_position_distance(&insect->_1C, &player_pos) < 200.0f) {
                sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, semi_sound_data[i - aINS_INSECT_TYPE_ROBUST_CICADA], &insect->_1C);
            }
        }

        for (i = aINS_INSECT_TYPE_CRICKET; i <= aINS_INSECT_TYPE_PINE_CRICKET; i++) {
            insect = &actor->privInsects[i];
            if ((insect->_8C & 1) && insect->_04 != minsect_batta_jump_process &&
                ((insect->_04 != minsect_batta_silent_process && insect->_8E) ||
                 (insect->_04 == minsect_batta_silent_process && insect->_8E == 0)) &&
                search_position_distanceXZ(&insect->_1C, &player_pos) < 200.0f) {
                sAdo_OngenPos((JaudioObjectId)(uintptr_t)insect, batta_sound_data[i - aINS_INSECT_TYPE_CRICKET], &insect->_1C);
            }
        }
    }
}

static void Museum_Insect_InterpolatePrivate(MUSEUM_INSECT_PRIVATE_DATA* out,
                                             const MUSEUM_INSECT_PRIVATE_DATA* from,
                                             const MUSEUM_INSECT_PRIVATE_DATA* to, f32 alpha, BOOL allow_motion) {
    *out = *to;

    if ((from->_8C & 1) == 0 || (to->_8C & 1) == 0) {
        return;
    }

    if (!allow_motion || !Museum_Insect_ShouldInterpolateMotion(to->_00)) {
        return;
    }

    out->_1C = Museum_Insect_LerpXYZ(from->_1C, to->_1C, alpha);
    out->_28 = Museum_Insect_LerpXYZ(from->_28, to->_28, alpha);
    out->_34 = Museum_Insect_LerpXYZ(from->_34, to->_34, alpha);
    out->_44 = Museum_Insect_LerpXYZ(from->_44, to->_44, alpha);
    out->_68 = Museum_Insect_LerpSXYZ(from->_68, to->_68, alpha);
    out->_58 = Museum_Insect_LerpF(from->_58, to->_58, alpha);
    out->_60 = Museum_Insect_LerpF(from->_60, to->_60, alpha);

    if (to->_00 != aINS_INSECT_TYPE_FIREFLY) {
        out->_5C = Museum_Insect_LerpF(from->_5C, to->_5C, alpha);
    } else {
        out->_0C = Museum_Insect_LerpF(from->_0C, to->_0C, alpha);
        out->_76 = Museum_Insect_LerpAngle(from->_76, to->_76, alpha);
        out->_7A = Museum_Insect_LerpAngle(from->_7A, to->_7A, alpha);
        out->_7E = Museum_Insect_LerpAngle(from->_7E, to->_7E, alpha);
    }
}

static void Museum_Insect_InterpolateFireflyFields(MUSEUM_INSECT_PRIVATE_DATA* out,
                                                   const MUSEUM_INSECT_PRIVATE_DATA* from,
                                                   const MUSEUM_INSECT_PRIVATE_DATA* to, f32 alpha) {
    if ((from->_8C & 1) == 0 || (to->_8C & 1) == 0) {
        return;
    }

    out->_0C = Museum_Insect_LerpF(from->_0C, to->_0C, alpha);
    out->_76 = Museum_Insect_LerpAngle(from->_76, to->_76, alpha);
    out->_7A = Museum_Insect_LerpAngle(from->_7A, to->_7A, alpha);
    out->_7E = Museum_Insect_LerpAngle(from->_7E, to->_7E, alpha);
}

static void Museum_Insect_InterpolateArray(MUSEUM_INSECT_PRIVATE_DATA* out, MUSEUM_INSECT_PRIVATE_DATA* from,
                                           MUSEUM_INSECT_PRIVATE_DATA* to, int count, f32 alpha, BOOL firefly_fields,
                                           BOOL allow_motion) {
    int i;

    for (i = 0; i < count; i++) {
        Museum_Insect_InterpolatePrivate(&out[i], &from[i], &to[i], alpha, allow_motion);
        if (firefly_fields) {
            Museum_Insect_InterpolateFireflyFields(&out[i], &from[i], &to[i], alpha);
        }
    }
}

static void Museum_Insect_RunLogicTick(MUSEUM_INSECT_ACTOR* actor, GAME* game) {
    int i;

    Museum_Insect_CopyLogicState(actor);
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            minsect_mv[i](&actor->privInsects[i], game);
        }
    }
}

static void Museum_Insect_RunFixedTicks(MUSEUM_INSECT_ACTOR* actor, GAME* game, int ticks) {
    double saved_dt;
    int tick;

    if (ticks <= 0) {
        return;
    }

    /* Fixed-step museum logic calls dt-aware helpers, so each tick must look like one frame. */
    saved_dt = game->graph->dt_num_60fps_frames;
    game->graph->dt_num_60fps_frames = 1.0f;
    for (tick = 0; tick < ticks; tick++) {
        Museum_Insect_RunLogicTick(actor, game);
    }
    game->graph->dt_num_60fps_frames = saved_dt;
}

void Museum_Insect_Actor_ct(ACTOR* actorx, GAME* game) {
    int i;
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    MI_Control_Actor = actor;
    actor->logic_accum = 0.0f;
    for (i = 0; i < 5; i++) {
        actor->_2F9C[i] = 0;
    }
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (mMmd_InsectInfo(i)) {
            actor->privInsects[i]._8C |= 1;
            actor->privInsects[i]._00 = i;
            actor->privInsects[i]._14 = minsect_scale_tbl[i];
            set_relax_active_time(&actor->privInsects[i], game);
            minsect_ct[i](&actor->privInsects[i], game);
        }
    }
    Museum_Insect_CopyLogicState(actor);
}

void Museum_Insect_Actor_dt(ACTOR* actor, GAME* game) {
    return;
}

void Museum_Insect_Actor_move(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    int ticks;

    actorx->world.position.y = 4000.f;
    Museum_Insect_Talk_process(actorx, game);

    ticks = graph_dt_60hz_ticks(game, &actor->logic_accum);
    Museum_Insect_RunFixedTicks(actor, game, ticks);

    if (ticks == 0) {
        Museum_Insect_RefreshPosSounds(actor, game);
    }
}

extern EVW_ANIME_DATA obj_museum4_water_evw_anime;
extern Gfx obj_museum4_water_modelT[];

void Museum_Insect_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_INSECT_ACTOR* actor = (MUSEUM_INSECT_ACTOR*)actorx;
    MUSEUM_INSECT_PRIVATE_DATA draw_actor;
    MUSEUM_INSECT_PRIVATE_DATA draw_1894[6];
    MUSEUM_INSECT_PRIVATE_DATA draw_1CA0[15];
    f32 alpha = actor->logic_accum;
    int i;

    if (alpha < 0.0f) {
        alpha = 0.0f;
    } else if (alpha > 1.0f) {
        alpha = 1.0f;
    }

    _texture_z_light_fog_prim_xlu(game->graph);
    Evw_Anime_Set((GAME_PLAY*)game, &obj_museum4_water_evw_anime);

    OPEN_DISP(game->graph);
    
    Matrix_translate(100.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_water_modelT);
    
    CLOSE_DISP(game->graph);

    Museum_Insect_InterpolateArray(draw_1894, actor->prev_1894, actor->_1894, 6, alpha, TRUE, TRUE);
    Museum_Insect_InterpolateArray(draw_1CA0, actor->prev_1CA0, actor->_1CA0, 15, alpha, FALSE, FALSE);
    MI_Draw_1894 = draw_1894;
    MI_Draw_1CA0 = draw_1CA0;
    
    for (i = 0; i < aINS_INSECT_TYPE_NUM; i++) {
        if (actor->privInsects[i]._8C & 1) {
            Museum_Insect_InterpolatePrivate(&draw_actor, &actor->prevPrivInsects[i], &actor->privInsects[i], alpha,
                                             TRUE);
            if (GETREG(TAKREG, 0) == i + 1) {
                draw_actor._14 = (GETREG(TAKREG, 1) * 0.0001f) + minsect_scale_tbl[i];
            }
            minsect_dw[i](&draw_actor, game);
        }
    }

    MI_Draw_1894 = NULL;
    MI_Draw_1CA0 = NULL;
}
