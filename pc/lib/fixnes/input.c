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
#include "input.h"

//used externally by main.c
uint8_t inValReads[8];
uint8_t inPollMode = 0;
uint8_t inPos = 0;

#define DEBUG_INPUT 0

void inputInit()
{
	memset(inValReads, 0, 8);
}

void inputSet(uint16_t addr, uint8_t in)
{
	(void)addr;
	inPollMode = in;
	#if DEBUG_INPUT
	printf("Set %02x\n",in);
	#endif
	if(!(in&1))
		inPos = 0;
}

extern uint8_t memLastVal;
uint8_t inputGetP1(uint16_t addr)
{
	(void)addr;
	uint8_t ret = 1;
	if(inPollMode&1)
		ret = inValReads[BUTTON_A];
	else if(inPos < 8)
	{
		if((inPos == BUTTON_DOWN && inValReads[BUTTON_UP]) || (inPos == BUTTON_RIGHT && inValReads[BUTTON_LEFT]))
			ret = 0; //dont allow up+down/left+right
		else
			ret = inValReads[inPos];
		#if DEBUG_INPUT
		printf("%d:%d\n",ret,inPos);
		#endif
		inPos++;
	}
	else
	{
		#if DEBUG_INPUT
		printf("keeps reading\n");
		#endif
	}
	return (memLastVal&(~0x1F))|(ret&1);
}

extern uint8_t memLastVal;
uint8_t inputGetP2(uint16_t addr)
{
	(void)addr;
	//no player 2 set up yet
	return (memLastVal&(~0x1F));
}
