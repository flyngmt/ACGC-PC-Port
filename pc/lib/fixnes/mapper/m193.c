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

void m193init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg8init(prgROMin,prgROMsizeIn);
	prg8setBank1(prgROMsizeIn-0x6000);
	prg8setBank2(prgROMsizeIn-0x4000);
	prg8setBank3(prgROMsizeIn-0x2000);
	chr2init(chrROMin,chrROMsizeIn);
	//default state of this mapper?
	ppuSetNameTblVertical();
	printf("Mapper 193 inited\n");
}

static void m193setParams6000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank0(((val>>1)&0xFE)<<11); chr2setBank1(((val>>1)|0x01)<<11); }
static void m193setParams6001(uint16_t addr, uint8_t val) { (void)addr; chr2setBank2((val>>1)<<11); }
static void m193setParams6002(uint16_t addr, uint8_t val) { (void)addr; chr2setBank3((val>>1)<<11); }
static void m193setParams6003(uint16_t addr, uint8_t val) { (void)addr; prg8setBank0(val<<13); }
void m193initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE003;
	if(proc_addr == 0x6000) memInitMapperSetPointer(ori_addr, m193setParams6000);
	else if(proc_addr == 0x6001) memInitMapperSetPointer(ori_addr, m193setParams6001);
	else if(proc_addr == 0x6002) memInitMapperSetPointer(ori_addr, m193setParams6002);
	else if(proc_addr == 0x6003) memInitMapperSetPointer(ori_addr, m193setParams6003);
}
