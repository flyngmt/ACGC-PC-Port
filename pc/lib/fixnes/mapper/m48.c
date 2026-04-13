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
	uint8_t *chrROM;
	uint8_t *chrROMBank0Ptr, *chrROMBank1Ptr,
			*chrROMBank2Ptr, *chrROMBank3Ptr,
			*chrROMBank4Ptr, *chrROMBank5Ptr;
	uint32_t chrROMand;
	uint8_t chrRAM[0x2000];
	uint8_t irqCtr;
	uint8_t irqStart;
	bool irqEnable;
	uint8_t irqReloadVal;
	uint16_t prevAddr;
} m48;

void m48init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin, prgROMsizeIn);
	prg8setBank2(prgROMsizeIn - 0x4000);
	prg8setBank3(prgROMsizeIn - 0x2000);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	if(chrROMsizeIn > 0)
	{
		m48.chrROM = chrROMin;
		m48.chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
	{
		m48.chrROM = m48.chrRAM;
		m48.chrROMand = 0x1FFF;
	}
	memset(m48.chrRAM,0,0x2000);
	m48.chrROMBank0Ptr = m48.chrROMBank1Ptr = m48.chrROMBank2Ptr =
		m48.chrROMBank3Ptr = m48.chrROMBank4Ptr = m48.chrROMBank5Ptr = m48.chrROM;
	m48.irqCtr = 0;
	m48.irqStart = 0;
	m48.irqEnable = false;
	m48.irqReloadVal = 0xFF;
	m48.prevAddr = 0;
	printf("Mapper 48 inited\n");
}

static void m48setParams8XX0(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0((val&0x3F)<<13); }
static void m48setParams8XX1(uint16_t addr, uint8_t val) { (void)addr; prg8setBank1((val&0x3F)<<13); }

static void m48setParams8XX2(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank0Ptr = m48.chrROM+((val<<11)&m48.chrROMand); }
static void m48setParams8XX3(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank1Ptr = m48.chrROM+((val<<11)&m48.chrROMand); }
static void m48setParamsAXX0(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank2Ptr = m48.chrROM+((val<<10)&m48.chrROMand); }
static void m48setParamsAXX1(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank3Ptr = m48.chrROM+((val<<10)&m48.chrROMand); }
static void m48setParamsAXX2(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank4Ptr = m48.chrROM+((val<<10)&m48.chrROMand); }
static void m48setParamsAXX3(uint16_t addr, uint8_t val) { (void)addr; m48.chrROMBank5Ptr = m48.chrROM+((val<<10)&m48.chrROMand); }

static void m48setParamsCXX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	m48.irqReloadVal = val^0xFF;
}

static void m48setParamsCXX1(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	m48.irqCtr = 0;
}

static void m48setParamsCXX2(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	m48.irqEnable = true;
}

extern uint8_t interrupt;
static void m48setParamsCXX3(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	m48.irqEnable = false;
	m48.irqStart = 0;
	interrupt &= ~MAPPER_IRQ;
}

static void m48setParamsEXX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
		if((val&0x40) == 0)
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

void m48initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE003;
	if(proc_addr == 0x8000)
		memInitMapperSetPointer(ori_addr, m48setParams8XX0);
	else if(proc_addr == 0x8001)
		memInitMapperSetPointer(ori_addr, m48setParams8XX1);
	else if(proc_addr == 0x8002)
		memInitMapperSetPointer(ori_addr, m48setParams8XX2);
	else if(proc_addr == 0x8003)
		memInitMapperSetPointer(ori_addr, m48setParams8XX3);
	else if(proc_addr == 0xA000)
		memInitMapperSetPointer(ori_addr, m48setParamsAXX0);
	else if(proc_addr == 0xA001)
		memInitMapperSetPointer(ori_addr, m48setParamsAXX1);
	else if(proc_addr == 0xA002)
		memInitMapperSetPointer(ori_addr, m48setParamsAXX2);
	else if(proc_addr == 0xA003)
		memInitMapperSetPointer(ori_addr, m48setParamsAXX3);
	else if(proc_addr == 0xC000)
		memInitMapperSetPointer(ori_addr, m48setParamsCXX0);
	else if(proc_addr == 0xC001)
		memInitMapperSetPointer(ori_addr, m48setParamsCXX1);
	else if(proc_addr == 0xC002)
		memInitMapperSetPointer(ori_addr, m48setParamsCXX2);
	else if(proc_addr == 0xC003)
		memInitMapperSetPointer(ori_addr, m48setParamsCXX3);
	else if(proc_addr == 0xE000)
		memInitMapperSetPointer(ori_addr, m48setParamsEXX0);
}

void m48clock(uint16_t addr)
{
	if((addr & 0x1000) && !(m48.prevAddr & 0x1000))
	{
		//printf("m48 Beep at "); ppuPrintCurLineDot();
		if(m48.irqCtr == 0)
			m48.irqCtr = m48.irqReloadVal;
		else
			m48.irqCtr--;
		if(m48.irqCtr == 0 && m48.irqStart == 0 && m48.irqEnable)
		{
			//printf("m48 Tick at "); ppuPrintCurLineDot();
			m48.irqStart = 5;
			m48.irqEnable = false;
		}
	}
	m48.prevAddr = addr;
}

static void m48chrSetRAM0(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank0Ptr[addr&0x7FF] = val;
	m48clock(addr);
}
static void m48chrSetRAM1(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank1Ptr[addr&0x7FF] = val;
	m48clock(addr);
}
static void m48chrSetRAM2(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank2Ptr[addr&0x3FF] = val;
	m48clock(addr);
}
static void m48chrSetRAM3(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank3Ptr[addr&0x3FF] = val;
	m48clock(addr);
}
static void m48chrSetRAM4(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank4Ptr[addr&0x3FF] = val;
	m48clock(addr);
}
static void m48chrSetRAM5(uint16_t addr, uint8_t val)
{	//remember, m48.chrROM = m48.chrRAM
	m48.chrROMBank5Ptr[addr&0x3FF] = val;
	m48clock(addr);
}

static void m48chrSetClock(uint16_t addr, uint8_t val)
{
	(void)val;
	m48clock(addr);
}

static uint8_t m48chrGetROM0(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank0Ptr[addr&0x7FF];
}
static uint8_t m48chrGetROM1(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank1Ptr[addr&0x7FF];
}
static uint8_t m48chrGetROM2(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank2Ptr[addr&0x3FF];
}
static uint8_t m48chrGetROM3(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank3Ptr[addr&0x3FF];
}
static uint8_t m48chrGetROM4(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank4Ptr[addr&0x3FF];
}
static uint8_t m48chrGetROM5(uint16_t addr)
{
	m48clock(addr);
	return m48.chrROMBank5Ptr[addr&0x3FF];
}

void m48initPPUGet8(uint16_t addr)
{
	if(addr < 0x800)
		memInitMapperPPUGetPointer(addr, m48chrGetROM0);
	else if(addr < 0x1000)
		memInitMapperPPUGetPointer(addr, m48chrGetROM1);
	else if(addr < 0x1400)
		memInitMapperPPUGetPointer(addr, m48chrGetROM2);
	else if(addr < 0x1800)
		memInitMapperPPUGetPointer(addr, m48chrGetROM3);
	else if(addr < 0x1C00)
		memInitMapperPPUGetPointer(addr, m48chrGetROM4);
	else if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, m48chrGetROM5);
}

void m48initPPUSet8(uint16_t addr)
{
	if(m48.chrROM == m48.chrRAM) //Writable
	{
		if(addr < 0x800)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM0);
		else if(addr < 0x1000)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM1);
		else if(addr < 0x1400)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM2);
		else if(addr < 0x1800)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM3);
		else if(addr < 0x1C00)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM4);
		else if(addr < 0x2000)
			memInitMapperPPUSetPointer(addr, m48chrSetRAM5);
	}
	else if(addr < 0x2000)
		memInitMapperPPUSetPointer(addr, m48chrSetClock);
}

void m48cycle()
{
	if(m48.irqStart == 1)
	{
		interrupt |= MAPPER_IRQ;
		m48.irqStart = 0;
		m48.irqEnable = false;
	}
	else if(m48.irqStart > 1)
		m48.irqStart--;
}
