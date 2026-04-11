/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _mem_h_
#define _mem_h_

void memInit();
void memInitGetSetPointers();
void memInitMapperGetPointer(uint16_t addr, get8FuncT func);
void memInitMapperSetPointer(uint16_t addr, set8FuncT func);
void memInitMapperPPUGetPointer(uint16_t addr, get8FuncT func);
void memInitMapperPPUSetPointer(uint16_t addr, set8FuncT func);
uint8_t memGet8(uint16_t addr);
void memSet8(uint16_t addr, uint8_t val);
uint8_t memPPUGet8(uint16_t addr);
void memPPUSet8(uint16_t addr, uint8_t val);
void memDumpMainMem();

#endif