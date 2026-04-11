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
#include "../vrc_irq.h"
#include "../mapper_h/common.h"

static struct {
	bool usesPrgRAM;
	uint32_t curPRGBank0;
	uint32_t curPRGBank1;
	uint32_t lastM1PRGBank;
	uint32_t lastPRGBank;
	uint32_t CHRBank[8];
	bool prg_bank_flip;
} vrc2_4;

static void vrc2_4_SetPrgROMBank0and2()
{
	if(vrc2_4.prg_bank_flip)
	{
		prg8setBank0(vrc2_4.lastM1PRGBank);
		prg8setBank2(vrc2_4.curPRGBank0);
	}
	else
	{
		prg8setBank0(vrc2_4.curPRGBank0);
		prg8setBank2(vrc2_4.lastM1PRGBank);
	}
}
static void vrc2_4_SetPrgROMBank1() { prg8setBank1(vrc2_4.curPRGBank1); }
static void vrc2_4_SetPrgROMBank3() { prg8setBank3(vrc2_4.lastPRGBank); }

void vrc2_4_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		vrc2_4.usesPrgRAM = true;
	}
	else
		vrc2_4.usesPrgRAM = false;
	chr1init(chrROMin,chrROMsizeIn);
	vrc2_4.curPRGBank0 = 0;
	vrc2_4.curPRGBank1 = 0x2000;
	vrc2_4.lastPRGBank = (prgROMsizeIn - 0x2000);
	vrc2_4.lastM1PRGBank = vrc2_4.lastPRGBank - 0x2000;
	memset(vrc2_4.CHRBank, 0, 8*sizeof(uint32_t));
	vrc2_4.prg_bank_flip = false;
	vrc2_4_SetPrgROMBank0and2();
	vrc2_4_SetPrgROMBank1();
	vrc2_4_SetPrgROMBank3();
	vrc_irq_init();
	printf("VRC2/4 inited\n");
}

void vrc2_4_initGet8(uint16_t addr)
{
	if(vrc2_4.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

static void vrc2_4_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc2_4.curPRGBank0 = (val&0x1F)<<13;
	vrc2_4_SetPrgROMBank0and2();
}

static void vrc2_4_setParams9XX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
		val &= 3;
		switch(val)
		{
			case 0:
				ppuSetNameTblVertical();
				break;
			case 1:
				ppuSetNameTblHorizontal();
				break;
			case 2:
				ppuSetNameTblSingleLower();
				break;
			default: //case 3
				ppuSetNameTblSingleUpper();
				break;
		}
	}
}

static void vrc2_4_setParams9XX2(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc2_4.prg_bank_flip = ((val&2) != 0);
	vrc2_4_SetPrgROMBank0and2();
}

static void vrc2_4_setParamsAXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	vrc2_4.curPRGBank1 = (val&0x1F)<<13;
	vrc2_4_SetPrgROMBank1();
}

static void __setCHRBank0Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[0] = (vrc2_4.CHRBank[0]&~0xF) | (val&0xF); }
static void __setCHRBank1Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[1] = (vrc2_4.CHRBank[1]&~0xF) | (val&0xF); }
static void __setCHRBank2Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[2] = (vrc2_4.CHRBank[2]&~0xF) | (val&0xF); }
static void __setCHRBank3Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[3] = (vrc2_4.CHRBank[3]&~0xF) | (val&0xF); }
static void __setCHRBank4Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[4] = (vrc2_4.CHRBank[4]&~0xF) | (val&0xF); }
static void __setCHRBank5Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[5] = (vrc2_4.CHRBank[5]&~0xF) | (val&0xF); }
static void __setCHRBank6Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[6] = (vrc2_4.CHRBank[6]&~0xF) | (val&0xF); }
static void __setCHRBank7Low(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[7] = (vrc2_4.CHRBank[7]&~0xF) | (val&0xF); }

static void __setCHRBank0High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[0] = (vrc2_4.CHRBank[0]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank1High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[1] = (vrc2_4.CHRBank[1]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank2High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[2] = (vrc2_4.CHRBank[2]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank3High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[3] = (vrc2_4.CHRBank[3]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank4High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[4] = (vrc2_4.CHRBank[4]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank5High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[5] = (vrc2_4.CHRBank[5]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank6High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[6] = (vrc2_4.CHRBank[6]&0xF) | ((val&0x1F)<<4); }
static void __setCHRBank7High(uint16_t addr, uint8_t val) { (void)addr; vrc2_4.CHRBank[7] = (vrc2_4.CHRBank[7]&0xF) | ((val&0x1F)<<4); }

static void vrc2_4_SetChrROMBank0() { chr1setBank0(vrc2_4.CHRBank[0]<<10); }
static void vrc2_4_SetChrROMBank1() { chr1setBank1(vrc2_4.CHRBank[1]<<10); }
static void vrc2_4_SetChrROMBank2() { chr1setBank2(vrc2_4.CHRBank[2]<<10); }
static void vrc2_4_SetChrROMBank3() { chr1setBank3(vrc2_4.CHRBank[3]<<10); }
static void vrc2_4_SetChrROMBank4() { chr1setBank4(vrc2_4.CHRBank[4]<<10); }
static void vrc2_4_SetChrROMBank5() { chr1setBank5(vrc2_4.CHRBank[5]<<10); }
static void vrc2_4_SetChrROMBank6() { chr1setBank6(vrc2_4.CHRBank[6]<<10); }
static void vrc2_4_SetChrROMBank7() { chr1setBank7(vrc2_4.CHRBank[7]<<10); }

static void vrc2_4_setParamsBXX0(uint16_t addr, uint8_t val) { __setCHRBank0Low(addr, val); vrc2_4_SetChrROMBank0(); }
static void vrc2_4_setParamsBXX1(uint16_t addr, uint8_t val) { __setCHRBank0High(addr, val); vrc2_4_SetChrROMBank0(); }
static void vrc2_4_setParamsBXX2(uint16_t addr, uint8_t val) { __setCHRBank1Low(addr, val); vrc2_4_SetChrROMBank1(); }
static void vrc2_4_setParamsBXX3(uint16_t addr, uint8_t val) { __setCHRBank1High(addr, val); vrc2_4_SetChrROMBank1(); }
static void vrc2_4_setParamsCXX0(uint16_t addr, uint8_t val) { __setCHRBank2Low(addr, val); vrc2_4_SetChrROMBank2(); }
static void vrc2_4_setParamsCXX1(uint16_t addr, uint8_t val) { __setCHRBank2High(addr, val); vrc2_4_SetChrROMBank2(); }
static void vrc2_4_setParamsCXX2(uint16_t addr, uint8_t val) { __setCHRBank3Low(addr, val); vrc2_4_SetChrROMBank3(); }
static void vrc2_4_setParamsCXX3(uint16_t addr, uint8_t val) { __setCHRBank3High(addr, val); vrc2_4_SetChrROMBank3(); }
static void vrc2_4_setParamsDXX0(uint16_t addr, uint8_t val) { __setCHRBank4Low(addr, val); vrc2_4_SetChrROMBank4(); }
static void vrc2_4_setParamsDXX1(uint16_t addr, uint8_t val) { __setCHRBank4High(addr, val); vrc2_4_SetChrROMBank4(); }
static void vrc2_4_setParamsDXX2(uint16_t addr, uint8_t val) { __setCHRBank5Low(addr, val); vrc2_4_SetChrROMBank5(); }
static void vrc2_4_setParamsDXX3(uint16_t addr, uint8_t val) { __setCHRBank5High(addr, val); vrc2_4_SetChrROMBank5(); }
static void vrc2_4_setParamsEXX0(uint16_t addr, uint8_t val) { __setCHRBank6Low(addr, val); vrc2_4_SetChrROMBank6(); }
static void vrc2_4_setParamsEXX1(uint16_t addr, uint8_t val) { __setCHRBank6High(addr, val); vrc2_4_SetChrROMBank6(); }
static void vrc2_4_setParamsEXX2(uint16_t addr, uint8_t val) { __setCHRBank7Low(addr, val); vrc2_4_SetChrROMBank7(); }
static void vrc2_4_setParamsEXX3(uint16_t addr, uint8_t val) { __setCHRBank7High(addr, val); vrc2_4_SetChrROMBank7(); }

static void vrc2_4_initSet8(uint16_t proc_addr, uint16_t ori_addr)
{
	if(proc_addr == 0x8000 || proc_addr == 0x8001 || proc_addr == 0x8002 || proc_addr == 0x8003)
		memInitMapperSetPointer(ori_addr, vrc2_4_setParams8XXX);
	else if(proc_addr == 0x9000 || proc_addr == 0x9001)
		memInitMapperSetPointer(ori_addr, vrc2_4_setParams9XX0);
	else if(proc_addr == 0x9002 || proc_addr == 0x9003)
		memInitMapperSetPointer(ori_addr, vrc2_4_setParams9XX2);
	else if(proc_addr == 0xA000 || proc_addr == 0xA001 || proc_addr == 0xA002 || proc_addr == 0xA003)
		memInitMapperSetPointer(ori_addr, vrc2_4_setParamsAXXX);
	//CHR Regs
	else if(proc_addr == 0xB000) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsBXX0);
	else if(proc_addr == 0xB001) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsBXX1);
	else if(proc_addr == 0xB002) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsBXX2);
	else if(proc_addr == 0xB003) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsBXX3);
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsCXX0);
	else if(proc_addr == 0xC001) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsCXX1);
	else if(proc_addr == 0xC002) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsCXX2);
	else if(proc_addr == 0xC003) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsCXX3);
	else if(proc_addr == 0xD000) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsDXX0);
	else if(proc_addr == 0xD001) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsDXX1);
	else if(proc_addr == 0xD002) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsDXX2);
	else if(proc_addr == 0xD003) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsDXX3);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsEXX0);
	else if(proc_addr == 0xE001) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsEXX1);
	else if(proc_addr == 0xE002) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsEXX2);
	else if(proc_addr == 0xE003) memInitMapperSetPointer(ori_addr, vrc2_4_setParamsEXX3);
	//VRC IRQ Regs
	else if(proc_addr == 0xF000) memInitMapperSetPointer(ori_addr, vrc_irq_setlatchLo);
	else if(proc_addr == 0xF001) memInitMapperSetPointer(ori_addr, vrc_irq_setlatchHi);
	else if(proc_addr == 0xF002) memInitMapperSetPointer(ori_addr, vrc_irq_control);
	else if(proc_addr == 0xF003) memInitMapperSetPointer(ori_addr, vrc_irq_ack);
}

void m21_initSet8(uint16_t ori_addr)
{
	if(vrc2_4.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		uint8_t tmp1 = (ori_addr>>1)&3;
		uint8_t tmp2 = (ori_addr>>6)&3;
		uint16_t proc_addr = (ori_addr & 0xF000) | tmp1 | tmp2;
		vrc2_4_initSet8(proc_addr, ori_addr);
	}
}

static void m22_setParams9XX0(uint16_t addr, uint8_t val)
{
	//always vrc2, does only vertical/horizontal
	val &= 1;
	vrc2_4_setParams9XX0(addr, val);
}
static void m22_SetChrROMBank0() { chr1setBank0((vrc2_4.CHRBank[0]>>1)<<10); }
static void m22_SetChrROMBank1() { chr1setBank1((vrc2_4.CHRBank[1]>>1)<<10); }
static void m22_SetChrROMBank2() { chr1setBank2((vrc2_4.CHRBank[2]>>1)<<10); }
static void m22_SetChrROMBank3() { chr1setBank3((vrc2_4.CHRBank[3]>>1)<<10); }
static void m22_SetChrROMBank4() { chr1setBank4((vrc2_4.CHRBank[4]>>1)<<10); }
static void m22_SetChrROMBank5() { chr1setBank5((vrc2_4.CHRBank[5]>>1)<<10); }
static void m22_SetChrROMBank6() { chr1setBank6((vrc2_4.CHRBank[6]>>1)<<10); }
static void m22_SetChrROMBank7() { chr1setBank7((vrc2_4.CHRBank[7]>>1)<<10); }

static void m22_setParamsBXX0(uint16_t addr, uint8_t val) { __setCHRBank0Low(addr, val); m22_SetChrROMBank0(); }
static void m22_setParamsBXX1(uint16_t addr, uint8_t val) { __setCHRBank0High(addr, val); m22_SetChrROMBank0(); }
static void m22_setParamsBXX2(uint16_t addr, uint8_t val) { __setCHRBank1Low(addr, val); m22_SetChrROMBank1(); }
static void m22_setParamsBXX3(uint16_t addr, uint8_t val) { __setCHRBank1High(addr, val); m22_SetChrROMBank1(); }
static void m22_setParamsCXX0(uint16_t addr, uint8_t val) { __setCHRBank2Low(addr, val); m22_SetChrROMBank2(); }
static void m22_setParamsCXX1(uint16_t addr, uint8_t val) { __setCHRBank2High(addr, val); m22_SetChrROMBank2(); }
static void m22_setParamsCXX2(uint16_t addr, uint8_t val) { __setCHRBank3Low(addr, val); m22_SetChrROMBank3(); }
static void m22_setParamsCXX3(uint16_t addr, uint8_t val) { __setCHRBank3High(addr, val); m22_SetChrROMBank3(); }
static void m22_setParamsDXX0(uint16_t addr, uint8_t val) { __setCHRBank4Low(addr, val); m22_SetChrROMBank4(); }
static void m22_setParamsDXX1(uint16_t addr, uint8_t val) { __setCHRBank4High(addr, val); m22_SetChrROMBank4(); }
static void m22_setParamsDXX2(uint16_t addr, uint8_t val) { __setCHRBank5Low(addr, val); m22_SetChrROMBank5(); }
static void m22_setParamsDXX3(uint16_t addr, uint8_t val) { __setCHRBank5High(addr, val); m22_SetChrROMBank5(); }
static void m22_setParamsEXX0(uint16_t addr, uint8_t val) { __setCHRBank6Low(addr, val); m22_SetChrROMBank6(); }
static void m22_setParamsEXX1(uint16_t addr, uint8_t val) { __setCHRBank6High(addr, val); m22_SetChrROMBank6(); }
static void m22_setParamsEXX2(uint16_t addr, uint8_t val) { __setCHRBank7Low(addr, val); m22_SetChrROMBank7(); }
static void m22_setParamsEXX3(uint16_t addr, uint8_t val) { __setCHRBank7High(addr, val); m22_SetChrROMBank7(); }

void m22_initSet8(uint16_t ori_addr)
{
	if(vrc2_4.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		//printf("m22_set8 %04x %02x\n", addr, val);
		//vrc2_4_2 M22 Address Setup
		uint8_t tmp = ori_addr&3;
		uint16_t proc_addr = (ori_addr & 0xF000) | ((tmp&1)<<1) | ((tmp&2)>>1);
		//vrc2_4_2 only supports vertical/horizonal and has special chr bank sets
		if(proc_addr == 0x9000 || proc_addr == 0x9001)
			memInitMapperSetPointer(ori_addr, m22_setParams9XX0);
		//CHR Regs
		else if(proc_addr == 0xB000) memInitMapperSetPointer(ori_addr, m22_setParamsBXX0);
		else if(proc_addr == 0xB001) memInitMapperSetPointer(ori_addr, m22_setParamsBXX1);
		else if(proc_addr == 0xB002) memInitMapperSetPointer(ori_addr, m22_setParamsBXX2);
		else if(proc_addr == 0xB003) memInitMapperSetPointer(ori_addr, m22_setParamsBXX3);
		else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, m22_setParamsCXX0);
		else if(proc_addr == 0xC001) memInitMapperSetPointer(ori_addr, m22_setParamsCXX1);
		else if(proc_addr == 0xC002) memInitMapperSetPointer(ori_addr, m22_setParamsCXX2);
		else if(proc_addr == 0xC003) memInitMapperSetPointer(ori_addr, m22_setParamsCXX3);
		else if(proc_addr == 0xD000) memInitMapperSetPointer(ori_addr, m22_setParamsDXX0);
		else if(proc_addr == 0xD001) memInitMapperSetPointer(ori_addr, m22_setParamsDXX1);
		else if(proc_addr == 0xD002) memInitMapperSetPointer(ori_addr, m22_setParamsDXX2);
		else if(proc_addr == 0xD003) memInitMapperSetPointer(ori_addr, m22_setParamsDXX3);
		else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, m22_setParamsEXX0);
		else if(proc_addr == 0xE001) memInitMapperSetPointer(ori_addr, m22_setParamsEXX1);
		else if(proc_addr == 0xE002) memInitMapperSetPointer(ori_addr, m22_setParamsEXX2);
		else if(proc_addr == 0xE003) memInitMapperSetPointer(ori_addr, m22_setParamsEXX3);
		else //the rest is used normally
			vrc2_4_initSet8(proc_addr, ori_addr);
	}
}

static void m23_setParams9XX0(uint16_t addr, uint8_t val)
{
	//can be vrc2 or vrc4, do vertical/horizontal when value == 0xFF
	//this is required for wai wai world to display correctly
	if(val == 0xFF)
		val &= 1;
	vrc2_4_setParams9XX0(addr, val);
}

void m23_initSet8(uint16_t ori_addr)
{
	if(vrc2_4.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		//printf("m23_set8 %04x %02x\n", addr, val);
		//vrc2_4_4 M23 Address Setup
		uint8_t tmp = (ori_addr>>2)&3;
		uint16_t proc_addr = (ori_addr & 0xF003) | tmp;
		//vrc2_4_2 Wai Wai World, avoid wrong mirroring
		if(proc_addr == 0x9000 || proc_addr == 0x9001) //checks if val == 0xFF
			memInitMapperSetPointer(ori_addr, m23_setParams9XX0);
		else
			vrc2_4_initSet8(proc_addr, ori_addr);
	}
}

void m25_initSet8(uint16_t ori_addr)
{
	if(vrc2_4.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	if(ori_addr >= 0x8000)
	{
		//printf("m25_set8 %04x %02x\n", addr, val);
		//vrc2_4_4 M25 Address Setup
		uint8_t tmp1 = (((ori_addr&1)<<1) | ((ori_addr&2)>>1));
		uint8_t tmp2 = ((((ori_addr>>2)&1)<<1) | (((ori_addr>>2)&2)>>1));
		uint16_t proc_addr = (ori_addr & 0xF000) | tmp1 | tmp2;
		vrc2_4_initSet8(proc_addr, ori_addr);
	}
}
