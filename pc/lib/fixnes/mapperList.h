/*
 * Copyright (C) 2017 - 2018 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#ifndef _MAPPERLIST_H_
#define _MAPPERLIST_H_

typedef struct _mapperList_t {
	initFuncT initF;
	initGet8FuncT initGet8F;
	initSet8FuncT initSet8F;
	initPPUGet8FuncT initPPUGet8F;
	initPPUSet8FuncT initPPUSet8F;
	cycleFuncT cycleFuncF;
	resetFuncT resetFuncF;
} mapperList_t;

extern mapperList_t mapperList[256];

#endif
