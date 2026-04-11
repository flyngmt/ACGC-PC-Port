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

static bool s1_usesChrRAM;
void s1init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr4init(chrROMin,chrROMsizeIn);
	if(chrROMin && chrROMsizeIn)
		s1_usesChrRAM = false;
	else
	{
		s1_usesChrRAM = true;
		chr4setBank0(0x0000); chr4setBank1(0x1000);
	}
	printf("Sunsoft-1 inited\n");
}

static void s1setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr4setBank0((val&7)<<12);
	chr4setBank1(((val>>4)&7)<<12);
}

static void s1setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0(((val>>4)&7)<<14);
}

void s1initSet8(uint16_t addr)
{
	if(s1_usesChrRAM) //Fantasy Zone
	{
		if(addr >= 0x8000)
			memInitMapperSetPointer(addr, s1setParams8XXX);
	}
	else //All the others set to 184
	{
		if(addr >= 0x6000 && addr < 0x8000)
			memInitMapperSetPointer(addr, s1setParams6XXX);
	} 
}
