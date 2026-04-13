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

static struct {
	uint32_t curPRGBank0;
	uint32_t curPRGBank1;
	uint32_t lastPRGBank;
	uint32_t lastM1PRGBank;
	uint8_t prgMode;
	bool usesPrgRAM;
} m32;
//used externally
bool m32_singlescreen;

static void m32SetPrgROMBankPtr()
{
	if(m32.prgMode == 0)
	{
		prg8setBank0(m32.curPRGBank0<<13);
		prg8setBank1(m32.curPRGBank1<<13);
		prg8setBank2(m32.lastM1PRGBank);
		prg8setBank3(m32.lastPRGBank);
	}
	else
	{
		prg8setBank0(m32.lastM1PRGBank);
		prg8setBank1(m32.curPRGBank1<<13);
		prg8setBank2(m32.curPRGBank0<<13);
		prg8setBank3(m32.lastPRGBank);
	}
}

void m32init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		m32.usesPrgRAM = true;
	}
	else
		m32.usesPrgRAM = false;
	chr1init(chrROMin,chrROMsizeIn);
	m32.curPRGBank0 = 0;
	m32.curPRGBank1 = 0x2000;
	m32.lastPRGBank = (prgROMsizeIn - 0x2000);
	m32.lastM1PRGBank = m32.lastPRGBank - 0x2000;
	m32.prgMode = 0;
	m32SetPrgROMBankPtr();
	if(m32_singlescreen)
		ppuSetNameTblSingleLower();
	printf("Mapper 32 inited\n");
}

void m32initGet8(uint16_t addr)
{
	if(m32.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

void m32setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m32.curPRGBank0 = val&0x1F;
	m32SetPrgROMBankPtr();
}

void m32setParams9XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!m32_singlescreen)
	{
		if(val&1)
			ppuSetNameTblHorizontal();
		else
			ppuSetNameTblVertical();
		m32.prgMode = !!(val&2);
		m32SetPrgROMBankPtr();
	}
}

void m32setParamsAXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m32.curPRGBank1 = val;
	m32SetPrgROMBankPtr();
}

void m32setParamsBXX0(uint16_t addr, uint8_t val) { (void)addr; chr1setBank0(val<<10); }
void m32setParamsBXX1(uint16_t addr, uint8_t val) { (void)addr; chr1setBank1(val<<10); }
void m32setParamsBXX2(uint16_t addr, uint8_t val) { (void)addr; chr1setBank2(val<<10); }
void m32setParamsBXX3(uint16_t addr, uint8_t val) { (void)addr; chr1setBank3(val<<10); }
void m32setParamsBXX4(uint16_t addr, uint8_t val) { (void)addr; chr1setBank4(val<<10); }
void m32setParamsBXX5(uint16_t addr, uint8_t val) { (void)addr; chr1setBank5(val<<10); }
void m32setParamsBXX6(uint16_t addr, uint8_t val) { (void)addr; chr1setBank6(val<<10); }
void m32setParamsBXX7(uint16_t addr, uint8_t val) { (void)addr; chr1setBank7(val<<10); }

void m32initSet8(uint16_t addr)
{
	if(m32.usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr >= 0x8000)
	{
		if(addr < 0x9000)
			memInitMapperSetPointer(addr, m32setParams8XXX);
		else if(addr < 0xA000)
			memInitMapperSetPointer(addr, m32setParams9XXX);
		else if(addr < 0xB000)
			memInitMapperSetPointer(addr, m32setParamsAXXX);
		else if(addr < 0xC000)
		{
			switch(addr&7)
			{
				case 0x0:
					memInitMapperSetPointer(addr, m32setParamsBXX0);
					break;
				case 0x1:
					memInitMapperSetPointer(addr, m32setParamsBXX1);
					break;
				case 0x2:
					memInitMapperSetPointer(addr, m32setParamsBXX2);
					break;
				case 0x3:
					memInitMapperSetPointer(addr, m32setParamsBXX3);
					break;
				case 0x4:
					memInitMapperSetPointer(addr, m32setParamsBXX4);
					break;
				case 0x5:
					memInitMapperSetPointer(addr, m32setParamsBXX5);
					break;
				case 0x6:
					memInitMapperSetPointer(addr, m32setParamsBXX6);
					break;
				case 0x7:
					memInitMapperSetPointer(addr, m32setParamsBXX7);
					break;
				default:
					break;
			}
		}
	}
}
