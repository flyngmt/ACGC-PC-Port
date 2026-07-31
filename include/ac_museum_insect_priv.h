#ifndef AC_MUSEUM_INSECT_PRIV_H
#define AC_MUSEUM_INSECT_PRIV_H

#include "ac_museum_insect.h"
#include "m_msg.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_debug_mode.h"
#include "m_rcp.h"
#include "ac_insect_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]
#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))
#define CALC_EASE2(x) CALC_EASE(CALC_EASE(x))

struct _MUSEUM_INSECT_PRIVATE_DATA;

typedef void (*PRIV_INSECT_PROCESS)(struct _MUSEUM_INSECT_PRIVATE_DATA*, GAME*);

typedef struct _MUSEUM_INSECT_SKELETON {
    cKF_SkeletonInfo_R_c _00;
    N64Mtx _70;
    artificial_padding(0x70, 0x170, N64Mtx);
    N64Mtx _170;
    artificial_padding(0x170, 0x270, N64Mtx);
    s_xyz _270;
    artificial_padding(0x270, 0x288, s_xyz);
    s_xyz _288;
    artificial_padding(0x288, 0x2A8, s_xyz);
    cKF_Skeleton_R_c* _2A8;
    cKF_Animation_R_c* _2AC;
} MUSEUM_INSECT_SKELETON;

typedef struct _MUSEUM_INSECT_PRIVATE_DATA {
    int _00;
    PRIV_INSECT_PROCESS _04;
    MUSEUM_INSECT_SKELETON* _08;
    f32 _0C;
    f32 _10;
    f32 _14; // scale
    f32 _18;
    xyz_t _1C;
    xyz_t _28;
    xyz_t _34;
    f32 _40;
    xyz_t _44;
    int _50;
    int _54;
    f32 _58;
    union {
        f32 _5C;
        struct {
            s16 _5C_s16;
            s16 _5E_s16;
        };
    };
    f32 _60;
    artificial_padding(0x60, 0x68, f32);
    s_xyz _68;
    s16 _6E;
    s16 _70;
    s16 _72;
    s16 _74;
    s16 _76;
    s16 _78;
    s16 _7A;
    s16 _7C;
    s16 _7E;
    s16 _80;
    s16 _82;
    artificial_padding(0x82, 0x8C, s16);
    s16 _8C;
    s16 _8E;
    int _90;
} MUSEUM_INSECT_PRIVATE_DATA;

typedef struct _INSECT_DISPLAY_MSG_INFO {
    s16 insectName;
    s16 insectInfo;
} INSECT_DISPLAY_MSG_INFO;

typedef struct _MUSEUM_INSECT_ACTOR {
    ACTOR actor;                                                  // offset: 0x0
    MUSEUM_INSECT_PRIVATE_DATA privInsects[aINS_INSECT_TYPE_NUM]; // offset: 0x174
    MUSEUM_INSECT_PRIVATE_DATA _1894[6];                          // offset: 0x1894
    MUSEUM_INSECT_PRIVATE_DATA _1CA0[15];                         // offset: 0x1CA0
    MUSEUM_INSECT_PRIVATE_DATA prevPrivInsects[aINS_INSECT_TYPE_NUM];
    MUSEUM_INSECT_PRIVATE_DATA prev_1894[6];
    MUSEUM_INSECT_PRIVATE_DATA prev_1CA0[15];
    MUSEUM_INSECT_SKELETON _24B8[4];                              // offset: 0x24B8
    int _2F78;                                                    // offset: 0x2F78
    int _2F7C;                                                    // offset: 0x2F7C
    INSECT_DISPLAY_MSG_INFO _2F80[7];                             // offset: 0x2F82
    s16 _2F9C[5];                                                 // offset: 0x2F9C
    f32 logic_accum;
} MUSEUM_INSECT_ACTOR;

// bss
extern MUSEUM_INSECT_ACTOR* MI_Control_Actor;

// data
extern rgba_t window_color;
extern Gfx *m_monshiro_disp_tbl[], *m_monki_disp_tbl[], *m_ageha_disp_tbl[], *m_ohmurasaki_disp_tbl[],
    *m_minmin_disp_tbl[], *m_tukutuku_disp_tbl[], *m_higurashi_disp_tbl[], *m_abura_disp_tbl[], *m_shiokara_disp_tbl[],
    *m_akiakane_disp_tbl[], *m_ginyanma_disp_tbl[], *m_oniyanma_disp_tbl[], *m_syouryou_disp_tbl[],
    *m_tonosama_disp_tbl[], *m_koorogi_disp_tbl[], *m_kirigirisu_disp_tbl[], *m_suzumushi_disp_tbl[],
    *m_matumushi_disp_tbl[], *m_tentou_disp_tbl[], *m_nanahoshi_disp_tbl[], *m_kamakiri_disp_tbl[],
    *m_maimai_disp_tbl[], *m_hachi_disp_tbl[], *m_kanabun_disp_tbl[], *m_kabuto_disp_tbl[], *m_hirata_disp_tbl[],
    *m_tamamushi_disp_tbl[], *m_gomadara_disp_tbl[], *m_nokogiri_disp_tbl[], *m_miyama_disp_tbl[], *m_okuwa_disp_tbl[],
    *m_amenbo_disp_tbl[], *m_mino_disp_tbl[], *m_kumo_disp_tbl[], *m_goki_disp_tbl[], *m_genji_disp_tbl[],
    *m_dango_disp_tbl[], *m_ari_disp_tbl[], *m_okera_disp_tbl[], *m_ka_disp_tbl[];
extern Gfx** minsect_mdl[aINS_INSECT_TYPE_NUM];
extern PRIV_INSECT_PROCESS minsect_ct[aINS_INSECT_TYPE_NUM];
extern PRIV_INSECT_PROCESS minsect_mv[aINS_INSECT_TYPE_NUM];
extern PRIV_INSECT_PROCESS minsect_dw[aINS_INSECT_TYPE_NUM];
extern f32 minsect_shadow_scale_tbl[aINS_INSECT_TYPE_NUM];
extern int active_time_tbl[aINS_INSECT_TYPE_NUM];
extern int relax_time_tbl[aINS_INSECT_TYPE_NUM];
extern xyz_t flower_pos[8];
extern xyz_t tree_pos[8];
extern xyz_t rock_pos[2];
extern xyz_t tonbo_rock_pos[6];
extern xyz_t tentou_flower_pos[4];
extern xyz_t hachi_base_pos;
extern xyz_t kabuto_base_pos[9];
extern cKF_Skeleton_R_c* kuwagata_model_tbl[4];
extern cKF_Animation_R_c* kuwagata_anim_tbl[4];
extern xyz_t kuwagata_base_pos[4];
extern xyz_t amenbo_center_pos;
extern xyz_t rail_pos[6];
extern xyz_t ari_rail_pos[3];
extern f32 minsect_scale_tbl[aINS_INSECT_TYPE_NUM];

// rodata
extern const f32 base_high_tbl[4];
extern const s16 aim_angle_tbl[6];
extern const xyz_t mino_base_pos;
extern const xyz_t mino_top_pos;
extern const xyz_t mino_bottom_pos;
extern const xyz_t kumo_base_pos;
extern const xyz_t kumo_top_pos;
extern const xyz_t kumo_bottom_pos;
extern const xyz_t base_genji_pos;
extern const xyz_t genji_mizu_pos;
extern const xyz_t okera_base_pos;

// ac_museum_insect.c
int Museum_Insect_GetMsgNo(ACTOR* actorx);
int Museum_Insect_Check_Talk_Distance(GAME* game, int i);
void Museum_Insect_Set_MsgInsectInfo(ACTOR* actor, int i);
void Museum_Insect_set_talk_info(ACTOR* actor);
void Museum_Insect_Talk_process(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_dt(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_move(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_draw(ACTOR* actor, GAME* game);

// ac_museum_insect_base.c_inc
void mID_insect_moveF(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_amenbo_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_amenbo_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_amenbo_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void ari_alone_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void ari_alone_make(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void ari_alone_dt(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void ari_alone_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void ari_alone_draw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_ari_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_ari_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_ari_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_draw_shadow(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_fly_BGCheck(MUSEUM_INSECT_PRIVATE_DATA* actor, f32 f1, f32 f2);
void minsect_garden_BGCheck(MUSEUM_INSECT_PRIVATE_DATA* actor, f32 f1, f32 f2);
void minsect_flower_BGCheck(MUSEUM_INSECT_PRIVATE_DATA* actor, xyz_t* p);
void minsect_goki_BGCheck(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_kanban_BGCheck(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_tree_ObjCheck(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_rock_ObjCheck(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_batta_ObjCheck(MUSEUM_INSECT_PRIVATE_DATA* actor);
BOOL get_now_mind_flag(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void set_relax_active_time(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_chou.c_inc
void minsect_chou_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_normal_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_normal_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_aim_flower_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_aim_flower_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_flower_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_flower_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_fly_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_fly_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_chou_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_semi.c_inc
void minsect_semi_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_semi_hane_anime(MUSEUM_INSECT_PRIVATE_DATA* actor);
void mi_semi_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_semi_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_semi_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_tonbo.c_inc
void minsect_tonbo_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tonbo_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
BOOL minsect_tonbo_bg_check(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_near_target_set(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_rock_target_set(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game, xyz_t* p);
BOOL minsect_tonbo_suprised_rest_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
f32 minsect_tonbo_acc_change(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_tonbo_max_speed_set(MUSEUM_INSECT_PRIVATE_DATA* actor);
f32 minsect_tonbo_aim_distance_set(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_tonbo_aim_angle_check(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_tonbo_normal_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_normal_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_aim_rock_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_aim_rock_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_rock_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_rock_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_rock_wait_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_rock_wait_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_fly_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_fly_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tonbo_MoveF(MUSEUM_INSECT_PRIVATE_DATA* actor);

// ac_museum_insect_batta.c_inc
void mi_batta_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_batta_suzumushi_hane_anime(MUSEUM_INSECT_PRIVATE_DATA* actor);
void mi_batta_hane_anime(MUSEUM_INSECT_PRIVATE_DATA* actor);
void minsect_batta_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_normal_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_normal_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_silent_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_silent_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_jump_wait_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_jump_wait_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_jump_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_jump_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_batta_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_tentou.c_inc
void mi_tentou_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_kama_anime(MUSEUM_INSECT_PRIVATE_DATA* actor);
void mi_tentou_wait_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_wait(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_menace_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_menace(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_tentou_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_tentou_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tentou_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_tentou_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_hachi.c_inc
void mi_hachi_hane_anime(MUSEUM_INSECT_PRIVATE_DATA* actor);
void mi_hachi_mitu_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_mitu(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_wait_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_wait(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_hachi_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_hachi_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_hachi_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_hachi_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_kabuto.c_inc
void minsect_kabuto_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kabuto_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kabuto_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_kuwagata.c_inc
void mi_kuwagata_rensa_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_rensa(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_wait_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_wait(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_battle_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_battle(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_menace_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_menace(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_attack_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_attack(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_kuwagata_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_kuwagata_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kuwagata_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kuwagata_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_mino.c_inc
void minsect_mino_up_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_up(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_down_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_down(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_check_dush_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_furiko(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_wait_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_wait(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_hineri(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_mino_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_mino_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_kumo.c_inc
void minsect_kumo_hide_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_hide(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_up_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_up(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_down_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_down(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_furiko(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_wait_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_wait(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_hineri(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_kumo_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_kumo_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_goki.c_inc
void minsect_goki_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
BOOL goki_player_check(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void goki_wall_hit_angle_corect_sub(MUSEUM_INSECT_PRIVATE_DATA* actor, int angle);
void goki_wall_hit_angle_corect(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void goki_set_talk_info_init(ACTOR* actor);
void goki_talk_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void goki_talk_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_goki_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_goki_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_genji.c_inc
void mi_genji_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void genji_light_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game, s16 r5);
void genji_light_make(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game, s16 i);
void genji_light_anime(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void genji_light_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void genji_light_draw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_genji_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_genji_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_genji_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_dango.c_inc
void mi_dango_defence_anime(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_move_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_move(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_defence_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_defence(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void mi_dango_setupAction(MUSEUM_INSECT_PRIVATE_DATA* actor, int r4, GAME* game);
void minsect_dango_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_dango_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_dango_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_okera.c_inc
void mi_okera_check_player(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_okera_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_up_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_up_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_normal_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_normal_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_down_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_down_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_wait_process_init(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void okera_dig_wait_process(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_okera_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_okera_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_ka.c_inc
void minsect_ka_ct(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_ka_mv(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);
void minsect_ka_dw(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

#ifdef __cplusplus
}
#endif

#endif
