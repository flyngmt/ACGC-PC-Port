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
#include "../mapper_h/m237.h"

static struct {
	uint8_t *prgROM;
	uint32_t prgROMand;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr;
	uint16_t type;
	uint8_t prgBank;
	bool lock;
} m237;

static void m237setBank0(uint32_t val) { m237.prgROMBank0Ptr = m237.prgROM+(val&m237.prgROMand); }
static void m237setBank1(uint32_t val) { m237.prgROMBank1Ptr = m237.prgROM+(val&m237.prgROMand); }

void m237init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	m237.prgROM = prgROMin;
	m237.prgROMand = mapperGetAndValue(prgROMsizeIn);
	//sets prg banks
	m237reset();
	chr8init(chrROMin,chrROMsizeIn);
	printf("Mapper 237 inited\n");
}

static uint8_t m237GetROM0(uint16_t addr) { return m237.prgROMBank0Ptr[(addr|m237.type)&0x3FFF]; }
static uint8_t m237GetROM1(uint16_t addr) { return m237.prgROMBank1Ptr[(addr|m237.type)&0x3FFF]; }

void m237initGet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	else if(addr < 0xC000) memInitMapperGetPointer(addr, m237GetROM0);
	else memInitMapperGetPointer(addr, m237GetROM1);
}

static void m237setParams(uint16_t addr, uint8_t val)
{
	m237.prgBank = (m237.prgBank&0x38)|(val&7);
	if(!m237.lock)
	{
		m237.prgBank = ((addr<<3)&0x20)|(val&0x18)|(m237.prgBank&7);
		m237.lock = ((addr&2) != 0);
		m237.type = (addr&1) ? 2 : 0;
		if((val&0x20) == 0)
			ppuSetNameTblVertical();
		else
			ppuSetNameTblHorizontal();
	}
	switch((val>>6)&3)
	{
		case 0:
			m237setBank0(m237.prgBank<<14);
			m237setBank1((m237.prgBank|0x07)<<14);
			break;
		case 1:
			m237setBank0((m237.prgBank&0xFE)<<14);
			m237setBank1((m237.prgBank|0x07)<<14);
			break;
		case 2:
			m237setBank0(m237.prgBank<<14);
			m237setBank1(m237.prgBank<<14);
			break;
		case 3:
			m237setBank0((m237.prgBank&0xFE)<<14);
			m237setBank1((m237.prgBank|0x01)<<14);
			break;
	}
}
void m237initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m237setParams);
}

void m237reset()
{
	m237setBank0(0<<14); m237setBank1(7<<14);
	m237.type = 0;
	m237.prgBank = 0;
	m237.lock = false;
}
