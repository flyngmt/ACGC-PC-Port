/* pc_dvd.c - DVD filesystem: reads from disc image (CISO/ISO/GCM) or extracted files */
#include "pc_platform.h"
#include "pc_disc.h"
#include "pc_settings.h"
#include <sys/stat.h>

typedef struct {
    char gameName[4];
    char company[2];
    u8   diskNumber;
    u8   gameVersion;
    u8   streaming;
    u8   streamBufSize;
    u8   padding[22];
} DVDDiskID;

static DVDDiskID disk_id = {
    {'G', 'A', 'F', 'E'},
    {'0', '1'},
    0, 0,
    0, 0,
    {0}
};

DVDDiskID* DVDGetCurrentDiskID(void) { return &disk_id; }

#define MAX_DVD_ENTRIES 512
#define MAX_LOCALIZED_CACHE 512

static struct {
    char path[256];
    int  used;
} dvd_entry_table[MAX_DVD_ENTRIES];
static int dvd_entry_count = 0;

/* File-based fallback path (only used when no disc image) */
static char assets_base_path[512] = {0};
static int assets_fallback_inited = 0;
static char translations_base_path[512] = {0};
static int translations_fallback_inited = 0;
static char translations_fallback_language[32] = {0};

typedef enum {
    DVD_LOCALIZED_SOURCE_NONE = 0,
    DVD_LOCALIZED_SOURCE_DISC,
    DVD_LOCALIZED_SOURCE_FALLBACK,
} dvd_localized_source_t;

typedef struct {
    int used;
    char path[256];
    char resolved_path[256];
} dvd_localized_cache_entry_t;

static dvd_localized_cache_entry_t dvd_localized_cache[MAX_LOCALIZED_CACHE];
static int dvd_localized_cache_count = 0;
static char dvd_localized_cache_language[32] = {0};

static void dvd_init_fallback_path(void);
static void dvd_init_translations_path(void);

static void dvd_localized_cache_reset(void) {
    memset(dvd_localized_cache, 0, sizeof(dvd_localized_cache));
    dvd_localized_cache_count = 0;
}

static void dvd_localized_cache_sync_language(void) {
    const char* lang = pc_settings_get_language();
    const char* effective_lang = (lang != NULL) ? lang : "";

    if (strcmp(dvd_localized_cache_language, effective_lang) != 0) {
        dvd_localized_cache_reset();
        strncpy(dvd_localized_cache_language, effective_lang, sizeof(dvd_localized_cache_language) - 1);
        dvd_localized_cache_language[sizeof(dvd_localized_cache_language) - 1] = '\0';
    }
}

static dvd_localized_cache_entry_t* dvd_localized_cache_find(const char* path) {
    for (int i = 0; i < dvd_localized_cache_count; i++) {
        if (dvd_localized_cache[i].used && strcmp(dvd_localized_cache[i].path, path) == 0) {
            return &dvd_localized_cache[i];
        }
    }

    return NULL;
}

static void dvd_localized_cache_store(const char* path, const char* resolved_path_or_null) {
    dvd_localized_cache_entry_t* entry = dvd_localized_cache_find(path);

    if (entry == NULL) {
        if (dvd_localized_cache_count >= MAX_LOCALIZED_CACHE) {
            return;
        }

        entry = &dvd_localized_cache[dvd_localized_cache_count++];
        entry->used = 1;
        strncpy(entry->path, path, sizeof(entry->path) - 1);
        entry->path[sizeof(entry->path) - 1] = '\0';
    }

    if (resolved_path_or_null != NULL && resolved_path_or_null[0] != '\0') {
        strncpy(entry->resolved_path, resolved_path_or_null, sizeof(entry->resolved_path) - 1);
        entry->resolved_path[sizeof(entry->resolved_path) - 1] = '\0';
    } else {
        entry->resolved_path[0] = '\0';
    }
}

static int dvd_is_language_default(void) {
    const char* lang = pc_settings_get_language();
    return (lang == NULL || lang[0] == '\0' || strcmp(lang, "default") == 0);
}

static int dvd_path_has_language_tag(const char* path, const char* lang) {
    const char* dot;
    size_t name_len;
    size_t lang_len;

    if (path == NULL || path[0] == '\0' || lang == NULL || lang[0] == '\0') {
        return 0;
    }

    dot = strrchr(path, '.');
    if (dot == NULL || dot == path) {
        return 0;
    }

    lang_len = strlen(lang);
    name_len = (size_t)(dot - path);
    if (name_len <= lang_len + 1) {
        return 0;
    }

    if (path[name_len - lang_len - 1] != '.') {
        return 0;
    }

    return strncmp(path + name_len - lang_len, lang, lang_len) == 0;
}

static int dvd_strip_language_tag(const char* path, const char* lang, char* out_path, size_t out_path_size) {
    const char* dot;
    size_t lang_len;
    size_t prefix_len;

    if (!dvd_path_has_language_tag(path, lang) || out_path == NULL || out_path_size == 0) {
        return 0;
    }

    dot = strrchr(path, '.');
    lang_len = strlen(lang);
    prefix_len = (size_t)(dot - path) - lang_len - 1;

    if (prefix_len + strlen(dot) + 1 > out_path_size) {
        return 0;
    }

    memcpy(out_path, path, prefix_len);
    snprintf(out_path + prefix_len, out_path_size - prefix_len, "%s", dot);
    return 1;
}

static int dvd_try_open_from_base(const char* base, const char* path, FILE** out_fp, u32* out_size) {
    char fullpath[768];
    FILE* fp;
    long end_pos;

    if (base == NULL || base[0] == '\0' || path == NULL || out_fp == NULL || out_size == NULL) {
        return 0;
    }

    if (path[0] == '/') {
        snprintf(fullpath, sizeof(fullpath), "%s%s", base, path);
    } else {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", base, path);
    }

    fp = fopen(fullpath, "rb");
    if (!fp) {
        return 0;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return 0;
    }

    end_pos = ftell(fp);
    if (end_pos < 0) {
        fclose(fp);
        return 0;
    }

    if (fseek(fp, 0, SEEK_SET) != 0) {
        fclose(fp);
        return 0;
    }

    *out_fp = fp;
    *out_size = (u32)end_pos;
    return 1;
}

static int dvd_dir_exists(const char* path) {
    struct stat st;

    if (path == NULL || path[0] == '\0') {
        return 0;
    }

    if (stat(path, &st) != 0) {
        return 0;
    }

    return S_ISDIR(st.st_mode) ? 1 : 0;
}

static int dvd_build_localized_path(const char* path, char* localized_path, size_t localized_path_size) {
    const char* lang;
    const char* dot;
    const char* name;
    int has_leading_slash;
    size_t name_len;

    if (dvd_is_language_default()) {
        return 0;
    }

    if (path == NULL || path[0] == '\0') {
        return 0;
    }

    lang = pc_settings_get_language();
    if (lang == NULL || lang[0] == '\0') {
        return 0;
    }

    has_leading_slash = (path[0] == '/');
    name = has_leading_slash ? path + 1 : path;

    if (name[0] == '\0') {
        return 0;
    }

    dot = strrchr(name, '.');

    if (dot != NULL) {
        name_len = (size_t)(dot - name);
        if (has_leading_slash) {
            snprintf(localized_path, localized_path_size, "/%.*s.%s%s", (int)name_len, name, lang, dot);
        } else {
            snprintf(localized_path, localized_path_size, "%.*s.%s%s", (int)name_len, name, lang, dot);
        }
    } else {
        if (has_leading_slash) {
            snprintf(localized_path, localized_path_size, "/%s.%s", name, lang);
        } else {
            snprintf(localized_path, localized_path_size, "%s.%s", name, lang);
        }
    }

    return 1;
}

static int dvd_fallback_file_open(const char* path, FILE** out_fp, u32* out_size) {
    const char* lang;
    char stripped_path[256];

    if (path == NULL || out_fp == NULL || out_size == NULL) {
        return 0;
    }

    lang = pc_settings_get_language();
    if (lang != NULL && lang[0] != '\0' && strcmp(lang, "default") != 0 && dvd_path_has_language_tag(path, lang)) {
        dvd_init_translations_path();

        if (translations_base_path[0] != '\0') {
            if (dvd_strip_language_tag(path, lang, stripped_path, sizeof(stripped_path))) {
                if (dvd_try_open_from_base(translations_base_path, stripped_path, out_fp, out_size)) {
                    return 1;
                }
            }

            if (dvd_try_open_from_base(translations_base_path, path, out_fp, out_size)) {
                return 1;
            }
        }

        return 0;
    }

    dvd_init_fallback_path();
    return dvd_try_open_from_base(assets_base_path, path, out_fp, out_size);
}

static dvd_localized_source_t dvd_get_localized_source(const char* localized_path) {
    FILE* fp;
    u32 size;
    u32 disc_off;
    u32 disc_sz;

    if (pc_disc_is_open() && pc_disc_find_file(localized_path, &disc_off, &disc_sz)) {
        return DVD_LOCALIZED_SOURCE_DISC;
    }

    if (dvd_fallback_file_open(localized_path, &fp, &size)) {
        fclose(fp);
        return DVD_LOCALIZED_SOURCE_FALLBACK;
    }

    return DVD_LOCALIZED_SOURCE_NONE;
}

static int dvd_compare_disc_region(u32 off_a, u32 size_a, u32 off_b, u32 size_b) {
    u8 buf_a[4096];
    u8 buf_b[4096];
    u32 read_off_a = off_a;
    u32 read_off_b = off_b;
    u32 remaining;

    if (size_a != size_b) {
        return 1;
    }

    remaining = size_a;
    while (remaining > 0) {
        u32 chunk = remaining > (u32)sizeof(buf_a) ? (u32)sizeof(buf_a) : remaining;

        if (!pc_disc_read(read_off_a, buf_a, chunk)) {
            return -1;
        }

        if (!pc_disc_read(read_off_b, buf_b, chunk)) {
            return -1;
        }

        if (memcmp(buf_a, buf_b, chunk) != 0) {
            return 1;
        }

        read_off_a += chunk;
        read_off_b += chunk;
        remaining -= chunk;
    }

    return 0;
}

static int dvd_compare_disc_vs_fallback(u32 disc_off, u32 disc_sz, FILE* fallback_fp, u32 fallback_sz) {
    u8 disc_buf[4096];
    u8 file_buf[4096];
    u32 read_off = disc_off;
    u32 remaining;

    if (disc_sz != fallback_sz) {
        return 1;
    }

    remaining = disc_sz;
    while (remaining > 0) {
        size_t nread;
        u32 chunk = remaining > (u32)sizeof(disc_buf) ? (u32)sizeof(disc_buf) : remaining;

        if (!pc_disc_read(read_off, disc_buf, chunk)) {
            return -1;
        }

        nread = fread(file_buf, 1, chunk, fallback_fp);
        if (nread != chunk) {
            return -1;
        }

        if (memcmp(disc_buf, file_buf, chunk) != 0) {
            return 1;
        }

        read_off += chunk;
        remaining -= chunk;
    }

    return 0;
}

static int dvd_localized_differs_from_disc(const char* base_path, const char* localized_path,
                                           dvd_localized_source_t source) {
    u32 base_off;
    u32 base_sz;

    if (!pc_disc_is_open()) {
        return 1;
    }

    if (!pc_disc_find_file(base_path, &base_off, &base_sz)) {
        return 1;
    }

    if (source == DVD_LOCALIZED_SOURCE_DISC) {
        u32 loc_off;
        u32 loc_sz;

        if (!pc_disc_find_file(localized_path, &loc_off, &loc_sz)) {
            return 0;
        }

        return dvd_compare_disc_region(base_off, base_sz, loc_off, loc_sz);
    }

    if (source == DVD_LOCALIZED_SOURCE_FALLBACK) {
        FILE* fp;
        u32 fsz;
        int result;

        if (!dvd_fallback_file_open(localized_path, &fp, &fsz)) {
            return 0;
        }

        result = dvd_compare_disc_vs_fallback(base_off, base_sz, fp, fsz);
        fclose(fp);
        return result;
    }

    return 0;
}

static const char* dvd_resolve_localized_path(const char* path, char* localized_path, size_t localized_path_size) {
    dvd_localized_cache_entry_t* cached;
    dvd_localized_source_t source;
    int differs;

    dvd_localized_cache_sync_language();

    cached = dvd_localized_cache_find(path);
    if (cached != NULL) {
        if (cached->resolved_path[0] != '\0') {
            snprintf(localized_path, localized_path_size, "%s", cached->resolved_path);
            return localized_path;
        }
        return path;
    }

    if (!dvd_build_localized_path(path, localized_path, localized_path_size)) {
        dvd_localized_cache_store(path, NULL);
        return path;
    }

    source = dvd_get_localized_source(localized_path);
    if (source == DVD_LOCALIZED_SOURCE_NONE) {
        dvd_localized_cache_store(path, NULL);
        return path;
    }

    differs = dvd_localized_differs_from_disc(path, localized_path, source);
    if (differs > 0) {
        fprintf(stderr, "[PC/DVD] Localized override: %s -> %s\n", path, localized_path);
        dvd_localized_cache_store(path, localized_path);
        return localized_path;
    }

    if (differs < 0) {
        fprintf(stderr, "[PC/DVD] Localized compare failed for %s, using original\n", path);
        dvd_localized_cache_store(path, NULL);
        return path;
    }

    fprintf(stderr, "[PC/DVD] Localized file identical to DVD original for %s, using original\n", path);
    dvd_localized_cache_store(path, NULL);
    return path;
}

static void dvd_init_fallback_path(void) {
    if (assets_fallback_inited) return;
    assets_fallback_inited = 1;

    const char* candidates[] = {
        "assets/files",
        "assets",
        "../assets/files",
        "../assets",
        "../../assets/files",
        "../../assets",
    };
    for (int i = 0; i < (int)(sizeof(candidates)/sizeof(candidates[0])); i++) {
        char test[768];
        snprintf(test, sizeof(test), "%s/COPYDATE", candidates[i]);
        FILE* f = fopen(test, "rb");
        if (f) {
            fclose(f);
            strncpy(assets_base_path, candidates[i], sizeof(assets_base_path)-1);
            assets_base_path[sizeof(assets_base_path)-1] = '\0';
            return;
        }
    }
    strncpy(assets_base_path, "assets", sizeof(assets_base_path)-1);
    assets_base_path[sizeof(assets_base_path)-1] = '\0';
}

static void dvd_init_translations_path(void) {
    const char* lang = pc_settings_get_language();
    const char* effective_lang = (lang != NULL) ? lang : "";

    if (translations_fallback_inited && strcmp(translations_fallback_language, effective_lang) == 0) {
        return;
    }

    translations_fallback_inited = 1;
    strncpy(translations_fallback_language, effective_lang, sizeof(translations_fallback_language) - 1);
    translations_fallback_language[sizeof(translations_fallback_language) - 1] = '\0';
    translations_base_path[0] = '\0';

    if (effective_lang[0] == '\0' || strcmp(effective_lang, "default") == 0) {
        return;
    }

    {
        const char* candidates[] = {
            "translations",
            "../translations",
            "../../translations",
            "../../../translations",
        };

        for (int i = 0; i < (int)(sizeof(candidates) / sizeof(candidates[0])); i++) {
            char test[768];

            snprintf(test, sizeof(test), "%s/%s", candidates[i], effective_lang);
            if (dvd_dir_exists(test)) {
                strncpy(translations_base_path, test, sizeof(translations_base_path) - 1);
                translations_base_path[sizeof(translations_base_path) - 1] = '\0';
                return;
            }
        }
    }
}

s32 DVDConvertPathToEntrynum(const char* path) {
    for (int i = 0; i < dvd_entry_count; i++) {
        if (dvd_entry_table[i].used && strcmp(dvd_entry_table[i].path, path) == 0) {
            return i;
        }
    }

    if (dvd_entry_count >= MAX_DVD_ENTRIES) {
        fprintf(stderr, "[PC/DVD] Entry table full (%d entries)! Cannot register: %s\n",
                MAX_DVD_ENTRIES, path);
        return -1;
    }

    int idx = dvd_entry_count++;
    strncpy(dvd_entry_table[idx].path, path, sizeof(dvd_entry_table[idx].path) - 1);
    dvd_entry_table[idx].path[sizeof(dvd_entry_table[idx].path) - 1] = '\0';
    dvd_entry_table[idx].used = 1;
    return idx;
}

/* DVDFileInfo field access — compute offsets from struct layout so they work on 64-bit.
 * On GC (32-bit), DVDCommandBlock has 4-byte pointers → DVDFileInfo is 0x3C bytes.
 * On 64-bit, pointers are 8 bytes → DVDCommandBlock grows, shifting all fields.
 *
 * DVDCommandBlock layout (see dolphin/dvd.h):
 *   DVDCommandBlock* next, *prev;   // 2 pointers
 *   u32 command, state, offset, length;  // 4 × u32
 *   void* addr;                     // 1 pointer ← we store FILE* here
 *   u32 currTransferSize, transferredSize; // 2 × u32
 *   DVDDiskID* id;                  // 1 pointer
 *   DVDCBCallback callback;         // 1 pointer (func ptr)
 *   void* userData;                 // 1 pointer
 *
 * DVDFileInfo = { DVDCommandBlock cb; u32 startAddr; u32 length; DVDCallback callback; }
 */
#include <stddef.h>

/* Mirror the struct layout locally to compute correct offsets without
 * pulling in the full dolphin/dvd.h (which conflicts with our void* stubs). */
typedef struct {
    void* next; void* prev;          /* 2 ptrs */
    u32 command; s32 state;
    u32 offset_; u32 length_;
    void* addr;                      /* FILE* stored here */
    u32 currTransferSize; u32 transferredSize;
    void* id; void (*callback_)(s32, void*); void* userData;
} DVDCommandBlock_PC;

typedef struct {
    DVDCommandBlock_PC cb;
    u32 startAddr;
    u32 length;
    void (*callback)(s32, void*);
} DVDFileInfo_PC;

#define DISC_SENTINEL ((FILE*)(uintptr_t)0xDEADC0DE)

static FILE** dvd_fi_fp(void* fileInfo) {
    return (FILE**)((u8*)fileInfo + offsetof(DVDFileInfo_PC, cb) + offsetof(DVDCommandBlock_PC, addr));
}
static u32* dvd_fi_length(void* fileInfo) {
    return (u32*)((u8*)fileInfo + offsetof(DVDFileInfo_PC, length));
}
static u32* dvd_fi_startAddr(void* fileInfo) {
    return (u32*)((u8*)fileInfo + offsetof(DVDFileInfo_PC, startAddr));
}

BOOL DVDFastOpen(s32 entrynum, void* fileInfo) {
    if (entrynum < 0 || entrynum >= dvd_entry_count || !dvd_entry_table[entrynum].used) {
        return FALSE;
    }

    const char* path = dvd_entry_table[entrynum].path;
    char localized_path[256];

    path = dvd_resolve_localized_path(path, localized_path, sizeof(localized_path));

    /* Try disc image first */
    if (pc_disc_is_open()) {
        u32 disc_off, disc_sz;
        if (pc_disc_find_file(path, &disc_off, &disc_sz)) {
            memset(fileInfo, 0, sizeof(DVDFileInfo_PC));
            *dvd_fi_fp(fileInfo) = DISC_SENTINEL;
            *dvd_fi_startAddr(fileInfo) = disc_off;
            *dvd_fi_length(fileInfo) = disc_sz;
            return TRUE;
        }
    }

    /* Fall back to extracted files */
    {
        FILE* fp;
        u32 len;

        if (!dvd_fallback_file_open(path, &fp, &len)) {
            return FALSE;
        }

        memset(fileInfo, 0, sizeof(DVDFileInfo_PC));
        *dvd_fi_fp(fileInfo) = fp;
        *dvd_fi_startAddr(fileInfo) = 0;
        *dvd_fi_length(fileInfo) = len;
    }

    return TRUE;
}

BOOL DVDOpen(const char* filename, void* fileInfo) {
    s32 entry = DVDConvertPathToEntrynum(filename);
    if (entry < 0) return FALSE;
    return DVDFastOpen(entry, fileInfo);
}

BOOL DVDClose(void* fileInfo) {
    FILE* fp = *dvd_fi_fp(fileInfo);
    if (fp && fp != DISC_SENTINEL) {
        fclose(fp);
    }
    *dvd_fi_fp(fileInfo) = NULL;
    return TRUE;
}

s32 DVDReadPrio(void* fileInfo, void* buf, s32 length, s32 offset, s32 prio) {
    FILE* fp = *dvd_fi_fp(fileInfo);
    (void)prio;

    if (fp == DISC_SENTINEL) {
        /* disc image read */
        u32 base = *dvd_fi_startAddr(fileInfo);
        if (pc_disc_read(base + (u32)offset, buf, (u32)length))
            return length;
        return -1;
    }

    if (!fp) {
        return -1;
    }

    fseek(fp, offset, SEEK_SET);
    return (s32)fread(buf, 1, length, fp);
}

s32 DVDRead(void* fileInfo, void* buf, s32 length, s32 offset) {
    return DVDReadPrio(fileInfo, buf, length, offset, 2);
}

u32 DVDGetLength(void* fileInfo) {
    return *dvd_fi_length(fileInfo);
}

typedef void (*pc_DVDCallback)(s32, void*);

BOOL DVDReadAsyncPrio(void* fileInfo, void* buf, s32 length, s32 offset,
                      pc_DVDCallback callback, s32 prio) {
    s32 nread = DVDReadPrio(fileInfo, buf, length, offset, prio);
    if (callback) {
        callback(nread, fileInfo);
    }
    return TRUE;
}

void OSDVDFatalError(void) {
    fprintf(stderr, "[PC/DVD] Fatal DVD error\n");
}

void DVDInit(void) {
    /* disc image init is done in pc_main.c via pc_disc_init() */
}

void DVDSetAutoFatalMessaging(BOOL enable) { (void)enable; }

s32 DVDGetFileInfoStatus(void* fileInfo) {
    (void)fileInfo;
    return 0;
}

s32 DVDGetTransferredSize(void* fileInfo) {
    (void)fileInfo;
    return 0;
}

BOOL DVDFastClose(void* fileInfo) {
    return DVDClose(fileInfo);
}

s32 DVDGetDriveStatus(void) { return 0; }
s32 DVDCancel(void* block) { (void)block; return 0; }
BOOL DVDCancelAsync(void* block, void* callback) { (void)block; (void)callback; return TRUE; }
s32 DVDChangeDisk(void* block, void* id) { (void)block; (void)id; return 0; }
BOOL DVDChangeDiskAsync(void* block, void* id, void* callback) { (void)block; (void)id; (void)callback; return TRUE; }
s32 DVDGetCommandBlockStatus(void* block) { (void)block; return 0; }

BOOL DVDPrepareStreamAsync(void* fi, u32 len, u32 off, void* cb) {
    (void)fi; (void)len; (void)off; (void)cb;
    return TRUE;
}
s32 DVDCancelStream(void* block) { (void)block; return 0; }
