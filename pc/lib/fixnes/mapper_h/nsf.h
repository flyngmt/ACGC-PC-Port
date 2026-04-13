/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef nsf_h_
#define nsf_h_

void nsfinit(uint8_t *nsfBIN, uint32_t nsfBINsize,
			uint8_t *prgRAM, uint32_t prgRAMsize);
void nsfinitGet8(uint16_t addr);
void nsfinitSet8(uint16_t addr);
void nsfcycle();
void nsfVsync();

extern bool nsf_startPlayback;
extern bool nsf_endPlayback;
uint16_t nsfGetPlayAddr();

#endif
