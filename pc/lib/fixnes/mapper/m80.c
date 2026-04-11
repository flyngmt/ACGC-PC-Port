/*
 * Copyright (C) 2019 FIX94
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
	bool usesPrgRAM;
	bool prgRAMenabled;
	uint8_t *prgRAM;
} m80;

void m80init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin, prgROMsizeIn);
	prg8setBank3(prgROMsizeIn - 0x2000);
	if(prgRAMin && prgRAMsizeIn)
	{
		m80.prgRAM = prgRAMin;
		m80.usesPrgRAM = true;
	}
	else
		m80.usesPrgRAM = true;
	m80.prgRAMenabled = false;
	chr1init(chrROMin, chrROMsizeIn);
	printf("Taito X1-005 inited\n");
}

static uint16_t m207nt0, m207nt1;
void m207init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m80init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	//some extra regs
	m207nt0 = 0, m207nt1 = 0;
	ppuSetNameTblCustom(m207nt0,m207nt0,m207nt1,m207nt1);
}

extern uint8_t memLastVal;
static uint8_t m80prgRAMget8(uint16_t addr)
{
	if(m80.usesPrgRAM && m80.prgRAMenabled)
		return m80.prgRAM[addr&0x7F];
	return memLastVal; //aka open bus
}

void m80initGet8(uint16_t addr)
{
	if(addr >= 0x7F00 && addr < 0x8000)
		memInitMapperGetPointer(addr, m80prgRAMget8);
	else
		prg8initGet8(addr);
}

static void m80setParams7EF0(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr1setBank0((val&0xFE)<<10);
	chr1setBank1((val|0x01)<<10);
}

static void m80setParams7EF1(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr1setBank2((val&0xFE)<<10);
	chr1setBank3((val|0x01)<<10);
}

static void m80setParams7EF2(uint16_t addr, uint8_t val) { (void)addr; chr1setBank4(val<<10); }
static void m80setParams7EF3(uint16_t addr, uint8_t val) { (void)addr; chr1setBank5(val<<10); }
static void m80setParams7EF4(uint16_t addr, uint8_t val) { (void)addr; chr1setBank6(val<<10); }
static void m80setParams7EF5(uint16_t addr, uint8_t val) { (void)addr; chr1setBank7(val<<10); }

static void m80setParams7EF6(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
		if(val&1)
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
}

static void m80setParams7EF8(uint16_t addr, uint8_t val) { (void)addr; m80.prgRAMenabled = (val == 0xA3); }

static void m80setParams7EFA(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0(val<<13); }
static void m80setParams7EFC(uint16_t addr, uint8_t val) { (void)addr; prg8setBank1(val<<13); }
static void m80setParams7EFE(uint16_t addr, uint8_t val) { (void)addr; prg8setBank2(val<<13); }

static void m80prgRAMset8(uint16_t addr, uint8_t val) { if(m80.usesPrgRAM && m80.prgRAMenabled) m80.prgRAM[addr&0x7F] = val; }

void m80initSet8(uint16_t addr)
{
	if(addr >= 0x7EF0 && addr < 0x7F00)
	{
		switch(addr&0xF)
		{
			case 0:
				memInitMapperSetPointer(addr, m80setParams7EF0);
				break;
			case 1:
				memInitMapperSetPointer(addr, m80setParams7EF1);
				break;
			case 2:
				memInitMapperSetPointer(addr, m80setParams7EF2);
				break;
			case 3:
				memInitMapperSetPointer(addr, m80setParams7EF3);
				break;
			case 4:
				memInitMapperSetPointer(addr, m80setParams7EF4);
				break;
			case 5:
				memInitMapperSetPointer(addr, m80setParams7EF5);
				break;
			case 6: case 7:
				memInitMapperSetPointer(addr, m80setParams7EF6);
				break;
			case 8: case 9:
				memInitMapperSetPointer(addr, m80setParams7EF8);
				break;
			case 0xA: case 0xB:
				memInitMapperSetPointer(addr, m80setParams7EFA);
				break;
			case 0xC: case 0xD:
				memInitMapperSetPointer(addr, m80setParams7EFC);
				break;
			case 0xE: case 0xF:
				memInitMapperSetPointer(addr, m80setParams7EFE);
				break;
		}
	}
	else if(addr >= 0x7F00 && addr < 0x8000)
		memInitMapperSetPointer(addr, m80prgRAMset8);
}

static void m207setParams7EF0(uint16_t addr, uint8_t val)
{
	(void)addr;
	m207nt0 = (val&0x80) ? 0x400 : 0;
	ppuSetNameTblCustom(m207nt0,m207nt0,m207nt1,m207nt1);
	m80setParams7EF0(addr, val&0x7F);
}

static void m207setParams7EF1(uint16_t addr, uint8_t val)
{
	(void)addr;
	m207nt1 = (val&0x80) ? 0x400 : 0;
	ppuSetNameTblCustom(m207nt0,m207nt0,m207nt1,m207nt1);
	m80setParams7EF1(addr, val&0x7F);
}

void m207initSet8(uint16_t addr)
{
	if(addr == 0x7EF0)
		memInitMapperSetPointer(addr, m207setParams7EF0);
	else if(addr == 0x7EF1)
		memInitMapperSetPointer(addr, m207setParams7EF1);
	else if(addr != 0x7EF6 && addr != 0x7EF7)
		m80initSet8(addr);
}
