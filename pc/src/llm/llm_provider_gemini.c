/* llm_provider_gemini.c - Gemini API via HTTPS */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

extern int llm_tls_post(const char *host, int port, const char *path,
                         const char *body, char *response, int response_sz,
                         int timeout_ms);

static void gemini_query(const char *prompt, LlmCallback cb, void *userdata) {
    char body[16384];
    char escaped[8192];
    llm_json_escape(escaped, sizeof(escaped), prompt);

    /* Gemini generateContent API */
    snprintf(body, sizeof(body),
        "{"
        "\"contents\":[{\"parts\":[{\"text\":\"%s\"}]}],"
        "\"generationConfig\":{"
          "\"maxOutputTokens\":%d,"
          "\"temperature\":%.2f"
        "}"
        "}",
        escaped, g_llm_config.max_tokens, g_llm_config.temperature);

    char path[1024];
    snprintf(path, sizeof(path),
        "/v1beta/models/%s:generateContent?key=%s",
        g_llm_config.model, g_llm_config.api_key);

    char response[32768] = {0};
    int rc = llm_tls_post("generativelanguage.googleapis.com", 443,
                           path, body, response, sizeof(response),
                           g_llm_config.timeout_ms);

    if (rc != 0) { if (cb) cb(NULL, -1, userdata); return; }

    /* extract "text" from candidates[0].content.parts[0].text */
    char text[4096] = {0};
    const char *p = strstr(response, "\"text\":");
    if (p) {
        /* value is the first quoted string after the key's colon */
        p = strchr(p, ':');
        p = strchr(p + 1, '"');
        if (p) {
            p++;
            int i = 0;
            while (*p && *p != '"' && i < (int)sizeof(text) - 1) {
                if (*p == '\\' && p[1]) { p++; text[i++] = *p++; }
                else { text[i++] = *p++; }
            }
            text[i] = '\0';
        }
    }
    if (text[0]) { if (cb) cb(text, 0, userdata); }
    else { if (cb) cb(NULL, -1, userdata); }
}

static int gemini_init(const LlmConfig *cfg) {
    if (!cfg->api_key[0]) {
        fprintf(stderr, "[LLM/Gemini] No API key configured\n");
        return -1;
    }
    printf("[LLM/Gemini] model=%s key=%s...\n",
           cfg->model, cfg->api_key[0] ? "yes" : "no");
    return 0;
}

static void gemini_shutdown(void) {}

LlmProvider llm_provider_gemini = {
    .name = "gemini",
    .init = gemini_init,
    .query = gemini_query,
    .shutdown = gemini_shutdown,
    .context_limit = 32000,
};
