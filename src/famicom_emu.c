
#include "famicom_emu.h"

#include "Famicom/famicomPriv.h"
#include "_mem.h"
#include "dolphin/gx.h"
#include "jsyswrap.h"
#include "libc64/sprintf.h"
#include "libjsys/jsyswrapper.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_malloc.h"
#include "m_scene.h"

static int famicom_done = FALSE;
static int famicom_done_countdown = 0;
static void* freeXfbBase = NULL;
static u32 freeXfbSize = 0;

static void my_alloc_init(GAME* game, void* start, size_t size) {
    u32 freebytes;
    uintptr_t alloc;
    uintptr_t aligned;
    uintptr_t tsize;

    freebytes = game_getFreeBytes(game);
    alloc = (uintptr_t)THA_alloc16(&game->tha, freebytes);
    aligned = ALIGN_NEXT(alloc, 16);
    tsize = aligned - alloc;

    zelda_InitArena((void*)aligned, freebytes - tsize);

    if ((start != NULL) && (size != 0)) {
        zelda_AddBlockArena(start, size);
    }
}

static void my_alloc_cleanup() {
    zelda_CleanupArena();
}

static int my_zelda_getmemblocksize(void* ptr) {
    return zelda_GetMemBlockSize(ptr);
}

static int my_zelda_gettotalfreesize() {
    return zelda_GetTotalFreeSize();
}

static void* my_zelda_malloc_align(size_t size, u32 align) {
    void* aligned = zelda_malloc_align(size, align);

    if (aligned != NULL) {
        memset(aligned, 0xFF, size);
    }
    return aligned;
}

static void my_zelda_free(void* ptr) {
    zelda_free(ptr);
}

Famicom_MallocInfo my_malloc_func = {
    my_zelda_malloc_align,
    my_zelda_free,
    my_zelda_getmemblocksize,
    my_zelda_gettotalfreesize,
};

extern void famicom_emu_main(GAME* famicom) {
    int padid;
    pad_t* current_pad;
    u32 combo;

    if (!famicom_done) {
        if (famicom_rom_load_check() < 0) {
            Common_Set(my_room_message_control_flags, Common_Get(my_room_message_control_flags) | 1);
            famicom_done = TRUE;
            famicom_done_countdown = 0;
        } else {
            for (padid = 0; padid < 4; padid++) {
                current_pad = &gamePT->pads[padid];
                combo = current_pad->now.button | current_pad->on.button;

                if (combo == (BUTTON_L | BUTTON_R | BUTTON_Z) || combo == (BUTTON_L | BUTTON_R | BUTTON_X | BUTTON_Y)) {
                    famicom_done = TRUE;
                    famicom_done_countdown = 60;
                    JC_JFWDisplay_startFadeOut(JC_JFWDisplay_getManager(), famicom_done_countdown);
                    break;
                }
            }
        }
    }
    
    if (famicom_done) {
        if (famicom_done_countdown == 0) {
            return_emu_game(famicom);
        } else {
            famicom_done_countdown--;
        }
    }

    JW_BeginFrame();
    famicom->disable_display = 1;

    if (!famicom_done) {
        famicom_1frame();
    } else {
        static GXColor black_color = { 0, 0, 0, 0 };
        void* manager = JC_JFWDisplay_getManager();

        JC_JFWDisplay_clearEfb(manager, black_color);
    }
    JW_EndFrame();
}

extern void famicom_emu_init(GAME* game) {
#ifdef TARGET_PC
    /* NES emulators are not implemented on PC — immediately return to room */
    game->exec = famicom_emu_main;
    game->cleanup = famicom_emu_cleanup;
    famicom_done = TRUE;
    famicom_done_countdown = 0;
    Common_Set(my_room_message_control_flags, Common_Get(my_room_message_control_flags) | 1);
    return_emu_game(game);
    return;
#endif
    int rom_id;
    u8 player;
    int debug;
    void* manager;
    const GXRenderModeObj* render;

    famicom_done = FALSE;
    famicom_done_countdown = 0;
    game_resize_hyral(game, 0);
    Common_Set(famicom_287F9, 0);

    rom_id = Common_Get(current_famicom_rom);
    player = Common_Get(player_no);
    save_game_image = (GETREG(HREG, 4) == 1);
    debug = GETREG(HREG, 3);

    if ((rom_id > 0) && (debug != 0)) {
        rom_id = debug > 0 ? debug : 0;
    }

    game->exec = famicom_emu_main;
    game->cleanup = famicom_emu_cleanup;

    while (sAdo_SubGameOK() == FALSE) {
        VIWaitForRetrace();
        sAdo_GameFrame();
    }

    manager = JC_JFWDisplay_getManager();
    render = JC_JFWDisplay_getRenderMode(manager);
    freeXfbBase = JC_JFWDisplay_changeToSingleXfb(manager, 1);
    freeXfbSize = render->fbWidth * render->xfbHeight * sizeof(u16);

    my_alloc_init(game, freeXfbBase, freeXfbSize);

    if (famicom_init(rom_id, &my_malloc_func, player) != 0) {
        Common_Set(my_room_message_control_flags, Common_Get(my_room_message_control_flags) | 1);
        return_emu_game(game);
    }
}

extern void famicom_emu_cleanup(GAME* game) {
    JC_JFWDisplay_startFadeIn(JC_JFWDisplay_getManager(), 1);

    if (famicom_cleanup() != 0) {
        Common_Set(my_room_message_control_flags, Common_Get(my_room_message_control_flags) | 2);
    }

    my_alloc_cleanup();

    if (freeXfbBase != NULL) {
        JC_JFWDisplay_changeToDoubleXfb(JC_JFWDisplay_getManager());
        freeXfbBase = NULL;
        freeXfbSize = 0;
    }
    sAdo_SubGameEnd();
}

extern void* famicom_gba_getImage(u32 rom_id, size_t* size) {
    static char* names[] = {
        "cluclu", "usa_balloon",  "donkey", "usa_jr_math", "pinball",  "tennis", "usa_golf",
        NULL,     "usa_baseball", NULL,     "usa_donkey3", "donkeyjr", "soccer", "exbike",
        NULL,     "usa_icecl",    "mario",  "smario",      NULL,
    };

    char buf[256];
    void* resource;
    char* rom;

    if (rom_id > 19) {
        return 0;
    }

    rom = names[(rom_id == 0) ? 0 : rom_id - 1];

    if (rom == NULL) {
        return 0;
    } else {
        sprintf(buf, "/FAMICOM/GBA/jb_%s.bin.szs", rom);
        resource = JC__JKRGetResource(buf);
        if ((resource != NULL) && (size != NULL)) {
            *size = JC__JKRGetMemBlockSize(0, resource);
        }
    }
    return resource;
}

extern void famicom_gba_removeImage(void* p) {
    JC__JKRRemoveResource(p);
}
