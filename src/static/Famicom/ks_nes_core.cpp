
#include "Famicom/ks_nes_core.h"
#include "Famicom/ks_nes_draw.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/base/PPCArch.h"
#include "jaudio_NES/emusound.h"
#include "_mem.h"
#include "dolphin/os.h"

#ifndef TARGET_PC
#pragma optimizewithasm off
#endif

// TODO: verify function signatures.
// TODO: replace hard-coded function pointers with function names.

#ifndef TARGET_PC /* All function tables + asm reference PPC asm entry points */

typedef void (*STORE_FUNC)(u32 addr, u32 data);

// clang-format off
STORE_FUNC ksNesStoreFuncTblDefault[] = {
    (STORE_FUNC)ksNesStoreWRAM,         
    (STORE_FUNC)ksNesStorePPU,          
    (STORE_FUNC)ksNesStoreIO,           
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
};

typedef void (*STORE_PPU_FUNC)(u32, u32);

STORE_PPU_FUNC ksNesStorePPUFuncTblDefault[] = {
    (STORE_PPU_FUNC)ksNesStore2000,         
    (STORE_PPU_FUNC)ksNesStorePPURam,       
    (STORE_PPU_FUNC)ksNesLinecntIrqDefault, 
    (STORE_PPU_FUNC)ksNesStorePPURam,       
    (STORE_PPU_FUNC)ksNesStore2004,         
    (STORE_PPU_FUNC)ksNesStore2005,         
    (STORE_PPU_FUNC)ksNesStore2006,         
    (STORE_PPU_FUNC)ksNesStore2007ChrRom,   
};

typedef void (*STORE_IO_FUNC)(u32, u32);

STORE_IO_FUNC ksNesStoreIOFuncTblDefault[] = {
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4011,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4014,
    (STORE_IO_FUNC)ksNesStore4015,
    (STORE_IO_FUNC)ksNesStore4016,
    (STORE_IO_FUNC)ksNesStore4017,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesLinecntIrqDefault,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesLinecntIrqDefault,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
};

typedef void (*STORE_QD_FUNC)(u32, u32);

STORE_QD_FUNC ksNesStoreQDFuncTbl[] = {
    (STORE_QD_FUNC)ksNesStoreQD_4020, // 4020 (timer irq reload value lo)
    (STORE_QD_FUNC)ksNesStoreQD_4020, // 4021 (timer irq reload value hi)
    (STORE_QD_FUNC)ksNesStoreQD_4022,
    (STORE_QD_FUNC)ksNesStoreQD_4023,
    (STORE_QD_FUNC)ksNesStoreQD_4024,
    (STORE_QD_FUNC)ksNesStoreQD_4025,
    (STORE_QD_FUNC)ksNesStoreQD_4026,
    (STORE_QD_FUNC)ksNesStoreInvalid,
};

u8 ksNesInitQDDataTbl[11] = {
    0x00, 0x2f, 0x00, 0x00, 
    0x00, 0x06, 0x10, 0xc0, 
    0x80, 0x35, 0xac
};

typedef void (*STORE_05_FUNC)(u32, u32);

STORE_05_FUNC ksNesStore05FuncTbl[] = {
    (STORE_05_FUNC)ksNesStore05_5100,
    (STORE_05_FUNC)ksNesStore05_5101,
    (STORE_05_FUNC)ksNesStore05_5102,
    (STORE_05_FUNC)ksNesStore05_5102,
    (STORE_05_FUNC)ksNesStore05_5104,
    (STORE_05_FUNC)ksNesStore05_5105,
    (STORE_05_FUNC)ksNesStore05_5106,
    (STORE_05_FUNC)ksNesStore05_5106,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5130
};

typedef u32 (*LOAD_FUNC)(u32);

LOAD_FUNC ksNesLoadFuncTblDefault[] = {
    (LOAD_FUNC)ksNesLoadWRAM,
    (LOAD_FUNC)ksNesLoadPPU,
    (LOAD_FUNC)ksNesLoadIO,
    (LOAD_FUNC)ksNesLoadIgnore,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM
};

typedef u32 (*LOAD_IO_FUNC)(u32);

LOAD_IO_FUNC ksNesLoadIOFuncTblDefault[] = {
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoad4015,
    (LOAD_IO_FUNC)ksNesLoad4016,
    (LOAD_IO_FUNC)ksNesLoad4017
};

u8 ksNesVoiceIdTable_12[] = {
    0x04, 0x05, 0x06, 0x07, 0x01, 0x02, 0x03, 0x08, 0x0a, 0x0b, 0x09, 0x0c, 0x0e, 0x0d, 0x0f, 0x0f,
};

// typedef u32(*MAPPER_INIT_FUNC)(ksNesCommonWorkObj* wp,ksNesStateObj* sp);

// clang-format off
// https://www.nesdev.org/wiki/Mapper
// https://www.nesdev.org/wiki/List_of_mappers
void* ksNesMapperInitFuncTbl[185][5] = {
    // 0    NROM
    {
        NULL,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 1    SxROM, MMC1
    {
        ksNesInit01,
        ksNesStore01_8000,
        ksNesStore01_8000,
        ksNesStore01_8000,
        ksNesStore01_8000
    },
    // 2    UxROM
    {
        NULL,
        ksNesStore02_8000,
        ksNesStore02_8000,
        ksNesStore02_8000,
        ksNesStore02_8000
    },
    // 3    CNROM
    {
        ksNesInit03,
        ksNesStore03_6000,
        ksNesStore03_6000,
        ksNesStore03_6000,
        ksNesStore03_6000
    },
    // 4    TxROM, MMC3, MMC6
    {
        ksNesInit04,
        ksNesStore04_8000,
        ksNesStore04_a000,
        ksNesStore04_c000,
        ksNesStore04_e000
    },
    // 5    ExROM, MMC5
    {
        ksNesInit05,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 6 
    {},
    // 7    AxROM
    {
        ksNesInit07,
        ksNesStore07_8000,
        ksNesStore07_8000,
        ksNesStore07_8000,
        ksNesStore07_8000
    },
    // 8 
    {},
    // 9    PxROM, MMC2
    {
        ksNesInit09,
        ksNesStore09_8000,
        ksNesStore09_a000,
        ksNesStore09_c000,
        ksNesStore09_e000
    },
    // 10   FxROM, MMC4
    {
        NULL,
        ksNesStore0a_8000,
        ksNesStore0a_a000,
        ksNesStore09_c000,
        ksNesStore09_e000
    },
    // 11   Color Dreams
    {},
    // 12
    {},
    // 13   CPROM
    {},
    // 14
    {},
    // 15   100-in-1 Contra Function 16
    {},
    // 16   Bandai EPROM (24C02)
    {},
    // 17
    {},
    // 18   Jaleco SS8806
    {
        ksNesInit12,
        ksNesStore12_8000,
        ksNesStore12_a000,
        ksNesStore12_a000,
        ksNesStore12_e000
    },
    // 19   Namco 163
    {
        ksNesInit13,
        ksNesStore13_8000,
        ksNesStore13_8000,
        ksNesStore13_c000,
        ksNesStore13_e000
    },
    // 20
    {},
    // 21   VRC4a, VRC4c
    {
        ksNesInit15,
        ksNesStore19_8000,
        ksNesStore19_a000,
        ksNesStore19_b000,
        ksNesStore19_e000
    },
    // 22   VRC2a
    {
        NULL,
        ksNesStore16_8000,
        ksNesStore16_a000,
        ksNesStore16_b000,
        ksNesStore16_b000
    },
    // 23   VRC2b, VRC4e
    {
        ksNesInit15,
        ksNesStore16_8000,
        ksNesStore17_a000,
        ksNesStore17_b000,
        ksNesStore17_e000
    },
    // 24   VRC6a
    {
        ksNesInit18,
        ksNesStore18_8000,
        ksNesStore18_a000,
        ksNesStore18_c000,
        ksNesStore18_e000
    },
    // 25   VRC4b, VRC4d
    {
        ksNesInit15,
        ksNesStore19_8000,
        ksNesStore19_a000,
        ksNesStore19_b000,
        ksNesStore19_e000
    },
    // 26   VRC6b
    {
        ksNesInit1a,
        ksNesStore18_8000,
        ksNesStore18_a000,
        ksNesStore18_c000,
        ksNesStore18_e000
    },
    // 27
    {},
    // 28
    {},
    // 29
    {},
    // 30
    {},
    // 31
    {},
    // 32
    {},
    // 33
    {},
    // 34   BNROM, NINA-001
    {},
    // 35
    {},
    // 36
    {},
    // 37
    {},
    // 38
    {},
    // 39
    {},
    // 40
    {},
    // 41
    {},
    // 42
    {},
    // 43
    {},
    // 44
    {},
    // 45
    {},
    // 46
    {},
    // 47
    {},
    // 48
    {},
    // 49
    {},
    // 50
    {},
    // 51
    {},
    // 52
    {},
    // 53
    {},
    // 54
    {},
    // 55
    {},
    // 56
    {},
    // 57
    {},
    // 58
    {},
    // 59
    {},
    // 60
    {},
    // 61
    {},
    // 62
    {},
    // 63
    {},
    // 64   RAMBO-1
    {},
    // 65
    {},
    // 66   GxROM, MxROM
    {
        ksNesInit42,
        ksNesStore42_8000,
        ksNesStore42_8000,
        ksNesStore42_8000,
        ksNesStore42_8000
    },
    // 67
    {
        ksNesInit43,
        ksNesStore44_8000,
        ksNesStore44_8000,
        ksNesStore43_c000,
        ksNesStore44_e000
    },
    // 68   After Burner
    {
        NULL,
        ksNesStore44_8000,
        ksNesStore44_8000,
        ksNesStore44_c000,
        ksNesStore44_e000
    },
    // 69   FME-7, Sunsoft 5B
    {
        ksNesInit45,
        ksNesStore45_8000,
        ksNesStore45_a000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 70
    {
        NULL,
        ksNesStore46_8000,
        ksNesStore46_8000,
        ksNesStore46_8000,
        ksNesStore46_8000
    },
    // 71   Camerica/Codemasters
    {},
    // 72
    {},
    // 73   VRC3
    {
        ksNesInit49,
        ksNesLinecntIrqDefault,
        ksNesStore49_a000,
        ksNesStore49_c000,
        ksNesStore02_8000
    },
    // 74   Pirate MMC3 derivative
    {},
    // 75   VRC1
    {
        NULL,
        ksNesStore4b_8000,
        ksNesStore4b_a000,
        ksNesStore4b_a000,
        ksNesStore4b_e000
    },
    // 76   Namco 109 variant
    {},
    // 77
    {},
    // 78
    {},
    // 79   NINA-03/NINA-06
    {},
    // 80
    {},
    // 81
    {},
    // 82
    {},
    // 83
    {},
    // 84
    {},
    // 85   VRC7
    {},
    // 86   JALECO-JF-13
    {
        ksNesInit56,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
    },
    // 87
    {
        ksNesInit03,
        ksNesStore57_6000,
        ksNesStore57_6000,
        ksNesStore57_6000,
        ksNesStore57_6000
    },
    // 88
    {},
    // 89
    {
        NULL,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesStore59_c000,
        ksNesLinecntIrqDefault
    },
    // 90
    {},
    // 91
    {},
    // 92
    {},
    // 93
    {
        ksNesInit03,
        ksNesStore5d_6000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 94   Senjou no Ookami
    {},
    // 95
    {},
    // 96
    {},
    // 97
    {},
    // 98
    {},
    // 99
    {},
    // 100
    {},
    // 101
    {},
    // 102
    {},
    // 103
    {},
    // 104
    {},
    // 105  NES-EVENT
    {},
    // 106
    {},
    // 107
    {},
    // 108
    {},
    // 109
    {},
    // 110
    {},
    // 111
    {},
    // 112
    {},
    // 113  NINA-03/NINA-06??
    {},
    // 114
    {},
    // 115
    {},
    // 116
    {},
    // 117
    {},
    // 118  TxSROM, MMC3
    {},
    // 119  TQROM, MMC3
    {},
    // 120
    {},
    // 121
    {},
    // 122
    {},
    // 123
    {},
    // 124
    {},
    // 125
    {},
    // 126
    {},
    // 127
    {},
    // 128
    {},
    // 129
    {},
    // 130
    {},
    // 131
    {},
    // 132
    {},
    // 133
    {},
    // 134
    {},
    // 135
    {},
    // 136
    {},
    // 137
    {},
    // 138
    {},
    // 139
    {},
    // 140
    {},
    // 141
    {},
    // 142
    {},
    // 143
    {},
    // 144
    {},
    // 145
    {},
    // 146
    {},
    // 147
    {},
    // 148
    {},
    // 149
    {},
    // 150
    {},
    // 151
    {},
    // 152
    {},
    // 153
    {},
    // 154
    {},
    // 155
    {},
    // 156
    {},
    // 157
    {},
    // 158
    {},
    // 159  Bandai EPROM (24C01)
    {},
    // 160
    {},
    // 161
    {},
    // 162
    {},
    // 163
    {},
    // 164
    {},
    // 165
    {},
    // 166  SUBOR
    {},
    // 167  SUBOR
    {},
    // 168
    {},
    // 169
    {},
    // 170
    {},
    // 171
    {},
    // 172
    {},
    // 173
    {},
    // 174
    {},
    // 175
    {},
    // 176
    {},
    // 177
    {},
    // 178
    {},
    // 179
    {},
    // 180  Crazy Climber
    {},
    // 181
    {},
    // 182
    {},
    // 183
    {},
    // 184
    {
        ksNesInit03,
        ksNesStoreb8_6000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
    },
};

typedef struct {
    void* instructionEvaluationFunction;
    u8 cycles;
    u8 byteSize;
    // u16 unused
    void* followUpFunction;
    u8 padding[4];
} KS_NES_INSTR;

#define TEMP_NULL_CAST (void*)

KS_NES_INSTR ksNesInstJumpTbl[0x100] = {
    // 0x00 BRK
    {
        ksNesInst_brk_00,
        7, 2,
        NULL,
    },
    // 0x01 ORA X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_ora_01
    },
    // 0x02 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        8, 1,
        NULL,
    },
    // 0x03 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x04 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x05 ORA zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ora_01
    },
    // 0x06 ASL zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_asl_06
    },
    // 0x07 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL
    },
    // 0x08 PHP
    {
        ksNesInst_php_08,
        3, 1,
        ksNesLinecntIrqDefault
    },
    // 0x09 ORA #
    {
        ksNesInst_ora_01,
        2, 2,
        NULL
    },
    // 0x0A ASL A
    {
        ksNesInst_asl_0a,
        2, 1,
        NULL
    },
    // 0x0B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL
    },
    // 0x0C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL
    },
    // 0x0D ORA abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ora_01
    },
    // 0x0E ASL abs
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_asl_06,
    },
    // 0x0F ---
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL
    },
    // 0x10 BPL rel
    {
        ksNesInst_bpl_10,
        3, 2,
        NULL,
    },
    // 0x11 ORA ind,Y
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_ora_01,
    },
    // 0x12 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL
    },
    // 0x13 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL
    },
    // 0x14 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x15 ORA zpg,X
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_ora_01,
    },
    // 0x16 ROL zpg
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_asl_06,
    },
    // 0x17 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x18 CLC
    {
        ksNesInst_clc_18,
        2, 1,
        NULL,
    },
    // 0x19 ORA abs,Y
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_ora_01,
    },
    // 0x1A ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x1B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x1C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x1D ORA abs,X
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_ora_01,
    },
    // 0x1E ASL abs,X
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_asl_06,
    },
    // 0x1F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x20 JSR abs
    {
        ksNesInst_load16_imm,
        6, 3,
        ksNesInst_jsr_20,
    },
    // 0x21 AND X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_and_21,
    },
    // 0x22 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        8, 1,
        NULL,
    },
    // 0x23 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x24 BIT zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_bit_24,
    },
    // 0x25 AND zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_and_21,
    },
    // 0x26 ROL zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_rol_26,
    },
    // 0x27 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x28 PLP impl
    {
        ksNesInst_plp_28,
        4, 1,
        ksNesActivateIntrIRQ,
    },
    // 0x29 AND #
    {
        ksNesInst_and_21,
        2, 2,
        NULL,
    },
    // 0x2A ROL A
    {
        ksNesInst_rol_2a,
        2, 1,
        NULL,
    },
    // 0x2B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x2C BIT abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_bit_24,
    },
    // 0x2D AND abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x2E ROL abs
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_rol_26,
    },
    // 0x2F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x30 BMI rel
    {
        ksNesInst_bmi_30,
        3, 2,
        NULL,
    },
    // 0x31 AND ind,Y
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_and_21,
    },
    // 0x32 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x33 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x34 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x35 AND zpg,X
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_and_21,
    },
    // 0x36 ROL zpg,X
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_rol_26,
    },
    // 0x37 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x38 SEC impl
    {
        ksNesInst_sec_38,
        2, 1,
        NULL,
    },
    // 0x39 AND abs,Y
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x3A ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x3B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x3C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x3D AND abs,X
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x3E ROL abs,X
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_rol_26,
    },
    // 0x3F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x40 RTI impl
    {
        ksNesInst_rti_40,
        6, 1,
        ksNesInst_rti_40_2,
    },
    // 0x41 EOR X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_eor_41,
    },
    // 0x42 ILLEGAL INSTRUCTION
    {
        ksNesInst_wdm_42,
        2, 2,
        NULL,
    },
    // 0x43 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x44 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x45 EOR zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_eor_41,
    },
    // 0x46 LSR zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_lsr_46,
    },
    // 0x47 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x48
    {
        ksNesInst_pha_48,
        3, 1,
        NULL,
    },
    // 0x49
    {
        ksNesInst_eor_41,
        2, 2,
        NULL,
    },
    // 0x4A
    {
        ksNesInst_lsr_4a,
        2, 1,
        NULL,
    },
    // 0x4B
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x4C
    {
        ksNesInst_load16_imm,
        3, 3,
        ksNesInst_jmp_4c,
    },
    // 0x4D
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x4E
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_lsr_46,
    },
    // 0x4F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x50
    {
        ksNesInst_bvc_50,
        3, 2,
        NULL,
    },
    // 0x51
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_eor_41,
    },
    // 0x52
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x53
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x54
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x55
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_eor_41,
    },
    // 0x56
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_lsr_46,
    },
    // 0x57
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x58
    {
        ksNesInst_cli_58,
        2, 1,
        NULL,
    },
    // 0x59
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x5A
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x5B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x5C
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x5D
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x5E
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_lsr_46,
    },
    // 0x5F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x60
    {
        ksNesInst_rts_60,
        6, 1,
        NULL,
    },
    // 0x61
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_adc_61,
    },
    // 0x62
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x63
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x64
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x65
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_adc_61,
    },
    // 0x66
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_ror_66,
    },
    // 0x67
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x68
    {
        ksNesInst_pla_68,
        4, 1,
        NULL,
    },
    // 0x69
    {
        ksNesInst_adc_61,
        2, 2,
        NULL,
    },
    // 0x6A
    {
        ksNesInst_ror_6a,
        2, 1,
        NULL,
    },
    // 0x6B
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x6C
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_jmp_6c,
    },
    // 0x6D
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x6E
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_ror_66,
    },
    // 0x6F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x70
    {
        ksNesInst_bvs_70,
        3, 2,
        NULL,
    },
    // 0x71
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_adc_61,
    },
    // 0x72
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x73
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x74
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x75
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_adc_61,
    },
    // 0x76
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_ror_66,
    },
    // 0x77
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x78
    {
        ksNesInst_sei_78,
        2, 1,
        NULL,
    },
    // 0x79
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x7A
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x7B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x7C
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x7D
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x7E
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_ror_66,
    },
    // 0x7F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x80
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x81
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_sta_81,
    },
    // 0x82
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x83
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x84
    {
        ksNesInst_sty_84,
        3, 2,
        NULL,
    },
    // 0x85
    {
        ksNesInst_sta_85,
        3, 2,
        NULL,
    },
    // 0x86
    {
        ksNesInst_stx_86,
        3, 2,
        NULL,
    },
    // 0x87
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x88
    {
        ksNesInst_dey_88,
        2, 1,
        NULL,
    },
    // 0x89
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x8A
    {
        ksNesInst_txa_8a,
        2, 1,
        NULL,
    },
    // 0x8B
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x8C
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_sty_8c,
    },
    // 0x8D
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_sta_8d,
    },
    // 0x8E
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_stx_8e,
    },
    // 0x8F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x90
    {
        ksNesInst_bcc_90,
        3, 2,
        NULL,
    },
    // 0x91
    {
        ksNesInst_sta_91,
        6, 2,
        NULL,
    },
    // 0x92
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x93
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x94
    {
        ksNesInst_sty_94,
        4, 2,
        NULL,
    },
    // 0x95
    {
        ksNesInst_sta_95,
        4, 2,
        NULL,
    },
    // 0x96
    {
        ksNesInst_stx_96,
        4, 2,
        NULL,
    },
    // 0x97
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x98
    {
        ksNesInst_tya_98,
        2, 1,
        NULL,
    },
    // 0x99
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_sta_99,
    },
    // 0x9A
    {
        ksNesInst_txs_9a,
        2, 1,
        NULL,
    },
    // 0x9B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x9C
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x9D
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_sta_9d,
    },
    // 0x9E
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x9F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xA0
    {
        ksNesInst_ldy_a0,
        2, 2,
        NULL,
    },
    // 0xA1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_lda_a1,
    },
    // 0xA2
    {
        ksNesInst_ldx_a2,
        2, 2,
        NULL,
    },
    // 0xA3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xA4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ldy_a0,
    },
    // 0xA5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_lda_a1,
    },
    // 0xA6
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ldx_a2,
    },
    // 0xA7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xA8
    {
        ksNesInst_tay_a8,
        2, 1,
        NULL,
    },
    // 0xA9
    {
        ksNesInst_lda_a1,
        2, 2,
        NULL,
    },
    // 0xAA
    {
        ksNesInst_tax_aa,
        2, 1,
        NULL,
    },
    // 0xAB
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xAC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ldy_a0,
    },
    // 0xAD
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xAE
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ldx_a2,
    },
    // 0xAF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xB0
    {
        ksNesInst_bcs_b0,
        3, 2,
        NULL,
    },
    // 0xB1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_lda_a1,
    },
    // 0xB2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xB3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xB4
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_ldy_a0,
    },
    // 0xB5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_lda_a1,
    },
    // 0xB6
    {
        ksNesInst_ldx_b6,
        4, 2,
        NULL,
    },
    // 0xB7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xB8
    {
        ksNesInst_clv_b8,
        2, 1,
        NULL,
    },
    // 0xB9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xBA
    {
        ksNesInst_tsx_ba,
        2, 1,
        NULL,
    },
    // 0xBB
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xBC
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_ldy_a0,
    },
    // 0xBD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xBE
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_ldx_a2,
    },
    // 0xBF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xC0
    {
        ksNesInst_cpy_c0,
        2, 2,
        NULL,
    },
    // 0xC1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_cmp_c1,
    },
    // 0xC2
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xC3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xC4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cpy_c0,
    },
    // 0xC5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cmp_c1,
    },
    // 0xC6
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_dec_c6,
    },
    // 0xC7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xC8
    {
        ksNesInst_iny_c8,
        2, 1,
        NULL,
    },
    // 0xC9
    {
        ksNesInst_cmp_c1,
        2, 2,
        NULL,
    },
    // 0xCA
    {
        ksNesInst_dex_ca,
        2, 1,
        NULL,
    },
    // 0xCB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xCC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cpy_c0,
    },
    // 0xCD
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xCE
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_dec_c6,
    },
    // 0xCF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xD0
    {
        ksNesInst_bne_d0,
        3, 2,
        NULL,
    },
    // 0xD1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_cmp_c1,
    },
    // 0xD2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xD3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xD4
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xD5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_cmp_c1,
    },
    // 0xD6
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_dec_c6,
    },
    // 0xD7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xD8
    {
        ksNesInst_cld_d8,
        2, 1,
        NULL,
    },
    // 0xD9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xDA
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xDB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xDC
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xDD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xDE
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_dec_c6,
    },
    // 0xDF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xE0
    {
        ksNesInst_cpx_e0,
        2, 2,
        NULL,
    },
    // 0xE1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_sbc_e1,
    },
    // 0xE2
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xE3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xE4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cpx_e0,
    },
    // 0xE5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_sbc_e1,
    },
    // 0xE6
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_inc_e6,
    },
    // 0xE7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xE8
    {
        ksNesInst_inx_e8,
        2, 1,
        NULL,
    },
    // 0xE9
    {
        ksNesInst_sbc_e1,
        2, 2,
        NULL,
    },
    // 0xEA
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xEB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xEC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cpx_e0,
    },
    // 0xED
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xEE
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_inc_e6,
    },
    // 0xEF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF0
    {
        ksNesInst_beq_f0,
        3, 2,
        NULL,
    },
    // 0xF1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_sbc_e1,
    },
    // 0xF2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xF4
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_sbc_e1,
    },
    // 0xF6
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_inc_e6,
    },
    // 0xF7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xF8
    {
        ksNesInst_sed_f8,
        2, 1,
        NULL,
    },
    // 0xF9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xFA
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xFB
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xFC
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xFD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xFE
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_inc_e6,
    },
    // 0xFF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
};
// clang-format on

#endif /* !TARGET_PC */

void ksNesDrawMakeOBJIndTex(ksNesCommonWorkObj* wp) {
    static const u8 array[] = {
        0x00, 0x02, 0x04, 0x06, 0x07, 0x05, 0x03, 0x01,
    };
    u32 i;
    u32 j;

    for (i = 0; i < 16; i++) {
#define TO_IND1(x) (((x) / 4) * 32) + (((x) % 4) * 8)
#define TO_IND2(x) (((x) / 4) * 32) + (((x) % 4) * 2)
        for (j = 0; j < 4; j++) {
            wp->draw_ctx.sprite_indirect_lut[TO_IND1(i) + TO_IND2(j)] = (i >> 3) & 1;
            wp->draw_ctx.sprite_indirect_lut[TO_IND1(i) + TO_IND2(j) + 1] = array[i & 7] << 2;
        }
    }
#undef TO_IND1
#undef TO_IND2
    DCFlushRangeNoSync(wp->draw_ctx.sprite_indirect_lut, sizeof(wp->draw_ctx.sprite_indirect_lut));
}

void ksNesDrawMakeOBJIndTexMMC5(ksNesCommonWorkObj* wp) {
#define TO_IND1(x) (((x) / 4) * 32) + (((x) % 4) * 8)
#define TO_IND2(x) (((x) / 4) * 32) + (((x) % 4) * 2)
    for (u32 i = 0; i < 16; i++) {
        for (u32 j = 0; j < 4; j++) {
            static const u8 array[] = { 0x00, 0x01, 0x02, 0x03 };
            wp->draw_ctx.sprite_indirect_lut[TO_IND1(i) + TO_IND2(j)] = 0;
            wp->draw_ctx.sprite_indirect_lut[TO_IND1(i) + TO_IND2(j) + 1] = array[i % 4] * 4;
        }
    }
#undef TO_IND1
#undef TO_IND2
    DCFlushRangeNoSync(&wp->draw_ctx.sprite_indirect_lut, sizeof(wp->draw_ctx.sprite_indirect_lut));
}

void ksNesConvertChrToI8(ksNesCommonWorkObj* wp, const u8* data, u32 flags) {
    u32 idx;
    u32 bufSize;
    u32 b;
    u32 a;
    u32 c;
    u32 abc;
    u32 i;
    u32 j;
    u32 d;
    u32 mask;

    bufSize = (wp->chr_to_i8_buf_size > CHR_TO_I8_BUF_SIZE ? 0x100 : wp->chr_to_i8_buf_size >> 12);
    idx = (flags >> 9) & 0x1f;

    a = (flags & 0x40) << 5;
    b = (flags >> 4) & 0x18;
    c = (flags & 0x3f) << 5;
    abc = c + a + b;

    for (i = 0; i < 8; i++) {
        if (i & 1) {
            d = (data[7 - (i >> 1)]) | (data[0xf - (i >> 1)] << 8);
        } else {
            d = (data[(i >> 1)]) | (data[8 + (i >> 1)] << 8);
        }

        mask = 0x8080;
        for (j = 0; j < 8; j++) {
            wp->chr_to_u8_bufp[abc + (flags & 0x3e00) * 8 + (i * (bufSize >> 3)) * 0x1000 + j] =
                (((d & mask) & 0xff00) != 0 ? 2 : 0) | (((u16)(d & mask) & 0x00FF) != 0 ? 1 : 0);
            mask >>= 1;
        }
        DCStoreRangeNoSync(wp->chr_to_u8_bufp + (((idx) + (i * (bufSize >> 3))) * 0x1000 + b + a + c), 0x20);
    }
}

void ksNesConvertChrToI8MMC5(ksNesCommonWorkObj* wp, const u8* ptr, u32 flag) {
    u32 idx;
    u32 adj;
    u32 b;
    u32 a;
    u32 c;
    u32 abc;
    u32 i;
    u32 j;
    u32 v;
    u32 mask;

    idx = (flag >> 9) & 0x3F;
    adj = wp->chr_to_i8_buf_size >> 12;

    a = ((flag & 0x40) << 5);
    b = ((flag >> 4) & 0x18);
    c = ((flag & 0x3F) << 5);
    abc = c + a + b;

    for (i = 0; i < 8; i++) {
        v = ptr[i] | ((ptr[8 + i]) << 8);
        mask = 0x8080;

        for (j = 0; j < 8; j++) {
            wp->chr_to_u8_bufp[abc + (flag & (0x3F << 9)) * 8 + (i * (adj >> 3)) * 0x1000 + j] =
                (((v & mask) & 0xFF00) != 0 ? 2 : 0) | ((((u16)(v & mask)) & 0x00FF) != 0 ? 1 : 0);
            mask >>= 1;
        }

        DCStoreRangeNoSync(wp->chr_to_u8_bufp + ((idx + ((i * (adj >> 3)))) * 0x1000 + b + a + c), 32);
    }
}

void ksNesQDSoundSync() {
    u32 i;
    u32 j;
    for (i = 0; i < 0xd; i++) {
        for (j = 0; j < 0x106; j++) {
            Sound_Write(0, 0, j * 0x72);
        }
        OSTick tick = OSGetTick();
        while (OSTicksToMilliseconds(OSGetTick() - tick) < 16) {}
    }
}

#define ksNes_READ16LE(buf, ofs) (((buf)[ofs + 1] << 8) | (buf)[ofs])
#define ksNes_READ16LE2(buf, ofs) ((buf)[ofs] | ((buf)[ofs + 1] << 8))
#define ksNes_ADDR2BANK(addr) (((addr) >> 13) & 0x7FFFF)

#define QD_DISK_SIZE 0x10000

#define QD_BLOCK_DISKINFO 1
#define QD_BLOCK_AMOUNT 2
#define QD_BLOCK_FILEHEADER 3
#define QD_BLOCK_FILEDATA 4

#define QD_BLOCK_DISKINFO_SZ 0x3A
#define QD_BLOCK_AMOUNT_SZ 0x04
#define QD_BLOCK_FILEHEADER_SZ 0x12
#define QD_BLOCK_FILEDATA_SZ(n) ((n) + 3)

#define QD_FILE_TYPE_PRAM 0 // program
#define QD_FILE_TYPE_CRAM 1 // character
#define QD_FILE_TYPE_VRAM 2 // name table

/**
 * QD Format Documentation
 *   QD format is made up of "block" types. List of block types:
 *      - 1: disk info block, disk info, size=0x3A
 *      - 2: amount block, amount of files on disk, size=0x04
 *      - 3: file header block, info about file which follows, size=0x12
 *      - 4: file data block, raw file data, size=0x01+file_size+0x02
 */

// QD/FDS format documentation https://www.nesdev.org/wiki/FDS_disk_format
int ksNesQDFastLoad(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    u8* search_p;
    u8* disk_end_p;
    u32 boot_file_no;
    u32 file_count;
    u32 load_ofs;
    u32 size;
    u32 i;

    if ((sp->frame_flags & 0x400) != 0) {
        return -1;
    }

    search_p = sp->nesromp;
    disk_end_p = &search_p[QD_DISK_SIZE];

    // listed as 'unknown' & always 0xFF on nesdev, when non-zero we exit immediately with error code?
    if (search_p[21] != 0) {
        return 0x45C;
    }

    memset(sp->wram + 0x200, 0, 0x600);
    boot_file_no = search_p[25];                           // boot file number
    file_count = search_p[QD_BLOCK_DISKINFO_SZ + 1];       // amount->file_amount
    search_p += QD_BLOCK_DISKINFO_SZ + QD_BLOCK_AMOUNT_SZ; // skip immediately to first file info block

    while (file_count != 0 && search_p < disk_end_p) {
        if (search_p[0] != QD_BLOCK_FILEHEADER || search_p[18] != 4) {
            break;
        }

        size = ksNes_READ16LE2(search_p, 13);
        // load file ID, check it's less than the boot file
        if (search_p[2] <= boot_file_no) {
            load_ofs = ksNes_READ16LE2(search_p, 11);

            // file type
            if (search_p[15] != QD_FILE_TYPE_PRAM) {
                if (load_ofs < KS_NES_CHRRAM_SIZE && size <= KS_NES_CHRRAM_SIZE) {
                    memcpy(sp->chrramp + load_ofs, &search_p[QD_BLOCK_FILEHEADER_SZ + 1], size);
                }
            } else if (((load_ofs < KS_NES_WRAM_SIZE || load_ofs > (0x6000 - 1)) &&
                        (load_ofs < 0xE000 && ((load_ofs + size) <= KS_NES_WRAM_SIZE || (load_ofs + size) > 0x6000))) &&
                       (load_ofs + size) <= 0xE000 && (size <= KS_NES_BBRAM_SIZE && size != 0)) {
                if (load_ofs < KS_NES_WRAM_SIZE) {
                    memcpy(sp->wram + load_ofs, &search_p[QD_BLOCK_FILEHEADER_SZ + 1], size);
                } else {
                    memcpy(sp->bbramp + (load_ofs - 0x6000), &search_p[QD_BLOCK_FILEHEADER_SZ + 1], size);
                }
            }
        }

        search_p += QD_BLOCK_FILEDATA_SZ(size) + QD_BLOCK_FILEHEADER_SZ;
        file_count--;
    }

    for (i = 0; i < KS_NES_CHRRAM_SIZE; i += 16) {
        ksNesConvertChrToI8(wp, sp->chrramp + i, i / 16);
    }

    return 0;
}

int ksNesQDFastSave(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    u32 j;
    u8* qd_disk;
    u32 wram_14;
    u8* disk_end_p;
    u8* search_p;
    u32 save_len;
    u32 read_ofs;
    u32 i;

    if ((sp->frame_flags & 0x400) != 0) {
        return -1;
    }

    if (sp->fds_fast_io_lock != 0) {
        return -1;
    }

    for (i = 0; i < sp->fds_disk_count; i++) {
        qd_disk = &sp->nesromp[i * QD_DISK_SIZE];
        if (memcmp(&qd_disk[15], sp->_176E, 10) == 0) {
            goto search_start;
        }
    }
    return -1;

search_start:
    wram_14 = sp->wram[14];
    disk_end_p = qd_disk + QD_DISK_SIZE;
    search_p = qd_disk + 0x3E;
    while (wram_14 != 0 && search_p < disk_end_p) {
        if (search_p[0] != 3 || search_p[18] != 4) {
            return -1;
        }

        search_p += ksNes_READ16LE2(search_p, 13) + 21; // load file size plus 21?
        wram_14--;
    }

    save_len = ksNes_READ16LE(sp->_176E, 21);
    read_ofs = ksNes_READ16LE(sp->_176E, 24);

    if (search_p + (save_len + 21) >= disk_end_p) {
        return -1;
    }

    search_p[0] = 3;            // write file header block code? (3)
    search_p[1] = sp->wram[14]; // write file number?
    memcpy(search_p + 2, sp->_176E + 10, 14);

    // write file data block code (4)
    search_p[18] = 4;
    search_p += 19;

    // write data

    j = 0;
    for (j = 0; j < save_len; j++) {
        u8* read_p = (&sp->cpu_0000_1fff)[ksNes_ADDR2BANK(read_ofs + j)] + j;
        *search_p++ = read_p[read_ofs];
    }

    // increase file num?
    qd_disk[0x3B] = sp->wram[14] + 1;
    sp->qd_irq_acknowledged_flag = 1;
    return 0;
}

void ksNesPushResetButton(ksNesStateObj* sp) {
    sp->cpu_state.A = 0;
    sp->cpu_state.X = 0;
    sp->cpu_state.Y = 0;
    sp->cpu_state.S = 0xff;
    sp->cpu_state.P = 4;
    sp->cpu_state.irq_pending_flag = 0;
    sp->cpu_state.apu_frame_counter_mode = 0x40;
    sp->cpu_state.irq_status_flags = 0;
    sp->cpu_state.mapper_irq_enable = 0;

    // disable scanline IRQs
    sp->scanline_irq_target_val = 0x7fff;
    sp->mmc5_scanline_irq_target_val = 0x7fff;

    sp->sprite0_hit_scanline = 0xff;

    sp->_17CB = 0;
    sp->_17CC = 0;

    sp->qd_disk_head_position.full = 0;

    // fds control register initialized to 0x27, bit 5 on, transfer mode is read, motor is stopped, and transfer timing state is reset
    sp->fds_control_register = KS_NES_FDS_CTRL_FLG_5 | KS_NES_FDS_CTRL_FLG_TRANSFER_MODE | KS_NES_FDS_CTRL_FLG_MOTOR | KS_NES_FDS_CTRL_FLG_TRANSFER_RESET;
    sp->_16BC = 0x27;

    sp->motor_timer = 0;

    sp->fds_ready_delay_counter = 120;

    sp->_179D = 0xff;
    sp->_179F = 0;

    // grab the reset vector and assign it to the program counter.
    sp->PC = (sp->cpu_e000_ffff[0xfffd] << 8) | sp->cpu_e000_ffff[0xfffc];

    return;
}

int ksNesReset(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags, u8* chrramp, u8* bbramp) {
#ifdef TARGET_PC
    /* On PC, fixNES handles NES emulation — ksNesReset just needs to succeed */
    (void)wp; (void)sp; (void)flags; (void)chrramp; (void)bbramp;
    return 0;
}
#else
{
    u8* wramp;
    uint uVar1;
    uint uVar2;
    int iVar2;
    int result;
    u8* nesromp;
    OSTick os_tick;
    uint uVar4;
    size_t count;
    u8 bVar1;
    int i;

    // 0x40XX values appear to be NES APU addresses
    // 0x5015 could be the address of the MMC5's audio status register
    // i think these are arguments for something like Sound_Write(u16, u8, u8)
    static u16 sound_init_data[] = {
        0x4015, 0x0000, 0x4008, 0x0000, 0x4080, 0x0080, 0x5015, 0x0000, 0x4010, 0x000f,
        0x4011, 0x0000, 0x4012, 0x0000, 0x4013, 0x0000, 0x4015, 0x0000, 0x5015, 0x0007,
    };
    const static u8 table[] = { 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04,
                                0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x04, 0x04 };

    // looks like we're checking memory alignment.
    // maybe done for performance reasons?
    if ((uint)wp & 0x1f || (uint)sp & 0x1f || (uint)&wp->draw_ctx & 0x1f || (uint)&wp->draw_ctx.ppu_scanline_regs & 0x1f ||
        (uint)sp->ppu_chr_banks & 0x03 || (uint)&wp->draw_ctx.post_process_lut & 0x1f) {
        return 0x515;
    }

    if ((flags & 0x40) == 0) {
        Sound_SetC000(sp->wram);
        Sound_SetE000(sp->wram);

        for (u32 i = 0; i < 0x106; i++) {
            if (!(i & 7) && 0x40 <= i && i < 0x90) {

                uVar1 = i - 0x40 >> 3 & 0x3fffffff;

                Sound_Write((u16)sound_init_data[uVar1], (u8)sound_init_data[uVar1 + 1], i * 0x72);
            }

            Sound_Write(0, 0, i * 0x72);
        }
    }

    if (flags & 1) {
        // temporarily save the work ram state.
        memcpy(&wp->draw_ctx, &sp->wram, KS_NES_WRAM_SIZE);
    }

    // zero out the state struct.
    memset(sp, 0, sizeof(ksNesStateObj));

    if (flags & 1) {
        // restore the previously saved work ram state.
        memcpy(&sp->wram, &wp->draw_ctx, KS_NES_WRAM_SIZE);
    } else {
        // fill ram with a predetermined pattern.

        for (i = 0, iVar2 = 0; i < 0x200; iVar2 += 4, i++) {
            wramp = &sp->wram[iVar2];

            wramp[0] = 0x0f;
            wramp[1] = 0xef;
            wramp[2] = 0xfe;
            wramp[3] = 0x7d;
        }
    }

    // zero out the private work struct
    memset(&wp->draw_ctx, 0, sizeof(ksNesDrawCtx));

    for (i = 0; i < 0x18; i++) {
        sp->ppu_chr_bank_pointers[i] = &sp->ppu_nametable_ram[table[i & 0xf] * 0x100];
    }

    sp->nesromp = wp->nesromp;
    nesromp = sp->nesromp;

    if (nesromp[0] == 1) {
        if (((chrramp == nullptr) || (bbramp == nullptr)) || ((flags & 0x10) == 0)) {
            return 0x570;
        }
        memcpy(&sp->ppu_nametable_pointers[0], &sp->ppu_chr_bank_pointers[12], 0x10);
        sp->fds_disk_count = wp->fds_disk_count;
    } else {
        // extract the mapper number from the ines header
        sp->mapper = (nesromp[7] & 0xf0) | (nesromp[6] >> 4);

        // skip over the ines header to grab a pointer to the prg rom data.
        sp->prgromp = sp->nesromp + KS_NES_NESFILE_HEADER_SIZE;

        // extract the prg rom size from the ines header and convert it from 16k chunks to bytes.
        sp->prg_size = (uint)sp->nesromp[0x4] << 0xe;

        if (sp->prg_size > wp->prg_size) {
            return 0x57a;
        }

        // calculate the number of 8k PRG ROM banks.
        sp->prg_banks = (sp->prg_size >> 0xd) - 1;

        // extract the chr ram/rom size from the ines header and convert it from 8k chunks to bytes.
        sp->chr_size = (size_t)sp->nesromp[0x5] << 0xd;

        if ((sp->chr_size > 0x40000) && ((sp->mapper != KS_NES_MAPPER_MMC5 || (wp->chr_to_i8_buf_size < sp->chr_size << 2)))) {
            return 0x584;
        }

        if ((sp->nesromp[0x6] & 1)) {
            memcpy(&sp->ppu_nametable_pointers[0], &sp->ppu_chr_bank_pointers[8], 0x10);
        } else {
            memcpy(&sp->ppu_nametable_pointers[0], &sp->ppu_chr_bank_pointers[12], 0x10);
        }
    }

    sp->reset_flags = flags;

    if (sp->mapper == KS_NES_MAPPER_MMC5) {
        ksNesDrawMakeOBJIndTexMMC5(wp);
    } else {
        ksNesDrawMakeOBJIndTex(wp);
    }

    if ((flags & 0x20) == 0) {
        memcpy(sp->palette_normal, &ksNesPaletteNormal, 0x80);
    }

    for (i = 0; i < 0x80; i++) {
        sp->ppu_palette_ram[i] = 0x0f;
    }

    for (i = 0; i < 8; i++) {
        sp->ppu_internal_state[i] = 0x20;
    }

    for (i = 0; i < 0xf0; i++) {
        wp->draw_ctx.ppu_scanline_regs[i].nametable_ptrs[0] = sp->ppu_nametable_pointers[0];
        wp->draw_ctx.ppu_scanline_regs[i].nametable_ptrs[1] = sp->ppu_nametable_pointers[1];
    }

    for (i = 0; i < 8; i++) {
        sp->ppu_chr_banks[i] = (u8)i;
    }

    memset(wp->chr_to_u8_bufp, 0, wp->chr_to_i8_buf_size);

    if (sp->chr_size == 0) {
        if (chrramp == nullptr) {
            return 0x5be;
        }

        sp->chr_ram_write_enable = TRUE;
        sp->chrramp = chrramp;
        sp->chr_size = 0x2000;

        if (((flags & 8) != 0) && (sp->mapper == KS_NES_MAPPER_MMC5)) {
            sp->chr_size = 0x20000;
        }

        if ((flags & 2) == 0) {
            memset(sp->chrramp, 0, sp->chr_size);
        }

    } else {
        sp->chrramp = sp->prgromp + sp->prg_size;

        if (sp->mapper == KS_NES_MAPPER_MMC5) {
            for (uVar4 = 0; uVar4 < sp->chr_size; uVar4 = uVar4 + 0x10) {
                ksNesConvertChrToI8MMC5(wp, sp->chrramp + uVar4, uVar4 >> 4);
            }
        } else {
            for (uVar4 = 0; uVar4 < sp->chr_size; uVar4 = uVar4 + 0x10) {
                ksNesConvertChrToI8(wp, sp->chrramp + uVar4, uVar4 >> 4);
            }
        }
    }

    sp->chr_banks = (sp->chr_size >> 10) - 1;

    DCFlushRangeNoSync(wp->chr_to_u8_bufp, wp->chr_to_i8_buf_size);

    sp->cpu_cycles_per_visible_scanline = -7614; // 113.6666666666... * 64 (close?)
    sp->cpu_cycles_per_vblank_scanline = -0x2a00; // -10752
    sp->cpu_cycles_for_nmi = -0x2800; // -10240

    sp->mapper_irq_handler = ksNesLinecntIrqDefault;

    memcpy(sp->store_func, ksNesStoreFuncTblDefault, sizeof(ksNesStoreFuncTblDefault));
    memcpy(sp->store_ppu_func, ksNesStorePPUFuncTblDefault, sizeof(ksNesStorePPUFuncTblDefault));
    memcpy(sp->store_io_func, ksNesStoreIOFuncTblDefault, 0xa0);
    memcpy(sp->load_func, ksNesLoadFuncTblDefault, 0x20);
    memcpy(sp->load_io_func, ksNesLoadIOFuncTblDefault, 0x60);

    sp->cpu_0000_1fff = sp->wram;
    sp->cpu_2000_3fff = sp->wram - 0x2000;
    sp->cpu_4000_5fff = sp->wram - 0x4000;
    sp->cpu_6000_7fff = sp->wram - 0x6000;
    sp->cpu_8000_9fff = sp->prgromp - 0x8000;
    sp->cpu_a000_bfff = sp->prgromp - 0x8000;
    sp->cpu_c000_dfff = sp->prgromp + sp->prg_size - 0x10000;
    sp->cpu_e000_ffff = sp->prgromp + sp->prg_size - 0x10000;

    sp->bbramp = bbramp;

    if (bbramp) {
        sp->cpu_6000_7fff = bbramp - 0x6000;

        sp->store_func[3] = ksNesStoreBBRAM;
        sp->load_func[3] = ksNesLoadBBRAM;

        sp->bbram_mode_select = flags & 0x10 ? 3 : 0; // 0x10 = bbram multi-bank (0-3), unset = single-bank mode (only 0)
    }

    if (*sp->nesromp == 1) {
        memcpy(sp->store_io_func + 0x20, &ksNesStoreQDFuncTbl, 0x20);

        sp->cpu_8000_9fff = sp->bbramp - 0x6000;
        sp->cpu_a000_bfff = sp->bbramp - 0x6000;
        sp->cpu_c000_dfff = sp->bbramp - 0x6000;
        sp->cpu_e000_ffff = wp->noise_bufp - 0xe000;

        sp->store_func[4] = ksNesStoreBBRAM;
        sp->store_func[5] = ksNesStoreBBRAM;
        sp->store_func[6] = ksNesStoreBBRAM;
        sp->mapper_irq_handler = ksNesLinecntIrqQD;

        wp->noise_bufp[0xebd] = 0x42;
        sp->fds_disk_drive_status = 0x47; // same as below
        sp->qd_drive.registers.drive_status = 0x47; // 0x40 = ?, 0x04 = disk write protected or ejected, 0x02 = disk not ready, 0x01 = disk not inserted
        sp->qd_drive.registers.expansion_connector = 0x80; // battery voltage flag is good (0 = low, 1 = OK)

        // looks to be a special case for one particular rom
        iVar2 = memcmp(sp->nesromp + KS_NES_NESFILE_HEADER_SIZE, "koro", 4);

        if (iVar2 == 0) {
            wp->noise_bufp[0x1a0] = 0xff;
        } else {
            wp->noise_bufp[0x1a0] = 0x7f;
        }
    } else {
        uVar2 = ksNesResetAsm(wp, sp);
        if (uVar2) {
            return uVar2;
        } else {
            // check some special cases for particular roms
            if (sp->prg_size == 0x20000) {
                // Check for 'Tetris 2 + Bombliss'
                iVar2 = memcmp(sp->prgromp + 0x1ffe8, "BomBliss", 8);
                if (iVar2 == 0) {
                    sp->ppu_scanline_threshold = 3;
                } else {
                    // Check for 'Quinty' (J) (Produced by GAME FREAK)
                    // Oddly, this checks for a subset of the string
                    // 'GAME DESIGNED BY SATOSHI TAJIRI'.
                    // It also does not check for Mendel Palace, the USA localization.
                    // This is likely because the JP version uses mapper 88
                    // which is similar to mapper 206 - Namcot 118.
                    // The US version uses mapper 4 - MMC3.
                    iVar2 = memcmp(sp->prgromp + 0x1fc01, "BY!\xc8\x0dSAT", 8);
                    if (iVar2 == 0) {
                        sp->ppu_scanline_threshold = 24;
                    }
                }
            }
        }
    }

    ksNesPushResetButton(sp);
    DCStoreRange(wp, sizeof(ksNesCommonWorkObj));

    if ((flags & 0x40) == 0) {
        Sound_SetC000(&sp->cpu_c000_dfff[0xc000]);
        Sound_SetE000(&sp->cpu_e000_ffff[0xe000]);

        switch (sp->mapper) {
            case KS_NES_MAPPER_MMC5: // Nintendo's MMC5
                Sound_SetMMC(0);
                break;
            case KS_NES_MAPPER_KONAMI_VRC6A: // Konami's VRC6a
            case KS_NES_MAPPER_KONAMI_VRC6B: // Konami's VRC6b
                Sound_SetMMC(1);
                Sound_Write(0x5015, 7, 0);
                break;
            default: // all other mappers
                if (sp->nesromp[0] == 1) {
                    Sound_SetMMC(2);
                } else {
                    Sound_SetMMC(3);
                }
        }
    }

    os_tick = OSGetTick();
    sp->os_tick = os_tick;
    return 0; // return success.
}
#endif /* !TARGET_PC */

#ifndef TARGET_PC
void ksNesEmuFrame(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags) {
    u8 status;
    size_t count = 0;

    sp->frame_flags = flags;

    while (true) {
        do {
            if ((flags & 0x1000) == 0) {
                status = Sound_Read(0x4015);
                sp->cpu_state.irq_status_flags = sp->cpu_state.irq_status_flags & 0xc0 | status;

                if (wp->frames != 1) {
                    sp->cpu_state.irq_mask_flags = 0xc0;
                    sp->cpu_state.irq_status_flags = sp->cpu_state.irq_status_flags & 0xc0;
                } else {
                    sp->cpu_state.irq_mask_flags = 0xff;
                }

                status = Sound_Read(0x5015);

                sp->mmc5_apu_status = status & 0x03;

                Sound_SetC000(&sp->cpu_c000_dfff[0xc000]);
                Sound_SetE000(&sp->cpu_e000_ffff[0xe000]);
            }

            ksNesEmuFrameAsm(wp, sp);

        } while (((flags & 0x400) == 0) && ((sp->fds_control_register & KS_NES_FDS_CTRL_FLG_MOTOR) == 0));

        if (((flags & 0x4000) == 0) || count == 0)
            break;

        count--;
    }

    PPCSync();

    return;
}
#endif /* !TARGET_PC */

#ifndef TARGET_PC /* PPC inline assembly — replaced by pc_nes_core.c on PC */

#define REGISTER_A r14
#define REGISTER_X r15
#define REGISTER_Y r16
#define REGISTER_PC r17
#define REGISTER_STACK r18
#define REGISTER_FLAG_ZERO r19
#define REGISTER_FLAG_CARRY r20
#define REGISTER_FLAG_OVERFLOW r21
#define REGISTER_FLAG_NEGATIVE r22
#define REGISTER_CYCLE_COUNT r25
// r26 is reused for various purposes throughout the code
#define REGISTER_SCANLINE_STATE r26
#define REGISTER_TEMP_26 r26
#define WRAM r31

// clang-format off
asm u32 ksNesResetAsm(register ksNesCommonWorkObj* work, register ksNesStateObj* state)
{
    register void* func_tbl;
    register ksNesStateObj* state_temp;
    nofralloc

    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stw state_temp, 0xec(r1)
    stw func_tbl, 0xe8(r1)
    stw work, 0xe0(r1)
    stw state, 0xe4(r1)
    stw work, 0x08(r1)
    stw state, 0x0c(r1)

    mr state_temp, state

    li r3, 0 // return code
    lis func_tbl, ksNesMapperInitFuncTbl@h
    ori func_tbl, func_tbl, ksNesMapperInitFuncTbl@l

    // return an error if the mapper number is greater than the highest supported mapper.
    lbz r7, state_temp->mapper
    cmpwi r7, sizeof(ksNesMapperInitFuncTbl) / sizeof(ksNesMapperInitFuncTbl[0])
    blt init_mapper

mapper_error:
    li r3, 0x732
    b exit

init_mapper:
    mulli r7, r7, 0x14
    add func_tbl, func_tbl, r7

    // void* store_8000 = ksNesMapperInitFuncTbl[(mapper + 1) * 5];
    // void* store_a000 = ksNesMapperInitFuncTbl[(mapper + 2) * 5];
    // void* store_c000 = ksNesMapperInitFuncTbl[(mapper + 3) * 5];
    // void* store_e000 = ksNesMapperInitFuncTbl[(mapper + 4) * 5];
    lwz r7, 0x04(func_tbl)
    lwz r8, 0x08(func_tbl)
    lwz r9, 0x0c(func_tbl)
    lwz r10, 0x10(func_tbl)

    // state_temp->store_func[4] = store_8000;
    // state_temp->store_func[5] = store_a000;
    // state_temp->store_func[6] = store_c000;
    // state_temp->store_func[7] = store_e000;
    stw r7, state_temp->store_func[4]
    stw r8, state_temp->store_func[5]
    stw r9, state_temp->store_func[6]
    stw r10, state_temp->store_func[7]

    // return an error if the mapper number isn't supported.
    // all supported mappers have a non-null pointer defined for state->store_func[4].
    cmpwi r7, nullptr
    beq mapper_error

    // call the mapper-specific initialization function if one exists.
    // if (ksNesMapperInitFuncTbl[mapper * 5] != nullptr) {
    //     ksNesMapperInitFuncTbl[mapper * 5]();
    // }
    lwz r0, 0x00(func_tbl)
    mtctr r0
    cmpwi r0, nullptr
    bnectrl

    b exit

entry ksNesInit01
    li r8, 0x05
    stb r8, state_temp->mmc1_regs[5] // load_counter

    li r8, 0x0f
    stb r8, state_temp->mmc1_regs[0] // ctrl reg

    lwz r9, state_temp->prg_size
    lis r8, 0x08
    cmpw r9, r8
    bnelr

    li r8, 0x01
    stb r8, state_temp->mmc1_regs[4] // 512k_prg_mode_flag

    li r8, 0x10
    stb r8, state_temp->mmc1_regs[1] // chr_bank0

    blr

entry ksNesInit03

    // state_temp->store_func[3] = store_8000;
    stw r7, state_temp->store_func[3]
    blr

entry ksNesInit04
    // state_temp->mapper_irq_handler = ksNesLinecntIrq04;
    lis r8, ksNesLinecntIrq04@h
    ori r8, r8, ksNesLinecntIrq04@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit05
    // if (state_temp->bbramp == nullptr) {
    //     return 0x78e;
    // }
    lwz r8, state_temp->bbramp
    cmpwi r8, nullptr
    bne init_05
    li r3, 0x78e // error

init_05:
    // state_temp->_176E[0x2a] = 0x03;
    li r8, 0x03
    stb r8, state_temp->_1798

    // state_temp->_176E[0x2f] = 0xff;
    li r8, 0xff
    stb r8, state_temp->_179D

    // state_temp->mmc5_ext_ram_mode = 0x03;
    li r8, 0x03
    stb r8, state_temp->mmc5_ext_ram_mode

    // state_temp->mmc5_apu_pcm_mode_irq = 0x01;
    li r8, 0x01 // enable read mode
    stb r8, state_temp->mmc5_apu_pcm_mode_irq

    // state_temp->store_func[2] = ksNesStore05_4000
    lis r8, ksNesStore05_4000@h
    ori r8, r8, ksNesStore05_4000@l
    stw r8, state_temp->store_func[2]

    // state_temp->load_func[2] = ksNesLoad05_4000
    lis r8, ksNesLoad05_4000@h 
    ori r8, r8, ksNesLoad05_4000@l
    stw r8, state_temp->load_func[2]

    // state_temp->mapper_irq_handler = ksNesLinecntIrq05Vcount
    lis r8, ksNesLinecntIrq05Vcount@h
    ori r8, r8, ksNesLinecntIrq05Vcount@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit07
    // state_temp->cpu_c000_dfff = state_temp->cpu_8000_9fff;
    // state_temp->cpu_e000_ffff = state_temp->cpu_8000_9fff;
    lwz r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_c000_dfff
    stw r8, state_temp->cpu_e000_ffff

    blr

entry ksNesInit09
    // state_temp->cpu_a000_bfff = state_temp->cpu_c000_dfff;
    lwz r8, state_temp->cpu_c000_dfff
    stw r8, state_temp->cpu_a000_bfff

    blr

entry ksNesInit12
    // state_temp->mapper_irq_handler = ksNesLinecntIrq49
    lis r8, ksNesLinecntIrq49@h 
    ori r8, r8, ksNesLinecntIrq49@l 
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit13
    // if (state_temp->bbramp == nullptr) {
    //     return 0x7c3;
    // }
    lwz r8, state_temp->bbramp
    cmpwi r8, nullptr
    bne init_13
    li r3, 0x7c3

    blr

init_13:
    // state_temp->store_func[2] = ksNesStore13_4000
    lis r8, ksNesStore13_4000@h
    ori r8, r8, ksNesStore13_4000@l
    stw r8, state_temp->store_func[2]

    // state_temp->load_func[2] = ksNesLoad13_4000
    lis r8, ksNesLoad13_4000@h
    ori r8, r8, ksNesLoad13_4000@l
    stw r8, state_temp->load_func[2]

    // state_temp->mapper_irq_handler = ksNesLinecntIrq49
    lis r8, ksNesLinecntIrq49@h
    ori r8, r8, ksNesLinecntIrq49@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit15
    // state_temp->mapper_irq_handler = ksNesLinecntIrq19
    lis r8, ksNesLinecntIrq19@h
    ori r8, r8, ksNesLinecntIrq19@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit18
    // state_temp->_17CE = 0x01;
    li r8, 0x01
    stb r8, state_temp->_17CE

    // state_temp->mapper_irq_handler = ksNesLinecntIrq18
    lis r8, ksNesLinecntIrq18@h
    ori r8, r8, ksNesLinecntIrq18@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit1a
    // state_temp->_17CD = 0x03;
    li r8, 0x03;
    stb r8, state_temp->_17CD

    // state_temp->_17CE = 0x02;
    li r8, 0x02;
    stb r8, state_temp->_17CE

    // state_temp->mapper_irq_handler = ksNesLinecntIrq18
    lis r8, ksNesLinecntIrq18@h
    ori r8, r8, ksNesLinecntIrq18@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit42
    // state_temp->store_func[3] = store_8000;
    // state_temp->cpu_c000_dfff = state_temp->cpu_8000_9fff;
    // state_temp->cpu_e000_ffff = state_temp->cpu_8000_9fff;
    lwz r9, state_temp->cpu_8000_9fff
    stw r7, state_temp->store_func[3]
    stw r9, state_temp->cpu_c000_dfff
    stw r9, state_temp->cpu_e000_ffff

    blr

entry ksNesInit43
    // state_temp->mapper_irq_handler = ksNesLinecntIrq43
    lis r8, ksNesLinecntIrq43@h
    ori r8, r8, ksNesLinecntIrq43@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit45
    // state_temp->mapper_irq_handler = ksNesLinecntIrq49
    lis r8, ksNesLinecntIrq49@h
    ori r8, r8, ksNesLinecntIrq49@l
    stw r8, state_temp->mapper_irq_handler

    // state_temp->store_func[3] = ksNesLinecntIrqDefault
    lis r8, ksNesLinecntIrqDefault@h
    ori r8, r8, ksNesLinecntIrqDefault@l
    stw r8, state_temp->store_func[3]

    blr

entry ksNesInit49
    // state_temp->mapper_irq_handler = ksNesLinecntIrq49
    lis r8, ksNesLinecntIrq49@h
    ori r8, r8, ksNesLinecntIrq49@l
    stw r8, state_temp->mapper_irq_handler

    blr

entry ksNesInit56
    // state_temp->store_func[3] = ksNesStore56_6000
    lis r8, ksNesStore56_6000@h
    ori r8, r8, ksNesStore56_6000@l 
    stw r8, state_temp->store_func[3]

    blr

exit:
    lwz state_temp, 0xec(r1)
    lwz func_tbl, 0xe8(r1)
    lwz r0, 0xf4(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr
}

extern "C" void _savegpr_14(void);
extern "C" void _restgpr_14(void);

// TODO: use ksNesStateObj members instead of hardcoded offsets
asm void ksNesEmuFrameAsm(register ksNesCommonWorkObj* work_arg, register ksNesStateObj* state_arg) {
    // these might be part of a fralloc? they're stored twice
    #define STACK_WORK_ARG 0x08(r1)
    #define STACK_STATE_ARG 0x0C(r1)

    #define STACK_FRAMES 0xEC(r1)
    #define STACK_CPU_CYCLES 0xF0(r1)
    #define STACK_PPU_SCANLINE_REGS 0xF4(r1)


    register int local_25;
    register int local_26;
    register int local_27;
    register int local_28;
    register int local_29;

    register void* state_cpu_ranges;
    register void* state_store_func;
    register void* state_load_func;
    register void* instr_jump_tbl;      // r30
    register ksNesStateObj* state_temp; // r31
    
    nofralloc
    stwu r1, -0x140(r1)
    mflr r0
    stw r0, 0x144(r1)
    addi r11, r1, 0x140
    bl _savegpr_14
    //fralloc
    stw r3, 0xe0(r1)
    stw r4, 0xe4(r1)
    stw r3, STACK_WORK_ARG
    stw r4, STACK_STATE_ARG
    mr state_temp, state_arg
    addi r7, work_arg, work_arg->draw_ctx.ppu_scanline_regs
    stw r7, STACK_PPU_SCANLINE_REGS
    lwz r7, (ksNesCommonWorkObj.cpu_cycle_count)(r3)
    stw r7, STACK_CPU_CYCLES
    lbz r7, (ksNesCommonWorkObj.frames)(r3)
    stw r7, STACK_FRAMES

    // r8 = state_temp->frame_flags & 0x4000 ? 2 : 0
    lwz r7, state_temp->frame_flags
    andi. r8, r7, 0x4000
    beq asdfasdf
    li r8, 2
asdfasdf:
    stw r8, 0xe8(r1)

    // state_temp->_1A70++;
    lwz r7, state_temp->frame_counter
    addi r7, r7, 1
    stw r7, state_temp->frame_counter

    lhz REGISTER_PC, state_temp->PC
    lbz REGISTER_A, state_temp->cpu_state.A // A
    lbz REGISTER_X, state_temp->cpu_state.X // X
    lbz REGISTER_Y, state_temp->cpu_state.Y // Y
    lbz REGISTER_STACK, state_temp->cpu_state.S // S
    lbz REGISTER_FLAG_ZERO, state_temp->cpu_state.flag_z // Z
    lbz REGISTER_FLAG_CARRY, state_temp->cpu_state.flag_c // C
    lbz REGISTER_FLAG_OVERFLOW, state_temp->cpu_state.flag_v // V
    lbz REGISTER_FLAG_NEGATIVE, state_temp->cpu_state.flag_n // N

    lis instr_jump_tbl, ksNesInstJumpTbl@h
    ori instr_jump_tbl, instr_jump_tbl, ksNesInstJumpTbl@l

    // r29 = &state_temp->load_func
    addi state_load_func, state_temp, state_temp->load_func

    // r28 = &state_temp->store_func
    addi state_store_func, state_temp, state_temp->store_func

    // r27 = &state_temp->cpu_0000_1fff
    addi state_cpu_ranges, state_temp, state_temp->cpu_0000_1fff

    lwz REGISTER_CYCLE_COUNT, state_temp->cycle_count

// SUB_8003ada4
entry ksNesLinecntIrqDefault
    cmpwi REGISTER_CYCLE_COUNT, 0
    bge somewhere

entry ksNesMainLoop2
ksNesMainLoop1:
    // r26 = (REGISTER_PC >> 11) & 0x1C;
    // address range | r26  | description
    // --------------+------+--------------------------
    // 0x0000–0x1FFF | 0x00 | internal RAM and mirrors
    // 0x2000–0x3FFF | 0x04 | PPU registers and mirrors
    // 0x4000-0x5FFF | 0x08 | APU, I/O, and usually unmapped cartridge addresses
    // 0x6000–0x7FFF | 0x0C | usually cartridge RAM
    // 0x8000–0x9FFF | 0x10 | usually cartridge ROM and mapper registers
    // 0xA000–0xBFFF | 0x14 | usually cartridge ROM and mapper registers
    // 0xC000–0xDFFF | 0x18 | usually cartridge ROM and mapper registers
    // 0xE000–0xFFFF | 0x1C | usually cartridge ROM and mapper registers
    rlwinm r26, REGISTER_PC, 21, 27, 29

    // r0 = REGISTER_PC - 0x2000;
    // subtract 0x2000 from the PC.
    // if PC points to the NES's internal 2k of RAM or one if its mirrors,
    // then r0 will be negative.
    // r0 will be positive otherwise.
    //
    // address range | size   | description
    // --------------+--------+----------------------
    // 0x0000–0x07FF | 0x0800 | 2 KB internal RAM
    // 0x0800–0x0FFF | 0x0800 | mirror of $0000–$07FF
    // 0x1000–0x17FF | 0x0800 | mirror of $0000–$07FF
    // 0x1800–0x1FFF | 0x0800 | mirror of $0000–$07FF
    subi r0, REGISTER_PC, 0x2000

    // r7 = state_cpu_ranges[r26];
    // select 1 of 8 pointers to an 8k range of the CPU address space.
    lwzx r7, state_cpu_ranges, r26

    // r0 = (r0 >> 16) & 0xF800;
    // if r0 is negative then r0 = 0x00000000
    // if r0 is positive then r0 = 0x0000F800
    // r0 will be used as a bitmask later.
    rlwinm r0, r0, 16, 16, 20

    // REGISTER_PC = REGISTER_PC & 0xFFFF;
    // restrict PC to a 16-bit value.
    andi. REGISTER_PC, REGISTER_PC, 0xFFFF

    // REGISTER_PC = REGISTER_PC & ~r0;
    // if PC points to RAM or one of its mirrors then ~r0 will be 0xFFFF07FF.
    // ~r0 will be 0xFFFFFFFF otherwise.
    // that redirects RAM mirror access to actual RAM or leaves PC unchanged otherwise.
    andc REGISTER_PC, REGISTER_PC, r0

    // r12 = (u8) r7[REGISTER_PC];
    // grab the byte pointed to by PC.
    // this should be an instruction opcode.
    lbzx r12, r7, REGISTER_PC

    // r4 = REGISTER_PC + 1;
    // get the address of the byte following PC.
    addi r4, REGISTER_PC, 1

    // r26 = (r4 >> 11) & 0x1C;
    // check which CPU range the next byte falls into.
    rlwinm r26, r4, 21, 27, 29

    // r7 = r12 << 4;
    // shift the opcode byte by 4, effectively multiplying by 16.
    // that allows r7 to be used as an offset into instr_jump_tbl
    // since every item in that array is 16 bytes.
    slwi r7, r12, 4

    // r26 = state_cpu_ranges[r26];
    // get a pointer to the range containing the byte following the one pointed to by PC.
    lwzx r26, state_cpu_ranges, r26

    // r8 = instr_jump_tbl[r7]
    // r7 = &instr_jump_tbl[r7]
    // grab a pointer to the first handler function for this instruction.
    lwzux r8, r7, instr_jump_tbl

    // r10 = r7[1]
    // grab size and cycle information about this instruction
    lhz r10, 0x04(r7)

    // r9 = r7[2]
    // grab a pointer to the second handler function for this instruction.
    // may be a null pointer.
    lwz r9, 0x08(r7)

    // lr = r8
    // put the address of the first handler in the link register
    // we'll use this to call the function shortly
    mtlr r8

    andi. r11, r10, 0x00ff // instruction bytes
    andi. r10, r10, 0xff00 // instruction cycles << 8

    // ctr = r9
    // put the address of the second handler in the counter register
    // it may be called later if it isn't null.
    mtctr r9

    // r4 = (u8) r26[r4]
    // get the byte following the one pointed to by PC.
    lbzx r4, r26, r4

    // REGISTER_PC += r11
    // advance PC to the next instruction?
    add REGISTER_PC, REGISTER_PC, r11

    // REGISTER_CYCLE_COUNT += r10
    // increase the total cycle count by the number of cycles this instruction takes?
    add REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, r10

    // r4  == the byte following the instruction opcode
    // r10 == instruction cycle count shifted left by 8 bits
    // r11 == instruction length in bytes
    // REGISTER_PC == 6502 address of the next instruction
    // REGISTER_CYCLE_COUNT == something to do with cycle count
    // r26 == pointer to the range containing the byte following the instruction opcode
    // ctr == pointer to a second handler function, if any
    // lr()
    blrl

    // while (REGISTER_CYCLE_COUNT < 0)
    cmpwi REGISTER_CYCLE_COUNT, 0
    blt ksNesMainLoop1

somewhere:
    lha r3, state_temp->ppu_scanline_counter
    clrlslwi. r7, REGISTER_CYCLE_COUNT, 30, 3 // r7 = (REGISTER_CYCLE_COUNT & 0x3) << 3
    lha r9, state_temp->cpu_cycles_per_vblank_scanline
    rlwimi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 31, 30, 31
    beq LAB_8003b2f0

    cmpwi r3, 0
    add REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, r9
    blt LAB_8003b4b8

    cmpwi r3, 0xf0
    bge LAB_8003b3b4

    // r7 holds the cycle count % 4 multiplied by 8 to get the index to write the ppu_chr_banks into the scanline state's registers
    // this is done to accomodate different mapper implementations
    lwz r9, STACK_PPU_SCANLINE_REGS
    slwi r8, r3, 5
    lwz r0, state_temp->ppu_chr_banks[0]
    lwz r10, state_temp->ppu_chr_banks[4]
    add  REGISTER_SCANLINE_STATE, r8, r9 // r26 holds a pointer to the current scanline state struct
    stwux r0, r7, REGISTER_SCANLINE_STATE // store ((u32*)ppu_chr_banks)[0] to wp->draw_ctx.ppu_scanline_regs[state_temp->ppu_scanline_counter]._00[cycle_count & 3][0]
    andi. r0, REGISTER_CYCLE_COUNT, 0x1
    stw r10, (ksNesPPUScanlineState.nametable_ptrs[1])(r7) // store ((u32*)ppu_chr_banks)[4] to wp->draw_ctx.ppu_scanline_regs[r3]._00[cycle_count & 3][1]
    bne ksNesMainLoop1

    lhz r0, state_temp->ppu_register_cache[0]
    lbz r8, state_temp->_17C6
    lbz r7, state_temp->mapper
    rlwimi r0, r8, 0x9, 0x10, 0x11
    sth r0, (ksNesPPUScanlineState.ppu_ctrl)(REGISTER_SCANLINE_STATE) // update both ppu_ctrl and ppumask_flags (PPUCTRL and PPUMASK regs)
    cmpwi r7, KS_NES_MAPPER_MMC5
    bne LAB_8003b19c

    // handle MMC5 specific logic
    lbz r7, state_temp->_17C7
    stb r0, state_temp->_17C7
    xor r9, r7, r0
    and r9, r9, r7
    andi.      r9, r9, 0x8
    beq        LAB_8003aecc
    cmpwi      r8, 0x60
    bge        LAB_8003aecc
    addi       r7, state_temp, state_temp->ppu_palette_ram
    addi       r9, r8, 0x20
    add        r8, r8, r7
    stb        r9, state_temp->_17C6
    rlwimi     r0, r9, 0x9, 0x10, 0x11
    sth        r0, (ksNesPPUScanlineState.ppu_ctrl)(REGISTER_SCANLINE_STATE)
    add        r9, r9, r7
    lswi       r3, r8, 0x10
    addi       r8, r8, 0x10
    stswi      r3, r9, 0x10
    addi       r9, r9, 0x10
    lswi       r3, r8, 0x10
    stswi      r3, r9, 0x10
    lha        r3, state_temp->ppu_scanline_counter

LAB_8003aecc:
    lbz        r7, state_temp->_179E
    lhz        r8, state_temp->chr_banks
    lbz        r9, state_temp->_17A7
    cmpwi      r7, 0x2
    bge        LAB_8003af34
    cmpwi      r7, 0x0
    bne        LAB_8003af00
    rlwinm     r9, r9, 0x3, 0x0, 0x1c
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    b          LAB_8003afc4
LAB_8003af00:
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    lbz        r9, state_temp->_17A3
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x18, 0x1b
    b          LAB_8003afc4
LAB_8003af34:
    cmpwi      r7, 0x2
    bne        LAB_8003afa8
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    lbz        r9, state_temp->_17A5
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x1c, 0x1d
    lbz        r9, state_temp->_17A3
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x1a, 0x1b
    lbz        r9, state_temp->_17A1
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x18, 0x19
    b          LAB_8003afc4
LAB_8003afa8:
    addi       r7, state_temp, state_temp.mapper_chr_bank_ext[-1]
    addi       r0, state_temp, state_temp.mapper_chr_bank_ext[8-1]
LAB_8003afb0:
    lbzu       r9, 0x1(r7)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    rlwinm     r10, r9, 0x0, 0x1f, 0x1f
    cmpw       r7, r0
    bne        LAB_8003afb0
LAB_8003afc4:
    stb        r10, (ksNesPPUScanlineState.chr_bank_ext_upper_sprite)(REGISTER_SCANLINE_STATE)
    lbz        r0, state_temp->ppu_register_cache[0]
    andi.      r0, r0, 0x20
    beq        LAB_8003b134
    lbz        r7, state_temp->_179E
    lhz        r8, state_temp->chr_banks
    lbz        r9, state_temp->_17AB
    cmpwi      r7, 0x2
    bge        LAB_8003b054
    cmpwi      r7, 0x0
    bne        LAB_8003b01c
    rlwinm     r9, r9, 0x3, 0x0, 0x1c
    addi       r6, REGISTER_SCANLINE_STATE, 0xf
    and        r9, r9, r8
    addi       r0, r6, 0x8
LAB_8003b000:
    stbu       r9, 0x1(r6)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    rlwimi     r10, r9, 0x18, 0x1f, 0x1f
    cmpw       r6, r0
    addi       r9, r9, 0x1
    bne        LAB_8003b000
    b          LAB_8003b138
LAB_8003b01c:
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    addi       r6, REGISTER_SCANLINE_STATE, 0x10
    and        r9, r9, r8
    addi       r0, r6, 0x4
LAB_8003b02c:
    stb        r9, 0x0(r6)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    stb        r9, 0x4(r6)
    addi       r6, r6, 0x1
    rlwimi     r10, r9, 0x18, 0x1f, 0x1f
    cmpw       r6, r0
    addi       r9, r9, 0x1
    bne        LAB_8003b02c
    rlwimi     r10, r10, 0x4, 0x18, 0x1b
    b          LAB_8003b138
LAB_8003b054:
    cmpwi      r7, 0x2
    bne        LAB_8003b0b0
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 2)(REGISTER_SCANLINE_STATE)
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[1] + 2)(REGISTER_SCANLINE_STATE)
    addi       r9, r9, 0x1
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 3)(REGISTER_SCANLINE_STATE)
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[1] + 3)(REGISTER_SCANLINE_STATE)
    rlwinm     r10, r9, 0x1d, 0x1a, 0x1a
    lbz        r9, state_temp->_17A9
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 0)(REGISTER_SCANLINE_STATE)
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[1] + 0)(REGISTER_SCANLINE_STATE)
    addi       r9, r9, 0x1
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 1)(REGISTER_SCANLINE_STATE)
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[1] + 1)(REGISTER_SCANLINE_STATE)
    rlwimi     r10, r8, 0x1f, 0x18, 0x18
    rlwinm     r9, r10, 0x1f, 0x1, 0x1f
    or         r10, r10, r9
    rlwimi     r10, r10, 0x1c, 0x18, 0x1b
    b          LAB_8003b138
LAB_8003b0b0:
    lbz        r10, state_temp->mapper_chr_bank_ext[11]
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 3)(REGISTER_SCANLINE_STATE)
    lbz        r9, state_temp->_17AA
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 2)(REGISTER_SCANLINE_STATE)
    lbz        r9, state_temp->_17A9
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 1)(REGISTER_SCANLINE_STATE)
    lbz        r9, state_temp->_17A8
    and        r9, r9, r8
    stb        r9, (ksNesPPUScanlineState.chr_bank_bg[0] + 0)(REGISTER_SCANLINE_STATE)
    lwz        r9, (ksNesPPUScanlineState.chr_bank_bg[0])(REGISTER_SCANLINE_STATE)
    stw        r9, (ksNesPPUScanlineState.chr_bank_bg[1])(REGISTER_SCANLINE_STATE)
    lbz        r9, state_temp->mapper_chr_bank_ext[10]
    subi       r10, r10, 0x1
    lbz        r8, state_temp->mapper_chr_bank_ext[9]
    xori       r10, r10, 0xff
    lbz        r0, state_temp->mapper_chr_bank_ext[8]
    subi       r9, r9, 0x1
    andi.      r10, r10, 0x11
    xori       r9, r9, 0xff
    subi       r8, r8, 0x1
    andi.      r9, r9, 0x22
    li         r0, -0x1
    or         r10, r10, r9
    xori       r8, r8, 0xff
    xori       r0, r0, 0xff
    andi.      r8, r8, 0x44
    andi.      r0, r0, 0x88
    or         r10, r10, r8
    or         r10, r10, r0
    b          LAB_8003b138
LAB_8003b134:
    lbz        r10, (ksNesPPUScanlineState.chr_bank_ext_upper_sprite)(REGISTER_SCANLINE_STATE)
LAB_8003b138:
    stb        r10, (ksNesPPUScanlineState.chr_bank_ext_upper_bg)(REGISTER_SCANLINE_STATE)
    lhz        r7, state_temp->ppu_vram_addr_v_hi
    addi       r0, state_temp, state_temp->ppu_nametable_pointers
    xori       r9, r7, 0x100
    rlwinm     r8, r7, 0x1a, 0x1c, 0x1d
    rlwinm     r9, r9, 0x1a, 0x1c, 0x1d
    lwzx       r8, r8, r0
    lwzx       r9, r9, r0
    addi       r0, state_temp, state_temp->cartridge_nametable_ram
    cmpw       r8, r0
    bne        LAB_8003b168
    lhz        r8, state_temp->_17AC
LAB_8003b168:
    cmpw       r9, r0
    bne        LAB_8003b174
    lhz        r9, state_temp->_17AC
LAB_8003b174:
    lbz        r0, state_temp->mmc5_ext_ram_mode
    lbz        r10, state_temp->_17C0
    cmpwi      r0, 0x1
    bne        LAB_8003b188
    ori        r10, r10, 0x20
LAB_8003b188:
    stb        r10, (ksNesPPUScanlineState.mmc5_ext_mode)(REGISTER_SCANLINE_STATE)
    stw        r8, (ksNesPPUScanlineState.nametable_ptrs[0])(REGISTER_SCANLINE_STATE)
    stw        r9, (ksNesPPUScanlineState.nametable_ptrs[1])(REGISTER_SCANLINE_STATE)
    andi.      r4, r7, 0x7
    b          LAB_8003b1dc
LAB_8003b19c:
    lhz        r7, state_temp->ppu_vram_addr_v_hi
    addi       r0, state_temp, state_temp->ppu_nametable_pointers
    xori       r9, r7, 0x100
    rlwinm     r8, r7, 0x1a, 0x1c, 0x1d
    rlwinm     r9, r9, 0x1a, 0x1c, 0x1d
    lwzx       r8, r8, r0
    lwzx       r9, r9, r0
    stw        r8, (ksNesPPUScanlineState.nametable_ptrs[0])(REGISTER_SCANLINE_STATE)
    stw        r9, (ksNesPPUScanlineState.nametable_ptrs[1])(REGISTER_SCANLINE_STATE)
    rlwinm     r8, r7, 0x1e, 0x1f, 0x1f
    rlwinm     r9, r7, 0x1, 0x0, 0x1e
    xor        r10, r7, r8
    xor        r9, r7, r9
    rlwinm     r10, r10, 0x1, 0x1e, 0x1e
    rlwimi     r8, r9, 0x0, 0x1d, 0x1d
    or         r4, r8, r10
LAB_8003b1dc:
    stb        r7, (ksNesPPUScanlineState.vram_addr_y)(REGISTER_SCANLINE_STATE)
    add        r4, state_temp, r4
    addi       r8, r7, 0x1
    andi.      r0, r7, 0x300
    lbz        r10, (ksNesStateObj.ppu_render_latches)(r4)
    andi.      r8, r8, 0xff
    cmpwi      r8, 0xf0
    lbz        r9, state_temp->ppu_fine_x_scroll
    bne        LAB_8003b208
    xori       r0, r0, 0x200
    li         r8, 0x0
LAB_8003b208:
    sth        r9, (ksNesPPUScanlineState.fine_x_and_next)(REGISTER_SCANLINE_STATE)
    or         r8, r8, r0
    sth        r8, state_temp->ppu_vram_addr_v_hi
    subic.     r10, r10, 0x80
    lbz        r9, (ksNesStateObj.ppu_render_latches + 0x10)(r4)
    beq        LAB_8003b230
    stb        r10, (ksNesStateObj.ppu_render_latches)(r4)
    stb        r3, (ksNesStateObj.ppu_render_latches + 0x08)(r4)
    stb        r3, (ksNesStateObj.ppu_render_latches + 0x10)(r4)
    b          LAB_8003b244
LAB_8003b230:
    subf       r8, r9, r3
    stb        r3, (ksNesStateObj.ppu_render_latches + 0x10)(r4)
    rlwinm     r8, r8, 0x5, 0x0, 0x1a
    subf       r8, r8, REGISTER_SCANLINE_STATE
    stb        r3, (ksNesPPUScanlineState.fine_x_and_next)(r8)
LAB_8003b244:
    lbz        r8, 0x1020(state_temp)
    lbz        r10, state_temp->sprite0_hit_scanline
    cmpw       r3, r8
    bne        LAB_8003b2d8
    lbz        r8, state_temp->ppu_register_cache[0]
    li         r0, 0x0
    lbz        r10, 0x1021(state_temp)
    andi.      r9, r8, 0x20
    beq        LAB_8003b270
    rlwinm     r0, r10, 0x3, 0x1c, 0x1c
    andi.      r10, r10, 0xfe
LAB_8003b270:
    xor        r8, r8, r0
    rlwinm     r0, r10, 0x1a, 0x1e, 0x1f
    rlwinm     r8, r8, 0x1f, 0x1d, 0x1d
    add        r0, r0, state_temp
    lwz        r7, state_temp->chrramp
    add        r8, r8, r0
    lbz        r8, (ksNesStateObj.ppu_chr_banks)(r8)
    rlwinm     r10, r10, 0x4, 0x16, 0x1b
    add        r7, r7, r10
    rlwinm     r8, r8, 0xa, 0x0, 0x15
    add        r8, r8, r7
    li         r10, 0x0
LAB_8003b2a0:
    lbz        r0, 0x0(r8)
    lbz        r7, 0x8(r8)
    addi       r10, r10, 0x1
    or.        r7, r7, r0
    bne        LAB_8003b2d0
    andi.      r7, r10, 0x7
    addi       r8, r8, 0x1
    bne        LAB_8003b2a0
    subic.     r9, r9, 0x20
    addi       r8, r8, 0x8
    bge        LAB_8003b2a0
    li         r10, 0x1
LAB_8003b2d0:
    add        r10, r10, r3
    stb        r10, state_temp->sprite0_hit_scanline
LAB_8003b2d8:
    cmpw       r3, r10
    bne        ksNesMainLoop1
    lbz        r8, state_temp->ppu_internal_state[2]
    ori        r8, r8, 0x40
    stb        r8, state_temp->ppu_internal_state[2]
    b          ksNesMainLoop1
LAB_8003b2f0:
    lwz        r8, state_temp->frame_flags
    lwz        r5, STACK_CPU_CYCLES
    lbz        r7, STACK_FRAMES
    andi.      r8, r8, 0x1000
    bne        LAB_8003b340
    divwu      r5, r5, r7 // r5 = frames / _0014
    li         r3, 0x0
    bl         Sound_Write
    li         r3, KS_NES_REG_APU_STATUS
    bl         Sound_Read
    lbz        r7, state_temp->cpu_state.irq_status_flags
    lbz        r8, state_temp->cpu_state.irq_mask_flags
    or         r7, r7, r3
    and        r7, r7, r8
    stb        r7, state_temp->cpu_state.irq_status_flags
// check MMC5 audio status for MMC5 pulse1 and pulse2
    li         r3, KS_NES_REG_MMC5_AUDIO_STATUS
    bl         Sound_Read
    andi.      r3, r3, KS_NES_REG_MMC5_AUDIO_STATUS_PULSE_MASK
    stb        r3, state_temp->mmc5_apu_status
    lha        r3, state_temp->ppu_scanline_counter
LAB_8003b340:
    lha        r9, state_temp->cpu_cycles_per_visible_scanline
    addi       r8, r3, 0x1
    lwz        r7, STACK_CPU_CYCLES
    add        REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, r9
    lha        r10, state_temp->scanline_irq_target_val
    lha        r9, state_temp->mmc5_scanline_irq_target_val
    sth        r8, state_temp->ppu_scanline_counter
    addi       r7, r7, KS_NES_CPU_CYCLES_PER_SCANLINE
    stw        r7, STACK_CPU_CYCLES
    cmpw       r8, r9
    beq        ksNesLinecntIrq05Timer // LAB_8003cb78
    cmpw       r8, r10
    bne        ksNesMainLoop1
    lbz        r7, state_temp->cpu_state.apu_frame_counter_mode
    andi.      r7, r7, 0xc0
    bne        LAB_8003b390
    lbz        r7, state_temp->cpu_state.irq_status_flags
    ori        r7, r7, 0x40
    stb        r7, state_temp->cpu_state.irq_status_flags
    b          SUB_8003b3a0
LAB_8003b390:
    lwz        r8, state_temp->mapper_irq_handler
    mtspr      CTR, r8
    lbz        r7, state_temp->cpu_state.mapper_irq_enable
    bctr
 SUB_8003b3a0:
    lbz        r7, state_temp->cpu_state.P
    andi.      r7, r7, 0x4
    stb        r7, state_temp->cpu_state.irq_pending_flag
    beq        ksNesActivateIntrIRQ // FUN_8003bc54
    b          ksNesMainLoop1
LAB_8003b3b4:
    lbz        r7, state_temp->ppu_internal_state[2]
    li         r8, 0xff
    stb        r8, state_temp->sprite0_hit_scanline
    li         r8, 0x80
    li         r9, -0x16
    rlwimi     r7, r8, 0x0, 0x18, 0x19
    lwz        r8, state_temp->vblank_frame_counter
    stb        r7, state_temp->ppu_internal_state[2]
    sth        r9, state_temp->ppu_scanline_counter
    lwz        r9, STACK_WORK_ARG
    addi       r8, r8, 0x1
    stw        r8, state_temp->vblank_frame_counter
    lwz        r7, (ksNesCommonWorkObj._0044)(r9)
    addi       r7, r7, 0x1
    stw        r7, (ksNesCommonWorkObj._0044)(r9)
    lbz        r7, state_temp->fds_ready_delay_counter
    cmpwi      r7, 0xc3
    bgt        LAB_8003b418
    cmpwi      r7, 0x78
    blt        LAB_8003b418
    lwz        r9, STACK_WORK_ARG
    lwz        r8, (ksNesCommonWorkObj.pads[0])(r9)
    rlwinm.    r8, r8, 0x1, 0x1f, 0x1f
    beq        LAB_8003b420
    li         r7, 0xc3
LAB_8003b418:
    addi       r7, r7, 0x1
    stb        r7, state_temp->fds_ready_delay_counter
LAB_8003b420:
    lbz        r7, state_temp->fds_control_register
    lbz        r8, state_temp->motor_timer
    andi.      r0, r7, KS_NES_FDS_CTRL_FLG_MOTOR
    bne        LAB_8003b434
    li         r8, 90
LAB_8003b434:
    subic.     r8, r8, 0x1
    bge        LAB_8003b440
    li         r8, 0x0
LAB_8003b440:
    stb        r8, state_temp->motor_timer
    lwz        r9, STACK_WORK_ARG
    li         r8, 0x80
    addi       r7, state_temp, state_temp->ppu_palette_ram
    mtspr      CTR, r8
    li         r8, 0x0
    addi       r9, r9, ksNesCommonWorkObj.draw_ctx.post_process_lut
    addi       r3, state_temp, state_temp->palette_normal
LAB_8003b460:
    lbzx       r0, r7, r8
    rlwinm     r10, r8, 0x1, 0x1a, 0x1a
    rlwimi     r10, r8, 0x5, 0x17, 0x18
    rlwimi     r10, r8, 0x4, 0x15, 0x16
    rlwinm     r0, r0, 0x1, 0x0, 0x1e
    lhzx       r0, r3, r0
    rlwimi     r10, r8, 0x1, 0x1d, 0x1e
    addi       r8, r8, 0x1
    sthx       r0, r9, r10
    bdnz       LAB_8003b460
    lbz        r8, state_temp->_17C6
    addi       r7, state_temp, state_temp->ppu_palette_ram
    add        r8, r8, r7
    lswi       r3, r8, 0x10
    addi       r8, r8, 0x10
    stswi      r3, r7, 0x10
    addi       r7, r7, 0x10
    lswi       r3, r8, 0x10
    stswi      r3, r7, 0x10
    li         r8, 0x0
    stb        r8, state_temp->_17C6
    b          LAB_8003b570
LAB_8003b4b8:
    add        REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, r9
    rlwinm     REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x0, 0x0, 0x1d
    cmpwi      r3, -0x15
    bne        LAB_8003b4fc
    li         r7, 0x0
    stb        r7, state_temp->mmc5_scanline_irq_status
    lbz        r8, state_temp->ppu_register_cache[0]
    lha        r7, state_temp->cpu_cycles_for_nmi
    andi.      r8, r8, 0x80
    add        REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, r7
    beq        ksNesMainLoop1
    lis        r0, ksNesMainLoop2@h
    ori        r0, r0, ksNesMainLoop2@l // this gets interpreted as a nop by disassemblers
    lis        r7, 0x0
    ori        r7, r7, 0xfffa
    mtspr      CTR, r0
    b          ksNesActivateIntr
LAB_8003b4fc:
    cmpwi      r3, -0x1
    bne        ksNesMainLoop1
    lbz        r7, state_temp->ppu_internal_state[2]
    lhz        r8, state_temp->ppu_vram_addr_t_hi
    andi.      r7, r7, 0x3f
    sth        r8, state_temp->ppu_vram_addr_v_hi
    stb        r7, state_temp->ppu_internal_state[2]
    li         r8, 0x0
    sth        r8, state_temp->_17C4
    lbz        r7, state_temp->ppu_register_cache[1]
    stb        r7, state_temp->_17C7
    addi       r7, state_temp, state_temp->ppu_render_latches
    li         r8, 0x0
    li         r9, 0x0
    stswi      r8, r7, 0x8
    lbz        r8, state_temp->mapper
    cmpwi      r8, KS_NES_MAPPER_MMC5
    bne        LAB_8003b54c
    li         r7, 0x40
    stb        r7, state_temp->mmc5_scanline_irq_status
LAB_8003b54c:
    lwz        r9, STACK_WORK_ARG
    li         r0, KS_NES_OAM_TABLE_SIZE
    addi       r7, state_temp, state_temp->primary_oam - 4
    mtctr      r0
    addi       r9, r9, (ksNesCommonWorkObj.draw_ctx.OAMTable) - 4
LAB_8003b560:
    lwzu       r0, 0x4(r7)
    stwu       r0, 0x4(r9)
    bdnz       LAB_8003b560
    b          ksNesMainLoop1
LAB_8003b570:
    sth        REGISTER_PC, state_temp->PC
    stb        REGISTER_A, state_temp->cpu_state.A
    stb        REGISTER_X, state_temp->cpu_state.X
    stb        REGISTER_Y, state_temp->cpu_state.Y
    stb        REGISTER_STACK, state_temp->cpu_state.S
    stb        REGISTER_FLAG_ZERO, state_temp->cpu_state.flag_z
    stb        REGISTER_FLAG_CARRY, state_temp->cpu_state.flag_c
    cmpwi      REGISTER_FLAG_OVERFLOW, 0x0
    beq        LAB_8003b598
    li         REGISTER_FLAG_OVERFLOW, 0x40
LAB_8003b598:
    stb        REGISTER_FLAG_OVERFLOW, state_temp->cpu_state.flag_v
    stb        REGISTER_FLAG_NEGATIVE, state_temp->cpu_state.flag_n
    stw        REGISTER_CYCLE_COUNT, state_temp->cycle_count
    lwz        r3, STACK_WORK_ARG
    lwz        r7, STACK_CPU_CYCLES
    lwz        r8, (ksNesCommonWorkObj.total_cpu_cycles)(r3)
    stw        r7, (ksNesCommonWorkObj.cpu_cycle_count)(r3)
    add        r8, r8, r7
    stw        r8, (ksNesCommonWorkObj.total_cpu_cycles)(r3)

    addi r11, r1, 0x140
    bl _restgpr_14
    lwz r0, 0x144(r1)
    mtlr r0
    addi r1, r1, 0x140
    // frfree
    blr

// load a 16-bit immediate value into r3.
// calls: CTR
// < r4 = the first byte (low byte) of a 16-bit immediate
// < REGISTER_PC = 16-bit 6502 address of the following instruction
// > r3 = 16-bit immediate value following the opcode
// > r26 = ???
entry ksNesInst_load16_imm
    // decrement REGISTER_PC by 1 to get the address of the high byte of the 16-bit immediate
    subi r7, REGISTER_PC, 0x1

    // get the high byte of the 16-bit immediate from somewhere in memory
    // r8 = (r7 >> 11) & 0x1C;
    rlwinm r8, r7, 21, 27, 29
    // r9 = state_cpu_ranges[r8]
    lwzx r9, state_cpu_ranges, r8
    // r8 = r9[r7]
    lbzx r8, r9, r7

    // r26 = (r8 >> 3) & 0x1C;
    // why?
    rlwinm r26, r8, 29, 27, 29

    // r8 = r8 << 8
    slwi r8, r8, 8

    // combine the low and high bytes of the 16-bit immediate
    // r4 already had the low byte
    or r3, r4, r8

    // call the second handler for this instruction
    bctr

entry ksNesInst_load8_abs
    subi r7, REGISTER_PC, 0x1
    rlwinm r8, r7, 21, 27, 29
    lwzx r9, state_cpu_ranges, r8
    lbzx r8, r9, r7
    rlwinm r26, r8, 29, 27, 29
    slwi r8, r8, 8

    // get a pointer to a function for loading bytes
    // r9 = state_load_func[r26]
    lwzx r9, state_load_func, r26

    or r3, r4, r8
    mtspr LR, r9
    blr

entry ksNesInst_load8_absx
    subi       r7, REGISTER_PC, 0x1
    add        r4, r4, REGISTER_X
    rlwinm     r8, r7, 0x15, 0x1b, 0x1d
    lwzx       r9, state_cpu_ranges, r8
    lbzx       r8, r9, r7
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r4
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, state_load_func, r26
    mtlr       r9
    blr

entry ksNesInst_load8_absy
    subi       r7, REGISTER_PC, 0x1
    add        r4, r4, REGISTER_Y
    rlwinm     r8, r7, 0x15, 0x1b, 0x1d
    lwzx       r9, state_cpu_ranges, r8
    lbzx       r8, r9, r7
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r4
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, state_load_func, r26
    mtlr       r9
    blr

entry ksNesInst_load8_zerop
    or         r3, r4, r4
    lbzx       r4, state_temp, r4
    li         r26, 0x0
    bctr

entry ksNesInst_load8_dx
    add        r3, r4, REGISTER_X
    li         r26, 0x0
    andi.      r3, r3, 0xff
    lbzx       r4, state_temp, r3
    bctr

entry ksNesInst_load8_dxi
    add        r8, r4, REGISTER_X
    andi.      r7, r8, 0xff
    addi       r8, r8, 0x1
    lbzx       r3, state_temp, r7
    andi.      r8, r8, 0xff
    lbzx       r8, state_temp, r8
    rlwinm     r26, r8, 0x1d, 0x1b, 0x1d
    rlwimi     r3, r8, 0x8, 0x10, 0x17
    lwzx       r9, state_load_func, r26
    mtlr       r9
    blr

entry ksNesInst_load8_dyi
    lbzx       r3, state_temp, r4
    addi       r4, r4, 0x1
    andi.      r4, r4, 0xff
    lbzx       r8, state_temp, r4
    add        r3, r3, REGISTER_Y
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r3
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, state_load_func, r26
    mtlr       r9
    blr

// https://www.masswerk.at/6502/6502_instruction_set.html

//      addressing	assembler	  opc bytes cycles
// LDA (indirect,X)	LDA (oper,X)	A1	2	6
entry ksNesInst_lda_a1
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_A, r4
    b ksNesLinecntIrqDefault

// LDX zeropage,Y	LDX oper,Y	B6	2	4  
entry ksNesInst_ldx_b6
    add r7, r4, REGISTER_Y
    andi. r7, r7, 0xff
    lbzx r4, WRAM, r7
// fallthrough

// LDX immediate	LDX #oper	A2	2	2
entry ksNesInst_ldx_a2
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_X, r4
    b ksNesLinecntIrqDefault

// LDY immediate	LDY #oper	A0	2	2  
entry ksNesInst_ldy_a0
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_Y, r4
    b ksNesLinecntIrqDefault

// STA zeropage	    STA oper	85	2	3  
entry ksNesInst_sta_85
    stbx REGISTER_A, WRAM, r4
    b ksNesLinecntIrqDefault

// STX zeropage	    STX oper	86	2	3  
entry ksNesInst_stx_86
    stbx REGISTER_X, WRAM, r4
    b ksNesLinecntIrqDefault

// STY zeropage	    STY oper	84	2	3  
entry ksNesInst_sty_84
    stbx REGISTER_Y, WRAM, r4
    b ksNesLinecntIrqDefault

// STA zeropage,X	STA oper,X	95	2	4  
entry ksNesInst_sta_95
    add r7, r4, REGISTER_X
    andi. r7, r7, 0xff
    stbx REGISTER_A, WRAM, r7
    b ksNesLinecntIrqDefault

// STX zeropage,Y	STX oper,Y	96	2	4  
entry ksNesInst_stx_96
    add r7, r4, REGISTER_Y
    andi. r7, r7, 0xff
    stbx REGISTER_X, WRAM, r7
    b ksNesLinecntIrqDefault

// STY zeropage,X	STY oper,X	94	2	4  
entry ksNesInst_sty_94
    add r7, r4, REGISTER_X
    andi. r7, r7, 0xff
    stbx REGISTER_Y, WRAM, r7
    b ksNesLinecntIrqDefault

//STA absolute	    STA oper	8D	3	4  
entry ksNesInst_sta_8d
    lwzx r8, state_store_func, r26
    mr r4, REGISTER_A
    mtctr r8
    bctr

//STX absolute	    STX oper	8E	3	4  
entry ksNesInst_stx_8e
    lwzx r8, state_store_func, r26
    mr r4, REGISTER_X
    mtctr r8
    bctr

// STY absolute     STY oper	8C	3	4  
entry ksNesInst_sty_8c
    lwzx r8, state_store_func, r26
    mr r4, REGISTER_Y
    mtctr r8
    bctr

// STA  absolute,X	STA oper,X	9D	3	5  
entry ksNesInst_sta_9d
    add r3, r3, REGISTER_X
    mr r4, REGISTER_A
    rlwinm r26, r3, 21, 27, 29 //  (r3 >> 11) & 0x1C
    lwzx r8, state_store_func, r26
    mtctr r8
    bctr

// STA  absolute,Y	STA oper,Y	99	3	5  
entry ksNesInst_sta_99
    add r3, r3, REGISTER_Y
    mr r4, REGISTER_A
    rlwinm r26, r3, 21, 27, 29 //  (r3 >> 11) & 0x1C
    lwzx r8, state_store_func, r26
    mtctr r8
    bctr

// STA  (indirect,X)    STA (oper,X)	81	2	6  
entry ksNesInst_sta_81
    addi r8, r3, 0x1
    andi. r8, r8, 0xff
    lbzx r3, WRAM, r8
    rlwinm r26, r3, 29, 27, 29 // (r3 >> 3) & 0x1C;
    slwi r3, r3, 8
    lwzx r8, state_store_func, r26
    or r3, r3, r4
    mtctr r8
    mr r4, REGISTER_A
    bctr

//STA   (indirect),Y	STA (oper),Y	91	2	6  
entry ksNesInst_sta_91
    lbzx r3, WRAM, r4
    addi r8, r4, 0x1
    andi. r8, r8, 0xff
    lbzx r4, WRAM, r8
    add r3, r3, REGISTER_Y
    rlwinm r26, r4, 29, 27, 29
    slwi r4, r4, 8
    lwzx r8, state_store_func, r26
    add r3, r3, r4
    mtctr r8
    mr r4, REGISTER_A
    bctr

// CLC  implied	CLC	18	1	2
// Clear Carry Flag
entry ksNesInst_clc_18
    li REGISTER_FLAG_CARRY, 0x0
    b ksNesLinecntIrqDefault

// SEC  implied	SEC	38	1	2
// Set Carry Flag
entry ksNesInst_sec_38
    li REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// DEX  implied	DEX	CA	1	2  
entry ksNesInst_dex_ca
    subi REGISTER_FLAG_ZERO, REGISTER_X, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_X, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INX  implied	INX	E8	1	2  
entry ksNesInst_inx_e8
    addi REGISTER_FLAG_ZERO, REGISTER_X, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_X, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// DEY  implied	DEY	88	1	2  
entry ksNesInst_dey_88
    subi REGISTER_FLAG_ZERO, REGISTER_Y, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_Y, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INY  implied	INY	C8	1	2  
entry ksNesInst_iny_c8
    addi REGISTER_FLAG_ZERO, REGISTER_Y, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_Y, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// TXA  implied	TXA	8A	1	2  
// Transfer Index X to Accumulator
entry ksNesInst_txa_8a
    mr REGISTER_FLAG_ZERO, REGISTER_X
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_X, 0x80
    mr REGISTER_A, REGISTER_X
    b ksNesLinecntIrqDefault

// TYA  implied	TYA	98	1	2  
// Transfer Index Y to Accumulator
entry ksNesInst_tya_98
    mr REGISTER_FLAG_ZERO, REGISTER_Y
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_Y, 0x80
    mr REGISTER_A, REGISTER_Y
    b ksNesLinecntIrqDefault

// TAX  implied	TAX	AA	1	2  
// Transfer Accumulator to Index X
entry ksNesInst_tax_aa
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    mr REGISTER_X, REGISTER_A
    b ksNesLinecntIrqDefault

// TAY  implied	TAY	A8	1	2  
// Transfer Accumulator to Index Y
entry ksNesInst_tay_a8
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    mr REGISTER_Y, REGISTER_A
    b ksNesLinecntIrqDefault

// CMP  (indirect,X)	CMP (oper,X)	C1	2	6  
// Compare Memory with Accumulator
entry ksNesInst_cmp_c1
    subf REGISTER_FLAG_ZERO, r4, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// CPX  immediate	CPX #oper	E0	2	2  
// Compare Memory with Index X
entry ksNesInst_cpx_e0
    subf REGISTER_FLAG_ZERO, r4, REGISTER_X
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault
// CPY  immediate	CPY #oper	C0	2	2  
// Compare Memory and Index Y
entry ksNesInst_cpy_c0
    subf REGISTER_FLAG_ZERO, r4, REGISTER_Y
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// ADC (indirect,X)	ADC (oper,X)	61	2	6  
// Add Memory to Accumulator with Carry
entry ksNesInst_adc_61
    extsb r7, REGISTER_A
    add REGISTER_FLAG_ZERO, REGISTER_A, REGISTER_FLAG_CARRY
    add r7, r7, REGISTER_FLAG_CARRY
    add REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, r4
    extsb r8, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    add r7, r7, r8
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    addi r7, r7, 0x80
    extrwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 1, 23 // (REGISTER_FLAG_ZERO >> 8) & 0x1
    srwi REGISTER_FLAG_OVERFLOW, r7, 8
    b ksNesLinecntIrqDefault

// SBC  (indirect,X)	SBC (oper,X)	E1	2	6  
// Subtract Memory from Accumulator with Borrow
entry ksNesInst_sbc_e1
    extsb r7, REGISTER_A
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    subf REGISTER_FLAG_ZERO, r4, REGISTER_A
    subf r7, REGISTER_FLAG_CARRY, r7
    subf REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO
    extsb r8, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    subf r7, r8, r7
    extrwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 1, 23 // (REGISTER_FLAG_ZERO >> 8) & 0x1
    addi r7, r7, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    srwi REGISTER_FLAG_OVERFLOW, r7, 8
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// ora  (indirect,X)	ORA (oper,X)	01	2	6  
// OR Memory with Accumulator
entry ksNesInst_ora_01
    // bitwise or A with some value
    // using Z as temporary storage?
    or REGISTER_FLAG_ZERO, REGISTER_A, r4
    // set the N flag if A is negative
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    // assign the result to A
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// AND  (indirect,X)	AND (oper,X)	21	2	6  
// AND Memory with Accumulator
entry ksNesInst_and_21
    and REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// BIT  zeropage	BIT oper	24	2	3  
// Test Bits in Memory with Accumulator
// https://www.masswerk.at/6502/6502_instruction_set.html#bitcompare
entry ksNesInst_bit_24
    and REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    andi. REGISTER_FLAG_OVERFLOW, r4, 0x40
    b ksNesLinecntIrqDefault

// EOR  (indirect,X)	EOR (oper,X)	41	2	6  
// Exclusive-OR Memory with Accumulator
entry ksNesInst_eor_41
    xor REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INC  zeropage	INC oper	E6	2	5  
// Increment Memory by One
entry ksNesInst_inc_e6
    lwzx r7, state_store_func, r26
    addi REGISTER_FLAG_ZERO, r4, 0x1
    mtctr r7
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// DEC  zeropage	DEC oper	C6	2	5  
// Decrement Memory by One
entry ksNesInst_dec_c6
    lwzx r7, state_store_func, r26
    subi REGISTER_FLAG_ZERO, r4, 0x1
    mtctr r7
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// ASL  accumulator	ASL A	0A	1	2  
// Shift Left One Bit (Memory or Accumulator)
entry ksNesInst_asl_0a
    slwi REGISTER_FLAG_ZERO, REGISTER_A, 1
    extrwi REGISTER_FLAG_CARRY, REGISTER_A, 1, 24 // (REGISTER_A >> 7) & 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// ASL  zeropage	ASL oper	06	2	5  
// Shift Left One Bit (Memory or Accumulator)
entry ksNesInst_asl_06
    lwzx r7, state_store_func, r26
    slwi REGISTER_FLAG_ZERO, r4, 1
    mtctr r7
    extrwi REGISTER_FLAG_CARRY, r4, 1, 24 // (r4 >> 7) & 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// LSR  accumulator	LSR A	4A	1	2  
// Shift One Bit Right (Memory or Accumulator)
entry ksNesInst_lsr_4a
andi. REGISTER_FLAG_CARRY, REGISTER_A, 0x1
andi. REGISTER_FLAG_ZERO, REGISTER_A, 0xfe
li REGISTER_FLAG_NEGATIVE, 0x0
srwi REGISTER_A, REGISTER_A, 1
b ksNesLinecntIrqDefault

// LSR  zeropage	LSR oper	46	2	5  
// Shift One Bit Right (Memory or Accumulator)
entry ksNesInst_lsr_46
    lwzx r7, state_store_func, r26
    li REGISTER_FLAG_NEGATIVE, 0x0
    mtctr r7
    andi. REGISTER_FLAG_CARRY, r4, 0x1
    andi. REGISTER_FLAG_ZERO, r4, 0xfe
    srwi r4, r4, 1
    bctr

// ROL  accumulator	ROL A	2A	1	2  
// Rotate One Bit Left (Memory or Accumulator)
entry ksNesInst_rol_2a
    slwi REGISTER_FLAG_ZERO, REGISTER_A, 1
    rlwinm REGISTER_FLAG_NEGATIVE, REGISTER_A, 1, 24, 24 // (REGISTER_A << 1) & 0x80
    or REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY
    extrwi REGISTER_FLAG_CARRY, REGISTER_A, 1, 24 // (REGISTER_A >> 7) & 0x1
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// ROL  zeropage	ROL oper	26	2	5  
// Rotate One Bit Left (Memory or Accumulator)
entry ksNesInst_rol_26
    lwzx r7, state_store_func, r26
    slwi REGISTER_FLAG_ZERO, r4, 1
    mtctr r7
    rlwinm REGISTER_FLAG_NEGATIVE, r4, 1, 24, 24 // (r4 << 1) & 0x80
    or REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY
    extrwi REGISTER_FLAG_CARRY, r4, 1, 24 // (r4 >> 7) & 0x1
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// ROR  accumulator	ROR A	6A	1	2  
// Rotate One Bit Right (Memory or Accumulator)
entry ksNesInst_ror_6a
    slwi REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, 7
    andi. REGISTER_FLAG_CARRY, REGISTER_A, 0x1
    mr REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO
    
    rlwimi REGISTER_FLAG_ZERO, REGISTER_A, 31, 25, 31 
    // REGISTER_FLAG_ZERO = ((REGISTER_A>>1) & 0x7F) | (REGISTER_FLAG_ZERO & ~0x7F)
    
    mr REGISTER_A, REGISTER_FLAG_ZERO
    b ksNesLinecntIrqDefault

// ROR  zeropage	ROR oper	66	2	5  
// Rotate One Bit Right (Memory or Accumulator)
entry ksNesInst_ror_66
    lwzx r7, state_store_func, r26
    slwi REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, 7
    mtctr r7
    andi. REGISTER_FLAG_CARRY, r4, 0x1
    mr REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO

    rlwimi REGISTER_FLAG_ZERO, r4, 31, 25, 31
    // REGISTER_FLAG_ZERO = ((r4>>1) & 0x7F) | (REGISTER_FLAG_ZERO & ~0x7F)

    mr r4, REGISTER_FLAG_ZERO
    bctr

// BPL  relative	BPL oper	10	2	2**
// Branch on Result Plus
entry ksNesInst_bpl_10
    extsb r8, r4
    andi. r7, REGISTER_FLAG_NEGATIVE, 0x80
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BMI  relative	BMI oper	30	2	2**
// Branch on Result Minus
entry ksNesInst_bmi_30
    extsb r8, r4
    andi. r7, REGISTER_FLAG_NEGATIVE, 0x80
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BVC  relative	BVC oper	50	2	2**
// Branch on Overflow Clear
entry ksNesInst_bvc_50
    extsb r8, r4
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BVS  relative	BVS oper	70	2	2**
// Branch on Overflow Set
entry ksNesInst_bvs_70
    extsb r8, r4
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault
    
// BCC  relative	BCC oper	90	2	2**
// Branch on Carry Clear
entry ksNesInst_bcc_90
    extsb r8, r4
    andi. r7, REGISTER_FLAG_CARRY, 0x1
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BCS  relative	BCS oper	B0	2	2**
// Branch on Carry Set
entry ksNesInst_bcs_b0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_CARRY, 0x1
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BNE  relative	BNE oper	D0	2	2**
// Branch on Result not Zero
entry ksNesInst_bne_d0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_ZERO, 0xff
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// BEQ  relative	BEQ oper	D0	2	2**
// Branch on Result Zero
entry ksNesInst_beq_f0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_ZERO, 0xff
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x100
    b ksNesLinecntIrqDefault

// JSR absolute	JSR oper	20	3	6  
// Jump to New Location Saving Return Address
entry ksNesInst_jsr_20
    subi r4, REGISTER_PC, 0x1
    mr REGISTER_PC, r3
    // fallthrough

entry ksNesPush16_a1
    addi r0, WRAM, 0x100
    srwi r8, r4, 8
    stbx r8, REGISTER_STACK, r0
    subi r7, REGISTER_STACK, 0x1
    andi. r7, r7, 0xff
    subi REGISTER_STACK, REGISTER_STACK, 0x2
    stbx r4, r7, r0
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    blr

// PHA  implied	PHA	48	1	3  
// Push Accumulator on Stack
entry ksNesInst_pha_48
    addi r7, REGISTER_STACK, 0x100
    subi REGISTER_STACK, REGISTER_STACK, 0x1
    stbx REGISTER_A, WRAM, r7
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    b ksNesLinecntIrqDefault

// PLA  implied	PLA	68	1	4  
// Pull Accumulator from Stack
entry ksNesInst_pla_68
    addi REGISTER_STACK, REGISTER_STACK, 0x1
    addi r7, WRAM, 0x100
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    lbzx REGISTER_A, r7, REGISTER_STACK
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    b ksNesLinecntIrqDefault
    
// RTS  implied	RTS	60	1	6  
// Return from Subroutine
entry ksNesInst_rts_60
    li r4, 0x1
    // fallthrough

entry ksNesPopPC
    addi r8, REGISTER_STACK, 0x1
    addi r7, REGISTER_STACK, 0x2
    ori r8, r8, 0x100
    ori r7, r7, 0x100
    lbzx r3, WRAM, r8
    andi. REGISTER_STACK, r7, 0xff
    lbzx r9, WRAM, r7
    add r3, r3, r4
    slwi r9, r9, 8
    add r3, r3, r9
    andi. REGISTER_PC, r3, 0xffff
    blr

// JMP  absolute	JMP oper	4C	3	3  
// Jump to New Location  
entry ksNesInst_jmp_4c
    mr REGISTER_PC, r3
    b ksNesLinecntIrqDefault

// JMP  indirect	JMP (oper)	6C	3	5  
// Jump to New Location
entry ksNesInst_jmp_6c
    lwzx r9, state_cpu_ranges, r26
    subi r7, r3, 0x2000
    addi r4, r3, 0x1
    rlwinm r7, r7, 16, 16, 20
    andc r8, r3, r7
    lbzx REGISTER_PC, r9, r8
    rlwimi r3, r4, 0, 24, 31
    andc r3, r3, r7
    lbzx r4, r9, r3
    rlwimi REGISTER_PC, r4, 8, 16, 23
    b ksNesLinecntIrqDefault

// BRK  implied	BRK	00	1	7  
// Force Break
entry ksNesInst_brk_00
    li r9, 0x14
    lis r7, 0x0
    ori r7, r7, 0xfffe
    b L_8003BC60

entry ksNesActivateIntrIRQ
    lis r7, 0x0
    ori r7, r7, 0xfffe
    // fallthrough

entry ksNesActivateIntr
    li r9, 0x24
L_8003BC60:
    lwz r8, state_temp->cpu_e000_ffff
    mr r4, REGISTER_PC
    lbzux REGISTER_PC, r8, r7
    lbz r7, 0x1(r8)
    rlwimi REGISTER_PC, r7, 8, 16, 23
    bl ksNesPush16_a1
    addi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x700
L_8003BC7C:
    lbz r7, state_temp->cpu_state.P
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    rlwinm r8, r9, 31, 27, 27
    or r0, REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_CARRY
    andc r7, r7, r8
    beq L_8003BC98
    ori r0, r0, 0x40
L_8003BC98:
    andi. r9, r9, 0x14
    andi. r8, REGISTER_FLAG_ZERO, 0xff
    or r0, r0, r7
    subi r8, r8, 0x1
    or r9, r9, r7
    addi r7, REGISTER_STACK, 0x100
    stb r9, state_temp->cpu_state.P
    rlwimi r0, r8, 2, 30, 30
    subi REGISTER_STACK, REGISTER_STACK, 0x1
    stbx r0, WRAM, r7
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    b ksNesLinecntIrqDefault


// PHP  implied	PHP	08	1	3  
// Push Processor Status on Stack
entry ksNesInst_php_08
    li r9, 0x0
    b L_8003BC7C

// PLP  implied	PLP	28	1	4  
// Pull Processor Status from Stack
entry ksNesInst_plp_28
    addi REGISTER_STACK, REGISTER_STACK, 0x1
    addi r7, WRAM, 0x100
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    lbzx r8, r7, REGISTER_STACK
    lbz r9, state_temp->cpu_state.P
    andi. r7, r8, 0x3c
    andi. REGISTER_FLAG_CARRY, r8, 0x1
    stb r7, state_temp->cpu_state.P
    andi. REGISTER_FLAG_ZERO, r8, 0x2
    andi. REGISTER_FLAG_OVERFLOW, r8, 0x40
    xori REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, 0x2
    andi. REGISTER_FLAG_NEGATIVE, r8, 0x80
    andi. r7, r7, 0x4
    lbz r8, state_temp->cpu_state.irq_pending_flag
    bnelr
    cmpwi r8, 0x0
    beqlr
    li r8, 0x0
    stb r8, state_temp->cpu_state.irq_pending_flag
    bctr

// RTI  implied	RTI	40	1	6  
// Return from Interrupt
entry ksNesInst_rti_40
    bl ksNesInst_plp_28
    li r4, 0x0
    bl ksNesPopPC
    b ksNesLinecntIrqDefault

entry ksNesInst_rti_40_2
    li r4, 0x0
    bl ksNesPopPC
    b ksNesActivateIntrIRQ

// CLI  implied	CLI	58	1	2  
// Clear Interrupt Disable Bit
entry ksNesInst_cli_58
    lbz r7, state_temp->cpu_state.P
    andi. r7, r7, 0xfb
    stb r7, state_temp->cpu_state.P
    lbz r8, state_temp->cpu_state.irq_pending_flag
    cmpwi r8, 0x0
    beq ksNesLinecntIrqDefault
    li r8, 0x0
    stb r8, state_temp->cpu_state.irq_pending_flag
    b ksNesActivateIntrIRQ

// SEI  implied	SEI	78	1	2  
// Set Interrupt Disable Status
entry ksNesInst_sei_78
    lbz r7, state_temp->cpu_state.P
    ori r7, r7, 0x4
    stb r7, state_temp->cpu_state.P
    b ksNesLinecntIrqDefault

// TXS  implied	TXS	9A	1	2  
// Transfer Index X to Stack Register
entry ksNesInst_txs_9a
    mr REGISTER_STACK, REGISTER_X
    b ksNesLinecntIrqDefault

// TSX  implied	TSX	BA	1	2  
// Transfer Stack Pointer to Index X
entry ksNesInst_tsx_ba
    mr REGISTER_FLAG_ZERO, REGISTER_STACK
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_STACK, 0x80
    mr REGISTER_X, REGISTER_STACK
    b ksNesLinecntIrqDefault

// CLD  Clear Decimal Mode
// Clear Decimal Mode
entry ksNesInst_cld_d8
    lbz r7, state_temp->cpu_state.P
    andi. r7, r7, ~0x8 & 0xff
    stb r7, state_temp->cpu_state.P
    b ksNesLinecntIrqDefault

// SED  implied	SED	F8	1	2  
// Set Decimal Flag
entry ksNesInst_sed_f8
    lbz r7, state_temp->cpu_state.P
    ori r7, r7, 0x8
    stb r7, state_temp->cpu_state.P
    b ksNesLinecntIrqDefault

// CLV implied	CLV	B8	1	2  
// Clear Overflow Flag
entry ksNesInst_clv_b8
    li REGISTER_FLAG_OVERFLOW, 0x0
    b ksNesLinecntIrqDefault

entry ksNesLoadInvalid
    bctr
entry ksNesLoadIgnore
    srwi r4, r3, 8
    bctr
// < r3 = address to load from
entry ksNesLoadWRAM
    // we're loading from wram so we'll limit the address to valid wram addresses
    andi.      r7,r3,0x7ff

    // r4 = state_temp->wram[r7]
    // read a byte from work ram
    // the state object starts with a work ram array.
    lbzx       r4,WRAM,r7
    bctr

entry ksNesLoadBBRAM
    // r7 = r27[r26]
    lwzx       r7,state_cpu_ranges,r26
    // r4 = r7[r3]
    lbzx       r4,r7,r3
    bctr

entry ksNesLoadPPU
    andi.      r7,r3,0x7
    addi       r8, state_temp, state_temp->ppu_internal_state
    cmpwi      r7,0x7
    lbzx       r4,r8,r7
    bne        LAB_8003be58
    lhz        r7,state_temp->ppu_addr_latch
    cmpwi      r7,0x3000
    bge        LAB_8003be14
    cmpwi      r7,0x2000
    blt        LAB_8003be30
    rlwinm     r9,r7,0x18,0x1c,0x1d // r9 = (r7 >> 8) & 0xC;
    addi       r0, state_temp, state_temp->ppu_nametable_pointers
    lwzx       r9,r9,r0
    andi.      r8,r7,0x3ff
    lbzx       r9,r9,r8
    stb        r9, state_temp->ppu_internal_state[7]
LAB_8003be14:
    lbz        r8, state_temp->ppu_register_cache[0]
    li         r0,0x3
    andi.      r8,r8,0x4
    rlwnm      r8,r0,r8,0x1f,0x1a // r8 = (r0 << r8) & 0x8000003F
    add        r7,r7,r8
    sth        r7,state_temp->ppu_addr_latch
    bctr
LAB_8003be30:
    rlwinm     r8, r7, 0x16, 0x1d, 0x1f
    addi       r9, state_temp, state_temp->ppu_chr_banks
    lbzx       r9, r9, r8
    andi.      r0, r7, 0x3ff
    lwz        r8, state_temp->chrramp
    rlwinm     r9, r9, 0xa, 0x0, 0x15 // r9=r9*1024
    add        r8, r8, r0
    lbzx       r9, r8, r9
    stb        r9, state_temp->ppu_internal_state[7]
    b          LAB_8003be14
LAB_8003be58:
    li         r9,0x20
    stbx       r9,r8,r7
    bctr

entry ksNesLoadIO
    addi r8, state_load_func, (8 * sizeof(void*)) // state->load_io_func immediately follows state_load_func (state->load_func), so move to the beginning of it by skipping over all entries in state_load_func.
    clrlslwi r7, r3, 26, 2
    lwzx r0, r8, r7
    cmpwi r3, 0x4018
    mtlr r0
    bltlr
    cmpwi r3, 0x4034
    bge L_8003BF0C
    subic. r7, r3, 0x4030
    addi r8, state_temp, state_temp->qd_drive.raw
    blt ksNesLoadInvalid
    lbzx r4, r8, r7
    bne L_8003BEA4
    li r7, 0x0
    stb r7, state_temp->qd_drive.raw
    bctr
L_8003BEA4:
    cmpwi r3, 0x4031
    beq L_8003BEFC
    cmpwi r3, 0x4032
    bnectr
    lbz r7, state_temp->fds_disk_drive_status
    and r4, r4, r7
    cmplwi REGISTER_PC, 0xe000
    blt L_8003BEDC
    cmplwi REGISTER_PC, 0xeee2
    beqctr
    cmplwi REGISTER_PC, 0xef36
    beqctr
    li r4, 0x40
    bctr
L_8003BEDC:
    lbz r7, state_temp->fds_ready_delay_counter
    ori r4, r4, KS_NES_FDS_CTRL_FLG_CRC_ENABLE|KS_NES_FDS_CTRL_FLG_TRANSFER_MODE|KS_NES_FDS_CTRL_FLG_MOTOR|KS_NES_FDS_CTRL_FLG_TRANSFER_RESET
    cmpwi r7, 0xc3
    bgectr
    lbz r7, state_temp->fds_control_register
    andi. r4, r4, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE|KS_NES_FDS_CTRL_FLG_CRC_ENABLE|KS_NES_FDS_CTRL_FLG_5|KS_NES_FDS_CTRL_FLG_CRC_TRANSFER|KS_NES_FDS_CTRL_FLG_NAMETABLE_MODE|KS_NES_FDS_CTRL_FLG_MOTOR
    rlwimi r4, r7, 0, 30, 30 // set control register while preserving disk motor state
    bctr
L_8003BEFC:
    lhz r9, state_temp->qd_disk_head_position.split.lower
    addi r9, r9, 0x1
    sth r9, state_temp->qd_disk_head_position.split.lower
    bctr
L_8003BF0C:
    mfctr r0
    stw r0, 0xd0(r1)
    bl Sound_Read
    lwz r0, 0xd0(r1)
    mr r4, r3
    mtctr r0
    bctr

entry ksNesLoad4015
	lbz r4, state_temp->cpu_state.irq_status_flags
	andi. r7, r4, 0x3f
	stb r7, state_temp->cpu_state.irq_status_flags
	bctr
    
entry ksNesLoad4017
    lwz r0, state_temp->io_shift_registers[6]
    li r4, 0x40
    lwz r10, state_temp->io_shift_registers[5]
    lwz r9, state_temp->io_shift_registers[4]
    rlwimi r4, r0, 5, 27, 27
    lwz r8, state_temp->io_shift_registers[3]
    rlwimi r4, r10, 4, 28, 28
    lwz r7, state_temp->io_shift_registers[2]
    rlwimi r4, r9, 3, 29, 29
    lbz r5, state_temp->cpu_state.controller_strobe
    rlwimi r4, r8, 2, 30, 30
    rlwimi r4, r7, 1, 31, 31
    andi. r5, r5, 0x1
    bnectr
    slwi r0, r0, 1
    slwi r10, r10, 1
    stw r0, state_temp->io_shift_registers[6]
    slwi r9, r9, 1
    stw r10, state_temp->io_shift_registers[5]
    slwi r8, r8, 1
    stw r9, state_temp->io_shift_registers[4]
    slwi r7, r7, 1
    stw r8, state_temp->io_shift_registers[3]
    stw r7, state_temp->io_shift_registers[2]
    bctr

entry ksNesLoad4016
    lbz r7, state_temp->cpu_state.controller_strobe
    li r4, 0x40
    lwz r8, state_temp->io_shift_registers[1]
    andi. r7, r7, 0x1
    lwz r9, state_temp->io_shift_registers[0]
    rlwimi r4, r8, 2, 30, 30
    rlwimi r4, r9, 1, 31, 31
    bnectr
    slwi r8, r8, 1
    slwi r9, r9, 1
    stw r8, state_temp->io_shift_registers[1]
    stw r9, state_temp->io_shift_registers[0]
    bctr

entry ksNesStoreWRAM
    andi. r7, r3, 0x7ff
    stbx r4, WRAM, r7
    b ksNesLinecntIrqDefault

entry ksNesStoreBBRAM
    lwzx       r7,state_cpu_ranges,r26
    stbx       r4,r7,r3
    b          ksNesLinecntIrqDefault

entry ksNesStoreInvalid
    b ksNesLinecntIrqDefault

entry ksNesStorePPU
    clrlslwi r7, r3, 29, 2
    subi r8, r28, 0xc0
    lwzx r7, r8, r7
    mtctr r7
    bctr

// PPU Ctrl Register
entry ksNesStore2000
    lbz r9, state_temp->ppu_vram_addr_v_hi
    andi. r8, r4, 0x3
    lbz r7, state_temp->ppu_register_cache[0]
    stb r4, state_temp->ppu_register_cache[0]
    rlwimi r9, r4, 0, 31, 31
    stb r8, state_temp->ppu_vram_addr_t_hi
    stb r9, state_temp->ppu_vram_addr_v_hi
    b ksNesLinecntIrqDefault

entry ksNesStorePPURam
    andi. r7, r3, 0x7
    addi r8, state_temp, state_temp->ppu_register_cache
    stbx r4, r8, r7
    b ksNesLinecntIrqDefault

// OAM Data Register
entry ksNesStore2004
    b ksNesLinecntIrqDefault

// PPU Scroll Register
entry ksNesStore2005
    lbz r7, state_temp->ppu_internal_state[2]
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    stb r7, state_temp->ppu_internal_state[2]
    bne L_8003C050
    stb r4, state_temp->ppu_fine_x_scroll
    b ksNesLinecntIrqDefault
L_8003C050:
    lbz r8, state_temp->ppu_scanline_threshold
    stb r4, state_temp->ppu_vram_addr_t_lo
    cmpwi r8, 0x0
    beq ksNesLinecntIrqDefault
    lha r9, state_temp->ppu_scanline_counter
    cmpw r9, r8
    bge ksNesLinecntIrqDefault
    stb r4, state_temp->ppu_vram_addr_v_lo
    cmpwi r9, 0x8
    blt ksNesLinecntIrqDefault
    add r4, r4, r9
L_8003C07C:
    cmpwi r4, 0xf0
    blt L_8003C08C
    subi r4, r4, 0xf0
    b L_8003C07C
L_8003C08C:
    stb r4, state_temp->ppu_vram_addr_v_lo
    b ksNesLinecntIrqDefault

// PPU Addr Register
entry ksNesStore2006
    lbz r7, state_temp->ppu_internal_state[2]
    addi r8, state_temp, state_temp->ppu_addr_latch
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    stbx r4, r8, r9 // stores to index 0 or 1, essentially writing to the u16 here
    stb r7, state_temp->ppu_internal_state[2]
    beq ksNesLinecntIrqDefault
    lhz r8, state_temp->ppu_addr_latch
    andi. r8, r8, 0x3fff
    sth r8, state_temp->ppu_addr_latch
    rlwinm r7, r8, 30, 22, 28
    rlwimi r7, r8, 20, 30, 31
    lbz r9, state_temp->mapper
    cmpwi r9, KS_NES_MAPPER_MMC5
    bne L_8003C0D4
    andi. r7, r7, 0x7ffe
L_8003C0D4:
    sth r7, state_temp->ppu_vram_addr_t_hi
    sth r7, state_temp->ppu_vram_addr_v_hi
    b ksNesLinecntIrqDefault

// PPU Data Register
entry ksNesStore2007ChrRom
    lhz r7, state_temp->ppu_addr_latch
    cmpwi r7, 0x3000
    bge L_8003C18C
    cmpwi r7, 0x2000
    blt L_8003C130
    rlwinm r9, r7, 24, 28, 29 // (r7 >> 8) & 0xC // ((r7 >> 10) & 0x2) << 2
    addi r0, state_temp, state_temp->ppu_nametable_pointers
    lwzx r9, r9, r0
    andi. r8, r7, 0x3ff
    addi r10, state_temp, state_temp->cartridge_nametable_ram
    cmpw r10, r9
    beq L_8003C114
    stbx r4, r9, r8
L_8003C114:
    lbz r8, state_temp->ppu_register_cache[0]
    li r0, 0x3
    andi. r8, r8, 0x4
    rlwnm r8, r0, r8, 31, 26
    add r7, r7, r8
    sth r7, state_temp->ppu_addr_latch
    b ksNesLinecntIrqDefault
L_8003C130:
    lbz r10, state_temp->chr_ram_write_enable
    extrwi r8, r7, 3, 19
    addi r9, state_temp, state_temp->ppu_chr_banks
    andi. r0, r7, 0x3ff
    cmpwi r10, 0x0
    lbzx r9, r9, r8
    beq ksNesLinecntIrqDefault
    lwz r8, state_temp->chrramp
    slwi r9, r9, 10
    add r9, r9, r0
    stbx r4, r8, r9
    lwz r3, 0x8(r1)
    srwi r5, r9, 4
    lbz r7, state_temp->mapper
    clrrwi r9, r9, 4
    add r4, r8, r9
    cmpwi r7, KS_NES_MAPPER_MMC5
    beq L_8003C180
    bl ksNesConvertChrToI8
    b L_8003C184
L_8003C180:
    bl ksNesConvertChrToI8MMC5
L_8003C184:
    lhz r7, state_temp->ppu_addr_latch
    b L_8003C114
L_8003C18C:
    cmpwi r7, 0x3f00
    blt L_8003C114
    cmpwi r7, 0x3f20
    bge L_8003C114
    lbz r10, state_temp->_17C6
    andi. r8, r7, 0x1f
    andi. r0, r4, 0x3f
    andi. r9, r7, 0xf
    addi r10, r10, state_temp->ppu_palette_ram
    add r10, r10, state_temp
    beq L_8003C1CC
    andi. r9, r7, 0x3
    beq L_8003C114
    stbx r0, r10, r8
    sth r7, state_temp->_17C4
    b L_8003C114
L_8003C1CC:
    stb r0, 0x0(r10)
    stb r0, 0x4(r10)
    stb r0, 0x8(r10)
    stb r0, 0xc(r10)
    stb r0, 0x10(r10)
    stb r0, 0x14(r10)
    stb r0, 0x18(r10)
    stb r0, 0x1c(r10)
    sth r7, state_temp->_17C4
    b L_8003C114

entry ksNesStoreIO
    subi r8, state_store_func, (40 * sizeof(void*)) // state_store_func already exists as a register, so backtrack to the beginning of state->store_io_func which immediately preceeds it
    clrlslwi r7, r3, 26, 2
    lwzx r0, r8, r7
    cmpwi r3, 0x4027
    mtctr r0
    bge ksNesStoreQDSound
    bctr

entry ksNesStoreQDSound
    b ksNesStore4000

entry ksNesStore4017
    andi. r8, r4, 0xc0
    bne L_8003C234
    lhz r7, state_temp->ppu_scanline_counter
    li r9, 0x1
    stb r8, state_temp->cpu_state.apu_frame_counter_mode
    sth r7, state_temp->scanline_irq_target_val
    stb r9, state_temp->cpu_state.mapper_irq_enable
    b ksNesStore4000
L_8003C234:
    lbz r9, state_temp->cpu_state.apu_frame_counter_mode
    andi. r9, r9, 0xc0
    stb r8, state_temp->cpu_state.apu_frame_counter_mode
    bne ksNesStore4000
    stb r9, state_temp->cpu_state.mapper_irq_enable
    b ksNesStore4000

entry ksNesStore4011
    lbz r8, state_temp->cpu_state.dac_value
    cmpw r8, r4
    beq ksNesLinecntIrqDefault
    stb r4, state_temp->cpu_state.dac_value
    b ksNesStore4000

entry ksNesStore4015
	lbz r9, state_temp->cpu_state.irq_status_flags
	andi. r8, r4, 0x10
	or r9, r9, r8
	stb r9, state_temp->cpu_state.irq_status_flags
	b ksNesStore4003

entry ksNesStore4003
    lbz r9, state_temp->cpu_state.irq_status_flags
    srwi r7, r3, 30
    li r8, 0x1
    slw r8, r8, r7
    or r9, r9, r8
    stb r9, state_temp->cpu_state.irq_status_flags
    // fallthrough

entry ksNesStore4000
    lwz r8, state_temp->frame_flags
    lwz r5, STACK_CPU_CYCLES
    lbz r7, STACK_FRAMES
    andi. r8, r8, 0x1000
    bne ksNesLinecntIrqDefault
    divwu r5, r5, r7
    bl Sound_Write
    b ksNesLinecntIrqDefault

entry ksNesStore4014
    rlwinm r7, r4, 29, 27, 29
    slwi r8, r4, 8
    lwzx r7, state_cpu_ranges, r7
    li r0, 0x40
    addi r9, state_temp, state_temp->primary_oam - sizeof(ksNesOAMEntry)
    mtctr r0
    add r7, r7, r8
    subi r7, r7, 0x4
L_8003C2CC:
    lwzu r0, 0x4(r7)
    stwu r0, 0x4(r9)
    bdnz L_8003C2CC
    addis REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x2
    b ksNesLinecntIrqDefault

entry ksNesStore4016
    andi. r7, r4, 0x1
    stb r4, state_temp->cpu_state.controller_strobe
    beq ksNesLinecntIrqDefault
    lwz r9, STACK_WORK_ARG
    lwz r7, (ksNesCommonWorkObj.pads[0])(r9)
    lwz r8, (ksNesCommonWorkObj.pads[1])(r9)
    stw r7, state_temp->io_shift_registers[0]
    stw r8, state_temp->io_shift_registers[1]
    lwz r7, (ksNesCommonWorkObj.pads[2])(r9)
    lwz r8, (ksNesCommonWorkObj.pads[3])(r9)
    stw r7, state_temp->io_shift_registers[2]
    stw r8, state_temp->io_shift_registers[3]
    lwz r7, (ksNesCommonWorkObj.pads[4])(r9)
    lwz r8, (ksNesCommonWorkObj.pads[5])(r9)
    lwz r0, (ksNesCommonWorkObj.pads[6])(r9)
    stw r7, state_temp->io_shift_registers[4]
    stw r8, state_temp->io_shift_registers[5]
    stw r0, state_temp->io_shift_registers[6]
    b ksNesLinecntIrqDefault

entry ksNesInst_wdm_42
    lwz r7, state_temp->prgromp
    cmpwi r7, 0x0
    bne ksNesLinecntIrqDefault
    cmplwi REGISTER_PC, 0xe408
    beq L_8003C4D8
    cmplwi REGISTER_PC, 0xeebf
    beq L_8003C464
    cmplwi REGISTER_PC, 0xeef6
    beq L_8003C440
    cmplwi REGISTER_PC, 0xe23b
    beq L_8003C36C
    cmplwi REGISTER_PC, 0xe7a6
    bne ksNesLinecntIrqDefault
    andi. REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x7
    subi REGISTER_PC, REGISTER_PC, 0x2
    b ksNesLinecntIrqDefault
L_8003C36C:
    stb REGISTER_A, state_temp->wram[0xE]
    cmpwi REGISTER_A, 0xff
    beq ksNesLinecntIrqDefault
    add r7, state_temp, REGISTER_STACK
    lbzu r9, (ksNesStateObj.wram + 0x101)(r7)
    lbz r8, 0x1(r7)
    rlwimi r9, r8, 8, 16, 23
    addi r5, r9, 0x1
    addi r6, r9, 0x5
    sth r6, state_temp->wdm_return_addr
    rlwinm r26, r5, 21, 27, 29
    lwzx r7, state_cpu_ranges, r26
    lbzx r7, r7, r5
    addi r5, r5, 0x1
    rlwinm r26, r5, 21, 27, 29
    lwzx r8, state_cpu_ranges, r26
    lbzx r8, r8, r5
    addi r5, r5, 0x1
    rlwimi r7, r8, 8, 16, 23
    addi r3, state_temp, state_temp->_176E[0-1]
    addi r4, state_temp, state_temp->_176E[10-1]
L_8003C3C0:
    rlwinm r26, r7, 21, 27, 29
    lwzx r8, state_cpu_ranges, r26
    lbzx r8, r8, r7
    addi r7, r7, 0x1
    stbu r8, 0x1(r3)
    cmpw r3, r4
    bne L_8003C3C0
    rlwinm r26, r5, 21, 27, 29
    lwzx r7, state_cpu_ranges, r26
    lbzx r7, r7, r5
    addi r5, r5, 0x1
    rlwinm r26, r5, 21, 27, 29
    lwzx r8, state_cpu_ranges, r26
    lbzx r8, r8, r5
    rlwimi r7, r8, 8, 16, 23
    addi r3, r4, 0x11
L_8003C400:
    rlwinm r26, r7, 21, 27, 29
    lwzx r8, state_cpu_ranges, r26
    lbzx r8, r8, r7
    addi r7, r7, 0x1
    stbu r8, 0x1(r4)
    cmpw r4, r3
    bne L_8003C400
    lwz r3, STACK_WORK_ARG
    lwz r4, STACK_STATE_ARG
    bl ksNesQDFastSave
    andi. REGISTER_FLAG_ZERO, r3, 0xff
    andi. REGISTER_A, r3, 0xff
    bne ksNesLinecntIrqDefault
    bl ksNesInst_rts_60
    lhz REGISTER_PC, state_temp->wdm_return_addr
    b ksNesLinecntIrqDefault
L_8003C440:
    lwz r9, STACK_WORK_ARG
    lwz r8, (ksNesCommonWorkObj.pads[0])(r9)
    srwi r7, r8, 28
    cmpwi r7, 0x6
    beq L_8003C45C
    li r8, 0x46
    stb r8, state_temp->fds_disk_drive_status
L_8003C45C:
    lbz REGISTER_A, state_temp->wram[0x90]
    b ksNesLinecntIrqDefault
L_8003C464:
    andi. r7, REGISTER_A, 0xf0
    cmpwi r7, 0x60
    beq ksNesLinecntIrqDefault
    subi r7, r26, 0x2
    li r8, 0xa9
    stbx r8, r7, REGISTER_PC
    lwz r3, 0x8(r1)
    lwz r4, 0xc(r1)
    bl ksNesQDFastLoad
    andi. REGISTER_FLAG_ZERO, r3, 0xff
    bne ksNesLinecntIrqDefault
    subi r7, state_temp, 0x1
    li r8, 0x46
    stb r8, state_temp->qd_drive.registers.drive_status
    stb r8, state_temp->fds_disk_drive_status
    li r8, 0x0
    addi r0, r7, 0xfa
L_8003C4A8:
    stbu r8, 0x1(r7)
    cmpw r7, r0
    bne L_8003C4A8
    addi r0, r7, 0x104
    lis r9, ksNesInitQDDataTbl@h
    ori r9, r9, ksNesInitQDDataTbl@l
L_8003C4C0:
    lbzu r8, 0x1(r9)
    stbu r8, 0x1(r7)
    cmpw r7, r0
    bne L_8003C4C0
    subi REGISTER_PC, REGISTER_PC, 0x24
    b ksNesLinecntIrqDefault
L_8003C4D8:
    lbz r7, 0x0(state_temp)
    stb REGISTER_A, 0x1(state_temp)
    rlwinm r26, REGISTER_A, 29, 27, 29
    rlwimi r7, REGISTER_A, 8, 16, 23
    lwzx r8, state_cpu_ranges, r26
    add r7, r7, r8
    addi r7, r7, 0x1
    lswi r8, r7, 8
    cmpwi r8, -0x1
    beq ksNesLinecntIrqDefault
    lwz r5, state_temp->nesromp
    lbz r7, state_temp->fds_disk_count
    addi r10, r5, 0x10
L_8003C50C:
    lswi r3, r10, 8
    cmpw r3, r8
    bne L_8003C520
    cmpw r4, r9
    beq L_8003C530
L_8003C520:
    addis r10, r10, 0x1
    subic. r7, r7, 0x1
    bgt L_8003C50C
    b ksNesLinecntIrqDefault
L_8003C530:
    subi r10, r10, 0x10
    subf r10, r5, r10
    stw r10, state_temp->qd_disk_head_position.full
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrqQD
    lbz r0, state_temp->fds_control_register
    andi. r8, r0, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE
    beq L_8003C588
    // check for motor start flag with all other flags enabled
    andi. r9, r0, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE|KS_NES_FDS_CTRL_FLG_CRC_ENABLE|KS_NES_FDS_CTRL_FLG_5|KS_NES_FDS_CTRL_FLG_MOTOR|KS_NES_FDS_CTRL_FLG_TRANSFER_RESET
    cmpwi r9, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE|KS_NES_FDS_CTRL_FLG_CRC_ENABLE|KS_NES_FDS_CTRL_FLG_5|KS_NES_FDS_CTRL_FLG_TRANSFER_RESET
    bne ksNesMainLoop2
    addi r10, r10, 0x1
    cmpwi r10, 0xee
    ble L_8003C568
    li r10, -0x14
L_8003C568:
    sth r10, state_temp->scanline_irq_target_val
    lwz r8, state_temp->nesromp
    lwz r9, state_temp->qd_disk_head_position.full
    andi. r10, r0, 0x4
    beq SUB_8003b3a0
    lbzx r10, r8, r9
    stb r10, state_temp->qd_drive.registers.data
    b SUB_8003b3a0
L_8003C588:
    lbz r8, state_temp->fds_timer_control_register
    // check for IRQ enabled
    andi. r0, r8, ~(KS_NES_FDS_TIMRE_CTRL_FLG_IRQ_ENABLE) & 0xFF
    li r9, 0x7fff
    // check for IRQ repeat flag
    andi. r8, r8, KS_NES_FDS_TIMER_CTRL_FLG_IRQ_REPEAT
    beq L_8003C5A8
    mr r0, r8
    lhz r9, state_temp->mapper_irq_latch
    add r9, r9, r10
L_8003C5A8:
    sth r9, state_temp->scanline_irq_target_val
    stb r0, state_temp->fds_timer_control_register
    andi. r0, r0, KS_NES_FDS_TIMRE_CTRL_FLG_IRQ_ENABLE
    stb r0, state_temp->cpu_state.mapper_irq_enable
    li r9, 0x1
    stb r9, state_temp->qd_drive.registers.disk_status
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStoreQD_4020
    subi r7, state_temp, 0x4020 - state_temp->_17CB // offset into 17CB, timer control 0x2855
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4022
    stb r4, state_temp->fds_timer_control_register
    andi. r8, r4, KS_NES_FDS_TIMRE_CTRL_FLG_IRQ_ENABLE
    stb r8, state_temp->cpu_state.mapper_irq_enable
    lbz r8, state_temp->_17CC
    lbz r7, state_temp->_17CB
    li r0, KS_NES_CPU_CYCLES_PER_SCANLINE
    lha r9, state_temp->ppu_scanline_counter
    rlwimi r7, r8, 8, 16, 23
    divwu r8, r7, r0
    sth r8, state_temp->mapper_irq_latch
    add r9, r9, r8
    sth r9, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4023
    stb r4, state_temp->fds_master_io_enable_register
    b ksNesStore4000

entry ksNesStoreQD_4024
    lbz r7, state_temp->fds_control_register
    lwz r8, state_temp->nesromp
    lwz r9, state_temp->qd_disk_head_position.full
    // Check that fds control state is: interrupt enabled, transfer mode = write, motor = start, and transfer reset flag is enabled
    andi. r7, r7, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE|KS_NES_FDS_CTRL_FLG_TRANSFER_MODE|KS_NES_FDS_CTRL_FLG_MOTOR|KS_NES_FDS_CTRL_FLG_TRANSFER_RESET
    cmpwi r7, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE|KS_NES_FDS_CTRL_FLG_TRANSFER_RESET
    bne ksNesLinecntIrqDefault
    add r8, r8, r9
    stb r4, -0x2(r8)
    li r7, 0x1
    stb r7, state_temp->qd_irq_acknowledged_flag
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4025
    lbz r7, state_temp->fds_control_register
    xor r8, r7, r4
    andi. r8, r8, KS_NES_FDS_CTRL_FLG_MOTOR
    stb r4, state_temp->fds_control_register
    beq L_8003C65C
    bl ksNesQDSoundSync
    lbz r4, state_temp->fds_control_register
L_8003C65C:
    andi. r7, r4, KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE
    beq L_8003C684
    stb r7, state_temp->cpu_state.mapper_irq_enable
    lha r8, state_temp->ppu_scanline_counter
    addi r8, r8, 0x1
    cmpwi r8, 0xee
    ble L_8003C67C
    li r8, -0x14
L_8003C67C:
    sth r8, state_temp->scanline_irq_target_val
    b L_8003C69C
L_8003C684:
    lbz r7, state_temp->fds_timer_control_register
    andi. r7, r7, KS_NES_FDS_TIMRE_CTRL_FLG_IRQ_ENABLE
    stb r7, state_temp->cpu_state.mapper_irq_enable
    bne L_8003C69C
    li r7, 0x7fff
    sth r7, state_temp->scanline_irq_target_val
L_8003C69C:
    andi. r7, r4, 0x3
    cmpwi r7, 0x2
    bne L_8003C6BC
    lbz r8, state_temp->qd_drive.registers.drive_status
    li r7, 0x0
    andi. r8, r8, 0xfd
    stb r8, state_temp->qd_drive.registers.drive_status
    sth r7, state_temp->qd_disk_head_position.split.lower
L_8003C6BC:
    rlwinm r7, r4, 1, 27, 27
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u32*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u32*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003C6D0:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003C6D0
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4026
    stb r4, state_temp->qd_drive.registers.expansion_connector
    b ksNesLinecntIrqDefault

entry ksNesStore01_8000
    lbz r9, state_temp->mmc1_regs[6] // shift register
    andi. r7, r4, 0x80
    bne L_8003C718
    lbz r8, state_temp->mmc1_regs[5] // load counter
    srwi r7, r9, 1
    subic. r8, r8, 0x1
    rlwimi r7, r4, 4, 27, 27
    beq L_8003C724
    stb r8, state_temp->mmc1_regs[5] // load counter
    stb r7, state_temp->mmc1_regs[6] // shift register
    b ksNesLinecntIrqDefault
L_8003C718:
    lbz r7, state_temp->mmc1_regs[0] // ctrl reg
    li r3, 0x0
    ori r7, r7, 0xc
L_8003C724:
    li r8, 0x5
    addi r0, state_temp, state_temp->mmc1_regs
    stb r8, state_temp->mmc1_regs[5] // load counter
    extrwi r9, r3, 2, 17
    lbzx r8, r9, r0
    cmpw r8, r7
    beq ksNesLinecntIrqDefault
    stbx r7, r9, r0
    lbz r7, state_temp->mmc1_regs[0] // control reg
    lbz r10, state_temp->mmc1_regs[3] // bank select
    lbz r8, state_temp->prg_banks
    rlwinm r0, r7, 30, 30, 30
    slwi r10, r10, 1
    ori r0, r0, 0x1c
    and r10, r10, r8
    lwz r9, state_temp->prgromp
    and r10, r10, r0
    subi r10, r10, 0x4
    slwi r10, r10, 13
    add r10, r10, r9
    andi. r0, r7, 0x8
    bne L_8003C790
    stw r10, state_temp->cpu_8000_9fff
    stw r10, state_temp->cpu_a000_bfff
    stw r10, state_temp->cpu_c000_dfff
    stw r10, state_temp->cpu_e000_ffff
    b L_8003C7FC
L_8003C790:
    andi. r0, r7, 0x4
    bne L_8003C7B4
    subi r10, r10, 0x4000
    stw r10, state_temp->cpu_c000_dfff
    stw r10, state_temp->cpu_e000_ffff
    addi r0, r9, -0x8000
    stw r0, state_temp->cpu_8000_9fff
    stw r0, state_temp->cpu_a000_bfff
    b L_8003C7FC
L_8003C7B4:
    lbz r8, state_temp->mmc1_regs[4] // 512k program mode flag
    cmpwi r8, 0x0
    beq L_8003C7D0
    lbz r0, state_temp->mmc1_regs[1] // chr_bank0
    andi. r0, r0, 0x10
    slwi r0, r0, 14
    add r10, r10, r0
L_8003C7D0:
    stw r10, state_temp->cpu_8000_9fff
    stw r10, state_temp->cpu_a000_bfff
    cmpwi r8, 0x0
    beq L_8003C7E8
    xoris r0, r0, 0x4
    subf r9, r0, r9
L_8003C7E8:
    lwz r0, state_temp->prg_size
    subis r10, r9, 0x1
    add r10, r10, r0
    stw r10, state_temp->cpu_c000_dfff
    stw r10, state_temp->cpu_e000_ffff
L_8003C7FC:
    andi. r0, r7, 0x10
    lbz r8, state_temp->mmc1_regs[1] // chr_bank0
    lhz r9, state_temp->chr_banks
    bne L_8003C834
    rlwinm r8, r8, 2, 25, 28
    and r8, r8, r9
    addi r9, state_temp, state_temp->ppu_chr_banks + 0
    addi r0, state_temp, state_temp->mapper_chr_bank_ext + 0
L_8003C81C:
    stb r8, 0x0(r9)
    addi r9, r9, 0x1
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003C81C
    b L_8003C86C
L_8003C834:
    lbz r0, state_temp->mmc1_regs[2] // chr_bank1
    clrlslwi r8, r8, 27, 2
    and r8, r8, r9
    clrlslwi r0, r0, 27, 2
    and r9, r0, r9
    addi r10, state_temp, state_temp->ppu_chr_banks + 0
    addi r0, state_temp, state_temp->ppu_chr_banks + 4
L_8003C850:
    stb r8, 0x0(r10)
    addi r8, r8, 0x1
    stb r9, 0x4(r10)
    addi r10, r10, 0x1
    cmpw r10, r0
    addi r9, r9, 0x1
    bne L_8003C850
L_8003C86C:
    clrlslwi r7, r7, 30, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[0] - sizeof(u32*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u32*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003C880:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003C880
    b ksNesLinecntIrqDefault

entry ksNesStore02_8000
    lbz r7, state_temp->prg_banks
    slwi r8, r4, 1
    lwz r9, state_temp->prgromp
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault

entry ksNesStore03_6000
    lhz r0, state_temp->chr_banks
    clrlslwi r7, r4, 30, 3
    addi r9, state_temp, state_temp->ppu_chr_banks
    li r8, 0x0
    and r7, r7, r0
L_8003C8D0:
    stbx r7, r9, r8
    addi r8, r8, 0x1
    addi r7, r7, 0x1
    cmpwi r8, 0x8
    blt L_8003C8D0
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq04
    cmpwi r10, 0x0
    blt L_8003C924
    cmpwi r10, 0xef
    bgt L_8003C924
    lha r9, state_temp->mapper_irq_latch
    lbz r8, state_temp->ppu_register_cache[1]
    addi r9, r9, 0x1
    add r9, r9, r10
    sth r9, state_temp->scanline_irq_target_val
    cmpwi r7, 0x0
    beq ksNesMainLoop2
    andi. r8, r8, 0x18
    beq L_8003C924
    rlwinm REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0, 28, 20
    b SUB_8003b3a0
L_8003C924:
    li r8, 0x7fff
    sth r8, state_temp->scanline_irq_target_val
    b ksNesMainLoop2

entry ksNesStore04_8000
    lbz r0, state_temp->mmc3_command_register
    andi. r8, r3, 0x1
    bne L_8003CA34
    stb r4, state_temp->mmc3_command_register
    xor r7, r0, r4
    andi. r8, r7, 0x80
    beq L_8003C9C8
    andi. r8, r4, 0x80
    bne L_8003C990
    lbz r8, state_temp->mmc3_bank_select_regs[0]
    lbz r9, state_temp->mmc3_bank_select_regs[1]
    andi. r8, r8, 0xfffe
    andi. r9, r9, 0xfffe
    stb r8, state_temp->ppu_chr_banks[0]
    stb r9, state_temp->ppu_chr_banks[2]
    ori r8, r8, 0x1
    ori r9, r9, 0x1
    stb r8, state_temp->ppu_chr_banks[1]
    stb r9, state_temp->ppu_chr_banks[3]
    addi r8, state_temp, state_temp->mmc3_bank_select_regs[2]
    lswi r9, r8, 4
    addi r8, state_temp, state_temp->ppu_chr_banks + 4
    stswi r9, r8, 4
    b L_8003C9C8
L_8003C990:
    addi r8, state_temp, state_temp->mmc3_bank_select_regs[2]
    lswi r9, r8, 4
    addi r8, state_temp, state_temp->ppu_chr_banks
    stswi r9, r8, 4
    lbz r8, state_temp->mmc3_bank_select_regs[0]
    lbz r9, state_temp->mmc3_bank_select_regs[1]
    andi. r8, r8, 0xfffe
    andi. r9, r9, 0xfffe
    stb r8, state_temp->ppu_chr_banks[4]
    stb r9, state_temp->ppu_chr_banks[6]
    ori r8, r8, 0x1
    ori r9, r9, 0x1
    stb r8, state_temp->ppu_chr_banks[5]
    stb r9, state_temp->ppu_chr_banks[7]
L_8003C9C8:
    andi. r8, r7, 0x40
    beq ksNesLinecntIrqDefault
    lbz r8, state_temp->mmc3_bank_select_regs[6]
    andi. r9, r4, 0x40
    lbz r0, state_temp->prg_banks
    lwz r10, state_temp->prgromp
    lwz r5, state_temp->prg_size
    and r8, r8, r0
    bne L_8003CA0C
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r10
    stw r8, state_temp->cpu_8000_9fff
    add r10, r10, r5
    subis r10, r10, 0x1
    stw r10, state_temp->cpu_c000_dfff
    b ksNesLinecntIrqDefault
L_8003CA0C:
    subi r8, r8, 0x6
    slwi r8, r8, 13
    add r8, r8, r10
    stw r8, state_temp->cpu_c000_dfff
    add r10, r10, r5
    lis r7, 0x0
    ori r7, r7, 0xc000
    subf r10, r7, r10
    stw r10, state_temp->cpu_8000_9fff
    b ksNesLinecntIrqDefault
L_8003CA34:
    andi. r7, r0, 0x7
    add r8, r7, state_temp
    lbz r9, ksNesStateObj.mmc3_bank_select_regs(r8)
    cmpw r9, r4
    beq ksNesLinecntIrqDefault
    lbz r9, state_temp->prg_banks
    subic. r10, r7, 0x6
    bge L_8003CA9C
    lhz r9, state_temp->chr_banks
    subic. r10, r7, 0x2
    addi r5, state_temp, state_temp->ppu_chr_banks
    xor r0, r0, r10
    and r9, r9, r4
    rlwinm r0, r0, 27, 29, 29
    stb r9, ksNesStateObj.mmc3_bank_select_regs(r8)
    xori r0, r0, 0x4
    add r10, r10, r0
    bge L_8003CA94
    clrlslwi r10, r7, 31, 1
    andi. r9, r9, 0xfffe
    add r10, r10, r0
    stbx r9, r5, r10
    ori r9, r9, 0x1
    addi r10, r10, 0x1
L_8003CA94:
    stbx r9, r5, r10
    b ksNesLinecntIrqDefault
L_8003CA9C:
    lwz r7, state_temp->prgromp
    and r9, r9, r4
    stb r9, ksNesStateObj.mmc3_bank_select_regs(r8)
    bne L_8003CADC
    andi. r0, r0, 0x40
    beq L_8003CAC8
    subi r9, r9, 0x6
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, state_temp->cpu_c000_dfff
    b ksNesLinecntIrqDefault
L_8003CAC8:
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, state_temp->cpu_8000_9fff
    b ksNesLinecntIrqDefault
L_8003CADC:
    subi r9, r9, 0x5
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault
    
entry ksNesStore04_a000
    andi. r7, r3, 0x1
    bne ksNesLinecntIrqDefault
    clrlslwi r7, r4, 31, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003CB0C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003CB0C
    b ksNesLinecntIrqDefault

entry ksNesStore04_c000
    lha r8, state_temp->ppu_scanline_counter
    andi. r7, r3, 0x1
    bne L_8003CB50
    sth r4, state_temp->mapper_irq_latch
    cmpwi r8, 0x0
    blt ksNesLinecntIrqDefault
    addi r10, r4, 0x1
    cmpwi r8, 0xef
    bgt ksNesLinecntIrqDefault
L_8003CB44:
    add r10, r10, r8
L_8003CB48:
    sth r10, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003CB50:
    lha r10, state_temp->mapper_irq_latch
    cmpwi r8, 0x0
    blt L_8003CB48
    cmpwi r8, 0xef
    bgt L_8003CB48
    addi r8, r8, 0x1
    b L_8003CB44
    
entry ksNesStore04_e000
    andi. r7, r3, 0x1
    stb r7, state_temp->cpu_state.mapper_irq_enable
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq05Timer
    li r0, 0x80
    stb r0, state_temp->mmc5a_hardware_timer_irq_upper
    li r0, 0x7fff
    sth r0, state_temp->mmc5_scanline_irq_target_val
    b SUB_8003b3a0

entry ksNesLinecntIrq05Vcount
    li r0, 0xc0
    stb r0, state_temp->mmc5_scanline_irq_status
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStore05_4000
    andi.      r7,r3,0x1000
    beq        ksNesStoreIO
    lbz        r7,state_temp->mmc5_ext_ram_mode
    subic.     r8,r3,0x5c00
    blt        LAB_8003cbc8
    cmpwi      r7,0x3
    addi       r9,state_temp,state_temp->mmc5_extension_ram
    beq        ksNesLinecntIrqDefault
    stbx       r4,r8,r9
    b          ksNesLinecntIrqDefault
LAB_8003cbc8:
    cmpwi      r3,0x520a
    bgt        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5209
    blt        LAB_8003cc20
    addi       r8,state_temp,state_temp->_17CB
    stbx       r4,r8,r7
    bne        ksNesLinecntIrqDefault
    lbz        r8,state_temp->_17CC
    li         r9,KS_NES_CPU_CYCLES_PER_SCANLINE
    rlwimi     r4,r8,0x8,0x10,0x17
    cmpwi      r4,0x0
    beq        LAB_8003cc14
    divwu      r7,r4,r9
    lha        r8,state_temp->ppu_scanline_counter
    add        r7,r7,r8
    sth        r7,state_temp->mmc5_scanline_irq_target_val
    li         r8,0x0
    stb        r8,state_temp->_17CC
    b          ksNesLinecntIrqDefault
LAB_8003cc14:
    li         r7,0x7fff
    sth        r7,state_temp->mmc5_scanline_irq_target_val
    b          ksNesLinecntIrqDefault
LAB_8003cc20:
    cmpwi      r3,0x5207
    bge        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5205
    blt        LAB_8003cc54
    addi       r8,state_temp,state_temp->mmc5_mul_operands
    stbx       r4,r8,r7
    bne        ksNesLinecntIrqDefault
    lbz        r8,state_temp->mmc5_mul_operands[1]
    mullw      r9,r8,r4
    stb        r9,state_temp->mmc5_mul_regs[0]
    rlwinm     r10,r9,0x18,0x8,0x1f
    stb        r10,state_temp->mmc5_mul_regs[1]
    b          ksNesLinecntIrqDefault
LAB_8003cc54:
    subic.     r7,r3,0x5203
    blt        LAB_8003cc84
    beq        LAB_8003cc6c
    andi.      r7,r4,0x80
    stb        r7,state_temp->cpu_state.mapper_irq_enable
    b          ksNesLinecntIrqDefault
LAB_8003cc6c:
    stb        r4,state_temp->mmc5_scanline_irq_compare_value
    cmpwi      r4,0xf0
    blt        LAB_8003cc7c
    subi       r4,r4,0x14
LAB_8003cc7c:
    sth        r4,state_temp->scanline_irq_target_val
    b          ksNesLinecntIrqDefault
LAB_8003cc84:
    subic.     r7,r3,0x5200
    blt        LAB_8003cca0
    bne        LAB_8003cc94
    andi.      r4,r4,0xdf
LAB_8003cc94:
    addi       r8,state_temp,state_temp->_17C0
    stbx       r4,r8,r7
    b          ksNesLinecntIrqDefault
LAB_8003cca0:
    cmpwi      r3,0x5130
    bgt        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5100
    blt        LAB_8003ccc8
    rlwinm     r8,r7,0x2,0x0,0x1d
    lis        r9,ksNesStore05FuncTbl@h
    ori        r9,r9,ksNesStore05FuncTbl@l
    lwzx       r8,r9,r8
    mtspr      CTR,r8
    bctr
LAB_8003ccc8:
    cmpwi      r3,KS_NES_REG_MMC5_AUDIO_STATUS
    bgt        ksNesLinecntIrqDefault
    beq        ksNesStore4000
    cmpwi      r3,KS_NES_REG_MMC5_AUDIO_RAW_PCM
    bgt        ksNesLinecntIrqDefault
    beq        LAB_8003ccf0
    cmpwi      r3,KS_NES_REG_MMC5_AUDIO_PCM_MODE_IRQ
    beq        LAB_8003ccf0
    cmpwi      r3,0x5008
    bge        ksNesLinecntIrqDefault
LAB_8003ccf0:
    b          ksNesStore4000

entry ksNesStore05_5130
    lhz r7, state_temp->chr_banks
    cmpwi r7, 0x100
    blt ksNesLinecntIrqDefault
    andi. r8, r4, 0x1
    stb r8, state_temp->_179F
    b ksNesLinecntIrqDefault

entry ksNesStore05_5100
    andi.      r7, r4, 0x3
    stb        r7, state_temp->_1798 // register 0x5100. Select PRG banking mode.
LAB_8003cd14:
    // select bbram bank?
    lbz        r8, state_temp->bbram_mode_select // 0 or 3
    lbz        r9, state_temp->_1799 // bank number?
    lwz        r10, state_temp->bbramp
    // r9 = r9 & r8;
    // r8 must be 0x03 to limit it to the range [0, 3]
    // r8 must be 0x03 to limit it to the range [3, 6]
    and        r9, r9, r8
    // r9 = r9 - 3;
    subi       r9, r9, 0x3
    // r9 = r9 << 13;
    // r9 = r9 * 8192;
    // r9 = r9 * 0x2000;
    slwi       r9, r9, 13
    // r9 = r9 + r10;
    add        r9, r9, r10
    // state_temp->cpu_6000_7fff = bbramp + (((r9 & r8) - 3) * 0x2000)
    // state_temp->cpu_6000_7fff = r9;
    stw        r9, state_temp->cpu_6000_7fff

    lbz        r8, state_temp->prg_banks
    lbz        r9, state_temp->_179D
    lbz        r7, state_temp->_1798
    lwz        r5, state_temp->prgromp
    and        r9, r9, r8
    cmpwi      r7, 0x2
    bge        LAB_8003cdac
    cmpwi      r7, 0x0
    bne        LAB_8003cd78
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x10
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    stw        r9, state_temp->cpu_c000_dfff
    stw        r9, state_temp->cpu_e000_ffff
    b          ksNesLinecntIrqDefault
LAB_8003cd78:
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_179B
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    b          ksNesLinecntIrqDefault
LAB_8003cdac:
    cmpwi      r7, 0x2
    bne        LAB_8003cdfc
    subi       r9, r9, 0x7
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_179C
    and        r9, r9, r8
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    lbz        r9, state_temp->_179B
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    b          ksNesLinecntIrqDefault
LAB_8003cdfc:
    subi       r9, r9, 0x7
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_179C
    and        r9, r9, r8
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    lbz        r9, state_temp->_179B
    and        r9, r9, r8
    subi       r9, r9, 0x5
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_a000_bfff
    lbz        r9, state_temp->_179A
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    b          ksNesLinecntIrqDefault

entry ksNesStore05_5113
    // r8 = &state_temp->_176E[24];
    addi r8, state_temp, state_temp->_176E[24] // TODO: this might signify a union?
    // this functions handles memory mapped registers 0x5113-0x5117.
    // r7 must control which register is written to.
    // r8[r7] = r4
    stbx r4, r8, r7
    b LAB_8003cd14

entry ksNesStore05_5101
    andi. r7, r4, 0x3
    stb r7, state_temp->_179E
L_8003CE6C:
    lbz r7, state_temp->_179E
    lhz r8, state_temp->chr_banks
    lbz r9, state_temp->_17A7
    cmpwi r7, 0x2
    bge L_8003CEF4
    cmpwi r7, 0x0
    bne L_8003CEAC
    slwi r9, r9, 3
    addi r5, state_temp, state_temp->ppu_chr_banks[-1]
    and r9, r9, r8
    addi r0, r5, 0x8
L_8003CE98:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CE98
    b ksNesLinecntIrqDefault
L_8003CEAC:
    slwi r9, r9, 2
    addi r5, state_temp, state_temp->ppu_chr_banks[4 - 1]
    and r9, r9, r8
    addi r0, r5, 0x4
L_8003CEBC:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CEBC
    lbz r9, state_temp->_17A3
    addi r5, state_temp, state_temp->ppu_chr_banks[-1]
    slwi r9, r9, 2
    addi r0, r5, 0x4
    and r9, r9, r8
L_8003CEE0:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CEE0
    b ksNesLinecntIrqDefault
L_8003CEF4:
    cmpwi r7, 0x2
    bne L_8003CF5C
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, state_temp->ppu_chr_banks[6]
    addi r9, r9, 0x1
    stb r9, state_temp->ppu_chr_banks[7]
    lbz r9, state_temp->_17A5
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, state_temp->ppu_chr_banks[4]
    addi r9, r9, 0x1
    stb r9, state_temp->ppu_chr_banks[5]
    lbz r9, state_temp->_17A3
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, state_temp->ppu_chr_banks[2]
    addi r9, r9, 0x1
    stb r9, state_temp->ppu_chr_banks[3]
    lbz r9, state_temp->_17A1
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, state_temp->ppu_chr_banks[0]
    addi r9, r9, 0x1
    stb r9, state_temp->ppu_chr_banks[1]
    b ksNesLinecntIrqDefault
L_8003CF5C:
    addi r5, state_temp, state_temp->ppu_chr_banks
    li r10, 0x7
    addi r7, state_temp, state_temp->_17A0
L_8003CF68:
    and r9, r9, r8
    stbx r9, r5, r10
    subic. r10, r10, 0x1
    lbzx r9, r7, r10
    bge L_8003CF68
    b ksNesLinecntIrqDefault

entry ksNesStore05_5120
    lbz r9, state_temp->_179F
    addi r8, state_temp, state_temp->_176E[18] // TODO: Check this
    stbx r4, r8, r7
    addi r8, state_temp, state_temp->_17E4
    stbx r9, r8, r7
    b L_8003CE6C

entry ksNesStore05_5128
    lbz r9, state_temp->_179F
    addi r8, state_temp, state_temp->_176E[18] // TODO: Check this
    stbx r4, r8, r7
    addi r8, state_temp, state_temp->_17E4
    stbx r9, r8, r7
    b ksNesLinecntIrqDefault

entry ksNesStore05_5102
    addi r7, state_temp, state_temp->mmc5_prg_ram_protect[0] - 0x5102
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesStore05_5104
    andi. r7, r4, 0x3
    stb r7, state_temp->mmc5_ext_ram_mode
    b ksNesLinecntIrqDefault

entry ksNesStore05_5105
    stb r4, state_temp->mmc5_nametable_mapping
    ori r5, r4, 0x100
    addi r7, state_temp, state_temp->mapper_chr_bank_ext[8]
    addi r8, state_temp, state_temp->ppu_nametable_ram
L_8003CFD8:
    andi. r9, r5, 0x3
    srwi r5, r5, 2
    cmpwi r9, 0x2
    bge L_8003CFF4
    slwi r9, r9, 10
    add r0, r8, r9
    b L_8003D000
L_8003CFF4:
    addi r0, state_temp, state_temp->mmc5_extension_ram
    beq L_8003D000
    addi r0, state_temp, state_temp->cartridge_nametable_ram
L_8003D000:
    cmpwi r5, 0x1
    stwu r0, 0x4(r7)
    bne L_8003CFD8
    b ksNesLinecntIrqDefault

entry ksNesStore05_5106
    // MMC5 Registers 62 & 63 are used for fillmode_tile & fillmode_color
    addi r7, state_temp, state_temp->_17AC - 0x5106
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesLoad05_4000
    andi. r7, r3, 0x1000
    beq ksNesLoadIO
    subic. r7, r3, 0x5c00
    addi r9, state_temp, state_temp->mmc5_extension_ram
    blt L_8003D038
    lbzx r4, r9, r7
    bctr
L_8003D038:
    cmpwi r3, 0x5010
    bltctr
    bgt L_8003D054
    lbz r4, state_temp->mmc5_apu_pcm_mode_irq
    li r7, 0x1
    stb r7, state_temp->mmc5_apu_pcm_mode_irq
    bctr
L_8003D054:
    cmpwi r3, KS_NES_REG_MMC5_AUDIO_STATUS
    bltctr
    bgt L_8003D068
    lbz r4, state_temp->mmc5_apu_status
    bctr
L_8003D068:
    subic. r7, r3, 0x5204
    bltctr
    bgt L_8003D084
    lbz r4, state_temp->mmc5_scanline_irq_status
    andi. r8, r4, 0x7f
    stb r8, state_temp->mmc5_scanline_irq_status
    bctr
L_8003D084:
    // This handles the register mapping for 0x5025-5028. It incorrectly allows reading from
    // CL3/SL3 Data Direction & Output Data Source (0x5027)
    // There's also no handling for the lower 8 bits of the MMC5A hardware timer & IRQ register at 0x520A.
    cmpwi r3, 0x5209
    bgtctr
    beq L_8003D09C
    addi r9, state_temp, state_temp->mmc5_mul_regs[-1] // -1 because r7 is 1-4
    lbzx r4, r9, r7
    bctr
L_8003D09C:
    lbz r4, state_temp->mmc5a_hardware_timer_irq_upper
    li r8, 0x0
    stb r8, state_temp->mmc5a_hardware_timer_irq_upper
    bctr

entry ksNesStore07_8000
    lbz r8, state_temp->prg_banks
    clrlslwi r10, r4, 28, 2
    lwz r9, state_temp->prgromp
    addi r0, state_temp, state_temp->ppu_nametable_ram
    and r10, r10, r8
    rlwinm r7, r4, 6, 21, 21
    subi r10, r10, 0x4
    add r7, r7, r0
    slwi r10, r10, 13
    stw r7, state_temp->ppu_nametable_pointers[0]
    stw r7, state_temp->ppu_nametable_pointers[1]
    stw r7, state_temp->ppu_nametable_pointers[2]
    stw r7, state_temp->ppu_nametable_pointers[3]
    add r10, r10, r9
    stw r10, state_temp->cpu_8000_9fff
    stw r10, state_temp->cpu_a000_bfff
    stw r10, state_temp->cpu_c000_dfff
    stw r10, state_temp->cpu_e000_ffff
    b ksNesLinecntIrqDefault

entry ksNesStore09_8000
    b ksNesLinecntIrqDefault

entry ksNesStore09_a000
    andi. r7, r3, 0x1000
    bne L_8003D124
    lbz r8, state_temp->prg_banks
    lwz r9, state_temp->prgromp
    and r8, r8, r4
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    b ksNesLinecntIrqDefault
L_8003D124:
    lhz r8, state_temp->chr_banks
    slwi r7, r4, 2
    and r8, r8, r7
    addi r8, r8, 0x1
    stb r8, state_temp->ppu_chr_banks[1]
    b ksNesLinecntIrqDefault

entry ksNesStore09_c000
    andi. r7, r3, 0x1000
    bne L_8003D158
    lhz r8, state_temp->chr_banks
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, state_temp->ppu_chr_banks[0]
    b ksNesLinecntIrqDefault
L_8003D158:
    lhz r8, state_temp->chr_banks
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, state_temp->ppu_chr_banks[5]
    b ksNesLinecntIrqDefault

entry ksNesStore09_e000
    andi. r7, r3, 0x1000
    bne L_8003D188
    lhz r8, state_temp->chr_banks
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, state_temp->ppu_chr_banks[4]
    b ksNesLinecntIrqDefault
L_8003D188:
    clrlslwi r7, r4, 31, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D19C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D19C
    b ksNesLinecntIrqDefault
    
entry ksNesStore0a_8000
    b ksNesLinecntIrqDefault

entry ksNesStore0a_a000
    andi. r7, r3, 0x1000
    bne L_8003D124
    lbz r8, state_temp->prg_banks
    slwi r7, r4, 1
    lwz r9, state_temp->prgromp
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq49
    li r8, 0x7fff
    sth r8, state_temp->scanline_irq_target_val
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStore12_8000
    rlwinm r7, r3, 22, 29, 29
    addi r0, state_temp, state_temp->_17D0
    rlwimi r7, r3, 0, 30, 31
    andi. r8, r4, 0xf
    cmpwi r7, 0x6
    bge ksNesLinecntIrqDefault
    stbx r8, r7, r0
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    lbzx r9, r7, r0
    slwi r8, r8, 4
    lbz r10, state_temp->prg_banks
    bne L_8003D234
    srwi r8, r8, 4
    slwi r9, r9, 4
L_8003D234:
    or r8, r8, r9
    lwz r9, state_temp->prgromp
    and r8, r8, r10
    srwi r7, r7, 1
    subi r8, r8, 0x4
    subf r8, r7, r8
    slwi r7, r7, 2
    slwi r8, r8, 13
    add r7, r7, state_temp
    add r8, r8, r9
    stw r8, (ksNesStateObj.cpu_8000_9fff)(r7)
    b ksNesLinecntIrqDefault

entry ksNesStore12_a000
    rlwinm r7, r3, 22, 27, 29
    addi r0, state_temp, state_temp->_17CE
    rlwimi r7, r3, 0, 30, 31
    andi. r8, r4, 0xf
    stbx r8, r7, r0
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    lbzx r9, r7, r0
    slwi r8, r8, 4
    bne L_8003D294
    srwi r8, r8, 4
    slwi r9, r9, 4
L_8003D294:
    lhz r10, state_temp->chr_banks
    or r8, r8, r9
    srwi r7, r7, 1
    addi r0, state_temp, state_temp->bbramp
    and r8, r8, r10
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
    
entry ksNesStore12_e000
    andi. r7, r3, 0x1000
    bne L_8003D2CC
    andi. r8, r4, 0xf
    andi. r7, r3, 0x3
    addi r0, state_temp, state_temp->_17E6
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
L_8003D2CC:
    andi. r7, r3, 0x2
    bne L_8003D318
    andi. r7, r3, 0x1
    beq ksNesLinecntIrqDefault
    andi. r7, r4, 0x1
    stb r7, state_temp->cpu_state.mapper_irq_enable
    lbz r7, state_temp->_17E6
    lbz r8, state_temp->_17E7
    lbz r9, state_temp->_17E8
    lbz r10, state_temp->_17E9
    rlwimi r7, r8, 4, 24, 27
    rlwimi r7, r9, 8, 20, 23
    rlwimi r7, r10, 12, 16, 19
    li r8, KS_NES_CPU_CYCLES_PER_SCANLINE
    divwu r9, r7, r8
    lha r8, state_temp->ppu_scanline_counter
    add r8, r8, r9
    sth r8, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003D318:
    andi. r8, r3, 0x1
    bne L_8003D328
    xori r4, r4, 0x1
    b ksNesStore16_9000
L_8003D328:
    cmpwi r4, 0x4e
    li r3, 0x10
    beq L_8003D354
    andi. r7, r4, 0x42
    xori r7, r7, 0x2
    cmpwi r7, 0x0
    bne ksNesLinecntIrqDefault
    extrwi r8, r4, 4, 26
    lis r7, ksNesVoiceIdTable_12@h
    ori r7, r7, ksNesVoiceIdTable_12@l
    lbzx r3, r7, r8
L_8003D354:
    lwz r9, state_temp->frame_flags
    andi. r9, r9, 0x1000
    bne ksNesLinecntIrqDefault
    bl Sound_PlayMENUPCM
    b ksNesLinecntIrqDefault
    
entry ksNesStore13_4000
    cmpwi r3, 0x4800
    blt ksNesStoreIO
    beq L_8003D3B4
    extrwi r8, r3, 1, 20
    addi r7, state_temp, state_temp->_17CB
    stbx r4, r7, r8
    lbz r8, state_temp->_17CC
    lbz r7, state_temp->_17CB
    andi. r9, r8, 0x80
    stb r9, state_temp->cpu_state.mapper_irq_enable
    rlwimi r7, r8, 8, 17, 23
    li r8, 0x7fff
    subf r7, r7, r8
    li r8, KS_NES_CPU_CYCLES_PER_SCANLINE
    divwu r9, r7, r8
    lha r8, state_temp->ppu_scanline_counter
    add r9, r9, r8
    sth r9, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003D3B4:
    lbz r8, state_temp->_17EA
    lwz r7, state_temp->bbramp
    andi. r9, r8, 0x7f
    andi. r10, r8, 0x80
    stbx r4, r7, r8
    beq ksNesLinecntIrqDefault
    addi r8, r8, 0x1
    ori r8, r8, 0x80
    stb r8, state_temp->_17EA
    b ksNesLinecntIrqDefault
    
entry ksNesLoad13_4000
    cmpwi r3, 0x4800
    blt ksNesLoadIO
    beq L_8003D41C
    lha r7, state_temp->ppu_scanline_counter
    lha r8, state_temp->scanline_irq_target_val
    subf r7, r7, r8
    li r8, 0x7fff
    mulli r7, r7, KS_NES_CPU_CYCLES_PER_SCANLINE
    andi. r9, r3, 0x800
    subf r7, r7, r8
    bne L_8003D410
    andi. r4, r7, 0xff
    bctr
L_8003D410:
    lbz r4, state_temp->_17CC
    rlwimi r4, r7, 0, 25, 31
    bctr
L_8003D41C:
    lbz r8, state_temp->_17EA
    lwz r7, state_temp->bbramp
    andi. r9, r8, 0x7f
    andi. r10, r8, 0x80
    lbzx r4, r7, r8
    beqctr
    addi r8, r8, 0x1
    ori r8, r8, 0x80
    stb r8, state_temp->_17EA
    bctr

entry ksNesStore13_8000
    lhz r8, state_temp->chr_banks
    extrwi r7, r3, 3, 18
    addi r9, state_temp, state_temp->ppu_chr_banks
    and r8, r8, r4
    stbx r8, r9, r7
    b ksNesLinecntIrqDefault

entry ksNesStore13_c000
    lhz r8, state_temp->chr_banks
    rlwinm r7, r3, 23, 28, 29
    cmpwi r4, 0x1
    ble ksNesLinecntIrqDefault
    cmpwi r4, 0xe0
    addi r9, state_temp, state_temp->ppu_nametable_pointers
    bge L_8003D490
    lwz r5, state_temp->chrramp
    and r8, r8, r4
    slwi r8, r8, 10
    add r8, r8, r5
    stwx r8, r9, r7
    b ksNesLinecntIrqDefault
L_8003D490:
    addi r5, state_temp, state_temp->ppu_nametable_ram
    clrlslwi r8, r4, 31, 10
    add r8, r8, r5
    stwx r8, r9, r7
    b ksNesLinecntIrqDefault

entry ksNesStore13_e000
    andi. r7, r3, 0x1000
    beq L_8003D4B4
    andi. r7, r3, 0x800
    bne L_8003D4E4
L_8003D4B4:
    lbz r9, state_temp->prg_banks
    extrwi r7, r3, 2, 19
    rlwinm r8, r3, 23, 28, 29
    addi r5, state_temp, state_temp->cpu_8000_9fff
    and r9, r9, r4
    addi r7, r7, 0x4
    lwz r10, state_temp->prgromp
    subf r9, r7, r9
    slwi r9, r9, 13
    add r9, r9, r10
    stwx r9, r5, r8
    b ksNesLinecntIrqDefault
L_8003D4E4:
    stb r4, state_temp->_17EA
    b ksNesLinecntIrqDefault

entry ksNesStore16_8000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    bne ksNesStore16_9000
    lwz r7, state_temp->prgromp
    and r9, r4, r8
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    stw r7, state_temp->cpu_8000_9fff
    b ksNesLinecntIrqDefault

entry ksNesStore16_9000
    clrlslwi r7, r4, 30, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D528:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D528
    b ksNesLinecntIrqDefault

entry ksNesStore16_a000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    bne ksNesStore16_b000
L_8003D548:
    lwz r7, state_temp->prgromp
    and r9, r4, r8
    subi r9, r9, 0x5
    slwi r9, r9, 13
    add r7, r7, r9
    stw r7, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault

entry ksNesStore16_b000
    rlwinm r7, r3, 21, 28, 30
    andi. r8, r3, 0x2
    bne ksNesLinecntIrqDefault
    rlwimi r7, r3, 0, 31, 31
    srwi r8, r4, 1
    add r7, r7, state_temp
    stb r8, (ksNesStateObj.ppu_chr_banks - 6)(r7) // dunno if this is right but I'd assume so?
    b ksNesLinecntIrqDefault

entry ksNesStore17_a000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    beq L_8003D548

entry ksNesStore17_b000
    rlwinm r7, r3, 21, 28, 30
    andi. r8, r3, 0xa
    beq L_8003D5A0
    addi r7, r7, 0x1
L_8003D5A0:
    add r7, r7, state_temp
    lbz r10, (ksNesStateObj.ppu_chr_banks - 6)(r7) // dunno if this is right but I'd assume so?
    andi. r8, r3, 0x5
    bne L_8003D814
    b L_8003D820
    
entry ksNesStore17_e000
    andi. r8, r3, 0x1000
    beq ksNesStore17_b000
    andi. r7, r3, 0xf
    beq L_8003D870
    andi. r8, r7, 0x4
    bne L_8003D87C
    andi. r8, r7, 0x8
    bne L_8003D888
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq18
    addi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0xc00
    andi. r8, r7, 0x1
    bne L_8003D5F0
    li r8, 0x7fff
    sth r8, state_temp->scanline_irq_target_val
    b L_8003D608
L_8003D5F0:
    lbz r8, state_temp->_17CF
    lha r9, state_temp->ppu_scanline_counter
    li r10, 0x100
    subf r8, r8, r10
    add r9, r9, r8
    sth r9, state_temp->scanline_irq_target_val
L_8003D608:
    cmpwi r7, 0x0
    beq ksNesMainLoop2
    b SUB_8003b3a0

entry ksNesStore18_8000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    bne L_8003D644
    lwz r7, state_temp->prgromp
    slwi r9, r4, 1
    and r8, r8, r9
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r7, r7, r8
    stw r7, state_temp->cpu_8000_9fff
    stw r7, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault
L_8003D644:
    lbz r10, state_temp->_17CD
    andi. r7, r3, 0x3000
    subi r7, r7, 0x1000
    srwi r7, r7, 10
    andi. r8, r3, 0x3
    beq L_8003D670
    xor r8, r8, r10
    add r7, r7, r8
    addi r7, r7, 0x1
    cmpwi r8, 0x3
    beq ksNesLinecntIrqDefault
L_8003D670:
    ori r3, r7, 0x5000
    b ksNesStore4000

entry ksNesStore18_a000
    andi. r7, r3, 0x1fff
    cmpwi r7, 0x1003
    bne L_8003D644
    rlwinm r7, r4, 2, 26, 27
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D698:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D698
    b ksNesLinecntIrqDefault

entry ksNesStore18_c000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    bne L_8003D6D4
    lwz r7, state_temp->prgromp
    and r8, r8, r4
    subi r8, r8, 0x6
    slwi r8, r8, 13
    add r7, r7, r8
    stw r7, state_temp->cpu_c000_dfff
    b ksNesLinecntIrqDefault
L_8003D6D4:
    lbz r9, state_temp->_17CD
    andi. r8, r3, 0x3
    beq L_8003D6EC
    cmpwi r8, 0x3
    beq L_8003D6EC
    xor r8, r8, r9
L_8003D6EC:
    rlwimi r8, r7, 22, 29, 29
    xori r8, r8, 0x4
    add r8, r8, state_temp
    stb r4, (ksNesStateObj.ppu_chr_banks)(r8)
    b ksNesLinecntIrqDefault
    
entry ksNesStore18_e000
    andi. r7, r3, 0x1000
    beq L_8003D6D4
    andi. r7, r3, 0x3
    beq L_8003D720
    lbz r10, state_temp->_17CE
    and. r8, r3, r10
    bne L_8003D728
    b ksNesLinecntIrqDefault
L_8003D720:
    stb r4, state_temp->_17CF
    b ksNesLinecntIrqDefault
L_8003D728:
    andi. r7, r4, 0x3
    stb r7, state_temp->cpu_state.mapper_irq_enable
    lbz r8, state_temp->_17CF
    lha r9, state_temp->ppu_scanline_counter
    li r10, 0x100
    subf r8, r8, r10
    add r9, r9, r8
    sth r9, state_temp->scanline_irq_target_val
    bne ksNesLinecntIrqDefault
    stb r7, state_temp->cpu_state.irq_pending_flag
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq19
    subi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0xc00
    li r8, 0x7fff
    sth r8, state_temp->scanline_irq_target_val
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2
    
entry ksNesStore19_8000
    lbz r8, state_temp->_17C9
    andi. r7, r3, 0x1000
    bne L_8003D7A4
    lwz r7, state_temp->prgromp
    lbz r9, state_temp->prg_banks
    and r9, r9, r4
    stb r9, state_temp->_17CA
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    andi. r8, r8, 0x2
    bne L_8003D7DC
L_8003D79C:
    stw r7, state_temp->cpu_8000_9fff
    b ksNesLinecntIrqDefault
L_8003D7A4:
    lbz r8, state_temp->_17C9
    andi. r7, r3, 0x2
    beq ksNesStore16_9000
    lbz r9, state_temp->_17CA
    stb r4, state_temp->_17C9
    xor r8, r8, r4
    andi. r8, r8, 0x2
    bne ksNesLinecntIrqDefault
    lwz r7, state_temp->prgromp
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    andi. r8, r4, 0x2
    beq L_8003D79C
L_8003D7DC:
    subi r7, r7, 0x4000
    stw r7, state_temp->cpu_c000_dfff
    b ksNesLinecntIrqDefault
    
entry ksNesStore19_a000
    lbz r8, state_temp->prg_banks
    andi. r7, r3, 0x1000
    beq L_8003D548

entry ksNesStore19_b000
    andi. r9, r3, 0x85
    rlwinm r7, r3, 21, 28, 30
    beq L_8003D804
    addi r7, r7, 0x1
L_8003D804:
    add r7, r7, state_temp
    lbz r10, (ksNesStateObj.ppu_chr_banks - 6)(r7)
    andi. r8, r3, 0x42
    beq L_8003D820
L_8003D814:
    rlwimi r10, r4, 4, 24, 27
    stb r10, (ksNesStateObj.ppu_chr_banks - 6)(r7)
    b ksNesLinecntIrqDefault
L_8003D820:
    rlwimi r10, r4, 0, 28, 31
    stb r10, (ksNesStateObj.ppu_chr_banks - 6)(r7)
    b ksNesLinecntIrqDefault

entry ksNesStore19_e000
    andi. r7, r3, 0x1000
    beq ksNesStore19_b000
    andi. r7, r3, 0xc7
    beq L_8003D870
    cmpwi r7, 0x2
    beq L_8003D87C
    cmpwi r7, 0x1
    beq L_8003D888
    cmpwi r7, 0x4
    beq L_8003D888
    cmpwi r7, 0x3
    beq L_8003D8B8
    andi. r8, r7, 0x40
    bne L_8003D87C
    andi. r8, r7, 0x80
    bne L_8003D888
    b ksNesLinecntIrqDefault
L_8003D870:
    andi. r8, r4, 0xf
    stb r8, state_temp->_17CB
    b ksNesLinecntIrqDefault
L_8003D87C:
    slwi r8, r4, 4
    stb r8, state_temp->_17CC
    b ksNesLinecntIrqDefault
L_8003D888:
    andi. r7, r4, 0x2
    stb r7, state_temp->cpu_state.mapper_irq_enable
    lha r10, state_temp->ppu_scanline_counter
    lbz r7, state_temp->_17CB
    lbz r8, state_temp->_17CC
    sth r10, state_temp->mapper19_irq_scanline_latch
    or r7, r7, r8
    li r9, 0x101
    subf r7, r7, r9
    add r10, r10, r7
    sth r10, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003D8B8:
    lbz r7, state_temp->_17CB
    lbz r8, state_temp->_17CC
    lha r10, state_temp->mapper19_irq_scanline_latch
    or r7, r7, r8
    add r10, r10, r7
    sth r10, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault

entry ksNesStore42_8000
    lhz r5, state_temp->chr_banks
    addi r7, state_temp, state_temp->ppu_chr_banks[0] - 1
    clrlslwi r10, r4, 28, 3
    addi r0, r7, 0x8
    and r10, r10, r5
    L_8003D8E8:
    stbu r10, 0x1(r7)
    addi r10, r10, 0x1
    cmpw r7, r0
    bne L_8003D8E8
    lbz r8, state_temp->prg_banks
    rlwinm r9, r4, 30, 28, 29
    lwz r7, state_temp->prgromp
    and r8, r8, r9
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r7
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    stw r8, state_temp->cpu_c000_dfff
    stw r8, state_temp->cpu_e000_ffff
    b ksNesLinecntIrqDefault
    
entry ksNesLinecntIrq43
    addi REGISTER_CYCLE_COUNT, REGISTER_CYCLE_COUNT, 0x4000
    li r8, 0x7fff
    sth r8, state_temp->scanline_irq_target_val
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2
    
entry ksNesStore43_c000
    andi. r7, r3, 0x1000
    bne L_8003D960
    lha r8, state_temp->ppu_scanline_counter
    li r9, 0xdb
    subf r9, r4, r9
    add r8, r8, r9
    sth r8, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003D960:
    andi. r7, r4, 0x10
    stb r7, state_temp->cpu_state.mapper_irq_enable
    b ksNesLinecntIrqDefault

entry ksNesStore44_8000
    lhz r7, state_temp->chr_banks
    slwi r8, r4, 1
    rlwinm r9, r3, 21, 29, 30
    addi r0, state_temp, state_temp->ppu_chr_banks
    and r7, r7, r8
    stbux r7, r9, r0
    addi r7, r7, 0x1
    stb r7, 0x1(r9)
    b ksNesLinecntIrqDefault

entry ksNesStore44_c000
    lhz r8, state_temp->chr_banks
    extrwi r7, r3, 1, 19
    addi r9, state_temp, state_temp->_17EB
    and r8, r8, r4
    stbx r8, r9, r7
L_8003D9A4:
    lbz r0, state_temp->_17ED
    andi. r8, r0, 0x10
    bne L_8003D9D8
    clrlslwi r7, r0, 30, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D9C4:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D9C4
    b ksNesLinecntIrqDefault
L_8003D9D8:
    lbz r7, state_temp->_17EB
    lwz r9, state_temp->chrramp
    lbz r8, state_temp->_17EC
    addis r9, r9, 0x2
    slwi r7, r7, 10
    slwi r8, r8, 10
    add r7, r7, r9
    add r8, r8, r9
    andi. r9, r0, 0x3
    bne L_8003DA14
    stw r7, state_temp->ppu_nametable_pointers[0]
    stw r8, state_temp->ppu_nametable_pointers[1]
    stw r7, state_temp->ppu_nametable_pointers[2]
    stw r8, state_temp->ppu_nametable_pointers[3]
    b ksNesLinecntIrqDefault
L_8003DA14:
    cmpwi r9, 0x1
    bne L_8003DA30
    stw r7, state_temp->ppu_nametable_pointers[0]
    stw r7, state_temp->ppu_nametable_pointers[1]
    stw r8, state_temp->ppu_nametable_pointers[2]
    stw r8, state_temp->ppu_nametable_pointers[3]
    b ksNesLinecntIrqDefault
L_8003DA30:
    andi. r9, r9, 0x1
    bne L_8003DA3C
    mr r8, r7
L_8003DA3C:
    stw r8, state_temp->ppu_nametable_pointers[0]
    stw r8, state_temp->ppu_nametable_pointers[1]
    stw r8, state_temp->ppu_nametable_pointers[2]
    stw r8, state_temp->ppu_nametable_pointers[3]
    b ksNesLinecntIrqDefault
    
entry ksNesStore44_e000
    andi. r7, r3, 0x1000
    beq L_8003DA80
    lbz r9, state_temp->prg_banks
    slwi r7, r4, 1
    lwz r8, state_temp->prgromp
    and r7, r7, r9
    subi r7, r7, 0x4
    slwi r7, r7, 13
    add r7, r7, r8
    stw r7, state_temp->cpu_8000_9fff
    stw r7, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault
L_8003DA80:
    stb r4, state_temp->_17ED
    b L_8003D9A4
    
// Sunsoft FME-7
entry ksNesStore45_8000
    stb r4, state_temp->_17EE
    b ksNesLinecntIrqDefault

entry ksNesStore45_a000
    lbz r7, state_temp->_17EE
    cmpwi r7, 0x8
    blt L_8003DAD0
    cmpwi r7, 0xc
    bge L_8003DAE4
    lbz r8, state_temp->prg_banks
    clrlslwi r5, r7, 30, 2
    lwz r9, state_temp->prgromp
    subi r7, r7, 0x5
    and r8, r8, r4
    addi r0, state_temp, state_temp->cpu_6000_7fff
    subf r8, r7, r8
    slwi r8, r8, 13
    add r8, r8, r9
    stwx r8, r5, r0
    b ksNesLinecntIrqDefault
L_8003DAD0:
    lhz r8, state_temp->chr_banks
    addi r0, state_temp, state_temp->ppu_chr_banks
    and r8, r8, r4
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
L_8003DAE4:
    bne L_8003DB10
    clrlslwi r7, r4, 30, 4
    addi r0, state_temp, state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*)
    addi r9, state_temp, state_temp->ppu_nametable_pointers[0] - sizeof(u8*)
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DAFC:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DAFC
    b ksNesLinecntIrqDefault
L_8003DB10:
    cmpwi r7, 0xd
    bne L_8003DB54
    li r8, 0x1
    cmpwi r4, 0x81
    beq L_8003DB28
    li r8, 0x0
L_8003DB28:
    stb r8, state_temp->cpu_state.mapper_irq_enable
    lbz r8, state_temp->_17CC
    lbz r7, state_temp->_17CB
    li r0, KS_NES_CPU_CYCLES_PER_SCANLINE
    lha r9, state_temp->ppu_scanline_counter
    rlwimi r7, r8, 8, 16, 23
    divwu r8, r7, r0
    add r9, r9, r8
    addi r9, r9, 0x1
    sth r9, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault
L_8003DB54:
    cmpwi r7, 0x10
    bge ksNesLinecntIrqDefault
    addi r0, state_temp, (state_temp->_17BE - sizeof(u8))
    stbx r4, r7, r0
    b ksNesLinecntIrqDefault

entry ksNesStore46_8000
    lbz r8, state_temp->prg_banks
    rlwinm r7, r4, 29, 28, 30
    lwz r9, state_temp->prgromp
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    lhz r8, state_temp->chr_banks
    clrlslwi r7, r4, 28, 3
    and r8, r8, r7
    addi r9, state_temp, (state_temp->ppu_chr_banks[0] - sizeof(u8))
    addi r0, r9, 0x8
L_8003DBA0:
    stbu r8, 0x1(r9)
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003DBA0
    andi. r0, r4, 0x80
    addi r7, state_temp, state_temp->ppu_nametable_ram
    addi r8, state_temp, 0xc00
    bne L_8003DBC4
    mr r7, r8
L_8003DBC4:
    stw r7, state_temp->ppu_nametable_pointers[0]
    stw r8, state_temp->ppu_nametable_pointers[1]
    stw r7, state_temp->ppu_nametable_pointers[2]
    stw r8, state_temp->ppu_nametable_pointers[3]
    b ksNesLinecntIrqDefault

entry ksNesStore49_a000
    andi. r7, r4, 0xf
    extrwi. r8, r3, 1, 19
    beq L_8003DBE8
    clrlslwi r7, r4, 28, 4
L_8003DBE8:
    add r8, r8, state_temp
    stb r7, (ksNesStateObj._17CB)(r8)
    b ksNesLinecntIrqDefault
    
entry ksNesStore49_c000
    lbz r8, state_temp->_17CB
    andi. r7, r4, 0x2
    lbz r9, state_temp->_17CC
    lha r10, state_temp->ppu_scanline_counter
    stb r7, state_temp->cpu_state.mapper_irq_enable
    or r8, r8, r9
    li r9, 378
    subf r8, r8, r9
    add r8, r8, r10
    sth r8, state_temp->scanline_irq_target_val
    b ksNesLinecntIrqDefault

entry ksNesStore4b_8000
    andi. r7, r3, 0x1000
    bne L_8003DC54
    // fallthrough

entry ksNesStore4b_a000
    lbz r9, state_temp->prg_banks
    andi. r0, r3, 0xe000
    lwz r10, state_temp->prgromp
    rlwinm r7, r3, 21, 28, 29
    and r9, r9, r4
    addi r8, state_temp, state_temp->cpu_8000_9fff
    slwi r9, r9, 13
    subf r10, r0, r10
    add r9, r9, r10
    stwx r9, r8, r7
    b ksNesLinecntIrqDefault
L_8003DC54:
    lbz r7, (ksNesStateObj.ppu_chr_banks)(state_temp)
    rlwinm r8, r4, 5, 25, 25
    lhz r9, state_temp->chr_banks
    addi r10, state_temp, (state_temp->ppu_chr_banks[0] - sizeof(u8))
    andi. r7, r7, 0x3c
    addi r0, r10, 0x4
    or r7, r7, r8
    and r7, r7, r9
L_8003DC74:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DC74
    lbz r7, state_temp->ppu_chr_banks[4]
    rlwinm r8, r4, 4, 25, 25
    addi r0, r10, 0x4
    andi. r7, r7, 0x3c
    or r7, r7, r8
    and r7, r7, r9
L_8003DC9C:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DC9C
    clrlslwi r7, r4, 31, 4
    addi r0, state_temp, (state_temp->ppu_chr_bank_pointers[8] - sizeof(u8*))
    addi r9, state_temp, (state_temp->ppu_nametable_pointers[0] - sizeof(u32))
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DCC0:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DCC0
    b ksNesLinecntIrqDefault

entry ksNesStore4b_e000
    andi. r7, r3, 0x1000
    lhz r9, state_temp->chr_banks
    clrlslwi r8, r4, 28, 2
    bne L_8003DD10
    lbz r7, (ksNesStateObj.ppu_chr_banks)(state_temp)
    addi r10, state_temp, (state_temp->ppu_chr_banks[0] - sizeof(u8))
    addi r0, r10, 0x4
    andi. r7, r7, 0x40
    or r7, r7, r8
    and r7, r7, r9
L_8003DCFC:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DCFC
    b ksNesLinecntIrqDefault
L_8003DD10:
    lbz r7, state_temp->ppu_chr_banks[4]
    addi r10, state_temp, (state_temp->ppu_chr_banks[4] - sizeof(u8))
    addi r0, r10, 0x4
    andi. r7, r7, 0x40
    or r7, r7, r8
    and r7, r7, r9
L_8003DD28:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DD28
    b ksNesLinecntIrqDefault

entry ksNesStore56_6000
    andi. r7, r3, 0x1000
    bne L_8003DD94
    lbz r10, state_temp->prg_banks
    rlwinm r8, r4, 30, 28, 29
    lwz r9, state_temp->prgromp
    and r10, r10, r8
    subi r10, r10, 0x4
    slwi r10, r10, 13
    add r10, r10, r9
    stw r10, state_temp->cpu_8000_9fff
    stw r10, state_temp->cpu_a000_bfff
    stw r10, state_temp->cpu_c000_dfff
    stw r10, state_temp->cpu_e000_ffff
    clrlslwi r7, r4, 30, 3
    addi r8, state_temp, (state_temp->ppu_chr_banks - sizeof(u8))
    rlwimi r7, r4, 31, 26, 26
    addi r0, r8, 0x8
L_8003DD80:
    stbu r7, 0x1(r8)
    addi r7, r7, 0x1
    cmpw r8, r0
    bne L_8003DD80
    b ksNesLinecntIrqDefault
L_8003DD94:
    andi. r7, r4, 0x10
    bne ksNesLinecntIrqDefault
    lwz r8, state_temp->frame_flags
    andi. r3, r4, 0xf
    addi r3, r3, 0x1
    andi. r8, r8, 0x1000
    bne ksNesLinecntIrqDefault
    bl Sound_PlayMENUPCM
    b ksNesLinecntIrqDefault

entry ksNesStore57_6000
    rlwinm r7, r4, 2, 28, 28
    addi r9, state_temp, state_temp->ppu_chr_banks
    li r8, 0x0
L_8003DDC4:
    stbx r7, r9, r8
    addi r8, r8, 0x1
    addi r7, r7, 0x1
    cmpwi r8, 0x8
    blt L_8003DDC4
    b ksNesLinecntIrqDefault

entry ksNesStore59_c000
    lbz r8, state_temp->prg_banks
    rlwinm r7, r4, 29, 28, 30
    lwz r9, state_temp->prgromp
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    lhz r8, state_temp->chr_banks
    clrlslwi r7, r4, 29, 3
    rlwimi r7, r4, 31, 25, 25
    addi r9, state_temp, (state_temp->ppu_chr_banks - sizeof(u8))
    and r7, r7, r8
    addi r0, r9, 0x8
L_8003DE18:
    stbu r7, 0x1(r9)
    addi r7, r7, 0x1
    cmpw r9, r0
    bne L_8003DE18
    rlwinm r7, r4, 1, 27, 27
    addi r0, state_temp, state_temp->nesromp
    addi r9, state_temp, (state_temp->ppu_nametable_pointers - sizeof(u32))
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DE3C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DE3C
    b ksNesLinecntIrqDefault
   
entry ksNesStore5d_6000
    lbz r8, state_temp->prg_banks
    slwi r7, r4, 1
    lwz r9, state_temp->prgromp
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_a000_bfff
    b ksNesLinecntIrqDefault

entry ksNesStoreb8_6000
    lhz r10, state_temp->chr_banks
    addi r9, state_temp, state_temp->ppu_chr_banks
    clrlslwi r7, r4, 28, 2
    addi r0, r9, 0x4
    and r7, r7, r10
    rlwinm r8, r4, 30, 26, 29
    and r8, r8, r10
L_8003DE94:
    stb r7, 0x0(r9)
    addi r7, r7, 0x1
    stb r8, 0x4(r9)
    addi r9, r9, 0x1
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003DE94
    b ksNesLinecntIrqDefault
}

// clang-format on

#endif /* !TARGET_PC */

// void ksNesStoreBBRAM() {}
