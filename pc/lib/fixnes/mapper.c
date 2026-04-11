/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "mapper.h"
#include "mapperList.h"
#include "mapper_h/nsf.h"
#include "mapper_h/fds.h"
#include "mapper_h/m32.h"
#include "mapper_h/p16c8.h"
#include "mapper_h/common.h"
#include "ppu.h"
#include "mem.h"

cycleFuncT mapperCycle;
resetFuncT mapperReset;
uint8_t mapperChrMode;

static void mapperNone() { };

bool mapperInit(uint8_t mapper, uint8_t *prgROM, uint32_t prgROMsize, uint8_t *prgRAM, uint32_t prgRAMsize, uint8_t *chrROM, uint32_t chrROMsize)
{
	if(mapperList[mapper].initF == NULL)
	{
		printf("Unsupported Mapper %i!\n", mapper);
		return false;
	}
	memInitGetSetPointers(); //pre-set get8/set8
	mapperList[mapper].initF(prgROM, prgROMsize, prgRAM, prgRAMsize, chrROM, chrROMsize);
	uint32_t addr;
	for(addr = 0; addr < 0x4000; addr++)
	{
		mapperList[mapper].initPPUGet8F(addr);
		mapperList[mapper].initPPUSet8F(addr);
	}
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		mapperList[mapper].initGet8F(addr);
		mapperList[mapper].initSet8F(addr);
	}
	//just have something assigned
	if(mapperList[mapper].cycleFuncF == NULL)
		mapperCycle = mapperNone;
	else
		mapperCycle = mapperList[mapper].cycleFuncF;
	//just have something assigned
	if(mapperList[mapper].resetFuncF == NULL)
		mapperReset = mapperNone;
	else
		mapperReset = mapperList[mapper].resetFuncF;
	mapperChrMode = 0;
	return true;
}

bool mapperInitNSF(uint8_t *nsfBIN, uint32_t nsfBINsize, uint8_t *prgRAM, uint32_t prgRAMsize)
{
	memInitGetSetPointers(); //pre-set get8/set8
	nsfinit(nsfBIN, nsfBINsize, prgRAM, prgRAMsize);
	uint32_t addr;
	//common CHR RAM for NSF
	for(addr = 0; addr < 0x4000; addr++)
	{
		chr8initPPUGet8(addr);
		chr8initPPUSet8(addr);
	}
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		nsfinitGet8(addr);
		nsfinitSet8(addr);
	}
	mapperCycle = nsfcycle;
	mapperReset = mapperNone;
	mapperChrMode = 0;
	return true;
}

#ifdef __LIBRETRO__
FILE *doOpenFDSBIOS();
#endif

static uint8_t fdsBIOS[0x2000];
bool mapperInitFDS(uint8_t *fdsFile, bool fdsSideB, uint8_t *prgRAM, uint32_t prgRAMsize)
{
	if(fdsFile == NULL)
	{
		printf("No FDS loaded!\n");
		return false;
	}
#ifndef __LIBRETRO__
	FILE *f = fopen("disksys.rom","rb");
#else
	FILE *f = doOpenFDSBIOS();
#endif
	if(f == NULL)
	{
		printf("disksys.rom not found!\n");
		return false;
	}
	fseek(f,0,SEEK_END);
	size_t fsize = ftell(f);
	rewind(f);
	if(fsize != 0x2000)
	{
		printf("disksys.rom has a wrong size, is %i bytes, should be 8192 bytes!\n", fsize);
		fclose(f);
		return false;
	}
	fread(fdsBIOS, 1, 0x2000, f);
	fclose(f);
	memInitGetSetPointers(); //pre-set get8/set8
	fdsinit(fdsBIOS, fsize, fdsFile, fdsSideB, prgRAM, prgRAMsize);
	uint32_t addr;
	//common CHR RAM for FDS
	for(addr = 0; addr < 0x4000; addr++)
	{
		chr8initPPUGet8(addr);
		chr8initPPUSet8(addr);
	}
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		fdsinitGet8(addr);
		fdsinitSet8(addr);
	}
	mapperCycle = fdscycle;
	mapperReset = mapperNone;
	mapperChrMode = 0;
	return true;
}

uint32_t mapperGetAndValue(uint32_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	return v;
}
