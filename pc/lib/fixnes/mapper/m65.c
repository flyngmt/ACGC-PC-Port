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

static struct {
	uint16_t irqCtr;
	uint16_t irqReloadCtr;
	bool irqEnable;
} m65;
extern uint8_t interrupt;

void m65init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr1init(chrROMin,chrROMsizeIn);
	prg8setBank0(0<<13);
	prg8setBank1(1<<13);
	prg8setBank2(0xFE<<13);
	prg8setBank3(prgROMsizeIn-0x2000);
	m65.irqCtr = 0;
	m65.irqReloadCtr = 0;
	m65.irqEnable = false;
	printf("Mapper 65 inited\n");
}

static void m65setParams8000(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank0(val<<13);
}

static void m65setParams9001(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val&0x80)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}

static void m65setParams9003(uint16_t addr, uint8_t val)
{
	(void)addr;
	m65.irqEnable = !!(val&0x80);
	interrupt &= ~MAPPER_IRQ;
}

static void m65setParams9004(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	m65.irqCtr = m65.irqReloadCtr;
	interrupt &= ~MAPPER_IRQ;
}

static void m65setParams9005(uint16_t addr, uint8_t val)
{
	(void)addr;
	m65.irqReloadCtr = (m65.irqReloadCtr&0xFF) | (val<<8);
}

static void m65setParams9006(uint16_t addr, uint8_t val)
{
	(void)addr;
	m65.irqReloadCtr = (m65.irqReloadCtr&~0xFF) | val;
}

static void m65setParamsA000(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank1(val<<13);
}

static void m65setParamsB000(uint16_t addr, uint8_t val) { (void)addr; chr1setBank0(val<<10); }
static void m65setParamsB001(uint16_t addr, uint8_t val) { (void)addr; chr1setBank1(val<<10); }
static void m65setParamsB002(uint16_t addr, uint8_t val) { (void)addr; chr1setBank2(val<<10); }
static void m65setParamsB003(uint16_t addr, uint8_t val) { (void)addr; chr1setBank3(val<<10); }
static void m65setParamsB004(uint16_t addr, uint8_t val) { (void)addr; chr1setBank4(val<<10); }
static void m65setParamsB005(uint16_t addr, uint8_t val) { (void)addr; chr1setBank5(val<<10); }
static void m65setParamsB006(uint16_t addr, uint8_t val) { (void)addr; chr1setBank6(val<<10); }
static void m65setParamsB007(uint16_t addr, uint8_t val) { (void)addr; chr1setBank7(val<<10); }

static void m65setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank2(val<<13);
}

void m65initSet8(uint16_t addr)
{
	if(addr == 0x8000) memInitMapperSetPointer(addr, m65setParams8000);
	else if(addr == 0x9001) memInitMapperSetPointer(addr, m65setParams9001);
	else if(addr == 0x9003) memInitMapperSetPointer(addr, m65setParams9003);
	else if(addr == 0x9004) memInitMapperSetPointer(addr, m65setParams9004);
	else if(addr == 0x9005) memInitMapperSetPointer(addr, m65setParams9005);
	else if(addr == 0x9006) memInitMapperSetPointer(addr, m65setParams9006);
	else if(addr == 0xA000) memInitMapperSetPointer(addr, m65setParamsA000);
	else if(addr == 0xB000) memInitMapperSetPointer(addr, m65setParamsB000);
	else if(addr == 0xB001) memInitMapperSetPointer(addr, m65setParamsB001);
	else if(addr == 0xB002) memInitMapperSetPointer(addr, m65setParamsB002);
	else if(addr == 0xB003) memInitMapperSetPointer(addr, m65setParamsB003);
	else if(addr == 0xB004) memInitMapperSetPointer(addr, m65setParamsB004);
	else if(addr == 0xB005) memInitMapperSetPointer(addr, m65setParamsB005);
	else if(addr == 0xB006) memInitMapperSetPointer(addr, m65setParamsB006);
	else if(addr == 0xB007) memInitMapperSetPointer(addr, m65setParamsB007);
	else if(addr == 0xC000) memInitMapperSetPointer(addr, m65setParamsC000);
}

void m65cycle()
{
	if(m65.irqCtr && m65.irqEnable)
	{
		m65.irqCtr--;
		if(m65.irqCtr == 0)
			interrupt |= MAPPER_IRQ;
	}
}
