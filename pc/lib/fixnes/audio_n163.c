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
#include "audio_n163.h"
#include "audio.h"
#include "mapper.h"
#include "mem.h"
#include "cpu.h"
#include "apu.h"

//used externally
extern uint8_t audioExpansion;
int16_t n163Out = 0;

static int8_t n163cOut[8];
static uint8_t n163Buf[0x80];
static int8_t n163CurChan;
static uint8_t n163CurAddr;
static uint8_t n163Ctr;
static bool n163_addrInc;

void n163AudioInit()
{
	audioExpansion |= EXP_N163;
	n163Out = 0;
	memset(n163cOut,0,8);
	memset(n163Buf,0,0x80);
	n163CurChan = 7;
	n163CurAddr = 0;
	n163Ctr = 15;
	n163_addrInc = false;
	//printf("n163 Audio Inited!\n");
}

//helper function to get current 4-bit sample
static int8_t n163sample(uint8_t addr)
{
	return (n163Buf[addr>>1] >> ((addr&1)<<2))&0xF;
}

void n163AudioClockTimers()
{
	if(n163Ctr)
		n163Ctr--;
	//every 15 cpu ticks this will be updated
	if(n163Ctr == 0)
	{
		//channel counter
		uint8_t lowestChanEnabled = (~(n163Buf[0x7F]>>4))&7;
		//current channel memory pointer
		uint8_t chn = (n163CurChan<<3) | 0x40;
		//contains wave length and high bits of frequency
		uint8_t cChnByte4 = n163Buf[4|chn];
		//update current channel phase by adding current channel frequency
		uint32_t freq = ((cChnByte4 & 3) << 16) | (n163Buf[2|chn] << 8) | n163Buf[chn];
		uint32_t phase = (n163Buf[5|chn] << 16) | (n163Buf[3|chn] << 8) | n163Buf[1|chn];
		phase = (phase + freq) % ((256 - (cChnByte4 & 0xFC)) << 16); //wrap phase by wave length
		n163Buf[5|chn] = phase >> 16; n163Buf[3|chn] = phase >> 8; n163Buf[1|chn] = phase;
		//generate current channel sample, also keep all channel outs in separate buffers
		//instead of constantly switching outputs (technically inaccurate but sounds better)
		n163cOut[n163CurChan] = (n163sample((phase >> 16) + n163Buf[6|chn]) - 8) * (n163Buf[7|chn] & 0xF);
		//add all channels together into one full output
		n163Out = 0; int8_t i;
		for(i = lowestChanEnabled; i < 8; i++)
			n163Out += n163cOut[i];
		//chan handling done, move to next one
		n163CurChan--;
		if(n163CurChan < lowestChanEnabled)
			n163CurChan = 7;
		//run again in 15 cpu ticks
		n163Ctr = 15;
	}
}

void n163AudioSet8_48XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	//printf("n163AudioSet8_48XX %04x %02x\n", addr, val);
	n163Buf[n163CurAddr] = val;
	if(n163_addrInc)
	{
		n163CurAddr++;
		n163CurAddr&=0x7F;
	}
}

void n163AudioSet8_F8XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	//printf("n163AudioSet8_F8XX %04x %02x\n", addr, val);
	n163CurAddr = val&0x7F;
	n163_addrInc = ((val&0x80)!=0);
}

uint8_t n163AudioGet8_48XX(uint16_t addr)
{
	(void)addr;
	uint8_t val = n163Buf[n163CurAddr];
	if(n163_addrInc)
	{
		n163CurAddr++;
		n163CurAddr&=0x7F;
	}
	return val;
}
