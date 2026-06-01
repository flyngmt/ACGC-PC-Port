#include "jaudio_NES/heapctrl.h"

#include "jaudio_NES/dummyrom.h"

#include "dolphin/os/OSMessage.h"
#include "dolphin/ar.h"
#include "dolphin/os/OSCache.h"

#define DMABUFFER_SIZE (0x10000)
static u8 dmabuffer[DMABUFFER_SIZE] ATTRIBUTE_ALIGN(32);

static u32 global_id = 0;

/*
 * --INFO--
 * Address:	8000E9C0
 * Size:	000034
 */
static void ARAMFinish(u32 msg)
{
	// STACK_PAD_VAR(1);
	u32* REF_param_1;

	REF_param_1         = &msg;
	ARQRequest* request = (ARQRequest*)msg;
	OSSendMessage((OSMessageQueue*)request->owner, (OSMessage)1, OS_MESSAGE_BLOCK);
}

/*
 * --INFO--
 * Address:	8000EA00
 * Size:	0000E8
 */
static void ARAM_TO_ARAM_DMA(u32 src, u32 dst, u32 totalSize)
{
	ARQRequest request;
	OSMessageQueue msgQueue;
	OSMessage msg;
	u32 burstSize;

	OSInitMessageQueue(&msgQueue, &msg, 1);
	while (totalSize != 0) {
		burstSize = totalSize >= DMABUFFER_SIZE ? DMABUFFER_SIZE : totalSize;

#ifdef TARGET_PC
		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW, src, (uintptr_t)dmabuffer, burstSize, &ARAMFinish);
#else
		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW, src, (uintptr_t)dmabuffer, burstSize, &ARAMFinish);
#endif
		OSReceiveMessage(&msgQueue, NULL, OS_MESSAGE_BLOCK);
#ifdef TARGET_PC
		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW, (uintptr_t)dmabuffer, dst, burstSize, &ARAMFinish);
#else
		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW, (uintptr_t)dmabuffer, dst, burstSize, &ARAMFinish);
#endif
		OSReceiveMessage(&msgQueue, NULL, OS_MESSAGE_BLOCK);

		totalSize -= burstSize;
		src += burstSize;
		dst += burstSize;
	}
}

/*
 * --INFO--
 * Address:	8000EB00
 * Size:	0000FC
 */
static void DRAM_TO_DRAM_DMA(u32 src, u32 dst, u32 totalSize)
{
	ARQRequest request;
	OSMessageQueue msgQueue;
	OSMessage msg;
	u32 dma_buffer_top;
	u32 burstSize;

	dma_buffer_top = (uintptr_t)JAC_ARAM_DMA_BUFFER_TOP;
	OSInitMessageQueue(&msgQueue, &msg, 1);
	DCFlushRange((void*)src, totalSize);
	DCInvalidateRange((void*)dst, totalSize);
	while (totalSize != 0) {
		burstSize = totalSize >= DMABUFFER_SIZE ? DMABUFFER_SIZE : totalSize;

		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_LOW, src, dma_buffer_top, burstSize, &ARAMFinish);
		OSReceiveMessage(&msgQueue, NULL, OS_MESSAGE_BLOCK);
		ARQPostRequest(&request, (uintptr_t)&msgQueue, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_LOW, dma_buffer_top, dst, burstSize, &ARAMFinish);
		OSReceiveMessage(&msgQueue, NULL, OS_MESSAGE_BLOCK);

		totalSize -= burstSize;
		src += burstSize;
		dst += burstSize;
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jac_GetUnlockHeap(jaheap_*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void Jac_CheckAlloc(jaheap_*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000EC00
 * Size:	000044
 */
void Jac_InitHeap(jaheap_* heap)
{
	heap->startAddress     = 0;
	heap->usedSize         = 0;
	heap->size             = 0;
	heap->heapId           = global_id++;
	heap->isRootHeap       = 0;
	heap->childCount       = 0;
	heap->firstChild       = 0;
	heap->parent           = NULL;
	heap->nextSibling      = 0;
	heap->groupOwner       = 0;
	heap->firstGroupedHeap = 0;
	heap->nextGroupedHeap  = 0;
}

/*
 * --INFO--
 * Address:	8000EC60
 * Size:	000038
 */
void Jac_SelfInitHeap(jaheap_* heap, u32 startAddr, u32 size, u32 memType)
{
	heap->startAddress     = startAddr;
	heap->size             = size;
	heap->usedSize         = 0;
	heap->isRootHeap       = 0;
	heap->memoryType       = memType;
	heap->childCount       = 0;
	heap->firstChild       = NULL;
	heap->parent           = NULL;
	heap->nextSibling      = 0;
	heap->groupOwner       = 0;
	heap->firstGroupedHeap = 0;
	heap->nextGroupedHeap  = 0;
}

/*
 * --INFO--
 * Address:	8000ECA0
 * Size:	000100
 */
BOOL Jac_SelfAllocHeap(jaheap_* parent, jaheap_* heap, u32 size, u32 startAddr)
{
	if (parent->startAddress && parent->startAddress != -1) {
		return FALSE;
	}

	parent->startAddress = startAddr;
	parent->size         = size;
	parent->usedSize     = 0;
	parent->isRootHeap   = 0;
	parent->memoryType   = heap->memoryType;
	parent->childCount   = 0;
	parent->firstChild   = nullptr;
	parent->parent       = heap;

	jaheap_* temp = heap->firstChild;
	if (temp == NULL) {
		heap->firstChild    = parent;
		parent->nextSibling = nullptr;
		heap->usedSize      = parent->startAddress - heap->startAddress + parent->size;
	} else {
		jaheap_* temp2 = heap->firstChild;
		if (parent->startAddress < heap->firstChild->startAddress) {
			parent->nextSibling = heap->firstChild;
			heap->firstChild    = parent;
		} else {
			while (TRUE) {
				if (!(temp = temp2->nextSibling)) {
					parent->nextSibling = NULL;
					temp2->nextSibling  = parent;
					heap->usedSize      = parent->startAddress - heap->startAddress + parent->size;
					break;
				}
				if (parent->startAddress < temp->startAddress) {
					parent->nextSibling = temp;
					temp2->nextSibling  = parent;
					break;
				}
				temp2 = temp;
			}
		}
	}

	heap->childCount++;
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000EDA0
 * Size:	000038
 */
BOOL Jac_SetGroupHeap(jaheap_* heapA, jaheap_* heapB)
{
	if (heapA->groupOwner || heapA->nextGroupedHeap) {
		return FALSE;
	}

	heapA->groupOwner       = heapB;
	heapA->nextGroupedHeap  = heapB->firstGroupedHeap;
	heapB->firstGroupedHeap = heapA;
	return TRUE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00000C
 */
void Jac_CutdownHeap(jaheap_*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000EDE0
 * Size:	00005C
 */
#ifdef TARGET_PC
void Jac_InitMotherHeap(jaheap_* heap, uintptr_t startAddr, u32 size, u8 memType)
#else
void Jac_InitMotherHeap(jaheap_* heap, u32 startAddr, u32 size, u8 memType)
#endif
{
	heap->startAddress     = startAddr + 0x1f & 0xffffffe0;
	heap->usedSize         = 0;
	heap->size             = size - (startAddr & 0x1f);
	heap->heapId           = global_id++;
	heap->isRootHeap       = 1;
	heap->memoryType       = memType;
	heap->childCount       = 0;
	heap->firstChild       = NULL;
	heap->parent           = NULL;
	heap->nextSibling      = NULL;
	heap->groupOwner       = NULL;
	heap->firstGroupedHeap = NULL;
	heap->nextGroupedHeap  = NULL;
}

/*
 * --INFO--
 * Address:	8000EE40
 * Size:	0001B4
 */
BOOL Jac_AllocHeap(jaheap_* heap, jaheap_* parent, u32 size)
{
	u32 y;
	jaheap_* temp;
	jaheap_* temp2;
	jaheap_* result;
	u32 t;
	u32 max;
	u32 x;

	size = OSRoundUp32B(size);

	if (parent->startAddress == 0) {
		return FALSE;
	} else if (heap->startAddress && heap->startAddress != -1) {
		return FALSE;
	} else if (parent->size - parent->usedSize < size) {
		temp   = parent->firstChild;
		y      = parent->startAddress;
		result = NULL;
		max    = 0xfffffff;
		while (TRUE) {
			if (temp == NULL) {
				break;
			}
			x = temp->startAddress - y;
			if (x >= size) {
				x -= size;

				if (x < max) {
					result = temp;
					t      = y;
					max    = x;
				}
			}

			y    = temp->startAddress + temp->size;
			temp = temp->nextSibling;
		}

		if (result == 0) {
			return FALSE;
		}

        if (result == parent->firstChild) {
            heap->nextSibling  = parent->firstChild;
            parent->firstChild = heap;
        } else {
            temp2 = parent->firstChild;
            while (TRUE) {
                if (temp2->nextSibling == result) {
                    heap->nextSibling  = temp2->nextSibling;
                    temp2->nextSibling = heap;
                    break;
                }
                temp2 = temp2->nextSibling;
            }
        }

        heap->startAddress = t;
        heap->size         = size;
        heap->usedSize     = 0;
        heap->isRootHeap   = 0;
        heap->memoryType   = parent->memoryType;
        heap->childCount   = 0;
        heap->firstChild   = NULL;
        heap->parent       = parent;
        parent->childCount++;
        return TRUE;
	} else {
        heap->startAddress = parent->startAddress + parent->usedSize;
        heap->size         = size;
        heap->usedSize     = 0;
        heap->isRootHeap   = 0;
        heap->memoryType   = parent->memoryType;
        heap->childCount   = 0;
        heap->firstChild   = NULL;
        heap->parent       = parent;

        if (parent->firstChild == NULL) {
            parent->firstChild = heap;
            heap->nextSibling  = NULL;
        } else {
            temp = parent->firstChild;
            while (TRUE) {
                if (temp->nextSibling == NULL) {
                    temp->nextSibling = heap;
                    break;
                }
                temp = temp->nextSibling;
            }
        }

        heap->nextSibling = NULL;
        parent->usedSize += size;
        parent->childCount++;
        return TRUE;
    }
}

/*
 * --INFO--
 * Address:	8000F000
 * Size:	0001B0
 */
BOOL Jac_DeleteHeap(jaheap_* heap)
{
	// STACK_PAD_VAR(4);
	jaheap_** pt = &heap;

	if (heap->startAddress == 0) {
		return FALSE;
	}

	jaheap_* heap2 = heap->firstChild;
	while (heap2) {
		jaheap_* next = heap2->nextSibling;
		Jac_DeleteHeap(heap2);
		heap2 = next;
	}

	heap->firstChild = NULL;

	heap2 = heap->firstGroupedHeap;
	while (heap2) {
		jaheap_* next = heap2->nextGroupedHeap;
		Jac_DeleteHeap(heap2);
		heap2 = next;
	}

	heap->firstGroupedHeap = NULL;

	if (heap->parent) {
		heap2 = heap->parent->firstChild;
		if (heap2 == heap) {
			heap->parent->firstChild = heap->nextSibling;
			if (heap->nextSibling == NULL) {
				heap->parent->usedSize = NULL;
			}
		} else {
			while (TRUE) {
				if (heap2 == NULL) {
					heap->startAddress = 0;
					return FALSE;
				}

				if (heap2->nextSibling == heap) {
					heap2->nextSibling = heap->nextSibling;
					if (heap->nextSibling == NULL) {
						heap->parent->usedSize = heap2->startAddress + heap2->size - heap->parent->startAddress;
					}
					break;
				}

				heap2 = heap2->nextSibling;
			}
		}

		heap->parent->childCount--;
	}

	if (heap->groupOwner) {
		heap2 = heap->groupOwner->firstGroupedHeap;

		if (heap2 == heap) {
			heap->groupOwner->firstGroupedHeap = heap->nextGroupedHeap;
		} else {
			while (TRUE) {
				if (heap2 == NULL) {
					return FALSE;
				}

				if (heap2->nextGroupedHeap == heap) {
					heap2->nextGroupedHeap = heap->nextGroupedHeap;
					break;
				}

				heap2 = heap2->nextGroupedHeap;
			}
		}

		heap->groupOwner      = NULL;
		heap->nextGroupedHeap = NULL;
	}

	heap->startAddress = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000F1C0
 * Size:	000064
 */
static void Jac_Move_Children(jaheap_* heap, s32 flag)
{
	if (flag == 0) {
		return;
	}

	for (jaheap_* c = heap->firstChild;; c = c->nextSibling) {
		if (c == NULL) {
			break;
		}

		c->startAddress += flag;
		if (c->firstChild) {
			Jac_Move_Children(c, flag);
		}
	}
}

/*
 * --INFO--
 * Address:	8000F240
 * Size:	0000C8
 */
void Jac_GarbageCollection_St(jaheap_* heap)
{
	jaheap_* heap_00;
	u32 src;
	u32 dst;

	dst     = heap->startAddress;
	heap_00 = heap->firstChild;

	if (heap_00 == NULL) {
		heap->usedSize = 0;
		return;
	}

	do {
		src = heap_00->startAddress;
		if (dst != src) {
			switch (heap->memoryType) {
			case 0:
				ARAM_TO_ARAM_DMA(src, dst, heap_00->size);
				break;
			case 1:
				DRAM_TO_DRAM_DMA(src, dst, heap_00->size);
				break;
			}
			Jac_Move_Children(heap_00, dst - heap_00->startAddress);
			heap_00->startAddress = dst;
		}
		dst = heap_00->startAddress + heap_00->size;
	} while (heap_00 = heap_00->nextSibling);

	heap->usedSize = dst - heap->startAddress;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void Jac_CheckFreeHeap_Total(jaheap_*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00005C
 */
void Jac_CheckFreeHeap_Linear(jaheap_*)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000F320
 * Size:	0000C4
 */
void Jac_ShowHeap(jaheap_* heap, u32 flag)
{
	jaheap_** REF_heap = &heap;
	jaheap_* c;
	jaheap_** REF_c;

	// STACK_PAD_VAR(3);
	char unused[] = "        ";
	(void*)unused[0];

	c     = heap->firstChild;
	REF_c = &c;
	// STACK_PAD_VAR(15);
	if (c) {
		do {
			if (c->firstChild) {
				Jac_ShowHeap(c, flag + 1);
			}
			c = c->nextSibling;
		} while (c);
	}

	jaheap_* c2;
	if (c2 = heap->firstGroupedHeap) {
		do {
			if (c2->firstGroupedHeap) {
				Jac_ShowHeap(c2, flag + 1);
			}
			c2 = c2->nextGroupedHeap;
		} while (c2);
	}
}
