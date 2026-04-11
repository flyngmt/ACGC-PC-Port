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
#include <string.h>
#include <math.h>
#include "audio_s5b.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"
#include "apu.h"

//repeat values for all 16 shapes
static const bool s5b_envRepeatTbl[16] = { 
	false, false, false, false, false, false, false, false,
	true,  false, true,  false, true,  false, true,  false,
};

//used externally
extern uint8_t audioExpansion;
uint16_t s5BOut;

static struct {
	const bool *envRepeatTbl;
	uint16_t volTbl[32];
	//16 shapes, 2x32 steps
	uint8_t envShapeTbl[16][64];

	uint8_t curReg;

	uint16_t freq[3];
	uint16_t freqCtr[3];
	uint16_t vol[3];
	uint8_t cycle[3];
	bool disable[3];
	bool nonoise[3];
	bool env[3];

	uint8_t ctr;

	uint16_t noiseFreq;
	uint16_t noiseFreqCtr;
	uint32_t noiseReg;

	uint32_t envFreq;
	uint32_t envFreqCtr;
	uint8_t envStep;
	uint8_t envShape;
	uint16_t envVol;
	bool envRepeat;
} s5b_apu;

void s5BAudioInit()
{
	audioExpansion |= EXP_S5B;
	s5BOut = 0;
	s5b_apu.curReg = 0xE;

	uint8_t i;
	for(i = 0; i < 3; i++)
	{
		s5b_apu.freq[i] = 0;
		s5b_apu.freqCtr[i] = 0;
		s5b_apu.vol[i] = 0;
		s5b_apu.cycle[i] = 0;
		s5b_apu.disable[i] = true;
		s5b_apu.nonoise[i] = true;
		s5b_apu.env[i] = false;
	}

	s5b_apu.ctr = 0;

	s5b_apu.noiseFreq = 0;
	s5b_apu.noiseFreqCtr = 0;
	s5b_apu.noiseReg = 1;

	s5b_apu.envFreq = 0;
	s5b_apu.envFreqCtr = 0;
	s5b_apu.envStep = 0;
	s5b_apu.envShape = 0;
	s5b_apu.envVol = 0;
	s5b_apu.envRepeatTbl = s5b_envRepeatTbl;
	s5b_apu.envRepeat = false;

	//printf("s5B Audio Inited!\n");
	//build volume LUT
	s5b_apu.volTbl[0] = 0;
	//set max channel volume to 10922 (1/3rd of 32768)
	double conv = 10922.0 / pow(10.0, (1.5*31.0) / 20.0);
	for(i = 1; i < 32; i++)
		s5b_apu.volTbl[i] = pow(10.0, (1.5*i) / 20.0) * conv;
	//build envelope LUT
	for(i = 0; i < 32; i++)
	{
		//envelope shapes step 1
		s5b_apu.envShapeTbl[0x0][i] = s5b_apu.envShapeTbl[0x1][i] = 
		s5b_apu.envShapeTbl[0x2][i] = s5b_apu.envShapeTbl[0x3][i] = 
		s5b_apu.envShapeTbl[0x8][i] = s5b_apu.envShapeTbl[0x9][i] = 
		s5b_apu.envShapeTbl[0xA][i] = s5b_apu.envShapeTbl[0xB][i] = 31-i;
		s5b_apu.envShapeTbl[0x4][i] = s5b_apu.envShapeTbl[0x5][i] = 
		s5b_apu.envShapeTbl[0x6][i] = s5b_apu.envShapeTbl[0x7][i] = 
		s5b_apu.envShapeTbl[0xC][i] = s5b_apu.envShapeTbl[0xD][i] = 
		s5b_apu.envShapeTbl[0xE][i] = s5b_apu.envShapeTbl[0xF][i] = i;
		//envelope shapes step 2
		s5b_apu.envShapeTbl[0x0][i+32] = s5b_apu.envShapeTbl[0x1][i+32] = 
		s5b_apu.envShapeTbl[0x2][i+32] = s5b_apu.envShapeTbl[0x3][i+32] = 
		s5b_apu.envShapeTbl[0x4][i+32] = s5b_apu.envShapeTbl[0x5][i+32] = 
		s5b_apu.envShapeTbl[0x6][i+32] = s5b_apu.envShapeTbl[0x7][i+32] =
		s5b_apu.envShapeTbl[0x9][i+32] = s5b_apu.envShapeTbl[0xF][i+32] = 0;
		s5b_apu.envShapeTbl[0xB][i+32] = s5b_apu.envShapeTbl[0xD][i+32] = 31;
		s5b_apu.envShapeTbl[0x8][i+32] = s5b_apu.envShapeTbl[0xE][i+32] = 31-i;
		s5b_apu.envShapeTbl[0xA][i+32] = s5b_apu.envShapeTbl[0xC][i+32] = i;
	}
}

void s5BAudioClockTimers()
{
	//every 16 cpu ticks this will be updated
	if((s5b_apu.ctr&0xF) == 0)
	{
		uint8_t i;
		for(i = 0; i < 3; i++)
		{
			if(s5b_apu.freqCtr[i])
				s5b_apu.freqCtr[i]--;
			if(s5b_apu.freqCtr[i] == 0)
			{
				s5b_apu.freqCtr[i] = s5b_apu.freq[i];
				s5b_apu.cycle[i]++;
			}
		}
		if(s5b_apu.noiseFreqCtr)
			s5b_apu.noiseFreqCtr--;
		if(s5b_apu.noiseFreqCtr == 0)
		{
			s5b_apu.noiseFreqCtr = s5b_apu.noiseFreq;
			if(s5b_apu.noiseReg&1) s5b_apu.noiseReg ^= 0x24000;
			s5b_apu.noiseReg >>= 1;
		}
		if(s5b_apu.envFreqCtr)
			s5b_apu.envFreqCtr--;
		if(s5b_apu.envFreqCtr == 0)
		{
			s5b_apu.envFreqCtr = s5b_apu.envFreq;
			if(s5b_apu.envStep >= 63)
			{
				if(s5b_apu.envRepeat)
					s5b_apu.envStep = 0;
			}
			else
				s5b_apu.envStep++;
			s5b_apu.envVol = s5b_apu.volTbl[s5b_apu.envShapeTbl[s5b_apu.envShape][s5b_apu.envStep]];
		}
	}
	s5b_apu.ctr++;
}

static inline void _s5BsetChanFreqLow(uint8_t chan, uint8_t val)
{
	s5b_apu.freq[chan] = ((s5b_apu.freq[chan]&0xF00) | val);
}

static inline void _s5BsetChanFreqHigh(uint8_t chan, uint8_t val)
{
	s5b_apu.freq[chan] = (s5b_apu.freq[chan]&0xFF) | ((val&0xF)<<8);
}

static inline void _s5BsetChanVolEnv(uint8_t chan, uint8_t val)
{
	s5b_apu.vol[chan] = (val&0xF) ? (s5b_apu.volTbl[((val&0xF)<<1)+1]) : 0;
	s5b_apu.env[chan] = (val&0x10);
}

void s5BAudioSet8_C000(uint16_t addr, uint8_t val)
{
	(void)addr;
	s5b_apu.curReg = val&0xF;
}


void s5BAudioSet8_E000(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(s5b_apu.curReg)
	{
		case 0x0:
			_s5BsetChanFreqLow(0, val);
			break;
		case 0x1:
			_s5BsetChanFreqHigh(0, val);
			break;
		case 0x2:
			_s5BsetChanFreqLow(1, val);
			break;
		case 0x3:
			_s5BsetChanFreqHigh(1, val);
			break;
		case 0x4:
			_s5BsetChanFreqLow(2, val);
			break;
		case 0x5:
			_s5BsetChanFreqHigh(2, val);
			break;
		case 0x6:
			s5b_apu.noiseFreq = (val&0x1F)<<1;
			break;
		case 0x7:
			s5b_apu.disable[0] = (val&1);
			s5b_apu.disable[1] = (val&2);
			s5b_apu.disable[2] = (val&4);
			s5b_apu.nonoise[0] = (val&0x08);
			s5b_apu.nonoise[1] = (val&0x10);
			s5b_apu.nonoise[2] = (val&0x20);
			break;
		case 0x8:
			_s5BsetChanVolEnv(0, val);
			break;
		case 0x9:
			_s5BsetChanVolEnv(1, val);
			break;
		case 0xA:
			_s5BsetChanVolEnv(2, val);
			break;
		case 0xB:
			s5b_apu.envFreq = (s5b_apu.envFreq&0xFF00) | val;
			break;
		case 0xC:
			s5b_apu.envFreq = (s5b_apu.envFreq&0xFF) | (val<<8);
			break;
		case 0xD:
			s5b_apu.envStep = 0;
			s5b_apu.envShape = (val&0xF);
			s5b_apu.envRepeat = s5b_apu.envRepeatTbl[s5b_apu.envShape];
			break;
		default:
			break;
	}
}

FIXNES_NOINLINE void s5BAudioCycle()
{
	uint16_t out = 0;
	uint8_t i;
	for(i = 0; i < 3; i++)
	{
		if((s5b_apu.disable[i] || (s5b_apu.freq[i] && ((s5b_apu.cycle[i])&1))) && (s5b_apu.nonoise[i] || (s5b_apu.noiseFreq && (s5b_apu.noiseReg&1))))
			out += s5b_apu.env[i] ? s5b_apu.envVol : s5b_apu.vol[i];
	}
	s5BOut = out;
}
