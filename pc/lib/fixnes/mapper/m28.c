/*
 * Copyright (C) 2018 FIX94
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
	uint8_t chrRAM[0x8000];
	uint8_t *chrRAMBankPtr;
	uint8_t prgBankMode;
	uint16_t prgBankAnd;
	uint8_t prgBankInner;
	uint16_t prgBankOuter;
	uint8_t reg;
	uint8_t mirror;
	bool usesPrgRAM;
} m28;

static void m28SetPrgROMBankPtr()
{
	//inner can be both 16k and 32k
	uint8_t curPrgBankInner = (m28.prgBankMode&2) ? (m28.prgBankInner) : (m28.prgBankInner<<1);
	//combine both inner and outer banks
	uint16_t curPrgBank = (curPrgBankInner&m28.prgBankAnd) | (m28.prgBankOuter&~m28.prgBankAnd);
	//set current 16k bank 0
	if((m28.prgBankMode&3) == 3) //normal inner+outer bank
		prg16setBank0(curPrgBank<<14);
	else if((m28.prgBankMode&3) == 2) //use lower half of outer bank
		prg16setBank0((m28.prgBankOuter&0x1FE)<<14);
	else //use lower half of inner+outer bank
		prg16setBank0((curPrgBank&0x1FE)<<14);
	//set current 16k bank 1
	if((m28.prgBankMode&3) == 2)  //normal inner+outer bank
		prg16setBank1(curPrgBank<<14);
	else if((m28.prgBankMode&3) == 3) //use upper half of outer bank
		prg16setBank1((m28.prgBankOuter|0x01)<<14);
	else //use upper half of inner+outer bank
		prg16setBank1((curPrgBank|0x01)<<14);
}

static void m28SetMirroring()
{
	switch(m28.mirror&3)
	{
		case 0:
			ppuSetNameTblSingleLower();
			break;
		case 1:
			ppuSetNameTblSingleUpper();
			break;
		case 2:
			ppuSetNameTblVertical();
			break;
		case 3:
			ppuSetNameTblHorizontal();
			break;
	}
}

void m28init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		m28.usesPrgRAM = true;
	}
	else
		m28.usesPrgRAM = false;
	prg16init(prgROMin,prgROMsizeIn);
	m28.prgBankMode = 0, m28.prgBankAnd = 0,
	m28.prgBankInner = 0, m28.prgBankOuter = 0;
	prg16setBank1(prgROMsizeIn - 0x4000);
	(void)chrROMin; (void)chrROMsizeIn;
	m28.chrRAMBankPtr = m28.chrRAM;
	m28.reg = 0; m28.mirror = 0;
	printf("Mapper 28 inited\n");
}

void m28initGet8(uint16_t addr)
{
	if(m28.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg16initGet8(addr);
}

static void m28setParams5XXX(uint16_t addr, uint8_t val) { (void)addr; m28.reg = ((val>>6)&2)|(val&1); }
static void m28setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((m28.reg&2) == 0 && (m28.mirror&2) == 0)
	{
		m28.mirror = ((val>>4)&1);
		m28SetMirroring();
	}
	switch(m28.reg&3)
	{
		case 0:
			m28.chrRAMBankPtr = m28.chrRAM+((val&3)<<13);
			break;
		case 1:
			m28.prgBankInner = val&0xF;
			m28SetPrgROMBankPtr();
			break;
		case 2:
			m28.mirror = (val&3);
			m28SetMirroring();
			m28.prgBankMode = (val>>2)&3;
			m28.prgBankAnd = (2<<((val>>4)&3))-1;
			m28SetPrgROMBankPtr();
			break;
		case 3:
			m28.prgBankOuter = (val<<1);
			m28SetPrgROMBankPtr();
			break;
	}
}
void m28initSet8(uint16_t addr)
{
	if(m28.usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr >= 0x5000 && addr < 0x6000)
		memInitMapperSetPointer(addr, m28setParams5XXX);
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m28setParams8XXX);
}

static uint8_t m28ChrGetRAM(uint16_t addr) { return m28.chrRAMBankPtr[addr]; }
void m28initPPUGet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, m28ChrGetRAM);
}

static void m28ChrSetRAM(uint16_t addr, uint8_t val) { m28.chrRAMBankPtr[addr] = val; }
void m28initPPUSet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUSetPointer(addr, m28ChrSetRAM);
}
