/*
 * Copyright (C) 2019 FIX94
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

//sector erase and byte write
enum {
	//get erase/write cmd
	M30_STATE_C0_INIT = 0,
	M30_STATE_80_INIT,
	M30_STATE_C1_INIT,
	M30_STATE_81_INIT,
	M30_STATE_C2_INIT,
	M30_STATE_82_INIT,
	//erase cmd check
	M30_STATE_C3_DEL,
	M30_STATE_83_DEL,
	M30_STATE_C4_DEL,
	M30_STATE_84_DEL,
	//erase cmd execute
	M30_STATE_C5_DEL,
	M30_STATE_85_DEL,
	//write cmd execute
	M30_STATE_C3_WRI,
	M30_STATE_83_WRI,
};

static struct {
	uint8_t chrRAM[0x8000];
	uint8_t *chrRAMBankPtr;
	uint8_t *prgRAMptr;
	uint8_t *prgRAMBankPtr;
	uint32_t prgRAMsize;
	uint32_t prgRAMand;
	uint8_t step, manID, devID;
	bool software_id;
} m30;
//used externally
bool m30_flashable;
bool m30_singlescreen;

void m30init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	if(m30_flashable)
	{
		m30.prgRAMptr = prgRAMin;
		m30.prgRAMBankPtr = m30.prgRAMptr;
		m30.prgRAMsize = prgRAMsizeIn;
		m30.prgRAMand = mapperGetAndValue(prgRAMsizeIn);
		prg16init(prgRAMin, prgRAMsizeIn);
		prg16setBank1(prgRAMsizeIn - 0x4000);
		m30.step = M30_STATE_C0_INIT; //sequence progress
		m30.software_id = false; //replaces 8000/8001
		m30.manID = 0xBF; //SST, Device ID Below
		m30.devID = (prgRAMsizeIn == 0x20000 ? 0xB5 : (prgRAMsizeIn == 0x40000 ? 0xB6 : (prgRAMsizeIn == 0x80000 ? 0xB7 : 0)));
		printf("Mapper 30 flashable, Man ID %02x Dev ID %02x\n", m30.manID, m30.devID);
	}
	else
	{
		m30.prgRAMptr = NULL, m30.prgRAMBankPtr = NULL;
		m30.prgRAMsize = 0;
		prg16init(prgROMin, prgROMsizeIn);
		prg16setBank1(prgROMsizeIn - 0x4000);
		printf("Mapper 30 not flashable\n");
	}
	(void)chrROMin; (void)chrROMsizeIn;
	m30.chrRAMBankPtr = m30.chrRAM;
	if(m30_singlescreen)
		ppuSetNameTblSingleLower();
	printf("Mapper 30 inited\n");
}

static void m30setParamsNoFlash(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg16setBank0((val&0x1F)<<14);
	m30.chrRAMBankPtr = m30.chrRAM+((val&0x60)<<8);
	if(m30_singlescreen)
	{
		if(val & 0x80)
			ppuSetNameTblSingleUpper();
		else
			ppuSetNameTblSingleLower();
	}
}

static uint8_t m30GetId0(uint16_t addr) { (void)addr; return m30.manID; }
static uint8_t m30GetId1(uint16_t addr) { (void)addr; return m30.devID; }

static void m30sidEntry()
{
	//printf("M30 Software ID CMD Entry\n");
	m30.software_id = true;
	memInitMapperGetPointer(0x8000, m30GetId0);
	memInitMapperGetPointer(0x8001, m30GetId1);
}

static void m30sidExit()
{
	//printf("M30 Software ID CMD Exit\n");
	m30.software_id = false;
	prg16initGet8(0x8000);
	prg16initGet8(0x8001);
}

static void m30setParams8000(uint16_t addr, uint8_t val)
{
	//printf("%04x %02x %02x\n", addr, val, m30.step);
	if(val == 0xF0 && m30.software_id)
		m30sidExit();
	switch(m30.step)
	{
		//initial cmd check
		case M30_STATE_80_INIT:
			if(addr == 0x9555 && val == 0xAA)
				m30.step = M30_STATE_C1_INIT;
			else goto _8000_step_reset;
			break;
		case M30_STATE_81_INIT:
			if(addr == 0xAAAA && val == 0x55)
				m30.step = M30_STATE_C2_INIT;
			else goto _8000_step_reset;
			break;
		case M30_STATE_82_INIT:
			if(addr == 0x9555 && val == 0x80)
			{
				//printf("M30 Erase CMD\n");
				m30.step = M30_STATE_C3_DEL;
			}
			else if(addr == 0x9555 && val == 0xA0)
			{
				//printf("M30 Write CMD\n");
				m30.step = M30_STATE_C3_WRI;
			}
			else
			{
				if(addr == 0x9555 && val == 0x90 && !m30.software_id)
					m30sidEntry();
				//redundant since any address exits software id?
				//else if(addr == 0x9555 && val == 0xF0 && m30.software_id)
				//	m30sidExit();
				goto _8000_step_reset;
			}
			break;
		//delete cmd check
		case M30_STATE_83_DEL:
			if(addr == 0x9555 && val == 0xAA)
				m30.step = M30_STATE_C4_DEL;
			else goto _8000_step_reset;
			break;
		case M30_STATE_84_DEL:
			if(addr == 0xAAAA && val == 0x55)
				m30.step = M30_STATE_C5_DEL;
			else goto _8000_step_reset;
			break;
		//executes delete
		case M30_STATE_85_DEL:
			if(addr == 0x9555 && val == 0x10) //full erase
			{
				//printf("M30 Full Erase\n");
				if(m30.prgRAMptr && m30.prgRAMsize)
					memset(m30.prgRAMptr, 0xFF, m30.prgRAMsize);
			}
			else if(val == 0x30) //sector erase
			{
				//printf("M30 Sector Erase %04x\n", (addr&0x3000));
				if(m30.prgRAMBankPtr)
					memset(m30.prgRAMBankPtr+(addr&0x3000), 0xFF, 0x1000);
			}
			goto _8000_step_reset;
		//executes write
		case M30_STATE_83_WRI:
			if(m30.prgRAMBankPtr) //byte write
			{
				//printf("M30 Byte Write %04x %02x\n", addr&0x3FFF, val);
				m30.prgRAMBankPtr[addr&0x3FFF] &= val;
			}
			goto _8000_step_reset;
		//any other state or state verify fail
		//will result in a command reset
		default:
		_8000_step_reset:
			m30.step = M30_STATE_C0_INIT;
			break;
	}
}

static void m30setParamsC000(uint16_t addr, uint8_t val)
{
	//printf("%04x %02x %02x\n", addr, val, m30.step);
	m30setParamsNoFlash(addr, val);
	if(val == 0xF0 && m30.software_id)
		m30sidExit();
	switch(m30.step)
	{
		//initial cmd check
		case M30_STATE_C0_INIT:
			if(addr == 0xC000 && val == 1)
				m30.step = M30_STATE_80_INIT;
			break;
		case M30_STATE_C1_INIT:
			if(addr == 0xC000 && val == 0)
				m30.step = M30_STATE_81_INIT;
			else goto c000_step_reset;
			break;
		case M30_STATE_C2_INIT:
			if(addr == 0xC000 && val == 1)
				m30.step = M30_STATE_82_INIT;
			else goto c000_step_reset;
			break;
		//delete cmd check
		case M30_STATE_C3_DEL:
			if(addr == 0xC000 && val == 1)
				m30.step = M30_STATE_83_DEL;
			else goto c000_step_reset;
			break;
		case M30_STATE_C4_DEL:
			if(addr == 0xC000 && val == 0)
				m30.step = M30_STATE_84_DEL;
			else goto c000_step_reset;
			break;
		//executes delete
		case M30_STATE_C5_DEL:
			if(addr == 0xC000 && val < 0x20)
			{
				m30.step = M30_STATE_85_DEL;
				if(m30.prgRAMptr) //for memset
				{
					//printf("M30 Delete Bank %04x\n", val);
					m30.prgRAMBankPtr = m30.prgRAMptr+((val<<14)&m30.prgRAMand);
				}
			}
			else goto c000_step_reset;
			break;
		//executes write
		case M30_STATE_C3_WRI:
			if(addr == 0xC000 && val < 0x20)
			{
				m30.step = M30_STATE_83_WRI;
				if(m30.prgRAMptr) //for byte write
				{
					//printf("M30 Write Bank %04x\n", val);
					m30.prgRAMBankPtr = m30.prgRAMptr+((val<<14)&m30.prgRAMand);
				}
			}
			else goto c000_step_reset;
			break;
		//any other state or state verify fail
		//will result in a command reset
		default:
		c000_step_reset:
			//immediately do M30_STATE_C0_INIT check
			if(addr == 0xC000 && val == 1)
				m30.step = M30_STATE_80_INIT;
			else //different values, full reset
				m30.step = M30_STATE_C0_INIT;
			break;
	}
}

void m30initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	if(m30_flashable)
	{
		if(addr < 0xC000)
			memInitMapperSetPointer(addr, m30setParams8000);
		else
			memInitMapperSetPointer(addr, m30setParamsC000);
	}
	else
		memInitMapperSetPointer(addr, m30setParamsNoFlash);
}

static uint8_t m30ChrGetRAM(uint16_t addr) { return m30.chrRAMBankPtr[addr]; }
void m30initPPUGet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, m30ChrGetRAM);
}

static void m30ChrSetRAM(uint16_t addr, uint8_t val) { m30.chrRAMBankPtr[addr] = val; }
void m30initPPUSet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUSetPointer(addr, m30ChrSetRAM);
}
