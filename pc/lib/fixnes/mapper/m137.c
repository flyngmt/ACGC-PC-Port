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

static struct {
	uint8_t reg, regB, regC,
		regc, regd, rege, regf;
	uint8_t mode, mirror;
	bool revhv;
} m137;

static void m137setChrBankPtr()
{
	uint8_t chrBank0 = m137.regc&7;
	if(m137.mode == 0)
	{
		uint8_t chrBank1 = (m137.regd&7)|((m137.regB&1)?0x10:0);
		uint8_t chrBank2 = (m137.rege&7)|((m137.regB&2)?0x10:0);
		uint8_t chrBank3 = (m137.regf&7)|((m137.regB&4)?0x10:0)|((m137.regC&1)?8:0);
		chr1setBank0(chrBank0<<10); chr1setBank1(chrBank1<<10);
		chr1setBank2(chrBank2<<10); chr1setBank3(chrBank3<<10);
	}
	else
	{
		chr1setBank0(chrBank0<<10); chr1setBank1(chrBank0<<10);
		chr1setBank2(chrBank0<<10); chr1setBank3(chrBank0<<10);
	}
}

static void m138setChrBankPtr()
{
	uint8_t chrBank0 = (m137.regc&7)|((m137.regB<<3)&0x38);
	if(m137.mode == 0)
	{
		uint8_t chrBank1 = (m137.regd&7)|((m137.regB<<3)&0x38);
		uint8_t chrBank2 = (m137.rege&7)|((m137.regB<<3)&0x38);
		uint8_t chrBank3 = (m137.regf&7)|((m137.regB<<3)&0x38);
		chr2setBank0(chrBank0<<11); chr2setBank1(chrBank1<<11);
		chr2setBank2(chrBank2<<11); chr2setBank3(chrBank3<<11);
	}
	else
	{
		chr2setBank0(chrBank0<<11); chr2setBank1(chrBank0<<11);
		chr2setBank2(chrBank0<<11); chr2setBank3(chrBank0<<11);
	}
}

static void m139setChrBankPtr()
{
	uint8_t chrBank0 = ((m137.regc<<2)&0x1C)|((m137.regB<<5)&0xE0);
	if(m137.mode == 0)
	{
		uint8_t chrBank1 = ((m137.regd<<2)&0x1C)|((m137.regB<<5)&0xE0);
		uint8_t chrBank2 = ((m137.rege<<2)&0x1C)|((m137.regB<<5)&0xE0);
		uint8_t chrBank3 = ((m137.regf<<2)&0x1C)|((m137.regB<<5)&0xE0);
		chr2setBank0((chrBank0|0)<<11); chr2setBank1((chrBank1|1)<<11);
		chr2setBank2((chrBank2|2)<<11); chr2setBank3((chrBank3|3)<<11);
	}
	else
	{
		chr2setBank0((chrBank0|0)<<11); chr2setBank1((chrBank0|1)<<11);
		chr2setBank2((chrBank0|2)<<11); chr2setBank3((chrBank0|3)<<11);
	}
}

static void m141setChrBankPtr()
{
	uint8_t chrBank0 = ((m137.regc<<1)&0xE)|((m137.regB<<4)&0x70);
	if(m137.mode == 0)
	{
		uint8_t chrBank1 = ((m137.regd<<1)&0xE)|((m137.regB<<4)&0x70);
		uint8_t chrBank2 = ((m137.rege<<1)&0xE)|((m137.regB<<4)&0x70);
		uint8_t chrBank3 = ((m137.regf<<1)&0xE)|((m137.regB<<4)&0x70);
		chr2setBank0((chrBank0|0)<<11); chr2setBank1((chrBank1|1)<<11);
		chr2setBank2((chrBank2|0)<<11); chr2setBank3((chrBank3|1)<<11);
	}
	else
	{
		chr2setBank0((chrBank0|0)<<11); chr2setBank1((chrBank0|1)<<11);
		chr2setBank2((chrBank0|0)<<11); chr2setBank3((chrBank0|1)<<11);
	}
}

static void m137_commonInit()
{
	m137.reg = 0, m137.regB = 0, m137.regC = 0,
	m137.regc = 0, m137.regd = 0, m137.rege = 0, m137.regf = 0;
	m137.mode = 0, m137.mirror = 0;
}

void m137init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m137_commonInit();
	m137.revhv = true;
	prg32init(prgROMin, prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr1init(chrROMin, chrROMsizeIn);
	m137setChrBankPtr();
	chr1setBank4(chrROMsizeIn - 0x1000);
	chr1setBank5(chrROMsizeIn - 0x0C00);
	chr1setBank6(chrROMsizeIn - 0x0800);
	chr1setBank7(chrROMsizeIn - 0x0400);
	printf("Mapper 137 inited\n");
}

void m138init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m137_commonInit();
	m137.revhv = false;
	prg32init(prgROMin, prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr2init(chrROMin, chrROMsizeIn);
	m138setChrBankPtr();
	printf("Mapper 138 inited\n");
}

void m139init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m137_commonInit();
	m137.revhv = false;
	prg32init(prgROMin, prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr2init(chrROMin, chrROMsizeIn);
	m139setChrBankPtr();
	printf("Mapper 139 inited\n");
}

void m141init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m137_commonInit();
	m137.revhv = false;
	prg32init(prgROMin, prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	chr2init(chrROMin, chrROMsizeIn);
	m141setChrBankPtr();
	printf("Mapper 141 inited\n");
}

static void m137common_setParams4100(uint16_t addr, uint8_t val) { (void)addr; m137.reg = val&7; }
static void m137common_setParams4101(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(m137.reg&7)
	{
		case 0:
			m137.regc = val&7;
			break;
		case 1:
			m137.regd = val&7;
			break;
		case 2:
			m137.rege = val&7;
			break;
		case 3:
			m137.regf = val&7;
			break;
		case 4:
			m137.regB = val&7;
			break;
		case 5:
			prg32setBank0((val&7)<<15);
			break;
		case 6:
			m137.regC = val&1;
			break;
		case 7:
			m137.mode = val&1;
			m137.mirror = (val>>1)&3;
			//update ppu mirroring
			if(m137.mirror == 0 || m137.mode)
				m137.revhv ? ppuSetNameTblHorizontal() : ppuSetNameTblVertical();
			else if(m137.mirror == 1)
				m137.revhv ? ppuSetNameTblVertical() : ppuSetNameTblHorizontal();
			else if(m137.mirror == 2)
				ppuSetNameTblCustom(0,0x400,0x400,0x400);
			else if(m137.mirror == 3)
				ppuSetNameTblSingleLower();
			break;
	}
}
static void m137setParams4101(uint16_t addr, uint8_t val) { m137common_setParams4101(addr,val); m137setChrBankPtr(); }
void m137initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xC101;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m137common_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m137setParams4101);
}

static void m138setParams4101(uint16_t addr, uint8_t val) { m137common_setParams4101(addr,val); m138setChrBankPtr(); }
void m138initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xC101;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m137common_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m138setParams4101);
}

static void m139setParams4101(uint16_t addr, uint8_t val) { m137common_setParams4101(addr,val); m139setChrBankPtr(); }
void m139initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xC101;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m137common_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m139setParams4101);
}

static void m141setParams4101(uint16_t addr, uint8_t val) { m137common_setParams4101(addr,val); m141setChrBankPtr(); }
void m141initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xC101;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m137common_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m141setParams4101);
}
