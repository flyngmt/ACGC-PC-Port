#include "boot.h"

#include "dolphin/dvd.h"
#include "dolphin/os.h"
#include <dolphin/os.h>
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSModule.h"
#include "dolphin/os/OSReset.h"
#include "dolphin/pad.h"
#include "libforest/fault.h"
#include "jaudio_NES/game64.h"
#include "libc64/malloc.h"
#include "libc64/sleep.h"
#include "libforest/osreport.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "jsyswrap.h"
#include "libultra/initialize.h"
#include "libultra/contreaddata.h"
#include "libultra/libultra.h"
#include "libultra/shutdown.h"
#include "m_nmibuf.h"
#include "nintendo_hi_0.h"
#include "sys_math.h"
#include "terminal.h"
#include "dolphin/vi.h"
#include "_mem.h"
#include "initial_menu.h"
#include "libforest/batconfig.h"
#include "dolphin/os/OSAlarm.h"
#include "dvderr.h"
#include "libforest/osreport.h"
#ifdef TARGET_PC
#include "m_field_make.h"
#include "m_map_ovl.h"
#include "pc_bswap.h"

/* Raw binary display lists (u8[] with BE data from ROM .inc files).
   On LE these need u32 byte-swap so emu64 reads correct commands. */
extern u8 cal_win_nen_before[];
extern u8 des_win_before[];
extern u8 des_win_suuji_before[];

/* u8[] arrays used as TLUT palettes via gsDPLoadTLUT_Dolphin.
   These contain raw BE byte pairs from ROM .inc files. On LE, pairs must
   be swapped so the texture decoder reads correct u16 RGB5A3 values.
   (u16[] palette arrays don't need this — C literals are native-endian.) */
extern u8 tim_win_newtokei_tex[];
extern u8 utPal_mike[];
extern u8 utPal_mouth[];
extern u8 int_iid_funediary[];
extern u8 int_iid_mdiary[];
extern u8 int_iid_newdiary[];
extern u8 int_iid_olddiary[];
extern u8 int_ike_jny_syon01_tex[];
extern u8 int_ike_jny_tower01[];
extern u8 int_noga_sprinkler[];
extern u8 int_yos_kflag_pat[];
extern u8 obj_item_omikuji[];
extern u8 rom_museum4_step_pal2[];
extern u8 int_iid_diary[];  /* static in original, non-static on PC */

static void pc_bswap_raw_display_lists(void) {
    struct { u8* data; int size; } lists[] = {
        { cal_win_nen_before, 40 },     /* 5 Gfx commands */
        { des_win_before, 32 },          /* 4 Gfx commands */
        { des_win_suuji_before, 40 },    /* 5 Gfx commands */
    };
    int i;
    for (i = 0; i < 3; i++) {
        pc_bswap32_array(lists[i].data, lists[i].size / 4);
    }
}

/* Swap byte pairs in u8[] arrays that are used as TLUT palettes.
   All are 16 entries (32 bytes). int_iid_diary is static, handled in its file. */
static void pc_bswap_u8_tlut_palettes(void) {
    u8* palettes[] = {
        tim_win_newtokei_tex,
        utPal_mike,
        utPal_mouth,
        int_iid_funediary,
        int_iid_mdiary,
        int_iid_newdiary,
        int_iid_olddiary,
        int_ike_jny_syon01_tex,
        int_ike_jny_tower01,
        int_noga_sprinkler,
        int_yos_kflag_pat,
        obj_item_omikuji,
        rom_museum4_step_pal2,
        int_iid_diary,
    };
    int i;
    for (i = 0; i < 14; i++) {
        pc_bswap16_array((u16*)palettes[i], 16);
    }
}

/* mMP_house_pos_list is raw binary ROM data (u8[0x978]) cast to mMP_HousePos_c[].
   Each entry has a u16 fgblock_name that needs BE/LE swap. The u8 fields (ut_x, ut_z, idx)
   are fine. Without this, the map overlay can't match buildings => wrong icon positions. */
extern mMP_HousePos_c mMP_house_pos_list[];
static void pc_bswap_house_pos_list(void) {
    mMP_HousePos_c* p = mMP_house_pos_list;
    /* 0x03B8 is the sentinel in BE. After swap, sentinel becomes native 0x03B8. */
    int count = 0x978 / sizeof(mMP_HousePos_c);
    int i;
    for (i = 0; i < count; i++) {
        p[i].fgblock_name = pc_bswap16(p[i].fgblock_name);
    }
}
#endif

static OSModuleHeader* moduleA;
static void* StringTable;  // swapped with fakemain_check
static BOOL fakemain_check;
OSTime InitialStartTime; /* TODO: this appears to be N64's type of OSTime (u64), and not Dolphin's (s64) */
void* boot_copyDate;
void* HotStartEntry;
#if VERSION == VER_GAFU01_00
u8 SoftResetEnable;
#endif
u8 boot_sound_initializing;

/**
 * @brief Stubbed function. Was responsible for allocated space for sound.
 * 
 * @return void* nullptr
 */
void* soundArenaAlloc(size_t size) { return nullptr; }

/**
 * @brief Tries to find an absolute address within any loaded modules.
 * 
 * @param addr The address to search for
 * @param module_id Out module id
 * @param section_idx  Out module section index
 * @param section_addr Out module section offset
 * @param module_name_ofs Out module name offset
 * @return s32 success
 */
s32 search_partial_address(u32 addr, u32* module_id, u32* section_idx, u32* section_addr, u32* module_name_ofs) {
#ifdef TARGET_PC
  (void)addr;
  (void)module_id;
  (void)section_idx;
  (void)section_addr;
  (void)module_name_ofs;
  return -1; /* REL modules are not loaded by the statically linked PC build. */
#else
  u32 section_size;
  OSModuleHeader* module_p;
  u32 section;
  u32 section_ofs;
  OSSectionInfo* section_info;

  if (addr == 0) {
    return -1; /* failed */
  }

  module_p = BaseModule;
  while (module_p != nullptr) {
    section_info = OSGetSectionInfo(module_p);
    for (section = 0; section < module_p->info.numSections;
         section_info++, section++) {
      section_size = section_info->size;
      if (section_size != 0) {
        section_ofs = OS_SECTIONINFO_OFFSET(section_info->offset);
        if ((section_ofs <= addr) && (addr < section_ofs + section_size)) {
          if (module_id != nullptr) {
            *module_id = module_p->info.id;
          }
          if (section_idx != nullptr) {
            *section_idx = section;
          }
          if (section_addr != nullptr) {
            *section_addr = addr - section_ofs;
          }
          if (module_name_ofs != nullptr) {
            *module_name_ofs = module_p->info.nameOffset;
          }

          return 0; /* success */
        }
      }
    }

    module_p = (OSModuleHeader*)module_p->info.link.next;
  }

  return -1; /* failed */
#endif
}

/**
 * @brief Attempts to convert an absolute address to a module_id-section_idx-section_offset pair.
 * 
 * @param addr Address to attempt conversion on
 * @return u32 convertedAddress
 */
extern u32 convert_partial_address(u32 addr) {
  u32 module_id, section_idx, section_ofs;

  if (search_partial_address(addr, &module_id, &section_idx, &section_ofs, nullptr) == 0) {
    return MAKE_PARTIAL_ADDRESS(section_idx, section_ofs);
  }

  return addr;
}

/**
 * @brief Loads a debug string table for debugging.
 * 
 * @param table Path to the string table.
 * @return int success
 */
int LoadStringTable(const char* table) {  // https://decomp.me/scratch/7syDa

  OSReport("ストリングテーブル読み込み開始\n"); /* Starting string table load */
  osGetTime(); /* This was probably a variable to a 'begin time' printf */
  StringTable = JC__JKRDvdToMainRam_byName(table, nullptr, EXPAND_SWITCH_DECOMPRESS);

  if (StringTable == nullptr) {
    OSDVDFatalError();
  }

  OSSetStringTable(StringTable);
  osGetTime(); /* This was probably a variable to an 'end time' printf */
  OSReport("ストリングテーブル読み込み 完了\n"); /* String table loading complete */
  return 0;
}

/**
 * @brief Utility function to "un-link" a relocatable module (rel).
 * 
 * @param module Handle to the module header to unload.
 */
extern void UnLink(OSModuleHeader* module) {
  if (module != nullptr) {
    if (module->epilog != 0) {
      OSReport("エピローグ開始\n"); /* epilog start */
      ((void (*)())(uintptr_t)module->epilog)();
      OSReport("エピローグ完了\n"); /* epilog complete */
    }

    OSReport("アンリンク中\n"); /* unlinking */
    OSUnlink(&module->info);
    OSReport("アンリンク完了\n"); /* unlinking complete */
  }

  JW_Free(module);
}

/**
 * @brief Relocatable module (reL) loading utility function. Loads a module by its file name.
 * May return nullptr if unable to load the module for whatever reason.
 * 
 * @param module_name The file name of the module.
 * @return OSModuleHeader* loadedModule
 */
OSModuleHeader* LoadLink(const char* module_name) {
  int result;
  size_t length;
  void* bss;
  int alignLength;
  OSModuleHeader* module;

  bss = nullptr;
  OSReport("モジュール(%s)の読み込み中\n", module_name); /* Loading module (%s) */
  module = (OSModuleHeader*)JC__JKRDvdToMainRam_byName(module_name, nullptr, EXPAND_SWITCH_DECOMPRESS);
  if (module == nullptr) {
    OSReport("モジュール(%s)の読み込みに失敗しました\n", module_name); /* Failed to load module (%s) */
    OSDVDFatalError();
    return module;
  }
  
  OSReport("モジュール(%s)の読み込み完了\n", module_name); /* Module (%s) load complete */
  OSReport("module=%08x\n", module);
  result = !!module;
  OSReport("result=%08x\n", result);
  length = JW_GetMemBlockSize(module);
  OSReport("length=%08x\n", length);
  JC__JKRDetachResource(module);
  if (result) {
    bss = soundArenaAlloc(module->bssSize);

    /* This case will never happen because soundArenaAlloc() was stubbed to always return nullptr. */
    if (bss != nullptr) {
      OSReport("サウンドアリーナ %08x 使用 bss=%08x\n", module->bssSize, bss);  /* Sound Arena %08x used bss=%08x */
      emu64_texture_cache_data_entry_set((u8*)module, (u8*)module + length);
    }
    else {
      alignLength = ALIGN_NEXT(length, 32);
      if (JW_Resize(module, alignLength + module->bssSize) >= 0) {
        bss = (u8*)module + alignLength;
        emu64_texture_cache_data_entry_set((u8*)module, (u8*)module + alignLength);
      }
      else {
        bss = JW_Alloc(module->bssSize, 32);
        if (bss != nullptr) {
          emu64_texture_cache_data_entry_set((u8*)module, (u8*)module + length);
        }
        else {
          goto failed;
        }
      }
    }
        
    OSLink(&module->info, bss);
    ((void (*)())(uintptr_t)module->prolog)();
    return module;
  }

failed:
  JW_Free(bss);
  JW_Free(module);
  return nullptr;
}

/**
 * @brief Callback if an error occurs during audio initialization.
 * 
 */
void audioFatalCallback() {
  OSReport("audioFatalCallback" VT_RST "\n");
  OSDVDFatalError();
}

/**
 * @brief First half of audio initialization. Prepares boot sound.
 * 
 */
void sound_initial() {
  Na_InitAudio(audioFatalCallback, nullptr, 0, nintendo_hi_0, 0x66a0, FALSE);
  OSReport("sizeof(nintendo_hi_0)=%08x\n", 0x9900);
  OSReport("実際のnintendo_hi_0.awのサイズ=%08x \n", 0x66a0); /* Real nintendo_hi_0.aw size=%08x */
  OSReport("ニンテンドー発生タイムラグまで寝てます(%dms)" VT_RST "\n", 2500); /* Sleeping until Nintendo latency time (%dms) occurs */
  msleep(2500);
}

/**
 * @brief Second half of audio initialization. Waits for 'Neos' to finish initialization.
 * 
 */
void sound_initial2() {
  while (!Na_CheckNeosBoot()) {
    VIWaitForRetrace();
    Na_GameFrame();
  }

  bzero(&nintendo_hi_0, sizeof(nintendo_hi_0));
}

/**
 * @brief Performs a hot reset to the IPL menu
 * 
 */
void HotResetIplMenu() {
  if (APPNMI_ZURUMODE3_GET()) {
    OSChangeBootMode(RETAIL_MODE); /* Switch back to retail mode before rebooting */
  }

  /* Utilize osAppNMIBuffer[15] as the boot code to recover it & signal hotreset*/
  OSResetSystem(OS_RESET_HOTRESET, osAppNMIBuffer[15], TRUE);
}

/**
 * @brief faultmgr callback which checks for correct debug key input.
 * 
 * @param msg The message displayed for the key combo.
 * @param param The key combination separated into two u16s.
 */
void fault_callback_keyCheck(const char* msg, u32 param) {
  u32 trigger;
  u32 button;

  if (APPNMI_ZURUMODE_GET()) {
    fault_Printf("PUSH %s\n", msg);
  }
  do {
    do {
      fault_ReadPad(&trigger, &button);
    } while ((u16)trigger != (u16)param);
  } while ((u16)button != (u16)((param >> 16) | trigger));
}

/**
 * @brief faultmgr callback which acknowledges correct debug key input.
 * 
 */
void fault_callback_OK() {
  fault_Printf("\nOK! YOU ARE GREAT!\n");
  fault_WaitTime(2000);
}

/**
 * @brief faultmgr callback which prints control text to the console.
 * 
 */
void fault_callback_Setumei() {
  fault_Printf("\n+ KEY to SCROLL UP/DOWN\nB BUTTON : TOP OF CONSOLE\nA BUTTON : BOTTOM OF CONSOLE\n");
}

/**
 * @brief faultmgr callback which reads PAD input & processes reboot requests.
 * 
 */
void fault_callback_vimode() {
  u32 triggers, buttons;

  APPNMI_RESETEXEMPT2_SET();
  if (!APPNMI_TESTMODE_GET()) {
    OSReport("貸し出しバージョンなのでコードは出しません\n"); /* Since this is a loaned version, we will not provide the code */
    OSReport("B+X+STARTでリスタートします\n"); /* B+X+START to restart */

    do {
      if (OSGetResetSwitchState()) {
        __osResetSwitchPressed = TRUE;
      } else {
        if (__osResetSwitchPressed) {
          osShutdownStart(OS_RESET_SHUTDOWN);
        }
      }

      fault_ReadPad(&triggers, &buttons);
      if ((buttons == PAD_BUTTON_B) | (PAD_BUTTON_START | PAD_BUTTON_X)) {
        osShutdownStart(OS_RESET_SHUTDOWN);
      }
    } while (TRUE);
  }

  JW_SetFamicomMode(FALSE);
  JW_SetLowResoMode(FALSE);
}

#define OVERLINE(con) (((JC_JUTConsole_getUsedLine(con) - JC_JUTConsole_getHeight(con)) + 1) <= JC_JUTConsole_getLineOffset(con))

/**
 * @brief faultmgr callback to scroll console
 * 
 */
void fault_callback_scroll() {
  u32 button;
  u32 trigger;
  void* manager;
  void* console;
  s32 up_speed;
  s32 down_speed;
  s32 update_console;
  u32 retrace_cnt;
  int pad_disabled;

  manager = JC_JUTException_getManager();
  console = JC_JUTException_getConsole();
  pad_disabled = !JC_JUTException_isEnablePad(manager);
  if (!pad_disabled) {
    OSEnableInterrupts();
    up_speed = 0;
    down_speed = 0;
    do {
      JC_JUTException_readPad(manager, &trigger, &button);
      update_console = FALSE;
      if (trigger == PAD_BUTTON_A) {
        JC_JUTConsole_scrollToLastLine(console);
        update_console = TRUE;
      }
      if (trigger == PAD_BUTTON_B) {
        JC_JUTConsole_scrollToFirstLine(console);
        update_console = TRUE;
      }
      if (button == PAD_BUTTON_UP) {
        JC_JUTConsole_scroll(
            console, (up_speed < 3)
                         ? -1
                         : ((up_speed < 5) ? -2 : ((up_speed < 7) ? -4 : -8)));
        update_console = TRUE;
        down_speed = 0;
        up_speed++;
      } else if (button == PAD_BUTTON_DOWN) {
        JC_JUTConsole_scroll(
            console, (down_speed < 3)
                         ? 1
                         : ((down_speed < 5) ? 2 : ((down_speed < 7) ? 4 : 8)));
        update_console = TRUE;
        up_speed = 0;
        down_speed++;
      } else {
        up_speed = 0;
        down_speed = 0;
      }
      if (update_console == TRUE) {
        retrace_cnt = VIGetRetraceCount();
        do {
        } while (retrace_cnt == VIGetRetraceCount());
        JC_JUTConsoleManager_drawDirect(JC_JUTConsoleManager_getManager(), 1);
      }
      JC_JUTException_waitTime(30);
      if (OSGetResetSwitchState()) {
        osShutdownStart(OS_RESET_RESTART);
      }
    } while (TRUE);
  }

  do {
    JC_JUTConsole_scrollToFirstLine(console);
    JC_JUTConsoleManager_drawDirect(JC_JUTConsoleManager_getManager(), 1);
    JC_JUTException_waitTime(2000);

    do {
      u32 height;
      for (height = JC_JUTConsole_getHeight(console); height != 0; height--) {
        JC_JUTConsole_scroll(console, 1);
        JC_JUTConsoleManager_drawDirect(JC_JUTConsoleManager_getManager(), 1);

        if (OVERLINE(console)) {
          break;
        }

        JC_JUTException_waitTime(20);
      }

      JC_JUTException_waitTime(3000);
      if (OVERLINE(console)) {
        break;
      }
    } while (TRUE);
  } while (TRUE);
}

/**
 * @brief Adjusts the memory arena depending on installed RAM size.
 * osAppNMIBuffers's 'extended memory' bitflag must be enabled for extended memory settings.
 */
void adjustOSArena() {
  void* arenalo = OSGetArenaLo();
  void* arenahi = OSGetArenaHi();

  OSReport("ARENA %08x-%08x" VT_RST "\n", arenalo, arenahi);

#ifndef TARGET_PC
  if (arenahi > (void*)0x81800000) {
    if (!APPNMI_EXTENDEDMEMORY_GET()) {
      OSReport("搭載メモリが 24MB を超えていますが、24MB に限定します。" VT_RST "\n"); /* The installed memory exceeds 24MB, but will be limited to 24MB. */
      arenahi = (void*)0x817ffa80;
    } else if (arenahi > (void*)0x82000000) {
      OSReport("搭載メモリが 32MB を超えていますが、32MB に限定します。" VT_RST "\n"); /* The installed memory exceeds 32MB, but will be limited to 32MB. */
      arenahi = (void*)0x81e00000;
    } else {
      OSReport("搭載メモリが 32MB を超えています。" VT_RST "\n"); /* The installed memory exceeds 32MB. */
    }
  } else {
    OSReport("搭載メモリが 24MB 以下なので動かない事がありえます。" VT_RST "\n"); /* Since the installed memory is 24MB or less, there may be issues. */
  }
#endif

  OSSetArenaHi(arenahi);
  OSReport("ARENA %08x-%08x" VT_RST "\n", arenalo, arenahi);

#ifdef TARGET_PC
  /* Use pointer arithmetic instead of u32 casts (which truncate on 64-bit) */
  bzero(arenalo, (size_t)((u8*)arenahi - (u8*)arenalo));
#else
  bzero(arenalo, ((u32)arenahi - (u32)arenalo));
#endif
}

/**
 * @brief Standard C main function/entry point
 * 
 * @param argc unused
 * @param argv unused
 * @return int exitCode
 */
int main(int argc, const char** argv) {
  static fault_client
    my_fault_client1,
    my_fault_client2,
    my_fault_client3,
    my_fault_client4,
    my_fault_client5,
    my_fault_client6;
  
  static const boot_tbl_t tbl = {
    "L+R+X+Y+Down, START BUTTON",
    PAD_TRIGGER_L | PAD_TRIGGER_R | PAD_BUTTON_X | PAD_BUTTON_Y | PAD_BUTTON_DOWN,
    PAD_BUTTON_START
  };

#ifndef TARGET_PC
  u32 var1;
  OSThread* var2;
#endif
  void* start;
  void* end;
  DVDDiskID* diskId;
#ifndef TARGET_PC
  u32* base;
  u32* basenext;
#endif

  ReconfigBATs();
  if (fakemain_check) {
    return -1;
  }

  fakemain_check = 1;

#ifdef NDEBUG
  OSReport("NDEBUG defined." VT_RST "\n");
#else
  OSReport("NDEBUG not defined." VT_RST "\n");
#endif

#ifdef _DEBUG
  OSReport("_DEBUG defined." VT_RST "\n");
#else
  OSReport("_DEBUG not defined." VT_RST "\n");
#endif

#ifdef DEBUG
  OSReport("DEBUG=%d" VT_RST "\n", DEBUG);
#endif

  InitialStartTime = osGetTime();
  OSInit();
  OSInitAlarm();

#ifndef TARGET_PC
  /* Fill the unused console stack. Host threads do not expose this layout. */
  var1 = ((u32)OSGetStackPointer() - 0x100);
  var2 = OSGetCurrentThread();
  base = (u32*)var1;

  if ((u8*)base < var2->stackBase) {
    basenext = (u32*)var2->stackEnd + 1;
    if (base > basenext) {
      memset(basenext, 0xfd, (u32)base - (u32)basenext);
    }
  }
#endif

  /* Reset N64 NMI buffer*/
  bzero(osAppNMIBuffer, 16 * sizeof(s32));

  /* Adjust process based on how the console started */
  switch (OSGetResetCode()) {
    case 0:
      OSReport("システムパワーオン\n"); /* system power on */
      break;
    case OS_RESETCODE_RESTART:
      OSReport("リスタート\n"); /* restart */
      OSGetSaveRegion(&start, &end);
      OSReport("OSGetSaveRegion %08x %08x\n", start, end);
      bcopy(NMISaveArea, osAppNMIBuffer, 16 * sizeof(s32));
      break;
    default:
      OSReport("ホットリセット\n"); /* hot reset */
      OSReport("OSGetResetCode=0x%08x\n", OSGetResetCode());
      OSReport("リリース版ではリセットコードを無視します\n"); /* In the release version, the reset code is ignored. */
      break;
  }

  __osInitialize_common();

  /* Setup development environment for dev hardware */
  if ((OSGetConsoleType() & OS_CONSOLE_DEVELOPMENT) != 0) {
    APPNMI_ZURUMODE3_SET();
  } else if (APPNMI_ZURUMODE3_GET()) {
    OSReport("デベロップメントモードに戻します。そしてリセット" VT_RST "\n"); /* Return to development mode, then reset. */
    OSChangeBootMode(0);
    OSResetSystem(1, osAppNMIBuffer[15], 0);
  }

  /* Initialize zurumode levels */
  diskId = DVDGetCurrentDiskID();
  if (diskId->gameVersion == 0x99) {
    APPNMI_DEBUGMODE_SET();
  }
  if (diskId->gameVersion >= 0x90) {
    APPNMI_TESTMODE_SET();
  }

  if (diskId->gameVersion >= 0x90) {
    OSReport("ZURUMODE2 ENABLE\n");
    APPNMI_ZURUMODE2_SET();
  }

  OSReport("osAppNMIBuffer[15]=0x%08x\n", osAppNMIBuffer[15]);
  if (APPNMI_RESETEXEMPT2_GET()) {
    APPNMI_RESETEXEMPT2_CLR();
    APPNMI_RESETEXEMPT_SET();
    OSReport(
        "異常状態でのリセット検出ゆえリセットさん免除フラグをセットしました" VT_RST "\n"); /* Decetected abnormal reset state, so set reset exemption flag. */
  } else {
    APPNMI_RESETEXEMPT_CLR();
  }

  APPNMI_RESETEXEMPT2_SET();
  OSReport("どうぶつの森ブートローダ起動\n"); /* Animal Crossing bootloader startup */
  adjustOSArena();
  JW_Init();

  /* Check enable debug process bars */
  if (APPNMI_DEBUGMODE_GET()) {
    JC_JUTProcBar_setVisible(JC_JUTProcBar_getManager(), APPNMI_TESTMODE_GET() != 0);
    JC_JUTProcBar_setVisibleHeapBar(JC_JUTProcBar_getManager(), APPNMI_TESTMODE_GET() != 0);
  }

  /* Load static.dol symbol map file */
  JC_JUTException_setMapFile("/static.map");
  JC_JUTException_enterAllPad(JC_JUTException_getManager());

  /* Initialize fault 'class' & clients */
  fault_Init();
  fault_AddClientEx(&my_fault_client5, (FaultCallback)fault_callback_vimode, nullptr, 0, 10, 14);
  fault_AddClientEx(&my_fault_client1, (FaultCallback)fault_callback_keyCheck, tbl.msg, (tbl.param_upper << 16) | tbl.param_lower, 10, 14);
  fault_AddClientEx(&my_fault_client2, (FaultCallback)fault_callback_OK, nullptr, 0, 10, 14);
  fault_AddClientEx(&my_fault_client3, (FaultCallback)fault_callback_Setumei, nullptr, 0, 10, 9);
  fault_AddClientEx(&my_fault_client6, (FaultCallback)fault_callback_scroll, nullptr, 0, 1, 9);
  fault_AddClient(&my_fault_client4, (FaultCallback)DisplayArena, nullptr, 0);

  /* Toggle JUtility debug console visibility */
  if (APPNMI_TESTMODE_GET()) {
    JC_JUTAssertion_changeDevice(3);
    JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), TRUE);
  } else {
    JC_JUTAssertion_changeDevice(2);
    JC_JUTDbPrint_setVisible(JC_JUTDbPrint_getManager(), FALSE);
  }
  JC_JUTAssertion_changeDisplayTime(600);

  OSReport("InitialStartTime=%u us\n", (u32)OSTicksToMicroseconds((u64)InitialStartTime));
#ifdef TARGET_PC
  OSReport("[PC] boot: calling sound_initial...\n");
#endif
  sound_initial();
#ifdef TARGET_PC
  OSReport("[PC] boot: calling initial_menu_init...\n");
#endif
  initial_menu_init();
#ifdef TARGET_PC
  OSReport("[PC] boot: calling dvderr_init...\n");
#endif
  dvderr_init();
#ifdef TARGET_PC
  OSReport("[PC] boot: calling sound_initial2...\n");
#endif
  sound_initial2();

  if ((OSGetConsoleType() & OS_CONSOLE_DEVELOPMENT) == 0) {
    OSReport("以降OSReportを無効\n"); /* OSReport disabled from now on. */
#ifndef TARGET_PC
    OSReportDisable();
#endif
  }

#ifdef TARGET_PC
  OSReport("[PC] boot: loading COPYDATE...\n");
#endif
  OSReport("Loging COPYDATE\n");
  boot_copyDate = JC__JKRDvdToMainRam_byName("/COPYDATE", nullptr, EXPAND_SWITCH_DECOMPRESS);
  if (boot_copyDate == nullptr) {
#ifdef TARGET_PC
    OSReport("[PC] boot: COPYDATE not found, skipping fatal error\n");
#else
    OSDVDFatalError();
#endif
  }

#ifdef TARGET_PC
  OSReport("[PC] boot: loading string table...\n");
#endif
  LoadStringTable("/static.str");

#ifdef TARGET_PC
  OSReport("[PC] boot: skipping REL module load (code is statically linked)\n");
  moduleA = (OSModuleHeader*)1;  /* non-null sentinel - code is statically linked */
#else
  OSReport("モジュール(%s)の読み込み中\n", "/foresta.rel.szs");
  moduleA = LoadLink("/foresta.rel.szs");
  if (moduleA == nullptr) {
    moduleA = LoadLink("/foresta.rel.szs");
  }
#endif
  JW_Init2();
  initial_menu_cleanup();

  JC_JKRExpHeap_changeGroupID(JC_JFWSystem_getSystemHeap(), 5);

#ifdef TARGET_PC
  pc_bswap_raw_display_lists();
  mFM_InitActableEndian();
  pc_bswap_u8_tlut_palettes();
  pc_bswap_house_pos_list();
  OSReport("[PC] boot: entering HotStartEntry loop (entry=%p)...\n", (void*)HotStartEntry);
#endif
  while (HotStartEntry != nullptr) {
    OSReport("ホットスタート(%08x)\n", HotStartEntry);
    HotStartEntry = (*(void* (*)())HotStartEntry)();
  }

#ifdef TARGET_PC
  /* No REL module to unlink on PC - code is statically linked */
  moduleA = nullptr;
#else
  UnLink(moduleA);
  moduleA = nullptr;
#endif
  if (StringTable != nullptr) {
    JW_Free(StringTable);
    StringTable = nullptr;
  }

  OSReport("どうぶつの森ブートローダ終了\n"); /* Animal Crossing bootloader end */
  JW_Cleanup();
  return 0;
}
