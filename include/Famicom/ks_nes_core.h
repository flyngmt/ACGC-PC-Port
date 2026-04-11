#ifndef KS_NES_CORE_H
#define KS_NES_CORE_H

#include "types.h"
#include "Famicom/ks_nes_common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void ksNesDrawMakeOBJIndTex(ksNesCommonWorkObj* wp);
extern void ksNesDrawMakeOBJIndTexMMC5(ksNesCommonWorkObj* wp);
extern void ksNesConvertChrToI8(ksNesCommonWorkObj* wp, const unsigned char* foo, unsigned long bar);
extern void ksNesConvertChrToI8MMC5(ksNesCommonWorkObj* wp, const unsigned char* foo, unsigned long bar);
extern void ksNesQDSoundSync();
extern int ksNesQDFastLoad(ksNesCommonWorkObj* wp, ksNesStateObj* sp);
extern int ksNesQDFastSave(ksNesCommonWorkObj* wp, ksNesStateObj* sp);
extern void ksNesPushResetButton(ksNesStateObj* sp);
extern int ksNesReset(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags, u8* chrramp, u8* bbramp);
extern void ksNesEmuFrame(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags);

extern u32 ksNesResetAsm(ksNesCommonWorkObj* wp, ksNesStateObj* sp);
extern void ksNesInit01();
extern void ksNesInit03();
extern void ksNesInit04();
extern void ksNesInit05();
extern void ksNesInit07();
extern void ksNesInit09();
extern void ksNesInit12();
extern void ksNesInit13();
extern void ksNesInit15();
extern void ksNesInit18();
extern void ksNesInit1a();
extern void ksNesInit42();
extern void ksNesInit43();
extern void ksNesInit45();
extern void ksNesInit49();
extern void ksNesInit56();

extern void ksNesEmuFrameAsm(ksNesCommonWorkObj* wp, ksNesStateObj* sp);
extern void ksNesLinecntIrqDefault();
extern void ksNesMainLoop2();
extern void ksNesInst_load16_imm();
extern void ksNesInst_load8_abs();
extern void ksNesInst_load8_absx();
extern void ksNesInst_load8_absy();
extern void ksNesInst_load8_zerop();
extern void ksNesInst_load8_dx();
extern void ksNesInst_load8_dxi();
extern void ksNesInst_load8_dyi();
extern void ksNesInst_lda_a1();
extern void ksNesInst_ldx_b6();
extern void ksNesInst_ldx_a2();
extern void ksNesInst_ldy_a0();
extern void ksNesInst_sta_85();
extern void ksNesInst_stx_86();
extern void ksNesInst_sty_84();
extern void ksNesInst_sta_95();
extern void ksNesInst_stx_96();
extern void ksNesInst_sty_94();
extern void ksNesInst_sta_8d();
extern void ksNesInst_stx_8e();
extern void ksNesInst_sty_8c();
extern void ksNesInst_sta_9d();
extern void ksNesInst_sta_99();
extern void ksNesInst_sta_81();
extern void ksNesInst_sta_91();
extern void ksNesInst_clc_18();
extern void ksNesInst_sec_38();
extern void ksNesInst_dex_ca();
extern void ksNesInst_inx_e8();
extern void ksNesInst_dey_88();
extern void ksNesInst_iny_c8();
extern void ksNesInst_txa_8a();
extern void ksNesInst_tya_98();
extern void ksNesInst_tax_aa();
extern void ksNesInst_tay_a8();
extern void ksNesInst_cmp_c1();
extern void ksNesInst_cpx_e0();
extern void ksNesInst_cpy_c0();
extern void ksNesInst_adc_61();
extern void ksNesInst_sbc_e1();
extern void ksNesInst_ora_01();
extern void ksNesInst_and_21();
extern void ksNesInst_bit_24();
extern void ksNesInst_eor_41();
extern void ksNesInst_inc_e6();
extern void ksNesInst_dec_c6();
extern void ksNesInst_asl_0a();
extern void ksNesInst_asl_06();
extern void ksNesInst_lsr_4a();
extern void ksNesInst_lsr_46();
extern void ksNesInst_rol_2a();
extern void ksNesInst_rol_26();
extern void ksNesInst_ror_6a();
extern void ksNesInst_ror_66();
extern void ksNesInst_bpl_10();
extern void ksNesInst_bmi_30();
extern void ksNesInst_bvc_50();
extern void ksNesInst_bvs_70();
extern void ksNesInst_bcc_90();
extern void ksNesInst_bcs_b0();
extern void ksNesInst_bne_d0();
extern void ksNesInst_beq_f0();
extern void ksNesInst_jsr_20();
extern void ksNesPush16_a1();
extern void ksNesInst_pha_48();
extern void ksNesInst_pla_68();
extern void ksNesInst_rts_60();
extern void ksNesPopPC();
extern void ksNesInst_jmp_4c();
extern void ksNesInst_jmp_6c();
extern void ksNesInst_brk_00();
extern void ksNesActivateIntrIRQ();
extern void ksNesActivateIntr();
extern void ksNesInst_php_08();
extern void ksNesInst_plp_28();
extern void ksNesInst_rti_40();
extern void ksNesInst_rti_40_2();
extern void ksNesInst_cli_58();
extern void ksNesInst_sei_78();
extern void ksNesInst_txs_9a();
extern void ksNesInst_tsx_ba();
extern void ksNesInst_cld_d8();
extern void ksNesInst_sed_f8();
extern void ksNesInst_clv_b8();
extern void ksNesLoadInvalid();
extern void ksNesLoadIgnore();
extern void ksNesLoadWRAM();
extern void ksNesLoadBBRAM();
extern void ksNesLoadPPU();
extern void ksNesLoadIO();
extern void ksNesLoad4015();
extern void ksNesLoad4017();
extern void ksNesLoad4016();
extern void ksNesStoreWRAM();
extern void ksNesStoreBBRAM();
extern void ksNesStoreInvalid();
extern void ksNesStorePPU();
extern void ksNesStore2000();
extern void ksNesStorePPURam();
extern void ksNesStore2004();
extern void ksNesStore2005();
extern void ksNesStore2006();
extern void ksNesStore2007ChrRom();
extern void ksNesStoreIO();
extern void ksNesStoreQDSound();
extern void ksNesStore4017();
extern void ksNesStore4011();
extern void ksNesStore4015();
extern void ksNesStore4003();
extern void ksNesStore4000();
extern void ksNesStore4014();
extern void ksNesStore4016();
extern void ksNesInst_wdm_42();
extern void ksNesLinecntIrqQD();
extern void ksNesStoreQD_4020();
extern void ksNesStoreQD_4022();
extern void ksNesStoreQD_4023();
extern void ksNesStoreQD_4024();
extern void ksNesStoreQD_4025();
extern void ksNesStoreQD_4026();
extern void ksNesStore01_8000();
extern void ksNesStore02_8000();
extern void ksNesStore03_6000();
extern void ksNesLinecntIrq04();
extern void ksNesStore04_8000();
extern void ksNesStore04_a000();
extern void ksNesStore04_c000();
extern void ksNesStore04_e000();
extern void ksNesLinecntIrq05Timer();
extern void ksNesLinecntIrq05Vcount();
extern void ksNesStore05_4000();
extern void ksNesStore05_5130();
extern void ksNesStore05_5100();
extern void ksNesStore05_5113();
extern void ksNesStore05_5101();
extern void ksNesStore05_5120();
extern void ksNesStore05_5128();
extern void ksNesStore05_5102();
extern void ksNesStore05_5104();
extern void ksNesStore05_5105();
extern void ksNesStore05_5106();
extern void ksNesLoad05_4000();
extern void ksNesStore07_8000();
extern void ksNesStore09_8000();
extern void ksNesStore09_a000();
extern void ksNesStore09_c000();
extern void ksNesStore09_e000();
extern void ksNesStore0a_8000();
extern void ksNesStore0a_a000();
extern void ksNesLinecntIrq49();
extern void ksNesStore12_8000();
extern void ksNesStore12_a000();
extern void ksNesStore12_e000();
extern void ksNesStore13_4000();
extern void ksNesLoad13_4000();
extern void ksNesStore13_8000();
extern void ksNesStore13_c000();
extern void ksNesStore13_e000();
extern void ksNesStore16_8000();
extern void ksNesStore16_9000();
extern void ksNesStore16_a000();
extern void ksNesStore16_b000();
extern void ksNesStore17_a000();
extern void ksNesStore17_b000();
extern void ksNesStore17_e000();
extern void ksNesLinecntIrq18();
extern void ksNesStore18_8000();
extern void ksNesStore18_a000();
extern void ksNesStore18_c000();
extern void ksNesStore18_e000();
extern void ksNesLinecntIrq19();
extern void ksNesStore19_8000();
extern void ksNesStore19_a000();
extern void ksNesStore19_b000();
extern void ksNesStore19_e000();
extern void ksNesStore42_8000();
extern void ksNesLinecntIrq43();
extern void ksNesStore43_c000();
extern void ksNesStore44_8000();
extern void ksNesStore44_c000();
extern void ksNesStore44_e000();
extern void ksNesStore45_8000();
extern void ksNesStore45_a000();
extern void ksNesStore46_8000();
extern void ksNesStore49_a000();
extern void ksNesStore49_c000();
extern void ksNesStore4b_8000();
extern void ksNesStore4b_a000();
extern void ksNesStore4b_e000();
extern void ksNesStore56_6000();
extern void ksNesStore57_6000();
extern void ksNesStore59_c000();
extern void ksNesStore5d_6000();
extern void ksNesStoreb8_6000();

// set:
//      keep ksNesStateObj->wram state
// unset:
//      init ksNesStateObj->wram with a pattern
#define KS_NES_FLAG_KEEP_WRAM_STATE = (1 << 0) // 0x00000001

// set:
//      chr ram unchanged?
// unset:
//      clear chr ram
#define KS_NES_FLAG_NO_INIT_CHR_RAM = (1 << 1) // 0x00000002

// set:
//      sp->chr_size = 0x20000
// unset:
//      chr size unchanged?
// #define KS_NES_FLAG_??? = (1 << 3) // 0x00000008

// something about CHR RAM and BB RAM initialization.
// #define KS_NES_FLAG_??? = (1 << 4) // 0x00000010

// set:
//      don't initialize ksNesStateObj->palette_normal
// unset:
//      init ksNesStateObj->palette_normal with ksNesPaletteNormal
#define KS_NES_FLAG_NO_INIT_PALETTE = (1 << 5) // 0x00000020

// set:
//      skip some sound initializing stuff
// unset:
//      init sound stuff
#define KS_NES_FLAG_NO_INIT_SOUND = (1 << 6) // 0x00000040

// unknown
// #define KS_NES_FLAG_??? = (1 << 10) // 0x00000400

// something to do with sound every frame
// #define KS_NES_FLAG_??? = (1 << 12) // 0x00001000

// unknown
// #define KS_NES_FLAG_??? = (1 << 14) // 0x00004000

#ifdef __cplusplus
}
#endif

#endif
