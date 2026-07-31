
#include "JSystem/JKernel/JKRMacro.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JKernel/JKRHeap.h"

JSUList<JKRThread> JKRThread::sThreadList;

JKRThread::JKRThread(u32 stackSize, int msgCount, int threadPrio) : mLink(this) {
    this->mHeap = JKRHeap::findFromRoot(this);
    if (this->mHeap == nullptr) {
        this->mHeap = JKRHeap::sSystemHeap;
    }

    this->mStackSize = (u32)JKR_ALIGN32(stackSize);
    this->mStackMemory = JKRHeap::alloc(this->mStackSize, 32, this->mHeap);
    this->mThreadRecord = (OSThread*)JKRHeap::alloc(sizeof(OSThread), 32, this->mHeap);
    OSCreateThread(this->mThreadRecord, &JKRThread::start, this,
                   static_cast<void*>(static_cast<u8*>(this->mStackMemory) + this->mStackSize),
                   this->mStackSize, threadPrio, OS_THREAD_ATTR_DETACH);
    this->mMesgCount = msgCount;
    this->mMesgBuffer = (OSMessage*)JKRHeap::alloc(mMesgCount * sizeof(OSMessage), 0, this->mHeap);
    OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, this->mMesgCount);
    JKRThread::sThreadList.append(&this->mLink);
}

JKRThread::JKRThread(OSThread* threadRecord, int msgCount) : mLink(this) {
    this->mHeap = nullptr;
    this->mThreadRecord = threadRecord;
    this->mStackSize = static_cast<u32>(reinterpret_cast<uintptr_t>(threadRecord->stackEnd) -
                                        reinterpret_cast<uintptr_t>(threadRecord->stackBase));
    this->mStackMemory = threadRecord->stackBase;
    this->mMesgCount = msgCount;
    this->mMesgBuffer = (OSMessage*)JKRHeap::sSystemHeap->alloc(mMesgCount * sizeof(OSMessage), 4);
    OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, this->mMesgCount);
    JKRThread::sThreadList.append(&this->mLink);
}

JKRThread::~JKRThread() {
    JKRThread::sThreadList.remove(&this->mLink);

    if (this->mHeap != nullptr) {
        if (!OSIsThreadTerminated(this->mThreadRecord)) {
            OSDetachThread(this->mThreadRecord);
            OSCancelThread(this->mThreadRecord);
        }

        JKRHeap::free(this->mStackMemory, this->mHeap);
        JKRHeap::free(this->mThreadRecord, this->mHeap);
    }

    JKRHeap::free(this->mMesgBuffer, nullptr);
}

void* JKRThread::start(void* thread) {
    return static_cast<JKRThread*>(thread)->run();
}

// UNUSED FUNCTIONS, REQUIRED FOR RTTI
JKRTask::JKRTask() : JKRThread(0x4000, 4, 31) {
}

JKRTask::~JKRTask() {
}

JKRTask* JKRTask::create() {
    return JKR_NEW JKRTask();
}

void JKRTask::destroy() {
    JKR_DELETE(this);
}

void* JKRTask::run() {
    Request* req;
    // OSInitFastCast();
    while (true) {
        req = (Request*)waitMessageBlock();
        if (req->mCb) {
            req->mCb(req->mArg);
            if (mTaskMsgQueue) {
                OSSendMessage(mTaskMsgQueue, req->mMsg, OS_MESSAGE_NOBLOCK);
            }
        }
        req->mCb = nullptr;
    }
}

bool JKRTask::request(RequestCallback callback, void* arg, void* msg) {
    Request* req = searchBlank();
    if (req == nullptr) {
        return false;
    }
    req->mCb = callback;
    req->mArg = arg;
    req->mMsg = msg;
    bool sendResult = OSSendMessage(&mMesgQueue, req, OS_MESSAGE_NOBLOCK);
    if (!sendResult) {
        req->mCb = nullptr;
    }
    return sendResult;
}

JKRTask::Request* JKRTask::searchBlank() {
    for (u32 i = 0; i < mRequestCnt; ++i) {
        if (mRequest[i].mCb == nullptr) {
            return &mRequest[i];
        }
    }
    return nullptr;
}
