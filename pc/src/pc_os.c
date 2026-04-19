/* pc_os.c - Dolphin OS replacement: arena, timers, threads, message queues */
#include "pc_platform.h"

#include <time.h>

/* --- Memory arena --- */
u8* arena_memory = NULL;
static u8* arena_lo = NULL;
static u8* arena_hi = NULL;

/* Exported for seg2k0 collision avoidance */
u8* pc_arena_base = NULL;
u8* pc_arena_end  = NULL;

void* OSGetArenaLo(void) { return arena_lo; }
void* OSGetArenaHi(void) { return arena_hi; }
void  OSSetArenaLo(void* lo) { arena_lo = (u8*)lo; }
void  OSSetArenaHi(void* hi) { arena_hi = (u8*)hi; }

/* --- Time/clock --- */
u32 pc_OSBusClock  = GC_BUS_CLOCK;
u32 pc_OSCoreClock = GC_CORE_CLOCK;

static u64 time_base_start = 0;
static s64 gc_epoch_offset_ticks = 0; /* Ticks from GC epoch to program start */

/* GC epoch: Jan 1, 2000 (946684800 seconds after Unix epoch) */
#define GC_UNIX_EPOCH_DIFF 946684800LL

s64 osGetTime(void) {
    u64 now = SDL_GetPerformanceCounter();
    u64 freq = SDL_GetPerformanceFrequency();
    s64 elapsed = (s64)((now - time_base_start) * (u64)GC_TIMER_CLOCK / freq);
    return gc_epoch_offset_ticks + elapsed;
}

s64 OSGetTime(void) { return osGetTime(); }

/* same as OSGetTime on PC (no time_adjust needed) */
s64 __OSGetSystemTime(void) { return OSGetTime(); }

u32 osGetCount(void) {
    return (u32)osGetTime();
}

u32 OSGetTick(void) { return osGetCount(); }

/* --- Calendar time (ported from OSTime.c) --- */
#define OS_TIMER_CLOCK          GC_TIMER_CLOCK
#define OSSecondsToTicks(sec)   ((s64)(sec) * (s64)OS_TIMER_CLOCK)
#define OSTicksToSeconds(ticks) ((s64)(ticks) / (s64)OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((s64)(msec) * (s64)(OS_TIMER_CLOCK / 1000))
#define OSTicksToMilliseconds(ticks) ((s64)(ticks) / (s64)(OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((s64)(usec) * (s64)(OS_TIMER_CLOCK / 125000)) / 8)
#define OSTicksToMicroseconds(ticks) (((s64)(ticks) * 8) / (s64)(OS_TIMER_CLOCK / 125000))

#define MONTH_MAX    12
#define WEEK_DAY_MAX 7
#define YEAR_DAY_MAX 365
#define USEC_MAX     1000
#define MSEC_MAX     1000
#define SECS_IN_MIN  60
#define SECS_IN_HOUR (60 * 60)
#define SECS_IN_DAY  (60 * 60 * 24)
#define SECS_IN_YEAR (SECS_IN_DAY * 365)
/* Days from March 1, year 0 (proleptic Gregorian) to Jan 1, 2000 (GC epoch).
 * = 2000*365 + floor(2000/4) - floor(2000/100) + floor(2000/400) = 730485 */
#define BIAS         0xB2575

static int YearDays_os[MONTH_MAX]
    = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
static int LeapYearDays_os[MONTH_MAX]
    = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

static int IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int GetYearDays(int year, int mon) {
    int* md = IsLeapYear(year) ? LeapYearDays_os : YearDays_os;
    return md[mon];
}

static int GetLeapDays(int year) {
    if (year < 1) return 0;
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

static void GetDates(int days, void* td_ptr) {
    int* td = (int*)td_ptr;
    int year, n, month;
    int* md;

    td[6] = (days + 6) % WEEK_DAY_MAX;  /* wday */

    for (year = days / YEAR_DAY_MAX;
         days < (n = year * YEAR_DAY_MAX + GetLeapDays(year)); year--)
        ;

    days -= n;
    td[5] = year;   /* year */
    td[7] = days;   /* yday */

    md = IsLeapYear(year) ? LeapYearDays_os : YearDays_os;
    for (month = MONTH_MAX; days < md[--month]; )
        ;
    td[4] = month;               /* mon */
    td[3] = days - md[month] + 1; /* mday */
}

void OSTicksToCalendarTime(s64 ticks, void* td_ptr) {
    int* td = (int*)td_ptr;
    int days, secs;
    s64 d;

    d = ticks % OSSecondsToTicks(1);
    if (d < 0) {
        d += OSSecondsToTicks(1);
    }

    td[9] = (int)(OSTicksToMicroseconds(d) % USEC_MAX); /* usec */
    td[8] = (int)(OSTicksToMilliseconds(d) % MSEC_MAX); /* msec */

    ticks -= d;

    days = (int)(OSTicksToSeconds(ticks) / SECS_IN_DAY) + BIAS;
    secs = (int)(OSTicksToSeconds(ticks) % SECS_IN_DAY);
    if (secs < 0) {
        days -= 1;
        secs += SECS_IN_DAY;
    }

    GetDates(days, td);
    td[2] = secs / 60 / 60;  /* hour */
    td[1] = secs / 60 % 60;  /* min */
    td[0] = secs % 60;       /* sec */
}

s64 OSCalendarTimeToTicks(void* td_ptr) {
    int* td = (int*)td_ptr;
    s64 secs;
    int ov_mon, mon, year;

    ov_mon = td[4] / MONTH_MAX;  /* mon / 12 */
    mon = td[4] - (ov_mon * MONTH_MAX);

    if (mon < 0) {
        mon += MONTH_MAX;
        ov_mon--;
    }

    year = td[5] + ov_mon;  /* year + overflow months as years */

    secs = (s64)SECS_IN_YEAR * year +
           (s64)SECS_IN_DAY * (GetLeapDays(year) + GetYearDays(year, mon) + td[3] - 1) +
           (s64)SECS_IN_HOUR * td[2] +
           (s64)SECS_IN_MIN * td[1] +
           td[0] -
           (s64)0xEB1E1BF80ULL;

    return OSSecondsToTicks(secs) + OSMillisecondsToTicks((s64)td[8]) +
           OSMicrosecondsToTicks((s64)td[9]);
}

void OSGetSaveRegion(void** start, void** end) {
    *start = NULL;
    *end = NULL;
}

/* --- Threads (single-threaded, all no-ops) --- */
typedef struct OSThread {
    void* stackBase;
    void* stackEnd;
    int priority;
    /* ... rest omitted, game accesses via pointers */
    u8 _pad[512]; /* padding for fields the game might access */
} OSThread_PC;

static OSThread_PC main_thread;
static OSThread_PC* current_thread = &main_thread;

/* N64 libultra message queue wrappers → Dolphin OS */
void OSInitMessageQueue(void* queue, void** msgArray, int msgCount);
BOOL OSSendMessage(void* queue, void* msg, int flags);
BOOL OSReceiveMessage(void* queue, void** msgPtr, int flags);

void osCreateMesgQueue(void* mq, void* buf, int count) {
    OSInitMessageQueue(mq, (void**)buf, count);
}

int osSendMesg(void* mq, void* msg, int flags) {
    return OSSendMessage(mq, msg, flags) ? 0 : -1;
}

int osRecvMesg(void* mq, void** msg, int flags) {
    return OSReceiveMessage(mq, msg, flags) ? 0 : -1;
}

static void (*pending_thread_entry)(void*) = NULL;
static void* pending_thread_arg = NULL;

void osCreateThread2(void* thread, int id, void (*entry)(void*), void* arg,
                     void* stack, int stack_size, int priority) {
    (void)thread; (void)id; (void)stack; (void)stack_size; (void)priority;
    pending_thread_entry = entry;
    pending_thread_arg = arg;
}

void osStartThread(void* thread) {
    /* don't actually start threads — single-threaded mode */
    (void)thread;
    pending_thread_entry = NULL;
    pending_thread_arg = NULL;
}

void osSetThreadPri(void* thread, int pri) { (void)thread; (void)pri; }
void* OSGetCurrentThread(void) { return current_thread; }
void* OSGetStackPointer(void) { return &arena_memory; /* dummy */ }

/* --- Interrupts --- */
BOOL OSDisableInterrupts(void) { return 0; }
BOOL OSEnableInterrupts(void) { return 0; }
BOOL OSRestoreInterrupts(BOOL level) { return level; }

/* --- Cache (no-ops on PC) --- */
void DCFlushRange(void* addr, u32 len) { (void)addr; (void)len; }
void DCTouchRange(void* addr, u32 len) { (void)addr; (void)len; }
void DCStoreRange(void* addr, u32 len) { (void)addr; (void)len; }
void DCInvalidateRange(void* addr, u32 len) { (void)addr; (void)len; }
void DCFlushRangeNoSync(void* addr, u32 len) { (void)addr; (void)len; }
void DCStoreRangeNoSync(void* addr, u32 len) { (void)addr; (void)len; }
void DCZeroRange(void* addr, u32 len) { memset(addr, 0, len); }
void ICFlashInvalidate(void) {}
void ICInvalidateRange(void* addr, u32 len) { (void)addr; (void)len; }
void LCEnable(void) {}
void LCDisable(void) {}

/* --- Init --- */
void OSInit(void) {
    if (!arena_memory) {
        /* alloc arena — on 64-bit, any mmap/VirtualAlloc returns high addresses
         * naturally (well above 0x0FFFFFFF), so no fixed-address loop needed.
         * On 32-bit, alloc at >=0x10000000 to avoid collision with N64 segment addresses. */
#if UINTPTR_MAX > 0xFFFFFFFFu
        /* 64-bit: let OS choose address (will be above N64 segment range) */
#ifdef _WIN32
        arena_memory = (u8*)VirtualAlloc(NULL,
            PC_MAIN_MEMORY_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
        arena_memory = (u8*)mmap(NULL, PC_MAIN_MEMORY_SIZE,
            PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (arena_memory == MAP_FAILED) arena_memory = NULL;
#endif
#else
        /* 32-bit: try fixed addresses above N64 segment range */
        {
            u32 base;
            for (base = 0x10000000; base <= 0x50000000; base += 0x01000000) {
#ifdef _WIN32
                arena_memory = (u8*)VirtualAlloc((void*)(uintptr_t)base,
                    PC_MAIN_MEMORY_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#else
                #ifndef MAP_FIXED_NOREPLACE
                #define MAP_FIXED_NOREPLACE 0x100000
                #endif
                arena_memory = (u8*)mmap((void*)(uintptr_t)base, PC_MAIN_MEMORY_SIZE,
                    PROT_READ | PROT_WRITE,
                    MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED_NOREPLACE, -1, 0);
                if (arena_memory == MAP_FAILED) arena_memory = NULL;
#endif
                if (arena_memory) break;
            }
        }
#endif
        if (!arena_memory) {
            /* fallback (may cause seg2k0 issues on 32-bit) */
            fprintf(stderr, "[PC] WARNING: memory allocation at high address failed, "
                            "falling back to malloc (seg2k0 may misfire)\n");
            arena_memory = (u8*)malloc(PC_MAIN_MEMORY_SIZE);
        }
        if (!arena_memory) {
            fprintf(stderr, "Failed to allocate main memory arena\n");
            exit(1);
        }
        memset(arena_memory, 0, PC_MAIN_MEMORY_SIZE);

        pc_arena_base = arena_memory;
        pc_arena_end  = arena_memory + PC_MAIN_MEMORY_SIZE;

        /* GC system info at phys addr 0; offset 0x28 = mem size for JKRHeap */
        *(u32*)(arena_memory + 0x28) = PC_MAIN_MEMORY_SIZE;

        arena_lo = arena_memory + 0x3100;
        arena_hi = arena_memory + PC_MAIN_MEMORY_SIZE;
    }
    time_base_start = SDL_GetPerformanceCounter();
    /* compute ticks from GC epoch (Jan 1, 2000) to now, with timezone */
    {
        time_t unix_now = time(NULL);

        struct tm* gmt = gmtime(&unix_now);
        if (!gmt) { gc_epoch_offset_ticks = 0; return; }
        struct tm utc_tm = *gmt;
        utc_tm.tm_isdst = -1; /* let mktime determine DST */
        time_t utc_as_local = mktime(&utc_tm);
        s64 tz_offset_secs = (s64)difftime(unix_now, utc_as_local);

        if (g_pc_time_override >= 0) {
            /* --time H[:M[:S]] override */
            struct tm* lt = localtime(&unix_now);
            if (lt) {
                unix_now += (g_pc_time_override - lt->tm_hour) * 3600;
                if (g_pc_min_override >= 0)
                    unix_now += (g_pc_min_override - lt->tm_min) * 60;
                if (g_pc_sec_override >= 0)
                    unix_now += (g_pc_sec_override - lt->tm_sec);
            }
        }

        s64 gc_secs = (s64)(unix_now - GC_UNIX_EPOCH_DIFF) + tz_offset_secs;
        gc_epoch_offset_ticks = gc_secs * (s64)GC_TIMER_CLOCK;
    }
}

void OSInitAlarm(void) { }

void __osInitialize_common(void) { }
void __OSPSInit(void) {}
void __OSFPRInit(void) {}
void __OSCacheInit(void) {}

u32 OSGetConsoleType(void) { return 0x10000004; /* OS_CONSOLE_DEVHW1 */ }

void OSPanic(const char* file, int line, const char* msg, ...) {
    va_list args;
    fprintf(stderr, "OSPanic at %s:%d: ", file, line);
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void OSReport(const char* fmt, ...) {
    if (!g_pc_verbose) return;
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}

void OSVReport(const char* fmt, va_list list) {
    if (!g_pc_verbose) return;
    vprintf(fmt, list);
}

void OSReportDisable(void) {}

/* --- Alarms --- */
typedef struct OSAlarm { u8 _pad[64]; } OSAlarm;
void OSSetAlarm(OSAlarm* alarm, s64 tick, void (*callback)(OSAlarm*, void*)) {
    (void)alarm; (void)tick; (void)callback;
}
void OSSetPeriodicAlarm(OSAlarm* alarm, s64 start, s64 period, void (*callback)(OSAlarm*, void*)) {
    (void)alarm; (void)start; (void)period; (void)callback;
}
void OSCancelAlarm(OSAlarm* alarm) { (void)alarm; }
void OSCreateAlarm(OSAlarm* alarm) { memset(alarm, 0, sizeof(OSAlarm)); }

/* --- Reset --- */
BOOL OSGetResetSwitchState(void) { return FALSE; }
void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu) {
    g_pc_running = 0;
}
u32 OSGetResetCode(void) { return 0; }
void OSChangeBootMode(u32 mode) { (void)mode; }

int __osResetSwitchPressed = 0;

/* --- Address translation (physical addr → arena_memory offset) --- */
void* OSPhysicalToCached(u32 paddr) { return (void*)(arena_memory + paddr); }
void* OSPhysicalToUncached(u32 paddr) { return (void*)(arena_memory + paddr); }
u32 OSCachedToPhysical(void* caddr) { return (u32)(uintptr_t)((u8*)caddr - arena_memory); }
u32 OSUncachedToPhysical(void* ucaddr) { return (u32)(uintptr_t)((u8*)ucaddr - arena_memory); }
void* OSCachedToUncached(void* caddr) { return caddr; }
void* OSUncachedToCached(void* ucaddr) { return ucaddr; }

s32 osAppNMIBuffer[64] = {0};

/* --- Misc --- */
void osShutdownStart(int type) {
    g_pc_running = 0;
}

int osShutdown = 0;

void ReconfigBATs(void) {}

void OSSetStringTable(void* table) { (void)table; }

typedef struct OSSramEx { u8 data[64]; } OSSramEx;
OSSramEx* __OSLockSramEx(void) {
    static OSSramEx sramex = {0};
    return &sramex;
}
void __OSUnlockSramEx(BOOL commit) { (void)commit; }

void msleep(int ms) { SDL_Delay(ms); }

typedef struct OSMutex { int lock; } OSMutex;
void OSInitMutex(OSMutex* mutex) { mutex->lock = 0; }
void OSLockMutex(OSMutex* mutex) { mutex->lock = 1; }
void OSUnlockMutex(OSMutex* mutex) { mutex->lock = 0; }
BOOL OSTryLockMutex(OSMutex* mutex) {
    if (mutex->lock) return FALSE;
    mutex->lock = 1;
    return TRUE;
}

/* --- Message queue --- */
/* matches OSMessageQueue from dolphin/os/OSMessage.h */
typedef struct {
    u8  _threadQueues[16]; /* queueSend + queueReceive - unused on PC */
    void** msgArray;       /* _10 */
    int msgCount;          /* _14 */
    int firstIndex;        /* _18 */
    int usedCount;         /* _1C */
} OSMessageQueue_PC;

void OSInitMessageQueue(void* queue, void** msgArray, int msgCount) {
    OSMessageQueue_PC* mq = (OSMessageQueue_PC*)queue;
    memset(mq->_threadQueues, 0, 16);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

BOOL OSSendMessage(void* queue, void* msg, int flags) {
    OSMessageQueue_PC* mq = (OSMessageQueue_PC*)queue;
    if (mq->usedCount >= mq->msgCount) {
        /* full */
        return FALSE;
    }
    int idx = (mq->firstIndex + mq->usedCount) % mq->msgCount;
    mq->msgArray[idx] = msg;
    mq->usedCount++;
    return TRUE;
}

BOOL OSReceiveMessage(void* queue, void** msgPtr, int flags) {
    OSMessageQueue_PC* mq = (OSMessageQueue_PC*)queue;
    if (mq->usedCount == 0) {
        return FALSE;
    }
    if (msgPtr) {
        *msgPtr = mq->msgArray[mq->firstIndex];
    }
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    return TRUE;
}

BOOL OSJamMessage(void* queue, void* msg, int flags) {
    OSMessageQueue_PC* mq = (OSMessageQueue_PC*)queue;
    if (mq->usedCount >= mq->msgCount) {
        return FALSE;
    }
    mq->firstIndex = (mq->firstIndex - 1 + mq->msgCount) % mq->msgCount;
    mq->msgArray[mq->firstIndex] = msg;
    mq->usedCount++;
    return TRUE;
}

/* --- Heap --- */
volatile int __OSCurrHeap = -1;

void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps) {
    /* skip past heap descriptors */
    uintptr_t arraySize = (uintptr_t)maxHeaps * 24;
    uintptr_t newStart = ((uintptr_t)arenaStart + arraySize + 0x1F) & ~(uintptr_t)0x1F;
    return (void*)newStart;
}

void* OSAllocFromHeap(int heap, u32 size) { return malloc(size); }
void OSFreeToHeap(int heap, void* ptr) { free(ptr); }
int OSCreateHeap(void* lo, void* hi) { return 0; }
int OSSetCurrentHeap(int heap) { return 0; }

typedef struct OSContext { u8 _pad[1024]; } OSContext;
void OSClearContext(OSContext* ctx) { memset(ctx, 0, sizeof(OSContext)); }

void* __OSSetExceptionHandler(u8 type, void* handler) {
    (void)type; (void)handler;
    return NULL;
}

u32 OSGetPhysicalMemSize(void) { return PC_MAIN_MEMORY_SIZE; }
