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
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

void m33init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin, prgROMsizeIn);
	prg8setBank2(prgROMsizeIn - 0x4000);
	prg8setBank3(prgROMsizeIn - 0x2000);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr1init(chrROMin, chrROMsizeIn);
	printf("Mapper 33 inited\n");
}

static void m33setParams8XX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank0((val&0x3F)<<13);
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

static void m33setParams8XX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank1((val&0x3F)<<13);
}

static void m33setParams8XX2(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr1setBank0((val<<11)|0x000);
	chr1setBank1((val<<11)|0x400);
}

static void m33setParams8XX3(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr1setBank2((val<<11)|0x000);
	chr1setBank3((val<<11)|0x400);
}

static void m33setParamsAXX0(uint16_t addr, uint8_t val) { (void)addr; chr1setBank4(val<<10); }
static void m33setParamsAXX1(uint16_t addr, uint8_t val) { (void)addr; chr1setBank5(val<<10); }
static void m33setParamsAXX2(uint16_t addr, uint8_t val) { (void)addr; chr1setBank6(val<<10); }
static void m33setParamsAXX3(uint16_t addr, uint8_t val) { (void)addr; chr1setBank7(val<<10); }

void m33initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xA003;
	if(proc_addr == 0x8000)
		memInitMapperSetPointer(ori_addr, m33setParams8XX0);
	else if(proc_addr == 0x8001)
		memInitMapperSetPointer(ori_addr, m33setParams8XX1);
	else if(proc_addr == 0x8002)
		memInitMapperSetPointer(ori_addr, m33setParams8XX2);
	else if(proc_addr == 0x8003)
		memInitMapperSetPointer(ori_addr, m33setParams8XX3);
	else if(proc_addr == 0xA000)
		memInitMapperSetPointer(ori_addr, m33setParamsAXX0);
	else if(proc_addr == 0xA001)
		memInitMapperSetPointer(ori_addr, m33setParamsAXX1);
	else if(proc_addr == 0xA002)
		memInitMapperSetPointer(ori_addr, m33setParamsAXX2);
	else if(proc_addr == 0xA003)
		memInitMapperSetPointer(ori_addr, m33setParamsAXX3);
}
