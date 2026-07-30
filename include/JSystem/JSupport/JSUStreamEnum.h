#ifndef JSUSTREAMENUM_H
#define JSUSTREAMENUM_H

/* Avoid the SEEK_* and EOF macro names exported by the host C library. */
enum JSUStreamSeekFrom { JSU_SEEK_SET = 0, JSU_SEEK_CUR = 1, JSU_SEEK_END = 2 };

enum EIoState { GOOD = 0, JSU_EOF = 1 };

#endif
