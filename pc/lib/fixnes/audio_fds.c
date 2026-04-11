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
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"

//used externally
extern uint8_t audioExpansion;
uint8_t fdsOut;

static struct {
	uint8_t wave[0x40];
	uint8_t modulation[0x20];
	uint8_t curModPos;
	uint8_t curWave;
	uint8_t envSpeed, volEnvSpeed, sweepSpeed;
	uint8_t volEnvGain, volEnvMode;
	uint8_t sweepModGain, sweepMode;
	uint8_t masterVol;
	uint8_t tickCnt;
	int8_t modCounter;
	uint16_t freq, modFreq;
	uint32_t curMasterClock;
	uint16_t curModClock;
	uint32_t volEnvClock, sweepClock, curVolEnvClock, curSweepClock;
	bool masterEnable;
	bool volEnvEnabled;
	bool envMasterEnable;
	bool sweepEnabled;
	bool modEnabled;
	bool modForce;
	bool wavWrite;
} fds_apu;

static void fdsUpdateClockRates()
{
	fds_apu.volEnvClock = 8 * (fds_apu.envSpeed + 1) * (fds_apu.volEnvSpeed + 1);
	fds_apu.sweepClock = 8 * (fds_apu.envSpeed + 1) * (fds_apu.sweepSpeed + 1);
}

void fdsAudioInit()
{
	memset(fds_apu.wave, 0, 0x40);
	memset(fds_apu.modulation, 0, 0x20);
	audioExpansion |= EXP_FDS;
	fdsOut = 0;
	fds_apu.curModPos = 0;
	fds_apu.curWave = 0;
	fds_apu.envSpeed = 0xE8; //from FDS BIOS
	fds_apu.volEnvSpeed = 0, fds_apu.volEnvGain = 0, fds_apu.volEnvMode = 0;
	fds_apu.sweepSpeed = 0, fds_apu.sweepModGain = 0, fds_apu.sweepMode = 0;
	fdsUpdateClockRates();
	fds_apu.masterVol = 0;
	fds_apu.tickCnt = 0;
	fds_apu.modCounter = 0;
	fds_apu.freq = 0, fds_apu.modFreq = 0;
	fds_apu.curMasterClock = 0;
	fds_apu.curModClock = 0;
	fds_apu.curVolEnvClock = fds_apu.volEnvClock;
	fds_apu.curSweepClock = fds_apu.sweepClock;
	fds_apu.masterEnable = false;
	fds_apu.volEnvEnabled = false;
	fds_apu.envMasterEnable = false;
	fds_apu.sweepEnabled = false;
	fds_apu.modEnabled = false;
	fds_apu.modForce = false;
	fds_apu.wavWrite = false;
}

FIXNES_NOINLINE void fdsAudioCycle()
{
	if(fds_apu.wavWrite)
		return;
	uint8_t fdsCurVol = fds_apu.volEnvGain;
	if(fdsCurVol > 0x20) //clamp output
		fdsCurVol = 0x20;
	uint16_t tmp = (fds_apu.curWave&0x3F)*fdsCurVol;
	if(fds_apu.masterVol == 1)
		tmp = tmp*20/30;
	else if(fds_apu.masterVol == 2)
		tmp = tmp*15/30;
	else if(fds_apu.masterVol == 3)
		tmp = tmp*12/30;
	fdsOut = (tmp>>5)&0x3F;
}

static void fdsDoEnv()
{
	if(fds_apu.volEnvEnabled)
	{
		if(fds_apu.curVolEnvClock)
			fds_apu.curVolEnvClock--;
		else
		{		
			fds_apu.curVolEnvClock = fds_apu.volEnvClock;
			//do env stuff
			if(fds_apu.volEnvMode == 1)
			{
				if(fds_apu.volEnvGain < 0x20)
					fds_apu.volEnvGain++;
			}
			else
			{
				if(fds_apu.volEnvGain > 0)
					fds_apu.volEnvGain--;
			}
		}
	}

	if(fds_apu.sweepEnabled)
	{
		if(fds_apu.curSweepClock)
			fds_apu.curSweepClock--;
		else
		{
			fds_apu.curSweepClock = fds_apu.sweepClock;
			//do sweep stuff
			if(fds_apu.sweepMode == 1)
			{
				if(fds_apu.sweepModGain < 0x20)
					fds_apu.sweepModGain++;
			}
			else
			{
				if(fds_apu.sweepModGain > 0)
					fds_apu.sweepModGain--;
			}
		}
	}
}

void fdsAudioClockTimers()
{
	if(!fds_apu.envMasterEnable || !fds_apu.envSpeed)
		return;
	fdsDoEnv();
	//when master is off but envs on, envs runs 4x faster
	if(!fds_apu.masterEnable)
	{
		fdsDoEnv();
		fdsDoEnv();
		fdsDoEnv();
	}
}

//mostly follows logic of http://forums.nesdev.com/viewtopic.php?p=232662#p232662
FIXNES_NOINLINE void fdsAudioMasterUpdate()
{
	if(!fds_apu.masterEnable) //when master is off, keep timer locked
		fds_apu.tickCnt = 0;
	else if((fds_apu.tickCnt&0xF) == 0) //do updates on counter wrap
	{
		//see if mod is enabled
		if(fds_apu.modEnabled)
		{
			fds_apu.curModClock += fds_apu.modFreq;
			//see if real overflow or force bit was set
			if(fds_apu.curModClock&(~0xFFF) || fds_apu.modForce)
			{
				fds_apu.curModClock &= 0xFFF;
				//do mod stuff
				switch((fds_apu.modulation[fds_apu.curModPos>>1]))
				{
					case 1:
						fds_apu.modCounter++;
						break;
					case 2:
						fds_apu.modCounter += 2;
						break;
					case 3:
						fds_apu.modCounter += 4;
						break;
					case 4:
						fds_apu.modCounter = 0;
						break;
					case 5:
						fds_apu.modCounter -= 4;
						break;
					case 6:
						fds_apu.modCounter -= 2;
						break;
					case 7:
						fds_apu.modCounter -= 1;
						break;
					default:
						break;
				}
				if(fds_apu.modCounter & 0x40) //7-bit signed
					fds_apu.modCounter |= 0x80;
				else
					fds_apu.modCounter &= ~0x80;
				//move along mod pos AFTER handling the overflow
				fds_apu.curModPos++; fds_apu.curModPos &= 0x3F;
			}
		}
		//update master always
		int16_t temp = fds_apu.modCounter * fds_apu.sweepModGain;
		if((temp & 0x0f) && !(temp & 0x800))
			temp += 0x20;
		temp += 0x400;
		uint8_t multi = (temp >> 4);
		//add change to accumulator and update wave
		fds_apu.curMasterClock += fds_apu.freq * multi;
		fds_apu.curMasterClock &= 0xFFFFFF; //24-bit overall
		fds_apu.curWave = fds_apu.wave[fds_apu.curMasterClock>>18];
	}
	fds_apu.tickCnt++;
}

void fdsAudioSet8(uint16_t addr, uint8_t val)
{
	switch(addr&0xF)
	{
		case 0:
			fds_apu.volEnvEnabled = ((val&0x80) == 0);
			fds_apu.volEnvMode = ((val&0x40) != 0);
			fds_apu.volEnvSpeed = val&0x3F; //always set speed
			if(!fds_apu.volEnvEnabled) //only set gain when unit is disabled
				fds_apu.volEnvGain = val&0x3F;
			fdsUpdateClockRates(); //always resets clock
			fds_apu.curVolEnvClock = fds_apu.volEnvClock;
			break;
		case 2:
			fds_apu.freq = ((fds_apu.freq&~0xFF) | val);
			break;
		case 3:
			fds_apu.masterEnable = ((val&0x80) == 0);
			fds_apu.freq = (fds_apu.freq&0xFF) | ((val&0xF)<<8);
			if(!fds_apu.masterEnable)
			{
				//disabling resets clock and wave pos
				fds_apu.curMasterClock = 0;
				fds_apu.curWave = fds_apu.wave[0];
			}
			fds_apu.envMasterEnable = ((val&0x40) == 0);
			if(!fds_apu.envMasterEnable)
			{
				//disabling resets both env clocks
				fds_apu.curVolEnvClock = fds_apu.volEnvClock;
				fds_apu.curSweepClock = fds_apu.sweepClock;
			}
			break;
		case 4:
			fds_apu.sweepEnabled = ((val&0x80) == 0);
			fds_apu.sweepMode = ((val&0x40) != 0);
			fds_apu.sweepSpeed = val&0x3F; //always set speed
			if(!fds_apu.sweepEnabled) //only set gain when unit is disabled
				fds_apu.sweepModGain = val&0x3F;
			fdsUpdateClockRates(); //always resets clock
			fds_apu.curSweepClock = fds_apu.sweepClock;
			break;
		case 5:
			fds_apu.modCounter = (val&0x7F);
			if(val&0x40) //7-bit signed
				fds_apu.modCounter |= 0x80;
			else
				fds_apu.modCounter &= ~0x80;
			break;
		case 6:
			fds_apu.modFreq = ((fds_apu.modFreq&~0xFF) | val);
			break;
		case 7:
			fds_apu.modEnabled = ((val&0x80) == 0);
			fds_apu.modForce = ((val&0x40) != 0);
			fds_apu.modFreq = (fds_apu.modFreq&0xFF) | ((val&0xF)<<8);
			if(!fds_apu.modEnabled)
			{
				//disabling resets clock 
				fds_apu.curModClock = 0;
				//clears lower bit of this too
				fds_apu.curModPos &= ~1;
			}
			break;
		case 8:
			if(!fds_apu.modEnabled)
			{
				fds_apu.modulation[fds_apu.curModPos>>1] = val&7;
				fds_apu.curModPos += 2; fds_apu.curModPos &= 0x3F;
			}
			break;
		case 9:
			fds_apu.wavWrite = ((val&0x80) != 0);
			fds_apu.masterVol = val&3;
			break;
		case 0xA:
			fds_apu.envSpeed = val;
			fdsUpdateClockRates();
			break;
		default:
			break;
	}
}

uint8_t fdsAudioGetReg90(uint16_t addr)
{
	(void)addr;
	return fds_apu.volEnvGain|0x40;
}

uint8_t fdsAudioGetReg92(uint16_t addr)
{
	(void)addr;
	return fds_apu.sweepModGain|0x40;
}


void fdsAudioSetWave(uint16_t addr, uint8_t val)
{
	if(!fds_apu.wavWrite)
		return;
	fds_apu.wave[addr&0x3F] = val;
}

uint8_t fdsAudioGetWave(uint16_t addr)
{
	return fds_apu.wave[addr&0x3F];
}
