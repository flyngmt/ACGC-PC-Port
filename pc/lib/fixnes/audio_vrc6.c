/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <malloc.h>
#include "audio_vrc6.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"
#include "apu.h"

//used externally
extern uint8_t audioExpansion;
uint8_t vrc6Out;

static struct {
	uint16_t freq1, freq2, sawFreq;
	uint16_t reloadFreq1, reloadFreq2, reloadSawFreq;
	uint16_t p1freqCtr, p2freqCtr, sawFreqCtr;
	uint8_t p1Cycle, p2Cycle, sawCycle;
	uint8_t p1Vol, p2Vol, sawVol;
	uint8_t p1Duty, p2Duty, sawAdd;
	uint8_t speed;
	uint8_t p1Out, p2Out, sawOut;
	bool p1const, p2const;
	bool p1enable, p2enable, sawenable;
	bool halt;
} vrc6_apu;

void vrc6AudioInit()
{
	audioExpansion |= EXP_VRC6;
	vrc6Out = 0;
	vrc6_apu.freq1 = 0, vrc6_apu.freq2 = 0, vrc6_apu.sawFreq = 0;
	vrc6_apu.reloadFreq1 = 0, vrc6_apu.reloadFreq2 = 0, vrc6_apu.reloadSawFreq = 0;
	vrc6_apu.p1freqCtr = 0, vrc6_apu.p2freqCtr = 0, vrc6_apu.sawFreqCtr = 0;
	vrc6_apu.p1Cycle = 0, vrc6_apu.p2Cycle = 0, vrc6_apu.sawCycle = 0;
	vrc6_apu.p1Vol = 0, vrc6_apu.p2Vol = 0, vrc6_apu.sawVol = 0;
	vrc6_apu.p1Duty = 0, vrc6_apu.p2Duty = 0, vrc6_apu.sawAdd = 0;
	vrc6_apu.speed = 0;
	vrc6_apu.p1Out = 0, vrc6_apu.p2Out = 0, vrc6_apu.sawOut = 0;
	vrc6_apu.p1const = false, vrc6_apu.p2const = false;
	vrc6_apu.p1enable = false, vrc6_apu.p2enable = false, vrc6_apu.sawenable = false;
	vrc6_apu.halt = false;
	//printf("VRC6 Audio Inited!\n");
}

FIXNES_NOINLINE void vrc6AudioCycle()
{
	if(vrc6_apu.p1enable)
		vrc6_apu.p1Out = (vrc6_apu.p1const || vrc6_apu.p1Cycle <= vrc6_apu.p1Duty) ? vrc6_apu.p1Vol : 0;
	if(vrc6_apu.p2enable)
		vrc6_apu.p2Out = (vrc6_apu.p2const || vrc6_apu.p2Cycle <= vrc6_apu.p2Duty) ? vrc6_apu.p2Vol : 0;
	if(vrc6_apu.sawenable)
		vrc6_apu.sawOut = (vrc6_apu.sawVol>>3);

	vrc6Out = vrc6_apu.p1Out+vrc6_apu.p2Out+vrc6_apu.sawOut;
}

void vrc6AudioClockTimers()
{
	if(vrc6_apu.halt) return;

	if(vrc6_apu.p1freqCtr == 0)
	{
		vrc6_apu.p1freqCtr = vrc6_apu.reloadFreq1;
		vrc6_apu.p1Cycle++;
		vrc6_apu.p1Cycle &= 0xF;
	}
	else
		vrc6_apu.p1freqCtr--;

	if(vrc6_apu.p2freqCtr == 0)
	{
		vrc6_apu.p2freqCtr = vrc6_apu.reloadFreq2;
		vrc6_apu.p2Cycle++;
		vrc6_apu.p2Cycle &= 0xF;
	}
	else
		vrc6_apu.p2freqCtr--;

	if(vrc6_apu.sawFreqCtr == 0)
	{
		vrc6_apu.sawFreqCtr = vrc6_apu.reloadSawFreq;
		vrc6_apu.sawCycle++;
		vrc6_apu.sawVol += vrc6_apu.sawAdd;
		if(vrc6_apu.sawCycle >= 7)
		{
			vrc6_apu.sawCycle = 0;
			vrc6_apu.sawVol = 0;
		}
	}
	else
		vrc6_apu.sawFreqCtr--;
}

static void vrc6UpdateReloadFreq1()
{
	if(vrc6_apu.speed == 0)
		vrc6_apu.reloadFreq1 = vrc6_apu.freq1;
	else if(vrc6_apu.speed == 1)
		vrc6_apu.reloadFreq1 = vrc6_apu.freq1>>4;
	else
		vrc6_apu.reloadFreq1 = vrc6_apu.freq1>>8;
}

static void vrc6UpdateReloadFreq2()
{
	if(vrc6_apu.speed == 0)
		vrc6_apu.reloadFreq2 = vrc6_apu.freq2;
	else if(vrc6_apu.speed == 1)
		vrc6_apu.reloadFreq2 = vrc6_apu.freq2>>4;
	else
		vrc6_apu.reloadFreq2 = vrc6_apu.freq2>>8;
}

static void vrc6UpdateReloadSawFreq()
{
	if(vrc6_apu.speed == 0)
		vrc6_apu.reloadSawFreq = ((vrc6_apu.sawFreq)<<1)+1;
	else if(vrc6_apu.speed == 1)
		vrc6_apu.reloadSawFreq = ((vrc6_apu.sawFreq>>4)<<1)+1;
	else
		vrc6_apu.reloadSawFreq = ((vrc6_apu.sawFreq>>8)<<1)+1;
}

void vrc6AudioSet8_9XX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.p1Vol = val&0xF;
	vrc6_apu.p1Duty = (val>>4)&7;
	vrc6_apu.p1const = ((val&0x80) != 0);
}

void vrc6AudioSet8_9XX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.freq1 = ((vrc6_apu.freq1&~0xFF) | val);
	vrc6UpdateReloadFreq1();
}

void vrc6AudioSet8_9XX2(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.freq1 = (vrc6_apu.freq1&0xFF) | ((val&0xF)<<8);
	vrc6UpdateReloadFreq1();
	//duty cycle starts from beginning when channel gets enabled
	if(!vrc6_apu.p1enable && ((val&0x80) != 0))
		vrc6_apu.p1Cycle = 0;
	vrc6_apu.p1enable = ((val&0x80) != 0);
}

void vrc6AudioSet8_9XX3(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.halt = ((val&1) != 0);
	if((val&6) == 0) vrc6_apu.speed = 0;
	if((val&2) != 0) vrc6_apu.speed = 1;
	if((val&4) != 0) vrc6_apu.speed = 2;
	vrc6UpdateReloadFreq1();
	vrc6UpdateReloadFreq2();
	vrc6UpdateReloadSawFreq();
}

void vrc6AudioSet8_AXX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.p2Vol = val&0xF;
	vrc6_apu.p2Duty = (val>>4)&7;
	vrc6_apu.p2const = ((val&0x80) != 0);
}

void vrc6AudioSet8_AXX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.freq2 = ((vrc6_apu.freq2&~0xFF) | val);
	vrc6UpdateReloadFreq2();
}

void vrc6AudioSet8_AXX2(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.freq2 = (vrc6_apu.freq2&0xFF) | ((val&0xF)<<8);
	vrc6UpdateReloadFreq2();
	//duty cycle starts from beginning when channel gets enabled
	if(!vrc6_apu.p2enable && ((val&0x80) != 0))
		vrc6_apu.p2Cycle = 0;
	vrc6_apu.p2enable = ((val&0x80) != 0);
}

void vrc6AudioSet8_BXX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.sawAdd = (val&0x3F);
}

void vrc6AudioSet8_BXX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.sawFreq = ((vrc6_apu.sawFreq&~0xFF) | val);
	vrc6UpdateReloadSawFreq();
}

void vrc6AudioSet8_BXX2(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6_apu.sawFreq = (vrc6_apu.sawFreq&0xFF) | ((val&0xF)<<8);
	vrc6UpdateReloadSawFreq();
	//duty cycle starts from beginning when channel gets enabled
	if(!vrc6_apu.sawenable && ((val&0x80) != 0))
	{
		vrc6_apu.sawCycle = 0;
		vrc6_apu.sawVol = 0;
	}
	vrc6_apu.sawenable = ((val&0x80) != 0);
}
