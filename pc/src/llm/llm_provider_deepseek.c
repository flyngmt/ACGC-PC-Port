/* llm_provider_deepseek.c - DeepSeek API (OpenAI-compatible) */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

extern int llm_tls_post_raw(const char *host, int port,
                              const char *request, char *response, int response_sz,
                              int timeout_ms);

static char g_ds_host[128];

static int deepseek_init(const LlmConfig *cfg) {
    const char *ep = cfg->endpoint;
    const char *p = strstr(ep, "://");
    if (p) ep = p + 3;
    const char *slash = strchr(ep, '/');
    if (slash) {
        int len = (int)(slash - ep);
        if (len > 127) len = 127;
        memcpy(g_ds_host, ep, len);
        g_ds_host[len] = '\0';
    } else {
        strncpy(g_ds_host, ep, sizeof(g_ds_host)-1);
    }
    printf("[LLM/DeepSeek] host=%s model=%s\n", g_ds_host, cfg->model);
    return 0;
}

static void deepseek_query(const char *prompt, LlmCallback cb, void *userdata) {
    char body[16384];
    char escaped[8192];
    llm_json_escape(escaped, sizeof(escaped), prompt);

    snprintf(body, sizeof(body),
        "{"
        "\"model\":\"%s\","
        "\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}],"
        "\"max_tokens\":%d,"
        "\"temperature\":%.2f,"
        "\"stream\":false"
        "}",
        g_llm_config.model, escaped,
        g_llm_config.max_tokens, g_llm_config.temperature);

    int body_len = (int)strlen(body);
    char full_req[32768];
    snprintf(full_req, sizeof(full_req),
        "POST /v1/chat/completions HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Authorization: Bearer %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        g_ds_host, g_llm_config.api_key, body_len, body);

    char response[32768] = {0};
    int rc = llm_tls_post_raw(g_ds_host, 443, full_req, response, sizeof(response),
                               g_llm_config.timeout_ms);

    if (rc != 0) { if (cb) cb(NULL, -1, userdata); return; }

    /* extract content from choices[0].message.content (same as OpenAI) */
    char text[4096] = {0};
    const char *p = strstr(response, "\"content\":\"");
    if (!p) p = strstr(response, "\"content\": \"");
    if (p) {
        p = strchr(p, '"') + 1;
        if (*p == '"') p++;
        if (*p == ' ') { p++; if (*p == '"') p++; }
        int i = 0;
        while (*p && i < (int)sizeof(text) - 1) {
            if (*p == '\\' && p[1] == '"') { p++; text[i++] = *p++; }
            else if (*p == '\\' && p[1] == 'n') { p++; text[i++] = '\n'; p++; }
            else if (*p == '\\' && p[1] == '\\') { p++; text[i++] = '\\'; p++; }
            else if (*p == '"') break;
            else { text[i++] = *p++; }
        }
        text[i] = '\0';
    }
    if (text[0]) { if (cb) cb(text, 0, userdata); }
    else { if (cb) cb(NULL, -1, userdata); }
}

static void deepseek_shutdown(void) {}

LlmProvider llm_provider_deepseek = {
    .name = "deepseek",
    .init = deepseek_init,
    .query = deepseek_query,
    .shutdown = deepseek_shutdown,
    .context_limit = 8192,
};
