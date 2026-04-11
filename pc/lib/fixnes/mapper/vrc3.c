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
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	bool usesPrgRAM;
	uint16_t irqCtr;
	uint16_t irqReloadCtr;
	bool irqEnable;
	bool irqEnable_after_ack;
	bool irq8Bit;
} vrc3;

extern uint8_t interrupt;

void vrc3init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		vrc3.usesPrgRAM = true;
	}
	else
		vrc3.usesPrgRAM = false;
	chr8init(chrROMin,chrROMsizeIn);
	vrc3.irqCtr = 0;
	vrc3.irqReloadCtr = 0;
	vrc3.irqEnable = false;
	vrc3.irqEnable_after_ack = false;
	vrc3.irq8Bit = false;
	printf("VRC3 inited\n");
}

void vrc3initGet8(uint16_t addr)
{
	if(vrc3.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg16initGet8(addr);
}

static void vrc3setParams8000(uint16_t addr, uint8_t val) { (void)addr; vrc3.irqReloadCtr = (vrc3.irqReloadCtr&0xFFF0)|((val&0xF)<<0); }
static void vrc3setParams9000(uint16_t addr, uint8_t val) { (void)addr; vrc3.irqReloadCtr = (vrc3.irqReloadCtr&0xFF0F)|((val&0xF)<<4); }
static void vrc3setParamsA000(uint16_t addr, uint8_t val) { (void)addr; vrc3.irqReloadCtr = (vrc3.irqReloadCtr&0xF0FF)|((val&0xF)<<8); }
static void vrc3setParamsB000(uint16_t addr, uint8_t val) { (void)addr; vrc3.irqReloadCtr = (vrc3.irqReloadCtr&0x0FFF)|((val&0xF)<<12); }

static void vrc3setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	interrupt &= ~MAPPER_IRQ;
	vrc3.irqEnable_after_ack = !!(val&1);
	vrc3.irqEnable = !!(val&2);
	vrc3.irq8Bit = !!(val&4);
	if(vrc3.irqEnable)
		vrc3.irqCtr = vrc3.irqReloadCtr;
}

static void vrc3setParamsD000(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	interrupt &= ~MAPPER_IRQ;
	vrc3.irqEnable = vrc3.irqEnable_after_ack;
}

static void vrc3setParamsF000(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val&7)<<14);
}

void vrc3initSet8(uint16_t ori_addr)
{
	if(vrc3.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	uint16_t proc_addr = ori_addr&0xF000;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, vrc3setParams8000);
	else if(proc_addr == 0x9000) memInitMapperSetPointer(ori_addr, vrc3setParams9000);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, vrc3setParamsA000);
	else if(proc_addr == 0xB000) memInitMapperSetPointer(ori_addr, vrc3setParamsB000);
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, vrc3setParamsC000);
	else if(proc_addr == 0xD000) memInitMapperSetPointer(ori_addr, vrc3setParamsD000);
	else if(proc_addr == 0xF000) memInitMapperSetPointer(ori_addr, vrc3setParamsF000);
}

void vrc3cycle()
{
	if(vrc3.irqEnable)
	{
		if(vrc3.irq8Bit)
		{
			uint8_t tmp = vrc3.irqCtr&0xFF;
			tmp++;
			vrc3.irqCtr = (vrc3.irqCtr&0xFF00)|tmp;
			if(tmp == 0)
			{
				interrupt |= MAPPER_IRQ;
				vrc3.irqCtr = (vrc3.irqCtr&0xFF00)|(vrc3.irqReloadCtr&0xFF);
			}
		}
		else
		{
			vrc3.irqCtr++;
			if(vrc3.irqCtr == 0)
			{
				interrupt |= MAPPER_IRQ;
				vrc3.irqCtr = vrc3.irqReloadCtr;
			}
		}
	}
}
