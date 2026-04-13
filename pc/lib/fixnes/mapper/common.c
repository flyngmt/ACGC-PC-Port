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
#include "../mapper_h/common.h"
#include "../mapper.h"
#include "../mem.h"


static struct {
	uint8_t *prgROM;
	uint32_t prgROMand;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr,
			*prgROMBank2Ptr, *prgROMBank3Ptr,
			*prgROMBank4Ptr, *prgROMBank5Ptr,
			*prgROMBank6Ptr, *prgROMBank7Ptr;
} prg4;

void prg4init(uint8_t *prgROM, uint32_t prgROMsize)
{
	prg4.prgROM = prgROM;
	prg4.prgROMand = mapperGetAndValue(prgROMsize);
	prg4setBank0(0); prg4setBank1(0); prg4setBank2(0); prg4setBank3(0);
	prg4setBank4(0); prg4setBank5(0); prg4setBank6(0); prg4setBank7(0);
	printf("Using Common PRG ROM (%iKB Total) 4KB Banks\n", (prgROMsize>>10));
}

static uint8_t prg4GetROM0(uint16_t addr) { return prg4.prgROMBank0Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM1(uint16_t addr) { return prg4.prgROMBank1Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM2(uint16_t addr) { return prg4.prgROMBank2Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM3(uint16_t addr) { return prg4.prgROMBank3Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM4(uint16_t addr) { return prg4.prgROMBank4Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM5(uint16_t addr) { return prg4.prgROMBank5Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM6(uint16_t addr) { return prg4.prgROMBank6Ptr[addr&0xFFF]; }
static uint8_t prg4GetROM7(uint16_t addr) { return prg4.prgROMBank7Ptr[addr&0xFFF]; }

void prg4initGet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	else if(addr < 0x9000) memInitMapperGetPointer(addr, prg4GetROM0);
	else if(addr < 0xA000) memInitMapperGetPointer(addr, prg4GetROM1);
	else if(addr < 0xB000) memInitMapperGetPointer(addr, prg4GetROM2);
	else if(addr < 0xC000) memInitMapperGetPointer(addr, prg4GetROM3);
	else if(addr < 0xD000) memInitMapperGetPointer(addr, prg4GetROM4);
	else if(addr < 0xE000) memInitMapperGetPointer(addr, prg4GetROM5);
	else if(addr < 0xF000) memInitMapperGetPointer(addr, prg4GetROM6);
	else memInitMapperGetPointer(addr, prg4GetROM7);
}

void prg4setBank0(uint32_t val) { prg4.prgROMBank0Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank1(uint32_t val) { prg4.prgROMBank1Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank2(uint32_t val) { prg4.prgROMBank2Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank3(uint32_t val) { prg4.prgROMBank3Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank4(uint32_t val) { prg4.prgROMBank4Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank5(uint32_t val) { prg4.prgROMBank5Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank6(uint32_t val) { prg4.prgROMBank6Ptr = prg4.prgROM+(val&prg4.prgROMand); }
void prg4setBank7(uint32_t val) { prg4.prgROMBank7Ptr = prg4.prgROM+(val&prg4.prgROMand); }




static struct {
	uint8_t *prgROM;
	uint32_t prgROMand;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr,
			*prgROMBank2Ptr, *prgROMBank3Ptr;
} prg8;

void prg8init(uint8_t *prgROM, uint32_t prgROMsize)
{
	prg8.prgROM = prgROM;
	prg8.prgROMand = mapperGetAndValue(prgROMsize);
	prg8setBank0(0); prg8setBank1(0);
	prg8setBank2(0); prg8setBank3(0);
	printf("Using Common PRG ROM (%iKB Total) 8KB Banks\n", (prgROMsize>>10));
}

static uint8_t prg8GetROM0(uint16_t addr) { return prg8.prgROMBank0Ptr[addr&0x1FFF]; }
static uint8_t prg8GetROM1(uint16_t addr) { return prg8.prgROMBank1Ptr[addr&0x1FFF]; }
static uint8_t prg8GetROM2(uint16_t addr) { return prg8.prgROMBank2Ptr[addr&0x1FFF]; }
static uint8_t prg8GetROM3(uint16_t addr) { return prg8.prgROMBank3Ptr[addr&0x1FFF]; }

void prg8initGet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	else if(addr < 0xA000) memInitMapperGetPointer(addr, prg8GetROM0);
	else if(addr < 0xC000) memInitMapperGetPointer(addr, prg8GetROM1);
	else if(addr < 0xE000) memInitMapperGetPointer(addr, prg8GetROM2);
	else memInitMapperGetPointer(addr, prg8GetROM3);
}

void prg8setBank0(uint32_t val) { prg8.prgROMBank0Ptr = prg8.prgROM+(val&prg8.prgROMand); }
void prg8setBank1(uint32_t val) { prg8.prgROMBank1Ptr = prg8.prgROM+(val&prg8.prgROMand); }
void prg8setBank2(uint32_t val) { prg8.prgROMBank2Ptr = prg8.prgROM+(val&prg8.prgROMand); }
void prg8setBank3(uint32_t val) { prg8.prgROMBank3Ptr = prg8.prgROM+(val&prg8.prgROMand); }



static struct {
	uint8_t *prgROM;
	uint32_t prgROMand;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr;
} prg16;

void prg16init(uint8_t *prgROM, uint32_t prgROMsize)
{
	prg16.prgROM = prgROM;
	prg16.prgROMand = mapperGetAndValue(prgROMsize);
	prg16setBank0(0); prg16setBank1(0);
	if(prg16.prgROMand == 0x3FFF)
		printf("Using Common PRG ROM Fixed 16KB Bank\n");
	else //normal banked pointer
		printf("Using Common PRG ROM (%iKB Total) 16KB Banks\n", (prgROMsize>>10));
}

static uint8_t prg16GetROM0(uint16_t addr) { return prg16.prgROMBank0Ptr[addr&0x3FFF]; }
static uint8_t prg16GetROM1(uint16_t addr) { return prg16.prgROMBank1Ptr[addr&0x3FFF]; }

void prg16initGet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	else if(addr < 0xC000) memInitMapperGetPointer(addr, prg16GetROM0);
	else memInitMapperGetPointer(addr, prg16GetROM1);
}

void prg16setBank0(uint32_t val) { prg16.prgROMBank0Ptr = prg16.prgROM+(val&prg16.prgROMand); }
void prg16setBank1(uint32_t val) { prg16.prgROMBank1Ptr = prg16.prgROM+(val&prg16.prgROMand); }



static struct {
	uint8_t *prgROM;
	uint32_t prgROMand;
	uint8_t *prgROMBank0Ptr;
} prg32;

void prg32init(uint8_t *prgROM, uint32_t prgROMsize)
{
	prg32.prgROM = prgROM;
	prg32.prgROMand = mapperGetAndValue(prgROMsize);
	prg32setBank0(0);
	if(prg32.prgROMand == 0x3FFF)
		printf("Using Common PRG ROM Fixed 16KB Bank\n");
	else if(prg32.prgROMand == 0x7FFF)
		printf("Using Common PRG ROM Fixed 32KB Bank\n");
	else //normal banked pointer
		printf("Using Common PRG ROM (%iKB Total) 32KB Bank\n", (prgROMsize>>10));
}

static uint8_t prg32_16GetROM0(uint16_t addr) { return prg32.prgROM[addr&0x3FFF]; }
static uint8_t prg32GetROM0(uint16_t addr) { return prg32.prgROMBank0Ptr[addr&0x7FFF]; }

void prg32initGet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	else if(prg32.prgROMand == 0x3FFF) //special case
		memInitMapperGetPointer(addr, prg32_16GetROM0);
	else //normal banked pointer
		memInitMapperGetPointer(addr, prg32GetROM0);
}

void prg32setBank0(uint32_t val) { prg32.prgROMBank0Ptr = prg32.prgROM+(val&prg32.prgROMand); }



static uint8_t *prgRAM8;
void prgRAM8init(uint8_t *prgRAM)
{
	prgRAM8 = prgRAM;
	printf("Using Common PRG RAM Fixed 8KB Bank\n");
}
static uint8_t prgRAM8get8(uint16_t addr)
{
	return prgRAM8[addr&0x1FFF];
}
void prgRAM8initGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperGetPointer(addr, prgRAM8get8);
}

static void prgRAM8set8(uint16_t addr, uint8_t val)
{
	prgRAM8[addr&0x1FFF] = val;
}
void prgRAM8initSet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, prgRAM8set8);
}


static uint8_t common_chrRAM[0x2000];

static struct {
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t *chrROMBank0Ptr, *chrROMBank1Ptr,
			*chrROMBank2Ptr, *chrROMBank3Ptr,
			*chrROMBank4Ptr, *chrROMBank5Ptr,
			*chrROMBank6Ptr, *chrROMBank7Ptr;
} chr1;

void chr1init(uint8_t *chrROM, uint32_t chrROMsize)
{
	if(chrROM == NULL)
	{
		memset(common_chrRAM, 0, 0x2000);
		chr1.chrROM = common_chrRAM;
		chr1.chrROMand = 0x1FFF;
		printf("Using Common CHR RAM (8KB Total) 1KB Banks\n");
	}
	else
	{
		chr1.chrROM = chrROM;
		chr1.chrROMand = mapperGetAndValue(chrROMsize);
		printf("Using Common CHR ROM (%iKB Total) 1KB Banks\n", (chrROMsize>>10));
	}
	chr1setBank0(0); chr1setBank1(0);
	chr1setBank2(0); chr1setBank3(0);
	chr1setBank4(0); chr1setBank5(0);
	chr1setBank6(0); chr1setBank7(0);
}

static uint8_t chr1getROM0(uint16_t addr) { return chr1.chrROMBank0Ptr[addr&0x3FF]; }
static uint8_t chr1getROM1(uint16_t addr) { return chr1.chrROMBank1Ptr[addr&0x3FF]; }
static uint8_t chr1getROM2(uint16_t addr) { return chr1.chrROMBank2Ptr[addr&0x3FF]; }
static uint8_t chr1getROM3(uint16_t addr) { return chr1.chrROMBank3Ptr[addr&0x3FF]; }
static uint8_t chr1getROM4(uint16_t addr) { return chr1.chrROMBank4Ptr[addr&0x3FF]; }
static uint8_t chr1getROM5(uint16_t addr) { return chr1.chrROMBank5Ptr[addr&0x3FF]; }
static uint8_t chr1getROM6(uint16_t addr) { return chr1.chrROMBank6Ptr[addr&0x3FF]; }
static uint8_t chr1getROM7(uint16_t addr) { return chr1.chrROMBank7Ptr[addr&0x3FF]; }

static void chr1setRAM0(uint16_t addr, uint8_t val) { chr1.chrROMBank0Ptr[addr&0x3FF] = val; }
static void chr1setRAM1(uint16_t addr, uint8_t val) { chr1.chrROMBank1Ptr[addr&0x3FF] = val; }
static void chr1setRAM2(uint16_t addr, uint8_t val) { chr1.chrROMBank2Ptr[addr&0x3FF] = val; }
static void chr1setRAM3(uint16_t addr, uint8_t val) { chr1.chrROMBank3Ptr[addr&0x3FF] = val; }
static void chr1setRAM4(uint16_t addr, uint8_t val) { chr1.chrROMBank4Ptr[addr&0x3FF] = val; }
static void chr1setRAM5(uint16_t addr, uint8_t val) { chr1.chrROMBank5Ptr[addr&0x3FF] = val; }
static void chr1setRAM6(uint16_t addr, uint8_t val) { chr1.chrROMBank6Ptr[addr&0x3FF] = val; }
static void chr1setRAM7(uint16_t addr, uint8_t val) { chr1.chrROMBank7Ptr[addr&0x3FF] = val; }

void chr1initPPUGet8(uint16_t addr)
{
	if(addr < 0x400) memInitMapperPPUGetPointer(addr, chr1getROM0);
	else if(addr < 0x800) memInitMapperPPUGetPointer(addr, chr1getROM1);
	else if(addr < 0xC00) memInitMapperPPUGetPointer(addr, chr1getROM2);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, chr1getROM3);
	else if(addr < 0x1400) memInitMapperPPUGetPointer(addr, chr1getROM4);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, chr1getROM5);
	else if(addr < 0x1C00) memInitMapperPPUGetPointer(addr, chr1getROM6);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, chr1getROM7);
}

void chr1initPPUSet8(uint16_t addr)
{
	if(chr1.chrROM == common_chrRAM) //writable
	{
		if(addr < 0x400) memInitMapperPPUSetPointer(addr, chr1setRAM0);
		else if(addr < 0x800) memInitMapperPPUSetPointer(addr, chr1setRAM1);
		else if(addr < 0xC00) memInitMapperPPUSetPointer(addr, chr1setRAM2);
		else if(addr < 0x1000) memInitMapperPPUSetPointer(addr, chr1setRAM3);
		else if(addr < 0x1400) memInitMapperPPUSetPointer(addr, chr1setRAM4);
		else if(addr < 0x1800) memInitMapperPPUSetPointer(addr, chr1setRAM5);
		else if(addr < 0x1C00) memInitMapperPPUSetPointer(addr, chr1setRAM6);
		else if(addr < 0x2000) memInitMapperPPUSetPointer(addr, chr1setRAM7);
	}
}

void chr1setBank0(uint32_t val) { chr1.chrROMBank0Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank1(uint32_t val) { chr1.chrROMBank1Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank2(uint32_t val) { chr1.chrROMBank2Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank3(uint32_t val) { chr1.chrROMBank3Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank4(uint32_t val) { chr1.chrROMBank4Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank5(uint32_t val) { chr1.chrROMBank5Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank6(uint32_t val) { chr1.chrROMBank6Ptr = chr1.chrROM+(val&chr1.chrROMand); }
void chr1setBank7(uint32_t val) { chr1.chrROMBank7Ptr = chr1.chrROM+(val&chr1.chrROMand); }



static struct {
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t *chrROMBank0Ptr;
	uint8_t *chrROMBank1Ptr;
	uint8_t *chrROMBank2Ptr;
	uint8_t *chrROMBank3Ptr;
} chr2;

void chr2init(uint8_t *chrROM, uint32_t chrROMsize)
{
	if(chrROM == NULL)
	{
		memset(common_chrRAM, 0, 0x2000);
		chr2.chrROM = common_chrRAM;
		chr2.chrROMand = 0x1FFF;
		printf("Using Common CHR RAM (8KB Total) 2KB Banks\n");
	}
	else
	{
		chr2.chrROM = chrROM;
		chr2.chrROMand = mapperGetAndValue(chrROMsize);
		printf("Using Common CHR ROM (%iKB Total) 2KB Banks\n", chrROMsize>>10);
	}
	chr2setBank0(0); chr2setBank1(0);
	chr2setBank2(0); chr2setBank3(0);
}

static uint8_t chr2getROM0(uint16_t addr) { return chr2.chrROMBank0Ptr[addr&0x7FF]; }
static uint8_t chr2getROM1(uint16_t addr) { return chr2.chrROMBank1Ptr[addr&0x7FF]; }
static uint8_t chr2getROM2(uint16_t addr) { return chr2.chrROMBank2Ptr[addr&0x7FF]; }
static uint8_t chr2getROM3(uint16_t addr) { return chr2.chrROMBank3Ptr[addr&0x7FF]; }

void chr2initPPUGet8(uint16_t addr)
{
	if(addr < 0x800) memInitMapperPPUGetPointer(addr, chr2getROM0);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, chr2getROM1);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, chr2getROM2);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, chr2getROM3);
}

static void chr2setRAM0(uint16_t addr, uint8_t val) { chr2.chrROMBank0Ptr[addr&0x7FF] = val; }
static void chr2setRAM1(uint16_t addr, uint8_t val) { chr2.chrROMBank1Ptr[addr&0x7FF] = val; }
static void chr2setRAM2(uint16_t addr, uint8_t val) { chr2.chrROMBank2Ptr[addr&0x7FF] = val; }
static void chr2setRAM3(uint16_t addr, uint8_t val) { chr2.chrROMBank3Ptr[addr&0x7FF] = val; }

void chr2initPPUSet8(uint16_t addr)
{
	if(chr2.chrROM == common_chrRAM) //writable
	{
		if(addr < 0x800) memInitMapperPPUSetPointer(addr, chr2setRAM0);
		else if(addr < 0x1000) memInitMapperPPUSetPointer(addr, chr2setRAM1);
		else if(addr < 0x1800) memInitMapperPPUSetPointer(addr, chr2setRAM2);
		else if(addr < 0x2000) memInitMapperPPUSetPointer(addr, chr2setRAM3);
	}
}

void chr2setBank0(uint32_t val) { chr2.chrROMBank0Ptr = chr2.chrROM+(val&chr2.chrROMand); }
void chr2setBank1(uint32_t val) { chr2.chrROMBank1Ptr = chr2.chrROM+(val&chr2.chrROMand); }
void chr2setBank2(uint32_t val) { chr2.chrROMBank2Ptr = chr2.chrROM+(val&chr2.chrROMand); }
void chr2setBank3(uint32_t val) { chr2.chrROMBank3Ptr = chr2.chrROM+(val&chr2.chrROMand); }



static struct {
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t *chrROMBank0Ptr;
	uint8_t *chrROMBank1Ptr;
} chr4;

void chr4init(uint8_t *chrROM, uint32_t chrROMsize)
{
	if(chrROM == NULL)
	{
		memset(common_chrRAM, 0, 0x2000);
		chr4.chrROM = common_chrRAM;
		chr4.chrROMand = 0x1FFF;
		printf("Using Common CHR RAM (8KB Total) 4KB Banks\n");
	}
	else
	{
		chr4.chrROM = chrROM;
		chr4.chrROMand = mapperGetAndValue(chrROMsize);
		printf("Using Common CHR ROM (%iKB Total) 4KB Banks\n", chrROMsize>>10);
	}
	chr4setBank0(0);
	chr4setBank1(0);
}

static uint8_t chr4getROM0(uint16_t addr) { return chr4.chrROMBank0Ptr[addr&0xFFF]; }
static uint8_t chr4getROM1(uint16_t addr) { return chr4.chrROMBank1Ptr[addr&0xFFF]; }

void chr4initPPUGet8(uint16_t addr)
{
	if(addr < 0x1000) memInitMapperPPUGetPointer(addr, chr4getROM0);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, chr4getROM1);
}

static void chr4setRAM0(uint16_t addr, uint8_t val) { chr4.chrROMBank0Ptr[addr&0xFFF] = val; }
static void chr4setRAM1(uint16_t addr, uint8_t val) { chr4.chrROMBank1Ptr[addr&0xFFF] = val; }

void chr4initPPUSet8(uint16_t addr)
{
	if(chr4.chrROM == common_chrRAM) //writable
	{
		if(addr < 0x1000) memInitMapperPPUSetPointer(addr, chr4setRAM0);
		else if(addr < 0x2000) memInitMapperPPUSetPointer(addr, chr4setRAM1);
	}
}

void chr4setBank0(uint32_t val) { chr4.chrROMBank0Ptr = chr4.chrROM+(val&chr4.chrROMand); }
void chr4setBank1(uint32_t val) { chr4.chrROMBank1Ptr = chr4.chrROM+(val&chr4.chrROMand); }



static struct {
	uint8_t *chrROM;
	uint32_t chrROMand;
	uint8_t *chrROMBank0Ptr;
} chr8;

void chr8init(uint8_t *chrROM, uint32_t chrROMsize)
{
	if(chrROM == NULL)
	{
		memset(common_chrRAM, 0, 0x2000);
		chr8.chrROM = common_chrRAM;
		chr8.chrROMand = 0x1FFF;
		printf("Using Common CHR RAM Fixed 8KB Bank\n");
	}
	else
	{
		chr8.chrROM = chrROM;
		chr8.chrROMand = mapperGetAndValue(chrROMsize);
		if(chr8.chrROMand == 0x1FFF)
			printf("Using Common CHR ROM Fixed 8KB Bank\n");
		else
			printf("Using Common CHR ROM (%iKB Total) 8KB Bank\n", chrROMsize>>10);
	}
	chr8setBank0(0);
}

static uint8_t chr8getROM0(uint16_t addr) { return chr8.chrROMBank0Ptr[addr]; }

void chr8initPPUGet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, chr8getROM0);
}

static void chr8setRAM0(uint16_t addr, uint8_t val) { chr8.chrROMBank0Ptr[addr] = val; }

void chr8initPPUSet8(uint16_t addr)
{
	if(chr8.chrROM == common_chrRAM) //writable
	{
		if(addr < 0x2000)
			memInitMapperPPUSetPointer(addr, chr8setRAM0);
	}
}

void chr8setBank0(uint32_t val) { chr8.chrROMBank0Ptr = chr8.chrROM+(val&chr8.chrROMand); }
