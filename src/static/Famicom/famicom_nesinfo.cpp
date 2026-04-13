#include "Famicom/famicomPriv.h"

#ifdef TARGET_PC
extern "C" void pc_fixnes_write_wram(unsigned int ofs, const unsigned char* data, unsigned int size);
#endif

#include "_mem.h"
#include "dolphin/os.h"
#include "libultra/libultra.h"
#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "terminal.h"

/* This is necessary because there are some unused implicitly created
   variables which I don't know how to generate */
static u8 __hack[0x3D];

static u8 highscore_num = 0;
static u8 highscore_updated = 0;
static u8* highscore_flags = nullptr;
static u8 nesinfo_mcrd_cont_no = 0;
static u8 nesinfo_mcrd_game_name[33];
static u8* nesinfo_ptr = nullptr;
u32 nesinfo_tags_size = 0;
u8* nesinfo_tags_start = nullptr;
u8* nesinfo_tags_end = nullptr;
static char* nesinfo_tags_gameName = nullptr;
static char* nesinfo_tags_kanjiName = nullptr;
static u8* nesinfo_tags_moriName = nullptr;
u32 nesinfo_data_size = 0;
u8* nesinfo_data_start = nullptr;
u8* nesinfo_data_end = nullptr;
static u32 nesinfo_rom_size = 0;
static u8* nesinfo_rom_start = nullptr;
static u8* nesinfo_rom_end = nullptr;
static u32 nesinfo_expand_rom_size = 0;
u8 tcs_bad = false;
u8 ics_bad = false;

// clang-format off

enum highscore_state {
    HIGHSCORE_STATE_UNSET,
    HIGHSCORE_STATE_SET,
    HIGHSCORE_STATE_2,
    HIGHSCORE_STATE_UNINITIALIZED
};

enum famicom_games {
    FAMICOM_GAME_CLU_CLU_LAND,
    FAMICOM_GAME_BALLOON_FIGHT,
    FAMICOM_GAME_DONKEY_KONG,
    FAMICOM_GAME_DONKEY_KONG_JR_MATH,
    FAMICOM_GAME_PINBALL,
    FAMICOM_GAME_TENNIS,
    FAMICOM_GAME_GOLF,
    FAMICOM_GAME_PUNCHOUT,
    FAMICOM_GAME_BASEBALL,
    FAMICOM_GAME_CLU_CLU_LAND_D,
    FAMICOM_GAME_DONKEY_KONG_3,
    FAMICOM_GAME_DONKEY_KONG_JR,
    FAMICOM_GAME_EXCITEBIKE,
    FAMICOM_GAME_SOCCER,
    FAMICOM_GAME_WARIOS_WOODS,
    FAMICOM_GAME_ICE_CLIMBER,
    FAMICOM_GAME_MARIO_BROS,
    FAMICOM_GAME_SUPER_MARIO_BROS,
    FAMICOM_GAME_LEGEND_OF_ZELDA,
    FAMICOM_GAME_NUM,

    FAMICOM_GAME_GOMOKU_NARABE = 22,
    FAMICOM_GAME_MAHJONG = 23,

    FAMICOM_GAME_EXTERNAL = 31
};

#define END_TAG()  'E', 'N', 'D', 0
#define GID_TAG(l) 'G', 'I', 'D', (l)
#define GNM_TAG(l) 'G', 'N', 'M', (l)
#define GNO_TAG()  'G', 'N', 'O', sizeof(u8)
#define OFS_TAG()  'O', 'F', 'S', sizeof(u16)
#define HSC_TAG(l) 'H', 'S', 'C', (sizeof(u16) + l)
#define BBR_TAG()  'B', 'B', 'R', 4
#define QDS_TAG()  'Q', 'D', 'S', 5
#define SPE_TAG()  'S', 'P', 'E', 1
#define TCS_TAG()  'T', 'C', 'S', 2
#define ICS_TAG()  'I', 'C', 'S', 2

#define OFS_U16(ofs) (u8)((u32)(ofs) >> 8), (u8)(ofs)
#define OFS_U24(ofs) (u8)((u32)(ofs) >> 16), (u8)((u32)(ofs) >> 8), (u8)(ofs)

static u8 tags_table_default[] = { END_TAG() };

static u8 tags_table_cluclu_land[] = {
    GID_TAG(2), 'C', 'L',
    GNM_TAG(12), 'C', 'L', 'U', ' ', 'C', 'L', 'U', ' ', 'L', 'A', 'N', 'D',
    GNO_TAG(), FAMICOM_GAME_CLU_CLU_LAND,
    OFS_TAG(), OFS_U16(0x0000),
    HSC_TAG(4), OFS_U16(0x8020), 0, 0, 0, 0,
    END_TAG(),
};

static u8 tags_table_balloon_fight[] = {
    GID_TAG(2), 'B', 'F',
    GNM_TAG(13), 'B', 'A', 'L', 'L', 'O', 'O', 'N', ' ', 'F', 'I', 'G', 'H', 'T',
    GNO_TAG(), FAMICOM_GAME_BALLOON_FIGHT,
    OFS_TAG(), OFS_U16(0x0004),
    HSC_TAG(5), OFS_U16(0x0629), 0, 0, 0, 1, 0,
    HSC_TAG(5), OFS_U16(0x062E), 0, 0, 0, 1, 0,
    HSC_TAG(5), OFS_U16(0x0633), 0, 0, 5, 2, 0,
    END_TAG(),
};

static u8 tags_table_donkey_kong[] = {
    GID_TAG(2), 'D', 'K',
    GNM_TAG(11), 'D', 'O', 'N', 'K', 'E', 'Y', ' ', 'K', 'O', 'N', 'G',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG,
    OFS_TAG(), OFS_U16(0x0013),
    HSC_TAG(2), OFS_U16(0x0507), 0, 0,
    HSC_TAG(2), OFS_U16(0x0509), 0, 0,
    END_TAG(),
};

static u8 tags_table_sansu_asobi[] = {
    GID_TAG(2), 'C', 'A',
    GNM_TAG(13), 'D', 'O', 'N', 'K', 'Y', ' ', 'J', 'R', ' ', 'M', 'A', 'T', 'H',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG_JR_MATH,
    OFS_TAG(), OFS_U16(0x0017),
    HSC_TAG(2), OFS_U16(0x04D7), 0, 0,
    HSC_TAG(2), OFS_U16(0x04D9), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DB), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DD), 0, 0,
    HSC_TAG(2), OFS_U16(0x04DF), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E1), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E3), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E5), 0, 0,
    HSC_TAG(2), OFS_U16(0x04E7), 0, 0,
    END_TAG(),
};

static u8 tags_table_pinball[] = {
    GID_TAG(2), 'P', 'N',
    GNM_TAG(7), 'P', 'I', 'N', 'B', 'A', 'L', 'L',
    GNO_TAG(), FAMICOM_GAME_PINBALL,
    OFS_TAG(), OFS_U16(0x0029),
    HSC_TAG(5), OFS_U16(0x010E), 0, 0, 0, 0, 0,
    HSC_TAG(5), OFS_U16(0x0113), 0, 0, 0, 0, 0,
    END_TAG(),
};

static u8 tags_table_tennis[] = {
    GID_TAG(2), 'T', 'E',
    GNM_TAG(6), 'T', 'E', 'N', 'N', 'I', 'S',
    GNO_TAG(), FAMICOM_GAME_TENNIS,
    END_TAG(),
};

static u8 tags_table_golf[] = {
    GID_TAG(2), 'G', 'F',
    GNM_TAG(4), 'G', 'O', 'L', 'F',
    GNO_TAG(), FAMICOM_GAME_GOLF,
    OFS_TAG(), OFS_U16(0x0033),
    HSC_TAG(1), OFS_U16(0x000E), 100,
    END_TAG(),
};

static u8 tags_table_punchout[] = {
    GID_TAG(2), 'P', 'T',
    GNM_TAG(10), 'P', 'U', 'N', 'C', 'H', '-', 'O', 'U', 'T', '!',
    GNO_TAG(), FAMICOM_GAME_PUNCHOUT,
    OFS_TAG(), OFS_U16(0x0034),
    HSC_TAG(10), OFS_U16(0x0110), 39, 39, 39, 39, 39, 39, 39, 39, 39, 39,
    END_TAG(),
};

static u8 tags_table_baseball[] = {
    GID_TAG(2), 'B', 'A',
    GNM_TAG(6), 'B', 'A', 'S', 'E', 'B', 'A', 'L', 'L', // @BUG - should be GNM_TAG(8) ??
    GNO_TAG(), FAMICOM_GAME_BASEBALL,
    END_TAG(),
};

static u8 tags_table_cluclu_land_disk[] = {
    GID_TAG(3), 'C', 'L', 'D',
    GNM_TAG(14), 'C', 'L', 'U', ' ', 'C', 'L', 'U', ' ', 'L', 'A', 'N', 'D', ' ', 'D',
    GNO_TAG(), FAMICOM_GAME_CLU_CLU_LAND_D,
    OFS_TAG(), OFS_U16(0x003E),
    QDS_TAG(), OFS_U24(0x00A170), OFS_U16(0x0050), // save 0x50 bytes starting at 0xA170
    END_TAG(),
};

static u8 tags_table_donkey_kong_3[] = {
    GID_TAG(2), 'D', 'T',
    GNM_TAG(13), 'D', 'O', 'N', 'K', 'E', 'Y', ' ', 'K', 'O', 'N', 'G', ' ', '3',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG_3,
    OFS_TAG(), OFS_U16(0x008E),
    HSC_TAG(2), OFS_U16(0x008C), 0, 0,
    HSC_TAG(2), OFS_U16(0x008E), 0, 0,
    END_TAG(),
};

static u8 tags_table_donkey_kong_jr[] = {
    GID_TAG(2), 'J', 'R',
    GNM_TAG(14), 'D', 'O', 'N', 'K', 'E', 'Y', ' ', 'K', 'O', 'N', 'G', ' ', 'J', 'R',
    GNO_TAG(), FAMICOM_GAME_DONKEY_KONG_JR,
    OFS_TAG(), OFS_U16(0x0092),
    HSC_TAG(2), OFS_U16(0x05D6), 0, 0,
    HSC_TAG(2), OFS_U16(0x05D8), 0, 0,
    END_TAG(),
};

static u8 tags_table_gomoku_narabe[] = {
    GID_TAG(2), 'G', 'O',
    GNM_TAG(13), 'G', 'O', 'M', 'O', 'K', 'U', ' ', 'N', 'A', 'R', 'A', 'B', 'E',
    GNO_TAG(), FAMICOM_GAME_GOMOKU_NARABE,
    END_TAG(),
};

static u8 tags_table_mahjong[] = {
    GID_TAG(2), 'M', 'J',
    GNM_TAG(6), 'M', 'A', 'H', 'J', 'O', 'N', 'G', // @BUG - should be GNM_TAG(7)
    GNO_TAG(), FAMICOM_GAME_MAHJONG,
    END_TAG(),
};

static u8 tags_table_wario_no_mori[] = {
    GID_TAG(2), 'U', 'W',
    GNM_TAG(13), 'W', 'A', 'R', 'I', 'O', '\'', 's', ' ', 'W', 'O', 'O', 'D', 'S',
    GNO_TAG(), FAMICOM_GAME_WARIOS_WOODS,
    
    OFS_TAG(), OFS_U16(0x00D8),
    BBR_TAG(), OFS_U16(0x1B00), OFS_U16(0x0004), //  4 bytes from 0x1B00
    BBR_TAG(), OFS_U16(0x1B10), OFS_U16(0x0034), // 34 bytes from 0x1B10
    BBR_TAG(), OFS_U16(0x1B50), OFS_U16(0x0010), // 16 bytes from 0x1B50
    BBR_TAG(), OFS_U16(0x1B67), OFS_U16(0x0003), //  3 bytes from 0x1B67
    BBR_TAG(), OFS_U16(0x1B70), OFS_U16(0x0002), //  2 bytes from 0x1B70
    BBR_TAG(), OFS_U16(0x1B74), OFS_U16(0x0002), //  2 bytes from 0x1B74
    
    /* Was this data saved at a later date and therefore had to have its offset much further? */
    OFS_TAG(), OFS_U16(0x0655),
    BBR_TAG(), OFS_U16(0x1B6D), OFS_U16(0x0002), //  2 bytes from 0x1B6D
    END_TAG(),
};

static u8 tags_table_ice_climber[] = {
    GID_TAG(2), 'I', 'C',
    GNM_TAG(11), 'I', 'C', 'E', ' ', 'C', 'L', 'I', 'M', 'B', 'E', 'R',
    GNO_TAG(), FAMICOM_GAME_ICE_CLIMBER,
    
    OFS_TAG(), OFS_U16(0x0128),
    HSC_TAG(3), OFS_U16(0x87ED), 0, 0, 0,
    END_TAG(),
};

static u8 tags_table_mario_bros[] = {
    GID_TAG(2), 'M', 'A',
    GNM_TAG(11), 'M', 'A', 'R', 'I', 'O', ' ', 'B', 'R', 'O', 'S', '.',
    GNO_TAG(), FAMICOM_GAME_MARIO_BROS,
    
    OFS_TAG(), OFS_U16(0x012B),
    HSC_TAG(3), OFS_U16(0x0091), 0, 0, 0,
    END_TAG(),
};

static u8 tags_table_super_mario_bros[] = {
    GID_TAG(2), 'S', 'M',
    GNM_TAG(16), 'S', 'U', 'P', 'E', 'R', ' ', 'M', 'A', 'R', 'I', 'O', ' ', 'B', 'R', 'O', 'S',
    GNO_TAG(), FAMICOM_GAME_SUPER_MARIO_BROS,
    
    OFS_TAG(), OFS_U16(0x0131),
    HSC_TAG(6), OFS_U16(0x87D7), 0, 0, 0, 0, 0, 0,
    HSC_TAG(1), OFS_U16(0x07FC), 0,
    HSC_TAG(1), OFS_U16(0x87FD), 0,
    END_TAG(),
};

static u8 tags_table_legend_of_zelda_disk[] = {
    GID_TAG(2), 'Z', 'L',
    GNM_TAG(15), 'L', 'E', 'G', 'E', 'N', 'D', ' ', 'O', 'F', ' ', 'Z', 'E', 'L', 'D', 'A',
    GNO_TAG(), FAMICOM_GAME_LEGEND_OF_ZELDA,
    
    OFS_TAG(), OFS_U16(0x0139),
    QDS_TAG(), OFS_U24(0x01BAFD), OFS_U16(0x051C), // Save 0x51C bytes from 0x1BAFD
    END_TAG(),
};

static u8 tags_table_legend_of_zelda_rom[] = {
    GID_TAG(2), 'Z', 'L',
    GNM_TAG(16), 'L', 'E', 'G', 'E', 'N', 'D', ' ', 'O', 'F', ' ', 'Z', 'E', 'L', 'D', 'A', '1',
    GNO_TAG(), FAMICOM_GAME_LEGEND_OF_ZELDA,
    
    OFS_TAG(), OFS_U16(0x0139),
    BBR_TAG(), OFS_U16(0x0002), OFS_U16(0x051C), // Save 0x51C bytes from BBR+0x0002
    SPE_TAG(), 1,
    END_TAG(),
};

static u8 tags_table_soccer[] = {
    GID_TAG(2), 'S', 'C',
    GNM_TAG(6), 'S', 'O', 'C', 'C', 'E', 'R',
    GNO_TAG(), FAMICOM_GAME_SOCCER,
    END_TAG(),
};

static u8 tags_table_excite_bike[] = {
    GID_TAG(2), 'E', 'B',
    GNM_TAG(10), 'E', 'X', 'C', 'I', 'T', 'E', 'B', 'I', 'K', 'E',
    GNO_TAG(), FAMICOM_GAME_EXCITEBIKE,
    OFS_TAG(), OFS_U16(0x0096),
    HSC_TAG(3), OFS_U16(0x8580), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x8583), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x8586), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x8589), 1, 12, 0,
    HSC_TAG(3), OFS_U16(0x858C), 1, 6, 0,
    HSC_TAG(3), OFS_U16(0x8590), 1, 24, 0,
    HSC_TAG(3), OFS_U16(0x8593), 1, 22, 0,
    HSC_TAG(3), OFS_U16(0x8596), 1, 10, 0,
    HSC_TAG(3), OFS_U16(0x8599), 1, 20, 0,
    HSC_TAG(3), OFS_U16(0x859C), 1, 6, 0,
    HSC_TAG(3), OFS_U16(0x85A0), 10, 0, 0,
    HSC_TAG(3), OFS_U16(0x85A3), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x85A6), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x85A9), 1, 16, 0,
    HSC_TAG(3), OFS_U16(0x85AC), 1, 12, 0,
    HSC_TAG(3), OFS_U16(0x85AF), 1, 6, 0,
    HSC_TAG(3), OFS_U16(0x85B3), 1, 24, 0,
    HSC_TAG(3), OFS_U16(0x85B6), 1, 22, 0,
    HSC_TAG(3), OFS_U16(0x85B9), 1, 10, 0,
    HSC_TAG(3), OFS_U16(0x85BC), 1, 20, 0,
    HSC_TAG(3), OFS_U16(0x85BF), 1, 6, 0,
    HSC_TAG(3), OFS_U16(0x85C3), 10, 0, 0,
    END_TAG(),
};

static u8 tags_table_excite_bike_design[] = {
    GID_TAG(2), 'E', 'B',
    GNM_TAG(10), 'E', 'X', 'C', 'I', 'T', 'E', 'B', 'I', 'K', 'E',
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    OFS_TAG(), OFS_U16(0x0000),
    HSC_TAG(3), OFS_U16(0x8580), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x8583), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x8586), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x8589), 1, 12, 0, 
    HSC_TAG(3), OFS_U16(0x858C), 1, 6, 0, 
    HSC_TAG(3), OFS_U16(0x8590), 1, 24, 0, 
    HSC_TAG(3), OFS_U16(0x8593), 1, 22, 0, 
    HSC_TAG(3), OFS_U16(0x8596), 1, 10, 0, 
    HSC_TAG(3), OFS_U16(0x8599), 1, 20, 0, 
    HSC_TAG(3), OFS_U16(0x859C), 1, 6, 0, 
    HSC_TAG(3), OFS_U16(0x85A0), 10, 0, 0, 
    HSC_TAG(3), OFS_U16(0x85A3), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x85A6), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x85A9), 1, 16, 0, 
    HSC_TAG(3), OFS_U16(0x85AC), 1, 12, 0, 
    HSC_TAG(3), OFS_U16(0x85AF), 1, 6, 0, 
    HSC_TAG(3), OFS_U16(0x85B3), 1, 24, 0, 
    HSC_TAG(3), OFS_U16(0x85B6), 1, 22, 0, 
    HSC_TAG(3), OFS_U16(0x85B9), 1, 10, 0, 
    HSC_TAG(3), OFS_U16(0x85BC), 1, 20, 0, 
    HSC_TAG(3), OFS_U16(0x85BF), 1, 6, 0, 
    HSC_TAG(3), OFS_U16(0x85C3), 10, 0, 0, 
    HSC_TAG(240), OFS_U16(0x86E0), 1, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    END_TAG(),
};

static u8 tags_table_nazo_no_murasamejo[] = {
    GID_TAG(3), 'N', 'M', 'J', 
    GNM_TAG(16), 'N', 'A', 'Z', 'O', 'N', 'O', 'M', 'U', 'R', 'A', 'S', 'A', 'M', 'E', 'J', 'O', 
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    OFS_TAG(), OFS_U16(0x0000),
    QDS_TAG(), OFS_U24(0x009AC7), OFS_U16(0x003E),
    END_TAG(),
};

static u8 tags_table_super_mario_bros_2[] = {
    TCS_TAG(), OFS_U16(0x0000),
    ICS_TAG(), OFS_U16(0x0000),
    GID_TAG(4), 'S', 'M', 'B', '2', 
    GNM_TAG(18), 'S', 'U', 'P', 'E', 'R', ' ', 'M', 'A', 'R', 'I', 'O', ' ', 'B', 'R', 'O', 'S', ' ', '2', 
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    OFS_TAG(), OFS_U16(0x0000),
    QDS_TAG(), OFS_U24(0x01CC4E), OFS_U16(0x0001),
    HSC_TAG(6), OFS_U16(0x87D7), 0, 0, 0, 0, 0, 0, 
    END_TAG(),
};

static u8 tags_table_marioopen_golf[] = {
    TCS_TAG(), OFS_U16(0x0000),
    ICS_TAG(), OFS_U16(0x0000),
    GID_TAG(2), 'U', 'G', 
    GNM_TAG(14), 'M', 'A', 'R', 'I', 'O', 'O', 'P', 'E', 'N', ' ', 'G', 'O', 'L', 'F', 
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    OFS_TAG(), OFS_U16(0x0000),
    BBR_TAG(), OFS_U16(0x0001), OFS_U16(0x0E0C),
    END_TAG(),
};

static u8 tags_table_external_default[] = {
    TCS_TAG(), OFS_U16(0x0000),
    ICS_TAG(), OFS_U16(0x0000),
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    END_TAG(),
};

static u8 tags_table_balloon_fight_jpn[] = {
    TCS_TAG(), OFS_U16(0x0000),
    ICS_TAG(), OFS_U16(0x0000),
    GID_TAG(2), 'B', 'F', 
    GNM_TAG(13), 'B', 'A', 'L', 'L', 'O', 'O', 'N', ' ', 'F', 'I', 'G', 'H', 'T', 
    GNO_TAG(), FAMICOM_GAME_EXTERNAL,
    OFS_TAG(), OFS_U16(0x0000),
    HSC_TAG(5), OFS_U16(0x8629), 0, 0, 0, 1, 0, 
    HSC_TAG(5), OFS_U16(0x862E), 0, 0, 0, 1, 0, 
    HSC_TAG(5), OFS_U16(0x8633), 0, 0, 5, 2, 0, 
    END_TAG(),
};

typedef struct nesinfo_tag_s {
    u8* tags_table;
    size_t tags_size;
    char* gameName;
    char* kanjiName;
} nesinfo_tag_info;

static const nesinfo_tag_info tags_table_table[FAMICOM_INTERNAL_ROM_NUM] = {
    { tags_table_cluclu_land, sizeof(tags_table_cluclu_land), "Clu Clu Land", "Clu Clu Land" },
    { tags_table_balloon_fight, sizeof(tags_table_balloon_fight), "Balloon Fight", "Balloon Fight" },
    { tags_table_donkey_kong, sizeof(tags_table_donkey_kong), "Donkey Kong", "Donkey Kong" },
    { tags_table_sansu_asobi, sizeof(tags_table_sansu_asobi), "Donkey Jr Math", "Donkey Jr Math" },
    { tags_table_pinball, sizeof(tags_table_pinball), "Pinball", "Pinball" },
    { tags_table_tennis, sizeof(tags_table_tennis), "Tennis", "Tennis" },
    { tags_table_golf, sizeof(tags_table_golf), "Golf", "Golf" },
    { tags_table_punchout, sizeof(tags_table_punchout), "Punch Out", "Punch Out" },
    { tags_table_baseball, sizeof(tags_table_baseball), "Base Ball", "Base Ball" },
    { tags_table_cluclu_land_disk, sizeof(tags_table_cluclu_land_disk), "New Clu Clu Land", "New Clu Clu Land" },
    { tags_table_donkey_kong_3, sizeof(tags_table_donkey_kong_3), "Donkey Kong 3", "Donkey Kong 3" },
    { tags_table_donkey_kong_jr, sizeof(tags_table_donkey_kong_jr), "Donkey Kong Jr", "Donkey Kong Jr" },
    { tags_table_soccer, sizeof(tags_table_soccer), "Soccer", "Soccer" },
    { tags_table_excite_bike, sizeof(tags_table_excite_bike), "Excitebike", "Excitebike" },
    { tags_table_wario_no_mori, sizeof(tags_table_wario_no_mori), "Wario's Woods", "Wario's Woods" },
    { tags_table_ice_climber, sizeof(tags_table_ice_climber), "Ice Climber", "Ice Climber" },
    { tags_table_mario_bros, sizeof(tags_table_mario_bros), "Mario Bros", "Mario Bros" },
    { tags_table_super_mario_bros, sizeof(tags_table_super_mario_bros), "Super Mario Bros", "Super Mario Bros" },
    { tags_table_legend_of_zelda_rom, sizeof(tags_table_legend_of_zelda_rom), "Legend of Zelda", "Legend of Zelda" },
};

static u8 moriNameTable[FAMICOM_INTERNAL_ROM_NUM][16] = {
    { 'C', 'l', 'u', ' ', 'C', 'l', 'u', ' ', 'L', 'a', 'n', 'd', ' ', ' ', ' ', ' ',  },
    { 'B', 'a', 'l', 'l', 'o', 'o', 'n', ' ', 'F', 'i', 'g', 'h', 't', ' ', ' ', ' ',  },
    { 'D', 'o', 'n', 'k', 'e', 'y', ' ', 'K', 'o', 'n', 'g', ' ', ' ', ' ', ' ', ' ',  },
    { 'D', 'o', 'n', 'k', 'e', 'y', ' ', 'J', 'r', ' ', 'M', 'a', 't', 'h', ' ', ' ',  },
    { 'P', 'i', 'n', 'b', 'a', 'l', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'T', 'e', 'n', 'n', 'i', 's', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'G', 'o', 'l', 'f', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'P', 'u', 'n', 'c', 'h', ' ', 'O', 'u', 't', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'B', 'a', 's', 'e', ' ', 'B', 'a', 'l', 'l', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'N', 'e', 'w', ' ', 'C', 'l', 'u', ' ', 'C', 'l', 'u', ' ', 'L', 'a', 'n', 'd',  },
    { 'D', 'o', 'n', 'k', 'e', 'y', ' ', 'K', 'o', 'n', 'g', ' ', '3', ' ', ' ', ' ',  },
    { 'D', 'o', 'n', 'k', 'e', 'y', ' ', 'K', 'o', 'n', 'g', ' ', 'J', 'r', ' ', ' ',  },
    { 'S', 'o', 'c', 'c', 'e', 'r', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'E', 'x', 'c', 'i', 't', 'e', 'b', 'i', 'k', 'e', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'W', 'a', 'r', 'i', 'o', '\'', 's', ' ', 'W', 'o', 'o', 'd', 's', ' ', ' ', ' ',  },
    { 'I', 'c', 'e', ' ', 'C', 'l', 'i', 'm', 'b', 'e', 'r', ' ', ' ', ' ', ' ', ' ',  },
    { 'M', 'a', 'r', 'i', 'o', ' ', 'B', 'r', 'o', 's', ' ', ' ', ' ', ' ', ' ', ' ',  },
    { 'S', 'u', 'p', 'e', 'r', ' ', 'M', 'a', 'r', 'i', 'o', ' ', 'B', 'r', 'o', 's',  },
    { 'L', 'e', 'g', 'e', 'n', 'd', ' ', 'o', 'f', ' ', 'Z', 'e', 'l', 'd', 'a', ' ',  },
};

// clang-format on

static void update_highscore_raw(unsigned int ofs, unsigned int size, u8* initial_value, u8* high_score, u8* state) {
    u8* current_score_p = &famicomCommon.sp->wram[ofs];

    if (*state == HIGHSCORE_STATE_UNINITIALIZED) {
        memcpy(high_score, initial_value, size);
        *state = HIGHSCORE_STATE_UNSET; // default highscore
        // High score data was not found, so it has been initialized.
        OSReport("ハイスコアデータがないので初期化しました\n");
    }

    if (*state == HIGHSCORE_STATE_UNSET) {
        if (memcmp(current_score_p, initial_value, size) == 0) {
            // The high score in WRAM has been reset to its default value.
            OSReport("WRAMのハイスコアが初期値になりました\n");
            memcpy(current_score_p, high_score, size);
#ifdef TARGET_PC
            /* Also write to fixNES Main_Mem so the NES game displays saved
             * scores. The sp->wram write above keeps the mirror consistent
             * so the next forward sync (Main_Mem→sp->wram) won't clobber. */
            pc_fixnes_write_wram(ofs, high_score, size);
#endif
            *state = HIGHSCORE_STATE_SET;
        } else {
            // The high score in WRAM has not been reset to its default value. Offset=%04x\n
            OSReport("WRAMのハイスコアが初期値になっていません オフセット=%04x\n", ofs);
        }
    } else {
        if (memcmp(current_score_p, high_score, size) != 0) {
            // The high score in WRAM has been updated.
            OSReport("WRAMのハイスコアが更新されました\n");
            memcpy(high_score, current_score_p, size);
            highscore_updated = true;
        }
    }
}

static u16 nesinfo_get_u16(u8* data) {
    return (u16)(((u32)data[0] << 8) + (u32)data[1]);
}

static u8 nesinfo_get_u8(u8* data) {
    return (u8)(u32)data[0];
}

static void nesinfo_set_u16(u8* data, u16 value) {
    data[0] = (u8)(((u32)value >> 8) & 0xFF);
    data[1] = (u8)((u32)value & 0xFF);
}

static u8* nesinfo_next_tag_raw(u8* data) {
    if (data == nullptr || (nesinfo_tags_end != nullptr && data >= nesinfo_tags_end) ||
        memcmp(data, NESTAG_END, NESTAG_CMD_SIZE) == 0) {
        return nullptr;
    } else {
        return data + data[NESTAG_CMD_SIZE] + NESTAG_SIZE;
    }
}

static u8* nesinfo_next_tag(u8* data) {
    do {
        data = nesinfo_next_tag_raw(data);
        if (data == nullptr) {
            break;
        }

        if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
            if (data[4] != 1) {
                data = nesinfo_next_tag_raw(data);
            }
        } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
            if (data[4] == 1) {
                data = nesinfo_next_tag_raw(data);
            }
        } else {
            break; // found a tag to return
        }
    } while (data != nullptr);

    return data;
}

static u16 calc_check_sum2(void* data, size_t size) {
    if (((u32)data & 1) == 0) {
        u16 sum;
        size_t i;
        u16* data2;

        data2 = (u16*)data;
        sum = 0;
        for (i = 0; i < size; i += 2) {
            sum += *data2++;
        }

        return sum;
    } else {
        u16 sum0;
        u16 sum1;
        size_t i;
        u8* data_u8;

        data_u8 = (u8*)data;
        sum0 = 0;
        sum1 = 0;
        for (i = 0; i < size - 1; i += sizeof(u16)) {
            sum0 += data_u8[0];
            sum1 += data_u8[1];
            data_u8 += sizeof(u16);
        }

        if (i < size) {
            sum0 += data_u8[0];
            data_u8 += sizeof(u8);
        }

        return (u16)((sum0 << 8) + sum1);
    }
}

static void print_stringn_lf(u8* data, size_t size) {
    while (size-- > 0) {
        OSReport("%c", *data++);
    }

    OSReport("\n");
}

static void print_hex_lf(u8* data, size_t size) {
    while (size-- > 0) {
        OSReport(" %02x", *data++);
    }

    OSReport("\n");
}

extern void nesinfo_tags_set(int rom_no) {
    nesinfo_tags_start = nullptr;
    nesinfo_tags_end = nullptr;
    nesinfo_tags_size = 0;
    nesinfo_tags_gameName = nullptr;
    nesinfo_tags_kanjiName = nullptr;
    nesinfo_tags_moriName = nullptr;

    if (rom_no < 0) {
        return;
    }

    if (rom_no < 0) {
        return;
    }

    u32 rom = rom_no;
    if (rom >= FAMICOM_INTERNAL_ROM_NUM) {
        return;
    }

    nesinfo_tags_start = tags_table_table[rom].tags_table;
    nesinfo_tags_end = nesinfo_tags_start + tags_table_table[rom].tags_size;
    nesinfo_tags_size = (u32)(nesinfo_tags_end - nesinfo_tags_start);
    nesinfo_tags_gameName = tags_table_table[rom].gameName;
    nesinfo_tags_kanjiName = tags_table_table[rom].kanjiName;

    if (rom < FAMICOM_INTERNAL_ROM_NUM) {
        nesinfo_tags_moriName = moriNameTable[rom];
    }
}

static int calcSum(u8* data, size_t len) {
    int checksum = 0;
    size_t i;

    for (i = 0; i != len; i++) {
        checksum += *data++;
    }

    return checksum;
}

static void special_zelda() {
    u8* bbram_p = famicomCommon.bbramp;
    int i;

    bbram_p[0] = 0x00;                // First byte in bbram is not used
    bbram_p[1] = 0x5A;                // Second byte must be 'Z' (0x5A)
    memset(&bbram_p[0x52A], 0xFF, 3); // Reset 'IsSaveFileBCommitted'
    bzero(&bbram_p[0x52D], 3);        // Unused 3 bytes after save file?
    memset(&bbram_p[0x51E], 0x5A, 3); // Reset save file open markers
    memset(&bbram_p[0x521], 0xA5, 3); // Reset save file close markers

    for (i = 0; i < 3; i++) {
        /* Sum previous checksums plus death counter, quest number, and whatever 0x518 is */
        u32 checksum = 0;
        u16 chksum16;
        u8 chksumUpper;
        u8 embeddedChksumUpper;
        u8 embeddedChksumLower;

        checksum += (u16)calcSum(bbram_p + 2 + i * 8, 8); /* Checksum of name */
        checksum += (u16)calcSum(bbram_p + 0x1A + i * 0x28, 0x28);   /* Checksum of items */
        checksum += (u16)calcSum(bbram_p + 0x92 + i * 0x180, 0x180); /* Checksum of world flags */
        checksum += (u16)calcSum(bbram_p + 0x512 + i, 1);            /* Checksum of 'SlotActive' */

        checksum += bbram_p[0x515 + i];
        checksum += bbram_p[0x518 + i];
        checksum += bbram_p[0x51B + i];

        chksum16 = (u16)checksum;
        /* Compare against embedded file checksums */
        chksumUpper = checksum >> 8;
        if ((embeddedChksumUpper = bbram_p[0x524 + i * 2], embeddedChksumUpper == chksumUpper) &&
            (embeddedChksumLower = bbram_p[0x525 + i * 2], embeddedChksumLower == (u8)checksum)) {
            OSReport("チェックサムＯＫ %d %04x\n", i, chksum16); // Checksum OK %d %04x\n
        } else {
            OSReport("チェックサムＮＧ %d %04x %02x%02x\n", i, chksum16, bbram_p[0x524 + i * 2],
                     bbram_p[0x525 + i * 2]); // Checksum NG %d %04x %02x%02x\n
            bbram_p[0x524 + i * 2] = chksumUpper;
            bbram_p[0x525 + i * 2] = checksum;
        }
    }
}

extern void nesinfo_tag_process1(u8* save_data, int mode, u32* max_ofs_p) {
    u8* data = nesinfo_tags_start;
    int first_play = FALSE;
    int cur_ofs = 0;
    int max_ofs = 0;

    if (mode == 0) {
        highscore_num = 0;
    }

    OSReport("nesinfo_tag_process1 開始 mode = %d\n", mode); // nesinfo_tag_process1 start mode = %d\n
    while (TRUE) {
        OSReport("タグ＝%.3s 長さ＝%d\n", data, data[NESTAG_CMD_SIZE]); // Tag=%.3s Length=%d\n
        data = nesinfo_next_tag(data);

        if (data == nullptr) {
            break;
        }

        if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
            if (data[4] != 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
            if (data[4] == 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_GID, NESTAG_CMD_SIZE) == 0) {
            print_stringn_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_GNM, NESTAG_CMD_SIZE) == 0) {
            print_stringn_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_CPN, NESTAG_CMD_SIZE) == 0) {
            memcpy(nesinfo_mcrd_game_name, &data[4], 16);
        } else if (memcmp(data, NESTAG_OFS, NESTAG_CMD_SIZE) == 0) {
            cur_ofs = nesinfo_get_u16(&data[4]);
        } else if (memcmp(data, NESTAG_HSC, NESTAG_CMD_SIZE) == 0) {
            size_t highscore_size = data[NESTAG_CMD_SIZE] - 2;

            OSReport("ハイスコア: オフセット＝%04x 初期値＝",
                     nesinfo_get_u16(&data[4])); // High Score: Offset=%04x Default Value=

            if (save_data != nullptr && mode == 1 && first_play) {
                u16 ofs = nesinfo_get_u16(&data[4]); // unnecessary?

                memcpy(save_data + 8 + cur_ofs, &data[6], highscore_size);
                OSReport("初プレイでハイスコアデータがないので初期化しました\n"); // Since it's the first play and
                                                                                  // there's no high score data, it has
                                                                                  // been initialized.\n
            }

            cur_ofs += highscore_size;
            if (mode == 0) {
                highscore_num++;
            }

            print_hex_lf(&data[6], data[NESTAG_CMD_SIZE] - 2);
        } else if (memcmp(data, NESTAG_GNO, NESTAG_CMD_SIZE) == 0) {
            u32 bit = 1 << nesinfo_get_u8(&data[4]);

            /* TODO: is save_data actually a struct? It has dynamic sized members in it. */
            if (save_data != 0 && mode == 1 && ((*(u32*)&save_data[4]) & bit) == 0) {
                (*(u32*)&save_data[4]) |= bit; // set first play bit
                first_play = TRUE;
            }

            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_BBR, NESTAG_CMD_SIZE) == 0) {
            u16 bbram_ofs = nesinfo_get_u16(&data[4]);
            u16 size = nesinfo_get_u16(&data[6]);

            if (save_data != nullptr && mode == 1) {
                if (first_play) {
                    OSReport("初プレイなので。クリアします\n"); // Since it's the first play, it will be cleared.\n
                    bzero(famicomCommon.bbramp + bbram_ofs, size);
                } else {
                    OSReport("バッテリーバックアップのロード\n"); // Loading battery backup.\n
                    memcpy(famicomCommon.bbramp + bbram_ofs, save_data + 8 + cur_ofs, size);
                }
            }

            cur_ofs += size;
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_QDS, NESTAG_CMD_SIZE) == 0) {
            u8 ofs_16_24 = nesinfo_get_u8(&data[4]);
            u16 ofs_00_16 = nesinfo_get_u16(&data[5]);
            u16 size = nesinfo_get_u16(&data[7]);

            if (save_data != nullptr && mode == 1) {
                if (first_play) {
                    OSReport("初プレイなのでディスクセーブエリアを保持します\n"); // Since it's the first play, the disk
                                                                                  // save area will be retained.\n
                } else {
                    OSReport("ディスクセーブエリアをロード\n"); // Loading the disk save area.\n
                    memcpy(famicomCommon.nesromp + (ofs_16_24 << 16) + ofs_00_16, save_data + 8 + cur_ofs, size);
                }
            }

            cur_ofs += size;
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_SPE, NESTAG_CMD_SIZE) == 0) {
            if (mode == 1) {
                OSReport("特別プログラム発動!\n"); // Special program activated!\n

                if (data[4] == 1 && first_play == FALSE) {
                    special_zelda(); // fixup zelda checksums
                }
            }

            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_ISZ, NESTAG_CMD_SIZE) == 0) {
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_IFM, NESTAG_CMD_SIZE) == 0) {
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_REM, NESTAG_CMD_SIZE) == 0) {
            print_stringn_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_END, NESTAG_CMD_SIZE) == 0) {
            break;
        } else if (memcmp(data, NESTAG_TCS, NESTAG_CMD_SIZE) == 0) {
            if (mode == 0 || mode == -1) {
                u16 checksum = calc_check_sum2(nesinfo_tags_start, nesinfo_tags_size);

                if (mode == -1) {
                    u16 chk = nesinfo_get_u16(&data[4]);
                    nesinfo_set_u16(&data[4], chk - checksum); // update tags checksum
                } else {
                    if (checksum != 0) {
                        OSReport(VT_COL(YELLOW, BLACK) "BAD %04x\n" VT_RST, checksum);
                        tcs_bad = true;
                        break;
                    } else {
                        OSReport("OK\n");
                    }
                }
            }
        } else if (memcmp(data, NESTAG_ICS, NESTAG_CMD_SIZE) == 0) {
            if (mode == 0 || mode == -1) {
                u16 checksum = calc_check_sum2(nesinfo_data_start, nesinfo_data_size);

                if (mode == -1) {
                    nesinfo_set_u16(&data[4], checksum); // update image checksum
                } else {
                    u16 chk = nesinfo_get_u16(&data[4]);

                    if (checksum != chk) {
                        ics_bad = true;
                        OSReport(VT_COL(YELLOW, BLACK) "BAD %04x %04x\n" VT_RST, checksum, chk);
                    } else {
                        OSReport("OK\n");
                    }
                }
            }
        } else if (memcmp(data, NESTAG_ESZ, NESTAG_CMD_SIZE) == 0) {
            nesinfo_expand_rom_size = nesinfo_get_u16(&data[4]) << 4;
        } else if (memcmp(data, NESTAG_FIL, NESTAG_CMD_SIZE) == 0) {
            // stubbed
        } else if (memcmp(data, NESTAG_ROM, NESTAG_CMD_SIZE) == 0) {
            u32 rom_id = data[4];
            u8* rom_p = famicomCommon.nesromp;

            OSReport("ロムデータ参照: %d\n", rom_id); // Referencing ROM data: %d\n
            if (nesrom_filename_ptrs != nullptr && rom_p != nullptr) {
                nesinfo_data_size = JKRFileLoader::readGlbResource(rom_p, 0x100000, (char*)nesrom_filename_ptrs[rom_id],
                                                                   EXPAND_SWITCH_DECOMPRESS);
                nesinfo_data_start = rom_p;
                nesinfo_data_end = rom_p + nesinfo_data_size;
            }
        }

        if (max_ofs < cur_ofs) {
            max_ofs = cur_ofs;
        }
    }

    OSReport("nesinfo_tag_process1 終了\n"); // nesinfo_tag_process1 finished\n
    if (max_ofs_p != nullptr) {
        *max_ofs_p = max_ofs;
    }
}

extern void nesinfo_tag_process2() {
    u8* data = nesinfo_tags_start;

    OSReport("nesinfo_tag_process2 開始\n"); // nesinfo_tag_process2 start\n

    while (TRUE) {
        data = nesinfo_next_tag(data);
        if (data == nullptr) {
            break;
        }

        OSReport("タグ＝%.3s 長さ＝%d\n", data, data[NESTAG_CMD_SIZE]); // Tag=%.3s Length=%d\n

        if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
            if (data[4] != 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
            if (data[4] == 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_MOV, NESTAG_CMD_SIZE) == 0) {
            u32 src = nesinfo_get_u16(&data[4]) << 4;
            u32 dst = nesinfo_get_u16(&data[6]) << 4;
            size_t size = nesinfo_get_u16(&data[8]) << 4;

            if (nesinfo_rom_start != nullptr) {
                memcpy(&nesinfo_rom_start[dst], &nesinfo_rom_start[src], size);
            }
        } else if (memcmp(data, NESTAG_NHD, NESTAG_CMD_SIZE) == 0) {
            if (nesinfo_rom_start != nullptr) {
                memcpy(nesinfo_rom_start, &data[4], data[NESTAG_CMD_SIZE]); // copy new header
            }
        } else if (memcmp(data, NESTAG_DIF, NESTAG_CMD_SIZE) == 0) {
            u8* rom_p = nesinfo_rom_start;
            if (rom_p != nullptr) {
                int i;
                size_t size = nesinfo_rom_start[4] * 0x4000 + nesinfo_rom_start[5] * 0x2000 + 16;
                u8* rom_end_p = nesinfo_rom_start + size;
                u8* dif_p = nesinfo_data_start;

                while (rom_p < rom_end_p) {
                    rom_p += *dif_p++;
                    if (rom_p >= rom_end_p) {
                        break;
                    }

                    for (i = *dif_p++; i > 0; i--) {
                        *rom_p++ = *dif_p++;
                    }

                    if (rom_p >= rom_end_p) {
                        break;
                    }
                }
            }
        } else if (memcmp(data, NESTAG_PAT, NESTAG_CMD_SIZE) == 0) {
            int patch_type;
            u8* next_tag_p;
            u8* dst_p;
            size_t patch_size;
            u8* patch_data_p;
            u32 patch_ofs;

            next_tag_p = nesinfo_next_tag(data);
            patch_data_p = &data[4];

            while (patch_data_p < next_tag_p) {
                patch_type = patch_data_p[0];
                patch_size = patch_data_p[1];
                patch_ofs = nesinfo_get_u16(&patch_data_p[2]);

                patch_data_p += 4;

                switch (patch_type) {
                    case 2: {
                        dst_p = &nesinfo_rom_start[patch_ofs];
                        break;
                    }

                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        break;

                    case 9: {
                        dst_p = &nesinfo_rom_start[patch_ofs << 4];
                        break;
                    }

                    case 3:
                    default: {
                        /* This gives us an effective patch application range of [0x80000000, 0x807FFFFF] */
                        if (patch_type >= 0x80 && patch_type <= 0xFF) {
                            dst_p = (u8*)((0x8000 + (patch_type - 0x80)) << 16) + patch_ofs;
                        } else {
                            dst_p = nullptr;
                        }

                        break;
                    }
                }

                if (dst_p != nullptr) {
                    while (patch_size-- > 0) {
                        *dst_p++ = *patch_data_p++;
                    }
                } else {
                    patch_data_p += patch_size;
                }
            }
        }
    }

    OSReport("nesinfo_tag_process2 終了\n"); // nesinfo_tag_process2 finished\n
}

extern void nesinfo_tag_process3(u8* save_data) {
    u8* data = nesinfo_tags_start;
    u32 cur_ofs = 0;

    OSReport("nesinfo_tag_process3 開始\n"); // nesinfo_tag_process3 start\n
    while (TRUE) {
        data = nesinfo_next_tag(data);
        if (data == nullptr) {
            break;
        }

        OSReport("タグ＝%.3s 長さ＝%d\n", data, data[NESTAG_CMD_SIZE]); // Tag=%.3s Length=%d\n
        if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
            if (data[4] != 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
            if (data[4] == 1) {
                data = nesinfo_next_tag(data);
            }
        } else if (memcmp(data, NESTAG_OFS, NESTAG_CMD_SIZE) == 0) {
            cur_ofs = nesinfo_get_u16(&data[4]);
        } else if (memcmp(data, NESTAG_HSC, NESTAG_CMD_SIZE) == 0) {
            cur_ofs = data[NESTAG_CMD_SIZE] + cur_ofs;
            cur_ofs -= 2;
            print_hex_lf(&data[6], data[NESTAG_CMD_SIZE] - 2);
        } else if (memcmp(data, NESTAG_BBR, NESTAG_CMD_SIZE) == 0) {
            u16 bbram_ofs = nesinfo_get_u16(&data[4]);
            u16 size = nesinfo_get_u16(&data[6]);

            if (save_data != nullptr) {
                OSReport("バッテリーバックアップの保存\n"); // Saving battery backup.\n
                memcpy(save_data + 8 + cur_ofs, famicomCommon.bbramp + bbram_ofs, size);
            }

            cur_ofs += size;
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_QDS, NESTAG_CMD_SIZE) == 0) {
            u8 ofs_16_24 = nesinfo_get_u8(&data[4]);
            u16 ofs_00_16 = nesinfo_get_u16(&data[5]);
            u16 size = nesinfo_get_u16(&data[7]);

            if (save_data != nullptr) {
                OSReport("ディスクセーブの保存\n"); // Saving the disk save.\n
                memcpy(save_data + 8 + cur_ofs, famicomCommon.nesromp + (ofs_16_24 << 16) + ofs_00_16, size);
            }

            cur_ofs += size;
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_SPE, NESTAG_CMD_SIZE) == 0) {
            OSReport("特別プログラム発動?\n"); // Special program activated?\n
            print_hex_lf(&data[4], data[NESTAG_CMD_SIZE]);
        } else if (memcmp(data, NESTAG_END, NESTAG_CMD_SIZE) == 0) {
            break;
        }
    }

    OSReport("nesinfo_tag_process2 終了\n"); // nesinfo_tag_process2 finished\n
}

extern void nesinfo_update_highscore(u8* save_data, int mode) {
    if (save_data != nullptr) {
        u8* flags;
        u8* data;
        u32 cur_ofs;

        cur_ofs = 0;
        flags = highscore_flags;
        data = nesinfo_tags_start;

        while (TRUE) {
            data = nesinfo_next_tag(data);
            if (data == nullptr) {
                break;
            }

            if (memcmp(data, NESTAG_VEQ, NESTAG_CMD_SIZE) == 0) {
                if (data[4] != 1) {
                    data = nesinfo_next_tag(data);
                }
            } else if (memcmp(data, NESTAG_VNE, NESTAG_CMD_SIZE) == 0) {
                if (data[4] == 1) {
                    data = nesinfo_next_tag(data);
                }
            } else if (memcmp(data, NESTAG_OFS, NESTAG_CMD_SIZE) == 0) {
                cur_ofs = nesinfo_get_u16(&data[4]);
            } else if (memcmp(data, NESTAG_HSC, NESTAG_CMD_SIZE) == 0) {
                size_t highscore_size = data[NESTAG_CMD_SIZE] - 2;
                u16 ofs_data = nesinfo_get_u16(&data[4]);
                u32 ofs = ofs_data & 0x7FF;
                u32 bit = (ofs_data >> 15) & 1;
                u8* dst_p = &data[6];

                if (save_data != nullptr) {
                    if (mode != 0) {
                        if (*flags == 1 && bit == 0) {
                            *flags = 0;
                        }
                    } else {
                        update_highscore_raw(ofs, highscore_size, dst_p, save_data + 8 + cur_ofs, flags);
                    }
                }

                cur_ofs += highscore_size;
                flags++;
            } else if (memcmp(data, NESTAG_BBR, NESTAG_CMD_SIZE) == 0) {
                u16 bbram_ofs = nesinfo_get_u16(&data[4]);
                u16 size = nesinfo_get_u16(&data[6]);

                cur_ofs += size;
            } else if (memcmp(data, NESTAG_QDS, NESTAG_CMD_SIZE) == 0) {
                u8 ofs_16_24 = nesinfo_get_u8(&data[4]);
                u16 ofs_00_16 = nesinfo_get_u16(&data[5]);
                u16 size = nesinfo_get_u16(&data[7]);

                cur_ofs += size;
            } else if (memcmp(data, NESTAG_END, NESTAG_CMD_SIZE) == 0) {
                break;
            }
        }
    }
}

extern int nesinfo_get_highscore_num() {
    return highscore_num;
}

extern u8* nesinfo_get_moriName() {
    return nesinfo_tags_moriName;
}

extern void nesinfo_init() {
    nesinfo_ptr = nullptr;
    nesinfo_tags_size = 0;
    nesinfo_tags_start = nullptr;
    nesinfo_tags_end = nullptr;
    nesinfo_data_size = 0;
    nesinfo_data_start = nullptr;
    nesinfo_data_end = nullptr;
    nesinfo_rom_size = 0;
    nesinfo_rom_start = nullptr;
    nesinfo_rom_end = nullptr;
}

/* @unused highscore_mcrd_readwrite__Fi */

extern void highscore_setup_flags(u8* flags) {
    highscore_flags = flags;
    bzero(flags, highscore_num);
}

/* @unused bbram_mcrd_readwrite__Fii */

/* @unused, necessary for matching .data*/
static void bbram_load() {
    // There is no BB RAM data on Memory Card %d\n
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dにはＢＢラムデータはない\n" VT_RST);

    // There is also no BB RAM data on Memory Card %d\n
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dにもＢＢラムデータはない\n" VT_RST);
}

/* @unused */
static void bbram_save() {
    // It seems that BBRAM is not being used.
    OSReport("BBRAMは使ってないようです\n");

    // Cannot save BB RAM data on Memory Card %d
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dにはＢＢラムデータをセーブできない\n" VT_RST);

    // Cannot save BB RAM data on Memory Card %d either
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dにもＢＢラムデータをセーブできない\n" VT_RST);
}

/* @unused state_mcrd_readwrite_Fii */

/* @unused */
static void state_mcrd_load() {
    // There is no state data on Memory Card %d
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dには状態データはない\n" VT_RST);

    // State data from Memory Card %d has been loaded
    OSReport(VT_FGCOL(YELLOW) "メモリーカード%dの状態データをロードしました\n" VT_RST);
}

/* @unused */
static void state_mcrd_save() {
    // Cannot save state data on Memory Card %d
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dには状態データをセーブできない\n" VT_RST);

    // State data has been saved on Memory Card %d
    OSReport(VT_COL(YELLOW, BLACK) "メモリーカード%dに状態データをセーブしました\n" VT_RST);
}
