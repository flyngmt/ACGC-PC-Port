/*
 * Copyright (C) 2018 FIX94
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
#include "../mapper_h/common.h"

void m31init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg4init(prgROMin, prgROMsizeIn);
	prg4setBank7(prgROMsizeIn - 0x1000);
	(void)prgRAMin; (void)prgRAMsizeIn;
	chr8init(chrROMin,chrROMsizeIn);
	printf("Mapper 31 inited\n");
}

static void m31setParams5000(uint16_t addr, uint8_t val) { (void)addr; prg4setBank0(val<<12); }
static void m31setParams5001(uint16_t addr, uint8_t val) { (void)addr; prg4setBank1(val<<12); }
static void m31setParams5002(uint16_t addr, uint8_t val) { (void)addr; prg4setBank2(val<<12); }
static void m31setParams5003(uint16_t addr, uint8_t val) { (void)addr; prg4setBank3(val<<12); }
static void m31setParams5004(uint16_t addr, uint8_t val) { (void)addr; prg4setBank4(val<<12); }
static void m31setParams5005(uint16_t addr, uint8_t val) { (void)addr; prg4setBank5(val<<12); }
static void m31setParams5006(uint16_t addr, uint8_t val) { (void)addr; prg4setBank6(val<<12); }
static void m31setParams5007(uint16_t addr, uint8_t val) { (void)addr; prg4setBank7(val<<12); }
void m31initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xF007;
	if(proc_addr == 0x5000) memInitMapperSetPointer(ori_addr, m31setParams5000);
	else if(proc_addr == 0x5001) memInitMapperSetPointer(ori_addr, m31setParams5001);
	else if(proc_addr == 0x5002) memInitMapperSetPointer(ori_addr, m31setParams5002);
	else if(proc_addr == 0x5003) memInitMapperSetPointer(ori_addr, m31setParams5003);
	else if(proc_addr == 0x5004) memInitMapperSetPointer(ori_addr, m31setParams5004);
	else if(proc_addr == 0x5005) memInitMapperSetPointer(ori_addr, m31setParams5005);
	else if(proc_addr == 0x5006) memInitMapperSetPointer(ori_addr, m31setParams5006);
	else if(proc_addr == 0x5007) memInitMapperSetPointer(ori_addr, m31setParams5007);
}
