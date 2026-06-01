/* pc_texture_pack.c - Dolphin-compatible HD texture pack loader
 *
 * Filename: tex1_{W}x{H}_{hash}[_{tlut_hash}]_{fmt}.dds
 * Hashes match Dolphin's XXHash64 (seed=0). CI textures use min/max palette
 * index scan for TLUT hash (only used entries, in BE byte order).
 * DDS: BC7, BC1/DXT1, BC3/DXT5, or uncompressed RGBA. */
#include "pc_texture_pack.h"
#include "pc_gx_internal.h"
#include "pc_settings.h"
#include "pc_bc7.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- XXHash64 (seed=0, matches Dolphin's GetHash64) --- */

typedef unsigned long long xxh_u64;
typedef unsigned int xxh_u32;

#define XXH_PRIME64_1 0x9E3779B185EBCA87ULL
#define XXH_PRIME64_2 0xC2B2AE3D27D4EB4FULL
#define XXH_PRIME64_3 0x165667B19E3779F9ULL
#define XXH_PRIME64_4 0x85EBCA77C2B2AE63ULL
#define XXH_PRIME64_5 0x27D4EB2F165667C5ULL

static inline xxh_u64 xxh_read64(const void* p) {
    xxh_u64 val;
    memcpy(&val, p, 8);
    return val; /* LE platform = native read */
}

static inline xxh_u32 xxh_read32(const void* p) {
    xxh_u32 val;
    memcpy(&val, p, 4);
    return val;
}

static inline xxh_u64 xxh_rotl64(xxh_u64 x, int r) {
    return (x << r) | (x >> (64 - r));
}

static inline xxh_u64 xxh_round(xxh_u64 acc, xxh_u64 input) {
    acc += input * XXH_PRIME64_2;
    acc = xxh_rotl64(acc, 31);
    acc *= XXH_PRIME64_1;
    return acc;
}

static inline xxh_u64 xxh_merge_round(xxh_u64 acc, xxh_u64 val) {
    val = xxh_round(0, val);
    acc ^= val;
    acc = acc * XXH_PRIME64_1 + XXH_PRIME64_4;
    return acc;
}

static xxh_u64 xxhash64(const void* input, int len) {
    const unsigned char* p = (const unsigned char*)input;
    const unsigned char* end = p + len;
    xxh_u64 h64;

    if (len >= 32) {
        const unsigned char* limit = end - 32;
        xxh_u64 v1 = 0 + XXH_PRIME64_1 + XXH_PRIME64_2; /* seed=0 */
        xxh_u64 v2 = 0 + XXH_PRIME64_2;
        xxh_u64 v3 = 0;
        xxh_u64 v4 = 0 - XXH_PRIME64_1;

        do {
            v1 = xxh_round(v1, xxh_read64(p));      p += 8;
            v2 = xxh_round(v2, xxh_read64(p));      p += 8;
            v3 = xxh_round(v3, xxh_read64(p));      p += 8;
            v4 = xxh_round(v4, xxh_read64(p));      p += 8;
        } while (p <= limit);

        h64 = xxh_rotl64(v1, 1) + xxh_rotl64(v2, 7) +
              xxh_rotl64(v3, 12) + xxh_rotl64(v4, 18);
        h64 = xxh_merge_round(h64, v1);
        h64 = xxh_merge_round(h64, v2);
        h64 = xxh_merge_round(h64, v3);
        h64 = xxh_merge_round(h64, v4);
    } else {
        h64 = 0 + XXH_PRIME64_5; /* seed + PRIME5 */
    }

    h64 += (xxh_u64)len;

    /* Remaining 8-byte chunks */
    while (p + 8 <= end) {
        xxh_u64 k1 = xxh_round(0, xxh_read64(p));
        h64 ^= k1;
        h64 = xxh_rotl64(h64, 27) * XXH_PRIME64_1 + XXH_PRIME64_4;
        p += 8;
    }

    /* Remaining 4-byte chunk */
    if (p + 4 <= end) {
        h64 ^= (xxh_u64)xxh_read32(p) * XXH_PRIME64_1;
        h64 = xxh_rotl64(h64, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
        p += 4;
    }

    /* Remaining bytes */
    while (p < end) {
        h64 ^= (xxh_u64)(*p) * XXH_PRIME64_5;
        h64 = xxh_rotl64(h64, 11) * XXH_PRIME64_1;
        p++;
    }

    /* Avalanche */
    h64 ^= h64 >> 33;
    h64 *= XXH_PRIME64_2;
    h64 ^= h64 >> 29;
    h64 *= XXH_PRIME64_3;
    h64 ^= h64 >> 32;

    return h64;
}

/* --- DDS format constants --- */

#define DDS_MAGIC          0x20534444  /* "DDS " */
#define DDS_HEADER_SIZE    124
#define DDS_DX10_SIZE      20
#define DDPF_FOURCC        0x04

#define DXGI_FORMAT_R8G8B8A8_UNORM   28
#define DXGI_FORMAT_B8G8R8A8_UNORM   87
#define DXGI_FORMAT_BC1_UNORM        71
#define DXGI_FORMAT_BC3_UNORM        77
#define DXGI_FORMAT_BC7_UNORM        98

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3
#endif
#ifndef GL_COMPRESSED_RGBA_BPTC_UNORM
#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C
#endif

static int g_has_bc7 = 0;
static int g_has_s3tc = 0;

static int g_stat_lookups = 0;
static int g_stat_hits = 0;
static int g_stat_loaded = 0;
static int g_stat_cache_hits = 0;
static int g_stat_neg_hits = 0;

/* --- Texture pack file lookup table --- */
#define TEXPACK_MAP_BITS  15
#define TEXPACK_MAP_SIZE  (1 << TEXPACK_MAP_BITS)  /* 32768 */
#define TEXPACK_MAP_MASK  (TEXPACK_MAP_SIZE - 1)

typedef struct {
    xxh_u64 data_hash;
    xxh_u64 tlut_hash;
    xxh_u32 gc_fmt;
    xxh_u32 orig_w, orig_h;
    char    filepath[260];
    int     occupied;
} TexPackEntry;

static TexPackEntry* g_texpack_map = NULL;
static int g_texpack_count = 0;
static int g_texpack_active = 0;

/* Wildcard TLUT entries: tex1_WxH_DATAHASH_$_FMT.dds (matches any palette) */
#define TEXPACK_WC_BITS  14
#define TEXPACK_WC_SIZE  (1 << TEXPACK_WC_BITS)
#define TEXPACK_WC_MASK  (TEXPACK_WC_SIZE - 1)

typedef struct {
    xxh_u64 data_hash;
    xxh_u32 gc_fmt;
    xxh_u32 orig_w, orig_h;
    char    filepath[260];
    int     occupied;
} TexPackWildcardEntry;

static TexPackWildcardEntry* g_texpack_wc_map = NULL;

/* --- Hash map operations --- */

static xxh_u32 texpack_slot(xxh_u64 data_hash, xxh_u64 tlut_hash, xxh_u32 fmt,
                            xxh_u32 w, xxh_u32 h) {
    xxh_u64 combined = data_hash ^ (tlut_hash * 0x9E3779B97F4A7C15ULL);
    combined ^= ((xxh_u64)fmt * 0x517CC1B727220A95ULL);
    combined ^= ((xxh_u64)w * 0x6C62272E07BB0142ULL);
    combined ^= ((xxh_u64)h * 0x165667B19E3779F9ULL);
    return (xxh_u32)(combined & TEXPACK_MAP_MASK);
}

static xxh_u32 texpack_wc_slot(xxh_u64 data_hash, xxh_u32 fmt, xxh_u32 w, xxh_u32 h) {
    xxh_u64 combined = data_hash;
    combined ^= ((xxh_u64)fmt * 0x517CC1B727220A95ULL);
    combined ^= ((xxh_u64)w * 0x6C62272E07BB0142ULL);
    combined ^= ((xxh_u64)h * 0x165667B19E3779F9ULL);
    return (xxh_u32)(combined & TEXPACK_WC_MASK);
}

static void texpack_insert(xxh_u64 data_hash, xxh_u64 tlut_hash, xxh_u32 fmt,
                           xxh_u32 w, xxh_u32 h, const char* filepath) {
    if (!g_texpack_map) return;

    xxh_u32 slot = texpack_slot(data_hash, tlut_hash, fmt, w, h);
    for (int i = 0; i < TEXPACK_MAP_SIZE; i++) {
        xxh_u32 idx = (slot + i) & TEXPACK_MAP_MASK;
        if (!g_texpack_map[idx].occupied) {
            g_texpack_map[idx].data_hash = data_hash;
            g_texpack_map[idx].tlut_hash = tlut_hash;
            g_texpack_map[idx].gc_fmt = fmt;
            g_texpack_map[idx].orig_w = w;
            g_texpack_map[idx].orig_h = h;
            strncpy(g_texpack_map[idx].filepath, filepath, 259);
            g_texpack_map[idx].filepath[259] = '\0';
            g_texpack_map[idx].occupied = 1;
            g_texpack_count++;
            break;
        }
    }

}

static TexPackEntry* texpack_find(xxh_u64 data_hash, xxh_u64 tlut_hash, xxh_u32 fmt,
                                  xxh_u32 w, xxh_u32 h) {
    if (!g_texpack_map || g_texpack_count == 0) return NULL;
    xxh_u32 slot = texpack_slot(data_hash, tlut_hash, fmt, w, h);
    for (int i = 0; i < TEXPACK_MAP_SIZE; i++) {
        xxh_u32 idx = (slot + i) & TEXPACK_MAP_MASK;
        if (!g_texpack_map[idx].occupied) return NULL;
        if (g_texpack_map[idx].data_hash == data_hash &&
            g_texpack_map[idx].tlut_hash == tlut_hash &&
            g_texpack_map[idx].gc_fmt == fmt &&
            g_texpack_map[idx].orig_w == w &&
            g_texpack_map[idx].orig_h == h) {
            return &g_texpack_map[idx];
        }
    }
    return NULL;
}

static void texpack_insert_wildcard(xxh_u64 data_hash, xxh_u32 fmt,
                                    xxh_u32 w, xxh_u32 h, const char* filepath) {
    if (!g_texpack_wc_map) return;
    xxh_u32 slot = texpack_wc_slot(data_hash, fmt, w, h);
    for (int i = 0; i < TEXPACK_WC_SIZE; i++) {
        xxh_u32 idx = (slot + i) & TEXPACK_WC_MASK;
        if (!g_texpack_wc_map[idx].occupied) {
            g_texpack_wc_map[idx].data_hash = data_hash;
            g_texpack_wc_map[idx].gc_fmt = fmt;
            g_texpack_wc_map[idx].orig_w = w;
            g_texpack_wc_map[idx].orig_h = h;
            strncpy(g_texpack_wc_map[idx].filepath, filepath, 259);
            g_texpack_wc_map[idx].filepath[259] = '\0';
            g_texpack_wc_map[idx].occupied = 1;
            g_texpack_count++;
            break;
        }
    }
}

static TexPackWildcardEntry* texpack_find_wildcard(xxh_u64 data_hash, xxh_u32 fmt,
                                                   xxh_u32 w, xxh_u32 h) {
    if (!g_texpack_wc_map || g_texpack_count == 0) return NULL;
    xxh_u32 slot = texpack_wc_slot(data_hash, fmt, w, h);
    for (int i = 0; i < TEXPACK_WC_SIZE; i++) {
        xxh_u32 idx = (slot + i) & TEXPACK_WC_MASK;
        if (!g_texpack_wc_map[idx].occupied) return NULL;
        if (g_texpack_wc_map[idx].data_hash == data_hash &&
            g_texpack_wc_map[idx].gc_fmt == fmt &&
            g_texpack_wc_map[idx].orig_w == w &&
            g_texpack_wc_map[idx].orig_h == h) {
            return &g_texpack_wc_map[idx];
        }
    }
    return NULL;
}

/* --- Filename parser --- */

static int parse_hex64(const char* s, xxh_u64* out) {
    *out = 0;
    for (int i = 0; i < 16; i++) {
        char c = s[i];
        xxh_u64 nibble;
        if (c >= '0' && c <= '9')      nibble = c - '0';
        else if (c >= 'a' && c <= 'f')  nibble = 10 + c - 'a';
        else if (c >= 'A' && c <= 'F')  nibble = 10 + c - 'A';
        else return 0;
        *out = (*out << 4) | nibble;
    }
    return 1;
}

static int parse_texpack_filename(const char* name, xxh_u32* w, xxh_u32* h,
                                  xxh_u64* data_hash, xxh_u64* tlut_hash, int* tlut_wildcard,
                                  xxh_u32* fmt) {
    if (strncmp(name, "tex1_", 5) != 0) return 0;
    const char* p = name + 5;

    char* end_w;
    unsigned long pw = strtoul(p, &end_w, 10);
    if (*end_w != 'x') return 0;
    char* end_h;
    unsigned long ph = strtoul(end_w + 1, &end_h, 10);
    if (*end_h != '_') return 0;
    *w = (xxh_u32)pw;
    *h = (xxh_u32)ph;
    p = end_h + 1;

    const char* parts[4];
    int part_count = 0;
    parts[part_count++] = p;
    while (*p && part_count < 4) {
        if (*p == '_') {
            parts[part_count++] = p + 1;
        }
        if (*p == '.') break;
        p++;
    }

    if (part_count == 2) {
        if (!parse_hex64(parts[0], data_hash)) return 0;
        *tlut_hash = 0;
        *tlut_wildcard = 0;
        *fmt = (xxh_u32)strtoul(parts[1], NULL, 10);
    } else if (part_count == 3) {
        if (!parse_hex64(parts[0], data_hash)) return 0;
        if (parts[1][0] == '$') {
            *tlut_hash = 0;
            *tlut_wildcard = 1;
        } else {
            if (!parse_hex64(parts[1], tlut_hash)) return 0;
            *tlut_wildcard = 0;
        }
        *fmt = (xxh_u32)strtoul(parts[2], NULL, 10);
    } else {
        return 0;
    }

    return 1;
}

/* --- Directory scanner --- */

#ifdef _WIN32
#include <windows.h>
#undef near
#undef far

static void scan_directory(const char* dir_path) {
    char search_path[300];
    snprintf(search_path, sizeof(search_path), "%s\\*", dir_path);

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(search_path, &fd);
    if (h == INVALID_HANDLE_VALUE) return;

    do {
        if (fd.cFileName[0] == '.') continue;

        char full_path[300];
        snprintf(full_path, sizeof(full_path), "%s\\%s", dir_path, fd.cFileName);

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            scan_directory(full_path);
        } else {
            int len = (int)strlen(fd.cFileName);
            if (len > 4 && strcmp(fd.cFileName + len - 4, ".dds") == 0) {
                xxh_u32 w, h_val, fmt;
                xxh_u64 data_hash, tlut_hash;
                int tlut_wildcard = 0;
                if (parse_texpack_filename(fd.cFileName, &w, &h_val, &data_hash, &tlut_hash,
                                           &tlut_wildcard, &fmt)) {
                    if (tlut_wildcard) {
                        texpack_insert_wildcard(data_hash, fmt, w, h_val, full_path);
                    } else {
                        texpack_insert(data_hash, tlut_hash, fmt, w, h_val, full_path);
                    }
                }
            }
        }
    } while (FindNextFileA(h, &fd));

    FindClose(h);
}

#else
#include <dirent.h>
#include <sys/stat.h>

static void scan_directory(const char* dir_path) {
    DIR* d = opendir(dir_path);
    if (!d) return;

    struct dirent* ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        char full_path[300];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, ent->d_name);

        struct stat st;
        if (stat(full_path, &st) != 0) continue;

        if (S_ISDIR(st.st_mode)) {
            scan_directory(full_path);
        } else {
            int len = (int)strlen(ent->d_name);
            if (len > 4 && strcmp(ent->d_name + len - 4, ".dds") == 0) {
                xxh_u32 w, h_val, fmt;
                xxh_u64 data_hash, tlut_hash;
                int tlut_wildcard = 0;
                if (parse_texpack_filename(ent->d_name, &w, &h_val, &data_hash, &tlut_hash,
                                           &tlut_wildcard, &fmt)) {
                    if (tlut_wildcard) {
                        texpack_insert_wildcard(data_hash, fmt, w, h_val, full_path);
                    } else {
                        texpack_insert(data_hash, tlut_hash, fmt, w, h_val, full_path);
                    }
                }
            }
        }
    }
    closedir(d);
}
#endif

/* --- DDS file loader --- */

static GLuint load_dds_file(const char* filepath, int* out_w, int* out_h) {
    FILE* f = fopen(filepath, "rb");
    if (!f) return 0;

    unsigned char header[148];
    if (fread(header, 1, 128, f) != 128) { fclose(f); return 0; }

    xxh_u32 magic;
    memcpy(&magic, header, 4);
    if (magic != DDS_MAGIC) { fclose(f); return 0; }

    xxh_u32 dds_height, dds_width;
    memcpy(&dds_height, header + 12, 4);
    memcpy(&dds_width, header + 16, 4);

    xxh_u32 pf_flags, pf_fourcc;
    memcpy(&pf_flags, header + 80, 4);
    memcpy(&pf_fourcc, header + 84, 4);

    xxh_u32 dxgi_format = 0;
    GLenum gl_internal = 0;
    int compressed = 0;
    int block_size = 0;

    if ((pf_flags & DDPF_FOURCC) && pf_fourcc == 0x30315844) {
        /* "DX10" FourCC — read extended header */
        if (fread(header + 128, 1, 20, f) != 20) { fclose(f); return 0; }
        memcpy(&dxgi_format, header + 128, 4);

        switch (dxgi_format) {
            case DXGI_FORMAT_BC7_UNORM:
                gl_internal = GL_COMPRESSED_RGBA_BPTC_UNORM;
                compressed = 1;
                block_size = 16;
                break;
            case DXGI_FORMAT_BC1_UNORM:
                if (!g_has_s3tc) { fclose(f); return 0; }
                gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                compressed = 1;
                block_size = 8;
                break;
            case DXGI_FORMAT_BC3_UNORM:
                if (!g_has_s3tc) { fclose(f); return 0; }
                gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                compressed = 1;
                block_size = 16;
                break;
            case DXGI_FORMAT_R8G8B8A8_UNORM:
            case DXGI_FORMAT_B8G8R8A8_UNORM:
                gl_internal = GL_RGBA;
                compressed = 0;
                break;
            default:
                fclose(f);
                return 0;
        }
    } else if ((pf_flags & DDPF_FOURCC)) {
        /* Legacy FourCC (DXT1, DXT3, DXT5) */
        if (pf_fourcc == 0x31545844) { /* "DXT1" */
            if (!g_has_s3tc) { fclose(f); return 0; }
            gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            compressed = 1;
            block_size = 8;
        } else if (pf_fourcc == 0x35545844) { /* "DXT5" */
            if (!g_has_s3tc) { fclose(f); return 0; }
            gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            compressed = 1;
            block_size = 16;
        } else {
            fclose(f);
            return 0;
        }
    } else {
        /* Uncompressed — check for 32-bit RGBA by bit counts */
        xxh_u32 rgb_bit_count;
        memcpy(&rgb_bit_count, header + 88, 4);
        if (rgb_bit_count == 32) {
            gl_internal = GL_RGBA;
            compressed = 0;
        } else {
            fclose(f);
            return 0;
        }
    }

    int data_size;
    if (compressed) {
        int blocks_x = ((int)dds_width + 3) / 4;
        int blocks_y = ((int)dds_height + 3) / 4;
        data_size = blocks_x * blocks_y * block_size;
    } else {
        data_size = (int)(dds_width * dds_height * 4);
    }

    unsigned char* pixels = (unsigned char*)malloc(data_size);
    if (!pixels) { fclose(f); return 0; }
    if ((int)fread(pixels, 1, data_size, f) != data_size) {
        free(pixels);
        fclose(f);
        return 0;
    }
    fclose(f);

    /* BGRA→RGBA swap if needed */
    if (!compressed && dxgi_format == DXGI_FORMAT_B8G8R8A8_UNORM) {
        for (int i = 0; i < data_size; i += 4) {
            unsigned char tmp = pixels[i];
            pixels[i] = pixels[i + 2];
            pixels[i + 2] = tmp;
        }
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    if (compressed && gl_internal == GL_COMPRESSED_RGBA_BPTC_UNORM && !g_has_bc7) {
        // macOS OpenGL doesn't support BC7, so it has to be decoded to RGBA
        int num_pixels = (int)(dds_width * dds_height);
        unsigned char* rgba = (unsigned char*)malloc(num_pixels * 4);
        if (!rgba) { free(pixels); fclose(f); glDeleteTextures(1, &tex); return 0; }
        int blocks_x = ((int)dds_width  + 3) / 4;
        int blocks_y = ((int)dds_height + 3) / 4;
        for (int by = 0; by < blocks_y; by++) {
            for (int bx = 0; bx < blocks_x; bx++) {
                const unsigned char* block = pixels + (by * blocks_x + bx) * 16;
                unsigned char decoded[64];
                pc_bc7_decomp_block(block, decoded);
                int bw = ((int)dds_width  - bx * 4) < 4 ? (int)dds_width  - bx * 4 : 4;
                int bh = ((int)dds_height - by * 4) < 4 ? (int)dds_height - by * 4 : 4;
                for (int py = 0; py < bh; py++) {
                    for (int px = 0; px < bw; px++) {
                        int dst = ((by * 4 + py) * (int)dds_width + (bx * 4 + px)) * 4;
                        int src = (py * 4 + px) * 4;
                        rgba[dst+0] = decoded[src+0];
                        rgba[dst+1] = decoded[src+1];
                        rgba[dst+2] = decoded[src+2];
                        rgba[dst+3] = decoded[src+3];
                    }
                }
            }
        }
        free(pixels);
        pixels = rgba;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)dds_width, (GLsizei)dds_height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else if (compressed) {
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, gl_internal,
                               (GLsizei)dds_width, (GLsizei)dds_height,
                               0, data_size, pixels);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)dds_width, (GLsizei)dds_height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        fprintf(stderr, "[TexturePack] GL error 0x%X uploading %s\n", err, filepath);
        glDeleteTextures(1, &tex);
        free(pixels);
        return 0;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(pixels);

    if (out_w) *out_w = (int)dds_width;
    if (out_h) *out_h = (int)dds_height;

    return tex;
}

/* --- GC texture block-aligned data size (for hash input) --- */

static int gc_texture_data_size(int w, int h, unsigned int fmt) {
    int bw, bh, block_bytes;
    switch (fmt) {
        case 0:  /* GX_TF_I4 */
        case 8:  /* GX_TF_C4 */
            bw = 8; bh = 8; block_bytes = 32; break;
        case 14: /* GX_TF_CMPR */
            bw = 8; bh = 8; block_bytes = 32; break;
        case 1:  /* GX_TF_I8 */
        case 2:  /* GX_TF_IA4 */
        case 9:  /* GX_TF_C8 */
            bw = 8; bh = 4; block_bytes = 32; break;
        case 3:  /* GX_TF_IA8 */
        case 4:  /* GX_TF_RGB565 */
        case 5:  /* GX_TF_RGB5A3 */
            bw = 4; bh = 4; block_bytes = 32; break;
        case 6:  /* GX_TF_RGBA8 */
            bw = 4; bh = 4; block_bytes = 64; break;
        default:
            bw = 8; bh = 4; block_bytes = 32; break;
    }
    int blocks_x = (w + bw - 1) / bw;
    int blocks_y = (h + bh - 1) / bh;
    return blocks_x * blocks_y * block_bytes;
}

/* --- Loaded texture cache (GL ID, avoids re-reading DDS from disk) --- */
#define LOADED_CACHE_SIZE 32768
#define LOADED_CACHE_MASK (LOADED_CACHE_SIZE - 1)

typedef struct {
    xxh_u64 key;
    GLuint  gl_tex;
    int     tex_w, tex_h;
    int     occupied;
} LoadedCacheEntry;

static LoadedCacheEntry g_loaded_cache[LOADED_CACHE_SIZE];

static xxh_u64 loaded_cache_key(xxh_u64 data_hash, xxh_u64 tlut_hash, xxh_u32 fmt,
                                xxh_u32 w, xxh_u32 h) {
    xxh_u64 k = data_hash;
    k ^= tlut_hash * 0x517CC1B727220A95ULL;
    k ^= (xxh_u64)fmt * 0x6C62272E07BB0142ULL;
    k ^= (xxh_u64)w * 0x165667B19E3779F9ULL;
    k ^= (xxh_u64)h * 0x85EBCA77C2B2AE63ULL;
    return k;
}

static LoadedCacheEntry* loaded_cache_find(xxh_u64 key) {
    xxh_u32 slot = (xxh_u32)(key & LOADED_CACHE_MASK);
    for (int i = 0; i < LOADED_CACHE_SIZE; i++) {
        xxh_u32 idx = (slot + i) & LOADED_CACHE_MASK;
        if (!g_loaded_cache[idx].occupied) return NULL;
        if (g_loaded_cache[idx].key == key) return &g_loaded_cache[idx];
    }
    return NULL;
}

static void loaded_cache_insert(xxh_u64 key, GLuint tex, int w, int h) {
    xxh_u32 slot = (xxh_u32)(key & LOADED_CACHE_MASK);
    for (int i = 0; i < LOADED_CACHE_SIZE; i++) {
        xxh_u32 idx = (slot + i) & LOADED_CACHE_MASK;
        if (!g_loaded_cache[idx].occupied) {
            g_loaded_cache[idx].key = key;
            g_loaded_cache[idx].gl_tex = tex;
            g_loaded_cache[idx].tex_w = w;
            g_loaded_cache[idx].tex_h = h;
            g_loaded_cache[idx].occupied = 1;
            return;
        }
    }
}

/* --- Negative lookup cache (skip re-hashing textures with no pack match) --- */

#define NEG_CACHE_SIZE 2048
#define NEG_CACHE_MASK (NEG_CACHE_SIZE - 1)

static xxh_u64 g_neg_cache[NEG_CACHE_SIZE];
static int     g_neg_cache_valid[NEG_CACHE_SIZE];

static int neg_cache_check(xxh_u64 key) {
    xxh_u32 slot = (xxh_u32)(key & NEG_CACHE_MASK);
    return g_neg_cache_valid[slot] && g_neg_cache[slot] == key;
}

static void neg_cache_insert(xxh_u64 key) {
    xxh_u32 slot = (xxh_u32)(key & NEG_CACHE_MASK);
    g_neg_cache[slot] = key;
    g_neg_cache_valid[slot] = 1;
}

/* --- Public API --- */

static void check_compressed_texture_support(void) {
    GLint num_ext = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext);
    for (GLint i = 0; i < num_ext; i++) {
        const char* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
        if (!ext) continue;
        if (strcmp(ext, "GL_ARB_texture_compression_bptc") == 0) g_has_bc7 = 1;
        if (strcmp(ext, "GL_EXT_texture_compression_s3tc") == 0) g_has_s3tc = 1;
    }
}

static void xxhash64_selftest(void) {
    xxh_u64 h0 = xxhash64("", 0);
    unsigned char b32[32];
    for (int i = 0; i < 32; i++) b32[i] = (unsigned char)i;
    xxh_u64 h32 = xxhash64(b32, 32);
    int ok = (h0 == 0xEF46DB3751D8E999ULL) && (h32 == 0xCBF59C5116FF32B4ULL);
    printf("[TexturePack] XXH64 selftest: %s\n", ok ? "PASS" : "FAIL");
}

void pc_texture_pack_init(void) {
    g_texpack_count = 0;
    g_texpack_active = 0;
    g_stat_lookups = g_stat_hits = g_stat_loaded = g_stat_cache_hits = g_stat_neg_hits = 0;
    memset(g_loaded_cache, 0, sizeof(g_loaded_cache));
    memset(g_neg_cache_valid, 0, sizeof(g_neg_cache_valid));

    xxhash64_selftest();

    check_compressed_texture_support();

    g_texpack_map = (TexPackEntry*)calloc(TEXPACK_MAP_SIZE, sizeof(TexPackEntry));
    g_texpack_wc_map = (TexPackWildcardEntry*)calloc(TEXPACK_WC_SIZE, sizeof(TexPackWildcardEntry));
    if (!g_texpack_map || !g_texpack_wc_map) {
        printf("[TexturePack] Failed to allocate lookup table\n");
        if (g_texpack_map) { free(g_texpack_map); g_texpack_map = NULL; }
        if (g_texpack_wc_map) { free(g_texpack_wc_map); g_texpack_wc_map = NULL; }
        return;
    }

    scan_directory("texture_pack");

    if (g_texpack_count > 0) {
        g_texpack_active = 1;
        printf("[TexturePack] Loaded %d texture entries (BC7:%s S3TC:%s)\n",
               g_texpack_count,
               g_has_bc7 ? "yes" : "no",
               g_has_s3tc ? "yes" : "no");
    } else {
        printf("[TexturePack] No texture pack found in texture_pack/\n");
    }
}

/* --- Texture preload cache file ---
 * Packs all parsed DDS pixel data into one file so subsequent launches
 * only open a single file (avoids antivirus scanning 17K+ individual DDS files).
 *
 * Format:
 *   Header: magic(4) version(4) entry_count(4) texpack_count(4)
 *   Entry[]:  cache_key(8) gl_internal(4) compressed(4) width(4) height(4) data_size(4)
 *   Pixel data follows each entry header immediately.
 */
#define TPC_MAGIC   0x43505431  /* "TPC1" */
#define TPC_VERSION 1
#define TPC_FILE    "texture_pack/texture_cache.bin"

typedef struct {
    xxh_u64 cache_key;
    xxh_u32 gl_internal;
    xxh_u32 compressed;
    xxh_u32 width;
    xxh_u32 height;
    xxh_u32 data_size;
} TPCEntryHeader;

/* Upload a single cached texture entry to GL and insert into loaded_cache */
static int tpc_upload_entry(const TPCEntryHeader* eh, const unsigned char* pixels) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    if (eh->compressed) {
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, (GLenum)eh->gl_internal,
                               (GLsizei)eh->width, (GLsizei)eh->height,
                               0, (GLsizei)eh->data_size, pixels);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     (GLsizei)eh->width, (GLsizei)eh->height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    if (glGetError() != GL_NO_ERROR) {
        glDeleteTextures(1, &tex);
        return 0;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    loaded_cache_insert(eh->cache_key, tex, (int)eh->width, (int)eh->height);
    return 1;
}

/* Try loading from binary cache file. Returns 1 on success, 0 if cache missing/stale. */
static int preload_from_cache(int expected_count) {
    extern SDL_Window* g_pc_window;
    FILE* f = fopen(TPC_FILE, "rb");
    if (!f) return 0;

    xxh_u32 header[4];
    if (fread(header, 4, 4, f) != 4) { fclose(f); return 0; }
    if (header[0] != TPC_MAGIC || header[1] != TPC_VERSION) { fclose(f); return 0; }

    int entry_count = (int)header[2];
    int stored_texpack_count = (int)header[3];

    /* Invalidate if texture pack file count changed */
    if (stored_texpack_count != expected_count) {
        printf("[TexturePack] Cache stale (pack has %d entries, cache has %d) — rebuilding\n",
               expected_count, stored_texpack_count);
        fclose(f);
        return 0;
    }

    int loaded = 0;
    unsigned char* buf = NULL;
    int buf_cap = 0;

    for (int i = 0; i < entry_count; i++) {
        TPCEntryHeader eh;
        if (fread(&eh, sizeof(eh), 1, f) != 1) break;

        if ((int)eh.data_size > buf_cap) {
            buf_cap = (int)eh.data_size + 4096;
            buf = (unsigned char*)realloc(buf, buf_cap);
            if (!buf) break;
        }
        if (fread(buf, 1, eh.data_size, f) != eh.data_size) break;

        if (tpc_upload_entry(&eh, buf)) loaded++;

        if (g_pc_window && (i % 500) == 0) {
            char title[128];
            snprintf(title, sizeof(title), "Animal Crossing - Loading textures... %d/%d (%d%%)",
                     i, entry_count, i * 100 / entry_count);
            SDL_SetWindowTitle(g_pc_window, title);
            SDL_PumpEvents();
        }
    }

    free(buf);
    fclose(f);

    if (g_pc_window) SDL_SetWindowTitle(g_pc_window, "Animal Crossing");

    printf("[TexturePack] Loaded %d textures from cache\n", loaded);
    return 1;
}

/* Load raw DDS file data without creating a GL texture (for cache building).
 * Returns malloc'd pixel data, fills out metadata. Caller must free(). */
static unsigned char* load_dds_raw(const char* filepath, xxh_u32* out_w, xxh_u32* out_h,
                                    xxh_u32* out_gl_internal, xxh_u32* out_compressed,
                                    int* out_data_size) {
    FILE* f = fopen(filepath, "rb");
    if (!f) return NULL;

    unsigned char header[148];
    if (fread(header, 1, 128, f) != 128) { fclose(f); return NULL; }

    xxh_u32 magic;
    memcpy(&magic, header, 4);
    if (magic != DDS_MAGIC) { fclose(f); return NULL; }

    xxh_u32 dds_height, dds_width;
    memcpy(&dds_height, header + 12, 4);
    memcpy(&dds_width, header + 16, 4);

    xxh_u32 pf_flags, pf_fourcc;
    memcpy(&pf_flags, header + 80, 4);
    memcpy(&pf_fourcc, header + 84, 4);

    xxh_u32 dxgi_format = 0;
    GLenum gl_internal = 0;
    int compressed = 0;
    int block_size = 0;

    if ((pf_flags & DDPF_FOURCC) && pf_fourcc == 0x30315844) {
        if (fread(header + 128, 1, 20, f) != 20) { fclose(f); return NULL; }
        memcpy(&dxgi_format, header + 128, 4);
        switch (dxgi_format) {
            case DXGI_FORMAT_BC7_UNORM:
                if (!g_has_bc7) { fclose(f); return NULL; }
                gl_internal = GL_COMPRESSED_RGBA_BPTC_UNORM; compressed = 1; block_size = 16; break;
            case DXGI_FORMAT_BC1_UNORM:
                if (!g_has_s3tc) { fclose(f); return NULL; }
                gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; compressed = 1; block_size = 8; break;
            case DXGI_FORMAT_BC3_UNORM:
                if (!g_has_s3tc) { fclose(f); return NULL; }
                gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; compressed = 1; block_size = 16; break;
            case DXGI_FORMAT_R8G8B8A8_UNORM:
            case DXGI_FORMAT_B8G8R8A8_UNORM:
                gl_internal = GL_RGBA; compressed = 0; break;
            default: fclose(f); return NULL;
        }
    } else if ((pf_flags & DDPF_FOURCC)) {
        if (pf_fourcc == 0x31545844) {
            if (!g_has_s3tc) { fclose(f); return NULL; }
            gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; compressed = 1; block_size = 8;
        } else if (pf_fourcc == 0x35545844) {
            if (!g_has_s3tc) { fclose(f); return NULL; }
            gl_internal = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; compressed = 1; block_size = 16;
        } else { fclose(f); return NULL; }
    } else {
        xxh_u32 rgb_bit_count;
        memcpy(&rgb_bit_count, header + 88, 4);
        if (rgb_bit_count == 32) { gl_internal = GL_RGBA; compressed = 0; }
        else { fclose(f); return NULL; }
    }

    int data_size;
    if (compressed) {
        int blocks_x = ((int)dds_width + 3) / 4;
        int blocks_y = ((int)dds_height + 3) / 4;
        data_size = blocks_x * blocks_y * block_size;
    } else {
        data_size = (int)(dds_width * dds_height * 4);
    }

    unsigned char* pixels = (unsigned char*)malloc(data_size);
    if (!pixels) { fclose(f); return NULL; }
    if ((int)fread(pixels, 1, data_size, f) != data_size) { free(pixels); fclose(f); return NULL; }
    fclose(f);

    if (!compressed && dxgi_format == DXGI_FORMAT_B8G8R8A8_UNORM) {
        for (int i = 0; i < data_size; i += 4) {
            unsigned char tmp = pixels[i]; pixels[i] = pixels[i + 2]; pixels[i + 2] = tmp;
        }
    }

    *out_w = dds_width;
    *out_h = dds_height;
    *out_gl_internal = (xxh_u32)gl_internal;
    *out_compressed = (xxh_u32)compressed;
    *out_data_size = data_size;
    return pixels;
}

/* Preload entry info for cache building */
typedef struct {
    xxh_u64 cache_key;
    char filepath[260];
} PreloadEntry;

void pc_texture_pack_preload_all(void) {
    if (!g_texpack_active) return;

    extern SDL_Window* g_pc_window;
    Uint64 t_start = SDL_GetPerformanceCounter();
    Uint64 freq = SDL_GetPerformanceFrequency();

    int use_cache = (g_pc_settings.preload_textures >= 2);

    /* Try binary cache first (mode 2 only) */
    if (use_cache && preload_from_cache(g_texpack_count)) {
        Uint64 t_end = SDL_GetPerformanceCounter();
        double elapsed = (double)(t_end - t_start) * 1000.0 / (double)freq;
        printf("[TexturePack] Preload from cache took %.0fms\n", elapsed);
        return;
    }

    /* Load all DDS files individually */
    int total = 0, processed = 0, loaded = 0, failed = 0;
    for (int i = 0; i < TEXPACK_MAP_SIZE; i++)
        if (g_texpack_map[i].occupied) total++;
    for (int i = 0; i < TEXPACK_WC_SIZE; i++)
        if (g_texpack_wc_map[i].occupied) total++;

    /* Collect entries and load DDS + upload to GL + write cache simultaneously */
    FILE* cache_f = NULL;
    if (use_cache) {
        cache_f = fopen(TPC_FILE, "wb");
        if (cache_f) {
            xxh_u32 header[4] = { TPC_MAGIC, TPC_VERSION, 0, (xxh_u32)g_texpack_count };
            fwrite(header, 4, 4, cache_f); /* entry_count placeholder, patched later */
        }
    }

    int cache_entries = 0;

    /* Exact-match entries */
    for (int i = 0; i < TEXPACK_MAP_SIZE; i++) {
        if (!g_texpack_map[i].occupied) continue;
        processed++;

        xxh_u64 key = loaded_cache_key(g_texpack_map[i].data_hash,
                                        g_texpack_map[i].tlut_hash,
                                        g_texpack_map[i].gc_fmt,
                                        g_texpack_map[i].orig_w,
                                        g_texpack_map[i].orig_h);
        if (loaded_cache_find(key)) continue;

        xxh_u32 dds_w, dds_h, gl_int, comp;
        int data_size;
        unsigned char* pixels = load_dds_raw(g_texpack_map[i].filepath,
                                              &dds_w, &dds_h, &gl_int, &comp, &data_size);
        if (pixels) {
            TPCEntryHeader eh = { key, gl_int, comp, dds_w, dds_h, (xxh_u32)data_size };

            /* Upload to GL */
            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            if (comp)
                glCompressedTexImage2D(GL_TEXTURE_2D, 0, (GLenum)gl_int,
                                       (GLsizei)dds_w, (GLsizei)dds_h, 0, data_size, pixels);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                             (GLsizei)dds_w, (GLsizei)dds_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            if (glGetError() == GL_NO_ERROR) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                loaded_cache_insert(key, tex, (int)dds_w, (int)dds_h);
                loaded++;

                if (cache_f) {
                    fwrite(&eh, sizeof(eh), 1, cache_f);
                    fwrite(pixels, 1, data_size, cache_f);
                    cache_entries++;
                }
            } else {
                glDeleteTextures(1, &tex);
                failed++;
            }
            free(pixels);
        } else {
            failed++;
        }

        if (g_pc_window && (processed % 100) == 0) {
            char title[128];
            snprintf(title, sizeof(title), "Animal Crossing - Building texture cache... %d/%d (%d%%)",
                     processed, total, processed * 100 / total);
            SDL_SetWindowTitle(g_pc_window, title);
            SDL_PumpEvents();
        }
    }

    /* Wildcard entries */
    for (int i = 0; i < TEXPACK_WC_SIZE; i++) {
        if (!g_texpack_wc_map[i].occupied) continue;
        processed++;

        xxh_u64 key = loaded_cache_key(g_texpack_wc_map[i].data_hash, 0,
                                        g_texpack_wc_map[i].gc_fmt,
                                        g_texpack_wc_map[i].orig_w,
                                        g_texpack_wc_map[i].orig_h);
        if (loaded_cache_find(key)) continue;

        xxh_u32 dds_w, dds_h, gl_int, comp;
        int data_size;
        unsigned char* pixels = load_dds_raw(g_texpack_wc_map[i].filepath,
                                              &dds_w, &dds_h, &gl_int, &comp, &data_size);
        if (pixels) {
            TPCEntryHeader eh = { key, gl_int, comp, dds_w, dds_h, (xxh_u32)data_size };

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            if (comp)
                glCompressedTexImage2D(GL_TEXTURE_2D, 0, (GLenum)gl_int,
                                       (GLsizei)dds_w, (GLsizei)dds_h, 0, data_size, pixels);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                             (GLsizei)dds_w, (GLsizei)dds_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            if (glGetError() == GL_NO_ERROR) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                loaded_cache_insert(key, tex, (int)dds_w, (int)dds_h);
                loaded++;

                if (cache_f) {
                    fwrite(&eh, sizeof(eh), 1, cache_f);
                    fwrite(pixels, 1, data_size, cache_f);
                    cache_entries++;
                }
            } else {
                glDeleteTextures(1, &tex);
                failed++;
            }
            free(pixels);
        } else {
            failed++;
        }

        if (g_pc_window && (processed % 100) == 0) {
            char title[128];
            snprintf(title, sizeof(title), "Animal Crossing - Building texture cache... %d/%d (%d%%)",
                     processed, total, processed * 100 / total);
            SDL_SetWindowTitle(g_pc_window, title);
            SDL_PumpEvents();
        }
    }

    /* Patch entry count in cache header and close */
    if (cache_f) {
        fseek(cache_f, 8, SEEK_SET);
        xxh_u32 count32 = (xxh_u32)cache_entries;
        fwrite(&count32, 4, 1, cache_f);
        fclose(cache_f);
        printf("[TexturePack] Wrote cache: %d textures to %s\n", cache_entries, TPC_FILE);
    }

    if (g_pc_window) SDL_SetWindowTitle(g_pc_window, "Animal Crossing");

    Uint64 t_end = SDL_GetPerformanceCounter();
    double elapsed = (double)(t_end - t_start) * 1000.0 / (double)freq;
    printf("[TexturePack] Preloaded %d/%d textures in %.0fms (%d failed)\n",
           loaded, total, elapsed, failed);
}

void pc_texture_pack_shutdown(void) {
    if (g_texpack_active) {
        printf("[TexturePack] Summary: %d/%d unique textures matched (%d loaded from disk, %d cache hits, %d neg-cache skips)\n",
               g_stat_hits, g_stat_lookups, g_stat_loaded, g_stat_cache_hits, g_stat_neg_hits);
    }

    for (int i = 0; i < LOADED_CACHE_SIZE; i++) {
        if (g_loaded_cache[i].occupied && g_loaded_cache[i].gl_tex) {
            glDeleteTextures(1, &g_loaded_cache[i].gl_tex);
        }
    }
    memset(g_loaded_cache, 0, sizeof(g_loaded_cache));
    memset(g_neg_cache_valid, 0, sizeof(g_neg_cache_valid));

    if (g_texpack_map) {
        free(g_texpack_map);
        g_texpack_map = NULL;
    }
    if (g_texpack_wc_map) {
        free(g_texpack_wc_map);
        g_texpack_wc_map = NULL;
    }
    g_texpack_count = 0;
    g_texpack_active = 0;
}

int pc_texture_pack_active(void) {
    return g_texpack_active;
}

GLuint pc_texture_pack_lookup(const void* data, int data_size,
                              int w, int h, unsigned int fmt,
                              const void* tlut_data, int tlut_entries, int tlut_is_be,
                              int* out_w, int* out_h) {
    if (!g_texpack_active || !data || data_size <= 0) return 0;

    int hash_size = gc_texture_data_size(w, h, fmt);
    if (hash_size > data_size) hash_size = data_size;

    xxh_u64 data_hash = xxhash64(data, hash_size);

    /* CI textures: Dolphin hashes only used palette entries (min..max index), in BE byte order */
    xxh_u64 tlut_hash = 0;
    if (tlut_data && tlut_entries > 0) {
        const unsigned char* tex_bytes = (const unsigned char*)data;
        unsigned int pal_min = 0xFFFF, pal_max = 0;

        if (tlut_entries <= 16) {
            /* CI4: each byte = 2 pixels, 4 bits each */
            for (int i = 0; i < hash_size; i++) {
                unsigned int lo = tex_bytes[i] & 0xF;
                unsigned int hi = tex_bytes[i] >> 4;
                if (lo < pal_min) pal_min = lo;
                if (hi < pal_min) pal_min = hi;
                if (lo > pal_max) pal_max = lo;
                if (hi > pal_max) pal_max = hi;
            }
        } else if (tlut_entries <= 256) {
            /* CI8: each byte = 1 pixel index */
            for (int i = 0; i < hash_size; i++) {
                unsigned int idx = tex_bytes[i];
                if (idx < pal_min) pal_min = idx;
                if (idx > pal_max) pal_max = idx;
            }
        } else {
            /* CI14x2: each u16 & 0x3FFF = index (big-endian) */
            for (int i = 0; i + 1 < hash_size; i += 2) {
                unsigned int idx = ((unsigned int)tex_bytes[i] << 8 | tex_bytes[i+1]) & 0x3FFF;
                if (idx < pal_min) pal_min = idx;
                if (idx > pal_max) pal_max = idx;
            }
        }

        if (pal_min > pal_max) { pal_min = 0; pal_max = 0; }

        int used_entries = (int)(pal_max + 1 - pal_min);
        int tlut_offset = (int)(pal_min * 2);
        int tlut_bytes = used_entries * 2;

        if (tlut_offset + tlut_bytes > tlut_entries * 2)
            tlut_bytes = tlut_entries * 2 - tlut_offset;
        if (tlut_bytes <= 0) tlut_bytes = tlut_entries * 2;

        const unsigned char* tlut_src = (const unsigned char*)tlut_data + tlut_offset;

        if (tlut_is_be) {
            tlut_hash = xxhash64(tlut_src, tlut_bytes);
        } else {
            /* Swap u16s to BE for Dolphin compatibility */
            unsigned char* tmp = (unsigned char*)malloc(tlut_bytes);
            if (!tmp) return 0;
            for (int i = 0; i < tlut_bytes; i += 2) {
                tmp[i] = tlut_src[i + 1];
                tmp[i + 1] = tlut_src[i];
            }
            tlut_hash = xxhash64(tmp, tlut_bytes);
            free(tmp);
        }
    }

    xxh_u64 cache_key = loaded_cache_key(data_hash, tlut_hash, (xxh_u32)fmt, (xxh_u32)w, (xxh_u32)h);
    if (neg_cache_check(cache_key)) { g_stat_neg_hits++; return 0; }

    LoadedCacheEntry* loaded = loaded_cache_find(cache_key);
    if (loaded) {
        g_stat_cache_hits++;
        if (out_w) *out_w = loaded->tex_w;
        if (out_h) *out_h = loaded->tex_h;
        return loaded->gl_tex;
    }

    g_stat_lookups++;

    TexPackEntry* entry = texpack_find(data_hash, tlut_hash, (xxh_u32)fmt, (xxh_u32)w, (xxh_u32)h);
    TexPackWildcardEntry* wc_entry = NULL;
    if (!entry && tlut_hash != 0) {
        wc_entry = texpack_find_wildcard(data_hash, (xxh_u32)fmt, (xxh_u32)w, (xxh_u32)h);
    }
    if (!entry && !wc_entry) {
        neg_cache_insert(cache_key);
        return 0;
    }
    g_stat_hits++;

    int dds_w = 0, dds_h = 0;
    const char* path = entry ? entry->filepath : wc_entry->filepath;
    GLuint tex = load_dds_file(path, &dds_w, &dds_h);
    if (!tex) {
        printf("[TexturePack] Failed to load DDS: %s\n", path);
        neg_cache_insert(cache_key);
        return 0;
    }

    g_stat_loaded++;
    printf("[TexturePack] Loaded HD %dx%d (was %dx%d): %s\n",
           dds_w, dds_h, w, h, path);

    loaded_cache_insert(cache_key, tex, dds_w, dds_h);

    if (out_w) *out_w = dds_w;
    if (out_h) *out_h = dds_h;

    return tex;
}
