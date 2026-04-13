/*
 * Copyright (C) 2017 - 2019 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	bool usesPrgRAM;
	uint8_t *chrROM;
	uint32_t chrROMaddFull;
	uint32_t chrROMadd0XXX;
	uint32_t chrROMadd1XXX;
	uint32_t chrROMandFull;
	uint8_t chrRAM[0x2000];
	uint32_t curPRGBank0;
	uint32_t curPRGBank1;
	uint32_t lastM1PRGBank;
	uint32_t lastPRGBank;
	uint32_t CHRBank[8];
	uint8_t *chrROMBank0Ptr, *chrROMBank1Ptr,
			*chrROMBank2Ptr, *chrROMBank3Ptr,
			*chrROMBank4Ptr, *chrROMBank5Ptr,
			*chrROMBank6Ptr, *chrROMBank7Ptr;
	uint8_t writeAddr;
	uint8_t chr_bank_flip;
	bool prg_bank_flip;
	uint8_t irqCtr;
	bool irqEnable;
	bool altirq;
	bool clear;
	uint8_t irqReloadVal;
	uint16_t prevAddr;
} mmc3;
//used externally
uint32_t mmc3_prgROMadd;
uint32_t mmc3_prgROMand;
uint32_t mmc3_chrROMand;

void mmc3SetPrgROMBankPtr()
{
	if(mmc3.prg_bank_flip)
	{
		prg8setBank0((mmc3.lastM1PRGBank&mmc3_prgROMand)|mmc3_prgROMadd);
		prg8setBank2((mmc3.curPRGBank0&mmc3_prgROMand)|mmc3_prgROMadd);
	}
	else
	{
		prg8setBank0((mmc3.curPRGBank0&mmc3_prgROMand)|mmc3_prgROMadd);
		prg8setBank2((mmc3.lastM1PRGBank&mmc3_prgROMand)|mmc3_prgROMadd);
	}
	prg8setBank1((mmc3.curPRGBank1&mmc3_prgROMand)|mmc3_prgROMadd);
	prg8setBank3((mmc3.lastPRGBank&mmc3_prgROMand)|mmc3_prgROMadd);
}

void mmc3SetChrROMBankPtr()
{
	mmc3.chrROMBank0Ptr = mmc3.chrROM+(((mmc3.CHRBank[0^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd0XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank1Ptr = mmc3.chrROM+(((mmc3.CHRBank[1^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd0XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank2Ptr = mmc3.chrROM+(((mmc3.CHRBank[2^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd0XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank3Ptr = mmc3.chrROM+(((mmc3.CHRBank[3^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd0XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank4Ptr = mmc3.chrROM+(((mmc3.CHRBank[4^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd1XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank5Ptr = mmc3.chrROM+(((mmc3.CHRBank[5^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd1XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank6Ptr = mmc3.chrROM+(((mmc3.CHRBank[6^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd1XXX)&mmc3.chrROMandFull);
	mmc3.chrROMBank7Ptr = mmc3.chrROM+(((mmc3.CHRBank[7^mmc3.chr_bank_flip]&mmc3_chrROMand)|mmc3.chrROMadd1XXX)&mmc3.chrROMandFull);
}

static void mmc3SetChrROMadd0XXX(uint32_t val)
{
	mmc3.chrROMadd0XXX = val;
}

static void mmc3SetChrROMadd1XXX(uint32_t val)
{
	mmc3.chrROMadd1XXX = val;
}

void mmc3SetChrROMadd(uint32_t val)
{
	mmc3.chrROMaddFull = val;
	mmc3SetChrROMadd0XXX(val);
	mmc3SetChrROMadd1XXX(val);
}

uint32_t mmc3GetChrROMadd()
{
	return mmc3.chrROMaddFull;
}

void mmc3init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		mmc3.usesPrgRAM = true;
	}
	else
		mmc3.usesPrgRAM = false;
	mmc3_prgROMand = mapperGetAndValue(prgROMsizeIn);
	mmc3.curPRGBank0 = 0;
	mmc3.curPRGBank1 = 0x2000;
	mmc3.lastPRGBank = (prgROMsizeIn - 0x2000);
	mmc3.lastM1PRGBank = mmc3.lastPRGBank - 0x2000;
	if(chrROMin && chrROMsizeIn)
	{
		mmc3.chrROM = chrROMin;
		mmc3_chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
	{
		mmc3.chrROM = mmc3.chrRAM;
		mmc3_chrROMand = 0x1FFF;
	}
	//save initial and value
	mmc3.chrROMandFull = mmc3_chrROMand;
	memset(mmc3.chrRAM,0,0x2000);
	memset(mmc3.CHRBank,0,8*sizeof(uint32_t));
	//bank 1 and 3 start out being the upper one
	mmc3.CHRBank[1] = (1<<10);
	mmc3.CHRBank[3] = (1<<10);
	mmc3.irqCtr = 0;
	mmc3.writeAddr = 0;
	mmc3.irqEnable = false;
	//can enable MMC3A IRQ behaviour
	mmc3.altirq = false;
	mmc3.clear = false;
	mmc3.irqReloadVal = 0xFF;
	mmc3.chr_bank_flip = 0;
	mmc3.prg_bank_flip = false;
	mmc3.prevAddr = 0;
	mmc3_prgROMadd = 0;
	mmc3SetPrgROMBankPtr();
	mmc3SetChrROMadd(0);
	mmc3SetChrROMBankPtr();
	printf("MMC3 inited\n");
}

void m12init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	mmc3.altirq = true; //needs to be MMC3A
	mmc3_chrROMand = 0x3FFFF; //forced CHR size
	mmc3SetChrROMadd0XXX(0);
	mmc3SetChrROMadd1XXX(0);
	mmc3SetChrROMBankPtr();
	printf("Mapper 12 (Pirate Mapper 4) inited\n");
}

static uint16_t m118nt[6];
static void m118refreshNT()
{
	//refresh ppu nametable values
	if(mmc3.chr_bank_flip) //upper bits used for low ppu
		ppuSetNameTblCustom(m118nt[2],m118nt[3],m118nt[4],m118nt[5]);
	else //lower bits used for low ppu
		ppuSetNameTblCustom(m118nt[0],m118nt[0],m118nt[1],m118nt[1]);
}
void m118init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	memset(m118nt,0,6*sizeof(uint16_t));
	m118refreshNT();
	printf("Mapper 118 (Mapper 4 Variant) inited\n");
}

static uint8_t m119_chrRAM[0x2000];
static bool m119_chrIsRAM[8];
void m119SetChrRAMBankPtr()
{
	m119_chrIsRAM[0] = mmc3.CHRBank[0^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[0]) mmc3.chrROMBank0Ptr = m119_chrRAM+(mmc3.CHRBank[0^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[1] = mmc3.CHRBank[1^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[1]) mmc3.chrROMBank1Ptr = m119_chrRAM+(mmc3.CHRBank[1^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[2] = mmc3.CHRBank[2^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[2]) mmc3.chrROMBank2Ptr = m119_chrRAM+(mmc3.CHRBank[2^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[3] = mmc3.CHRBank[3^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[3]) mmc3.chrROMBank3Ptr = m119_chrRAM+(mmc3.CHRBank[3^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[4] = mmc3.CHRBank[4^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[4]) mmc3.chrROMBank4Ptr = m119_chrRAM+(mmc3.CHRBank[4^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[5] = mmc3.CHRBank[5^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[5]) mmc3.chrROMBank5Ptr = m119_chrRAM+(mmc3.CHRBank[5^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[6] = mmc3.CHRBank[6^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[6]) mmc3.chrROMBank6Ptr = m119_chrRAM+(mmc3.CHRBank[6^mmc3.chr_bank_flip]&0x1FFF);
	m119_chrIsRAM[7] = mmc3.CHRBank[7^mmc3.chr_bank_flip]&0x10000;
	if(m119_chrIsRAM[7]) mmc3.chrROMBank7Ptr = m119_chrRAM+(mmc3.CHRBank[7^mmc3.chr_bank_flip]&0x1FFF);
}
void m119init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc3init(prgROMin, prgROMsizeIn, prgRAMin, prgRAMsizeIn, chrROMin, chrROMsizeIn);
	memset(m119_chrRAM,0,0x2000);
	m119SetChrRAMBankPtr();
	printf("Mapper 119 (Mapper 4 Variant) inited\n");
}

void mmc3initGet8(uint16_t addr)
{
	if(mmc3.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg8initGet8(addr);
}

void mmc3setParams8000(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc3.chr_bank_flip = ((val&(1<<7)) != 0) ? 4 : 0;
	mmc3SetChrROMBankPtr();
	mmc3.prg_bank_flip = ((val&(1<<6)) != 0);
	mmc3SetPrgROMBankPtr();
	mmc3.writeAddr = (val&7);
}
void mmc3setParams8001(uint16_t addr, uint8_t val)
{
	(void)addr;
	switch(mmc3.writeAddr)
	{
		case 0:
			mmc3.CHRBank[0] = ((val&0xFE)<<10);
			mmc3.CHRBank[1] = ((val|0x01)<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 1:
			mmc3.CHRBank[2] = ((val&0xFE)<<10);
			mmc3.CHRBank[3] = ((val|0x01)<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 2:
			mmc3.CHRBank[4] = (val<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 3:
			mmc3.CHRBank[5] = (val<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 4:
			mmc3.CHRBank[6] = (val<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 5:
			mmc3.CHRBank[7] = (val<<10);
			mmc3SetChrROMBankPtr();
			break;
		case 6:
			mmc3.curPRGBank0 = (val<<13);
			mmc3SetPrgROMBankPtr();
			break;
		case 7:
			mmc3.curPRGBank1 = (val<<13);
			mmc3SetPrgROMBankPtr();
			break;
	}
}
void mmc3setParamsA000(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!ppu4Screen)
	{
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
}
void mmc3setParamsC000(uint16_t addr, uint8_t val)
{
	(void)addr;
	//printf("Reload value set to %i\n", val);
	mmc3.irqReloadVal = val;
	if(mmc3.altirq)
		mmc3.clear = true;
}
void mmc3setParamsC001(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	//printf("Reset counter\n");
	mmc3.irqCtr = 0;
}
extern uint8_t interrupt;
void mmc3setParamsE000(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	mmc3.irqEnable = false;
	interrupt &= ~MAPPER_IRQ;
	//printf("Interrupt disabled\n");
}
void mmc3setParamsE001(uint16_t addr, uint8_t val)
{
	(void)addr;
	(void)val;
	mmc3.irqEnable = true;
	//printf("Interrupt enabled\n");
}

void mmc3initSet8(uint16_t ori_addr)
{
	if(mmc3.usesPrgRAM)
		prgRAM8initSet8(ori_addr);
	uint16_t proc_addr = ori_addr&0xE001;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, mmc3setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, mmc3setParams8001);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, mmc3setParamsA000);
	//  mmc3setParamsAXX1 would be ram protect which I dont do atm
	else if(proc_addr == 0xC000) memInitMapperSetPointer(ori_addr, mmc3setParamsC000);
	else if(proc_addr == 0xC001) memInitMapperSetPointer(ori_addr, mmc3setParamsC001);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, mmc3setParamsE000);
	else if(proc_addr == 0xE001) memInitMapperSetPointer(ori_addr, mmc3setParamsE001);
}

void m12setParams4XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc3SetChrROMadd0XXX((val&0x01)?0x40000:0);
	mmc3SetChrROMadd1XXX((val&0x10)?0x40000:0);
	mmc3SetChrROMBankPtr();
}

void m12initSet8(uint16_t addr)
{
	//special pirate regs
	if(addr >= 0x4020 && addr < 0x6000)
		memInitMapperSetPointer(addr, m12setParams4XXX);
	else //do normal mmc3 sets
		mmc3initSet8(addr);
}

static void m118setParams8000(uint16_t addr, uint8_t val)
{
	//call original function
	mmc3setParams8000(addr, val);
	//update nametable vals for possible bank flip
	m118refreshNT();
}
static void m118setParams8001(uint16_t addr, uint8_t val)
{
	if(mmc3.writeAddr <= 5) //chr bank sets
	{
		//call original function without upper bit
		mmc3setParams8001(addr, val&0x7F);
		//update nametable vals for new nt bit write
		m118nt[mmc3.writeAddr] = (val&0x80)?0x400:0;
		m118refreshNT();
	}
	else //prg bank sets, call original function normally
		mmc3setParams8001(addr, val);
}
void m118initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	//special nametable regs
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m118setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m118setParams8001);
	else if(proc_addr == 0xA000) return; //Bypass standard mirroring controls
	else //do normal mmc3 sets
		mmc3initSet8(ori_addr);
}

static void m119setParams8000(uint16_t addr, uint8_t val)
{
	//call original function
	mmc3setParams8000(addr, val);
	//update chr ram pointers for possible bank flip
	m119SetChrRAMBankPtr();
}
static void m119setParams8001(uint16_t addr, uint8_t val)
{
	//call original function
	mmc3setParams8001(addr, val);
	if(mmc3.writeAddr <= 5) //chr bank sets
	{
		//update chr ram pointers for new banks
		m119SetChrRAMBankPtr();
	}
}
void m119initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE001;
	//special chr ram pointers
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m119setParams8000);
	else if(proc_addr == 0x8001) memInitMapperSetPointer(ori_addr, m119setParams8001);
	else //do normal mmc3 sets
		mmc3initSet8(ori_addr);
}

static void m224setParams5XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	mmc3_prgROMadd = (val&4)<<17;
	mmc3SetPrgROMBankPtr();
}
void m224initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xF003;
	//special pirate regs
	if(proc_addr == 0x5000) memInitMapperSetPointer(ori_addr, m224setParams5XXX);
	else //do normal mmc3 sets
		mmc3initSet8(ori_addr);
}

extern void ppuPrintCurLineDot();
void mmc3clock(uint16_t addr)
{
	if((addr & 0x1000) && !(mmc3.prevAddr & 0x1000))
	{
		//printf("MMC3 Beep at "); ppuPrintCurLineDot();
		uint8_t oldCtr = mmc3.irqCtr;
		if(mmc3.irqCtr == 0 || mmc3.clear)
			mmc3.irqCtr = mmc3.irqReloadVal;
		else
			mmc3.irqCtr--;
		if((!mmc3.altirq || oldCtr != 0 || mmc3.clear) && mmc3.irqCtr == 0 && mmc3.irqEnable)
		{
			//printf("MMC3 Tick at "); ppuPrintCurLineDot();
			interrupt |= MAPPER_IRQ;
			mmc3.irqEnable = false;
		}
		mmc3.clear = false;
	}
	mmc3.prevAddr = addr;
}
/*
uint8_t m119chrGet8(uint16_t addr)
{
	mmc3clock(addr);
	//check for RAM first
	if(mmc3_CHRBank[(addr>>10)^mmc3_chr_bank_flip]&0x10000)
		return mmc3_chrRAM[(mmc3_CHRBank[(addr>>10)^mmc3_chr_bank_flip]|(addr&0x3FF))&0x1FFF];
	return mmc3_chrROM[((mmc3_CHRBank[(addr>>10)^mmc3_chr_bank_flip]|(addr&0x3FF))&mmc3_chrROMand)|mmc3_chrROMadd];
}

void m119chrSet8(uint16_t addr, uint8_t val)
{
	mmc3clock(addr);
	//printf("m119chrSet8 %04x %02x\n", addr, val);
	if(mmc3_CHRBank[(addr>>10)^mmc3_chr_bank_flip]&0x10000)
		mmc3_chrRAM[(mmc3_CHRBank[(addr>>10)^mmc3_chr_bank_flip]|(addr&0x3FF))&0x1FFF] = val;
}
*/
static void mmc3chrSetRAM0(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank0Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM1(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank1Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM2(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank2Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM3(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank3Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM4(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank4Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM5(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank5Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM6(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank6Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void mmc3chrSetRAM7(uint16_t addr, uint8_t val)
{	//remember, mmc3.chrROM = mmc3.chrRAM
	mmc3.chrROMBank7Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}

static void mmc3chrSetClock(uint16_t addr, uint8_t val)
{
	(void)val;
	mmc3clock(addr);
}

static uint8_t mmc3chrGetROM0(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank0Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM1(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank1Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM2(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank2Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM3(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank3Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM4(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank4Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM5(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank5Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM6(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank6Ptr[addr&0x3FF];
}
static uint8_t mmc3chrGetROM7(uint16_t addr)
{
	mmc3clock(addr);
	return mmc3.chrROMBank7Ptr[addr&0x3FF];
}

void mmc3initPPUGet8(uint16_t addr)
{
	if(addr >= 0x2000)
		return;
	if(addr < 0x400) memInitMapperPPUGetPointer(addr, mmc3chrGetROM0);
	else if(addr < 0x800) memInitMapperPPUGetPointer(addr, mmc3chrGetROM1);
	else if(addr < 0xC00) memInitMapperPPUGetPointer(addr, mmc3chrGetROM2);
	else if(addr < 0x1000) memInitMapperPPUGetPointer(addr, mmc3chrGetROM3);
	else if(addr < 0x1400) memInitMapperPPUGetPointer(addr, mmc3chrGetROM4);
	else if(addr < 0x1800) memInitMapperPPUGetPointer(addr, mmc3chrGetROM5);
	else if(addr < 0x1C00) memInitMapperPPUGetPointer(addr, mmc3chrGetROM6);
	else if(addr < 0x2000) memInitMapperPPUGetPointer(addr, mmc3chrGetROM7);
}

void mmc3initPPUSet8(uint16_t addr)
{
	if(addr >= 0x2000)
		return;
	if(mmc3.chrROM == mmc3.chrRAM) //Writable
	{
		if(addr < 0x400) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM0);
		else if(addr < 0x800) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM1);
		else if(addr < 0xC00) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM2);
		else if(addr < 0x1000) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM3);
		else if(addr < 0x1400) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM4);
		else if(addr < 0x1800) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM5);
		else if(addr < 0x1C00) memInitMapperPPUSetPointer(addr, mmc3chrSetRAM6);
		else memInitMapperPPUSetPointer(addr, mmc3chrSetRAM7);
	}
	else
		memInitMapperPPUSetPointer(addr, mmc3chrSetClock);
}

static void m119chrSetRAM0(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[0]) mmc3.chrROMBank0Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM1(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[1]) mmc3.chrROMBank1Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM2(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[2]) mmc3.chrROMBank2Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM3(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[3]) mmc3.chrROMBank3Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM4(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[4]) mmc3.chrROMBank4Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM5(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[5]) mmc3.chrROMBank5Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM6(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[6]) mmc3.chrROMBank6Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}
static void m119chrSetRAM7(uint16_t addr, uint8_t val)
{
	if(m119_chrIsRAM[7]) mmc3.chrROMBank7Ptr[addr&0x3FF] = val;
	mmc3clock(addr);
}

void m119initPPUSet8(uint16_t addr)
{
	if(addr >= 0x2000)
		return;
	if(addr < 0x400) memInitMapperPPUSetPointer(addr, m119chrSetRAM0);
	else if(addr < 0x800) memInitMapperPPUSetPointer(addr, m119chrSetRAM1);
	else if(addr < 0xC00) memInitMapperPPUSetPointer(addr, m119chrSetRAM2);
	else if(addr < 0x1000) memInitMapperPPUSetPointer(addr, m119chrSetRAM3);
	else if(addr < 0x1400) memInitMapperPPUSetPointer(addr, m119chrSetRAM4);
	else if(addr < 0x1800) memInitMapperPPUSetPointer(addr, m119chrSetRAM5);
	else if(addr < 0x1C00) memInitMapperPPUSetPointer(addr, m119chrSetRAM6);
	else memInitMapperPPUSetPointer(addr, m119chrSetRAM7);
}
