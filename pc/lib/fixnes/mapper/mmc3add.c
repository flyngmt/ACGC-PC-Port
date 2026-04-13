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
#include "../mapper_h/mmc3.h"
#include "../mapper_h/mmc3add.h"
#include "../mapper_h/common.h"

extern uint32_t mmc3_prgROMadd;
extern uint32_t mmc3_prgROMand;
extern uint32_t mmc3_chrROMand;
static bool mmc3add_regLock;
static bool mmc3add_prgRAMenable;
extern void mmc3SetPrgROMBankPtr();
extern void mmc3SetChrROMBankPtr();

void m37_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m37_reset(); //start with default config
	printf("Mapper 37 (Mapper 4 Game Select) inited\n");
}

void m44_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m44_reset(); //start with default config
	printf("Mapper 44 (Mapper 4 Game Select) inited\n");
}

static uint8_t m45_curReg, m45_chrROMandVal;

void m45_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m45_reset(); //start with default config
	printf("Mapper 45 (Mapper 4 Game Select) inited\n");
}

void m47_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m47_reset(); //start with default config
	printf("Mapper 47 (Mapper 4 Game Select) inited\n");
}

static uint8_t m49_prgmode;
static uint8_t m49_prgreg;

void m49_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	//for prg mode
	prg32init(prgROMin,prgROMsizeIn);
	m49_reset(); //start with default config
	printf("Mapper 49 (Mapper 4 Game Select) inited\n");
}

void m52_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m52_reset();
	printf("Mapper 52 (Mapper 4 Game Select) inited\n");
}

void m205_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	m205_reset(); //start with default config
	printf("Mapper 205 (Mapper 4 Game Select) inited\n");
}

void mmc3NoRAMInitGet8(uint16_t addr)
{
	if(addr >= 0x8000)
		mmc3initGet8(addr);
}

static void mmc3addSetParamsAXX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc3add_prgRAMenable = (!!(val&0x80)) && ((val&0x40) == 0);
}

void m49_initGet8(uint16_t addr)
{
	if(addr >= 0x8000)
	{
		if(m49_prgmode == 0)
			prg32initGet8(addr);
		else
			mmc3initGet8(addr);
	}
}

static void m37_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!mmc3add_prgRAMenable)
		return;
	val &= 7;
	if(val < 3)
	{
		mmc3_prgROMadd = 0;
		mmc3_prgROMand = 0xFFFF;
		mmc3SetChrROMadd(0);
		mmc3_chrROMand = 0x1FFFF;
	}
	else if(val == 3)
	{
		mmc3_prgROMadd = 0x10000;
		mmc3_prgROMand = 0xFFFF;
		mmc3SetChrROMadd(0);
		mmc3_chrROMand = 0x1FFFF;
	}
	else if(val < 7)
	{
		mmc3_prgROMadd = 0x20000;
		mmc3_prgROMand = 0x1FFFF;
		mmc3SetChrROMadd(0x20000);
		mmc3_chrROMand = 0x1FFFF;
	}
	else //val == 7
	{
		mmc3_prgROMadd = 0x30000;
		mmc3_prgROMand = 0xFFFF;
		mmc3SetChrROMadd(0x20000);
		mmc3_chrROMand = 0x1FFFF;
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
}

void m37_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m37_setParams6XXX);
	else if((addr&0xE001) == 0xA001) //reg enable/disable
		memInitMapperSetPointer(addr, mmc3addSetParamsAXX1);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m44_setParamsAXX1(uint16_t addr, uint8_t val)
{
	(void)addr;
	val &= 7;
	switch(val)
	{
		case 0:
			mmc3_prgROMadd = 0;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 1:
			mmc3_prgROMadd = 0x20000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x20000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 2:
			mmc3_prgROMadd = 0x40000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x40000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 3:
			mmc3_prgROMadd = 0x60000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x60000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 4:
			mmc3_prgROMadd = 0x80000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x80000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 5:
			mmc3_prgROMadd = 0xA0000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0xA0000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		default: //6,7
			mmc3_prgROMadd = 0xC0000;
			mmc3_prgROMand = 0x3FFFF;
			mmc3SetChrROMadd(0xC0000);
			mmc3_chrROMand = 0x3FFFF;
			break;
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
}

void m44_initSet8(uint16_t addr)
{
	//special select regs
	if((addr&0xE001) == 0xA001)
		memInitMapperSetPointer(addr, m44_setParamsAXX1);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m45_setChrROMand()
{
	if(mmc3GetChrROMadd() || m45_chrROMandVal) //default chr rom mask generation
		mmc3_chrROMand = (((0xFF >> ((~m45_chrROMandVal)&0xF))+1)<<10)-1;
	else //this code is just a guess, if no chr rom or/and value, use full and value
		mmc3_chrROMand = (((0xFF >> ((~0xF)&0xF))+1)<<10)-1;
}

static void m45_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(m45_curReg == 0)
	{
		mmc3SetChrROMadd((mmc3GetChrROMadd() & ~0x3FFFF) | (val<<10));
		m45_setChrROMand(); //update because of new add value
		//printf("mmc3_chrROMadd r0 %08x inVal %02x\n", mmc3GetChrROMadd(), val);
	}
	else if(m45_curReg == 1)
	{
		mmc3_prgROMadd = val<<13;
		//printf("mmc3_prgROMadd %08x inVal %02x\n", mmc3_prgROMadd, val);
	}
	else if(m45_curReg == 2)
	{
		mmc3SetChrROMadd((mmc3GetChrROMadd() & 0x3FFFF) | ((val>>4)<<18));
		m45_chrROMandVal = val&0xF;
		m45_setChrROMand();
		//printf("mmc3_chrROMand %08x mmc3_chrROMadd r1 %08x inVal %02x\n", mmc3_chrROMand, mmc3GetChrROMadd(), val);
	}
	else if(m45_curReg == 3)
	{
		mmc3add_regLock = ((val&0x40) != 0);
		mmc3_prgROMand = ((((val^0x3F)&0x3F)+1)<<13)-1;
		//printf("mmc3add_regLock %d mmc3_prgROMand %08x inVal %02x\n", mmc3add_regLock, mmc3_prgROMand, val);
		if(mmc3add_regLock)
		{
			//this will allow ram writes
			//printf("allowing prg ram\n");
			uint16_t ramaddr;
			for(ramaddr = 0x6000; ramaddr < 0x8000; ramaddr++)
				m45_initSet8(ramaddr);
		}
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
	m45_curReg++;
	m45_curReg&=3;
}

void m45_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000 && !mmc3add_regLock)
		memInitMapperSetPointer(addr, m45_setParams6XXX);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m47_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!mmc3add_prgRAMenable)
		return;
	val &= 1;
	if(val == 0)
	{
		mmc3_prgROMadd = 0;
		mmc3SetChrROMadd(0);
	}
	else
	{
		mmc3_prgROMadd = 0x20000;
		mmc3SetChrROMadd(0x20000);
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
}

void m47_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m47_setParams6XXX);
	else if((addr&0xE001) == 0xA001) //prg ram enable/disable
		memInitMapperSetPointer(addr, mmc3addSetParamsAXX1);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m49_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!mmc3add_prgRAMenable)
		return;
	switch(val>>6)
	{
		case 0:
			mmc3_prgROMadd = 0;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 1:
			mmc3_prgROMadd = 0x20000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x20000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 2:
			mmc3_prgROMadd = 0x40000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x40000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		case 3:
			mmc3_prgROMadd = 0x60000;
			mmc3_prgROMand = 0x1FFFF;
			mmc3SetChrROMadd(0x60000);
			mmc3_chrROMand = 0x1FFFF;
			break;
		default:
			break;
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
	//for prgmode 0
	m49_prgreg = (val>>4)&3;
	prg32setBank0((m49_prgreg<<15)|mmc3_prgROMadd);
	//reset how prg rom is read
	if(!!(val&1) ^ m49_prgmode)
	{
		m49_prgmode = val&1;
		//printf("Switched to prg mode %d\n", m49_prgmode);
		uint32_t addr;
		for(addr = 0x8000; addr <= 0xFFFF; addr++)
			m49_initGet8(addr);
	}
}

void m49_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m49_setParams6XXX);
	else if((addr&0xE001) == 0xA001) //regs enable/disable
		memInitMapperSetPointer(addr, mmc3addSetParamsAXX1);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m52_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!mmc3add_prgRAMenable)
		return;
	if((val&8) != 0)
	{
		mmc3_prgROMand = 0x1FFFF;
		mmc3_prgROMadd = (val&7)<<17;
	}
	else
	{
		mmc3_prgROMand = 0x3FFFF;
		mmc3_prgROMadd = (val&6)<<17;
	}
	uint8_t chrVal = ((val>>4)&3) | (val&4);
	if((val&0x40) != 0)
	{
		mmc3_chrROMand = 0x1FFFF;
		mmc3SetChrROMadd((chrVal&7)<<17);
	}
	else
	{
		mmc3_chrROMand = 0x3FFFF;
		mmc3SetChrROMadd((chrVal&6)<<17);
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = ((val&0x80) != 0);
	if(mmc3add_regLock)
	{
		//this will allow ram writes
		//printf("allowing prg ram\n");
		uint16_t ramaddr;
		for(ramaddr = 0x6000; ramaddr < 0x8000; ramaddr++)
			m52_initSet8(ramaddr);
	}
}

void m52_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000 && !mmc3add_regLock)
		memInitMapperSetPointer(addr, m52_setParams6XXX);
	else if((addr&0xE001) == 0xA001) //regs enable/disable
		memInitMapperSetPointer(addr, mmc3addSetParamsAXX1);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

void m205_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	val &= 3;
	if(val == 0)
	{
		mmc3_prgROMadd = 0;
		mmc3_prgROMand = 0x3FFFF;
		mmc3SetChrROMadd(0);
		mmc3_chrROMand = 0x3FFFF;
	}
	else if(val == 1)
	{
		mmc3_prgROMadd = 0x20000;
		mmc3_prgROMand = 0x3FFFF;
		mmc3SetChrROMadd(0x20000);
		mmc3_chrROMand = 0x3FFFF;
	}
	else if(val == 2)
	{
		mmc3_prgROMadd = 0x40000;
		mmc3_prgROMand = 0x1FFFF;
		mmc3SetChrROMadd(0x40000);
		mmc3_chrROMand = 0x1FFFF;
	}
	else //val == 3
	{
		mmc3_prgROMadd = 0x60000;
		mmc3_prgROMand = 0x1FFFF;
		mmc3SetChrROMadd(0x60000);
		mmc3_chrROMand = 0x1FFFF;
	}
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
}
void m205_initSet8(uint16_t addr)
{
	//special select regs
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m205_setParams6XXX);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

void m37_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0xFFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x1FFFF;
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
}

void m44_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x1FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x1FFFF;
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
}

void m45_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x7FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	m45_chrROMandVal = 0;
	m45_setChrROMand();
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
	//make sure to unlock reg writes of course
	//printf("allowing reg writes\n");
	uint16_t regaddr;
	for(regaddr = 0x6000; regaddr < 0x8000; regaddr++)
		m45_initSet8(regaddr);
	m45_curReg = 0;
}

void m47_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x1FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x1FFFF;
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
}

void m49_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x1FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x1FFFF;
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
	//for prgmode 0
	m49_prgreg = 0;
	prg32setBank0((m49_prgreg<<15)|mmc3_prgROMadd);
	//reset how prg rom is read
	m49_prgmode = 0;
	//printf("Switched to prg mode 0\n");
	uint32_t addr;
	for(addr = 0x8000; addr <= 0xFFFF; addr++)
		m49_initGet8(addr);
}

void m52_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x3FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x3FFFF;
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
	mmc3add_prgRAMenable = false;
	//make sure to unlock reg writes of course
	//printf("allowing reg writes\n");
	uint16_t regaddr;
	for(regaddr = 0x6000; regaddr < 0x8000; regaddr++)
		m52_initSet8(regaddr);
}

void m205_reset()
{
	mmc3_prgROMadd = 0;
	mmc3_prgROMand = 0x3FFFF;
	mmc3SetChrROMadd(0);
	mmc3_chrROMand = 0x3FFFF;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMBankPtr();
	mmc3add_regLock = false;
}
