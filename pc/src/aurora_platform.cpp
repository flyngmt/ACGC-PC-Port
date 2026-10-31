#include <dolphin/ar.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GXAurora.h>
#include <dolphin/os.h>

#include "boot.h"
#include "GBA/gba.h"
#include "pc_platform.h"
#include "pc_settings.h"
#include "borealis/io.hpp"
#include "borealis/log_c.h"

#include <SDL3/SDL.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace {

std::FILE* open_file(const char* path, const char* mode) {
#ifdef _MSC_VER
    std::FILE* file = nullptr;
    return fopen_s(&file, path, mode) == 0 ? file : nullptr;
#else
    return std::fopen(path, mode);
#endif
}

struct ThreadData {
    std::thread thread;
    std::mutex mutex;
    std::condition_variable resumed;
    void* (*entry)(void*) = nullptr;
    void* argument = nullptr;
    bool started = false;

    ~ThreadData() {
        if (thread.joinable()) {
            thread.detach();
        }
    }
};

struct MutexData {
    std::recursive_mutex mutex;
};

struct MessageQueueData {
    std::mutex mutex;
    std::condition_variable canSend;
    std::condition_variable canReceive;
};

struct ThreadQueueData {
    std::mutex mutex;
    std::condition_variable wake;
    uint64_t generation = 0;
};

struct AlarmData {
    std::atomic<uint64_t> generation{ 0 };
};

std::mutex& side_table_mutex() {
    static auto* mutex = new std::mutex;
    return *mutex;
}

template <typename Key, typename Value>
Value& side_table_value(std::unordered_map<Key*, std::unique_ptr<Value>>& table, Key* key) {
    std::lock_guard lock(side_table_mutex());
    auto [iterator, inserted] = table.try_emplace(key, nullptr);
    if (inserted) {
        iterator->second = std::make_unique<Value>();
    }
    return *iterator->second;
}

std::unordered_map<OSThread*, std::unique_ptr<ThreadData>>& thread_table() {
    static auto* table = new std::unordered_map<OSThread*, std::unique_ptr<ThreadData>>;
    return *table;
}

std::unordered_map<OSMutex*, std::unique_ptr<MutexData>>& mutex_table() {
    static auto* table = new std::unordered_map<OSMutex*, std::unique_ptr<MutexData>>;
    return *table;
}

std::unordered_map<OSMessageQueue*, std::unique_ptr<MessageQueueData>>& message_queue_table() {
    static auto* table = new std::unordered_map<OSMessageQueue*, std::unique_ptr<MessageQueueData>>;
    return *table;
}

std::unordered_map<OSThreadQueue*, std::unique_ptr<ThreadQueueData>>& thread_queue_table() {
    static auto* table = new std::unordered_map<OSThreadQueue*, std::unique_ptr<ThreadQueueData>>;
    return *table;
}

std::unordered_map<OSAlarm*, std::unique_ptr<AlarmData>>& alarm_table() {
    static auto* table = new std::unordered_map<OSAlarm*, std::unique_ptr<AlarmData>>;
    return *table;
}

ThreadData& thread_data(OSThread* thread) {
    return side_table_value(thread_table(), thread);
}
MutexData& mutex_data(OSMutex* mutex) {
    return side_table_value(mutex_table(), mutex);
}
MessageQueueData& message_queue_data(OSMessageQueue* queue) {
    return side_table_value(message_queue_table(), queue);
}
ThreadQueueData& thread_queue_data(OSThreadQueue* queue) {
    return side_table_value(thread_queue_table(), queue);
}
AlarmData& alarm_data(OSAlarm* alarm) {
    return side_table_value(alarm_table(), alarm);
}

thread_local OSThread* current_thread;
OSThread main_thread{};
std::once_flag main_thread_once;
std::atomic<s32> active_thread_count{ 0 };
std::atomic<bool> interrupts_enabled{ true };

void initialize_main_thread() {
    std::memset(&main_thread, 0, sizeof(main_thread));
    main_thread.state = OS_THREAD_STATE_RUNNING;
    main_thread.priority = 16;
    main_thread.base = 16;
    current_thread = &main_thread;
    active_thread_count = 1;
}

void run_thread(OSThread* thread, ThreadData* data) {
    current_thread = thread;
    thread->state = OS_THREAD_STATE_RUNNING;
    thread->val = data->entry(data->argument);
    thread->state = OS_THREAD_STATE_MORIBUND;
    active_thread_count.fetch_sub(1);
}

std::atomic<size_t> malloc_arena_size{ 0 };
std::atomic<u32> sound_mode{ OS_SOUND_MODE_MONO };
std::atomic<u32> progressive_mode{ 0 };

struct VoidThreadStart {
    void (*entry)(void*);
    void* argument;
};

void* run_void_thread(void* raw_start) {
    std::unique_ptr<VoidThreadStart> start(static_cast<VoidThreadStart*>(raw_start));
    start->entry(start->argument);
    return nullptr;
}

struct PendingAlarm {
    OSAlarm* alarm;
    OSAlarmHandler handler;
    AlarmData* data;
    uint64_t generation;
};

struct AlarmScheduler {
    std::mutex mutex;
    std::condition_variable changed;
    std::multimap<std::chrono::steady_clock::time_point, PendingAlarm> pending;
};

void run_alarm_scheduler(AlarmScheduler* scheduler) {
    std::unique_lock lock(scheduler->mutex);
    for (;;) {
        if (scheduler->pending.empty()) {
            scheduler->changed.wait(lock);
            continue;
        }
        const auto next = scheduler->pending.begin();
        if (std::chrono::steady_clock::now() < next->first) {
            scheduler->changed.wait_until(lock, next->first);
            continue;
        }
        const PendingAlarm due = next->second;
        scheduler->pending.erase(next);
        lock.unlock();
        if (due.data->generation.load() == due.generation && due.handler != nullptr) {
            due.handler(due.alarm, nullptr);
        }
        lock.lock();
    }
}

AlarmScheduler& alarm_scheduler() {
    static auto* scheduler = [] {
        auto* created = new AlarmScheduler;
        std::thread(run_alarm_scheduler, created).detach();
        return created;
    }();
    return *scheduler;
}

void remove_pending_alarm(AlarmScheduler& scheduler, OSAlarm* alarm) {
    for (auto it = scheduler.pending.begin(); it != scheduler.pending.end();) {
        if (it->second.alarm == alarm) {
            it = scheduler.pending.erase(it);
        } else {
            ++it;
        }
    }
}

} // namespace

extern "C" {

extern int osShutdown;

OSModuleHeader* BaseModule = nullptr;
s32 osAppNMIBuffer[16] = {};

int g_pc_paused = 0;
int g_pc_pause_input_drain = 0;
int g_pc_nes_active = 0;

int pc_emu64_frame_cmds = 0;
int pc_emu64_frame_noop_cmds = 0;
int pc_emu64_frame_tri_cmds = 0;
int pc_emu64_frame_vtx_cmds = 0;
int pc_emu64_frame_dl_cmds = 0;
int pc_emu64_frame_cull_visible = 0;
int pc_emu64_frame_cull_rejected = 0;

u16 s_tlut_first_word[16] = {};

void OSInitThreadQueue(OSThreadQueue* queue) {
    queue->head = nullptr;
    queue->tail = nullptr;
    (void)thread_queue_data(queue);
}

OSThread* OSGetCurrentThread() {
    std::call_once(main_thread_once, initialize_main_thread);
    return current_thread != nullptr ? current_thread : &main_thread;
}

BOOL OSCreateThread(OSThread* thread, void* (*entry)(void*), void* argument, void* stack, u32 stack_size,
                    OSPriority priority, u16 attributes) {
    if (thread == nullptr || entry == nullptr || priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return FALSE;
    }
    OSGetCurrentThread();
    std::memset(thread, 0, sizeof(*thread));
    thread->state = OS_THREAD_STATE_READY;
    thread->attr = attributes & OS_THREAD_ATTR_DETACH;
    thread->suspend = 1;
    thread->priority = priority;
    thread->base = priority;
    thread->stackBase = static_cast<u8*>(stack);
    thread->stackEnd = static_cast<u8*>(stack) - stack_size;
    OSInitThreadQueue(&thread->queueJoin);

    ThreadData& data = thread_data(thread);
    data.entry = entry;
    data.argument = argument;
    data.started = false;
    active_thread_count.fetch_add(1);
    return TRUE;
}

s32 OSResumeThread(OSThread* thread) {
    if (thread == nullptr) {
        return 0;
    }
    ThreadData& data = thread_data(thread);
    std::lock_guard lock(data.mutex);
    const s32 previous = thread->suspend;
    if (thread->suspend > 0) {
        --thread->suspend;
    }
    if (thread->suspend == 0 && !data.started) {
        data.started = true;
        data.thread = std::thread(run_thread, thread, &data);
        if ((thread->attr & OS_THREAD_ATTR_DETACH) != 0) {
            data.thread.detach();
        }
    }
    data.resumed.notify_all();
    return previous;
}

s32 OSSuspendThread(OSThread* thread) {
    if (thread == nullptr) {
        return 0;
    }
    ThreadData& data = thread_data(thread);
    std::unique_lock lock(data.mutex);
    const s32 previous = thread->suspend;
    ++thread->suspend;
    if (thread == OSGetCurrentThread()) {
        thread->state = OS_THREAD_STATE_WAITING;
        data.resumed.wait(lock, [thread] { return thread->suspend == 0; });
        thread->state = OS_THREAD_STATE_RUNNING;
    }
    return previous;
}

void OSCancelThread(OSThread* thread) {
    if (thread == nullptr) {
        return;
    }
    ThreadData& data = thread_data(thread);
    if (data.thread.joinable()) {
        data.thread.detach();
    }
    thread->state = OS_THREAD_STATE_MORIBUND;
}

void OSDetachThread(OSThread* thread) {
    if (thread == nullptr) {
        return;
    }
    thread->attr |= OS_THREAD_ATTR_DETACH;
    ThreadData& data = thread_data(thread);
    if (data.thread.joinable()) {
        data.thread.detach();
    }
}

BOOL OSJoinThread(OSThread* thread, void** value) {
    if (thread == nullptr) {
        return FALSE;
    }
    ThreadData& data = thread_data(thread);
    if (data.thread.joinable()) {
        data.thread.join();
    }
    if (value != nullptr) {
        *value = thread->val;
    }
    return TRUE;
}

BOOL OSIsThreadTerminated(OSThread* thread) {
    return thread == nullptr || thread->state == OS_THREAD_STATE_MORIBUND || thread->state == 0;
}

void OSYieldThread() {
    std::this_thread::yield();
}
s32 OSCheckActiveThreads() {
    return active_thread_count.load();
}
s32 OSEnableScheduler() {
    return 0;
}
s32 OSDisableScheduler() {
    return 0;
}

void OSSleepThread(OSThreadQueue* queue) {
    ThreadQueueData& data = thread_queue_data(queue);
    std::unique_lock lock(data.mutex);
    const uint64_t generation = data.generation;
    data.wake.wait(lock, [&] { return data.generation != generation; });
}

void OSWakeupThread(OSThreadQueue* queue) {
    ThreadQueueData& data = thread_queue_data(queue);
    {
        std::lock_guard lock(data.mutex);
        ++data.generation;
    }
    data.wake.notify_all();
}

void OSInitMutex(OSMutex* mutex) {
    OSInitThreadQueue(&mutex->queue);
    mutex->thread = nullptr;
    mutex->count = 0;
    (void)mutex_data(mutex);
}

void OSLockMutex(OSMutex* mutex) {
    mutex_data(mutex).mutex.lock();
    mutex->thread = OSGetCurrentThread();
    ++mutex->count;
}

BOOL OSTryLockMutex(OSMutex* mutex) {
    if (!mutex_data(mutex).mutex.try_lock()) {
        return FALSE;
    }
    mutex->thread = OSGetCurrentThread();
    ++mutex->count;
    return TRUE;
}

void OSUnlockMutex(OSMutex* mutex) {
    if (mutex == nullptr || mutex->count == 0) {
        return;
    }
    if (--mutex->count == 0) {
        mutex->thread = nullptr;
    }
    mutex_data(mutex).mutex.unlock();
}

void OSInitMessageQueue(OSMessageQueue* queue, OSMessage* messages, s32 count) {
    queue->msgArray = messages;
    queue->msgCount = count;
    queue->firstIndex = 0;
    queue->usedCount = 0;
    OSInitThreadQueue(&queue->queueSend);
    OSInitThreadQueue(&queue->queueReceive);
    (void)message_queue_data(queue);
}

BOOL OSSendMessage(OSMessageQueue* queue, OSMessage message, s32 flags) {
    if (queue == nullptr || queue->msgCount <= 0) {
        return FALSE;
    }
    MessageQueueData& data = message_queue_data(queue);
    std::unique_lock lock(data.mutex);
    if (flags == OS_MESSAGE_BLOCK) {
        data.canSend.wait(lock, [queue] { return queue->usedCount < queue->msgCount; });
    } else if (queue->usedCount >= queue->msgCount) {
        return FALSE;
    }
    const s32 index = (queue->firstIndex + queue->usedCount) % queue->msgCount;
    queue->msgArray[index] = message;
    ++queue->usedCount;
    lock.unlock();
    data.canReceive.notify_one();
    return TRUE;
}

BOOL OSReceiveMessage(OSMessageQueue* queue, OSMessage* message, s32 flags) {
    if (queue == nullptr || queue->msgCount <= 0) {
        return FALSE;
    }
    MessageQueueData& data = message_queue_data(queue);
    std::unique_lock lock(data.mutex);
    if (flags == OS_MESSAGE_BLOCK) {
        data.canReceive.wait(lock, [queue] { return queue->usedCount > 0; });
    } else if (queue->usedCount == 0) {
        return FALSE;
    }
    if (message != nullptr) {
        *message = queue->msgArray[queue->firstIndex];
    }
    queue->firstIndex = (queue->firstIndex + 1) % queue->msgCount;
    --queue->usedCount;
    lock.unlock();
    data.canSend.notify_one();
    return TRUE;
}

BOOL OSJamMessage(OSMessageQueue* queue, OSMessage message, s32 flags) {
    if (queue == nullptr || queue->msgCount <= 0) {
        return FALSE;
    }
    MessageQueueData& data = message_queue_data(queue);
    std::unique_lock lock(data.mutex);
    if (flags == OS_MESSAGE_BLOCK) {
        data.canSend.wait(lock, [queue] { return queue->usedCount < queue->msgCount; });
    } else if (queue->usedCount >= queue->msgCount) {
        return FALSE;
    }
    queue->firstIndex = (queue->firstIndex - 1 + queue->msgCount) % queue->msgCount;
    queue->msgArray[queue->firstIndex] = message;
    ++queue->usedCount;
    lock.unlock();
    data.canReceive.notify_one();
    return TRUE;
}

BOOL OSDisableInterrupts() {
    return interrupts_enabled.exchange(false) ? TRUE : FALSE;
}
BOOL OSEnableInterrupts() {
    return interrupts_enabled.exchange(true) ? TRUE : FALSE;
}
BOOL OSRestoreInterrupts(BOOL enabled) {
    return interrupts_enabled.exchange(enabled != FALSE) ? TRUE : FALSE;
}

void OSInitAlarm() {
}

void OSCreateAlarm(OSAlarm* alarm) {
    std::memset(alarm, 0, sizeof(*alarm));
    ++alarm_data(alarm).generation;
}

void OSSetAlarm(OSAlarm* alarm, OSTime ticks, OSAlarmHandler handler) {
    alarm->handler = handler;
    AlarmData& data = alarm_data(alarm);
    const uint64_t generation = ++data.generation;
    const auto duration = std::chrono::nanoseconds(
        static_cast<int64_t>((static_cast<long double>(ticks) * 1'000'000'000.0L) / OS_TIMER_CLOCK));
    const auto deadline = std::chrono::steady_clock::now() + duration;
    AlarmScheduler& scheduler = alarm_scheduler();
    {
        std::lock_guard lock(scheduler.mutex);
        remove_pending_alarm(scheduler, alarm);
        scheduler.pending.emplace(deadline, PendingAlarm{ alarm, handler, &data, generation });
    }
    scheduler.changed.notify_one();
}

void OSCancelAlarm(OSAlarm* alarm) {
    ++alarm_data(alarm).generation;
    AlarmScheduler& scheduler = alarm_scheduler();
    std::lock_guard lock(scheduler.mutex);
    remove_pending_alarm(scheduler, alarm);
}

void DCFlushRange(void*, u32) {
}
void DCFlushRangeNoSync(void*, u32) {
}
void DCInvalidateRange(void*, u32) {
}
void DCStoreRange(void*, u32) {
}
void DCStoreRangeNoSync(void*, u32) {
}
void DCTouchRange(void*, u32) {
}
void DCZeroRange(void* address, u32 size) {
    std::memset(address, 0, size);
}

void OSReport(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    OSVReport(format, arguments);
    va_end(arguments);
}

void OSVReport(const char* format, va_list arguments) {
    borealis_log_vprintf(BOREALIS_LOG_INFO, "game", format, arguments);
}

void OSPanic(const char* file, int line, const char* format, ...) {
    borealis_log_printf(BOREALIS_LOG_ERROR, "game", "Animal Crossing panic at %s:%d", file, line);
    va_list arguments;
    va_start(arguments, format);
    borealis_log_vprintf(BOREALIS_LOG_ERROR, "game", format, arguments);
    va_end(arguments);
    borealis_log_printf(BOREALIS_LOG_FATAL, "game", "Aborting after OSPanic");
    std::abort();
}

void OSReportDisable() {
}
void OSReportEnable() {
}
u16 OSGetFontEncode() {
    return OS_FONT_ENCODE_ANSI;
}
u32 OSGetSoundMode() {
    return sound_mode.load();
}
void OSSetSoundMode(u32 mode) {
    sound_mode = mode;
}
u32 OSGetProgressiveMode() {
    return progressive_mode.load();
}
void OSSetProgressiveMode(u32 enabled) {
    progressive_mode = enabled;
}
void OSProtectRange(u32, void*, u32, u32) {
}
void OSFillFPUContext(OSContext*) {
}

u32 __OSFpscrEnableBits = 0;
OSErrorHandler __OSErrorTable[17] = {};
OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    if (error >= OS_ERROR_MAX) {
        return nullptr;
    }
    OSErrorHandler previous = __OSErrorTable[error];
    __OSErrorTable[error] = handler;
    return previous;
}

u32 OSGetConsoleType() {
    return OS_CONSOLE_DEVHW1;
}
BOOL OSGetResetSwitchState() {
    return FALSE;
}
u32 OSGetResetCode() {
    return 0;
}
void OSChangeBootMode(u32) {
}
void OSResetSystem(int, u32, BOOL) {
    g_pc_running = 0;
}
void OSGetSaveRegion(void** start, void** end) {
    *start = nullptr;
    *end = nullptr;
}
u32 OSGetStackPointer() {
    return 0;
}
void OSSetStringTable(void*) {
}
BOOL OSLink(OSModuleInfo*, void*) {
    return TRUE;
}
BOOL OSUnlink(OSModuleInfo*) {
    return TRUE;
}

u32 PPCMfmsr() {
    return 0;
}
void PPCMtmsr(u32) {
}
void PPCSync() {
}

OSThread* GXSetCurrentGXThread() {
    return OSGetCurrentThread();
}
void GXAbortFrame() {
}
void GXReadXfRasMetric(u32* xf_wait_in, u32* xf_wait_out, u32* ras_busy, u32* clocks) {
    if (xf_wait_in)
        *xf_wait_in = 0;
    if (xf_wait_out)
        *xf_wait_out = 0;
    if (ras_busy)
        *ras_busy = 0;
    if (clocks)
        *clocks = 0;
}

u32 ARGetBaseAddress() {
    return 0;
}

OSTime osGetTime() {
    return OSGetTime();
}
u32 osGetCount() {
    return OSGetTick();
}

void osSyncPrintf(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    OSVReport(format, arguments);
    va_end(arguments);
}

void osWritebackDCache(void* address, u32 size) {
    DCStoreRange(address, size);
}

/* Aurora does not currently expose a GBA-link transport. Report the device as
 * unavailable while keeping the game's optional e-Reader/link flow benign. */
void GBAInit() {
}
s32 GBAGetStatus(s32, u8*) {
    return -1;
}
s32 GBAGetProcessStatus(s32, u8*) {
    return -1;
}
s32 GBARead(s32, u8*, u8*) {
    return -1;
}
s32 GBAWrite(s32, u8*, u8*) {
    return -1;
}
s32 GBAReset(s32, u8*) {
    return -1;
}
s32 GBAJoyBootAsync(s32, s32, s32, u8*, s32, u8*, GBACallback) {
    return -1;
}

int __abs(int value) {
    return value < 0 ? -value : value;
}
void _strip(float) {
}

#ifdef _WIN32
int bcmp(const void* first, const void* second, size_t size) {
    return std::memcmp(first, second, size);
}

void bcopy(const void* source, void* destination, size_t size) {
    std::memmove(destination, source, size);
}

void bzero(void* destination, size_t size) {
    std::memset(destination, 0, size);
}
#endif

void osCreateMesgQueue(OSMessageQueue* queue, OSMessage messages, int count) {
    OSInitMessageQueue(queue, static_cast<OSMessage*>(messages), count);
}
int osSendMesg(OSMessageQueue* queue, OSMessage message, int flags) {
    return OSSendMessage(queue, message, flags) ? 0 : -1;
}
int osRecvMesg(OSMessageQueue* queue, OSMessage* message, int flags) {
    return OSReceiveMessage(queue, message, flags) ? 0 : -1;
}

void osCreateThread2(OSThread* thread, s32, void (*entry)(void*), void* argument, void* stack, size_t stack_size,
                     OSPriority priority) {
    auto start = std::make_unique<VoidThreadStart>(VoidThreadStart{ entry, argument });
    if (OSCreateThread(thread, run_void_thread, start.get(), stack, static_cast<u32>(stack_size), priority,
                       OS_THREAD_ATTR_DETACH)) {
        start.release();
    }
}
void osStartThread(OSThread* thread) {
    OSResumeThread(thread);
}
void osSetThreadPri(OSThread* thread, s32 priority) {
    OSThread* target = thread != nullptr ? thread : OSGetCurrentThread();
    target->priority = priority;
}
void osShutdownStart(int) {
    osShutdown = 1;
}

void MallocInit(void*, size_t size) {
    malloc_arena_size = size;
}
void MallocCleanup() {
    malloc_arena_size = 0;
}
void GetFreeArena(size_t* max_size, size_t* free_size, size_t* alloc_size) {
    if (max_size)
        *max_size = malloc_arena_size.load();
    if (free_size)
        *free_size = malloc_arena_size.load();
    if (alloc_size)
        *alloc_size = 0;
}
void DisplayArena() {
}

void ReconfigBATs() {
}
void OSDVDFatalError() {
    std::fprintf(stderr, "Fatal DVD read error\n");
}
void msleep(int milliseconds) {
    SDL_Delay(static_cast<Uint32>(milliseconds));
}

int pc_platform_flush_file(FILE* file) {
    if (std::fflush(file) != 0) return false;
#ifdef _WIN32
    return _commit(_fileno(file)) == 0;
#else
    return fsync(fileno(file)) == 0;
#endif
}

int pc_platform_next_gci(const char* directory_path, char* filename, int filename_size) {
    if (directory_path == nullptr || filename == nullptr || filename_size <= 0) return 0;
    const std::string previous{filename};
    std::string next;
    std::error_code error;
    std::filesystem::directory_iterator entry{directory_path, error};
    for (; !error && entry != std::filesystem::directory_iterator{}; entry.increment(error)) {
        if (!entry->is_regular_file(error) || entry->path().extension() != ".gci") continue;
        const std::string name = borealis::io::fs_path_to_string(entry->path().filename());
        if (name <= previous || (!next.empty() && name >= next) ||
            name.size() + 1 > static_cast<size_t>(filename_size)) continue;

        FILE* file = open_file(borealis::io::fs_path_to_string(entry->path()).c_str(), "rb");
        if (file == nullptr) continue;
        u8 header[4] = {};
        const bool valid = std::fread(header, 1, sizeof(header), file) == sizeof(header) &&
                           header[0] == 'G' && header[1] == 'A' && header[2] == 'F';
        std::fclose(file);
        if (!valid) continue;

        next = name;
    }
    if (error || next.empty()) return 0;
    std::memcpy(filename, next.c_str(), next.size() + 1);
    return 1;
}

} // extern "C"
