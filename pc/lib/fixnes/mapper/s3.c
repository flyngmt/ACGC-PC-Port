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
	bool TmpWrite;
	bool irqCtrEnable;
} s3;

extern uint8_t interrupt;

void s3init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr2init(chrROMin,chrROMsizeIn);
	s3.irqCtr = 0;
	s3.TmpWrite = false;
	s3.irqCtrEnable = false;
	printf("Sunsoft-3 inited\n");
}

static void s3setParams8800(uint16_t addr, uint8_t val) { (void)addr; chr2setBank0(val<<11); }
static void s3setParams9800(uint16_t addr, uint8_t val) { (void)addr; chr2setBank1(val<<11); }
static void s3setParamsA800(uint16_t addr, uint8_t val) { (void)addr; chr2setBank2(val<<11); }
static void s3setParamsB800(uint16_t addr, uint8_t val) { (void)addr; chr2setBank3(val<<11); }

static void s3setParamsC800(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!s3.TmpWrite)
	{
		s3.TmpWrite = true;
		s3.irqCtr &= 0xFF;
		s3.irqCtr |= (val<<8);
	}
	else
	{
		s3.TmpWrite = false;
		s3.irqCtr &= ~0xFF;
		s3.irqCtr |= val;
	}
}

static void s3setParamsD800(uint16_t addr, uint8_t val)
{
	(void)addr;
	s3.TmpWrite = false;
	interrupt &= ~MAPPER_IRQ;
	s3.irqCtrEnable = !!(val&0x10);
}

static void s3setParamsE800(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(val&3)
	{
		case 0:
			ppuSetNameTblVertical();
			break;
		case 1:
			ppuSetNameTblHorizontal();
			break;
		case 2:
			ppuSetNameTblSingleLower();
			break;
		case 3:
			ppuSetNameTblSingleUpper();
			break;
	}
}

static void s3setParamsF800(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0(val<<14);
}

void s3initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xF800;
	if(proc_addr == 0x8800) memInitMapperSetPointer(ori_addr, s3setParams8800);
	else if(proc_addr == 0x9800) memInitMapperSetPointer(ori_addr, s3setParams9800);
	else if(proc_addr == 0xA800) memInitMapperSetPointer(ori_addr, s3setParamsA800);
	else if(proc_addr == 0xB800) memInitMapperSetPointer(ori_addr, s3setParamsB800);
	else if(proc_addr == 0xC800) memInitMapperSetPointer(ori_addr, s3setParamsC800);
	else if(proc_addr == 0xD800) memInitMapperSetPointer(ori_addr, s3setParamsD800);
	else if(proc_addr == 0xE800) memInitMapperSetPointer(ori_addr, s3setParamsE800);
	else if(proc_addr == 0xF800) memInitMapperSetPointer(ori_addr, s3setParamsF800);
}

void s3cycle()
{
	if(s3.irqCtrEnable)
	{
		s3.irqCtr--;
		if(s3.irqCtr == 0xFFFF)
		{
			s3.irqCtrEnable = false;
			interrupt |= MAPPER_IRQ;
		}
	}
}
