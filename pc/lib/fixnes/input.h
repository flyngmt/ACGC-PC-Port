/*
 * Copyright (C) 2017 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#define BUTTON_A        0
#define BUTTON_B        1
#define BUTTON_SELECT   2
#define BUTTON_START    3
#define BUTTON_UP       4
#define BUTTON_DOWN     5
#define BUTTON_LEFT     6
#define BUTTON_RIGHT    7

void inputInit();
uint8_t inputGetP1(uint16_t addr);
uint8_t inputGetP2(uint16_t addr);
void inputSet(uint16_t addr, uint8_t in);

#endif
