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
#include "../ppu.h"
#include "../cpu.h"
#include "../input.h"
#include "../mapper.h"
#include "../mem.h"
#include "../apu.h"
#include "../ppu.h"
#include "../audio_fds.h"
#include "../audio_vrc6.h"
#include "../audio_vrc7.h"
#include "../audio_mmc5.h"
#include "../audio_n163.h"
#include "../audio_s5b.h"
#include "../mapper_h/common.h"

static struct {
	uint8_t *prgROM;
	uint8_t *prgRAM;
	uint8_t FillRAM[0x8000];
	uint32_t prgROMsize;
	uint32_t prgRAMsize;
	uint32_t InitPRGBank[8];
	uint32_t InitRAMBank[2];
	uint32_t PRGBank[8];
	uint32_t RAMBank[2];
	uint16_t loadAddr;
	uint16_t initAddr;
	uint16_t playAddr;
	uint8_t trackTotal;
	uint8_t curTrack;
	bool bankEnable;
	bool playing;
	bool init;
	uint8_t init_timeout;
	uint8_t MMC5ExRAM[0x400];
	uint8_t mmc5_mul1, mmc5_mul2;
	uint16_t mmc5_mulRes;
	uint8_t prevValReads[8];
} nsf;

extern bool nesPAL;
extern uint8_t audioExpansion;
//used externally
bool nsf_startPlayback;
bool nsf_endPlayback;

static void nsfInitPlayback()
{
	nsf_startPlayback = false;
	nsf_endPlayback = false;
	nsf.playing = false;
	nsf.init = true;
	nsf.init_timeout = 10; //give it a couple frames
	memset(nsf.prgRAM, 0, nsf.prgRAMsize);
	memset(nsf.FillRAM, 0, 0x8000);
	memset(nsf.MMC5ExRAM, 0, 0x400);
	nsf.mmc5_mul1 = 0, nsf.mmc5_mul2 = 0, nsf.mmc5_mulRes = 0;
	memcpy(nsf.PRGBank, nsf.InitPRGBank, 8*sizeof(uint32_t));
	memcpy(nsf.RAMBank, nsf.InitRAMBank, 2*sizeof(uint32_t));
	cpuInitNSF(nsf.initAddr, nsf.curTrack-1, nesPAL ? 1 : 0);
	if(audioExpansion & EXP_VRC6)
		vrc6AudioInit();
	if(audioExpansion & EXP_VRC7)
		vrc7AudioInit();
	if(audioExpansion & EXP_FDS)
		fdsAudioInit();
	if(audioExpansion & EXP_MMC5)
		mmc5AudioInit();
	if(audioExpansion & EXP_N163)
		n163AudioInit();
	if(audioExpansion & EXP_S5B)
		s5BAudioInit();
}

#define onOff(x) (x ? "On" : "Off")

void nsfinit(uint8_t *nsfBIN, uint32_t nsfBINsize, uint8_t *prgRAMin, uint32_t prgRAMsizeIn)
{
	nsf.prgROM = nsfBIN+0x80;
	nsf.prgROMsize = nsfBINsize-0x80;
	nsf.prgRAM = prgRAMin;
	nsf.prgRAMsize = prgRAMsizeIn;
	chr8init(NULL,0); //RAM only
	nsf.loadAddr = ((nsfBIN[0x8])|(nsfBIN[0x9]<<8))&0x7FFF;
	nsf.initAddr = ((nsfBIN[0xA])|(nsfBIN[0xB]<<8));
	nsf.playAddr = ((nsfBIN[0xC])|(nsfBIN[0xD]<<8));
	nesPAL = ((nsfBIN[0x7A]&1) != 0);
	apuInitBufs(); //audioExpansion=0
	//the inits will set audioExpansion
	if(nsfBIN[0x7B] & EXP_VRC6)
		vrc6AudioInit();
	if(nsfBIN[0x7B] & EXP_VRC7)
		vrc7AudioInit();
	if(nsfBIN[0x7B] & EXP_FDS)
		fdsAudioInit();
	if(nsfBIN[0x7B] & EXP_MMC5)
		mmc5AudioInit();
	if(nsfBIN[0x7B] & EXP_N163)
		n163AudioInit();
	if(nsfBIN[0x7B] & EXP_S5B)
		s5BAudioInit();
	nsf.bankEnable = false;
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		nsf.InitPRGBank[i] = (nsfBIN[0x70+i]<<12);
		if(i == 6) nsf.InitRAMBank[0] = nsf.InitPRGBank[i];
		if(i == 7) nsf.InitRAMBank[1] = nsf.InitPRGBank[i];
		if(nsf.InitPRGBank[i] != 0)
			nsf.bankEnable = true;
	}
	if(nsf.bankEnable) nsf.loadAddr &= 0xFFF;
	nsf.trackTotal = nsfBIN[6];
	nsf.curTrack = nsfBIN[7];
	if(nsf.curTrack > nsf.trackTotal)
		nsf.curTrack = 1;
	memset(nsf.prevValReads, 0, 8);
	printf("NSF Player inited in %s Mode (VRC6 %s, VRC7 %s, FDS %s, MMC5 %s, N163 %s, S5B %s) %s banking\n", nesPAL ? "PAL" : "NTSC", 
		onOff(audioExpansion&EXP_VRC6), onOff(audioExpansion&EXP_VRC7), onOff(audioExpansion&EXP_FDS), onOff(audioExpansion&EXP_MMC5),
		onOff(audioExpansion&EXP_N163), onOff(audioExpansion&EXP_S5B), nsf.bankEnable ? "with" : "without");
	if(nsfBIN[0xE] != 0) printf("Playing back %.32s\n", nsfBIN+0xE);
	//printf("Track %i/%i         ", nsf.curTrack, nsf.trackTotal);
	ppuDrawNSFTrackNum(nsf.curTrack, nsf.trackTotal);
	inputInit();
	nsfInitPlayback();
}

static uint32_t nsfgetromAddr(uint16_t addr)
{
	uint32_t romAddr;
	if(nsf.bankEnable)
	{
		switch(addr>>12)
		{
			case 0x6:
				romAddr = nsf.RAMBank[0]+(addr&0xFFF);
				break;
			case 0x7:
				romAddr = nsf.RAMBank[1]+(addr&0xFFF);
				break;
			case 0x8:
				romAddr = nsf.PRGBank[0]+(addr&0xFFF);
				break;
			case 0x9:
				romAddr = nsf.PRGBank[1]+(addr&0xFFF);
				break;
			case 0xA:
				romAddr = nsf.PRGBank[2]+(addr&0xFFF);
				break;
			case 0xB:
				romAddr = nsf.PRGBank[3]+(addr&0xFFF);
				break;
			case 0xC:
				romAddr = nsf.PRGBank[4]+(addr&0xFFF);
				break;
			case 0xD:
				romAddr = nsf.PRGBank[5]+(addr&0xFFF);
				break;
			case 0xE:
				romAddr = nsf.PRGBank[6]+(addr&0xFFF);
				break;
			default: //0xF
				romAddr = nsf.PRGBank[7]+(addr&0xFFF);
				break;
		}
	}
	else
		romAddr = (addr&0x7FFF);
	return romAddr;
}

static uint8_t nsfGetMMC5_5205(uint16_t addr)
{
	(void)addr;
	return (nsf.mmc5_mulRes&0xFF);
}

static uint8_t nsfGetMMC5_5206(uint16_t addr)
{
	(void)addr;
	return (nsf.mmc5_mulRes>>8);
}

static uint8_t nsfGetMMC5_EXRAM(uint16_t addr)
{
	return nsf.MMC5ExRAM[addr&0x3FF];
}

/* Init Loop Routine */
static uint8_t nsfGet_4567(uint16_t addr)
{
	(void)addr;
	return 0x4C; //JMP Absolute
}

static uint8_t nsfGet_4568(uint16_t addr)
{
	(void)addr;
	return 0x67; //low addr, 0x67
}

static uint8_t nsfGet_4569(uint16_t addr)
{
	(void)addr;
	//if(nsf.init)
	//	printf("Init return\n");
	nsf.init = false;
	return 0x45; //high addr, 0x4567
}

/* Play Return Routine */
static uint8_t nsfGet_456A(uint16_t addr)
{
	(void)addr;
	return 0x4C; //JMP Absolute
}

static uint8_t nsfGet_456B(uint16_t addr)
{
	(void)addr;
	return 0x6A; //low addr, 0x6A
}

static uint8_t nsfGet_456C(uint16_t addr)
{
	(void)addr;
	//if(nsf.playing)
	//	printf("Play return\n");
	//will end on next CPU_GET_INSTRUCTION state
	nsf_endPlayback = true;
	nsf.playing = false;
	return 0x45; //high addr, 0x456A
}

static uint8_t nsfGetRAM(uint16_t addr)
{
	return nsf.prgRAM[addr&0x1FFF];
}

static uint8_t nsfGet_Bank(uint16_t addr)
{
	uint8_t aExp = audioExpansion;
	uint8_t val;
	uint32_t romAddr = nsfgetromAddr(addr);
	if(romAddr >= nsf.loadAddr && (romAddr-nsf.loadAddr) < nsf.prgROMsize)
	{
		val = nsf.prgROM[romAddr-nsf.loadAddr];
		//printf("Ret from ROM %04x with %02x\n", romAddr-nsf.loadAddr, val);
		if(addr < 0xE000 && (aExp&EXP_FDS))
			nsf.FillRAM[addr-0x6000] = val;
	}
	else if(addr < 0xE000 && (aExp&EXP_FDS))
		val = nsf.FillRAM[addr-0x6000];
	else //ROM data not available so return 0
		val = 0;
	if((aExp&EXP_MMC5) && addr >= 0x8000 && addr < 0xC000 && mmc5_dmcreadmode)
		mmc5AudioPCMWrite(val);
	return val;
}

void nsfinitGet8(uint16_t addr)
{
	uint8_t aExp = audioExpansion;
	//printf("nsfget8 %04x\n", addr);
	if(addr < 0x6000)
	{
		/* FDS Audio Regs */
		if(aExp&EXP_FDS)
		{
			if(addr >= 0x4040 && addr <= 0x407F)
				memInitMapperGetPointer(addr, fdsAudioGetWave);
			else if(addr == 0x4090)
				memInitMapperGetPointer(addr, fdsAudioGetReg90);
			else if(addr == 0x4092)
				memInitMapperGetPointer(addr, fdsAudioGetReg92);
		}
		/* N163 Regs */
		if(aExp&EXP_N163)
		{
			if(addr >= 0x4800 && addr < 0x5000)
				memInitMapperGetPointer(addr, n163AudioGet8_48XX);
		}
		/* MMC5 Regs */
		if(aExp&EXP_MMC5)
		{
			if(addr >= 0x5000 && addr <= 0x5015)
				memInitMapperGetPointer(addr, mmc5AudioGet8);
			else if(addr == 0x5205)
				memInitMapperGetPointer(addr, nsfGetMMC5_5205);
			else if(addr == 0x5206)
				memInitMapperGetPointer(addr, nsfGetMMC5_5206);
			else if(addr >= 0x5C00 && addr < 0x5FF6)
				memInitMapperGetPointer(addr, nsfGetMMC5_EXRAM);
		}
		if(addr == 0x4567)
			memInitMapperGetPointer(addr, nsfGet_4567);
		else if(addr == 0x4568)
			memInitMapperGetPointer(addr, nsfGet_4568);
		else if(addr == 0x4569)
			memInitMapperGetPointer(addr, nsfGet_4569);
		else if(addr == 0x456A)
			memInitMapperGetPointer(addr, nsfGet_456A);
		else if(addr == 0x456B)
			memInitMapperGetPointer(addr, nsfGet_456B);
		else if(addr == 0x456C)
			memInitMapperGetPointer(addr, nsfGet_456C);
	}
	else 
	{
		if(addr < 0x8000 && (!(aExp&EXP_FDS) || !nsf.bankEnable))
			memInitMapperGetPointer(addr, nsfGetRAM);
		else //does a bunch of rather ugly stuff
			memInitMapperGetPointer(addr, nsfGet_Bank);
	}
}

static void nsfSetMMC5_5205(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.mmc5_mul1 = val;
	nsf.mmc5_mulRes = nsf.mmc5_mul1*nsf.mmc5_mul2;
}

static void nsfSetMMC5_5206(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.mmc5_mul2 = val;
	nsf.mmc5_mulRes = nsf.mmc5_mul1*nsf.mmc5_mul2;
}

static void nsfSetMMC5_EXRAM(uint16_t addr, uint8_t val)
{
	nsf.MMC5ExRAM[addr&0x3FF] = val;
}

static void nsfSetRAMBank0(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.RAMBank[0] = val<<12;
}

static void nsfSetRAMBank1(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.RAMBank[1] = val<<12;
}

static void nsfSetPRGBank0(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[0] = val<<12;
}

static void nsfSetPRGBank1(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[1] = val<<12;
}

static void nsfSetPRGBank2(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[2] = val<<12;
}

static void nsfSetPRGBank3(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[3] = val<<12;
}

static void nsfSetPRGBank4(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[4] = val<<12;
}

static void nsfSetPRGBank5(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[5] = val<<12;
}

static void nsfSetPRGBank6(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[6] = val<<12;
}

static void nsfSetPRGBank7(uint16_t addr, uint8_t val)
{
	(void)addr;
	nsf.PRGBank[7] = val<<12;
}

static void nsfSetRAM(uint16_t addr, uint8_t val)
{
	nsf.prgRAM[addr&0x1FFF] = val;
}

static void nsfSetFillRAM(uint16_t addr, uint8_t val)
{
	nsf.FillRAM[addr-0x6000] = val;
}

void nsfinitSet8(uint16_t addr)
{
	uint8_t aExp = audioExpansion;
	//printf("nsfset8 %04x %02x\n", addr, val);
	if(addr < 0x6000)
	{
		/* FDS Audio Regs */
		if(aExp&EXP_FDS)
		{
			if(addr >= 0x4040 && addr <= 0x407F)
				memInitMapperSetPointer(addr, fdsAudioSetWave);
			else if(addr >= 0x4080 && addr <= 0x408A)
				memInitMapperSetPointer(addr, fdsAudioSet8);
		}
		/* N163 Regs */
		if(aExp&EXP_N163)
		{
			if(addr >= 0x4800 && addr < 0x5000)
				memInitMapperSetPointer(addr, n163AudioSet8_48XX);
		}
		/* MMC5 Regs */
		if(aExp&EXP_MMC5)
		{
			if(addr >= 0x5000 && addr <= 0x5015)
				memInitMapperSetPointer(addr, mmc5AudioSet8);
			else if(addr == 0x5205)
				memInitMapperSetPointer(addr, nsfSetMMC5_5205);
			else if(addr == 0x5206)
				memInitMapperSetPointer(addr, nsfSetMMC5_5206);
			else if(addr >= 0x5C00 && addr < 0x5FF6)
				memInitMapperSetPointer(addr, nsfSetMMC5_EXRAM);
		}
		/* NSF Bank Regs */
		if(addr == 0x5FF6)
			memInitMapperSetPointer(addr, nsfSetRAMBank0);
		else if(addr == 0x5FF7)
			memInitMapperSetPointer(addr, nsfSetRAMBank1);
		else if(addr == 0x5FF8)
			memInitMapperSetPointer(addr, nsfSetPRGBank0);
		else if(addr == 0x5FF9)
			memInitMapperSetPointer(addr, nsfSetPRGBank1);
		else if(addr == 0x5FFA)
			memInitMapperSetPointer(addr, nsfSetPRGBank2);
		else if(addr == 0x5FFB)
			memInitMapperSetPointer(addr, nsfSetPRGBank3);
		else if(addr == 0x5FFC)
			memInitMapperSetPointer(addr, nsfSetPRGBank4);
		else if(addr == 0x5FFD)
			memInitMapperSetPointer(addr, nsfSetPRGBank5);
		else if(addr == 0x5FFE)
			memInitMapperSetPointer(addr, nsfSetPRGBank6);
		else if(addr == 0x5FFF)
			memInitMapperSetPointer(addr, nsfSetPRGBank7);
	}
	else
	{
		if(addr < 0x8000 && (!(aExp&EXP_FDS) || !nsf.bankEnable))
			memInitMapperSetPointer(addr, nsfSetRAM);
		else if((aExp&EXP_N163) && addr >= 0xF800)
			memInitMapperSetPointer(addr, n163AudioSet8_F8XX);
		else if((aExp&EXP_S5B) && addr == 0xC000)
			memInitMapperSetPointer(addr, s5BAudioSet8_C000);
		else if((aExp&EXP_S5B) && addr == 0xE000)
			memInitMapperSetPointer(addr, s5BAudioSet8_E000);
		else if((aExp&EXP_VRC6) && addr == 0x9000)
			memInitMapperSetPointer(addr, vrc6AudioSet8_9XX0);
		else if((aExp&EXP_VRC6) && addr == 0x9001)
			memInitMapperSetPointer(addr, vrc6AudioSet8_9XX1);
		else if((aExp&EXP_VRC6) && addr == 0x9002)
			memInitMapperSetPointer(addr, vrc6AudioSet8_9XX2);
		else if((aExp&EXP_VRC6) && addr == 0x9003)
			memInitMapperSetPointer(addr, vrc6AudioSet8_9XX3);
		else if((aExp&EXP_VRC7) && addr == 0x9010)
			memInitMapperSetPointer(addr, vrc7AudioSet9010);
		else if((aExp&EXP_VRC7) && addr == 0x9030)
			memInitMapperSetPointer(addr, vrc7AudioSet9030);
		else if((aExp&EXP_VRC6) && addr == 0xA000)
			memInitMapperSetPointer(addr, vrc6AudioSet8_AXX0);
		else if((aExp&EXP_VRC6) && addr == 0xA001)
			memInitMapperSetPointer(addr, vrc6AudioSet8_AXX1);
		else if((aExp&EXP_VRC6) && addr == 0xA002)
			memInitMapperSetPointer(addr, vrc6AudioSet8_AXX2);
		else if((aExp&EXP_VRC6) && addr == 0xB000)
			memInitMapperSetPointer(addr, vrc6AudioSet8_BXX0);
		else if((aExp&EXP_VRC6) && addr == 0xB001)
			memInitMapperSetPointer(addr, vrc6AudioSet8_BXX1);
		else if((aExp&EXP_VRC6) && addr == 0xB002)
			memInitMapperSetPointer(addr, vrc6AudioSet8_BXX2);
		else if(addr < 0xE000 && (aExp&EXP_FDS))
			memInitMapperSetPointer(addr, nsfSetFillRAM);
	}
}

void nsfcycle()
{
	uint8_t aExp = audioExpansion;
	if(aExp&EXP_VRC6)
		vrc6AudioClockTimers();
	if(aExp&EXP_FDS)
		fdsAudioClockTimers();
	if(aExp&EXP_MMC5)
		mmc5AudioClockTimers();
	if(aExp&EXP_N163)
		n163AudioClockTimers();
	if(aExp&EXP_S5B)
		s5BAudioClockTimers();
}

extern uint8_t inValReads[8];

void nsfVsync()
{
	if(inValReads[BUTTON_RIGHT] && !nsf.prevValReads[BUTTON_RIGHT])
	{
		nsf.prevValReads[BUTTON_RIGHT] = inValReads[BUTTON_RIGHT];
		nsf.curTrack++;
		if(nsf.curTrack > nsf.trackTotal)
			nsf.curTrack = 1;
		//printf("\rTrack %i/%i         ", nsf.curTrack, nsf.trackTotal);
		ppuDrawNSFTrackNum(nsf.curTrack, nsf.trackTotal);
		nsfInitPlayback();
		return;
	}
	else if(!inValReads[BUTTON_RIGHT])
		nsf.prevValReads[BUTTON_RIGHT] = 0;
	
	if(inValReads[BUTTON_LEFT] && !nsf.prevValReads[BUTTON_LEFT])
	{
		nsf.prevValReads[BUTTON_LEFT] = inValReads[BUTTON_LEFT];
		nsf.curTrack--;
		if(nsf.curTrack < 1)
			nsf.curTrack = nsf.trackTotal;
		//printf("\rTrack %i/%i         ", nsf.curTrack, nsf.trackTotal);
		ppuDrawNSFTrackNum(nsf.curTrack, nsf.trackTotal);
		nsfInitPlayback();
		return;
	}
	else if(!inValReads[BUTTON_LEFT])
		nsf.prevValReads[BUTTON_LEFT] = 0;

	if(nsf.playing)
		return;

	//wait for init return
	if(nsf.init_timeout)
	{
		nsf.init_timeout--;
		return;
	}
	//will get started on next CPU_GET_INSTRUCTION state
	nsf_startPlayback = true;
	nsf.playing = true;
}

uint16_t nsfGetPlayAddr()
{
	return nsf.playAddr;
}
