#include "ac_museum_fish_priv.h"

// extern data
// clang-format off
extern cKF_Skeleton_R_c
    cKF_bs_r_act_mus_funa_a1,
    cKF_bs_r_act_mus_hera_a1,
    cKF_bs_r_act_mus_koi_a1,
    cKF_bs_r_act_mus_nisiki_a1,
    cKF_bs_r_act_mus_namazu_a1,
    cKF_bs_r_act_mus_bass_a1,
    cKF_bs_r_act_mus_bassm_a1,
    cKF_bs_r_act_mus_bassl_a1,
    cKF_bs_r_act_mus_gill_a1,
    cKF_bs_r_act_mus_onamazu_a1,
    cKF_bs_r_act_mus_raigyo_a1,
    cKF_bs_r_act_mus_nigoi_a1,
    cKF_bs_r_act_mus_ugui_a1,
    cKF_bs_r_act_mus_oikawa_a1,
    cKF_bs_r_act_mus_tanago_a1,
    cKF_bs_r_act_mus_dojyo_a1,
    cKF_bs_r_act_mus_wakasa_a1,
    cKF_bs_r_act_mus_ayu_a1,
    cKF_bs_r_act_mus_yamame_a1,
    cKF_bs_r_act_mus_iwana_a1,
    cKF_bs_r_act_mus_niji_a1,
    cKF_bs_r_act_mus_ito_a1,
    cKF_bs_r_act_mus_sake_a1,
    cKF_bs_r_act_mus_kingyo_a1,
    cKF_bs_r_act_mus_pirania_a1,
    cKF_bs_r_act_mus_aroana_a1,
    cKF_bs_r_act_mus_unagi_a1,
    cKF_bs_r_act_mus_donko_a1,
    cKF_bs_r_act_mus_angel_a1,
    cKF_bs_r_act_mus_gupi_a1,
    cKF_bs_r_act_mus_demekin_a1,
    cKF_bs_r_act_mus_kaseki_a1,
    cKF_bs_r_act_mus_zari,
    cKF_bs_r_act_mus_kaeru_a1,
    cKF_bs_r_act_mus_medaka_a1,
    cKF_bs_r_act_mus_suzuki_a1,
    cKF_bs_r_act_mus_tai_a1,
    cKF_bs_r_act_mus_isidai_a1,
    cKF_bs_r_act_mus_pira_a1;

extern cKF_Animation_R_c
    cKF_ba_r_act_mus_funa_a1,
    cKF_ba_r_act_mus_hera_a1,
    cKF_ba_r_act_mus_koi_a1,
    cKF_ba_r_act_mus_nisiki_a1,
    cKF_ba_r_act_mus_namazu_a1,
    cKF_ba_r_act_mus_bass_a1,
    cKF_ba_r_act_mus_bassm_a1,
    cKF_ba_r_act_mus_bassl_a1,
    cKF_ba_r_act_mus_gill_a1,
    cKF_ba_r_act_mus_onamazu_a1,
    cKF_ba_r_act_mus_raigyo_a1,
    cKF_ba_r_act_mus_nigoi_a1,
    cKF_ba_r_act_mus_ugui_a1,
    cKF_ba_r_act_mus_oikawa_a1,
    cKF_ba_r_act_mus_tanago_a1,
    cKF_ba_r_act_mus_dojyo_a1,
    cKF_ba_r_act_mus_wakasa_a1,
    cKF_ba_r_act_mus_ayu_a1,
    cKF_ba_r_act_mus_yamame_a1,
    cKF_ba_r_act_mus_iwana_a1,
    cKF_ba_r_act_mus_niji_a1,
    cKF_ba_r_act_mus_ito_a1,
    cKF_ba_r_act_mus_sake_a1,
    cKF_ba_r_act_mus_kingyo_a1,
    cKF_ba_r_act_mus_pirania_a1,
    cKF_ba_r_act_mus_aroana_a1,
    cKF_ba_r_act_mus_unagi_a2,
    cKF_ba_r_act_mus_donko_a1,
    cKF_ba_r_act_mus_angel_a1,
    cKF_ba_r_act_mus_gupi_a1,
    cKF_ba_r_act_mus_demekin_a1,
    cKF_ba_r_act_mus_kaseki_a1,
    cKF_ba_r_act_mus_zari,
    cKF_ba_r_act_mus_kaeru_a1,
    cKF_ba_r_act_mus_medaka_a1,
    cKF_ba_r_act_mus_suzuki_a1,
    cKF_ba_r_act_mus_tai_a1,
    cKF_ba_r_act_mus_isidai_a1,
    cKF_ba_r_act_mus_pira_a1;
    
extern cKF_Skeleton_R_c
    cKF_bs_r_obj_museum5_kusa1,
    cKF_bs_r_obj_museum5_kusa2,
    cKF_bs_r_obj_museum5_kusa3;

extern cKF_Animation_R_c
    cKF_ba_r_obj_museum5_kusa1,
    cKF_ba_r_obj_museum5_kusa2,
    cKF_ba_r_obj_museum5_kusa3;

// data
MUSEUM_FISH_ACTOR* MF_Control_Actor;

/*  Init stuff  */
ACTOR_PROFILE Museum_Fish_Profile = {
    mAc_PROFILE_MUSEUM_FISH,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_407,
    sizeof(MUSEUM_FISH_ACTOR),
    Museum_Fish_Actor_ct,
    Museum_Fish_Actor_dt,
    Museum_Fish_Actor_move,
    Museum_Fish_Actor_draw,
    NULL
};

static xyz_t suisou_pos[5] = { 
    { 220.0f, 40.0f, 220.0f }, 
    { 420.0f, 40.0f, 220.0f }, 
    { 220.0f, 40.0f, 460.0f }, 
    { 420.0f, 40.0f, 460.0f }, 
    { 320.0f, 40.0f,  20.0f } 
};

int kusa_group_tbl[14] = {
    mfish_TANK_0,
    mfish_TANK_2,
    mfish_TANK_1,
    mfish_TANK_3,
    mfish_TANK_3,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_0,
    mfish_TANK_2,
    mfish_TANK_1,
    mfish_TANK_3,
};

xyz_t kusa_pos[14] = {
    { 179.0f, 40.0f, 170.0f },
    { 253.0f, 40.0f, 495.0f },
    { 376.0f, 40.0f, 260.0f },
    { 397.0f, 40.0f, 412.0f },
    { 467.0f, 40.0f, 432.0f },
    { 141.0f, 40.0f, -18.0f },
    { 206.0f, 40.0f, -25.0f },
    { 346.0f, 40.0f, -38.0f },
    { 473.0f, 40.0f, -29.0f },
    { 495.0f, 40.0f, -21.0f },
    { 210.0f, 40.0f, 215.0f },
    { 266.0f, 40.0f, 507.0f },
    { 393.0f, 40.0f, 270.0f },
    { 415.0f, 40.0f, 415.0f }
};

xyz_t hasu_pos = { 420, 0, 220 };

xyz_t suisou_awa_pos[20] = {
    { 150.0f, 60.0f, -12.0f },
    { 192.0f, 60.0f, -20.0f },
    { 216.0f, 60.0f,  -4.0f }, 
    { 300.0f, 60.0f, -42.0f },
    { 332.0f, 60.0f, -28.0f },
    { 356.0f, 60.0f, -46.0f },
    { 416.0f, 60.0f, -28.0f },
    { 456.0f, 60.0f,  20.0f }, 
    { 190.0f, 60.0f, 173.0f },
    { 196.0f, 60.0f, 186.0f },
    { 232.0f, 60.0f, 178.0f },
    { 372.0f, 60.0f, 254.0f },
    { 388.0f, 60.0f, 270.0f },
    { 434.0f, 60.0f, 173.0f },
    { 180.0f, 60.0f, 408.0f },
    { 256.0f, 60.0f, 512.0f },
    { 270.0f, 60.0f, 500.0f },
    { 406.0f, 60.0f, 414.0f },
    { 458.0f, 60.0f, 424.0f },
    { 447.0f, 60.0f, 442.0f }
};

s16 suisou_awa_group[20] = { 
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_4,
    mfish_TANK_0,
    mfish_TANK_0,
    mfish_TANK_0,
    mfish_TANK_1,
    mfish_TANK_1,
    mfish_TANK_1,
    mfish_TANK_2,
    mfish_TANK_2,
    mfish_TANK_2,
    mfish_TANK_3,
    mfish_TANK_3,
    mfish_TANK_3,
};

cKF_Skeleton_R_c* mfish_model_tbl[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ &cKF_bs_r_act_mus_funa_a1,
/* BROOK_TROUT      */ &cKF_bs_r_act_mus_hera_a1,
/* CARP             */ &cKF_bs_r_act_mus_koi_a1,
/* KOI              */ &cKF_bs_r_act_mus_nisiki_a1,
/* CATFISH          */ &cKF_bs_r_act_mus_namazu_a1,
/* SMALL_BASS       */ &cKF_bs_r_act_mus_bass_a1,
/* BASS             */ &cKF_bs_r_act_mus_bassm_a1,
/* LARGE_BASS       */ &cKF_bs_r_act_mus_bassl_a1,
/* BLUEGILL         */ &cKF_bs_r_act_mus_gill_a1,
/* GIANT_CATFISH    */ &cKF_bs_r_act_mus_onamazu_a1,
/* GIANT_SNAKEHEAD  */ &cKF_bs_r_act_mus_raigyo_a1,
/* BARBEL_STEED     */ &cKF_bs_r_act_mus_nigoi_a1,
/* DACE             */ &cKF_bs_r_act_mus_ugui_a1,
/* PALE_CHUB        */ &cKF_bs_r_act_mus_oikawa_a1,
/* BITTERLING       */ &cKF_bs_r_act_mus_tanago_a1,
/* LOACH            */ &cKF_bs_r_act_mus_dojyo_a1,
/* POND_SMELT       */ &cKF_bs_r_act_mus_wakasa_a1,
/* SWEETFISH        */ &cKF_bs_r_act_mus_ayu_a1,
/* CHERRY_SALMON    */ &cKF_bs_r_act_mus_yamame_a1,
/* LARGE_CHAR       */ &cKF_bs_r_act_mus_iwana_a1,
/* RAINBOW_TROUT    */ &cKF_bs_r_act_mus_niji_a1,
/* STRINGFISH       */ &cKF_bs_r_act_mus_ito_a1,
/* SALMON           */ &cKF_bs_r_act_mus_sake_a1,
/* GOLDFISH         */ &cKF_bs_r_act_mus_kingyo_a1,
/* PIRANHA          */ &cKF_bs_r_act_mus_pirania_a1,
/* AROWANA          */ &cKF_bs_r_act_mus_aroana_a1,
/* EEL              */ &cKF_bs_r_act_mus_unagi_a1,
/* FRESHWATER_GOBY  */ &cKF_bs_r_act_mus_donko_a1,
/* ANGELFISH        */ &cKF_bs_r_act_mus_angel_a1,
/* GUPPY            */ &cKF_bs_r_act_mus_gupi_a1,
/* POPEYED_GOLDFISH */ &cKF_bs_r_act_mus_demekin_a1,
/* COELACANTH       */ &cKF_bs_r_act_mus_kaseki_a1,
/* CRAWFISH         */ &cKF_bs_r_act_mus_zari,
/* FROG             */ &cKF_bs_r_act_mus_kaeru_a1,
/* KILLIFISH        */ &cKF_bs_r_act_mus_medaka_a1,
/* JELLYFISH        */ NULL,
/* SEA_BASS         */ &cKF_bs_r_act_mus_suzuki_a1,
/* RED_SNAPPER      */ &cKF_bs_r_act_mus_tai_a1,
/* BARRED_KNIFEJAW  */ &cKF_bs_r_act_mus_isidai_a1,
/* ARAPAIMA         */ &cKF_bs_r_act_mus_pira_a1
};

cKF_Animation_R_c* mfish_anime_init_tbl[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ &cKF_ba_r_act_mus_funa_a1,
/* BROOK_TROUT      */ &cKF_ba_r_act_mus_hera_a1,
/* CARP             */ &cKF_ba_r_act_mus_koi_a1,
/* KOI              */ &cKF_ba_r_act_mus_nisiki_a1,
/* CATFISH          */ &cKF_ba_r_act_mus_namazu_a1,
/* SMALL_BASS       */ &cKF_ba_r_act_mus_bass_a1,
/* BASS             */ &cKF_ba_r_act_mus_bassm_a1,
/* LARGE_BASS       */ &cKF_ba_r_act_mus_bassl_a1,
/* BLUEGILL         */ &cKF_ba_r_act_mus_gill_a1,
/* GIANT_CATFISH    */ &cKF_ba_r_act_mus_onamazu_a1,
/* GIANT_SNAKEHEAD  */ &cKF_ba_r_act_mus_raigyo_a1,
/* BARBEL_STEED     */ &cKF_ba_r_act_mus_nigoi_a1,
/* DACE             */ &cKF_ba_r_act_mus_ugui_a1,
/* PALE_CHUB        */ &cKF_ba_r_act_mus_oikawa_a1,
/* BITTERLING       */ &cKF_ba_r_act_mus_tanago_a1,
/* LOACH            */ &cKF_ba_r_act_mus_dojyo_a1,
/* POND_SMELT       */ &cKF_ba_r_act_mus_wakasa_a1,
/* SWEETFISH        */ &cKF_ba_r_act_mus_ayu_a1,
/* CHERRY_SALMON    */ &cKF_ba_r_act_mus_yamame_a1,
/* LARGE_CHAR       */ &cKF_ba_r_act_mus_iwana_a1,
/* RAINBOW_TROUT    */ &cKF_ba_r_act_mus_niji_a1,
/* STRINGFISH       */ &cKF_ba_r_act_mus_ito_a1,
/* SALMON           */ &cKF_ba_r_act_mus_sake_a1,
/* GOLDFISH         */ &cKF_ba_r_act_mus_kingyo_a1,
/* PIRANHA          */ &cKF_ba_r_act_mus_pirania_a1,
/* AROWANA          */ &cKF_ba_r_act_mus_aroana_a1,
/* EEL              */ &cKF_ba_r_act_mus_unagi_a2,
/* FRESHWATER_GOBY  */ &cKF_ba_r_act_mus_donko_a1,
/* ANGELFISH        */ &cKF_ba_r_act_mus_angel_a1,
/* GUPPY            */ &cKF_ba_r_act_mus_gupi_a1,
/* POPEYED_GOLDFISH */ &cKF_ba_r_act_mus_demekin_a1,
/* COELACANTH       */ &cKF_ba_r_act_mus_kaseki_a1,
/* CRAWFISH         */ &cKF_ba_r_act_mus_zari,
/* FROG             */ &cKF_ba_r_act_mus_kaeru_a1,
/* KILLIFISH        */ &cKF_ba_r_act_mus_medaka_a1,
/* JELLYFISH        */ NULL,
/* SEA_BASS         */ &cKF_ba_r_act_mus_suzuki_a1,
/* RED_SNAPPER      */ &cKF_ba_r_act_mus_tai_a1,
/* BARRED_KNIFEJAW  */ &cKF_ba_r_act_mus_isidai_a1,
/* ARAPAIMA         */ &cKF_ba_r_act_mus_pira_a1
};

MUSEUM_FISH_INIT_DATA mfish_init_data[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ { 0.0100f, 3.8f,  7.5f,  74.0f,  0.400f, 0.450f, 0.98995f,    0.2f, 0.40f,  -3.5f,  -6.0f, 120,  120, DEG2SHORT_ANGLE(70) },
/* BROOK_TROUT      */ { 0.0100f, 4.6f,  7.0f,  78.0f,  0.400f, 0.600f, 0.98995f,    0.2f, 0.40f,  -3.5f,  -6.0f, 100,  160, DEG2SHORT_ANGLE(70) },
/* CARP             */ { 0.0100f, 6.0f, 10.6f,  80.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.60f,  -5.0f,  -9.0f, 100,  150, DEG2SHORT_ANGLE(90) },
/* KOI              */ { 0.0100f, 6.0f, 10.7f,  85.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.60f,  -5.0f,  -9.0f, 100,  120, DEG2SHORT_ANGLE(90) },
/* CATFISH          */ { 0.0110f, 6.0f, 13.6f,  63.0f,  0.050f, 0.075f, 0.995f,      0.4f, 0.85f,  -2.5f, -10.0f, 600,  900, DEG2SHORT_ANGLE(60) },
/* SMALL_BASS       */ { 0.0110f, 3.0f,  8.0f,  85.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.30f,  -4.0f,  -6.0f, 100,  100, DEG2SHORT_ANGLE(70) },
/* BASS             */ { 0.0110f, 4.7f,  9.8f,  92.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.60f,  -5.0f,  -8.0f, 150,  110, DEG2SHORT_ANGLE(70) },
/* LARGE_BASS       */ { 0.0110f, 5.5f, 12.0f,  90.0f,  0.600f, 0.500f, 0.97468f,    0.2f, 0.80f,  -5.5f, -10.0f, 160,  120, DEG2SHORT_ANGLE(70) },
/* BLUEGILL         */ { 0.0100f, 4.3f,  6.1f,  95.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.30f,  -3.5f,  -5.0f,  80,   80, DEG2SHORT_ANGLE(70) },
/* GIANT_CATFISH    */ { 0.0120f, 7.6f, 19.4f,  65.0f,  0.075f, 0.150f, 0.995f,      0.4f, 0.95f,  -6.0f, -18.0f, 720, 1000, DEG2SHORT_ANGLE(60) },
/* GIANT_SNAKEHEAD  */ { 0.0120f, 9.6f, 20.8f,  65.0f,  0.050f, 0.100f, 0.98488998f, 0.4f, 0.95f, -13.0f, -19.0f, 240,  480, DEG2SHORT_ANGLE(90) },
/* BARBEL_STEED     */ { 0.0100f, 4.8f, 10.5f, 102.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.70f,  -3.5f,  -9.0f, 150,  120, DEG2SHORT_ANGLE(70) },
/* DACE             */ { 0.0100f, 3.0f, 10.6f,  75.0f,  0.750f, 1.500f, 0.94867998f, 0.2f, 0.60f,  -4.5f,  -8.0f, 480,  150, DEG2SHORT_ANGLE(45) },
/* PALE_CHUB        */ { 0.0100f, 2.5f,  7.0f,  90.0f,  0.050f, 0.475f, 0.94867998f, 0.4f, 0.30f,  -3.5f,  -6.0f, 240,  200, DEG2SHORT_ANGLE(50) },
/* BITTERLING       */ { 0.0100f, 3.5f,  6.0f,  76.0f,  0.350f, 0.400f, 0.98995f,    0.4f, 0.40f,  -3.0f,  -6.0f, 100,  120, DEG2SHORT_ANGLE(45) },
/* LOACH            */ { 0.0100f, 4.0f,  6.4f,  65.0f,  0.100f, 0.150f, 0.89442998f, 0.4f, 0.20f,  -2.0f,  -6.0f, 240,  240, DEG2SHORT_ANGLE(50) },
/* POND_SMELT       */ { 0.0100f, 2.0f,  6.0f,  96.0f,  0.100f, 0.450f, 0.92194998f, 0.2f, 0.10f,  -3.5f,  -6.0f, 300,  120, DEG2SHORT_ANGLE(50) },
/* SWEETFISH        */ { 0.0100f, 3.0f,  9.8f,  75.0f,  1.000f, 1.500f, 0.94867998f, 0.2f, 0.50f,  -3.5f,  -7.5f, 480,  120, DEG2SHORT_ANGLE(45) },
/* CHERRY_SALMON    */ { 0.0100f, 3.5f,  9.3f,  85.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.50f,  -3.0f,  -8.0f, 540,  120, DEG2SHORT_ANGLE(45) },
/* LARGE_CHAR       */ { 0.0100f, 2.5f, 10.6f,  80.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.70f,  -3.0f,  -9.0f, 600,  140, DEG2SHORT_ANGLE(70) },
/* RAINBOW_TROUT    */ { 0.0100f, 2.5f,  8.8f,  80.0f,  0.500f, 1.000f, 0.94867998f, 0.2f, 0.50f,  -4.0f,  -7.0f, 660,  160, DEG2SHORT_ANGLE(45) },
/* STRINGFISH       */ { 0.0120f, 6.1f, 19.8f,  75.0f,  0.050f, 0.100f, 0.98488998f, 0.4f, 0.95f, -14.0f, -19.0f, 360,  720, DEG2SHORT_ANGLE(90) },
/* SALMON           */ { 0.0140f, 6.2f, 15.0f,  80.0f,  0.300f, 1.000f, 0.995f,      0.1f, 0.70f,  -6.0f, -10.0f, 120,  220, DEG2SHORT_ANGLE(40) },
/* GOLDFISH         */ { 0.0080f, 2.2f,  4.9f,  90.0f,  0.000f, 0.250f, 0.89442998f, 0.2f, 0.10f,  -1.5f,  -3.0f, 120,  240, DEG2SHORT_ANGLE(50) },
/* PIRANHA          */ { 0.0120f, 4.2f,  7.0f,  75.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.40f,  -3.5f,  -6.0f, 240,  240, DEG2SHORT_ANGLE(90) },
/* AROWANA          */ { 0.0130f, 5.0f, 13.4f,  70.0f,  0.500f, 0.750f, 0.98995f,    0.2f, 0.60f,  -4.5f, -12.0f, 240,  300, DEG2SHORT_ANGLE(60) },
/* EEL              */ { 0.0095f, 3.4f, 15.0f,  55.0f,  0.200f, 0.250f, 0.98995f,    0.6f, 0.70f, -13.5f,  -4.0f,  60, 1120, DEG2SHORT_ANGLE(70) },
/* FRESHWATER_GOBY  */ { 0.0120f, 3.3f,  8.0f,  75.0f,  0.300f, 0.600f, 0.97468f,    0.2f, 0.20f,  -2.0f,  -7.0f, 240,  240, DEG2SHORT_ANGLE(70) },
/* ANGELFISH        */ { 0.0100f, 5.1f,  6.0f,  85.0f,  0.200f, 0.200f, 0.94867998f, 0.5f, 0.20f,  -3.0f,  -4.0f, 120,  360, DEG2SHORT_ANGLE(50) },
/* GUPPY            */ { 0.0080f, 2.7f,  4.9f,  96.0f,  0.200f, 0.400f, 0.89442998f, 0.5f, 0.10f,  -3.0f,  -3.0f, 120,  360, DEG2SHORT_ANGLE(30) },
/* POPEYED_GOLDFISH */ { 0.0080f, 2.5f,  4.9f, 102.0f,  0.000f, 0.250f, 0.89442998f, 0.2f, 0.10f,  -2.0f,  -3.0f, 120,  240, DEG2SHORT_ANGLE(50) },
/* COELACANTH       */ { 0.0160f, 7.1f, 22.8f,  65.0f,  0.100f, 0.300f, 0.98995f,    0.4f, 0.85f,  -2.5f, -20.5f, 300,  420, DEG2SHORT_ANGLE(20) },
/* CRAWFISH         */ { 0.0165f, 5.8f, 10.4f,  70.0f, -0.050f, 0.150f, 0.94867998f, 0.2f, 0.40f,   5.0f, -14.0f, 120,  180, DEG2SHORT_ANGLE(70) },
/* FROG             */ { 0.0100f, 1.0f,  1.0f,  70.0f,  0.500f, 0.500f, 0.94867998f, 0.2f, 0.40f,  -1.0f,  -9.0f, 120,  180, DEG2SHORT_ANGLE(70) },
/* KILLIFISH        */ { 0.0080f, 1.5f,  3.9f, 102.0f,  0.150f, 0.400f, 0.89442998f, 0.1f, 0.40f,  -1.0f,  -3.0f, 120,  360, DEG2SHORT_ANGLE(30) },
/* JELLYFISH        */ { 0.0100f, 4.0f,  5.5f,  70.0f,  0.200f, 0.150f, 0.94867998f, 0.1f, 0.40f,  -1.0f,  -3.0f,  60,  120, DEG2SHORT_ANGLE(70) },
/* SEA_BASS         */ { 0.0100f, 4.0f,  9.5f,  80.0f,  0.300f, 0.800f, 0.995f,      0.1f, 0.75f,  -3.5f,  -5.0f, 160,  200, DEG2SHORT_ANGLE(25) },
/* RED_SNAPPER      */ { 0.0100f, 6.0f, 11.4f,  90.0f,  0.250f, 0.350f, 0.995f,      0.2f, 0.45f,  -6.0f,  -6.5f, 120,  240, DEG2SHORT_ANGLE(30) },
/* BARRED_KNIFEJAW  */ { 0.0100f, 5.0f, 10.9f,  95.0f,  0.250f, 0.450f, 0.995f,      0.2f, 0.40f,  -5.0f,  -6.0f, 120,  240, DEG2SHORT_ANGLE(30) },
/* ARAPAIMA         */ { 0.0120f, 9.3f, 31.5f,  75.0f,  0.050f, 0.100f, 0.97468f,    0.2f, 0.90f, -14.0f, -31.0f, 240,  480, DEG2SHORT_ANGLE(90) }
};

s16 mfish_group_tbl[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ mfish_TANK_0, 
/* BROOK_TROUT      */ mfish_TANK_0, 
/* CARP             */ mfish_TANK_0, 
/* KOI              */ mfish_TANK_0, 
/* CATFISH          */ mfish_TANK_1, 
/* SMALL_BASS       */ mfish_TANK_1, 
/* BASS             */ mfish_TANK_1, 
/* LARGE_BASS       */ mfish_TANK_1, 
/* BLUEGILL         */ mfish_TANK_1, 
/* GIANT_CATFISH    */ mfish_TANK_1, 
/* GIANT_SNAKEHEAD  */ mfish_TANK_3, 
/* BARBEL_STEED     */ mfish_TANK_0, 
/* DACE             */ mfish_TANK_2, 
/* PALE_CHUB        */ mfish_TANK_2, 
/* BITTERLING       */ mfish_TANK_0, 
/* LOACH            */ mfish_TANK_1, 
/* POND_SMELT       */ mfish_TANK_2, 
/* SWEETFISH        */ mfish_TANK_2, 
/* CHERRY_SALMON    */ mfish_TANK_2, 
/* LARGE_CHAR       */ mfish_TANK_2,
/* RAINBOW_TROUT    */ mfish_TANK_2, 
/* STRINGFISH       */ mfish_TANK_2, 
/* SALMON           */ mfish_TANK_4, 
/* GOLDFISH         */ mfish_TANK_0, 
/* PIRANHA          */ mfish_TANK_3, 
/* AROWANA          */ mfish_TANK_3, 
/* EEL              */ mfish_TANK_0, 
/* FRESHWATER_GOBY  */ mfish_TANK_1, 
/* ANGELFISH        */ mfish_TANK_3, 
/* GUPPY            */ mfish_TANK_3, 
/* POPEYED_GOLDFISH */ mfish_TANK_0, 
/* COELACANTH       */ mfish_TANK_4, 
/* CRAWFISH         */ mfish_TANK_2, 
/* FROG             */ mfish_TANK_1, 
/* KILLIFISH        */ mfish_TANK_0, 
/* JELLYFISH        */ mfish_TANK_4, 
/* SEA_BASS         */ mfish_TANK_4, 
/* RED_SNAPPER      */ mfish_TANK_4, 
/* BARRED_KNIFEJAW  */ mfish_TANK_4, 
/* ARAPAIMA         */ mfish_TANK_3,
};

PRIV_FISH_CONSTRUCTOR mfish_ct[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ mfish_afish_ct,
/* BROOK_TROUT      */ mfish_afish_ct,
/* CARP             */ mfish_koi_ct,
/* KOI              */ mfish_koi_ct,
/* CATFISH          */ mfish_namazu_ct,
/* SMALL_BASS       */ mfish_bass_ct,
/* BASS             */ mfish_bass_ct,
/* LARGE_BASS       */ mfish_bass_ct,
/* BLUEGILL         */ mfish_bass_ct,
/* GIANT_CATFISH    */ mfish_namazu_ct,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_ct,
/* BARBEL_STEED     */ mfish_koi_ct,
/* DACE             */ mfish_ani_base_ct,
/* PALE_CHUB        */ mfish_small_fish_ct,
/* BITTERLING       */ mfish_afish_ct,
/* LOACH            */ mfish_dojou_ct,
/* POND_SMELT       */ mfish_small_fish_ct,
/* SWEETFISH        */ mfish_ani_base_ct,
/* CHERRY_SALMON    */ mfish_ani_base_ct,
/* LARGE_CHAR       */ mfish_ani_base_ct,
/* RAINBOW_TROUT    */ mfish_ani_base_ct,
/* STRINGFISH       */ mfish_ito_ct,
/* SALMON           */ mfish_seafish_ct,
/* GOLDFISH         */ mfish_kingyo_ct,
/* PIRANHA          */ mfish_ani_base_ct,
/* AROWANA          */ mfish_aroana_ct,
/* EEL              */ mfish_unagi_ct,
/* FRESHWATER_GOBY  */ mfish_donko_ct,
/* ANGELFISH        */ mfish_small_fish_ct,
/* GUPPY            */ mfish_gupi_ct,
/* POPEYED_GOLDFISH */ mfish_kingyo_ct,
/* COELACANTH       */ mfish_kaseki_ct,
/* CRAWFISH         */ mfish_zarigani_ct,
/* FROG             */ mfish_kaeru_ct,
/* KILLIFISH        */ mfish_medaka_ct,
/* JELLYFISH        */ mfish_kurage_ct,
/* SEA_BASS         */ mfish_seafish_ct,
/* RED_SNAPPER      */ mfish_tai_ct,
/* BARRED_KNIFEJAW  */ mfish_tai_ct,
/* ARAPAIMA         */ mfish_big_fish_ct
};

PRIV_FISH_MOVE mfish_mv[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ mfish_afish_mv,
/* BROOK_TROUT      */ mfish_afish_mv,
/* CARP             */ mfish_koi_mv,
/* KOI              */ mfish_koi_mv,
/* CATFISH          */ mfish_namazu_mv,
/* SMALL_BASS       */ mfish_bass_mv,
/* BASS             */ mfish_bass_mv,
/* LARGE_BASS       */ mfish_bass_mv,
/* BLUEGILL         */ mfish_bass_mv,
/* GIANT_CATFISH    */ mfish_namazu_mv,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_mv,
/* BARBEL_STEED     */ mfish_koi_mv,
/* DACE             */ mfish_ani_base_mv,
/* PALE_CHUB        */ mfish_small_fish_mv,
/* BITTERLING       */ mfish_afish_mv,
/* LOACH            */ mfish_dojou_mv,
/* POND_SMELT       */ mfish_small_fish_mv,
/* SWEETFISH        */ mfish_ani_base_mv,
/* CHERRY_SALMON    */ mfish_ani_base_mv,
/* LARGE_CHAR       */ mfish_ani_base_mv,
/* RAINBOW_TROUT    */ mfish_ani_base_mv,
/* STRINGFISH       */ mfish_ito_mv,
/* SALMON           */ mfish_seafish_mv,
/* GOLDFISH         */ mfish_kingyo_mv,
/* PIRANHA          */ mfish_ani_base_mv,
/* AROWANA          */ mfish_aroana_mv,
/* EEL              */ mfish_unagi_mv,
/* FRESHWATER_GOBY  */ mfish_donko_mv,
/* ANGELFISH        */ mfish_small_fish_mv,
/* GUPPY            */ mfish_gupi_mv,
/* POPEYED_GOLDFISH */ mfish_kingyo_mv,
/* COELACANTH       */ mfish_kaseki_mv,
/* CRAWFISH         */ mfish_zarigani_mv,
/* FROG             */ mfish_kaeru_mv,
/* KILLIFISH        */ mfish_medaka_mv,
/* JELLYFISH        */ mfish_kurage_mv,
/* SEA_BASS         */ mfish_seafish_mv,
/* RED_SNAPPER      */ mfish_tai_mv,
/* BARRED_KNIFEJAW  */ mfish_tai_mv,
/* ARAPAIMA         */ mfish_big_fish_mv
};


PRIV_FISH_DRAW mfish_dw[aGYO_TYPE_NUM] = {
/* CRUCIAN_CARP     */ mfish_afish_dw,
/* BROOK_TROUT      */ mfish_afish_dw,
/* CARP             */ mfish_koi_dw,
/* KOI              */ mfish_koi_dw,
/* CATFISH          */ mfish_namazu_dw,
/* SMALL_BASS       */ mfish_bass_dw,
/* BASS             */ mfish_bass_dw,
/* LARGE_BASS       */ mfish_bass_dw,
/* BLUEGILL         */ mfish_bass_dw,
/* GIANT_CATFISH    */ mfish_namazu_dw,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_dw,
/* BARBEL_STEED     */ mfish_koi_dw,
/* DACE             */ mfish_ani_base_dw,
/* PALE_CHUB        */ mfish_small_fish_dw,
/* BITTERLING       */ mfish_afish_dw,
/* LOACH            */ mfish_dojou_dw,
/* POND_SMELT       */ mfish_small_fish_dw,
/* SWEETFISH        */ mfish_ani_base_dw,
/* CHERRY_SALMON    */ mfish_ani_base_dw,
/* LARGE_CHAR       */ mfish_ani_base_dw,
/* RAINBOW_TROUT    */ mfish_ani_base_dw,
/* STRINGFISH       */ mfish_ito_dw,
/* SALMON           */ mfish_seafish_dw,
/* GOLDFISH         */ mfish_kingyo_dw,
/* PIRANHA          */ mfish_ani_base_dw,
/* AROWANA          */ mfish_aroana_dw,
/* EEL              */ mfish_unagi_dw,
/* FRESHWATER_GOBY  */ mfish_donko_dw,
/* ANGELFISH        */ mfish_small_fish_dw,
/* GUPPY            */ mfish_gupi_dw,
/* POPEYED_GOLDFISH */ mfish_kingyo_dw,
/* COELACANTH       */ mfish_kaseki_dw,
/* CRAWFISH         */ mfish_zarigani_dw,
/* FROG             */ mfish_kaeru_dw,
/* KILLIFISH        */ mfish_medaka_dw,
/* JELLYFISH        */ mfish_kurage_dw,
/* SEA_BASS         */ mfish_ani_base_dw,
/* RED_SNAPPER      */ mfish_tai_dw,
/* BARRED_KNIFEJAW  */ mfish_tai_dw,
/* ARAPAIMA         */ mfish_big_fish_dw
};

#include "../src/actor/ac_museum_fish_base.c_inc"

// clang-format on

void Museum_Fish_Prv_data_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, int fishNum, int r6) {
    actor->fish_idx = fishNum;
    actor->init_data = mfish_init_data[fishNum];
    actor->tank = mfish_group_tbl[fishNum];

    if (actor->tank >= 0) {
        actor->position = suisou_pos[actor->tank];
    } else {
        actor->position = ZeroVec;
    }

    actor->position.y = mfish_init_data[fishNum]._0C + RANDOM2_F(10);
    if (r6 == 1) {
        actor->position.x += RANDOM2_F(90.f);
        actor->position.z += RANDOM2_F(90.f);
    }
    actor->currentProcess = &mfish_normal_process;
    mfish_ct[fishNum](actor, game);
}

// clang-format off
cKF_Skeleton_R_c* kusa_model[14] = {
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3
};
cKF_Animation_R_c* kusa_anime[14]= {
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3
};

float kusa_start_frame[14] = {
    25.0f, 0.0f, 25.0f, 0.0f, 50.0f, 0.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, 25.0f, 0.0f, 75.0f
};
// clang-format on

void Museum_Fish_Actor_ct(ACTOR* actorx, GAME* gamex) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    int i;
    MUSEUM_FISH_PRIVATE_DATA* prv;
    MF_Control_Actor = actor;
    actor->player_area_update_timer = 0x1e;
    actor->logic_accum = 0.0f;

    mfish_point_light_ct(actorx, gamex);

    for (i = 0; i < 14; i++) {
        actor->prvKusa[i]._54C = kusa_model[i];
        cKF_SkeletonInfo_R_ct(&actor->prvKusa[i].keyframe, kusa_model[i], kusa_anime[i], actor->prvKusa[i].work,
                              actor->prvKusa[i].morph);
        cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(&actor->prvKusa[i].keyframe, kusa_anime[i], NULL,
                                                                 kusa_group_tbl[i] == mfish_TANK_2 ? 1.5f : 0.5f, 0.0f);
        actor->prvKusa[i].keyframe.frame_control.current_frame = kusa_start_frame[i];
        actor->prvKusa[i]._538.x = qrand();
        actor->prvKusa[i]._538.z = qrand();
    }

    if (mMmd_FishInfo(aGYO_TYPE_FROG)) {
        actor->prvFish[aGYO_TYPE_FROG].hasu_p = &actor->_14788;
    } else {
        mfish_hasu_ct(&actor->_14788, gamex);
    }

    prv = actor->prvFish;
    for (i = 0; i < aGYO_TYPE_NUM; i++, prv++) {
        prv->_62E_flags &= ~1;
        if (mMmd_FishInfo(i)) {
            prv->kf._54C = mfish_model_tbl[i];
            prv->kf._550[0] = mfish_anime_init_tbl[i];
            prv->_62E_flags |= 1;
            Museum_Fish_Prv_data_init(prv, gamex, i, 1);
        }
    }

    for (i = 0; i < 20; i++) {
        actor->_14d50[i] = RANDOMF_RANGE(40, 120);
        actor->_14d78[i] = RANDOMF_RANGE(2, 5);
    }
}

void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game) {
    mfish_point_light_dt(actor, game);
}

int Museum_Fish_GetMsgNo(MUSEUM_FISH_ACTOR* actor) {
    static u8 item_name[mIN_ITEM_NAME_LEN];
    int itemArticle;
    mMsg_Window_c* msg;

    int fishInfo = actor->fishDisplayMsgInfo[actor->fishDisplayMsgIter].fishInfo;
    mActor_name_t fishName = mNT_FishIdx2FishItemNo(actor->fishDisplayMsgInfo[actor->fishDisplayMsgIter].fishName);
    mIN_copy_name_str(item_name, fishName);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), 0, item_name, 0x10, mIN_get_item_article(fishName));

    if (fishInfo >= 1 && fishInfo <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), 0,
                          common_data.save.save.private_data[fishInfo - 1].player_ID.player_name, 8);
    }

    if (actor->fishDisplayMsgIter < actor->numFishDisplayed - 1) {
        if (fishInfo >= 1 && fishInfo <= 4) {
            return MSG_12194;
        } else {
            return MSG_12195;
        }
    }

    if (fishInfo >= 1 && fishInfo <= 4) {
        return MSG_12191;
    } else {
        return MSG_12192;
    }
}

BOOL Museum_Fish_Check_Talk_Distance(GAME* gamex, int index) {
    s16 subAngle;
    xyz_t pos;
    ACTOR* playerx;

    // fish tank locations?
    static xyz_t kanban_pos[5] = { { 260.0f, 40.0f, 300.0f },
                                   { 460.0f, 40.0f, 300.0f },
                                   { 260.0f, 40.0f, 540.0f },
                                   { 460.0f, 40.0f, 540.0f },
                                   { 500.0f, 40.0f, 60.0f } };

    playerx = GET_PLAYER_ACTOR_GAME_ACTOR(gamex);
    subAngle = DEG2SHORT_ANGLE(-180) + playerx->world.angle.y;
    xyz_t_sub(&playerx->world.position, &kanban_pos[index], &pos);

    if (ABS(pos.x) < 20.0f && ABS(pos.z) < 20.0f && ABS(subAngle) < 0x3000) {
        return TRUE;
    }
    return FALSE;
}

void Museum_Fish_Set_MsgFishInfo(MUSEUM_FISH_ACTOR* actor, int param2) {
    // MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    int i;
    // defines how many fish are in each grouping of fish names
    static int group_max_num[5] = { 10, 9, 9, 6, 6 };
    static int group_A_fish_name[10] = {
        aGYO_TYPE_CRUCIAN_CARP,     aGYO_TYPE_BROOK_TROUT, aGYO_TYPE_CARP, aGYO_TYPE_KOI,
        aGYO_TYPE_BARBEL_STEED,     aGYO_TYPE_BITTERLING,  aGYO_TYPE_EEL,  aGYO_TYPE_GOLDFISH,
        aGYO_TYPE_POPEYED_GOLDFISH, aGYO_TYPE_KILLIFISH,
    };
    static int group_B_fish_name[9] = {
        aGYO_TYPE_CATFISH, aGYO_TYPE_GIANT_CATFISH, aGYO_TYPE_LOACH,           aGYO_TYPE_BLUEGILL, aGYO_TYPE_SMALL_BASS,
        aGYO_TYPE_BASS,    aGYO_TYPE_LARGE_BASS,    aGYO_TYPE_FRESHWATER_GOBY, aGYO_TYPE_FROG,
    };
    static int group_C_fish_name[9] = {
        aGYO_TYPE_DACE,       aGYO_TYPE_PALE_CHUB,     aGYO_TYPE_POND_SMELT,
        aGYO_TYPE_SWEETFISH,  aGYO_TYPE_CHERRY_SALMON, aGYO_TYPE_RAINBOW_TROUT,
        aGYO_TYPE_LARGE_CHAR, aGYO_TYPE_STRINGFISH,    aGYO_TYPE_CRAWFISH,
    };
    static int group_D_fish_name[6] = {
        aGYO_TYPE_GIANT_SNAKEHEAD, aGYO_TYPE_GUPPY,   aGYO_TYPE_ANGELFISH,
        aGYO_TYPE_PIRANHA,         aGYO_TYPE_AROWANA, aGYO_TYPE_ARAPAIMA,
    };
    static int group_E_fish_name[6] = {
        aGYO_TYPE_SALMON,   aGYO_TYPE_COELACANTH,  aGYO_TYPE_JELLYFISH,
        aGYO_TYPE_SEA_BASS, aGYO_TYPE_RED_SNAPPER, aGYO_TYPE_BARRED_KNIFEJAW,
    };

    static int* group_fish_name[5] = {
        group_A_fish_name, group_B_fish_name, group_C_fish_name, group_D_fish_name, group_E_fish_name,
    };

    actor->numFishDisplayed = 0;
    actor->fishDisplayMsgIter = 0;
    for (i = 0; i < group_max_num[param2]; i++) {
        s16 fishName = group_fish_name[param2][i];
        s16 fishInfo = mMmd_FishInfo(fishName); // is this fish on display?
        if (fishInfo != 0) {
            actor->fishDisplayMsgInfo[actor->numFishDisplayed].fishName = fishName; // add info to list
            actor->fishDisplayMsgInfo[actor->numFishDisplayed].fishInfo = fishInfo;
            actor->numFishDisplayed++; // incrememnt counter of fish on display
        }
    }

    return;
}

void Museum_Fish_set_talk_info(ACTOR* actorx) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    static rgba_t window_color = { 255, 255, 205, 255 };
    int msg_no;
    if (actor->numFishDisplayed > 0) { // maybe related to if there are fish in the tank
        msg_no = Museum_Fish_GetMsgNo(actor);
        actor->fishDisplayMsgIter++; // maybe iterating through the fish donation record, given which fish are donated?
    } else {
        msg_no = MSG_12193;
    }

    mDemo_Set_msg_num(msg_no);
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

void Museum_Fish_Talk_process(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    // MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    if (mDemo_Check(mDemo_TYPE_SPEAK, (ACTOR*)actor) != 0) {
        s_xyz rotation = GET_PLAYER_ACTOR_GAME_ACTOR(game)->shape_info.rotation;
        add_calc_short_angle2(&rotation.y, DEG2SHORT_ANGLE(-180), 0.3f, DEG2SHORT_ANGLE(22.5f), 0);
        GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, NULL, &rotation, 32);
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) != 0) {
            int choseNum = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            if (choseNum != -1) {
                if (choseNum == 0) {
                    mMsg_Window_c* windowC;
                    int msgNum = Museum_Fish_GetMsgNo(actor);
                    actor->fishDisplayMsgIter += 1;
                    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), msgNum);
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                } else {
                    mMsg_Set_CancelNormalContinue(mMsg_Get_base_window_p());
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                }
            }
        }
    } else if (chkTrigger(BUTTON_A) != 0 && mDemo_Get_talk_actor() == 0) {
        int i;
        for (i = 0; i < 5; i++) {
            if (Museum_Fish_Check_Talk_Distance(game, i)) {
                Museum_Fish_Set_MsgFishInfo(actor, i);
                mDemo_Request(mDemo_TYPE_SPEAK, (ACTOR*)actor, &Museum_Fish_set_talk_info);
            }
        }
    }
}

static void Museum_Fish_RunBubbleTick(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    int i;

    for (i = 0; i < 20; i++) {
        actor->_14d50[i]--;
        if (actor->_14d50[i] < 0) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_SUISOU_AWA, suisou_awa_pos[i], 2, 0, game, RSV_NO,
                                       suisou_awa_group[i], 0);
            if (actor->_14d78[i] > 0) {
                actor->_14d78[i]--;
                actor->_14d50[i] = RANDOMF_RANGE(2, 10);
            } else {
                actor->_14d50[i] = RANDOMF_RANGE(80, 240);
                actor->_14d78[i] = RANDOMF_RANGE(2, 5);
            }
        }
    }
}

static void Museum_Fish_UpdatePlayerArea(MUSEUM_FISH_ACTOR* actor, GAME* game);

static void Museum_Fish_RunLogicTick(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    MUSEUM_FISH_PRIVATE_DATA* prv;
    int i;
    int j;

    Museum_Fish_UpdatePlayerArea(actor, game);

    for (j = 0; j < 14; j++) {
        cKF_SkeletonInfo_R_play(&actor->prvKusa[j].keyframe);
        if (kusa_group_tbl[j] == mfish_TANK_2) {
            add_calc2(&actor->prvKusa[j]._540.x, -4.0f, 0.5f, 0.5f);
            add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(3.5f), CALC_EASE2(0.1f), 22, 4);
        } else {
            actor->prvKusa[j]._540.x *= DTCONV_GAME(0.98f, game);
            add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(0), CALC_EASE2(0.1f), 22, 4);
        }
        actor->prvKusa[j]._540.z *= DTCONV_GAME(0.98f, game);

        actor->prvKusa[j]._538.x += actor->prvKusa[j]._538.y;
        actor->prvKusa[j]._538.z += actor->prvKusa[j]._538.y >> 1;

        add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(0), CALC_EASE2(0.1f), 22, 4);
    }

    Museum_Fish_Kusa_Check(actor, game);
    Museum_Fish_Object_Check(actor, game);
    Museum_Fish_RunBubbleTick(actor, game);

    prv = actor->prvFish;
    for (i = 0; i < aGYO_TYPE_NUM; i++, prv++) {
        if (prv->_62E_flags & 1) {
            mfish_mv[i](prv, game);
        }
    }

    if ((actor->prvFish[aGYO_TYPE_FROG]._62E_flags & 1) == 0) {
        mfish_hasu_mv(&actor->_14788, game);
    }

    for (i = 0; i < 5; i++) {
        if (i == 2) {
            actor->_14daa[i] += (s16)DEG2SHORT_ANGLE2((float)GETREG(TAKREG, 31) * 0.1f + 0.5f + RANDOM_F(1));
        } else {
            actor->_14daa[i] += 8;
        }
    }
}

static void Museum_Fish_RunFixedTicks(MUSEUM_FISH_ACTOR* actor, GAME* game, int ticks) {
    double saved_dt;
    int tick;

    if (ticks <= 0) {
        return;
    }

    /* Fixed-step museum logic calls dt-aware helpers, so each tick must look like one frame. */
    saved_dt = game->graph->dt_num_60fps_frames;
    game->graph->dt_num_60fps_frames = 1.0f;
    for (tick = 0; tick < ticks; tick++) {
        Museum_Fish_RunLogicTick(actor, game);
    }
    game->graph->dt_num_60fps_frames = saved_dt;
}

static void Museum_Fish_UpdatePlayerArea(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    MUSEUM_FISH_PRIVATE_DATA* prv;
    xyz_t p;
    s16 oldplayer_area = actor->player_area;
    int i;

    mfish_get_player_area(actor, game);
    if (actor->player_area == oldplayer_area) {
        return;
    }

    if (actor->player_area == mfish_TANK_3) {
        actor->prvFish[aGYO_TYPE_GOLDFISH].activityFrameCount = 0;
        actor->prvFish[aGYO_TYPE_POPEYED_GOLDFISH].activityFrameCount = 0;
        actor->prvFish[aGYO_TYPE_PIRANHA].activityFrameCount = 0;
    } else if (actor->player_area == mfish_TANK_0) {
        actor->prvFish[aGYO_TYPE_CARP].activityFrameCount = 20;
        actor->prvFish[aGYO_TYPE_KOI].activityFrameCount = 20;
    }

    p = GET_PLAYER_ACTOR_GAME_ACTOR(game)->world.position;
    prv = actor->prvFish;
    for (i = 0; i < aGYO_TYPE_NUM; i++, prv++) {
        f32 distance = search_position_distanceXZ(&p, &prv->position);

        if (actor->player_area == prv->tank && distance < 60.0f) {
            prv->activityFrameCount = RANDOM_F(60);
        }
    }
}

void Museum_Fish_Actor_move(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    int ticks;

    mfish_point_light_mv(actor, game);
    Museum_Fish_Talk_process(actor, game);

    ticks = graph_dt_60hz_ticks(game, &actor->logic_accum);
    Museum_Fish_RunFixedTicks(actor, game, ticks);
}

extern Gfx obj_suisou1_model[];
extern Gfx obj_suisou1_modelT[];

extern Gfx obj_museum5_model[];
extern Gfx obj_museum5_modelT[];

void Museum_Fish_Suisou_draw(ACTOR* actorx, GAME* game, int r5) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = play->game.graph;
    if (r5 < 4) {
        xyz_t* p = &suisou_pos[r5];
        if (mfish_cull_check(game, &suisou_pos[r5], 350.0f, 20.0f, 650.0f)) {
            Matrix_translate(suisou_pos[r5].x, 0, suisou_pos[r5].z, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

            OPEN_DISP(graph);
            gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            Setpos_HiliteReflect_xlu_init(&suisou_pos[r5], play);

            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_suisou1_model);
            gSPDisplayList(NEXT_POLY_XLU_DISP, obj_suisou1_modelT);

            CLOSE_DISP(graph);

            if ((actor->prvFish[aGYO_TYPE_FROG]._62E_flags & 1) == 0) {
                mfish_hasu_dw(&actor->_14788, game);
            }
        }
    } else if (mfish_cull_check(game, &suisou_pos[4], 215.0f, 25.0f, 0.0f)) {
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_LOAD);
        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        Setpos_HiliteReflect_xlu_init(&suisou_pos[r5], play);

        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_museum5_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum5_modelT);
        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);
        CLOSE_DISP(graph);
    }
}

BOOL kusa_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                      void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    MUSEUM_FISH_KUSA_DATA* actor = (MUSEUM_FISH_KUSA_DATA*)arg;
    if (joint_idx > 0) {
        f32 v = (actor->_54C == &cKF_bs_r_obj_museum5_kusa3) ? 35.0f : 20.f;

        joint_rot->y += (s16)(sin_s(actor->_538.x + (joint_idx * DEG2SHORT_ANGLE(90))) * 1274.0f);
        joint_rot->x += (s16)(sin_s(actor->_538.z + (joint_idx * DEG2SHORT_ANGLE(90))) * 4369.0f);

        joint_pos->y -= actor->_540.x * (v * joint_idx);
        joint_pos->z += actor->_540.z * (v * joint_idx);
    }
    return TRUE;
}

void Museum_Fish_Kusa_Draw(ACTOR* actorx, GAME* game, int r5) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    if (mfish_cull_check(game, &kusa_pos[r5], 0.0f, 0.0f, 120.0f)) {
        N64Mtx* mtx;
        if (play->game.frame_counter % 2 != 0) {
            mtx = actor->prvKusa[r5].mtx[0];
        } else {
            mtx = actor->prvKusa[r5].mtx[1];
        }
        OPEN_DISP(game->graph);
        Matrix_translate(kusa_pos[r5].x, 0, kusa_pos[r5].z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        CLOSE_DISP(game->graph);
        cKF_Si3_draw_R_SV(game, &actor->prvKusa[r5].keyframe, mtx, kusa_before_disp, NULL, &actor->prvKusa[r5]);
    }
}

extern EVW_ANIME_DATA obj_suisou1_evw_anime, obj_museum5_evw_anime;
extern Gfx act_mus_fish_set_mode;

void Museum_Fish_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int i;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    if (!GETREG(TAKREG, 90)) {
        for (i = 0; i < 14; i++) {
            Museum_Fish_Kusa_Draw(actorx, game, i);
        }
    }

    if (!GETREG(TAKREG, 92)) {
        MUSEUM_FISH_PRIVATE_DATA* prv;
        GRAPH* graph;
        graph = play->game.graph;
        OPEN_DISP(graph);
        gSPDisplayList(NEXT_POLY_OPA_DISP, &act_mus_fish_set_mode);
        CLOSE_DISP(graph);

        prv = actor->prvFish;
        for (i = 0; i < aGYO_TYPE_NUM; i++, prv++) {
            if (prv->_62E_flags & 1 && prv->fish_idx != aGYO_TYPE_JELLYFISH && prv->fish_idx != aGYO_TYPE_FROG &&
                mfish_cull_check(game, &prv->objchk_pos, prv->init_data._08 + 50.0f, prv->init_data._08 + 10.0f,
                                 prv->init_data._08 + 10.0f)) {
                mfish_dw[i](prv, game);
            }
        }

        if (actor->prvFish[aGYO_TYPE_JELLYFISH]._62E_flags & 1 &&
            mfish_cull_check(game, &actor->prvFish[aGYO_TYPE_JELLYFISH].position,
                             actor->prvFish[aGYO_TYPE_JELLYFISH].init_data._08 + 10.0f,
                             actor->prvFish[aGYO_TYPE_JELLYFISH].init_data.ofs_y,
                             actor->prvFish[aGYO_TYPE_JELLYFISH].init_data.ofs_y)) {
            mfish_dw[0x23](&actor->prvFish[aGYO_TYPE_JELLYFISH], game);
        }

        if (!GETREG(TAKREG, 82)) {
            mfish_normal_light_set(actorx, game);
        }

        if (actor->prvFish[aGYO_TYPE_FROG]._62E_flags & 1) {
            mfish_dw[aGYO_TYPE_FROG](&actor->prvFish[aGYO_TYPE_FROG], game);
        }

        if (GETREG(TAKREG, 82) == 1) {
            mfish_normal_light_set(actorx, game);
        }
    }

    if (!GETREG(TAKREG, 91)) {
        if (!GETREG(TAKREG, 88)) {
            Evw_Anime_Set(play, &obj_museum5_evw_anime);
            Museum_Fish_Suisou_draw(actorx, game, 0x5);
        }

        for (i = 0; i < 4; i++) {
            Evw_Anime_Set(play, &obj_suisou1_evw_anime);
            Museum_Fish_Suisou_draw(actorx, game, i);
        }
    }
}

BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y) {
    xyz_t screenPos;
    Game_play_Projection_Trans((GAME_PLAY*)game, worldPos, &screenPos);
    if ((-x < screenPos.x) && (screenPos.x < x + 320) && (-y < screenPos.y) && (screenPos.y < _y + 240)) {
        return TRUE;
    }
    return FALSE;
}

void mfish_point_ligh_pos_get(ACTOR* actorx, GAME* game, int lightIndex) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 extentRight, extentLeft, extentUp, extentDown;
    xyz_t playerPosition, vecToPlayer, lightPos, tankPos;

    int tankIndex;
    f32 distLightToPlayer;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    playerPosition = player->actor_class.world.position;

    if (playerPosition.z < 100.0f) {
        tankIndex = 4;
    } else if (playerPosition.z > 100.0f && playerPosition.z < 340.0f) {
        if (lightIndex == 0) {
            tankIndex = 0;
        } else {
            tankIndex = 1;
        }
    } else if (playerPosition.z > 340.0f && playerPosition.z < 580.0f) {
        if (lightIndex == 0) {
            tankIndex = 2;
        } else {
            tankIndex = 3;
        }
    } else {
        return;
    }

    if (tankIndex < 4) {
        extentRight = 60.0f;
        extentLeft = 60.0f;
        extentUp = 60.0f;
        extentDown = 60.0f;
        tankPos = suisou_pos[tankIndex];
        lightPos = playerPosition;
    } else {
        extentRight = 200.0f;
        extentLeft = 200.0f;
        extentUp = 35.0f;
        extentDown = 20.0f;
        tankPos = suisou_pos[tankIndex];
        lightPos = playerPosition;
        if (lightIndex == 0) {
            lightPos.x -= extentDown;
        } else {
            lightPos.x += extentDown;
        }
    }

    if (lightPos.x > tankPos.x + extentRight) {
        lightPos.x = tankPos.x + extentRight;
    } else if (lightPos.x < tankPos.x - extentLeft) {
        lightPos.x = tankPos.x - extentLeft;
    }

    if (lightPos.z > tankPos.z + extentUp) {
        lightPos.z = tankPos.z + extentUp;
    } else if (lightPos.z < tankPos.z - extentDown) {
        lightPos.z = tankPos.z - extentDown;
    }

    actor->lightPosition[lightIndex] = lightPos;

    xyz_t_sub(&lightPos, &playerPosition, &vecToPlayer);

    distLightToPlayer = sqrtf(SQ(vecToPlayer.x) + SQ(vecToPlayer.z));

    actor->lightPower[lightIndex] = (u8)(((60.0f - CLAMP(distLightToPlayer, 0.0f, 60.0f)) / 60.0f) * 55.0f);
}

void mfish_point_light_ct(ACTOR* _actor, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)_actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    // fill in the light positions
    mfish_point_ligh_pos_get(&actor->actor, game, 0);
    mfish_point_ligh_pos_get(&actor->actor, game, 1);
    // make the lights
    actor->lightID1 = mEnv_ReservePointLight(play, &actor->lightPosition[0], 0, 150, 255, (u8)actor->lightPower[0]);
    actor->lightID2 = mEnv_ReservePointLight(play, &actor->lightPosition[1], 0, 150, 255, (u8)actor->lightPower[1]);
    actor->_14dc0 = 0;
}

void mfish_point_light_dt(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (actor->lightID1 != -1) {
        mEnv_CancelReservedPointLight(actor->lightID1, (GAME_PLAY*)game);
    }

    if (actor->lightID2 != -1) {
        mEnv_CancelReservedPointLight(actor->lightID2, (GAME_PLAY*)game);
    }
}

void mfish_point_light_mv(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    mfish_point_ligh_pos_get(&actor->actor, game, 0);
    mfish_point_ligh_pos_get(&actor->actor, game, 1);

    mEnv_OperateReservedPointLight(actor->lightID1, &actor->lightPosition[0], 0, 150, 255, (u8)actor->lightPower[0]);
    mEnv_OperateReservedPointLight(actor->lightID2, &actor->lightPosition[1], 0, 150, 255, (u8)actor->lightPower[1]);
    actor->actor.world.position = actor->lightPosition[0];
    actor->actor.world.position.x = sin_s(actor->_14dc0) * 200.0f;
    actor->actor.world.position.y = sin_s(actor->_14dc0 * 2) * 10.0f;
    actor->actor.world.position.z = cos_s(actor->_14dc0) * 200.0f;
    actor->_14dc0 += F32_TO_S16((f32)DEG2SHORT_ANGLE(1.5f) * dt);
}

void mfish_normal_light_set(ACTOR* actor, GAME* game) {
    LightsN* lights;
    GAME_PLAY* play = (GAME_PLAY*)game;

    xyz_t lightPos;
    lightPos.x = 320;
    lightPos.y = 0;
    lightPos.z = 240;

    lights = Global_light_read(&play->global_light, play->game.graph);
    LightsN_list_check(lights, play->global_light.list, &lightPos);
    LightsN_disp(lights, play->game.graph);
}
