/* llm_util.c - minimal JSON helpers, no external deps */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

char *llm_json_escape(const char *src) {
    static char buf[4096];
    int j = 0;
    for (const char *p = src; *p && j < (int)sizeof(buf) - 2; p++) {
        switch (*p) {
            case '"':  buf[j++] = '\\'; buf[j++] = '"';  break;
            case '\\': buf[j++] = '\\'; buf[j++] = '\\'; break;
            case '\n': buf[j++] = '\\'; buf[j++] = 'n';  break;
            case '\r': buf[j++] = '\\'; buf[j++] = 'r';  break;
            case '\t': buf[j++] = '\\'; buf[j++] = 't';  break;
            default:   buf[j++] = *p; break;
        }
    }
    buf[j] = '\0';
    return buf;
}

void llm_json_build_kv(char *buf, int bufsz, const char *key, const char *val) {
    int off = (int)strlen(buf);
    if (off > 0) {
        snprintf(buf + off, bufsz - off, ",\"%s\":\"%s\"", key, val);
    } else {
        snprintf(buf, bufsz, "\"%s\":\"%s\"", key, val);
    }
}

int llm_json_parse_str(const char *json, const char *key, char *out, int outsz) {
    char search[64];
    snprintf(search, sizeof(search), "\"%s\":\"", key);
    const char *p = strstr(json, search);
    if (!p) return -1;
    p += strlen(search);
    int i = 0;
    while (*p && *p != '"' && i < outsz - 1) {
        if (*p == '\\' && p[1]) { p++; out[i++] = *p++; }
        else { out[i++] = *p++; }
    }
    out[i] = '\0';
    return 0;
}
