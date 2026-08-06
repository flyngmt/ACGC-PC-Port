#ifndef LLM_API_H
#define LLM_API_H

#include "llm/llm_types.h"

/* forward declarations for game types */
typedef struct message_window_s mMsg_Window_c;
typedef struct message_data_s mMsg_Data_c;

/* history */
void llm_history_init(LlmHistory *h);
void llm_history_append(LlmHistory *h, const char *name, const char *text,
                         int role, int gossip_seed, uint16_t npc_id);
void llm_history_clear(LlmHistory *h);
int  llm_history_save(const char *path, LlmHistory *histories, int count);
int  llm_history_load(const char *path, LlmHistory *histories, int count);

/* prompt */
int  llm_build_prompt(char *buf, int bufsz,
                       const char *npc_name, int personality,
                       const char *catchphrase,
                       const char *town_name, const char *player_name,
                       const char *weather, const char *season,
                       const char *time_of_day, int mood,
                       LlmHistory *history, LlmHistory *gossip_sources,
                       int gossip_count, const char *stock_text,
                       const char *town_residents, int resident_count);

/* gossip */
void llm_gossip_tick(void);
void llm_gossip_purge_npc(int npc_idx);

/* hook */
void llm_hook_init(void);
int  llm_hook_on_msg_change(int msg_no, mMsg_Window_c *msg_window, mMsg_Data_c *msg_data);
void llm_hook_tick(void);
void llm_hook_on_conversation_end(int npc_idx);
void llm_hook_apply_response(void *msg_data, const char *text);
void llm_hook_on_job_failed(void *msg_data);

/* core */
int  llm_submit_job(LlmJob *job);
void llm_tick_jobs(void);

/* util */
char *llm_json_escape(const char *src);
void  llm_json_build_kv(char *buf, int bufsz, const char *key, const char *val);
int   llm_json_parse_str(const char *json, const char *key, char *out, int outsz);

#endif
