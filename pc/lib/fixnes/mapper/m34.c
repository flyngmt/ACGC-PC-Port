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
	uint8_t *prgRAM;
	uint32_t prgRAMsize;
	bool usesPrgRAM;
} m34;

void m34init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg32init(prgROMin,prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		m34.usesPrgRAM = true;
		m34.prgRAM = prgRAMin;
		m34.prgRAMsize = prgRAMsizeIn;
	}
	else
		m34.usesPrgRAM = false;
	chr4init(chrROMin,chrROMsizeIn);
	chr4setBank0(0x0000);
	chr4setBank1(0x1000);
	printf("Mapper 34 inited\n");
}

static uint8_t m34getRAM(uint16_t addr)
{
	return m34.prgRAM[addr&0x1FFF];
}

void m34initGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000 && m34.usesPrgRAM)
		memInitMapperGetPointer(addr, m34getRAM);
	prg32initGet8(addr);
}

static void m34setRAM(uint16_t addr, uint8_t val)
{
	m34.prgRAM[addr&0x1FFF] = val;
}

static void m34setParams7FFD(uint16_t addr, uint8_t val) { (void)addr; prg32setBank0((val & 0xF)<<15); }
static void m34setParams7FFE(uint16_t addr, uint8_t val) { (void)addr; chr4setBank0((val & 0xF)<<12); }
static void m34setParams7FFF(uint16_t addr, uint8_t val) { (void)addr; chr4setBank1((val & 0xF)<<12); }

static void m34setParams7FFD_RAM(uint16_t addr, uint8_t val) { m34setRAM(addr,val); m34setParams7FFD(addr,val); }
static void m34setParams7FFE_RAM(uint16_t addr, uint8_t val) { m34setRAM(addr,val); m34setParams7FFE(addr,val); }
static void m34setParams7FFF_RAM(uint16_t addr, uint8_t val) { m34setRAM(addr,val); m34setParams7FFF(addr,val); }

static void m34setParams8XXX(uint16_t addr, uint8_t val) { (void)addr; prg32setBank0((val & 0xF)<<15); }

void m34initSet8(uint16_t addr)
{
	//printf("m34set8 %04x %02x\n", addr, val);
	if(addr >= 0x6000 && addr < 0x8000)
	{
		if(m34.usesPrgRAM)
		{
			if(addr < 0x7FFD)
				memInitMapperSetPointer(addr, m34setRAM);
			else if(addr == 0x7FFD)
				memInitMapperSetPointer(addr, m34setParams7FFD_RAM);
			else if(addr == 0x7FFE)
				memInitMapperSetPointer(addr, m34setParams7FFE_RAM);
			else if(addr == 0x7FFF)
				memInitMapperSetPointer(addr, m34setParams7FFF_RAM);
		}
		else
		{
			if(addr == 0x7FFD)
				memInitMapperSetPointer(addr, m34setParams7FFD);
			else if(addr == 0x7FFE)
				memInitMapperSetPointer(addr, m34setParams7FFE);
			else if(addr == 0x7FFF)
				memInitMapperSetPointer(addr, m34setParams7FFF);
		}
	}
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m34setParams8XXX);
}
