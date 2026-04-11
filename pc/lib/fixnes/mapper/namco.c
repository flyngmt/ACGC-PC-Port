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
#include "../apu.h"
#include "../cpu.h"
#include "../ppu.h"
#include "../mapper.h"
#include "../mem.h"
#include "../audio_n163.h"
#include "../mapper_h/common.h"
#include "../mapper_h/namco.h"

enum {
	T_N163 = 0,
	T_N175,
	T_N340,
	T_UNK,
};

static struct {
	uint8_t *prgRAM;
	uint8_t *chrROM;
	uint8_t *chrBankPtr[8];
	uint8_t chrBankPtrType[8];
	uint32_t prgRAMsize;
	uint32_t chrROMsize;
	uint32_t CHRBank[8];
	uint8_t VRAM[0x800];
	uint8_t *VRAMBankPtr[4];
	uint8_t VRAMBankPtrType[4];
	bool CHRAddr0XXXIsNT;
	bool CHRAddr1XXXIsNT;
	uint8_t NTAddr[4];
	uint16_t irqCtr;
	bool irqEnable;
	uint8_t type;
	uint32_t chrROMand;
} namco;

static void namco_SetChrROMBankPtr()
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		namco.chrBankPtr[i] = namco.chrROM+((namco.CHRBank[i]<<10)&namco.chrROMand);
		namco.chrBankPtrType[i] = 1; //all ROM
	}
}

extern uint8_t emuInitialNT;
static void namco_SetInitialNT()
{
	if(emuInitialNT == NT_VERTICAL)
	{
		namco.VRAMBankPtr[0] = namco.VRAM+0x000; namco.VRAMBankPtr[1] = namco.VRAM+0x400;
		namco.VRAMBankPtr[2] = namco.VRAM+0x000; namco.VRAMBankPtr[3] = namco.VRAM+0x400;
	}
	else
	{
		if(emuInitialNT != NT_HORIZONTAL)
			printf("Unknown Initial Nametable, guessing horizontal\n");
		namco.VRAMBankPtr[0] = namco.VRAM+0x000; namco.VRAMBankPtr[1] = namco.VRAM+0x000;
		namco.VRAMBankPtr[2] = namco.VRAM+0x400; namco.VRAMBankPtr[3] = namco.VRAM+0x400;
	}
	//all RAM
	namco.VRAMBankPtrType[0] = 0, namco.VRAMBankPtrType[1] = 0,
	namco.VRAMBankPtrType[2] = 0, namco.VRAMBankPtrType[3] = 0;
}

void namco_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg8init(prgROMin,prgROMsizeIn);
	namco.prgRAM = prgRAMin;
	namco.prgRAMsize = prgRAMsizeIn;
	prg8setBank0(0x0000);
	prg8setBank1(0x2000);
	prg8setBank2(0x4000);
	prg8setBank3(prgROMsizeIn - 0x2000);
	namco.chrROM = chrROMin;
	namco.chrROMsize = chrROMsizeIn;
	namco.chrROMand = mapperGetAndValue(chrROMsizeIn);
	memset(namco.CHRBank,0,8*sizeof(uint32_t));
	memset(namco.VRAM,0,0x800);
	namco.CHRAddr0XXXIsNT = false;
	namco.CHRAddr1XXXIsNT = false;
	namco.NTAddr[0] = 0xE0, namco.NTAddr[1] = 0xE0,
	namco.NTAddr[2] = 0xE0, namco.NTAddr[3] = 0xE0;
	namco.irqCtr = 0;
	namco.irqEnable = false;
	namco.type = T_UNK;
	namco_SetInitialNT();
	namco_SetChrROMBankPtr();
	printf("Namco Mapper inited\n");
}

static void namco_SetChrBankPtr_N163()
{
	uint8_t i;
	//CHR Addr 0x0000-0x0FFF
	for(i = 0; i < 4; i++)
	{
		if(namco.CHRBank[i] >= 0xE0 && namco.CHRAddr0XXXIsNT) //CHR from NT RAM
		{
			namco.chrBankPtr[i] = namco.VRAM+((namco.CHRBank[i]&1)?0x400:0);
			namco.chrBankPtrType[i] = 0;
		}
		else //CHR from CHR ROM
		{
			namco.chrBankPtr[i] = namco.chrROM+((namco.CHRBank[i]<<10)&namco.chrROMand);
			namco.chrBankPtrType[i] = 1;
		}
	}
	//CHR Addr 0x1000-0x1FFF
	for(i = 4; i < 8; i++)
	{
		if(namco.CHRBank[i] >= 0xE0 && namco.CHRAddr1XXXIsNT) //CHR from NT RAM
		{
			namco.chrBankPtr[i] = namco.VRAM+((namco.CHRBank[i]&1)?0x400:0);
			namco.chrBankPtrType[i] = 0;
		}
		else //CHR from CHR ROM
		{
			namco.chrBankPtr[i] = namco.chrROM+((namco.CHRBank[i]<<10)&namco.chrROMand);
			namco.chrBankPtrType[i] = 1;
		}
	}
}

static void namco_SetNTPtr_N163()
{
	uint8_t i;
	for(i = 0; i < 4; i++)
	{
		if(namco.NTAddr[i] >= 0xE0) //NT from NT RAM
		{
			namco.VRAMBankPtr[i] = namco.VRAM+((namco.NTAddr[i]&1)?0x400:0);
			namco.VRAMBankPtrType[i] = 0;
		}
		else //NT from CHR ROM
		{
			namco.VRAMBankPtr[i] = namco.chrROM+((namco.NTAddr[i]<<10)&namco.chrROMand);
			namco.VRAMBankPtrType[i] = 1;
		}
	}
}

static void namcoSetN163(uint16_t inaddr)
{
	printf("Should be Namco N129/N163, wrote to %04x\n", inaddr);
	namco.type = T_N163;
	n163AudioInit();
	namco_SetChrBankPtr_N163();
	namco_SetNTPtr_N163();
	uint32_t addr;
	for(addr = 0x0000; addr < 0x4000; addr++)
	{
		namco_initPPUGet8(addr);
		namco_initPPUSet8(addr);
	}
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		namco_initGet8(addr);
		namco_initSet8(addr);
	}
}

static void namcoGuessN175(uint16_t inaddr)
{
	printf("Guessing Namco N175, wrote to %04x\n", inaddr);
	namco.type = T_N175;
	namco_SetInitialNT();
	uint32_t addr;
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		namco_initGet8(addr);
		namco_initSet8(addr);
	}
}

static void namcoGuessN340(uint16_t inaddr)
{
	printf("Guessing Namco N340, wrote to %04x\n", inaddr);
	namco.type = T_N340;
	uint32_t addr;
	for(addr = 0x4000; addr < 0x10000; addr++)
	{
		namco_initGet8(addr);
		namco_initSet8(addr);
	}
}

static uint8_t namco_getParams50XX(uint16_t addr)
{
	(void)addr;
	return namco.irqCtr&0xFF;
}

static uint8_t namco_getParams58XX(uint16_t addr)
{
	(void)addr;
	return (((namco.irqCtr>>8)&0x7F)|(namco.irqEnable<<7));
}

static uint8_t namco_getParams48XX_SetN163(uint16_t addr)
{
	namcoSetN163(addr);
	return n163AudioGet8_48XX(addr);
}

static uint8_t namco_getParams50XX_SetN163(uint16_t addr)
{
	namcoSetN163(addr);
	return namco_getParams50XX(addr);
}

static uint8_t namco_getParams58XX_SetN163(uint16_t addr)
{
	namcoSetN163(addr);
	return namco_getParams58XX(addr);
}

static uint8_t namco_getRAM(uint16_t addr)
{
	return namco.prgRAM[addr&0x1FFF];
}

static uint8_t namco_getRAM_GuessN175(uint16_t addr)
{
	namcoGuessN175(addr);
	return namco_getRAM(addr);
}


void namco_initGet8(uint16_t addr)
{
	if(addr >= 0x4800 && addr < 0x6000)
	{
		if(namco.type != T_N163)
		{
			if(addr < 0x5000)
				memInitMapperGetPointer(addr, namco_getParams48XX_SetN163);
			else if(addr < 0x5800)
				memInitMapperGetPointer(addr, namco_getParams50XX_SetN163);
			else //if addr < 0x6000
				memInitMapperGetPointer(addr, namco_getParams58XX_SetN163);
		}
		else
		{
			if(addr < 0x5000)
				memInitMapperGetPointer(addr, n163AudioGet8_48XX);
			else if(addr < 0x5800)
				memInitMapperGetPointer(addr, namco_getParams50XX);
			else //if addr < 0x6000
				memInitMapperGetPointer(addr, namco_getParams58XX);
		}
	}
	else if(addr >= 0x6000 && addr < 0x8000)
	{
		if((namco.type == T_N340) || (namco.type == T_UNK))
			memInitMapperGetPointer(addr, namco_getRAM_GuessN175);
		else
			memInitMapperGetPointer(addr, namco_getRAM);
	}
	else
		prg8initGet8(addr);
}

extern uint8_t interrupt;
static void namco_setParams50XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.irqCtr &= ~0xFF;
	namco.irqCtr |= val;
	interrupt &= ~MAPPER_IRQ;
}

static void namco_setParams58XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.irqCtr &= 0xFF;
	namco.irqCtr |= (val&0x7F)<<8;
	namco.irqEnable = (val&0x80)!=0;
	interrupt &= ~MAPPER_IRQ;
}

static void namco_setParams48XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	n163AudioSet8_48XX(addr, val);
}

static void namco_setParams50XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	namco_setParams50XX(addr, val);
}

static void namco_setParams58XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	namco_setParams58XX(addr, val);
}

//0x6000-0x7FFF
static void namco_setRAM(uint16_t addr, uint8_t val)
{
	namco.prgRAM[addr&0x1FFF] = val;
}
static void namco_setRAM_GuessN175(uint16_t addr, uint8_t val)
{
	namcoGuessN175(addr);
	namco_setRAM(addr, val);
}

//0x8000-0xBFFF
static void namco_setChrROMBank(uint16_t addr, uint8_t val)
{
	namco.CHRBank[(addr>>11)&7] = val;
	namco_SetChrROMBankPtr();
}
static void namco_setChrBank_N163(uint16_t addr, uint8_t val)
{
	namco.CHRBank[(addr>>11)&7] = val;
	namco_SetChrBankPtr_N163();
}

static void namco_setParamsC0XX_N175(uint16_t addr, uint8_t val)
{
	(void)addr;
	//save this just in case
	namco.NTAddr[0] = val;
}

static void namco_setParamsC0XX_N163(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.NTAddr[0] = val;
	namco_SetNTPtr_N163();
}

static void namco_setParamsC8XX_N163(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.NTAddr[1] = val;
	namco_SetNTPtr_N163();
}

static void namco_setParamsD0XX_N163(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.NTAddr[2] = val;
	namco_SetNTPtr_N163();
}

static void namco_setParamsD8XX_N163(uint16_t addr, uint8_t val)
{
	(void)addr;
	namco.NTAddr[3] = val;
	namco_SetNTPtr_N163();
}

static void namco_setParamsC0XX_GuessN175(uint16_t addr, uint8_t val)
{
	namcoGuessN175(addr);
	namco_setParamsC0XX_N175(addr, val);
}

static void namco_setParamsC8XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	namco_setParamsC8XX_N163(addr, val);
}

static void namco_setParamsD0XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	namco_setParamsD0XX_N163(addr, val);
}

static void namco_setParamsD8XX_SetN163(uint16_t addr, uint8_t val)
{
	namcoSetN163(addr);
	namco_setParamsD8XX_N163(addr, val);
}

static void namco_setParamsE0XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank0((val&0x3F)<<13);
}

static void namco_setParamsE0XX_N340(uint16_t addr, uint8_t val)
{
	namco_setParamsE0XX(addr, val);
	switch((val>>6)&3)
	{
		case 0: //NT Single Lower
			namco.VRAMBankPtr[0] = namco.VRAM+0x000; namco.VRAMBankPtr[1] = namco.VRAM+0x000;
			namco.VRAMBankPtr[2] = namco.VRAM+0x000; namco.VRAMBankPtr[3] = namco.VRAM+0x000;
			break;
		case 1: //Vertical
			namco.VRAMBankPtr[0] = namco.VRAM+0x000; namco.VRAMBankPtr[1] = namco.VRAM+0x400;
			namco.VRAMBankPtr[2] = namco.VRAM+0x000; namco.VRAMBankPtr[3] = namco.VRAM+0x400;
			break;
		case 2: //NT Single Upper
			namco.VRAMBankPtr[0] = namco.VRAM+0x400; namco.VRAMBankPtr[1] = namco.VRAM+0x400;
			namco.VRAMBankPtr[2] = namco.VRAM+0x400; namco.VRAMBankPtr[3] = namco.VRAM+0x400;
			break;
		case 3: //Horizontal
			namco.VRAMBankPtr[0] = namco.VRAM+0x000; namco.VRAMBankPtr[1] = namco.VRAM+0x000;
			namco.VRAMBankPtr[2] = namco.VRAM+0x400; namco.VRAMBankPtr[3] = namco.VRAM+0x400;
			break;
	}
	//all RAM
	namco.VRAMBankPtrType[0] = 0, namco.VRAMBankPtrType[1] = 0,
	namco.VRAMBankPtrType[2] = 0, namco.VRAMBankPtrType[3] = 0;
}

static void namco_setParamsE0XX_GuessN340(uint16_t addr, uint8_t val)
{
	if((val&0xC0) != 0)
	{
		namcoGuessN340(addr);
		namco_setParamsE0XX_N340(addr, val);
	}
	else
		namco_setParamsE0XX(addr, val);
}

static void namco_setParamsE8XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank1((val&0x3F)<<13);
	//always back up in case type changes to N163
	namco.CHRAddr0XXXIsNT = (val&0x40) == 0;
	namco.CHRAddr1XXXIsNT = (val&0x80) == 0;
}

static void namco_setParamsF0XX(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg8setBank2((val&0x3F)<<13);
}

void namco_initSet8(uint16_t addr)
{
	if(addr >= 0x4800 && addr < 0x6000)
	{
		if(namco.type != T_N163)
		{
			if(addr < 0x5000)
				memInitMapperSetPointer(addr, namco_setParams48XX_SetN163);
			else if(addr < 0x5800)
				memInitMapperSetPointer(addr, namco_setParams50XX_SetN163);
			else //if addr < 0x6000
				memInitMapperSetPointer(addr, namco_setParams58XX_SetN163);
		}
		else
		{
			if(addr < 0x5000)
				memInitMapperSetPointer(addr, n163AudioSet8_48XX);
			else if(addr < 0x5800)
				memInitMapperSetPointer(addr, namco_setParams50XX);
			else //if addr < 0x6000
				memInitMapperSetPointer(addr, namco_setParams58XX);
		}
	}
	else if(addr >= 0x6000 && addr < 0x8000)
	{
		if((namco.type == T_N340) || (namco.type == T_UNK))
			memInitMapperSetPointer(addr, namco_setRAM_GuessN175);
		else
			memInitMapperSetPointer(addr, namco_setRAM);
	}
	else if(addr >= 0x8000)
	{
		if(addr < 0xE000)
		{
			if(addr >= 0xC000)
			{
				if(namco.type != T_N163)
				{
					if(addr < 0xC800)
					{
						if((namco.type == T_N340) || (namco.type == T_UNK))
							memInitMapperSetPointer(addr, namco_setParamsC0XX_GuessN175);
						else //namco.type == T_N175
							memInitMapperSetPointer(addr, namco_setParamsC0XX_N175);
					}
					else if(addr < 0xD000)
						memInitMapperSetPointer(addr, namco_setParamsC8XX_SetN163);
					else if(addr < 0xD800)
						memInitMapperSetPointer(addr, namco_setParamsD0XX_SetN163);
					else //if addr < 0xE000
						memInitMapperSetPointer(addr, namco_setParamsD8XX_SetN163);
				}
				else
				{
					if(addr < 0xC800)
						memInitMapperSetPointer(addr, namco_setParamsC0XX_N163);
					else if(addr < 0xD000)
						memInitMapperSetPointer(addr, namco_setParamsC8XX_N163);
					else if(addr < 0xD800)
						memInitMapperSetPointer(addr, namco_setParamsD0XX_N163);
					else //if addr < 0xE000
						memInitMapperSetPointer(addr, namco_setParamsD8XX_N163);
				}
			}
			else
			{
				if(namco.type != T_N163)
					memInitMapperSetPointer(addr, namco_setChrROMBank);
				else
					memInitMapperSetPointer(addr, namco_setChrBank_N163);
			}
		}
		else if(addr < 0xE800)
		{
			if(namco.type == T_UNK)
				memInitMapperSetPointer(addr, namco_setParamsE0XX_GuessN340);
			else if(namco.type == T_N340)
				memInitMapperSetPointer(addr, namco_setParamsE0XX_N340);
			else
				memInitMapperSetPointer(addr, namco_setParamsE0XX);
		}
		else if(addr < 0xF000)
			memInitMapperSetPointer(addr, namco_setParamsE8XX);
		else if(addr < 0xF800)
			memInitMapperSetPointer(addr, namco_setParamsF0XX);
		else if(addr >= 0xF800)
		{
			//cant use this for namcoSetN163, dream master writes 0x40 into this reg on boot
			memInitMapperSetPointer(addr, n163AudioSet8_F8XX);
		}
	}
}

static uint8_t namco_chrGetBank0(uint16_t addr)
{
	return namco.chrBankPtr[0][addr&0x3FF];
}
static uint8_t namco_chrGetBank1(uint16_t addr)
{
	return namco.chrBankPtr[1][addr&0x3FF];
}
static uint8_t namco_chrGetBank2(uint16_t addr)
{
	return namco.chrBankPtr[2][addr&0x3FF];
}
static uint8_t namco_chrGetBank3(uint16_t addr)
{
	return namco.chrBankPtr[3][addr&0x3FF];
}
static uint8_t namco_chrGetBank4(uint16_t addr)
{
	return namco.chrBankPtr[4][addr&0x3FF];
}
static uint8_t namco_chrGetBank5(uint16_t addr)
{
	return namco.chrBankPtr[5][addr&0x3FF];
}
static uint8_t namco_chrGetBank6(uint16_t addr)
{
	return namco.chrBankPtr[6][addr&0x3FF];
}
static uint8_t namco_chrGetBank7(uint16_t addr)
{
	return namco.chrBankPtr[7][addr&0x3FF];
}

static uint8_t namco_VRAMGetBank0(uint16_t addr)
{
	return namco.VRAMBankPtr[0][addr&0x3FF];
}
static uint8_t namco_VRAMGetBank1(uint16_t addr)
{
	return namco.VRAMBankPtr[1][addr&0x3FF];
}
static uint8_t namco_VRAMGetBank2(uint16_t addr)
{
	return namco.VRAMBankPtr[2][addr&0x3FF];
}
static uint8_t namco_VRAMGetBank3(uint16_t addr)
{
	return namco.VRAMBankPtr[3][addr&0x3FF];
}
void namco_initPPUGet8(uint16_t addr)
{
	if(addr < 0x400)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank0);
	else if(addr < 0x800)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank1);
	else if(addr < 0xC00)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank2);
	else if(addr < 0x1000)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank3);
	else if(addr < 0x1400)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank4);
	else if(addr < 0x1800)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank5);
	else if(addr < 0x1C00)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank6);
	else if(addr < 0x2000)
		memInitMapperPPUGetPointer(addr, namco_chrGetBank7);
	else if(addr < 0x2400)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank0);
	else if(addr < 0x2800)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank1);
	else if(addr < 0x2C00)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank2);
	else if(addr < 0x3000)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank3);
	else if(addr < 0x3400)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank0);
	else if(addr < 0x3800)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank1);
	else if(addr < 0x3C00)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank2);
	else if(addr < 0x3F00)
		memInitMapperPPUGetPointer(addr, namco_VRAMGetBank3);
}

static void namco_chrSetBank0_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[0] == 0) //RAM
		namco.chrBankPtr[0][addr&0x3FF] = val;
}
static void namco_chrSetBank1_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[1] == 0) //RAM
		namco.chrBankPtr[1][addr&0x3FF] = val;
}
static void namco_chrSetBank2_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[2] == 0) //RAM
		namco.chrBankPtr[2][addr&0x3FF] = val;
}
static void namco_chrSetBank3_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[3] == 0) //RAM
		namco.chrBankPtr[3][addr&0x3FF] = val;
}
static void namco_chrSetBank4_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[4] == 0) //RAM
		namco.chrBankPtr[4][addr&0x3FF] = val;
}
static void namco_chrSetBank5_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[5] == 0) //RAM
		namco.chrBankPtr[5][addr&0x3FF] = val;
}
static void namco_chrSetBank6_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[6] == 0) //RAM
		namco.chrBankPtr[6][addr&0x3FF] = val;
}
static void namco_chrSetBank7_N163(uint16_t addr, uint8_t val)
{
	if(namco.chrBankPtrType[7] == 0) //RAM
		namco.chrBankPtr[7][addr&0x3FF] = val;
}

static void namco_VRAMSetBank0_N163(uint16_t addr, uint8_t val)
{
	if(namco.VRAMBankPtrType[0] == 0) //RAM
		namco.VRAMBankPtr[0][addr&0x3FF] = val;
}
static void namco_VRAMSetBank1_N163(uint16_t addr, uint8_t val)
{
	if(namco.VRAMBankPtrType[1] == 0) //RAM
		namco.VRAMBankPtr[1][addr&0x3FF] = val;
}
static void namco_VRAMSetBank2_N163(uint16_t addr, uint8_t val)
{
	if(namco.VRAMBankPtrType[2] == 0) //RAM
		namco.VRAMBankPtr[2][addr&0x3FF] = val;
}
static void namco_VRAMSetBank3_N163(uint16_t addr, uint8_t val)
{
	if(namco.VRAMBankPtrType[3] == 0) //RAM
		namco.VRAMBankPtr[3][addr&0x3FF] = val;
}

static void namco_VRAMSetBank0(uint16_t addr, uint8_t val)
{
	namco.VRAMBankPtr[0][addr&0x3FF] = val;
}
static void namco_VRAMSetBank1(uint16_t addr, uint8_t val)
{
	namco.VRAMBankPtr[1][addr&0x3FF] = val;
}
static void namco_VRAMSetBank2(uint16_t addr, uint8_t val)
{
	namco.VRAMBankPtr[2][addr&0x3FF] = val;
}
static void namco_VRAMSetBank3(uint16_t addr, uint8_t val)
{
	namco.VRAMBankPtr[3][addr&0x3FF] = val;
}

void namco_initPPUSet8(uint16_t addr)
{
	if(namco.type == T_N163)
	{
		if(addr < 0x400)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank0_N163);
		else if(addr < 0x800)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank1_N163);
		else if(addr < 0xC00)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank2_N163);
		else if(addr < 0x1000)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank3_N163);
		else if(addr < 0x1400)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank4_N163);
		else if(addr < 0x1800)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank5_N163);
		else if(addr < 0x1C00)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank6_N163);
		else if(addr < 0x2000)
			memInitMapperPPUSetPointer(addr, namco_chrSetBank7_N163);
		else if(addr < 0x2400)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank0_N163);
		else if(addr < 0x2800)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank1_N163);
		else if(addr < 0x2C00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank2_N163);
		else if(addr < 0x3000)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank3_N163);
		else if(addr < 0x3400)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank0_N163);
		else if(addr < 0x3800)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank1_N163);
		else if(addr < 0x3C00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank2_N163);
		else if(addr < 0x3F00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank3_N163);
	}
	else if(addr >= 0x2000)
	{
		if(addr < 0x2400)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank0);
		else if(addr < 0x2800)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank1);
		else if(addr < 0x2C00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank2);
		else if(addr < 0x3000)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank3);
		else if(addr < 0x3400)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank0);
		else if(addr < 0x3800)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank1);
		else if(addr < 0x3C00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank2);
		else if(addr < 0x3F00)
			memInitMapperPPUSetPointer(addr, namco_VRAMSetBank3);
	}
}

extern uint8_t audioExpansion;
void namco_cycle()
{
	if(audioExpansion&EXP_N163)
		n163AudioClockTimers();
	if(namco.irqEnable)
	{
		if(namco.irqCtr < 0x7FFF)
			namco.irqCtr++;
		if(namco.irqCtr >= 0x7FFF)
		{
			namco.irqEnable = false;
			if(!(interrupt&MAPPER_IRQ))
			{
				interrupt |= MAPPER_IRQ;
				//printf("Namco Interrupt\n");
			}
		}
	}
}
