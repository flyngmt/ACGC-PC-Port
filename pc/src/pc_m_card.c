/* pc_m_card.c - memory card manager: GCI save/load, village generation, ARAM data blocks
 *
 * Card A (save/card_a/) = player's home town
 * Card B (save/card_b/) = second town for visiting (drop any AC GCI file there)
 */
#include "m_card.h"
#include "m_start_data_init.h"
#include "m_common_data.h"
#include "m_flashrom.h"
#include "m_field_make.h"
#include "m_msg.h"
#include "m_npc.h"
#include "m_quest.h"
#include "m_island.h"
#include "m_font.h"
#include "m_vibctl.h"
#include "m_bg_item.h"
#include "m_land.h"
#include "m_private.h"
#include "m_event.h"
#include "m_time.h"
#include "m_scene.h"
#include "m_name_table.h"
#include "sys_math3d.h"
#include "sys_math.h"
#include "zurumode.h"
#include "pc_gci.h"
#include "pc_platform.h"
#include "pc_settings.h"
#include "m_cockroach.h"
#include "m_all_grow_ovl.h"
#include "m_home.h"
#include "lb_rtc.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif
#include <dolphin/os.h>

/* --- Save paths below the configured --user-dir --- */
#define PC_CWD_CARD_A_GCI_PATH "save/card_a/" PC_GCI_FILENAME
#define PC_CWD_CARD_A_PREFIXED_GCI_PATH "save/card_a/8P-GAFE-" PC_GCI_FILENAME
#define PC_CWD_FLAT_GCI_PATH "save/" PC_GCI_FILENAME

static char l_pc_save_dir[PC_GCI_PATH_MAX];
static char l_pc_card_a_dir[PC_GCI_PATH_MAX];
static char l_pc_card_b_dir[PC_GCI_PATH_MAX];
static char l_pc_gci_path[PC_GCI_PATH_MAX];
static char l_pc_gci_path_legacy[PC_GCI_PATH_MAX];

#define PC_SAVE_DIR l_pc_save_dir
#define PC_CARD_A_DIR l_pc_card_a_dir
#define PC_CARD_B_DIR l_pc_card_b_dir
#define PC_GCI_PATH l_pc_gci_path
#define PC_GCI_PATH_LEGACY l_pc_gci_path_legacy

typedef enum {
    PC_START_IDLE,
    PC_START_FAILED,
    PC_START_WRITE_PENDING,
    PC_START_COMPLETE
} pc_start_phase;

static int pc_save_loaded = 0;
static int pc_save_ready = 0;
static pc_save_result pc_save_load_status = PC_SAVE_MISSING;
static pc_start_phase pc_start_state = PC_START_IDLE;

/* --- Travel state --- */
static Save l_keepSave;                        /* Other town's save data (for Card B visit) */
static int l_keepSave_set = FALSE;
static mCD_keep_mail_c l_keepMail;
static mCD_keep_original_c l_keepOriginal;
static mCD_keep_diary_c l_keepDiary;

/* Passport: the traveling player's private data + departing animal */
static union {
    mCD_foreigner_c file;
    u8 sector_align[mCD_ALIGN_SECTORSIZE(sizeof(mCD_foreigner_c))];
} l_mcd_foreigner_file;

static int l_mcd_keep_startCond = 0;
static char l_card_b_gci_path[PC_GCI_PATH_MAX] = {0};

extern void mTM_rtcTime_limit_check(void);
extern void mEv_ClearEventInfo(void);
extern void mEv_toland_clear_common(void);
extern void mNpc_ClearInAnimal(void);
extern void mNpc_FirstClearGoodbyMail(void);
extern void mQst_ClearGrabItemInfo(void);
extern void mISL_ClearKeepIsland(void);
extern void mNpc_ClearCacheName(void);
extern void mTM_clear_renew_is(void);
extern void lbRTC_GetTime(lbRTC_time_c* time);

/* --- ARAM data blocks (mail/diary/original designs) — malloc'd instead of ARAM DMA --- */

static u32 l_aram_alloc_size_table[mCD_ARAM_DATA_NUM] = {
    ALIGN_NEXT(sizeof(mCD_keep_original_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_mail_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_diary_c), 32),
};

static void* l_aram_block_p_table[mCD_ARAM_DATA_NUM];

static void pc_init_diary_entries(void* block) {
    mCD_keep_diary_c* diary = (mCD_keep_diary_c*)block;
    int p, m;
    for (p = 0; p < mCD_KEEP_DIARY_COUNT; p++) {
        for (m = 0; m < mCD_KEEP_DIARY_ENTRY_COUNT; m++) {
            mDi_init_diary(&diary->entries[p][m]);
        }
    }
}

static void pc_init_mail_entries(void* block) {
    mCD_keep_mail_c* keep_mail = (mCD_keep_mail_c*)block;
    Mail_c* mail = (Mail_c*)keep_mail->mail;
    int i, j;
    for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++) {
        mem_clear(keep_mail->folder_names[i], sizeof(keep_mail->folder_names[i]), CHAR_SPACE);
        for (j = 0; j < mCD_KEEP_MAIL_COUNT; j++) {
            mMl_clear_mail(mail);
            mail++;
        }
    }
}

static void pc_init_original_entries(void* block) {
    mCD_keep_original_c* original = (mCD_keep_original_c*)block;
    int page, slot;
    for (page = 0; page < mCD_KEEP_ORIGINAL_PAGE_COUNT; page++) {
        mem_clear(original->folder_names[page], sizeof(original->folder_names[page]), CHAR_SPACE);
        for (slot = 0; slot < mCD_KEEP_ORIGINAL_COUNT; slot++) {
            mNW_InitOriginalData(&original->original[page][slot]);
        }
    }
}

/* Old PC saves can contain an entirely zeroed design block. Preserve any nonzero data. */
static void pc_fix_zeroed_original_entries(mCD_keep_original_c* original, u16 land_id) {
    const u8* bytes = (const u8*)original;
    u32 i;
    for (i = 0; i < sizeof(*original); i++) {
        if (bytes[i] != 0) return;
    }

    pc_init_original_entries(original);
    original->landid = land_id;
    original->checksum = mFRm_GetFlatCheckSum((u16*)original, sizeof(*original), original->checksum);
    OSReport("[PC] GCI: initialized all-zero Mabel design storage to GC blanks in memory\n");
}

static void pc_init_aram_block(int index) {
    static void (*const initialize[mCD_ARAM_DATA_NUM])(void*) = {
        pc_init_original_entries,
        pc_init_mail_entries,
        pc_init_diary_entries,
    };
    void* block = l_aram_block_p_table[index];
    if (block == NULL) return;
    memset(block, 0, l_aram_alloc_size_table[index]);
    initialize[index](block);
}

void mCD_save_data_aram_malloc(void) {
    int i;
    for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
        if (l_aram_block_p_table[i] == NULL) {
            l_aram_block_p_table[i] = malloc(l_aram_alloc_size_table[i]);
            pc_init_aram_block(i);
        }
    }
}

int mCD_save_data_aram_to_main(void* dst, u32 size, u32 idx) {
    void* block;
    if (idx >= mCD_ARAM_DATA_NUM) idx = 0;
    block = l_aram_block_p_table[idx];
    if (block != NULL) {
        u32 copy_size = size < l_aram_alloc_size_table[idx] ? size : l_aram_alloc_size_table[idx];
        memcpy(dst, block, copy_size);
        return TRUE;
    }
    return FALSE;
}

int mCD_save_data_main_to_aram(void* src, u32 size, u32 idx) {
    void* block;
    if (idx >= mCD_ARAM_DATA_NUM) idx = 0;
    block = l_aram_block_p_table[idx];
    if (block != NULL) {
        u32 copy_size = size < l_aram_alloc_size_table[idx] ? size : l_aram_alloc_size_table[idx];
        memcpy(block, src, copy_size);
        return TRUE;
    }
    return FALSE;
}

void mCD_set_aram_save_data(void) {
    int i;
    for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
        pc_init_aram_block(i);
    }
}

/* --- Save paths and game state --- */

static int pc_save_paths_init(void) {
    static int initialized = FALSE;
    if (initialized) return TRUE;

    if (!pc_platform_user_path("save", PC_SAVE_DIR, sizeof(l_pc_save_dir)) ||
        !pc_platform_user_path("save/card_a", PC_CARD_A_DIR, sizeof(l_pc_card_a_dir)) ||
        !pc_platform_user_path("save/card_b", PC_CARD_B_DIR, sizeof(l_pc_card_b_dir)) ||
        !pc_platform_user_path("save/card_a/" PC_GCI_FILENAME, PC_GCI_PATH, sizeof(l_pc_gci_path)) ||
        !pc_platform_user_path("save/" PC_GCI_FILENAME, PC_GCI_PATH_LEGACY,
                               sizeof(l_pc_gci_path_legacy))) {
        OSReport("[PC] Save path exceeds %d bytes\n", PC_GCI_PATH_MAX);
        return FALSE;
    }
    initialized = TRUE;
    return TRUE;
}

static void pc_ensure_save_dirs(void) {
    if (!pc_save_paths_init()) return;
#ifdef _WIN32
    _mkdir(PC_SAVE_DIR);
    _mkdir(PC_CARD_A_DIR);
    _mkdir(PC_CARD_B_DIR);
#else
    mkdir(PC_SAVE_DIR, 0755);
    mkdir(PC_CARD_A_DIR, 0755);
    mkdir(PC_CARD_B_DIR, 0755);
#endif
}

static int pc_save_write_gci_to(const char* gci_path);

static u16 pc_get_land_copy_protect(void) {
    u16 code = (u16)RANDOM(0xFFF0);
    return (u16)(code + 1);
}

static int pc_check_reset_code(Private_c* priv) {
    if (priv->state_flags & mPr_FLAG_BIRTHDAY_ACTIVE) {
        priv->reset_code = 0;
    }
    return priv->reset_code == 0;
}

/* mCD_SetResetCode: arm a nonzero code; still set at next load = reset */
static void pc_set_reset_code(Private_c* priv) {
    priv->reset_code = (u32)RANDOM_F(USHT_MAX_S);
    priv->reset_code++;
}

/* GC save_mode: 0 is a full save; door saves leave the reset code armed. */
static void pc_save_pre_write_side_effects(int save_mode) {
    Private_c* priv = Now_Private;
    u16 copy_protect;
    int i;

    mCkRh_SavePlayTime(Common_Get(player_no));

    if (priv != NULL) {
        if (save_mode == 0) {
            priv->reset_code = 0;

            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                if (ITEM_IS_WISP(priv->inventory.pockets[i])) {
                    mPr_SetPossessionItem(priv, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }
            }
        } else if (pc_check_reset_code(priv)) {
            pc_set_reset_code(priv);
        }
    }

    if (save_mode == 0) {
        mAGrw_ClearMoneyStoneShineGround();
    }

    copy_protect = pc_get_land_copy_protect();
    Common_Set(copy_protect, copy_protect);
    Save_Set(copy_protect, copy_protect);
    Save_Set(travel_hard_time, lbRTC_HardTime());
}

static int pc_save_write_gci(void) {
    if (!pc_save_paths_init()) return FALSE;
    return pc_save_write_gci_to(PC_GCI_PATH);
}

static int pc_save_write_gci_to(const char* gci_path) {
    if (!pc_save_ready || pc_save_load_status == PC_SAVE_INVALID || pc_save_load_status == PC_SAVE_IO_ERROR) return FALSE;
    if (!l_aram_block_p_table[mCD_ARAM_DATA_MAIL] ||
        !l_aram_block_p_table[mCD_ARAM_DATA_ORIGINAL] ||
        !l_aram_block_p_table[mCD_ARAM_DATA_DIARY]) return FALSE;

    pc_ensure_save_dirs();
    Save_Get(save_exist) = TRUE;
    Save_Get(save_check).version = mFRm_VERSION;
    mFRm_SetSaveCheckData(Save_GetPointer(save_check));

    if (!pc_gci_write(gci_path, &common_data.save.save,
                      l_aram_block_p_table[mCD_ARAM_DATA_MAIL],
                      l_aram_block_p_table[mCD_ARAM_DATA_ORIGINAL],
                      l_aram_block_p_table[mCD_ARAM_DATA_DIARY])) return FALSE;
    if (strcmp(gci_path, PC_GCI_PATH) == 0) {
        pc_save_loaded = TRUE;
        pc_save_load_status = PC_SAVE_LOADED;
    }
    return TRUE;
}

static pc_save_result pc_save_read_image(const char* path, pc_gci_image* image) {
    pc_save_result result = pc_gci_read(path, image);
    if (result == PC_SAVE_LOADED) {
        pc_fix_zeroed_original_entries(image->original, image->save->land_info.id);
    }
    return result;
}

static pc_save_result pc_save_read_gci(const char* path) {
    pc_gci_image image;
    pc_save_result result = pc_save_read_image(path, &image);
    int i;
    if (result != PC_SAVE_LOADED) return result;
    mCD_save_data_aram_malloc();
    for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
        if (!l_aram_block_p_table[i]) {
            pc_gci_free(&image);
            return PC_SAVE_IO_ERROR;
        }
    }
    memcpy(&common_data.save.save, image.save, sizeof(Save_t));
    memcpy(l_aram_block_p_table[mCD_ARAM_DATA_MAIL], image.mail, sizeof(*image.mail));
    memcpy(l_aram_block_p_table[mCD_ARAM_DATA_ORIGINAL], image.original, sizeof(*image.original));
    memcpy(l_aram_block_p_table[mCD_ARAM_DATA_DIARY], image.diary, sizeof(*image.diary));
    Common_Set(copy_protect, Save_Get(copy_protect));
    pc_gci_free(&image);
    return PC_SAVE_LOADED;
}

static int pc_save_read_gci_to_keep(const char* path) {
    pc_gci_image image;
    l_keepSave_set = FALSE;
    if (pc_save_read_image(path, &image) != PC_SAVE_LOADED) return FALSE;
    memcpy(&l_keepSave.save, image.save, sizeof(Save_t));
    memcpy(&l_keepMail, image.mail, sizeof(l_keepMail));
    memcpy(&l_keepOriginal, image.original, sizeof(l_keepOriginal));
    memcpy(&l_keepDiary, image.diary, sizeof(l_keepDiary));
    pc_gci_free(&image);
    l_keepSave_set = TRUE;
    return TRUE;
}

/* Legacy saves may be relative to the working directory or executable directory. */
static void pc_save_migrate_legacy(void) {
    char exe_card_a[PC_GCI_PATH_MAX] = {0};
    char exe_card_a_prefixed[PC_GCI_PATH_MAX] = {0};
    char exe_flat[PC_GCI_PATH_MAX] = {0};
    const char* sources[7];
    int count = 0;
    int i;

    sources[count++] = PC_GCI_PATH_LEGACY;
    sources[count++] = PC_CWD_CARD_A_GCI_PATH;
    sources[count++] = PC_CWD_CARD_A_PREFIXED_GCI_PATH;
    sources[count++] = PC_CWD_FLAT_GCI_PATH;
    if (pc_platform_base_path(PC_CWD_CARD_A_GCI_PATH, exe_card_a, sizeof(exe_card_a))) {
        sources[count++] = exe_card_a;
    }
    if (pc_platform_base_path(PC_CWD_CARD_A_PREFIXED_GCI_PATH, exe_card_a_prefixed,
                              sizeof(exe_card_a_prefixed))) {
        sources[count++] = exe_card_a_prefixed;
    }
    if (pc_platform_base_path(PC_CWD_FLAT_GCI_PATH, exe_flat, sizeof(exe_flat))) {
        sources[count++] = exe_flat;
    }

    pc_ensure_save_dirs();
    for (i = 0; i < count; i++) {
        if (pc_gci_import(sources[i], PC_GCI_PATH)) break;
    }
}

static int pc_card_find_town(int channel, char* path, int path_size) {
    const char* relative_dir = channel == mCD_SLOT_B ? "save/card_b" : "save/card_a";
    char active_dir[PC_GCI_PATH_MAX];
    char exe_dir[PC_GCI_PATH_MAX] = {0};
    char filename[PC_GCI_PATH_MAX];
    char source[PC_GCI_PATH_MAX];
    const char* directories[] = { active_dir, relative_dir, exe_dir };
    int i, length;

    path[0] = '\0';
    if (!pc_platform_user_path(relative_dir, active_dir, sizeof(active_dir))) return FALSE;
    if (!pc_platform_base_path(relative_dir, exe_dir, sizeof(exe_dir))) exe_dir[0] = '\0';

    for (i = 0; i < ARRAY_COUNT(directories); i++) {
        if (directories[i][0] == '\0') continue;
        filename[0] = '\0';
        while (pc_platform_next_gci(directories[i], filename, sizeof(filename))) {
            length = snprintf(path, path_size, "%s/%s", active_dir, filename);
            if (length < 0 || length >= path_size) continue;
            if (i == 0) return TRUE;

            length = snprintf(source, sizeof(source), "%s/%s", directories[i], filename);
            if (length < 0 || length >= (int)sizeof(source)) continue;
            pc_ensure_save_dirs();
            if (pc_gci_import(source, path)) return TRUE;
        }
    }
    path[0] = '\0';
    return FALSE;
}

static pc_save_result pc_save_scan_gci_dir(void) {
    char path[PC_GCI_PATH_MAX];
    pc_save_result result;
    pc_save_result candidate;

    result = pc_save_read_gci(PC_GCI_PATH);
    if (result != PC_SAVE_MISSING) return result;
    if (!pc_platform_user_path("save/card_a/8P-GAFE-" PC_GCI_FILENAME, path, sizeof(path))) return PC_SAVE_IO_ERROR;
    candidate = pc_save_read_gci(path);
    if (candidate != PC_SAVE_MISSING) return candidate;
    if (pc_card_find_town(mCD_SLOT_A, path, sizeof(path))) {
        return pc_save_read_gci(path);
    }
    return PC_SAVE_MISSING;
}

static pc_save_result pc_save_find_and_load(void) {
    pc_save_result result;
    if (!pc_save_paths_init()) return PC_SAVE_IO_ERROR;
    pc_ensure_save_dirs();
    result = pc_save_read_gci(PC_GCI_PATH);
    if (result != PC_SAVE_MISSING) return result;
    pc_save_migrate_legacy();
    return pc_save_scan_gci_dir();
}

static int pc_save_check_and_load(void) {
    pc_save_result result;
    pc_save_ready = FALSE;
    pc_start_state = PC_START_IDLE;
    result = pc_save_find_and_load();
    if (result == PC_SAVE_MISSING && pc_save_load_status != PC_SAVE_MISSING) {
        result = PC_SAVE_IO_ERROR;
    }
    pc_save_load_status = result;
    pc_save_loaded = result == PC_SAVE_LOADED;
    Common_Set(save_error_type, result == PC_SAVE_INVALID || result == PC_SAVE_IO_ERROR ? mFRm_ERROR_DATA_CORRUPTED : 0);
    Common_Set(memcard_slot, mCD_SLOT_A);
    if (!pc_save_loaded) mFRm_ClearSaveCheckData(Save_GetPointer(save_check));
    return pc_save_loaded;
}

/* --- Card B scanning --- */

static int pc_card_b_find_town(void) {
    if (pc_card_find_town(mCD_SLOT_B, l_card_b_gci_path, sizeof(l_card_b_gci_path))) {
        return TRUE;
    }
    l_card_b_gci_path[0] = '\0';
    return FALSE;
}

/* --- Memory card API implementation --- */

void mCD_init_card(void) {
    /* Town and NES saves bypass Aurora CARD emulation; CARDInit would create an unused card directory. */
}

void mCD_InitAll(void) {
    pc_save_ready = FALSE;
    pc_start_state = PC_START_IDLE;
    /* ARAM blocks must persist — don't null them */
    memset(&l_mcd_foreigner_file, 0, sizeof(l_mcd_foreigner_file));
    l_keepSave_set = FALSE;
    l_mcd_keep_startCond = 0;
    l_card_b_gci_path[0] = '\0';
}

static int pc_start_write(void) {
    if (!pc_save_write_gci()) return mCD_TRANS_ERR_IOERROR;
    pc_start_state = PC_START_COMPLETE;
    return mCD_TRANS_ERR_NONE;
}

static int pc_start_persist(void) {
    u16 copy_protect = pc_get_land_copy_protect();
    Common_Set(copy_protect, copy_protect);
    Save_Set(copy_protect, copy_protect);
    Save_Set(travel_hard_time, lbRTC_HardTime());
    pc_start_state = PC_START_WRITE_PENDING;
    return pc_start_write();
}

static int pc_start_resident(void) {
    Private_c* priv = Now_Private;
    if (priv == NULL) return mCD_TRANS_ERR_IOERROR;
    Common_Set(reset_flag, FALSE);
    if (!pc_check_reset_code(priv) && !ZURUMODE2_ENABLED() && !g_pc_settings.disable_resetti) {
        Common_Set(reset_flag, TRUE);
        priv->reset_count++;
    }
    pc_set_reset_code(priv);
    return pc_start_persist();
}

static int pc_start_return_home(int player_no) {
    Private_c* foreigner = mPr_GetForeignerP();
    mPr_CopyPrivateInfo(foreigner, &l_mcd_foreigner_file.file.priv);
    mPr_LoadPak_and_SetPrivateInfo2(foreigner, (u8)player_no);
    mHm_SetNowHome();
    if (Common_Get(player_no) != mPr_FOREIGNER && Now_Private != NULL) {
        pc_set_reset_code(Now_Private);
        return pc_start_persist();
    }
    pc_start_state = PC_START_COMPLETE;
    return mCD_TRANS_ERR_NONE;
}

int mCD_InitGameStart_bg(int player_no, int card_private_idx, int start_cond, s32* mounted_chan) {
    static const int init_modes[mCD_START_COND_NUM] = {
        mSDI_INIT_MODE_NEW, mSDI_INIT_MODE_FROM, mSDI_INIT_MODE_NEW_PLAYER,
        mSDI_INIT_MODE_PAK, mSDI_INIT_MODE_PAK,
    };
    int mode;
    (void)card_private_idx;
    if (mounted_chan) *mounted_chan = mCD_SLOT_A;
    if (pc_save_load_status == PC_SAVE_INVALID || pc_save_load_status == PC_SAVE_IO_ERROR ||
        start_cond < 0 || start_cond >= mCD_START_COND_NUM || player_no < 0 || player_no >= TOTAL_PLAYER_NUM) {
        return mCD_TRANS_ERR_IOERROR;
    }

    switch (pc_start_state) {
        case PC_START_COMPLETE: return mCD_TRANS_ERR_NONE;
        case PC_START_FAILED: return mCD_TRANS_ERR_IOERROR;
        case PC_START_WRITE_PENDING: return pc_start_write();
        case PC_START_IDLE: break;
    }
    pc_start_state = PC_START_FAILED;
    mode = init_modes[start_cond];
    if (!pc_save_loaded) {
        if (start_cond != mCD_START_COND_0 && start_cond != mCD_START_COND_2) return mCD_TRANS_ERR_IOERROR;
        mode = mSDI_INIT_MODE_NEW;
    }
    if (!mSDI_StartDataInit(gamePT, player_no, mode)) return mCD_TRANS_ERR_IOERROR;
    l_mcd_keep_startCond = start_cond;
    pc_save_ready = TRUE;

    switch (start_cond) {
        case mCD_START_COND_1:
            return pc_start_resident();
        case mCD_START_COND_OUTGOING_FOREIGNER:
            return pc_start_return_home(player_no);
        case mCD_START_COND_INCOMING_FOREIGNER:
            Common_Set(now_private, &l_mcd_foreigner_file.file.priv);
            Common_Set(player_no, mPr_FOREIGNER);
            break;
        default:
            break;
    }
    pc_start_state = PC_START_COMPLETE;
    return mCD_TRANS_ERR_NONE;
}

void mCD_LoadLand(void) {
    pc_save_check_and_load();
}

int mCD_SaveHome_bg(int param_1, int* chan) {
    int slot = mCD_GetThisLandSlotNo();
    int result;

    if (chan) *chan = slot;
    if (slot == mCD_SLOT_B && l_card_b_gci_path[0] == '\0') {
        OSReport("[PC] mCD_SaveHome_bg: no Card B path\n");
        return mCD_TRANS_ERR_IOERROR;
    }

    pc_save_pre_write_side_effects(param_1);

    if (slot == mCD_SLOT_B) {
        result = pc_save_write_gci_to(l_card_b_gci_path);
    } else {
        result = pc_save_write_gci();
    }

    if (!result) {
        OSReport("[PC] mCD_SaveHome_bg: save failed!\n");
        return mCD_TRANS_ERR_IOERROR;
    }

    return mCD_TRANS_ERR_NONE;
}

/* --- Travel / Station functions --- */

static pc_save_result pc_read_gci_land_info(const char* path, mLd_land_info_c* out) {
    pc_gci_image image;
    pc_save_result result = pc_save_read_image(path, &image);
    if (result != PC_SAVE_LOADED) return result;
    memcpy(out, &image.save->land_info, sizeof(*out));
    pc_gci_free(&image);
    return PC_SAVE_LOADED;
}

int mCD_CheckStation_bg(s32* chan) {
    int is_foreigner = mLd_PlayerManKindCheck();
    int slot = is_foreigner ? mCD_SLOT_A : mCD_SLOT_B;
    const char* path = is_foreigner ? PC_GCI_PATH : l_card_b_gci_path;
    mLd_land_info_c land_info;

    if (chan) *chan = slot;
    if (!is_foreigner && !pc_card_b_find_town()) {
        OSReport("[PC] CheckStation: no destination town on Card B\n");
        return mCD_TRANS_ERR_NO_TOWN_DATA;
    }

    switch (pc_read_gci_land_info(path, &land_info)) {
        case PC_SAVE_MISSING: return mCD_TRANS_ERR_NO_TOWN_DATA;
        case PC_SAVE_INVALID: return mCD_TRANS_ERR_CORRUPT;
        case PC_SAVE_IO_ERROR: return mCD_TRANS_ERR_IOERROR;
        case PC_SAVE_LOADED: break;
    }
    if (!mLd_CheckId(land_info.id)) return mCD_TRANS_ERR_CORRUPT;
    if (mLd_CheckThisLand(land_info.name, land_info.id)) {
        OSReport("[PC] CheckStation: destination is the current town\n");
        return mCD_TRANS_ERR_LAND_EXIST;
    }

    return mCD_TRANS_ERR_NONE_NEXTLAND;
}

/* Persist current town and load the "other" town into l_keepSave.
 *  - Resident: save home (Card A, marked away) + load Card B → l_keepSave.
 *  - Foreigner: save visited town (Card B) + load Card A → l_keepSave. */
int mCD_SaveStation_NextLand_bg(s32* chan) {
    int is_foreigner = mLd_PlayerManKindCheck();

    l_keepSave_set = FALSE;
    if (chan) *chan = is_foreigner ? mCD_SLOT_B : mCD_SLOT_A;
    if (l_card_b_gci_path[0] == '\0') {
        OSReport("[PC] SaveStation_NextLand: no Card B path\n");
        return mCD_TRANS_ERR_NO_TOWN_DATA;
    }

    if (is_foreigner) {
        /* Record departure info (visited town) for Rover. */
        {
            mCD_persistent_data_c* persistant = Common_GetPointer(travel_persistent_data);
            int i;
            memcpy(&persistant->land, Save_GetPointer(land_info), sizeof(mLd_land_info_c));
            for (i = 0; i < PLAYER_NUM; i++) {
                mPr_CopyPersonalID(&persistant->pid[i], &Save_Get(private_data[i]).player_ID);
            }
        }

        /* Refresh passport from Now_Private so visit-time changes carry home. */
        {
            Private_c* current_priv = Now_Private;
            if (current_priv) {
                mPr_CopyPrivateInfo(&l_mcd_foreigner_file.file.priv, current_priv);
                l_mcd_foreigner_file.file.checksum = 0;
                l_mcd_foreigner_file.file.checksum =
                    mFRm_GetFlatCheckSum((u16*)&l_mcd_foreigner_file.file,
                                         sizeof(mCD_foreigner_c),
                                         l_mcd_foreigner_file.file.checksum);
            }
        }

        if (!pc_save_write_gci_to(l_card_b_gci_path)) {
            OSReport("[PC] SaveStation_NextLand(return): failed to save visited town\n");
            return mCD_TRANS_ERR_IOERROR;
        }

        if (!pc_save_read_gci_to_keep(PC_GCI_PATH)) {
            OSReport("[PC] SaveStation_NextLand(return): failed to load home town\n");
            if (chan) *chan = mCD_SLOT_A;
            return mCD_TRANS_ERR_CORRUPT;
        }

        l_mcd_keep_startCond = mCD_START_COND_OUTGOING_FOREIGNER;

        if (chan) *chan = mCD_SLOT_A;
        return mCD_TRANS_ERR_NONE;
    }

    if (!pc_save_read_gci_to_keep(l_card_b_gci_path)) {
        OSReport("[PC] SaveStation_NextLand: failed to load Card B town\n");
        if (chan) *chan = mCD_SLOT_B;
        return mCD_TRANS_ERR_CORRUPT;
    }

    /* Preserve the departure town for Rover's dialogue. */
    {
        mCD_persistent_data_c* persistant = Common_GetPointer(travel_persistent_data);
        int i;
        memcpy(&persistant->land, Save_GetPointer(land_info), sizeof(mLd_land_info_c));
        for (i = 0; i < PLAYER_NUM; i++) {
            mPr_CopyPersonalID(&persistant->pid[i], &Save_Get(private_data[i]).player_ID);
        }
    }

    /* Capture the full player data before marking the resident as away. */
    {
        Private_c* current_priv = Now_Private;
        memset(&l_mcd_foreigner_file, 0, sizeof(l_mcd_foreigner_file));
        if (current_priv) {
            mPr_CopyPrivateInfo(&l_mcd_foreigner_file.file.priv, current_priv);
        }
        memset(&l_mcd_foreigner_file.file.remove_animal, 0, sizeof(Animal_c));
        l_mcd_foreigner_file.file.copy_protect = (u16)Common_Get(copy_protect);
        l_mcd_foreigner_file.file.checksum = 0;
        l_mcd_foreigner_file.file.checksum =
            mFRm_GetFlatCheckSum((u16*)&l_mcd_foreigner_file.file,
                                 sizeof(mCD_foreigner_c),
                                 l_mcd_foreigner_file.file.checksum);
    }

    /* GC uses exists == FALSE to detect an interrupted visit and apply its return-home penalty. */
    if (Now_Private != NULL && mLd_PlayerManKindCheckNo(Common_Get(player_no)) == FALSE) {
        Now_Private->exists = FALSE;
        Now_Private->reset_code = 0;
    }

    if (!pc_save_write_gci()) {
        if (Now_Private != NULL) {
            Now_Private->exists = l_mcd_foreigner_file.file.priv.exists;
            Now_Private->reset_code = l_mcd_foreigner_file.file.priv.reset_code;
        }
        l_keepSave_set = FALSE;
        OSReport("[PC] SaveStation_NextLand: failed to save home town\n");
        return mCD_TRANS_ERR_IOERROR;
    }

    l_mcd_keep_startCond = mCD_START_COND_INCOMING_FOREIGNER;

    if (chan) *chan = mCD_SLOT_B;
    return mCD_TRANS_ERR_NONE;
}

/* PC travel requires a destination town; standalone passport files are unsupported. */
int mCD_SaveStation_Passport_bg(s32* chan) {
    if (chan) *chan = mLd_PlayerManKindCheck() ? mCD_SLOT_A : mCD_SLOT_B;
    l_keepSave_set = FALSE;
    OSReport("[PC] SaveStation_Passport: no destination town loaded; travel blocked\n");
    return mCD_TRANS_ERR_NO_TOWN_DATA;
}

void mCD_toNextLand(void) {
    Save_t* save = &l_keepSave.save;
    int scene_no;
    mCD_persistent_data_c persis;
    mLd_land_info_c* land_info;
    int last_scene_no;
    mActor_name_t last_field_id;
    s16 demo_profile[2];
    Time_c time;
    Transition_c transition;
    int rtc_enabled;

    if (l_keepSave_set != TRUE) {
        return;
    }

    land_info = &save->land_info;
    if (!mLd_CheckId(land_info->id)) {
        OSReport("[PC] toNextLand: invalid land_info in l_keepSave\n");
        return;
    }

    if (g_pc_verbose) {
        OSReport("[PC] Travel transition: from=0x%04X to=0x%04X start_cond=%d\n",
                 Save_Get(land_info).id, land_info->id, l_mcd_keep_startCond);
    }
    scene_no = Save_Get(scene_no);

    /* Save persistent data that must survive the common_data wipe */
    memcpy(&persis, Common_GetPointer(travel_persistent_data), sizeof(persis));
    last_scene_no = Common_Get(last_scene_no);
    last_field_id = Common_Get(last_field_id);
    memcpy(demo_profile, Common_Get(demo_profiles), sizeof(demo_profile));
    memcpy(&time, Common_GetPointer(time), sizeof(time));
    memcpy(&transition, Common_GetPointer(transition), sizeof(transition));

    memset(&common_data, 0, sizeof(common_data_t));

    memcpy(Common_GetPointer(travel_persistent_data), &persis, sizeof(persis));
    Common_Set(last_field_id, last_field_id);
    Common_Set(last_scene_no, last_scene_no);
    memcpy(Common_Get(demo_profiles), demo_profile, sizeof(demo_profile));
    memcpy(Common_GetPointer(time), &time, sizeof(time));
    memcpy(Common_GetPointer(transition), &transition, sizeof(transition));

    memcpy(Common_GetPointer(save), save, sizeof(Save));

    Common_Set(copy_protect, Save_Get(copy_protect));
    Save_Set(scene_no, scene_no);

    rtc_enabled = Common_Get(time.rtc_enabled);
    Common_Set(time.rtc_enabled, TRUE);
    mTM_rtcTime_limit_check();
    Common_Set(time.rtc_enabled, rtc_enabled);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));

    Common_Set(now_private, &l_mcd_foreigner_file.file.priv);
    Common_Set(player_no, mPr_FOREIGNER);
    Common_Set(auto_nwrite_set, FALSE);
    memset(Common_GetPointer(auto_nwrite_time), 0, sizeof(Common_Get(auto_nwrite_time)));
    Common_Set(ball_pos, ZeroVec);

    /* Clear town-specific state */
    mTM_clear_renew_is();
    mEv_ClearEventInfo();
    mEv_toland_clear_common();
    mNpc_ClearInAnimal();
    mNpc_FirstClearGoodbyMail();
    mQst_ClearGrabItemInfo();
    memset(Common_Get(npc_schedule), 0, sizeof(Common_Get(npc_schedule)));
    mISL_ClearKeepIsland();
    memset(Common_GetPointer(unused_mail_26522), 0, sizeof(Mail_c));
    Common_Set(_2664E, 0);
    Common_Set(_26650, 0);
    mNpc_ClearCacheName();

    Common_Set(submenu_disabled, TRUE);

    pc_start_state = PC_START_IDLE;

    memset(&l_keepSave, 0, sizeof(Save));
    l_keepSave_set = FALSE;

    mCD_save_data_main_to_aram(&l_keepMail, l_aram_alloc_size_table[mCD_ARAM_DATA_MAIL], mCD_ARAM_DATA_MAIL);
    mCD_save_data_main_to_aram(&l_keepOriginal, l_aram_alloc_size_table[mCD_ARAM_DATA_ORIGINAL], mCD_ARAM_DATA_ORIGINAL);
    mCD_save_data_main_to_aram(&l_keepDiary, l_aram_alloc_size_table[mCD_ARAM_DATA_DIARY], mCD_ARAM_DATA_DIARY);
}

void mCD_ReCheckLoadLand(GAME_PLAY* play) {
    int scene = Save_Get(scene_no);

    /* Reload home town from Card A at the same point as GC. */
    mCD_LoadLand();
    Save_Set(scene_no, scene);

    if (Common_Get(save_error_type) != 0) {
        play->next_scene_no = SCENE_PLAYERSELECT_3;
        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, RSV_NO);
    } else if (mFRm_CheckSaveData()) {
        int rtc_on = Common_Get(time.rtc_enabled);
        Common_Set(time.rtc_enabled, TRUE);
        mTM_rtcTime_limit_check();
        play->next_scene_no = SCENE_PLAYERSELECT_2;
        Common_Set(time.rtc_enabled, rtc_on);
        mEv_ClearEventInfo();
    } else {
        play->next_scene_no = SCENE_PLAYERSELECT;
        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, RSV_NO);
    }
}

/* --- Remaining card management functions --- */

int mCD_GetThisLandSlotNo(void) {

    if (Common_Get(player_no) == mPr_FOREIGNER) return mCD_SLOT_B;
    return mCD_SLOT_A;
}

int mCD_GetThisLandSlotNo_code(int* player_no, s32* slot_card_results) {
    int slot = mCD_GetThisLandSlotNo();

    if (player_no) *player_no = Common_Get(player_no);
    if (slot_card_results) {
        slot_card_results[mCD_SLOT_A] = CARD_RESULT_READY;
        slot_card_results[mCD_SLOT_B] = (slot == mCD_SLOT_B) ? CARD_RESULT_READY : CARD_RESULT_NOCARD;
    }
    return slot;
}

int mCD_GetSaveHomeSlotNo(void) {
    return mCD_SLOT_A;
}

int mCD_GetPlayerNum(void) {
    return 1;
}

int mCD_GetCardPrivateNameCopy(u8* name, int idx) {
    (void)name;
    (void)idx;
    return 0;
}

int mCD_CheckCardPlayerNative(int idx) {

    if (Common_Get(player_no) == mPr_FOREIGNER && idx == mPr_FOREIGNER) {
        return FALSE;
    }
    return TRUE;
}

int mCD_CheckPassportFile(void) {

    if (l_mcd_foreigner_file.file.checksum != 0) {
        return 0; /* passport exists on slot 0 */
    }
    return -1; /* no passport */
}

int mCD_CheckBrokenPassportFile(int slot) {
    (void)slot;
    return 0;
}

int mCD_EraseBrokenLand_bg(int* slot) {
    if (slot) *slot = mCD_SLOT_A;
    return mCD_TRANS_ERR_NONE;
}

int mCD_EraseLand_bg(int* slot) {
    if (slot) *slot = mCD_SLOT_A;
    return mCD_TRANS_ERR_NONE;
}

int mCD_ErasePassportFile_bg(int slot) {
    (void)slot;

    memset(&l_mcd_foreigner_file, 0, sizeof(l_mcd_foreigner_file));
    return mCD_TRANS_ERR_NONE;
}

int mCD_SaveErasePlayer_bg(int* slot) {
    if (slot) *slot = mCD_SLOT_A;
    return mCD_TRANS_ERR_NONE;
}

int mCD_card_format_bg(s32 chan) {
    (void)chan;
    return mCD_TRANS_ERR_NONE;
}

void mCD_PrintErrInfo(gfxprint_t* gfxprint) {
    (void)gfxprint;
}
