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

static uint32_t m228_prgROMsize;
static uint32_t m228_prgROMand;
static uint8_t m228_regRAM[4];

void m228init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank0(0<<14); prg16setBank1(1<<14);
	m228_prgROMsize = prgROMsizeIn;
	if(prgROMsizeIn < 0x80000)
		m228_prgROMand = mapperGetAndValue(prgROMsizeIn);
	else //Action 52 chip size
		m228_prgROMand = 0x7FFFF;
	chr8init(chrROMin,chrROMsizeIn);
	memset(m228_regRAM,0,4);
	printf("Mapper 228 inited\n");
}

static uint8_t m228getRAM(uint16_t addr)
{
	return m228_regRAM[addr&3];
}
void m228initGet8(uint16_t addr)
{
	if(addr >= 0x4020 && addr < 0x6000)
		memInitMapperGetPointer(addr, m228getRAM);
	prg16initGet8(addr);
}

static void m228setRAM(uint16_t addr, uint8_t val)
{
	m228_regRAM[addr&3] = val&0xF;
}
static void m228setParams(uint16_t addr, uint8_t val)
{
	uint32_t prgROMadd;
	switch((addr>>11)&3)
	{
		case 1:
			prgROMadd = 0x80000;
			break;
		case 3:
			prgROMadd = 0x100000;
			break;
		default:
			prgROMadd = 0;
			break;
	}
	if(prgROMadd >= m228_prgROMsize)
		prgROMadd = 0; //For Cheetahmen II
	uint8_t prgBank = (addr>>6)&0x1F;
	if((addr&0x20) == 0) //mode 32k
	{
		prg16setBank0((((prgBank&0xFE)<<14)&m228_prgROMand)+prgROMadd);
		prg16setBank1((((prgBank|0x01)<<14)&m228_prgROMand)+prgROMadd);
	}
	else //mode 16k
	{
		prg16setBank0(((prgBank<<14)&m228_prgROMand)+prgROMadd);
		prg16setBank1(((prgBank<<14)&m228_prgROMand)+prgROMadd);
	}
	chr8setBank0(((val&3)|((addr&0xF)<<2))<<13);
	if((addr&0x2000) == 0)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}
void m228initSet8(uint16_t addr)
{
	if(addr >= 0x4200 && addr < 0x6000)
		memInitMapperSetPointer(addr, m228setRAM);
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m228setParams);
}
