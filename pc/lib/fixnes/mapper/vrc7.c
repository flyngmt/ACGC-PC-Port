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
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../audio_vrc7.h"
#include "../vrc_irq.h"
#include "../mapper_h/common.h"

static bool vrc7_usesPrgRAM;
void vrc7init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	prg8setBank3(prgROMsizeIn - 0x2000);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		vrc7_usesPrgRAM = true;
	}
	else
		vrc7_usesPrgRAM = false;
	chr1init(chrROMin,chrROMsizeIn);
	vrc7AudioInit();
	vrc_irq_init();
	printf("VRC7 inited\n");
}

void vrc7initGet8(uint16_t addr)
{
	if(vrc7_usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

static void vrc7setParams8000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0((val&0x3F)<<13); }
static void vrc7setParams8010(uint16_t addr, uint8_t val) { (void)addr; prg8setBank1((val&0x3F)<<13); }
static void vrc7setParams9000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank2((val&0x3F)<<13); }

static void vrc7setParamsA000(uint16_t addr, uint8_t val) { (void)addr; chr1setBank0(val<<10); }
static void vrc7setParamsA010(uint16_t addr, uint8_t val) { (void)addr; chr1setBank1(val<<10); }
static void vrc7setParamsB000(uint16_t addr, uint8_t val) { (void)addr; chr1setBank2(val<<10); }
static void vrc7setParamsB010(uint16_t addr, uint8_t val) { (void)addr; chr1setBank3(val<<10); }
static void vrc7setParamsC000(uint16_t addr, uint8_t val) { (void)addr; chr1setBank4(val<<10); }
static void vrc7setParamsC010(uint16_t addr, uint8_t val) { (void)addr; chr1setBank5(val<<10); }
static void vrc7setParamsD000(uint16_t addr, uint8_t val) { (void)addr; chr1setBank6(val<<10); }
static void vrc7setParamsD010(uint16_t addr, uint8_t val) { (void)addr; chr1setBank7(val<<10); }

static void vrc7setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
		if((val & 0x3) == 0)
			ppuSetNameTblVertical();
		else if((val & 0x3) == 1)
			ppuSetNameTblHorizontal();
		else if((val & 0x3) == 2)
			ppuSetNameTblSingleLower();
		else //if((val & 0x3) == 3)
			ppuSetNameTblSingleUpper();
	}
}

void vrc7initSet8(uint16_t ori_addr)
{
	if(vrc7_usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	uint16_t proc_addr = ori_addr&0xF038;
	if(proc_addr == 0x8000)
		memInitMapperSetPointer(ori_addr, vrc7setParams8000);
	else if(proc_addr == 0x8010 || proc_addr == 0x8008)
		memInitMapperSetPointer(ori_addr, vrc7setParams8010);
	else if(proc_addr == 0x9000)
		memInitMapperSetPointer(ori_addr, vrc7setParams9000);
	else if(proc_addr == 0x9010 || proc_addr == 0x9008)
		memInitMapperSetPointer(ori_addr, vrc7AudioSet9010);
	else if(proc_addr == 0x9030 || proc_addr == 0x9028)
		memInitMapperSetPointer(ori_addr, vrc7AudioSet9030);
	else if(proc_addr == 0xA000)
		memInitMapperSetPointer(ori_addr, vrc7setParamsA000);
	else if(proc_addr == 0xA010 || proc_addr == 0xA008)
		memInitMapperSetPointer(ori_addr, vrc7setParamsA010);
	else if(proc_addr == 0xB000)
		memInitMapperSetPointer(ori_addr, vrc7setParamsB000);
	else if(proc_addr == 0xB010 || proc_addr == 0xB008)
		memInitMapperSetPointer(ori_addr, vrc7setParamsB010);
	else if(proc_addr == 0xC000)
		memInitMapperSetPointer(ori_addr, vrc7setParamsC000);
	else if(proc_addr == 0xC010 || proc_addr == 0xC008)
		memInitMapperSetPointer(ori_addr, vrc7setParamsC010);
	else if(proc_addr == 0xD000)
		memInitMapperSetPointer(ori_addr, vrc7setParamsD000);
	else if(proc_addr == 0xD010 || proc_addr == 0xD008)
		memInitMapperSetPointer(ori_addr, vrc7setParamsD010);
	else if(proc_addr == 0xE000)
		memInitMapperSetPointer(ori_addr, vrc7setParamsE000);
	else if(proc_addr == 0xE010 || proc_addr == 0xE008)
		memInitMapperSetPointer(ori_addr, vrc_irq_setlatch);
	else if(proc_addr == 0xF000)
		memInitMapperSetPointer(ori_addr, vrc_irq_control);
	else if(proc_addr == 0xF010 || proc_addr == 0xF008)
		memInitMapperSetPointer(ori_addr, vrc_irq_ack);
}
