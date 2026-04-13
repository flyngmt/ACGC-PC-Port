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

static uint8_t *m206chrROM;
static uint32_t m206chrROMand;
static uint8_t m206Register;
static uint8_t *m206CHRBank0Ptr, *m206CHRBank1Ptr,
				*m206CHRBank2Ptr, *m206CHRBank3Ptr,
				*m206CHRBank4Ptr, *m206CHRBank5Ptr;

void m206init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	prg8setBank2(prgROMsizeIn - 0x4000);
	prg8setBank3(prgROMsizeIn - 0x2000);
	(void)prgRAMin; (void)prgRAMsizeIn;
	if(chrROMin && chrROMsizeIn)
	{
		m206chrROM = chrROMin;
		m206chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
		printf("s206 missing chr rom??? this will crash\n");
	m206CHRBank0Ptr = m206CHRBank1Ptr = m206CHRBank2Ptr =
		m206CHRBank3Ptr = m206CHRBank4Ptr = m206CHRBank5Ptr = chrROMin;
	m206Register = 0;
	printf("Mapper 206 (and Variants) inited\n");
}

static uint16_t m95nt0, m95nt1;
void m95init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m206init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	//some extra regs
	m95nt0 = 0, m95nt1 = 0;
	ppuSetNameTblCustom(m95nt0,m95nt0,m95nt1,m95nt1);
}

//"Huang Di" appears to require PRG RAM, see when booting up the game in the
//top right it will have an X without PRG RAM and the game will not function
//correctly, with PRG RAM however it will display "OK" and actually work
static bool m112_usesPrgRAM;
//extended chr bank bit used by for example "Fighting Hero III"
static uint16_t m112b0Upper, m112b1Upper, m112b2Upper, m112b3Upper;
void m112init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	m206init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		m112_usesPrgRAM = true;
	}
	else
		m112_usesPrgRAM = false;
	m112b0Upper = 0, m112b1Upper = 0, m112b2Upper = 0, m112b3Upper = 0;
}

void m112initGet8(uint16_t addr)
{
	if(m112_usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

static void m206setParams8000(uint16_t addr, uint8_t val)
{
	(void)addr;
	m206Register = val&7;
}

static void m76setParams8001(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(m206Register)
	{
		case 2:
			m206CHRBank2Ptr = m206chrROM+((val<<11)&m206chrROMand);
			break;
		case 3:
			m206CHRBank3Ptr = m206chrROM+((val<<11)&m206chrROMand);
			break;
		case 4:
			m206CHRBank4Ptr = m206chrROM+((val<<11)&m206chrROMand);
			break;
		case 5:
			m206CHRBank5Ptr = m206chrROM+((val<<11)&m206chrROMand);
			break;
		case 6:
			prg8setBank0(val<<13);
			break;
		case 7:
			prg8setBank1(val<<13);
			break;
		default:
			break;
	}
}
static void m88setParams8001(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(m206Register)
	{
		case 0:
			m206CHRBank0Ptr = m206chrROM+(((val&0x3E)<<10)&m206chrROMand);
			break;
		case 1:
			m206CHRBank1Ptr = m206chrROM+(((val&0x3E)<<10)&m206chrROMand);
			break;
		case 2:
			m206CHRBank2Ptr = m206chrROM+(((val|0x40)<<10)&m206chrROMand);
			break;
		case 3:
			m206CHRBank3Ptr = m206chrROM+(((val|0x40)<<10)&m206chrROMand);
			break;
		case 4:
			m206CHRBank4Ptr = m206chrROM+(((val|0x40)<<10)&m206chrROMand);
			break;
		case 5:
			m206CHRBank5Ptr = m206chrROM+(((val|0x40)<<10)&m206chrROMand);
			break;
		case 6:
			prg8setBank0(val<<13);
			break;
		case 7:
			prg8setBank1(val<<13);
			break;
	}
}
static void m112setParamsA000(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(m206Register)
	{
		case 0:
			prg8setBank0(val<<13);
			break;
		case 1:
			prg8setBank1(val<<13);
			break;
		case 2:
			m206CHRBank0Ptr = m206chrROM+(((val&~1)<<10)&m206chrROMand);
			break;
		case 3:
			m206CHRBank1Ptr = m206chrROM+(((val&~1)<<10)&m206chrROMand);
			break;
		case 4:
			m206CHRBank2Ptr = m206chrROM+(((val|m112b0Upper)<<10)&m206chrROMand);
			break;
		case 5:
			m206CHRBank3Ptr = m206chrROM+(((val|m112b1Upper)<<10)&m206chrROMand);
			break;
		case 6:
			m206CHRBank4Ptr = m206chrROM+(((val|m112b2Upper)<<10)&m206chrROMand);
			break;
		case 7:
			m206CHRBank5Ptr = m206chrROM+(((val|m112b3Upper)<<10)&m206chrROMand);
			break;
	}
}
static void m206setParams8001(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(m206Register)
	{
		case 0:
			m206CHRBank0Ptr = m206chrROM+(((val&~1)<<10)&m206chrROMand);
			break;
		case 1:
			m206CHRBank1Ptr = m206chrROM+(((val&~1)<<10)&m206chrROMand);
			break;
		case 2:
			m206CHRBank2Ptr = m206chrROM+((val<<10)&m206chrROMand);
			break;
		case 3:
			m206CHRBank3Ptr = m206chrROM+((val<<10)&m206chrROMand);
			break;
		case 4:
			m206CHRBank4Ptr = m206chrROM+((val<<10)&m206chrROMand);
			break;
		case 5:
			m206CHRBank5Ptr = m206chrROM+((val<<10)&m206chrROMand);
			break;
		case 6:
			prg8setBank0(val<<13);
			break;
		case 7:
			prg8setBank1(val<<13);
			break;
	}
}

static void m95setParams8001(uint16_t addr, uint8_t val)
{
	m206setParams8001(addr,val);
	//some extra regs
	if(m206Register == 0)
	{
		m95nt0 = (val&0x20) ? 0x400 : 0;
		ppuSetNameTblCustom(m95nt0,m95nt0,m95nt1,m95nt1);
	}
	else if(m206Register == 1)
	{
		m95nt1 = (val&0x20) ? 0x400 : 0;
		ppuSetNameTblCustom(m95nt0,m95nt0,m95nt1,m95nt1);
	}
}

static void m112setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	m112b0Upper = (val&0x10)<<4, m112b1Upper = (val&0x20)<<3,
	m112b2Upper = (val&0x40)<<2, m112b3Upper = (val&0x80)<<1;
}
static void m112setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((val&1)==0)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}

static void m154setParamsMirror(uint16_t addr, uint8_t val)
{
	(void)addr;
	if((val&0x40)==0)
		ppuSetNameTblSingleLower();
	else
		ppuSetNameTblSingleUpper();
}
static void m154setParams8000(uint16_t addr, uint8_t val)
{
	m206setParams8000(addr,val);
	m154setParamsMirror(addr,val);
}
static void m154setParams8001(uint16_t addr, uint8_t val)
{
	m88setParams8001(addr,val);
	m154setParamsMirror(addr,val);
}

void m76initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m206setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m76setParams8001);
}
void m88initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m206setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m88setParams8001);
}
void m95initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m206setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m95setParams8001);
}
void m112initSet8(uint16_t ori_addr)
{
	if(m112_usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m206setParams8000);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, m112setParamsA000);
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, m112setParamsC000);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, m112setParamsE000);
}
void m154initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m154setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m154setParams8001);
	else if(ori_addr >= 0x8000) memInitMapperSetPointer(ori_addr, m154setParamsMirror);
}
void m206initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m206setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m206setParams8001);
}

static uint8_t m76getCHRBank2(uint16_t addr) { return m206CHRBank2Ptr[addr&0x7FF]; }
static uint8_t m76getCHRBank3(uint16_t addr) { return m206CHRBank3Ptr[addr&0x7FF]; }
static uint8_t m76getCHRBank4(uint16_t addr) { return m206CHRBank4Ptr[addr&0x7FF]; }
static uint8_t m76getCHRBank5(uint16_t addr) { return m206CHRBank5Ptr[addr&0x7FF]; }

void m76initPPUGet8(uint16_t addr)
{
	if(addr < 0x800) memInitMapperPPUGetPointer(addr, m76getCHRBank2);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, m76getCHRBank3);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, m76getCHRBank4);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, m76getCHRBank5);
}

static uint8_t m206getCHRBank0(uint16_t addr) { return m206CHRBank0Ptr[addr&0x7FF]; }
static uint8_t m206getCHRBank1(uint16_t addr) { return m206CHRBank1Ptr[addr&0x7FF]; }
static uint8_t m206getCHRBank2(uint16_t addr) { return m206CHRBank2Ptr[addr&0x3FF]; }
static uint8_t m206getCHRBank3(uint16_t addr) { return m206CHRBank3Ptr[addr&0x3FF]; }
static uint8_t m206getCHRBank4(uint16_t addr) { return m206CHRBank4Ptr[addr&0x3FF]; }
static uint8_t m206getCHRBank5(uint16_t addr) { return m206CHRBank5Ptr[addr&0x3FF]; }

void m206initPPUGet8(uint16_t addr)
{
	if(addr < 0x800) memInitMapperPPUGetPointer(addr, m206getCHRBank0);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, m206getCHRBank1);
	else if(addr < 0x1400) memInitMapperPPUGetPointer(addr, m206getCHRBank2);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, m206getCHRBank3);
	else if(addr < 0x1C00) memInitMapperPPUGetPointer(addr, m206getCHRBank4);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, m206getCHRBank5);
}

void m206initPPUSet8(uint16_t addr)
{
	(void)addr;
}
