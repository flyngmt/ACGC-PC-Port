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
#include "mapper.h"
#include "ppu.h"
#include "cpu.h"
#include "input.h"
#include "fm2play.h"
#include "apu.h"

static get8FuncT memGet8ptr[0x10000];
static set8FuncT memSet8ptr[0x10000];
//region 4000-4020 can set 2 things at once
static set8FuncT memSet8_4000_1[0x20];
static set8FuncT memSet8_4000_2[0x20];
static uint8_t memGet8OpenBus(uint16_t addr);
static void memSet8OpenBus(uint16_t addr, uint8_t val);
static uint8_t memGet8MainMem(uint16_t addr);
static void memSet8MainMem(uint16_t addr, uint8_t val);
static void memSet8_4000(uint16_t addr, uint8_t val);
static get8FuncT memPPUGet8ptr[0x4000];
static set8FuncT memPPUSet8ptr[0x4000];
static uint8_t memChrGet8None(uint16_t addr);
static void memChrSet8None(uint16_t addr, uint8_t val);
static uint8_t Main_Mem[0x800];
uint8_t memLastVal;

void memInit()
{
	memset(Main_Mem,0,0x800);
	memLastVal = 0;
}

void memInitGetSetPointers()
{
	printf("Setting Mem Pointers\n");
	//init memPPUGet8 and memPPUSet8 arrays
	uint32_t addr;
	for(addr = 0; addr < 0x4000; addr++)
	{
		if(addr < 0x2000)
		{
			memPPUGet8ptr[addr] = memChrGet8None;
			memPPUSet8ptr[addr] = memChrSet8None;
		}
		else if(addr < 0x2400)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM0;
			memPPUSet8ptr[addr] = ppuSetVRAM0;
		}
		else if(addr < 0x2800)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM1;
			memPPUSet8ptr[addr] = ppuSetVRAM1;
		}
		else if(addr < 0x2C00)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM2;
			memPPUSet8ptr[addr] = ppuSetVRAM2;
		}
		else if(addr < 0x3000)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM3;
			memPPUSet8ptr[addr] = ppuSetVRAM3;
		}
		else if(addr < 0x3400)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM0;
			memPPUSet8ptr[addr] = ppuSetVRAM0;
		}
		else if(addr < 0x3800)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM1;
			memPPUSet8ptr[addr] = ppuSetVRAM1;
		}
		else if(addr < 0x3C00)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM2;
			memPPUSet8ptr[addr] = ppuSetVRAM2;
		}
		else if(addr < 0x3F00)
		{
			memPPUGet8ptr[addr] = ppuGetVRAM3;
			memPPUSet8ptr[addr] = ppuSetVRAM3;
		}
		else //addr >= 0x3F00
		{
			memPPUGet8ptr[addr] = ppuGetPALRAM;
			if((addr&3) == 0) //copies 00,04,08,0C regs
				memPPUSet8ptr[addr] = ppuSetPALRAMMirror;
			else //normal mem set
				memPPUSet8ptr[addr] = ppuSetPALRAM;
		}
	}
	//init memGet8 and memSet8 arrays
	for(addr = 0; addr < 0x10000; addr++)
	{
		//get pointers
		if(addr >= 0x4020) //set up by mapper
			memGet8ptr[addr] = memGet8OpenBus;
		else if(addr >= 0x4000)
		{
			if(addr == 0x4015)
				memGet8ptr[addr] = apuGetReg15;
			else if(addr == 0x4016)
				memGet8ptr[addr] = inputGetP1;
			else if(addr == 0x4017)
				memGet8ptr[addr] = inputGetP2;
			else //unused
				memGet8ptr[addr] = memGet8OpenBus;
		}
		else if(addr >= 0x2000)
			memGet8ptr[addr] = ppuGet8;
		else
			memGet8ptr[addr] = memGet8MainMem;
		//set pointers
		if(addr >= 0x4020) //set up by mapper
			memSet8ptr[addr] = memSet8OpenBus;
		else if(addr >= 0x4000)
		{
			if(addr == 0x4000) memSet8ptr[addr] = apuSetReg00;
			else if(addr == 0x4001) memSet8ptr[addr] = apuSetReg01;
			else if(addr == 0x4002) memSet8ptr[addr] = apuSetReg02;
			else if(addr == 0x4003) memSet8ptr[addr] = apuSetReg03;
			else if(addr == 0x4004) memSet8ptr[addr] = apuSetReg04;
			else if(addr == 0x4005) memSet8ptr[addr] = apuSetReg05;
			else if(addr == 0x4006) memSet8ptr[addr] = apuSetReg06;
			else if(addr == 0x4007) memSet8ptr[addr] = apuSetReg07;
			else if(addr == 0x4008) memSet8ptr[addr] = apuSetReg08;
			else if(addr == 0x400A) memSet8ptr[addr] = apuSetReg0A;
			else if(addr == 0x400B) memSet8ptr[addr] = apuSetReg0B;
			else if(addr == 0x400C) memSet8ptr[addr] = apuSetReg0C;
			else if(addr == 0x400E) memSet8ptr[addr] = apuSetReg0E;
			else if(addr == 0x400F) memSet8ptr[addr] = apuSetReg0F;
			else if(addr == 0x4010) memSet8ptr[addr] = apuSetReg10;
			else if(addr == 0x4011) memSet8ptr[addr] = apuSetReg11;
			else if(addr == 0x4012) memSet8ptr[addr] = apuSetReg12;
			else if(addr == 0x4013) memSet8ptr[addr] = apuSetReg13;
			else if(addr == 0x4014) memSet8ptr[addr] = cpuDoOAM_DMA;
			else if(addr == 0x4015) memSet8ptr[addr] = apuSetReg15;
			else if(addr == 0x4016) memSet8ptr[addr] = inputSet;
			else if(addr == 0x4017) memSet8ptr[addr] = apuSetReg17;
			else //unused
				memSet8ptr[addr] = memSet8OpenBus;
		}
		else if(addr >= 0x2000)
			memSet8ptr[addr] = ppuSet8;
		else
			memSet8ptr[addr] = memSet8MainMem;
	}
}

void memInitMapperGetPointer(uint16_t addr, get8FuncT func)
{
	if(addr < 0x4020)
		printf("Ignored mapper get for address %04x\n", addr);
	else
	{
		//printf("Set mapper get for address %04x\n", addr);
		memGet8ptr[addr] = func;
	}
}

void memInitMapperSetPointer(uint16_t addr, set8FuncT func)
{
	if(addr < 0x4020)
	{
		if(addr >= 0x4000)
		{
			//everything starting from 0x4000 to 0x401F has to
			//go to mapper, even if its actively used by more
			if(memSet8ptr[addr] == memSet8OpenBus)
			{
				//no need for wrapper function in this case
				memSet8ptr[addr] = func;
			}
			else
			{
				uint8_t reg = addr&0x1F;
				//address used in 2 functions, set up wrapper
				memSet8_4000_1[reg] = func;
				//back up original call address for this reg
				memSet8_4000_2[reg] = memSet8ptr[addr];
				//jump to wrapper function calling both
				memSet8ptr[addr] = memSet8_4000;
				printf("Set mapper wrapper set for address %04x\n", addr);
			}
		}
		else
			printf("Ignored mapper set for address %04x\n", addr);
	}
	else
	{
		memSet8ptr[addr] = func;
		//printf("Set mapper set for address %04x\n", addr);
	}
}

void memInitMapperPPUGetPointer(uint16_t addr, get8FuncT func)
{
	if(addr >= 0x4000)
		printf("Ignored mapper ppu get for address %04x\n", addr);
	else
	{
		//printf("Set mapper get for address %04x\n", addr);
		memPPUGet8ptr[addr] = func;
	}
}

void memInitMapperPPUSetPointer(uint16_t addr, set8FuncT func)
{
	if(addr >= 0x4000)
		printf("Ignored mapper ppu set for address %04x\n", addr);
	else
	{
		//printf("Set mapper get for address %04x\n", addr);
		memPPUSet8ptr[addr] = func;
	}
}

static uint8_t memGet8OpenBus(uint16_t addr)
{
	(void)addr;
	return memLastVal;
}

static void memSet8OpenBus(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
}

static uint8_t memChrGet8None(uint16_t addr)
{
	(void)addr;
	return 0;
}

static void memChrSet8None(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
}

static uint8_t memGet8MainMem(uint16_t addr)
{
	return Main_Mem[addr&0x7FF];
}

static void memSet8MainMem(uint16_t addr, uint8_t val)
{
	Main_Mem[addr&0x7FF] = val;
}

static void memSet8_4000(uint16_t addr, uint8_t val)
{
	uint8_t reg = addr&0x1F;
	memSet8_4000_1[reg](addr, val);
	memSet8_4000_2[reg](addr, val);
}

uint8_t memGet8(uint16_t addr)
{
	uint8_t val = memGet8ptr[addr](addr);
	memLastVal = val;
	return val;
}

void memSet8(uint16_t addr, uint8_t val)
{
	memSet8ptr[addr](addr, val);
	memLastVal = val;
}

uint8_t memPPUGet8(uint16_t addr)
{
	return memPPUGet8ptr[addr](addr);
}

void memPPUSet8(uint16_t addr, uint8_t val)
{
	memPPUSet8ptr[addr](addr, val);
}

#define DEBUG_MEM_DUMP 0

void memDumpMainMem()
{
	#if DEBUG_MEM_DUMP
	FILE *f = fopen("MainMem.bin","wb");
	if(f)
	{
		fwrite(Main_Mem,1,0x800,f);
		fclose(f);
	}
	ppuDumpMem();
	#endif
}

