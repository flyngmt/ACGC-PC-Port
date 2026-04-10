/* pc_aram.c - GC's 16MB auxiliary RAM, replaced with a malloc'd buffer */
#include "pc_platform.h"

static u8* aram_base = NULL;
static u32 aram_alloc_ptr = 0;

u32 ARInit(u32* stack_idx_addr, u32 length) {
    (void)stack_idx_addr; (void)length;
    if (!aram_base) {
        aram_base = (u8*)malloc(PC_ARAM_SIZE);
        if (aram_base) {
            memset(aram_base, 0, PC_ARAM_SIZE);
        }
        aram_alloc_ptr = 0;
    }
    return 0; /* offset-based, base is always 0 */
}

u8* pc_aram_get_base(void) { return aram_base; }

u32 ARGetBaseAddress(void) { return 0; }
u32 ARGetSize(void) { return PC_ARAM_SIZE; }

u32 ARAlloc(u32 size) {
    u32 aligned_size = (size + 31) & ~31; /* 32-byte align */
    if (aram_alloc_ptr + aligned_size > PC_ARAM_SIZE) {
        fprintf(stderr, "[PC/ARAM] Out of ARAM! Requested %lu, used %lu/%u\n",
                size, aram_alloc_ptr, PC_ARAM_SIZE);
        return 0;
    }
    u32 addr = aram_alloc_ptr;
    aram_alloc_ptr += aligned_size;
    return addr;
}

void ARFree(u32* addr) {
    (void)addr; /* bump allocator, no-op */
}

/* type 0 = MRAM→ARAM, type 1 = ARAM→MRAM. params are always (type, mram, aram). */
void ARStartDMA(u32 type, uintptr_t mram_addr, u32 aram_addr, u32 length) {
    if (!aram_base) return;

    /* some code passes (aram_base + offset) instead of just the offset */
    uintptr_t base = (uintptr_t)aram_base;
    if (aram_addr >= base && aram_addr < base + PC_ARAM_SIZE) {
        aram_addr -= (u32)base;
    }

    if (length > PC_ARAM_SIZE || aram_addr > PC_ARAM_SIZE - length) {
        /* OOB read: zero-fill dest so caller doesn't get garbage (cap 1MB) */
        if (type == 1 && mram_addr != 0 && length > 0 && length <= 0x100000) {
            memset((void*)mram_addr, 0, length);
        }
        return;
    }

    if (type == 0) {
        memcpy(aram_base + aram_addr, (void*)mram_addr, length);
    } else {
        memcpy((void*)mram_addr, aram_base + aram_addr, length);
    }
}

u32 ARGetInternalSize(void) { return PC_ARAM_SIZE; }
BOOL ARCheckInit(void) { return aram_base != NULL; }

/* ARQ - synchronous wrapper around ARStartDMA.
 * ARQPostRequest's source/dest order differs from ARStartDMA's, so we remap. */
void ARQInit(void) {}
void ARQPostRequest(void* req, u32 owner, u32 type, u32 prio,
                    uintptr_t source, uintptr_t dest, u32 length, void* callback) {
    if (type == 0) {
        ARStartDMA(type, source, (u32)dest, length); /* source=mram, dest=aram */
    } else {
        ARStartDMA(type, dest, (u32)source, length); /* source=aram, dest=mram — swapped */
    }
    if (callback) ((void (*)(uintptr_t))callback)((uintptr_t)req);
}

void ARQFlushQueue(void) {}
