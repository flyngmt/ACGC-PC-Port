/*
 * Copyright (C) 2017 - 2018 FIX94
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
#include "../mapper_h/p32c8.h"

static bool p32c8_usesPrgRAM;
void p32c8init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	prg32init(prgROMin,prgROMsizeIn);
	(void)prgRAMin;
	(void)prgRAMsizeIn;
	p32c8_usesPrgRAM = false;
	prg32setBank0(0);
	chr8init(chrROMin,chrROMsizeIn);
	chr8setBank0(0);
	printf("32k PRG 8k CHR Mapper inited\n");
}

void p32c8RAMinit(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	if(prgRAMin && prgRAMsizeIn)
	{
		prgRAM8init(prgRAMin);
		p32c8_usesPrgRAM = true;
	}
}

void m7_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	//mapper 7 uses either single lower or single upper
	ppuSetNameTblSingleLower();
}

static struct {
	uint8_t input;
	uint8_t reg;
	uint8_t invert;
	uint8_t mode;
} m36;
void m36_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	m36.input = 0, m36.reg = 0, m36.invert = 0, m36.mode = 0;
}

static bool m41_inner;
static uint32_t m41_curCHRBank;
void m41_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	m41_reset();
}

static uint32_t m46_curPRGBank;
void m46_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	m46_reset();
}

static bool m185_CHRDisable;
void m185_init(uint8_t *prgROMin, uint32_t prgROMsizeIn, 
			uint8_t *prgRAMin, uint32_t prgRAMsizeIn,
			uint8_t *chrROMin, uint32_t chrROMsizeIn)
{
	p32c8init(prgROMin,prgROMsizeIn,prgRAMin,prgRAMsizeIn,chrROMin,chrROMsizeIn);
	m185_CHRDisable = false;
}

void p32c8RAMinitGet8(uint16_t addr)
{
	if(p32c8_usesPrgRAM)
		prgRAM8initGet8(addr);
	//normal ROM get
	prg32initGet8(addr);
}

extern uint8_t memLastVal;
static uint8_t m36getParams(uint16_t addr)
{
	(void)addr;
	uint8_t ret = memLastVal&(~0x30);
	ret |= (m36.reg<<4);
	return ret;
}
void m36_initGet8(uint16_t addr)
{
	uint16_t maskedAddr = (addr & 0xE100);
	if(maskedAddr == 0x4100)
		memInitMapperGetPointer(addr, m36getParams);
	else //normal ROM get
		prg32initGet8(addr);
}

static uint8_t m132getParams(uint16_t addr)
{
	(void)addr;
	uint8_t ret = memLastVal&0xF0;
	if(m36.invert) //reverse of the set
		ret |= (m36.reg&7)|((m36.reg^8)&8);
	else ret |= (m36.reg&0xF);
	return ret;
}
void m132_initGet8(uint16_t addr)
{
	uint16_t maskedAddr = (addr & 0xE100);
	if(maskedAddr == 0x4100)
		memInitMapperGetPointer(addr, m132getParams);
	else //normal ROM get
		prg32initGet8(addr);
}

static uint8_t m136getParams(uint16_t addr)
{
	(void)addr;
	uint8_t ret = memLastVal&0xC0;
	if(m36.invert) //reverse of the set
		ret |= (m36.reg&0xF)|((m36.reg^0x30)&0x30);
	else ret |= (m36.reg&0x3F);
	return ret;
}
void m136_initGet8(uint16_t addr)
{
	uint16_t maskedAddr = (addr & 0xE100);
	if(maskedAddr == 0x4100)
		memInitMapperGetPointer(addr, m136getParams);
	else //normal ROM get
		prg32initGet8(addr);
}

//Mapper 172 has data bits reversed so this has to be done
static uint8_t m172doBitRev(uint8_t val)
{
	return (val&0xC0)|((val>>5)&1)|((val>>3)&2)|((val>>1)&4)
			|((val<<1)&8)|((val<<3)&0x10)|((val<<5)&0x20);
}
static uint8_t m172getParams(uint16_t addr) { return m172doBitRev(m136getParams(addr)); }
void m172_initGet8(uint16_t addr)
{
	uint16_t maskedAddr = (addr & 0xE100);
	if(maskedAddr == 0x4100)
		memInitMapperGetPointer(addr, m172getParams);
	else //normal ROM get
		prg32initGet8(addr);
}

void m0_initSet8(uint16_t addr)
{
	if(p32c8_usesPrgRAM)
		prgRAM8initSet8(addr);
}

static void m3_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0(val<<13);
}
void m3_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m3_setParams);
}

static void m7_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val & (1<<4))
		ppuSetNameTblSingleUpper();
	else
		ppuSetNameTblSingleLower();
	prg32setBank0((val & 7)<<15);
}
void m7_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m7_setParams);
}

static void m11_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg32setBank0((val & 3)<<15);
	chr8setBank0((val >> 4)<<13);
}
void m11_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m11_setParams);
}

static void m36_setParams41X0(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	if(m36.mode == 0)
	{
		if(m36.invert == 0) m36.reg = m36.input&3;
		else m36.reg = (~m36.input)&3;
	}
	else m36.reg = (m36.reg+1)&3;
}
static void m36_setParams41X1(uint16_t addr, uint8_t val) { (void)addr; m36.invert = (val>>4)&1; }
static void m36_setParams41X2(uint16_t addr, uint8_t val) { (void)addr; m36.input = (val>>4)&3; }
static void m36_setParams41X3(uint16_t addr, uint8_t val) { (void)addr; m36.mode = (val>>4)&1; }
static void m36_setParams42XX(uint16_t addr, uint8_t val) { (void)addr; chr8setBank0((val & 0xF)<<13); }
static void m36_setParams41X0_42XX(uint16_t addr, uint8_t val) { m36_setParams41X0(addr,val); m36_setParams42XX(addr,val); }
static void m36_setParams41X1_42XX(uint16_t addr, uint8_t val) { m36_setParams41X1(addr,val); m36_setParams42XX(addr,val); }
static void m36_setParams41X2_42XX(uint16_t addr, uint8_t val) { m36_setParams41X2(addr,val); m36_setParams42XX(addr,val); }
static void m36_setParams41X3_42XX(uint16_t addr, uint8_t val) { m36_setParams41X3(addr,val); m36_setParams42XX(addr,val); }
static void m36_setParams8XXX(uint16_t addr, uint8_t val) { (void)addr; (void)val; prg32setBank0((m36.reg&3)<<15); }
void m36_initSet8(uint16_t addr)
{
	uint16_t maskedAddr1 = (addr & 0xE103);
	uint16_t maskedAddr2 = (addr & 0xE200);
	if(maskedAddr2 == 0x4200)
	{
		if(maskedAddr1 == 0x4100) memInitMapperSetPointer(addr, m36_setParams41X0_42XX);
		else if(maskedAddr1 == 0x4101) memInitMapperSetPointer(addr, m36_setParams41X1_42XX);
		else if(maskedAddr1 == 0x4102) memInitMapperSetPointer(addr, m36_setParams41X2_42XX);
		else if(maskedAddr1 == 0x4103) memInitMapperSetPointer(addr, m36_setParams41X3_42XX);
		else //just maskedAddr2 == 0x4200
			memInitMapperSetPointer(addr, m36_setParams42XX);
	}
	else
	{
		if(maskedAddr1 == 0x4100) memInitMapperSetPointer(addr, m36_setParams41X0);
		else if(maskedAddr1 == 0x4101) memInitMapperSetPointer(addr, m36_setParams41X1);
		else if(maskedAddr1 == 0x4102) memInitMapperSetPointer(addr, m36_setParams41X2);
		else if(maskedAddr1 == 0x4103) memInitMapperSetPointer(addr, m36_setParams41X3);
		else if(addr >= 0x8000) memInitMapperSetPointer(addr, m36_setParams8XXX);
	}
}

static void m38_setParams7XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0(((val>>2)&3)<<13);
	prg32setBank0((val & 3)<<15);
}
void m38_initSet8(uint16_t addr)
{
	if(addr >= 0x7000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m38_setParams7XXX);
}

void m41_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)val;
	m41_curCHRBank &= 0x7FFF;
	m41_curCHRBank |= (((addr&0x18)>>3)<<15);
	chr8setBank0(m41_curCHRBank);
	prg32setBank0((addr&7)<<15);
	m41_inner = (addr&4) != 0;
	if((addr&0x20) != 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
static void m41_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(m41_inner)
	{
		m41_curCHRBank &= ~0x7FFF;
		m41_curCHRBank |= ((val&3)<<13);
		chr8setBank0(m41_curCHRBank);
	}
}
void m41_initSet8(uint16_t addr)
{
	//printf("m41set8 %04x %02x\n", addr, val);
	if(addr >= 0x6000 && addr < 0x6800)
		memInitMapperSetPointer(addr, m41_setParams6XXX);
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m41_setParams8XXX);
}

static void m46_setParams6XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m46_curPRGBank &= 0xFFFF;
	m46_curPRGBank |= ((val & 0xF)<<16);
	prg32setBank0(m46_curPRGBank);
	m41_curCHRBank &= 0xFFFF;
	m41_curCHRBank |= ((val >> 4)<<16);
	chr8setBank0(m41_curCHRBank);
}
static void m46_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr;
	m46_curPRGBank &= ~0xFFFF;
	m46_curPRGBank |= ((val & 1)<<15);
	prg32setBank0(m46_curPRGBank);
	m41_curCHRBank &= ~0xFFFF;
	m41_curCHRBank |= (((val>>4)&7)<<13);
	chr8setBank0(m41_curCHRBank);
}
void m46_initSet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m46_setParams6XXX);
	else if(addr >= 0x8000)
		memInitMapperSetPointer(addr, m46_setParams8XXX);
}

void m66_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg32setBank0(((val>>4)&3)<<15);
	chr8setBank0((val & 3)<<13);
}
void m66_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m66_setParams);
}

static void m79_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val & 7)<<13);
	prg32setBank0(((val>>3)&1)<<15);
}
void m79_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE100;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m79_setParams);
}

static void m87_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((((val&1)<<1)|((val&2)>>1))<<13);
}
void m87_initSet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m87_setParams);
}

static void m101_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0(val<<13);
}
void m101_initSet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m101_setParams);
}

void m107_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg32setBank0((val>>1)<<15);
	chr8setBank0(val<<13);
}
void m107_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m107_setParams);
}

static void m113_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((((val>>3)&8)|(val&7))<<13);
	prg32setBank0(((val>>3)&7)<<15);
	if((val&(1<<7)) == 0)
		ppuSetNameTblHorizontal();
	else
		ppuSetNameTblVertical();
}
void m113_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE100;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m113_setParams);
}

static void m132_setParams4100(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	if(m36.mode == 0)
	{
		if(m36.invert) //reverse of the get
			m36.reg = (m36.input&8)|((m36.input^7)&7);
		else m36.reg = (m36.input&0xF);
	} //special reg increase
	else m36.reg = (m36.reg&8)|((m36.reg+1)&7);
}
static void m132_setParams4101(uint16_t addr, uint8_t val) { (void)addr; m36.invert = val&1; }
static void m132_setParams4102(uint16_t addr, uint8_t val) { (void)addr; m36.input = val&0xF; }
static void m132_setParams4103(uint16_t addr, uint8_t val) { (void)addr; m36.mode = val&1; }
static void m132_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	chr8setBank0((m36.reg&3)<<13);
	prg32setBank0(((m36.reg>>2)&1)<<15);
}
void m132_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE103;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m132_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m132_setParams4101);
	else if(proc_addr == 0x4102) memInitMapperSetPointer(ori_addr, m132_setParams4102);
	else if(proc_addr == 0x4103) memInitMapperSetPointer(ori_addr, m132_setParams4103);
	else if(ori_addr >= 0x8000) memInitMapperSetPointer(ori_addr, m132_setParams8XXX);
}

static void m133_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val & 3)<<13);
	prg32setBank0(((val>>2)&1)<<15);
}
void m133_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE100;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m133_setParams);
}

static void m136_setParams4100(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	if(m36.mode == 0)
	{
		if(m36.invert) //reverse of the get
			m36.reg = (m36.input&0x30)|((m36.input^0xF)&0xF);
		else m36.reg = (m36.input&0x3F);
	} //special reg increase
	else m36.reg = (m36.reg&0x30)|((m36.reg+1)&0xF);
}
static void m136_setParams4101(uint16_t addr, uint8_t val) { (void)addr; m36.invert = val&1; }
static void m136_setParams4102(uint16_t addr, uint8_t val) { (void)addr; m36.input = val&0x3F; }
static void m136_setParams4103(uint16_t addr, uint8_t val) { (void)addr; m36.mode = val&1; }
static void m136_setParams8XXX(uint16_t addr, uint8_t val) { (void)addr; (void)val; chr8setBank0((m36.reg&3)<<13); }
void m136_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE103;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m136_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m136_setParams4101);
	else if(proc_addr == 0x4102) memInitMapperSetPointer(ori_addr, m136_setParams4102);
	else if(proc_addr == 0x4103) memInitMapperSetPointer(ori_addr, m136_setParams4103);
	else if(ori_addr >= 0x8000) memInitMapperSetPointer(ori_addr, m136_setParams8XXX);
}

static void m140_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val & 0xF)<<13);
	prg32setBank0(((val>>4)&3)<<15);
}
void m140_initSet8(uint16_t addr)
{
	if(addr >= 0x6000 && addr < 0x8000)
		memInitMapperSetPointer(addr, m140_setParams);
}

static void m144_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	prg32setBank0((val & 3)<<15);
	chr8setBank0((val >> 4)<<13);
}
void m144_initSet8(uint16_t addr)
{
	if(addr <= 0x8000) return; //ignore 0x8000
	memInitMapperSetPointer(addr, m144_setParams);
}

static void m145_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val>>7)<<13);
}
void m145_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE100;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m145_setParams);
}

static void m147_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0(((val>>3)&0xF)<<13);
	prg32setBank0((((val>>6)&2)|((val>>2)&1))<<15);
}
void m147_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0x4103;
	if(proc_addr == 0x4102) memInitMapperSetPointer(ori_addr, m147_setParams);
}

static void m148_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val & 7)<<13);
	prg32setBank0(((val>>3)&1)<<15);
}
void m148_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m148_setParams);
}

void m149_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	//uses mapper 145 chr set type
	memInitMapperSetPointer(addr, m145_setParams);
}

//again identical to 136, just the data bits get reversed
static void m172_setParams4100(uint16_t addr, uint8_t val) { m136_setParams4100(addr, m172doBitRev(val)); }
static void m172_setParams4101(uint16_t addr, uint8_t val) { m136_setParams4101(addr, m172doBitRev(val)); }
static void m172_setParams4102(uint16_t addr, uint8_t val) { m136_setParams4102(addr, m172doBitRev(val)); }
static void m172_setParams4103(uint16_t addr, uint8_t val) { m136_setParams4103(addr, m172doBitRev(val)); }
static void m172_setParams8XXX(uint16_t addr, uint8_t val)
{
	m136_setParams8XXX(addr,m172doBitRev(val));
	//actually something different to m136
	if(m36.invert)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}
void m172_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE103;
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m172_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m172_setParams4101);
	else if(proc_addr == 0x4102) memInitMapperSetPointer(ori_addr, m172_setParams4102);
	else if(proc_addr == 0x4103) memInitMapperSetPointer(ori_addr, m172_setParams4103);
	else if(ori_addr >= 0x8000) memInitMapperSetPointer(ori_addr, m172_setParams8XXX);
}

static void m173_setParams8XXX(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	chr8setBank0( ( (m36.reg&1) | (((~m36.invert)&1)<<1) ) <<13 );
}
void m173_initSet8(uint16_t ori_addr)
{
	uint16_t proc_addr = ori_addr&0xE103;
	//all the 41.. writes are identical to 132, only the 8... write is different
	if(proc_addr == 0x4100) memInitMapperSetPointer(ori_addr, m132_setParams4100);
	else if(proc_addr == 0x4101) memInitMapperSetPointer(ori_addr, m132_setParams4101);
	else if(proc_addr == 0x4102) memInitMapperSetPointer(ori_addr, m132_setParams4102);
	else if(proc_addr == 0x4103) memInitMapperSetPointer(ori_addr, m132_setParams4103);
	else if(ori_addr >= 0x8000) memInitMapperSetPointer(ori_addr, m173_setParams8XXX);
}

static void m185_setParams(uint16_t addr, uint8_t val)
{
	(void)addr; (void)val;
	m185_CHRDisable ^= true;
	uint16_t chraddr;
	for(chraddr = 0; chraddr < 0x2000; chraddr++)
		m185_initPPUGet8(chraddr);
}
void m185_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m185_setParams);
}

static void m201_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	chr8setBank0((addr&0xFF)<<13);
	prg32setBank0((addr&0xFF)<<15);
}
void m201_initSet8(uint16_t addr)
{
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m201_setParams);
}

static void m240_setParams(uint16_t addr, uint8_t val)
{
	(void)addr;
	chr8setBank0((val & 0xF)<<13);
	prg32setBank0((val >> 4)<<15);
}
void m240_initSet8(uint16_t addr)
{
	if(addr >= 0x4020 && addr < 0x6000)
		memInitMapperSetPointer(addr, m240_setParams);
	if(p32c8_usesPrgRAM)
		prgRAM8initSet8(addr);
}

void m242_setParams(uint16_t addr, uint8_t val)
{
	(void)val;
	prg32setBank0(((addr>>3)&0xF)<<15);
	if((addr&2) == 0)
		ppuSetNameTblVertical();
	else
		ppuSetNameTblHorizontal();
}
void m242_initSet8(uint16_t addr)
{
	if(p32c8_usesPrgRAM)
		prgRAM8initSet8(addr);
	if(addr < 0x8000) return;
	memInitMapperSetPointer(addr, m242_setParams);
}

static uint8_t m185_chrGetGarbage(uint16_t addr) { (void)addr; return 1; }
void m185_initPPUGet8(uint16_t addr)
{
	if(addr >= 0x2000) return;
	if(m185_CHRDisable)
		memInitMapperPPUGetPointer(addr, m185_chrGetGarbage);
	else
		chr8initPPUGet8(addr);
}

void m41_reset()
{
	m41_inner = false;
	prg32setBank0(0);
	m41_curCHRBank = 0;
	chr8setBank0(0);
	ppuSetNameTblVertical();
}

void m46_reset()
{
	m46_curPRGBank = 0;
	prg32setBank0(0);
	//also uses m41 chr
	m41_curCHRBank = 0;
	chr8setBank0(0);
}

void m242_reset()
{
	prg32setBank0(0);
}
