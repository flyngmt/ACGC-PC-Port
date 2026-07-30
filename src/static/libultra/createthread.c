#include "libultra/libultra.h"
#include "libultra/osThread.h"
#include "_mem.h"

void osCreateThread2(OSThread* t, OSId id, void(*entry)(void*), void* arg, void* stack_pointer, size_t stack_size, OSPriority priority){

#ifdef TARGET_PC
    memset((void*)((uintptr_t)stack_pointer - stack_size), 0xfd, stack_size);
#else
    memset((void*)((int)stack_pointer - stack_size),0xfd, stack_size);
#endif

    OSCreateThread(t, (void*)entry, arg, stack_pointer, stack_size, (0x1f - priority), 1);
} 
