#ifndef ACGC_PC_DOLPHIN_OS_H
#define ACGC_PC_DOLPHIN_OS_H

#include_next <dolphin/os.h>

#ifndef OS_CONSOLE_DEV_MASK
#define OS_CONSOLE_DEV_MASK OS_CONSOLE_DEVELOPMENT
#endif
#ifndef OS_CONSOLE_IS_DEV
#define OS_CONSOLE_IS_DEV() ((OSGetConsoleType() & OS_CONSOLE_DEV_MASK) != 0)
#endif
#ifndef OSErrorLine
#define OSErrorLine(line, ...) OSPanic(__FILE__, line, __VA_ARGS__)
#endif

#endif
