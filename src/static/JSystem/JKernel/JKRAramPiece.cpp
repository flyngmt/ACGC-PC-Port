#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRMacro.h"
#include "JSystem/JSystem.h"
#include "dolphin/ar.h"
#include "dolphin/os.h" /* TODO: OSReport lives in libforest in AC */
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSMessage.h"
#include "types.h"

JSUList<JKRAMCommand> JKRAramPiece::sAramPieceCommandList;
OSMutex JKRAramPiece::mMutex;

#ifdef TARGET_PC
JKRAMCommand* JKRAramPiece::prepareCommand(int direction, uintptr_t source, uintptr_t destination, u32 length,
                                           JKRAramBlock* aramBlock, JKRAMCommand::AMCommandCallback callback) {
#else
JKRAMCommand* JKRAramPiece::prepareCommand(int direction, u32 source, u32 destination, u32 length,
                                           JKRAramBlock* aramBlock, JKRAMCommand::AMCommandCallback callback) {
#endif
    JKRAMCommand* cmd = new (JKRGetSystemHeap(), -4) JKRAMCommand();
    cmd->mDirection = direction;
    cmd->mSource = source;
    cmd->mDestination = destination;
    cmd->mAramBlock = aramBlock;
    cmd->mLength = length;
    cmd->mCallback = callback;

    return cmd;
}

void JKRAramPiece::sendCommand(JKRAMCommand* cmd) {
    JKRAramPiece::startDMA(cmd);
}

#ifdef TARGET_PC
JKRAMCommand* JKRAramPiece::orderAsync(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* aramBlock,
                                       JKRAMCommand::AMCommandCallback callback) {
#else
JKRAMCommand* JKRAramPiece::orderAsync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock,
                                       JKRAMCommand::AMCommandCallback callback) {
#endif
    JKRAramPiece::lock();

    if (!JKR_ISALIGNED32(source) || !JKR_ISALIGNED32(destination)) {
        JLOGF("direction = %x\n", direction);
        JLOGF("source = %x\n", source);
        JLOGF("destination = %x\n", destination);
        JLOGF("length = %x\n", length);
        JPANICLINE(102);
    }

    JKRAMCommand* cmd = JKRAramPiece::prepareCommand(direction, source, destination, length, aramBlock, callback);

#ifdef TARGET_PC
    /* On PC, execute DMA synchronously (no worker thread) */
    JKRAramPiece::startDMA(cmd);
#else
    JKRAramCommand* aramCmd = new (JKRGetSystemHeap(), -4) JKRAramCommand();
    aramCmd->setting(TRUE, cmd);
    OSSendMessage((OSMessageQueue*)&JKRAram::sMessageQueue, (OSMessage)aramCmd, OS_MESSAGE_BLOCK);
    if (cmd->mCallback != nullptr) {
        JKRAramPiece::sAramPieceCommandList.append(&cmd->mAramPieceCommandLink);
    }
#endif

    JKRAramPiece::unlock();
    return cmd;
}

bool JKRAramPiece::sync(JKRAMCommand* cmd, BOOL noBlock) {
    OSMessage msg[1];

    JKRAramPiece::lock();

    if (!noBlock) {
        OSReceiveMessage(&cmd->mMesgQueue, msg, OS_MESSAGE_BLOCK);
        JKRAramPiece::sAramPieceCommandList.remove(&cmd->mAramPieceCommandLink);
        JKRAramPiece::unlock();
        return true;
    } else {
        if (!OSReceiveMessage(&cmd->mMesgQueue, msg, OS_MESSAGE_NOBLOCK)) {
            JKRAramPiece::unlock();
            return false;
        } else {
            JKRAramPiece::sAramPieceCommandList.remove(&cmd->mAramPieceCommandLink);
            JKRAramPiece::unlock();
            return true;
        }
    }
}

#ifdef TARGET_PC
bool JKRAramPiece::orderSync(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* aramBlock) {
#else
bool JKRAramPiece::orderSync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock) {
#endif
    JKRAramPiece::lock();

    JKRAMCommand* cmd = JKRAramPiece::orderAsync(direction, source, destination, length, aramBlock, nullptr);
    bool res = JKRAramPiece::sync(cmd, FALSE);
    delete cmd;

    JKRAramPiece::unlock();
    return res;
}

void JKRAramPiece::startDMA(JKRAMCommand* cmd) {
    if (cmd->mDirection == ARAM_DIR_ARAM_TO_MRAM) {
        DCInvalidateRange((u8*)cmd->mDestination, cmd->mLength);
    } else { /* cmd->mDirection == ARAM_DIR_MRAM_TO_ARAM */
        DCStoreRange((u8*)cmd->mSource, cmd->mLength);
    }

    ARQPostRequest(cmd, 0, cmd->mDirection, 0, cmd->mSource, cmd->mDestination, cmd->mLength, JKRAramPiece::doneDMA);
}

#ifdef TARGET_PC
void JKRAramPiece::doneDMA(uintptr_t param) {
#else
void JKRAramPiece::doneDMA(u32 param) {
#endif
    JKRAMCommand* cmd = (JKRAMCommand*)param;
    if (cmd->mDirection == ARAM_DIR_ARAM_TO_MRAM) {
        DCInvalidateRange((u8*)cmd->mDestination, cmd->mLength);
    }
    if (cmd->mCallbackType != ARAMPIECE_DONE_CALLBACK) {
        if (cmd->mCallbackType == ARAMPIECE_DONE_DECOMPRESS) {
            JKRDecomp::sendCommand(cmd->mDecompCommand);
        }
    } else {
        if (cmd->mCallback != nullptr) {
            (*cmd->mCallback)(param);
        } else {
            if (cmd->mCompletedMesgQueue != nullptr) {
                OSSendMessage(cmd->mCompletedMesgQueue, (OSMessage)cmd, OS_MESSAGE_NOBLOCK);
            } else {
                OSSendMessage(&cmd->mMesgQueue, (OSMessage)cmd, OS_MESSAGE_NOBLOCK);
            }
        }
    }
}

JKRAMCommand::JKRAMCommand() : mAramPieceCommandLink(this), mLink30(this) {
    OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, 1);
    this->mCallback = nullptr;
    this->mCompletedMesgQueue = nullptr;
    this->mCallbackType = ARAMPIECE_DONE_CALLBACK;
    this->_8C = nullptr;
    this->_90 = nullptr;
    this->_94 = nullptr;
}

JKRAMCommand::~JKRAMCommand() {
    if (this->_8C != nullptr) {
        delete this->_8C;
    }

    if (this->_90 != nullptr) {
        delete this->_90;
    }

    if (this->_94 != nullptr) {
        JKRFree(this->_94);
    }
}
