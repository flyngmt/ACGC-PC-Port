/* llm_provider_openai.c - OpenAI/OpenCode Zen compatible API via HTTPS */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

extern int llm_tls_post(const char *host, int port, const char *path,
                         const char *body, char *response, int response_sz,
                         int timeout_ms);

static char g_openai_host[128];
static char g_openai_path[256];

static int openai_init(const LlmConfig *cfg) {
    /* parse host from endpoint URL */
    const char *ep = cfg->endpoint;
    const char *p = strstr(ep, "://");
    if (p) ep = p + 3;
    const char *slash = strchr(ep, '/');
    if (slash) {
        int len = (int)(slash - ep);
        if (len > 127) len = 127;
        memcpy(g_openai_host, ep, len);
        g_openai_host[len] = '\0';
        snprintf(g_openai_path, sizeof(g_openai_path), "%s", slash);
        if (!strstr(g_openai_path, "chat/completions"))
            snprintf(g_openai_path, sizeof(g_openai_path), "%s/chat/completions", slash);
    } else {
        strncpy(g_openai_host, ep, sizeof(g_openai_host)-1);
        strcpy(g_openai_path, "/v1/chat/completions");
    }
    if (!cfg->api_key[0] && strstr(g_openai_host, "api.openai.com"))
        fprintf(stderr, "[LLM/OpenAI] No API key configured\n");
    printf("[LLM/OpenAI] host=%s model=%s\n", g_openai_host, cfg->model);
    return 0;
}

static void openai_query(const char *prompt, LlmCallback cb, void *userdata) {
    char body[16384];
    char *esc = llm_json_escape(prompt);

    snprintf(body, sizeof(body),
        "{"
        "\"model\":\"%s\","
        "\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}],"
        "\"max_tokens\":%d,"
        "\"temperature\":%.2f"
        "}",
        g_llm_config.model, esc,
        g_llm_config.max_tokens, g_llm_config.temperature);

    char request_headers[17408];
    int body_len = (int)strlen(body);
    snprintf(request_headers, sizeof(request_headers),
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Authorization: Bearer %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        g_openai_path, g_openai_host, g_llm_config.api_key,
        body_len, body);

    /* llm_tls_post builds its own HTTP, so we need a raw-send version */
    /* ponytail: use llm_tls_raw helper instead */
    char response[32768] = {0};
    /* send body as raw POST body via TLS */
    /* For now, use the full request as body to a raw endpoint */
    int port = 443;
    char path[1024];
    snprintf(path, sizeof(path), "%s", g_openai_path);

    /* build full request including auth header */
    char full_req[32768];
    snprintf(full_req, sizeof(full_req),
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Authorization: Bearer %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        path, g_openai_host, g_llm_config.api_key, body_len, body);

    /* use raw socket + TLS */
    extern int llm_tls_post_raw(const char *host, int port,
                                 const char *request, char *response, int response_sz,
                                 int timeout_ms);
    int rc = llm_tls_post_raw(g_openai_host, port, full_req, response, sizeof(response),
                               g_llm_config.timeout_ms);

    if (rc != 0) { if (cb) cb(NULL, -1, userdata); return; }

    /* extract assistant message text */
    char text[4096] = {0};

    /* Try content first */
    const char *p = strstr(response, "\"content\":\"");
    if (p) {
        p += 11;
        int i = 0;
        while (*p && *p != '"' && i < (int)sizeof(text) - 1) {
            if (*p == '\\') { p++; if (*p) text[i++] = *p++; }
            else { text[i++] = *p++; }
        }
        text[i] = '\0';
    }

    /* If empty, fall back to reasoning_content (DeepSeek V4) */
    if (!text[0]) {
        p = strstr(response, "\"reasoning_content\":\"");
        if (p) {
            p += 22;
            int i = 0;
            while (*p && *p != '"' && i < (int)sizeof(text) - 1) {
                if (*p == '\\') { p++; if (*p) text[i++] = *p++; }
                else { text[i++] = *p++; }
            }
            text[i] = '\0';
        }
    }

#ifdef PC_DEBUG_MSG
    if (!text[0]) printf("[DBG-LLM/OpenAI] raw=%s\n", response);
#endif
    if (text[0]) { if (cb) cb(text, 0, userdata); }
    else { if (cb) cb(NULL, -1, userdata); }
}

static void openai_shutdown(void) {}

LlmProvider llm_provider_openai = {
    .name = "openai",
    .init = openai_init,
    .query = openai_query,
    .shutdown = openai_shutdown,
    .context_limit = 8192,
};
