#ifndef PPC_EABI_INIT_H
#define PPC_EABI_INIT_H

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*voidfunctionptr)(void); // pointer to function returning void
#ifndef TARGET_PC
__declspec(section ".ctors") extern voidfunctionptr _ctors[];
__declspec(section ".dtors") extern voidfunctionptr _dtors[];
#else
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
#endif

/**
 * Linker Generated Symbols
 */

// Declare linker symbols for a section in the ROM
#define DECL_ROM_SECTION(x)                                                    \
    extern u8 _f##x[];                                                         \
    extern u8 _f##x##_rom[];                                                   \
    extern u8 _e##x[];

// Declare linker symbols for a BSS section
#define DECL_BSS_SECTION(x)                                                    \
    extern u8 _f##x[];                                                         \
    extern u8 _e##x[];

// Debugger stack
extern u8 _db_stack_addr[];
extern u8 _db_stack_end[];

// Program arena
extern u8 __ArenaLo[];
extern u8 __ArenaHi[];

// Program stack
extern u8 _stack_addr[];
extern u8 _stack_end[];

// Small data bases
extern u8 _SDA_BASE_[];
extern u8 _SDA2_BASE_[];

// ROM sections
DECL_ROM_SECTION(_init);
DECL_ROM_SECTION(extab);
DECL_ROM_SECTION(extabindex);
DECL_ROM_SECTION(_text);
DECL_ROM_SECTION(_ctors);
DECL_ROM_SECTION(_dtors);
DECL_ROM_SECTION(_rodata);
DECL_ROM_SECTION(_data);
DECL_ROM_SECTION(_sdata);
DECL_ROM_SECTION(_sdata2);
DECL_ROM_SECTION(_stack);

// BSS sections
DECL_BSS_SECTION(_bss);
DECL_BSS_SECTION(_sbss);
DECL_BSS_SECTION(_sbss2);

void __init_hardware(void);
void __flush_cache(void*, size_t);
void __init_user(void);
void _ExitProcess(void);

typedef struct RomSection {
    void* romOfs;     // at 0x4
    void* virtualOfs; // at 0x0
    size_t size;      // at 0x8
} RomSection;

typedef struct BssSection {
    void* virtualOfs; // at 0x0
    size_t size;      // at 0x8
} BssSection;

typedef struct ExtabIndexInfo {
    void* etiStart;  // at 0x0
    void* etiEnd;    // at 0x4
    void* codeStart; // at 0x8
    u32 codeSize;    // at 0x10
} ExtabIndexInfo;

#ifndef TARGET_PC
__declspec(section ".init") extern  RomSection _rom_copy_info[];
__declspec(section ".init") extern  BssSection _bss_init_info[];
__declspec(section ".init") extern  ExtabIndexInfo _eti_init_info[];
#else
extern RomSection _rom_copy_info[];
extern BssSection _bss_init_info[];
extern ExtabIndexInfo _eti_init_info[];
#endif

#ifdef __cplusplus
}
#endif
#endif
