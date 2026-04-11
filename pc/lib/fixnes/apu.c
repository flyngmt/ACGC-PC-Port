/*
 * Copyright (C) 2017 - 2020 FIX94
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
#include "audio_fds.h"
#include "audio_mmc5.h"
#include "audio_vrc6.h"
#include "audio_vrc7.h"
#include "audio_n163.h"
#include "audio_s5b.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"

#define P1_ENABLE (1<<0)
#define P2_ENABLE (1<<1)
#define TRI_ENABLE (1<<2)
#define NOISE_ENABLE (1<<3)
#define DMC_ENABLE (1<<4)

#define PULSE_CONST_V (1<<4)
#define PULSE_HALT_LOOP (1<<5)

#define TRI_HALT_LOOP (1<<7)

#define DMC_HALT_LOOP (1<<6)
#define DMC_IRQ_ENABLE (1<<7)

static struct {
	uint8_t reg[0x18];
	uint32_t BufSize;
	uint32_t BufSizeBytes;
	uint32_t curBufPos;
	uint32_t Frequency;
	uint16_t freq1;
	uint16_t freq2;
	uint16_t triFreq;
	uint16_t noiseFreq;
	uint16_t noiseShiftReg;
	uint16_t dmcFreq;
	uint16_t dmcAddr, dmcLen;
	uint16_t dmcCurAddr, dmcCurLen;
	uint8_t p1LengthCtr, p2LengthCtr, noiseLengthCtr;
	uint8_t triLengthCtr, triLinearCtr, triCurLinearCtr;
	uint8_t dmcVol, dmcCurVol;
	uint8_t dmcSampleRemain;
	uint8_t dmcSampleBuf, dmcCpuBuf;
	uint8_t irq;
	bool mode5;
	uint8_t modePos;
	uint16_t modeCurCtr;
	uint16_t p1freqCtr, p2freqCtr, triFreqCtr, noiseFreqCtr, dmcFreqCtr;
	uint8_t p1Cycle, p2Cycle, triCycle;
	bool p1haltloop, p2haltloop, trihaltloop, noisehaltloop, dmchaltloop;
	bool dmcenabled;
	bool dmcready;
	bool dmcirqenable;
	bool trireload;
	bool noiseMode1;
	bool enable_irq;
	envelope_t p1Env, p2Env, noiseEnv;
	sweep_t p1Sweep, p2Sweep;
	#if AUDIO_FLOAT
	float pulseLookupTbl[32];
	float tndLookupTbl[204];
	float lpVal;
	float hpVal;
	float *OutBuf;
	float lastHPOut;
	float lastLPOut;
	float *ampVol;
	#else
	int32_t pulseLookupTbl[32];
	int32_t tndLookupTbl[204];
	int32_t lpVal;
	int32_t hpVal;
	int16_t *OutBuf;
	int32_t lastHPOut;
	int32_t lastLPOut;
	int32_t *ampVol;
	#endif

	#if FAKE_STEREO
	uint32_t DelaySize;
	uint32_t DelaySizeBytes;
	uint32_t DelayCnt;
	#if AUDIO_FLOAT
	float *DelayBuf;
	#else
	int16_t *DelayBuf;
	#endif
	#endif

	const uint16_t *dmcPeriod, *noisePeriod;
	const uint16_t *mode4Ctr, *mode5Ctr;
	bool mode_change;
	bool new_mode5;
	uint8_t vrc7Clock;
	uint8_t apuClock;
	uint8_t p1Out;
	uint8_t p2Out;
	uint8_t triOut;
	uint8_t noiseOut;

	const uint8_t *p1seq;
	const uint8_t *p2seq;
	const uint8_t *lengthLookupTbl;
	const uint8_t *triSeq;

	bool waitForRefill;
} apu;

#if AUDIO_FLOAT
static float APU_ampVol[7] = { 2.0f, 1.75f, 1.5f, 1.2f, 1.0f, 0.85f, 0.75f };
#else
static int32_t APU_ampVol[7] = { 128, 112, 96, 77, 64, 55, 48 };
#endif

//used externally
const uint8_t lengthLookupTbl[0x20] = {
	10,254, 20,  2, 40,  4, 80,  6, 160,  8, 60, 10, 14, 12, 26, 14,
	12, 16, 24, 18, 48, 20, 96, 22, 192, 24, 72, 26, 16, 28, 32, 30
};

//used externally
const uint8_t pulseSeqs[4][8] = {
	{ 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 0, 0, 0 },
	{ 1, 0, 0, 1, 1, 1, 1, 1 },
};

static const uint8_t triSeq[32] = {
	15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
};

static const uint16_t noisePeriodNtsc[16] = {
	4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068,
};

static const uint16_t noisePeriodPal[16] = {
	4, 8, 14, 30, 60, 88, 118, 148, 188, 236, 354, 472, 708,  944, 1890, 3778,
};

static const uint16_t dmcPeriodNtsc[16] = {
	428, 380, 340, 320, 286, 254, 226, 214, 190, 160, 142, 128, 106,  84,  72,  54,
};

static const uint16_t dmcPeriodPal[16] = {
	398, 354, 316, 298, 276, 236, 210, 198, 176, 148, 132, 118, 98, 78, 66, 50,
};

//used externally
const uint16_t mode4CtrNtsc[6] = {
	7456, 7458, 7457, 1, 1, 7457
};
const uint16_t mode4CtrPal[6] = {
	8314, 8312, 8313, 1, 1, 8313
};

static const uint16_t mode5CtrNtsc[6] = {
	1, 7457, 7456, 7458, 7458, 7452
};

static const uint16_t mode5CtrPal[6] = {
	1, 8313, 8314, 8312, 8314, 8312
};

extern uint8_t interrupt;

#define M_2_PI 6.28318530717958647692

extern bool fdsMasterEnable;
extern uint32_t vrc7CycleTimer;

extern bool nesPAL;
uint8_t audioExpansion;
void apuInitBufs()
{
	apu.noisePeriod = nesPAL ? noisePeriodPal : noisePeriodNtsc;
	apu.dmcPeriod = nesPAL ? dmcPeriodPal : dmcPeriodNtsc;
	apu.mode4Ctr = nesPAL ? mode4CtrPal : mode4CtrNtsc;
	apu.mode5Ctr = nesPAL ? mode5CtrPal : mode5CtrNtsc;
	apu.lengthLookupTbl = lengthLookupTbl;
	apu.triSeq = triSeq;
	apu.ampVol = APU_ampVol;
	//effective frequencies for 50.000Hz and 60.000Hz Video out
	//apu.Frequency = nesPAL ? 831187 : 893415;
	//effective frequencies for Original PPU Video out
	//apu.Frequency = nesPAL ? 831303 : 894886;
#if AUDIO_LOWERFREQ
	apu.Frequency = nesPAL ? 51956 : 55930;
#else
	apu.Frequency = nesPAL ? 207825 : 223721;
#endif
	audioExpansion = 0;
	double dt = 1.0/((double)apu.Frequency);
	//LP at 22kHz
	double rc = 1.0/(M_2_PI * 22000.0);
#if AUDIO_FLOAT
	apu.lpVal = dt / (rc + dt);
#else
	//convert to 32bit int for calcs later
	apu.lpVal = (int32_t)((dt / (rc + dt))*32768.0);
#endif
	//HP at 40Hz
	rc = 1.0/(M_2_PI * 40.0);
#if AUDIO_FLOAT
	apu.hpVal = rc / (rc + dt);
#else
	//convert to 32bit int for calcs later
	apu.hpVal = (int32_t)((rc / (rc + dt))*32768.0);
#endif
	//just have something larger than 1 frame
	//to hold changing data size
	apu.BufSize = apu.Frequency/30*2;
#if AUDIO_FLOAT
	apu.BufSizeBytes = apu.BufSize*sizeof(float);
	apu.OutBuf = (float*)malloc(apu.BufSizeBytes);
	printf("Audio: 32-bit Float Output at %iHz\n", apu.Frequency);
#else
	apu.BufSizeBytes = apu.BufSize*sizeof(int16_t);
	apu.OutBuf = (int16_t*)malloc(apu.BufSizeBytes);
	printf("Audio: 16-bit Short Output at %iHz\n", apu.Frequency);
#endif
	//extra delay
#if FAKE_STEREO
	apu.DelaySize = apu.Frequency/125; //8ms
	apu.DelayCnt = 0;
#if AUDIO_FLOAT
	apu.DelaySizeBytes = apu.DelaySize*sizeof(float);
	apu.DelayBuf = (float*)malloc(apu.DelaySizeBytes);
#else
	apu.DelaySizeBytes = apu.DelaySize*sizeof(int16_t);
	apu.DelayBuf = (int16_t*)malloc(apu.DelaySizeBytes);
#endif
	memset(apu.DelayBuf, 0, apu.DelaySizeBytes);
	printf("Audio: Enabled Fake Stereo Delay of 8ms\n");
#endif
	/* https://wiki.nesdev.com/w/index.php/APU_Mixer#Lookup_Table */
	uint8_t i;
#if AUDIO_FLOAT
	for(i = 0; i < 32; i++)
		apu.pulseLookupTbl[i] = (95.52 / ((8128.0 / i) + 100));
	for(i = 0; i < 204; i++)
		apu.tndLookupTbl[i] = (163.67 / ((24329.0 / i) + 100));
#else
	for(i = 0; i < 32; i++)
		apu.pulseLookupTbl[i] = (int32_t)((95.52 / ((8128.0 / i) + 100))*32768.0);
	for(i = 0; i < 204; i++)
		apu.tndLookupTbl[i] = (int32_t)((163.67 / ((24329.0 / i) + 100))*32768.0);
#endif
}

void apuDeinitBufs()
{
	if(apu.OutBuf)
		free(apu.OutBuf);
	apu.OutBuf = NULL;
#if FAKE_STEREO
	if(apu.DelayBuf)
		free(apu.DelayBuf);
	apu.DelayBuf = NULL;
#endif
}

void apuInit()
{
	memset(apu.reg,0,0x18);
	memset(apu.OutBuf, 0, apu.BufSizeBytes);
	apu.curBufPos = 0;

	apu.freq1 = 0; apu.freq2 = 0; apu.triFreq = 0; apu.noiseFreq = apu.noisePeriod[0]-1, apu.dmcFreq = apu.dmcPeriod[0]-1;
	apu.noiseShiftReg = 1;
	apu.p1LengthCtr = 0; apu.p2LengthCtr = 0;
	apu.noiseLengthCtr = 0;	apu.triLengthCtr = 0;
	apu.triLinearCtr = 0; apu.triCurLinearCtr = 0;
	//make sure to properly init dmc values
	apu.dmcAddr = 0xC000, apu.dmcLen = 1, apu.dmcVol = 0;
	apu.dmcSampleBuf = 0; apu.dmcCpuBuf = 0;
	apu.dmcCurAddr = 0, apu.dmcCurLen = 0; apu.dmcCurVol = 0;
	apu.dmcSampleRemain = 0;
	apu.irq = 0;
	apu.p1freqCtr = 0; apu.p2freqCtr = 0; apu.triFreqCtr = 0, apu.noiseFreqCtr = 0, apu.dmcFreqCtr = 0;
	apu.p1Cycle = 0; apu.p2Cycle = 0; apu.triCycle = 0;

	memset(&apu.p1Env,0,sizeof(envelope_t));
	memset(&apu.p2Env,0,sizeof(envelope_t));
	memset(&apu.noiseEnv,0,sizeof(envelope_t));

	memset(&apu.p1Sweep,0,sizeof(sweep_t));
	apu.p1Sweep.chan1 = true; //for negative sweep
	memset(&apu.p2Sweep,0,sizeof(sweep_t));
	apu.p2Sweep.chan1 = false;

	apu.p1haltloop = false;	apu.p2haltloop = false;
	apu.trihaltloop = false; apu.noisehaltloop = false;
	apu.dmcenabled = false;
	apu.dmcready = false;
	apu.dmcirqenable = false;
	apu.trireload = false;
	apu.noiseMode1 = false;
	//4017 starts out as 0, so enable
	apu.enable_irq = true;
	apu.mode_change = false;
	apu.new_mode5 = false;
	apu.vrc7Clock = 1;
	apu.apuClock = 0;

	apu.mode5 = false;
	apu.modePos = 5;
	apu.modeCurCtr = nesPAL ? 8315 : 7459;

	apu.p1seq = pulseSeqs[0];
	apu.p2seq = pulseSeqs[1];
}
void apuWriteDMCBuf(uint8_t val)
{
	apu.dmcready = true;
	apu.dmcCpuBuf = val;
	apu.dmcCurAddr++;
	if(!apu.dmcCurLen)
	{
		if(apu.dmchaltloop)
		{
			apu.dmcCurAddr = apu.dmcAddr;
			apu.dmcCurLen = apu.dmcLen;
		}
		else if(apu.dmcirqenable)
		{
			//printf("DMC IRQ\n");
			interrupt |= DMC_IRQ;
		}
	}
}

extern bool cpu_odd_cycle;

FIXNES_NOINLINE static void apuChangeMode()
{
	if(!cpu_odd_cycle)
		return;
	apu.mode_change = false;
	apu.mode5 = apu.new_mode5;
	apu.modePos = 5;
	if(apu.mode5)
		apu.modeCurCtr = 1;
	else
		apu.modeCurCtr = nesPAL ? 8315 : 7459;
}


void doEnvelopeLogic(envelope_t *env)
{
	if(env->start)
	{
		env->start = false;
		env->divider = env->vol;
		env->decay = 15;
	}
	else
	{
		if(env->divider == 0)
		{
			env->divider = env->vol;
			if(env->decay == 0)
			{
				if(env->loop)
					env->decay = 15;
			}
			else
				env->decay--;
		}
		else
			env->divider--;
	}
	//too slow on its own?
	//env->envelope = (env->constant ? env->vol : env->decay);
}

static void sweepUpdateFreq(sweep_t *sw, uint16_t *freq)
{
	//any freq update causes target freq update
	sw->targetFreq = *freq;
	if(sw->targetFreq >= 8)
	{
		if(sw->negative)
		{
			sw->targetFreq -= (sw->targetFreq >> sw->shift);
			if(sw->chan1 == true) sw->targetFreq--;
		}
		else
			sw->targetFreq += (sw->targetFreq >> sw->shift);
		if(sw->targetFreq <= 0x7FF)
			sw->mute = false;
		else //larger than freq register
			sw->mute = true;
	}
	else //any input < 8 gets muted
		sw->mute = true;
}

static void doSweepLogic(sweep_t *sw, uint16_t *freq)
{
	if(sw->divider == 0)
	{
		if(sw->enabled && sw->shift && !sw->mute)
		{
			*freq = sw->targetFreq;
			sweepUpdateFreq(sw, freq);
		}
		sw->divider = sw->period;
	}
	else
		sw->divider--;
	if(sw->start)
	{
		sw->divider = sw->period;
		sw->start = false;
	}
}

FIXNES_NOINLINE static void apuClockA()
{
	if(apu.p1LengthCtr)
	{
		doSweepLogic(&apu.p1Sweep, &apu.freq1);
		if(!apu.p1haltloop)
			apu.p1LengthCtr--;
	}
	if(apu.p2LengthCtr)
	{
		doSweepLogic(&apu.p2Sweep, &apu.freq2);
		if(!apu.p2haltloop)
			apu.p2LengthCtr--;
	}
	if(apu.triLengthCtr && !apu.trihaltloop)
		apu.triLengthCtr--;
	if(apu.noiseLengthCtr && !apu.noisehaltloop)
		apu.noiseLengthCtr--;
}

FIXNES_NOINLINE static void apuClockB()
{
	if(apu.p1LengthCtr)
		doEnvelopeLogic(&apu.p1Env);
	if(apu.p2LengthCtr)
		doEnvelopeLogic(&apu.p2Env);
	if(apu.noiseLengthCtr)
		doEnvelopeLogic(&apu.noiseEnv);
	if(apu.trireload)
		apu.triCurLinearCtr = apu.triLinearCtr;
	else if(apu.triCurLinearCtr)
		apu.triCurLinearCtr--;
	if(!apu.trihaltloop)
		apu.trireload = false;
}

FIXNES_ALWAYSINLINE void apuCycle()
{
	uint8_t aExp = audioExpansion;
#if AUDIO_LOWERFREQ
	if(!(apu.apuClock&31))
#else
	if(!(apu.apuClock&7))
#endif
	{
		if(apu.p1LengthCtr && (apu.reg[0x15] & P1_ENABLE))
		{
			if(!apu.p1Sweep.mute)
				apu.p1Out = apu.p1seq[apu.p1Cycle] ? (apu.p1Env.constant ? apu.p1Env.vol : apu.p1Env.decay) : 0;
		}
		if(apu.p2LengthCtr && (apu.reg[0x15] & P2_ENABLE))
		{
			if(!apu.p2Sweep.mute)
				apu.p2Out = apu.p2seq[apu.p2Cycle] ? (apu.p2Env.constant ? apu.p2Env.vol : apu.p2Env.decay) : 0;
		}
		if(apu.triLengthCtr && apu.triCurLinearCtr && (apu.reg[0x15] & TRI_ENABLE))
		{
			if(apu.triFreq >= 2)
				apu.triOut = apu.triSeq[apu.triCycle];
		}
		if(apu.noiseLengthCtr && (apu.reg[0x15] & NOISE_ENABLE))
		{
			if(apu.noiseFreq > 0)
				apu.noiseOut = (apu.noiseShiftReg&1) == 0 ? (apu.noiseEnv.constant ? apu.noiseEnv.vol : apu.noiseEnv.decay) : 0;
		}
#if AUDIO_FLOAT
		float curIn = apu.pulseLookupTbl[apu.p1Out + apu.p2Out] + apu.tndLookupTbl[(3*apu.triOut) + (2*apu.noiseOut) + apu.dmcVol];
		uint8_t ampVolPos = 0;
		//very rough still
		if(aExp & EXP_VRC6)
		{
			vrc6AudioCycle();
			curIn += ((float)vrc6Out)*0.008f;
			ampVolPos++;
		}
		if(aExp & EXP_FDS)
		{
			fdsAudioCycle();
			curIn += ((float)fdsOut)*0.00617f;
			ampVolPos++;
		}
		if(aExp & EXP_MMC5)
		{
			mmc5AudioCycle();
			curIn += apu.pulseLookupTbl[mmc5Out]+(mmc5pcm*0.002f);
			ampVolPos++;
		}
		if(aExp & EXP_VRC7)
		{
			curIn += (((float)(vrc7Out>>7))/32768.f);
			ampVolPos++;
		}
		if(aExp & EXP_N163)
		{
			curIn += ((float)n163Out)*0.0008f;
			ampVolPos++;
		}
		if(aExp & EXP_S5B)
		{
			s5BAudioCycle();
			curIn += ((float)s5BOut)/32768.f;
			ampVolPos++;
		}
		//amplify input
		curIn *= apu.ampVol[ampVolPos];
		float curLPout = apu.lastLPOut+(apu.lpVal*(curIn-apu.lastLPOut));
		float curHPOut = apu.hpVal*(apu.lastHPOut+apu.lastLPOut-curLPout);
		//set output
		apu.OutBuf[apu.curBufPos] = curHPOut;
		apu.lastLPOut = curLPout;
		apu.lastHPOut = curHPOut;
#else
		int32_t curIn = apu.pulseLookupTbl[apu.p1Out + apu.p2Out] + apu.tndLookupTbl[(3*apu.triOut) + (2*apu.noiseOut) + apu.dmcVol];
		uint8_t ampVolPos = 0;
		//very rough still
		if(aExp & EXP_VRC6)
		{
			vrc6AudioCycle();
			curIn += ((int32_t)vrc6Out)*262;
			ampVolPos++;
		}
		if(aExp & EXP_FDS)
		{
			fdsAudioCycle();
			curIn += ((int32_t)fdsOut)*202;
			ampVolPos++;
		}
		if(aExp & EXP_MMC5)
		{
			mmc5AudioCycle();
			curIn += apu.pulseLookupTbl[mmc5Out]+(mmc5pcm<<6);
			ampVolPos++;
		}
		if(aExp & EXP_VRC7)
		{
			curIn += vrc7Out>>7;
			ampVolPos++;
		}
		if(aExp & EXP_N163)
		{
			curIn += n163Out*26;
			ampVolPos++;
		}
		if(aExp & EXP_S5B)
		{
			s5BAudioCycle();
			curIn += s5BOut;
			ampVolPos++;
		}
		//amplify input
		curIn *= apu.ampVol[ampVolPos];
		int32_t curOut;
		//gen output
		curOut = apu.lastLPOut+((apu.lpVal*((curIn>>6)-apu.lastLPOut))>>15); //Set Lowpass Output
		curIn = (apu.lastHPOut+apu.lastLPOut-curOut); //Set Highpass Input
		curIn += (curIn>>31)&1; //Add Sign Bit for proper Downshift later
		apu.lastLPOut = curOut; //Save Lowpass Output
		curOut = (apu.hpVal*curIn)>>15; //Set Highpass Output
		apu.lastHPOut = curOut; //Save Highpass Output
		//Save Clipped Highpass Output
		apu.OutBuf[apu.curBufPos] = (curOut > 32767)?(32767):((curOut < -32768)?(-32768):curOut);
#endif
#if FAKE_STEREO //add slight delay for stereo effect
		apu.OutBuf[apu.curBufPos+1] = apu.DelayBuf[apu.DelayCnt];
		apu.DelayBuf[apu.DelayCnt] = apu.OutBuf[apu.curBufPos];
		apu.DelayCnt++;
		apu.DelayCnt%=apu.DelaySize;
#else //just copy same output
		apu.OutBuf[apu.curBufPos+1] = apu.OutBuf[apu.curBufPos];
#endif
		apu.curBufPos+=2;
	}
	apu.apuClock++;

	if(apu.p1freqCtr == 0)
	{
		apu.p1freqCtr = (apu.freq1<<1)+1;
		apu.p1Cycle = (apu.p1Cycle+1)&7;
	}
	else
		apu.p1freqCtr--;

	if(apu.p2freqCtr == 0)
	{
		apu.p2freqCtr = (apu.freq2<<1)+1;
		apu.p2Cycle = (apu.p2Cycle+1)&7;
	}
	else
		apu.p2freqCtr--;

	if(apu.triFreqCtr == 0)
	{
		apu.triFreqCtr = apu.triFreq;
		apu.triCycle = (apu.triCycle+1)&31;
	}
	else
		apu.triFreqCtr--;

	if(apu.noiseFreqCtr == 0)
	{
		apu.noiseFreqCtr = apu.noiseFreq;
		uint8_t cmpBit = apu.noiseMode1 ? (apu.noiseShiftReg>>6)&1 : (apu.noiseShiftReg>>1)&1;
		uint8_t cmpRes = (apu.noiseShiftReg&1)^cmpBit;
		apu.noiseShiftReg >>= 1;
		apu.noiseShiftReg |= cmpRes<<14;
	}
	else
		apu.noiseFreqCtr--;

	if(apu.dmcFreqCtr == 0)
	{
		apu.dmcFreqCtr = apu.dmcFreq;
		if(apu.dmcenabled)
		{
			if(apu.dmcSampleBuf&1)
			{
				if(apu.dmcVol <= 125)
					apu.dmcVol += 2;
			}
			else if(apu.dmcVol >= 2)
				apu.dmcVol -= 2;
			apu.dmcSampleBuf>>=1;
		}
		if(apu.dmcSampleRemain == 0)
		{
			if(apu.dmcready)
			{
				apu.dmcSampleBuf = apu.dmcCpuBuf;
				apu.dmcenabled = true;
				apu.dmcready = false;
			}
			else
				apu.dmcenabled = false;
			apu.dmcSampleRemain = 7;
		}
		else
			apu.dmcSampleRemain--;
	}
	else
		apu.dmcFreqCtr--;
	if(!apu.dmcready && !cpuInDMC_DMA() && apu.dmcCurLen)
	{
		cpuDoDMC_DMA(apu.dmcCurAddr);
		apu.dmcCurLen--;
	}

	if(aExp&EXP_VRC7)
	{
		if(apu.vrc7Clock == vrc7CycleTimer)
		{
			vrc7AudioCycle();
			apu.vrc7Clock = 1;
		}
		else
			apu.vrc7Clock++;
	}
	if(aExp&EXP_FDS)
		fdsAudioMasterUpdate();
	if(aExp&EXP_MMC5)
		mmc5AudioLenCycle();

	if(apu.mode_change)
		apuChangeMode();

	if(apu.modeCurCtr == 0)
	{
		if(apu.modePos == 5)
			apu.modePos = 0;
		else
			apu.modePos++;
		if(apu.mode5 == false)
		{
			apu.modeCurCtr = apu.mode4Ctr[apu.modePos]-1;
			if(apu.modePos == 3 || apu.modePos == 5)
			{
				if(apu.enable_irq)
					apu.irq = 1;
			}
			else
			{
				if(apu.modePos == 1)
					apuClockA();
				else if(apu.modePos == 4)
				{
					apuClockA();
					if(apu.enable_irq)
					{
						apu.irq = 1;
						//actually set for cpu
						interrupt |= APU_IRQ;
					}
				}
				apuClockB();
			}
		}
		else
		{
			apu.modeCurCtr = apu.mode5Ctr[apu.modePos]-1;
			if(apu.modePos != 1 && apu.modePos != 5)
			{
				if(apu.modePos == 0 || apu.modePos == 3)
					apuClockA();
				apuClockB();
			}
		}
	}
	else
		apu.modeCurCtr--;
}

void apuSetReg00(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0] = val;
	apu.p1Env.vol = val&0xF;
	apu.p1seq = pulseSeqs[val>>6];
	apu.p1Env.constant = ((val&PULSE_CONST_V) != 0);
	apu.p1Env.loop = apu.p1haltloop = ((val&PULSE_HALT_LOOP) != 0);
}
void apuSetReg01(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[1] = val;
	//printf("P1 sweep %02x\n", val);
	apu.p1Sweep.enabled = ((val&0x80) != 0);
	apu.p1Sweep.shift = val&7;
	apu.p1Sweep.period = (val>>4)&7;
	apu.p1Sweep.negative = ((val&0x8) != 0);
	apu.p1Sweep.start = true;
	//adjust for new sweep regs
	sweepUpdateFreq(&apu.p1Sweep, &apu.freq1);
}
void apuSetReg02(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[2] = val;
	//printf("P1 time low %02x\n", val);
	apu.freq1 = ((apu.freq1&~0xFF) | val);
	sweepUpdateFreq(&apu.p1Sweep, &apu.freq1);
}
void apuSetReg03(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[3] = val;
	apu.p1Cycle = 0;
	if(apu.reg[0x15] & P1_ENABLE)
		apu.p1LengthCtr = apu.lengthLookupTbl[val>>3];
	apu.freq1 = (apu.freq1&0xFF) | ((val&7)<<8);
	sweepUpdateFreq(&apu.p1Sweep, &apu.freq1);
	//printf("P1 new freq %04x\n", apu.freq1);
	apu.p1Env.start = true;
}
void apuSetReg04(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[4] = val;
	apu.p2Env.vol = val&0xF;
	apu.p2seq = pulseSeqs[val>>6];
	apu.p2Env.constant = ((val&PULSE_CONST_V) != 0);
	apu.p2Env.loop = apu.p2haltloop = ((val&PULSE_HALT_LOOP) != 0);
}
void apuSetReg05(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[5] = val;
	//printf("P2 sweep %02x\n", val);
	apu.p2Sweep.enabled = ((val&0x80) != 0);
	apu.p2Sweep.shift = val&7;
	apu.p2Sweep.period = (val>>4)&7;
	apu.p2Sweep.negative = ((val&0x8) != 0);
	apu.p2Sweep.start = true;
	//adjust for new sweep regs
	sweepUpdateFreq(&apu.p2Sweep, &apu.freq2);
}
void apuSetReg06(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[6] = val;
	//printf("P2 time low %02x\n", val);
	apu.freq2 = ((apu.freq2&~0xFF) | val);
	sweepUpdateFreq(&apu.p2Sweep, &apu.freq2);
}
void apuSetReg07(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[7] = val;
	apu.p2Cycle = 0;
	if(apu.reg[0x15] & P2_ENABLE)
		apu.p2LengthCtr = apu.lengthLookupTbl[val>>3];
	apu.freq2 = (apu.freq2&0xFF) | ((val&7)<<8);
	sweepUpdateFreq(&apu.p2Sweep, &apu.freq2);
	//printf("P2 new freq %04x\n", apu.freq2);
	apu.p2Env.start = true;
}
void apuSetReg08(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[8] = val;
	apu.triLinearCtr = val&0x7F;
	apu.trihaltloop = ((val&TRI_HALT_LOOP) != 0);
}
void apuSetReg0A(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0xA] = val;
	apu.triFreq = ((apu.triFreq&~0xFF) | val);
}
void apuSetReg0B(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0xB] = val;
	if(apu.reg[0x15] & TRI_ENABLE)
		apu.triLengthCtr = apu.lengthLookupTbl[val>>3];
	apu.triFreq = (apu.triFreq&0xFF) | ((val&7)<<8);
	//printf("Tri new freq %04x\n", apu.triFreq);
	apu.trireload = true;
}
void apuSetReg0C(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0xC] = val;
	apu.noiseEnv.vol = val&0xF;
	apu.noiseEnv.constant = ((val&PULSE_CONST_V) != 0);
	apu.noiseEnv.loop = apu.noisehaltloop = ((val&PULSE_HALT_LOOP) != 0);
}
void apuSetReg0E(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0xE] = val;
	apu.noiseMode1 = ((val&0x80) != 0);
	apu.noiseFreq = apu.noisePeriod[val&0xF]-1;
}
void apuSetReg0F(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0xF] = val;
	if(apu.reg[0x15] & NOISE_ENABLE)
		apu.noiseLengthCtr = apu.lengthLookupTbl[val>>3];
	apu.noiseEnv.start = true;
}
void apuSetReg10(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x10] = val;
	//printf("Set 0x10 %02x\n", val);
	apu.dmcFreq = apu.dmcPeriod[val&0xF]-1;
	apu.dmchaltloop = ((val&DMC_HALT_LOOP) != 0);
	apu.dmcirqenable = ((val&DMC_IRQ_ENABLE) != 0);
	//printf("%d\n", apu.dmcirqenable);
	if(!apu.dmcirqenable)
		interrupt &= ~DMC_IRQ;
}
void apuSetReg11(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x11] = val;
	apu.dmcVol = val&0x7F;
}
void apuSetReg12(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x12] = val;
	apu.dmcAddr = 0xC000+(val*64);
}
void apuSetReg13(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x13] = val;
	//printf("Set 0x13 %02x\n", val);
	apu.dmcLen = (val*16)+1;
}
void apuSetReg15(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x15] = val;
	//printf("Set 0x15 %02x\n",val);
	if(!(val & P1_ENABLE))
		apu.p1LengthCtr = 0;
	if(!(val & P2_ENABLE))
		apu.p2LengthCtr = 0;
	if(!(val & TRI_ENABLE))
		apu.triLengthCtr = 0;
	if(!(val & NOISE_ENABLE))
		apu.noiseLengthCtr = 0;
	if(!(val & DMC_ENABLE))
		apu.dmcCurLen = 0;
	else if(apu.dmcCurLen == 0)
	{
		apu.dmcCurAddr = apu.dmcAddr;
		apu.dmcCurLen = apu.dmcLen;
	}
	interrupt &= ~DMC_IRQ;
}
void apuSetReg17(uint16_t addr, uint8_t val)
{
	(void)addr;
	apu.reg[0x17] = val;
	apu.enable_irq = ((val&(1<<6)) == 0);
	if(!apu.enable_irq)
	{
		apu.irq = 0;
		interrupt &= ~APU_IRQ;
	}
	apu.new_mode5 = ((val&(1<<7)) != 0);
	//printf("Set 0x17 %d %d\n", apu.enable_irq, apu.new_mode5);
	apu.mode_change = true;
}

uint8_t apuGetReg15(uint16_t addr)
{
	(void)addr;
	uint8_t intrflags = ((apu.irq<<6) | ((!!(interrupt&DMC_IRQ))<<7));
	uint8_t apuretval = ((apu.p1LengthCtr > 0) | ((apu.p2LengthCtr > 0)<<1) | ((apu.triLengthCtr > 0)<<2) | ((apu.noiseLengthCtr > 0)<<3) | ((apu.dmcCurLen > 0)<<4) | intrflags);
	//printf("Get 0x15 %02x\n",apuretval);
	interrupt &= ~APU_IRQ;
	apu.irq = 0;
	return apuretval;
}

void apuBoot()
{
	apuSetReg15(0x15,0);
	apuSetReg17(0x17,0);
}

void apuReset()
{
	apuSetReg15(0x15,0);
	interrupt &= ~APU_IRQ;
	apu.irq = 0;
	apu.mode_change = true;
}

uint8_t *apuGetBuf()
{
	return (uint8_t*)apu.OutBuf;
}

uint32_t apuGetBufSize()
{
#if AUDIO_FLOAT
	return apu.curBufPos*sizeof(float);
#else
	return apu.curBufPos*sizeof(int16_t);
#endif
}

uint32_t apuGetFrequency()
{
	return apu.Frequency;
}

extern bool emuSkipFrame;
bool apuUpdate()
{
#ifdef __LIBRETRO__
	audioUpdate();
#else
	int updateRes = audioUpdate();
	//printf("%i\n",updateRes);
	if(updateRes == 0)
	{
		emuSkipFrame = false;
		apu.waitForRefill = false;
		return false;
	}
	if(apu.waitForRefill && updateRes < 2)
	{
		apu.waitForRefill = false;
		emuSkipFrame = false;
	}
	else if(!apu.waitForRefill && updateRes > 2)
	{
		emuSkipFrame = true;
		apu.waitForRefill = true;
	}
#endif
	apu.curBufPos = 0;
	return true;
}
