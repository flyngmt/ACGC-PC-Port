#include "JSystem/JSupport/JSUStream.h"

JSUFileInputStream::JSUFileInputStream(JKRFile* file) : mObject(file), mPosition(0) {
}

int JSUFileInputStream::readData(void* buf, s32 len) {
    int read = 0;

    if (((JKRFile*)this->mObject)->isAvailable()) {
        /* Check if need to clamp length to EOF */
        if ((u32)(this->mPosition + len) > ((JKRFile*)this->mObject)->getFileSize()) {
            len = ((JKRFile*)this->mObject)->getFileSize() - this->mPosition;
        }

        if (len > 0) {
            read = ((JKRFile*)this->mObject)->readData(buf, len, this->mPosition);
            this->mPosition += read;
        }
    }

    return read;
}

int JSUFileInputStream::seekPos(s32 offset, JSUStreamSeekFrom from) {
    int pos = this->mPosition;

    switch (from) {
        case JSU_SEEK_SET:
            this->mPosition = offset;
            break;

        case JSU_SEEK_END:
            this->mPosition = ((JKRFile*)this->mObject)->getFileSize() - offset;
            break;

        case JSU_SEEK_CUR:
            this->mPosition = pos + offset;
            break;
    }

    if (this->mPosition < 0) {
        this->mPosition = 0;
    }

    if (this->mPosition > (s32)((JKRFile*)this->mObject)->getFileSize()) {
        this->mPosition = ((JKRFile*)this->mObject)->getFileSize();
    }

    return this->mPosition - pos;
}

JSUFileOutputStream::JSUFileOutputStream(JKRFile* file) {
}
