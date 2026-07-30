#include "dolphin/os.h"
#include "dolphin/db.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "dolphin/os/__ppc_eabi_init.h"
#include <libc/stdlib.h>

__declspec(section ".init") void __init_registers(void);
__declspec(section ".init") void __init_data(void);

int main(int argc, char** argv);

__declspec(section ".init") void __check_pad3(void) {
    if ((*(u16*)0x800030E4 & 0xEEF) == 0xEEF) {
        OSResetSystem(0, 0, 0);
    }
}

/* clang-format off */
__declspec(section ".init") asm void __start(void){
    nofralloc

    bl __init_registers
    bl __init_hardware
    li r0, -1
    stwu r1, -8(r1)
    stw r0, 4(r1)
    stw r0, 0(r1)
    bl __init_data
    li r0, 0x0
    lis r6, 0x8000
    addi r6, r6, 0x44
    stw r0, 0(r6)
    lis r6, 0x8000
    addi r6, r6, 0xf4
    lwz r6, 0(r6)
    cmplwi r6, 0
    beq- ar
    lwz r7, 0xc(r6)
    b h

ar:
    lis r5, 0x8000
    addi r5, r5, 0x34
    lwz r5, 0(r5)
    cmplwi r5, 0
    beq- d
    lis r7, 0x8000
    addi r7, r7, 0x30E8
    lwz r7, 0(r7)
h:
    li r5, 0x0
    cmplwi r7, 2
    beq met
    cmplwi r7, 3
    bne- d
    li r5, 0x1
met:
    lis r6, InitMetroTRK@ha
    addi r6, r6, InitMetroTRK@l
    mtlr r6
    blrl
d:
    lis r6, 0x8000
    addi r6, r6, 0xF4
    lwz r5, 0(r6)
    cmplwi r5, 0
    beq+ res
    lwz r6, 8(r5)
    cmplwi r6, 0
    beq+ res
    add r6, r5, r6
    lwz r14, 0(r6)
    cmplwi r14, 0
    beq- res
    addi r15, r6, 0x4
    mtctr r14

loop:
    addi r6, r6, 0x4
    lwz r7, 0(r6)
    add r7, r7, r5
    stw r7, 0(r6)
    bdnz loop
    lis r5, 0x8000
    addi r5, r5, 0x34
    rlwinm r7, r15, 0, 0, 0x1A
    stw r7, 0(r5)
    b  indeb
res:
    li r14, 0x0
    li r15, 0x0
indeb:
    bl DBInit
    bl OSInit
    lis r4, 0x8000
    addi r4, r4, 0x30E6
    lhz r3, 0(r4)
    andi. r5, r3, 0x8000
    beq- check
    andi. r3, r3, 0x7FFF
    cmplwi r3, 1
    bne- user

check:
    bl __check_pad3
user:
    bl __init_user
    mr r3, r14
    mr r4, r15
    bl main // can't find the dol main, because there's one main in dol and then one in rel
    b exit
}

__declspec(section ".init") asm void __init_registers(void){
    nofralloc
    lis r1, _stack_addr@h
    ori r1, r1, _stack_addr@l
    lis r2, _SDA2_BASE_@h
    ori r2, r2, _SDA2_BASE_@l
    lis r13, _SDA_BASE_@h
    ori r13, r13, _SDA_BASE_@l
    blr
}
/* clang-format on */

inline void __copy_rom_section(void* dst, const void* src, size_t size) {
    if (size && (dst != src)) {
        memcpy(dst, src, size);
        __flush_cache(dst, size);
    }
}

inline void __init_bss_section(void* dst, size_t size) {
    if (size) {
        memset(dst, 0, size);
    }
}

__declspec(section ".init") static void __init_data(void) {
    RomSection* rs;
    BssSection* bs;

    rs = _rom_copy_info;
    while (1) {
        if (rs->size == 0) {
            break;
        }

        __copy_rom_section(rs->virtualOfs, rs->romOfs, rs->size);
        rs++;
    }

    bs = _bss_init_info;
    while (1) {
        if (bs->size == 0) {
            break;
        }

        __init_bss_section(bs->virtualOfs, bs->size);
        bs++;
    }
}
