/* llm_util.c - minimal JSON helpers, no external deps */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

char *llm_json_escape(char *dst, int dstsz, const char *src) {
    int j = 0;
    for (const char *p = src; *p && j < dstsz - 2; p++) {
        switch (*p) {
            case '"':  dst[j++] = '\\'; dst[j++] = '"';  break;
            case '\\': dst[j++] = '\\'; dst[j++] = '\\'; break;
            case '\n': dst[j++] = '\\'; dst[j++] = 'n';  break;
            case '\r': dst[j++] = '\\'; dst[j++] = 'r';  break;
            case '\t': dst[j++] = '\\'; dst[j++] = 't';  break;
            default:   dst[j++] = *p; break;
        }
    }
    dst[j] = '\0';
    return dst;
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
