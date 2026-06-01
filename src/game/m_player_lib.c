#include "m_player_lib.h"

#include "m_play.h"
#include "m_actor.h"
#include "m_common_data.h"
#include "jsyswrap.h"
#include "libultra/libultra.h"
#include "ac_t_umbrella.h"
#include "ac_snowman.h"
#include "ac_uki.h"
#ifdef TARGET_PC
#include "pc_bswap.h"
#endif

extern cKF_Animation_R_c cKF_ba_r_ply_1_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_walk1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_run1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_push1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_pull1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hold_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_pickup1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_Lturn1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_Rturn1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_change1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_putaway1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_open1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_putaway1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_trans_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_transfer1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_umb_open1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_umbrella1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_dash1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_run_slip1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_pull1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_m1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kamae_move_m1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kamae_wait_m1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru_a1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru_getup_a1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru_getup_n1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru_n1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_net1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_net_swing1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe_swing1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kamae_slip_m1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kokeru_getup1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_sitdown1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_sitdown_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_standup1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_putaway_m1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_bed_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_inbed_L1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_inbed_R1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_intrain1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_open_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_open_h1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_open_k1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_negaeri_L1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_negaeri_R1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_outbed_L1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_outbed_R1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_outtrain1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_close_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_close_h1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_close_k1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_wait_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_wait_h1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kagu_wait_k1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_go_out_o1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_go_out_s1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_into_s1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe_hane1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe_suka1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hold_wait_h1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hold_wait_o1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_t1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_t2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_putaway_t1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_sao1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_sao_swing1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_turi_hiki1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_turi_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_not_get_t1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_menu_catch1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_menu_change1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_umb_close1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_not_sao_swing1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_intrain_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_clear_table1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_dig1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_fill_up1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_not_dig1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_clear_table_l1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_pickup_l1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_scoop1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_confirm1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_dig_suka1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_putaway_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_dig_kabu1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_fill_up_i1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_send_mail1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_f1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_pull_f1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_get_putaway_f1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_trans_wait_f1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_transfer_f1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_shake1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_tired1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_wash1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_wash2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_wash3;
extern cKF_Animation_R_c cKF_ba_r_ply_1_wash4;
extern cKF_Animation_R_c cKF_ba_r_ply_1_wash5;
extern cKF_Animation_R_c cKF_ba_r_ply_1_fukubiki1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_omairi1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_saisen1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_return_mail1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_return_mail2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_return_mail3;
extern cKF_Animation_R_c cKF_ba_r_ply_1_eat1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_gaaan1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_gaaan2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_deru1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_guratuku1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_mogaku1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_otiru1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_zassou1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_knock1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_biku1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hati1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hati2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_hati3;
extern cKF_Animation_R_c cKF_ba_r_ply_1_push_yuki1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_deru2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_otiru2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_itazura1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_umb_rot1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_pickup_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_yatta1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_yatta2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_yatta3;
extern cKF_Animation_R_c cKF_ba_r_ply_1_kaza1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_mosquito1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_mosquito2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_ride1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_ride2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_ridewait;
extern cKF_Animation_R_c cKF_ba_r_ply_1_getoff1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_getoff2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_utiwa_wait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_utiwa_d1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe_break1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_axe_breakwait1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_light_on1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou2_1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou2_2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou3;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou4_1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou4_2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou5_1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou5_2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou6_1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou6_2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou7_1;
extern cKF_Animation_R_c cKF_ba_r_ply_1_taisou7_2;
extern cKF_Animation_R_c cKF_ba_r_ply_1_omairi_us1;

extern cKF_Animation_R_c* mPlib_Get_Pointer_Animation(int anim_idx) {
    static cKF_Animation_R_c* data[] = {
        &cKF_ba_r_ply_1_wait1,
        &cKF_ba_r_ply_1_walk1,
        &cKF_ba_r_ply_1_axe1,
        &cKF_ba_r_ply_1_run1,
        &cKF_ba_r_ply_1_push1,
        &cKF_ba_r_ply_1_pull1,
        &cKF_ba_r_ply_1_hold_wait1,
        &cKF_ba_r_ply_1_pickup1,
        &cKF_ba_r_ply_1_Lturn1,
        &cKF_ba_r_ply_1_Rturn1,
        &cKF_ba_r_ply_1_get1,
        &cKF_ba_r_ply_1_get_change1,
        &cKF_ba_r_ply_1_get_putaway1,
        &cKF_ba_r_ply_1_open1,
        &cKF_ba_r_ply_1_putaway1,
        &cKF_ba_r_ply_1_trans_wait1,
        &cKF_ba_r_ply_1_transfer1,
        &cKF_ba_r_ply_1_umb_open1,
        &cKF_ba_r_ply_1_umbrella1,
        &cKF_ba_r_ply_1_dash1,
        &cKF_ba_r_ply_1_run_slip1,
        &cKF_ba_r_ply_1_get_pull1,
        &cKF_ba_r_ply_1_get_m1,
        &cKF_ba_r_ply_1_kamae_move_m1,
        &cKF_ba_r_ply_1_kamae_wait_m1,
        &cKF_ba_r_ply_1_kokeru_a1,
        &cKF_ba_r_ply_1_kokeru_getup_a1,
        &cKF_ba_r_ply_1_kokeru_getup_n1,
        &cKF_ba_r_ply_1_kokeru_n1,
        &cKF_ba_r_ply_1_net1,
        &cKF_ba_r_ply_1_net_swing1,
        &cKF_ba_r_ply_1_axe_swing1,
        &cKF_ba_r_ply_1_kamae_slip_m1,
        &cKF_ba_r_ply_1_kokeru1,
        &cKF_ba_r_ply_1_kokeru_getup1,
        &cKF_ba_r_ply_1_sitdown1,
        &cKF_ba_r_ply_1_sitdown_wait1,
        &cKF_ba_r_ply_1_standup1,
        &cKF_ba_r_ply_1_putaway_m1,
        &cKF_ba_r_ply_1_bed_wait1,
        &cKF_ba_r_ply_1_inbed_L1,
        &cKF_ba_r_ply_1_inbed_R1,
        &cKF_ba_r_ply_1_intrain1,
        &cKF_ba_r_ply_1_kagu_open_d1,
        &cKF_ba_r_ply_1_kagu_open_h1,
        &cKF_ba_r_ply_1_kagu_open_k1,
        &cKF_ba_r_ply_1_negaeri_L1,
        &cKF_ba_r_ply_1_negaeri_R1,
        &cKF_ba_r_ply_1_outbed_L1,
        &cKF_ba_r_ply_1_outbed_R1,
        &cKF_ba_r_ply_1_outtrain1,
        &cKF_ba_r_ply_1_kagu_close_d1,
        &cKF_ba_r_ply_1_kagu_close_h1,
        &cKF_ba_r_ply_1_kagu_close_k1,
        &cKF_ba_r_ply_1_kagu_wait_d1,
        &cKF_ba_r_ply_1_kagu_wait_h1,
        &cKF_ba_r_ply_1_kagu_wait_k1,
        &cKF_ba_r_ply_1_go_out_o1,
        &cKF_ba_r_ply_1_go_out_s1,
        &cKF_ba_r_ply_1_into_s1,
        &cKF_ba_r_ply_1_axe_hane1,
        &cKF_ba_r_ply_1_axe_suka1,
        &cKF_ba_r_ply_1_hold_wait_h1,
        &cKF_ba_r_ply_1_hold_wait_o1,
        &cKF_ba_r_ply_1_get_t1,
        &cKF_ba_r_ply_1_get_t2,
        &cKF_ba_r_ply_1_putaway_t1,
        &cKF_ba_r_ply_1_sao1,
        &cKF_ba_r_ply_1_sao_swing1,
        &cKF_ba_r_ply_1_turi_hiki1,
        &cKF_ba_r_ply_1_turi_wait1,
        &cKF_ba_r_ply_1_not_get_t1,
        &cKF_ba_r_ply_1_menu_catch1,
        &cKF_ba_r_ply_1_menu_change1,
        &cKF_ba_r_ply_1_umb_close1,
        &cKF_ba_r_ply_1_not_sao_swing1,
        &cKF_ba_r_ply_1_intrain_wait1,
        &cKF_ba_r_ply_1_clear_table1,
        &cKF_ba_r_ply_1_dig1,
        &cKF_ba_r_ply_1_fill_up1,
        &cKF_ba_r_ply_1_not_dig1,
        &cKF_ba_r_ply_1_clear_table_l1,
        &cKF_ba_r_ply_1_pickup_l1,
        &cKF_ba_r_ply_1_scoop1,
        &cKF_ba_r_ply_1_confirm1,
        &cKF_ba_r_ply_1_dig_suka1,
        &cKF_ba_r_ply_1_get_d1,
        &cKF_ba_r_ply_1_putaway_d1,
        &cKF_ba_r_ply_1_dig_kabu1,
        &cKF_ba_r_ply_1_fill_up_i1,
        &cKF_ba_r_ply_1_send_mail1,
        &cKF_ba_r_ply_1_get_f1,
        &cKF_ba_r_ply_1_get_pull_f1,
        &cKF_ba_r_ply_1_get_putaway_f1,
        &cKF_ba_r_ply_1_trans_wait_f1,
        &cKF_ba_r_ply_1_transfer_f1,
        &cKF_ba_r_ply_1_shake1,
        &cKF_ba_r_ply_1_tired1,
        &cKF_ba_r_ply_1_wash1,
        &cKF_ba_r_ply_1_wash2,
        &cKF_ba_r_ply_1_wash3,
        &cKF_ba_r_ply_1_wash4,
        &cKF_ba_r_ply_1_wash5,
        &cKF_ba_r_ply_1_fukubiki1,
        &cKF_ba_r_ply_1_omairi1,
        &cKF_ba_r_ply_1_saisen1,
        &cKF_ba_r_ply_1_return_mail1,
        &cKF_ba_r_ply_1_return_mail2,
        &cKF_ba_r_ply_1_return_mail3,
        &cKF_ba_r_ply_1_eat1,
        &cKF_ba_r_ply_1_gaaan1,
        &cKF_ba_r_ply_1_gaaan2,
        &cKF_ba_r_ply_1_deru1,
        &cKF_ba_r_ply_1_guratuku1,
        &cKF_ba_r_ply_1_mogaku1,
        &cKF_ba_r_ply_1_otiru1,
        &cKF_ba_r_ply_1_zassou1,
        &cKF_ba_r_ply_1_knock1,
        &cKF_ba_r_ply_1_biku1,
        &cKF_ba_r_ply_1_hati1,
        &cKF_ba_r_ply_1_hati2,
        &cKF_ba_r_ply_1_hati3,
        &cKF_ba_r_ply_1_push_yuki1,
        &cKF_ba_r_ply_1_deru2,
        &cKF_ba_r_ply_1_otiru2,
        &cKF_ba_r_ply_1_itazura1,
        &cKF_ba_r_ply_1_umb_rot1,
        &cKF_ba_r_ply_1_pickup_wait1,
        &cKF_ba_r_ply_1_yatta1,
        &cKF_ba_r_ply_1_yatta2,
        &cKF_ba_r_ply_1_yatta3,
        &cKF_ba_r_ply_1_kaza1,
        &cKF_ba_r_ply_1_mosquito1,
        &cKF_ba_r_ply_1_mosquito2,
        &cKF_ba_r_ply_1_ride1,
        &cKF_ba_r_ply_1_ride2,
        &cKF_ba_r_ply_1_ridewait,
        &cKF_ba_r_ply_1_getoff1,
        &cKF_ba_r_ply_1_getoff2,
        &cKF_ba_r_ply_1_utiwa_wait1,
        &cKF_ba_r_ply_1_utiwa_d1,
        &cKF_ba_r_ply_1_axe_break1,
        &cKF_ba_r_ply_1_axe_breakwait1,
        &cKF_ba_r_ply_1_light_on1,
        &cKF_ba_r_ply_1_taisou1,
        &cKF_ba_r_ply_1_taisou2_1,
        &cKF_ba_r_ply_1_taisou2_2,
        &cKF_ba_r_ply_1_taisou3,
        &cKF_ba_r_ply_1_taisou4_1,
        &cKF_ba_r_ply_1_taisou4_2,
        &cKF_ba_r_ply_1_taisou5_1,
        &cKF_ba_r_ply_1_taisou5_2,
        &cKF_ba_r_ply_1_taisou6_1,
        &cKF_ba_r_ply_1_taisou6_2,
        &cKF_ba_r_ply_1_taisou7_1,
        &cKF_ba_r_ply_1_taisou7_2,
        &cKF_ba_r_ply_1_omairi_us1,
    };

    if (anim_idx >= 0 && anim_idx < mPlayer_ANIM_NUM && data[anim_idx] != NULL) {
        return data[anim_idx];
    }

    return NULL;
}

extern int mPlib_Get_BasicPlayerAnimeIndex_fromItemKind(int item_kind) {
    if (item_kind >= 0 && item_kind < (mPlayer_ITEM_KIND_NUM + 1)) {
        // clang-format off
        static const u8 data[] = {
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_AXE1,
            mPlayer_ANIM_NET1,
            mPlayer_ANIM_NET1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_UMBRELLA1,
            mPlayer_ANIM_SAO1,
            mPlayer_ANIM_SAO1,
            mPlayer_ANIM_SCOOP1,
            mPlayer_ANIM_SCOOP1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_KAZA1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_UTIWA_WAIT1,
            mPlayer_ANIM_WAIT1,
        };
        // clang-format on

        return data[item_kind];
    }

    return -1;
}

extern int mPlib_Get_BasicPartTableIndex_fromAnimeIndex(int anim_idx) {
    if (anim_idx >= 0 && anim_idx < mPlayer_ANIM_NUM) {
        // clang-format off
        static const s8 data[] = {
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_AXE,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NET,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NET,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_AXE,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_AXE,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NET,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_PICK_UP,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NET,
            mPlayer_PART_TABLE_NET,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
            mPlayer_PART_TABLE_NORMAL,
        };
        // clang-format on

        return data[anim_idx];
    }

    return -1;
}

extern Gfx tol_axe_1_model[];
extern Gfx tol_axe_1_b_model[];
extern Gfx tol_axe_1_c_model[];
extern Gfx tol_axe_2_model[];
extern cKF_Skeleton_R_c cKF_bs_r_tol_net_1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_net_2;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_get_m1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_net_swing1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_kamae_main_m1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_kokeru_getup_n1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_kokeru_n1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_swing_wait1;
extern cKF_Animation_R_c cKF_ba_r_tol_net_1_yatta_m1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_sao_1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_sao_2;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_get_t1;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_move1;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_sinari1;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_swing1;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_sao_wait1;
extern cKF_Animation_R_c cKF_ba_r_tol_sao_1_not_sao_swing1;
extern Gfx tol_scoop_1_model[];
extern Gfx tol_scoop_2_model[];
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon2;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon3;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon4;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon5;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon6;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon7;
extern cKF_Skeleton_R_c cKF_bs_r_tol_balloon8;
extern cKF_Animation_R_c cKF_ba_r_tol_balloon1_wait;
extern cKF_Animation_R_c cKF_ba_r_tol_balloon1_gyaza1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza1;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza2;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza3;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza4;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza5;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza6;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza7;
extern cKF_Skeleton_R_c cKF_bs_r_tol_kaza8;
extern cKF_Animation_R_c cKF_ba_r_tol_kaza1_wait;
extern Gfx tol_fan1_model[];
extern Gfx tol_fan2_model[];
extern Gfx tol_fan3_model[];
extern Gfx tol_fan4_model[];
extern Gfx tol_fan5_model[];
extern Gfx tol_fan6_model[];
extern Gfx tol_fan7_model[];
extern Gfx tol_fan8_model[];

extern void* mPlib_Get_Item_DataPointer(int data_kind) {
    if (mPlayer_ITEM_DATA_VALID(data_kind)) {
        static void* mPlib_Item_DataPointer[] = {
            tol_axe_1_model,
            tol_axe_1_b_model,
            tol_axe_1_c_model,
            tol_axe_2_model,
            &cKF_bs_r_tol_net_1,
            &cKF_bs_r_tol_net_2,
            &cKF_ba_r_tol_net_1_get_m1,
            &cKF_ba_r_tol_net_1_net_swing1,
            &cKF_ba_r_tol_net_1_kamae_main_m1,
            &cKF_ba_r_tol_net_1_kokeru_getup_n1,
            &cKF_ba_r_tol_net_1_kokeru_n1,
            &cKF_ba_r_tol_net_1_swing_wait1,
            &cKF_ba_r_tol_net_1_yatta_m1,
            &cKF_bs_r_tol_sao_1,
            &cKF_bs_r_tol_sao_2,
            &cKF_ba_r_tol_sao_1_sao_get_t1,
            &cKF_ba_r_tol_sao_1_sao_move1,
            &cKF_ba_r_tol_sao_1_sao_sinari1,
            &cKF_ba_r_tol_sao_1_sao_swing1,
            &cKF_ba_r_tol_sao_1_sao_wait1,
            &cKF_ba_r_tol_sao_1_not_sao_swing1,
            tol_scoop_1_model,
            tol_scoop_2_model,
            &cKF_bs_r_tol_balloon1,
            &cKF_bs_r_tol_balloon2,
            &cKF_bs_r_tol_balloon3,
            &cKF_bs_r_tol_balloon4,
            &cKF_bs_r_tol_balloon5,
            &cKF_bs_r_tol_balloon6,
            &cKF_bs_r_tol_balloon7,
            &cKF_bs_r_tol_balloon8,
            &cKF_ba_r_tol_balloon1_wait,
            &cKF_ba_r_tol_balloon1_gyaza1,
            &cKF_bs_r_tol_kaza1,
            &cKF_bs_r_tol_kaza2,
            &cKF_bs_r_tol_kaza3,
            &cKF_bs_r_tol_kaza4,
            &cKF_bs_r_tol_kaza5,
            &cKF_bs_r_tol_kaza6,
            &cKF_bs_r_tol_kaza7,
            &cKF_bs_r_tol_kaza8,
            &cKF_ba_r_tol_kaza1_wait,
            tol_fan1_model,
            tol_fan2_model,
            tol_fan3_model,
            tol_fan4_model,
            tol_fan5_model,
            tol_fan6_model,
            tol_fan7_model,
            tol_fan8_model,
        };

        return mPlib_Item_DataPointer[data_kind];
    }

    return NULL;
}

extern int mPlib_Get_BasicItemShapeIndex_fromItemKind(int item_kind) {
    if (item_kind >= 0 && item_kind < (mPlayer_ITEM_KIND_NUM + 1)) {
        // clang-format off
        static const s8 data[] = {
            mPlayer_ITEM_DATA_AXE,
            mPlayer_ITEM_DATA_AXE,
            mPlayer_ITEM_DATA_AXE_B,
            mPlayer_ITEM_DATA_AXE_B,
            mPlayer_ITEM_DATA_AXE_B,
            mPlayer_ITEM_DATA_AXE_C,
            mPlayer_ITEM_DATA_AXE_C,
            mPlayer_ITEM_DATA_AXE_C,
            mPlayer_ITEM_DATA_GOLD_AXE,
            mPlayer_ITEM_DATA_NET,
            mPlayer_ITEM_DATA_GOLD_NET,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            mPlayer_ITEM_DATA_ROD,
            mPlayer_ITEM_DATA_GOLD_ROD,
            mPlayer_ITEM_DATA_SHOVEL,
            mPlayer_ITEM_DATA_GOLD_SHOVEL,
            mPlayer_ITEM_DATA_BALLOON1,
            mPlayer_ITEM_DATA_BALLOON2,
            mPlayer_ITEM_DATA_BALLOON3,
            mPlayer_ITEM_DATA_BALLOON4,
            mPlayer_ITEM_DATA_BALLOON5,
            mPlayer_ITEM_DATA_BALLOON6,
            mPlayer_ITEM_DATA_BALLOON7,
            mPlayer_ITEM_DATA_BALLOON8,
            mPlayer_ITEM_DATA_PINWHEEL1,
            mPlayer_ITEM_DATA_PINWHEEL2,
            mPlayer_ITEM_DATA_PINWHEEL3,
            mPlayer_ITEM_DATA_PINWHEEL4,
            mPlayer_ITEM_DATA_PINWHEEL5,
            mPlayer_ITEM_DATA_PINWHEEL6,
            mPlayer_ITEM_DATA_PINWHEEL7,
            mPlayer_ITEM_DATA_PINWHEEL8,
            mPlayer_ITEM_DATA_FAN1,
            mPlayer_ITEM_DATA_FAN2,
            mPlayer_ITEM_DATA_FAN3,
            mPlayer_ITEM_DATA_FAN4,
            mPlayer_ITEM_DATA_FAN5,
            mPlayer_ITEM_DATA_FAN6,
            mPlayer_ITEM_DATA_FAN7,
            mPlayer_ITEM_DATA_FAN8,
            0x00,
        };
        // clang-format on

        return data[item_kind];
    }

    return -1;
}

extern int mPlib_Get_BasicItemAnimeIndex_fromItemKind(int item_kind) {
    if (item_kind >= 0 && item_kind < (mPlayer_ITEM_KIND_NUM + 1)) {
        // clang-format off
        static const s8 data[] = {
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            mPlayer_ITEM_DATA_KAMAE_MAIN_M,
            mPlayer_ITEM_DATA_KAMAE_MAIN_M,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            -1,
            mPlayer_ITEM_DATA_ROD_WAIT,
            mPlayer_ITEM_DATA_ROD_WAIT,
            -1,
            -1,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_BALLOON_GYAZA,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            mPlayer_ITEM_DATA_PINWHEEL_WAIT,
            -1,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00,
            0x00
        };
        // clang-format on

        return data[item_kind];
    }

    return -1;
}

extern u8 mPlib_Get_Item_DataPointerType(int data_idx) {
    if (data_idx >= 0 && data_idx < mPlayer_ITEM_DATA_NUM) {
        // clang-format off
        static const u8 mPlib_Item_DataPointerType[] = {
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_NET_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_ROD_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_BALLOON_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_BALLOON_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_SKELETON,
            mPlayer_ITEM_DATA_TYPE_PINWHEEL_ANIMATION,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
            mPlayer_ITEM_DATA_TYPE_GFX,
        };
        // clang-format on

        return mPlib_Item_DataPointerType[data_idx];
    }

    return mPlayer_ITEM_DATA_TYPE_GFX;
}

static u32 mPlib_Get_UseFaceRom_index(int sex, int face_type, int swell, int decoy, int res_type) {
    int swell_flag = swell != FALSE;
    int decoy_flag = decoy != FALSE;
    int ofs;

    if (res_type != mPlayer_USE_FACE_ROM_TYPE_TEX) {
        ofs = face_type * 8;
        ofs += sex * 64;
        ofs += swell_flag * 128;
    } else {
        ofs = decoy_flag * 32;
        ofs += face_type;
        ofs += sex * 8;
        ofs += swell_flag * 16;
    }

    return ofs;
}

static u32 mPlib_Get_UseFaceTexRom_p_common(int sex, int face_type, int swell, int decoy) {
    u32 idx = mPlib_Get_UseFaceRom_index(sex, face_type, swell, decoy, mPlayer_USE_FACE_ROM_TYPE_TEX);
    u32 base_address = JW_GetAramAddress(RESOURCE_FACE_BOY);

    return base_address + idx * 0xE20;
}

static u32 mPlib_Get_UseFaceTexRom_p(void) {
    return mPlib_Get_UseFaceTexRom_p_common(Now_Private->gender, Now_Private->face, Common_Get(player_bee_swell_flag),
                                            Common_Get(player_decoy_flag));
}

static u32 mPlib_Get_UseFacePalletRom_p(void) {
    int sunburn_rank = Now_Private->sunburn.rank;
    int decoy_flag = Common_Get(player_decoy_flag);
    u32 base;
    u32 ofs;

    if (sunburn_rank > 0 && decoy_flag == FALSE) {
        u32 idx = mPlib_Get_UseFaceRom_index(Now_Private->gender, Now_Private->face, Common_Get(player_bee_swell_flag),
                                             FALSE, mPlayer_USE_FACE_ROM_TYPE_PAL);

        base = mPlib_Get_UseFaceTexRom_p_common(mPr_SEX_FEMALE, mPr_FACE_TYPE7, TRUE, TRUE);
        ofs = 0xE00 + (sunburn_rank + idx) * 0x20;
    } else {
        base = mPlib_Get_UseFaceTexRom_p();
        ofs = 0xE00;
    }

    return base + ofs;
}

extern void mPlib_Object_Exchange_keep_new_PlayerMdl(GAME_PLAY* play) {
    Actor_data* player_data = play->player_data;

    actor_dlftbls[player_data->profile].profile->obj_bank_id = mPlib_get_player_Object_Bank();
}

static int mPlib_Object_Exchange_keep_new(GAME_PLAY* play, s16 bank, u32 src, u32 size, int aram_flag) {
    Object_Exchange_c* obj_ex = &play->object_exchange;
    Object_Bank_c* bank_p = &obj_ex->banks[obj_ex->bank_idx];

    bank_p->bank_id = bank;
    bank_p->dma_start = obj_ex->next_bank_ram_address;
    bank_p->ram_start = obj_ex->next_bank_ram_address;
    bank_p->size = size;

    if (src != 0) {
        if (aram_flag) {
            _JW_GetResourceAram(src, (u8*)bank_p->dma_start, size);
        } else {
            bcopy((void*)src, bank_p->dma_start, size);
        }

        DCStoreRangeNoSync(bank_p->ram_start, size);
    }

    if (obj_ex->bank_idx < (mSc_OBJECT_BANK_NUM - 1)) {
        obj_ex->next_bank_ram_address = (char*)ALIGN_NEXT((uintptr_t)obj_ex->next_bank_ram_address + size, 32);
        obj_ex->bank_idx++;
    }

    return mSc_bank_regist_check(obj_ex, bank);
}

static int Player_bank_ID_Index = 0;

static int Change_Player_bank_ID_Index(void) {
    Player_bank_ID_Index ^= 1;
    return Player_bank_ID_Index;
}

static int Player_face_bank_ID_Index = 0;

static int Change_Player_face_bank_ID_Index(void) {
    Player_face_bank_ID_Index ^= 1;
    return Player_face_bank_ID_Index;
}

extern u32 mPlib_Get_PlayerTexRom_p(int idx) {
    if (mPlib_Check_PlayerClothInAram(idx)) {
        u32 addr = JW_GetAramAddress(RESOURCE_TEX_BOY);
        addr += idx * mNW_DESIGN_TEX_SIZE;
        return addr;
    } else {
        int org_idx = idx - (CLOTH_NUM + 1);

        if (!mPr_ORIGINAL_DESIGN_IDX_VALID(org_idx)) {
            org_idx = 0;
        }

        return (uintptr_t)Now_Private->my_org[org_idx & 7].design.data;
    }
}

static u32 mPlib_Get_UseTexRom_p(void) {
    return mPlib_Get_PlayerTexRom_p(Now_Private->cloth.idx);
}

static int Player_Tex_bank_ID[] = { -1, -1 };

extern void mPlib_Object_Exchange_keep_new_PlayerTex(GAME_PLAY* play, int bank_idx, int bank) {
    u32 tex = mPlib_Get_UseTexRom_p();
    int idx = mPlib_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_14, tex, mNW_DESIGN_TEX_SIZE,
                                             mPlib_Check_PlayerClothInAram(Now_Private->cloth.idx));

    Player_Tex_bank_ID[bank_idx] = bank + idx;
}

extern u32 mPlib_Get_PlayerPalletRom_p(int idx) {
    if (mPlib_Check_PlayerClothInAram(idx)) {
        u32 addr = JW_GetAramAddress(RESOURCE_PALLET_BOY);
        addr += idx * mNW_PALETTE_SIZE;
        return addr;
    } else {
        int org_idx = idx - (CLOTH_NUM + 1);

        if (!mPr_ORIGINAL_DESIGN_IDX_VALID(org_idx)) {
            org_idx = 0;
        }

        return (uintptr_t)mNW_PaletteIdx2Palette(Now_Private->my_org[org_idx & 7].palette);
    }
}

static u32 mPlib_Get_UsePalletRom_p(void) {
    return mPlib_Get_PlayerPalletRom_p(Now_Private->cloth.idx);
}

#ifdef TARGET_PC
static void mPlib_ByteSwapPlayerPalette(u16* pal);
#endif

static int Player_Pallet_bank_ID[] = { -1, -1 };

extern void mPlib_Object_Exchange_keep_new_PlayerPallet(GAME_PLAY* play, int bank_idx, int bank) {
    u32 pal = mPlib_Get_UsePalletRom_p();
    int in_aram = mPlib_Check_PlayerClothInAram(Now_Private->cloth.idx);
    int bank_no;
    Object_Exchange_c* obj_ex = &play->object_exchange;

    Player_Pallet_bank_ID[bank_idx] = bank + mPlib_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_15, pal, mNW_PALETTE_SIZE,
                                                                             in_aram);

    if (in_aram) {
        bank_no = Player_Pallet_bank_ID[bank_idx];

        if (bank_no >= 0 && obj_ex->banks[bank_no].bank_id > 0) {
            u16* pal_p = (u16*)obj_ex->banks[bank_no].ram_start;
#ifdef TARGET_PC
            mPlib_ByteSwapPlayerPalette(pal_p);
#endif
            DCStoreRangeNoSync(pal_p, mNW_PALETTE_SIZE);
        }
    }
}

extern int mPlib_Check_PlayerClothInAram(int idx) {
    if (idx < (CLOTH_NUM + 1)) {
        return TRUE;
    }

    return FALSE;
}

static int Player_face_tex_bank_ID = -1;

extern void mPlib_Object_Exchange_keep_new_PlayerFaceTex(GAME_PLAY* play) {
    Player_face_tex_bank_ID = mPlib_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_52, 0, 0xE00, TRUE);
}

static int Player_face_pallet_bank_ID[] = { -1, -1 };

#ifdef TARGET_PC
static void mPlib_ByteSwapPlayerPalette(u16* pal) {
    if (pal != NULL) {
        pc_bswap16_array(pal, mNW_PALETTE_SIZE / (int)sizeof(u16));
    }
}
#endif

extern void mPlib_Object_Exchange_keep_new_PlayerFacePallet(GAME_PLAY* play, int bank, int bank_idx) {
    Player_face_pallet_bank_ID[bank_idx] =
        bank + mPlib_Object_Exchange_keep_new(play, ACTOR_OBJ_BANK_52, 0, mNW_PALETTE_SIZE, TRUE);
}

extern void mPlib_Object_Exchange_keep_Player_dt(GAME_PLAY* play) {
    Player_face_tex_bank_ID = -1;
    Player_face_pallet_bank_ID[0] = -1;
    Player_face_pallet_bank_ID[1] = -1;
    Player_bank_ID_Index = 0;
    Player_face_bank_ID_Index = 0;
    Player_Tex_bank_ID[0] = -1;
    Player_Tex_bank_ID[1] = -1;
    Player_Pallet_bank_ID[0] = -1;
    Player_Pallet_bank_ID[1] = -1;
}

extern u8* mPlib_get_player_tex_p(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Object_Exchange_c* obj_ex = &play->object_exchange;
    int bank_no = Player_Tex_bank_ID[Player_bank_ID_Index];

    if (bank_no >= 0 && obj_ex->banks[bank_no].bank_id > 0) {
        return (u8*)obj_ex->banks[bank_no].ram_start;
    }

    return NULL;
}

extern u16* mPlib_get_player_pallet_p(GAME* game) {
    u8* tex_p = mPlib_get_player_tex_p(game);

    if (tex_p != NULL) {
        tex_p = tex_p + mNW_DESIGN_TEX_SIZE;
    }

    return (u16*)tex_p;
}

extern u8* mPlib_get_player_face_p(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Object_Exchange_c* obj_ex = &play->object_exchange;
    int bank_no = Player_face_tex_bank_ID;

    if (bank_no >= 0 && obj_ex->banks[bank_no].bank_id > 0) {
        return (u8*)obj_ex->banks[bank_no].ram_start;
    }

    return NULL;
}

extern u16* mPlib_get_player_face_pallet_p(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Object_Exchange_c* obj_ex = &play->object_exchange;
    int bank_no = Player_face_pallet_bank_ID[Player_face_bank_ID_Index];

    if (bank_no >= 0 && obj_ex->banks[bank_no].bank_id > 0) {
        return (u16*)obj_ex->banks[bank_no].ram_start;
    }

    return NULL;
}

extern void mPlib_change_player_cloth(GAME* game, u16 cloth_idx) {
    int idx = cloth_idx;
    int in_aram = mPlib_Check_PlayerClothInAram(idx);
    Change_Player_bank_ID_Index();

    {
        u8* player_tex_p = mPlib_get_player_tex_p(game);
        u32 player_tex_rom_p = mPlib_Get_PlayerTexRom_p(idx);

        if (in_aram) {
            _JW_GetResourceAram(player_tex_rom_p, player_tex_p, mNW_DESIGN_TEX_SIZE);
        } else {
            bcopy((u8*)player_tex_rom_p, player_tex_p, mNW_DESIGN_TEX_SIZE);
        }

        DCStoreRangeNoSync(player_tex_p, mNW_DESIGN_TEX_SIZE);
    }

    {
        u16* player_pallet_p = mPlib_get_player_pallet_p(game);
        u32 player_pallet_rom_p = mPlib_Get_PlayerPalletRom_p(idx);

        if (in_aram) {
            _JW_GetResourceAram(player_pallet_rom_p, (u8*)player_pallet_p, mNW_PALETTE_SIZE);
        } else {
            bcopy((u16*)player_pallet_rom_p, player_pallet_p, mNW_PALETTE_SIZE);
        }

#ifdef TARGET_PC
        if (in_aram) {
            mPlib_ByteSwapPlayerPalette(player_pallet_p);
        }
#endif
        DCStoreRangeNoSync(player_pallet_p, mNW_PALETTE_SIZE);
    }
}

extern void mPlib_change_player_face_pallet(GAME* game) {
    Change_Player_face_bank_ID_Index();

    {
        u16* player_face_pallet_p = mPlib_get_player_face_pallet_p(game);
        u32 player_face_pallet_rom_p = mPlib_Get_UseFacePalletRom_p();

        if (player_face_pallet_p != NULL && player_face_pallet_rom_p != 0) {
            _JW_GetResourceAram(player_face_pallet_rom_p, (u8*)player_face_pallet_p, mNW_PALETTE_SIZE);
#ifdef TARGET_PC
            mPlib_ByteSwapPlayerPalette(player_face_pallet_p);
#endif
            DCStoreRangeNoSync(player_face_pallet_p, mNW_PALETTE_SIZE);
        }
    }
}

extern void mPlib_change_player_face(GAME* game) {
    u8* player_face_p = mPlib_get_player_face_p(game);
    u32 player_face_rom_p = mPlib_Get_UseFaceTexRom_p();

    if (player_face_p != NULL && player_face_rom_p != 0) {
        _JW_GetResourceAram(player_face_rom_p, player_face_p, 0xE00);
        DCStoreRangeNoSync(player_face_p, 0xE00);
    }

    mPlib_change_player_face_pallet(game);
}

extern PLAYER_ACTOR* get_player_actor_withoutCheck(GAME_PLAY* play) {
    return (PLAYER_ACTOR*)&play->actor_info.list[ACTOR_PART_PLAYER].actor[0];
}

static int mPlib_check_DynamicLinkFile_m_player(void) {
    return SubmenuArea_IsPlayer() != FALSE;
}

extern int mPlib_get_player_actor_main_index(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->now_main_index;
}

extern int mPlib_get_player_actor_request_main_index(GAME* game) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);

    if (player->requested_main_index_changed) {
        return player->requested_main_index;
    }

    return -1;
}

extern cKF_Skeleton_R_c cKF_bs_r_boy_1;
extern cKF_Skeleton_R_c cKF_bs_r_grl_1;

extern cKF_Skeleton_R_c* mPlib_get_player_mdl_p(void) {
    if (Now_Private->gender == mPr_SEX_MALE) {
        return &cKF_bs_r_boy_1;
    } else {
        return &cKF_bs_r_grl_1;
    }
}

extern s16 mPlib_get_player_Object_Bank(void) {
    if (Now_Private->gender == mPr_SEX_MALE) {
        return ACTOR_OBJ_BANK_8;
    } else {
        return ACTOR_OBJ_BANK_51;
    }
}

extern s8 BOY_part_data[][mPlayer_JOINT_NUM + 1];

extern void mPlib_DMA_player_Part_Table(s8* part_table_p, int idx) {
    if (idx >= 0 && idx < mPlayer_PART_TABLE_NUM) {
        bcopy(&BOY_part_data[idx], part_table_p, sizeof(BOY_part_data[idx]));
    }
}

extern void mPlib_change_player_cloth_info(mPr_cloth_c* cloth_p, mActor_name_t item) {
    cloth_p->item = item;
    cloth_p->idx = ITEM_IS_CLOTH(item) ? (item - ITM_CLOTH_START) : 0;
}

extern void mPlib_change_player_cloth_info_lv2(Private_c* priv, mActor_name_t item) {
    mPlib_change_player_cloth_info(&priv->cloth, item);
}

extern void mPlib_Load_PlayerTexAndPallet(void* tex_p, void* pal_p, int idx) {
    if (idx >= 0 && idx < (CLOTH_NUM + 1 + mPr_ORIGINAL_DESIGN_COUNT) && tex_p != NULL && pal_p != NULL) {
        u32 tex_rom_p = mPlib_Get_PlayerTexRom_p(idx);
        u32 pal_rom_p = mPlib_Get_PlayerPalletRom_p(idx);
        int in_aram = mPlib_Check_PlayerClothInAram(idx);

        if (in_aram) {
            _JW_GetResourceAram(tex_rom_p, (u8*)tex_p, mNW_DESIGN_TEX_SIZE);
            _JW_GetResourceAram(pal_rom_p, (u8*)pal_p, mNW_PALETTE_SIZE);
        } else {
            bcopy((u8*)tex_rom_p, tex_p, mNW_DESIGN_TEX_SIZE);
            bcopy((u16*)pal_rom_p, pal_p, mNW_PALETTE_SIZE);
        }

#ifdef TARGET_PC
        if (in_aram) {
            mPlib_ByteSwapPlayerPalette((u16*)pal_p);
        }
#endif

        DCStoreRangeNoSync(tex_p, mNW_DESIGN_TEX_SIZE);
        DCStoreRangeNoSync(pal_p, mNW_PALETTE_SIZE);
    }
}

static mPlayer_change_data_from_submenu_c change_data_from_submenu;

extern mPlayer_change_data_from_submenu_c* mPlib_Get_change_data_from_submenu_p(void) {
    return &change_data_from_submenu;
}

extern void mPlib_Clear_change_data_from_submenu(void) {
    bzero(&change_data_from_submenu, sizeof(change_data_from_submenu));
}

extern void mPlib_request_main_give_from_submenu(mActor_name_t item, int after_mode, int present_flag,
                                                 int surface_flag) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_give_c* req_give_p = &change_data_from_submenu_p->request_main_data.give;

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_GIVE;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_give_p->item = item;
    req_give_p->mode = after_mode;
    req_give_p->present_flag = present_flag;
    req_give_p->on_surface_flag = surface_flag;
}

extern void mPlib_request_main_putin_scoop_from_submenu(const xyz_t* pos_p, mActor_name_t item, int gold_scoop_flag) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_putin_scoop_c* req_putin_scoop_p = &change_data_from_submenu_p->request_main_data.putin_scoop;

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_PUTIN_SCOOP;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_putin_scoop_p->dig_pos = *pos_p;
    req_putin_scoop_p->item = item;
    req_putin_scoop_p->get_gold_scoop_flag = gold_scoop_flag;
}

extern void mPlib_request_main_release_creature_gyoei_from_submenu(s16 angle_y, s16 item, int gold_scoop_flag) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_release_creature_c* req_release_creature_p =
        &change_data_from_submenu_p->request_main_data.release_creature;
    mPlayer_request_release_creature_gyoei_c* release_gyoei_p = &req_release_creature_p->data.gyoei;

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_RELEASE_CREATURE;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_release_creature_p->type = mPlayer_CREATURE_GYOEI;
    req_release_creature_p->gold_scoop_flag = gold_scoop_flag;

    release_gyoei_p->angle_y = angle_y;
    release_gyoei_p->_02 = item;
}

extern void mPlib_request_main_release_creature_insect_from_submenu(int insect_type, int gold_scoop_flag) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_release_creature_c* req_release_creature_p =
        &change_data_from_submenu_p->request_main_data.release_creature;
    mPlayer_request_release_creature_insect_c* release_insect_p = &req_release_creature_p->data.insect;
    ACTOR* actorx = GET_PLAYER_ACTOR_NOW_ACTOR();

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_RELEASE_CREATURE;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_release_creature_p->type = mPlayer_CREATURE_INSECT;
    req_release_creature_p->gold_scoop_flag = gold_scoop_flag;

    release_insect_p->pos.x = actorx->world.position.x + 7.0f * sin_s(actorx->shape_info.rotation.y);
    release_insect_p->pos.y = actorx->world.position.y + 13.0f;
    release_insect_p->pos.z = actorx->world.position.z + 7.0f * cos_s(actorx->shape_info.rotation.y);
    release_insect_p->type = insect_type;
}

extern s8 mPlib_Get_ItemNoToItemKind(mActor_name_t itemNo) {
    switch (itemNo) {
        case ITM_NET:
            return mPlayer_ITEM_KIND_NET;
        case ITM_GOLDEN_NET:
            return mPlayer_ITEM_KIND_GOLD_NET;
        case ITM_AXE:
            return mPlayer_ITEM_KIND_AXE;
        case ITM_AXE_USE_1:
            return mPlayer_ITEM_KIND_AXE_USE_1;
        case ITM_AXE_USE_2:
            return mPlayer_ITEM_KIND_AXE_USE_2;
        case ITM_AXE_USE_3:
            return mPlayer_ITEM_KIND_AXE_USE_3;
        case ITM_AXE_USE_4:
            return mPlayer_ITEM_KIND_AXE_USE_4;
        case ITM_AXE_USE_5:
            return mPlayer_ITEM_KIND_AXE_USE_5;
        case ITM_AXE_USE_6:
            return mPlayer_ITEM_KIND_AXE_USE_6;
        case ITM_AXE_USE_7:
            return mPlayer_ITEM_KIND_AXE_USE_7;
        case ITM_GOLDEN_AXE:
            return mPlayer_ITEM_KIND_GOLD_AXE;
        case ITM_UMBRELLA00:
            return mPlayer_ITEM_KIND_UMBRELLA00;
        case ITM_UMBRELLA01:
            return mPlayer_ITEM_KIND_UMBRELLA01;
        case ITM_UMBRELLA02:
            return mPlayer_ITEM_KIND_UMBRELLA02;
        case ITM_UMBRELLA03:
            return mPlayer_ITEM_KIND_UMBRELLA03;
        case ITM_UMBRELLA04:
            return mPlayer_ITEM_KIND_UMBRELLA04;
        case ITM_UMBRELLA05:
            return mPlayer_ITEM_KIND_UMBRELLA05;
        case ITM_UMBRELLA06:
            return mPlayer_ITEM_KIND_UMBRELLA06;
        case ITM_UMBRELLA07:
            return mPlayer_ITEM_KIND_UMBRELLA07;
        case ITM_UMBRELLA08:
            return mPlayer_ITEM_KIND_UMBRELLA08;
        case ITM_UMBRELLA09:
            return mPlayer_ITEM_KIND_UMBRELLA09;
        case ITM_UMBRELLA10:
            return mPlayer_ITEM_KIND_UMBRELLA10;
        case ITM_UMBRELLA11:
            return mPlayer_ITEM_KIND_UMBRELLA11;
        case ITM_UMBRELLA12:
            return mPlayer_ITEM_KIND_UMBRELLA12;
        case ITM_UMBRELLA13:
            return mPlayer_ITEM_KIND_UMBRELLA13;
        case ITM_UMBRELLA14:
            return mPlayer_ITEM_KIND_UMBRELLA14;
        case ITM_UMBRELLA15:
            return mPlayer_ITEM_KIND_UMBRELLA15;
        case ITM_UMBRELLA16:
            return mPlayer_ITEM_KIND_UMBRELLA16;
        case ITM_UMBRELLA17:
            return mPlayer_ITEM_KIND_UMBRELLA17;
        case ITM_UMBRELLA18:
            return mPlayer_ITEM_KIND_UMBRELLA18;
        case ITM_UMBRELLA19:
            return mPlayer_ITEM_KIND_UMBRELLA19;
        case ITM_UMBRELLA20:
            return mPlayer_ITEM_KIND_UMBRELLA20;
        case ITM_UMBRELLA21:
            return mPlayer_ITEM_KIND_UMBRELLA21;
        case ITM_UMBRELLA22:
            return mPlayer_ITEM_KIND_UMBRELLA22;
        case ITM_UMBRELLA23:
            return mPlayer_ITEM_KIND_UMBRELLA23;
        case ITM_UMBRELLA24:
            return mPlayer_ITEM_KIND_UMBRELLA24;
        case ITM_UMBRELLA25:
            return mPlayer_ITEM_KIND_UMBRELLA25;
        case ITM_UMBRELLA26:
            return mPlayer_ITEM_KIND_UMBRELLA26;
        case ITM_UMBRELLA27:
            return mPlayer_ITEM_KIND_UMBRELLA27;
        case ITM_UMBRELLA28:
            return mPlayer_ITEM_KIND_UMBRELLA28;
        case ITM_UMBRELLA29:
            return mPlayer_ITEM_KIND_UMBRELLA29;
        case ITM_UMBRELLA30:
            return mPlayer_ITEM_KIND_UMBRELLA30;
        case ITM_UMBRELLA31:
            return mPlayer_ITEM_KIND_UMBRELLA31;
        case ITM_MY_ORG_UMBRELLA0:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA00;
        case ITM_MY_ORG_UMBRELLA1:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA01;
        case ITM_MY_ORG_UMBRELLA2:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA02;
        case ITM_MY_ORG_UMBRELLA3:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA03;
        case ITM_MY_ORG_UMBRELLA4:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA04;
        case ITM_MY_ORG_UMBRELLA5:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA05;
        case ITM_MY_ORG_UMBRELLA6:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA06;
        case ITM_MY_ORG_UMBRELLA7:
            return mPlayer_ITEM_KIND_ORG_UMBRELLA07;
        case ITM_ROD:
            return mPlayer_ITEM_KIND_ROD;
        case ITM_GOLDEN_ROD:
            return mPlayer_ITEM_KIND_GOLD_ROD;
        case ITM_SHOVEL:
            return mPlayer_ITEM_KIND_SHOVEL;
        case ITM_GOLDEN_SHOVEL:
            return mPlayer_ITEM_KIND_GOLD_SHOVEL;
        case ITM_RED_BALLOON:
            return mPlayer_ITEM_KIND_RED_BALLOON;
        case ITM_YELLOW_BALLOON:
            return mPlayer_ITEM_KIND_YELLOW_BALLOON;
        case ITM_BLUE_BALLOON:
            return mPlayer_ITEM_KIND_BLUE_BALLOON;
        case ITM_GREEN_BALLOON:
            return mPlayer_ITEM_KIND_GREEN_BALLOON;
        case ITM_PURPLE_BALLOON:
            return mPlayer_ITEM_KIND_PURPLE_BALLOON;
        case ITM_BUNNY_P_BALLOON:
            return mPlayer_ITEM_KIND_BUNNY_P_BALLOON;
        case ITM_BUNNY_B_BALLOON:
            return mPlayer_ITEM_KIND_BUNNY_B_BALLOON;
        case ITM_BUNNY_O_BALLOON:
            return mPlayer_ITEM_KIND_BUNNY_O_BALLOON;
        case ITM_YELLOW_PINWHEEL:
            return mPlayer_ITEM_KIND_YELLOW_PINWHEEL;
        case ITM_RED_PINWHEEL:
            return mPlayer_ITEM_KIND_RED_PINWHEEL;
        case ITM_TIGER_PINWHEEL:
            return mPlayer_ITEM_KIND_TIGER_PINWHEEL;
        case ITM_GREEN_PINWHEEL:
            return mPlayer_ITEM_KIND_GREEN_PINWHEEL;
        case ITM_PINK_PINWHEEL:
            return mPlayer_ITEM_KIND_PINK_PINWHEEL;
        case ITM_STRIPED_PINWHEEL:
            return mPlayer_ITEM_KIND_STRIPED_PINWHEEL;
        case ITM_FLOWER_PINWHEEL:
            return mPlayer_ITEM_KIND_FLOWER_PINWHEEL;
        case ITM_FANCY_PINWHEEL:
            return mPlayer_ITEM_KIND_FANCY_PINWHEEL;
        case ITM_BLUEBELL_FAN:
            return mPlayer_ITEM_KIND_BLUEBELL_FAN;
        case ITM_PLUM_FAN:
            return mPlayer_ITEM_KIND_PLUM_FAN;
        case ITM_BAMBOO_FAN:
            return mPlayer_ITEM_KIND_BAMBOO_FAN;
        case ITM_CLOUD_FAN:
            return mPlayer_ITEM_KIND_CLOUD_FAN;
        case ITM_MAPLE_FAN:
            return mPlayer_ITEM_KIND_MAPLE_FAN;
        case ITM_FAN_FAN:
            return mPlayer_ITEM_KIND_FAN_FAN;
        case ITM_FLOWER_FAN:
            return mPlayer_ITEM_KIND_FLOWER_FAN;
        case ITM_LEAF_FAN:
            return mPlayer_ITEM_KIND_LEAF_FAN;
        default:
            return -1;
    }
}

extern int mPlib_Get_ItemKindTOBalloonShapeType(int item_kind) {
    if (mPlayer_ITEM_IS_BALLOON(item_kind) != FALSE) {
        return item_kind - mPlayer_ITEM_KIND_RED_BALLOON;
    }

    return 0;
}

static int mPlib_Get_itemNOTOBalloonShapeType(mActor_name_t itemNo) {
    return mPlib_Get_ItemKindTOBalloonShapeType(mPlib_Get_ItemNoToItemKind(itemNo));
}

extern void mPlib_request_main_release_creature_balloon_from_submenu(mActor_name_t itemNo, int gold_scoop_flag) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_release_creature_c* req_release_creature_p =
        &change_data_from_submenu_p->request_main_data.release_creature;
    mPlayer_request_release_creature_balloon_c* release_balloon_p = &req_release_creature_p->data.balloon;
    ACTOR* actorx = GET_PLAYER_ACTOR_NOW_ACTOR(); /* @unused */

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_RELEASE_CREATURE;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_release_creature_p->type = mPlayer_CREATURE_BALLOON;
    req_release_creature_p->gold_scoop_flag = gold_scoop_flag;

    release_balloon_p->balloon_type = mPlib_Get_itemNOTOBalloonShapeType(itemNo);
}

extern void mPlib_request_main_wait_from_submenu(void) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_WAIT;
    change_data_from_submenu_p->requested_index_pending = TRUE;
}

extern void mPlib_request_main_demo_get_golden_item_from_submenu(void) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_DEMO_GET_GOLDEN_ITEM;
    change_data_from_submenu_p->requested_index_pending = TRUE;
}

extern void mPlib_request_main_mail_land_from_submenu(void) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_MAIL_LAND;
    change_data_from_submenu_p->requested_index_pending = TRUE;
}

extern void mPlib_request_main_demo_wait_from_submenu(ACTOR* speak_actor_p) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();
    mPlayer_request_demo_wait_c* req_demo_wait_p = &change_data_from_submenu_p->request_main_data.demo_wait;

    change_data_from_submenu_p->requested_main_index = mPlayer_INDEX_DEMO_WAIT;
    change_data_from_submenu_p->requested_index_pending = TRUE;

    req_demo_wait_p->umbrella_flag = FALSE;
    req_demo_wait_p->label = (uintptr_t)speak_actor_p;

    if (speak_actor_p != NULL) {
        mPlib_Set_able_force_speak_label(speak_actor_p);
    }
}

extern void mPlib_Set_unable_wade(int v) {
    Common_Set(unable_wade, v);
}

extern int mPlib_Get_unable_wade(void) {
    return Common_Get(unable_wade);
}

extern int mPlib_Check_able_force_speak_label(GAME* game, ACTOR* label) {
    if (Common_Get(player_actor_exists) == FALSE) {
        return FALSE;
    }

    return GET_PLAYER_ACTOR_GAME(game)->Check_able_force_speak_label_proc(game, label);
}

extern void mPlib_Set_able_force_speak_label(ACTOR* label) {
    if (Common_Get(player_actor_exists)) {
        GET_PLAYER_ACTOR_NOW()->able_force_speak_label = (uintptr_t)label;
    }
}

extern void mPlib_Reset_able_force_speak_label(void) {
    mPlib_Set_able_force_speak_label(NULL);
}

extern u8 ply_1_get_change12_tex_index[];
extern u8 ply_1_kokeru_a12_tex_index[];
extern u8 ply_1_kokeru_getup_a12_tex_index[];
extern u8 ply_1_kokeru_getup_n12_tex_index[];
extern u8 ply_1_kokeru_n12_tex_index[];
extern u8 ply_1_axe_swing12_tex_index[];
extern u8 ply_1_kokeru12_tex_index[];
extern u8 ply_1_kokeru_getup12_tex_index[];
extern u8 ply_1_axe_hane12_tex_index[];
extern u8 ply_1_axe_suka12_tex_index[];
extern u8 ply_1_get_t12_tex_index[];
extern u8 ply_1_menu_change12_tex_index[];
extern u8 ply_1_not_sao_swing12_tex_index[];
extern u8 ply_1_not_dig12_tex_index[];
extern u8 ply_1_dig_suka12_tex_index[];
extern u8 ply_1_shake12_tex_index[];
extern u8 ply_1_eat12_tex_index[];
extern u8 ply_1_gaaan12_tex_index[];
extern u8 ply_1_deru12_tex_index[];
extern u8 ply_1_guratuku12_tex_index[];
extern u8 ply_1_otiru12_tex_index[];
extern u8 ply_1_biku12_tex_index[];
extern u8 ply_1_hati12_tex_index[];
extern u8 ply_1_hati22_tex_index[];
extern u8 ply_1_hati32_tex_index[];
extern u8 ply_1_deru22_tex_index[];
extern u8 ply_1_otiru22_tex_index[];
extern u8 ply_1_itazura12_tex_index[];
extern u8 ply_1_yatta12_tex_index[];
extern u8 ply_1_yatta22_tex_index[];
extern u8 ply_1_yatta32_tex_index[];
extern u8 ply_1_mosquito12_tex_index[];
extern u8 ply_1_axe_break12_tex_index[];

extern u8* mPlib_Get_PlayerEyeTexAnimation_p(int anim_idx) {
    if (anim_idx >= 0 && anim_idx < mPlayer_ANIM_NUM) {
        static u8* const eye_tex_index_table[] = {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_get_change12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_kokeru_a12_tex_index,
            ply_1_kokeru_getup_a12_tex_index,
            ply_1_kokeru_getup_n12_tex_index,
            ply_1_kokeru_n12_tex_index,
            NULL,
            NULL,
            ply_1_axe_swing12_tex_index,
            NULL,
            ply_1_kokeru12_tex_index,
            ply_1_kokeru_getup12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_axe_hane12_tex_index,
            ply_1_axe_suka12_tex_index,
            NULL,
            NULL,
            ply_1_get_t12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_menu_change12_tex_index,
            NULL,
            ply_1_not_sao_swing12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_not_dig12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_dig_suka12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_shake12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_eat12_tex_index,
            ply_1_gaaan12_tex_index,
            NULL,
            ply_1_deru12_tex_index,
            ply_1_guratuku12_tex_index,
            NULL,
            ply_1_otiru12_tex_index,
            NULL,
            NULL,
            ply_1_biku12_tex_index,
            ply_1_hati12_tex_index,
            ply_1_hati22_tex_index,
            ply_1_hati32_tex_index,
            NULL,
            ply_1_deru22_tex_index,
            ply_1_otiru22_tex_index,
            ply_1_itazura12_tex_index,
            NULL,
            NULL,
            ply_1_yatta12_tex_index,
            ply_1_yatta22_tex_index,
            ply_1_yatta32_tex_index,
            NULL,
            ply_1_mosquito12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_axe_break12_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        };

        return eye_tex_index_table[anim_idx];
    }

    return NULL;
}

extern u8 ply_1_get_change11_tex_index[];
extern u8 ply_1_kokeru_a11_tex_index[];
extern u8 ply_1_kokeru_getup_a11_tex_index[];
extern u8 ply_1_kokeru_getup_n11_tex_index[];
extern u8 ply_1_kokeru_n11_tex_index[];
extern u8 ply_1_axe_swing11_tex_index[];
extern u8 ply_1_kokeru11_tex_index[];
extern u8 ply_1_kokeru_getup11_tex_index[];
extern u8 ply_1_axe_hane11_tex_index[];
extern u8 ply_1_axe_suka11_tex_index[];
extern u8 ply_1_get_t11_tex_index[];
extern u8 ply_1_get_t21_tex_index[];
extern u8 ply_1_not_get_t11_tex_index[];
extern u8 ply_1_menu_change11_tex_index[];
extern u8 ply_1_not_sao_swing11_tex_index[];
extern u8 ply_1_not_dig11_tex_index[];
extern u8 ply_1_dig_suka11_tex_index[];
extern u8 ply_1_eat11_tex_index[];
extern u8 ply_1_gaaan11_tex_index[];
extern u8 ply_1_deru11_tex_index[];
extern u8 ply_1_guratuku11_tex_index[];
extern u8 ply_1_mogaku11_tex_index[];
extern u8 ply_1_otiru11_tex_index[];
extern u8 ply_1_biku11_tex_index[];
extern u8 ply_1_hati11_tex_index[];
extern u8 ply_1_hati21_tex_index[];
extern u8 ply_1_hati31_tex_index[];
extern u8 ply_1_deru21_tex_index[];
extern u8 ply_1_otiru21_tex_index[];
extern u8 ply_1_itazura11_tex_index[];
extern u8 ply_1_yatta11_tex_index[];
extern u8 ply_1_yatta21_tex_index[];
extern u8 ply_1_yatta31_tex_index[];
extern u8 ply_1_mosquito11_tex_index[];
extern u8 ply_1_axe_break11_tex_index[];

extern u8* mPlib_Get_PlayerMouthTexAnimation_p(int anim_idx) {
    if (anim_idx >= 0 && anim_idx < mPlayer_ANIM_NUM) {
        static u8* const mouth_tex_index_table[] = {
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_get_change11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_kokeru_a11_tex_index,
            ply_1_kokeru_getup_a11_tex_index,
            ply_1_kokeru_getup_n11_tex_index,
            ply_1_kokeru_n11_tex_index,
            NULL,
            NULL,
            ply_1_axe_swing11_tex_index,
            NULL,
            ply_1_kokeru11_tex_index,
            ply_1_kokeru_getup11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_axe_hane11_tex_index,
            ply_1_axe_suka11_tex_index,
            NULL,
            NULL,
            ply_1_get_t11_tex_index,
            ply_1_get_t21_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_not_get_t11_tex_index,
            NULL,
            ply_1_menu_change11_tex_index,
            NULL,
            ply_1_not_sao_swing11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_not_dig11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_dig_suka11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_eat11_tex_index,
            ply_1_gaaan11_tex_index,
            NULL,
            ply_1_deru11_tex_index,
            ply_1_guratuku11_tex_index,
            ply_1_mogaku11_tex_index,
            ply_1_otiru11_tex_index,
            NULL,
            NULL,
            ply_1_biku11_tex_index,
            ply_1_hati11_tex_index,
            ply_1_hati21_tex_index,
            ply_1_hati31_tex_index,
            NULL,
            ply_1_deru21_tex_index,
            ply_1_otiru21_tex_index,
            ply_1_itazura11_tex_index,
            NULL,
            NULL,
            ply_1_yatta11_tex_index,
            ply_1_yatta21_tex_index,
            ply_1_yatta31_tex_index,
            NULL,
            ply_1_mosquito11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            ply_1_axe_break11_tex_index,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
        };

        return mouth_tex_index_table[anim_idx];
    }

    return NULL;
}

extern u8* mPlib_Get_eye_tex_p(int idx) {
    if (idx >= 0 && idx < mPlayer_EYE_TEX_NUM) {
        u8* face_tex_p = mPlib_get_player_face_p(gamePT);

        if (face_tex_p != NULL) {
            return face_tex_p + idx * 0x100;
        }
    }

    return NULL;
}

extern u8* mPlib_Get_mouth_tex_p(int idx) {
    if (idx >= 0 && idx < mPlayer_MOUTH_TEX_NUM) {
        u8* face_tex_p = mPlib_get_player_face_p(gamePT);

        if (face_tex_p != NULL) {
            face_tex_p += (mPlayer_EYE_TEX_NUM * 0x100) + idx * 0x100;
            return face_tex_p;
        }
    }

    return NULL;
}

extern int mPlib_request_main_invade_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_invade_all_proc(game, mPlayer_REQUEST_PRIORITY_2);
}

extern int mPlib_request_main_refuse_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_refuse_all_proc(game, mPlayer_REQUEST_PRIORITY_34);
}

extern int mPlib_request_main_wait_type3(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_return_demo_all_proc(game, mPlayer_INDEX_WAIT, 3.0f,
                                                                          mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_get_golden_item2_type1(GAME* game, int golden_item_type) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_get_golden_item2_all_proc(game, golden_item_type,
                                                                                    mPlayer_REQUEST_PRIORITY_34);
}

extern int mPlib_request_main_talk_end_type1(GAME* game, int wait_demo, int demo_get_golden_axe) {
    if (wait_demo == FALSE) {
        if (demo_get_golden_axe == FALSE) {
            return GET_PLAYER_ACTOR_GAME(game)->request_main_return_demo_all_proc(game, mPlayer_INDEX_WAIT, 3.0f,
                                                                                  mPlayer_REQUEST_PRIORITY_19);
        } else {
            return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_get_golden_axe_wait_all_proc(
                game, mPlayer_REQUEST_PRIORITY_33);
        }
    } else {
        return mPlib_request_main_demo_wait_type1(game, FALSE, NULL);
    }
}

extern int mPlib_request_main_talk_type1(GAME* game, ACTOR* talk_actor_p, int turn_flag, int umbrella_flag) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_talk_all_proc(game, talk_actor_p, turn_flag, -5.0f, umbrella_flag,
                                                                   mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_hold_type1(GAME* game, int ftr_no, int player_direct, const xyz_t* player_pos_p) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_hold_all_proc(game, ftr_no, player_direct, player_pos_p, -5.0f, 1,
                                                                   mPlayer_REQUEST_PRIORITY_9);
}

extern int mPlib_request_main_recieve_wait_type1(GAME* game, mActor_name_t item, int counter_flag) {
    GET_PLAYER_ACTOR_GAME(game)->request_main_recieve_wait_all_proc(
        game, GET_PLAYER_ACTOR_GAME(game)->main_data.talk.talk_actor_p,
        GET_PLAYER_ACTOR_GAME(game)->main_data.talk.turn_flag, GET_PLAYER_ACTOR_GAME(game)->now_main_index, item,
        counter_flag, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_give_type1(GAME* game, mActor_name_t item, int mode, int present, int on_surface) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);
    int return_main_index = player->now_main_index;
    ACTOR* talk_actor_p;
    int turn_flag;

    if (return_main_index == mPlayer_INDEX_TALK) {
        talk_actor_p = player->main_data.talk.talk_actor_p;
        turn_flag = player->main_data.talk.turn_flag;
    } else {
        talk_actor_p = NULL;
        turn_flag = FALSE;
    }

    GET_PLAYER_ACTOR_GAME(game)->request_main_give_all_proc(game, talk_actor_p, turn_flag, return_main_index, item,
                                                            mode, present, on_surface, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_sitdown_type1(GAME* game, int direct, const xyz_t* pos_p, int ftr_no) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_sitdown_all_proc(game, direct, pos_p, ftr_no,
                                                                      mPlayer_REQUEST_PRIORITY_2);
}

extern int mPlib_request_main_close_furniture_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_close_furniture_all_proc(game, mPlayer_REQUEST_PRIORITY_23);
}

extern int mPlib_request_main_lie_bed_type1(GAME* game, int direct, const xyz_t* pos_p, int head_direct, int ftr_no) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_lie_bed_all_proc(game, direct, pos_p, head_direct, ftr_no,
                                                                      mPlayer_REQUEST_PRIORITY_9);
}

extern int mPlib_request_main_hide_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_hide_all_proc(game, mPlayer_REQUEST_PRIORITY_43);
}

extern int mPlib_request_main_groundhog_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_groundhog_proc(game, mPlayer_REQUEST_PRIORITY_43);
}

extern int mPlib_request_main_door_type1(GAME* game, const xyz_t* pos_p, s16 angle_y, int door_type, void* door_label) {
    if (GET_PLAYER_ACTOR_GAME(game)->request_main_door_all_proc(game, pos_p, angle_y, door_type, door_label,
                                                                mPlayer_REQUEST_PRIORITY_7)) {
        return TRUE;
    }
    return FALSE;
}

extern int mPlib_request_main_door_type2(GAME* game, const xyz_t* pos_p, s16 angle_y, int door_type, void* door_label) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_door_all_proc(game, pos_p, angle_y, door_type, door_label,
                                                                   mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_outdoor_type1(GAME* game, int is_start_demo, int door_type) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_outdoor_all_proc(game, is_start_demo, door_type,
                                                                      mPlayer_REQUEST_PRIORITY_43);
}

extern int mPlib_request_main_wash_car_type1(GAME* game, const xyz_t* car_pos_p, const xyz_t* ret_pos_p,
                                             s16 ret_angle_y, ACTOR* ctrl_actor_p) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_wash_car_all_proc(game, car_pos_p, ret_pos_p, ret_angle_y,
                                                                       ctrl_actor_p, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_rotate_octagon_type1(GAME* game, const xyz_t* pos_p, s16 angle_y) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_TALK) {
        return GET_PLAYER_ACTOR_GAME(game)->request_main_rotate_octagon_all_proc(
            game, GET_PLAYER_ACTOR_GAME(game)->main_data.talk.talk_actor_p,
            GET_PLAYER_ACTOR_GAME(game)->main_data.talk.turn_flag, GET_PLAYER_ACTOR_GAME(game)->now_main_index, pos_p,
            angle_y, mPlayer_REQUEST_PRIORITY_19);
    } else {
        return GET_PLAYER_ACTOR_GAME(game)->request_main_rotate_octagon_all_proc(
            game, NULL, FALSE, GET_PLAYER_ACTOR_GAME(game)->now_main_index, pos_p, angle_y,
            mPlayer_REQUEST_PRIORITY_19);
    }
}

extern int mPlib_request_main_throw_money_type1(GAME* game, const xyz_t* pos_p, s16 angle_y) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_throw_money_all_proc(game, pos_p, angle_y,
                                                                          mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_pray_type1(GAME* game, const xyz_t* pos_p, s16 angle_y) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_pray_all_proc(game, pos_p, angle_y, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_mail_jump_type1(GAME* game, const xyz_t* pos_p, s16 angle_y) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_mail_jump_all_proc(game, pos_p, angle_y,
                                                                        mPlayer_REQUEST_PRIORITY_9);
}

extern int mPlib_request_main_stung_bee_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_stung_bee_all_proc(game, mPlayer_REQUEST_PRIORITY_25);
}

extern int mPlib_request_main_stung_mosquito_type1(void* label) {
    return GET_PLAYER_ACTOR_NOW()->request_main_stung_mosquito_all_proc(gamePT, label, mPlayer_REQUEST_PRIORITY_25);
}

extern int mPlib_request_main_switch_on_lighthouse_type1(GAME* game, const xyz_t* pos_p, s16 angle_y) {
    return GET_PLAYER_ACTOR_NOW()->request_main_switch_on_lighthouse_all_proc(game, pos_p, angle_y,
                                                                              mPlayer_REQUEST_PRIORITY_9);
}

extern int mPlib_request_main_demo_geton_boat_type1(f32 goal_x, f32 goal_z, s16 angleY) {
    ACTOR* actorx = GET_PLAYER_ACTOR_NOW_ACTOR();
    xyz_t goal_pos;

    goal_pos.x = goal_x;
    goal_pos.z = goal_z;
    goal_pos.y = actorx->world.position.y;

    return GET_PLAYER_ACTOR_NOW()->request_main_demo_geton_boat_all_proc(gamePT, &goal_pos, angleY,
                                                                         mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_getoff_boat_standup_type1(const xyz_t* pos_p, s16 angleY) {
    return GET_PLAYER_ACTOR_NOW()->request_main_demo_getoff_boat_standup_all_proc(gamePT, pos_p, angleY,
                                                                                  mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_shock_type1(GAME* game, f32 time, s16 angle_y, int axe_swing) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_shock_all_proc(game, time, angle_y, FALSE, axe_swing,
                                                                    mPlayer_REQUEST_PRIORITY_14);
}

extern int mPlib_request_main_change_cloth_forNPC_type1(GAME* game, mActor_name_t cloth_item, u16 cloth_idx,
                                                        int try_on_flag) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_change_cloth_forNPC_proc(game, cloth_item, cloth_idx, try_on_flag);
}

extern int mPlib_request_main_push_snowball_type1(GAME* game, void* label) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_push_snowball_all_proc(game, label, FALSE,
                                                                            mPlayer_REQUEST_PRIORITY_2);
}

extern int mPlib_request_main_push_snowball_end_type1(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUSH_SNOWBALL) {
        return GET_PLAYER_ACTOR_GAME(game)->request_main_wait_all_proc(game, -5.0f, 0.0f, 0,
                                                                       mPlayer_REQUEST_PRIORITY_1);
    }

    return FALSE;
}

extern int mPlib_request_main_demo_wait_type1(GAME* game, int umbrella_flag, void* label) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_wait_all_proc(game, umbrella_flag, label,
                                                                        mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_walk_type1(GAME* game, f32 goal_x, f32 goal_z, f32 speed, int wait_flag) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_walk_all_proc(game, goal_x, goal_z, speed, wait_flag,
                                                                        mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_geton_train_type1(GAME* game, const xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_geton_train_all_proc(game, pos_p, DEG2SHORT_ANGLE2(180.0f),
                                                                               mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_getoff_train_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_getoff_train_all_proc(
        game, &GET_PLAYER_ACTOR_GAME_ACTOR(game)->world.position,
        GET_PLAYER_ACTOR_GAME_ACTOR(game)->shape_info.rotation.y, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_request_main_demo_standing_train_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->request_main_demo_standing_train_all_proc(game, mPlayer_REQUEST_PRIORITY_19);
}

extern int mPlib_check_request_main_talk_type1_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_TALK) == FALSE) {
            if (mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_WAIT &&
                mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_WALK &&
                mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_TIRED &&
                mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_TALK &&
                mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_WASH_CAR &&
                mPlib_get_player_actor_main_index(game) != mPlayer_INDEX_DEMO_STANDING_TRAIN) {
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mPlib_check_request_main_speak_type1_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_TALK) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mPlib_check_request_main_door_type1_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_7) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_DOOR) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mPlib_check_request_main_door_type2_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_DOOR) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mPlib_check_request_main_wade_priority(GAME* game) {
    int res;

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_WADE_SNOWBALL) {
        res = FALSE;

        if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_2) > 0) {
            if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_WADE_SNOWBALL) ==
                FALSE) {
                res = TRUE;
            }
        }
    } else {
        res = FALSE;

        if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_2) > 0) {
            if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_WADE) == FALSE) {
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mPlib_check_request_main_demo_wade_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(mPlayer_INDEX_DEMO_WADE) ==
            FALSE) {
            res = TRUE;
        }
    }

    return res;
}

extern int mPlib_check_request_main_demo_geton_boat_wade_priority(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0) {
        if (GET_PLAYER_ACTOR_GAME(game)->check_cancel_request_change_proc_index_proc(
                mPlayer_INDEX_DEMO_GETON_BOAT_WADE) == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

static int mPlib_strength_request_main_index_priority(GAME* game, int priority) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);

    if (player->requested_main_index_priority < priority) {
        player->requested_main_index_priority = priority;
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_strength_request_main_wade_priority(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_WADE) {
        return TRUE;
    }

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_WADE) {
        mPlib_strength_request_main_index_priority(game, mPlayer_REQUEST_PRIORITY_19);
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_strength_request_main_demo_wade_priority(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DEMO_WADE) {
        return TRUE;
    }

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_DEMO_WADE) {
        mPlib_strength_request_main_index_priority(game, mPlayer_REQUEST_PRIORITY_19);
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_strength_request_main_wade_snowball_priority(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_WADE_SNOWBALL) {
        return TRUE;
    }

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_WADE_SNOWBALL) {
        mPlib_strength_request_main_index_priority(game, mPlayer_REQUEST_PRIORITY_19);
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_strength_request_main_demo_geton_boat_wade_priority(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DEMO_GETON_BOAT_WADE) {
        return TRUE;
    }

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_DEMO_GETON_BOAT_WADE) {
        mPlib_strength_request_main_index_priority(game, mPlayer_REQUEST_PRIORITY_19);
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_strength_request_main_door_priority(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DOOR) {
        return TRUE;
    }

    if (mPlib_get_player_actor_request_main_index(game) == mPlayer_INDEX_DOOR) {
        mPlib_strength_request_main_index_priority(game, mPlayer_REQUEST_PRIORITY_19);
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_check_request_main_outdoor_priority(GAME* game) {
    return TRUE;
}

extern int mPlib_Check_SetOrderSubmenu(void) {
    mPlayer_change_data_from_submenu_c* change_data_from_submenu_p = mPlib_Get_change_data_from_submenu_p();

    return change_data_from_submenu_p->requested_index_pending != FALSE;
}

static int mPlib_check_request_change_item(void) {
    int idx;

    if (Common_Get(player_actor_exists) == FALSE) {
        return TRUE;
    }

    if (mPlib_check_DynamicLinkFile_m_player() == FALSE) {
        return TRUE;
    }

    idx = GET_PLAYER_ACTOR_GAME(gamePT)->check_request_change_item_proc(gamePT);
    return mPlayer_MAIN_INDEX_VALID(idx);
}

static int mPlib_CheckScene_AbleSubmenu(void) {

    if (Common_Get(player_actor_exists) == FALSE) {
        return FALSE;
    }

    if (mPlib_check_DynamicLinkFile_m_player() == FALSE) {
        return FALSE;
    }

    return GET_PLAYER_ACTOR_GAME(gamePT)->CheckScene_AbleSubmenu_proc();
}

extern int mPlib_able_submenu_type1(GAME* game) {
    int res = FALSE;

    if (GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_19) > 0 &&
        mPlib_Check_SetOrderSubmenu() == FALSE && mPlib_check_request_change_item() == FALSE &&
        mPlib_check_player_warp_forEvent() == FALSE &&
        GET_PLAYER_ACTOR_GAME(game)->able_submenu_request_main_index_proc(game) && mPlib_CheckScene_AbleSubmenu()) {
        res = TRUE;
    }

    return res;
}

static int mPlib_check_priority_event_type1(GAME* game) {
    return GET_PLAYER_ACTOR_GAME(game)->check_request_main_priority_proc(game, mPlayer_REQUEST_PRIORITY_17) > 0;
}

extern int mPlib_check_player_open_umbrella(GAME* game) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);

    if (player->umbrella_actor != NULL) {
        UMBRELLA_ACTOR* umbrella_actor = (UMBRELLA_ACTOR*)player->umbrella_actor;

        if (umbrella_actor->opened_fully) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mPlib_check_player_outdoor_start(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_OUTDOOR) {
        mPlayer_main_outdoor_c* outdoor_p = &GET_PLAYER_ACTOR_GAME(game)->main_data.outdoor;

        if (outdoor_p->is_demo) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mPlib_check_label_player_demo_wait(GAME* game, void* label) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DEMO_WAIT) {
        mPlayer_main_demo_wait_c* demo_wait_p = &GET_PLAYER_ACTOR_GAME(game)->main_data.demo_wait;

        if (demo_wait_p->label == (uintptr_t)label) {
            return TRUE;
        }
    }

    return FALSE;
}

extern void mPlib_Set_goal_player_demo_walk(f32 pos_x, f32 pos_z, f32 speed) {
    mDemo_Set_OrderValue(mDemo_ORDER_PLAYER, 2, (int)pos_x);
    mDemo_Set_OrderValue(mDemo_ORDER_PLAYER, 4, (int)pos_z);
    mDemo_Set_OrderValue(mDemo_ORDER_PLAYER, 7, (int)(speed * 100.0f));
}

extern void mPlib_Get_goal_player_demo_walk(f32* pos_x_p, f32* pos_z_p, f32* speed_p) {
    *pos_x_p = (f32)(int)mDemo_Get_OrderValue(mDemo_ORDER_PLAYER, 2);
    *pos_z_p = (f32)(int)mDemo_Get_OrderValue(mDemo_ORDER_PLAYER, 4);
    *speed_p = (f32)(int)mDemo_Get_OrderValue(mDemo_ORDER_PLAYER, 7) * 0.01f;
}

extern void mPlib_Set_continue_player_after_demo_walk(int value) {
    mDemo_Set_OrderValue(mDemo_ORDER_PLAYER, 8, value);
}

extern int mPlib_Get_continue_player_after_demo_walk(void) {
    return mDemo_Get_OrderValue(mDemo_ORDER_PLAYER, 8);
}

extern void mPlib_Set_end_player_demo_walk(int value) {
    mDemo_Set_OrderValue(mDemo_ORDER_PLAYER, 9, value);
}

extern int mPlib_Get_end_player_demo_walk(void) {
    return mDemo_Get_OrderValue(mDemo_ORDER_PLAYER, 9);
}

extern int mPlib_Get_space_putin_item(void) {
    return mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);
}

extern int mPlib_Get_space_putin_item_forTICKET(mActor_name_t* item_p) {
    mActor_name_t item = *item_p;

    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_TICKET) {
        int ticket_month = (item >> 3) & 0xF;
        int ticket_count = 1 + (item & 7);
        int ticket_begin = ITM_TICKET_START | (ticket_month << 3);
        int ticket_end = ticket_begin + (5 - ticket_count);
        int idx = mPr_GetPossessionItemIdxKindWithCond(Now_Private, ticket_begin, ticket_end, mPr_ITEM_COND_NORMAL);

        if (idx >= 0) {
            *item_p = Now_Private->inventory.pockets[idx] + ticket_count;
            return idx;
        }
    } else if (ITEM_IS_PAPER(item)) {
        int paper_base = item - ITM_PAPER_START;
        int paper_type = PAPER2TYPE(paper_base);
        int paper_num = PAPER2STACK(paper_base) + 1;
        int i;

        for (i = 4 - paper_num; i > 0; i--) {
            mActor_name_t paper_item = ITM_PAPER_START + paper_type + (i - 1) * PAPER_UNIQUE_NUM;
            int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, paper_item, mPr_ITEM_COND_NORMAL);

            if (idx != -1) {
                *item_p = (mActor_name_t)(ITM_PAPER_START + paper_type + (i + paper_num - 1) * PAPER_UNIQUE_NUM);
                return idx;
            }
        }
    }

    return mPlib_Get_space_putin_item();
}

extern int mPlib_Get_space_putin_item_forHITODAMA(mActor_name_t* item_p) {
    mActor_name_t item = *item_p;

    if (ITEM_IS_WISP(item)) {
        int hitodama_count = ITEM_IS_WISP(item) ? (1 + (item - ITM_SPIRIT0)) : 0;
        mActor_name_t hitodama_begin = ITM_SPIRIT0;
        mActor_name_t hitodama_end = hitodama_begin + (5 - hitodama_count);
        int idx = mPr_GetPossessionItemIdxKindWithCond(Now_Private, hitodama_begin, hitodama_end, mPr_ITEM_COND_NORMAL);

        if (idx >= 0) {
            *item_p = Now_Private->inventory.pockets[idx] + hitodama_count;
            return idx;
        }
    }

    return mPlib_Get_space_putin_item();
}

extern int mPlib_able_player_warp_forEvent(void) {
    if (mPlib_check_DynamicLinkFile_m_player() == FALSE) {
        return FALSE;
    }

    if (mPlib_check_player_warp_forEvent()) {
        return FALSE;
    }

    if (mEv_CheckFirstIntro()) {
        return FALSE;
    }

    if (Common_Get(player_actor_exists) == FALSE) {
        return FALSE;
    }

    if (Common_Get(complete_payment_type) != mPlayer_COMPLETE_PAYMENT_TYPE_NONE) {
        return FALSE;
    }

    if (Common_Get(fail_emu_flag) != FALSE) {
        return FALSE;
    }

    if (mPlib_Check_SetOrderSubmenu()) {
        return FALSE;
    }

    if (mPlib_check_request_change_item()) {
        return FALSE;
    }

    if (mPlib_check_priority_event_type1(gamePT)) {
        return GET_PLAYER_ACTOR_NOW()->check_cancel_event_without_priority_proc(gamePT) == FALSE;
    }

    if (mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_RELAX_ROD ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_READY_NET ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_READY_WALK_NET ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_HOLD ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_SITDOWN_WAIT ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_WAIT_BED ||
        mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_STRUGGLE_PITFALL) {
        if (GET_PLAYER_ACTOR_NOW()->requested_main_index_changed == FALSE) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mPlib_request_player_warp_forEvent(void) {
    Common_Set(player_warp_request, TRUE);
    return TRUE;
}

extern int mPlib_cancel_player_warp_forEvent(void) {
    Common_Set(player_warp_request, FALSE);
    return TRUE;
}

extern int mPlib_check_player_warp_forEvent(void) {
    return Common_Get(player_warp_request);
}

extern int mPlib_Check_HitAxe(xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_HitAxe_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

/**
 * @brief Checks if the player hit something with their axe in the same block
 * @param pos_p Position to check
 * @return TRUE if the player hit something with their axe in the same block, FALSE otherwise
 */
extern int mPlib_Check_VibUnit_OneFrame(const xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_VibUnit_OneFrame_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_Check_StopNet(xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_StopNet_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern uintptr_t mPlib_Get_item_net_catch_label(void) {
    return GET_PLAYER_ACTOR_NOW()->Get_item_net_catch_label_proc(GET_PLAYER_ACTOR_NOW_ACTOR());
}

extern int mPlib_Change_item_net_catch_label(uintptr_t label, s8 type) {
    return GET_PLAYER_ACTOR_NOW()->Change_item_net_catch_label_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), label, type);
}

extern int mPlib_Check_HitScoop(xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_HitScoop_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_Check_DigScoop(xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_DigScoop_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_Get_address_able_display(void) {
    return GET_PLAYER_ACTOR_NOW()->address_able_display;
}

static ACTOR* mPlib_Search_exist_npc_inCircle_forScoop(GAME* game, const xyz_t* pos_p, f32 radius_sq) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Actor_info* actor_info = &play->actor_info;
    Actor_list* npc_actor_list = &actor_info->list[ACTOR_PART_NPC];
    ACTOR* actor = npc_actor_list->actor;
    f32 pos_x = pos_p->x;
    f32 pos_z = pos_p->z;

    for (actor; actor != NULL; actor = actor->next_actor) {
        f32 dx = actor->world.position.x - pos_x;
        f32 dz = actor->world.position.z - pos_z;

        if (Math3DVecLengthSquare2D(dx, dz) < radius_sq) {
            NPC_ACTOR* npc_actor = (NPC_ACTOR*)actor;

            if (npc_actor->condition_info.hide_flg == FALSE) {
                return actor;
            }
        }
    }

    return NULL;
}

static ACTOR* mPlib_Search_exist_psnowman_inCircle_forScoop(GAME* game, const xyz_t* pos_p, f32 radius_sq) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Actor_info* actor_info = &play->actor_info;
    Actor_list* bg_actor_list = &actor_info->list[ACTOR_PART_BG];
    ACTOR* actor = bg_actor_list->actor;
    f32 pos_x = pos_p->x;
    f32 pos_z = pos_p->z;

    for (actor; actor != NULL; actor = actor->next_actor) {
        if (actor->id == mAc_PROFILE_PSNOWMAN) {
            f32 dx = actor->world.position.x - pos_x;
            f32 dz = actor->world.position.z - pos_z;

            if (Math3DVecLengthSquare2D(dx, dz) < radius_sq) {
                return actor;
            }
        }
    }

    return NULL;
}

static ACTOR* mPlib_Search_exist_snowball_forScoop(GAME* game, const xyz_t* pos_p) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Actor_info* actor_info = &play->actor_info;
    Actor_list* bg_actor_list = &actor_info->list[ACTOR_PART_BG];
    ACTOR* actor = bg_actor_list->actor;
    f32 pos_x = pos_p->x;
    f32 pos_y = pos_p->y;
    f32 pos_z = pos_p->z;

    for (actor; actor != NULL; actor = actor->next_actor) {
        if (actor->id == mAc_PROFILE_SNOWMAN) {
            SNOWMAN_ACTOR* snowball = (SNOWMAN_ACTOR*)actor;
            f32 dy = actor->world.position.y - pos_y;
            f32 abs_dy = ABS(dy);
            f32 radius = MIN(10.0f + 20.0f * snowball->normalized_scale, 19.0f);

            if (abs_dy <= 35.0f) {
                f32 dx = actor->world.position.x - pos_x;
                f32 dz = actor->world.position.z - pos_z;
                f32 len;
                f32 sq_radius;

                radius += 19.0f;
                len = Math3DVecLengthSquare2D(dx, dz);
                sq_radius = SQ(radius);

                if (len < sq_radius) {
                    return actor;
                }
            }
        }
    }

    return NULL;
}

static ACTOR* mPlib_Search_exist_ball_forScoop(GAME* game, const xyz_t* pos_p) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Actor_info* actor_info = &play->actor_info;
    Actor_list* bg_actor_list = &actor_info->list[ACTOR_PART_BG];
    ACTOR* actor = bg_actor_list->actor;
    f32 pos_x = pos_p->x;
    f32 pos_y = pos_p->y;
    f32 pos_z = pos_p->z;

    for (actor; actor != NULL; actor = actor->next_actor) {
        if (actor->id == mAc_PROFILE_BALL) {
            f32 dy = actor->world.position.y - pos_y;
            f32 abs_dy = ABS(dy);

            if (abs_dy <= 20.0f) {
                f32 dx = actor->world.position.x - pos_x;
                f32 dz = actor->world.position.z - pos_z;

                if (Math3DVecLengthSquare2D(dx, dz) < SQ(39.0f)) {
                    return actor;
                }
            }
        }
    }

    return NULL;
}

extern int mPlib_Check_scoop_after(GAME* game, xyz_t* pos_p, mActor_name_t* item_p, ACTOR** reflect_actor_pp,
                                   int gold_scoop) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    xyz_t* player_pos_p = &player_actor->world.position;
    int player_ux;
    int player_uz;
    int field_type = Common_Get(field_type);

    if (reflect_actor_pp != NULL) {
        *reflect_actor_pp = NULL;
    }

    *item_p = EMPTY_NO;

    if (field_type == mFI_FIELDTYPE2_FG) {
        if (mFI_Wpos2UtNum(&player_ux, &player_uz, *player_pos_p)) {
            // clang-format off
            static const int add_num[8][2] = {
                { -1, -1 },
                {  0, -1 },
                {  1, -1 },
                { -1,  0 },
            //  {  0,  0 }, <--- player pos
                {  1,  0 },
                { -1,  1 },
                {  0,  1 },
                {  1,  1 },
            };
            // clang-format on
            xyz_t unit_pos[8];
            int unit_num[8][2];
            int unit_exist[8];
            xyz_t center_ut_pos;
            xyz_t unit_dist[8];
            s16 unit_angle_y[8];
            int unit_abs_diff_angle_y[8];
            f32 player_pos_x = player_pos_p->x;
            f32 player_pos_y = player_pos_p->y;
            f32 player_pos_z = player_pos_p->z;
            int idx = 0;
            int min_angle_y;
            int player_angle_y;
            int i;

            mFI_UtNum2CenterWpos(&center_ut_pos, player_ux, player_uz);

            /* Get the center position for each surrounding unit and if it exists or not */
            for (i = 0; i < 8; i++) {
                unit_num[i][0] = player_ux + add_num[i][0];
                unit_num[i][1] = player_uz + add_num[i][1];
                unit_exist[i] = mFI_UtNum2CenterWpos(&unit_pos[i], unit_num[i][0], unit_num[i][1]);
                unit_pos[i].y = player_pos_y;

                if (unit_exist[i] == FALSE) {
                    unit_pos[i].x = center_ut_pos.x + unit_num[i][0] * mFI_UT_WORLDSIZE_X_F;
                    unit_pos[i].z = center_ut_pos.z + unit_num[i][1] * mFI_UT_WORLDSIZE_Z_F;
                }
            }

            /* Calculate distance and angle to center of each surrounding unit */
            for (i = 0; i < 8; i++) {
                unit_dist[i].x = unit_pos[i].x - player_pos_x;
                unit_dist[i].z = unit_pos[i].z - player_pos_z;
                unit_angle_y[i] = atans_table(unit_dist[i].z, unit_dist[i].x);
            }

            player_angle_y = player_actor->shape_info.rotation.y;
            min_angle_y = DEG2SHORT_ANGLE2(360.0f);

            /* Find the closest unit in relation to player's rotation */
            for (i = 0; i < 8; i++) {
                int diff_angle_y = unit_angle_y[i] - player_angle_y;

                unit_abs_diff_angle_y[i] = ABS(diff_angle_y);

                if (unit_abs_diff_angle_y[i] > DEG2SHORT_ANGLE2(180.0f)) {
                    unit_abs_diff_angle_y[i] = DEG2SHORT_ANGLE2(360.0f) - unit_abs_diff_angle_y[i];
                }

                if (min_angle_y > unit_abs_diff_angle_y[i]) {
                    min_angle_y = unit_abs_diff_angle_y[i];
                    idx = i;
                }
            }

            /* Special handling for diagonal units */
            if (idx == 0 || idx == 2 || idx == 5 || idx == 7) {
                int near_wall;
                int too_far_away = FALSE;
                int check_ut0;
                int check_ut1;
                int wall0 = FALSE;
                int wall1 = FALSE;
                f32 base_ut_y = mCoBG_GetBgY_OnlyCenter_FromWpos2(unit_pos[idx], 0.0f);

                if (idx == 0) {
                    check_ut0 = 1;
                    check_ut1 = 3;
                } else if (idx == 2) {
                    check_ut0 = 1;
                    check_ut1 = 4;
                } else if (idx == 5) {
                    check_ut0 = 3;
                    check_ut1 = 6;
                } else {
                    check_ut0 = 4;
                    check_ut1 = 6;
                }

                if (unit_exist[check_ut0]) {
                    f32 ground0 = mCoBG_GetBgY_OnlyCenter_FromWpos2(unit_pos[check_ut0], 0.0f);
                    f32 ground1 = mCoBG_Wpos2BgUtCenterHeight_AddColumn(unit_pos[check_ut0]);

                    /* If the base ground position and the 'column' height aren't the same, and our ground position is
                     * less than the 'column' height, there must be a wall in front of us. */
                    if (ground0 != ground1 && base_ut_y < ground1) {
                        wall0 = TRUE;
                    }
                }

                if (unit_exist[check_ut1]) {
                    f32 ground0 = mCoBG_GetBgY_OnlyCenter_FromWpos2(unit_pos[check_ut1], 0.0f);
                    f32 ground1 = mCoBG_Wpos2BgUtCenterHeight_AddColumn(unit_pos[check_ut1]);

                    /* If the base ground position and the 'column' height aren't the same, and our ground position is
                     * less than the 'column' height, there must be a wall in front of us. */
                    if (ground0 != ground1 && base_ut_y < ground1) {
                        wall1 = TRUE;
                    }
                }

                /* If both units diagonally have a wall then we've definitely hit a wall */
                if (wall0 && wall1) {
                    near_wall = TRUE;
                } else {
                    near_wall = FALSE;
                }

                if (near_wall == FALSE) {
                    f32 dist = Math3DVecLengthSquare2D(unit_dist[idx].z, unit_dist[idx].x);

                    if (SQ(63.245553f) > dist) {
                        too_far_away = FALSE;
                    } else {
                        too_far_away = TRUE;
                    }
                }

                if (too_far_away || near_wall) {
                    min_angle_y = DEG2SHORT_ANGLE2(360.0f);

                    if (min_angle_y > unit_abs_diff_angle_y[1]) {
                        min_angle_y = unit_abs_diff_angle_y[1];
                        idx = 1;
                    }

                    if (min_angle_y > unit_abs_diff_angle_y[3]) {
                        min_angle_y = unit_abs_diff_angle_y[3];
                        idx = 3;
                    }

                    if (min_angle_y > unit_abs_diff_angle_y[4]) {
                        min_angle_y = unit_abs_diff_angle_y[4];
                        idx = 4;
                    }

                    if (min_angle_y > unit_abs_diff_angle_y[6]) {
                        min_angle_y = unit_abs_diff_angle_y[6];
                        idx = 6;
                    }
                }
            }

            if (unit_exist[idx] == FALSE) {
                *pos_p = unit_pos[idx];
                return mPlayer_INDEX_AIR_SCOOP;
            } else {
                mActor_name_t* scoop_fg_p = mFI_UtNum2UtFG(unit_num[idx][0], unit_num[idx][1]);
                mActor_name_t scoop_fg = scoop_fg_p == NULL ? EMPTY_NO : *scoop_fg_p;
                int is_stump;
                int is_stone_tencoin;
                int is_tree;
                int is_rsv;
                int is_special_scoop_item;

                is_stump = FALSE;
                is_stone_tencoin = FALSE;
                is_tree = FALSE;
                is_rsv = FALSE;
                is_special_scoop_item = TRUE;

                if (IS_ITEM_TREE_STUMP(scoop_fg) != FALSE) {
                    is_stump = TRUE;
                } else if (IS_ITEM_STONE_TC(scoop_fg) != FALSE) {
                    is_stone_tencoin = TRUE;
                } else if (IS_ITEM_HITTABLE_TREE(scoop_fg) != FALSE) {
                    is_tree = TRUE;
                } else if (scoop_fg == DUMMY_RESERVE) {
                    is_rsv = TRUE;
                } else {
                    is_special_scoop_item = FALSE;
                }

                {
                    f32 diff_col_y;
                    f32 diff_pos_y;
                    f32 tmp_y;

                    unit_pos[idx].y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(unit_pos[idx]);
                    diff_col_y = unit_pos[idx].y - mCoBG_GetBgY_OnlyCenter_FromWpos2(unit_pos[idx], 0.0f);
                    diff_pos_y = unit_pos[idx].y - player_pos_p->y;
                    *pos_p = unit_pos[idx];

                    if (is_special_scoop_item && diff_pos_y > diff_col_y) {
                        return mPlayer_INDEX_REFLECT_SCOOP;
                    }

                    if (is_special_scoop_item && diff_pos_y < -diff_col_y) {
                        return mPlayer_INDEX_AIR_SCOOP;
                    }

                    if (!is_special_scoop_item && diff_pos_y > 63.245552f) {
                        return mPlayer_INDEX_REFLECT_SCOOP;
                    }

                    if (!is_special_scoop_item && diff_pos_y < -63.245552f) {
                        return mPlayer_INDEX_AIR_SCOOP;
                    }

                    if (is_stump || is_stone_tencoin || is_tree || is_rsv) {
                        pos_p->y = mCoBG_GetBgY_OnlyCenter_FromWpos2(*pos_p, 0.0f);
                        diff_pos_y = pos_p->y - player_pos_p->y;
                    }

                    {
                        xyz_t start_pos = *player_pos_p;
                        xyz_t end_pos = *pos_p;
                        xyz_t rev_pos;
                        xyz_t start2_pos = *player_pos_p;
                        xyz_t end2_pos = *pos_p;
                        xyz_t rev2_pos;
                        xyz_t rev3_pos;
                        xyz_t rev4_pos;

                        start_pos.y += 1.0f;
                        end_pos.y += 1.0f;
                        start2_pos.y -= 1.0f;
                        end2_pos.y -= 1.0f;

                        if (is_stump) {
                            mCoBG_LineCheck_RemoveFg(&rev_pos, start_pos, end_pos, &mNT_ItIsStump,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev3_pos, end_pos, start_pos, &mNT_ItIsStump,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev2_pos, start2_pos, end2_pos, &mNT_ItIsStump,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev4_pos, end2_pos, start2_pos, &mNT_ItIsStump,
                                                     mCoBG_LINE_CHECK_WALL);
                        } else if (is_stone_tencoin) {
                            mCoBG_LineCheck_RemoveFg(&rev_pos, start_pos, end_pos, &mNT_ItIsStoneCoin10,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev3_pos, end_pos, start_pos, &mNT_ItIsStoneCoin10,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev2_pos, start2_pos, end2_pos, &mNT_ItIsStoneCoin10,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev4_pos, end2_pos, start2_pos, &mNT_ItIsStoneCoin10,
                                                     mCoBG_LINE_CHECK_WALL);
                        } else if (is_rsv) {
                            mCoBG_LineCheck_RemoveFg(&rev_pos, start_pos, end_pos, &mNT_ItIsReserveDummy,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev3_pos, end_pos, start_pos, &mNT_ItIsReserveDummy,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev2_pos, start2_pos, end2_pos, &mNT_ItIsReserveDummy,
                                                     mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev4_pos, end2_pos, start2_pos, &mNT_ItIsReserveDummy,
                                                     mCoBG_LINE_CHECK_WALL);
                        } else if (!is_tree) {
                            mCoBG_LineCheck_RemoveFg(&rev_pos, start_pos, end_pos, NULL, mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev3_pos, end_pos, start_pos, NULL, mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev2_pos, start2_pos, end2_pos, NULL, mCoBG_LINE_CHECK_WALL);
                            mCoBG_LineCheck_RemoveFg(&rev4_pos, end2_pos, start2_pos, NULL, mCoBG_LINE_CHECK_WALL);
                        }

                        if (!is_tree) {
                            if (((rev_pos.x != 0.0f || rev_pos.y != 0.0f || rev_pos.z != 0.0f) &&
                                 (rev2_pos.x != 0.0f || rev2_pos.y != 0.0f || rev2_pos.z != 0.0f)) ||
                                ((rev3_pos.x != 0.0f || rev3_pos.y != 0.0f || rev3_pos.z != 0.0f) &&
                                 (rev4_pos.x != 0.0f || rev4_pos.y != 0.0f || rev4_pos.z != 0.0f))) {
                                if (diff_pos_y >= 0.0f) {
                                    return mPlayer_INDEX_REFLECT_SCOOP;
                                } else {
                                    return mPlayer_INDEX_AIR_SCOOP;
                                }
                            }
                        }

                        {
                            int dig_status;
                            int hit_flag = FALSE;
                            ACTOR* hit_actor_p;
                            mActor_name_t hit_item;

                            dig_status = mFI_GetDigStatus(&hit_item, *pos_p, gold_scoop);

                            /* Don't let the player hit NPCs with the shovel */
                            hit_actor_p = mPlib_Search_exist_npc_inCircle_forScoop(game, pos_p, SQ(39.0f));
                            if (hit_actor_p != NULL) {
#if VERSION >= VER_GAFU01_00
                                if (is_stone_tencoin) {
                                    *item_p = scoop_fg;
                                    return mPlayer_INDEX_REFLECT_SCOOP;
                                }
#endif

                                return mPlayer_INDEX_AIR_SCOOP;
                            }

                            hit_actor_p = mPlib_Search_exist_psnowman_inCircle_forScoop(game, pos_p, SQ(39.0f));
                            if (hit_actor_p != NULL) {
                                hit_flag = TRUE;
                            }

                            if (hit_actor_p == NULL) {
                                hit_actor_p = mPlib_Search_exist_snowball_forScoop(game, pos_p);
                                if (hit_actor_p != NULL) {
                                    hit_flag = TRUE;
                                }
                            }

                            if (hit_actor_p == NULL) {
                                hit_actor_p = mPlib_Search_exist_ball_forScoop(game, pos_p);
                                if (hit_actor_p != NULL) {
                                    hit_flag = TRUE;
                                }
                            }

                            if (reflect_actor_pp != NULL) {
                                *reflect_actor_pp = hit_actor_p;
                            }

                            if (scoop_fg != hit_item) {
                                *item_p = hit_item;
                            } else {
                                *item_p = scoop_fg;
                            }

                            if (is_tree) {
                                return mPlayer_INDEX_REFLECT_SCOOP;
                            }

                            if (is_rsv) {
                                return mPlayer_INDEX_REFLECT_SCOOP;
                            }

                            switch (dig_status) {
                                case mFI_DIGSTATUS_FILLIN:
                                    if (hit_flag) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else if (is_stone_tencoin) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else {
                                        return mPlayer_INDEX_FILL_SCOOP;
                                    }
                                    break;
                                case mFI_DIGSTATUS_DIG:
                                case mFI_DIGSTATUS_PUT_ITEM:
                                    if (hit_flag) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else if (is_stone_tencoin) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else {
                                        return mPlayer_INDEX_DIG_SCOOP;
                                    }
                                    break;
                                case mFI_DIGSTATUS_GET_ITEM:
                                    if (hit_flag) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else if (is_stone_tencoin) {
                                        return mPlayer_INDEX_REFLECT_SCOOP;
                                    } else {
                                        return mPlayer_INDEX_GET_SCOOP;
                                    }
                                    break;
                                case mFI_DIGSTATUS_MISS:
                                    return mPlayer_INDEX_AIR_SCOOP;
                                default:
                                    if (is_stone_tencoin) {
                                        *item_p = scoop_fg;
                                    }
                                    return mPlayer_INDEX_REFLECT_SCOOP;
                            }
                        }
                    }
                }
            }
        }
    }

    return -1;
}

extern int mPlib_Check_scene_able_change_camera_pos(void) {
    if (mFI_CheckFieldData()) {
        int field_type = mFI_GET_TYPE(mFI_GetFieldId());

        return (field_type == mFI_FIELD_NPCROOM0 || field_type == mFI_FIELD_PLAYER0_ROOM ||
                Save_Get(scene_no) == SCENE_MUSEUM_ROOM_FOSSIL || Save_Get(scene_no) == SCENE_MUSEUM_ROOM_PAINTING ||
                Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT || Save_Get(scene_no) == SCENE_MUSEUM_ROOM_FISH);
    }

    return FALSE;
}

extern int mPlib_Check_RotateOctagon(void) {
    return GET_PLAYER_ACTOR_NOW()->Check_RotateOctagon_proc(gamePT);
}

extern int mPlib_Set_EndWashCar(void) {
    if (mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_WASH_CAR) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
        mPlayer_main_wash_car_c* wash_car_p = &player->main_data.wash_car;

        wash_car_p->ret_order = TRUE;
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_Set_AnimeSpeedWashCar(f32 anime_speed) {
    if (mPlib_get_player_actor_main_index(gamePT) == mPlayer_INDEX_WASH_CAR) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();

        player->keyframe0.frame_control.speed = anime_speed;
        player->keyframe1.frame_control.speed = anime_speed;
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_Check_now_handin_item_kind(void) {
    return GET_PLAYER_ACTOR_NOW()->item_kind;
}

extern int mPlib_Check_now_handin_item(void) {
    return GET_PLAYER_ACTOR_NOW()->item_kind >= 0;
}

extern void mPlib_Set_able_hand_all_item_in_demo(s8 v) {
    GET_PLAYER_ACTOR_NOW()->able_hand_all_item_in_demo = v;
}

extern int mPlib_Get_status_for_bee(void) {
    return GET_PLAYER_ACTOR_NOW()->Get_status_for_bee_proc(GET_PLAYER_ACTOR_NOW_ACTOR());
}

extern int mPlib_Check_end_stung_bee(void) {
    return GET_PLAYER_ACTOR_NOW()->Check_end_stung_bee_proc(GET_PLAYER_ACTOR_NOW_ACTOR());
}

extern int mPlib_Check_Label_main_push_snowball(void* label) {
    return GET_PLAYER_ACTOR_NOW()->Check_Label_main_push_snowball_proc(gamePT, label);
}

extern int mPlib_Check_Label_main_wade_snowball(void* label) {
    return GET_PLAYER_ACTOR_NOW()->Check_Label_main_wade_snowball_proc(gamePT, label);
}

extern int mPlib_Set_ScrollDemo_forWade_snowball(int dir, const xyz_t* snowball_dist_p) {
    return GET_PLAYER_ACTOR_NOW()->Set_ScrollDemo_forWade_snowball_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), dir,
                                                                        snowball_dist_p);
}

extern int mPlib_GetSnowballPos_forWadeSnowball(xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->GetSnowballPos_forWadeSnowball_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_CheckCondition_forWadeSnowball(const xyz_t* pos_p, s16 angle_y) {
    return GET_PLAYER_ACTOR_NOW()->CheckCondition_forWadeSnowball_proc(gamePT, pos_p, angle_y);
}

extern int mPlib_SetParam_for_push_snowball(const xyz_t* pos_p, s16 angle_y, f32 anim_speed) {
    return GET_PLAYER_ACTOR_NOW()->SetParam_for_push_snowball_proc(gamePT, pos_p, angle_y, anim_speed);
}

extern void mPlib_Set_crash_snowball_for_wade(int v) {
    GET_PLAYER_ACTOR_NOW()->crash_snowball_for_wade = v;
}

static mPlayer_Controller_Data_c controller_data_for_title_demo;

extern mPlayer_Controller_Data_c* mPlib_Get_controller_data_for_title_demo_p(void) {
    return &controller_data_for_title_demo;
}

extern void mPlib_Clear_controller_data_for_title_demo(void) {
    bzero(&controller_data_for_title_demo, sizeof(controller_data_for_title_demo));
    controller_data_for_title_demo.equipped_item = ITM_PAPER_START; /* @BUG - this should be a tool, not paper */
}

extern void mPlib_SetData1_controller_data_for_title_demo(int btn_a, int btn_b, f32 stick_x, f32 stick_y) {
    mCon_calc(&controller_data_for_title_demo.mcon, stick_x, stick_y);

    if (controller_data_for_title_demo.trigger_btn_a == FALSE && btn_a != FALSE) {
        controller_data_for_title_demo.trigger_btn_a = TRUE;
    } else {
        controller_data_for_title_demo.trigger_btn_a = FALSE;
    }
    controller_data_for_title_demo.btn_a = btn_a;

    if (controller_data_for_title_demo.trigger_btn_b == FALSE && btn_b != FALSE) {
        controller_data_for_title_demo.trigger_btn_b = TRUE;
    } else {
        controller_data_for_title_demo.trigger_btn_b = FALSE;
    }
    controller_data_for_title_demo.btn_b = btn_b;
}

extern void mPlib_SetData2_controller_data_for_title_demo(mActor_name_t item) {
    controller_data_for_title_demo.equipped_item = item;
}

extern int mPlib_Check_CorrectPlayerPos_forEvent(void) {
    if (Common_Get(player_actor_exists)) {
        int main_index = GET_PLAYER_ACTOR_NOW()->now_main_index;

        if (mPlayer_MAIN_INDEX_VALID(main_index) != FALSE) {
            // clang-format off
            static const s8 data[] = {
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                TRUE,
                TRUE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
            };
            // clang-format on

            return data[main_index];
        }
    }

    return FALSE;
}

extern int mPlib_Check_UKI_COMEBACK_STATUS(void) {
    if (Common_Get(player_actor_exists)) {
        PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();

        if (player->fishing_rod_actor_p) {
            UKI_ACTOR* uki_actor = (UKI_ACTOR*)player->fishing_rod_actor_p;

            return uki_actor->status == aUKI_STATUS_COMEBACK;
        }
    }

    return FALSE;
}

extern int mPlib_Check_tree_shaken(const xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_tree_shaken_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_Check_tree_shaken_little(const xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_tree_shaken_little_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern int mPlib_Check_tree_shaken_big(const xyz_t* pos_p) {
    return GET_PLAYER_ACTOR_NOW()->Check_tree_shaken_big_proc(GET_PLAYER_ACTOR_NOW_ACTOR(), pos_p);
}

extern mActor_name_t mPlib_Get_itemNo_forWindow(void) {
    if (Common_Get(player_actor_exists) == FALSE) {
        return EMPTY_NO;
    }

    if (SubmenuArea_IsPlayer() == FALSE) {
        return EMPTY_NO;
    }

    return GET_PLAYER_ACTOR_NOW()->Get_itemNo_forWindow_proc(GET_PLAYER_ACTOR_NOW_ACTOR());
}

extern int mPlib_able_birth_bee(void) {
    if (mEv_CheckFirstIntro() != FALSE || Common_Get(reset_flag) != FALSE ||
        Common_Get(player_bee_chase_flag) != FALSE || mEv_IsTitleDemo()) {
        return FALSE;
    }

    return TRUE;
}

extern int mPlib_check_able_change_camera_normal_index(void) {
    if (Common_Get(player_actor_exists) == FALSE) {
        return EMPTY_NO;
    }

    if (SubmenuArea_IsPlayer() == FALSE) {
        return EMPTY_NO;
    }

    return GET_PLAYER_ACTOR_NOW()->check_able_change_camera_normal_index_proc(GET_PLAYER_ACTOR_NOW_ACTOR());
}

extern int mPlib_check_player_actor_main_index_Furniture_Move(GAME* game) {
    int res = FALSE;

    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUSH ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PULL) {
        res = TRUE;
    }

    return res;
}

extern int mPlib_check_player_actor_main_index_RecieveMove(GAME* game) {
    int res = FALSE;

    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RECIEVE_WAIT ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RECIEVE_STRETCH ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RECIEVE ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RECIEVE_PUTAWAY) {
        res = TRUE;
    }

    return res;
}

extern int mPlib_check_player_actor_main_index_Pitfall(GAME* game) {
    int res = FALSE;

    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_READY_PITFALL ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_FALL_PITFALL ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_STRUGGLE_PITFALL ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_CLIMBUP_PITFALL) {
        res = TRUE;
    }

    return res;
}

extern int mPlib_check_player_actor_main_index_OutDoorMove(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DMA ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_INTRO ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_OUTDOOR ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_COMPLETE_PAYMENT ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RETURN_OUTDOOR ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RETURN_OUTDOOR2 ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_TAKEOUT_ITEM) {
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_check_player_actor_main_index_OutDoorMove2(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DMA ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_INTRO ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_OUTDOOR ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_RETURN_OUTDOOR ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_COMPLETE_PAYMENT ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_TAKEOUT_ITEM) {
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_check_player_actor_main_index_AllWade(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_WADE ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DEMO_WADE ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_WADE_SNOWBALL ||
        mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_DEMO_GETON_BOAT_WADE) {
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_check_player_actor_main_index_catch_insect(GAME* game) {
    return (mPlib_Get_item_net_catch_label() != 0 &&
            mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_SWING_NET) ||
           mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PULL_NET ||
           mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_NOTICE_NET ||
           mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUTAWAY_NET;
}

extern int mPlib_check_player_actor_main_index_catch_fish(GAME* game) {
    return mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_FLY_ROD ||
           mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_NOTICE_ROD ||
           mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_PUTAWAY_ROD;
}

extern int mPlib_check_player_actor_start_switch_on_lighthouse(GAME* game) {
    if (mPlib_get_player_actor_main_index(game) == mPlayer_INDEX_SWITCH_ON_LIGHTHOUSE &&
        GET_PLAYER_ACTOR_GAME(game)->keyframe0.frame_control.current_frame > 1.0f) {
        return TRUE;
    }

    return FALSE;
}

extern int mPlib_Check_stung_mosquito(void* label) {
    return GET_PLAYER_ACTOR_NOW()->Check_stung_mosquito_proc(gamePT, label);
}

extern void mPlib_Set_boat_angleZ(s16 angle_z) {
    GET_PLAYER_ACTOR_NOW()->boat_angleZ = angle_z;
}

extern int mPlib_CheckButtonOnly_forDush(void) {
    return chkButton(BUTTON_B) || chkButton(BUTTON_L) || chkButton(BUTTON_R);
}

extern int mPlib_Check_golden_item_get_demo_end(int gold_item_type) {
    static u8 data[] = {
        (1 << mPlayer_GOLDEN_ITEM_TYPE_AXE),
        (1 << mPlayer_GOLDEN_ITEM_TYPE_NET),
        (1 << mPlayer_GOLDEN_ITEM_TYPE_ROD),
        (1 << mPlayer_GOLDEN_ITEM_TYPE_SHOVEL),
    };

    return data[gold_item_type] & Now_Private->golden_items_collected;
}

extern void mPlib_Set_change_color_request(void) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();

    player->change_color_request = TRUE;
}
