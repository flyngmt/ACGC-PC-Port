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
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../audio_mmc5.h"

static struct {
	uint8_t *prgROM;
	uint8_t *prgRAM;
	uint8_t *prgRAMBank6XXXPtr;
	uint8_t *chrROM;
	uint8_t *chrROMPtrLower[8];
	uint8_t *chrROMPtrUpper[8];
	uint8_t *prgBank0Ptr, *prgBank1Ptr,
			*prgBank2Ptr, *prgBank3Ptr;
	uint8_t prgBank0PtrType, prgBank1PtrType,
			prgBank2PtrType;
	uint32_t prgROMsize;
	uint32_t prgRAMsize;
	uint32_t chrROMsize;
	uint8_t chrRAM[0x2000];
	uint8_t VRAM[0x800];
	uint8_t exRAM[0x400];
	uint32_t PRGRAMBank6XXX;
	uint32_t PRGBank[4];
	uint8_t PRGBankType[3];
	uint32_t CHRBank[12];
	uint32_t upperCHRBank;
	uint8_t vramBankMode[4];
	uint8_t prg_bank_mode;
	uint8_t chr_bank_mode;
	uint8_t irqCtr;
	uint8_t irqVal;
	uint8_t fillTile;
	uint8_t fillAttr;
	bool irqEnable;
	bool irqPending;
	bool chrSet;
	bool split;
	bool splitAllow;
	bool splitInitEnable;
	bool splitEnable;
	uint8_t splitTile;
	uint8_t splitBank;
	uint8_t DrawnXTile;
	uint8_t exMode;
	uint8_t mode1Bank;
	uint8_t mode1Attrib;
	uint8_t mulA, mulB;
	uint16_t mulRes;
	uint32_t prgROMand;
	uint32_t prgRAMand;
	uint32_t chrROMand;
	uint32_t PRGRAMBank6XXXadd;
	uint32_t prgRAMadd[4];
} mmc5;

static void mmc5SetChrBankPtrLower()
{
	uint32_t tmp;
	switch(mmc5.chr_bank_mode)
	{
		case 0: //8kb bank
			tmp = (mmc5.CHRBank[7]<<13)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[1] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrLower[2] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrLower[3] = mmc5.chrROM+(tmp|0x0C00);
			mmc5.chrROMPtrLower[4] = mmc5.chrROM+(tmp|0x1000); mmc5.chrROMPtrLower[5] = mmc5.chrROM+(tmp|0x1400);
			mmc5.chrROMPtrLower[6] = mmc5.chrROM+(tmp|0x1800); mmc5.chrROMPtrLower[7] = mmc5.chrROM+(tmp|0x1C00);
			break;
		case 1: //4kb banks
			tmp = (mmc5.CHRBank[3]<<12)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[1] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrLower[2] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrLower[3] = mmc5.chrROM+(tmp|0x0C00);
			tmp = (mmc5.CHRBank[7]<<12)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[4] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[5] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrLower[6] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrLower[7] = mmc5.chrROM+(tmp|0x0C00);
			break;
		case 2: //2kb banks
			tmp = (mmc5.CHRBank[1]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[1] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[3]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[2] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[3] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[5]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[4] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[5] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[7]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrLower[6] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrLower[7] = mmc5.chrROM+(tmp|0x0400);
			break;
		case 3: //1kb banks
			mmc5.chrROMPtrLower[0] = mmc5.chrROM+((mmc5.CHRBank[0]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[1] = mmc5.chrROM+((mmc5.CHRBank[1]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[2] = mmc5.chrROM+((mmc5.CHRBank[2]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[3] = mmc5.chrROM+((mmc5.CHRBank[3]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[4] = mmc5.chrROM+((mmc5.CHRBank[4]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[5] = mmc5.chrROM+((mmc5.CHRBank[5]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[6] = mmc5.chrROM+((mmc5.CHRBank[6]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrLower[7] = mmc5.chrROM+((mmc5.CHRBank[7]<<10)&mmc5.chrROMand);
			break;
		default:
			break;
	}
}

static void mmc5SetChrBankPtrUpper()
{
	uint32_t tmp;
	switch(mmc5.chr_bank_mode)
	{
		case 0: //8kb bank
			tmp = (mmc5.CHRBank[0xB]<<13)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[1] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrUpper[2] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrUpper[3] = mmc5.chrROM+(tmp|0x0C00);
			mmc5.chrROMPtrUpper[4] = mmc5.chrROM+(tmp|0x1000); mmc5.chrROMPtrUpper[5] = mmc5.chrROM+(tmp|0x1400);
			mmc5.chrROMPtrUpper[6] = mmc5.chrROM+(tmp|0x1800); mmc5.chrROMPtrUpper[7] = mmc5.chrROM+(tmp|0x1C00);
			break;
		case 1: //4kb banks
			tmp = (mmc5.CHRBank[0xB]<<12)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[1] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrUpper[2] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrUpper[3] = mmc5.chrROM+(tmp|0x0C00);
			//0xB used for both 4kb banks here
			mmc5.chrROMPtrUpper[4] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[5] = mmc5.chrROM+(tmp|0x0400);
			mmc5.chrROMPtrUpper[6] = mmc5.chrROM+(tmp|0x0800); mmc5.chrROMPtrUpper[7] = mmc5.chrROM+(tmp|0x0C00);
			break;
		case 2: //2kb banks
			tmp = (mmc5.CHRBank[0x9]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[0] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[1] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[0xB]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[2] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[3] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[0x9]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[4] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[5] = mmc5.chrROM+(tmp|0x0400);
			tmp = (mmc5.CHRBank[0xB]<<11)&mmc5.chrROMand;
			mmc5.chrROMPtrUpper[6] = mmc5.chrROM+(tmp|0x0000); mmc5.chrROMPtrUpper[7] = mmc5.chrROM+(tmp|0x0400);
			break;
		case 3: //1kb banks
			mmc5.chrROMPtrUpper[0] = mmc5.chrROM+((mmc5.CHRBank[0x8]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[1] = mmc5.chrROM+((mmc5.CHRBank[0x9]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[2] = mmc5.chrROM+((mmc5.CHRBank[0xA]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[3] = mmc5.chrROM+((mmc5.CHRBank[0xB]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[4] = mmc5.chrROM+((mmc5.CHRBank[0x8]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[5] = mmc5.chrROM+((mmc5.CHRBank[0x9]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[6] = mmc5.chrROM+((mmc5.CHRBank[0xA]<<10)&mmc5.chrROMand);
			mmc5.chrROMPtrUpper[7] = mmc5.chrROM+((mmc5.CHRBank[0xB]<<10)&mmc5.chrROMand);
			break;
		default:
			break;
	}
}

//6000-7FFF
static void mmc5SetPrgRAMBank6XXXPtr()
{
	mmc5.prgRAMBank6XXXPtr = mmc5.prgRAM+(((mmc5.PRGRAMBank6XXX<<13)&mmc5.prgRAMand)|mmc5.PRGRAMBank6XXXadd);
}
//8000-FFFF
static void mmc5SetPrgBankPtr()
{
	uint32_t tmp;
	switch(mmc5.prg_bank_mode)
	{
		case 0:
			//no RAM
			tmp = ((mmc5.PRGBank[3]&~3)<<13)&mmc5.prgROMand;
			mmc5.prgBank0Ptr = mmc5.prgROM+(tmp|0x0000), mmc5.prgBank1Ptr = mmc5.prgROM+(tmp|0x2000),
			mmc5.prgBank2Ptr = mmc5.prgROM+(tmp|0x4000), mmc5.prgBank3Ptr = mmc5.prgROM+(tmp|0x6000);
			mmc5.prgBank0PtrType = 1, mmc5.prgBank1PtrType = 1,	
			mmc5.prgBank2PtrType = 1; //no prgBank3PtrType, always ROM
			break;
		case 1:
			//8000-BFFF
			if(mmc5.PRGBankType[1] == 1) //ROM
			{
				tmp = ((mmc5.PRGBank[1]&~1)<<13)&mmc5.prgROMand;
				mmc5.prgBank0Ptr = mmc5.prgROM+(tmp|0x0000), mmc5.prgBank1Ptr = mmc5.prgROM+(tmp|0x2000);
				mmc5.prgBank0PtrType = 1, mmc5.prgBank1PtrType = 1;
			}
			else //RAM
			{
				tmp = (((mmc5.PRGBank[1]&~1)<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[1];
				mmc5.prgBank0Ptr = mmc5.prgRAM+(tmp|0x0000), mmc5.prgBank1Ptr = mmc5.prgRAM+(tmp|0x2000);
				mmc5.prgBank0PtrType = 0, mmc5.prgBank1PtrType = 0;
			}
			//C000-FFFF, no RAM
			tmp = ((mmc5.PRGBank[3]&~1)<<13)&mmc5.prgROMand;
			mmc5.prgBank2Ptr = mmc5.prgROM+(tmp|0x0000), mmc5.prgBank3Ptr = mmc5.prgROM+(tmp|0x2000);
			mmc5.prgBank2PtrType = 1; //no prgBank3PtrType, always ROM
			break;
		case 2:
			//8000-BFFF
			if(mmc5.PRGBankType[1] == 1) //ROM
			{
				tmp = ((mmc5.PRGBank[1]&~1)<<13)&mmc5.prgROMand;
				mmc5.prgBank0Ptr = mmc5.prgROM+(tmp|0x0000), mmc5.prgBank1Ptr = mmc5.prgROM+(tmp|0x2000);
				mmc5.prgBank0PtrType = 1, mmc5.prgBank1PtrType = 1;
			}
			else //RAM
			{
				tmp = (((mmc5.PRGBank[1]&~1)<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[1];
				mmc5.prgBank0Ptr = mmc5.prgRAM+(tmp|0x0000), mmc5.prgBank1Ptr = mmc5.prgRAM+(tmp|0x2000);
				mmc5.prgBank0PtrType = 0, mmc5.prgBank1PtrType = 0;
			}
			//C000-DFFF
			if(mmc5.PRGBankType[2] == 1) //ROM
			{
				tmp = (mmc5.PRGBank[2]<<13)&mmc5.prgROMand;
				mmc5.prgBank2Ptr = mmc5.prgROM+(tmp|0x0000);
				mmc5.prgBank2PtrType = 1;
			}
			else //RAM
			{
				tmp = ((mmc5.PRGBank[2]<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[2];
				mmc5.prgBank2Ptr = mmc5.prgRAM+(tmp|0x0000);
				mmc5.prgBank2PtrType = 0;
			}
			//E000-FFFF, no RAM
			tmp = (mmc5.PRGBank[3]<<13)&mmc5.prgROMand;
			mmc5.prgBank3Ptr = mmc5.prgROM+(tmp|0x0000);
			//no prgBank3PtrType, always ROM
			break;
		case 3:
			//8000-9FFF
			if(mmc5.PRGBankType[0] == 1) //ROM
			{
				tmp = (mmc5.PRGBank[0]<<13)&mmc5.prgROMand;
				mmc5.prgBank0Ptr = mmc5.prgROM+(tmp|0x0000);
				mmc5.prgBank0PtrType = 1;
			}
			else //RAM
			{
				tmp = ((mmc5.PRGBank[0]<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[0];
				mmc5.prgBank0Ptr = mmc5.prgRAM+(tmp|0x0000);
				mmc5.prgBank0PtrType = 0;
			}
			//A000-BFFF
			if(mmc5.PRGBankType[1] == 1) //ROM
			{
				tmp = (mmc5.PRGBank[1]<<13)&mmc5.prgROMand;
				mmc5.prgBank1Ptr = mmc5.prgROM+(tmp|0x0000);
				mmc5.prgBank1PtrType = 1;
			}
			else //RAM
			{
				tmp = ((mmc5.PRGBank[1]<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[1];
				mmc5.prgBank1Ptr = mmc5.prgRAM+(tmp|0x0000);
				mmc5.prgBank1PtrType = 0;
			}
			//C000-DFFF
			if(mmc5.PRGBankType[2] == 1) //ROM
			{
				tmp = (mmc5.PRGBank[2]<<13)&mmc5.prgROMand;
				mmc5.prgBank2Ptr = mmc5.prgROM+(tmp|0x0000);
				mmc5.prgBank2PtrType = 1;
			}
			else //RAM
			{
				tmp = ((mmc5.PRGBank[2]<<13)&mmc5.prgRAMand)|mmc5.prgRAMadd[2];
				mmc5.prgBank2Ptr = mmc5.prgRAM+(tmp|0x0000);
				mmc5.prgBank2PtrType = 0;
			}
			//E000-FFFF, no RAM
			tmp = (mmc5.PRGBank[3]<<13)&mmc5.prgROMand;
			mmc5.prgBank3Ptr = mmc5.prgROM+(tmp|0x0000);
			//no prgBank3PtrType, always ROM
			break;
		default:
			break;
	}
}

extern uint8_t interrupt;
void mmc5init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	mmc5.prgROM = prgROMin;
	mmc5.prgROMsize = prgROMsizeIn;
	mmc5.prgRAM = prgRAMin;
	mmc5.prgRAMsize = prgRAMsizeIn;
	mmc5.prgROMand = mapperGetAndValue(prgROMsizeIn);
	mmc5.prgRAMand = mapperGetAndValue(prgRAMsizeIn);
	if(chrROMsizeIn > 0)
	{
		mmc5.chrROM = chrROMin;
		mmc5.chrROMsize = chrROMsizeIn;
		mmc5.chrROMand = mapperGetAndValue(chrROMsizeIn);
	}
	else
	{
		mmc5.chrROM = mmc5.chrRAM;
		mmc5.chrROMsize = 0x2000;
		mmc5.chrROMand = 0x1FFF;
	}
	memset(mmc5.PRGBank,0,3*sizeof(uint32_t));
	mmc5.PRGBank[3] = 0xFF;
	memset(mmc5.PRGBankType,0,3*sizeof(uint8_t));
	memset(mmc5.chrRAM,0,0x2000);
	memset(mmc5.VRAM,0,0x800);
	memset(mmc5.exRAM,0,0x400);
	memset(mmc5.vramBankMode,0,4);
	memset(mmc5.CHRBank,0,12*sizeof(uint32_t));
	mmc5.upperCHRBank = 0;
	mmc5.irqCtr = 0;
	mmc5.irqEnable = false;
	mmc5.irqPending = false;
	mmc5.chrSet = false;
	mmc5.split = false;
	mmc5.splitAllow = false;
	mmc5.splitInitEnable = false;
	mmc5.splitEnable = false;
	mmc5.splitTile = 0;
	mmc5.splitBank = 0;
	mmc5.DrawnXTile = 0;
	mmc5.exMode = 0;
	mmc5.irqVal = 0;
	mmc5.fillTile = 0;
	mmc5.fillAttr = 0;
	mmc5.prg_bank_mode = 3;
	mmc5.chr_bank_mode = 3;
	mmc5SetChrBankPtrLower();
	mmc5SetChrBankPtrUpper();
	mmc5.mode1Bank = 0;
	mmc5.mode1Attrib = 0;
	mmc5.mulA = 0, mmc5.mulB = 0;
	mmc5.mulRes = 0;
	mmc5.PRGRAMBank6XXX = 0;
	mmc5.PRGRAMBank6XXXadd = 0;
	mmc5SetPrgRAMBank6XXXPtr();
	memset(mmc5.prgRAMadd,0,4*sizeof(uint32_t));
	mmc5SetPrgBankPtr();
	mmc5AudioInit();
	printf("MMC5 inited\n");
}

extern bool ppuInFrame;
extern bool ppu816Sprite;

static uint8_t mmc5getParams5203(uint16_t addr)
{
	(void)addr;
	return mmc5.irqVal;
}
static uint8_t mmc5getParams5204(uint16_t addr)
{
	(void)addr;
	uint8_t val = (mmc5.irqPending<<7)|(ppuInFrame<<6);
	mmc5.irqPending = false;
	interrupt &= ~MAPPER_IRQ;
	//printf("%08x\n",val);
	return val;
}
static uint8_t mmc5getParams5205(uint16_t addr)
{
	(void)addr;
	return mmc5.mulRes&0xFF;
}
static uint8_t mmc5getParams5206(uint16_t addr)
{
	(void)addr;
	return mmc5.mulRes>>8;
}
extern uint8_t memLastVal;
static uint8_t mmc5getEXRAM(uint16_t addr) //5C00-5FFF
{
	if(mmc5.exMode >= 2)
		return mmc5.exRAM[addr&0x3FF];
	return memLastVal; //aka open bus
}
static uint8_t mmc5getRAMBank6XXX(uint16_t addr) //6000-7FFF
{
	return mmc5.prgRAMBank6XXXPtr[addr&0x1FFF];
}
static uint8_t mmc5getPrgBank0(uint16_t addr) //8000-9FFF
{
	uint8_t val = mmc5.prgBank0Ptr[addr&0x1FFF];
	if(mmc5_dmcreadmode) mmc5AudioPCMWrite(val); //for addr < 0xC000
	return val;
}
static uint8_t mmc5getPrgBank1(uint16_t addr) //A000-BFFF
{
	uint8_t val = mmc5.prgBank1Ptr[addr&0x1FFF];
	if(mmc5_dmcreadmode) mmc5AudioPCMWrite(val); //for addr < 0xC000
	return val;
}
static uint8_t mmc5getPrgBank2(uint16_t addr) //C000-DFFF
{
	return mmc5.prgBank2Ptr[addr&0x1FFF];
}
static uint8_t mmc5getPrgBank3(uint16_t addr) //E000-FFFF
{
	return mmc5.prgBank3Ptr[addr&0x1FFF];
}

void mmc5initGet8(uint16_t addr)
{
	if(addr >= 0x5000 && addr < 0x5016)
		memInitMapperGetPointer(addr, mmc5AudioGet8);
	else if(addr == 0x5203)
		memInitMapperGetPointer(addr, mmc5getParams5203);
	else if(addr == 0x5204)
		memInitMapperGetPointer(addr, mmc5getParams5204);
	else if(addr == 0x5205)
		memInitMapperGetPointer(addr, mmc5getParams5205);
	else if(addr == 0x5206)
		memInitMapperGetPointer(addr, mmc5getParams5206);
	else if(addr >= 0x5C00 && addr < 0x6000)
		memInitMapperGetPointer(addr, mmc5getEXRAM);
	else if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperGetPointer(addr, mmc5getRAMBank6XXX);
	else if(addr >= 0x8000)
	{
		if(addr < 0xA000)
			memInitMapperGetPointer(addr, mmc5getPrgBank0);
		else if(addr < 0xC000)
			memInitMapperGetPointer(addr, mmc5getPrgBank1);
		else if(addr < 0xE000)
			memInitMapperGetPointer(addr, mmc5getPrgBank2);
		else //addr >= 0xE000
			memInitMapperGetPointer(addr, mmc5getPrgBank3);
	}
}
static void mmc5UpdateSplitAllow()
{
	mmc5.splitAllow = (mmc5.split && mmc5.exMode < 2);
	if(!mmc5.splitAllow) mmc5.splitEnable = false;
}
static void mmc5setParams51XX(uint16_t addr, uint8_t val)
{
	//printf("mmc5set8 %04x %02x\n", addr, val);
	switch(addr&0x3F)
	{
		case 0:
			mmc5.prg_bank_mode = val&3;
			mmc5SetPrgBankPtr();
			break;
		case 1:
			mmc5.chr_bank_mode = val&3;
			mmc5SetChrBankPtrLower();
			mmc5SetChrBankPtrUpper();
			break;
		case 4:
			mmc5.exMode = val&3;
			mmc5UpdateSplitAllow();
			break;
		case 5:
			mmc5.vramBankMode[0] = (val&3);
			mmc5.vramBankMode[1] = ((val>>2)&3);
			mmc5.vramBankMode[2] = ((val>>4)&3);
			mmc5.vramBankMode[3] = ((val>>6)&3);
			break;
		case 6:
			mmc5.fillTile = val;
			break;
		case 7:
			mmc5.fillAttr = (val&3)|((val&3)<<2)|((val&3)<<4)|((val&3)<<6);
			break;
		case 0x13:
			mmc5.PRGRAMBank6XXX = val&3;
			mmc5.PRGRAMBank6XXXadd = (val&4)?0x8000:0;
			mmc5SetPrgRAMBank6XXXPtr();
			break;
		case 0x14:
			mmc5.PRGBankType[0] = (val&0x80)!=0;
			if(mmc5.PRGBankType[0] == 1) //ROM
				mmc5.PRGBank[0] = val&0x7F;
			else //RAM
			{
				mmc5.PRGBank[0] = val&3;
				mmc5.prgRAMadd[0] = (val&4)?0x8000:0;
			}
			mmc5SetPrgBankPtr();
			break;
		case 0x15:
			mmc5.PRGBankType[1] = (val&0x80)!=0;
			if(mmc5.PRGBankType[1] == 1) //ROM
				mmc5.PRGBank[1] = val&0x7F;
			else //RAM
			{
				mmc5.PRGBank[1] = val&3;
				mmc5.prgRAMadd[1] = (val&4)?0x8000:0;
			}
			mmc5SetPrgBankPtr();
			break;
		case 0x16:
			mmc5.PRGBankType[2] = (val&0x80)!=0;
			if(mmc5.PRGBankType[2] == 1) //ROM
				mmc5.PRGBank[2] = val&0x7F;
			else //RAM
			{
				mmc5.PRGBank[2] = val&3;
				mmc5.prgRAMadd[2] = (val&4)?0x8000:0;
			}
			mmc5SetPrgBankPtr();
			break;
		case 0x17:
			//always ROM
			mmc5.PRGBank[3] = val&0x7F;
			mmc5SetPrgBankPtr();
			break;
		case 0x20:
			mmc5.CHRBank[0] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x21:
			mmc5.CHRBank[1] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x22:
			mmc5.CHRBank[2] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x23:
			mmc5.CHRBank[3] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x24:
			mmc5.CHRBank[4] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x25:
			mmc5.CHRBank[5] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x26:
			mmc5.CHRBank[6] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x27:
			mmc5.CHRBank[7] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = false;
			mmc5SetChrBankPtrLower();
			break;
		case 0x28:
			mmc5.CHRBank[0x8] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = true;
			mmc5SetChrBankPtrUpper();
			break;
		case 0x29:
			mmc5.CHRBank[0x9] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = true;
			mmc5SetChrBankPtrUpper();
			break;
		case 0x2A:
			mmc5.CHRBank[0xA] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = true;
			mmc5SetChrBankPtrUpper();
			break;
		case 0x2B:
			mmc5.CHRBank[0xB] = val|(mmc5.upperCHRBank<<8);
			mmc5.chrSet = true;
			mmc5SetChrBankPtrUpper();
			break;
		case 0x30:
			mmc5.upperCHRBank = val&3;
			break;
	}
}
static void mmc5setParams52XX(uint16_t addr, uint8_t val)
{
	//printf("mmc5set8 %04x %02x\n", addr, val);
	switch(addr&7)
	{
		case 0:
			mmc5.split = (val&0x80)!=0;
			mmc5UpdateSplitAllow();
			mmc5.splitInitEnable = (val&0x40)==0;
			mmc5.splitTile = val&0x1F;
			break;
		case 1:
			//ignored for now
			break;
		case 2:
			mmc5.splitBank = val;
			break;
		case 3:
			mmc5.irqVal = val;
			break;
		case 4:
			mmc5.irqEnable = (val&0x80)!=0;
			if(mmc5.irqPending && mmc5.irqEnable)
				interrupt |= MAPPER_IRQ;
			break;
		case 5:
			mmc5.mulA = val;
			mmc5.mulRes = mmc5.mulA*mmc5.mulB;
			break;
		case 6:
			mmc5.mulB = val;
			mmc5.mulRes = mmc5.mulA*mmc5.mulB;
			break;
	}
}
static void mmc5setEXRAM(uint16_t addr, uint8_t val) //5C00-5FFF
{
	mmc5.exRAM[addr&0x3FF] = val;
}
static void mmc5setRAMBank6XXX(uint16_t addr, uint8_t val) //6000-7FFF
{
	mmc5.prgRAMBank6XXXPtr[addr&0x1FFF] = val;
}
static void mmc5setPrgBank0(uint16_t addr, uint8_t val) //8000-9FFF
{
	if(mmc5.prgBank0PtrType == 0) //RAM
		mmc5.prgBank0Ptr[addr&0x1FFF] = val;
}
static void mmc5setPrgBank1(uint16_t addr, uint8_t val) //A000-BFFF
{
	if(mmc5.prgBank1PtrType == 0) //RAM
		mmc5.prgBank1Ptr[addr&0x1FFF] = val;
}
static void mmc5setPrgBank2(uint16_t addr, uint8_t val) //C000-DFFF
{
	if(mmc5.prgBank2PtrType == 0) //RAM
		mmc5.prgBank2Ptr[addr&0x1FFF] = val;
}
//no mmc5setPrgBank3, E000-FFFF is always ROM

void mmc5initSet8(uint16_t addr)
{
	if(addr >= 0x5000 && addr < 0x5016)
		memInitMapperSetPointer(addr, mmc5AudioSet8);
	else if((addr >= 0x5100 && addr < 0x512C) || addr == 0x5130)
		memInitMapperSetPointer(addr, mmc5setParams51XX);
	else if(addr >= 0x5200 && addr < 0x5207)
		memInitMapperSetPointer(addr, mmc5setParams52XX);
	else if(addr >= 0x5C00 && addr < 0x6000)
		memInitMapperSetPointer(addr, mmc5setEXRAM);
	else if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, mmc5setRAMBank6XXX);
	else if(addr >= 0x8000)
	{
		if(addr < 0xA000)
			memInitMapperSetPointer(addr, mmc5setPrgBank0);
		else if(addr < 0xC000)
			memInitMapperSetPointer(addr, mmc5setPrgBank1);
		else if(addr < 0xE000)
			memInitMapperSetPointer(addr, mmc5setPrgBank2);
		//no addr >= 0xE000 here cause theres no mmc5setPrgBank3
	}
}

uint8_t mmc5chrGet8(uint16_t addr)
{
	//printf("%04x\n",addr);
	if(mapperChrMode == 0)
	{
		if(mmc5.splitEnable)
			return mmc5.chrROM[(((mmc5.splitBank<<12)+(addr&0xFFF))&mmc5.chrROMand)];
		else if(mmc5.exMode == 1) //Special ROM Bank per tile
			return mmc5.chrROM[(((mmc5.mode1Bank<<12)+(addr&0xFFF))&mmc5.chrROMand)];
	}
	bool readLowRegs = true;
	if(ppu816Sprite)
	{
		if(mapperChrMode == 0) //BG
			readLowRegs = false;
		else if(mapperChrMode == 1) //Sprite
			readLowRegs = true;
		else if(mapperChrMode == 2) //2007
		{
			if(mmc5.chrSet)
				readLowRegs = false;
			else
				readLowRegs = true;
		}
	}
	if(readLowRegs) //using chr regs 0-7
		return mmc5.chrROMPtrLower[(addr>>10)&7][addr&0x3FF];
	else //using chr regs 0x8-0xB
		return mmc5.chrROMPtrUpper[(addr>>10)&7][addr&0x3FF];
}

uint8_t mmc5vramGetNT(uint16_t addr)
{
	if(mmc5.splitEnable)
		return mmc5.exRAM[mmc5.DrawnXTile+((mmc5.irqCtr&~7)<<2)];
	else if(mmc5.exMode == 1)
	{
		uint8_t tmp = mmc5.exRAM[addr&0x3FF];
		mmc5.mode1Bank = (tmp&0x3F)|(mmc5.upperCHRBank<<6);
		mmc5.mode1Attrib = (tmp>>6)|((tmp>>4)&0xC)|((tmp>>2)&0x30)|(tmp&0xC0);
	}
	switch(mmc5.vramBankMode[(addr>>10)&3])
	{
		case 0:
			return mmc5.VRAM[(addr&0x3FF)];
		case 1:
			return mmc5.VRAM[(addr&0x3FF)|0x400];
		case 2:
			if(mmc5.exMode < 2)
				return mmc5.exRAM[addr&0x3FF];
			return 0;
		case 3:
		default:
			return mmc5.fillTile;
	}
}

uint8_t mmc5vramGetAT(uint16_t addr)
{
	if(mmc5.splitEnable)
		return mmc5.exRAM[0x3C0|((mmc5.DrawnXTile>>3)+((mmc5.irqCtr&~15)>>2))];
	else if(mmc5.exMode == 1)
		return mmc5.mode1Attrib;
	switch(mmc5.vramBankMode[(addr>>10)&3])
	{
		case 0:
			return mmc5.VRAM[(addr&0x3FF)];
		case 1:
			return mmc5.VRAM[(addr&0x3FF)|0x400];
		case 2:
			if(mmc5.exMode < 2)
				return mmc5.exRAM[addr&0x3FF];
			return 0;
		case 3:
		default:
			return mmc5.fillAttr;
	}
}

void mmc5vramSet8(uint16_t addr, uint8_t val)
{
	switch(mmc5.vramBankMode[(addr>>10)&3])
	{
		case 0:
			mmc5.VRAM[(addr&0x3FF)] = val;
			break;
		case 1:
			mmc5.VRAM[(addr&0x3FF)|0x400] = val;
			break;
		case 2:
			if(mmc5.exMode < 2)
				mmc5.exRAM[addr&0x3FF] = val;
			break;
		default:
			break;
	}
}

void mmc5chrSetRAM(uint16_t addr, uint8_t val)
{
	//printf("mmc5chrSet8 %04x %02x\n", addr, val);
	mmc5.chrROM[addr&0x1FFF] = val;
}

void mmc5initPPUGet8(uint16_t addr)
{
	if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, mmc5chrGet8);
	else if(addr < 0x3F00)
	{
		if((addr&0x3FF) < 0x3C0)
			memInitMapperPPUGetPointer(addr, mmc5vramGetNT);
		else
			memInitMapperPPUGetPointer(addr, mmc5vramGetAT);
	}
}

void mmc5initPPUSet8(uint16_t addr)
{
	if(addr < 0x2000)
	{
		if(mmc5.chrROM == mmc5.chrRAM) //Writable
			memInitMapperPPUSetPointer(addr, mmc5chrSetRAM);
	}
	else if(addr < 0x3F00)
		memInitMapperPPUSetPointer(addr, mmc5vramSet8);
}

void mmc5setTile(uint16_t dot)
{
	if(dot == 337) //unused tile fetch, not doing anything here
		return;
	else if(dot == 339) //unused fetch too, we use it for scanline detection
	{
		//happens after rendering was disabled or on pre-render scanline
		if(!ppuInFrame)
		{
			//later cleared by ppu itself for now...
			ppuInFrame = true;
			mmc5.irqCtr = 0;
			mmc5.irqPending = false;
		}
		else
		{
			mmc5.irqCtr++;
			if(mmc5.irqCtr == mmc5.irqVal)
			{
				mmc5.irqPending = true;
				if(mmc5.irqEnable)
					interrupt |= MAPPER_IRQ;
				//printf("MMC5 IRQ at %i\n", mmc5.irqCtr);
			}
		}
		//dont update tiles as its an unused fetch
		return;
	}
	if(dot == 321) //first tile
	{
		mmc5.DrawnXTile = 0;
		if(mmc5.splitAllow)
			mmc5.splitEnable = mmc5.splitInitEnable;
	}
	else
		mmc5.DrawnXTile++;
	if(mmc5.splitAllow && mmc5.DrawnXTile == mmc5.splitTile)
		mmc5.splitEnable ^= true;
}
