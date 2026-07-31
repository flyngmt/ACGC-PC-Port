#include "JSystem/JSupport/JSUStream.h"
#include "JSystem/JKernel/JKRHeap.h"

JSUInputStream::~JSUInputStream() {
}

int JSUInputStream::read(void* buf, s32 size) {
    int len = this->readData(buf, size);
    if (len != size) {
        this->setState(JSU_EOF);
    }
    return len;
}

char* JSUInputStream::read(char* str) {
    u16 size;
    int len = this->readData(&size, sizeof(size));
    if (len != sizeof(size)) {
        str[0] = '\0';
        this->setState(JSU_EOF);
        str = nullptr;
    } else {
        int strRead = this->readData(str, size);
        str[strRead] = '\0';
        if (strRead != size) {
            this->setState(JSU_EOF);
        }
    }

    return str;
}

/* @fabricated -- this method is confirmed to exist, but goes unused in AC */
char* JSUInputStream::readString() {
    u16 len;
    int r = this->readData(&len, sizeof(len));
    if (r != sizeof(len)) {
        this->setState(JSU_EOF);
        return nullptr;
    }

    char* buf = JKR_NEW_ARRAY(char, len + 1);
    r = this->readData(buf, len);
    if (r != len) {
        JKR_DELETE_ARRAY(buf);
        this->setState(JSU_EOF);
        return nullptr;
    }

    buf[len] = '\0';
    return buf;
}

/* @fabricated -- this method is confirmed to exist, but goes unused in AC */
char* JSUInputStream::readString(char* buf, u16 len) {
    int r = this->readData(buf, len);
    if (r != len) {
        this->setState(JSU_EOF);
        return nullptr;
    }

    buf[len] = '\0';
    return buf;
}

int JSUInputStream::skip(s32 amount) {
    u8 _p;
    int i;

    for (i = 0; i < amount; i++) {
        if (this->readData(&_p, sizeof(_p)) != sizeof(_p)) {
            this->setState(JSU_EOF);
            break;
        }
    }

    return i;
}

/* JSURandomInputStream */

int JSURandomInputStream::skip(s32 amount) {
    int s = this->seekPos(amount, JSU_SEEK_CUR);
    if (s != amount) {
        this->setState(JSU_EOF);
    }
    return s;
}

/* This method is confirmed to exist, but goes unused in AC. Retrieved from TP debug. */
int JSURandomInputStream::align(s32 alignment) {
    int pos = this->getPosition();
    int aligned = ((alignment - 1) + pos) & ~(alignment - 1);
    int change = aligned - pos;

    if (change != 0) {
        int s = this->seekPos(aligned, JSU_SEEK_SET);
        if (s != change) {
            this->setState(JSU_EOF);
        }
    }

    return change;
}

/* This method is confirmed to exist, but goes unused in AC. Retrieved from TP debug. */
int JSURandomInputStream::peek(void* buf, s32 len) {
    int pos = this->getPosition();
    int r = this->read(buf, len);
    if (r != 0) {
        this->seekPos(pos, JSU_SEEK_SET);
    }

    return r;
}

int JSURandomInputStream::seek(s32 offset, JSUStreamSeekFrom from) {
    int s = this->seekPos(offset, from);
    this->clrState(JSU_EOF);
    return s;
}

/* JSUOutputStream */

JSUOutputStream::~JSUOutputStream() {
}

int JSUOutputStream::skip(s32 amount) {
    u8 padding = 0;
    int skipped;

    for (skipped = 0; skipped < amount; skipped++) {
        if (this->readData(&padding, sizeof(padding)) != sizeof(padding)) {
            this->setState(JSU_EOF);
            break;
        }
    }

    return skipped;
}

/* JSURandomOutputStream */

int JSURandomOutputStream::getAvailable() const {
    return this->getLength() - this->getPosition();
}

int JSURandomOutputStream::skip(s32 amount) {
    int skipped = this->seekPos(amount, JSU_SEEK_CUR);
    if (skipped != amount) {
        this->setState(JSU_EOF);
    }
    return skipped;
}
