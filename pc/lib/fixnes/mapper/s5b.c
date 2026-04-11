/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"
#include "../audio_s5b.h"

static struct {
	uint8_t *prgROM;
	uint8_t *prgRAM;
	uint32_t prgROMand;
	uint32_t prgRAMand;
	uint32_t prgRAMBank;
	uint8_t *prgRAMBankPtr;
	uint16_t irqCtr;
	uint8_t CurReg;
	bool lowRAM;
	bool enableRAM;
	bool irqEnable;
	bool irqCtrEnable;
} s5B;

void s5Binit(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	prg8setBank3(prgROMsizeIn - 0x2000);
	s5B.prgROM = prgROMin;
	s5B.prgROMand = mapperGetAndValue(prgROMsizeIn);
	s5B.prgRAM = prgRAMin;
	s5B.prgRAMand = mapperGetAndValue(prgRAMsizeIn);
	s5B.prgRAMBank = 0;
	s5B.prgRAMBankPtr = s5B.prgRAM;
	chr1init(chrROMin,chrROMsizeIn);
	s5B.irqCtr = 0;
	s5B.CurReg = 0;
	s5B.lowRAM = false;
	s5B.enableRAM = false;
	s5B.irqEnable = false;
	s5B.irqCtrEnable = false;
	s5BAudioInit();
	printf("Sunsoft-5B inited\n");
}

extern uint8_t memLastVal;
static uint8_t s5BgetRAM(uint16_t addr)
{
	if(!s5B.lowRAM || s5B.enableRAM)
		return s5B.prgRAMBankPtr[addr&0x1FFF];
	else
		return memLastVal;
}

void s5BinitGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperGetPointer(addr, s5BgetRAM);
	else
		prg8initGet8(addr);
}

static void s5BsetRAM(uint16_t addr, uint8_t val)
{
	if(s5B.lowRAM && s5B.enableRAM)
		s5B.prgRAMBankPtr[addr&0x1FFF] = val;
}

static void s5BsetParams8000(uint16_t addr, uint8_t val)
{
	(void)addr;
	s5B.CurReg = val;
}

extern uint8_t interrupt;
static void s5BsetParamsA000(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(s5B.CurReg&0xF)
	{
		case 0x0:
			chr1setBank0(val<<10);
			break;
		case 0x1:
			chr1setBank1(val<<10);
			break;
		case 0x2:
			chr1setBank2(val<<10);
			break;
		case 0x3:
			chr1setBank3(val<<10);
			break;
		case 0x4:
			chr1setBank4(val<<10);
			break;
		case 0x5:
			chr1setBank5(val<<10);
			break;
		case 0x6:
			chr1setBank6(val<<10);
			break;
		case 0x7:
			chr1setBank7(val<<10);
			break;
		case 0x8:
			s5B.prgRAMBank = (val&0x3F)<<13;
			s5B.lowRAM = !!(val&0x40);
			s5B.enableRAM = !!(val&0x80);
			if(!s5B.lowRAM)
				s5B.prgRAMBankPtr = s5B.prgROM+(s5B.prgRAMBank&s5B.prgROMand);
			else if(s5B.enableRAM)
				s5B.prgRAMBankPtr = s5B.prgRAM+(s5B.prgRAMBank&s5B.prgRAMand);
			break;
		case 0x9:
			prg8setBank0((val&0x3F)<<13);
			break;
		case 0xA:
			prg8setBank1((val&0x3F)<<13);
			break;
		case 0xB:
			prg8setBank2((val&0x3F)<<13);
			break;
		case 0xC:
			switch(val&3)
			{
				case 0:
					ppuSetNameTblVertical();
					break;
				case 1:
					ppuSetNameTblHorizontal();
					break;
				case 2:
					ppuSetNameTblSingleLower();
					break;
				case 3:
					ppuSetNameTblSingleUpper();
					break;
			}
			break;
		case 0xD:
			s5B.irqEnable = !!(val&1);
			s5B.irqCtrEnable = !!(val&0x80);
			interrupt &= ~MAPPER_IRQ;
			break;
		case 0xE:
			s5B.irqCtr = (s5B.irqCtr&~0xFF) | val;
			break;
		case 0xF:
			s5B.irqCtr = (s5B.irqCtr&0xFF) | (val<<8);
			break;
	}
}

void s5BinitSet8(uint16_t ori_addr)
{
	if(ori_addr >= 0x6000 && ori_addr < 0x8000)
		memInitMapperSetPointer(ori_addr, s5BsetRAM);
	else if(ori_addr >= 0x8000)
	{
		uint16_t proc_addr = ori_addr&0xE000;
		if(proc_addr == 0x8000)
			memInitMapperSetPointer(ori_addr, s5BsetParams8000);
		else if(proc_addr == 0xA000)
			memInitMapperSetPointer(ori_addr, s5BsetParamsA000);
		else if(proc_addr == 0xC000)
			memInitMapperSetPointer(ori_addr, s5BAudioSet8_C000);
		else if(proc_addr == 0xE000)
			memInitMapperSetPointer(ori_addr, s5BAudioSet8_E000);
	}
}

void s5Bcycle()
{
	s5BAudioClockTimers();
	if(s5B.irqCtrEnable && !(interrupt&MAPPER_IRQ))
	{
		s5B.irqCtr--;
		if(s5B.irqCtr == 0xFFFF && s5B.irqEnable)
			interrupt |= MAPPER_IRQ;
	}
}
