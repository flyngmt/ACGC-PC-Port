/*
 * Copyright (C) 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
 
#ifndef _COMMON_H_
#define _COMMON_H_

void prg4init(uint8_t *prgROM, uint32_t prgROMsize);
void prg4initGet8(uint16_t addr);
void prg4setBank0(uint32_t val);
void prg4setBank1(uint32_t val);
void prg4setBank2(uint32_t val);
void prg4setBank3(uint32_t val);
void prg4setBank4(uint32_t val);
void prg4setBank5(uint32_t val);
void prg4setBank6(uint32_t val);
void prg4setBank7(uint32_t val);

void prg8init(uint8_t *prgROM, uint32_t prgROMsize);
void prg8initGet8(uint16_t addr);
void prg8setBank0(uint32_t val);
void prg8setBank1(uint32_t val);
void prg8setBank2(uint32_t val);
void prg8setBank3(uint32_t val);

void prg16init(uint8_t *prgROM, uint32_t prgROMsize);
void prg16initGet8(uint16_t addr);
void prg16setBank0(uint32_t val);
void prg16setBank1(uint32_t val);

void prg32init(uint8_t *prgROM, uint32_t prgROMsize);
void prg32initGet8(uint16_t addr);
void prg32setBank0(uint32_t val);



void prgRAM8init(uint8_t *prgRAM);
void prgRAM8initGet8(uint16_t addr);
void prgRAM8initSet8(uint16_t addr);



void chr1init(uint8_t *chrROM, uint32_t chrROMsize);
void chr1initPPUGet8(uint16_t addr);
void chr1initPPUSet8(uint16_t addr);
void chr1setBank0(uint32_t val);
void chr1setBank1(uint32_t val);
void chr1setBank2(uint32_t val);
void chr1setBank3(uint32_t val);
void chr1setBank4(uint32_t val);
void chr1setBank5(uint32_t val);
void chr1setBank6(uint32_t val);
void chr1setBank7(uint32_t val);

void chr2init(uint8_t *chrROM, uint32_t chrROMsize);
void chr2initPPUGet8(uint16_t addr);
void chr2initPPUSet8(uint16_t addr);
void chr2setBank0(uint32_t val);
void chr2setBank1(uint32_t val);
void chr2setBank2(uint32_t val);
void chr2setBank3(uint32_t val);

void chr4init(uint8_t *chrROM, uint32_t chrROMsize);
void chr4initPPUGet8(uint16_t addr);
void chr4initPPUSet8(uint16_t addr);
void chr4setBank0(uint32_t val);
void chr4setBank1(uint32_t val);

void chr8init(uint8_t *chrROM, uint32_t chrROMsize);
void chr8initPPUGet8(uint16_t addr);
void chr8initPPUSet8(uint16_t addr);
void chr8setBank0(uint32_t val);

#endif
