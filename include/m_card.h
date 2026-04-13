#ifndef M_CARD_H
#define M_CARD_H

#include "dolphin/types.h"
#include "types.h"
#include "libu64/gfxprint.h"
#include "m_personal_id.h"
#include "m_land_h.h"
#include "m_private.h"
#include "m_diary.h"
#include "dolphin/card.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCD_LAND_SAVE_SIZE 0x72000
#define mCD_ORIGINAL_SAVE_SIZE 0xE000
#define mCD_MAIL_SAVE_SIZE 0xC000
#define mCD_DIARY_SAVE_SIZE 0xC000
#define mCD_PRESENT_SAVE_SIZE 0x2000
#define mCD_PLAYER_SAVE_SIZE 0x6000
/* Offset to start of save data when loading from card.
   Skips the comment, banner, & icon data. */
#define mCD_SAVE_DATA_OFS 0x1440
#define mCD_LAND_PROTECT_CODE_MAGIC0 0x3C1C

enum {
    mCD_SLOT_A,
    mCD_SLOT_B,

    mCD_SLOT_NUM
};

enum {
    mCD_START_COND_0,
    mCD_START_COND_1,
    mCD_START_COND_2,
    mCD_START_COND_INCOMING_FOREIGNER,
    mCD_START_COND_OUTGOING_FOREIGNER,

    mCD_START_COND_NUM
};

enum {
    mCD_ERROR_NOT_ENABLED, // N [not enabled?]
    mCD_ERROR_AREA,        // A [area?]
    mCD_ERROR_WRITE,       // W [write]
    mCD_ERROR_READ,        // R [read?]
    mCD_ERROR_CHECKSUM,    // C [checksum]
    mCD_ERROR_OUTDATED,    // O [outdated]
    mCD_ERROR_CREATE,      // c [create]

    mCD_ERROR_NUM
};

enum {
    mCD_SPACE_BG_GET_SLOT,
    mCD_SPACE_BG_MAIN,

    mCD_SPACE_BG_NUM
};

enum {
    mCD_ARAM_DATA_ORIGINAL,
    mCD_ARAM_DATA_MAIL,
    mCD_ARAM_DATA_DIARY,
    
    mCD_ARAM_DATA_NUM
};

enum {
    mCD_FILE_SAVE_MISC,
    mCD_FILE_SAVE_MAIN,
    mCD_FILE_SAVE_MAIN_BAK,
    mCD_FILE_SAVE_MAIL,
    mCD_FILE_SAVE_ORIGINAL,
    mCD_FILE_SAVE_DIARY,
    mCD_FILE_PRESENT,
    mCD_FILE_PLAYER,

    mCD_FILE_NUM
};

/* This is also a priority table where lower = higher priority */
enum {
    mCD_TRANS_ERR_NONE,
    mCD_TRANS_ERR_NONE_NEXTLAND, // leave town
    mCD_TRANS_ERR_IOERROR,
    mCD_TRANS_ERR_DAMAGED,
    mCD_TRANS_ERR_BROKEN_WRONGENCODING,
    mCD_TRANS_ERR_REPAIR,
    mCD_TRANS_ERR_NOT_MEMCARD,
    mCD_TRANS_ERR_WRONG_LAND,
    mCD_TRANS_ERR_INVALID_NOLAND_CODE,
    mCD_TRANS_ERR_LAND_EXIST,
    mCD_TRANS_ERR_PASSPORT_EXIST,
    mCD_TRANS_ERR_NO_FILES,
    mCD_TRANS_ERR_NO_SPACE,
    mCD_TRANS_ERR_TOWN_INVALID,
    mCD_TRANS_ERR_OTHER_TOWN,
    mCD_TRANS_ERR_15,
    mCD_TRANS_ERR_16,
    mCD_TRANS_ERR_CORRUPT,
    mCD_TRANS_ERR_18,
    mCD_TRANS_ERR_TRAVEL_DATA_MISSING,
    mCD_TRANS_ERR_TRAVEL_DATA_EXISTS,
    mCD_TRANS_ERR_WRONGDEVICE,
    mCD_TRANS_ERR_NOCARD,
    mCD_TRANS_ERR_NO_TOWN_DATA,
    mCD_TRANS_ERR_GENERIC,
    mCD_TRANS_ERR_BUSY,

    mCD_TRANS_ERR_NUM
};

enum {
    mCD_HOME_SFX_NORMAL,
    mCD_HOME_SFX_DELETE,

    mCD_HOME_SFX_NUM
};

#define mCD_RESULT_ERROR -1
#define mCD_RESULT_BUSY 0
#define mCD_RESULT_SUCCESS 1

#define mCD_MEMCARD_SECTORSIZE 0x2000
#define mCD_ALIGN_SECTORSIZE(s) ALIGN_NEXT(s, mCD_MEMCARD_SECTORSIZE)

typedef struct memcard_header_s {
    char comment[CARD_COMMENT_SIZE];
    u8 banner[0xE00];
    u8 icon[0x600];
} MemcardHeader_c;

typedef struct {
    mLd_land_info_c land;
    PersonalID_c pid[PLAYER_NUM];
} mCD_persistent_data_c;

#define mCD_KEEP_ORIGINAL_PAGE_COUNT 8
#define mCD_KEEP_ORIGINAL_COUNT 12
#define mCD_KEEP_ORIGINAL_FOLDER_NAME_LEN 12

typedef struct {
    u16 checksum;
    u16 landid;
    u8 folder_names[mCD_KEEP_ORIGINAL_PAGE_COUNT][mCD_KEEP_ORIGINAL_FOLDER_NAME_LEN];
    mNW_original_design_c original[mCD_KEEP_ORIGINAL_PAGE_COUNT][mCD_KEEP_ORIGINAL_COUNT];
    int _CC80; // force size to 0xCCA0
} mCD_keep_original_c ATTRIBUTE_ALIGN(32);

#define mCD_KEEP_ORIGINAL_SIZE ALIGN_NEXT(sizeof(mCD_keep_original_c), 32)

#define mCD_KEEP_MAIL_PAGE_COUNT 8
#define mCD_KEEP_MAIL_COUNT 20
#define mCD_KEEP_MAIL_FOLDER_NAME_LEN 12

typedef struct {
    u16 checksum;
    u16 landid;
    u8 folder_names[mCD_KEEP_MAIL_PAGE_COUNT][mCD_KEEP_MAIL_FOLDER_NAME_LEN];
    Mail_c mail[mCD_KEEP_MAIL_PAGE_COUNT][mCD_KEEP_MAIL_COUNT];
} mCD_keep_mail_c ATTRIBUTE_ALIGN(32);

#define mCD_KEEP_MAIL_SIZE ALIGN_NEXT(sizeof(mCD_keep_mail_c), 32)

#define mCD_KEEP_DIARY_COUNT PLAYER_NUM
#define mCD_KEEP_DIARY_ENTRY_COUNT lbRTC_MONTHS_MAX

typedef struct {
    u16 checksum;
    mDi_entry_c entries[mCD_KEEP_DIARY_COUNT][mCD_KEEP_DIARY_ENTRY_COUNT];
} mCD_keep_diary_c ATTRIBUTE_ALIGN(32);

#define mCD_KEEP_DIARY_SIZE ALIGN_NEXT(sizeof(mCD_keep_diary_c), 32)

typedef struct {
    MemcardHeader_c header;
    u8 pad[32];
    mCD_keep_original_c original ATTRIBUTE_ALIGN(32);
    mCD_keep_mail_c mail ATTRIBUTE_ALIGN(32);
    mCD_keep_diary_c diary ATTRIBUTE_ALIGN(32);
} mCD_others_c;

typedef struct {
    CARDStat stat;
    s32 fileNo;
    s32 freeBytes;
    s32 result;
    s32 game_result;
    void* workArea;

    u8 _80[0x8C - 0x80];
    int _8C;
    int _90;
} mCD_memMgr_card_info_c;

typedef struct {
    int proc;
    int _04;
    s32 fileNo;
    s32 chan;
    int _10;
    int _14;
    s32 game_result;
    int _1C;
} mCD_memMgr_fileInfo_c;

typedef struct private_item_keep_s {
    mActor_name_t items[mPr_POCKETS_SLOT_COUNT];
    u8 ticket_expiry_month;
    u8 ticket_storage;
    u32 item_cond;
    u32 wallet;
    mQst_delivery_c delivery[mPr_DELIVERY_QUEST_NUM];
    mQst_errand_c errand[mPr_ERRAND_QUEST_NUM];
    Mail_c mail[mPr_INVENTORY_MAIL_COUNT];
    mPr_catalog_order_c catalog_order[mPr_CATALOG_ORDER_NUM];
    u8 _0FF0;
    Anmremail_c remail;
    mPr_animal_memory_c animal_memory;
} mCD_PrivateItem_c;

typedef struct {
    int chan;
    int loaded_file_type;
    u32 workArea_size;
    void* workArea;
    u8 _0010;
    mCD_memMgr_fileInfo_c save_home_info;
    mCD_memMgr_fileInfo_c init_game_start_info;
    mCD_memMgr_card_info_c cards[CARD_NUM_CHANS];
    u32 _017C;
    int land_saved;
    int copy_protect;
    int _0188;
    int _018C;
    int _0190;
    int _0194;
    int _0198;
    int _019C;
    int _01A0;
    int broken_file_idx;
    mCD_PrivateItem_c private_item;
    char filename[32];
} mCD_memMgr_c;

/* Bonus letter */
#define mCD_PRESENT_MAX 9

typedef struct present_save_s {
    u16 checksum;
    u16 present_count;
    Mail_c letters[mCD_PRESENT_MAX];
} PresentSave_c;

typedef union {
    struct {
        MemcardHeader_c header;
        PresentSave_c save;
    };
    u8 __align_sector[mCD_MEMCARD_SECTORSIZE];
} PresentSaveFile_c ATTRIBUTE_ALIGN(32);

typedef struct {
    MemcardHeader_c header;
    u16 checksum; // presumed
    mCD_keep_mail_c keep_mail ATTRIBUTE_ALIGN(32);
    mCD_keep_original_c keep_original ATTRIBUTE_ALIGN(32);
    mCD_keep_diary_c keep_diary ATTRIBUTE_ALIGN(32);
} OthersSave_c;

typedef union {
    OthersSave_c save;
    u8 __align[ALIGN_NEXT(sizeof(OthersSave_c), mCD_MEMCARD_SECTORSIZE)];
} OthersSave_u;

enum {
    mCD_PRESENT_TYPE_BONUS,
    mCD_PRESENT_TYPE_GIFT,

    mCD_PRESENT_TYPE_NUM
};

#define OTHERS_SIZE ALIGN_NEXT(sizeof(mCD_others_c), mCD_MEMCARD_SECTORSIZE)

extern int mCD_GetThisLandSlotNo_code(int* player_no, s32* slot_card_results);
extern int mCD_GetThisLandSlotNo(void);
extern int mCD_GetSaveHomeSlotNo(void);
extern void mCD_save_data_aram_malloc(void);
extern void mCD_set_aram_save_data();
extern void mCD_init_card();
extern int mCD_InitGameStart_bg(int player_no, int card_private_idx, int start_cond, s32* mounted_chan);
extern int mCD_GetCardPrivateNameCopy(u8* name, int idx);
extern int mCD_CheckCardPlayerNative(int idx);
extern int mCD_CheckPassportFile(void);
extern int mCD_CheckBrokenPassportFile(int slot);
extern int mCD_GetPlayerNum(void);

extern int mCD_CheckStation_bg(s32* chan);
extern int mCD_SaveStation_NextLand_bg(s32* chan);
extern int mCD_SaveStation_Passport_bg(s32* chan);

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint);
extern void mCD_InitAll();
extern void mCD_LoadLand(void);
extern void mCD_toNextLand();

extern int mCD_EraseBrokenLand_bg(int* slot);
extern int mCD_EraseLand_bg(int* slot);
extern int mCD_ErasePassportFile_bg(int slot);
extern int mCD_SaveErasePlayer_bg(int* slot);
extern int mCD_card_format_bg(s32 chan);
extern void mCD_ReCheckLoadLand(GAME_PLAY* play);
extern int mCD_SaveHome_bg(int param_1, int* chan);

extern int mCD_save_data_aram_to_main(void* dst, u32 size, u32 idx);
extern int mCD_save_data_main_to_aram(void* src, u32 size, u32 idx);

#ifdef TARGET_PC
extern int pc_save_loaded;
extern int pc_save_reload(void);

/* These structs are local to m_card.c in the original decomp, but the PC port
   needs them in pc_m_card.c and pc_save_bswap.c for foreigner/travel support. */

typedef struct {
    u16 checksum;
    Private_c priv;
    Animal_c remove_animal;
    u16 copy_protect;
    u8 _2DEA[54];
} mCD_foreigner_c;

typedef union {
    struct {
        char comment[CARD_COMMENT_SIZE];
        u8 banner[0xC00 + 0x200];
        u8 icon[0x400 * 8 + 0x200];
        mCD_foreigner_c file;
    };
    u8 sector_align[mCD_ALIGN_SECTORSIZE(sizeof(MemcardHeader_c) + sizeof(mCD_foreigner_c))];
} ForeignerFile_c;

#endif /* TARGET_PC */

#ifdef __cplusplus
}
#endif

#endif
