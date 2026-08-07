/* llm_provider_ollama.c - Ollama HTTP provider (POSIX sockets, no TLS) */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include "llm/llm_types.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#define sockerr WSAGetLastError()
#define close_sock closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#define sockerr errno
#define close_sock close
#endif

extern int g_pc_verbose;

static char g_host[128];
static int  g_port = 11434;

static int ollama_init(const LlmConfig *cfg) {
    const char *ep = cfg->endpoint;
    /* parse http://host:port/... */
    const char *p = strstr(ep, "://");
    if (p) ep = p + 3;
    const char *slash = strchr(ep, '/');
    char hostpart[128];
    if (slash) {
        int len = (int)(slash - ep);
        if (len > 127) len = 127;
        memcpy(hostpart, ep, len);
        hostpart[len] = '\0';
    } else {
        strncpy(hostpart, ep, sizeof(hostpart)-1);
    }
    /* split host:port */
    char *colon = strchr(hostpart, ':');
    if (colon) {
        *colon = '\0';
        g_port = atoi(colon + 1);
    } else {
        g_port = 11434;
    }
    strncpy(g_host, hostpart, sizeof(g_host)-1);

    printf("[LLM/Ollama] Using %s:%d\n", g_host, g_port);
    return 0;
}

static void ollama_query(const char *prompt, LlmCallback cb, void *userdata) {
    char body[16384];
    char escaped[8192];
    llm_json_escape(escaped, sizeof(escaped), prompt);

    snprintf(body, sizeof(body),
        "{\"model\":\"%s\",\"prompt\":\"%s\",\"stream\":false,"
        "\"options\":{\"num_predict\":%d,\"temperature\":%.2f}}",
        g_llm_config.model, escaped, g_llm_config.max_tokens, g_llm_config.temperature);

    char request[20480];
    snprintf(request, sizeof(request),
        "POST /api/generate HTTP/1.1\r\n"
        "Host: %s:%d\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        g_host, g_port, (int)strlen(body), body);

    /* connect and send */
    struct sockaddr_in addr;
    struct hostent *he = gethostbyname(g_host);
    if (!he) { if (cb) cb(NULL, -1, userdata); return; }

    int sock = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { if (cb) cb(NULL, -1, userdata); return; }

    /* set timeout */
#ifdef _WIN32
    DWORD to = g_llm_config.timeout_ms;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&to, sizeof(to));
#else
    struct timeval tv = { .tv_sec = g_llm_config.timeout_ms / 1000,
                          .tv_usec = (g_llm_config.timeout_ms % 1000) * 1000 };
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)g_port);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close_sock(sock); if (cb) cb(NULL, -1, userdata); return;
    }
    if (g_pc_verbose)
        printf("[LLM/Ollama] -> %s:%d (%d bytes)\n", g_host, g_port, (int)strlen(request));
    if (send(sock, request, (int)strlen(request), 0) < 0) {
        close_sock(sock); if (cb) cb(NULL, -1, userdata); return;
    }

    /* read response */
    char buf[8192] = {0};
    int total = 0;
    int n;
    while ((n = (int)recv(sock, buf + total, sizeof(buf) - total - 1, 0)) > 0) {
        total += n;
    }
    close_sock(sock);

    if (g_pc_verbose)
        printf("[LLM/Ollama] <- %d bytes\n", total);

    if (total <= 0) { if (cb) cb(NULL, -1, userdata); return; }
    buf[total] = '\0';

    /* extract "response" field */
    char parsed[2048] = {0};
    llm_json_parse_str(buf, "response", parsed, sizeof(parsed));
    if (parsed[0]) {
        if (cb) cb(parsed, 0, userdata);
    } else {
        if (cb) cb(NULL, -1, userdata);
    }
}

static void ollama_shutdown(void) {}

LlmProvider llm_provider_ollama = {
    .name = "ollama",
    .init = ollama_init,
    .query = ollama_query,
    .shutdown = ollama_shutdown,
    .context_limit = 4096,
};
