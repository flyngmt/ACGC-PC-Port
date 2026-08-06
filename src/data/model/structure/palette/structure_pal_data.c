#include "types.h"

// TODO: we should probably make these individual files and include them
// in one top level TU for organization

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_a_pal[16] = {
    #include "assets/obj_s_house1_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_b_pal[16] = {
    #include "assets/obj_s_house1_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_c_pal[16] = {
    #include "assets/obj_s_house1_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_d_pal[16] = {
    #include "assets/obj_s_house1_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house1_e_pal[16] = {
    #include "assets/obj_s_house1_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_e_pal[16] = {
    #include "assets/obj_s_house2_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_d_pal[16] = {
    #include "assets/obj_s_house2_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_c_pal[16] = {
    #include "assets/obj_s_house2_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_b_pal[16] = {
    #include "assets/obj_s_house2_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house2_a_pal[16] = {
    #include "assets/obj_s_house2_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_e_pal[16] = {
    #include "assets/obj_s_house3_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_d_pal[16] = {
    #include "assets/obj_s_house3_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_c_pal[16] = {
    #include "assets/obj_s_house3_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_b_pal[16] = {
    #include "assets/obj_s_house3_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house3_a_pal[16] = {
    #include "assets/obj_s_house3_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_e_pal[16] = {
    #include "assets/obj_s_house4_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_d_pal[16] = {
    #include "assets/obj_s_house4_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_c_pal[16] = {
    #include "assets/obj_s_house4_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_b_pal[16] = {
    #include "assets/obj_s_house4_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house4_a_pal[16] = {
    #include "assets/obj_s_house4_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_e_pal[16] = {
    #include "assets/obj_s_house5_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_d_pal[16] = {
    #include "assets/obj_s_house5_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_c_pal[16] = {
    #include "assets/obj_s_house5_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_b_pal[16] = {
    #include "assets/obj_s_house5_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house5_a_pal[16] = {
    #include "assets/obj_s_house5_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_a_pal[16] = {
    #include "assets/obj_w_house1_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_b_pal[16] = {
    #include "assets/obj_w_house1_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_c_pal[16] = {
    #include "assets/obj_w_house1_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_d_pal[16] = {
    #include "assets/obj_w_house1_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house1_e_pal[16] = {
    #include "assets/obj_w_house1_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_e_pal[16] = {
    #include "assets/obj_w_house2_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_d_pal[16] = {
    #include "assets/obj_w_house2_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_c_pal[16] = {
    #include "assets/obj_w_house2_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_b_pal[16] = {
    #include "assets/obj_w_house2_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house2_a_pal[16] = {
    #include "assets/obj_w_house2_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_e_pal[16] = {
    #include "assets/obj_w_house3_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_d_pal[16] = {
    #include "assets/obj_w_house3_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_c_pal[16] = {
    #include "assets/obj_w_house3_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_b_pal[16] = {
    #include "assets/obj_w_house3_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house3_a_pal[16] = {
    #include "assets/obj_w_house3_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_e_pal[16] = {
    #include "assets/obj_w_house4_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_d_pal[16] = {
    #include "assets/obj_w_house4_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_c_pal[16] = {
    #include "assets/obj_w_house4_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_b_pal[16] = {
    #include "assets/obj_w_house4_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house4_a_pal[16] = {
    #include "assets/obj_w_house4_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_e_pal[16] = {
    #include "assets/obj_w_house5_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_d_pal[16] = {
    #include "assets/obj_w_house5_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_c_pal[16] = {
    #include "assets/obj_w_house5_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_b_pal[16] = {
    #include "assets/obj_w_house5_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_house5_a_pal[16] = {
    #include "assets/obj_w_house5_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_a_pal[16] = {
    #include "assets/obj_s_myhome_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_b_pal[16] = {
    #include "assets/obj_s_myhome_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_d_pal[16] = {
    #include "assets/obj_s_myhome_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_c_pal[16] = {
    #include "assets/obj_s_myhome_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_e_pal[16] = {
    #include "assets/obj_s_myhome_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_f_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_f_pal[16] = {
    #include "assets/obj_s_myhome_f_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_g_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_g_pal[16] = {
    #include "assets/obj_s_myhome_g_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_h_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_h_pal[16] = {
    #include "assets/obj_s_myhome_h_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_i_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_i_pal[16] = {
    #include "assets/obj_s_myhome_i_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_j_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_j_pal[16] = {
    #include "assets/obj_s_myhome_j_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_k_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_k_pal[16] = {
    #include "assets/obj_s_myhome_k_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_l_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_l_pal[16] = {
    #include "assets/obj_s_myhome_l_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_a_pal[16] = {
    #include "assets/obj_w_myhome_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_b_pal[16] = {
    #include "assets/obj_w_myhome_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_d_pal[16] = {
    #include "assets/obj_w_myhome_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_c_pal[16] = {
    #include "assets/obj_w_myhome_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_e_pal[16] = {
    #include "assets/obj_w_myhome_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_f_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_f_pal[16] = {
    #include "assets/obj_w_myhome_f_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_g_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_g_pal[16] = {
    #include "assets/obj_w_myhome_g_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_h_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_h_pal[16] = {
    #include "assets/obj_w_myhome_h_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_i_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_i_pal[16] = {
    #include "assets/obj_w_myhome_i_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_j_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_j_pal[16] = {
    #include "assets/obj_w_myhome_j_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_k_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_k_pal[16] = {
    #include "assets/obj_w_myhome_k_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_l_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_myhome_l_pal[16] = {
    #include "assets/obj_w_myhome_l_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop1_pal[16] = {
    #include "assets/obj_shop1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop1_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop1_winter_pal[16] = {
    #include "assets/obj_shop1_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop2_pal[16] = {
    #include "assets/obj_shop2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop2_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop2_winter_pal[16] = {
    #include "assets/obj_shop2_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop3_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop3_pal[16] = {
    #include "assets/obj_shop3_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop3_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop3_winter_pal[16] = {
    #include "assets/obj_shop3_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop4_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop4_pal[16] = {
    #include "assets/obj_shop4_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_shop4_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_shop4_winter_pal[16] = {
    #include "assets/obj_shop4_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 br_shop_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 br_shop_pal[16] = {
    #include "assets/br_shop_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 br_shop_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 br_shop_winter_pal[16] = {
    #include "assets/br_shop_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_post_office_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_post_office_pal[16] = {
    #include "assets/obj_s_post_office_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_post_office_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_post_office_winter_pal[16] = {
    #include "assets/obj_s_post_office_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_a_pal[16] = {
    #include "assets/obj_s_station1_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_b_pal[16] = {
    #include "assets/obj_s_station1_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_c_pal[16] = {
    #include "assets/obj_s_station1_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_d_pal[16] = {
    #include "assets/obj_s_station1_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station1_e_pal[16] = {
    #include "assets/obj_s_station1_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_a_pal[16] = {
    #include "assets/obj_s_station2_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_b_pal[16] = {
    #include "assets/obj_s_station2_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_c_pal[16] = {
    #include "assets/obj_s_station2_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_d_pal[16] = {
    #include "assets/obj_s_station2_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station2_e_pal[16] = {
    #include "assets/obj_s_station2_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_a_pal[16] = {
    #include "assets/obj_s_station3_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_b_pal[16] = {
    #include "assets/obj_s_station3_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_c_pal[16] = {
    #include "assets/obj_s_station3_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_d_pal[16] = {
    #include "assets/obj_s_station3_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_station3_e_pal[16] = {
    #include "assets/obj_s_station3_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_a_pal[16] = {
    #include "assets/obj_w_station1_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_b_pal[16] = {
    #include "assets/obj_w_station1_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_c_pal[16] = {
    #include "assets/obj_w_station1_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_d_pal[16] = {
    #include "assets/obj_w_station1_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station1_e_pal[16] = {
    #include "assets/obj_w_station1_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_a_pal[16] = {
    #include "assets/obj_w_station2_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_d_pal[16] = {
    #include "assets/obj_w_station2_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_b_pal[16] = {
    #include "assets/obj_w_station2_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_c_pal[16] = {
    #include "assets/obj_w_station2_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station2_e_pal[16] = {
    #include "assets/obj_w_station2_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_a_pal[16] = {
    #include "assets/obj_w_station3_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_d_pal[16] = {
    #include "assets/obj_w_station3_d_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_b_pal[16] = {
    #include "assets/obj_w_station3_b_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_c_pal[16] = {
    #include "assets/obj_w_station3_c_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_station3_e_pal[16] = {
    #include "assets/obj_w_station3_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_train1_a1_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_train1_a1_pal[16] = {
    #include "assets/obj_train1_a1_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_train1_a1_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_train1_a1_winter_pal[16] = {
    #include "assets/obj_train1_a1_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_train1_a2_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_train1_a2_pal[16] = {
    #include "assets/obj_train1_a2_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_train1_a2_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_train1_a2_winter_pal[16] = {
    #include "assets/obj_train1_a2_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_police_box_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_police_box_pal[16] = {
    #include "assets/obj_police_box_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_police_box_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_police_box_winter_pal[16] = {
    #include "assets/obj_police_box_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 reserve_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 reserve_pal[16] = {
    #include "assets/reserve_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 reserve_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 reserve_winter_pal[16] = {
    #include "assets/reserve_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_buggy_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_buggy_pal[16] = {
    #include "assets/obj_buggy_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_buggy_winter_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_buggy_winter_pal[16] = {
    #include "assets/obj_buggy_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 s_car_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 s_car_pal[16] = {
    #include "assets/s_car_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_kamakura_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_kamakura_pal[16] = {
    #include "assets/obj_w_kamakura_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_shrine_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_shrine_pal[16] = {
    #include "assets/obj_s_shrine_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_shrine_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_shrine_pal[16] = {
    #include "assets/obj_w_shrine_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_goza_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_goza_pal[16] = {
    #include "assets/obj_e_goza_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_radio_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_radio_pal[16] = {
    #include "assets/obj_e_radio_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_yatai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_yatai_pal[16] = {
    #include "assets/obj_e_yatai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_tukimi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_tukimi_pal[16] = {
    #include "assets/obj_e_tukimi_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_mikuji_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_mikuji_pal[16] = {
    #include "assets/obj_e_mikuji_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_count_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_count_pal[16] = {
    #include "assets/obj_e_count_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_count02_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_count02_pal[16] = {
    #include "assets/obj_e_count02_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_kago_r_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_kago_r_pal[16] = {
    #include "assets/obj_e_kago_r_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_kago_w_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_kago_w_pal[16] = {
    #include "assets/obj_e_kago_w_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_turi_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_turi_pal[16] = {
    #include "assets/obj_e_turi_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_koinobori_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_koinobori_a_pal[16] = {
    #include "assets/obj_e_koinobori_a_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_dump_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_dump_pal[16] = {
    #include "assets/obj_dump_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_w_windmill_a_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_windmill_a_pal[16] = {
    #include "assets/obj_w_windmill_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_w_windmill_b_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_windmill_b_pal[16] = {
    #include "assets/obj_w_windmill_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_w_windmill_c_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_windmill_c_pal[16] = {
    #include "assets/obj_w_windmill_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_w_windmill_d_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_windmill_d_pal[16] = {
    #include "assets/obj_w_windmill_d_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_w_windmill_e_pal[0x20 / sizeof(u16)];
#else
u16 obj_w_windmill_e_pal[16] = {
    #include "assets/obj_w_windmill_e_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_windmill_a_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_windmill_a_pal[16] = {
    #include "assets/obj_s_windmill_a_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_windmill_b_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_windmill_b_pal[16] = {
    #include "assets/obj_s_windmill_b_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_windmill_c_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_windmill_c_pal[16] = {
    #include "assets/obj_s_windmill_c_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_windmill_d_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_windmill_d_pal[16]  = {
    #include "assets/obj_s_windmill_d_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_windmill_e_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_windmill_e_pal[16] = {
    #include "assets/obj_s_windmill_e_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_01_lotus_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_01_lotus_pal[16] = {
    #include "assets/obj_01_lotus_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_e_mikanbox_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_e_mikanbox_pal[16] = {
    #include "assets/obj_e_mikanbox_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_douzou_dai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_douzou_dai_pal[16] = {
    #include "assets/obj_s_douzou_dai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_douzou_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_douzou_pal[16] = {
    #include "assets/obj_w_douzou_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_toudai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_toudai_pal[16] = {
    #include "assets/obj_s_toudai_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_toudai_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_toudai_pal[16] = {
    #include "assets/obj_w_toudai_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_museum_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_museum_pal[16] = {
    #include "assets/obj_s_museum_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 obj_s_museum_winter_pal[0x20 / sizeof(u16)];
#else
u16 obj_s_museum_winter_pal[16] = {
    #include "assets/obj_s_museum_winter_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_boat_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_boat_pal[16] = {
    #include "assets/obj_s_boat_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_tailor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_tailor_pal[16] = {
    #include "assets/obj_s_tailor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_w_tailor_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_w_tailor_pal[16] = {
    #include "assets/obj_w_tailor_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_island_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_myhome_island_pal[16] = {
    #include "assets/obj_s_myhome_island_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 obj_s_house_i_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 obj_s_house_i_pal[16] = {
    #include "assets/obj_s_house_i_pal.inc"
};
#endif
