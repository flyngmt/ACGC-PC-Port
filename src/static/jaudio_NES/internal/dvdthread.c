#include "jaudio_NES/dvdthread.h"
#include "jaudio_NES/sample.h"
#include "jaudio_NES/aictrl.h"
#include "dolphin/os.h"
#include "dolphin/dvd.h"
#include "dolphin/ar.h"
#include "string.h"
#include "dolphin/os/OSTime.h"

typedef struct DVDCall_ {
    u32 owner;
    char fileName[64];
    u32 dst;
    u32 src;
    u32 length;
    u32* callbackStatus;
    Jac_DVDCallback callback;
} DVDCall;

static char audio_root_path[32] = "";

static ErrorCallback error_callback;

#ifdef TARGET_PC
/*==========================================================================
 * PC: Synchronous DVD task queue — tasks execute immediately inline.
 * No message queue, no thread. Task stack stored in a simple circular buffer.
 *==========================================================================*/
static u8 CALLSTACK[0x8000];
static u32 cur_q = 0;
static u32 mq_init = 0;

/* Task queue for deferred execution */
#define PC_TASK_QUEUE_SIZE 128
static void* pc_task_queue[PC_TASK_QUEUE_SIZE];
static u32 pc_task_read = 0;
static u32 pc_task_write = 0;

/* DVD read buffers */
static u8* ADVD_BUFFER[2];
static size_t buffersize = 0;
static u32 buffers = 0;
static u32 buffer_load = 0;

static void* GetCallStack() {
    void* ret = &CALLSTACK[cur_q * 0x100];
    cur_q = (cur_q + 1) % 0x80;
    return ret;
}

static void __WriteBufferSize(u8* buf, u32 amount, u32 size) {
    buffersize = size;
    buffers = amount;
    for (u32 i = 0; i < amount; i++) {
        ADVD_BUFFER[i] = buf;
        buf += size;
    }
}

extern void DVDT_ExtendPath(char* dst, char* ext) {
    if (*audio_root_path != 0) {
        strcpy(dst, audio_root_path);
        if (*ext == '/') {
            strcat(dst, ext + 1);
        } else {
            strcat(dst, ext);
        }
    } else {
        strcpy(dst, ext);
    }
}

extern s32 DVDT_AddTaskHigh(TaskCallback callback, void* stackp, size_t len) {
    if (mq_init == 0) return 0;

    TaskCallback* stack = (TaskCallback*)GetCallStack();
    Jac_bcopy(stackp, stack + 1, len);
    *stack = callback;

    /* Queue the task for deferred execution */
    pc_task_queue[pc_task_write % PC_TASK_QUEUE_SIZE] = stack;
    pc_task_write++;
    return 1;
}

extern s32 DVDT_AddTask(TaskCallback callback, void* stackp, size_t len) {
    if (mq_init == 0) return 0;

    TaskCallback* stack = (TaskCallback*)GetCallStack();
    Jac_bcopy(stackp, stack + 1, len);
    *stack = callback;

    /* Queue the task for deferred execution */
    pc_task_queue[pc_task_write % PC_TASK_QUEUE_SIZE] = stack;
    pc_task_write++;
    return 1;
}

extern void jac_dvdproc_init() {
    mq_init = 1;
    pc_task_read = 0;
    pc_task_write = 0;

    /* Allocate read buffer */
    static u8 dvd_buf[0x10000];
    __WriteBufferSize(dvd_buf, 2, 0x8000);
}

/* Process all pending DVD tasks synchronously */
void pc_dvd_process_all_tasks(void) {
    while (pc_task_read < pc_task_write) {
        TaskCallback* callback = (TaskCallback*)pc_task_queue[pc_task_read % PC_TASK_QUEUE_SIZE];
        pc_task_read++;
        if (callback != nullptr) {
            (*callback)(callback + 1);
        }
    }
}

extern void* jac_dvdproc(void* arg) {
    /* Not used on PC — synchronous model */
    (void)arg;
    return nullptr;
}

static void __DoError(DVDCall* call, u32 type) {
    if (call->callbackStatus != nullptr) {
        *call->callbackStatus = (u32)-1;
    }
    if (call->callback != nullptr) {
        call->callback((u32)-1);
    }
}

static void __DoFinish(DVDCall* call, u32 arg) {
    if (call->callbackStatus != nullptr) {
        *call->callbackStatus = arg;
    }
    if (call->callback != nullptr) {
        call->callback(call->owner);
    }
}

static void __DVDT_CheckBack(void* cb) {
    DVDCall* callback = (DVDCall*)cb;
    __DoFinish(callback, callback->owner);
}

extern s32 DVDT_LoadtoARAM_Main(void* arg) {
    DVDCall* call = (DVDCall*)arg;
    static DVDFileInfo finfo;

    if (!Jac_DVDOpen(call->fileName, &finfo)) {
        __DoError(call, 0);
        return -1;
    }

    u32 len = finfo.length;
    if (len == 0) {
        __DoError(call, 1);
        return -1;
    }

    if (call->length == 0) {
        call->length = len;
        if (call->src != 0) {
            call->length -= call->src;
        }
    }

    while (call->length != 0) {
        u32 readSize;
        u8* buf = ADVD_BUFFER[buffer_load];
        buffer_load = (buffer_load + 1) % buffers;

        if (call->length < buffersize) {
            readSize = (call->length + 31) & ~31;  /* ALIGN_NEXT(call->length, 32) */
            DVDReadPrio(&finfo, buf, readSize, call->src, 2);
            call->length = 0;
        } else {
            readSize = buffersize;
            DVDReadPrio(&finfo, buf, buffersize, call->src, 2);
            call->src += buffersize;
            call->length -= buffersize;
        }

        /* Copy to ARAM synchronously */
        ARQPostRequest(nullptr, 0x12345678, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH,
                       (uintptr_t)buf, call->dst, readSize, nullptr);
        call->dst += readSize;
    }

    DVDClose(&finfo);
    __DoFinish(call, len);
    return 0;
}

extern s32 DVDT_LoadtoARAM(u32 owner, char* name, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    call.owner = owner;
    DVDT_ExtendPath(call.fileName, name);
    call.dst = dst;
    call.callbackStatus = status;
    if (status != 0) *status = 0;
    call.callback = callback;
    call.src = src;
    call.length = length;

    DVDT_AddTask(DVDT_LoadtoARAM_Main, (void*)&call, 0x58);
    return 0;
}

extern s32 DVDT_ARAMtoDRAM_Main(void* arg) {
    DVDCall* call = (DVDCall*)arg;
    ARQPostRequest(nullptr, (uintptr_t)call, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH,
                   call->src, call->dst, call->length, nullptr);
    __DoFinish(call, call->length);
    return 0;
}

extern s32 DVDT_DRAMtoARAM_Main(void* arg) {
    DVDCall* call = (DVDCall*)arg;
    ARQPostRequest(nullptr, (uintptr_t)call, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH,
                   call->dst, call->src, call->length, nullptr);
    __DoFinish(call, call->length);
    return 0;
}

extern s32 DVDT_ARAMtoDRAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    call.owner = owner;
    call.dst = dst;
    call.callbackStatus = status;
    if (status != 0) *status = 0;
    call.callback = callback;
    call.src = src;
    call.length = length;
    DVDT_AddTaskHigh(DVDT_ARAMtoDRAM_Main, (void*)&call, 0x58);
    return 0;
}

extern s32 DVDT_DRAMtoARAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    call.owner = owner;
    call.dst = dst;
    call.callbackStatus = status;
    if (status != 0) *status = 0;
    call.callback = callback;
    call.src = src;
    call.length = length;
    DVDT_AddTaskHigh(DVDT_DRAMtoARAM_Main, (void*)&call, 0x58);
    return 0;
}

#else /* !TARGET_PC — original GC code */

static OSMessageQueue mq;
static s32 msgbuf[0x80];
static u8 CALLSTACK[0x8000];

static u32 mq_init;
static size_t buffersize;
static u32 buffers;
static size_t next_buffersize;
static u8* next_buffertop;
static u32 next_buffers;
static u32 cur_q;
static OSThreadQueue dvdt_sleep;
static BOOL DVDT_PAUSE_FLAG;

static u8* ADVD_BUFFER[2];
static u32 buffer_load;

static void __Alloc_DVDBuffer();
static void __UpdateBuffer();
static void __WriteBufferSize(u8* buf, u32 amount, u32 size);

static void* GetCallStack() {
    BOOL enable = OSDisableInterrupts();
    void* ret;
    u32 pre = cur_q + 1;

    ret = &CALLSTACK[cur_q * 0x100];

    cur_q = pre;

    if (pre == 0x80) {
        cur_q = 0;
    }

    OSRestoreInterrupts(enable);

    return ret;
}

static s32 DVDReadMutex(DVDFileInfo* fileInfo, void* addr, s32 len, s32 offs, char* arg4) {
    if (DVDT_PAUSE_FLAG == true) {
        OSSleepThread(&dvdt_sleep);
    }

    while (true) {
        if (DVDReadPrio(fileInfo, addr, len, offs, 2) != -1 || error_callback == nullptr) {
            break;
        }
        error_callback(arg4, (u8*)addr);
    }
}

extern void DVDT_ExtendPath(char* dst, char* ext) {
    if (*audio_root_path != nullptr) {
        strcpy(dst, audio_root_path);
        if (*ext == '/') {
            strcat(dst, ext + 1);
        } else {
            strcat(dst, ext);
        }
    } else {
        strcpy(dst, ext);
    }
}

extern s32 DVDT_AddTaskHigh(TaskCallback callback, void* stackp, size_t len) {
    if (mq_init == false) {
        return 0;
    }

    TaskCallback* stack = (TaskCallback*)GetCallStack();

    Jac_bcopy(stackp, stack + 1, len);

    *stack = callback;
    OSJamMessage(&mq, (OSMessage)stack, OS_MESSAGE_BLOCK);

    return 1;
}

extern s32 DVDT_AddTask(TaskCallback callback, void* stackp, size_t len) {
    if (mq_init == false) {
        return 0;
    }

    TaskCallback* stack = (TaskCallback*)GetCallStack();

    Jac_bcopy(stackp, stack + 1, len);

    *stack = callback;
    OSSendMessage(&mq, (OSMessage)stack, OS_MESSAGE_BLOCK);

    return 1;
}

extern void jac_dvdproc_init() {
    OSInitMessageQueue(&mq, (OSMessage*)msgbuf, ARRAY_COUNT(msgbuf));
    mq_init = 1;
}

extern void* jac_dvdproc(void* arg) {
    __Alloc_DVDBuffer();
    TaskCallback* callback;

    u8* buf = (u8*)OSAlloc2(0x10000);

    OSInitThreadQueue(&dvdt_sleep);
    OSMessage msg;
    while (true) {
        while (true) {
            OSReceiveMessage(&mq, &msg, OS_MESSAGE_BLOCK);
            callback = (TaskCallback*)msg;
            __UpdateBuffer();

            if (buffersize == 0) {
                __WriteBufferSize(buf, 2, 0x8000);
            }
            if (callback != nullptr) {
                break;
            };
        }
        (*callback)(callback + 1);
    }
}

static void __DoError(DVDCall* call, u32 type) {
    if (call->callbackStatus != nullptr) {
        *call->callbackStatus = -1;
    }

    if (call->callback != nullptr) {
        call->callback(-1);
    }
}

static void __DoFinish(DVDCall* call, u32 arg) {
    if (call->callbackStatus != nullptr) {
        *call->callbackStatus = arg;
    }

    if (call->callback != nullptr) {
        call->callback(call->owner);
    }
}
static void __DVDT_CheckBack(void* cb) {
    DVDCall* callback = (DVDCall*)cb;

    __DoFinish(callback, callback->owner);
}

static void __Alloc_DVDBuffer() {
    if (buffersize == 0) {
        int i;

        for (i = 0; i < buffers; i++) {
            ADVD_BUFFER[i] = 0;
        }
    }
}

static void __WriteBufferSize(u8* buf, u32 amount, u32 size) {
    buffersize = size;
    buffers = amount;

    int i;
    int j = amount;

    for (i = 0; i < amount; i++, j--) {
        ADVD_BUFFER[i] = buf;
        buf += size;
    }
}

static void __UpdateBuffer() {
    if (next_buffers != 0) {
        __WriteBufferSize(next_buffertop, next_buffers, next_buffersize);
        next_buffers = 0;
        next_buffertop = nullptr;
    }
}

static vu32 buffer_full;

static void ARAM_DMAfinish(u32 arg0) {
    buffer_full -= 1;
}

extern s32 DVDT_LoadtoARAM_Main(void* arg) {
    DVDCall* call = (DVDCall*)arg;
    static int arq_index = 0;
    static DVDFileInfo finfo;
    static ARQRequest req[4];

    if (!Jac_DVDOpen(call->fileName, &finfo)) {
        __DoError(call, 0);
        return -1;
    }

    u32 len = finfo.length;
    if (len == 0) {
        __DoError(call, 1);
        return -1;
    }

    if (call->length == 0) {
        call->length = len;

        if (call->src != 0) {
            call->length -= call->src;
        }
    }

    OSGetTick();

    while (call->length != 0) {
        u32 readSize;
        u8* buf = ADVD_BUFFER[buffer_load];
        buffer_load = (buffer_load + 1) % buffers;
        while (buffer_full == buffers)
            ;

        if (call->length < buffersize) {
            readSize = ALIGN_NEXT(call->length, 32);
            len = DVDReadMutex(&finfo, buf, readSize, call->src, call->fileName);

            call->length = 0;
        } else {
            readSize = buffersize;
            len = DVDReadMutex(&finfo, buf, buffersize, call->src, call->fileName);

            call->src += buffersize;
            call->length -= buffersize;
        }

        ARQPostRequest(&req[arq_index], 0x12345678, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (u32)buf, call->dst,
                       readSize, ARAM_DMAfinish);
        buffer_full++;
        arq_index++;
        arq_index &= 3;
        call->dst += readSize;
    }

    DVDClose(&finfo);

    while (buffer_full != 0)
        ;

    OSGetTick();

    __DoFinish(call, len);

    return 0;
}

extern s32 DVDT_LoadtoARAM(u32 owner, char* name, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    void* cb = (void*)&call;

    call.owner = owner;
    DVDT_ExtendPath(call.fileName, name);

    call.dst = dst;
    call.callbackStatus = status;
    if (status != 0) {
        *status = 0;
    }

    call.callback = callback;
    call.src = src;
    call.length = length;

    DVDT_AddTask(DVDT_LoadtoARAM_Main, cb, 0x58);

    return 0;
}

static vu32 buffer_full2;

static void ARAM_DMAfinish2(u32) {
    buffer_full2 -= 1;
}

extern s32 DVDT_ARAMtoDRAM_Main(void* arg) {
    static ARQRequest req;
    DVDCall* call = (DVDCall*)arg;

    buffer_full2++;

    ARQPostRequest(&req, (u32)call, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH, call->src, call->dst, call->length,
                   ARAM_DMAfinish2);

    while (buffer_full2 != 0)
        ;

    __DoFinish(call, call->length);

    return 0;
}

extern s32 DVDT_DRAMtoARAM_Main(void* arg) {
    static ARQRequest req;
    DVDCall* call = (DVDCall*)arg;

    buffer_full2++;

    ARQPostRequest(&req, (u32)call, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, call->dst, call->src, call->length,
                   ARAM_DMAfinish2);

    while (buffer_full2 != 0)
        ;

    __DoFinish(call, call->length);

    return 0;
}

extern s32 DVDT_ARAMtoDRAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    void* cb = (void*)&call;

    call.owner = owner;
    call.dst = dst;
    call.callbackStatus = status;

    if (status != 0) {
        *status = 0;
    }

    call.callback = callback;
    call.src = src;
    call.length = length;

    DVDT_AddTaskHigh(DVDT_ARAMtoDRAM_Main, cb, 0x58);

    return 0;
}

extern s32 DVDT_DRAMtoARAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    void* cb = (void*)&call;

    call.owner = owner;
    call.dst = dst;
    call.callbackStatus = status;

    if (status != 0) {
        *status = 0;
    }

    call.callback = callback;
    call.src = src;
    call.length = length;

    DVDT_AddTaskHigh(DVDT_DRAMtoARAM_Main, cb, 0x58);

    return 0;
}

#endif /* TARGET_PC */

/* Common code (shared between PC and GC) */

extern s32 DVDT_CheckFile(char* file) {
    static DVDFileInfo finfo;

    char path[64];
    DVDT_ExtendPath(path, file);

    if (!Jac_DVDOpen(path, &finfo)) {
        return 0;
    }
    u32 len = finfo.length;

    DVDClose(&finfo);

    return len;
}

extern s32 DVDT_CheckPass(u32 owner, u32* status, Jac_DVDCallback callback) {
    DVDCall call;
    void* cb = (void*)&call;

    call.owner = owner;
    call.callbackStatus = status;
    call.callback = callback;

    return DVDT_AddTask((TaskCallback)__DVDT_CheckBack, cb, 0x58);
}

extern s32 Jac_CheckFile(char* file) {
    static DVDFileInfo finfo;

    if (!Jac_DVDOpen(file, &finfo)) {
        return 0;
    }
    u32 len = finfo.length;

    DVDClose(&finfo);

    return len;
}

extern void Jac_RegisterDVDErrorCallback(ErrorCallback callback) {
    error_callback = callback;
}

static u32 dvdfile_dics;
static char dvd_file[32][64];
static u32 dvd_entrynum[32];

extern s32 Jac_RegisterFastOpen(char* file) {
    int num;
    if (strlen(file) > 63) {
        return -1;
    }

    int i;

    for (i = 0; (u32)i < dvdfile_dics; i++) {
        if (!strcmp(dvd_file[i], file)) {
            return dvd_entrynum[i];
        }
    }
    if (dvdfile_dics == 32) {
        return -1;
    }

    num = DVDConvertPathToEntrynum(file);

    if (num != -1) {
        strcpy(dvd_file[dvdfile_dics], file);
        dvd_entrynum[dvdfile_dics] = num;
        dvdfile_dics++;
    }
    return num;
}

extern BOOL Jac_DVDOpen(char* name, DVDFileInfo* info) {
    int entry = Jac_RegisterFastOpen(name);

    if (entry == -1) {
        return DVDOpen(name, info);
    } else {
        return DVDFastOpen(entry, info);
    }
}
