#include "m_trademark.h"

#include "m_scene_table.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_kankyo.h"
#include "m_cpak.h"
#include "m_flashrom.h"
#include "m_private.h"
#include "m_event.h"
#include "m_private.h"
#include "m_time.h"
#include "libultra/libultra.h"
#include "initial_menu.h"
#include "m_titledemo.h"
#include "m_bgm.h"
#include "m_rcp.h"
#include "m_home.h"
#include "m_mail.h"
#include "m_msg.h"
#include "m_field_info.h"
#include "m_font.h"
#include "m_quest.h"
#include "m_bg_item.h"
#include "m_card.h"
#include "m_island.h"
#include "m_vibctl.h"
#include "sys_matrix.h"
#include "sys_vimgr.h"
#include "jsyswrap.h"
#include "libc64/qrand.h"
#include "m_common_data.h"
#include "m_play.h"

static int mTR_first_flag = TRUE;

static Door_data_c demo_1_door_data = { SCENE_TITLE_DEMO, 4, FALSE, 0, { 2180, 200, 824 }, EMPTY_NO, 3, { 0, 0, 0 } };

static Door_data_c demo_2_door_data = { SCENE_TITLE_DEMO, 4, FALSE, 0, { 3218, 40, 3074 }, EMPTY_NO, 3, { 0, 0, 0 } };

static Door_data_c demo_3_door_data = { SCENE_TITLE_DEMO, 4, FALSE, 0, { 2117, 160, 1488 }, EMPTY_NO, 3, { 0, 0, 0 } };

static Door_data_c demo_4_door_data = { SCENE_TITLE_DEMO, 4, FALSE, 0, { 2899, 160, 1101 }, EMPTY_NO, 3, { 0, 0, 0 } };

static Door_data_c demo_5_door_data = { SCENE_TITLE_DEMO, 4, FALSE, 0, { 1578, 40, 2472 }, EMPTY_NO, 3, { 0, 0, 0 } };

static Door_data_c* l_demo_door_data_table[mTD_TITLE_DEMO_NUM] = { &demo_1_door_data, &demo_2_door_data,
                                                                   &demo_3_door_data, &demo_4_door_data,
                                                                   &demo_5_door_data };

#define DEMO_NPC(name, bx, bz, utx, utz) \
    { NPC_##name, (bx), (bz), (utx), (utz) }
static mNpc_demo_npc_c demo_npc_list[] = {
    DEMO_NPC(BOB, 1, 2, 3, 7),     DEMO_NPC(PAOLO, 1, 2, 8, 11),  DEMO_NPC(VESTA, 1, 4, 12, 11),
    DEMO_NPC(JOEY, 2, 3, 5, 6),    DEMO_NPC(LOBO, 2, 3, 4, 12),   DEMO_NPC(CARRIE, 3, 5, 11, 5),
    DEMO_NPC(TANK, 4, 3, 3, 12),   DEMO_NPC(BUZZ, 4, 4, 3, 4),    DEMO_NPC(RASHER, 4, 4, 12, 13),
    DEMO_NPC(BIFF, 4, 6, 5, 6),    DEMO_NPC(SAMSON, 5, 2, 12, 4), DEMO_NPC(JANE, 5, 2, 9, 11),
    DEMO_NPC(TYBALT, 5, 4, 11, 4),
/* @BUG - mNpc_SetAnimalTitleDemo uses ANIMAL_NUM_MAX (15) but only 14 are set */
#if !defined(BUGFIXES) && !defined(TARGET_PC)
    DEMO_NPC(CUBE, 5, 5, 5, 11)
#else
    DEMO_NPC(CUBE, 5, 5, 5, 11),   { EMPTY_NO, 0, 0, 0, 0 }
#endif
};

static int demo_npc_num = sizeof(demo_npc_list) / sizeof(mNpc_demo_npc_c);

static int set_npc_4_title_demo(GAME_TRADEMARK* trademark) {
    Animal_c* animals = Save_Get(animals);

#ifdef TARGET_PC
    mNpc_InitNpcList(Common_Get(npclist), ANIMAL_NUM_MAX);
#endif
    mNpc_SetAnimalTitleDemo(demo_npc_list, animals, (GAME*)trademark);
    mNpc_SetNpcList(Common_Get(npclist), animals, demo_npc_num, 0);

    return demo_npc_num;
}

typedef struct tradeday_s {
    lbRTC_month_t month;
    lbRTC_day_t day;
    lbRTC_hour_t hour;
    s16 weather;
} mTM_tradeday_c;

static void mTM_demotime_set(int title_no) {
    static mTM_tradeday_c tradeday_table[] = {
        { lbRTC_APRIL, 6, 13, mEnv_WEATHER_SAKURA },   /* April 6th @ 1pm, Cherry Blossoms */
        { lbRTC_JUNE, 16, 13, mEnv_WEATHER_RAIN },     /* June 16th @ 1pm, Raining */
        { lbRTC_AUGUST, 1, 6, mEnv_WEATHER_CLEAR },    /* August 1st @ 6am, Clear */
        { lbRTC_NOVEMBER, 1, 16, mEnv_WEATHER_CLEAR }, /* November 1st @ 4pm, Clear */
        { lbRTC_FEBRUARY, 1, 2, mEnv_WEATHER_SNOW }    /* February 1st @ 2am, Snowing */
    };

    Common_Set(time.rtc_enabled, FALSE);
    Common_Set(time.rtc_time.year, GAME_YEAR_MIN + 1);
    Common_Set(time.rtc_time.min, 0);

    if (title_no != 0) {
        Common_Set(time.rtc_time.month, tradeday_table[(title_no - 1)].month);
        Common_Set(time.rtc_time.day, tradeday_table[(title_no - 1)].day);
        Common_Set(time.rtc_time.hour, tradeday_table[(title_no - 1)].hour);
        Common_Set(weather, tradeday_table[(title_no - 1)].weather);
    }
}

static void trademark_goto_demo_scene(GAME_TRADEMARK* trademark) {
    int demo_no;
    int i;
    Private_c* n_private;
    Save_t* save;
    Private_c* private;

    save = Common_GetPointer(save.save);
    mCPk_InitPak(0);
    n_private = Save_Get(private_data);
    Common_Set(now_private, n_private);

    if (mFRm_CheckSaveData() == FALSE) {
        bzero(save, sizeof(Save));
        mFRm_ClearSaveCheckData(Save_GetPointer(save_check));

        private = n_private;
        for (i = 0; i < PLAYER_NUM; i++) {
            mPr_ClearPrivateInfo(private);
            private++;
        }

        Save_Set(land_info.exists, TRUE);
        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, -1);
    }

    mEv_ClearEventInfo();

    demo_no = mEv_CheckTitleDemo();
    if (demo_no > mEv_TITLEDEMO_NONE) {
        Door_data_c* demo_door_data = l_demo_door_data_table[demo_no -mEv_TITLEDEMO_START1 ];

        Common_Set(door_data, *demo_door_data);
        Common_Set(door_data.next_scene_id, demo_door_data->next_scene_id + 1); // go to next demo scene
        mTM_demotime_set(demo_no);                                              // set demo date, time, and weather
#ifdef TARGET_PC
        /* On PC, save data lives only in memory. The title demo functions
         * mPr_RandomSetPlayerData_title_demo and set_npc_4_title_demo both
         * mutate Save_t data (player private data and animal data respectively).
         * On GC this doesn't matter because the real save lives on the memory card
         * and gets reloaded. On PC we must save and restore the data. */
        {
            extern int pc_save_loaded;
            static Private_c pc_saved_private[PLAYER_NUM];
            static Animal_c pc_saved_animals[ANIMAL_NUM_MAX];
            static u8 pc_saved_door_original[PLAYER_NUM];
            if (pc_save_loaded) {
                for (i = 0; i < PLAYER_NUM; i++) {
                    pc_saved_private[i] = Save_Get(private_data[i]);
                    pc_saved_door_original[i] = Save_Get(homes[i]).door_original;
                }
                memcpy(pc_saved_animals, Save_Get(animals), sizeof(pc_saved_animals));
            }
            mPr_RandomSetPlayerData_title_demo();
            set_npc_4_title_demo(trademark);
            if (pc_save_loaded) {
                for (i = 0; i < PLAYER_NUM; i++) {
                    Save_Get(private_data[i]) = pc_saved_private[i];
                    Save_Get(homes[i]).door_original = pc_saved_door_original[i];
                }
                memcpy(Save_Get(animals), pc_saved_animals, sizeof(pc_saved_animals));
            }
        }
#else
        mPr_RandomSetPlayerData_title_demo();                                   // randomize player data
        set_npc_4_title_demo(trademark);                                        // set animals in the demo
#endif
        Common_Set(transition.wipe_type, WIPE_TYPE_FADE_BLACK);
    }

    Save_Set(scene_no, SCENE_TITLE_DEMO);
    mTM_set_season();
    Common_Set(submenu_disabled, TRUE);
    GAME_GOTO_NEXT((GAME*)trademark, play, PLAY);
}

static void nintendo_logo_move(GAME_TRADEMARK* trademark) {
    const double dt_frames = trademark->game.graph->dt_num_60fps_frames;
    int timer;
    float alpha2;

    if (trademark->stage == 2) {
        alpha2 = trademark->alpha2;
        alpha2 += 0x880 * dt_frames;
        if (alpha2 >= 0xFF00) {
            trademark->stage = 4;
            alpha2 = 0xFF00;
        }

        trademark->alpha2 = alpha2;
    } else if (trademark->stage == 4) {
        trademark->logo_timer -= dt_frames;
        if (trademark->logo_timer <= 0) {
            trademark->stage = 3;
        }
    }
}

static void nintendo_logo_draw(GAME_TRADEMARK* trademark) {
    Gfx* gfx;
    GRAPH* g = trademark->game.graph;
    u8 a;

    OPEN_DISP(g);
    nintendo_logo_move(trademark);
    gfx = NOW_POLY_OPA_DISP;
    a = (int)trademark->alpha2 >> 8;
    make_dl_nintendo_logo(&gfx, a);
    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(g);
}

static void trademark_cancel(GAME_TRADEMARK* trademark) {
    if (trademark->cancel != FALSE) {
        return;
    }

    if (trademark->stage != 4) {
        return;
    }

    if (Common_Get(pad_connected) == FALSE) {
        return;
    }

    if ((gamePT->pads[0].on.button & BUTTON_START) != BUTTON_START) {
        return;
    }

    trademark->cancel = TRUE;
}

static void trademark_move(GAME_TRADEMARK* trademark) {
    static u8 s_titlebgm[mTD_TITLE_DEMO_NUM] = { 83, 84, 85, 86, 87 }; // TODO: convert to enum/definitions
    const double dt_frames = trademark->game.graph->dt_num_60fps_frames;

    if (trademark->stage == 0) {
        int titledemo_no = mTD_get_titledemo_no();
        mBGMPsComp_make_ps_lost_fanfare(s_titlebgm[titledemo_no], 360);
        trademark->alpha = 0;
        trademark->stage = 1;
    }

    if (trademark->stage == 1) {
        trademark->move_timer -= dt_frames;
        if (trademark->move_timer <= 0) {
            trademark->stage = 2;
        }
    }

    if (trademark->stage == 3 || trademark->cancel) {
        if (trademark->alpha < 0xFF00) {
            trademark->alpha += 0x880 * dt_frames;
        }

        if (trademark->check != TRUE) {
            trademark->check = TRUE;
        }

        if (trademark->alpha >= 0xFF00 && trademark->check == TRUE) {
            trademark->alpha = 0xFF00;
            trademark->stage = 5;
        }
    }
}

static void trademark_draw(GAME_TRADEMARK* trademark) {
    GRAPH* g = trademark->game.graph;
    Gfx* gfx;

    OPEN_DISP(g);

    gSPSegment(NOW_POLY_OPA_DISP++, 0, 0);
    DisplayList_initialize(g, 0, 0, 0, NULL);
    if (mTR_first_flag == FALSE) {
        if (trademark->stage >= 2) {
            nintendo_logo_draw(trademark);
        }

        gfx = NOW_POLY_XLU_DISP;
        fade_black_draw(&gfx, (int)trademark->alpha >> 8);
        SET_POLY_XLU_DISP(gfx);
    }

    CLOSE_DISP(g);
}

static void trademark_main(GAME* game) {
    GAME_TRADEMARK* trademark = (GAME_TRADEMARK*)game;
    GRAPH* g;

    fqrand(); /* increment qrand seed every frame */
    trademark_cancel(trademark);
    trademark_move(trademark);
    trademark_draw(trademark);

    g = game->graph;
    game_debug_draw_last(game, g);
    game_draw_last(g);

    if (trademark->stage == 5) {
        trademark->stage = 0;
        trademark_goto_demo_scene(trademark);
        mTR_first_flag = FALSE;
    }
}

extern void trademark_cleanup(GAME* game) {
    GAME_TRADEMARK* trademark = (GAME_TRADEMARK*)game;
    mHm_hs_c* home = Save_Get(homes);
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        home->outlook_pal = i;
        home->next_outlook_pal = i;

        mMl_clear_mail_box(home->mailbox, HOME_MAILBOX_SIZE);
        home++;
    }

    JW_SetLogoMode(0);
    SoftResetEnable = TRUE;
}

extern void trademark_init(GAME* game) {
#ifdef TARGET_PC
    OSReport("[PC] trademark_init: enter\n");
#endif
    GAME_TRADEMARK* trademark = (GAME_TRADEMARK*)game;
    GRAPH* g = game->graph;

    common_data_reinit();
    mFI_SetClimate(mFI_CLIMATE_0);
    game->exec = &trademark_main;
    game->cleanup = &trademark_cleanup;
    initView(&trademark->view, g);
    new_Matrix(game);
    trademark->alpha = 0xFF00;
    trademark->alpha2 = 0;
    trademark->logo_timer = 60;
    trademark->move_timer = 16;
    trademark->unused_254 = 0;
    trademark->unused_210 = 0;
    trademark->stage = 0;
    trademark->unused_200.x = 0.0f;
    trademark->unused_200.y = 0.0f;
    trademark->unused_200.z = 0.0f;
    trademark->unused_20c = 0.5f;
    trademark->unused_25a62 = 0;
    trademark->unused_25a64 = 5072;
    trademark->unused_25a67 = 0;
    trademark->cancel = FALSE;
    trademark->check = FALSE;

    if (mTR_first_flag) {
        trademark->stage = 5;
    }

    SetGameFrame(1);
    viBlack(FALSE);
    JW_SetLogoMode(1);
    mMsg_aram_init();

    Common_Set(player_no, 0);
    Common_Set(player_data_mode, 0);
    Common_Set(scene_from_title_demo, -1);
    mNpc_ClearCacheName();
    mNpc_ClearInAnimal();
    mNpc_FirstClearGoodbyMail();
    mQst_ClearGrabItemInfo();
    mNpc_ClearIslandNpcRoomData();
    mCD_InitAll();
    mISL_ClearKeepIsland();
    mBI_ct();
    mFont_ct();
    mBGMPsComp_scene_mode(0);
    mVibctl_init0();
    mFRm_clear_err_info();
    mEv_SetTitleDemo(mTD_demono_get());
}
