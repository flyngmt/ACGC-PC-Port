/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _cpu_h_
#define _cpu_h_

#include "common.h"

void cpuInit();
void cpuInitNSF(uint16_t addr, uint8_t newA, uint8_t newX);
void cpuStartPlayNSF();
void cpuEndPlayNSF();
void cpuSoftReset();
FIXNES_ALWAYSINLINE bool cpuCycle();
void cpuDoOAM_DMA(uint16_t addr, uint8_t val);
void cpuDoDMC_DMA(uint16_t addr);
bool cpuInDMC_DMA();
uint16_t cpuGetPc();

#define MAPPER_IRQ (1<<0)
#define APU_IRQ (1<<1)
#define DMC_IRQ (1<<2)
#define FDS_IRQ (1<<3)
#define FDS_TRANSFER_IRQ (1<<4)
#define MMC5_DMC_IRQ (1<<5)
#define PPU_NMI (1<<6) //not maskable of course
#define IRQ_MASK (MAPPER_IRQ | APU_IRQ | DMC_IRQ | FDS_IRQ | FDS_TRANSFER_IRQ | MMC5_DMC_IRQ)

#endif
