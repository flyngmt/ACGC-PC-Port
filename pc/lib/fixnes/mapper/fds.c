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
#include "../cpu.h"
#include "../input.h"
#include "../mapper.h"
#include "../mem.h"
#include "../audio_fds.h"
#include "../mapper_h/common.h"

bool fdsSwitch;

static struct {
	uint8_t *BIOS;
	uint8_t *File;
	uint8_t *prgRAM;
	uint32_t BIOSsize;
	uint32_t FileLoc;
	uint32_t prgRAMsize;
	bool irq_enable;
	bool transfer_irq_enable;
	bool disk_ready;
	bool transfer_done;
	bool data_read;
	bool cur_data_read;
	bool has_disk_sideB;
	bool disk_sideB;
	bool crc_check;
	bool disk_start;
	bool disk_active;
	uint8_t transfer_val;
	uint8_t switch_delay;
	uint16_t irq_timer;
	uint16_t cur_irq_timer;
	uint16_t transfer_timer;
	uint16_t disk_position;
	uint32_t disk_ready_timer;
} fds;

extern uint8_t interrupt;

static void fdsLoadDisk(bool req_side_b)
{
	if(req_side_b)
		fds.FileLoc = 0x10000;
	else
		fds.FileLoc = 0;
	fds.disk_sideB = req_side_b;
	fds.disk_ready = false;
	//give it 1 second to get ready
	fds.disk_ready_timer = 60*1;
}


void fdsinit(uint8_t *fdsBIOS, uint32_t fdsBIOSsize, uint8_t *fdsFile, bool fdsSideB, uint8_t *prgRAMin, uint32_t prgRAMsizeIn)
{
	fds.BIOS = fdsBIOS;
	fds.BIOSsize = fdsBIOSsize;
	fds.File = fdsFile;
	fds.FileLoc = 0;
	fds.has_disk_sideB = fdsSideB;
	fdsLoadDisk(false);
	fdsSwitch = false;
	//give it another 6 seconds to get ready
	fds.disk_ready_timer += 60*6;
	fds.prgRAM = prgRAMin;
	fds.prgRAMsize = prgRAMsizeIn;
	chr8init(NULL,0); //RAM only
	fds.irq_enable = false;
	fds.transfer_irq_enable = false;
	fds.transfer_done = false;
	fds.data_read = true;
	fds.disk_active = false;
	fds.crc_check = false;
	fds.disk_start = true;
	fds.cur_data_read = false;
	fds.transfer_val = 0;
	fds.switch_delay = 0;
	fds.irq_timer = 0;
	fds.cur_irq_timer = 0;
	fds.transfer_timer = 0;
	fds.disk_position = 0;
	fdsAudioInit();
	printf("FDS Inited\n");
}

static uint8_t fdsGet_4030(uint16_t addr)
{
	(void)addr;
	uint8_t ret = ((!!(interrupt&FDS_IRQ))&1) | ((fds.transfer_done&1)<<1) | (((!fds.disk_active)&1)<<6) | 0x80;
	fds.transfer_done = false;
	interrupt &= ~FDS_IRQ;
	return ret;
}

static uint8_t fdsGet_4031(uint16_t addr)
{
	(void)addr;
	//printf("Returning %02x\n", fds.transfer_val);
	return fds.transfer_val;
}

static uint8_t fdsGet_4032(uint16_t addr)
{
	(void)addr;
	//printf("Returning %02x\n", fds.transfer_val);
	return (((!fds.disk_ready)&1) | ((!fds.disk_active)&1)<<1) | 0x40;
}

static uint8_t fdsGet_4033(uint16_t addr)
{
	(void)addr;
	//battery status
	return 0x80;
}

static uint8_t fdsGetRAM(uint16_t addr)
{
	return fds.prgRAM[addr-0x6000];
}

static uint8_t fdsGetBIOS(uint16_t addr)
{
	return fds.BIOS[addr&0x1FFF];
}

void fdsinitGet8(uint16_t addr)
{
	//printf("fdsget8 %04x\n", addr);
	if(addr < 0x6000)
	{
		/* FDS Disk Regs */
		if(addr == 0x4030)
			memInitMapperGetPointer(addr, fdsGet_4030);
		else if(addr == 0x4031)
			memInitMapperGetPointer(addr, fdsGet_4031);
		else if(addr == 0x4032)
			memInitMapperGetPointer(addr, fdsGet_4032);
		else if(addr == 0x4033)
			memInitMapperGetPointer(addr, fdsGet_4033);
		/* FDS Audio Regs */
		if(addr >= 0x4040 && addr <= 0x407F)
			memInitMapperGetPointer(addr, fdsAudioGetWave);
		else if(addr == 0x4090)
			memInitMapperGetPointer(addr, fdsAudioGetReg90);
		else if(addr == 0x4092)
			memInitMapperGetPointer(addr, fdsAudioGetReg92);
	}
	else //if addr >= 0x6000
	{
		if(addr < 0xE000)
			memInitMapperGetPointer(addr, fdsGetRAM);
		else
			memInitMapperGetPointer(addr, fdsGetBIOS);
	}
}

static void fdsSet_4020(uint16_t addr, uint8_t val)
{
	(void)addr;
	fds.irq_timer = ((fds.irq_timer&~0xFF)|val);
}

static void fdsSet_4021(uint16_t addr, uint8_t val)
{
	(void)addr;
	fds.irq_timer = ((fds.irq_timer&0xFF)|(val<<8));
}

static void fdsSet_4022(uint16_t addr, uint8_t val)
{
	(void)addr;
	fds.irq_enable = ((val&2) != 0);
	if(fds.irq_enable)
		fds.cur_irq_timer = fds.irq_timer;
	else
		fds.cur_irq_timer = 0;
}

static void fdsSet_4024(uint16_t addr, uint8_t val)
{
	(void)addr;
	//fds.transfer_interrupt = false;
	fds.transfer_done = false;
	if(!fds.data_read)
	{
		//printf("Writing %02x\n", val);
		fds.transfer_val = val;
	}
	else
	{
		//printf("Writing nothing\n");
	}
}

static void fdsSet_4025(uint16_t addr, uint8_t val)
{
	(void)addr;
	if(val&2)
	{
		//printf("Resetting disc position\n");
		fds.disk_position = 0;
		fds.disk_start = true;
		fds.crc_check = false;
		fds.disk_active = false;
		fds.transfer_timer = 0;
	}
	else
	{
		fds.disk_active = true;
		if((val&4) == 0)
		{
			if(fds.data_read != false)
			{
				//printf("Write mode\n");
				fds.data_read = false;
				fds.switch_delay = 2;
			}
		}
		else
		{
			if(fds.data_read != true)
			{
				//printf("Read mode\n");
				fds.data_read = true;
			}
		}
		if(val&0x40)
		{
			if(fds.transfer_timer == 0)
				fds.transfer_timer = 145;
		}
		else
			fds.transfer_timer = 0;
	}
	if((val&8) == 0)
	{
		//printf("Vertical mode\n");
		ppuSetNameTblVertical();
	}
	else
	{
		//printf("Horizontal mode\n");
		ppuSetNameTblHorizontal();
	}
	if(val&0x10 && !fds.data_read)
	{
		if(fds.crc_check != true)
		{
			//printf("In CRC Write check\n");
			fds.disk_position+=2;
		}
		fds.crc_check = true;
	}
	else
	{
		if(fds.crc_check != false)
		{
			//printf("Finished CRC Write check\n");
			fds.transfer_val = fds.File[fds.FileLoc+fds.disk_position];
		}
		fds.crc_check = false;
	}
	if(val&0x80)
		fds.transfer_irq_enable = true;
	else
	{
		fds.transfer_irq_enable = false;
		//fds.transfer_interrupt = false;
	}
}

static void fdsSetRAM(uint16_t addr, uint8_t val)
{
	fds.prgRAM[addr-0x6000] = val;
}

void fdsinitSet8(uint16_t addr)
{
	//printf("fdsset8 %04x %02x\n", addr, val);
	/* FDS Disk Regs */
	if(addr == 0x4020)
		memInitMapperSetPointer(addr, fdsSet_4020);
	else if(addr == 0x4021)
		memInitMapperSetPointer(addr, fdsSet_4021);
	else if(addr == 0x4022)
		memInitMapperSetPointer(addr, fdsSet_4022);
	else if(addr == 0x4024)
		memInitMapperSetPointer(addr, fdsSet_4024);
	else if(addr == 0x4025)
		memInitMapperSetPointer(addr, fdsSet_4025);
	/* FDS Audio Regs */
	if(addr >= 0x4040 && addr <= 0x407F)
		memInitMapperSetPointer(addr, fdsAudioSetWave);
	else if(addr >= 0x4080 && addr <= 0x408A)
		memInitMapperSetPointer(addr, fdsAudioSet8);
	/* FDS RAM */
	if(addr >= 0x6000 && addr < 0xE000)
		memInitMapperSetPointer(addr, fdsSetRAM);
}

void fdscycle()
{
	fdsAudioClockTimers();
	if(fds.cur_irq_timer == 1)
	{
		if(fds.irq_enable)
			interrupt |= FDS_IRQ;
		fds.cur_irq_timer = 0;
	}
	else if(fds.cur_irq_timer > 1)
		fds.cur_irq_timer--;

	if(!fds.disk_active || fds.crc_check)
		return;

	if(fds.transfer_timer == 1)
	{
		if(fds.switch_delay == 0)
		{
			if(!fds.disk_start)
				fds.disk_position++;
			//printf("Transfer done, giving pos %04x\n", fds.disk_position);
			if(fds.data_read)
				fds.transfer_val = fds.File[fds.FileLoc+fds.disk_position];
			else
				fds.File[fds.FileLoc+fds.disk_position] = fds.transfer_val;
		}
		else if(fds.switch_delay > 0)
			fds.switch_delay--;
		fds.transfer_done = true;
		fds.transfer_timer = 145;
		interrupt |= FDS_TRANSFER_IRQ;
		fds.disk_start = false;
	}
	else if(fds.transfer_timer > 1)
		fds.transfer_timer--;
}

void fdsupdatedisc()
{
	//called right on vsync
	if(fds.disk_ready_timer == 1)
	{
		fds.disk_ready = true;
		fds.disk_ready_timer = 0;
	}
	else if(fds.disk_ready_timer > 1)
		fds.disk_ready_timer--;

	if(fdsSwitch)
	{
		if(fds.has_disk_sideB)
			fdsLoadDisk(!fds.disk_sideB);
		fdsSwitch = false;
	}
}
