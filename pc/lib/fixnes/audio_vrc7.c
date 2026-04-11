/*
 * Copyright (C) 2017 - 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "audio_vrc7.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"
#include "apu.h"

//used externally
extern uint8_t audioExpansion;
int32_t vrc7Out;

#if NUKEDOPLL
#include "opll.h"
static opll_t nukedchip;
static int32_t nukedout;
#else
//https://siliconpr0n.org/archive/doku.php?id=vendor:yamaha:opl2#vrc7_instrument_rom_dump
static const uint8_t vrc7instrumentTbl[16][8] = 
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 
	{ 0x03, 0x21, 0x05, 0x06, 0xE8, 0x81, 0x42, 0x27 }, 
	{ 0x13, 0x41, 0x14, 0x0D, 0xD8, 0xF6, 0x23, 0x12 }, 
	{ 0x11, 0x11, 0x08, 0x08, 0xFA, 0xB2, 0x20, 0x12 }, 
	{ 0x31, 0x61, 0x0C, 0x07, 0xA8, 0x64, 0x61, 0x27 }, 
	{ 0x32, 0x21, 0x1E, 0x06, 0xE1, 0x76, 0x01, 0x28 }, 
	{ 0x02, 0x01, 0x06, 0x00, 0xA3, 0xE2, 0xF4, 0xF4 }, 
	{ 0x21, 0x61, 0x1D, 0x07, 0x82, 0x81, 0x11, 0x07 }, 
	{ 0x23, 0x21, 0x22, 0x17, 0xA2, 0x72, 0x01, 0x17 }, 
	{ 0x35, 0x11, 0x25, 0x00, 0x40, 0x73, 0x72, 0x01 }, 
	{ 0xB5, 0x01, 0x0F, 0x0F, 0xA8, 0xA5, 0x51, 0x02 }, 
	{ 0x17, 0xC1, 0x24, 0x07, 0xF8, 0xF8, 0x22, 0x12 }, 
	{ 0x71, 0x23, 0x11, 0x06, 0x65, 0x74, 0x18, 0x16 }, 
	{ 0x01, 0x02, 0xD3, 0x05, 0xC9, 0x95, 0x03, 0x02 }, 
	{ 0x61, 0x63, 0x0C, 0x00, 0x94, 0xC0, 0x33, 0xF6 }, 
	{ 0x21, 0x72, 0x0D, 0x00, 0xC1, 0xD5, 0x56, 0x06 }, 
};

static const uint8_t vrc7multiTbl[16] = 
{
	1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30
};

typedef struct _vrc7slot_t {
	int32_t rate;
	uint32_t phase;
	int32_t out;
	int32_t out2;
	int32_t fbOut;
	uint32_t levelAtten;
	uint32_t kslAtten;
	uint32_t envPhase;
	int32_t state;
	uint32_t attackRate;
	uint32_t decayRate;
	uint32_t sustainRate;
	uint32_t releaseRate;
	uint32_t sustainLevel;
} vrc7slot_t;

typedef struct _vrc7chan_t {
	vrc7slot_t mod;
	vrc7slot_t carry;
	bool enabled;
	bool s;
	uint16_t freq;
	uint8_t block;
	uint8_t instrument;
	uint8_t v;
} vrc7chan_t;

typedef struct _vrc7Ksr_t
{
	int32_t K;
	int32_t RL;
	int32_t RH;
} vrc7Ksr_t;

enum
{
	vrc7StateIdle = 0,
	vrc7StateAttack,
	vrc7StateDecay,
	vrc7StateSustain,
	vrc7StateRelease
};

#define vrc7MaxAtten (1<<22)
#define attenDb ((double)(1<<22)) / 48.0

static inline int32_t vrc7FromDb(double in)
{
	return (int32_t)(in * attenDb);
}

// LUTs and a lot of code based on this code from Disch:
// http://codepad.org/aAQjWXwJ
static struct {
	uint8_t instrument[16][8];
	uint32_t attackLut[256];
	uint32_t amLut[256];
	double fmLut[256];
	uint32_t sinLut[1024];
	int32_t linearLut[65536];
	int32_t kslLut[0x10];
	const uint8_t *multi;

	vrc7chan_t channel[6];
	vrc7Ksr_t ksr;

	uint32_t amPhase;
	uint32_t amOut;
	uint32_t fmPhase;
	double fmOut;
	uint8_t reg;
} vrc7_apu;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_2PI
#define M_2PI 6.28318530717958647692
#endif

#endif //NUKEDOPLL

void vrc7AudioInit()
{
	audioExpansion |= EXP_VRC7;
	vrc7Out = 0;
#if NUKEDOPLL
	nukedout = 0;
	OPLL_Reset(&nukedchip, opll_type_ds1001);
#else
	vrc7_apu.amPhase = 0; vrc7_apu.amOut = 0; vrc7_apu.fmPhase = 0; vrc7_apu.fmOut = 0; vrc7_apu.reg = 0;
	memset(vrc7_apu.channel, 0, sizeof(vrc7chan_t)*6);

	uint32_t i;
	for(i = 0; i < 16; i++)
		memcpy(vrc7_apu.instrument[i], vrc7instrumentTbl[i], 8);
	vrc7_apu.multi = vrc7multiTbl;

	// Half Sine lut
	for(i = 0; i < 1024; ++i)
	{
		double sinx = sin(M_PI * i / 1024);
		if(!sinx)
			vrc7_apu.sinLut[i] = vrc7MaxAtten;
		else
		{
			sinx = -20.0 * log10(sinx) * attenDb;
			if(sinx > vrc7MaxAtten)
				vrc7_apu.sinLut[i] = vrc7MaxAtten;
			else
				vrc7_apu.sinLut[i] = (uint32_t)(sinx);
		}
	}

	// Ksl Lut
	vrc7_apu.kslLut[0] = vrc7FromDb(0), vrc7_apu.kslLut[1] = vrc7FromDb(18), vrc7_apu.kslLut[2] = vrc7FromDb(24), vrc7_apu.kslLut[3] = vrc7FromDb(27.75),
	vrc7_apu.kslLut[4] = vrc7FromDb(30), vrc7_apu.kslLut[5] = vrc7FromDb(32.25), vrc7_apu.kslLut[6] = vrc7FromDb(33.75), vrc7_apu.kslLut[7] = vrc7FromDb(35.25),
	vrc7_apu.kslLut[8] = vrc7FromDb(36), vrc7_apu.kslLut[9] = vrc7FromDb(37.5), vrc7_apu.kslLut[10] = vrc7FromDb(38.25), vrc7_apu.kslLut[11] = vrc7FromDb(39),
	vrc7_apu.kslLut[12] = vrc7FromDb(39.75), vrc7_apu.kslLut[13] = vrc7FromDb(40.5), vrc7_apu.kslLut[14] = vrc7FromDb(41.25), vrc7_apu.kslLut[15] = vrc7FromDb(42);

	// Attack Lut
	for(i = 0; i < 256; ++i)
	{
		double baselog = log((double)(vrc7MaxAtten >> 14));
		vrc7_apu.attackLut[i] = vrc7FromDb(48) - (uint32_t)(vrc7FromDb(48) * log((double)(i)) / baselog);
	}

	// Linear Lut
	for(i = 0; i < 65536; ++i)
	{
		int32_t outscale = (1 << 20);  // channel output is 20 bits wide
		double inscale = attenDb / (1 << 7);
		double lin = pow(10.0, (i / -20.0 / inscale));
		vrc7_apu.linearLut[i] = (int32_t)(lin * outscale);
	}

	// Am Lut
	for(i = 0; i < 256; ++i)
		vrc7_apu.amLut[i] = (uint32_t)((1.0 + sin(M_2PI * i / 256)) * vrc7FromDb(1.2));

	// Fm Lut
	for(i = 0; i < 256; ++i)
		vrc7_apu.fmLut[i] = pow(2.0, 13.75 / 1200 * sin(M_2PI * i / 256));
#endif //NUKEDOPLL
}


#if NUKEDOPLL
//none of the following functions used in nuked core
#else
void vrc7SetR(vrc7Ksr_t *k, int32_t r)
{
	r = (r * 4) + k->K;
	k->RH = r>>2;
	if(k->RH > 15)
		k->RH = 15;
	k->RL = r&3;
}

static void vrc7CalcSlotVals(vrc7chan_t *chan, vrc7slot_t *slot, uint8_t slotNum)
{
	// Phase Change Rate
	slot->rate = chan->freq * (1 << chan->block) * vrc7_apu.multi[(vrc7_apu.instrument[chan->instrument][slotNum]&0xF)] / 2;

	// Total level
	slot->levelAtten = slotNum ? (chan->v << 2) : (vrc7_apu.instrument[chan->instrument][2] & 0x3F);
	slot->levelAtten = slot->levelAtten * vrc7FromDb(0.75);

	// Sustain level
	slot->sustainLevel = vrc7FromDb(3) * (vrc7_apu.instrument[chan->instrument][6 | slotNum] >> 4);

	// Ksl
	uint8_t kslbits = vrc7_apu.instrument[chan->instrument][2 | slotNum] >> 6;
	if(kslbits)
	{
		int32_t a = vrc7_apu.kslLut[chan->freq >> 5] - vrc7FromDb(6)*(7 - chan->block);
		if(a <= 0)
			slot->kslAtten = 0;
		else
			slot->kslAtten = a >> (3-kslbits);
	}
	else
		slot->kslAtten = 0;

	vrc7_apu.ksr.K = (chan->block << 1) | (chan->freq >> 8);
	if(!(vrc7_apu.instrument[chan->instrument][slotNum] & 0x10)) // if Ksr is "off"
		vrc7_apu.ksr.K >>= 2;

	// bits as written to reg
	slot->attackRate = vrc7_apu.instrument[chan->instrument][4 | slotNum] >> 4;
	slot->decayRate = vrc7_apu.instrument[chan->instrument][4 | slotNum] & 0x0F;
	slot->sustainRate = vrc7_apu.instrument[chan->instrument][6 | slotNum] & 0x0F;
	if(chan->s)
		slot->releaseRate = 5;
	else if(vrc7_apu.instrument[chan->instrument][0 | slotNum] & 0x20)
		slot->releaseRate = slot->sustainRate;
	else
		slot->releaseRate = 7;
	// sustain hold
	if(vrc7_apu.instrument[chan->instrument][0 | slotNum] & 0x20)
		slot->sustainRate = 0;

	// convert
	if(slot->attackRate)
	{
		vrc7SetR(&vrc7_apu.ksr, slot->attackRate);
		if(slot->attackRate < 15)
			slot->attackRate = (3 * (vrc7_apu.ksr.RL+4)) << (vrc7_apu.ksr.RH+1);
		else //rate 15 is like rate 0
			slot->attackRate = 0;
	}
	if(slot->decayRate)
	{
		vrc7SetR(&vrc7_apu.ksr, slot->decayRate);
		slot->decayRate = (vrc7_apu.ksr.RL+4) << (vrc7_apu.ksr.RH-1);
	}
	if(slot->sustainRate)
	{
		vrc7SetR(&vrc7_apu.ksr, slot->sustainRate);
		slot->sustainRate = (vrc7_apu.ksr.RL+4) << (vrc7_apu.ksr.RH-1);
	}
	if(slot->releaseRate)
	{
		vrc7SetR(&vrc7_apu.ksr, slot->releaseRate);
		slot->releaseRate = (vrc7_apu.ksr.RL+4) << (vrc7_apu.ksr.RH-1);
	}
}

static void vrc7KeyOn(vrc7slot_t *slot)
{
	slot->phase = 0;
	slot->envPhase = 0;
	slot->state = vrc7StateAttack;
}

static void vrc7KeyOff(vrc7slot_t *slot)
{
	if(slot->state == vrc7StateAttack)
		slot->envPhase = vrc7_apu.attackLut[(slot->envPhase >> 14) & 0xFF];
	slot->state = vrc7StateRelease;
}

static void vrc7UpdateEnable(vrc7chan_t *chan, vrc7slot_t *slot, uint8_t slotNum, bool wasenabled)
{
	if(chan->enabled && !wasenabled)
		vrc7KeyOn(slot);
	else if(wasenabled && !chan->enabled && slotNum)
		vrc7KeyOff(slot);
}

static uint32_t vrc7Env(vrc7chan_t *chan, vrc7slot_t *slot, uint8_t slotNum)
{
	uint32_t out = 0;

	switch(slot->state)
	{
		case vrc7StateAttack:
			out = vrc7_apu.attackLut[(slot->envPhase >> 14) & 0xFF];
			slot->envPhase += slot->attackRate;
			if(slot->envPhase >= vrc7MaxAtten || (vrc7_apu.instrument[chan->instrument][4 | slotNum] >> 4) == 0xF)
			{
				slot->envPhase = 0;
				slot->state = vrc7StateDecay;
			}
			break;
		case vrc7StateDecay:
			out = slot->envPhase;
			slot->envPhase += slot->decayRate;
			if(slot->envPhase >= slot->sustainLevel)
			{
				slot->envPhase = slot->sustainLevel;
				slot->state = vrc7StateSustain;
			}
			break;
		case vrc7StateSustain:
			out = slot->envPhase;
			slot->envPhase += slot->sustainRate;
			if(slot->envPhase >= vrc7MaxAtten)
				slot->state = vrc7StateIdle;
			break;
		case vrc7StateRelease:
			out = slot->envPhase;
			slot->envPhase += slot->releaseRate;
			if(slot->envPhase >= vrc7MaxAtten)
				slot->state = vrc7StateIdle;
			break;
	}

	if(vrc7_apu.instrument[chan->instrument][slotNum] & 0x80)
		out += vrc7_apu.amOut;

	return out + slot->levelAtten + slot->kslAtten;
}

static int32_t vrc7GetOut(vrc7chan_t *chan, vrc7slot_t *slot, uint8_t slotNum, uint32_t inV)
{
	if(slot->state == vrc7StateIdle)
		return 0;

	slot->out2 = slot->out;
	//mod base
	if(slotNum == 0)
	{
		uint8_t fb = vrc7_apu.instrument[chan->instrument][3] & 7;
		if(fb) inV = (slot->fbOut) >> (8-fb);
	}

	uint32_t env = vrc7Env(chan, slot, slotNum);
	if((vrc7_apu.instrument[chan->instrument][slotNum]&0x40) != 0)
		slot->phase += (uint32_t)(slot->rate / 2 * vrc7_apu.fmOut);
	else
		slot->phase += slot->rate / 2;
	inV += slot->phase;
	env += vrc7_apu.sinLut[(inV>>7)&0x3FF];

	if(env >= vrc7MaxAtten)
		return 0;

	int32_t output = vrc7_apu.linearLut[env>>7];
	int32_t Rectify = (vrc7_apu.instrument[chan->instrument][3] & (0x8 << slotNum)) ? 0 : -1;
	if(inV & (1<<17))
		output *= Rectify;
	slot->out = output;
	slot->fbOut = (slot->out + slot->out2) / 2;
	return slot->fbOut;
}
#endif //NUKEDOPLL

FIXNES_NOINLINE void vrc7AudioCycle()
{
#if NUKEDOPLL
	int32_t tmp[2];
	OPLL_Clock(&nukedchip,tmp);
	nukedout+=tmp[0]; nukedout+=tmp[1];
	if(nukedchip.cycles == 0) //back to start, output
	{
		vrc7Out = nukedout*4096; //amplify out
		nukedout = 0; //reset accumulator
	}
#else
	vrc7Out = 0;
	//update am and fm for all chans
	vrc7_apu.amPhase += 78;
	vrc7_apu.amOut = vrc7_apu.amLut[(vrc7_apu.amPhase >> 12) & 0xFF];
	vrc7_apu.fmPhase += 105;
	vrc7_apu.fmOut = vrc7_apu.fmLut[(vrc7_apu.fmPhase >> 12) & 0xFF];
	//go through all chans and get final out
	uint8_t i;
	for(i = 0; i < 6; i++)
	{
		vrc7chan_t *c = &vrc7_apu.channel[i];
		uint32_t modOut = vrc7GetOut(c, &c->mod, 0, 0);
		int32_t carryOut = vrc7GetOut(c, &c->carry, 1, modOut);
		vrc7Out += carryOut;
	}
#endif //NUKEDOPLL
}

void vrc7AudioSet9010(uint16_t addr, uint8_t val)
{
	(void)addr;
#if NUKEDOPLL
	OPLL_Write(&nukedchip,0,val);
#else
	vrc7_apu.reg = (val&0x3F);
#endif //NUKEDOPLL
}

void vrc7AudioSet9030(uint16_t addr, uint8_t val)
{
	(void)addr;
#if NUKEDOPLL
	OPLL_Write(&nukedchip,1,val);
#else
	if(vrc7_apu.reg < 8)
		vrc7_apu.instrument[0][vrc7_apu.reg] = val;
	else if(vrc7_apu.reg >= 0x10 && vrc7_apu.reg <= 0x15)
	{
		vrc7chan_t *c = &vrc7_apu.channel[vrc7_apu.reg&0xF];
		c->freq &= ~0xFF;
		c->freq |= val;
		vrc7CalcSlotVals(c, &c->mod, 0);
		vrc7CalcSlotVals(c, &c->carry, 1);
	}
	else if(vrc7_apu.reg >= 0x20 && vrc7_apu.reg <= 0x25)
	{
		vrc7chan_t *c = &vrc7_apu.channel[vrc7_apu.reg&0xF];
		c->freq &= 0xFF;
		c->freq |= (val&1)<<8;
		c->block = (val>>1)&7;
		bool prevenabled = c->enabled;
		c->enabled = ((val&0x10) != 0);
		c->s = ((val&0x20) != 0);
		vrc7UpdateEnable(c, &c->mod, 0, prevenabled);
		vrc7UpdateEnable(c, &c->carry, 1, prevenabled);
		vrc7CalcSlotVals(c, &c->mod, 0);
		vrc7CalcSlotVals(c, &c->carry, 1);
	}
	else if(vrc7_apu.reg >= 0x30 && vrc7_apu.reg <= 0x35)
	{
		vrc7chan_t *c = &vrc7_apu.channel[vrc7_apu.reg&0xF];
		c->v = (val&0xF);
		c->instrument = (val>>4)&0xF;
		vrc7CalcSlotVals(c, &c->mod, 0);
		vrc7CalcSlotVals(c, &c->carry, 1);
	}
#endif //NUKEDOPLL
}
