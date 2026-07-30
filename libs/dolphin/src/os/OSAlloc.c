#include <dolphin.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/os.h>
#include <macros.h>

#define ALIGNMENT 32

#define InRange(cell, arenaStart, arenaEnd)                                    \
	((u32)arenaStart <= (u32)cell) && ((u32)cell < (u32)arenaEnd)

#define HEADERSIZE 32u
#define MINOBJSIZE 64u

struct Cell {
	struct Cell* prev;
	struct Cell* next;
	long size;
};

struct HeapDesc {
	long size;
	struct Cell* free;
	struct Cell* allocated;
};

volatile int __OSCurrHeap = -1;

static struct HeapDesc* HeapArray;
static int NumHeaps;
static void* ArenaStart;
static void* ArenaEnd;

// functions
static struct Cell* DLAddFront(struct Cell* list, struct Cell* cell);
static struct Cell* DLLookup(struct Cell* list, struct Cell* cell);
static struct Cell* DLExtract(struct Cell* list, struct Cell* cell);
static struct Cell* DLInsert(struct Cell* list, struct Cell* cell);

static struct Cell* DLAddFront(struct Cell* list, struct Cell* cell)
{
	cell->next = list;
	cell->prev = 0;
	if (list) {
		list->prev = cell;
	}
	return cell;
}

static struct Cell* DLLookup(struct Cell* list, struct Cell* cell)
{
	for (; list; list = list->next) {
		if (list == cell) {
			return list;
		}
	}
	return NULL;
}

static struct Cell* DLExtract(struct Cell* list, struct Cell* cell)
{
	if (cell->next) {
		cell->next->prev = cell->prev;
	}
	if (cell->prev == NULL) {
		return cell->next;
	}
	cell->prev->next = cell->next;
	return list;
}

static struct Cell* DLInsert(struct Cell* list, struct Cell* cell)
{
	struct Cell* prev;
	struct Cell* next;

	for (next = list, prev = NULL; next != 0; prev = next, next = next->next) {
		if (cell <= next) {
			break;
		}
	}

	cell->next = next;
	cell->prev = prev;
	if (next) {
		next->prev = cell;
		if ((u8*)cell + cell->size == (u8*)next) {
			cell->size += next->size;
			next       = next->next;
			cell->next = next;
			if (next) {
				next->prev = cell;
			}
		}
	}
	if (prev) {
		prev->next = cell;
		if ((u8*)prev + prev->size == (u8*)cell) {
			prev->size += cell->size;
			prev->next = next;
			if (next) {
				next->prev = prev;
			}
		}
		return list;
	}
	return cell;
}

void* OSAllocFromHeap(int heap, unsigned long size)
{
	struct HeapDesc* hd;
	struct Cell* cell;
	struct Cell* newCell;
	long leftoverSize;
	long requested;

	requested = size;
	ASSERTMSGLINE(0x14D, HeapArray,
	              "OSAllocFromHeap(): heap is not initialized.");
	ASSERTMSGLINE(0x14E, (signed long)size > 0,
	              "OSAllocFromHeap(): invalid size.");
	ASSERTMSGLINE(0x14F, heap >= 0 && heap < NumHeaps,
	              "OSAllocFromHeap(): invalid heap handle.");
	ASSERTMSGLINE(0x150, HeapArray[heap].size >= 0,
	              "OSAllocFromHeap(): invalid heap handle.");

	hd = &HeapArray[heap];
	size += 0x20;
	size = (size + 0x1F) & 0xFFFFFFE0;

	for (cell = hd->free; cell != NULL; cell = cell->next) {
		if ((signed)size <= (signed)cell->size) {
			break;
		}
	}

	if (cell == NULL) {
		return NULL;
	}
	ASSERTMSGLINE(0x168, !((s32)cell & 0x1F),
	              "OSAllocFromHeap(): heap is broken.");
	ASSERTMSGLINE(0x169, cell->hd == NULL,
	              "OSAllocFromHeap(): heap is broken.");

	leftoverSize = cell->size - size;
	if (leftoverSize < 0x40U) {
		hd->free = DLExtract(hd->free, cell);
	} else {
		cell->size    = size;
		newCell       = (void*)((u8*)cell + size);
		newCell->size = leftoverSize;
		newCell->prev = cell->prev;
		newCell->next = cell->next;
		if (newCell->next != NULL) {
			newCell->next->prev = newCell;
		}
		if (newCell->prev != NULL) {
			newCell->prev->next = newCell;
		} else {
			ASSERTMSGLINE(0x186, hd->free == cell,
			              "OSAllocFromHeap(): heap is broken.");
			hd->free = newCell;
		}
	}

	hd->allocated = DLAddFront(hd->allocated, cell);
	return (u8*)cell + 0x20;
}

void OSFreeToHeap(int heap, void* ptr)
{
	struct HeapDesc* hd;
	struct Cell* cell;

	ASSERTMSGLINE(0x23D, HeapArray, "OSFreeToHeap(): heap is not initialized.");
	ASSERTMSGLINE(
	    0x23F, ((u32)ArenaStart + 0x20) <= (u32)ptr && (u32)ptr < (u32)ArenaEnd,
	    "OSFreeToHeap(): invalid pointer.");
	ASSERTMSGLINE(0x240, OFFSET(ptr, ALIGNMENT) == 0,
	              "OSFreeToHeap(): invalid pointer.");
	ASSERTMSGLINE(0x241, HeapArray[heap].size >= 0,
	              "OSFreeToHeap(): invalid heap handle.");
	cell = (void*)((u32)ptr - 0x20);
	hd   = &HeapArray[heap];
	ASSERTMSGLINE(0x246, cell->hd == hd, "OSFreeToHeap(): invalid pointer.");
	ASSERTMSGLINE(0x247, DLLookup(hd->allocated, cell),
	              "OSFreeToHeap(): invalid pointer.");

	hd->allocated = DLExtract(hd->allocated, cell);
	hd->free      = DLInsert(hd->free, cell);
}

void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps)
{
	unsigned long arraySize;
	int i;
	struct HeapDesc* hd;

	ASSERTMSGLINE(0x283, maxHeaps > 0,
	              "OSInitAlloc(): invalid number of heaps.");
	ASSERTMSGLINE(0x285, (u32)arenaStart < (u32)arenaEnd,
	              "OSInitAlloc(): invalid range.");
	ASSERTMSGLINE(0x288, maxHeaps <= (((u32)arenaEnd - (u32)arenaStart) / 24U),
	              "OSInitAlloc(): too small range.");
	arraySize = maxHeaps * sizeof(struct HeapDesc);
	HeapArray = arenaStart;
	NumHeaps  = maxHeaps;

	for (i = 0; i < NumHeaps; i++) {
		hd       = &HeapArray[i];
		hd->size = -1;
		hd->free = hd->allocated = 0;
	}
	__OSCurrHeap = -1;
	arenaStart   = (void*)((u32)((char*)HeapArray + arraySize));
	arenaStart   = (void*)(((u32)arenaStart + 0x1F) & 0xFFFFFFE0);
	ArenaStart   = arenaStart;
	ArenaEnd     = (void*)((u32)arenaEnd & 0xFFFFFFE0);
	ASSERTMSGLINE(0x2A4, ((u32)ArenaEnd - (u32)ArenaStart) >= 0x40U,
	              "OSInitAlloc(): too small range.");
	return arenaStart;
}

int OSCreateHeap(void* start, void* end)
{
	int heap;
	struct HeapDesc* hd;
	struct Cell* cell;

	ASSERTMSGLINE(0x2BD, HeapArray, "OSCreateHeap(): heap is not initialized.");
	ASSERTMSGLINE(0x2BE, (u32)start < (u32)end,
	              "OSCreateHeap(): invalid range.");

	start = (void*)(((u32)start + 0x1FU) & ~((32) - 1));
	end   = (void*)(((u32)end) & ~((32) - 1));

	ASSERTMSGLINE(0x2C1, (u32)start < (u32)end,
	              "OSCreateHeap(): invalid range.");
	ASSERTMSGLINE(0x2C3,
	              (u32)ArenaStart <= (u32)start && (u32)end <= (u32)ArenaEnd,
	              "OSCreateHeap(): invalid range.");
	ASSERTMSGLINE(0x2C5, ((u32)end - (u32)start) >= 0x40U,
	              "OSCreateHeap(): too small range.");

	for (heap = 0; heap < NumHeaps; heap++) {
		hd = &HeapArray[heap];
		if (hd->size < 0) {
			hd->size      = (u32)end - (u32)start;
			cell          = start;
			cell->prev    = 0;
			cell->next    = 0;
			cell->size    = hd->size;
			hd->free      = cell;
			hd->allocated = 0;
			return heap;
		}
	}
	return -1;
}

void OSDestroyHeap(int heap)
{
	struct HeapDesc* hd;
	long size;

	ASSERTMSGLINE(0x30A, HeapArray,
	              "OSDestroyHeap(): heap is not initialized.");
	ASSERTMSGLINE(0x30B, (heap >= 0) && (heap < NumHeaps),
	              "OSDestroyHeap(): invalid heap handle.");
	ASSERTMSGLINE(0x30C, HeapArray[heap].size >= 0,
	              "OSDestroyHeap(): invalid heap handle.");

	hd = &HeapArray[heap];

	hd->size = -1;
}

// custom macro for OSCheckHeap
#define ASSERTREPORT(line, cond)                                               \
	if (!(cond)) {                                                             \
		OSReport("OSCheckHeap: Failed " #cond " in %d", line);                 \
		return -1;                                                             \
	}

long OSCheckHeap(int heap)
{
	struct HeapDesc* hd;
	struct Cell* cell;
	long total = 0;
	long free  = 0;

	ASSERTREPORT(0x37D, HeapArray);
	ASSERTREPORT(0x37E, 0 <= heap && heap < NumHeaps);
	hd = &HeapArray[heap];
	ASSERTREPORT(0x381, 0 <= hd->size);

	ASSERTREPORT(0x383, hd->allocated == NULL || hd->allocated->prev == NULL);

	for (cell = hd->allocated; cell; cell = cell->next) {
		ASSERTREPORT(0x386, InRange(cell, ArenaStart, ArenaEnd));
		ASSERTREPORT(0x387, OFFSET(cell, ALIGNMENT) == 0);
		ASSERTREPORT(0x388, cell->next == NULL || cell->next->prev == cell);
		ASSERTREPORT(0x389, MINOBJSIZE <= cell->size);
		ASSERTREPORT(0x38A, OFFSET(cell->size, ALIGNMENT) == 0);
		total += cell->size;
		ASSERTREPORT(0x38D, 0 < total && total <= hd->size);
	}

	ASSERTREPORT(0x395, hd->free == NULL || hd->free->prev == NULL);

	for (cell = hd->free; cell; cell = cell->next) {
		ASSERTREPORT(0x398, InRange(cell, ArenaStart, ArenaEnd));
		ASSERTREPORT(0x399, OFFSET(cell, ALIGNMENT) == 0);
		ASSERTREPORT(0x39A, cell->next == NULL || cell->next->prev == cell);
		ASSERTREPORT(0x39B, MINOBJSIZE <= cell->size);
		ASSERTREPORT(0x39C, OFFSET(cell->size, ALIGNMENT) == 0);
		// NOTE: macro arg is stringified so format mustn't touch it
		// clang-format off
		ASSERTREPORT(0x39D, cell->next == NULL
		                 || (char*) cell + cell->size < (char*) cell->next);
		// clang-format on
		total += cell->size;
		free = (cell->size + free);
		free -= HEADERSIZE;
		ASSERTREPORT(0x3A1, 0 < total && total <= hd->size);
	}
	ASSERTREPORT(0x3A8, total == hd->size);
	return free;
}

unsigned long OSReferentSize(void* ptr)
{
	struct Cell* cell;

	ASSERTMSGLINE(0x3BB, HeapArray,
	              "OSReferentSize(): heap is not initialized.");
	ASSERTMSGLINE(0x3BD, InRange(ptr, ArenaStart + HEADERSIZE, ArenaEnd),
	              "OSReferentSize(): invalid pointer.");
	ASSERTMSGLINE(0x3BE, !OFFSET(ptr, 32),
	              "OSReferentSize(): invalid pointer.");
	cell = (void*)((u32)ptr - HEADERSIZE);
	ASSERTMSGLINE(0x3C2, cell->hd, "OSReferentSize(): invalid pointer.");
	ASSERTMSGLINE(0x3C4, !(((u32)cell->hd - (u32)HeapArray) % 24),
	              "OSReferentSize(): invalid pointer.");
	ASSERTMSGLINE(
	    0x3C6,
	    ((u32)HeapArray <= (u32)cell->hd)
	        && ((u32)cell->hd < (u32)((u32)HeapArray + (NumHeaps * 0x18))),
	    "OSReferentSize(): invalid pointer.");
	ASSERTMSGLINE(0x3C7, cell->hd->size >= 0,
	              "OSReferentSize(): invalid pointer.");
	ASSERTMSGLINE(0x3C9, DLLookup(cell->hd->allocated, cell),
	              "OSReferentSize(): invalid pointer.");
	return (long)((u32)cell->size - HEADERSIZE);
}

void OSDumpHeap(int heap)
{
	struct HeapDesc* hd;
	struct Cell* cell;

	OSReport("\nOSDumpHeap(%d):\n", heap);
	ASSERTMSGLINE(0x3DE, HeapArray, "OSDumpHeap(): heap is not initialized.");
	ASSERTMSGLINE(0x3DF, (heap >= 0) && (heap < NumHeaps),
	              "OSDumpHeap(): invalid heap handle.");
	hd = &HeapArray[heap];
	if (hd->size < 0) {
		OSReport("--------Inactive\n");
		return;
	}
	ASSERTMSGLINE(0x3E8, OSCheckHeap(heap) >= 0,
	              "OSDumpHeap(): heap is broken.");

	OSReport("addr	size		end	prev	next\n");
	OSReport("--------Allocated\n");

	ASSERTMSGLINE(0x3F5, hd->allocated == NULL || hd->allocated->prev == NULL,
	              "OSDumpHeap(): heap is broken.");

	for (cell = hd->allocated; cell; cell = cell->next) {
		OSReport("%x	%d	%x	%x	%x\n", cell, cell->size,
		         (char*)cell + cell->size, cell->prev, cell->next);
	}
	OSReport("--------Free\n");
	for (cell = hd->free; cell; cell = cell->next) {
		OSReport("%x	%d	%x	%x	%x\n", cell, cell->size,
		         (char*)cell + cell->size, cell->prev, cell->next);
	}
}
