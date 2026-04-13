/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _apu_h_
#define _apu_h_

#include "common.h"

#define NUM_BUFFERS 4

#define EXP_VRC6 (1<<0)
#define EXP_VRC7 (1<<1)
#define EXP_FDS (1<<2)
#define EXP_MMC5 (1<<3)
#define EXP_N163 (1<<4)
#define EXP_S5B (1<<5)

void apuInitBufs();
void apuDeinitBufs();
void apuInit();
FIXNES_ALWAYSINLINE void apuCycle();
void apuWriteDMCBuf(uint8_t val);
uint8_t *apuGetBuf();
uint32_t apuGetBufSize();
uint32_t apuGetFrequency();
void apuSetReg00(uint16_t addr, uint8_t val);
void apuSetReg01(uint16_t addr, uint8_t val);
void apuSetReg02(uint16_t addr, uint8_t val);
void apuSetReg03(uint16_t addr, uint8_t val);
void apuSetReg04(uint16_t addr, uint8_t val);
void apuSetReg05(uint16_t addr, uint8_t val);
void apuSetReg06(uint16_t addr, uint8_t val);
void apuSetReg07(uint16_t addr, uint8_t val);
void apuSetReg08(uint16_t addr, uint8_t val);
void apuSetReg0A(uint16_t addr, uint8_t val);
void apuSetReg0B(uint16_t addr, uint8_t val);
void apuSetReg0C(uint16_t addr, uint8_t val);
void apuSetReg0E(uint16_t addr, uint8_t val);
void apuSetReg0F(uint16_t addr, uint8_t val);
void apuSetReg10(uint16_t addr, uint8_t val);
void apuSetReg11(uint16_t addr, uint8_t val);
void apuSetReg12(uint16_t addr, uint8_t val);
void apuSetReg13(uint16_t addr, uint8_t val);
void apuSetReg15(uint16_t addr, uint8_t val);
void apuSetReg17(uint16_t addr, uint8_t val);
uint8_t apuGetReg15(uint16_t addr);
bool apuUpdate();
void apuBoot();
void apuReset();

typedef struct _envelope_t {
	bool start;
	bool constant;
	bool loop;
	uint8_t vol;
	//uint8_t envelope;
	uint8_t divider;
	uint8_t decay;
} envelope_t;

typedef struct _sweep_t {
	bool enabled;
	bool start;
	bool negative;
	bool mute;
	bool chan1;
	uint8_t period;
	uint8_t divider;
	uint8_t shift;
	//specifically signed for pulse 1 as a shift value of 0 and negative
	//flag enabled would cause an overflow and a mute otherwise
	int16_t targetFreq;
} sweep_t;

void doEnvelopeLogic(envelope_t *env);

#endif
