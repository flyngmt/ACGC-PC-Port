#include "libc64/__osMalloc.h"

#include <dolphin/os.h>
#include "libultra/libultra.h"
#include "terminal.h"

#define OS_MALLOC_MAGIC (s16)'ss' // magic number for an OSMemBlock
#define OS_MALLOC_BLOCK_OK(block) ((block) != NULL && (block)->magic == OS_MALLOC_MAGIC) // check if OSMemBlock structure is OK
#define OS_MALLOC_DATA2BLOCK(data) ((OSMemBlock*)((uintptr_t)(data) - sizeof(OSMemBlock))) // get memblock data pointer from OSMemBlock
#define OS_MALLOC_BLOCK2DATA(block) ((u8*)(block) + sizeof(OSMemBlock)) // get OSMemBlock pointer from data

// Gets the pointer to the next OSMemBlock immediately following this block in RAM, may or may not be a valid OSMemBlock
#define OS_MALLOC_NEXTMEMBLOCK(block) ((OSMemBlock*)((uintptr_t)(block) + sizeof(OSMemBlock) + (block)->size))

int __osMalloc_FreeBlockTest_Enable = FALSE;

static void setDebugInfo(OSMemBlock* block, const char* file, s32 line, OSArena* arena) {
    block->file = file;
    block->line = line;
    block->threadId = osGetThreadId(NULL);
    block->arena = arena;
    block->time = osGetTime();
}

static void arena_lock_init(OSArena* arena) {
    static OSMesg arena_lock_msg;

    osCreateMesgQueue(&arena->lockQueue, &arena_lock_msg, OS_MESG_BLOCK);
}

static void arena_lock(OSArena* arena) {
    osSendMesg(&arena->lockQueue, NULL, OS_MESG_BLOCK);
}

static void arena_unlock(OSArena* arena) {
    osRecvMesg(&arena->lockQueue, NULL, OS_MESG_BLOCK);
}

static OSMemBlock* get_block_next(OSMemBlock* block) {
    if (block->next != NULL && !OS_MALLOC_BLOCK_OK(block->next)) {
        // Emergency! Memory leak discovered!
        OSReport(VT_COL(RED, WHITE) "緊急事態！メモリリーク発見！ (block=%08x)\n" VT_RST, block->next);
        OSPanic(__FILE__, 133, "");
        block->next = NULL; // @BUG - OSPanic halts CPU execution, this is pointless
    }

    return block->next;
}

static OSMemBlock* get_block_prev(OSMemBlock* block) {
    // @BUG - this shouldn't check for block->prev != NULL
    if (block->prev != NULL && !OS_MALLOC_BLOCK_OK(block->prev)) {
        // Emergency! Memory leak discovered!
        OSReport(VT_COL(RED, WHITE) "緊急事態！メモリリーク発見！ (block=%08x)\n" VT_RST, block->prev);
        OSPanic(__FILE__, 144, "");
        block->prev = NULL; // @BUG - OSPanic halts CPU execution, this is pointless
    }

    return block->prev;
}

static OSMemBlock* search_last_block(OSArena* arena) {
    OSMemBlock* block = NULL;

    if (arena != NULL) {
        OSMemBlock* current = arena->head;

        if (OS_MALLOC_BLOCK_OK(current)) {
            while (current != NULL) {
                block = current;
                current = get_block_next(current);
            }
        }
    }

    return block;
}

extern void __osMallocInit(OSArena* arena, u8* base, s32 size) {
    bzero(arena, sizeof(OSArena));
    arena_lock_init(arena);
    __osMallocAddBlock(arena, base, size);
    arena->initialized = TRUE;
}

extern void __osMallocAddBlock(OSArena* arena, u8* base, s32 size) {
    s32 align_size;
    OSMemBlock* block;
    OSMemBlock* last;
    
    if (base != NULL) {
        block = (OSMemBlock*)ALIGN_NEXT((uintptr_t)base, 32);
        align_size = ALIGN_PREV(size - ((uintptr_t)block - (uintptr_t)base), 32);

        if (align_size > (int)sizeof(OSMemBlock)) {
            memset(block, 0xAB, align_size);
            block->next = NULL;
            block->prev = NULL;
            block->size = align_size - sizeof(OSMemBlock);
            block->free = TRUE;
            block->magic = OS_MALLOC_MAGIC;
            
            arena_lock(arena);
            last = search_last_block(arena);
            if (last == NULL) {
                arena->head = block;
                arena->base = base;
            } else {
                block->prev = last;
                last->next = block;
            }
            arena_unlock(arena);
        }
    }
}

static void destroy_all_block(OSArena* arena) {
    OSMemBlock* block;
    OSMemBlock* next;
    
    arena_lock(arena);
    block = arena->head;
    while (block != NULL) {
        next = get_block_next(block);
        memset(block, 0xAB, block->size + sizeof(OSMemBlock));
        block = next;
    }
    arena_unlock(arena);
}

extern void __osMallocCleanup(OSArena* arena) {
    destroy_all_block(arena);
    bzero(arena, sizeof(OSArena));
}

extern BOOL __osMallocIsInitalized(OSArena* arena) {
    return arena->initialized;
}

static void __osMalloc_FreeBlockTest(OSArena* arena, OSMemBlock* block) {
    if (__osMalloc_FreeBlockTest_Enable) {
        u32* s = (u32*)(OS_MALLOC_BLOCK2DATA(block));
        u32* e = (u32*)(OS_MALLOC_BLOCK2DATA(block) + block->size);
        u32* p;

        for (p = s; p < e; p++) {
            u32 v = *p;

            if (v != 0xABABABAB && v != 0xEFEFEFEF) {
                // Emergency! Memory leak detected!
                OSReport(VT_COL(RED, WHITE) "緊急事態！メモリリーク検出！ (block=%08x s=%08x e=%08x p=%08x)\n" VT_RST, block, s, e, p);
                __osDisplayArena(arena);
                OSPanic(__FILE__, 300, "");
                break;
            }
        }
    }
}

static void* __osMallocAlign_NoLock(OSArena* arena, u32 size, u32 align) {
    OSMemBlock* aligned_block;
    OSMemBlock* new_next;
    int alignment_bytes;
    OSMemBlock* block;
    u8* data_p = NULL;
    OSMemBlock* next;
    u32 full_size;
    u32 mask;
    int remain;

    size = ALIGN_NEXT(size, 32);
    full_size = ALIGN_NEXT(size, 32) + sizeof(OSMemBlock);

    if (align <= 16) {
        align = 16;
    } else if (align <= 32) {
        align = 32;
    } else if (align <= 64) {
        align = 64;
    } else if (align <= 128) {
        align = 128;
    } else if (align <= 256) {
        align = 256;
    } else if (align <= 1024) {
        align = 1024;
    } else {
        align = 8;
    }

    block = arena->head;
    mask = align - 1;
    while (block != NULL) {
        if (block->free) {
            remain = ((uintptr_t)block +sizeof(OSMemBlock)) & mask;
            alignment_bytes = remain == 0 ? 0 : align - remain;
            aligned_block = (OSMemBlock*)((uintptr_t)block +alignment_bytes);

            if (block->size - alignment_bytes >= size) {
                if (arena->flags & OSArena_FLAG_FREE_BLOCK_TEST) {
                    __osMalloc_FreeBlockTest(arena, block);
                }

                if (block != aligned_block) {
                    memmove(aligned_block, block, sizeof(OSMemBlock));
                    block = aligned_block;
                    block->size -= alignment_bytes;
                    if (block->prev != NULL) {
                        block->prev->next = block;
                        block->prev->size += alignment_bytes; // do not orphan alignment bytes
                    } else {
                        arena->head = block;
                    }

                    if (block->next != NULL) {
                        block->next->prev = block;
                    }
                }

                if (block->size > full_size) {
                    new_next = (OSMemBlock*)((uintptr_t)block +full_size);
                    new_next->next = get_block_next(block);
                    new_next->prev = block;
                    new_next->size = block->size - full_size;
                    new_next->free = TRUE;
                    new_next->magic = OS_MALLOC_MAGIC;
                    block->next = new_next;
                    block->size = size;

                    next = get_block_next(new_next);
                    if (next != NULL) {
                        next->prev = new_next;
                    }
                }

                block->free = FALSE;
                setDebugInfo(block, NULL, 0, arena);
                data_p = OS_MALLOC_BLOCK2DATA(block);
                if (arena->flags & OSArena_FLAG_CLEAR_MEM_ON_ALLOC) {
                    memset(data_p, 0xCD, size);
                }

                break;
            }
        }

        block = get_block_next(block);
    }

    return data_p;
}

static void* __osMalloc_NoLock(OSArena* arena, u32 size) {
    return __osMallocAlign_NoLock(arena, size, 0);
}

extern void* __osMallocAlign(OSArena* arena, u32 size, u32 align) {
    void* ret;
    
    arena_lock(arena);
    ret = __osMallocAlign_NoLock(arena, size, align);
    arena_unlock(arena);
    return ret;
}

extern void* __osMalloc(OSArena* arena, u32 size) {
    return __osMallocAlign(arena, size, 0);
}

extern void* __osMallocR(OSArena* arena, u32 size) {
    OSMemBlock* block;
    OSMemBlock* next;
    OSMemBlock* n;
    u8* ret = NULL;
    u32 full_size;

    size = ALIGN_NEXT(size, 32);
    full_size = ALIGN_NEXT(size, 32) + sizeof(OSMemBlock);
    arena_lock(arena);
    block = search_last_block(arena);
    while (block != NULL) {
        if (block->free && block->size >= size) {
            if (arena->flags & OSArena_FLAG_FREE_BLOCK_TEST) {
                __osMalloc_FreeBlockTest(arena, block);
            }

            if (block->size > full_size) {
                next = (OSMemBlock*)((uintptr_t)block +block->size - size);
                next->next = get_block_next(block);
                next->prev = block;
                next->size = size;
                next->magic = OS_MALLOC_MAGIC;
                block->next = next;
                block->size -= full_size;
                n = get_block_next(next);
                if (n != NULL) {
                    n->prev = next;
                }
                block = next;
            }

            block->free = FALSE;
            setDebugInfo(block, NULL, 0, arena);
            ret = OS_MALLOC_BLOCK2DATA(block);
            if (arena->flags & OSArena_FLAG_CLEAR_MEM_ON_ALLOC) {
                memset(ret, 0xCD, size);
            }

            break;
        }

        block = get_block_prev(block);
    }

    arena_unlock(arena);
    return ret;
}

static void __osFree_NoLock(OSArena* arena, void* ptr) {
    OSMemBlock* block = OS_MALLOC_DATA2BLOCK(ptr);
    OSMemBlock* next;
    OSMemBlock* prev;
    OSMemBlock* temp;

    if (ptr != NULL) {
        if (!OS_MALLOC_BLOCK_OK(block)) {
            OSReport(VT_COL(RED, WHITE) "__osFree:不正解放(%08x)\n" VT_RST, ptr); // __osFree: irregular deallocation
            OSPanic(__FILE__, 738, "");
            return;
        }

        if (block->free) {
            OSReport(VT_COL(RED, WHITE) "__osFree:二重解放(%08x)\n" VT_RST, ptr); // __osFree: double deallocation
            OSPanic(__FILE__, 743, "");
            return;
        }

        if (block->arena != arena && arena != NULL) {
            OSReport(VT_COL(RED, WHITE) "__osFree:確保時と違う方法で解放しようとした (%08x:%08x)\n" VT_RST, arena, block->arena); // __osFree: attempt to release memory in a different arena from where it was allocated
            OSPanic(__FILE__, 750, "");
            return;
        }

        next = get_block_next(block);
        prev = get_block_prev(block);
        block->free = TRUE;
        setDebugInfo(block, NULL, 0, arena);
        if (arena->flags & OSArena_FLAG_CLEAR_MEM_ON_FREE) {
            memset(OS_MALLOC_BLOCK2DATA(block), 0xEF, block->size);
        }

        if (next == OS_MALLOC_NEXTMEMBLOCK(block)) {
            if (next->free) {
                temp = get_block_next(next);
                if (temp != NULL) {
                    temp->prev = block;
                }

                block->size += next->size + sizeof(OSMemBlock);
                if (arena->flags & OSArena_FLAG_CLEAR_MEM_ON_FREE) {
                    memset(next, 0xEF, sizeof(OSMemBlock));
                }
                block->next = temp;
                next = temp;
            }
        }

        if (prev != NULL && prev->free && block == OS_MALLOC_NEXTMEMBLOCK(prev)) {
            if (next != NULL) {
                next->prev = prev;
            }

            prev->next = next;
            prev->size += block->size + sizeof(OSMemBlock);
            if (arena->flags & OSArena_FLAG_CLEAR_MEM_ON_FREE) {
                memset(block, 0xEF, sizeof(OSMemBlock));
            }
        }
    }
}

extern void __osFree(OSArena* arena, void* ptr) {
    arena_lock(arena);
    __osFree_NoLock(arena, ptr);
    arena_unlock(arena);
}

// @fabricated, most likely suspect from DnM+'s symbol map
static void* __osFree_NoLock_DEBUG(OSArena* arena, void* ptr) {
    // __osFree: irregular deallocation
    OSReport(VT_COL(RED, WHITE) "__osFree:不正解放(%08x) [%s:%d ]\n" VT_RST);

    // __osFree: double deallocation
    OSReport(VT_COL(RED, WHITE) "__osFree:二重解放(%08x) [%s:%d ]\n" VT_RST);
}

#pragma force_active on
extern void* __osRealloc(OSArena* arena, void* ptr, u32 size) {
    void* new_ptr;
    OSMemBlock* orig_block;
    OSMemBlock* next;
    OSMemBlock* temp;
    OSMemBlock* new_next;
    u32 full_size;
    u32 need_size;

    orig_block = OS_MALLOC_DATA2BLOCK(ptr);
    size = ALIGN_NEXT(size, 32);
    full_size = ALIGN_NEXT(size, 32) + sizeof(OSMemBlock);

    arena_lock(arena);

    if (ptr == NULL) {
        ptr = __osMalloc_NoLock(arena, size);
    } else if (size == 0) {
        __osFree_NoLock(arena, ptr);
        ptr = NULL;
    } else if (size != orig_block->size) {
        if (size > orig_block->size) {
            next = get_block_next(orig_block);
            need_size = size - orig_block->size;
            if (next == OS_MALLOC_NEXTMEMBLOCK(orig_block) && next->free && next->size >= need_size) {
                OSMemBlock* new_next = (OSMemBlock*)((uintptr_t)next + need_size);
                next->size -= need_size;
                temp = get_block_next(next);
                if (temp != NULL) {
                    temp->prev = new_next;
                }
                orig_block->next = new_next;
                orig_block->size = size;
                memmove(new_next, next, sizeof(OSMemBlock));
            } else {
                new_ptr = __osMalloc_NoLock(arena, size);
                if (new_ptr != NULL) {
                    memmove(new_ptr, ptr, orig_block->size);
                    __osFree_NoLock(arena, ptr);
                }
                ptr = new_ptr;
            }
        } else if (size < orig_block->size) {
            next = get_block_next(orig_block);
            if (next != NULL && next->free) {
                OSMemBlock* new_next = (OSMemBlock*)((u32)orig_block + full_size);
                *new_next = *next;
                new_next->size += orig_block->size - size;
                orig_block->next = new_next;
                orig_block->size = size;
                temp = get_block_next(new_next);
                if (temp != NULL) {
                    temp->prev = new_next;
                }
            } else if (size + sizeof(OSMemBlock) < orig_block->size) {
                new_next = (OSMemBlock*)((u32)orig_block + full_size);
                new_next->next = get_block_next(orig_block);
                new_next->prev = orig_block;
                new_next->size = orig_block->size - full_size;
                new_next->free = TRUE;
                new_next->magic = OS_MALLOC_MAGIC;
                orig_block->next = new_next;
                orig_block->size = size;
                temp = get_block_next(new_next);
                if (temp != NULL) {
                    temp->prev = new_next;
                }
            } else {
                ptr = NULL;
            }
        }
    }

    arena_unlock(arena);
    return ptr;
}
#pragma force_active reset

static int __osAnalyzeArena(OSArena* arena, u32* ptr) {
    OSMemBlock* block;
    u32 max_free_block_size = 0;
    u32 free_blocks_size = 0;
    u32 free_blocks = 0;
    u32 used_blocks_size = 0;
    u32 used_blocks = 0;

    if (arena == NULL || ptr == NULL) {
        return -1;
    }

    arena_lock(arena);

    for (block = arena->head; block != NULL; block = get_block_next(block)) {
        if (block->free) {
            free_blocks++;
            free_blocks_size += block->size;
            if (max_free_block_size < block->size) {
                max_free_block_size = block->size;
            }
        } else {
            used_blocks++;
            used_blocks_size += block->size;
        }
    }

    ptr[0] = max_free_block_size;
    ptr[1] = free_blocks_size;
    ptr[2] = free_blocks;
    ptr[3] = used_blocks_size;
    ptr[4] = used_blocks;

    arena_unlock(arena);
    return 0;
}

extern void __osGetFreeArena(OSArena* arena, u32* max_free_block_size, u32* free_blocks_size, u32* used_blocks_size) {
    u32 data[5];
    
    if (__osAnalyzeArena(arena, data) == 0) {
        if (max_free_block_size != NULL) {
            *max_free_block_size = data[0];
        }

        if (free_blocks_size != NULL) {
            *free_blocks_size = data[1];
        }

        if (used_blocks_size != NULL) {
            *used_blocks_size = data[3];
        }
    }
}

extern u32 __osGetTotalFreeSize(OSArena* arena) {
    u32 total_free_size;

    __osGetFreeArena(arena, NULL, &total_free_size, NULL);
    return total_free_size;
}

#pragma force_active on
extern u32 __osGetFreeSize(OSArena* arena) {
    u32 free_size;

    __osGetFreeArena(arena, &free_size, NULL, NULL);
    return free_size;
}
#pragma force_active reset

extern s32 __osGetMemBlockSize(OSArena* arena, void* ptr) {
    OSMemBlock* block;
    
    if (ptr == NULL) {
        return -1;
    }

    block = OS_MALLOC_DATA2BLOCK(ptr);
    if (OS_MALLOC_BLOCK_OK(block)) {
        return block->size;
    }

    return -1;
}

extern void __osDisplayArena(OSArena* arena) {
    OSMemBlock* block;
    OSMemBlock* next;
    u32 max_free;
    u32 total_free;
    u32 total_used;

    if (__osMallocIsInitalized(arena)) {
        arena_lock(arena);
        max_free = 0;
        total_free = 0;
        total_used = 0;

        // Arena Contents
        OSReport("アリーナの内容 (0x%08x)\n", arena);
        // Memory block span | status | size | [time  s ms us ns: TID:src:line]
        OSReport("メモリブロック範囲 status サイズ  [時刻  s ms us ns: TID:src:行]\n");

        block = arena->head;
        while (block != NULL) {
            if (OS_MALLOC_BLOCK_OK(block)) {
                next = block->next;
                OSReport("%08x-%08x%c %s %08x", (u32)block, (u32)block + sizeof(OSMemBlock) + block->size, next == NULL ? '$' : (next->prev != block ? '!' : ' '), block->free ? "空き" : "確保", block->size);
                if (!block->free) {
                    // 空き = free, 確保 = used
                    OSReport(" [%016llu:%2d:%s:%d]", OSTicksToMicroseconds((u64)block->time * 1000), block->threadId, block->file != NULL ? block->file : "**NULL**", block->line);
                }
                OSReport("\n");
                if (block->free) {
                    total_free += block->size;
                    if (max_free < block->size) {
                        max_free = block->size;
                    }
                } else {
                    total_used += block->size;
                }
            } else {
                OSReport("%08x Block Invalid\n", block);
                next = NULL;
            }

            block = next;
        }

        // Total used memblock size: 0x%08x bytes
        OSReport("確保ブロックサイズの合計 0x%08x バイト\n", total_used);
        // Total free memblock size: 0x%08x bytes
        OSReport("空きブロックサイズの合計 0x%08x バイト\n", total_free);
        // Largest free block size: %08x bytes
        OSReport("最大空きブロックサイズ   0x%08x バイト\n", max_free);
        arena_unlock(arena);
    }
}

#pragma force_active on
extern int __osCheckArena(OSArena* arena) {
    int ret = FALSE;
    OSMemBlock* block;
    
    arena_lock(arena);
    block = arena->head;
    while (block != NULL) {
        if (!OS_MALLOC_BLOCK_OK(block)) {
            // Oops!!
            OSReport(VT_COL(RED, WHITE) "おおっと！！ (%08x %08x)\n" VT_RST, block, block->magic);
            OSPanic(__FILE__, 1307, "");
            ret = TRUE;
            break;
        }

        block = get_block_next(block);
    }
    arena_unlock(arena);
    return ret;
}
#pragma force_active reset
