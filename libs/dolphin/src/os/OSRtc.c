#include "dolphin/os/OSRtc.h"

#include "dolphin/os/OSCache.h"
#include "dolphin/os.h"
#include "types.h"

static SramControlBlock Scb ATTRIBUTE_ALIGN(32);

static inline BOOL ReadSram(void* buffer) {
  u32 cmd;
  BOOL err;

  DCInvalidateRange(buffer, RTC_SRAM_SIZE);

  if (!EXILock(RTC_CHAN, RTC_DEVICE, NULL)) {
    return FALSE;
  }

  if (!EXISelect(RTC_CHAN, RTC_DEVICE, RTC_FREQUENCY)) {
    EXIUnlock(RTC_CHAN);
    return FALSE;
  }

  cmd = RTC_CMD_READ | RTC_SRAM_ADDR;
  err  = !EXIImm(RTC_CHAN, &cmd, sizeof(u32), EXI_WRITE, NULL);
  err |= !EXISync(RTC_CHAN);
  err |= !EXIDma(RTC_CHAN, buffer, RTC_SRAM_SIZE, EXI_READ, NULL);
  err |= !EXISync(RTC_CHAN);
  err |= !EXIDeselect(RTC_CHAN);
  EXIUnlock(RTC_CHAN);
  
  return !err;
}

void WriteSramCallback(s32 chan, OSContext* ctx) {
  DOLPHIN_ASSERTLINE(!Scb.locked, 258);
  Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, RTC_SRAM_SIZE - Scb.offset);
  DOLPHIN_ASSERTLINE(Scb.sync, 264);

  if (Scb.sync) {
      Scb.offset = RTC_SRAM_SIZE;
  }
}

static BOOL WriteSram(void* buffer, u32 offset, u32 size) {
  u32 cmd;
  BOOL err;

  if (EXILock(RTC_CHAN, 1, WriteSramCallback) == FALSE) {
    return FALSE;
  }

  if (EXISelect(RTC_CHAN, RTC_DEVICE, RTC_FREQUENCY) == FALSE) {
    EXIUnlock(RTC_CHAN);
    return FALSE;
  }

  offset *= RTC_SRAM_SIZE;
  cmd = offset + RTC_SRAM_ADDR | RTC_CMD_WRITE;
  err  = !EXIImm(RTC_CHAN, &cmd, sizeof(u32), EXI_WRITE, NULL);
  err |= !EXISync(RTC_CHAN);
  err |= !EXIImmEx(RTC_CHAN, buffer, size, EXI_WRITE);
  err |= !EXIDeselect(RTC_CHAN);
  EXIUnlock(RTC_CHAN);
  return !err;
}

extern void __OSInitSram() {
  Scb.enabled = FALSE;
  Scb.locked = FALSE;
  Scb.sync = ReadSram(Scb.sram);
  DOLPHIN_ASSERTLINE(Scb.sync, 318);
  Scb.offset = RTC_SRAM_SIZE;
}

static inline void* LockSram(u32 offset) {
  BOOL enabled = OSDisableInterrupts();

  DOLPHIN_ASSERTLINE(Scb.locked, 341);
  if (Scb.locked != FALSE) {
    OSRestoreInterrupts(enabled);
    return NULL;
  }

  Scb.enabled = enabled;
  Scb.locked = TRUE;
  return Scb.sram + offset;
}

extern OSSram* __OSLockSram() {
  return (OSSram*)LockSram(0);
  //return sram;
}

extern OSSramEx* __OSLockSramEx() {
  return (OSSramEx*)LockSram(sizeof(OSSram));
  //return sramEx;
}

static BOOL UnlockSram(BOOL commit, u32 offset) {
  u16* chksum_p;

  DOLPHIN_ASSERTLINE(Scb.locked, 375);
  if (commit) {
    if (offset == 0) {
      OSSram* sram = (OSSram*)Scb.sram;
      if ((sram->flags & 3u) > 2u) {
        sram->flags &= (~3u);
      }

      sram->checkSum = sram->checkSumInv = 0;
      for (chksum_p = (u16*)&sram->counterBias; chksum_p < (u16*)(Scb.sram + sizeof(OSSram)); chksum_p++) {
        sram->checkSum += *chksum_p;
        sram->checkSumInv += ~*chksum_p;
      }
    }

    if (offset < Scb.offset) {
      Scb.offset = offset;
    }

    Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, RTC_SRAM_SIZE - Scb.offset);
    if (Scb.sync) {
      Scb.offset =  RTC_SRAM_SIZE;
    }
  }

  Scb.locked = FALSE;
  OSRestoreInterrupts(Scb.enabled);
  return Scb.sync;
}

extern void __OSUnlockSram(BOOL commit) {
  UnlockSram(commit, 0);
}

extern void __OSUnlockSramEx(BOOL commit) {
  UnlockSram(commit, sizeof(OSSram));
}

extern BOOL __OSSyncSram() {
  return Scb.sync;
}

extern u32 OSGetSoundMode() {
  OSSram* sram = __OSLockSram();
  u32 mode = GET_SOUNDMODE(sram->flags) ? OS_SOUND_MODE_STEREO : OS_SOUND_MODE_MONO;
  __OSUnlockSram(FALSE);
  return mode;
}

extern void OSSetSoundMode(u32 mode) {
  u32 flag;
  OSSram* sram;
  u32 m;

  DOLPHIN_ASSERTLINE(mode == OS_SOUND_MODE_MONO || mode == OS_SOUND_MODE_STEREO, 617);
  flag = SET_SOUNDMODE(mode);
  sram = (OSSram*)__OSLockSram();
  if (flag == GET_SOUNDMODE(sram->flags)) {
    __OSUnlockSram(FALSE);
  }
  else {
    sram->flags = CLR_SOUNDMODE(sram->flags);
    sram->flags |= flag;
    __OSUnlockSram(TRUE);
  }
}

extern u32 OSGetProgressiveMode() {
  OSSram* sram = __OSLockSram();
  u32 mode = GET_PROGMODE(sram->flags) >> 7;
  __OSUnlockSram(FALSE);
  return mode;
}

extern void OSSetProgressiveMode(u32 on) {
  u32 flag;
  OSSram* sram;
  u32 m;

  DOLPHIN_ASSERTLINE(on == OS_PROGRESSIVE_MODE_OFF || on == OS_PROGRESSIVE_MODE_ON, 670);
  flag = SET_PROGMODE(on);
  sram = __OSLockSram();

  if (flag == GET_PROGMODE(sram->flags)) {
    __OSUnlockSram(FALSE);
  }
  else {
    sram->flags = CLR_PROGMODE(sram->flags);
    sram->flags |= flag;
    __OSUnlockSram(TRUE);
  }
}

extern void __OSSetBootMode(u8 mode) {
  OSSram* sram;
  u32 m;
  
  mode &= OS_BOOT_MODE_RETAIL;
  sram = __OSLockSram();
  if (mode == (u32)GET_BOOTMODE(sram->ntd)) {
    __OSUnlockSram(FALSE);
  }
  else {
    sram->ntd = CLR_BOOTMODE(sram->ntd);
    sram->ntd |= mode;
    __OSUnlockSram(TRUE);
  }
}

extern u16 OSGetWirelessID(s32 chan) {
  OSSramEx* sramEx = __OSLockSramEx();
  u16 id = sramEx->wirelessPadID[chan];
  __OSUnlockSramEx(FALSE);
  return id;
}

extern void OSSetWirelessID(s32 chan, u16 id) {
  OSSramEx* sramEx = __OSLockSramEx();
  if (sramEx->wirelessPadID[chan] != id) {
    sramEx->wirelessPadID[chan] = id;
    __OSUnlockSramEx(TRUE);
  }
  else {
    __OSUnlockSramEx(FALSE);
  }
}
