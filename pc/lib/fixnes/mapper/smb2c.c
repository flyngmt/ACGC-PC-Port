/*
 * Copyright (C) 2019 FIX94
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
	uint8_t *prgROM;
	uint8_t *prgROMBank5000Ptr, *prgROMBank6000Ptr;
	uint32_t curPRGBank5000, curPRGBank6000;
	uint16_t irqCtr;
} smb2c;

void smb2c_reset()
{
	smb2c.irqCtr = 0;
}

void smb2c_SetPrgROMBankPtr()
{
	smb2c.prgROMBank5000Ptr = smb2c.prgROM+smb2c.curPRGBank5000;
	smb2c.prgROMBank6000Ptr = smb2c.prgROM+smb2c.curPRGBank6000;
}

void m40init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg8init(prgROMin,prgROMsizeIn);
	smb2c.prgROM = prgROMin;
	//special low banks
	smb2c.curPRGBank5000 = 0;
	smb2c.curPRGBank6000 = (6<<13);
	smb2c_SetPrgROMBankPtr();
	//other banks
	prg8setBank0(4<<13);
	prg8setBank1(5<<13);
	prg8setBank2(0);
	prg8setBank3(7<<13);
	chr8init(chrROMin,chrROMsizeIn);
	smb2c_reset();
	printf("Mapper 40 inited\n");
}

static bool m43_isMary2;
void m43init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg8init(prgROMin,prgROMsizeIn);
	smb2c.prgROM = prgROMin;
	//special low banks
	smb2c.curPRGBank5000 = (16<<12); //17<<12 hides title logo
	smb2c.curPRGBank6000 = (2<<13);
	smb2c_SetPrgROMBankPtr();
	//other banks
	prg8setBank0(1<<13);
	prg8setBank1(0);
	prg8setBank2(0);
	prg8setBank3(9<<13);
	chr8init(chrROMin,chrROMsizeIn);
	//mr mary 2 uses chr ram, others use chr rom
	m43_isMary2 = (chrROMsizeIn == 0);
	smb2c_reset();
	printf("Mapper 43 inited (Mr Mary 2=%d)\n", m43_isMary2);
}

void m50init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	prg8init(prgROMin,prgROMsizeIn);
	smb2c.prgROM = prgROMin;
	//special low banks
	smb2c.curPRGBank5000 = 0;
	smb2c.curPRGBank6000 = (15<<13);
	smb2c_SetPrgROMBankPtr();
	//other banks
	prg8setBank0(8<<13);
	prg8setBank1(9<<13);
	prg8setBank2(0);
	prg8setBank3(11<<13);
	chr8init(chrROMin,chrROMsizeIn);
	smb2c_reset();
	printf("Mapper 50 inited\n");
}

extern uint8_t interrupt;
static void smb2c_irqDisable()
{
	//disable and ack
	smb2c.irqCtr = 0;
	interrupt &= ~MAPPER_IRQ;
	//printf("Interrupt disabled\n");
}

static void smb2c_irqEnable()
{
	smb2c.irqCtr = 0x1000;
	//printf("Interrupt enabled\n");
}

void smb2c_cycle()
{
	if(smb2c.irqCtr && !(--smb2c.irqCtr))
		interrupt |= MAPPER_IRQ;
}

static uint8_t smb2c_getROM5000(uint16_t addr) { return smb2c.prgROMBank5000Ptr[addr&0x7FF]; }
static uint8_t smb2c_getROM6000(uint16_t addr) { return smb2c.prgROMBank6000Ptr[addr&0x1FFF]; }


//mapper 40 specific mapping
void m40initGet8(uint16_t addr)
{
	if(addr < 0x6000) return;
	else if(addr < 0x8000) memInitMapperGetPointer(addr, smb2c_getROM6000);
	else prg8initGet8(addr);
}

void m40setParams8000(uint16_t addr, uint8_t val) { (void)addr; (void)val; smb2c_irqDisable(); }
void m40setParamsA000(uint16_t addr, uint8_t val) { (void)addr; (void)val; smb2c_irqEnable(); }

void m40setParamsE000(uint16_t addr, uint8_t val) { (void)addr; prg8setBank2(val<<13); }

void m40initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE000;
	if(proc_addr == 0x8000) memInitMapperSetPointer(ori_addr, m40setParams8000);
	else if(proc_addr == 0xA000) memInitMapperSetPointer(ori_addr, m40setParamsA000);
	else if(proc_addr == 0xE000) memInitMapperSetPointer(ori_addr, m40setParamsE000);
}


//mapper 43 specific mapping
void m43initGet8(uint16_t addr)
{
	if(addr < 0x5000) return;
	else if(addr < 0x6000) memInitMapperGetPointer(addr, smb2c_getROM5000);
	else if(addr < 0x8000) memInitMapperGetPointer(addr, smb2c_getROM6000);
	else prg8initGet8(addr);
}

//seems to be layout of some lf36 file, follows https://wiki.nesdev.com/w/index.php/INES_Mapper_043
static const uint8_t m43bankConv[8] = { 4, 3, 4, 4, 4, 7, 5, 6 };
//seems to be layout of some mr mary 2 file, follows https://wiki.nesdev.com/w/index.php/NES_2.0_Mapper_357
static const uint8_t m43bankConvMary2[8] = { 4, 3, 5, 3, 6, 3, 7, 3 };
void m43setParams4022(uint16_t addr, uint8_t val)
{
	(void)addr;
	uint8_t newBank = m43_isMary2 ? m43bankConvMary2[val&7] : m43bankConv[val&7];
	prg8setBank2(newBank<<13);
}
//also specific to that mr mary 2 file, not used by the lf36 file
void m43setParams4120(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(!m43_isMary2) return; //just in case
	smb2c.curPRGBank6000 = (val&1) ? 0 : (2<<13);
	smb2c_SetPrgROMBankPtr();
	prg8setBank3((val&1) ? (8<<13) : (9<<13));
}

void m43setParams4122(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val&1)
		smb2c_irqEnable();
	else
		smb2c_irqDisable();
}

void m43initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xF1FF;
	if(proc_addr == 0x4022)
		memInitMapperSetPointer(ori_addr, m43setParams4022);
	else if(proc_addr == 0x4120)
		memInitMapperSetPointer(ori_addr, m43setParams4120);
	else if(proc_addr == 0x4122 || proc_addr == 0x8122)
		memInitMapperSetPointer(ori_addr, m43setParams4122);
}


//mapper 50 specific mapping
void m50initGet8(uint16_t addr)
{
	if(addr < 0x6000) return;
	else if(addr < 0x8000) memInitMapperGetPointer(addr, smb2c_getROM6000);
	else prg8initGet8(addr);
}

//appears to be yet another layout, follows https://wiki.nesdev.com/w/index.php/INES_Mapper_050
static const uint8_t m50bankConv[16] = { 0, 4, 1, 5, 2, 6, 3, 7, 8, 12, 9, 13, 10, 14, 11, 15 };
void m50setParams4020(uint16_t addr, uint8_t val)
{
	(void)addr;
	uint8_t newBank = m50bankConv[val&15];
	prg8setBank2(newBank<<13);
}

void m50setParams4120(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val&1)
		smb2c_irqEnable();
	else
		smb2c_irqDisable();
}

void m50initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xD160;
	if(proc_addr == 0x4020) memInitMapperSetPointer(ori_addr, m50setParams4020);
	else if(proc_addr == 0x4120) memInitMapperSetPointer(ori_addr, m50setParams4120);
}
