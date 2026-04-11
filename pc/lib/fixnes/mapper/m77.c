/*
 * Copyright (C) 2019 FIX94
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

void m77init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg32init(prgROMin,prgROMsizeIn);
	chr2init(chrROMin,chrROMsizeIn);
	//extra chr ram
	chr8init(NULL,0);
	printf("Mapper 77 inited\n");
}

static void m77setParams8000(uint16_t addr, uint8_t val) { (void)addr; chr2setBank0(((val>>4)&0xF)<<11); prg32setBank0((val&0xF)<<15); }
void m77initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m77setParams8000);
}

void m77initPPUGet8(uint16_t addr)
{
	if(addr < 0x800) //ROM
		chr2initPPUGet8(addr);
	else if(addr < 0x2000) //RAM
		chr8initPPUGet8(addr);
}

void m77initPPUSet8(uint16_t addr)
{
	if(addr < 0x800) //ROM
		chr2initPPUSet8(addr);
	else if(addr < 0x2000) //RAM
		chr8initPPUSet8(addr);
}
