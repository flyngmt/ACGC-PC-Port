/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include "../mapper.h"
#include "../mem.h"

static struct {
	uint8_t *prgROM;
	uint32_t prgROMsize;
	uint32_t curCHRBank;
	uint8_t chrRAM[0x4000];
	uint8_t *chrRAMBankPtr;
} m13;

static void m13setChrRAMBankPtr()
{
	m13.chrRAMBankPtr = m13.chrRAM+m13.curCHRBank;
}

void m13init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn, 
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m13.prgROM = prgROMin;
	m13.prgROMsize = prgROMsizeIn;
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	(void)chrROMin;
	(void)chrROMsizeIn;
	m13.curCHRBank = 0;
	m13setChrRAMBankPtr();
	memset(m13.chrRAM,0,0x4000);
	printf("Mapper 13 inited\n");
}

static uint8_t m13getROM(uint16_t addr)
{
	return m13.prgROM[addr&0x7FFF];
}

void m13initGet8(uint16_t addr)
{
	if(addr < 0x8000)
		return;
	memInitMapperGetPointer(addr, m13getROM);
}

void m13setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	m13.curCHRBank = ((val & 3)<<12);
	m13setChrRAMBankPtr();
}

void m13initSet8(uint16_t addr)
{
	if(addr < 0x8000)
		return;
	memInitMapperSetPointer(addr, m13setParams);
}

static uint8_t m13chrGetRAM0XXX(uint16_t addr)
{
	return m13.chrRAM[addr&0xFFF];
}

static uint8_t m13chrGetRAM1XXX(uint16_t addr)
{
	return m13.chrRAMBankPtr[addr&0xFFF];
}

void m13initPPUGet8(uint16_t addr)
{
	if(addr < 0x1000)
		memInitMapperPPUGetPointer(addr, m13chrGetRAM0XXX);
	else if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, m13chrGetRAM1XXX);
}

static void m13chrSetRAM0XXX(uint16_t addr, uint8_t val)
{
	m13.chrRAM[addr&0xFFF] = val;
}

static void m13chrSetRAM1XXX(uint16_t addr, uint8_t val)
{
	m13.chrRAMBankPtr[addr&0xFFF] = val;
}

void m13initPPUSet8(uint16_t addr)
{
	if(addr < 0x1000)
		memInitMapperPPUSetPointer(addr, m13chrSetRAM0XXX);
	else if(addr < 0x2000)
		memInitMapperPPUSetPointer(addr, m13chrSetRAM1XXX);
}
