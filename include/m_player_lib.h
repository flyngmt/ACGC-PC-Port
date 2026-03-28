#ifndef M_PLAYER_LIB_H
#define M_PLAYER_LIB_H

#include "types.h"
#include "m_player.h"
#include "m_private_h.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern cKF_Animation_R_c* mPlib_Get_Pointer_Animation(int anim_idx);
extern int mPlib_Get_BasicPlayerAnimeIndex_fromItemKind(int item_kind);
extern int mPlib_Get_BasicPartTableIndex_fromAnimeIndex(int anim_idx);
extern void* mPlib_Get_Item_DataPointer(int data_kind);
extern int mPlib_Get_BasicItemShapeIndex_fromItemKind(int item_kind);
extern int mPlib_Get_BasicItemAnimeIndex_fromItemKind(int item_kind);
extern u8 mPlib_Get_Item_DataPointerType(int data_idx);
extern void mPlib_Object_Exchange_keep_new_PlayerMdl(GAME_PLAY* play);
extern u32 mPlib_Get_PlayerTexRom_p(int idx);
extern void mPlib_Object_Exchange_keep_new_PlayerTex(GAME_PLAY* play, int bank_idx, int bank);
extern u32 mPlib_Get_PlayerPalletRom_p(int idx);
extern void mPlib_Object_Exchange_keep_new_PlayerPallet(GAME_PLAY* play, int bank_idx, int bank);
extern int mPlib_Check_PlayerClothInAram(int idx);
extern void mPlib_Object_Exchange_keep_new_PlayerFaceTex(GAME_PLAY* play);
extern void mPlib_Object_Exchange_keep_new_PlayerFacePallet(GAME_PLAY* play, int bank, int bank_idx);
extern void mPlib_Object_Exchange_keep_Player_dt(GAME_PLAY* play);
extern u8* mPlib_get_player_tex_p(GAME* game);
extern u16* mPlib_get_player_pallet_p(GAME* game);
extern u8* mPlib_get_player_face_p(GAME* game);
extern u16* mPlib_get_player_face_pallet_p(GAME* game);
extern void mPlib_change_player_cloth(GAME* game, u16 cloth_idx);
extern void mPlib_change_player_face_pallet(GAME* game);
extern void mPlib_change_player_face(GAME* game);
extern PLAYER_ACTOR* get_player_actor_withoutCheck(GAME_PLAY* play);
extern int mPlib_get_player_actor_main_index(GAME* game);
extern int mPlib_get_player_actor_request_main_index(GAME* game);
extern cKF_Skeleton_R_c* mPlib_get_player_mdl_p(void);
extern s16 mPlib_get_player_Object_Bank(void);
extern void mPlib_DMA_player_Part_Table(s8* part_table_p, int idx);
extern void mPlib_change_player_cloth_info(mPr_cloth_c* cloth_p, mActor_name_t item);
extern void mPlib_change_player_cloth_info_lv2(Private_c* priv, mActor_name_t item);
extern void mPlib_Load_PlayerTexAndPallet(void* tex_p, void* pal_p, int idx);
extern mPlayer_change_data_from_submenu_c* mPlib_Get_change_data_from_submenu_p(void);
extern void mPlib_Clear_change_data_from_submenu(void);
extern void mPlib_request_main_give_from_submenu(mActor_name_t item, int after_mode, int present_flag,
                                                 int surface_flag);
extern void mPlib_request_main_putin_scoop_from_submenu(const xyz_t* pos_p, mActor_name_t item, int gold_scoop_flag);
extern void mPlib_request_main_release_creature_gyoei_from_submenu(s16 angle_y, s16 item, int gold_scoop_flag);
extern void mPlib_request_main_release_creature_insect_from_submenu(int insect_type, int gold_scoop_flag);
extern s8 mPlib_Get_ItemNoToItemKind(mActor_name_t itemNo);
extern int mPlib_Get_ItemKindTOBalloonShapeType(int item_kind);
extern void mPlib_request_main_release_creature_balloon_from_submenu(mActor_name_t itemNo, int gold_scoop_flag);
extern void mPlib_request_main_wait_from_submenu(void);
extern void mPlib_request_main_demo_get_golden_item_from_submenu(void);
extern void mPlib_request_main_mail_land_from_submenu(void);
extern void mPlib_request_main_demo_wait_from_submenu(ACTOR* speak_actor_p);
extern void mPlib_Set_unable_wade(int v);
extern int mPlib_Get_unable_wade(void);
extern int mPlib_Check_able_force_speak_label(GAME* game, ACTOR* label);
extern void mPlib_Set_able_force_speak_label(ACTOR* label);
extern void mPlib_Reset_able_force_speak_label(void);
extern u8* mPlib_Get_PlayerEyeTexAnimation_p(int anim_idx);
extern u8* mPlib_Get_PlayerMouthTexAnimation_p(int anim_idx);
extern u8* mPlib_Get_eye_tex_p(int idx);
extern u8* mPlib_Get_mouth_tex_p(int idx);
extern int mPlib_request_main_invade_type1(GAME* game);
extern int mPlib_request_main_refuse_type1(GAME* game);
extern int mPlib_request_main_wait_type3(GAME* game);
extern int mPlib_request_main_demo_get_golden_item2_type1(GAME* game, int golden_item_type);
extern int mPlib_request_main_talk_end_type1(GAME* game, int wait_demo, int demo_get_golden_axe);
extern int mPlib_request_main_talk_type1(GAME* game, ACTOR* talk_actor_p, int turn_flag, int umbrella_flag);
extern int mPlib_request_main_hold_type1(GAME* game, int ftr_no, int player_direct, const xyz_t* player_pos_p);
extern int mPlib_request_main_recieve_wait_type1(GAME* game, mActor_name_t item, int counter_flag);
extern int mPlib_request_main_give_type1(GAME* game, mActor_name_t item, int mode, int present, int on_surface);
extern int mPlib_request_main_sitdown_type1(GAME* game, int direct, const xyz_t* pos_p, int ftr_no);
extern int mPlib_request_main_close_furniture_type1(GAME* game);
extern int mPlib_request_main_lie_bed_type1(GAME* game, int direct, const xyz_t* pos_p, int head_direct, int ftr_no);
extern int mPlib_request_main_hide_type1(GAME* game);
extern int mPlib_request_main_groundhog_type1(GAME* game);
extern int mPlib_request_main_door_type1(GAME* game, const xyz_t* pos_p, s16 angle_y, int door_type, void* door_label);
extern int mPlib_request_main_door_type2(GAME* game, const xyz_t* pos_p, s16 angle_y, int door_type, void* door_label);
extern int mPlib_request_main_outdoor_type1(GAME* game, int is_start_demo, int door_type);
extern int mPlib_request_main_wash_car_type1(GAME* game, const xyz_t* car_pos_p, const xyz_t* ret_pos_p,
                                             s16 ret_angle_y, ACTOR* ctrl_actor_p);
extern int mPlib_request_main_rotate_octagon_type1(GAME* game, const xyz_t* pos_p, s16 angle_y);
extern int mPlib_request_main_throw_money_type1(GAME* game, const xyz_t* pos_p, s16 angle_y);
extern int mPlib_request_main_pray_type1(GAME* game, const xyz_t* pos_p, s16 angle_y);
extern int mPlib_request_main_mail_jump_type1(GAME* game, const xyz_t* pos_p, s16 angle_y);
extern int mPlib_request_main_stung_bee_type1(GAME* game);
extern int mPlib_request_main_stung_mosquito_type1(void* label);
extern int mPlib_request_main_switch_on_lighthouse_type1(GAME* game, const xyz_t* pos_p, s16 angle_y);
extern int mPlib_request_main_demo_geton_boat_type1(f32 goal_x, f32 goal_z, s16 angleY);
extern int mPlib_request_main_demo_getoff_boat_standup_type1(const xyz_t* pos_p, s16 angleY);
extern int mPlib_request_main_shock_type1(GAME* game, f32 time, s16 angle_y, int axe_swing);
extern int mPlib_request_main_change_cloth_forNPC_type1(GAME* game, mActor_name_t cloth_item, u16 cloth_idx,
                                                        int try_on_flag);
extern int mPlib_request_main_push_snowball_type1(GAME* game, void* label);
extern int mPlib_request_main_push_snowball_end_type1(GAME* game);
extern int mPlib_request_main_demo_wait_type1(GAME* game, int umbrella_flag, void* label);
extern int mPlib_request_main_demo_walk_type1(GAME* game, f32 goal_x, f32 goal_z, f32 speed, int wait_flag);
extern int mPlib_request_main_demo_geton_train_type1(GAME* game, const xyz_t* pos_p);
extern int mPlib_request_main_demo_getoff_train_type1(GAME* game);
extern int mPlib_request_main_demo_standing_train_type1(GAME* game);
extern int mPlib_check_request_main_talk_type1_priority(GAME* game);
extern int mPlib_check_request_main_speak_type1_priority(GAME* game);
extern int mPlib_check_request_main_door_type1_priority(GAME* game);
extern int mPlib_check_request_main_door_type2_priority(GAME* game);
extern int mPlib_check_request_main_wade_priority(GAME* game);
extern int mPlib_check_request_main_demo_wade_priority(GAME* game);
extern int mPlib_check_request_main_demo_geton_boat_wade_priority(GAME* game);
extern int mPlib_strength_request_main_wade_priority(GAME* game);
extern int mPlib_strength_request_main_demo_wade_priority(GAME* game);
extern int mPlib_strength_request_main_wade_snowball_priority(GAME* game);
extern int mPlib_strength_request_main_demo_geton_boat_wade_priority(GAME* game);
extern int mPlib_strength_request_main_door_priority(GAME* game);
extern int mPlib_check_request_main_outdoor_priority(GAME* game);
extern int mPlib_Check_SetOrderSubmenu(void);
extern int mPlib_able_submenu_type1(GAME* game);
extern int mPlib_check_player_open_umbrella(GAME* game);
extern int mPlib_check_player_outdoor_start(GAME* game);
extern int mPlib_check_label_player_demo_wait(GAME* game, void* label);
extern void mPlib_Set_goal_player_demo_walk(f32 pos_x, f32 pos_z, f32 speed);
extern void mPlib_Get_goal_player_demo_walk(f32* pos_x_p, f32* pos_z_p, f32* speed_p);
extern void mPlib_Set_continue_player_after_demo_walk(int value);
extern int mPlib_Get_continue_player_after_demo_walk(void);
extern void mPlib_Set_end_player_demo_walk(int value);
extern int mPlib_Get_end_player_demo_walk(void);
extern int mPlib_Get_space_putin_item(void);
extern int mPlib_Get_space_putin_item_forTICKET(mActor_name_t* item_p);
extern int mPlib_Get_space_putin_item_forHITODAMA(mActor_name_t* item_p);
extern int mPlib_able_player_warp_forEvent(void);
extern int mPlib_request_player_warp_forEvent(void);
extern int mPlib_cancel_player_warp_forEvent(void);
extern int mPlib_check_player_warp_forEvent(void);
extern int mPlib_Check_HitAxe(xyz_t* pos_p);
extern int mPlib_Check_VibUnit_OneFrame(const xyz_t* pos_p);
extern int mPlib_Check_StopNet(xyz_t* pos_p);
extern uintptr_t mPlib_Get_item_net_catch_label(void);
extern int mPlib_Change_item_net_catch_label(uintptr_t label, s8 type);
extern int mPlib_Check_HitScoop(xyz_t* pos_p);
extern int mPlib_Check_DigScoop(xyz_t* pos_p);
extern int mPlib_Get_address_able_display(void);
extern int mPlib_Check_scoop_after(GAME* game, xyz_t* pos_p, mActor_name_t* item_p, ACTOR** reflect_actor_pp,
                                   int gold_scoop);
extern int mPlib_Check_scene_able_change_camera_pos(void);
extern int mPlib_Check_RotateOctagon(void);
extern int mPlib_Set_EndWashCar(void);
extern int mPlib_Set_AnimeSpeedWashCar(f32 anime_speed);
extern int mPlib_Check_now_handin_item_kind(void);
extern int mPlib_Check_now_handin_item(void);
extern void mPlib_Set_able_hand_all_item_in_demo(s8 v);
extern int mPlib_Get_status_for_bee(void);
extern int mPlib_Check_end_stung_bee(void);
extern int mPlib_Check_Label_main_push_snowball(void* label);
extern int mPlib_Check_Label_main_wade_snowball(void* label);
extern int mPlib_Set_ScrollDemo_forWade_snowball(int dir, const xyz_t* snowball_dist_p);
extern int mPlib_GetSnowballPos_forWadeSnowball(xyz_t* pos_p);
extern int mPlib_CheckCondition_forWadeSnowball(const xyz_t* pos_p, s16 angle_y);
extern int mPlib_SetParam_for_push_snowball(const xyz_t* pos_p, s16 angle_y, f32 anim_speed);
extern void mPlib_Set_crash_snowball_for_wade(int v);
extern mPlayer_Controller_Data_c* mPlib_Get_controller_data_for_title_demo_p(void);
extern void mPlib_Clear_controller_data_for_title_demo(void);
extern void mPlib_SetData1_controller_data_for_title_demo(int btn_a, int btn_b, f32 stick_x, f32 stick_y);
extern void mPlib_SetData2_controller_data_for_title_demo(mActor_name_t item);
extern int mPlib_Check_CorrectPlayerPos_forEvent(void);
extern int mPlib_Check_UKI_COMEBACK_STATUS(void);
extern int mPlib_Check_tree_shaken(const xyz_t* pos_p);
extern int mPlib_Check_tree_shaken_little(const xyz_t* pos_p);
extern int mPlib_Check_tree_shaken_big(const xyz_t* pos_p);
extern mActor_name_t mPlib_Get_itemNo_forWindow(void);
extern int mPlib_able_birth_bee(void);
extern int mPlib_check_able_change_camera_normal_index(void);
extern int mPlib_check_player_actor_main_index_Furniture_Move(GAME* game);
extern int mPlib_check_player_actor_main_index_RecieveMove(GAME* game);
extern int mPlib_check_player_actor_main_index_Pitfall(GAME* game);
extern int mPlib_check_player_actor_main_index_OutDoorMove(GAME* game);
extern int mPlib_check_player_actor_main_index_OutDoorMove2(GAME* game);
extern int mPlib_check_player_actor_main_index_AllWade(GAME* game);
extern int mPlib_check_player_actor_main_index_catch_insect(GAME* game);
extern int mPlib_check_player_actor_main_index_catch_fish(GAME* game);
extern int mPlib_check_player_actor_start_switch_on_lighthouse(GAME* game);
extern int mPlib_Check_stung_mosquito(void* label);
extern void mPlib_Set_boat_angleZ(s16 angle_z);
extern int mPlib_CheckButtonOnly_forDush(void);
extern int mPlib_Check_golden_item_get_demo_end(int gold_item_type);
extern void mPlib_Set_change_color_request(void);

#define GET_PLAYER_ACTOR(play) get_player_actor_withoutCheck(play)
#define GET_PLAYER_ACTOR_NOW() get_player_actor_withoutCheck((GAME_PLAY*)gamePT)
#define GET_PLAYER_ACTOR_GAME(game) get_player_actor_withoutCheck((GAME_PLAY*)(game))

#define GET_PLAYER_ACTOR_ACTOR(play) ((ACTOR*)GET_PLAYER_ACTOR(play))
#define GET_PLAYER_ACTOR_NOW_ACTOR() ((ACTOR*)GET_PLAYER_ACTOR_NOW())
#define GET_PLAYER_ACTOR_GAME_ACTOR(game) ((ACTOR*)GET_PLAYER_ACTOR_GAME(game))

#ifdef __cplusplus
}
#endif

#endif
