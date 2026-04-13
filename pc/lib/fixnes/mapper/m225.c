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
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"
#include "../mapper_h/m225.h"

static uint8_t m225_regRAM[4];

void m225init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg16init(prgROMin,prgROMsizeIn);
	m225reset();
	chr8init(chrROMin,chrROMsizeIn);
	memset(m225_regRAM,0,4);
	printf("Mapper 225 inited\n");
}

static uint8_t m225getRAM(uint16_t addr)
{
	return m225_regRAM[addr&3];
}

void m225initGet8(uint16_t addr)
{
	if(addr >= 0x5800 && addr < 0x6000)
		memInitMapperGetPointer(addr, m225getRAM);
	prg16initGet8(addr);
}

static void m225setRAM(uint16_t addr, uint8_t val)
{
	m225_regRAM[addr&3] = val&0xF;
}

static void m225setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	uint8_t chrBank = addr&0x3F;
	uint8_t prgBank = (addr>>6)&0x3F;
	if(addr&0x4000)
	{
		chrBank |= 0x40;
		prgBank |= 0x40;
	}
	if((addr&0x1000) == 0) //mode 32k
	{
		prg16setBank0((prgBank&0xFE)<<14);
		prg16setBank1((prgBank|0x01)<<14);
	}
	else //mode 16k
	{
		prg16setBank0(prgBank<<14);
		prg16setBank1(prgBank<<14);
	}
	chr8setBank0(chrBank<<13);
	if((addr&0x2000) == 0)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}

void m225initSet8(uint16_t addr)
{
	if(addr >= 0x5800 && addr < 0x6000)
		memInitMapperSetPointer(addr, m225setRAM);
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m225setParams);
}

void m225reset()
{
	//reset to menu vectors seem to generally exist on most games,
	//however on some without this it will reset glitchy,
	//so for the sake of clean resetting everywhere do this
	prg16setBank0(0<<14); prg16setBank1(1<<14);
	chr8setBank0(0);
	ppuSetNameTblVertical();
}
