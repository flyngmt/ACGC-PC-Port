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
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	bool usesPrgRAM;
	uint32_t curPRGBank;
	uint32_t upperPRGBank;
	uint8_t bankMode;
} m15;

static void m15SetPrgROMBankPtr()
{
	switch(m15.bankMode)
	{
		case 0:
			prg8setBank0(m15.curPRGBank+0x0000);
			prg8setBank1(m15.curPRGBank+0x2000);
			prg8setBank2((m15.curPRGBank|0x4000)+0x0000);
			prg8setBank3((m15.curPRGBank|0x4000)+0x2000);
			break;
		case 1:
			prg8setBank0(m15.curPRGBank+0x0000);
			prg8setBank1(m15.curPRGBank+0x2000);
			prg8setBank2((m15.curPRGBank|0x1C000)+0x0000);
			prg8setBank3((m15.curPRGBank|0x1C000)+0x2000);
			break;
		case 2:
			prg8setBank0((m15.curPRGBank|m15.upperPRGBank)+0x0000);
			prg8setBank1((m15.curPRGBank|m15.upperPRGBank)+0x0000);
			prg8setBank2((m15.curPRGBank|m15.upperPRGBank)+0x0000);
			prg8setBank3((m15.curPRGBank|m15.upperPRGBank)+0x0000);
			break;
		default: //case 3
			prg8setBank0(m15.curPRGBank+0x0000);
			prg8setBank1(m15.curPRGBank+0x2000);
			prg8setBank2(m15.curPRGBank+0x0000);
			prg8setBank3(m15.curPRGBank+0x2000);
			break;
	}
}

void m15init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin, prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		m15.usesPrgRAM = true;
	}
	else
		m15.usesPrgRAM = false;
	m15.curPRGBank = 0;
	m15.bankMode = 0;
	m15.upperPRGBank = 0;
	m15SetPrgROMBankPtr();
	(void)chrROMin;
	(void)chrROMsizeIn;
	chr8init(NULL,0); //RAM only
	printf("Mapper 15 inited\n");
}

void m15initGet8(uint16_t addr)
{
	if(m15.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

void m15setParams(uint16_t addr, uint8_t val)
{
	m15.bankMode = (addr&3);
	m15.upperPRGBank = ((val&(1<<7))<<6);
	m15.curPRGBank = ((val&0x3F)<<14);
	m15SetPrgROMBankPtr();
	if((val&(1<<6)) == 0)
	{
		//printf("Vertical mode\n");
		ppuSetNameTblVertical();
	}
	else
	{
		//printf("Horizontal mode\n");
		ppuSetNameTblHorizontal();
	}
}

void m15initSet8(uint16_t addr)
{
	if(m15.usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m15setParams);
}

void m15reset()
{
	m15setParams(0,0);
}
