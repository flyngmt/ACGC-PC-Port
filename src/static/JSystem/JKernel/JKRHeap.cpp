#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/os.h"
#include "dolphin/os/OSArena.h"
#include "dolphin/os/OSAlloc.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSUtil.h"
#include "dolphin/os.h"

JKRHeap* JKRHeap::sSystemHeap;
JKRHeap* JKRHeap::sCurrentHeap;
JKRHeap* JKRHeap::sRootHeap;
JKRHeapErrorHandler* JKRHeap::mErrorHandler;
void* JKRHeap::mCodeStart;
void* JKRHeap::mCodeEnd;
void* JKRHeap::mUserRamStart;
void* JKRHeap::mUserRamEnd;
u32 JKRHeap::mMemorySize;

bool JKRHeap::sDefaultFillFlag = true;

JKRHeap::JKRHeap(void* data, u32 size, JKRHeap* heap, bool errorFlag)
    : JKRDisposer(), mChildTree(this), mDisposerList() {
    OSInitMutex(&mMutex);
    mSize = size;
    mStart = (u8*)data;
    mEnd = ((u8*)data + size);
    if (heap == nullptr) {
        becomeSystemHeap();
        becomeCurrentHeap();
    } else {
        heap->mChildTree.appendChild(&mChildTree);
        if (sSystemHeap == sRootHeap)
            becomeSystemHeap();
        if (sCurrentHeap == sRootHeap)
            becomeCurrentHeap();
    }
    mErrorFlag = errorFlag;
    if (mErrorFlag == true && mErrorHandler == nullptr)
        mErrorHandler = JKRDefaultMemoryErrorRoutine;
    mDebugFill = sDefaultFillFlag;
    mInitFlag = false;
}

JKRHeap::~JKRHeap() {
    mChildTree.getParent()->removeChild(&mChildTree);
    JSUTree<JKRHeap>* nextRootHeap = sRootHeap->mChildTree.getFirstChild();
    if (sCurrentHeap == this)
        sCurrentHeap = !nextRootHeap ? sRootHeap : nextRootHeap->getObject();

    if (sSystemHeap == this)
        sSystemHeap = !nextRootHeap ? sRootHeap : nextRootHeap->getObject();
}

bool JKRHeap::initArena(char** outUserRamStart, u32* outUserRamSize, int numHeaps) {
    void* arenaLo = OSGetArenaLo();
    void* arenaHi = OSGetArenaHi();
    if (arenaLo == arenaHi) {
        return false;
    }
    void* arenaStart = OSInitAlloc(arenaLo, arenaHi, numHeaps);
    arenaHi = (u8*)OSRoundDown32B(arenaHi);
    arenaLo = (u8*)OSRoundUp32B(arenaStart);
    u8* start = (u8*)OSPhysicalToCached(0);
    mCodeStart = (u8*)start;
    mCodeEnd = (u8*)arenaLo;
    mUserRamStart = (u8*)arenaLo;
    mUserRamEnd = (u8*)arenaHi;
    mMemorySize = *(u32*)((start + 0x28));
    OSSetArenaLo(arenaHi);
    OSSetArenaHi(arenaHi);
    *outUserRamStart = (char*)arenaLo;
#ifdef TARGET_PC
    *outUserRamSize = (u32)((uintptr_t)arenaHi - (uintptr_t)arenaLo);
#else
    *outUserRamSize = (u32)arenaHi - (u32)arenaLo;
#endif
    return true;
}

JKRHeap* JKRHeap::becomeSystemHeap() {
    JKRHeap* old = sSystemHeap;
    sSystemHeap = this;
    return old;
}

JKRHeap* JKRHeap::becomeCurrentHeap() {
    JKRHeap* old = sCurrentHeap;
    sCurrentHeap = this;
    return old;
}

void JKRHeap::destroy(JKRHeap* heap) {
    JUT_ASSERT(heap != 0);
    heap->destroy();
}

void* JKRHeap::alloc(u32 byteCount, int padding, JKRHeap* heap) {
    void* memory = nullptr;
    if (heap) {
        memory = heap->do_alloc(byteCount, padding);
    } else if (sCurrentHeap) {
        memory = sCurrentHeap->do_alloc(byteCount, padding);
    }
    return memory;
}

void* JKRHeap::alloc(u32 byteCount, int padding) {
    JUT_WARNING_F(!mInitFlag, "alloc %x byte in heap %x", byteCount, this);
    return do_alloc(byteCount, padding);
}

void JKRHeap::free(void* memory, JKRHeap* heap) {
    if ((heap) || (heap = findFromRoot(memory), heap)) {
        heap->free(memory);
    }
}

void JKRHeap::free(void* memory) {
    JUT_WARNING_F(!mInitFlag, "free %x in heap %x", memory, this);
    do_free(memory);
}

void JKRHeap::callAllDisposer() {
    JSUListIterator<JKRDisposer> iterator;
    while (iterator = mDisposerList.getFirst(), iterator != mDisposerList.getEnd()) {
        iterator->~JKRDisposer();
    }
}

void JKRHeap::freeAll() {
    JUT_WARNING_F(!mInitFlag, "freeAll in heap %x", this);
    do_freeAll();
}

void JKRHeap::freeTail() {
    JUT_WARNING_F(!mInitFlag, "freeTail in heap %x", this);
    do_freeTail();
}

s32 JKRHeap::resize(void* memoryBlock, u32 newSize) {
    JUT_WARNING_F(!mInitFlag, "resize block %x into %x in heap %x", memoryBlock, newSize, this);
    return do_resize(memoryBlock, newSize);
}

s32 JKRHeap::getSize(void* memoryBlock, JKRHeap* heap) {
    if (heap == nullptr && (heap = findFromRoot(memoryBlock), heap == nullptr)) {
        return -1;
    } else
        return heap->getSize(memoryBlock);
}

s32 JKRHeap::getSize(void* memoryBlock) {
    return do_getSize(memoryBlock);
}
s32 JKRHeap::getFreeSize() {
    return do_getFreeSize();
}
s32 JKRHeap::getTotalFreeSize() {
    return do_getTotalFreeSize();
}

s32 JKRHeap::changeGroupID(u8 newGroupID) {
    JUT_WARNING_F(!mInitFlag, "change heap ID into %x in heap %x", newGroupID, this);
    return do_changeGroupID(newGroupID);
}

u8 JKRHeap::getCurrentGroupId() {
    return do_getCurrentGroupId();
}

JKRHeap* JKRHeap::findFromRoot(void* ptr) {
    if (sRootHeap != nullptr)
        return sRootHeap->find(ptr);

    return nullptr;
}

JKRHeap* JKRHeap::find(void* memory) const {
    if ((mStart <= memory) && (memory <= mEnd)) {
        if (mChildTree.getNumChildren() != 0) {
            for (JSUTreeIterator<JKRHeap> iterator(mChildTree.getFirstChild()); iterator != mChildTree.getEndChild();
                 ++iterator) {
                JKRHeap* result = iterator->find(memory);
                if (result) {
                    return result;
                }
            }
        }
        return const_cast<JKRHeap*>(this);
    }
    return nullptr;
}

JKRHeap* JKRHeap::findAllHeap(void* memory) const {
    if (mChildTree.getNumChildren() != 0) {
        for (JSUTreeIterator<JKRHeap> iterator(mChildTree.getFirstChild()); iterator != mChildTree.getEndChild();
             ++iterator) {
            JKRHeap* result = iterator->findAllHeap(memory);
            if (result) {
                return result;
            }
        }
    }

    if (mStart <= memory && memory < mEnd) {
        return const_cast<JKRHeap*>(this);
    }

    return nullptr;
}

// generates __as__25JSUTreeIterator<7JKRHeap>FP17JSUTree<7JKRHeap> and __ct__25JSUTreeIterator<7JKRHeap>Fv, remove this
#ifdef TARGET_PC
void JKRHeap::dispose_subroutine(uintptr_t begin, uintptr_t end) {
#else
void JKRHeap::dispose_subroutine(u32 begin, u32 end) {
#endif
    JSUListIterator<JKRDisposer> last_iterator;
    JSUListIterator<JKRDisposer> next_iterator;
    JSUListIterator<JKRDisposer> iterator;
    for (iterator = mDisposerList.getFirst(); iterator != mDisposerList.getEnd(); iterator = next_iterator) {
        JKRDisposer* disposer = iterator.getObject();

        if ((void*)begin <= disposer && disposer < (void*)end) {
            disposer->~JKRDisposer();
            if (last_iterator == nullptr) {
                next_iterator = mDisposerList.getFirst();
            } else {
                next_iterator = last_iterator;
                next_iterator++;
            }
        } else {
            last_iterator = iterator;
            next_iterator = iterator;
            next_iterator++;
        }
    }
}

bool JKRHeap::dispose(void* memory, u32 size) {
#ifdef TARGET_PC
    uintptr_t begin = (uintptr_t)memory;
    uintptr_t end = (uintptr_t)memory + size;
#else
    u32 begin = (u32)memory;
    u32 end = (u32)memory + size;
#endif
    dispose_subroutine(begin, end);
    return false;
}

void JKRHeap::dispose(void* begin, void* end) {
#ifdef TARGET_PC
    dispose_subroutine((uintptr_t)begin, (uintptr_t)end);
#else
    dispose_subroutine((u32)begin, (u32)end);
#endif
}

void JKRHeap::dispose() {
    JSUListIterator<JKRDisposer> iterator;
    while (iterator = mDisposerList.getFirst(), iterator != mDisposerList.getEnd()) {
        iterator->~JKRDisposer();
    }
}

void JKRHeap::copyMemory(void* dst, void* src, u32 size) {
    u32 count = (size + 3) / 4;

    u32* dst_32 = (u32*)dst;
    u32* src_32 = (u32*)src;
    while (count > 0) {
        *dst_32 = *src_32;
        dst_32++;
        src_32++;
        count--;
    }
}

void JKRDefaultMemoryErrorRoutine(void* heap, u32 size, int alignment) {
    // OSReport("Error: Cannot allocate memory %d(0x%x)byte in %d byte alignment from %08x\n", size, size, alignment,
    // heap);
    OSErrorLine(710, "abort\n");
}

JKRHeapErrorHandler* JKRHeap::setErrorHandler(JKRHeapErrorHandler* newHandler) {
    JKRHeapErrorHandler* oldHandler = mErrorHandler;
    if (!newHandler) {
        newHandler = JKRDefaultMemoryErrorRoutine;
    }
    mErrorHandler = newHandler;
    return oldHandler;
}

bool JKRHeap::isSubHeap(JKRHeap* heap) const {
    if (!heap)
        return false;

    if (mChildTree.getNumChildren() != 0) {
        JSUTreeIterator<JKRHeap> iterator;
        for (iterator = mChildTree.getFirstChild(); iterator != mChildTree.getEndChild(); ++iterator) {
            if (iterator.getObject() == heap) {
                return true;
            }

            if (iterator.getObject()->isSubHeap(heap)) {
                return true;
            }
        }
    }

    return false;
}

#ifdef TARGET_PC
/* On PC, the default operator new uses system malloc (not JKRHeap), because
 * macOS/Linux frameworks also call global operator new and expect malloc memory.
 *
 * operator delete must handle BOTH malloc'd memory AND JKR heap memory (from
 * objects allocated via `new (heap, alignment)` which uses JKRHeap::alloc). */
extern u8* arena_memory; /* from pc_os.c */

static inline bool pc_is_arena_ptr(void* p) {
    if (!arena_memory || !p) return false;
    uintptr_t addr = (uintptr_t)p;
    uintptr_t base = (uintptr_t)arena_memory;
    /* 48MB arena on 64-bit, 24MB on 32-bit */
    return (addr >= base && addr < base + (48u * 1024u * 1024u));
}

void* operator new(u32 byteCount) {
    return malloc(byteCount);
}
void* operator new(u32 byteCount, int alignment) {
    return malloc(byteCount);
}
void* operator new[](u32 byteCount) {
    return malloc(byteCount);
}
void* operator new[](u32 byteCount, int alignment) {
    return malloc(byteCount);
}
void operator delete(void* memory) {
    if (pc_is_arena_ptr(memory)) { JKRHeap::free(memory, nullptr); return; }
    free(memory);
}
void operator delete[](void* memory) {
    if (pc_is_arena_ptr(memory)) { JKRHeap::free(memory, nullptr); return; }
    free(memory);
}
/* C++14 sized deallocation - GCC 15 generates calls to these by default. */
void operator delete(void* memory, size_t) {
    if (pc_is_arena_ptr(memory)) { JKRHeap::free(memory, nullptr); return; }
    free(memory);
}
void operator delete[](void* memory, size_t) {
    if (pc_is_arena_ptr(memory)) { JKRHeap::free(memory, nullptr); return; }
    free(memory);
}
#else
void* operator new(u32 byteCount) {
    return JKRHeap::alloc(byteCount, 4, nullptr);
}
void* operator new(u32 byteCount, int alignment) {
    return JKRHeap::alloc(byteCount, alignment, nullptr);
}
void* operator new[](u32 byteCount) {
    return JKRHeap::alloc(byteCount, 4, nullptr);
}
void* operator new[](u32 byteCount, int alignment) {
    return JKRHeap::alloc(byteCount, alignment, nullptr);
}
void operator delete(void* memory) {
    JKRHeap::free(memory, nullptr);
}
void operator delete[](void* memory) {
    JKRHeap::free(memory, nullptr);
}
#endif
void* operator new(u32 byteCount, JKRHeap* heap, int alignment) {
    return JKRHeap::alloc(byteCount, alignment, heap);
}
void* operator new[](u32 byteCount, JKRHeap* heap, int alignment) {
    return JKRHeap::alloc(byteCount, alignment, heap);
}
#ifdef TARGET_PC
/* already defined above with malloc fallback */
#endif

/*JKRHeap::TState::TState(const JKRHeap::TState::TArgument &arg, const JKRHeap::TState::TLocation &location)
{
    // UNUSED FUNCTION
}

JKRHeap::TState::TState(const JKRHeap::TState &other, bool p2)
{
    // UNUSED FUNCTION
}

JKRHeap::TState::TState(const JKRHeap::TState &other, const JKRHeap::TState::TLocation &location, bool p3)
{
    // UNUSED FUNCTION
}*/

JKRHeap::TState::~TState() {
    // Unused, however might need it
}

void JKRHeap::state_register(JKRHeap::TState* p, u32) const {
    JUT_ASSERT(p != 0);
    JUT_ASSERT(p->getHeap() == this);
}

bool JKRHeap::state_compare(const JKRHeap::TState& r1, const JKRHeap::TState& r2) const {
    JUT_ASSERT(r1.getHeap() == r2.getHeap());
    return (r1.getCheckCode() == r2.getCheckCode());
}

// fabricated, but probably matches(except for line numbers)
void JKRHeap::state_dumpDifference(const JKRHeap::TState& r1, const JKRHeap::TState& r2) {
    JUT_LOG_F("heap       : %p / %p", r1.getHeap(), r2.getHeap());
    JUT_LOG_F("check-code : 0x%08x / 0x%08x", r1.getCheckCode(), r2.getCheckCode());
    JUT_LOG_F("id         : 0x%08x / 0x%08x", r1.getId(), r2.getId());
    JUT_LOG_F("used size  : %10u / %10u", r1.getUsedSize(), r2.getUsedSize());
}

void JKRHeap::state_dump(const TState& state) const {
    JUT_LOG_F("check-code : 0x%08x", state.getCheckCode());
    JUT_LOG_F("id         : 0x%08x", state.getId());
    JUT_LOG_F("used size  : %u", state.getUsedSize());
}
