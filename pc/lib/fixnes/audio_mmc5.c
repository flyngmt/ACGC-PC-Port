/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <malloc.h>
#include "apu.h"
#include "audio_mmc5.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"

//used externally
extern uint8_t audioExpansion;
uint8_t mmc5Out;
uint8_t mmc5pcm;
bool mmc5_dmcreadmode;

#define P1_ENABLE (1<<0)
#define P2_ENABLE (1<<1)

#define PULSE_CONST_V (1<<4)
#define PULSE_HALT_LOOP (1<<5)

#define DMC_READ_MODE (1<<0)
#define DMC_IRQ_ENABLE (1<<7)

static struct {
	uint8_t reg[0x18];
	envelope_t p1Env, p2Env;

	const uint16_t *mode4Ctr;
	const uint8_t *p1seq, *p2seq;

	uint16_t freq1, freq2;
	uint8_t p1LengthCtr, p2LengthCtr;
	uint8_t modePos;
	uint16_t modeCurCtr;
	uint16_t p1freqCtr, p2freqCtr;
	uint8_t p1Cycle, p2Cycle;
	bool p1haltloop, p2haltloop;
	bool dmcirqenable;
} mmc5_apu;

//from apu.c
extern const uint8_t lengthLookupTbl[0x20];
extern const uint8_t pulseSeqs[4][8];

static const uint16_t mmc5_mode4CtrNtsc[4] = {
	7456, 7458, 7458, 7458
};

static const uint16_t mmc5_mode4CtrPal[4] = {
	8314, 8312, 8314, 8314
};

extern uint8_t interrupt;
extern bool nesPAL;

void mmc5AudioInit()
{
	audioExpansion |= EXP_MMC5;
	mmc5Out = 0;
	mmc5pcm = 0;

	memset(mmc5_apu.reg,0,0x18);

	memset(&mmc5_apu.p1Env,0,sizeof(envelope_t));
	memset(&mmc5_apu.p2Env,0,sizeof(envelope_t));

	mmc5_apu.freq1 = 0; mmc5_apu.freq2 = 0;
	mmc5_apu.p1LengthCtr = 0; mmc5_apu.p2LengthCtr = 0;
	mmc5_apu.p1freqCtr = 0; mmc5_apu.p2freqCtr = 0;
	mmc5_apu.p1Cycle = 0; mmc5_apu.p2Cycle = 0;
	mmc5_apu.mode4Ctr = nesPAL ? mmc5_mode4CtrPal : mmc5_mode4CtrNtsc;
	mmc5_apu.modePos = 0;
	mmc5_apu.modeCurCtr = 0;

	mmc5_apu.p1seq = pulseSeqs[0];
	mmc5_apu.p2seq = pulseSeqs[1];

	mmc5_apu.p1haltloop = false; mmc5_apu.p2haltloop = false;
	mmc5_apu.dmcirqenable = false;
	mmc5_dmcreadmode = false;
}

void mmc5AudioClockTimers()
{
	if(mmc5_apu.p1freqCtr)
		mmc5_apu.p1freqCtr--;
	if(mmc5_apu.p1freqCtr == 0)
	{
		mmc5_apu.p1freqCtr = (mmc5_apu.freq1+1)*2;
		mmc5_apu.p1Cycle++;
		if(mmc5_apu.p1Cycle >= 8)
			mmc5_apu.p1Cycle = 0;
	}

	if(mmc5_apu.p2freqCtr)
		mmc5_apu.p2freqCtr--;
	if(mmc5_apu.p2freqCtr == 0)
	{
		mmc5_apu.p2freqCtr = (mmc5_apu.freq2+1)*2;
		mmc5_apu.p2Cycle++;
		if(mmc5_apu.p2Cycle >= 8)
			mmc5_apu.p2Cycle = 0;
	}
}

void mmc5AudioPCMWrite(uint8_t val)
{
	if(val == 0 && mmc5_apu.dmcirqenable)
		interrupt |= MMC5_DMC_IRQ;
	mmc5pcm = val;
}

static uint8_t mmc5_p1Out = 0, mmc5_p2Out = 0;

FIXNES_NOINLINE void mmc5AudioCycle()
{
	if(mmc5_apu.p1LengthCtr && (mmc5_apu.reg[0x15] & P1_ENABLE))
	{
		if(mmc5_apu.freq1 >= 8 && mmc5_apu.freq1 < 0x7FF)
			mmc5_p1Out = mmc5_apu.p1seq[mmc5_apu.p1Cycle] ? (mmc5_apu.p1Env.constant ? mmc5_apu.p1Env.vol : mmc5_apu.p1Env.decay) : 0;
	}
	if(mmc5_apu.p2LengthCtr && (mmc5_apu.reg[0x15] & P2_ENABLE))
	{
		if(mmc5_apu.freq2 >= 8 && mmc5_apu.freq2 < 0x7FF)
			mmc5_p2Out = mmc5_apu.p2seq[mmc5_apu.p2Cycle] ? (mmc5_apu.p2Env.constant ? mmc5_apu.p2Env.vol : mmc5_apu.p2Env.decay) : 0;
	}
	mmc5Out = mmc5_p1Out + mmc5_p2Out;
}

FIXNES_NOINLINE void mmc5AudioLenCycle()
{
	if(mmc5_apu.modeCurCtr)
		mmc5_apu.modeCurCtr--;
	if(mmc5_apu.modeCurCtr == 0)
	{
		if(mmc5_apu.p1LengthCtr)
		{
			doEnvelopeLogic(&mmc5_apu.p1Env);
			if(!mmc5_apu.p1haltloop)
				mmc5_apu.p1LengthCtr--;
		}
		if(mmc5_apu.p2LengthCtr)
		{
			doEnvelopeLogic(&mmc5_apu.p2Env);
			if(!mmc5_apu.p2haltloop)
				mmc5_apu.p2LengthCtr--;
		}
		mmc5_apu.modePos++;
		if(mmc5_apu.modePos >= 4)
			mmc5_apu.modePos = 0;
		mmc5_apu.modeCurCtr = mmc5_apu.mode4Ctr[mmc5_apu.modePos];
	}
}

void mmc5AudioSet8(uint16_t addr, uint8_t val)
{
	uint8_t reg = addr&0x1F;
	//printf("%02x %02x %04x\n", reg, val, cpuGetPc());
	mmc5_apu.reg[reg] = val;
	switch(reg)
	{
		case 0:
			mmc5_apu.p1Env.vol = val&0xF;
			mmc5_apu.p1seq = pulseSeqs[val>>6];
			mmc5_apu.p1Env.constant = ((val&PULSE_CONST_V) != 0);
			mmc5_apu.p1Env.loop = mmc5_apu.p1haltloop = ((val&PULSE_HALT_LOOP) != 0);
			break;
		case 2:
			//printf("P1 time low %02x\n", val);
			mmc5_apu.freq1 = ((mmc5_apu.freq1&~0xFF) | val);
			break;
		case 3:
			mmc5_apu.p1Cycle = 0;
			if(mmc5_apu.reg[0x15] & P1_ENABLE)
				mmc5_apu.p1LengthCtr = lengthLookupTbl[val>>3];
			mmc5_apu.freq1 = (mmc5_apu.freq1&0xFF) | ((val&7)<<8);
			//printf("P1 new freq %04x\n", mmc5_apu.freq2);
			mmc5_apu.p1Env.start = true;
			break;
		case 4:
			mmc5_apu.p2Env.vol = val&0xF;
			mmc5_apu.p2seq = pulseSeqs[val>>6];
			mmc5_apu.p2Env.constant = ((val&PULSE_CONST_V) != 0);
			mmc5_apu.p2Env.loop = mmc5_apu.p2haltloop = ((val&PULSE_HALT_LOOP) != 0);
			break;
		case 6:
			//printf("P2 time low %02x\n", val);
			mmc5_apu.freq2 = ((mmc5_apu.freq2&~0xFF) | val);
			break;
		case 7:
			mmc5_apu.p2Cycle = 0;
			if(mmc5_apu.reg[0x15] & P2_ENABLE)
				mmc5_apu.p2LengthCtr = lengthLookupTbl[val>>3];
			mmc5_apu.freq2 = (mmc5_apu.freq2&0xFF) | ((val&7)<<8);
			//printf("P2 new freq %04x\n", mmc5_apu.freq2);
			mmc5_apu.p2Env.start = true;
			break;
		case 0x10:
			mmc5_dmcreadmode = (val&DMC_READ_MODE)!=0;
			mmc5_apu.dmcirqenable = (val&DMC_IRQ_ENABLE)!=0;
			if(!mmc5_apu.dmcirqenable)
				interrupt &= ~MMC5_DMC_IRQ;
			break;
		case 0x11:
			if(!mmc5_dmcreadmode)
				mmc5AudioPCMWrite(val);
			break;
		case 0x15:
			//printf("Set 0x15 %02x\n",val);
			if(!(val & P1_ENABLE))
				mmc5_apu.p1LengthCtr = 0;
			if(!(val & P2_ENABLE))
				mmc5_apu.p2LengthCtr = 0;
			break;
		default:
			break;
	}
}

uint8_t mmc5AudioGet8(uint16_t addr)
{
	uint8_t ret, reg = addr&0x1F;
	//printf("%08x\n", reg)
	switch(reg)
	{
		case 0x10:
			ret = ((!!(interrupt&MMC5_DMC_IRQ))<<7);
			//printf("Get 0x10 %02x\n",ret);
			interrupt &= ~MMC5_DMC_IRQ;
			break;
		case 0x15:
			ret = (mmc5_apu.p1LengthCtr > 0) | ((mmc5_apu.p2LengthCtr > 0)<<1);
			break;
		default:
			ret = mmc5_apu.reg[reg];
			break;
	}
	return ret;
}
