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
#include "../mapper_h/common.h"
#include "../mapper_h/p16c8.h"

void p16c8init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr8init(chrROMin,chrROMsizeIn);
	printf("16k PRG 8k CHR Mapper inited\n");
}

static bool p1632_p16;
static uint32_t p1632_curPRGBank;
static void p1632c8SetPrgROMBank()
{
	if(p1632_p16)
	{
		prg16setBank0(p1632_curPRGBank);
		prg16setBank1(p1632_curPRGBank);
	}
	else
	{
		prg16setBank0((p1632_curPRGBank&~0x7FFF)+0x0000);
		prg16setBank1((p1632_curPRGBank&~0x7FFF)+0x4000);
	}
}

static uint8_t m57_regA, m57_regB;
void m57_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//init extra regs used by mapper 57
	m57_regA = 0, m57_regB = 0;
	//sets special prg bank layout
	p1632_p16 = true;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
}

void m58_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//sets special prg bank layout
	m58_reset();
}

static uint8_t m60_state;
void m60_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//init extra regs used by mapper 60
	m60_state = 0;
	//sets special prg bank layout
	m60_reset();
}

void m62_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//sets special prg bank layout
	m62_reset();
}

void p1632c8init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	p1632_p16 = false;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
}

void m97_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//reversed prg bank layout
	prg16setBank0(prgROMsizeIn - 0x4000);
	prg16setBank1(0);
}

void m174_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//reversed compared to other mappers using this...
	p1632_p16 = true;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
}

void m180_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	prg16setBank0(0); //fixed first bank
	prg16setBank1(0); //swappable bank
}

static void m200SetPrgROMBank(uint32_t bank)
{
	prg16setBank0(bank); prg16setBank1(bank);
}

void m200_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//both the same swappable bank
	m200SetPrgROMBank(0);
}

static uint8_t m221_prgmode;
static uint32_t m221_curPRGBank,m221_outerPRGBank;
static void m221SetPrgROMBank()
{
	if(m221_prgmode&1)
	{
		if(m221_prgmode&2)
		{
			prg16setBank0((m221_curPRGBank)|m221_outerPRGBank);
			prg16setBank1((((m221_curPRGBank)&~0x1FFFF)|0x1C000)|m221_outerPRGBank);
		}
		else
		{
			prg16setBank0((m221_curPRGBank&~0x7FFF)|m221_outerPRGBank);
			prg16setBank1((m221_curPRGBank|0x4000)|m221_outerPRGBank);
		}
	}
	else
	{
		prg16setBank0(m221_curPRGBank|m221_outerPRGBank);
		prg16setBank1(m221_curPRGBank|m221_outerPRGBank);
	}
}

void m221_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//sets special prg bank layout
	m221_reset();
}

void m226_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//sets special prg bank layout
	m226_reset();
}

static void m231SetPrgROMBank(uint32_t bank)
{
	prg16setBank0(bank&~0x7FFF); prg16setBank1(bank);
}

void m231_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//special prg bank layout
	m231SetPrgROMBank(0);
}

static uint8_t m230_mode;
void m230_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//special prg bank layout
	m230_mode = 0;
	m230_reset();
}

static uint32_t m232_curPRGBank;
static void m232SetPrgROMBank()
{
	prg16setBank0(m232_curPRGBank);
	prg16setBank1((m232_curPRGBank&~0xFFFF)|0xC000);
}

void m232_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//special prg bank layout
	m232_curPRGBank = 0;
	m232SetPrgROMBank();
}

static uint8_t m235_bankshift;
void m235_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p16c8init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//seemingly select from either 512kb or 1mb rom banks depending on input size
	m235_bankshift = (prgROMsizeIn <= 0x200000) ? 19 : 20;
	//special prg bank layout
	m235_reset();
}


extern uint8_t memLastVal;
static uint8_t m212_getParams(uint16_t addr) { (void)addr; return 0x80|memLastVal; }
void m212_initGet8(uint16_t addr)
{
	if((addr&0xE010) == 0x6000) //required for some to not lock up
		memInitMapperGetPointer(addr, m212_getParams);
	else //normal rom init
		prg16initGet8(addr);
}

static void m2_setParams(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0((val & 0xF)<<14); }
void m2_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m2_setParams);
}

static void m57_setParams80XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m57_regA = (val&7)|((val>>3)&8);
	chr8setBank0((m57_regA|m57_regB)<<13);
}
static void m57_setParams88XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	p1632_p16 = ((val&0x10) == 0);
	p1632_curPRGBank = ((val>>5)&7)<<14;
	p1632c8SetPrgROMBank();
	m57_regB = val&7;
	chr8setBank0((m57_regA|m57_regB)<<13);
	if((val&8) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m57_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0x8800;
	if(proc_addr == 0x8000)
		memInitMapperSetPointer(ori_addr, m57_setParams80XX);
	else if(proc_addr == 0x8800)
		memInitMapperSetPointer(ori_addr, m57_setParams88XX);
}

static void m58_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&0x40) != 0);
	p1632_curPRGBank = (addr&7)<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0(((addr>>3)&7)<<13);
	if((addr&0x80) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m58_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m58_setParams);
}

void m60_initSet8(uint16_t addr)
{
	(void)addr;
}

static void m61_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&0x10) != 0);
	p1632_curPRGBank = (((addr & 0xF)<<1)|((addr&0x20)>>5))<<14;
	p1632c8SetPrgROMBank();
	if((addr&0x80) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m61_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m61_setParams);
}

static void m62_setParams(uint16_t addr, uint8_t val)
{
	p1632_p16 = ((addr&0x20) != 0);
	p1632_curPRGBank = ((addr&0x40)|((addr>>8)&0x3F))<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0((((addr&0x1F)<<2)|(val&3))<<13);
	if((addr&0x80) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m62_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m62_setParams);
}

static void m70_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val >> 4)<<14);
	chr8setBank0((val & 0xF)<<13);
}
void m70_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m70_setParams);
}

static void m71_setParams9000(uint16_t addr, uint8_t val)
{
	(void)addr;
	//For Fire Hawk
	if((val&0x10) != 0)
		ppuSetNameTblSingleLower();
	else if(val == 0)
		ppuSetNameTblSingleUpper();
}
static void m71_setParamsCXXX(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0((val & 0xF)<<14); }
void m71_initSet8(uint16_t addr)
{
	if(addr == 0x9000) memInitMapperSetPointer(addr, m71_setParams9000);
	else if(addr >= 0xC000) memInitMapperSetPointer(addr, m71_setParamsCXXX);
}

static void m78a_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val & 7)<<14);
	chr8setBank0(((val>>4) & 0xF)<<13);
	if((val&0x8) == 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
static void m78b_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val & 7)<<14);
	chr8setBank0(((val>>4) & 0xF)<<13);
	if((val&0x8) == 0)
		ppuSetNameTblSingleLower();
	else
		ppuSetNameTblSingleUpper();
}
bool m78_m78a;
void m78_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if(m78_m78a) //set externally in main.c
		memInitMapperSetPointer(addr, m78a_setParams8XXX);
	else
		memInitMapperSetPointer(addr, m78b_setParams8XXX);
}

void m89_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0(((val>>4) & 7)<<14);
	chr8setBank0((((val&0x80)>>4)|(val & 7))<<13);
	if((val&0x8) == 0)
		ppuSetNameTblSingleLower();
	else
		ppuSetNameTblSingleUpper();
}
void m89_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m89_setParams);
}

void m93_setParams(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0(((val>>4) & 7)<<14); }
void m93_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m93_setParams);
}

void m94_setParams(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0(((val>>2) & 0xF)<<14); }
void m94_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m94_setParams);
}

static void m97_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	//reversed prg bank layout
	prg16setBank1((val & 0xF)<<14);
	switch(val>>6)
	{
		case 0:
			ppuSetNameTblSingleLower();
			break;
		case 1:
			ppuSetNameTblHorizontal();
			break;
		case 2:
			ppuSetNameTblVertical();
			break;
		default: //case 3
			ppuSetNameTblSingleUpper();
			break;
	}
}
void m97_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m97_setParams);
}

static void m152_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0(((val >> 4)&7)<<14);
	chr8setBank0((val & 0xF)<<13);
	if((val&0x80) == 0)
		ppuSetNameTblSingleLower();
	else
		ppuSetNameTblSingleUpper();
}
void m152_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m152_setParams);
}

static void m174_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&0x80) == 0);
	p1632_curPRGBank = ((addr>>4)&7)<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0(((addr>>1)&7)<<13);
	if((addr&1) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m174_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m174_setParams);
}

static void m180_setParams(uint16_t addr, uint8_t val) { (void)addr; prg16setBank1((val & 0xF)<<14); }
void m180_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m180_setParams);
}

static void m200_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	m200SetPrgROMBank((addr&7)<<14);
	chr8setBank0((addr&7)<<13);
	//some assigned to 200 seem to have this reversed so
	//those will look wrong, oh well..
	if((addr&8) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m200_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m200_setParams);
}

static void m202_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&9) != 9);
	p1632_curPRGBank = ((addr>>1)&7)<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0(((addr>>1)&7)<<13);
	if((addr&1) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m202_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m202_setParams);
}

static void m203_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	m200SetPrgROMBank((val>>2)<<14);
	chr8setBank0((val&3)<<13);
}
void m203_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m203_setParams);
}

static void m212_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&0x4000) == 0);
	p1632_curPRGBank = (addr&7)<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0((addr&7)<<13);
	if((addr&8) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m212_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m212_setParams);
}

static void m221_setParams8000(uint16_t addr, uint8_t val)
{
	(void)val;
	if(addr&1)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
	m221_prgmode = ((addr>>1)&1)|((addr>>7)&2);
	//this selection can indeed overlap the inner bank seemingly...
	m221_outerPRGBank = ((addr>>2)&0x3F)<<14;
	m221SetPrgROMBank();
}
static void m221_setParamsC000(uint16_t addr, uint8_t val)
{
	(void)val;
	m221_curPRGBank = (addr&7)<<14;
	m221SetPrgROMBank();
}
void m221_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if((addr&0xC000) == 0x8000) memInitMapperSetPointer(addr, m221_setParams8000);
	else memInitMapperSetPointer(addr, m221_setParamsC000);
}

static void m226_setParams8XX0(uint16_t addr, uint8_t val)
{
	(void)addr;
	p1632_p16 = ((val&0x20) != 0);
	p1632_curPRGBank &= ~0xFFFFF;
	p1632_curPRGBank |= ((val&0x1F)|((val&0x80)>>2))<<14;
	if((val&0x40) == 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
	p1632c8SetPrgROMBank();
}
static void m226_setParams8XX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	p1632_curPRGBank &= 0xFFFFF;
	p1632_curPRGBank |= (val&1)<<20;
	p1632c8SetPrgROMBank();
}
void m226_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if((addr&1) == 0) memInitMapperSetPointer(addr, m226_setParams8XX0);
	else memInitMapperSetPointer(addr, m226_setParams8XX1);
}

static void m229_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	//rather unusual mode switch
	p1632_p16 = ((addr&0x1E) != 0);
	p1632_curPRGBank = (addr&0x1F)<<14;
	p1632c8SetPrgROMBank();
	chr8setBank0((addr&0x1F)<<13);
	if((addr&0x20) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();

}
void m229_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m229_setParams);
}

static void m230_setParamsContra(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0((val&7)<<14); }
static void m230_setParamsMulti(uint16_t addr, uint8_t val)
{
	(void)addr;
	p1632_p16 = ((val&0x20) != 0);
	p1632_curPRGBank = ((val&0x1F)<<14)+(8<<14);
	p1632c8SetPrgROMBank();
	if((val&0x40) != 0)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}
void m230_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if(m230_mode == 0) memInitMapperSetPointer(addr, m230_setParamsContra);
	else memInitMapperSetPointer(addr, m230_setParamsMulti);
}

static void m231_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	m231SetPrgROMBank(((addr&0x1E)|((addr>>5)&1))<<14);
	if((addr&0x80) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m231_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m231_setParams);
}

static void m232_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m232_curPRGBank &= 0xFFFF;
	m232_curPRGBank |= (val & 0x18)<<13;
	m232SetPrgROMBank();
}
static void m232_setParamsCXXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m232_curPRGBank &= ~0xFFFF;
	m232_curPRGBank |= (val & 3)<<14;
	m232SetPrgROMBank();
}
void m232_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if(addr < 0xC000) memInitMapperSetPointer(addr, m232_setParams8XXX);
	else memInitMapperSetPointer(addr, m232_setParamsCXXX);
}

static void m235_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	p1632_p16 = ((addr&0x800) != 0);
	p1632_curPRGBank = (addr&0x1F)<<15;
	if(p1632_p16 && (addr&0x1000) != 0) //upper 16k
		p1632_curPRGBank |= (1<<14);
	p1632_curPRGBank |= (((addr>>8)&3)<<m235_bankshift);
	p1632c8SetPrgROMBank();
	if((addr&0x400) != 0)
		ppuSetNameTblSingleLower();
	else if((addr&0x2000) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m235_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m235_setParams);
}

void m58_reset()
{
	p1632_p16 = false;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
	chr8setBank0(0);
	ppuSetNameTblVertical();
}

void m60_reset()
{
	switch(m60_state)
	{
		case 0:
			m200SetPrgROMBank(0);
			chr8setBank0(0);
			break;
		case 1:
			m200SetPrgROMBank(0x4000);
			chr8setBank0(0x2000);
			break;
		case 2:
			m200SetPrgROMBank(0x8000);
			chr8setBank0(0x4000);
			break;
		case 3:
			m200SetPrgROMBank(0xC000);
			chr8setBank0(0x6000);
			break;
		default:
			break;
	}
	m60_state++;
	m60_state&=3;
}

void m62_reset()
{
	p1632_p16 = false;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
	chr8setBank0(0);
	ppuSetNameTblVertical();
}

void m221_reset()
{
	m221_prgmode = 0;
	m221_curPRGBank = 0; m221_outerPRGBank = 0;
	m221SetPrgROMBank();
}

void m226_reset()
{
	//without this seems to reset
	//into some different (wrong) menu
	//which is interesting...
	p1632_p16 = false;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
	ppuSetNameTblHorizontal();
}

void m230_reset()
{
	m230_mode^=1;
	if(m230_mode == 0)
	{
		prg16setBank0(0<<14);
		prg16setBank1(7<<14);
		ppuSetNameTblVertical();
	}
	else
	{
		p1632_p16 = false;
		p1632_curPRGBank = (8<<14);
		p1632c8SetPrgROMBank();
		ppuSetNameTblHorizontal();
	}
	uint32_t prgaddr;
	for(prgaddr = 0x8000; prgaddr < 0x10000; prgaddr++)
		m230_initSet8(prgaddr);
}

void m235_reset()
{
	p1632_p16 = false;
	p1632_curPRGBank = 0;
	p1632c8SetPrgROMBank();
	ppuSetNameTblVertical();
}
