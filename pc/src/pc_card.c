/* pc_card.c - memory card API → local file I/O
 * Channel 0 (Slot A) → save/card_a/
 * Channel 1 (Slot B) → save/card_b/ */
#include "pc_platform.h"
#include <sys/stat.h>   /* mkdir (Linux), stat */
#ifdef _WIN32
#include <direct.h>  /* _mkdir */
#include <windows.h>
#else
#include <dirent.h>
#endif

#define CARD_RESULT_READY     0
#define CARD_RESULT_BUSY     -1
#define CARD_RESULT_WRONGDEVICE -2
#define CARD_RESULT_NOCARD   -3
#define CARD_RESULT_NOFILE   -4
#define CARD_RESULT_IOERROR  -5
#define CARD_RESULT_BROKEN   -6
#define CARD_RESULT_EXIST    -7
#define CARD_RESULT_NOENT    -8
#define CARD_RESULT_INSSPACE -9
#define CARD_RESULT_NOPERM   -10
#define CARD_RESULT_LIMIT    -11
#define CARD_RESULT_NAMETOOLONG -12
#define CARD_RESULT_ENCODING -13
#define CARD_RESULT_CANCELED -14
#define CARD_RESULT_FATAL_ERROR -128

/* must match card.h layout (20 bytes); extra state goes in side table */
typedef struct {
    s32   chan;
    s32   fileNo;
    s32   offset;
    s32   length;
    u16   iBlock;
} CARDFileInfo_PC;

#define CARD_MAX_OPEN 4
typedef struct {
    CARDFileInfo_PC* owner;   /* NULL = slot free */
    FILE*            fp;
    char             filename[64];
} CARDOpenSlot;

static CARDOpenSlot card_slots[CARD_MAX_OPEN];

static CARDOpenSlot* card_slot_alloc(CARDFileInfo_PC* fi) {
    int i;
    for (i = 0; i < CARD_MAX_OPEN; i++) {
        if (card_slots[i].owner == NULL) {
            card_slots[i].owner = fi;
            card_slots[i].fp = NULL;
            card_slots[i].filename[0] = '\0';
            return &card_slots[i];
        }
    }
    return NULL;
}

static CARDOpenSlot* card_slot_find(CARDFileInfo_PC* fi) {
    int i;
    for (i = 0; i < CARD_MAX_OPEN; i++) {
        if (card_slots[i].owner == fi) return &card_slots[i];
    }
    return NULL;
}

static void card_slot_free(CARDFileInfo_PC* fi) {
    int i;
    for (i = 0; i < CARD_MAX_OPEN; i++) {
        if (card_slots[i].owner == fi) {
            card_slots[i].owner = NULL;
            card_slots[i].fp = NULL;
            return;
        }
    }
}

/* Per-channel directory: chan 0 = card_a, chan 1 = card_b */
static const char* card_dir[2] = { "save/card_a", "save/card_b" };
static int card_mounted[2] = {0, 0};

static const char* get_card_dir(s32 chan) {
    if (chan >= 0 && chan <= 1) return card_dir[chan];
    return card_dir[0];
}

/* reject path traversal */
static int card_filename_safe(const char* name) {
    if (!name || !name[0]) return 0;
    if (strstr(name, "..")) return 0;
    if (strchr(name, '/') || strchr(name, '\\')) return 0;
    return 1;
}

#define CARD_SECTOR_SIZE 8192

static void ensure_dirs(void) {
#ifdef _WIN32
    _mkdir("save");
    _mkdir("save/card_a");
    _mkdir("save/card_b");
#else
    mkdir("save", 0755);
    mkdir("save/card_a", 0755);
    mkdir("save/card_b", 0755);
#endif
}

void CARDInit(void) {
    ensure_dirs();
}

s32 CARDMount(s32 chan, void* workArea, void* detachCallback) {
    (void)workArea; (void)detachCallback;
    if (chan < 0 || chan > 1) return CARD_RESULT_NOCARD;
    card_mounted[chan] = 1;
    return CARD_RESULT_READY;
}

s32 CARDMountAsync(s32 chan, void* workArea, void* detachCb, void* attachCb) {
    s32 result = CARDMount(chan, workArea, detachCb);
    if (attachCb) ((void (*)(s32, s32))attachCb)(chan, result);
    return result;
}

s32 CARDUnmount(s32 chan) {
    if (chan >= 0 && chan <= 1) card_mounted[chan] = 0;
    return CARD_RESULT_READY;
}

s32 CARDOpen(s32 chan, const char* fileName, CARDFileInfo_PC* fileInfo) {
    char path[512];
    CARDOpenSlot* slot;
    if (!card_filename_safe(fileName)) return CARD_RESULT_NAMETOOLONG;
    snprintf(path, sizeof(path), "%s/%s", get_card_dir(chan), fileName);

    fileInfo->chan = chan;
    fileInfo->offset = 0;

    slot = card_slot_alloc(fileInfo);
    if (!slot) return CARD_RESULT_IOERROR;

    strncpy(slot->filename, fileName, sizeof(slot->filename) - 1);
    slot->filename[sizeof(slot->filename) - 1] = '\0';
    slot->fp = fopen(path, "r+b");
    if (!slot->fp) {
        card_slot_free(fileInfo);
        return CARD_RESULT_NOFILE;
    }
    fseek(slot->fp, 0, SEEK_END);
    fileInfo->length = (s32)ftell(slot->fp);
    fseek(slot->fp, 0, SEEK_SET);
    return CARD_RESULT_READY;
}

s32 CARDClose(CARDFileInfo_PC* fileInfo) {
    CARDOpenSlot* slot = card_slot_find(fileInfo);
    if (slot && slot->fp) {
        fclose(slot->fp);
        slot->fp = NULL;
    }
    card_slot_free(fileInfo);
    return CARD_RESULT_READY;
}

s32 CARDCreate(s32 chan, const char* fileName, u32 size, CARDFileInfo_PC* fileInfo) {
    char path[512];
    CARDOpenSlot* slot;
    if (!card_filename_safe(fileName)) return CARD_RESULT_NAMETOOLONG;
    snprintf(path, sizeof(path), "%s/%s", get_card_dir(chan), fileName);

    fileInfo->chan = chan;
    fileInfo->offset = 0;
    fileInfo->length = size;

    slot = card_slot_alloc(fileInfo);
    if (!slot) return CARD_RESULT_IOERROR;

    strncpy(slot->filename, fileName, sizeof(slot->filename) - 1);
    slot->filename[sizeof(slot->filename) - 1] = '\0';

    slot->fp = fopen(path, "w+b");
    if (!slot->fp) { card_slot_free(fileInfo); return CARD_RESULT_IOERROR; }

    {
        u8* zeros = (u8*)calloc(1, size);
        if (!zeros) { fclose(slot->fp); slot->fp = NULL; card_slot_free(fileInfo); return CARD_RESULT_IOERROR; }
        size_t written = fwrite(zeros, 1, size, slot->fp);
        free(zeros);
        if (written != size) { fclose(slot->fp); slot->fp = NULL; card_slot_free(fileInfo); return CARD_RESULT_IOERROR; }
        fseek(slot->fp, 0, SEEK_SET);
    }

    return CARD_RESULT_READY;
}

s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, void* fileInfo, void* callback) {
    s32 result = CARDCreate(chan, fileName, size, (CARDFileInfo_PC*)fileInfo);
    if (callback) ((void (*)(s32, s32))callback)(chan, result);
    return result;
}

s32 CARDRead(CARDFileInfo_PC* fileInfo, void* buf, s32 length, s32 offset) {
    CARDOpenSlot* slot = card_slot_find(fileInfo);
    if (!slot || !slot->fp) return CARD_RESULT_NOFILE;
    fseek(slot->fp, offset, SEEK_SET);
    if ((s32)fread(buf, 1, length, slot->fp) != length) return CARD_RESULT_IOERROR;
    return CARD_RESULT_READY;
}

s32 CARDReadAsync(void* fileInfo, void* buf, s32 length, s32 offset, void* callback) {
    s32 result = CARDRead((CARDFileInfo_PC*)fileInfo, buf, length, offset);
    if (callback) ((void (*)(s32, s32))callback)(0, result);
    return result;
}

s32 CARDWrite(CARDFileInfo_PC* fileInfo, const void* buf, s32 length, s32 offset) {
    CARDOpenSlot* slot = card_slot_find(fileInfo);
    if (!slot || !slot->fp) return CARD_RESULT_NOFILE;
    fseek(slot->fp, offset, SEEK_SET);
    if ((s32)fwrite(buf, 1, length, slot->fp) != length) return CARD_RESULT_IOERROR;
    fflush(slot->fp);
    return CARD_RESULT_READY;
}

s32 CARDWriteAsync(void* fileInfo, const void* buf, s32 length, s32 offset, void* callback) {
    s32 result = CARDWrite((CARDFileInfo_PC*)fileInfo, buf, length, offset);
    if (callback) ((void (*)(s32, s32))callback)(0, result);
    return result;
}

s32 CARDDelete(s32 chan, const char* fileName) {
    char path[512];
    if (!card_filename_safe(fileName)) return CARD_RESULT_NAMETOOLONG;
    snprintf(path, sizeof(path), "%s/%s", get_card_dir(chan), fileName);
    remove(path);
    return CARD_RESULT_READY;
}

s32 CARDDeleteAsync(s32 chan, const char* fileName, void* callback) {
    s32 result = CARDDelete(chan, fileName);
    if (callback) ((void (*)(s32, s32))callback)(chan, result);
    return result;
}

s32 CARDGetResultCode(s32 chan) { return CARD_RESULT_READY; }
s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed) {
    if (byteNotUsed) *byteNotUsed = 1024 * 1024; /* 1 MB free */
    if (filesNotUsed) *filesNotUsed = 100;
    return CARD_RESULT_READY;
}

s32 CARDGetSectorSize(s32 chan, u32* size) {
    if (size) *size = CARD_SECTOR_SIZE;
    return CARD_RESULT_READY;
}

s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize) {
    if (memSize) *memSize = 16 * 1024 * 1024; /* 16 MB */
    if (sectorSize) *sectorSize = CARD_SECTOR_SIZE;
    return CARD_RESULT_READY;
}

s32 CARDProbe(s32 chan) { return CARD_RESULT_READY; }

s32 CARDCheck(s32 chan) { return CARD_RESULT_READY; }
s32 CARDCheckAsync(s32 chan, void* callback) {
    if (callback) ((void (*)(s32, s32))callback)(chan, CARD_RESULT_READY);
    return CARD_RESULT_READY;
}

typedef struct {
    char fileName[32];
    u32  length;
    u32  time;
    u8   gameName[4];
    u8   company[2];
    u8   bannerFormat;
    u32  iconAddr;
    u16  iconFormat;
    u16  iconSpeed;
    u32  commentAddr;
    u32  offsetBanner;
    u32  offsetBannerTlut;
    u32  offsetIcon[8];
    u32  offsetIconTlut;
    u32  offsetData;
} CARDStat;

s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat) {
    memset(stat, 0, sizeof(CARDStat));
    return CARD_RESULT_READY;
}

s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat* stat) {
    return CARD_RESULT_READY;
}

s32 CARDSetStatusAsync(s32 chan, s32 fileNo, void* stat, void* callback) {
    if (callback) ((void (*)(s32, s32))callback)(chan, CARD_RESULT_READY);
    return CARD_RESULT_READY;
}

s32 CARDRename(s32 chan, const char* oldName, const char* newName) {
    char oldPath[512], newPath[512];
    if (!card_filename_safe(oldName) || !card_filename_safe(newName)) return CARD_RESULT_NAMETOOLONG;
    snprintf(oldPath, sizeof(oldPath), "%s/%s", get_card_dir(chan), oldName);
    snprintf(newPath, sizeof(newPath), "%s/%s", get_card_dir(chan), newName);
    rename(oldPath, newPath);
    return CARD_RESULT_READY;
}

s32 CARDRenameAsync(s32 chan, const char* oldName, const char* newName, void* callback) {
    s32 result = CARDRename(chan, oldName, newName);
    if (callback) ((void (*)(s32, s32))callback)(chan, result);
    return result;
}

s32 CARDFormat(s32 chan) { return CARD_RESULT_READY; }
s32 CARDFormatAsync(s32 chan, void* callback) {
    if (callback) ((void (*)(s32, s32))callback)(chan, CARD_RESULT_READY);
    return CARD_RESULT_READY;
}

/* Scan a card directory for the first valid AC GCI file.
 * Returns 1 and writes full path to out_path if found, 0 otherwise. */
int pc_card_scan_for_gci(s32 chan, char* out_path, int out_size) {
    const char* dir = get_card_dir(chan);

#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    HANDLE h;
    char search[300];
    snprintf(search, sizeof(search), "%s\\*.gci", dir);
    h = FindFirstFileA(search, &fd);
    if (h == INVALID_HANDLE_VALUE) return 0;
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        /* Quick-validate: read first 4 bytes of GCI header (gameName) */
        {
            char full[512];
            FILE* fp;
            u8 hdr[4];
            snprintf(full, sizeof(full), "%s/%s", dir, fd.cFileName);
            fp = fopen(full, "rb");
            if (fp) {
                if (fread(hdr, 1, 4, fp) == 4 && hdr[0] == 'G' && hdr[1] == 'A' && hdr[2] == 'F') {
                    fclose(fp);
                    snprintf(out_path, out_size, "%s", full);
                    FindClose(h);
                    return 1;
                }
                fclose(fp);
            }
        }
    } while (FindNextFileA(h, &fd));
    FindClose(h);
#else
    DIR* d = opendir(dir);
    struct dirent* ent;
    if (!d) return 0;
    while ((ent = readdir(d)) != NULL) {
        const char* name = ent->d_name;
        int len = strlen(name);
        if (len < 5) continue;
        if (strcasecmp(name + len - 4, ".gci") != 0) continue;
        {
            char full[512];
            FILE* fp;
            u8 hdr[4];
            snprintf(full, sizeof(full), "%s/%s", dir, name);
            fp = fopen(full, "rb");
            if (fp) {
                if (fread(hdr, 1, 4, fp) == 4 && hdr[0] == 'G' && hdr[1] == 'A' && hdr[2] == 'F') {
                    fclose(fp);
                    snprintf(out_path, out_size, "%s", full);
                    closedir(d);
                    return 1;
                }
                fclose(fp);
            }
        }
    }
    closedir(d);
#endif

    return 0;
}
