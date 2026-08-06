/* llm_core.c - LLM subsystem: config, threading, job management */
#include "pc_platform.h"
#include "llm/llm_types.h"
#include "llm/llm_api.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

extern int g_pc_verbose;

LlmConfig g_llm_config = {0};
LlmHistory g_llm_history[15] = {0};

/* --- INI config parser --- */
static void llm_trim(char *s) {
    int len = (int)strlen(s);
    while (len > 0 && (s[len-1] == '\r' || s[len-1] == '\n' || s[len-1] == ' ' || s[len-1] == '\t'))
        s[--len] = '\0';
    int off = 0;
    while (s[off] == ' ' || s[off] == '\t') off++;
    if (off > 0) memmove(s, s + off, len - off + 1);
}

static int llm_parse_int(const char *val, int def) {
    int v = atoi(val);
    return v ? v : def;
}

static float llm_parse_float(const char *val, float def) {
    float v = (float)atof(val);
    return v != 0.0f ? v : def;
}

static int llm_parse_provider(const char *val) {
    if (strcmp(val, "ollama") == 0)  return LLM_PROVIDER_OLLAMA;
    if (strcmp(val, "openai") == 0)  return LLM_PROVIDER_OPENAI;
    if (strcmp(val, "gemini") == 0)  return LLM_PROVIDER_GEMINI;
    if (strcmp(val, "deepseek") == 0) return LLM_PROVIDER_DEEPSEEK;
    return LLM_PROVIDER_OLLAMA;
}

static void llm_config_defaults(LlmConfig *cfg) {
    memset(cfg, 0, sizeof(*cfg));
    cfg->provider = LLM_PROVIDER_OLLAMA;
    strcpy(cfg->endpoint, "http://localhost:11434/api/generate");
    cfg->timeout_ms = 3000;
    cfg->max_tokens = 350;
    cfg->temperature = 0.8f;
    cfg->chat_chance = 20;
    cfg->topic_hobbies_pct = 50;
    cfg->topic_relations_pct = 20;
    cfg->topic_smalltalk_pct = 30;
    cfg->memory_influence_pct = 25;
}

static int llm_config_load(const char *path, LlmConfig *cfg) {
    FILE *fp = fopen(path, "r");
    char line[512], key[64], val[256];
    llm_config_defaults(cfg);
    if (!fp) return 0;
    while (fgets(line, sizeof(line), fp)) {
        llm_trim(line);
        if (line[0] == '#' || line[0] == '[' || line[0] == '\0') continue;
        char *eq = strchr(line, '=');
        if (!eq) continue;
        *eq = '\0';
        strcpy(key, line); strcpy(val, eq + 1);
        llm_trim(key); llm_trim(val);
        if (strcmp(key, "provider") == 0)      cfg->provider = llm_parse_provider(val);
        else if (strcmp(key, "endpoint") == 0) strncpy(cfg->endpoint, val, sizeof(cfg->endpoint)-1);
        else if (strcmp(key, "api_key") == 0)  strncpy(cfg->api_key, val, sizeof(cfg->api_key)-1);
        else if (strcmp(key, "model") == 0)    strncpy(cfg->model, val, sizeof(cfg->model)-1);
        else if (strcmp(key, "timeout_ms") == 0) cfg->timeout_ms = llm_parse_int(val, 3000);
        else if (strcmp(key, "max_tokens") == 0) cfg->max_tokens = llm_parse_int(val, 150);
        else if (strcmp(key, "temperature") == 0) cfg->temperature = llm_parse_float(val, 0.8f);
        else if (strcmp(key, "enabled") == 0) cfg->enabled = llm_parse_int(val, 0);
        else if (strcmp(key, "chat_chance") == 0) cfg->chat_chance = llm_parse_int(val, 50);
        else if (strcmp(key, "prompt_extra") == 0) strncpy(cfg->prompt_extra, val, sizeof(cfg->prompt_extra)-1);
        else if (strcmp(key, "topic_hobbies_pct") == 0) cfg->topic_hobbies_pct = llm_parse_int(val, 40);
        else if (strcmp(key, "topic_relations_pct") == 0) cfg->topic_relations_pct = llm_parse_int(val, 30);
        else if (strcmp(key, "topic_smalltalk_pct") == 0) cfg->topic_smalltalk_pct = llm_parse_int(val, 30);
        else if (strcmp(key, "memory_influence_pct") == 0) cfg->memory_influence_pct = llm_parse_int(val, 40);
    }
    fclose(fp);
    return 1;
}

static void llm_config_write_defaults(const char *path) {
    FILE *fp = fopen(path, "w");
    if (!fp) return;
    fprintf(fp,
        "[llm]\n"
        "provider = ollama\n"
        "endpoint = http://localhost:11434/api/generate\n"
        "api_key = \n"
        "model = \n"
        "timeout_ms = 3000\n"
        "max_tokens = 350\n"
        "temperature = 0.8\n"
         "enabled = 0\n"
        "\n"
        "# 0-100: %% chance LLM replaces a villager greeting (0=never, 100=always)\n"
        "chat_chance = 20\n"
        "\n"
        "# Topic distribution percentages (should sum to ~100)\n"
        "topic_hobbies_pct = 50\n"
        "topic_relations_pct = 20\n"
        "topic_smalltalk_pct = 30\n"
        "\n"
        "# %% chance past memories are injected into the prompt\n"
        "memory_influence_pct = 25\n"
        "\n"
        "# Extra prompt text appended to every LLM request\n"
        "prompt_extra =\n"
    );
    fclose(fp);
}

/* --- provider dispatch --- */
extern LlmProvider llm_provider_ollama;
extern LlmProvider llm_provider_openai;
extern LlmProvider llm_provider_gemini;
extern LlmProvider llm_provider_deepseek;

static LlmProvider *g_active_provider = NULL;

static const LlmProvider *providers[] = {
    [LLM_PROVIDER_OLLAMA]  = &llm_provider_ollama,
    [LLM_PROVIDER_OPENAI]  = &llm_provider_openai,
    [LLM_PROVIDER_GEMINI]  = &llm_provider_gemini,
    [LLM_PROVIDER_DEEPSEEK] = &llm_provider_deepseek,
};

/* --- thread pool --- */
static SDL_Thread *g_llm_threads[LLM_MAX_JOBS];
static LlmJob    *g_llm_jobs[LLM_MAX_JOBS];
static SDL_mutex *g_llm_mutex = NULL;
static int        g_llm_thread_count = 0;

static void llm_job_cb(const char *response, int status, void *userdata) {
    LlmJob *job = (LlmJob *)userdata;
    SDL_LockMutex(g_llm_mutex);
    if (status == 0 && response && response[0]) {
        snprintf(job->response, sizeof(job->response), "%s", response);
        job->done = 1;
    } else {
        job->done = -1;
    }
    if (job->done_ref) *job->done_ref = job->done;
    SDL_UnlockMutex(g_llm_mutex);
}

static int llm_worker(void *data) {
    LlmJob *job = (LlmJob *)data;
    g_active_provider->query(job->prompt, llm_job_cb, job);
    return 0;
}

/* --- public API --- */
int llm_init(void) {
#ifdef _WIN32
    /* winsock must be started before any socket call (gethostbyname etc.).
     * SDL does not reliably do this for us — without it every request fails
     * with WSANOTINITIALISED (10093). */
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        fprintf(stderr, "[LLM] WSAStartup failed\n");
#endif
    int loaded = llm_config_load(LLM_CONFIG_PATH, &g_llm_config);
    if (!loaded) {
        llm_config_write_defaults(LLM_CONFIG_PATH);
        llm_config_load(LLM_CONFIG_PATH, &g_llm_config);
        printf("[LLM] Created llm.ini with defaults. Edit to configure.\n");
    }

    printf("[LLM] Loaded config: provider=%d enabled=%d\n",
           g_llm_config.provider, g_llm_config.enabled);

    if (!g_llm_config.enabled) return 0;

    g_active_provider = (LlmProvider *)providers[g_llm_config.provider];
    if (g_active_provider->init && g_active_provider->init(&g_llm_config) != 0) {
        fprintf(stderr, "[LLM] Provider init failed\n");
        g_llm_config.enabled = 0;
        return -1;
    }

    g_llm_mutex = SDL_CreateMutex();
    memset(g_llm_threads, 0, sizeof(g_llm_threads));
    memset(g_llm_jobs, 0, sizeof(g_llm_jobs));

    llm_history_load(LLM_SAVE_PATH, g_llm_history, 15);

    printf("[LLM] Initialized: %s, model=%s\n",
           g_active_provider->name, g_llm_config.model);
    return 0;
}

void llm_shutdown(void) {
    if (!g_llm_config.enabled) return;

    /* wait for pending threads */
    SDL_LockMutex(g_llm_mutex);
    for (int i = 0; i < LLM_MAX_JOBS; i++) {
        if (g_llm_threads[i]) {
            SDL_UnlockMutex(g_llm_mutex);
            SDL_WaitThread(g_llm_threads[i], NULL);
            SDL_LockMutex(g_llm_mutex);
            g_llm_threads[i] = NULL;
        }
    }
    SDL_UnlockMutex(g_llm_mutex);

    llm_history_save(LLM_SAVE_PATH, g_llm_history, 15);
    if (g_active_provider && g_active_provider->shutdown)
        g_active_provider->shutdown();
    if (g_llm_mutex) SDL_DestroyMutex(g_llm_mutex);
    g_active_provider = NULL;
    g_llm_mutex = NULL;
}

int llm_submit_job(LlmJob *job) {
    if (!g_llm_config.enabled || !g_active_provider) return -1;

    job->done = 0;
    job->response[0] = '\0';

    int slot = -1;
    SDL_LockMutex(g_llm_mutex);
    for (int i = 0; i < LLM_MAX_JOBS; i++) {
        if (!g_llm_threads[i]) { slot = i; break; }
    }
    if (slot < 0) {
        SDL_UnlockMutex(g_llm_mutex);
        if (g_pc_verbose) printf("[LLM] Request rejected: all %d worker slots busy\n", LLM_MAX_JOBS);
        return -1;
    }

    /* copy job so caller can reuse stack memory */
    LlmJob *copy = malloc(sizeof(LlmJob));
    memcpy(copy, job, sizeof(LlmJob));
    g_llm_jobs[slot] = copy;
    SDL_UnlockMutex(g_llm_mutex);

    g_llm_threads[slot] = SDL_CreateThread(llm_worker, "llm_worker", copy);
    if (!g_llm_threads[slot]) {
        SDL_LockMutex(g_llm_mutex);
        free(copy);
        g_llm_jobs[slot] = NULL;
        SDL_UnlockMutex(g_llm_mutex);
        if (g_pc_verbose) printf("[LLM] Request rejected: worker thread creation failed\n");
        return -1;
    }

    return 0;
}

int llm_is_enabled(void) {
    return g_llm_config.enabled;
}

/* called each frame from the game loop: check for completed jobs */
extern void llm_hook_apply_response(void *msg_data, const char *text);

void llm_tick_jobs(void) {
    if (!g_llm_config.enabled) return;

    SDL_LockMutex(g_llm_mutex);
    for (int i = 0; i < LLM_MAX_JOBS; i++) {
        LlmJob *job = g_llm_jobs[i];
        if (!job || !g_llm_threads[i]) continue;
        if (job->done == 0) continue; /* still running */

        /* job completed — apply response */
        if (job->done == 1 && job->response[0]) {
            if (g_pc_verbose)
                printf("[LLM] Response received: \"%.150s\"\n", job->response);
            llm_hook_apply_response(job->target_msg_data, job->response);
        } else {
            /* restore stock text / clear pending state, regardless of verbose */
            llm_hook_on_job_failed(job->target_msg_data);
            if (g_pc_verbose)
                printf("[LLM] Request failed (no response from provider)\n");
        }

        /* reclaim thread */
        SDL_UnlockMutex(g_llm_mutex);
        SDL_WaitThread(g_llm_threads[i], NULL);
        SDL_LockMutex(g_llm_mutex);

        free(job);
        g_llm_threads[i] = NULL;
        g_llm_jobs[i] = NULL;
    }
    SDL_UnlockMutex(g_llm_mutex);
}
