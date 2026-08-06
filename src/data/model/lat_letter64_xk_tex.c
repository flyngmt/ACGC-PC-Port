#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 lat_letter01_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 lat_letter01_pal[] = {
#include "assets/lat_letter01_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter02_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter02_pal[] = {
#include "assets/lat_letter02_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter03_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter03_pal[] = {
#include "assets/lat_letter03_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter04_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter04_pal[] = {
#include "assets/lat_letter04_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter05_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter05_pal[] = {
#include "assets/lat_letter05_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter06_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter06_pal[] = {
#include "assets/lat_letter06_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter07_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter07_pal[] = {
#include "assets/lat_letter07_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter08_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter08_pal[] = {
#include "assets/lat_letter08_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter09_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter09_pal[] = {
#include "assets/lat_letter09_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter10_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter10_pal[] = {
#include "assets/lat_letter10_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter11_1_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter11_1_pal[] = {
#include "assets/lat_letter11_1_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter12_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter12_pal[] = {
#include "assets/lat_letter12_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter13_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter13_pal[] = {
#include "assets/lat_letter13_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter14_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter14_pal[] = {
#include "assets/lat_letter14_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter15_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter15_pal[] = {
#include "assets/lat_letter15_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter16_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter16_pal[] = {
#include "assets/lat_letter16_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter17_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter17_pal[] = {
#include "assets/lat_letter17_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter18_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter18_pal[] = {
#include "assets/lat_letter18_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter19_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter19_pal[] = {
#include "assets/lat_letter19_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter20_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter20_pal[] = {
#include "assets/lat_letter20_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter21_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter21_pal[] = {
#include "assets/lat_letter21_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter22_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter22_pal[] = {
#include "assets/lat_letter22_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter23_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter23_pal[] = {
#include "assets/lat_letter23_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter24_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter24_pal[] = {
#include "assets/lat_letter24_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter25_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter25_pal[] = {
#include "assets/lat_letter25_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter26_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter26_pal[] = {
#include "assets/lat_letter26_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter27_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter27_pal[] = {
#include "assets/lat_letter27_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter28_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter28_pal[] = {
#include "assets/lat_letter28_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter65_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter65_pal[] = {
#include "assets/lat_letter65_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter30_tex[0x20];
#else
u8 lat_letter30_tex[] = {
#include "assets/lat_letter30_tex.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter31_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter31_pal[] = {
#include "assets/lat_letter31_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter32_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter32_pal[] = {
#include "assets/lat_letter32_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter33_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter33_pal[] = {
#include "assets/lat_letter33_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter34_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter34_pal[] = {
#include "assets/lat_letter34_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter35_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter35_pal[] = {
#include "assets/lat_letter35_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter36_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter36_pal[] = {
#include "assets/lat_letter36_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter37_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter37_pal[] = {
#include "assets/lat_letter37_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter39_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter39_pal[] = {
#include "assets/lat_letter39_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter40_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter40_pal[] = {
#include "assets/lat_letter40_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter42_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter42_pal[] = {
#include "assets/lat_letter42_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter43_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter43_pal[] = {
#include "assets/lat_letter43_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter44_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter44_pal[] = {
#include "assets/lat_letter44_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter45_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter45_pal[] = {
#include "assets/lat_letter45_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter46_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter46_pal[] = {
#include "assets/lat_letter46_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter47_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter47_pal[] = {
#include "assets/lat_letter47_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter48_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter48_pal[] = {
#include "assets/lat_letter48_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter49_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter49_pal[] = {
#include "assets/lat_letter49_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter50_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter50_pal[] = {
#include "assets/lat_letter50_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter51_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter51_pal[] = {
#include "assets/lat_letter51_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter52_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter52_pal[] = {
#include "assets/lat_letter52_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter53_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter53_pal[] = {
#include "assets/lat_letter53_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter54_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter54_pal[] = {
#include "assets/lat_letter54_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter55_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter55_pal[] = {
#include "assets/lat_letter55_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter56_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter56_pal[] = {
#include "assets/lat_letter56_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter57_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter57_pal[] = {
#include "assets/lat_letter57_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter58_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter58_pal[] = {
#include "assets/lat_letter58_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter59_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter59_pal[] = {
#include "assets/lat_letter59_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter60_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter60_pal[] = {
#include "assets/lat_letter60_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter61_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter61_pal[] = {
#include "assets/lat_letter61_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter62_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter62_pal[] = {
#include "assets/lat_letter62_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter63_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter63_pal[] = {
#include "assets/lat_letter63_pal.inc"
};
#endif

#ifdef TARGET_PC
u16 lat_letter64_pal[0x20 / sizeof(u16)];
#else
u16 lat_letter64_pal[] = {
#include "assets/lat_letter64_pal.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter01_01_tex[0x100];
#else
u8 lat_letter01_01_tex[] = {
#include "assets/lat_letter01_01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter01_02_tex[0x100];
#else
u8 lat_letter01_02_tex[] = {
#include "assets/lat_letter01_02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter01_03_tex[0x400];
#else
u8 lat_letter01_03_tex[] = {
#include "assets/lat_letter01_03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter01_04_tex[0x80];
#else
u8 lat_letter01_04_tex[] = {
#include "assets/lat_letter01_04_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_tegami_fusen_tex[0x80];
#else
u8 lat_tegami_fusen_tex[] = {
#include "assets/lat_tegami_fusen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter02_01_tex[0x200];
#else
u8 lat_letter02_01_tex[] = {
#include "assets/lat_letter02_01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter02_02_tex[0x200];
#else
u8 lat_letter02_02_tex[] = {
#include "assets/lat_letter02_02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter02_03_tex[0x200];
#else
u8 lat_letter02_03_tex[] = {
#include "assets/lat_letter02_03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_01_tex[0x100];
#else
u8 lat_letter03_01_tex[] = {
#include "assets/lat_letter03_01_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_02_tex[0x100];
#else
u8 lat_letter03_02_tex[] = {
#include "assets/lat_letter03_02_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_03_tex[0x100];
#else
u8 lat_letter03_03_tex[] = {
#include "assets/lat_letter03_03_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_04_tex[0x100];
#else
u8 lat_letter03_04_tex[] = {
#include "assets/lat_letter03_04_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_05_tex[0x100];
#else
u8 lat_letter03_05_tex[] = {
#include "assets/lat_letter03_05_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_06_tex[0x100];
#else
u8 lat_letter03_06_tex[] = {
#include "assets/lat_letter03_06_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter03_07_tex[0x200];
#else
u8 lat_letter03_07_tex[] = {
#include "assets/lat_letter03_07_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth2_tex[0x80];
#else
u8 lat_letter04_cloth2_tex[] = {
#include "assets/lat_letter04_cloth2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth3_tex[0x80];
#else
u8 lat_letter04_cloth3_tex[] = {
#include "assets/lat_letter04_cloth3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth4_tex[0x80];
#else
u8 lat_letter04_cloth4_tex[] = {
#include "assets/lat_letter04_cloth4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth5_tex[0x80];
#else
u8 lat_letter04_cloth5_tex[] = {
#include "assets/lat_letter04_cloth5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth6_tex[0x80];
#else
u8 lat_letter04_cloth6_tex[] = {
#include "assets/lat_letter04_cloth6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth1_tex[0x80];
#else
u8 lat_letter04_cloth1_tex[] = {
#include "assets/lat_letter04_cloth1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth7_tex[0x80];
#else
u8 lat_letter04_cloth7_tex[] = {
#include "assets/lat_letter04_cloth7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth8_tex[0x80];
#else
u8 lat_letter04_cloth8_tex[] = {
#include "assets/lat_letter04_cloth8_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_fusen_tex[0x80];
#else
u8 lat_letter04_fusen_tex[] = {
#include "assets/lat_letter04_fusen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter04_cloth9_tex[0x80];
#else
u8 lat_letter04_cloth9_tex[] = {
#include "assets/lat_letter04_cloth9_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter05_1[0x200];
#else
u8 lat_letter05_1[] = {
#include "assets/lat_letter05_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter05_2[0x100];
#else
u8 lat_letter05_2[] = {
#include "assets/lat_letter05_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter06_1[0x200];
#else
u8 lat_letter06_1[] = {
#include "assets/lat_letter06_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter06_sen[0x100];
#else
u8 lat_letter06_sen[] = {
#include "assets/lat_letter06_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter06_4[0x100];
#else
u8 lat_letter06_4[] = {
#include "assets/lat_letter06_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter06_5[0x200];
#else
u8 lat_letter06_5[] = {
#include "assets/lat_letter06_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter06_6[0x80];
#else
u8 lat_letter06_6[] = {
#include "assets/lat_letter06_6.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter07_1[0x100];
#else
u8 lat_letter07_1[] = {
#include "assets/lat_letter07_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter07_2[0x200];
#else
u8 lat_letter07_2[] = {
#include "assets/lat_letter07_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter07_sen[0x100];
#else
u8 lat_letter07_sen[] = {
#include "assets/lat_letter07_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter07_3[0x80];
#else
u8 lat_letter07_3[] = {
#include "assets/lat_letter07_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter08_1[0x200];
#else
u8 lat_letter08_1[] = {
#include "assets/lat_letter08_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter08_2[0x200];
#else
u8 lat_letter08_2[] = {
#include "assets/lat_letter08_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter08_3[0x80];
#else
u8 lat_letter08_3[] = {
#include "assets/lat_letter08_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter08_sen[0x100];
#else
u8 lat_letter08_sen[] = {
#include "assets/lat_letter08_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter09_1[0x400];
#else
u8 lat_letter09_1[] = {
#include "assets/lat_letter09_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter09_2[0x200];
#else
u8 lat_letter09_2[] = {
#include "assets/lat_letter09_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter09_3[0x100];
#else
u8 lat_letter09_3[] = {
#include "assets/lat_letter09_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter10_1[0x200];
#else
u8 lat_letter10_1[] = {
#include "assets/lat_letter10_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter10_2[0x80];
#else
u8 lat_letter10_2[] = {
#include "assets/lat_letter10_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter10_3[0x80];
#else
u8 lat_letter10_3[] = {
#include "assets/lat_letter10_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter10_sen[0x100];
#else
u8 lat_letter10_sen[] = {
#include "assets/lat_letter10_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter10_5[0x80];
#else
u8 lat_letter10_5[] = {
#include "assets/lat_letter10_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter11_1[0x400];
#else
u8 lat_letter11_1[] = {
#include "assets/lat_letter11_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter11_2[0x100];
#else
u8 lat_letter11_2[] = {
#include "assets/lat_letter11_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter12_1[0x400];
#else
u8 lat_letter12_1[] = {
#include "assets/lat_letter12_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter12_sen[0x100];
#else
u8 lat_letter12_sen[] = {
#include "assets/lat_letter12_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter13_1[0x400];
#else
u8 lat_letter13_1[] = {
#include "assets/lat_letter13_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter13_3[0x200];
#else
u8 lat_letter13_3[] = {
#include "assets/lat_letter13_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter14_1[0x400];
#else
u8 lat_letter14_1[] = {
#include "assets/lat_letter14_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter14_2[0x100];
#else
u8 lat_letter14_2[] = {
#include "assets/lat_letter14_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter14_3[0x100];
#else
u8 lat_letter14_3[] = {
#include "assets/lat_letter14_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter14_4[0x100];
#else
u8 lat_letter14_4[] = {
#include "assets/lat_letter14_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter15_1[0x200];
#else
u8 lat_letter15_1[] = {
#include "assets/lat_letter15_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter15_2[0x80];
#else
u8 lat_letter15_2[] = {
#include "assets/lat_letter15_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter16_1[0x200];
#else
u8 lat_letter16_1[] = {
#include "assets/lat_letter16_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter16_sen[0x100];
#else
u8 lat_letter16_sen[] = {
#include "assets/lat_letter16_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter16_3[0x100];
#else
u8 lat_letter16_3[] = {
#include "assets/lat_letter16_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter17_1[0x400];
#else
u8 lat_letter17_1[] = {
#include "assets/lat_letter17_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter17_sen[0x100];
#else
u8 lat_letter17_sen[] = {
#include "assets/lat_letter17_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter18_4[0x400];
#else
u8 lat_letter18_4[] = {
#include "assets/lat_letter18_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter18_5[0x100];
#else
u8 lat_letter18_5[] = {
#include "assets/lat_letter18_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter18_sen[0x100];
#else
u8 lat_letter18_sen[] = {
#include "assets/lat_letter18_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter19_1[0x400];
#else
u8 lat_letter19_1[] = {
#include "assets/lat_letter19_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter19_2[0x400];
#else
u8 lat_letter19_2[] = {
#include "assets/lat_letter19_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter20_1[0x400];
#else
u8 lat_letter20_1[] = {
#include "assets/lat_letter20_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter20_sen[0x100];
#else
u8 lat_letter20_sen[] = {
#include "assets/lat_letter20_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter21_1[0x800];
#else
u8 lat_letter21_1[] = {
#include "assets/lat_letter21_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter21_sen[0x100];
#else
u8 lat_letter21_sen[] = {
#include "assets/lat_letter21_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter22_1[0x200];
#else
u8 lat_letter22_1[] = {
#include "assets/lat_letter22_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter22_3[0x80];
#else
u8 lat_letter22_3[] = {
#include "assets/lat_letter22_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter22_sen[0x100];
#else
u8 lat_letter22_sen[] = {
#include "assets/lat_letter22_sen.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter22_4[0x100];
#else
u8 lat_letter22_4[] = {
#include "assets/lat_letter22_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter22_5[0x400];
#else
u8 lat_letter22_5[] = {
#include "assets/lat_letter22_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter23_1[0x200];
#else
u8 lat_letter23_1[] = {
#include "assets/lat_letter23_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter23_2[0x40];
#else
u8 lat_letter23_2[] = {
#include "assets/lat_letter23_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter23_4[0x200];
#else
u8 lat_letter23_4[] = {
#include "assets/lat_letter23_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter24_1[0x400];
#else
u8 lat_letter24_1[] = {
#include "assets/lat_letter24_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter24_5[0x100];
#else
u8 lat_letter24_5[] = {
#include "assets/lat_letter24_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter24_3[0x200];
#else
u8 lat_letter24_3[] = {
#include "assets/lat_letter24_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter24_4[0x80];
#else
u8 lat_letter24_4[] = {
#include "assets/lat_letter24_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter25_1[0x100];
#else
u8 lat_letter25_1[] = {
#include "assets/lat_letter25_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter25_2[0x80];
#else
u8 lat_letter25_2[] = {
#include "assets/lat_letter25_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter25_3[0x100];
#else
u8 lat_letter25_3[] = {
#include "assets/lat_letter25_3.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter25_4[0x80];
#else
u8 lat_letter25_4[] = {
#include "assets/lat_letter25_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter25_5[0x400];
#else
u8 lat_letter25_5[] = {
#include "assets/lat_letter25_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test1_tex[0x100];
#else
u8 lat_letter26_test1_tex[] = {
#include "assets/lat_letter26_test1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test2_tex[0x100];
#else
u8 lat_letter26_test2_tex[] = {
#include "assets/lat_letter26_test2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test4_tex[0x80];
#else
u8 lat_letter26_test4_tex[] = {
#include "assets/lat_letter26_test4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test5_tex[0x80];
#else
u8 lat_letter26_test5_tex[] = {
#include "assets/lat_letter26_test5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test6_tex[0x100];
#else
u8 lat_letter26_test6_tex[] = {
#include "assets/lat_letter26_test6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test7_tex[0x80];
#else
u8 lat_letter26_test7_tex[] = {
#include "assets/lat_letter26_test7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test8_tex[0x80];
#else
u8 lat_letter26_test8_tex[] = {
#include "assets/lat_letter26_test8_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test9_tex[0x100];
#else
u8 lat_letter26_test9_tex[] = {
#include "assets/lat_letter26_test9_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test10_tex[0x100];
#else
u8 lat_letter26_test10_tex[] = {
#include "assets/lat_letter26_test10_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter26_test11_tex[0x80];
#else
u8 lat_letter26_test11_tex[] = {
#include "assets/lat_letter26_test11_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter27_9[0x100];
#else
u8 lat_letter27_9[] = {
#include "assets/lat_letter27_9.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter27_4[0x200];
#else
u8 lat_letter27_4[] = {
#include "assets/lat_letter27_4.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter27_8[0x400];
#else
u8 lat_letter27_8[] = {
#include "assets/lat_letter27_8.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter27_6[0x100];
#else
u8 lat_letter27_6[] = {
#include "assets/lat_letter27_6.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_1[0x200];
#else
u8 lat_letter28_1[] = {
#include "assets/lat_letter28_1.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_2[0x100];
#else
u8 lat_letter28_2[] = {
#include "assets/lat_letter28_2.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_9[0x80];
#else
u8 lat_letter28_9[] = {
#include "assets/lat_letter28_9.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_5[0x100];
#else
u8 lat_letter28_5[] = {
#include "assets/lat_letter28_5.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_6[0x100];
#else
u8 lat_letter28_6[] = {
#include "assets/lat_letter28_6.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter28_7[0x200];
#else
u8 lat_letter28_7[] = {
#include "assets/lat_letter28_7.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter65_kt_tex[0x400];
#else
u8 lat_letter65_kt_tex[] = {
#include "assets/lat_letter65_kt_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter65_me_tex[0x100];
#else
u8 lat_letter65_me_tex[] = {
#include "assets/lat_letter65_me_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter65_sk_tex[0x200];
#else
u8 lat_letter65_sk_tex[] = {
#include "assets/lat_letter65_sk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter65_xk_tex[0x100];
#else
u8 lat_letter65_xk_tex[] = {
#include "assets/lat_letter65_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter30_ed_tex[0x40];
#else
u8 lat_letter30_ed_tex[] = {
#include "assets/lat_letter30_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter30_ba_tex[0x40];
#else
u8 lat_letter30_ba_tex[] = {
#include "assets/lat_letter30_ba_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter30_ki_tex[0x100];
#else
u8 lat_letter30_ki_tex[] = {
#include "assets/lat_letter30_ki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter30_xk_tex[0x100];
#else
u8 lat_letter30_xk_tex[] = {
#include "assets/lat_letter30_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter31_xk_tex[0x100];
#else
u8 lat_letter31_xk_tex[] = {
#include "assets/lat_letter31_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter31_ed_tex[0x100];
#else
u8 lat_letter31_ed_tex[] = {
#include "assets/lat_letter31_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter32_ce_tex[0x200];
#else
u8 lat_letter32_ce_tex[] = {
#include "assets/lat_letter32_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter32_ed_tex[0x400];
#else
u8 lat_letter32_ed_tex[] = {
#include "assets/lat_letter32_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter32_xk_tex[0x100];
#else
u8 lat_letter32_xk_tex[] = {
#include "assets/lat_letter32_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter33_ed_tex[0x200];
#else
u8 lat_letter33_ed_tex[] = {
#include "assets/lat_letter33_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter33_xk_tex[0x100];
#else
u8 lat_letter33_xk_tex[] = {
#include "assets/lat_letter33_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter34_ed_tex[0x400];
#else
u8 lat_letter34_ed_tex[] = {
#include "assets/lat_letter34_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter34_ed2_tex[0x200];
#else
u8 lat_letter34_ed2_tex[] = {
#include "assets/lat_letter34_ed2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter34_ce_tex[0x200];
#else
u8 lat_letter34_ce_tex[] = {
#include "assets/lat_letter34_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter34_xk_tex[0x100];
#else
u8 lat_letter34_xk_tex[] = {
#include "assets/lat_letter34_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter35_ed_tex[0x400];
#else
u8 lat_letter35_ed_tex[] = {
#include "assets/lat_letter35_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter35_ce_tex[0x400];
#else
u8 lat_letter35_ce_tex[] = {
#include "assets/lat_letter35_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter35_xk_tex[0x100];
#else
u8 lat_letter35_xk_tex[] = {
#include "assets/lat_letter35_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter36_ed4_tex[0x100];
#else
u8 lat_letter36_ed4_tex[] = {
#include "assets/lat_letter36_ed4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter36_ed_tex[0x200];
#else
u8 lat_letter36_ed_tex[] = {
#include "assets/lat_letter36_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter36_xk_tex[0x100];
#else
u8 lat_letter36_xk_tex[] = {
#include "assets/lat_letter36_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter36_ed3_tex[0x100];
#else
u8 lat_letter36_ed3_tex[] = {
#include "assets/lat_letter36_ed3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter37_ed_tex[0x400];
#else
u8 lat_letter37_ed_tex[] = {
#include "assets/lat_letter37_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter37_kd_tex[0x200];
#else
u8 lat_letter37_kd_tex[] = {
#include "assets/lat_letter37_kd_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter37_k_tex[0x100];
#else
u8 lat_letter37_k_tex[] = {
#include "assets/lat_letter37_k_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter38_xk_tex[0x100];
#else
u8 lat_letter38_xk_tex[] = {
#include "assets/lat_letter38_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter38_ce_tex[0x800];
#else
u8 lat_letter38_ce_tex[] = {
#include "assets/lat_letter38_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter39_sk_tex[0x400];
#else
u8 lat_letter39_sk_tex[] = {
#include "assets/lat_letter39_sk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter39_xk_tex[0x100];
#else
u8 lat_letter39_xk_tex[] = {
#include "assets/lat_letter39_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter40_nk_tex[0x200];
#else
u8 lat_letter40_nk_tex[] = {
#include "assets/lat_letter40_nk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter40_hw_tex[0x80];
#else
u8 lat_letter40_hw_tex[] = {
#include "assets/lat_letter40_hw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter40_xk_tex[0x100];
#else
u8 lat_letter40_xk_tex[] = {
#include "assets/lat_letter40_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter41_gr_tex[0x800];
#else
u8 lat_letter41_gr_tex[] = {
#include "assets/lat_letter41_gr_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter41_xk_tex[0x100];
#else
u8 lat_letter41_xk_tex[] = {
#include "assets/lat_letter41_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter42_gr_tex[0x200];
#else
u8 lat_letter42_gr_tex[] = {
#include "assets/lat_letter42_gr_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter42_xk_tex[0x100];
#else
u8 lat_letter42_xk_tex[] = {
#include "assets/lat_letter42_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter43_ed_tex[0x400];
#else
u8 lat_letter43_ed_tex[] = {
#include "assets/lat_letter43_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter43_xk_tex[0x100];
#else
u8 lat_letter43_xk_tex[] = {
#include "assets/lat_letter43_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter44_ce_tex[0x200];
#else
u8 lat_letter44_ce_tex[] = {
#include "assets/lat_letter44_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter44_ed_tex[0x200];
#else
u8 lat_letter44_ed_tex[] = {
#include "assets/lat_letter44_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter44_xh_tex[0x100];
#else
u8 lat_letter44_xh_tex[] = {
#include "assets/lat_letter44_xh_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter45_ed2_tex[0x400];
#else
u8 lat_letter45_ed2_tex[] = {
#include "assets/lat_letter45_ed2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter45_ed_tex[0x400];
#else
u8 lat_letter45_ed_tex[] = {
#include "assets/lat_letter45_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter45_xk_tex[0x100];
#else
u8 lat_letter45_xk_tex[] = {
#include "assets/lat_letter45_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter46_ce_tex[0x200];
#else
u8 lat_letter46_ce_tex[] = {
#include "assets/lat_letter46_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter46_ed_tex[0x400];
#else
u8 lat_letter46_ed_tex[] = {
#include "assets/lat_letter46_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter46_xk_tex[0x100];
#else
u8 lat_letter46_xk_tex[] = {
#include "assets/lat_letter46_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter47_ce_tex[0x400];
#else
u8 lat_letter47_ce_tex[] = {
#include "assets/lat_letter47_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter47_xk_tex[0x100];
#else
u8 lat_letter47_xk_tex[] = {
#include "assets/lat_letter47_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter48_hn_tex[0x200];
#else
u8 lat_letter48_hn_tex[] = {
#include "assets/lat_letter48_hn_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter48_hn2_tex[0x200];
#else
u8 lat_letter48_hn2_tex[] = {
#include "assets/lat_letter48_hn2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter48_hn3_tex[0x80];
#else
u8 lat_letter48_hn3_tex[] = {
#include "assets/lat_letter48_hn3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter48_si_tex[0x200];
#else
u8 lat_letter48_si_tex[] = {
#include "assets/lat_letter48_si_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter48_xk_tex[0x100];
#else
u8 lat_letter48_xk_tex[] = {
#include "assets/lat_letter48_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter49_ki_tex[0x400];
#else
u8 lat_letter49_ki_tex[] = {
#include "assets/lat_letter49_ki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter49_xk_tex[0x100];
#else
u8 lat_letter49_xk_tex[] = {
#include "assets/lat_letter49_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter50_ed_tex[0x400];
#else
u8 lat_letter50_ed_tex[] = {
#include "assets/lat_letter50_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter50_xk_tex[0x100];
#else
u8 lat_letter50_xk_tex[] = {
#include "assets/lat_letter50_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter51_ed_tex[0x400];
#else
u8 lat_letter51_ed_tex[] = {
#include "assets/lat_letter51_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter51_ce_tex[0x400];
#else
u8 lat_letter51_ce_tex[] = {
#include "assets/lat_letter51_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter51_xk_tex[0x100];
#else
u8 lat_letter51_xk_tex[] = {
#include "assets/lat_letter51_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter52_ed_tex[0x400];
#else
u8 lat_letter52_ed_tex[] = {
#include "assets/lat_letter52_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter52_ce_tex[0x400];
#else
u8 lat_letter52_ce_tex[] = {
#include "assets/lat_letter52_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter52_xk_tex[0x100];
#else
u8 lat_letter52_xk_tex[] = {
#include "assets/lat_letter52_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter53_ki_tex[0x400];
#else
u8 lat_letter53_ki_tex[] = {
#include "assets/lat_letter53_ki_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter53_ed_tex[0x400];
#else
u8 lat_letter53_ed_tex[] = {
#include "assets/lat_letter53_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter53_xk_tex[0x100];
#else
u8 lat_letter53_xk_tex[] = {
#include "assets/lat_letter53_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter54_ce_tex[0x200];
#else
u8 lat_letter54_ce_tex[] = {
#include "assets/lat_letter54_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter54_xk_tex[0x100];
#else
u8 lat_letter54_xk_tex[] = {
#include "assets/lat_letter54_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter55_ce_tex[0x400];
#else
u8 lat_letter55_ce_tex[] = {
#include "assets/lat_letter55_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter55_bg_tex[0x200];
#else
u8 lat_letter55_bg_tex[] = {
#include "assets/lat_letter55_bg_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter55_xk_tex[0x100];
#else
u8 lat_letter55_xk_tex[] = {
#include "assets/lat_letter55_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter56_ce_tex[0x200];
#else
u8 lat_letter56_ce_tex[] = {
#include "assets/lat_letter56_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter56_wh_tex[0x80];
#else
u8 lat_letter56_wh_tex[] = {
#include "assets/lat_letter56_wh_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter56_xk_tex[0x100];
#else
u8 lat_letter56_xk_tex[] = {
#include "assets/lat_letter56_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter57_ce_tex[0x400];
#else
u8 lat_letter57_ce_tex[] = {
#include "assets/lat_letter57_ce_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter57_xk_tex[0x100];
#else
u8 lat_letter57_xk_tex[] = {
#include "assets/lat_letter57_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter58_ed_tex[0x400];
#else
u8 lat_letter58_ed_tex[] = {
#include "assets/lat_letter58_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter58_xk_tex[0x100];
#else
u8 lat_letter58_xk_tex[] = {
#include "assets/lat_letter58_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter59_sn_tex[0x400];
#else
u8 lat_letter59_sn_tex[] = {
#include "assets/lat_letter59_sn_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter59_xk_tex[0x100];
#else
u8 lat_letter59_xk_tex[] = {
#include "assets/lat_letter59_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter60_de_tex[0x200];
#else
u8 lat_letter60_de_tex[] = {
#include "assets/lat_letter60_de_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter60_ed_tex[0x200];
#else
u8 lat_letter60_ed_tex[] = {
#include "assets/lat_letter60_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter60_gd_tex[0x80];
#else
u8 lat_letter60_gd_tex[] = {
#include "assets/lat_letter60_gd_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter60_hw_tex[0x80];
#else
u8 lat_letter60_hw_tex[] = {
#include "assets/lat_letter60_hw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter61_ed_tex[0x200];
#else
u8 lat_letter61_ed_tex[] = {
#include "assets/lat_letter61_ed_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter61_kd_tex[0x200];
#else
u8 lat_letter61_kd_tex[] = {
#include "assets/lat_letter61_kd_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter61_ha_tex[0x200];
#else
u8 lat_letter61_ha_tex[] = {
#include "assets/lat_letter61_ha_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter61_xk_tex[0x100];
#else
u8 lat_letter61_xk_tex[] = {
#include "assets/lat_letter61_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter62_ch_tex[0x400];
#else
u8 lat_letter62_ch_tex[] = {
#include "assets/lat_letter62_ch_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter62_hn_tex[0x400];
#else
u8 lat_letter62_hn_tex[] = {
#include "assets/lat_letter62_hn_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter62_xk_tex[0x100];
#else
u8 lat_letter62_xk_tex[] = {
#include "assets/lat_letter62_xk_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth3_tex[0x80];
#else
u8 lat_letter63_cloth3_tex[] = {
#include "assets/lat_letter63_cloth3_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth4_tex[0x80];
#else
u8 lat_letter63_cloth4_tex[] = {
#include "assets/lat_letter63_cloth4_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth5_tex[0x80];
#else
u8 lat_letter63_cloth5_tex[] = {
#include "assets/lat_letter63_cloth5_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth6_tex[0x100];
#else
u8 lat_letter63_cloth6_tex[] = {
#include "assets/lat_letter63_cloth6_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth7_tex[0x100];
#else
u8 lat_letter63_cloth7_tex[] = {
#include "assets/lat_letter63_cloth7_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth8_tex[0x100];
#else
u8 lat_letter63_cloth8_tex[] = {
#include "assets/lat_letter63_cloth8_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth1_tex[0x80];
#else
u8 lat_letter63_cloth1_tex[] = {
#include "assets/lat_letter63_cloth1_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_fusen_tex[0x80];
#else
u8 lat_letter63_fusen_tex[] = {
#include "assets/lat_letter63_fusen_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth2_tex[0x80];
#else
u8 lat_letter63_cloth2_tex[] = {
#include "assets/lat_letter63_cloth2_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter63_cloth9_tex[0x80];
#else
u8 lat_letter63_cloth9_tex[] = {
#include "assets/lat_letter63_cloth9_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter64_ik_tex[0x200];
#else
u8 lat_letter64_ik_tex[] = {
#include "assets/lat_letter64_ik_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter64_ti_tex[0x200];
#else
u8 lat_letter64_ti_tex[] = {
#include "assets/lat_letter64_ti_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter64_aw_tex[0x400];
#else
u8 lat_letter64_aw_tex[] = {
#include "assets/lat_letter64_aw_tex.inc"
};
#endif

#ifdef TARGET_PC
u8 lat_letter64_xk_tex[0x100];
#else
u8 lat_letter64_xk_tex[] = {
#include "assets/lat_letter64_xk_tex.inc"
};
#endif
