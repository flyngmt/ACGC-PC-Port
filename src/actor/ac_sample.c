#include "ac_sample.h"

#include "m_demo.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_mail.h"
#include "m_rcp.h"
#include "m_name_table.h"
#include "m_play.h"

static ClObjPipeData_c Ac_Sample_OcInfoData_forStand = { { 0x39, 0x20, ClObj_TYPE_PIPE }, // collision data
                                                         { 1 },                           // element data
                                                         // Pipe specs
                                                         {
                                                             30, // radius
                                                             60, // height
                                                             0,  // offset

                                                             { 0, 0, 0 } // center
                                                         } };

static void Ac_Sample_ct_forCorect(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    SAMPLE_ACTOR* sample = (SAMPLE_ACTOR*)actor;
    ClObjPipe_ct(game, &sample->stand);
    ClObjPipe_set5(game, &sample->stand, (ACTOR*)actor, &Ac_Sample_OcInfoData_forStand);
}

static void Ac_Sample_Excute_Corect(SAMPLE_ACTOR* actor, GAME_PLAY* play) {
    ClObjPipe_c* stand = &actor->stand;

    CollisionCheck_Uty_ActorWorldPosSetPipeC((ACTOR*)actor, stand);
    CollisionCheck_setOC(&play->game, &play->collision_check, (ClObj_c*)stand);
}

static void Ac_Sample_Actor_dt(ACTOR* actor, GAME* game) {
    SAMPLE_ACTOR* sample = (SAMPLE_ACTOR*)actor;
    cKF_SkeletonInfo_R_c* keyframe = &sample->keyframe;
    if (actor->child_actor != NULL) {
        Actor_delete(actor->child_actor);
    }

    cKF_SkeletonInfo_R_dt(keyframe);
    ClObjPipe_dt(game, &sample->stand);
}

static void Ac_Sample_Animation_Base(SAMPLE_ACTOR* actor) {
    cKF_SkeletonInfo_R_play(&actor->keyframe);
}

static void Ac_Sample_Actor_wait_demo_ct(ACTOR* actor) {
    // ドリキャス "Dreamcast"
    static u8 str0[16] = { 0xDC,       0xB8,       0x97,       0x8C,       0x9D,       CHAR_SPACE,
                           CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE,
                           CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE };

    // プレステ2 "Playstation 2"
    static u8 str9[5] = { 0xE4, 0xBA, 0x9D, 0xA3, 0x32 };

    static u8 str_mail[64];

    mDemo_Set_msg_num(MSG_9);
    mMsg_Set_item_str(mMsg_Get_base_window_p(), 0, str0, 6);
    mMsg_Set_item_str(mMsg_Get_base_window_p(), 4, str9, 5);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 0, str0, 16);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 9, str9, 5);
    mMsg_Set_mail_str(mMsg_Get_base_window_p(), 0, str_mail, 64);
}

static void Ac_Sample_Actor_main_wait(SAMPLE_ACTOR* actor, GAME_PLAY* play) {
    Ac_Sample_Animation_Base(actor);
    Actor_world_to_eye((ACTOR*)actor, 48.0f);
    Ac_Sample_Excute_Corect(actor, play);

    if (mDemo_Check(mDemo_TYPE_TALK, (ACTOR*)actor) == FALSE) {
        mDemo_Request(mDemo_TYPE_TALK, (ACTOR*)actor, &Ac_Sample_Actor_wait_demo_ct);
    } else {
        actor->main_action = 1;
    }
}

static void Ac_Sample_Actor_main_talk(SAMPLE_ACTOR* actor, GAME_PLAY* play) {
    Ac_Sample_Animation_Base(actor);
    Actor_world_to_eye((ACTOR*)actor, 48.0f);
    Ac_Sample_Excute_Corect(actor, play);

    if (mDemo_Check(mDemo_TYPE_TALK, (ACTOR*)actor)) {
        s16 angle = add_calc_short_angle2(&actor->actor_class.shape_info.rotation.y, actor->actor_class.player_angle_y,
                                          1.0f, 5000, 100);
        actor->actor_class.world.angle.y = actor->actor_class.shape_info.rotation.y;

        if (mDemo_Check_ListenAble() == FALSE && mDemo_Check_DiffAngle_forTalk(angle)) {
            mDemo_Set_ListenAble();
        }
    } else {
        actor->main_action = 0;
    }
}

typedef void (*Ac_Sample_Actor_PROC)(SAMPLE_ACTOR*, GAME_PLAY*);

static void Ac_Sample_Actor_main(ACTOR* actor, GAME* game) {
    static Ac_Sample_Actor_PROC proc[] = { &Ac_Sample_Actor_main_wait, &Ac_Sample_Actor_main_talk };

    SAMPLE_ACTOR* sample = (SAMPLE_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (sample->main_action < 0 || sample->main_action >= 2 || proc[sample->main_action] == NULL) {
        return;
    }

    (*proc[sample->main_action])(sample, play);
}

extern cKF_Skeleton_R_c cKF_bs_r_hnw;
extern cKF_Animation_R_c cKF_ba_r_hnw_move;

static void Ac_Sample_Actor_ct(ACTOR* actor, GAME* game) {
    cKF_SkeletonInfo_R_c* keyframe;
    GAME_PLAY* play = (GAME_PLAY*)game;
    SAMPLE_ACTOR* sample = (SAMPLE_ACTOR*)actor;
    Object_Bank_c* bank;

    keyframe = &sample->keyframe;
    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_hnw, &cKF_ba_r_hnw_move, sample->work_area, sample->morph_area);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_hnw_move, NULL);
    Ac_Sample_ct_forCorect(actor, game);

    sample->draw_action = 1;
    bank = &play->object_exchange.banks[actor->data_bank_id];
    sample->obj_bank_ram_start = bank->ram_start;
}

extern u8 hnw_tmem_txt[];
extern u16 hnw_face[];

static void Ac_Sample_Actor_draw_normal(SAMPLE_ACTOR* actor, GAME_PLAY* play) {
    cKF_SkeletonInfo_R_c* keyframe = &actor->keyframe;
    N64Mtx* m = GRAPH_ALLOC_TYPE(play->game.graph, N64Mtx, keyframe->skeleton->num_shown_joints);

    if (m != NULL) {
        GRAPH* g;
        Gfx* gfx;
        _texture_z_light_fog_prim(play->game.graph);

        g = play->game.graph;
        OPEN_DISP(g);
        gfx = NOW_POLY_OPA_DISP;

        /* @BUG - rendering was never updated to GC format resulting in corrupted textures */
#ifndef BUGFIXES
        gDPLoadTextureBlockS(gfx++, hnw_tmem_txt, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                             G_TX_MIRROR | G_TX_WRAP, 7, 7, G_TX_NOLOD, G_TX_NOLOD);
        gDPLoadTLUT_pal16(gfx++, 15, hnw_face); // pal is different
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
#else
        gSPSegment(gfx++, G_MWO_SEGMENT_B, hnw_tmem_txt);
        gDPSetPrimColor(gfx++, 0, 128, 255, 255, 255, 255);
        gDPLoadTLUT_Dolphin(gfx++, 15, 16, 1, hnw_face);
#endif

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(g);

        cKF_Si3_draw_R_SV((GAME*)play, keyframe, m, NULL, NULL, NULL);
    }
}

static void Ac_Sample_Actor_draw(ACTOR* actor, GAME* game) {
    static Ac_Sample_Actor_PROC proc[] = { (Ac_Sample_Actor_PROC)&none_proc2, &Ac_Sample_Actor_draw_normal };

    SAMPLE_ACTOR* sample = (SAMPLE_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (sample->draw_action < 0 || sample->draw_action >= 2 || proc[sample->draw_action] == NULL) {
        return;
    }

    (*proc[sample->draw_action])(sample, play);
}

ACTOR_PROFILE Sample_Profile = { mAc_PROFILE_SAMPLE,
                                 ACTOR_PART_BG,
                                 0,
                                 MISC_ACTOR_SAMPLE,
                                 ACTOR_OBJ_BANK_12,
                                 sizeof(SAMPLE_ACTOR),
                                 &Ac_Sample_Actor_ct,
                                 &Ac_Sample_Actor_dt,
                                 &Ac_Sample_Actor_main,
                                 &Ac_Sample_Actor_draw,
                                 NULL };
