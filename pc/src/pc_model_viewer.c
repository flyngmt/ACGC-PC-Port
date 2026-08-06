/* Multi-category debug model viewer scene (--model-viewer flag)
 *
 * Categories:
 *   Structures (75) - building/structure skeleton models with palettes
 *   NPCs (382) - animal NPC models with body/eye/mouth textures
 *   Fish (39) - museum fish skeleton models with swimming animation
 *
 * Controls:
 *   X          - cycle category (Structures -> NPCs -> Fish -> wrap)
 *   B / A      - next / previous model within category
 *   Left stick - orbit camera
 *   D-pad U/D  - zoom in/out
 *   D-pad L/R  - pan left/right
 *   Start      - toggle animation pause
 *   
 *   Note: File is starting to get annoyingly long, consider refactoring if I end up adding more features.
 *
 */
#include "pc_model_viewer.h"
#include "pc_platform.h"

#include "m_rcp.h"
#include "m_controller.h"
#include "sys_matrix.h"
#include "c_keyframe.h"
#include "graph.h"
#include "ac_structure.h"
#include "ac_npc.h"
#include "PR/mbi.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/vi.h"
#include "libultra/libultra.h"
#include "libforest/gbi_extensions.h"

#include <math.h>

/* STRUCTURE MODEL TABLE */

typedef struct {
    const char* name;
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;
    s16 pal_idx;    /* index into structure_pal_adrs_nowinter/winter, or -1 for no palette */
    u8 is_winter;   /* 1 = use winter palette */
} MVModelEntry;

extern u16* structure_pal_adrs_nowinter[];
extern u16* structure_pal_adrs_winter[];

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop4;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house5;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house5;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome4;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station3;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_yubinkyoku;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_yubinkyoku;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_tailor;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_tailor;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_yamishop;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_yamishop;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_bridgeA;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_bridgeA;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_douzou;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_douzou;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_toudai;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_toudai;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_frag;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_frag;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_post;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_post;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_uranai;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_uranai;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_lotus;

extern cKF_Skeleton_R_c cKF_bs_r_obj_train1_1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_train1_3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_romtrain_door;

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_boat;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_count01;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_count02_cl;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_koinobori;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_l;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_r;
extern cKF_Skeleton_R_c cKF_bs_r_obj_gara;
extern cKF_Skeleton_R_c cKF_bs_r_obj_misin;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome_i;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house_i;

extern cKF_Skeleton_R_c cKF_bs_r_obj_toudai_switch;
extern cKF_Skeleton_R_c cKF_bs_r_obj_toudai_pole;

extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_yub;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_koban;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_museum1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_tailor;

extern cKF_Skeleton_R_c cKF_bs_r_obj_museum5_hasu;

extern cKF_Animation_R_c cKF_ba_r_obj_s_shop1;
extern cKF_Animation_R_c cKF_ba_r_obj_w_shop1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_shop2;
extern cKF_Animation_R_c cKF_ba_r_obj_w_shop2;
extern cKF_Animation_R_c cKF_ba_r_obj_s_shop3;
extern cKF_Animation_R_c cKF_ba_r_obj_w_shop3;
extern cKF_Animation_R_c cKF_ba_r_obj_s_shop4;
extern cKF_Animation_R_c cKF_ba_r_obj_w_shop4;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house1;
extern cKF_Animation_R_c cKF_ba_r_obj_w_house1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house2;
extern cKF_Animation_R_c cKF_ba_r_obj_w_house2;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house3;
extern cKF_Animation_R_c cKF_ba_r_obj_w_house3;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house4;
extern cKF_Animation_R_c cKF_ba_r_obj_w_house4;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house5;
extern cKF_Animation_R_c cKF_ba_r_obj_w_house5;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome1;
extern cKF_Animation_R_c cKF_ba_r_obj_w_myhome1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome2;
extern cKF_Animation_R_c cKF_ba_r_obj_w_myhome2;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome3;
extern cKF_Animation_R_c cKF_ba_r_obj_w_myhome3;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome4;
extern cKF_Animation_R_c cKF_ba_r_obj_w_myhome4;
extern cKF_Animation_R_c cKF_ba_r_obj_s_station1;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_station2;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station2;
extern cKF_Animation_R_c cKF_ba_r_obj_s_station3;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station3;
extern cKF_Animation_R_c cKF_ba_r_obj_s_yubinkyoku;
extern cKF_Animation_R_c cKF_ba_r_obj_w_yubinkyoku;
extern cKF_Animation_R_c cKF_ba_r_obj_s_tailor;
extern cKF_Animation_R_c cKF_ba_r_obj_w_tailor;
extern cKF_Animation_R_c cKF_ba_r_obj_s_yamishop;
extern cKF_Animation_R_c cKF_ba_r_obj_w_yamishop;
extern cKF_Animation_R_c cKF_ba_r_obj_s_bridgeA;
extern cKF_Animation_R_c cKF_ba_r_obj_w_bridgeA;
extern cKF_Animation_R_c cKF_ba_r_obj_s_douzou;
extern cKF_Animation_R_c cKF_ba_r_obj_w_douzou;
extern cKF_Animation_R_c cKF_ba_r_obj_s_toudai;
extern cKF_Animation_R_c cKF_ba_r_obj_w_toudai;
extern cKF_Animation_R_c cKF_ba_r_obj_s_frag;
extern cKF_Animation_R_c cKF_ba_r_obj_w_frag;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post;
extern cKF_Animation_R_c cKF_ba_r_obj_s_uranai;
extern cKF_Animation_R_c cKF_ba_r_obj_w_uranai;
extern cKF_Animation_R_c cKF_ba_r_obj_s_lotus;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_1;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_3_close;
extern cKF_Animation_R_c cKF_ba_r_obj_romtrain_door;
extern cKF_Animation_R_c cKF_ba_r_obj_e_boat;
extern cKF_Animation_R_c cKF_ba_r_obj_e_count01;
extern cKF_Animation_R_c cKF_ba_r_obj_e_count02_cl;
extern cKF_Animation_R_c cKF_ba_r_obj_e_koinobori;
extern cKF_Animation_R_c cKF_ba_r_obj_e_tukimi_l;
extern cKF_Animation_R_c cKF_ba_r_obj_e_tukimi_r;
extern cKF_Animation_R_c cKF_ba_r_obj_gara;
extern cKF_Animation_R_c cKF_ba_r_obj_misin;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome_i;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house_i;
extern cKF_Animation_R_c cKF_ba_r_obj_toudai_switch;
extern cKF_Animation_R_c cKF_ba_r_obj_toudai_pole;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop1;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop2;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop3;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop4;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_yub;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_koban;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_museum1;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_tailor;
extern cKF_Animation_R_c cKF_ba_r_obj_museum5_hasu;

static const MVModelEntry s_model_table[] = {
    { "Shop 1 (Summer)",        &cKF_bs_r_obj_s_shop1,   &cKF_ba_r_obj_s_shop1,   aSTR_PAL_SHOP1, 0 },
    { "Shop 1 (Winter)",        &cKF_bs_r_obj_w_shop1,   &cKF_ba_r_obj_w_shop1,   aSTR_PAL_SHOP1, 1 },
    { "Shop 2 (Summer)",        &cKF_bs_r_obj_s_shop2,   &cKF_ba_r_obj_s_shop2,   aSTR_PAL_SHOP2, 0 },
    { "Shop 2 (Winter)",        &cKF_bs_r_obj_w_shop2,   &cKF_ba_r_obj_w_shop2,   aSTR_PAL_SHOP2, 1 },
    { "Shop 3 (Summer)",        &cKF_bs_r_obj_s_shop3,   &cKF_ba_r_obj_s_shop3,   aSTR_PAL_SHOP3, 0 },
    { "Shop 3 (Winter)",        &cKF_bs_r_obj_w_shop3,   &cKF_ba_r_obj_w_shop3,   aSTR_PAL_SHOP3, 1 },
    { "Shop 4 (Summer)",        &cKF_bs_r_obj_s_shop4,   &cKF_ba_r_obj_s_shop4,   aSTR_PAL_SHOP4, 0 },
    { "Shop 4 (Winter)",        &cKF_bs_r_obj_w_shop4,   &cKF_ba_r_obj_w_shop4,   aSTR_PAL_SHOP4, 1 },

    { "House 1 (Summer)",       &cKF_bs_r_obj_s_house1,  &cKF_ba_r_obj_s_house1,  aSTR_PAL_HOUSE1_A, 0 },
    { "House 1 (Winter)",       &cKF_bs_r_obj_w_house1,  &cKF_ba_r_obj_w_house1,  aSTR_PAL_HOUSE1_A, 1 },
    { "House 2 (Summer)",       &cKF_bs_r_obj_s_house2,  &cKF_ba_r_obj_s_house2,  aSTR_PAL_HOUSE2_A, 0 },
    { "House 2 (Winter)",       &cKF_bs_r_obj_w_house2,  &cKF_ba_r_obj_w_house2,  aSTR_PAL_HOUSE2_A, 1 },
    { "House 3 (Summer)",       &cKF_bs_r_obj_s_house3,  &cKF_ba_r_obj_s_house3,  aSTR_PAL_HOUSE3_A, 0 },
    { "House 3 (Winter)",       &cKF_bs_r_obj_w_house3,  &cKF_ba_r_obj_w_house3,  aSTR_PAL_HOUSE3_A, 1 },
    { "House 4 (Summer)",       &cKF_bs_r_obj_s_house4,  &cKF_ba_r_obj_s_house4,  aSTR_PAL_HOUSE4_A, 0 },
    { "House 4 (Winter)",       &cKF_bs_r_obj_w_house4,  &cKF_ba_r_obj_w_house4,  aSTR_PAL_HOUSE4_A, 1 },
    { "House 5 (Summer)",       &cKF_bs_r_obj_s_house5,  &cKF_ba_r_obj_s_house5,  aSTR_PAL_HOUSE5_A, 0 },
    { "House 5 (Winter)",       &cKF_bs_r_obj_w_house5,  &cKF_ba_r_obj_w_house5,  aSTR_PAL_HOUSE5_A, 1 },

    { "My Home 1 (Summer)",     &cKF_bs_r_obj_s_myhome1, &cKF_ba_r_obj_s_myhome1, aSTR_PAL_MYHOME_A, 0 },
    { "My Home 1 (Winter)",     &cKF_bs_r_obj_w_myhome1, &cKF_ba_r_obj_w_myhome1, aSTR_PAL_MYHOME_A, 1 },
    { "My Home 2 (Summer)",     &cKF_bs_r_obj_s_myhome2, &cKF_ba_r_obj_s_myhome2, aSTR_PAL_MYHOME_C, 0 },
    { "My Home 2 (Winter)",     &cKF_bs_r_obj_w_myhome2, &cKF_ba_r_obj_w_myhome2, aSTR_PAL_MYHOME_C, 1 },
    { "My Home 3 (Summer)",     &cKF_bs_r_obj_s_myhome3, &cKF_ba_r_obj_s_myhome3, aSTR_PAL_MYHOME_E, 0 },
    { "My Home 3 (Winter)",     &cKF_bs_r_obj_w_myhome3, &cKF_ba_r_obj_w_myhome3, aSTR_PAL_MYHOME_E, 1 },
    { "My Home 4 (Summer)",     &cKF_bs_r_obj_s_myhome4, &cKF_ba_r_obj_s_myhome4, aSTR_PAL_MYHOME_G, 0 },
    { "My Home 4 (Winter)",     &cKF_bs_r_obj_w_myhome4, &cKF_ba_r_obj_w_myhome4, aSTR_PAL_MYHOME_G, 1 },

    { "Station 1 (Summer)",     &cKF_bs_r_obj_s_station1, &cKF_ba_r_obj_s_station1, aSTR_PAL_STATION1_A, 0 },
    { "Station 1 (Winter)",     &cKF_bs_r_obj_w_station1, &cKF_ba_r_obj_w_station1, aSTR_PAL_STATION1_A, 1 },
    { "Station 2 (Summer)",     &cKF_bs_r_obj_s_station2, &cKF_ba_r_obj_s_station2, aSTR_PAL_STATION2_A, 0 },
    { "Station 2 (Winter)",     &cKF_bs_r_obj_w_station2, &cKF_ba_r_obj_w_station2, aSTR_PAL_STATION2_A, 1 },
    { "Station 3 (Summer)",     &cKF_bs_r_obj_s_station3, &cKF_ba_r_obj_s_station3, aSTR_PAL_STATION3_A, 0 },
    { "Station 3 (Winter)",     &cKF_bs_r_obj_w_station3, &cKF_ba_r_obj_w_station3, aSTR_PAL_STATION3_A, 1 },

    { "Post Office (Summer)",   &cKF_bs_r_obj_s_yubinkyoku, &cKF_ba_r_obj_s_yubinkyoku, aSTR_PAL_POST_OFFICE, 0 },
    { "Post Office (Winter)",   &cKF_bs_r_obj_w_yubinkyoku, &cKF_ba_r_obj_w_yubinkyoku, aSTR_PAL_POST_OFFICE, 1 },
    { "Tailor (Summer)",        &cKF_bs_r_obj_s_tailor,  &cKF_ba_r_obj_s_tailor,  aSTR_PAL_TAILOR, 0 },
    { "Tailor (Winter)",        &cKF_bs_r_obj_w_tailor,  &cKF_ba_r_obj_w_tailor,  aSTR_PAL_TAILOR, 1 },
    { "Redd's Shop (Summer)",   &cKF_bs_r_obj_s_yamishop, &cKF_ba_r_obj_s_yamishop, aSTR_PAL_BR_SHOP, 0 },
    { "Redd's Shop (Winter)",   &cKF_bs_r_obj_w_yamishop, &cKF_ba_r_obj_w_yamishop, aSTR_PAL_BR_SHOP, 1 },
    { "Fortune Teller (Summer)",&cKF_bs_r_obj_s_uranai,  &cKF_ba_r_obj_s_uranai,  aSTR_PAL_MIKUJI, 0 },
    { "Fortune Teller (Winter)",&cKF_bs_r_obj_w_uranai,  &cKF_ba_r_obj_w_uranai,  aSTR_PAL_MIKUJI, 1 },

    { "Bridge (Summer)",        &cKF_bs_r_obj_s_bridgeA, &cKF_ba_r_obj_s_bridgeA, aSTR_PAL_BRIDGE_A, 0 },
    { "Bridge (Winter)",        &cKF_bs_r_obj_w_bridgeA, &cKF_ba_r_obj_w_bridgeA, aSTR_PAL_BRIDGE_A, 1 },
    { "Statue (Summer)",        &cKF_bs_r_obj_s_douzou,  &cKF_ba_r_obj_s_douzou,  aSTR_PAL_DOUZOU_DAI, 0 },
    { "Statue (Winter)",        &cKF_bs_r_obj_w_douzou,  &cKF_ba_r_obj_w_douzou,  aSTR_PAL_DOUZOU_DAI, 1 },
    { "Lighthouse (Summer)",    &cKF_bs_r_obj_s_toudai,  &cKF_ba_r_obj_s_toudai,  aSTR_PAL_TOUDAI, 0 },
    { "Lighthouse (Winter)",    &cKF_bs_r_obj_w_toudai,  &cKF_ba_r_obj_w_toudai,  aSTR_PAL_TOUDAI, 1 },
    { "Flag (Summer)",          &cKF_bs_r_obj_s_frag,    &cKF_ba_r_obj_s_frag,    aSTR_PAL_FLAG, 0 },
    { "Flag (Winter)",          &cKF_bs_r_obj_w_frag,    &cKF_ba_r_obj_w_frag,    aSTR_PAL_FLAG, 1 },
    { "Mailbox (Summer)",       &cKF_bs_r_obj_s_post,    &cKF_ba_r_obj_s_post,    aSTR_PAL_POST_OFFICE, 0 },
    { "Mailbox (Winter)",       &cKF_bs_r_obj_w_post,    &cKF_ba_r_obj_s_post,    aSTR_PAL_POST_OFFICE, 1 },
    { "Lotus",                  &cKF_bs_r_obj_s_lotus,   &cKF_ba_r_obj_s_lotus,   aSTR_PAL_01_LOTUS, 0 },

    { "Train Engine",           &cKF_bs_r_obj_train1_1,  &cKF_ba_r_obj_train1_1,  aSTR_PAL_TRAIN1_A1, 0 },
    { "Train Car",              &cKF_bs_r_obj_train1_3,  &cKF_ba_r_obj_train1_3_close, aSTR_PAL_TRAIN1_A2, 0 },
    { "Train Door",             &cKF_bs_r_obj_romtrain_door, &cKF_ba_r_obj_romtrain_door, aSTR_PAL_TRAIN1_A1, 0 },

    { "Boat",                   &cKF_bs_r_obj_e_boat,    &cKF_ba_r_obj_e_boat,    aSTR_PAL_BOAT, 0 },
    { "Countdown 01",           &cKF_bs_r_obj_e_count01, &cKF_ba_r_obj_e_count01, aSTR_PAL_COUNT, 0 },
    { "Countdown 02",           &cKF_bs_r_obj_e_count02_cl, &cKF_ba_r_obj_e_count02_cl, aSTR_PAL_COUNT02, 0 },
    { "Koinobori",              &cKF_bs_r_obj_e_koinobori, &cKF_ba_r_obj_e_koinobori, aSTR_PAL_KOINOBORI_A, 0 },
    { "Moon Viewing L",         &cKF_bs_r_obj_e_tukimi_l, &cKF_ba_r_obj_e_tukimi_l, aSTR_PAL_TUKIMI, 0 },
    { "Moon Viewing R",         &cKF_bs_r_obj_e_tukimi_r, &cKF_ba_r_obj_e_tukimi_r, aSTR_PAL_TUKIMI, 0 },
    { "Gacha Machine",          &cKF_bs_r_obj_gara,      &cKF_ba_r_obj_gara,      -1, 0 },
    { "Sewing Machine",         &cKF_bs_r_obj_misin,     &cKF_ba_r_obj_misin,     -1, 0 },

    { "My Home Interior",       &cKF_bs_r_obj_s_myhome_i, &cKF_ba_r_obj_s_myhome_i, aSTR_PAL_MYHOME_ISLAND, 0 },
    { "House Interior",         &cKF_bs_r_obj_s_house_i, &cKF_ba_r_obj_s_house_i, aSTR_PAL_HOUSE_I, 0 },

    { "Lighthouse Switch",      &cKF_bs_r_obj_toudai_switch, &cKF_ba_r_obj_toudai_switch, aSTR_PAL_TOUDAI, 0 },
    { "Lighthouse Pole",        &cKF_bs_r_obj_toudai_pole, &cKF_ba_r_obj_toudai_pole, aSTR_PAL_TOUDAI, 0 },

    { "Clock (Shop 1)",         &cKF_bs_r_obj_clock_shop1, &cKF_ba_r_obj_clock_shop1, aSTR_PAL_SHOP1, 0 },
    { "Clock (Shop 2)",         &cKF_bs_r_obj_clock_shop2, &cKF_ba_r_obj_clock_shop2, aSTR_PAL_SHOP2, 0 },
    { "Clock (Shop 3)",         &cKF_bs_r_obj_clock_shop3, &cKF_ba_r_obj_clock_shop3, aSTR_PAL_SHOP3, 0 },
    { "Clock (Shop 4)",         &cKF_bs_r_obj_clock_shop4, &cKF_ba_r_obj_clock_shop4, aSTR_PAL_SHOP4, 0 },
    { "Clock (Post Office)",    &cKF_bs_r_obj_clock_yub, &cKF_ba_r_obj_clock_yub, aSTR_PAL_POST_OFFICE, 0 },
    { "Clock (Police Box)",     &cKF_bs_r_obj_clock_koban, &cKF_ba_r_obj_clock_koban, aSTR_PAL_POLICE_BOX, 0 },
    { "Clock (Museum)",         &cKF_bs_r_obj_clock_museum1, &cKF_ba_r_obj_clock_museum1, aSTR_PAL_MUSEUM, 0 },
    { "Clock (Tailor)",         &cKF_bs_r_obj_clock_tailor, &cKF_ba_r_obj_clock_tailor, aSTR_PAL_TAILOR, 0 },

    { "Museum Lily Pad",        &cKF_bs_r_obj_museum5_hasu, &cKF_ba_r_obj_museum5_hasu, aSTR_PAL_MUSEUM, 0 },
};

#define STRUCTURE_COUNT (int)(sizeof(s_model_table) / sizeof(s_model_table[0]))

/* NPC DATA */

extern aNPC_draw_data_c npc_draw_data_tbl[];
extern cKF_Animation_R_c cKF_ba_r_ply_1_wait1;

#define NPC_COUNT 382  /* must match npc_draw_data_tbl[] array size */

/* Dummy cloth texture (32x32 CI4 = 512 bytes) and white palette for segment 0x0A */
ATTRIBUTE_ALIGN(32) static u8 s_dummy_cloth_tex[512];
ATTRIBUTE_ALIGN(32) static u16 s_dummy_cloth_pal[16];
static int s_dummy_cloth_init = 0;

static void mv_init_dummy_cloth(void) {
    if (!s_dummy_cloth_init) {
        int i;
        memset(s_dummy_cloth_tex, 0, sizeof(s_dummy_cloth_tex));
        for (i = 0; i < 16; i++)
            s_dummy_cloth_pal[i] = 0xFFFF; /* white */
        s_dummy_cloth_init = 1;
    }
}

/* FISH DATA */

extern cKF_Skeleton_R_c* mfish_model_tbl[];
extern cKF_Animation_R_c* mfish_anime_init_tbl[];

#define FISH_COUNT       40  /* must match mfish_model_tbl[] array size */
#define FISH_JELLYFISH   35  /* NULL skeleton/animation */
#define FISH_SCALE       0.01f

static const char* s_fish_names[FISH_COUNT] = {
    "Crucian Carp",     "Brook Trout",      "Carp",             "Koi",
    "Catfish",          "Small Bass",       "Bass",             "Large Bass",
    "Bluegill",         "Giant Catfish",    "Giant Snakehead",  "Barbel Steed",
    "Dace",             "Pale Chub",        "Bitterling",       "Loach",
    "Pond Smelt",       "Sweetfish",        "Cherry Salmon",    "Large Char",
    "Rainbow Trout",    "Stringfish",       "Salmon",           "Goldfish",
    "Piranha",          "Arowana",          "Eel",              "Freshwater Goby",
    "Angelfish",        "Guppy",            "Popeyed Goldfish", "Coelacanth",
    "Crawfish",         "Frog",             "Killifish",        "Jellyfish (N/A)",
    "Sea Bass",         "Red Snapper",      "Barred Knifejaw",  "Arapaima",
};

/* CAMERA CONSTANTS (per-category) */

#define CAM_DEFAULT_ANGLE_X 0.3f
#define CAM_DEFAULT_ANGLE_Y 4.71238898f    /* 3PI/2 */
#define CAM_ORBIT_SPEED     0.03f

static const f32 s_cam_dist[MV_CAT_NUM]       = { 30000.0f, 170.0f, 60.0f   };
static const f32 s_cam_center_y[MV_CAT_NUM]   = { 3000.0f,  25.0f,  0.0f    };
static const f32 s_cam_min_dist[MV_CAT_NUM]   = { 500.0f,   40.0f,  5.0f    };
static const f32 s_cam_max_dist[MV_CAT_NUM]   = { 80000.0f, 2000.0f, 500.0f };
static const f32 s_cam_zoom_speed[MV_CAT_NUM] = { 300.0f,   2.0f,   1.0f   };
static const f32 s_cam_pan_speed[MV_CAT_NUM]  = { 100.0f,   2.0f,   1.0f   };

/* CATEGORY HELPERS */

static int mv_cat_count(int cat) {
    switch (cat) {
        case MV_CAT_STRUCTURES: return STRUCTURE_COUNT;
        case MV_CAT_NPCS:       return NPC_COUNT;
        case MV_CAT_FISH:       return FISH_COUNT;
        default:                return 0;
    }
}

static const char* mv_cat_name(int cat) {
    switch (cat) {
        case MV_CAT_STRUCTURES: return "Structures";
        case MV_CAT_NPCS:       return "NPCs";
        case MV_CAT_FISH:       return "Fish";
        default:                return "???";
    }
}

static const char* mv_model_name(int cat, int idx) {
    switch (cat) {
        case MV_CAT_STRUCTURES: return s_model_table[idx].name;
        case MV_CAT_NPCS:       return "NPC";
        case MV_CAT_FISH:       return s_fish_names[idx];
        default:                return "???";
    }
}

/* Skip NULL entries when navigating fish */
static int mv_fish_skip_null(int idx, int dir) {
    if (idx == FISH_JELLYFISH) {
        idx += dir;
        if (idx < 0) idx = FISH_COUNT - 1;
        if (idx >= FISH_COUNT) idx = 0;
    }
    return idx;
}

/* WINDOW TITLE & CAMERA RESET */

static void mv_update_title(GAME_MODEL_VIEWER* mv) {
    char title[160];
    int cat = mv->category;
    int idx = mv->cat_index[cat];
    int count = mv_cat_count(cat);
    snprintf(title, sizeof(title), "Model Viewer [%s %d/%d] %s",
             mv_cat_name(cat), idx + 1, count, mv_model_name(cat, idx));
    VISetWindowTitle(title);
    OSReport("[ModelViewer] %s\n", title);
}

static void mv_reset_camera(GAME_MODEL_VIEWER* mv) {
    int cat = mv->category;
    mv->cam_distance = s_cam_dist[cat];
    mv->cam_angle_x = CAM_DEFAULT_ANGLE_X;
    mv->cam_angle_y = CAM_DEFAULT_ANGLE_Y;
    mv->cam_pan_x = 0.0f;
    mv->cam_pan_z = 0.0f;
}

/* MODEL SETUP (per-category skeleton initialization) */

static void mv_setup_model(GAME_MODEL_VIEWER* mv) {
    int cat = mv->category;
    int idx = mv->cat_index[cat];

    memset(&mv->skeleton_info, 0, sizeof(mv->skeleton_info));
    memset(mv->joint_work, 0, sizeof(mv->joint_work));
    memset(mv->joint_target, 0, sizeof(mv->joint_target));

    switch (cat) {
        case MV_CAT_STRUCTURES: {
            const MVModelEntry* entry = &s_model_table[idx];
            cKF_SkeletonInfo_R_ct(&mv->skeleton_info, entry->skeleton, NULL,
                                  mv->joint_work, mv->joint_target);
            cKF_SkeletonInfo_R_init_standard_stop(&mv->skeleton_info, entry->animation, NULL);
            cKF_SkeletonInfo_R_play(&mv->skeleton_info);
            break;
        }
        case MV_CAT_NPCS: {
            aNPC_draw_data_c* npc = &npc_draw_data_tbl[idx];
            if (npc->model_skeleton == NULL) break;
            cKF_SkeletonInfo_R_ct(&mv->skeleton_info, npc->model_skeleton, NULL,
                                  mv->joint_work, mv->joint_target);
            /* Use player idle animation — same 26-joint structure as NPC skeletons */
            cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(
                &mv->skeleton_info, &cKF_ba_r_ply_1_wait1, NULL, 1.0f, 0.0f);
            cKF_SkeletonInfo_R_play(&mv->skeleton_info);
            break;
        }
        case MV_CAT_FISH: {
            cKF_Skeleton_R_c* skel = mfish_model_tbl[idx];
            cKF_Animation_R_c* anim = mfish_anime_init_tbl[idx];
            if (skel == NULL || anim == NULL) break;
            cKF_SkeletonInfo_R_ct(&mv->skeleton_info, skel, NULL,
                                  mv->joint_work, mv->joint_target);
            cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(
                &mv->skeleton_info, anim, NULL, 1.0f, 0.0f);
            cKF_SkeletonInfo_R_play(&mv->skeleton_info);
            break;
        }
    }

    mv->initialized_cat = cat;
    mv->initialized_model = idx;

    mv_reset_camera(mv);
    mv_update_title(mv);
}

/* INPUT HANDLING */

static void mv_handle_input(GAME_MODEL_VIEWER* mv) {
    int cat = mv->category;
    int count = mv_cat_count(cat);
    int changed_model = 0;

    /* X = cycle category */
    if (chkTrigger(BUTTON_X)) {
        mv->category = (cat + 1) % MV_CAT_NUM;
        cat = mv->category;
        count = mv_cat_count(cat);
        /* Force re-init */
        mv->initialized_cat = -1;
        mv_reset_camera(mv);
    }

    /* B = next model */
    if (chkTrigger(BUTTON_B)) {
        mv->cat_index[cat]++;
        if (mv->cat_index[cat] >= count) mv->cat_index[cat] = 0;
        if (cat == MV_CAT_FISH) mv->cat_index[cat] = mv_fish_skip_null(mv->cat_index[cat], 1);
        changed_model = 1;
    }

    /* A = previous model */
    if (chkTrigger(BUTTON_A)) {
        mv->cat_index[cat]--;
        if (mv->cat_index[cat] < 0) mv->cat_index[cat] = count - 1;
        if (cat == MV_CAT_FISH) mv->cat_index[cat] = mv_fish_skip_null(mv->cat_index[cat], -1);
        changed_model = 1;
    }

    /* Start = toggle animation pause */
    if (chkTrigger(BUTTON_START)) {
        mv->anim_paused ^= 1;
    }

    /* Joystick = orbit camera */
    {
        int jx = getJoystick_X();
        int jy = getJoystick_Y();
        if (jx != 0 || jy != 0) {
            mv->cam_angle_y += (f32)jx * CAM_ORBIT_SPEED * 0.02f;
            mv->cam_angle_x += (f32)jy * CAM_ORBIT_SPEED * 0.02f;
        }
    }

    /* D-pad left/right = pan */
    if (chkButton(BUTTON_DLEFT) || chkButton(BUTTON_DRIGHT)) {
        f32 right_x = cosf(mv->cam_angle_y);
        f32 right_z = -sinf(mv->cam_angle_y);
        f32 dir = chkButton(BUTTON_DLEFT) ? -s_cam_pan_speed[cat] : s_cam_pan_speed[cat];
        mv->cam_pan_x += right_x * dir;
        mv->cam_pan_z += right_z * dir;
    }

    /* Clamp pitch */
    if (mv->cam_angle_x > (f32)(PC_PI * 0.45))
        mv->cam_angle_x = (f32)(PC_PI * 0.45);
    if (mv->cam_angle_x < (f32)(-PC_PI * 0.45))
        mv->cam_angle_x = (f32)(-PC_PI * 0.45);

    /* D-pad up/down = zoom */
    if (chkButton(BUTTON_DUP)) {
        mv->cam_distance -= s_cam_zoom_speed[cat];
    }
    if (chkButton(BUTTON_DDOWN)) {
        mv->cam_distance += s_cam_zoom_speed[cat];
    }

    /* Clamp distance */
    if (mv->cam_distance < s_cam_min_dist[cat])
        mv->cam_distance = s_cam_min_dist[cat];
    if (mv->cam_distance > s_cam_max_dist[cat])
        mv->cam_distance = s_cam_max_dist[cat];

    /* Update title if model changed (without full reinit, just to show name) */
    if (changed_model) {
        mv_update_title(mv);
    }
}

/*  DRAW: COMMON SETUP (viewport, projection, lookAt) */

static void mv_draw_common_setup(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;
    int cat = mv->category;
    f32 center_y = s_cam_center_y[cat];
    f32 ex, ey, ez;

    ex = mv->cam_distance * cosf(mv->cam_angle_x) * sinf(mv->cam_angle_y);
    ey = mv->cam_distance * sinf(mv->cam_angle_x);
    ez = mv->cam_distance * cosf(mv->cam_angle_x) * cosf(mv->cam_angle_y);

    {
        GXColor clr;
        clr.r = 40; clr.g = 40; clr.b = 60; clr.a = 255;
        GXSetCopyClear(clr, 0x00FFFFFF);
    }

    OPEN_DISP(g);
    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    gSPSegment(NOW_FONT_DISP++, G_MWO_SEGMENT_0, 0);
    DisplayList_initialize(g, 40, 40, 60, NULL);
    gDPPipeSync(NOW_POLY_OPA_DISP++);
    CLOSE_DISP(g);

    /* Viewport, projection, lookAt, modelview */
    {
        Vp* vp = GRAPH_ALLOC_TYPE(g, Vp, 1);
        N64Mtx* proj_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
        N64Mtx* look_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
        N64Mtx* mv_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
        u16 perspNorm;
        f32 near_plane = (cat == MV_CAT_STRUCTURES) ? 10.0f : 1.0f;
        f32 far_plane  = (cat == MV_CAT_STRUCTURES) ? 50000.0f : 5000.0f;

        vp->vp.vscale[0] = 640 * 2;
        vp->vp.vscale[1] = 480 * 2;
        vp->vp.vscale[2] = 511;
        vp->vp.vscale[3] = 0;
        vp->vp.vtrans[0] = 640 * 2;
        vp->vp.vtrans[1] = 480 * 2;
        vp->vp.vtrans[2] = 511;
        vp->vp.vtrans[3] = 0;

        guPerspective(proj_mtx, &perspNorm, 45.0f,
                      640.0f / 480.0f, near_plane, far_plane, 1.0f);

        guLookAt(look_mtx,
                 ex + mv->cam_pan_x, ey + center_y, ez + mv->cam_pan_z,
                 mv->cam_pan_x, center_y, mv->cam_pan_z,
                 0.0f, 1.0f, 0.0f);
        guMtxIdent(mv_mtx);

        OPEN_DISP(g);

        gDPSetScissor(NOW_POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
        gSPViewport(NOW_POLY_OPA_DISP++, vp);
        gSPPerspNormalize(NOW_POLY_OPA_DISP++, perspNorm);
        gSPMatrix(NOW_POLY_OPA_DISP++, proj_mtx,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(NOW_POLY_OPA_DISP++, look_mtx,
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        gSPMatrix(NOW_POLY_OPA_DISP++, mv_mtx,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        CLOSE_DISP(g);
    }
}

/* DRAW: COMMON LIGHTING & FOG (Possibly should remove fog) */

static void mv_draw_common_lights(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;

    OPEN_DISP(g);

    gDPPipeSync(NOW_POLY_OPA_DISP++);
    gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);
    gDPSetEnvColor(NOW_POLY_OPA_DISP++, 255, 255, 255, 255);

    {
        static Lights1 default_light = gdSPDefLights1(
            /* ambient  */ 80, 80, 80,
            /* diffuse  */ 200, 200, 200,
            /* direction*/ 40, 100, 80
        );
        gSPSetLights1(NOW_POLY_OPA_DISP++, default_light);
    }

    gDPSetFogColor(NOW_POLY_OPA_DISP++, 0, 0, 0, 0);
    gSPFogPosition(NOW_POLY_OPA_DISP++, 999, 1000);

    CLOSE_DISP(g);
}

/* DRAW: STRUCTURES */

static void mv_draw_structures(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;
    int idx = mv->cat_index[MV_CAT_STRUCTURES];

    _texture_z_light_fog_prim(g);
    mv_draw_common_lights(mv);

    /* Set palette segments and pre-load TLUT */
    OPEN_DISP(g);
    {
        const MVModelEntry* entry = &s_model_table[idx];
        u16* pal;
        if (entry->pal_idx >= 0) {
            pal = entry->is_winter ? structure_pal_adrs_winter[entry->pal_idx]
                                   : structure_pal_adrs_nowinter[entry->pal_idx];
        } else {
            ATTRIBUTE_ALIGN(32) static u16 dummy_palette[16];
            static int pal_init = 0;
            if (!pal_init) {
                int i;
                for (i = 0; i < 16; i++)
                    dummy_palette[i] = 0xFFFF;
                pal_init = 1;
            }
            pal = dummy_palette;
        }
        gSPSegment(NOW_POLY_OPA_DISP++, 0x08, pal);
        gSPSegment(NOW_POLY_OPA_DISP++, 0x09, pal);
        gSPSegment(NOW_POLY_OPA_DISP++, 0x0A, pal);
        gDPLoadTLUT_Dolphin(NOW_POLY_OPA_DISP++, 15, 16, 1, pal);
    }
    CLOSE_DISP(g);

    /* Draw skeleton */
    {
        N64Mtx* joint_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 64);
        Matrix_push();
        Matrix_translate(0.0f, 0.0f, 0.0f, 0);
        cKF_Si3_draw_R_SV(game, &mv->skeleton_info, joint_mtx, NULL, NULL, NULL);
        Matrix_pull();
    }
}

/* DRAW: NPCs (body/eye/mouth textures, player idle animation) */

static void mv_draw_npc(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;
    int idx = mv->cat_index[MV_CAT_NPCS];
    aNPC_draw_data_c* npc = &npc_draw_data_tbl[idx];

    if (npc->model_skeleton == NULL) return;

    mv_init_dummy_cloth();

    /* NPC render mode (z_gsCPModeSet_Data[10] + prim color) */
    _texture_z_light_fog_prim_npc(g);
    mv_draw_common_lights(mv);

    OPEN_DISP(g);

    /* NPC-specific: tex edge alpha + Dolphin texture adjust (matches ac_npc_draw.c_inc) */
    gDPSetTexEdgeAlpha(NOW_POLY_OPA_DISP++, 127);
    gDPSetTextureAdjustMode(NOW_POLY_OPA_DISP++, G_TA_DOLPHIN);

    /* Eye texture => segment 0x08 */
    if (npc->tex_data.eye_texture[0] != NULL) {
        gSPSegment(NOW_POLY_OPA_DISP++, ANIME_1_TXT_SEG, npc->tex_data.eye_texture[0]);
    }

    /* Mouth texture => segment 0x09 */
    if (npc->tex_data.mouth_texture[0] != NULL) {
        gSPSegment(NOW_POLY_OPA_DISP++, ANIME_2_TXT_SEG, npc->tex_data.mouth_texture[0]);
    }

    /* Body texture => segment 0x0B + TLUT 15 */
    gSPSegment(NOW_POLY_OPA_DISP++, ANIME_4_TXT_SEG, npc->tex_data.texture);
    gDPLoadTLUT_Dolphin(NOW_POLY_OPA_DISP++, 15, 16, 1, npc->tex_data.palette);

    /* Dummy cloth => segment 0x0A + TLUT 14 */
    gSPSegment(NOW_POLY_OPA_DISP++, ANIME_3_TXT_SEG, s_dummy_cloth_tex);
    gDPLoadTLUT_Dolphin(NOW_POLY_OPA_DISP++, 14, 16, 1, s_dummy_cloth_pal);

    CLOSE_DISP(g);

    /* Draw skeleton with NPC scale */
    {
        N64Mtx* joint_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 64);
        Matrix_push();
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(npc->scale, npc->scale, npc->scale, MTX_MULT);
        cKF_Si3_draw_R_SV(game, &mv->skeleton_info, joint_mtx, NULL, NULL, NULL);
        Matrix_pull();
    }

    /* Restore tex edge alpha + N64 texture adjust */
    OPEN_DISP(g);
    gDPSetTexEdgeAlpha(NOW_POLY_OPA_DISP++, 144);
    gDPSetTextureAdjustMode(NOW_POLY_OPA_DISP++, G_TA_N64);
    CLOSE_DISP(g);
}

/* DRAW: FISH (museum fish skeletons with swimming animation) */

static void mv_draw_fish(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;
    int idx = mv->cat_index[MV_CAT_FISH];

    if (mfish_model_tbl[idx] == NULL) return;

    _texture_z_light_fog_prim(g);
    mv_draw_common_lights(mv);

    /* Draw skeleton with fish scale */
    {
        N64Mtx* joint_mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 64);
        Matrix_push();
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(FISH_SCALE, FISH_SCALE, FISH_SCALE, MTX_MULT);
        cKF_Si3_draw_R_SV(game, &mv->skeleton_info, joint_mtx, NULL, NULL, NULL);
        Matrix_pull();
    }
}

/* MAIN DRAW */

static void mv_draw(GAME_MODEL_VIEWER* mv) {
    GAME* game = (GAME*)mv;
    GRAPH* g = game->graph;
    int cat = mv->category;
    int idx = mv->cat_index[cat];

    /* Reinit model if category or index changed */
    if (cat != mv->initialized_cat || idx != mv->initialized_model) {
        mv_setup_model(mv);
    }

    /* Set cull override: only disable for structures (hollow shells) */
    g_pc_model_viewer_no_cull = (cat == MV_CAT_STRUCTURES);

    mv_draw_common_setup(mv);

    /* Category-specific draw */
    switch (cat) {
        case MV_CAT_STRUCTURES: mv_draw_structures(mv); break;
        case MV_CAT_NPCS:       mv_draw_npc(mv);        break;
        case MV_CAT_FISH:       mv_draw_fish(mv);        break;
    }

    game_debug_draw_last(game, g);
    game_draw_last(g);
}

/* SCENE ENTRY POINTS */

static void model_viewer_main(GAME* game) {
    GAME_MODEL_VIEWER* mv = (GAME_MODEL_VIEWER*)game;

    mv_handle_input(mv);
    mv_draw(mv);
}

void pc_model_viewer_init(GAME* game) {
    GAME_MODEL_VIEWER* mv = (GAME_MODEL_VIEWER*)game;
    GRAPH* g = game->graph;
    int i;

    game->exec = &model_viewer_main;
    game->cleanup = &pc_model_viewer_cleanup;

    {
        View* view = &mv->view;
        initView(view, g);
        view->flag = VIEW_UPDATE_LOOKAT | VIEW_UPDATE_SCISSOR | VIEW_UPDATE_PERSPECTIVE;
    }

    new_Matrix(game);
    SetGameFrame(1);

    for (i = 0; i < MV_CAT_NUM; i++)
        mv->cat_index[i] = 0;

    mv->category = MV_CAT_STRUCTURES;
    mv->initialized_cat = -1;
    mv->initialized_model = -1;
    mv->anim_paused = 0;

    if (g_pc_model_viewer_start >= 0 && g_pc_model_viewer_start < STRUCTURE_COUNT) {
        mv->cat_index[MV_CAT_STRUCTURES] = g_pc_model_viewer_start;
    }

    /* Fish: skip jellyfish if starting on it */
    mv->cat_index[MV_CAT_FISH] = mv_fish_skip_null(mv->cat_index[MV_CAT_FISH], 1);

    mv_reset_camera(mv);

    OSReport("[ModelViewer] Initialized: Structures=%d, NPCs=%d, Fish=%d\n",
             STRUCTURE_COUNT, NPC_COUNT, FISH_COUNT);
}

void pc_model_viewer_cleanup(GAME* game) {
    (void)game;
    g_pc_model_viewer_no_cull = 0;
    VISetWindowTitle(PC_WINDOW_TITLE);
}
