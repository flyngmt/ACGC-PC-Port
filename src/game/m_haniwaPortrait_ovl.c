#include "m_haniwaPortrait_ovl.h"

#include "m_rcp.h"
#include "sys_matrix.h"

extern cKF_Skeleton_R_c cKF_bs_r_hnw;
extern cKF_Animation_R_c cKF_ba_r_hnw_move;

static mHP_Ovl_c hp_ovl_data;

static void mHP_haniwaPortrait_shape_init(Submenu* submenu) {
  mHP_Ovl_c* haniwaPortrait_ovl = submenu->overlay->hanwiaPortrait_ovl;

  cKF_SkeletonInfo_R_ct(&haniwaPortrait_ovl->keyframe, &cKF_bs_r_hnw, NULL, haniwaPortrait_ovl->keyframe_work, haniwaPortrait_ovl->keyframe_morph);
  cKF_SkeletonInfo_R_init(&haniwaPortrait_ovl->keyframe, haniwaPortrait_ovl->keyframe.skeleton, &cKF_ba_r_hnw_move, 1.0f, 9.0f, 1.0f, 0.3f, 0.0f, cKF_FRAMECONTROL_REPEAT, NULL);
}

static void mHP_haniwaPortrait_shape_move(Submenu* submenu) {
  cKF_SkeletonInfo_R_play(&submenu->overlay->hanwiaPortrait_ovl->keyframe);
}

extern u8 hnw_tmem_txt[];
extern u16 hnw_face[];

static void mHP_haniwaPortrait_shape_draw(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
  GRAPH* graph = game->graph;
  N64Mtx* mtx = GRAPH_ALLOC_TYPE(graph, N64Mtx, submenu->overlay->hanwiaPortrait_ovl->keyframe.skeleton->num_shown_joints);

  if (mtx != NULL) {
    _texture_z_light_fog_prim(game->graph);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_LOAD);

    OPEN_DISP(graph);

    gDPPipeSync(NOW_POLY_OPA_DISP++);
    gSPMatrix(NOW_POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_B, hnw_tmem_txt);
    gDPLoadTLUT_Dolphin(NOW_POLY_OPA_DISP++, 15, 16, 1, hnw_face);

    if (menu_info->data0 == 0) {
      gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);
    }
    else {
      gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);
    }

    CLOSE_DISP(graph);

    cKF_Si3_draw_R_SV(game, &submenu->overlay->hanwiaPortrait_ovl->keyframe, mtx, NULL, NULL, NULL);
  }
}

static void mHP_set_haniwaPortrait(Submenu* submenu, mSM_MenuInfo_c* menu_info, GRAPH* graph, GAME* game, f32 x, f32 y) {
  if (x < -128.0f || x > 448.0f || y < -128.0f || y > 368.0f) {
    return;
  }

  Matrix_push();

  OPEN_DISP(graph);

  gDPPipeSync(NOW_POLY_OPA_DISP++);

  CLOSE_DISP(graph);

  (*submenu->overlay->change_view_proc)(graph, 105.0f, 25.0f, x * 4.0f, y * 4.0f, 0x0900, 128, 128);
  mHP_haniwaPortrait_shape_draw(submenu, menu_info, game);
  (*submenu->overlay->setup_view_proc)(submenu, graph, FALSE);

  Matrix_pull();
}

extern void mHP_haniwaPortrait_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->hanwiaPortrait_ovl == NULL) {
    mem_clear((u8*)&hp_ovl_data, sizeof(mHP_Ovl_c), 0);
    overlay->hanwiaPortrait_ovl = &hp_ovl_data;

    submenu->overlay->hanwiaPortrait_ovl->set_haniwaPortrait_proc = &mHP_set_haniwaPortrait;
    submenu->overlay->hanwiaPortrait_ovl->haniwaPortrait_shape_move_proc = &mHP_haniwaPortrait_shape_move;
    mHP_haniwaPortrait_shape_init(submenu);
    mHP_haniwaPortrait_shape_move(submenu);
  }
}

extern void mHP_haniwaPortrait_ovl_destruct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  cKF_SkeletonInfo_R_dt(&overlay->hanwiaPortrait_ovl->keyframe);
  submenu->overlay->hanwiaPortrait_ovl = NULL;
}
