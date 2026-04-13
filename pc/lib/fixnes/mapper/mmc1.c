/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../mapper_h/common.h"

static struct {
	bool usesPrgRAM;
	uint8_t *chrROM;
	uint8_t *chrROMBank0Ptr;
	uint8_t *chrROMBank1Ptr;
	uint32_t prgROMsize;
	uint32_t PRGBank256K;
	uint32_t curPRGBank;
	uint32_t firstPRGBank;
	uint32_t lastPRGBank;
	uint32_t curCHRBank0;
	uint32_t curCHRBank1;
	uint8_t sr;
	bool single_prg_bank;
	bool last_bank_fixed;
	bool single_chr_bank;
} mmc1;

static void mmc1SetPrgROMBankPtr()
{
	if(mmc1.single_prg_bank)
	{
		prg16setBank0((mmc1.curPRGBank&~0x7FFF)+0x0000+mmc1.PRGBank256K);
		prg16setBank1((mmc1.curPRGBank&~0x7FFF)+0x4000+mmc1.PRGBank256K);
	}
	else if(mmc1.last_bank_fixed)
	{
		prg16setBank0(mmc1.curPRGBank+mmc1.PRGBank256K);
		prg16setBank1(mmc1.lastPRGBank+mmc1.PRGBank256K);
	}
	else //first bank fixed
	{
		prg16setBank0(mmc1.firstPRGBank+mmc1.PRGBank256K);
		prg16setBank1(mmc1.curPRGBank+mmc1.PRGBank256K);
	}
}

static void mmc1SetChrBankPtr()
{
	if(mmc1.single_chr_bank)
	{
		chr4setBank0((mmc1.curCHRBank0&~0x1FFF)|0x0000);
		chr4setBank1((mmc1.curCHRBank0&~0x1FFF)|0x1000);
	}
	else
	{
		chr4setBank0(mmc1.curCHRBank0);
		chr4setBank1(mmc1.curCHRBank1);
	}
}

void mmc1init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg16init(prgROMin,prgROMsizeIn);
	mmc1.prgROMsize = prgROMsizeIn;
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		mmc1.usesPrgRAM = true;
	}
	else
		mmc1.usesPrgRAM = false;
	mmc1.firstPRGBank = 0;
	mmc1.PRGBank256K = 0;
	mmc1.curPRGBank = mmc1.firstPRGBank;
	mmc1.lastPRGBank = (prgROMsizeIn - 0x4000)&0x3C000;
	chr4init(chrROMin,chrROMsizeIn);
	mmc1.curCHRBank0 = 0;
	mmc1.curCHRBank1 = 0;
	mmc1.sr = (1<<4);//0;
	mmc1.single_prg_bank = false;
	mmc1.last_bank_fixed = true;
	mmc1.single_chr_bank = false;
	mmc1SetPrgROMBankPtr();
	mmc1SetChrBankPtr();
	printf("MMC1 inited\n");
}

void mmc1initGet8(uint16_t addr)
{
	if(mmc1.usesPrgRAM)
		prgRAM8initGet8(addr);
	prg16initGet8(addr);
}

extern bool cpuWriteTMP;
static void mmc1setParams(uint16_t addr, uint8_t val)
{
	// mmc1 regs cant be written to
	// with just 1 cpu cycle delay
	if(cpuWriteTMP)
		return;
	//printf("mmc1set8 %04x %02x\n", addr, val);
	if(val&(1<<7))
	{
		//printf("Reset (???)\n");
		mmc1.sr = (1<<4);//0;
		mmc1.last_bank_fixed = true;
		mmc1.single_prg_bank = false;
		mmc1SetPrgROMBankPtr();
	}
	else if(mmc1.sr & 1)
	{
		mmc1.sr >>= 1;
		mmc1.sr |= ((val&1)<<4);
		//printf("mmc1 sr full, addr %04x sr %02x\n", addr, mmc1.sr);
		if(addr < 0xA000)
		{
			if(!ppu4Screen)
			{
				if((mmc1.sr & 3) == 2)
				{
					//printf("Vertical mode\n");
					ppuSetNameTblVertical();
				}
				else if((mmc1.sr & 3) == 3)
				{
					//printf("Horizontal mode\n");
					ppuSetNameTblHorizontal();
				}
				else
				{
					if((mmc1.sr & 3) == 1)
					{
						//printf("Upper CHR Mode\n");
						//mmc1.small_upper_chr = true;
						ppuSetNameTblSingleUpper();
					}
					else
					{
						
						//printf("Lower CHR Mode\n");
						//mmc1.small_upper_chr = false;
						ppuSetNameTblSingleLower();
					}
				}
			}
			if(((mmc1.sr>>2) & 3) == 2)
			{
				//printf("First bank fixed\n");
				mmc1.last_bank_fixed = false;
				mmc1.single_prg_bank = false;
			}
			else if(((mmc1.sr>>2) & 3) == 3)
			{
				//printf("Last bank fixed\n");
				mmc1.last_bank_fixed = true;
				mmc1.single_prg_bank = false;
			}
			else
			{
				//printf("Some other PRG Bank mode\n");
				mmc1.single_prg_bank = true;
			}
			mmc1SetPrgROMBankPtr();
			if(mmc1.sr & (1<<4))
			{
				//printf("2 CHR Banks\n");
				mmc1.single_chr_bank = false;
			}
			else
			{
				//printf("Single CHR Bank\n");
				mmc1.single_chr_bank = true;
			}
			mmc1SetChrBankPtr();
		}
		else if(addr < 0xC000)
		{
			mmc1.curCHRBank0 = (mmc1.sr<<12);
			mmc1SetChrBankPtr();
			//printf("chr bank 0 now %04x\n", mmc1.curCHRBank0);
			if(mmc1.prgROMsize > 0x40000)
			{
				mmc1.PRGBank256K = (mmc1.sr&0x10)<<14;
				mmc1SetPrgROMBankPtr();
			}
		}
		else if(addr < 0xE000)
		{
			if(!mmc1.single_chr_bank)
			{
				mmc1.curCHRBank1 = (mmc1.sr<<12);
				mmc1SetChrBankPtr();
				//printf("chr bank 1 now %04x\n", mmc1.curCHRBank1);
				if(mmc1.prgROMsize > 0x40000)
				{
					mmc1.PRGBank256K = (mmc1.sr&0x10)<<14;
					mmc1SetPrgROMBankPtr();
				}
			}
		}
		else
		{
			mmc1.curPRGBank = (mmc1.sr&15)<<14;
			mmc1SetPrgROMBankPtr();
			//printf("switchable bank now %04x\n", mmc1.curPRGBank);
		}
		//mmc1.sr = 0;//(mmc1.sr<<4);
		mmc1.sr = (1<<4);
	}
	else
	{
		//printf("%02x\n", mmc1.sr);
		mmc1.sr >>= 1;
		mmc1.sr |= ((val&1)<<4);
		//printf("%02x\n", mmc1.sr);
	}
}

void mmc1initSet8(uint16_t addr)
{
	if(mmc1.usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr >= 0x8000)
		memInitMapperSetPointer(addr, mmc1setParams);
}
