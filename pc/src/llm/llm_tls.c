/* llm_tls.c - HTTPS helper using OpenSSL (shared by all TLS providers) */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
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

#include <openssl/ssl.h>
#include <openssl/err.h>

extern int g_pc_verbose;

static int tls_initialized = 0;

int llm_tls_init(void) {
    if (tls_initialized) return 0;
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    tls_initialized = 1;
    return 0;
}

void llm_tls_shutdown(void) {
    /* nothing needed */
}

/* connect host:port via TLS, return SSL* or NULL. caller must SSL_free+close socket. */
typedef struct {
    SSL *ssl;
    SSL_CTX *ctx;
    int sock;
} LlmTlsConn;

static LlmTlsConn *llm_tls_connect(const char *host, int port, int timeout_ms) {
    struct sockaddr_in addr;
    struct hostent *he = gethostbyname(host);
    if (!he) {
        fprintf(stderr, "[LLM/TLS] DNS lookup failed for %s (err=%d)\n", host, sockerr);
        return NULL;
    }

    int sock = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "[LLM/TLS] socket() failed (err=%d)\n", sockerr);
        return NULL;
    }

#ifdef _WIN32
    DWORD to = timeout_ms;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&to, sizeof(to));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&to, sizeof(to));
#else
    struct timeval tv = { .tv_sec = timeout_ms / 1000,
                          .tv_usec = (timeout_ms % 1000) * 1000 };
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t)port);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "[LLM/TLS] connect to %s:%d failed (err=%d)\n", host, port, sockerr);
        close_sock(sock); return NULL;
    }

    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) { fprintf(stderr, "[LLM/TLS] SSL_CTX_new failed\n"); close_sock(sock); return NULL; }
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);

    SSL *ssl = SSL_new(ctx);
    if (!ssl) { fprintf(stderr, "[LLM/TLS] SSL_new failed\n"); SSL_CTX_free(ctx); close_sock(sock); return NULL; }
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, host);

    if (SSL_connect(ssl) <= 0) {
        fprintf(stderr, "[LLM/TLS] TLS handshake with %s:%d failed: %s\n",
                host, port, ERR_error_string(ERR_get_error(), NULL));
        SSL_free(ssl); SSL_CTX_free(ctx); close_sock(sock); return NULL;
    }

    LlmTlsConn *conn = malloc(sizeof(LlmTlsConn));
    conn->ssl = ssl;
    conn->ctx = ctx;
    conn->sock = sock;
    return conn;
}

static void llm_tls_disconnect(LlmTlsConn *conn) {
    if (!conn) return;
    SSL_shutdown(conn->ssl);
    SSL_free(conn->ssl);
    SSL_CTX_free(conn->ctx);
    close_sock(conn->sock);
    free(conn);
}

int llm_tls_post(const char *host, int port, const char *path,
                  const char *body, char *response, int response_sz,
                  int timeout_ms) {
    llm_tls_init();
    LlmTlsConn *conn = llm_tls_connect(host, port, timeout_ms);
    if (!conn) return -1;

    /* build HTTP request */
    char req[16384];
    snprintf(req, sizeof(req),
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        path, host, (int)strlen(body), body);

    int req_len = (int)strlen(req);
    if (g_pc_verbose)
        printf("[LLM/TLS] -> %s:%d POST %s (%d bytes)\n", host, port, path, req_len);

    SSL_write(conn->ssl, req, req_len);

    /* read response */
    int total = 0, n;
    while ((n = SSL_read(conn->ssl, response + total, response_sz - total - 1)) > 0) {
        total += n;
        if (total >= response_sz - 1) break;
    }
    response[total] = '\0';

    /* extract body (after \r\n\r\n) */
    char *body_start = strstr(response, "\r\n\r\n");
    if (body_start) {
        body_start += 4;
        int blen = (int)strlen(body_start);
        memmove(response, body_start, blen + 1);
    }

    if (g_pc_verbose)
        printf("[LLM/TLS] <- %d bytes\n", total);

    llm_tls_disconnect(conn);
    return total > 0 ? 0 : -1;
}

int llm_tls_post_raw(const char *host, int port, const char *request,
                      char *response, int response_sz, int timeout_ms) {
    llm_tls_init();
    LlmTlsConn *conn = llm_tls_connect(host, port, timeout_ms);
    if (!conn) return -1;

    int req_len = (int)strlen(request);
    if (g_pc_verbose)
        printf("[LLM/TLS] -> %s:%d POST (raw, %d bytes)\n", host, port, req_len);

    SSL_write(conn->ssl, request, req_len);

    int total = 0, n;
    while ((n = SSL_read(conn->ssl, response + total, response_sz - total - 1)) > 0) {
        total += n;
        if (total >= response_sz - 1) break;
    }
    response[total] = '\0';

    char *body_start = strstr(response, "\r\n\r\n");
    if (body_start) {
        body_start += 4;
        int blen = (int)strlen(body_start);
        memmove(response, body_start, blen + 1);
    }

    if (g_pc_verbose)
        printf("[LLM/TLS] <- %d bytes\n", total);

    llm_tls_disconnect(conn);
    return total > 0 ? 0 : -1;
}
