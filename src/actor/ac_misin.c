#include "ac_misin.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void Misin_Actor_ct(ACTOR* actorx, GAME* game);
static void Misin_Actor_dt(ACTOR* actorx, GAME* game);
static void Misin_Actor_draw(ACTOR* actorx, GAME* game);
static void Misin_Actor_move(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Misin_Profile = {
    mAc_PROFILE_MISIN,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MISIN_ACTOR),
    &Misin_Actor_ct,
    &Misin_Actor_dt,
    &Misin_Actor_move,
    &Misin_Actor_draw,
    NULL,
};

static void aMSN_SetDustclothSwitch(s16 switch_flag) {
    if (aMSN_GetClip() != NULL) {
        ((MISIN_ACTOR*)aMSN_GetClip()->misin_actor_p)->dustcloth.switch_flag = switch_flag;
    }
}

static void aMSN_RequestDustclothMove(void) {
    aMSN_SetDustclothSwitch(TRUE);
}

static void aMSN_RequestDustclothStop(void) {
    aMSN_SetDustclothSwitch(FALSE);
}

static xyz_t aMSN_dustcloth_target_table[4] = {
    { -4.0f, 0.0f, 4.0f },
    { -4.0f, 0.0f, -4.0f },
    { 4.0f, 0.0f, -4.0f },
    { 4.0f, 0.0f, 4.0f },
};

static void aMSN_DustclothCT(aMSN_DustCloth_c* dustcloth, GAME* game) {
    dustcloth->switch_flag = TRUE;
    dustcloth->frame = 0;
    dustcloth->original_p = (mNW_original_design_c*)zelda_malloc_align(sizeof(mNW_original_design_c), 32);

    if (dustcloth->original_p != NULL) {
        if (RANDOM(3) == 1) {
            mNW_CopyOriginalTextureClass(dustcloth->original_p,
                                         &Save_Get(needlework).original_design[RANDOM(1000) & 7]);
        } else {
            dustcloth->palette_p = (u16*)zelda_malloc_align(sizeof(u16) * 16, 32);
            if (dustcloth->palette_p != NULL) {
                mActor_name_t cloth;

                mSP_SelectRandomItem_New(NULL, &cloth, 1, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);
                mPlib_Load_PlayerTexAndPallet(dustcloth->original_p->design.data, dustcloth->palette_p,
                                              ITEM_NAME_GET_INDEX(cloth));
            }
        }
    }

    dustcloth->target_idx = 1;
    dustcloth->pos.x = 91.0f;
    dustcloth->pos.y = 0.0f;
    dustcloth->pos.z = 136.0f;
    dustcloth->target_pos = aMSN_dustcloth_target_table[(dustcloth->target_idx - 1) & 3];
}

static void aMSN_SetMisinStatus(s16 status) {
    if (aMSN_GetClip() != NULL) {
        ((MISIN_ACTOR*)aMSN_GetClip()->misin_actor_p)->misin.status = status;
    }
}

static void aMSN_RequestMisinStop(void) {
    aMSN_SetMisinStatus(FALSE);
}

static void aMSN_ReqeustMisinMove(void) {
    aMSN_SetMisinStatus(TRUE);
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_misin;
extern cKF_Animation_R_c cKF_ba_r_obj_misin;

static void aMSN_MisinCT(aMSN_Misin_c* misin, GAME* game) {
    cKF_SkeletonInfo_R_c* keyframe = &misin->keyframe;

    misin->status = TRUE;
    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_obj_misin, &cKF_ba_r_obj_misin, misin->work, misin->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_obj_misin, NULL);
    cKF_SkeletonInfo_R_play(keyframe);

    misin->speed = 1.0f;
    keyframe->frame_control.speed = 1.0f;
    misin->pos.x = 0.0f;
    misin->pos.y = 0.0f;
    misin->pos.z = 0.0f;
    misin->needle_y_counter = 0.0f;
}

static void aMSN_SetClipInfo(ACTOR* actorx, GAME* game) {
    MISIN_ACTOR* misin_actor = (MISIN_ACTOR*)actorx;
    aMSN_Clip_c* clip = &misin_actor->clip;

    clip->misin_actor_p = actorx;
    clip->request_misin_stop_proc = &aMSN_RequestMisinStop;
    clip->request_misin_move_proc = &aMSN_ReqeustMisinMove;
    clip->request_dustcloth_stop_proc = &aMSN_RequestDustclothStop;
    clip->request_dustcloth_move_proc = &aMSN_RequestDustclothMove;
    Common_Get(clip).misin_clip = clip;
}

static void Misin_Actor_ct(ACTOR* actorx, GAME* game) {
    MISIN_ACTOR* misin_actor = (MISIN_ACTOR*)actorx;
    aMSN_DustCloth_c* dustcloth = &misin_actor->dustcloth;
    aMSN_Misin_c* misin = &misin_actor->misin;

    aMSN_DustclothCT(dustcloth, game);
    aMSN_MisinCT(misin, game);
    aMSN_SetClipInfo(actorx, game);
}

static void Misin_Actor_dt(ACTOR* actorx, GAME* game) {
    MISIN_ACTOR* misin = (MISIN_ACTOR*)actorx;

    if (misin->dustcloth.original_p != NULL) {
        zelda_free(misin->dustcloth.original_p);
    }

    if (misin->dustcloth.palette_p != NULL) {
        zelda_free(misin->dustcloth.palette_p);
    }

    Common_Get(clip).misin_clip = NULL;
}

extern Gfx obj_misin_cloth_model[];

static void aMSN_DrawDustcloth(aMSN_DustCloth_c* dustcloth, GAME* game) {
    s16 target_angle_y = dustcloth->target_angle_y;

    if (dustcloth->original_p != NULL) {
        _texture_z_light_fog_prim(game->graph);

        OPEN_DISP(game->graph);

        /* Segment 8 holds the custom design or shirt texture */
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, dustcloth->original_p->design.data);

        if (dustcloth->palette_p != NULL) {
            /* Segment 9 holds the palette for the shirt */
            gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, dustcloth->palette_p);
        } else {
            /* Segment 9 holds the palette for the custom design */
            gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, mNW_PaletteIdx2Palette(dustcloth->original_p->palette));
        }

        Matrix_translate(dustcloth->pos.x, dustcloth->pos.y, dustcloth->pos.z, MTX_LOAD);
        Matrix_RotateY(target_angle_y, MTX_MULT);
        Matrix_translate(-dustcloth->target_pos.x, -dustcloth->target_pos.y, -dustcloth->target_pos.z, MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_misin_cloth_model);

        CLOSE_DISP(game->graph);
    }
}

static int aMSN_DrawMisinBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    /* Skip drawing the needle model */
    if (joint_idx == 3) {
        *joint_shape = NULL;
    }

    return TRUE;
}

extern Gfx obj_misin_hari_model[];

static int aMSN_DrawMisinAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                               u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    aMSN_Misin_c* misin = (aMSN_Misin_c*)arg;

    /* Now draw the needle model */
    if (joint_idx == 3) {
        OPEN_DISP(game->graph);

        Matrix_translate(87.0f, 62.0f + misin->needle_offset.y, 141.0f, MTX_LOAD);
        Matrix_RotateY(DEG2SHORT_ANGLE(0.0f), MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(-90.0f), MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_misin_hari_model);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static Gfx* aMSN_MakeBeltGFX(aMSN_Misin_c* misin, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, 0, misin->y_scroll, 8, 32, 1, 0, 0, 0, 0);
}

static void aMSN_DrawMisin(aMSN_Misin_c* misin, GAME* game) {
    cKF_SkeletonInfo_R_c* keyframe = &misin->keyframe;
    Mtx* mtx_p = misin->mtx[game->frame_counter & 1];
    Gfx* belt_gfx = aMSN_MakeBeltGFX(misin, game);

    _texture_z_light_fog_prim(game->graph);
    if (belt_gfx != NULL) {
        OPEN_DISP(game->graph);

        Matrix_translate(misin->pos.x, misin->pos.y, misin->pos.z, MTX_LOAD);
        Matrix_RotateY(DEG2SHORT_ANGLE(0.0f), MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        /* Segment 9 has the scrolled belt gfx */
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, belt_gfx);

        /* Draw animated model */
        cKF_Si3_draw_R_SV(game, keyframe, mtx_p, &aMSN_DrawMisinBefore, &aMSN_DrawMisinAfter, misin);

        CLOSE_DISP(game->graph);
    }
}

static void Misin_Actor_draw(ACTOR* actorx, GAME* game) {
    MISIN_ACTOR* misin = (MISIN_ACTOR*)actorx;

    aMSN_DrawDustcloth(&misin->dustcloth, game);
    aMSN_DrawMisin(&misin->misin, game);
}

static void aMSN_MoveDustcloth(aMSN_DustCloth_c* dustcloth, GAME* game) {
    static s16 target_angle_table[4] = {
        DEG2SHORT_ANGLE(0.0f),
        DEG2SHORT_ANGLE(90.0f),
        DEG2SHORT_ANGLE(-180.0f),
        DEG2SHORT_ANGLE(-90.0f),
    };
    dustcloth->moving_flag = FALSE;

    if (dustcloth->switch_flag != FALSE) {
        if (dustcloth->frame == 137) {
            int target_idx = dustcloth->target_idx;

            dustcloth->target_pos = aMSN_dustcloth_target_table[target_idx];
            dustcloth->target_angle_y = target_angle_table[target_idx];

            if (dustcloth->target_angle_y == DEG2SHORT_ANGLE(0.0f)) {
                dustcloth->target_angle_y = -1;
            }
        }

        if (dustcloth->frame < 98) {
            f32 percent = get_percent(97, 0, dustcloth->frame);
            int now_idx = dustcloth->target_idx;
            int prev_idx = (dustcloth->target_idx - 1) & 3;

            /* Interpolate position between last target pos & now target pos */
            dustcloth->target_pos.x =
                aMSN_dustcloth_target_table[prev_idx].x +
                percent * (aMSN_dustcloth_target_table[now_idx].x - aMSN_dustcloth_target_table[prev_idx].x);
            dustcloth->target_pos.z =
                aMSN_dustcloth_target_table[prev_idx].z +
                percent * (aMSN_dustcloth_target_table[now_idx].z - aMSN_dustcloth_target_table[prev_idx].z);

            /* Set rotation */
            dustcloth->target_angle_y = target_angle_table[prev_idx];

            if (dustcloth->frame > 21) {
                /* Play sewing SFX */
                xyz_t pos = { 91.0f, 40.0f, 136.0f };

                sAdo_OngenPos((uintptr_t)&aMSN_MoveDustcloth, 0x48, &pos);
            }
        } else if (dustcloth->frame >= 120) {
            f32 percent = get_percent(138, 120, dustcloth->frame);
            int now_idx = dustcloth->target_idx;
            int prev_idx = (dustcloth->target_idx - 1) & 3;

            /* Interpolate rotation */
            dustcloth->target_angle_y = target_angle_table[prev_idx] + (s16)(percent * (f32)DEG2SHORT_ANGLE(90.0f));
        }

        if (!(dustcloth->frame > 4 && dustcloth->frame < 118)) {
            dustcloth->moving_flag = TRUE;
        }

        dustcloth->frame++;
        if (dustcloth->frame >= 138) {
            dustcloth->target_idx = (dustcloth->target_idx + 1) & 3;
            dustcloth->frame = 0;
        }
    }
}

static void aMSN_SetNeedleOffsetPosition(aMSN_Misin_c* misin, aMSN_DustCloth_c* dustcloth) {
    static xyz_t zero_offset = { 0.0f, 0.0f, 0.0f };
    int counter = misin->needle_y_counter;

    if (counter < 10) {
        misin->needle_offset.y = (misin->needle_y_counter / 10.0f) * -3.0f;
    } else if (counter < 17) {
        misin->needle_offset.y = ((misin->needle_y_counter - 10.0f) / 7.0f) * 3.0f + -3.0f;
    } else {
        misin->needle_offset = zero_offset;
    }

    if (dustcloth->moving_flag == FALSE) {
        misin->needle_y_counter += misin->speed;
    }

    if (misin->needle_y_counter > 19.0f) {
        misin->needle_y_counter -= 19.0f;
    }
}

static void aMSN_MoveMisin(aMSN_Misin_c* misin, aMSN_DustCloth_c* dustcloth, GAME* game) {
    f32 target_speed;
    cKF_SkeletonInfo_R_c* keyframe;

    if (misin->status == TRUE) {
        target_speed = 1.0f;
    } else {
        target_speed = 0.0f;
    }

    keyframe = &misin->keyframe;
    aMSN_SetNeedleOffsetPosition(misin, dustcloth);
    misin->y_scroll += (s16)(misin->speed * -6.0f);
    cKF_SkeletonInfo_R_play(keyframe);

    if (misin->speed < target_speed) {
        misin->speed += 0.01f;
    } else {
        misin->speed -= 0.01f;
    }

    if (misin->speed < 0.0f) {
        misin->speed = 0.0f;
    } else if (misin->speed > 1.0f) {
        misin->speed = 1.0f;
    }

    keyframe->frame_control.speed = misin->speed;
}

static void Misin_Actor_move(ACTOR* actorx, GAME* game) {
    MISIN_ACTOR* misin = (MISIN_ACTOR*)actorx;
    aMSN_DustCloth_c* dustcloth = &misin->dustcloth;

    aMSN_MoveDustcloth(dustcloth, game);
    aMSN_MoveMisin(&misin->misin, dustcloth, game);
}
