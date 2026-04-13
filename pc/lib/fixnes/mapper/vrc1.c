/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static uint32_t vrc1_curCHRBank0;
static uint32_t vrc1_curCHRBank1;

void vrc1init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	prg8setBank3(prgROMsizeIn - 0x2000);
	(void)prgRAMin; (void)prgRAMsizeIn;
	chr4init(chrROMin,chrROMsizeIn);
	vrc1_curCHRBank0 = 0;
	vrc1_curCHRBank1 = 0;
	printf("VRC1 inited\n");
}

static void vrc1setParams8000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0((val&0xF)<<13); }
static void vrc1setParamsA000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank1((val&0xF)<<13); }
static void vrc1setParamsC000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank2((val&0xF)<<13); }

static void vrc1setParams9000(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
		if((val&0x1) != 0)
			ppuSetNameTblHorizontal();
		else
			ppuSetNameTblVertical();
	}
	if((val&0x2) != 0) //set high bit
		vrc1_curCHRBank0 |= 0x10;
	else //clear high bit
		vrc1_curCHRBank0 &= ~0x10;
	chr4setBank0(vrc1_curCHRBank0<<12);
	if((val&0x4) != 0) //set high bit
		vrc1_curCHRBank1 |= 0x10;
	else //clear high bit
		vrc1_curCHRBank1 &= ~0x10;
	chr4setBank1(vrc1_curCHRBank1<<12);
}
static void vrc1setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc1_curCHRBank0 = (vrc1_curCHRBank0&~0xF) | (val&0xF);
	chr4setBank0(vrc1_curCHRBank0<<12);
}
static void vrc1setParamsF000(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc1_curCHRBank1 = (vrc1_curCHRBank1&~0xF) | (val&0xF);
	chr4setBank1(vrc1_curCHRBank1<<12);
}

void vrc1initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xF000;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, vrc1setParams8000);
	else if(proc_addr == 0x9000) memInitMapperSetPointer(ori_addr, vrc1setParams9000);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, vrc1setParamsA000);
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, vrc1setParamsC000);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, vrc1setParamsE000);
	else if(proc_addr == 0xF000) memInitMapperSetPointer(ori_addr, vrc1setParamsF000);
}
