#include "m_cporiginal_ovl.h"

#include "m_submenu_ovl.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_font.h"
#include "m_editEndChk_ovl.h"
#include "m_editor_ovl.h"
#include "m_needlework_ovl.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_malloc.h"

static mCO_Ovl_c co_ovl_data;

// clang-format off
static rgb8_t env_table[mCO_PAGE_NUM] = {
    {0xFF, 0xF5, 0xA0},
    {0xFF, 0xD7, 0x96},
    {0xF5, 0xC3, 0x82},
    {0xE1, 0xAF, 0x6E},
    {0xCD, 0x9B, 0x5A},
    {0xB9, 0x87, 0x46},
    {0xA5, 0x73, 0x32},
    {0x9B, 0x5F, 0x28},
};
// clang-format on

static int mCO_check_pat_idx(int pat_idx) {
    int ret = TRUE;

    if (pat_idx < 8 || pat_idx >= 104) {
        ret = FALSE;
    }

    return ret;
}

extern int mCO_get_change_flg(void) {
    return co_ovl_data.change_flg;
}

static int mCO_pat_idx_to_folder(int pat_idx) {
    return (pat_idx - 8) / mCO_ORIGINAL_NUM;
}

static int mCO_pat_idx_to_idx(int pat_idx) {
    return (pat_idx - 8) % mCO_ORIGINAL_NUM;
}

extern int mCO_top_folder(Submenu* submenu) {
    return submenu->overlay->cporiginal_ovl->page_order[0];
}

extern int mCO_check_mark_flg(Submenu* submenu, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int ret = FALSE;

    if (idx >= 0 && idx < mCO_ORIGINAL_NUM) {
        u16 flg = 1 << idx;

        if (cporiginal_ovl->mark_flg & flg) {
            ret = TRUE;
        }
    }

    return ret;
}

extern void mCO_clear_mark_flg(Submenu* submenu) {
    submenu->overlay->cporiginal_ovl->mark_flg = 0;
}

extern int mCO_check_hide_flg(Submenu* submenu, int folder, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    u16 flg = 1 << idx;
    int ret = FALSE;

    if (cporiginal_ovl->hide_flg[folder] & flg) {
        ret = TRUE;
    }

    return ret;
}

extern void mCO_on_hide_flg(Submenu* submenu, int folder, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    u16 flg = 1 << idx;

    cporiginal_ovl->hide_flg[folder] |= flg;
}

extern void mCO_clear_hide_flg(Submenu* submenu) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int i;

    for (i = 0; i < mCO_PAGE_NUM; i++) {
        cporiginal_ovl->hide_flg[i] = 0;
    }
}

static f32 mCO_page_accum = 0.0f;

static f32 mCO_page_pos_y(f32 timer) {
    return 100.0f * sinf_table(timer * DEG2RAD(4.5f));
}

extern int mCO_change_up_folder(Submenu* submenu, int folder) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int ret = FALSE;

    if (folder < mCO_PAGE_NUM && folder != cporiginal_ovl->page_order[0]) {
        cporiginal_ovl->timer = 40;
        mCO_page_accum = 0.0f;
        cporiginal_ovl->up_folder = folder;
        ret = TRUE;
    }

    return ret;
}

static mNW_original_tex_c* mCO_get_texture(Submenu* submenu, int folder, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    return &cporiginal_ovl->card_original->original[folder][idx].design;
}

extern mNW_original_tex_c sav_nuki_tex;

static mNW_original_tex_c* mCO_get_texture_pat_idx(Submenu* submenu, int pat_idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    mNW_original_tex_c* tex = &sav_nuki_tex;

    if (mCO_check_pat_idx(pat_idx)) {
        int folder = mCO_pat_idx_to_folder(pat_idx);
        int idx = mCO_pat_idx_to_idx(pat_idx);

        tex = mCO_get_texture(submenu, folder, idx);
    }

    return tex;
}

static int mCO_get_pallet_no(Submenu* submenu, int folder, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    return cporiginal_ovl->card_original->original[folder][idx].palette;
}

static int mCO_get_pallet_no_pat_idx(Submenu* submenu, int pat_idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int ret = 0;

    if (mCO_check_pat_idx(pat_idx)) {
        int folder = mCO_pat_idx_to_folder(pat_idx);
        int idx = mCO_pat_idx_to_idx(pat_idx);

        ret = mCO_get_pallet_no(submenu, folder, idx);
    }

    return ret;
}

extern Gfx inv_md_base_model_before[];
extern Gfx inv_md_base_model_b[];

extern void mCO_draw_cporiginal(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx,
                                int color_flag) {
    if (scale < 0.05f) {
        return;
    }
    
    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mCO_get_texture_pat_idx(submenu, idx));
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mNW_PaletteIdx2Palette(mCO_get_pallet_no_pat_idx(submenu, idx)));

    if (color_flag) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 0, 0, 80);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 255, 255, 255);
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_before);
    gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_b);

    CLOSE_POLY_OPA_DISP(graph);
}

extern u8* mCO_get_folder_name(Submenu* submenu, int folder) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    return cporiginal_ovl->card_original->folder_names[folder];
}

extern u8* mCO_get_image_name(Submenu* submenu, int folder, int idx) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    return cporiginal_ovl->card_original->original[folder][idx].name;
}

static mNW_original_design_c* mCO_itemNo_to_data(Submenu* submenu, mActor_name_t itemNo) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int pat_idx = itemNo - RSV_NW_ORIGINAL0;
    int folder = mCO_pat_idx_to_folder(pat_idx);
    int idx = mCO_pat_idx_to_idx(pat_idx);

    return &cporiginal_ovl->card_original->original[folder][idx];
}

static void mCO_swap_image_2(Submenu* submenu, mActor_name_t itemNo1, mActor_name_t itemNo2) {
    mNW_original_design_c* org1 = mNW_get_image_data(submenu, itemNo1 - RSV_NW_ORIGINAL0);
    mNW_original_design_c* org2 = mCO_itemNo_to_data(submenu, itemNo2);

    mNW_SwapOriginalData(org2, org1);
}

extern void mCO_swap_image(Submenu* submenu, mActor_name_t itemNo1, mActor_name_t itemNo2) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    if (ITEM_IS_RSVNWORG(itemNo1) && ITEM_IS_RSVNWORG(itemNo2)) {
        mNW_swap_image_no(submenu, itemNo1 - RSV_NW_ORIGINAL0, itemNo2 - RSV_NW_ORIGINAL0);
    } else if (ITEM_IS_RSVCPORG(itemNo1) && ITEM_IS_RSVCPORG(itemNo2)) {
        mNW_SwapOriginalData(mCO_itemNo_to_data(submenu, itemNo1), mCO_itemNo_to_data(submenu, itemNo2));
    } else if (ITEM_IS_RSVNWORG(itemNo1) && ITEM_IS_RSVCPORG(itemNo2)) {
        mCO_swap_image_2(submenu, itemNo1, itemNo2);
    } else if (ITEM_IS_RSVNWORG(itemNo2) && ITEM_IS_RSVCPORG(itemNo1)) {
        mCO_swap_image_2(submenu, itemNo2, itemNo1);
    }

    if (cporiginal_ovl != NULL) {
        u8 tmp = cporiginal_ovl->image_order[itemNo1 - RSV_NW_ORIGINAL0];
        cporiginal_ovl->image_order[itemNo1 - RSV_NW_ORIGINAL0] = cporiginal_ovl->image_order[itemNo2 - RSV_NW_ORIGINAL0];
        cporiginal_ovl->image_order[itemNo2 - RSV_NW_ORIGINAL0] = tmp;
    }
}

static void mCO_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mCO_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    if (menu_info->open_flag == FALSE) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_CPORIGINAL, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
        menu_info->open_flag = TRUE;
    } else if (cporiginal_ovl->timer != 0) {
        int old_timer = cporiginal_ovl->timer;
        int ticks = graph_dt_60hz_ticks(gamePT, &mCO_page_accum);
        cporiginal_ovl->timer -= ticks;
        if (cporiginal_ovl->timer < 0) {
            cporiginal_ovl->timer = 0;
        }
        menu_info->position[1] = mCO_page_pos_y((f32)cporiginal_ovl->timer);

        if (old_timer > 20 && cporiginal_ovl->timer <= 20) {
            u8* page_order_p = cporiginal_ovl->page_order;
            int i;

            for (i = 0; i < mCO_PAGE_NUM; i++, page_order_p++) {
                if (*page_order_p == cporiginal_ovl->up_folder) {
                    break;
                }
            }

            for (i; i > 0; i--) {
                *page_order_p = *(page_order_p - 1);
                page_order_p--;
            }

            cporiginal_ovl->page_order[0] = cporiginal_ovl->up_folder;
        } else if (cporiginal_ovl->timer == 0) {
            menu_info->position[1] = 0.0f;
            submenu->overlay->hand_ovl->set_hand_func(submenu);
            submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        }
    } else {
        submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
    }
}

static void mCO_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    mSM_MenuInfo_c* next_menu = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu->proc_status == mSM_OVL_PROC_MOVE && next_menu->next_proc_status == mSM_OVL_PROC_END) {
        if (next_menu->menu_type == mSM_OVL_EDITENDCHK) {
            if (next_menu->data1 == 0) {
                mNW_next_data(submenu);
                mCD_save_data_main_to_aram(cporiginal_ovl->card_original, mCD_KEEP_ORIGINAL_SIZE, mCD_ARAM_DATA_ORIGINAL);
                submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);

                if (Now_Private->cloth.idx >= (CLOTH_NUM + 1)) {
                    if (cporiginal_ovl->cloth_org_no != 255 && cporiginal_ovl->cloth_org_idx != 255) {
                        int idx = cporiginal_ovl->cloth_org_no;
                        int player_idx;
                        int i;

                        for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
                            if (idx == mNW_get_image_no(submenu, i)) {
                                player_idx = i;
                            }
                        }

                        if (cporiginal_ovl->image_order[player_idx] != cporiginal_ovl->cloth_org_idx) {
                            cporiginal_ovl->change_flg = TRUE;
                        }
                    }
                }
            } else if (next_menu->data1 == 1) {
                menu_info->proc_status = mSM_OVL_PROC_PLAY;
            } else {
                submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
            }
        } else if (next_menu->menu_type == mSM_OVL_EDITOR) {
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
        }
    }
}

static void mCO_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mCO_cporiginal_ovl_move(Submenu* submenu) {
    // clang-format off
    static mSM_MOVE_PROC ovl_move_proc[] = {
        mCO_move_Move,
        mCO_move_Play,
        mCO_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mCO_move_End,
    };
    // clang-format on

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPORIGINAL];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx sav_win1_taguT_model[];
extern Gfx sav_win1_kage_model[];

static void mCO_set_frame_tagS_dl(Submenu* submenu, GAME* game, int folder) {
    // clang-format off
    static rgb8_t prim_table[mCO_PAGE_NUM] = {
        {0xCD, 0xC3, 0x6E},
        {0xCD, 0xA5, 0x5F},
        {0xC3, 0x91, 0x4B},
        {0xAF, 0x7D, 0x37},
        {0x9B, 0x69, 0x23},
        {0x87, 0x5F, 0x14},
        {0x73, 0x55, 0x19},
        {0x5F, 0x2D, 0x14},
    };
    // clang-format on

    // clang-format off
    static rgb8_t env_table2[mCO_PAGE_NUM] = {
        {0xC3, 0xB9, 0x64},
        {0xC3, 0x9B, 0x5A},
        {0xB9, 0x87, 0x46},
        {0xA5, 0x73, 0x32},
        {0x91, 0x5F, 0x1E},
        {0x7D, 0x55, 0x0A},
        {0x69, 0x4B, 0x14},
        {0x55, 0x2D, 0x0A},
    };
    // clang-format on

    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int i;
    int idx;
    GRAPH* graph = game->graph;

    OPEN_POLY_OPA_DISP(graph);

    for (i = mCO_PAGE_NUM - 1; i >= 0; i--) {
        idx = cporiginal_ovl->page_order[i];

        if (idx != folder) {
            Matrix_push();
            Matrix_translate(0.0f, -((idx * 29) / 2), 0.0f, MTX_MULT);

            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, prim_table[idx].r, prim_table[idx].g, prim_table[idx].b, 255);
            gDPSetEnvColor(POLY_OPA_DISP++, env_table2[idx].r, env_table2[idx].g, env_table2[idx].b, 255);
            gSPDisplayList(POLY_OPA_DISP++, sav_win1_taguT_model);
            
            Matrix_pull();
        }
    }

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sav_win1_kage_model);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx sav_sentaku_taguT_model[];

static void mCO_set_frame_tagT_dl(Submenu* submenu, GAME* game, int folder) {
    // clang-format off
    static rgb8_t prim_table[mCO_PAGE_NUM] = {
        {0x91, 0x87, 0x5F},
        {0x8C, 0x6E, 0x4B},
        {0x7D, 0x69, 0x4B},
        {0x7D, 0x5F, 0x4B},
        {0x73, 0x5F, 0x41},
        {0x73, 0x55, 0x2D},
        {0x5F, 0x4B, 0x37},
        {0x5F, 0x41, 0x28},
    };
    // clang-format on

    GRAPH* graph = game->graph;
    int ofs_y;

    OPEN_POLY_OPA_DISP(graph);

    Matrix_push();

    // something is wrong with this function call, likely the calculation for y
    ofs_y = ((folder * 29) / 2);
    ofs_y = 52 - ofs_y;
    Matrix_translate(105.0f, ofs_y, 0.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, prim_table[folder].r, prim_table[folder].g, prim_table[folder].b, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, env_table[folder].r, env_table[folder].g, env_table[folder].b, 255);
    gSPDisplayList(POLY_OPA_DISP++, sav_sentaku_taguT_model);

    Matrix_pull();

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx sav_win1_ueT_model[];
extern Gfx sav_win1_nameT_model2[];

static void mCO_set_frame_ueT_dl(Submenu* submenu, GAME* game, int folder) {
    GRAPH* graph = game->graph;
    
    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    {
        // clang-format off
        static rgb8_t prim_table[mCO_PAGE_NUM] = {
            {0xA5, 0x87, 0x5A},
            {0x9B, 0x7D, 0x50},
            {0x91, 0x73, 0x46},
            {0x87, 0x69, 0x3C},
            {0x82, 0x64, 0x37},
            {0x78, 0x5A, 0x2D},
            {0x73, 0x55, 0x28},
            {0x6E, 0x50, 0x23},
        };
        // clang-format on

        // clang-format off
        static rgb8_t env2_table[mCO_PAGE_NUM] = {
            {0xEB, 0xD7, 0xAF},
            {0xE1, 0xCD, 0xA5},
            {0xD7, 0xC3, 0x9B},
            {0xCD, 0xB9, 0x91},
            {0xC3, 0xAF, 0x87},
            {0xB9, 0xA5, 0x7D},
            {0xAF, 0x9B, 0x73},
            {0xA5, 0x91, 0x69},
        };
        // clang-format on

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, prim_table[folder].r, prim_table[folder].g, prim_table[folder].b, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, env2_table[folder].r, env2_table[folder].g, env2_table[folder].b, 255);
        gSPDisplayList(POLY_OPA_DISP++, sav_win1_ueT_model);
    }

    {
        // clang-format off
        static rgb8_t prim_table[mCO_PAGE_NUM] = {
            {0x69, 0x50, 0x46},
            {0x3C, 0x32, 0x23},
            {0x4B, 0x37, 0x2D},
            {0x4B, 0x37, 0x2D},
            {0x41, 0x2D, 0x0F},
            {0x41, 0x37, 0x19},
            {0x41, 0x2D, 0x1E},
            {0x41, 0x37, 0x32},
        };
        // clang-format on

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, prim_table[folder].r, prim_table[folder].g, prim_table[folder].b, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, env_table[folder].r, env_table[folder].g, env_table[folder].b, 255);
        gSPDisplayList(POLY_OPA_DISP++, sav_win1_nameT_model2);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

extern u16 sav_win1_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win2_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win3_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win4_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win5_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win6_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win7_nuno_tex_rgb_ci4_pal[];
extern u16 sav_win8_nuno_tex_rgb_ci4_pal[];

extern Gfx save_win1_w_before_model[];
extern Gfx save_win1_w_all_model[];
extern Gfx sav_win1_waku_model[];
extern Gfx sav_mb_model[];
extern Gfx sav_win1_f_model[];

static void mCO_set_frame_main_dl(Submenu* submenu, GAME* game, int folder) {
    // clang-format off
    static u16* pallet_table[mCO_PAGE_NUM] = {
        sav_win1_nuno_tex_rgb_ci4_pal,
        sav_win2_nuno_tex_rgb_ci4_pal,
        sav_win3_nuno_tex_rgb_ci4_pal,
        sav_win4_nuno_tex_rgb_ci4_pal,
        sav_win5_nuno_tex_rgb_ci4_pal,
        sav_win6_nuno_tex_rgb_ci4_pal,
        sav_win7_nuno_tex_rgb_ci4_pal,
        sav_win8_nuno_tex_rgb_ci4_pal,
    };
    // clang-format on

    f32 pos_x = submenu->overlay->menu_control.texture_pos[0];
    f32 pos_y = submenu->overlay->menu_control.texture_pos[1];
    int tex_x;
    int tex_y;
    GRAPH* graph = game->graph;
    int idx;
    int j;
    int k;

    tex_x = F32_TO_U16(-pos_x * 4.0f);
    tex_y = F32_TO_U16(-pos_y * 4.0f);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 14, 16, 1, pallet_table[folder]);
    gSPDisplayList(POLY_OPA_DISP++, save_win1_w_before_model);
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, tex_x, tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, save_win1_w_all_model);
    gSPDisplayList(POLY_OPA_DISP++, sav_win1_waku_model);

    idx = 0;
    for (k = 0; k < 4; k++) {
        for (j = 0; j < 3; j++, idx++) {
            Matrix_push();
            Matrix_translate(32 * j, 29 * -k, 0.0f, MTX_MULT);

            if (mCO_check_hide_flg(submenu, folder, idx) == FALSE) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mCO_get_texture(submenu, folder, idx));
                gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mNW_PaletteIdx2Palette(mCO_get_pallet_no(submenu, folder, idx)));
                gSPDisplayList(POLY_OPA_DISP++, sav_mb_model);
            }

            Matrix_pull();
        }
    }

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sav_win1_f_model);

    CLOSE_POLY_OPA_DISP(graph);
    
    mNW_draw_sav_mark_before(game);

    idx = 0;
    for (k = 0; k < 4; k++) {
        for (j = 0; j < 3; j++, idx++) {
            if (mCO_check_mark_flg(submenu, idx)) {
                Matrix_push();
                
                mNW_draw_sav_mark(game, 32 * j, 44 + -k * 29);
                Matrix_pull();
            }
        }
    }

}

static void mCO_set_frame_string_dl(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y, int folder) {
    static rgb8_t color1 = { 0x50, 0x32, 0x32 };
    static rgb8_t color2 = { 0x46, 0x32, 0x32 };
    static rgb8_t color3 = { 0x3C, 0x28, 0x28 };
    static rgb8_t color4 = { 0x32, 0x1E, 0x1E };

    // clang-format off
    static rgb8_t* color_table[mCO_PAGE_NUM] = {
        &color1,
        &color1,
        &color1,
        &color2,
        &color2,
        &color3,
        &color3,
        &color4,
    };
    // clang-format on

    GRAPH* graph = game->graph;
    u8* folder_name = mCO_get_folder_name(submenu, folder);
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPORIGINAL];
    rgb8_t* color = color_table[folder];
    int len;
    
    if (menu_info->proc_status == mSM_OVL_PROC_WAIT && menu_info->next_menu_type == mSM_OVL_EDITOR) {
        OPEN_POLY_OPA_DISP(graph);

        gDPSetCycleType(POLY_OPA_DISP++, G_CYC_1CYCLE);
        gDPSetRenderMode(POLY_OPA_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        CLOSE_POLY_OPA_DISP(graph);
    }

    submenu->overlay->set_char_matrix_proc(graph);

    if (menu_info->proc_status == mSM_OVL_PROC_WAIT && menu_info->next_menu_type == mSM_OVL_EDITOR) {
        mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
        
        len = mCO_FOLDER_NAME_LEN;
        if (editor_ovl != NULL) {
            pos_x = (pos_x + 194.0f) - (editor_ovl->line_width * 0.875f) * 0.5f;
        }
    } else {
        len = mMl_strlen(folder_name, mCO_FOLDER_NAME_LEN, CHAR_SPACE);
        pos_x = (pos_x + 194.0f) - (mFont_GetStringWidth(folder_name, len, TRUE) * 0.875f) * 0.5f;
    }

    pos_y = 39.0f - pos_y;
    if (len != 0) {
        // clang-format off
        mFont_SetLineStrings(
            game,
            folder_name, len,
            pos_x, pos_y,
            color->r, color->g, color->b, 255,
            FALSE, TRUE,
            0.875f, 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on
    }

    if (menu_info->proc_status == mSM_OVL_PROC_WAIT && menu_info->next_menu_type == mSM_OVL_EDITOR) {
        mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;

        if (editor_ovl != NULL) {
            editor_ovl->cursol_draw(submenu, game, pos_x + (editor_ovl->_26 + -6.0f) * 0.875f, pos_y);
        }
    }
}

static void mCO_set_frame_change_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info, int folder) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;

    Matrix_push();
    Matrix_translate(menu_info->position[0], -menu_info->position[1], 140.0f, MTX_MULT);

    mCO_set_frame_main_dl(submenu, game, folder);
    mCO_set_frame_tagS_dl(submenu, game, cporiginal_ovl->up_folder);
    mCO_set_frame_ueT_dl(submenu, game, folder);
    mCO_set_frame_string_dl(submenu, game, 0.0f, -menu_info->position[1], folder);

    Matrix_pull();
}

static void mCO_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int folder;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);

    if (cporiginal_ovl->timer != 0) {
        if (cporiginal_ovl->page_order[0] == cporiginal_ovl->up_folder) {
            mCO_set_frame_change_dl(submenu, game, menu_info, cporiginal_ovl->page_order[1]);
        }

        folder = cporiginal_ovl->up_folder;

        Matrix_push();
        Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);
        mCO_set_frame_main_dl(submenu, game, folder);
        mCO_set_frame_ueT_dl(submenu, game, folder);
        mCO_set_frame_tagT_dl(submenu, game, folder);
        mCO_set_frame_string_dl(submenu, game, 0.0f, menu_info->position[1] , folder);
        Matrix_pull();

        if (cporiginal_ovl->page_order[0] != cporiginal_ovl->up_folder) {
            mCO_set_frame_change_dl(submenu, game, menu_info, cporiginal_ovl->page_order[0]);
        }
    } else {
        folder = cporiginal_ovl->page_order[0];

        Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);
        mCO_set_frame_main_dl(submenu, game, folder);
        mCO_set_frame_tagS_dl(submenu, game, folder);
        mCO_set_frame_ueT_dl(submenu, game, folder);
        mCO_set_frame_tagT_dl(submenu, game, folder);
        mCO_set_frame_string_dl(submenu, game, menu_info->position[0], 0.0f, folder);
    }
}

static void mCO_cporiginal_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPORIGINAL];
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    f32 pos_y = menu_info->position[1];

    menu_info->pre_draw_func(submenu, game);
    if (cporiginal_ovl->timer != 0 && mCO_page_accum > 0.0f) {
        f32 timer = (f32)cporiginal_ovl->timer - mCO_page_accum;

        if (timer < 0.0f) {
            timer = 0.0f;
        }
        menu_info->position[1] = mCO_page_pos_y(timer);
    }
    mCO_set_frame_dl(submenu, game, menu_info);
    menu_info->position[1] = pos_y;
    if (cporiginal_ovl->timer == 0) {
        submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_CPORIGINAL);
    }
}

extern void mCO_cporiginal_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_CPORIGINAL];

    ovl->menu_control.menu_move_func = mCO_cporiginal_ovl_move;
    ovl->menu_control.menu_draw_func = mCO_cporiginal_ovl_draw;

    if (ovl->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mCO_cporiginal_ovl_init(Submenu* submenu) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPORIGINAL];
    int i;
    u8* page_order_p = cporiginal_ovl->page_order;

    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    menu_info->move_drt = mSM_MOVE_IN_RIGHT;

    for (i = 0; i < mCO_PAGE_NUM; i++, page_order_p++) {
        *page_order_p = i;
    }

    cporiginal_ovl->timer = 0;
    cporiginal_ovl->change_flg = FALSE;
    cporiginal_ovl->cloth_org_no = 255;
    cporiginal_ovl->up_folder = 0;

    if (Now_Private->cloth.idx >= (CLOTH_NUM + 1)) {
        int cloth_idx = Now_Private->cloth.idx - (CLOTH_NUM + 1);
        
        cporiginal_ovl->cloth_org_no = cloth_idx;
        for (i = 0; i < mCO_PAGE_NUM; i++) {
            if (cloth_idx == Now_Private->my_org_no_table[i]) {
                cporiginal_ovl->cloth_org_idx = i;
            }
        }
    }

    mCD_save_data_aram_to_main(cporiginal_ovl->card_original, mCD_KEEP_ORIGINAL_SIZE, mCD_ARAM_DATA_ORIGINAL);
    for (i = 0; i < ARRAY_COUNT(cporiginal_ovl->image_order); i++) {
        cporiginal_ovl->image_order[i] = i;
    }
}

extern void mCO_cporiginal_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    
    if (ovl->cporiginal_ovl == NULL) {
        mem_clear((u8*)&co_ovl_data, sizeof(co_ovl_data), 0);
        ovl->cporiginal_ovl = &co_ovl_data;
        co_ovl_data.card_original = (mCD_keep_original_c*)zelda_malloc_align(mCD_KEEP_ORIGINAL_SIZE, 32);
        mCO_clear_mark_flg(submenu);
    }

    mCO_cporiginal_ovl_init(submenu);
    mCO_cporiginal_ovl_set_proc(submenu);
}

extern void mCO_cporiginal_ovl_destruct(Submenu* submenu) {
    if (co_ovl_data.card_original != NULL) {
        zelda_free(co_ovl_data.card_original);
        co_ovl_data.card_original = NULL;
    }

    submenu->overlay->cporiginal_ovl = NULL;
}
