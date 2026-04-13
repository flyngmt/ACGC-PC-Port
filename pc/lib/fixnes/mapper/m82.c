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
	bool prgRAMenabled[3];
	uint8_t *prgRAM;
	uint32_t CHRBank[8];
	uint8_t chr_bank_flip;
} m82;

static void m82SetChrROMBanks()
{
	chr1setBank0(m82.CHRBank[0^m82.chr_bank_flip]); chr1setBank1(m82.CHRBank[1^m82.chr_bank_flip]);
	chr1setBank2(m82.CHRBank[2^m82.chr_bank_flip]); chr1setBank3(m82.CHRBank[3^m82.chr_bank_flip]);
	chr1setBank4(m82.CHRBank[4^m82.chr_bank_flip]); chr1setBank5(m82.CHRBank[5^m82.chr_bank_flip]);
	chr1setBank6(m82.CHRBank[6^m82.chr_bank_flip]); chr1setBank7(m82.CHRBank[7^m82.chr_bank_flip]);
}

void m82init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin, prgROMsizeIn);
	prg8setBank3(prgROMsizeIn - 0x2000);
	if(prgRAMin && prgRAMsizeIn)
	{
		m82.prgRAM = prgRAMin;
		m82.usesPrgRAM = true;
	}
	else
		m82.usesPrgRAM = false;
	m82.prgRAMenabled[0] = false;
	m82.prgRAMenabled[1] = false;
	m82.prgRAMenabled[2] = false;
	chr1init(chrROMin, chrROMsizeIn);
	m82.chr_bank_flip = 0;
	memset(m82.CHRBank,0,8*sizeof(uint32_t));
	m82SetChrROMBanks();
	printf("Taito X1-017 inited\n");
}

extern uint8_t memLastVal;
static uint8_t m82prgRAMBank0Get8(uint16_t addr)
{
	if(m82.usesPrgRAM && m82.prgRAMenabled[0])
		return m82.prgRAM[addr&0x1FFF];
	return memLastVal; //aka open bus
}
static uint8_t m82prgRAMBank1Get8(uint16_t addr)
{
	if(m82.usesPrgRAM && m82.prgRAMenabled[1])
		return m82.prgRAM[addr&0x1FFF];
	return memLastVal; //aka open bus
}
static uint8_t m82prgRAMBank2Get8(uint16_t addr)
{
	if(m82.usesPrgRAM && m82.prgRAMenabled[2])
		return m82.prgRAM[addr&0x1FFF];
	return memLastVal; //aka open bus
}

void m82initGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x6800)
		memInitMapperGetPointer(addr, m82prgRAMBank0Get8);
	else if(addr >= 0x6800 && addr < 0x7000)
		memInitMapperGetPointer(addr, m82prgRAMBank1Get8);
	else if(addr >= 0x7000 && addr < 0x7400)
		memInitMapperGetPointer(addr, m82prgRAMBank2Get8);
	else
		prg8initGet8(addr);
}

static void m82setParams7EF0(uint16_t addr, uint8_t val)
{
	(void)addr;
	m82.CHRBank[0] = ((val&0xFE)<<10);
	m82.CHRBank[1] = ((val|0x01)<<10);
	m82SetChrROMBanks();
}

static void m82setParams7EF1(uint16_t addr, uint8_t val)
{
	(void)addr;
	m82.CHRBank[2] = ((val&0xFE)<<10);
	m82.CHRBank[3] = ((val|0x01)<<10);
	m82SetChrROMBanks();
}

static void m82setParams7EF2(uint16_t addr, uint8_t val) { (void)addr; m82.CHRBank[4] = (val<<10); m82SetChrROMBanks(); }
static void m82setParams7EF3(uint16_t addr, uint8_t val) { (void)addr; m82.CHRBank[5] = (val<<10); m82SetChrROMBanks(); }
static void m82setParams7EF4(uint16_t addr, uint8_t val) { (void)addr; m82.CHRBank[6] = (val<<10); m82SetChrROMBanks(); }
static void m82setParams7EF5(uint16_t addr, uint8_t val) { (void)addr; m82.CHRBank[7] = (val<<10); m82SetChrROMBanks(); }

static void m82setParams7EF6(uint16_t addr, uint8_t val)
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
	m82.chr_bank_flip = (val&2) ? 4 : 0;
	m82SetChrROMBanks();
}

static void m82setParams7EF7(uint16_t addr, uint8_t val) { (void)addr; m82.prgRAMenabled[0] = (val == 0xCA); }
static void m82setParams7EF8(uint16_t addr, uint8_t val) { (void)addr; m82.prgRAMenabled[1] = (val == 0x69); }
static void m82setParams7EF9(uint16_t addr, uint8_t val) { (void)addr; m82.prgRAMenabled[2] = (val == 0x84); }

static void m82setParams7EFA(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0((val&0xFC)<<11); }
static void m82setParams7EFB(uint16_t addr, uint8_t val) { (void)addr; prg8setBank1((val&0xFC)<<11); }
static void m82setParams7EFC(uint16_t addr, uint8_t val) { (void)addr; prg8setBank2((val&0xFC)<<11); }

static void m82prgRAMBank0Set8(uint16_t addr, uint8_t val) { if(m82.usesPrgRAM && m82.prgRAMenabled[0]) m82.prgRAM[addr&0x1FFF] = val; }
static void m82prgRAMBank1Set8(uint16_t addr, uint8_t val) { if(m82.usesPrgRAM && m82.prgRAMenabled[1]) m82.prgRAM[addr&0x1FFF] = val; }
static void m82prgRAMBank2Set8(uint16_t addr, uint8_t val) { if(m82.usesPrgRAM && m82.prgRAMenabled[2]) m82.prgRAM[addr&0x1FFF] = val; }

void m82initSet8(uint16_t addr)
{
	if(addr >= 0x7EF0 && addr <= 0x7EFC)
	{
		switch(addr&0xF)
		{
			case 0:
				memInitMapperSetPointer(addr, m82setParams7EF0);
				break;
			case 1:
				memInitMapperSetPointer(addr, m82setParams7EF1);
				break;
			case 2:
				memInitMapperSetPointer(addr, m82setParams7EF2);
				break;
			case 3:
				memInitMapperSetPointer(addr, m82setParams7EF3);
				break;
			case 4:
				memInitMapperSetPointer(addr, m82setParams7EF4);
				break;
			case 5:
				memInitMapperSetPointer(addr, m82setParams7EF5);
				break;
			case 6:
				memInitMapperSetPointer(addr, m82setParams7EF6);
				break;
			case 7:
				memInitMapperSetPointer(addr, m82setParams7EF7);
				break;
			case 8:
				memInitMapperSetPointer(addr, m82setParams7EF8);
				break;
			case 9:
				memInitMapperSetPointer(addr, m82setParams7EF9);
				break;
			case 0xA:
				memInitMapperSetPointer(addr, m82setParams7EFA);
				break;
			case 0xB:
				memInitMapperSetPointer(addr, m82setParams7EFB);
				break;
			case 0xC:
				memInitMapperSetPointer(addr, m82setParams7EFC);
				break;
		}
	}
	else if(addr >= 0x6000 && addr < 0x6800)
		memInitMapperSetPointer(addr, m82prgRAMBank0Set8);
	else if(addr >= 0x6800 && addr < 0x7000)
		memInitMapperSetPointer(addr, m82prgRAMBank1Set8);
	else if(addr >= 0x7000 && addr < 0x7400)
		memInitMapperSetPointer(addr, m82prgRAMBank2Set8);
}
