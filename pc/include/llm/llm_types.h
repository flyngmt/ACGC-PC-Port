#ifndef LLM_TYPES_H
#define LLM_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LLM_HISTORY_DEPTH 20
#define LLM_ENTRY_LEN 256
#define LLM_NAME_LEN 16
#define LLM_CONFIG_PATH "llm.ini"
#define LLM_SAVE_PATH "save/llm_history.bin"
#define LLM_MAX_JOBS 4

typedef enum {
    LLM_ROLE_SYSTEM,
    LLM_ROLE_PLAYER,
    LLM_ROLE_NPC,
} LlmEntryRole;

typedef struct {
    char name[LLM_NAME_LEN];
    char text[LLM_ENTRY_LEN];
    int  role;
    int  gossip_seed;
    uint16_t npc_id;
    uint32_t gossip_id;
} LlmHistoryEntry;

typedef struct {
    LlmHistoryEntry entries[LLM_HISTORY_DEPTH];
    int head;
    int count;
    uint32_t next_gossip_id;
} LlmHistory;

typedef enum {
    LLM_PROVIDER_OLLAMA,
    LLM_PROVIDER_OPENAI,
    LLM_PROVIDER_GEMINI,
    LLM_PROVIDER_DEEPSEEK,
    LLM_PROVIDER_COUNT
} LlmProviderType;

typedef struct {
    LlmProviderType provider;
    char endpoint[256];
    char api_key[128];
    char model[64];
    int  timeout_ms;
    int  max_tokens;
    float temperature;
    int  enabled;
    int  chat_chance;  /* 0-100: % chance LLM replaces greeting, default 50 */
    char prompt_extra[256]; /* additional prompt context, from llm.ini */
    int  topic_hobbies_pct;   /* default 40 */
    int  topic_relations_pct; /* default 30 */
    int  topic_smalltalk_pct; /* default 30 */
    int  memory_influence_pct; /* % chance memory injects into prompt, default 40 */
} LlmConfig;

typedef void (*LlmCallback)(const char *response, int status, void *userdata);

typedef struct {
    const char *name;
    int  (*init)(const LlmConfig *cfg);
    void (*query)(const char *prompt, LlmCallback cb, void *userdata);
    void (*shutdown)(void);
    int  context_limit;
} LlmProvider;

/* async job: prompt + target buffer, processed by background thread */
typedef struct {
    char prompt[4096];
    void *target_msg_data;   /* mMsg_Data_c* to write response into */
    int  msg_no;
    int  done;               /* 0=pending, 1=done, -1=error */
    char response[600];      /* response text */
    int *done_ref;           /* if set, *done_ref is written with 'done' on completion
                              * (job is copied in llm_submit_job, so the caller's own
                              * struct would otherwise never see the result) */
} LlmJob;

/* global state */
extern LlmConfig g_llm_config;
extern LlmHistory g_llm_history[];

/* public API */
int  llm_init(void);
void llm_shutdown(void);
int  llm_submit_job(LlmJob *job);
int  llm_is_enabled(void);
void llm_tick_jobs(void);

#ifdef __cplusplus
}
#endif

#endif
