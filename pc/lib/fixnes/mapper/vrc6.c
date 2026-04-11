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
#include "../audio_vrc6.h"
#include "../vrc_irq.h"
#include "../mapper_h/common.h"

static struct {
	uint8_t *prgROM;
	uint32_t prgROMsize;
	uint32_t prgROMand;
	bool usesPrgRAM;
	uint8_t *prgROMBank0Ptr, *prgROMBank1Ptr, *prgROMBank2Ptr;
	uint32_t curPRGBank0, curPRGBank1, lastPRGBank;
	uint32_t CHRBank[8];
	uint8_t CHRMode;
} vrc6;

static void vrc6SetPrgROMBankPtr0() { vrc6.prgROMBank0Ptr = vrc6.prgROM+vrc6.curPRGBank0; }
static void vrc6SetPrgROMBankPtr1() { vrc6.prgROMBank1Ptr = vrc6.prgROM+vrc6.curPRGBank1; }
static void vrc6SetPrgROMBankPtr2() { vrc6.prgROMBank2Ptr = vrc6.prgROM+vrc6.lastPRGBank; }

static void vrc6SetChrROMBankPtr()
{
	if(vrc6.CHRMode == 0)
	{
		chr1setBank0(vrc6.CHRBank[0]<<10); chr1setBank1(vrc6.CHRBank[1]<<10);
		chr1setBank2(vrc6.CHRBank[2]<<10); chr1setBank3(vrc6.CHRBank[3]<<10);
		chr1setBank4(vrc6.CHRBank[4]<<10); chr1setBank5(vrc6.CHRBank[5]<<10);
		chr1setBank6(vrc6.CHRBank[6]<<10); chr1setBank7(vrc6.CHRBank[7]<<10);
	}
	else if(vrc6.CHRMode == 1)
	{
		chr1setBank0((vrc6.CHRBank[0]<<11)|0x000); chr1setBank1((vrc6.CHRBank[0]<<11)|0x400);
		chr1setBank2((vrc6.CHRBank[1]<<11)|0x000); chr1setBank3((vrc6.CHRBank[1]<<11)|0x400);
		chr1setBank4((vrc6.CHRBank[2]<<11)|0x000); chr1setBank5((vrc6.CHRBank[2]<<11)|0x400);
		chr1setBank6((vrc6.CHRBank[3]<<11)|0x000); chr1setBank7((vrc6.CHRBank[3]<<11)|0x400);
	}
	else
	{
		chr1setBank0(vrc6.CHRBank[0]<<10); chr1setBank1(vrc6.CHRBank[1]<<10);
		chr1setBank2(vrc6.CHRBank[2]<<10); chr1setBank3(vrc6.CHRBank[3]<<10);
		chr1setBank4((vrc6.CHRBank[4]<<11)|0x000); chr1setBank5((vrc6.CHRBank[4]<<11)|0x400);
		chr1setBank6((vrc6.CHRBank[5]<<11)|0x000); chr1setBank7((vrc6.CHRBank[5]<<11)|0x400);
	}
}

void vrc6init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	vrc6.prgROM = prgROMin;
	vrc6.prgROMsize = prgROMsizeIn;
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		vrc6.usesPrgRAM = true;
	}
	else
		vrc6.usesPrgRAM = false;
	vrc6.curPRGBank0 = 0;
	vrc6SetPrgROMBankPtr0();
	vrc6.curPRGBank1 = 0x4000;
	vrc6SetPrgROMBankPtr1();
	vrc6.lastPRGBank = (prgROMsizeIn - 0x2000);
	vrc6SetPrgROMBankPtr2();
	vrc6.prgROMand = mapperGetAndValue(prgROMsizeIn);
	memset(vrc6.CHRBank, 0, 8*sizeof(uint32_t));
	vrc6.CHRMode = 0;
	chr1init(chrROMin,chrROMsizeIn);
	vrc_irq_init();
	vrc6AudioInit();
	printf("VRC6 inited\n");
}

static uint8_t vrc6getROM0(uint16_t addr) { return vrc6.prgROMBank0Ptr[addr&0x3FFF]; }
static uint8_t vrc6getROM1(uint16_t addr) { return vrc6.prgROMBank1Ptr[addr&0x1FFF]; }
static uint8_t vrc6getROM2(uint16_t addr) { return vrc6.prgROMBank2Ptr[addr&0x1FFF]; }

void vrc6initGet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		prgRAM8initGet8(addr);
	else if(addr >= 0x8000)
	{
		if(addr < 0xC000) memInitMapperGetPointer(addr, vrc6getROM0);
		else if(addr < 0xE000) memInitMapperGetPointer(addr, vrc6getROM1);
		else memInitMapperGetPointer(addr, vrc6getROM2);
	}
}

static void vrc6setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6.curPRGBank0 = ((val&0xF)<<14)&vrc6.prgROMand;
	vrc6SetPrgROMBankPtr0();
}

static void vrc6setParamsBXX3(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((val & 0x3) == 0)
		vrc6.CHRMode = 0;
	else if((val & 0x3) == 1)
		vrc6.CHRMode = 1;
	else
		vrc6.CHRMode = 2;
	vrc6SetChrROMBankPtr();
	if(!ppu4Screen)
	{
		if((val & 0xF) == 0 || (val & 0xF) == 7)
			ppuSetNameTblVertical();
		else if((val & 0xF) == 4 || (val & 0xF) == 3)
			ppuSetNameTblHorizontal();
		if((val & 0xF) == 8 || (val & 0xF) == 0xF)
			ppuSetNameTblSingleLower();
		if((val & 0xF) == 0xC || (val & 0xF) == 0xB)
			ppuSetNameTblSingleUpper();
	}
}

static void vrc6setParamsCXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc6.curPRGBank1 = ((val&0x1F)<<13)&vrc6.prgROMand;
	vrc6SetPrgROMBankPtr1();
}

//CHR Regs
static void vrc6setParamsDXX0(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[0] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsDXX1(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[1] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsDXX2(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[2] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsDXX3(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[3] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsEXX0(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[4] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsEXX1(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[5] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsEXX2(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[6] = val; vrc6SetChrROMBankPtr(); }
static void vrc6setParamsEXX3(uint16_t addr, uint8_t val) { (void)addr; vrc6.CHRBank[7] = val; vrc6SetChrROMBankPtr(); }

static void vrc6initSet8(uint16_t proc_addr, uint16_t ori_addr)
{
	//PRG Bank 0
	if(proc_addr == 0x8000 || proc_addr == 0x8001 || proc_addr == 0x8002 || proc_addr == 0x8003)
		memInitMapperSetPointer(ori_addr, vrc6setParams8XXX);
	//Audio Regs
	else if(proc_addr == 0x9000) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_9XX0);
	else if(proc_addr == 0x9001) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_9XX1);
	else if(proc_addr == 0x9002) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_9XX2);
	else if(proc_addr == 0x9003) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_9XX3);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_AXX0);
	else if(proc_addr == 0xA001) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_AXX1);
	else if(proc_addr == 0xA002) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_AXX2);
	else if(proc_addr == 0xB000) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_BXX0);
	else if(proc_addr == 0xB001) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_BXX1);
	else if(proc_addr == 0xB002) memInitMapperSetPointer(ori_addr, vrc6AudioSet8_BXX2);
	//Various Params
	else if(proc_addr == 0xB003) memInitMapperSetPointer(ori_addr, vrc6setParamsBXX3);
	//PRG Bank 1
	else if(proc_addr == 0xC000 || proc_addr == 0xC001 || proc_addr == 0xC002 || proc_addr == 0xC003)
		memInitMapperSetPointer(ori_addr, vrc6setParamsCXXX);
	//CHR Regs
	else if(proc_addr == 0xD000) memInitMapperSetPointer(ori_addr, vrc6setParamsDXX0);
	else if(proc_addr == 0xD001) memInitMapperSetPointer(ori_addr, vrc6setParamsDXX1);
	else if(proc_addr == 0xD002) memInitMapperSetPointer(ori_addr, vrc6setParamsDXX2);
	else if(proc_addr == 0xD003) memInitMapperSetPointer(ori_addr, vrc6setParamsDXX3);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, vrc6setParamsEXX0);
	else if(proc_addr == 0xE001) memInitMapperSetPointer(ori_addr, vrc6setParamsEXX1);
	else if(proc_addr == 0xE002) memInitMapperSetPointer(ori_addr, vrc6setParamsEXX2);
	else if(proc_addr == 0xE003) memInitMapperSetPointer(ori_addr, vrc6setParamsEXX3);
	//VRC IRQ Regs
	else if(proc_addr == 0xF000) memInitMapperSetPointer(ori_addr, vrc_irq_setlatch);
	else if(proc_addr == 0xF001) memInitMapperSetPointer(ori_addr, vrc_irq_control);
	else if(proc_addr == 0xF002) memInitMapperSetPointer(ori_addr, vrc_irq_ack);
}

void m24_initSet8(uint16_t ori_addr)
{
	if(vrc6.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		uint16_t proc_addr = ori_addr & 0xF003;
		vrc6initSet8(proc_addr, ori_addr);
	}
}

void m26_initSet8(uint16_t ori_addr)
{
	if(vrc6.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		uint8_t tmp = ori_addr&3;
		uint16_t proc_addr = (ori_addr & 0xF000) | ((tmp&1)<<1) | ((tmp&2)>>1);
		vrc6initSet8(proc_addr, ori_addr);
	}
}

void vrc6cycle()
{
	vrc6AudioClockTimers();
	vrc_irq_cycle();
}
