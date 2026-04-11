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

static uint32_t m156_CHRBank[8];
static bool m156_usesPrgRAM;

void m156init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	prg16setBank1(prgROMsizeIn - 0x4000);
	if(prgRAMin && prgRAMsizeIn)
	{
		m156_usesPrgRAM = true;
		prgRAM8init(prgRAMin);
	}
	else
		m156_usesPrgRAM = false;
	memset(m156_CHRBank,0,8*sizeof(uint32_t));
	chr1init(chrROMin,chrROMsizeIn);
	ppuSetNameTblSingleLower(); //seems to be default state?
	printf("Mapper 156 inited\n");
}

void m156initGet8(uint16_t addr)
{
	if(m156_usesPrgRAM)
		prgRAM8initGet8(addr);
	prg16initGet8(addr);
}

static void m156setParamsC000(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[0] = (m156_CHRBank[0]&0xFF00)|val; chr1setBank0(m156_CHRBank[0]<<10); }
static void m156setParamsC001(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[1] = (m156_CHRBank[1]&0xFF00)|val; chr1setBank1(m156_CHRBank[1]<<10); }
static void m156setParamsC002(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[2] = (m156_CHRBank[2]&0xFF00)|val; chr1setBank2(m156_CHRBank[2]<<10); }
static void m156setParamsC003(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[3] = (m156_CHRBank[3]&0xFF00)|val; chr1setBank3(m156_CHRBank[3]<<10); }
static void m156setParamsC004(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[0] = (m156_CHRBank[0]&0xFF)|(val<<8); chr1setBank0(m156_CHRBank[0]<<10); }
static void m156setParamsC005(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[1] = (m156_CHRBank[1]&0xFF)|(val<<8); chr1setBank1(m156_CHRBank[1]<<10); }
static void m156setParamsC006(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[2] = (m156_CHRBank[2]&0xFF)|(val<<8); chr1setBank2(m156_CHRBank[2]<<10); }
static void m156setParamsC007(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[3] = (m156_CHRBank[3]&0xFF)|(val<<8); chr1setBank3(m156_CHRBank[3]<<10); }
static void m156setParamsC008(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[4] = (m156_CHRBank[4]&0xFF00)|val; chr1setBank4(m156_CHRBank[4]<<10); }
static void m156setParamsC009(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[5] = (m156_CHRBank[5]&0xFF00)|val; chr1setBank5(m156_CHRBank[5]<<10); }
static void m156setParamsC00A(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[6] = (m156_CHRBank[6]&0xFF00)|val; chr1setBank6(m156_CHRBank[6]<<10); }
static void m156setParamsC00B(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[7] = (m156_CHRBank[7]&0xFF00)|val; chr1setBank7(m156_CHRBank[7]<<10); }
static void m156setParamsC00C(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[4] = (m156_CHRBank[4]&0xFF)|(val<<8); chr1setBank4(m156_CHRBank[4]<<10); }
static void m156setParamsC00D(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[5] = (m156_CHRBank[5]&0xFF)|(val<<8); chr1setBank5(m156_CHRBank[5]<<10); }
static void m156setParamsC00E(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[6] = (m156_CHRBank[6]&0xFF)|(val<<8); chr1setBank6(m156_CHRBank[6]<<10); }
static void m156setParamsC00F(uint16_t addr, uint8_t val) { (void)addr; m156_CHRBank[7] = (m156_CHRBank[7]&0xFF)|(val<<8); chr1setBank7(m156_CHRBank[7]<<10); }

static void m156setParamsC010(uint16_t addr, uint8_t val) { (void)addr; prg16setBank0(val<<14); }

static void m156setParamsC014(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val&1)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}

void m156initSet8(uint16_t addr)
{
	if(m156_usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr == 0xC000) memInitMapperSetPointer(addr, m156setParamsC000);
	else if(addr == 0xC001) memInitMapperSetPointer(addr, m156setParamsC001);
	else if(addr == 0xC002) memInitMapperSetPointer(addr, m156setParamsC002);
	else if(addr == 0xC003) memInitMapperSetPointer(addr, m156setParamsC003);
	else if(addr == 0xC004) memInitMapperSetPointer(addr, m156setParamsC004);
	else if(addr == 0xC005) memInitMapperSetPointer(addr, m156setParamsC005);
	else if(addr == 0xC006) memInitMapperSetPointer(addr, m156setParamsC006);
	else if(addr == 0xC007) memInitMapperSetPointer(addr, m156setParamsC007);
	else if(addr == 0xC008) memInitMapperSetPointer(addr, m156setParamsC008);
	else if(addr == 0xC009) memInitMapperSetPointer(addr, m156setParamsC009);
	else if(addr == 0xC00A) memInitMapperSetPointer(addr, m156setParamsC00A);
	else if(addr == 0xC00B) memInitMapperSetPointer(addr, m156setParamsC00B);
	else if(addr == 0xC00C) memInitMapperSetPointer(addr, m156setParamsC00C);
	else if(addr == 0xC00D) memInitMapperSetPointer(addr, m156setParamsC00D);
	else if(addr == 0xC00E) memInitMapperSetPointer(addr, m156setParamsC00E);
	else if(addr == 0xC00F) memInitMapperSetPointer(addr, m156setParamsC00F);
	else if(addr == 0xC010) memInitMapperSetPointer(addr, m156setParamsC010);
	else if(addr == 0xC014) memInitMapperSetPointer(addr, m156setParamsC014);
}
