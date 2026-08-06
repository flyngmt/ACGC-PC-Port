/* llm_hook.c - dialogue hook: submits async jobs, applies responses each frame */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include "llm/llm_types.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_npc.h"
#include "m_npc_personal_id.h"
#include "m_actor.h"
#include "m_player_lib.h"
#include "m_player.h"
#include "m_event.h"
#include "m_common_data.h"
#include "m_kankyo.h"
#include "game.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

extern int g_pc_verbose;

static LlmJob g_pending_job = {0};
static char g_stock_text[mMsg_MSG_BUF_SIZE] = {0};
static int  g_stock_len = 0;
static char g_memory_npc[ANIMAL_NAME_LEN + 1] = "";
static char g_memory_ctx[128] = "";  /* season/weather/time/mood snapshot */

#define MSG_LINE_MAX_UNITS 176

static int msg_write_text(u8 *dst, int dstsz, const char *src) {
    int out = 0, line_w = 0, lines = 1, truncated = 0;
    const char *p = src;
    while (*p && out < dstsz - 8 && lines <= 4) {
        if (*p == '\n') { dst[out++] = CHAR_NEW_LINE; line_w = 0; lines++; p++; continue; }
        int word_w = 0; const char *w = p;
        while (*w && *w != ' ' && *w != '\n') {
            unsigned char c = (unsigned char)*w;
            if (c >= 0x20 && c <= 0x7E) word_w += mFont_GetCodeWidth(c, TRUE);
            w++;
        }
        if (out > 0 && line_w > 0 && line_w + word_w > MSG_LINE_MAX_UNITS) {
            if (lines >= 4) { truncated = 1; break; }
            dst[out++] = CHAR_NEW_LINE; line_w = 0; lines++;
        }
        while (p < w && out < dstsz - 8) {
            unsigned char c = (unsigned char)*p;
            if (c >= 0x20 && c <= 0x7E) { dst[out++] = c; line_w += mFont_GetCodeWidth(c, TRUE); }
            p++;
        }
        if (*p == ' ') { dst[out++] = (u8)*p++; line_w += mFont_GetCodeWidth(' ', TRUE); }
    }
    if (*p) truncated = 1;
    if (truncated && out < dstsz - 8) { dst[out++] = '.'; dst[out++] = '.'; dst[out++] = '.'; }
    if (out > dstsz - 2) out = dstsz - 2;
    dst[out++] = CHAR_CONTROL_CODE;
    dst[out++] = (u8)mFont_CONT_CODE_LAST;
    return out;
}

static void decode_game_str(char *dst, int dstsz, const u8 *src, int srclen) {
    int out = 0;
    for (int i = 0; i < srclen && out < dstsz - 1; i++) {
        u8 c = src[i];
        dst[out++] = (c >= 0x20 && c <= 0x7E) ? (char)c : ' ';
    }
    while (out > 0 && dst[out - 1] == ' ') out--;
    dst[out] = '\0';
}

static const char *weather_str(int w, int i) {
    if (w == mEnv_WEATHER_RAIN) return i >= mEnv_WEATHER_INTENSITY_HEAVY ? "stormy" : "rainy";
    if (w == mEnv_WEATHER_SNOW) return "snowy";
    return "clear";
}
static const char *season_str(int s) {
    switch (s) { case 0: return "spring"; case 1: return "summer"; case 2: return "autumn"; case 3: return "winter"; default: return "spring"; }
}
static const char *time_of_day_str(int h) {
    if (h >= 5 && h < 12) return "morning";
    if (h >= 12 && h < 17) return "afternoon";
    if (h >= 17 && h < 21) return "evening";
    return "late night";
}

static void memory_save(const char *npc_name, const char *ctx, const char *text) {
    char path[256];
    snprintf(path, sizeof(path), "memory/%s.txt", npc_name);
#ifdef TARGET_PC
    FILE *fp = fopen(path, "a");
    if (!fp) {
        mkdir("memory"
#ifdef _WIN32
        );
#else
        , 0755);
#endif
        fp = fopen(path, "a");
    }
    if (fp) {
        fprintf(fp, "[%s] %s\n", ctx, text);
        fclose(fp);
    }
#else
    (void)npc_name; (void)ctx; (void)text;
#endif
}

void llm_hook_apply_response(void *msg_data, const char *text) {
    if (!msg_data || !text || !text[0]) return;
    mMsg_Data_c *md = (mMsg_Data_c *)msg_data;
    if (md->msg_no != g_pending_job.msg_no) return;
    md->msg_len = msg_write_text(md->text_buf.data, mMsg_MSG_BUF_SIZE, text);
    md->data_loaded = 1;
    mMsg_UNSET_LOCKCONTINUE();
    memory_save(g_memory_npc, g_memory_ctx, text);
#ifdef PC_DEBUG_MSG
    printf("[DBG-LLM] apply msg_no=%d len=%d\n", md->msg_no, md->msg_len);
#endif
    if (msg_data == g_pending_job.target_msg_data)
        g_pending_job.target_msg_data = NULL;
}

void llm_hook_on_job_failed(void *msg_data) {
    if (!msg_data || msg_data != g_pending_job.target_msg_data) return;
    mMsg_Data_c *md = (mMsg_Data_c *)msg_data;
    if (md->msg_no != g_pending_job.msg_no) return;
    if (g_stock_text[0]) { memcpy(md->text_buf.data, g_stock_text, sizeof(g_stock_text)); md->msg_len = g_stock_len; }
    md->data_loaded = 1;
    mMsg_UNSET_LOCKCONTINUE();
    g_pending_job.target_msg_data = NULL;
}

void llm_hook_init(void) {
    memset(&g_pending_job, 0, sizeof(g_pending_job));
    memset(g_stock_text, 0, sizeof(g_stock_text));
    g_stock_len = 0;
}

int llm_hook_on_msg_change(int msg_no, mMsg_Window_c *msg_p, mMsg_Data_c *msg_data) {
    if (!llm_is_enabled()) return 0;

    if (mPlib_get_player_actor_main_index(gamePT) != mPlayer_INDEX_TALK) {
        if (g_pc_verbose) printf("[LLM] Skip (not talk)\n");
        return 0;
    }
    ACTOR *actor = msg_p->client_actor_p;
    if (!actor || ITEM_NAME_GET_TYPE(actor->npc_id) != NAME_TYPE_NPC) {
        if (g_pc_verbose) printf("[LLM] Skip (not villager)\n");
        return 0;
    }

    /* Only intercept fresh conversation starts */
    if (msg_p->continue_msg_no != 0xFFFF) {
        if (g_pc_verbose) printf("[LLM] Skip (chain page)\n");
        return 0;
    }

    /* LLM chance from config (0-100, default 50) */
    int chance = g_llm_config.chat_chance;
    if (chance <= 0 || (rand() % 100) >= chance) {
        if (g_pc_verbose) printf("[LLM] Stock (%d%%)\n", chance);
        return 0;
    }

    if (g_pending_job.target_msg_data && g_pending_job.done == 0) {
        if (g_pc_verbose) printf("[LLM] Busy\n");
        return 0;
    }

    u8 *raw_name = mNpc_GetNpcWorldNameP(actor->npc_id);
    char npc_name[ANIMAL_NAME_LEN + 1];
    decode_game_str(npc_name, sizeof(npc_name), raw_name, mMsg_Get_Length_String(raw_name, ANIMAL_NAME_LEN));

    u8 *raw_phrase = mNpc_GetWordEnding(actor);
    char catchphrase[ANIMAL_CATCHPHRASE_LEN + 1];
    decode_game_str(catchphrase, sizeof(catchphrase), raw_phrase, mMsg_Get_Length_String(raw_phrase, ANIMAL_CATCHPHRASE_LEN));

    char player_name[PLAYER_NAME_LEN + 1];
    decode_game_str(player_name, sizeof(player_name), Now_Private->player_ID.player_name,
                    mMsg_Get_Length_String(Now_Private->player_ID.player_name, PLAYER_NAME_LEN));

    char town_name[LAND_NAME_SIZE + 1];
    decode_game_str(town_name, sizeof(town_name), Save_Get(land_info.name),
                    mMsg_Get_Length_String(Save_Get(land_info.name), LAND_NAME_SIZE));

    char stock_text[mMsg_MSG_BUF_MAX];
    decode_game_str(stock_text, sizeof(stock_text), msg_data->text_buf.data, msg_data->msg_len);

    /* Gather real town residents for relationship seeding */
    char residents[512] = "";
    int  resident_count = 0;
    {
        /* villagers */
        for (int i = 0; i < ANIMAL_NUM_MAX; i++) {
            Animal_c *a = &Save_Get(animals[i]);
            if (mNpc_CheckFreeAnimalPersonalID(&a->id) == FALSE) {
                u8 *raw = mNpc_GetNpcWorldNameP(a->id.npc_id);
                int rlen = mMsg_Get_Length_String(raw, ANIMAL_NAME_LEN);
                char rname[ANIMAL_NAME_LEN + 1];
                decode_game_str(rname, sizeof(rname), raw, rlen);
                if (rname[0]) {
                    int rpos = strlen(residents);
                    snprintf(residents + rpos, sizeof(residents) - rpos,
                             "%s%s", rpos > 0 ? ", " : "", rname);
                    resident_count++;
                }
            }
        }
        /* special NPCs: Tom Nook, Mayor */
        static const mActor_name_t specials[] = {
            SP_NPC_SHOP_MASTER, SP_NPC_SONCHO,
        };
        for (int i = 0; i < 2; i++) {
            u8 *raw = mNpc_GetNpcWorldNameP(specials[i]);
            int rlen = mMsg_Get_Length_String(raw, ANIMAL_NAME_LEN);
            char rname[ANIMAL_NAME_LEN + 1];
            decode_game_str(rname, sizeof(rname), raw, rlen);
            if (rname[0]) {
                int rpos = strlen(residents);
                snprintf(residents + rpos, sizeof(residents) - rpos,
                         "%s%s", rpos > 0 ? ", " : "", rname);
                resident_count++;
            }
        }
    }

    int personality = mNpc_GetLooks(actor->npc_id);
    int weather = Common_Get(weather), weather_int = Common_Get(weather_intensity);
    int season = Common_Get(time.season), hour = Common_Get(time.rtc_time.hour);
    int mood = ((NPC_ACTOR *)actor)->npc_info.animal->mood;

    llm_build_prompt(g_pending_job.prompt, sizeof(g_pending_job.prompt),
                     npc_name, personality, catchphrase,
                     town_name, player_name,
                     weather_str(weather, weather_int), season_str(season),
                     time_of_day_str(hour), mood, NULL, NULL, 0, stock_text,
                     residents, resident_count);

    /* Snapshot for memory bank: save at apply time */
    strncpy(g_memory_npc, npc_name, ANIMAL_NAME_LEN);
    g_memory_npc[ANIMAL_NAME_LEN] = '\0';
    snprintf(g_memory_ctx, sizeof(g_memory_ctx),
             "%s %s %s mood=%d %d-%02d-%02d %02d:%02d",
             season_str(season), weather_str(weather, weather_int),
             time_of_day_str(hour), mood,
             Common_Get(time.rtc_time.year),
             Common_Get(time.rtc_time.month),
             Common_Get(time.rtc_time.day),
             Common_Get(time.rtc_time.hour),
             Common_Get(time.rtc_time.min));

    g_pending_job.target_msg_data = msg_data;
    g_pending_job.msg_no = msg_no;
    g_pending_job.done = 0;
    g_pending_job.response[0] = '\0';
    g_pending_job.done_ref = &g_pending_job.done;

    if (llm_submit_job(&g_pending_job) == 0) {
        memcpy(g_stock_text, msg_data->text_buf.data, sizeof(g_stock_text));
        g_stock_len = msg_data->msg_len;
        msg_data->msg_len = msg_write_text(msg_data->text_buf.data, mMsg_MSG_BUF_SIZE, "...");
        msg_data->data_loaded = 1;
        mMsg_SET_LOCKCONTINUE();  /* block A press while waiting for LLM */
        if (g_pc_verbose) printf("[LLM] Submit: npc=%s msg=%d\n", npc_name, msg_no);
    }
    return 0;
}

void llm_hook_tick(void) { llm_tick_jobs(); }
void llm_hook_on_conversation_end(int npc_idx) { (void)npc_idx; }
