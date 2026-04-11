/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	uint8_t *prgROM;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr,
			*prgROMBank2Ptr, *prgROMBank3Ptr;
	bool usesPrgRAM;
	uint8_t *chrROM;
	uint8_t *chrROMBank0Ptr;
	uint8_t *chrROMBank1Ptr;
	uint32_t prgROMsize;
	uint32_t prgROMand;
	uint32_t prgRAMsize;
	uint32_t chrROMsize;
	uint32_t chrROMand;
	uint32_t curPRGBank;
	uint32_t curCHRBank00;
	uint32_t curCHRBank01;
	uint32_t curCHRBank10;
	uint32_t curCHRBank11;
	bool CHRSelect0;
	bool CHRSelect1;
} mmc2_4;

static void mmc2_4SetPrgROMBankPtr()
{
	mmc2_4.prgROMBank0Ptr = mmc2_4.prgROM+mmc2_4.curPRGBank;
}

static void mmc2_4SetChrROMBankPtr()
{
	//addr < 0x1000
	if(mmc2_4.CHRSelect0 == false)
		mmc2_4.chrROMBank0Ptr = mmc2_4.chrROM+mmc2_4.curCHRBank00;
	else
		mmc2_4.chrROMBank0Ptr = mmc2_4.chrROM+mmc2_4.curCHRBank01;
	//addr >= 0x1000
	if(mmc2_4.CHRSelect1 == false)
		mmc2_4.chrROMBank1Ptr = mmc2_4.chrROM+mmc2_4.curCHRBank10;
	else
		mmc2_4.chrROMBank1Ptr = mmc2_4.chrROM+mmc2_4.curCHRBank11;
}

void mmc2_4init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc2_4.prgROM = prgROMin;
	mmc2_4.prgROMsize = prgROMsizeIn;
	mmc2_4.prgROMand = mapperGetAndValue(mmc2_4.prgROMsize);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		mmc2_4.usesPrgRAM = true;
	}
	else
		mmc2_4.usesPrgRAM = false;
	mmc2_4.curPRGBank = 0;
	mmc2_4SetPrgROMBankPtr(); //sets mmc2_4.prgROMBank0Ptr
	mmc2_4.prgROMBank1Ptr = mmc2_4.prgROM+((mmc2_4.prgROMsize-0x6000)&0x3E000);
	mmc2_4.prgROMBank2Ptr = mmc2_4.prgROM+((mmc2_4.prgROMsize-0x4000)&0x3E000);
	mmc2_4.prgROMBank3Ptr = mmc2_4.prgROM+((mmc2_4.prgROMsize-0x2000)&0x3E000);
	mmc2_4.chrROM = chrROMin;
	mmc2_4.chrROMsize = chrROMsizeIn;
	mmc2_4.chrROMand = mapperGetAndValue(mmc2_4.chrROMsize);
	mmc2_4.curCHRBank00 = 0;
	mmc2_4.curCHRBank01 = 0;
	mmc2_4.curCHRBank10 = 0;
	mmc2_4.curCHRBank11 = 0;
	mmc2_4.CHRSelect0 = false;
	mmc2_4.CHRSelect1 = false;
	mmc2_4SetChrROMBankPtr();
	printf("MMC2/4 inited\n");
}

static uint8_t mmc2getROM0(uint16_t addr)
{
	return mmc2_4.prgROMBank0Ptr[addr&0x1FFF];
}
static uint8_t mmc4getROM0(uint16_t addr)
{
	return mmc2_4.prgROMBank0Ptr[addr&0x3FFF];
}

static uint8_t mmc2_4getROMLastM2(uint16_t addr)
{
	return mmc2_4.prgROMBank1Ptr[addr&0x1FFF];
}
static uint8_t mmc2_4getROMLastM1(uint16_t addr)
{
	return mmc2_4.prgROMBank2Ptr[addr&0x1FFF];
}
static uint8_t mmc2_4getROMLastM0(uint16_t addr)
{
	return mmc2_4.prgROMBank3Ptr[addr&0x1FFF];
}

static void mmc2_4initGet8(uint16_t addr)
{
	if(mmc2_4.usesPrgRAM)
		prgRAM8initGet8(addr);
	if(addr >= 0xA000)
	{
		if(addr < 0xC000)
			memInitMapperGetPointer(addr, mmc2_4getROMLastM2);
		else if(addr < 0xE000)
			memInitMapperGetPointer(addr, mmc2_4getROMLastM1);
		else //addr >= 0xE000
			memInitMapperGetPointer(addr, mmc2_4getROMLastM0);
	}
}

void mmc2initGet8(uint16_t addr)
{
	if(addr >= 0x8000 && addr < 0xA000)
		memInitMapperGetPointer(addr, mmc2getROM0);
	else //shared between MMC2 and MMC4
		mmc2_4initGet8(addr);
}

void mmc4initGet8(uint16_t addr)
{
	if(addr >= 0x8000 && addr < 0xC000)
		memInitMapperGetPointer(addr, mmc4getROM0);
	else //shared between MMC2 and MMC4
		mmc2_4initGet8(addr);
}

static void mmc2setParamsAXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curPRGBank = ((val&0xF)<<13)&mmc2_4.prgROMand;
	mmc2_4SetPrgROMBankPtr();
}
static void mmc4setParamsAXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curPRGBank = ((val&0xF)<<14)&mmc2_4.prgROMand;
	mmc2_4SetPrgROMBankPtr();
}

static void mmc2_4setParamsBXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curCHRBank00 = ((val&0x1F)<<12)&mmc2_4.chrROMand;
	mmc2_4SetChrROMBankPtr();
}
static void mmc2_4setParamsCXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curCHRBank01 = ((val&0x1F)<<12)&mmc2_4.chrROMand;
	mmc2_4SetChrROMBankPtr();
}
static void mmc2_4setParamsDXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curCHRBank10 = ((val&0x1F)<<12)&mmc2_4.chrROMand;
	mmc2_4SetChrROMBankPtr();
}
static void mmc2_4setParamsEXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc2_4.curCHRBank11 = ((val&0x1F)<<12)&mmc2_4.chrROMand;
	mmc2_4SetChrROMBankPtr();
}
static void mmc2_4setParamsFXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((val&1) == 0)
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

static void mmc2_4initSet8(uint16_t addr)
{
	if(mmc2_4.usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr >= 0xB000)
	{
		if(addr < 0xC000)
			memInitMapperSetPointer(addr, mmc2_4setParamsBXXX);
		else if(addr < 0xD000)
			memInitMapperSetPointer(addr, mmc2_4setParamsCXXX);
		else if(addr < 0xE000)
			memInitMapperSetPointer(addr, mmc2_4setParamsDXXX);
		else if(addr < 0xF000)
			memInitMapperSetPointer(addr, mmc2_4setParamsEXXX);
		else
			memInitMapperSetPointer(addr, mmc2_4setParamsFXXX);
	}
}

void mmc2initSet8(uint16_t addr)
{
	if(addr >= 0xA000 && addr < 0xB000)
		memInitMapperSetPointer(addr, mmc2setParamsAXXX);
	else //shared between MMC2 and MMC4
		mmc2_4initSet8(addr);
}

void mmc4initSet8(uint16_t addr)
{
	if(addr >= 0xA000 && addr < 0xB000)
		memInitMapperSetPointer(addr, mmc4setParamsAXXX);
	else //shared between MMC2 and MMC4
		mmc2_4initSet8(addr);
}

static uint8_t mmc2_4chrGetROM0(uint16_t addr)
{
	return mmc2_4.chrROMBank0Ptr[addr&0xFFF];
}
static uint8_t mmc2_4chrGetROM0SelFalse(uint16_t addr)
{
	uint8_t ret = mmc2_4.chrROMBank0Ptr[addr&0xFFF];
	mmc2_4.CHRSelect0 = false;
	mmc2_4SetChrROMBankPtr();
	return ret;
}
static uint8_t mmc2_4chrGetROM0SelTrue(uint16_t addr)
{
	uint8_t ret = mmc2_4.chrROMBank0Ptr[addr&0xFFF];
	mmc2_4.CHRSelect0 = true;
	mmc2_4SetChrROMBankPtr();
	return ret;
}

static uint8_t mmc2_4chrGetROM1(uint16_t addr)
{
	return mmc2_4.chrROMBank1Ptr[addr&0xFFF];
}
static uint8_t mmc2_4chrGetROM1SelFalse(uint16_t addr)
{
	uint8_t ret = mmc2_4.chrROMBank1Ptr[addr&0xFFF];
	mmc2_4.CHRSelect1 = false;
	mmc2_4SetChrROMBankPtr();
	return ret;
}
static uint8_t mmc2_4chrGetROM1SelTrue(uint16_t addr)
{
	uint8_t ret = mmc2_4.chrROMBank1Ptr[addr&0xFFF];
	mmc2_4.CHRSelect1 = true;
	mmc2_4SetChrROMBankPtr();
	return ret;
}

static void mmc2_4initPPUGet8(uint16_t addr)
{
	if(addr < 0x1000) //ROM0SelFalse/ROM0SelTrue already set up below
		memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM0);
	else
	{
		if(addr >= 0x1FD8 && addr <= 0x1FDF)
			memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM1SelFalse);
		else if(addr >= 0x1FE8 && addr <= 0x1FEF)
			memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM1SelTrue);
		else if(addr < 0x2000)
			memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM1);
	}
}

void mmc2initPPUGet8(uint16_t addr)
{
	if(addr == 0xFD8)
		memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM0SelFalse);
	else if(addr == 0xFE8)
		memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM0SelTrue);
	else //shared between MMC2 and MMC4
		mmc2_4initPPUGet8(addr);
}

void mmc4initPPUGet8(uint16_t addr)
{
	if(addr >= 0xFD8 && addr <= 0xFDF)
		memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM0SelFalse);
	else if(addr >= 0xFE8 && addr <= 0xFEF)
		memInitMapperPPUGetPointer(addr, mmc2_4chrGetROM0SelTrue);
	else //shared between MMC2 and MMC4
		mmc2_4initPPUGet8(addr);
}

void mmc2_4initPPUSet8(uint16_t addr)
{
	(void)addr;
}
