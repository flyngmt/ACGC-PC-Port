/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _mapper_h_
#define _mapper_h_

typedef void (*initFuncT)(uint8_t*, uint32_t, uint8_t*, uint32_t, uint8_t*, uint32_t);
typedef void (*initGet8FuncT)(uint16_t);
typedef void (*initSet8FuncT)(uint16_t);
typedef void (*initPPUGet8FuncT)(uint16_t);
typedef void (*initPPUSet8FuncT)(uint16_t);
typedef uint8_t (*get8FuncT)(uint16_t);
typedef void (*set8FuncT)(uint16_t, uint8_t);
typedef void (*cycleFuncT)();
typedef void (*resetFuncT)();

bool mapperInit(uint8_t mapper, uint8_t *prgROM, uint32_t prgROMsize, uint8_t *prgRAM, uint32_t prgRAMsize, uint8_t *chrROM, uint32_t chrROMsize);
bool mapperInitNSF(uint8_t *nsfBIN, uint32_t nsfBINsize, uint8_t *prgRAM, uint32_t prgRAMsize);
bool mapperInitFDS(uint8_t *fdsFile, bool fdsSideB, uint8_t *prgRAM, uint32_t prgRAMsize);
uint32_t mapperGetAndValue(uint32_t v);

extern cycleFuncT mapperCycle;
extern resetFuncT mapperReset;
extern uint8_t mapperChrMode;

#endif
