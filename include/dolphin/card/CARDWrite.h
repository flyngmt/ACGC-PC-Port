#ifndef _DOLPHIN_CARDWRITE_H_
#define _DOLPHIN_CARDWRITE_H_

#ifndef TARGET_PC
long CARDWriteAsync(struct CARDFileInfo * fileInfo, const void * buf, long length, long offset, void (* callback)(long, long));
long CARDWrite(struct CARDFileInfo * fileInfo, const void * buf, long length, long offset);
#endif

#endif // _DOLPHIN_CARDWRITE_H_
