#include "dolphin/os/OSArena.h"

static void* __OSArenaLo = (void*) - 1;
static void* __OSArenaHi = NULL;

void* OSGetArenaHi(void) {
	return (__OSArenaHi);
}

void* OSGetArenaLo (void) {
	return (__OSArenaLo);
}

void OSSetArenaHi(void* hi){
	__OSArenaHi = hi;
}

void OSSetArenaLo(void* lo){
	__OSArenaLo = lo;
}