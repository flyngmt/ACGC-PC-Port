#include "m_player_lib.h"

#include "libultra/libultra.h"
#include "m_play.h"
#include "m_common_data.h"
#include "m_actor_shadow.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "ac_tools.h"
#include "m_rcp.h"
#include "ac_my_room.h"
#include "ac_insect.h"
#include "ac_set_ovl_insect.h"
#include "m_house.h"
#include "ac_sign.h"
#include "m_msg.h"
#include "m_choice.h"
#include "ac_ball.h"
#include "ac_snowman.h"
#include "ac_boat_demo.h"
#include "ac_balloon.h"
#include "ac_uki.h"
#include "ac_insect.h"
#include "ac_gyoei.h"
#include "ac_gyo_release.h"
#include "jsyswrap.h"
#include "ac_set_ovl_gyoei.h"
#include "m_vibctl.h"
#include "m_debug.h"

/* Static function declarations, add as needed for intellisense */
static void Player_actor_Item_Setup_main(ACTOR* actor, int now, int last);
static mActor_name_t Player_actor_Get_ItemNoSubmenu(void);
static int Player_actor_request_main_broken_axe_type_swing(GAME* game, xyz_t* pos, mActor_name_t hit_item,
                                                           int hit_ut_x, int hit_ut_z, int priority);
static int Player_actor_request_main_swing_axe_all(GAME* game, xyz_t* pos, mActor_name_t hit_item, u16 damage_no,
                                                   int hit_ut_x, int hit_ut_z, int priority);
static int Player_actor_request_main_broken_axe_type_reflect(GAME* game, xyz_t* pos, mActor_name_t hit_item,
                                                             ACTOR* hit_actor, int priority);
static int Player_actor_request_main_reflect_axe_all(GAME* game, xyz_t* pos, mActor_name_t hit_item,
                                                     u16 damage_no, ACTOR* hit_actor, int priority);
static int Player_actor_request_main_air_axe_all(GAME* game, int priority);
static int Player_actor_request_main_rotate_umbrella_all(GAME* game, int prio);
static int Player_actor_request_main_swing_fan_all(GAME* game, int start_swing, int prio);
static int Player_actor_request_main_wade_all(GAME* game, int dir, int priority);
static int Player_actor_request_main_demo_wade_all(GAME* game, int dir, int priority);
static int Player_actor_request_main_demo_geton_boat_wade_all(GAME* game, int dir, f32 border_ofs, int prio);
static int Player_actor_request_main_wade_snowball_all(GAME* game, int dir, const xyz_t* snowball_dist_p, int priority);
static int Player_actor_Check_ItemAnimationToItemKind(int kind, int anim);
static int Player_actor_request_main_dig_scoop_all(GAME* game, const xyz_t* pos, mActor_name_t name, int priority);
static int Player_actor_request_main_fill_scoop_all(GAME* game, const xyz_t* pos, int priority);
static int Player_actor_request_main_reflect_scoop_all(GAME* game, const xyz_t* pos, mActor_name_t item,
                                                       ACTOR* hit_actor, int priority);
static int Player_actor_request_main_air_scoop_all(GAME* game, int priority);
static int Player_actor_request_main_get_scoop_all(GAME* game, const xyz_t* pos, mActor_name_t item, int priority);
static int Player_actor_request_main_shake_tree_all(GAME* game, const xyz_t* target_pos_p, mActor_name_t item,
                                                    int tree_ut_x, int tree_ut_z, int priority);
static int Player_actor_request_main_ready_pitfall_all(GAME* game, const xyz_t* pos_p, int prio);
static int Player_actor_request_main_knock_door(GAME* game, const xyz_t* pos_p, s16 angle_y, int prio);
static s8 Player_actor_Get_ItemKind_fromScene(void);
static int Player_actor_request_main_putin_item(GAME* game, int priority);
static int Player_actor_request_main_takeout_item(GAME* game, int priority);
static void Player_actor_Refuse_pickup_demo_ct(ACTOR* actor);
static int Player_actor_request_main_pickup_jump(GAME* game, int slot_idx, mActor_name_t item, const xyz_t* item_pos_p,
                                                 int ftr_flag, int knife_and_fork_flag);
static int Player_actor_request_main_pickup_furniture(GAME* game, int slot_idx, mActor_name_t item,
                                                      const xyz_t* item_pos_p);
static int Player_actor_request_main_remove_grass(GAME* game, const xyz_t* target_pos_p, const xyz_t* grass_pos_p);
static int Player_actor_request_main_pickup(GAME* game, mActor_name_t item, const xyz_t* target_pos_p,
                                            const xyz_t* item_pos_p, int slot_idx, int signboard_flag);
static int Player_actor_request_main_radio_exercise_all(GAME* game, int cmd, f32 speed, int prio);
static void Player_actor_request_main_change_from_submenu(ACTOR* actorx, GAME* game);
static void Player_actor_request_change_item(GAME* game);
static int Player_actor_check_request_main_able(GAME* game, int request_main_index, int priority);
static void Player_actor_request_main_index(GAME* game, int request_index, int priority);
static void Player_actor_InitAnimation_Base1(ACTOR* actorx, GAME* game, int anim0_idx, int anim1_idx, f32 anim0_frame,
                                             f32 anim1_frame, f32 frame_speed, f32 morph_counter, int part_table_idx);
static void Player_actor_InitAnimation_Base2(ACTOR* actorx, GAME* game, int anim0_idx, int anim1_idx, f32 anim0_frame,
                                             f32 anim1_frame, f32 frame_speed, f32 morph_counter, int mode,
                                             int part_table_idx);
static void Player_actor_InitAnimation_Base3(ACTOR* actorx, GAME* game, int anim0_idx, int anim1_idx, f32 frame_speed,
                                             f32 morph_counter, int mode, int part_table_idx);
static void Player_actor_SetupItem_Base1(ACTOR* actorx, int anim1_idx, f32 item_morph_speed, int* anim1_idx_p,
                                         int* part_table_idx_p);
static void Player_actor_setup_main_Base(ACTOR* actorx, GAME* game);
static int Player_actor_Movement_Base_Braking_common(ACTOR* actorx, f32 brake_amount);
static int Player_actor_Movement_Base_Braking(ACTOR* actorx);
static void Player_actor_Movement_Base_Stop(ACTOR* actorx, int use_position_speed_y);
static int Player_actor_CulcAnimation_Base2(ACTOR* actorx, f32* last_anim0_current_frame_p);
static int Player_actor_Check_AnimationFrame_PerfectEquel(ACTOR* actorx, f32 frame);
static int Player_actor_Check_AnimationFrame(cKF_FrameControl_c* fc_p, f32 target_frame);
static void Player_actor_set_eye_pattern(ACTOR* actorx, int idx);
static void Player_actor_set_eye_pattern_normal(ACTOR* actorx);
static void Player_actor_set_mouth_pattern(ACTOR* actorx, int idx);
static void Player_actor_set_tex_anime_pattern(ACTOR* actorx);
static void Player_actor_Excute_Corect_forBrake(ACTOR* actorx, GAME* game);
static void Player_actor_Excute_Corect_forStand(ACTOR* actorx, GAME* game);
static void Player_actor_BGcheck_common_type1(ACTOR* actorx);
static void Player_actor_BGcheck_common_type2(ACTOR* actorx);
static void Player_actor_BGcheck_common_type3(ACTOR* actorx);
static int Player_actor_RecieveDemoOrder_EffectOrder(void);
static void Player_actor_Reinput_force_position_angle(ACTOR* actorx, GAME* game);
static void Player_actor_recover_lean_angle(ACTOR* actorx);
static int Player_actor_Check_TradingItemMode(u8 mode);
static void Player_actor_SettleRequestMainIndexPriority(ACTOR* actorx);
static int Player_actor_check_item_is_fish(mActor_name_t item);
static void Player_actor_Change_ItemParent(ACTOR* actor);
static void Player_actor_Set_item_matrix_set(ACTOR* actorx);
static void Player_actor_Unset_item_matrix_set(ACTOR* actorx);
static void Player_actor_Birth_TradingItem(ACTOR* actor, mActor_name_t item, int mode, int present_flag);
static void Player_actor_CHange_TradingItemMode(ACTOR* actorx, u8 mode);
static int Player_actor_Check_ItemParent(ACTOR* actor);
static ACTOR* Player_actor_Get_umbrella_p(ACTOR* actor, GAME* game);
static s8 Player_actor_Get_ItemKind(ACTOR* actor, int kind);
static void Player_actor_Set_now_item_main_index(ACTOR* actorx, int item_main_index);
static void Player_actor_SetEffect_forTakeout_item(ACTOR* actorx, GAME* game);
static void Player_actor_Set_FootMark_Base1(ACTOR* actorx, GAME* game, int disable_effect, int disable_sound);
static s8 Player_actor_Get_ItemKind_from_submenu(void);
static int Player_actor_Set_shake_tree_table(ACTOR* actorx, GAME* game, mActor_name_t item, int tree_ut_x,
                                             int tree_ut_z, int little_flag);
static int Player_actor_Check_BirthBee_common(ACTOR* actorx, mActor_name_t item, int tree_ut_x, int tree_ut_z,
                                              s16* angle_y_p);
static void Player_actor_Set_status_for_bee(ACTOR* actorx, s8 v);
static int Player_actor_check_able_request_main_index_for_reset(int request_main_index);
static void Player_actor_putin_item(int slot, mActor_name_t item, xyz_t* pos_p);
static void Player_actor_putin_item_layer2(int slot, mActor_name_t item, xyz_t* pos_p);
static void Player_actor_putin_furniture(GAME* game, int slot, mActor_name_t item);

static void Player_actor_sound_SetStatus(ACTOR* actor);
static void Player_actor_set_sound_common1(xyz_t* pos, u16 id);
static void Player_actor_set_sound_common2(ACTOR* actor, u16 id);
static void Player_actor_sound_FootStep1(ACTOR* actor, u16 id);
static void Player_actor_sound_FootStep2(ACTOR* actor);
static void Player_actor_sound_Tumble(ACTOR* actor);
static void Player_actor_sound_AMI_FURI(ACTOR* actor);
static void Player_actor_sound_AMI_HIT(ACTOR* actor);
static void Player_actor_sound_AMI_GET(ACTOR* actor);
static void Player_actor_sound_GASAGOSO(ACTOR* actor);
static void Player_actor_sound_AXE_FURI(ACTOR* actor);
static void Player_actor_sound_AXE_HIT(ACTOR* actor, xyz_t* pos);
static void Player_actor_sound_AXE_CUT(ACTOR* actor, xyz_t* pos);
static void Player_actor_sound_SIT(ACTOR* actor, int ftr_idx);
static void Player_actor_sound_STANDUP(ACTOR* actor, int ftr_idx);
static void Player_actor_sound_JUMP(ACTOR* actor);
static void Player_actor_sound_LANDING(ACTOR* actor);
static void Player_actor_sound_ITEM_GET(ACTOR* actor);
static void Player_actor_sound_BED_IN(ACTOR* actor);
static void Player_actor_sound_BED_NEGAERI(ACTOR* actor);
static void Player_actor_sound_BED_OUT(ACTOR* actor);
static void Player_actor_sound_ROD_STROKE(ACTOR* actor);
static void Player_actor_sound_ROD_STROKE_small(ACTOR* actor);
static void Player_actor_sound_ROD_BACK(ACTOR* actor);
static void Player_actor_sound_scoop1(ACTOR* actor);
static void Player_actor_sound_scoop_umeru(ACTOR* actor);
static void Player_actor_sound_scoop_hit(ACTOR* actor);
static void Player_actor_sound_scoop_shigemi(ACTOR* actor);
static void Player_actor_sound_ITEM_HORIDASHI(ACTOR* actor);
static void Player_actor_sound_slip(ACTOR* actor);
static void Player_actor_sound_tree_touch(xyz_t* pos);
static void Player_actor_sound_tree_yurasu(xyz_t* pos);
static void Player_actor_sound_kirikabu_scoop(ACTOR* actor);
static void Player_actor_sound_kirikabu_out(ACTOR* actor);
static void Player_actor_sound_knock(ACTOR* actor);
static void Player_actor_sound_coin_gasagoso(ACTOR* actor);
static void Player_actor_sound_araiiki(ACTOR* actor);
static void Player_actor_sound_zassou_nuku(xyz_t* pos);
static void Player_actor_sound_hachi_sasareru(ACTOR* actor);
static void Player_actor_sound_wear(ACTOR* actor);
static void Player_actor_sound_dai_ue_kakunou(ACTOR* actor);
static void Player_actor_sound_umbrella_rotate(ACTOR* actor);
static u8 Player_actor_sound_Get_bgm_num_forCompletePayment(void);
static u8 Player_actor_sound_Get_bgm_num_forDemoGetGoldenItem(int type);
static void Player_actor_sound_camera_move1(void);
static void Player_actor_sound_camera_move2();
static void Player_actor_sound_karaburi(ACTOR* actor);
static void Player_actor_sound_scoop_tree_hit(ACTOR* actor);
static void Player_actor_sound_scoop_item_hit(ACTOR* actor);
static void Player_actor_sound_axe_ball_hit(ACTOR* actor);
static void Player_actor_sound_axe_broken1(ACTOR* actor);
static void Player_actor_sound_axe_broken2(ACTOR* actor);
static void Player_actor_sound_axe_broken3(ACTOR* actor);
static void Player_actor_sound_uchiwa(ACTOR* actor);
static void Player_actor_sound_move_temochi_kazaguruma(ACTOR* actor);

static void Player_actor_set_viblation_Shake_tree(void);

static int Player_actor_Item_main(ACTOR* actorx, GAME* game);
static void Player_actor_LoadOrDestruct_Item(ACTOR* actor, int kind, int anim_idx, f32 speed, f32 morph_speed,
                                             f32 frame, int mode);
static int Player_actor_Get_BasicItemMainIndex_fromItemKind(int kind);

static int Player_actor_CheckController_forPickup(GAME* game);
static int Player_actor_CheckController_forAxe(GAME* game);
static int Player_actor_CheckController_forNet(GAME* game);
static int Player_actor_CheckController_forRod(GAME* game);
static int Player_actor_CheckController_forScoop(GAME* game);
static int Player_actor_CheckController_forUmbrella(GAME* game);
static int Player_actor_CheckController_forFan(GAME* game, int type);
static int Player_actor_CheckController_forShake_tree(GAME* game);
static f32 Player_actor_CheckController_forStruggle_pitfall(void);
static int Player_actor_CheckController_forDush(void);
static f32 Player_actor_GetController_move_percentX(void);
static f32 Player_actor_GetController_move_percentY(void);
static f32 Player_actor_GetController_move_percentR(void);
static s16 Player_actor_GetController_move_angle(void);
static s16 Player_actor_GetController_old_move_angle(void);
static f32 Player_actor_GetController_recognize_percentR(void);
static f32 Player_actor_GetController_old_recognize_percentR(void);
static int Player_actor_CheckController_forRadio_exercise(GAME* game);

static void Player_actor_ct_forCorect(ACTOR* actorx, GAME* game);
static void Player_actor_set_eye_pattern(ACTOR* actorx, int idx);
static void Player_actor_set_mouth_pattern(ACTOR* actorx, int idx);
static void Player_actor_Set_old_sound_frame_counter(ACTOR* actorx);
static void Player_actor_change_proc_index(ACTOR* actorx, GAME* game);

static int Player_actor_request_main_fail_emu(GAME* game, int prio);
static int Player_actor_request_main_intro_all(GAME* game, int prio);
static int Player_actor_request_main_wait_all(GAME* game, f32 morph_speed, f32 _04, int flags, int priority);

static int Player_actor_request_main_invade_all(GAME*, int);
// static int Player_actor_request_main_refuse(GAME*, int);
// static int Player_actor_request_main_return_demo_all(GAME*, int, f32, int);
// static int Player_actor_request_main_wait_all(GAME*, f32, f32, int, int);
static int Player_actor_request_main_talk_all(GAME*, ACTOR*, int, f32, int, int);
static int Player_actor_request_main_hold(GAME*, int, int, const xyz_t*, f32, int, int);
static int Player_actor_request_main_recieve_wait(GAME*, ACTOR*, int, int, mActor_name_t, int, int);
static int Player_actor_request_main_give_all(GAME*, ACTOR*, int, int, mActor_name_t, int, int, int, int);
static int Player_actor_request_main_sitdown(GAME*, int, const xyz_t*, int, int);
static int Player_actor_request_main_close_furniture(GAME*, int);
static int Player_actor_request_main_lie_bed(GAME*, int, const xyz_t*, int, int, int);
static int Player_actor_request_main_hide(GAME*, int);
static int Player_actor_request_main_groundhog(GAME*, int);
static int Player_actor_request_main_door(GAME*, const xyz_t*, s16, int, void*, int);
static int Player_actor_request_main_outdoor(GAME*, int, int, int);
static int Player_actor_request_main_wash_car_all(GAME*, const xyz_t*, const xyz_t*, s16, ACTOR*, int);
static int Player_actor_request_main_rotate_octagon_all(GAME*, ACTOR*, int, int, const xyz_t*, s16, int);
static int Player_actor_request_main_throw_money_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_pray_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_mail_jump_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_wait_all(GAME*, int, void*, int);
static int Player_actor_request_main_demo_walk_all(GAME*, f32, f32, f32, int, int);
static int Player_actor_request_main_demo_geton_train(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_getoff_train(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_standing_train_all(GAME*, int);
static int Player_actor_request_main_stung_bee_all(GAME*, int);
static int Player_actor_request_main_shock_all(GAME*, f32, s16, s8, int, int);
static int Player_actor_request_main_change_cloth_forNPC(GAME*, mActor_name_t, u16, int);
static int Player_actor_request_main_push_snowball_all(GAME*, void*, int, int);
static int Player_actor_request_main_stung_mosquito_all(GAME*, void*, int);
static int Player_actor_request_main_switch_on_lighthouse_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_geton_boat_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_getoff_boat_standup_all(GAME*, const xyz_t*, s16, int);
static int Player_actor_request_main_demo_get_golden_item2_all(GAME*, int, int);
static int Player_actor_request_main_demo_get_golden_axe_wait_all(GAME*, int);
static int Player_actor_check_request_main_priority(GAME*, int);
static void* Player_actor_get_door_label(GAME*);
static int Player_actor_Set_Item_net_catch_request_table(ACTOR*, GAME*, uintptr_t, s8, const xyz_t*, f32);
static f32 Player_actor_Get_Item_net_catch_swing_timer(ACTOR*, GAME*);
static int Player_actor_Set_Item_net_catch_request_force(ACTOR*, GAME*, uintptr_t, s8);
static void Player_actor_Set_force_position_angle(GAME*, const xyz_t*, const s_xyz*, u8);
static u8 Player_actor_Get_force_position_angle(GAME*, xyz_t*, s_xyz*);
static int Player_actor_Get_WadeEndPos(GAME*, xyz_t*);
static int Player_actor_Check_Label_main_push_snowball(GAME*, void*);
static int Player_actor_SetParam_for_push_snowball(GAME*, const xyz_t*, s16, f32);
static int Player_actor_able_submenu_request_main_index(GAME*);
static int Player_actor_check_able_change_camera_normal_index(ACTOR*);
static int Player_actor_Check_able_force_speak_label(GAME*, void*);
static int Player_actor_check_cancel_request_change_proc_index(int);
static uintptr_t Player_actor_Get_item_net_catch_label(ACTOR*);
static int Player_actor_Change_item_net_catch_label(ACTOR*, uintptr_t, s8);
static int Player_actor_Check_StopNet(ACTOR*, xyz_t*);
static int Player_actor_Check_HitAxe(ACTOR*, xyz_t*);
static int Player_actor_Check_VibUnit_OneFrame(ACTOR*, const xyz_t*);
static int Player_actor_Check_HitScoop(ACTOR*, xyz_t*);
static int Player_actor_Check_DigScoop(ACTOR*, xyz_t*);
static int Player_actor_check_request_change_item(GAME*);
static int Player_actor_Check_RotateOctagon(GAME*);
static int Player_actor_Check_end_stung_bee(ACTOR*);
static int Player_actor_Get_status_for_bee(ACTOR*);
static int Player_actor_Set_ScrollDemo_forWade_snowball(ACTOR*, int, const xyz_t*);
static int Player_actor_Check_tree_shaken(ACTOR*, const xyz_t*);
static int Player_actor_Check_tree_shaken_little(ACTOR*, const xyz_t*);
static int Player_actor_Check_tree_shaken_big(ACTOR*, const xyz_t*);
static int Player_actor_Check_Label_main_wade_snowball(GAME*, void*);
static int Player_actor_GetSnowballPos_forWadeSnowball(ACTOR*, xyz_t*);
static int Player_actor_CheckCondition_forWadeSnowball(GAME*, const xyz_t*, s16);
static mActor_name_t Player_actor_Get_itemNo_forWindow(ACTOR*);
static int Player_actor_check_cancel_event_without_priority(GAME*);
static int Player_actor_CheckScene_AbleSubmenu(void);
static int Player_actor_Check_stung_mosquito(GAME*, void*);

static int Player_actor_request_main_walk_all(GAME*, xyz_t*, f32, int, int);
static int Player_actor_request_main_run_all(GAME*, f32, int, int);
static int Player_actor_request_main_dash_all(GAME*, f32, int, int);
static int Player_actor_request_main_return_outdoor2_all(GAME* game, int prev_index, int now_index, f32 time, f32 arg5);
static int Player_actor_request_main_fall_all(GAME* game, f32 speed, int flags, int prio);
static int Player_actor_request_main_ready_net(GAME* game, int priority);
static int Player_actor_request_main_ready_rod(GAME* game, int priority);
static int Player_actor_request_main_slip_net(GAME* game, int priority);
static int Player_actor_request_main_turn_dash_all(GAME* game, s16 angle, int prio);
static int Player_actor_request_main_tumble(GAME* game, int priority);
static int Player_actor_request_main_tumble_getup(GAME* game, int prio);
static int Player_actor_request_main_release_creature_all(GAME* game, int type, int gold_scoop_flag,
                                                          mPlayer_request_release_creature_u* release_data,
                                                          ACTOR* release_actor_p, int prio);
static int Player_actor_request_main_complete_payment(GAME* game, int prio);
static int Player_actor_request_main_push(GAME* game, int ftr_no, s16 angle_y, xyz_t* pos, int priority);
static int Player_actor_request_main_pull(GAME* game, int ftr_no, s16 angle, const xyz_t* start_pos, const xyz_t* end_pos,
                                          const xyz_t* ofs, int priority);
static int Player_actor_request_main_rotate_furniture(GAME* game, int ftr_no, s16 angle, xyz_t* pos, int type,
                                                      int priority);
static int Player_actor_request_main_open_furniture(GAME* game, s16 angle, xyz_t* pos, int anim_idx, int priority);
static int Player_actor_request_main_wait_open_furniture(GAME* game, int priority);
static int Player_actor_request_main_wait_bed(GAME* game, int priority);
static int Player_actor_request_main_roll_bed(GAME* game, int direction, int priority);
static int Player_actor_request_main_standup_bed(GAME* game, int move_direction, int priority);
static int Player_actor_request_main_pickup_exchange(GAME* game, const xyz_t* target_pos_p, mActor_name_t item,
                                                     int priority);
static int Player_actor_request_main_demo_get_golden_item_all(GAME* game, int type, int prio);
static int Player_actor_request_main_sitdown_wait(GAME* game, int ftr_no, int priority);
static int Player_actor_request_main_standup(GAME* game, int ftr_no, int priority);
static int Player_actor_request_main_swing_net(GAME* game, int priority);
static int Player_actor_request_main_ready_walk_net(GAME* game, int priority);
static int Player_actor_request_main_pull_net(GAME* game, int priority);
static int Player_actor_request_main_stop_net(GAME* game, int priority);
static int Player_actor_request_main_notice_net(GAME* game, int already_collected, int priority);
static int Player_actor_request_main_putaway_net(GAME* game, int exchange_flag, int priority);
static int Player_actor_request_main_cast_rod(GAME* game, const xyz_t* pos, int priority);
static int Player_actor_request_main_air_rod(GAME* game, int priority);
static int Player_actor_request_main_relax_rod(GAME* game, int priority);
static int Player_actor_request_main_vib_rod(GAME* game, int priority);
static int Player_actor_request_main_collect_rod(GAME* game, int priority);
static int Player_actor_request_main_fly_rod(GAME* game, int priority);
static int Player_actor_request_main_notice_rod(GAME* game, s16 angle, int priority);
static int Player_actor_request_main_putaway_rod(GAME* game, s16 angle, int exchange_flag, int priority);
static int Player_actor_request_main_recieve_stretch(GAME* game, ACTOR* talk_actor_p, int turn_flag, int ret_main_index,
                                                     mActor_name_t item, int surface_flag, int priority);
static int Player_actor_request_main_recieve(GAME* game, ACTOR* talk_actor_p, int turn_flag, int ret_main_index,
                                             mActor_name_t item, int surface_flag, int priority);
static int Player_actor_request_main_recieve_putaway(GAME* game, ACTOR* talk_actor_p, int turn_flag, int ret_main_index,
                                                     mActor_name_t item, int surface_flag, int priority);
static int Player_actor_request_main_give_wait_all(GAME* game, ACTOR* talk_actor_p, int turn_flag, int ret_main_index,
                                                   mActor_name_t item, int surface_flag, int priority);
static int Player_actor_request_main_demo_geton_train_wait_all(GAME* game, int prio);
static int Player_actor_request_main_tired_all(GAME* game, int priority);
static int Player_actor_request_main_fall_pitfall_all(GAME* game, int prio);
static int Player_actor_request_main_struggle_pitfall_all(GAME* game, int prio);
static int Player_actor_request_main_climbup_pitfall_all(GAME* game, int prio);
static int Player_actor_request_main_notice_bee_all(GAME* game, int prio);
static int Player_actor_request_main_notice_mosquito(GAME* game, u32 label, int prio);
static int Player_actor_request_main_demo_geton_boat_sitdown_all(GAME* game, int prio);
static int Player_actor_request_main_demo_geton_boat_wait_all(GAME* game, int prio);
static int Player_actor_request_main_demo_getoff_boat_all(GAME* game, const xyz_t* pos_p, s16 angle_y, int prio);

/* Tool Models */
#include "../src/game/m_player_tools.c_inc"

/* Common */
#include "../src/game/m_player_controller.c_inc"
#include "../src/game/m_player_vibration.c_inc"
#include "../src/game/m_player_common.c_inc"
#include "../src/game/m_player_sound.c_inc"
#include "../src/game/m_player_other_func.c_inc"

/* Item */
#include "../src/game/m_player_item_common.c_inc"
#include "../src/game/m_player_item_axe.c_inc"
#include "../src/game/m_player_item_net.c_inc"
#include "../src/game/m_player_item_umbrella.c_inc"
#include "../src/game/m_player_item_rod.c_inc"
#include "../src/game/m_player_item_scoop.c_inc"
#include "../src/game/m_player_item_balloon.c_inc"
#include "../src/game/m_player_item_windmill.c_inc"
#include "../src/game/m_player_item_fan.c_inc"
#include "../src/game/m_player_item.c_inc"

/* Draw */
#include "../src/game/m_player_draw.c_inc"

/* Main Index */
#include "../src/game/m_player_main_dma.c_inc"
#include "../src/game/m_player_main_intro.c_inc"
#include "../src/game/m_player_main_refuse.c_inc"
#include "../src/game/m_player_main_refuse_pickup.c_inc"
#include "../src/game/m_player_main_return_demo.c_inc"
#include "../src/game/m_player_main_return_outdoor.c_inc"
#include "../src/game/m_player_main_return_outdoor2.c_inc"
#include "../src/game/m_player_main_wait.c_inc"
#include "../src/game/m_player_main_walk.c_inc"
#include "../src/game/m_player_main_run.c_inc"
#include "../src/game/m_player_main_dash.c_inc"
#include "../src/game/m_player_main_tumble.c_inc"
#include "../src/game/m_player_main_tumble_getup.c_inc"
#include "../src/game/m_player_main_turn_dash.c_inc"
#include "../src/game/m_player_main_fall.c_inc"
#include "../src/game/m_player_main_wade.c_inc"
#include "../src/game/m_player_main_wade_snowball.c_inc"
#include "../src/game/m_player_main_door.c_inc"
#include "../src/game/m_player_main_outdoor.c_inc"
#include "../src/game/m_player_main_invade.c_inc"
#include "../src/game/m_player_main_hold.c_inc"
#include "../src/game/m_player_main_push.c_inc"
#include "../src/game/m_player_main_pull.c_inc"
#include "../src/game/m_player_main_rotate_furniture.c_inc"
#include "../src/game/m_player_main_open_furniture.c_inc"
#include "../src/game/m_player_main_wait_open_furniture.c_inc"
#include "../src/game/m_player_main_close_furniture.c_inc"
#include "../src/game/m_player_main_lie_bed.c_inc"
#include "../src/game/m_player_main_wait_bed.c_inc"
#include "../src/game/m_player_main_roll_bed.c_inc"
#include "../src/game/m_player_main_standup_bed.c_inc"
#include "../src/game/m_player_main_pickup.c_inc"
#include "../src/game/m_player_main_pickup_jump.c_inc"
#include "../src/game/m_player_main_pickup_furniture.c_inc"
#include "../src/game/m_player_main_pickup_exchange.c_inc"
#include "../src/game/m_player_main_sitdown.c_inc"
#include "../src/game/m_player_main_sitdown_wait.c_inc"
#include "../src/game/m_player_main_standup.c_inc"
#include "../src/game/m_player_main_swing_axe.c_inc"
#include "../src/game/m_player_main_air_axe.c_inc"
#include "../src/game/m_player_main_reflect_axe.c_inc"
#include "../src/game/m_player_main_broken_axe.c_inc"
#include "../src/game/m_player_main_slip_net.c_inc"
#include "../src/game/m_player_main_ready_net.c_inc"
#include "../src/game/m_player_main_ready_walk_net.c_inc"
#include "../src/game/m_player_main_swing_net.c_inc"
#include "../src/game/m_player_main_pull_net.c_inc"
#include "../src/game/m_player_main_stop_net.c_inc"
#include "../src/game/m_player_main_notice_net.c_inc"
#include "../src/game/m_player_main_putaway_net.c_inc"
#include "../src/game/m_player_main_ready_rod.c_inc"
#include "../src/game/m_player_main_cast_rod.c_inc"
#include "../src/game/m_player_main_air_rod.c_inc"
#include "../src/game/m_player_main_relax_rod.c_inc"
#include "../src/game/m_player_main_collect_rod.c_inc"
#include "../src/game/m_player_main_vib_rod.c_inc"
#include "../src/game/m_player_main_fly_rod.c_inc"
#include "../src/game/m_player_main_notice_rod.c_inc"
#include "../src/game/m_player_main_putaway_rod.c_inc"
#include "../src/game/m_player_main_dig_scoop.c_inc"
#include "../src/game/m_player_main_fill_scoop.c_inc"
#include "../src/game/m_player_main_reflect_scoop.c_inc"
#include "../src/game/m_player_main_air_scoop.c_inc"
#include "../src/game/m_player_main_putin_scoop.c_inc"
#include "../src/game/m_player_main_putaway_scoop.c_inc"
#include "../src/game/m_player_main_get_scoop.c_inc"
#include "../src/game/m_player_main_talk.c_inc"
#include "../src/game/m_player_main_recieve_wait.c_inc"
#include "../src/game/m_player_main_recieve_stretch.c_inc"
#include "../src/game/m_player_main_recieve.c_inc"
#include "../src/game/m_player_main_recieve_putaway.c_inc"
#include "../src/game/m_player_main_give.c_inc"
#include "../src/game/m_player_main_give_wait.c_inc"
#include "../src/game/m_player_main_takeout_item.c_inc"
#include "../src/game/m_player_main_putin_item.c_inc"
#include "../src/game/m_player_main_demo_wait.c_inc"
#include "../src/game/m_player_main_demo_walk.c_inc"
#include "../src/game/m_player_main_demo_geton_train.c_inc"
#include "../src/game/m_player_main_demo_geton_train_wait.c_inc"
#include "../src/game/m_player_main_demo_getoff_train.c_inc"
#include "../src/game/m_player_main_demo_standing_train.c_inc"
#include "../src/game/m_player_main_demo_wade.c_inc"
#include "../src/game/m_player_main_hide.c_inc"
#include "../src/game/m_player_main_groundhog.c_inc"
#include "../src/game/m_player_main_release_creature.c_inc"
#include "../src/game/m_player_main_wash_car.c_inc"
#include "../src/game/m_player_main_tired.c_inc"
#include "../src/game/m_player_main_rotate_octagon.c_inc"
#include "../src/game/m_player_main_throw_money.c_inc"
#include "../src/game/m_player_main_pray.c_inc"
#include "../src/game/m_player_main_shake_tree.c_inc"
#include "../src/game/m_player_main_mail_jump.c_inc"
#include "../src/game/m_player_main_mail_land.c_inc"
#include "../src/game/m_player_main_ready_pitfall.c_inc"
#include "../src/game/m_player_main_fall_pitfall.c_inc"
#include "../src/game/m_player_main_struggle_pitfall.c_inc"
#include "../src/game/m_player_main_climbup_pitfall.c_inc"
#include "../src/game/m_player_main_stung_bee.c_inc"
#include "../src/game/m_player_main_notice_bee.c_inc"
#include "../src/game/m_player_main_remove_grass.c_inc"
#include "../src/game/m_player_main_shock.c_inc"
#include "../src/game/m_player_main_knock_door.c_inc"
#include "../src/game/m_player_main_change_cloth.c_inc"
#include "../src/game/m_player_main_push_snowball.c_inc"
#include "../src/game/m_player_main_rotate_umbrella.c_inc"
#include "../src/game/m_player_main_complete_payment.c_inc"
#include "../src/game/m_player_main_fail_emu.c_inc"
#include "../src/game/m_player_main_stung_mosquito.c_inc"
#include "../src/game/m_player_main_notice_mosquito.c_inc"
#include "../src/game/m_player_main_demo_geton_boat.c_inc"
#include "../src/game/m_player_main_swing_fan.c_inc"
#include "../src/game/m_player_main_switch_on_lighthouse.c_inc"
#include "../src/game/m_player_main_radio_exercise.c_inc"
#include "../src/game/m_player_main_demo_geton_boat_sitdown.c_inc"
#include "../src/game/m_player_main_demo_geton_boat_wait.c_inc"
#include "../src/game/m_player_main_demo_geton_boat_wade.c_inc"
#include "../src/game/m_player_main_demo_getoff_boat_standup.c_inc"
#include "../src/game/m_player_main_demo_getoff_boat.c_inc"
#include "../src/game/m_player_main_demo_get_golden_item.c_inc"
#include "../src/game/m_player_main_demo_get_golden_item2.c_inc"
#include "../src/game/m_player_main_demo_get_golden_axe_wait.c_inc"

// static void Player_actor_Refuse_pickup_demo_ct(ACTOR*);

static void Player_actor_init_value(ACTOR* actorx, GAME* game) {
    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;

    player->actor_class.gravity = -1.0f;
    player->actor_class.max_velocity_y = -8.0f;
    player->actor_class.scale.x = 0.01f;
    player->actor_class.scale.y = 0.01f;
    player->actor_class.scale.z = 0.01f;
    player->balloon_actor = Actor_info_make_actor(&((GAME_PLAY*)game)->actor_info, game, mAc_PROFILE_BALLOON,
                                                  actorx->world.position.x, actorx->world.position.y,
                                                  actorx->world.position.z, 0, 0, 0, -1, -1, -1, EMPTY_NO, -1, -1, -1);
    player->animation0_idx = -1;
    player->animation1_idx = -1;
    player->part_table_idx = -1;
    player->item_shape_type[0] = -1;
    player->item_shape_type[1] = -1;
    player->item_shape_type[2] = -1;
    player->item_shape_type[3] = -1;

    Player_actor_ct_forCorect(actorx, game);
    Player_actor_set_eye_pattern(actorx, 0);
    Player_actor_set_mouth_pattern(actorx, 0);

    player->request_main_invade_all_proc = &Player_actor_request_main_invade_all;
    player->request_main_refuse_all_proc = &Player_actor_request_main_refuse;
    player->request_main_return_demo_all_proc = &Player_actor_request_main_return_demo_all;
    player->request_main_wait_all_proc = &Player_actor_request_main_wait_all;
    player->request_main_talk_all_proc = &Player_actor_request_main_talk_all;
    player->request_main_hold_all_proc = &Player_actor_request_main_hold;
    player->request_main_recieve_wait_all_proc = &Player_actor_request_main_recieve_wait;
    player->request_main_give_all_proc = &Player_actor_request_main_give_all;
    player->request_main_sitdown_all_proc = &Player_actor_request_main_sitdown;
    player->request_main_close_furniture_all_proc = &Player_actor_request_main_close_furniture;
    player->request_main_lie_bed_all_proc = &Player_actor_request_main_lie_bed;
    player->request_main_hide_all_proc = &Player_actor_request_main_hide;
    player->request_main_groundhog_proc = &Player_actor_request_main_groundhog;
    player->request_main_door_all_proc = &Player_actor_request_main_door;
    player->request_main_outdoor_all_proc = &Player_actor_request_main_outdoor;
    player->request_main_demo_wait_all_proc = &Player_actor_request_main_demo_wait_all;
    player->request_main_demo_walk_all_proc = &Player_actor_request_main_demo_walk_all;
    player->request_main_demo_geton_train_all_proc = &Player_actor_request_main_demo_geton_train;
    player->request_main_demo_getoff_train_all_proc = &Player_actor_request_main_demo_getoff_train;
    player->request_main_demo_standing_train_all_proc = &Player_actor_request_main_demo_standing_train_all;
    player->request_main_rotate_octagon_all_proc = &Player_actor_request_main_rotate_octagon_all;
    player->request_main_wash_car_all_proc = &Player_actor_request_main_wash_car_all;
    player->request_main_throw_money_all_proc = &Player_actor_request_main_throw_money_all;
    player->request_main_pray_all_proc = &Player_actor_request_main_pray_all;
    player->request_main_mail_jump_all_proc = &Player_actor_request_main_mail_jump_all;
    player->request_main_stung_bee_all_proc = &Player_actor_request_main_stung_bee_all;
    player->request_main_shock_all_proc = &Player_actor_request_main_shock_all;
    player->request_main_change_cloth_forNPC_proc = &Player_actor_request_main_change_cloth_forNPC;
    player->request_main_push_snowball_all_proc = &Player_actor_request_main_push_snowball_all;
    player->request_main_stung_mosquito_all_proc = &Player_actor_request_main_stung_mosquito_all;
    player->request_main_switch_on_lighthouse_all_proc = &Player_actor_request_main_switch_on_lighthouse_all;
    player->request_main_demo_geton_boat_all_proc = &Player_actor_request_main_demo_geton_boat_all;
    player->request_main_demo_getoff_boat_standup_all_proc = &Player_actor_request_main_demo_getoff_boat_standup_all;
    player->request_main_demo_get_golden_item2_all_proc = &Player_actor_request_main_demo_get_golden_item2_all;
    player->request_main_demo_get_golden_axe_wait_all_proc = &Player_actor_request_main_demo_get_golden_axe_wait_all;
    player->check_request_main_priority_proc = &Player_actor_check_request_main_priority;
    player->get_door_label_proc = &Player_actor_get_door_label;
    player->Set_Item_net_catch_request_table_proc = &Player_actor_Set_Item_net_catch_request_table;
    player->Set_Item_net_catch_request_force_proc = &Player_actor_Set_Item_net_catch_request_force;
    player->Get_Item_net_catch_swing_timer_proc = &Player_actor_Get_Item_net_catch_swing_timer;
    player->Set_force_position_angle_proc = &Player_actor_Set_force_position_angle;
    player->Get_force_position_angle_proc = &Player_actor_Get_force_position_angle;
    player->Get_WadeEndPos_proc = &Player_actor_Get_WadeEndPos;
    player->check_cancel_request_change_proc_index_proc = &Player_actor_check_cancel_request_change_proc_index;
    player->Get_item_net_catch_label_proc = &Player_actor_Get_item_net_catch_label;
    player->Check_StopNet_proc = &Player_actor_Check_StopNet;
    player->Check_HitAxe_proc = &Player_actor_Check_HitAxe;
    player->Check_VibUnit_OneFrame_proc = &Player_actor_Check_VibUnit_OneFrame;
    player->Check_HitScoop_proc = &Player_actor_Check_HitScoop;
    player->Check_DigScoop_proc = &Player_actor_Check_DigScoop;
    player->check_request_change_item_proc = &Player_actor_check_request_change_item;
    player->Check_RotateOctagon_proc = &Player_actor_Check_RotateOctagon;
    player->Change_item_net_catch_label_proc = &Player_actor_Change_item_net_catch_label;
    player->Get_status_for_bee_proc = &Player_actor_Get_status_for_bee;
    player->Check_end_stung_bee_proc = &Player_actor_Check_end_stung_bee;
    player->Check_Label_main_push_snowball_proc = &Player_actor_Check_Label_main_push_snowball;
    player->Check_Label_main_wade_snowball_proc = &Player_actor_Check_Label_main_wade_snowball;
    player->SetParam_for_push_snowball_proc = &Player_actor_SetParam_for_push_snowball;
    player->Set_ScrollDemo_forWade_snowball_proc = &Player_actor_Set_ScrollDemo_forWade_snowball;
    player->GetSnowballPos_forWadeSnowball_proc = &Player_actor_GetSnowballPos_forWadeSnowball;
    player->CheckCondition_forWadeSnowball_proc = &Player_actor_CheckCondition_forWadeSnowball;
    player->Check_tree_shaken_proc = &Player_actor_Check_tree_shaken;
    player->Check_tree_shaken_little_proc = &Player_actor_Check_tree_shaken_little;
    player->Check_tree_shaken_big_proc = &Player_actor_Check_tree_shaken_big;
    player->Get_itemNo_forWindow_proc = &Player_actor_Get_itemNo_forWindow;
    player->able_submenu_request_main_index_proc = &Player_actor_able_submenu_request_main_index;
    player->check_able_change_camera_normal_index_proc = &Player_actor_check_able_change_camera_normal_index;
    player->CheckScene_AbleSubmenu_proc = &Player_actor_CheckScene_AbleSubmenu;
    player->check_cancel_event_without_priority_proc = &Player_actor_check_cancel_event_without_priority;
    player->Check_able_force_speak_label_proc = &Player_actor_Check_able_force_speak_label;
    player->Check_stung_mosquito_proc = &Player_actor_Check_stung_mosquito;

    {
        int* shake_tree_table_ut_x_p = player->shake_tree_ut_x;
        int* shake_tree_table_ut_z_p = player->shake_tree_ut_z;
        int i;

        for (i = 0; i < 3; i++) {
            *shake_tree_table_ut_x_p++ = -1;
            *shake_tree_table_ut_z_p++ = -1;
        }
    }

// TODO: I don't like this deviation between 1.3.2/US AC and 2.0/Aus AC
#if VERSION >= VER_GAFU01_00
    {
        int i;

        for (i = 0; i < 8; i++) {
            player->radio_exercise_command_ring_buffer[i] = -1;
        }
    }
#else
    {
        s8* radio_exercise_command_ring_buffer_p = player->radio_exercise_command_ring_buffer;
        int i;

        for (i = 0; i < 8; i++) {
            *radio_exercise_command_ring_buffer_p++ = -1;
        }
    }
#endif

    Player_actor_Set_old_sound_frame_counter(actorx);
}

extern void Player_actor_ct(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (mEv_IsTitleDemo()) {
        actorx->status_data.weight = 255;
    } else {
        actorx->status_data.weight = 50;
    }

    Player_actor_init_value(actorx, game);
    Common_Set(player_actor_exists, TRUE);
    Player_actor_Check_player_sunburn_for_ct(actorx); //
    mPlib_change_player_face(game);                   //
    Player_actor_ct_other_func1(actorx, game);        //
    Player_actor_set_eye_PositionAndAngle(actorx);    //
    Camera2_request_main_normal(play, 1, 1);
    Shape_Info_init(actorx, 0.0f, &mAc_ActorShadowCircle, 18.0f, 18.0f);
    actorx->shape_info.ofs_y = 200.0f;
    mPlib_Clear_change_data_from_submenu();       //
    Player_actor_request_main_dma(game, 41);      //
    Player_actor_change_proc_index(actorx, game); //
}

extern void Player_actor_dt(ACTOR* actorx, GAME* game) {
    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;

    Player_actor_dt_forCorect(actorx, game); //
    Common_Set(player_actor_exists, FALSE);
    mPlib_cancel_player_warp_forEvent();              //
    Player_actor_Reset_bee_chase(actorx);             //
    Player_actor_Check_player_sunburn_for_dt(actorx); //

    if (mEv_IsNotTitleDemo() && player->bgm_volume_mode != mPlayer_BGM_VOLUME_MODE_NORMAL) {
        switch (player->bgm_volume_mode) {
            case mPlayer_BGM_VOLUME_MODE_COLLECT_INSECTS:
                mBGMPsComp_volume_collect_insects_end();
                break;
            case mPlayer_BGM_VOLUME_MODE_FISHING:
                mBGMPsComp_volume_fishing_end();
                break;
        }
    }
}

typedef void (*mPlayer_REQUEST_MAIN_CHANGE_FROM_SUBMENU_PROC)(ACTOR*, GAME*);

// static void Player_actor_request_main_wait_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_putin_scoop_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_give_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_demo_wait_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_release_creature_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_mail_land_from_submenu(ACTOR*, GAME*);
static void Player_actor_request_main_demo_get_golden_item_from_submenu(ACTOR*, GAME*);

static void Player_actor_request_main_change_from_submenu(ACTOR* actorx, GAME* game) {
    static const mPlayer_REQUEST_MAIN_CHANGE_FROM_SUBMENU_PROC proc[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_wait_from_submenu,
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
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_putin_scoop_from_submenu,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_give_from_submenu,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_demo_wait_from_submenu,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_release_creature_from_submenu,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_request_main_mail_land_from_submenu,
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
        NULL,
        &Player_actor_request_main_demo_get_golden_item_from_submenu,
        NULL,
        NULL,
    };

    if (mPlib_Check_SetOrderSubmenu()) {
        mPlayer_change_data_from_submenu_c* data = mPlib_Get_change_data_from_submenu_p();
        int idx = data->requested_main_index;

        if (mPlayer_MAIN_INDEX_VALID(idx) == FALSE || proc[idx] == NULL) {
            return;
        }

        (*proc[idx])(actorx, game);
    }

    mPlib_Clear_change_data_from_submenu();
}

static void Player_actor_request_change_item(GAME* game) {
    int item_kind = Player_actor_check_request_change_item(game);

    switch (item_kind) {
        case mPlayer_ITEM_KIND_AXE_USE_7:
            Player_actor_request_main_wait_all(game, 0.0f, 0.0f, 1, 16);
            break;
        case mPlayer_ITEM_KIND_GOLD_AXE:
            Player_actor_request_main_walk_all(game, NULL, 0.0f, 1, 16);
            break;
        case mPlayer_ITEM_KIND_NET:
            Player_actor_request_main_run_all(game, 0.0f, 1, 16);
            break;
        case mPlayer_ITEM_KIND_GOLD_NET:
            Player_actor_request_main_dash_all(game, 0.0f, 1, 16);
            break;
    }
}

typedef void (*mPlayer_SETTLE_MAIN_PROC)(ACTOR*, GAME*);

static void Player_actor_settle_main_Walk(ACTOR*, GAME*);
static void Player_actor_settle_main_Turn_dash(ACTOR*, GAME*);
static void Player_actor_settle_main_Wade(ACTOR*, GAME*);
static void Player_actor_settle_main_Outdoor(ACTOR*, GAME*);
static void Player_actor_settle_main_Push(ACTOR*, GAME*);
static void Player_actor_settle_main_Pull(ACTOR*, GAME*);
static void Player_actor_settle_main_Open_furniture(ACTOR*, GAME*);
static void Player_actor_settle_main_Wait_open_furniture(ACTOR*, GAME*);
static void Player_actor_settle_main_Close_furniture(ACTOR*, GAME*);
static void Player_actor_settle_main_Lie_bed(ACTOR*, GAME*);
static void Player_actor_settle_main_Roll_bed(ACTOR*, GAME*);
static void Player_actor_settle_main_Standup_bed(ACTOR*, GAME*);
static void Player_actor_settle_main_Pickup_jump(ACTOR*, GAME*);
static void Player_actor_settle_main_Pickup_furniture(ACTOR*, GAME*);
static void Player_actor_settle_main_Pickup_exchange(ACTOR*, GAME*);
static void Player_actor_settle_main_Sitdown(ACTOR*, GAME*);
static void Player_actor_settle_main_Standup(ACTOR*, GAME*);
static void Player_actor_settle_main_Reflect_axe(ACTOR*, GAME*);
static void Player_actor_settle_main_Broken_axe(ACTOR*, GAME*);
static void Player_actor_settle_main_Slip_net(ACTOR*, GAME*);
static void Player_actor_settle_main_Swing_net(ACTOR*, GAME*);
static void Player_actor_settle_main_Notice_net(ACTOR*, GAME*);
static void Player_actor_settle_main_Collect_rod(ACTOR*, GAME*);
static void Player_actor_settle_main_Fly_rod(ACTOR*, GAME*);
static void Player_actor_settle_main_Notice_rod(ACTOR*, GAME*);
static void Player_actor_settle_main_Reflect_scoop(ACTOR*, GAME*);
static void Player_actor_settle_main_Get_scoop(ACTOR*, GAME*);
static void Player_actor_settle_main_Talk(ACTOR*, GAME*);
static void Player_actor_settle_main_Recieve_putaway(ACTOR*, GAME*);
static void Player_actor_settle_main_Give_wait(ACTOR*, GAME*);
static void Player_actor_settle_main_Takeout_item(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_wait(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_geton_train(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_getoff_train(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_wade(ACTOR*, GAME*);
static void Player_actor_settle_main_Release_creature(ACTOR*, GAME*);
static void Player_actor_settle_main_Wash_car(ACTOR*, GAME*);
static void Player_actor_settle_main_Rotate_octagon(ACTOR*, GAME*);
static void Player_actor_settle_main_Throw_money(ACTOR*, GAME*);
static void Player_actor_settle_main_Pray(ACTOR*, GAME*);
static void Player_actor_settle_main_Mail_jump(ACTOR*, GAME*);
static void Player_actor_settle_main_Ready_pitfall(ACTOR*, GAME*);
static void Player_actor_settle_main_Fall_pitfall(ACTOR*, GAME*);
static void Player_actor_settle_main_Struggle_pitfall(ACTOR*, GAME*);
static void Player_actor_settle_main_Climbup_pitfall(ACTOR*, GAME*);
static void Player_actor_settle_main_Notice_bee(ACTOR*, GAME*);
static void Player_actor_settle_main_Shock(ACTOR*, GAME*);
static void Player_actor_settle_main_Knock_door(ACTOR*, GAME*);
static void Player_actor_settle_main_Wade_snowball(ACTOR*, GAME*);
static void Player_actor_settle_main_Complete_payment(ACTOR*, GAME*);
static void Player_actor_settle_main_Fail_emu(ACTOR*, GAME*);
static void Player_actor_settle_main_Notice_mosquito(ACTOR*, GAME*);
static void Player_actor_settle_main_Switch_on_lighthouse(ACTOR*, GAME*);
static void Player_actor_settle_main_Radio_exercise(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_geton_boat(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_geton_boat_wade(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_getoff_boat_standup(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_getoff_boat(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_get_golden_item(ACTOR*, GAME*);
static void Player_actor_settle_main_Demo_get_golden_item2(ACTOR*, GAME*);

static void Player_actor_settle_main(ACTOR* actorx, GAME* game) {
    static const mPlayer_SETTLE_MAIN_PROC proc[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Walk,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Turn_dash,
        NULL,
        &Player_actor_settle_main_Wade,
        NULL,
        &Player_actor_settle_main_Outdoor,
        NULL,
        NULL,
        &Player_actor_settle_main_Push,
        &Player_actor_settle_main_Pull,
        NULL,
        &Player_actor_settle_main_Open_furniture,
        &Player_actor_settle_main_Wait_open_furniture,
        &Player_actor_settle_main_Close_furniture,
        &Player_actor_settle_main_Lie_bed,
        NULL,
        &Player_actor_settle_main_Roll_bed,
        &Player_actor_settle_main_Standup_bed,
        NULL,
        &Player_actor_settle_main_Pickup_jump,
        &Player_actor_settle_main_Pickup_furniture,
        &Player_actor_settle_main_Pickup_exchange,
        &Player_actor_settle_main_Sitdown,
        NULL,
        &Player_actor_settle_main_Standup,
        NULL,
        NULL,
        &Player_actor_settle_main_Reflect_axe,
        &Player_actor_settle_main_Broken_axe,
        &Player_actor_settle_main_Slip_net,
        NULL,
        NULL,
        &Player_actor_settle_main_Swing_net,
        NULL,
        NULL,
        &Player_actor_settle_main_Notice_net,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Collect_rod,
        NULL,
        &Player_actor_settle_main_Fly_rod,
        &Player_actor_settle_main_Notice_rod,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Reflect_scoop,
        NULL,
        &Player_actor_settle_main_Get_scoop,
        NULL,
        NULL,
        &Player_actor_settle_main_Talk,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Recieve_putaway,
        NULL,
        &Player_actor_settle_main_Give_wait,
        &Player_actor_settle_main_Takeout_item,
        NULL,
        &Player_actor_settle_main_Demo_wait,
        NULL,
        &Player_actor_settle_main_Demo_geton_train,
        NULL,
        &Player_actor_settle_main_Demo_getoff_train,
        NULL,
        &Player_actor_settle_main_Demo_wade,
        NULL,
        NULL,
        &Player_actor_settle_main_Release_creature,
        &Player_actor_settle_main_Wash_car,
        NULL,
        &Player_actor_settle_main_Rotate_octagon,
        &Player_actor_settle_main_Throw_money,
        &Player_actor_settle_main_Pray,
        NULL,
        &Player_actor_settle_main_Mail_jump,
        NULL,
        &Player_actor_settle_main_Ready_pitfall,
        &Player_actor_settle_main_Fall_pitfall,
        &Player_actor_settle_main_Struggle_pitfall,
        &Player_actor_settle_main_Climbup_pitfall,
        NULL,
        &Player_actor_settle_main_Notice_bee,
        NULL,
        &Player_actor_settle_main_Shock,
        &Player_actor_settle_main_Knock_door,
        NULL,
        NULL,
        NULL,
        &Player_actor_settle_main_Wade_snowball,
        &Player_actor_settle_main_Complete_payment,
        &Player_actor_settle_main_Fail_emu,
        NULL,
        &Player_actor_settle_main_Notice_mosquito,
        NULL,
        &Player_actor_settle_main_Switch_on_lighthouse,
        &Player_actor_settle_main_Radio_exercise,
        &Player_actor_settle_main_Demo_geton_boat,
        NULL,
        NULL,
        &Player_actor_settle_main_Demo_geton_boat_wade,
        &Player_actor_settle_main_Demo_getoff_boat_standup,
        &Player_actor_settle_main_Demo_getoff_boat,
        &Player_actor_settle_main_Demo_get_golden_item,
        &Player_actor_settle_main_Demo_get_golden_item2,
        NULL,
    };

    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;
    int idx = player->now_main_index;

    if (mPlayer_MAIN_INDEX_VALID(idx) != FALSE) {
        if (proc[idx] != NULL) {
            (*proc[idx])(actorx, game);
        }

        Player_actor_settle_main_other_func2(actorx, game); //
    }
}

typedef void (*mPlayer_SETUP_MAIN_PROC)(ACTOR*, GAME*);

static void Player_actor_setup_main_Dma(ACTOR*, GAME*);
static void Player_actor_setup_main_Intro(ACTOR*, GAME*);
static void Player_actor_setup_main_Refuse(ACTOR*, GAME*);
static void Player_actor_setup_main_Refuse_pickup(ACTOR*, GAME*);
static void Player_actor_setup_main_Return_demo(ACTOR*, GAME*);
static void Player_actor_setup_main_Return_outdoor(ACTOR*, GAME*);
static void Player_actor_setup_main_Return_outdoor2(ACTOR*, GAME*);
static void Player_actor_setup_main_Wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Walk(ACTOR*, GAME*);
static void Player_actor_setup_main_Run(ACTOR*, GAME*);
static void Player_actor_setup_main_Dash(ACTOR*, GAME*);
static void Player_actor_setup_main_Tumble(ACTOR*, GAME*);
static void Player_actor_setup_main_Tumble_getup(ACTOR*, GAME*);
static void Player_actor_setup_main_Turn_dash(ACTOR*, GAME*);
static void Player_actor_setup_main_Fall(ACTOR*, GAME*);
static void Player_actor_setup_main_Wade(ACTOR*, GAME*);
static void Player_actor_setup_main_Door(ACTOR*, GAME*);
static void Player_actor_setup_main_Outdoor(ACTOR*, GAME*);
static void Player_actor_setup_main_Invade(ACTOR*, GAME*);
static void Player_actor_setup_main_Hold(ACTOR*, GAME*);
static void Player_actor_setup_main_Push(ACTOR*, GAME*);
static void Player_actor_setup_main_Pull(ACTOR*, GAME*);
static void Player_actor_setup_main_Rotate_furniture(ACTOR*, GAME*);
static void Player_actor_setup_main_Open_furniture(ACTOR*, GAME*);
static void Player_actor_setup_main_Wait_open_furniture(ACTOR*, GAME*);
static void Player_actor_setup_main_Close_furniture(ACTOR*, GAME*);
static void Player_actor_setup_main_Lie_bed(ACTOR*, GAME*);
static void Player_actor_setup_main_Wait_bed(ACTOR*, GAME*);
static void Player_actor_setup_main_Roll_bed(ACTOR*, GAME*);
static void Player_actor_setup_main_Standup_bed(ACTOR*, GAME*);
static void Player_actor_setup_main_Pickup(ACTOR*, GAME*);
static void Player_actor_setup_main_Pickup_jump(ACTOR*, GAME*);
static void Player_actor_setup_main_Pickup_furniture(ACTOR*, GAME*);
static void Player_actor_setup_main_Pickup_exchange(ACTOR*, GAME*);
static void Player_actor_setup_main_Sitdown(ACTOR*, GAME*);
static void Player_actor_setup_main_Sitdown_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Standup(ACTOR*, GAME*);
static void Player_actor_setup_main_Swing_axe(ACTOR*, GAME*);
static void Player_actor_setup_main_Air_axe(ACTOR*, GAME*);
static void Player_actor_setup_main_Reflect_axe(ACTOR*, GAME*);
static void Player_actor_setup_main_Broken_axe(ACTOR*, GAME*);
static void Player_actor_setup_main_Slip_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Ready_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Ready_walk_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Swing_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Pull_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Stop_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Notice_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Putaway_net(ACTOR*, GAME*);
static void Player_actor_setup_main_Ready_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Cast_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Air_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Relax_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Collect_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Vib_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Fly_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Notice_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Putaway_rod(ACTOR*, GAME*);
static void Player_actor_setup_main_Dig_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Fill_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Reflect_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Air_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Get_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Putaway_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Putin_scoop(ACTOR*, GAME*);
static void Player_actor_setup_main_Talk(ACTOR*, GAME*);
static void Player_actor_setup_main_Recieve_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Recieve_stretch(ACTOR*, GAME*);
static void Player_actor_setup_main_Recieve(ACTOR*, GAME*);
static void Player_actor_setup_main_Recieve_putaway(ACTOR*, GAME*);
static void Player_actor_setup_main_Give(ACTOR*, GAME*);
static void Player_actor_setup_main_Give_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Takeout_item(ACTOR*, GAME*);
static void Player_actor_setup_main_Putin_item(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_walk(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_train(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_train_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_getoff_train(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_standing_train(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_wade(ACTOR*, GAME*);
static void Player_actor_setup_main_Hide(ACTOR*, GAME*);
static void Player_actor_setup_main_Groundhog(ACTOR*, GAME*);
static void Player_actor_setup_main_Release_creature(ACTOR*, GAME*);
static void Player_actor_setup_main_Wash_car(ACTOR*, GAME*);
static void Player_actor_setup_main_Tired(ACTOR*, GAME*);
static void Player_actor_setup_main_Rotate_octagon(ACTOR*, GAME*);
static void Player_actor_setup_main_Throw_money(ACTOR*, GAME*);
static void Player_actor_setup_main_Pray(ACTOR*, GAME*);
static void Player_actor_setup_main_Shake_tree(ACTOR*, GAME*);
static void Player_actor_setup_main_Mail_jump(ACTOR*, GAME*);
static void Player_actor_setup_main_Mail_land(ACTOR*, GAME*);
static void Player_actor_setup_main_Ready_pitfall(ACTOR*, GAME*);
static void Player_actor_setup_main_Fall_pitfall(ACTOR*, GAME*);
static void Player_actor_setup_main_Struggle_pitfall(ACTOR*, GAME*);
static void Player_actor_setup_main_Climbup_pitfall(ACTOR*, GAME*);
static void Player_actor_setup_main_Stung_bee(ACTOR*, GAME*);
static void Player_actor_setup_main_Notice_bee(ACTOR*, GAME*);
static void Player_actor_setup_main_Remove_grass(ACTOR*, GAME*);
static void Player_actor_setup_main_Shock(ACTOR*, GAME*);
static void Player_actor_setup_main_Knock_door(ACTOR*, GAME*);
static void Player_actor_setup_main_Change_cloth(ACTOR*, GAME*);
static void Player_actor_setup_main_Push_snowball(ACTOR*, GAME*);
static void Player_actor_setup_main_Rotate_umbrella(ACTOR*, GAME*);
static void Player_actor_setup_main_Wade_snowball(ACTOR*, GAME*);
static void Player_actor_setup_main_Complete_payment(ACTOR*, GAME*);
static void Player_actor_setup_main_Fail_emu(ACTOR*, GAME*);
static void Player_actor_setup_main_Stung_mosquito(ACTOR*, GAME*);
static void Player_actor_setup_main_Notice_mosquito(ACTOR*, GAME*);
static void Player_actor_setup_main_Swing_fan(ACTOR*, GAME*);
static void Player_actor_setup_main_Switch_on_lighthouse(ACTOR*, GAME*);
static void Player_actor_setup_main_Radio_exercise(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_boat(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_boat_sitdown(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_boat_wait(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_geton_boat_wade(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_getoff_boat_standup(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_getoff_boat(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_get_golden_item(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_get_golden_item2(ACTOR*, GAME*);
static void Player_actor_setup_main_Demo_get_golden_axe_wait(ACTOR*, GAME*);

static int Player_actor_change_main_index(ACTOR* actorx, GAME* game) {
    static const mPlayer_SETUP_MAIN_PROC proc[] = {
        &Player_actor_setup_main_Dma,
        &Player_actor_setup_main_Intro,
        &Player_actor_setup_main_Refuse,
        &Player_actor_setup_main_Refuse_pickup,
        &Player_actor_setup_main_Return_demo,
        &Player_actor_setup_main_Return_outdoor,
        &Player_actor_setup_main_Return_outdoor2,
        &Player_actor_setup_main_Wait,
        &Player_actor_setup_main_Walk,
        &Player_actor_setup_main_Run,
        &Player_actor_setup_main_Dash,
        &Player_actor_setup_main_Tumble,
        &Player_actor_setup_main_Tumble_getup,
        &Player_actor_setup_main_Turn_dash,
        &Player_actor_setup_main_Fall,
        &Player_actor_setup_main_Wade,
        &Player_actor_setup_main_Door,
        &Player_actor_setup_main_Outdoor,
        &Player_actor_setup_main_Invade,
        &Player_actor_setup_main_Hold,
        &Player_actor_setup_main_Push,
        &Player_actor_setup_main_Pull,
        &Player_actor_setup_main_Rotate_furniture,
        &Player_actor_setup_main_Open_furniture,
        &Player_actor_setup_main_Wait_open_furniture,
        &Player_actor_setup_main_Close_furniture,
        &Player_actor_setup_main_Lie_bed,
        &Player_actor_setup_main_Wait_bed,
        &Player_actor_setup_main_Roll_bed,
        &Player_actor_setup_main_Standup_bed,
        &Player_actor_setup_main_Pickup,
        &Player_actor_setup_main_Pickup_jump,
        &Player_actor_setup_main_Pickup_furniture,
        &Player_actor_setup_main_Pickup_exchange,
        &Player_actor_setup_main_Sitdown,
        &Player_actor_setup_main_Sitdown_wait,
        &Player_actor_setup_main_Standup,
        &Player_actor_setup_main_Swing_axe,
        &Player_actor_setup_main_Air_axe,
        &Player_actor_setup_main_Reflect_axe,
        &Player_actor_setup_main_Broken_axe,
        &Player_actor_setup_main_Slip_net,
        &Player_actor_setup_main_Ready_net,
        &Player_actor_setup_main_Ready_walk_net,
        &Player_actor_setup_main_Swing_net,
        &Player_actor_setup_main_Pull_net,
        &Player_actor_setup_main_Stop_net,
        &Player_actor_setup_main_Notice_net,
        &Player_actor_setup_main_Putaway_net,
        &Player_actor_setup_main_Ready_rod,
        &Player_actor_setup_main_Cast_rod,
        &Player_actor_setup_main_Air_rod,
        &Player_actor_setup_main_Relax_rod,
        &Player_actor_setup_main_Collect_rod,
        &Player_actor_setup_main_Vib_rod,
        &Player_actor_setup_main_Fly_rod,
        &Player_actor_setup_main_Notice_rod,
        &Player_actor_setup_main_Putaway_rod,
        &Player_actor_setup_main_Dig_scoop,
        &Player_actor_setup_main_Fill_scoop,
        &Player_actor_setup_main_Reflect_scoop,
        &Player_actor_setup_main_Air_scoop,
        &Player_actor_setup_main_Get_scoop,
        &Player_actor_setup_main_Putaway_scoop,
        &Player_actor_setup_main_Putin_scoop,
        &Player_actor_setup_main_Talk,
        &Player_actor_setup_main_Recieve_wait,
        &Player_actor_setup_main_Recieve_stretch,
        &Player_actor_setup_main_Recieve,
        &Player_actor_setup_main_Recieve_putaway,
        &Player_actor_setup_main_Give,
        &Player_actor_setup_main_Give_wait,
        &Player_actor_setup_main_Takeout_item,
        &Player_actor_setup_main_Putin_item,
        &Player_actor_setup_main_Demo_wait,
        &Player_actor_setup_main_Demo_walk,
        &Player_actor_setup_main_Demo_geton_train,
        &Player_actor_setup_main_Demo_geton_train_wait,
        &Player_actor_setup_main_Demo_getoff_train,
        &Player_actor_setup_main_Demo_standing_train,
        &Player_actor_setup_main_Demo_wade,
        &Player_actor_setup_main_Hide,
        &Player_actor_setup_main_Groundhog,
        &Player_actor_setup_main_Release_creature,
        &Player_actor_setup_main_Wash_car,
        &Player_actor_setup_main_Tired,
        &Player_actor_setup_main_Rotate_octagon,
        &Player_actor_setup_main_Throw_money,
        &Player_actor_setup_main_Pray,
        &Player_actor_setup_main_Shake_tree,
        &Player_actor_setup_main_Mail_jump,
        &Player_actor_setup_main_Mail_land,
        &Player_actor_setup_main_Ready_pitfall,
        &Player_actor_setup_main_Fall_pitfall,
        &Player_actor_setup_main_Struggle_pitfall,
        &Player_actor_setup_main_Climbup_pitfall,
        &Player_actor_setup_main_Stung_bee,
        &Player_actor_setup_main_Notice_bee,
        &Player_actor_setup_main_Remove_grass,
        &Player_actor_setup_main_Shock,
        &Player_actor_setup_main_Knock_door,
        &Player_actor_setup_main_Change_cloth,
        &Player_actor_setup_main_Push_snowball,
        &Player_actor_setup_main_Rotate_umbrella,
        &Player_actor_setup_main_Wade_snowball,
        &Player_actor_setup_main_Complete_payment,
        &Player_actor_setup_main_Fail_emu,
        &Player_actor_setup_main_Stung_mosquito,
        &Player_actor_setup_main_Notice_mosquito,
        &Player_actor_setup_main_Swing_fan,
        &Player_actor_setup_main_Switch_on_lighthouse,
        &Player_actor_setup_main_Radio_exercise,
        &Player_actor_setup_main_Demo_geton_boat,
        &Player_actor_setup_main_Demo_geton_boat_sitdown,
        &Player_actor_setup_main_Demo_geton_boat_wait,
        &Player_actor_setup_main_Demo_geton_boat_wade,
        &Player_actor_setup_main_Demo_getoff_boat_standup,
        &Player_actor_setup_main_Demo_getoff_boat,
        &Player_actor_setup_main_Demo_get_golden_item,
        &Player_actor_setup_main_Demo_get_golden_item2,
        &Player_actor_setup_main_Demo_get_golden_axe_wait,
    };
    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;

    if (player->requested_main_index_changed) {
        int idx = player->requested_main_index;

        if (mPlayer_MAIN_INDEX_VALID(idx) == FALSE || proc[idx] == NULL) {
            return FALSE;
        }

        idx = Player_actor_CheckAndRequest_KnockDoor(actorx, game,
                                                     Player_actor_CheckAndRequest_ItemInOut(actorx, game, idx)); //
        Player_actor_Set_bgm_volume(actorx, idx);                                                                //
        Player_actor_settle_main(actorx, game);
        Player_actor_Reset_unable_hand_item_in_demo(actorx, idx);   //
        Player_actor_Reset_able_hand_all_item_in_demo(actorx, idx); //
        Player_actor_Reset_able_force_speak_label(actorx, idx);     //
        Player_actor_change_main_index_other_func1(actorx, game);   //
        (*proc[idx])(actorx, game);
        Player_actor_change_main_index_other_func2(actorx, game); //
        return TRUE;
    }

    return FALSE;
}

static void Player_actor_change_proc_index(ACTOR* actorx, GAME* game) {
    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;

    player->changed_main_index = Player_actor_change_main_index(actorx, game);
}

typedef void (*mPlayer_MAIN_PROC)(ACTOR*, GAME*);

static void Player_actor_main_Dma(ACTOR*, GAME*);
static void Player_actor_main_Intro(ACTOR*, GAME*);
static void Player_actor_main_Refuse(ACTOR*, GAME*);
static void Player_actor_main_Refuse_pickup(ACTOR*, GAME*);
static void Player_actor_main_Return_demo(ACTOR*, GAME*);
static void Player_actor_main_Return_outdoor(ACTOR*, GAME*);
static void Player_actor_main_Return_outdoor2(ACTOR*, GAME*);
static void Player_actor_main_Wait(ACTOR*, GAME*);
static void Player_actor_main_Walk(ACTOR*, GAME*);
static void Player_actor_main_Run(ACTOR*, GAME*);
static void Player_actor_main_Dash(ACTOR*, GAME*);
static void Player_actor_main_Tumble(ACTOR*, GAME*);
static void Player_actor_main_Tumble_getup(ACTOR*, GAME*);
static void Player_actor_main_Turn_dash(ACTOR*, GAME*);
static void Player_actor_main_Fall(ACTOR*, GAME*);
static void Player_actor_main_Wade(ACTOR*, GAME*);
static void Player_actor_main_Door(ACTOR*, GAME*);
static void Player_actor_main_Outdoor(ACTOR*, GAME*);
static void Player_actor_main_Invade(ACTOR*, GAME*);
static void Player_actor_main_Hold(ACTOR*, GAME*);
static void Player_actor_main_Push(ACTOR*, GAME*);
static void Player_actor_main_Pull(ACTOR*, GAME*);
static void Player_actor_main_Rotate_furniture(ACTOR*, GAME*);
static void Player_actor_main_Open_furniture(ACTOR*, GAME*);
static void Player_actor_main_Wait_open_furniture(ACTOR*, GAME*);
static void Player_actor_main_Close_furniture(ACTOR*, GAME*);
static void Player_actor_main_Lie_bed(ACTOR*, GAME*);
static void Player_actor_main_Wait_bed(ACTOR*, GAME*);
static void Player_actor_main_Roll_bed(ACTOR*, GAME*);
static void Player_actor_main_Standup_bed(ACTOR*, GAME*);
static void Player_actor_main_Pickup(ACTOR*, GAME*);
static void Player_actor_main_Pickup_jump(ACTOR*, GAME*);
static void Player_actor_main_Pickup_furniture(ACTOR*, GAME*);
static void Player_actor_main_Pickup_exchange(ACTOR*, GAME*);
static void Player_actor_main_Sitdown(ACTOR*, GAME*);
static void Player_actor_main_Sitdown_wait(ACTOR*, GAME*);
static void Player_actor_main_Standup(ACTOR*, GAME*);
static void Player_actor_main_Swing_axe(ACTOR*, GAME*);
static void Player_actor_main_Air_axe(ACTOR*, GAME*);
static void Player_actor_main_Reflect_axe(ACTOR*, GAME*);
static void Player_actor_main_Broken_axe(ACTOR*, GAME*);
static void Player_actor_main_Slip_net(ACTOR*, GAME*);
static void Player_actor_main_Ready_net(ACTOR*, GAME*);
static void Player_actor_main_Ready_walk_net(ACTOR*, GAME*);
static void Player_actor_main_Swing_net(ACTOR*, GAME*);
static void Player_actor_main_Pull_net(ACTOR*, GAME*);
static void Player_actor_main_Stop_net(ACTOR*, GAME*);
static void Player_actor_main_Notice_net(ACTOR*, GAME*);
static void Player_actor_main_Putaway_net(ACTOR*, GAME*);
static void Player_actor_main_Ready_rod(ACTOR*, GAME*);
static void Player_actor_main_Cast_rod(ACTOR*, GAME*);
static void Player_actor_main_Air_rod(ACTOR*, GAME*);
static void Player_actor_main_Relax_rod(ACTOR*, GAME*);
static void Player_actor_main_Collect_rod(ACTOR*, GAME*);
static void Player_actor_main_Vib_rod(ACTOR*, GAME*);
static void Player_actor_main_Fly_rod(ACTOR*, GAME*);
static void Player_actor_main_Notice_rod(ACTOR*, GAME*);
static void Player_actor_main_Putaway_rod(ACTOR*, GAME*);
static void Player_actor_main_Dig_scoop(ACTOR*, GAME*);
static void Player_actor_main_Fill_scoop(ACTOR*, GAME*);
static void Player_actor_main_Reflect_scoop(ACTOR*, GAME*);
static void Player_actor_main_Air_scoop(ACTOR*, GAME*);
static void Player_actor_main_Get_scoop(ACTOR*, GAME*);
static void Player_actor_main_Putaway_scoop(ACTOR*, GAME*);
static void Player_actor_main_Putin_scoop(ACTOR*, GAME*);
static void Player_actor_main_Talk(ACTOR*, GAME*);
static void Player_actor_main_Recieve_wait(ACTOR*, GAME*);
static void Player_actor_main_Recieve_stretch(ACTOR*, GAME*);
static void Player_actor_main_Recieve(ACTOR*, GAME*);
static void Player_actor_main_Recieve_putaway(ACTOR*, GAME*);
static void Player_actor_main_Give(ACTOR*, GAME*);
static void Player_actor_main_Give_wait(ACTOR*, GAME*);
static void Player_actor_main_Takeout_item(ACTOR*, GAME*);
static void Player_actor_main_Putin_item(ACTOR*, GAME*);
static void Player_actor_main_Demo_wait(ACTOR*, GAME*);
static void Player_actor_main_Demo_walk(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_train(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_train_wait(ACTOR*, GAME*);
static void Player_actor_main_Demo_getoff_train(ACTOR*, GAME*);
static void Player_actor_main_Demo_standing_train(ACTOR*, GAME*);
static void Player_actor_main_Demo_wade(ACTOR*, GAME*);
static void Player_actor_main_Hide(ACTOR*, GAME*);
static void Player_actor_main_Groundhog(ACTOR*, GAME*);
static void Player_actor_main_Release_creature(ACTOR*, GAME*);
static void Player_actor_main_Wash_car(ACTOR*, GAME*);
static void Player_actor_main_Tired(ACTOR*, GAME*);
static void Player_actor_main_Rotate_octagon(ACTOR*, GAME*);
static void Player_actor_main_Throw_money(ACTOR*, GAME*);
static void Player_actor_main_Pray(ACTOR*, GAME*);
static void Player_actor_main_Shake_tree(ACTOR*, GAME*);
static void Player_actor_main_Mail_jump(ACTOR*, GAME*);
static void Player_actor_main_Mail_land(ACTOR*, GAME*);
static void Player_actor_main_Ready_pitfall(ACTOR*, GAME*);
static void Player_actor_main_Fall_pitfall(ACTOR*, GAME*);
static void Player_actor_main_Struggle_pitfall(ACTOR*, GAME*);
static void Player_actor_main_Climbup_pitfall(ACTOR*, GAME*);
static void Player_actor_main_Stung_bee(ACTOR*, GAME*);
static void Player_actor_main_Notice_bee(ACTOR*, GAME*);
static void Player_actor_main_Remove_grass(ACTOR*, GAME*);
static void Player_actor_main_Shock(ACTOR*, GAME*);
static void Player_actor_main_Knock_door(ACTOR*, GAME*);
static void Player_actor_main_Change_cloth(ACTOR*, GAME*);
static void Player_actor_main_Push_snowball(ACTOR*, GAME*);
static void Player_actor_main_Rotate_umbrella(ACTOR*, GAME*);
static void Player_actor_main_Wade_snowball(ACTOR*, GAME*);
static void Player_actor_main_Complete_payment(ACTOR*, GAME*);
static void Player_actor_main_Fail_emu(ACTOR*, GAME*);
static void Player_actor_main_Stung_mosquito(ACTOR*, GAME*);
static void Player_actor_main_Notice_mosquito(ACTOR*, GAME*);
static void Player_actor_main_Swing_fan(ACTOR*, GAME*);
static void Player_actor_main_Switch_on_lighthouse(ACTOR*, GAME*);
static void Player_actor_main_Radio_exercise(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_boat(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_boat_sitdown(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_boat_wait(ACTOR*, GAME*);
static void Player_actor_main_Demo_geton_boat_wade(ACTOR*, GAME*);
static void Player_actor_main_Demo_getoff_boat_standup(ACTOR*, GAME*);
static void Player_actor_main_Demo_getoff_boat(ACTOR*, GAME*);
static void Player_actor_main_Demo_get_golden_item(ACTOR*, GAME*);
static void Player_actor_main_Demo_get_golden_item2(ACTOR*, GAME*);
static void Player_actor_main_Demo_get_golden_axe_wait(ACTOR*, GAME*);

extern void Player_actor_move(ACTOR* actorx, GAME* game) {
    static const mPlayer_MAIN_PROC proc[] = {
        &Player_actor_main_Dma,
        &Player_actor_main_Intro,
        &Player_actor_main_Refuse,
        &Player_actor_main_Refuse_pickup,
        &Player_actor_main_Return_demo,
        &Player_actor_main_Return_outdoor,
        &Player_actor_main_Return_outdoor2,
        &Player_actor_main_Wait,
        &Player_actor_main_Walk,
        &Player_actor_main_Run,
        &Player_actor_main_Dash,
        &Player_actor_main_Tumble,
        &Player_actor_main_Tumble_getup,
        &Player_actor_main_Turn_dash,
        &Player_actor_main_Fall,
        &Player_actor_main_Wade,
        &Player_actor_main_Door,
        &Player_actor_main_Outdoor,
        &Player_actor_main_Invade,
        &Player_actor_main_Hold,
        &Player_actor_main_Push,
        &Player_actor_main_Pull,
        &Player_actor_main_Rotate_furniture,
        &Player_actor_main_Open_furniture,
        &Player_actor_main_Wait_open_furniture,
        &Player_actor_main_Close_furniture,
        &Player_actor_main_Lie_bed,
        &Player_actor_main_Wait_bed,
        &Player_actor_main_Roll_bed,
        &Player_actor_main_Standup_bed,
        &Player_actor_main_Pickup,
        &Player_actor_main_Pickup_jump,
        &Player_actor_main_Pickup_furniture,
        &Player_actor_main_Pickup_exchange,
        &Player_actor_main_Sitdown,
        &Player_actor_main_Sitdown_wait,
        &Player_actor_main_Standup,
        &Player_actor_main_Swing_axe,
        &Player_actor_main_Air_axe,
        &Player_actor_main_Reflect_axe,
        &Player_actor_main_Broken_axe,
        &Player_actor_main_Slip_net,
        &Player_actor_main_Ready_net,
        &Player_actor_main_Ready_walk_net,
        &Player_actor_main_Swing_net,
        &Player_actor_main_Pull_net,
        &Player_actor_main_Stop_net,
        &Player_actor_main_Notice_net,
        &Player_actor_main_Putaway_net,
        &Player_actor_main_Ready_rod,
        &Player_actor_main_Cast_rod,
        &Player_actor_main_Air_rod,
        &Player_actor_main_Relax_rod,
        &Player_actor_main_Collect_rod,
        &Player_actor_main_Vib_rod,
        &Player_actor_main_Fly_rod,
        &Player_actor_main_Notice_rod,
        &Player_actor_main_Putaway_rod,
        &Player_actor_main_Dig_scoop,
        &Player_actor_main_Fill_scoop,
        &Player_actor_main_Reflect_scoop,
        &Player_actor_main_Air_scoop,
        &Player_actor_main_Get_scoop,
        &Player_actor_main_Putaway_scoop,
        &Player_actor_main_Putin_scoop,
        &Player_actor_main_Talk,
        &Player_actor_main_Recieve_wait,
        &Player_actor_main_Recieve_stretch,
        &Player_actor_main_Recieve,
        &Player_actor_main_Recieve_putaway,
        &Player_actor_main_Give,
        &Player_actor_main_Give_wait,
        &Player_actor_main_Takeout_item,
        &Player_actor_main_Putin_item,
        &Player_actor_main_Demo_wait,
        &Player_actor_main_Demo_walk,
        &Player_actor_main_Demo_geton_train,
        &Player_actor_main_Demo_geton_train_wait,
        &Player_actor_main_Demo_getoff_train,
        &Player_actor_main_Demo_standing_train,
        &Player_actor_main_Demo_wade,
        &Player_actor_main_Hide,
        &Player_actor_main_Groundhog,
        &Player_actor_main_Release_creature,
        &Player_actor_main_Wash_car,
        &Player_actor_main_Tired,
        &Player_actor_main_Rotate_octagon,
        &Player_actor_main_Throw_money,
        &Player_actor_main_Pray,
        &Player_actor_main_Shake_tree,
        &Player_actor_main_Mail_jump,
        &Player_actor_main_Mail_land,
        &Player_actor_main_Ready_pitfall,
        &Player_actor_main_Fall_pitfall,
        &Player_actor_main_Struggle_pitfall,
        &Player_actor_main_Climbup_pitfall,
        &Player_actor_main_Stung_bee,
        &Player_actor_main_Notice_bee,
        &Player_actor_main_Remove_grass,
        &Player_actor_main_Shock,
        &Player_actor_main_Knock_door,
        &Player_actor_main_Change_cloth,
        &Player_actor_main_Push_snowball,
        &Player_actor_main_Rotate_umbrella,
        &Player_actor_main_Wade_snowball,
        &Player_actor_main_Complete_payment,
        &Player_actor_main_Fail_emu,
        &Player_actor_main_Stung_mosquito,
        &Player_actor_main_Notice_mosquito,
        &Player_actor_main_Swing_fan,
        &Player_actor_main_Switch_on_lighthouse,
        &Player_actor_main_Radio_exercise,
        &Player_actor_main_Demo_geton_boat,
        &Player_actor_main_Demo_geton_boat_sitdown,
        &Player_actor_main_Demo_geton_boat_wait,
        &Player_actor_main_Demo_geton_boat_wade,
        &Player_actor_main_Demo_getoff_boat_standup,
        &Player_actor_main_Demo_getoff_boat,
        &Player_actor_main_Demo_get_golden_item,
        &Player_actor_main_Demo_get_golden_item2,
        &Player_actor_main_Demo_get_golden_axe_wait,
    };
    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;
    int idx;

    Player_actor_move_other_func1(actorx, game); //
    idx = player->now_main_index;
    if (mPlayer_MAIN_INDEX_VALID(idx) == FALSE || proc[idx] == NULL) {
        return;
    }

    (*proc[idx])(actorx, game);
    Player_actor_move_other_func2(actorx, game); //
}

typedef void (*mPlayer_DRAW_PROC)(ACTOR*, GAME*);

static void Player_actor_draw_Normal(ACTOR*, GAME*);

extern void Player_actor_draw(ACTOR* actorx, GAME* game) {
    static const s8 data[] = {
        mPlayer_DRAW_TYPE_NONE,   mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NONE,   mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL, mPlayer_DRAW_TYPE_NORMAL,
        mPlayer_DRAW_TYPE_NORMAL,
    };

    static const mPlayer_DRAW_PROC proc[] = {
        (mPlayer_DRAW_PROC)&none_proc2,
        &Player_actor_draw_Normal,
    };

    PLAYER_ACTOR* player = (PLAYER_ACTOR*)actorx;
    int main_idx = player->now_main_index;

    if (mPlayer_MAIN_INDEX_VALID(main_idx) != FALSE) {
        int draw_idx = data[main_idx];

        if (draw_idx >= 0 && draw_idx < mPlayer_DRAW_TYPE_NUM && proc[draw_idx] != NULL) {
            (*proc[draw_idx])(actorx, game);
            Player_actor_draw_other_func2(actorx, game); //
        }
    }
}
