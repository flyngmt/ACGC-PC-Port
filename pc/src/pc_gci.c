#include "pc_gci.h"
#include "pc_platform.h"
#include "pc_save_bswap.h"
#include "m_flashrom.h"
#include "m_land.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dolphin/os.h>

#define PC_SAVE_PENDING_SUFFIX ".write"
#define PC_SAVE_PRESERVED_PENDING_SUFFIX ".write.temp"
#define PC_SAVE_ROTATION_SUFFIX ".temp"
#define PC_SAVE_LEGACY_PENDING_SUFFIX ".tmp"

static const char* const pc_gci_rotation_suffixes[] = {
    "", ".bak1", ".bak2", ".bak3", PC_SAVE_ROTATION_SUFFIX,
};

#define GCI_HEADER_SIZE      sizeof(CARDDir)
#define GCI_FILE_DATA_SIZE   mCD_LAND_SAVE_SIZE
#define GCI_OTHERS_OFFSET    0
#define GCI_SAVE_MAIN_OFFSET OTHERS_SIZE
#define GCI_SAVE_BACK_OFFSET (OTHERS_SIZE + sizeof(Save))
#define GCI_SECTOR_SIZE      mCD_MEMCARD_SECTORSIZE

_Static_assert(sizeof(mNW_original_design_c) == 0x220, "mNW_original_design_c disk layout changed");
_Static_assert(offsetof(mQst_base_c, time_limit) == 0x04, "mQst_base_c.time_limit disk offset changed");
_Static_assert(sizeof(mQst_base_c) == 0x0C, "mQst_base_c disk layout changed");
_Static_assert(sizeof(mQst_delivery_c) == 0x28, "mQst_delivery_c disk layout changed");
_Static_assert(sizeof(mQst_errand_c) == 0x58, "mQst_errand_c disk layout changed");
_Static_assert(sizeof(mQst_contest_c) == 0x28, "mQst_contest_c disk layout changed");
_Static_assert(sizeof(Private_c) == 0x2440, "Private_c disk layout changed");
_Static_assert(offsetof(Save_t, land_info) == 0x9120, "Save_t.land_info disk offset changed");
_Static_assert(sizeof(Save_t) == 0x242A0, "Save_t disk layout changed");
_Static_assert(sizeof(Save) == 0x26000, "Save disk layout changed");
_Static_assert(sizeof(mCD_keep_original_c) == 0xCCA0, "mCD_keep_original_c disk layout changed");
_Static_assert(sizeof(mCD_keep_mail_c) == 0xBAC0, "mCD_keep_mail_c disk layout changed");
_Static_assert(sizeof(mCD_keep_diary_c) == 0xBA20, "mCD_keep_diary_c disk layout changed");
_Static_assert(OTHERS_SIZE == 0x26000, "GCI auxiliary block layout changed");
_Static_assert(GCI_SAVE_MAIN_OFFSET == 0x26000, "GCI main save offset changed");
_Static_assert(GCI_SAVE_BACK_OFFSET == 0x4C000, "GCI backup save offset changed");

static FILE* pc_fopen(const char* path, const char* mode) {
#ifdef _MSC_VER
    FILE* file = NULL;
    return fopen_s(&file, path, mode) == 0 ? file : NULL;
#else
    return fopen(path, mode);
#endif
}

static void put_be32(u8* dst, u32 val) {
    dst[0] = (u8)(val >> 24);
    dst[1] = (u8)(val >> 16);
    dst[2] = (u8)(val >> 8);
    dst[3] = (u8)(val);
}

static void put_be16(u8* dst, u16 val) {
    dst[0] = (u8)(val >> 8);
    dst[1] = (u8)(val);
}

static u16 get_be16(const void* source) {
    const u8* bytes = (const u8*)source;
    return ((u16)bytes[0] << 8) | bytes[1];
}

static u32 get_be32(const void* source) {
    const u8* bytes = (const u8*)source;
    return ((u32)bytes[0] << 24) | ((u32)bytes[1] << 16) | ((u32)bytes[2] << 8) | bytes[3];
}

static u16 pc_checksum_be(const u8* data, u32 size, u16 old_checksum) {
    u32 i;
    u32 sum = 0;
    u32 num_u16 = size / 2;
    u16 raw;

    for (i = 0; i < num_u16; i++) {
        u16 val = get_be16(data + i * 2);
        sum += val;
    }

    /* Two's complement: subtract old_checksum (included in sum), negate */
    raw = (u16)((sum - old_checksum) & 0xFFFF);
    return (u16)((~raw + 1) & 0xFFFF);
}

static int pc_gci_sibling_path(char* output, const char* base, const char* suffix) {
    int length = snprintf(output, PC_GCI_PATH_MAX, "%s%s", base, suffix);
    return length >= 0 && length < PC_GCI_PATH_MAX;
}

static int pc_gci_remove_if_present(const char* path) {
    return remove(path) == 0 || errno == ENOENT;
}

static int pc_gci_move_if_present(const char* source, const char* destination) {
    struct stat st;
    if (stat(source, &st) != 0) return errno == ENOENT;
    if (stat(destination, &st) == 0 || errno != ENOENT) return FALSE;
    return rename(source, destination) == 0;
}

static int pc_gci_move_rotation_file(const char* base, int from, int to) {
    char source[PC_GCI_PATH_MAX], destination[PC_GCI_PATH_MAX];
    return pc_gci_sibling_path(source, base, pc_gci_rotation_suffixes[from]) &&
           pc_gci_sibling_path(destination, base, pc_gci_rotation_suffixes[to]) &&
           pc_gci_move_if_present(source, destination);
}

static void pc_gci_restore_backups(const char* base, int first) {
    int i;
    for (i = first; i < ARRAY_COUNT(pc_gci_rotation_suffixes); i++) {
        if (!pc_gci_move_rotation_file(base, i, i - 1)) break;
    }
}

static int pc_gci_rotate_backups(const char* base) {
    int destination;
    for (destination = ARRAY_COUNT(pc_gci_rotation_suffixes) - 1; destination > 0; destination--) {
        if (!pc_gci_move_rotation_file(base, destination - 1, destination)) {
            pc_gci_restore_backups(base, destination + 1);
            return FALSE;
        }
    }
    return TRUE;
}

static pc_save_result pc_gci_read_image(const char* path, pc_gci_image* image);

static int pc_gci_preserve_pending(const char* base, const char* pending, const char* preserved) {
    pc_gci_image image;
    pc_save_result result = pc_gci_read_image(pending, &image);
    if (result == PC_SAVE_MISSING) return TRUE;
    if (result == PC_SAVE_IO_ERROR) return FALSE;
    if (result == PC_SAVE_INVALID) {
        if (pc_gci_read(base, &image) != PC_SAVE_LOADED) return FALSE;
        pc_gci_free(&image);
        return pc_gci_remove_if_present(pending);
    }
    pc_gci_free(&image);
    return pc_gci_remove_if_present(preserved) && pc_gci_move_if_present(pending, preserved);
}

int pc_gci_write(const char* gci_path, const Save_t* save, const mCD_keep_mail_c* mail,
                 const mCD_keep_original_c* original, const mCD_keep_diary_c* diary) {
    FILE* fp;
    u8* file_data;
    CARDDir dir_hdr;
    Save_t* save_copy;
    u16 checksum;
    u8* others_ptr;
    char tmp_path[PC_GCI_PATH_MAX];
    char preserved_path[PC_GCI_PATH_MAX];
    char rotation_path[PC_GCI_PATH_MAX];

    if (!save || !mail || !original || !diary) return FALSE;
    if (!pc_gci_sibling_path(tmp_path, gci_path, PC_SAVE_PENDING_SUFFIX)) return FALSE;
    if (!pc_gci_sibling_path(preserved_path, gci_path, PC_SAVE_PRESERVED_PENDING_SUFFIX) ||
        !pc_gci_sibling_path(rotation_path, gci_path, PC_SAVE_ROTATION_SUFFIX)) return FALSE;

    file_data = (u8*)calloc(1, GCI_FILE_DATA_SIZE);
    if (!file_data) return FALSE;

    others_ptr = file_data + GCI_OTHERS_OFFSET;
    {
        const char* title = "DobutsunomoriP (AC PC Port)";
        u8* comment = others_ptr;
        memset(comment, 0, CARD_COMMENT_SIZE);
        memcpy(comment, title, strlen(title));
        memcpy(comment + 32, save->land_info.name, 8);
    }

    /* ARAM blocks: mail, original, diary (GC/Dolphin order).
     * Set landid on mail block so load-time detection identifies the order. */
    {
        u32 offset = sizeof(MemcardHeader_c) + 32;
        u16 land_id = save->land_info.id;

        offset = ALIGN_NEXT(offset, 32);
        {
            u8* blk = others_ptr + offset;
            u32 sz = mCD_KEEP_MAIL_SIZE;
            memcpy(blk, mail, sz);
            pc_save_bswap_keep_mail((mCD_keep_mail_c*)blk, PC_BSWAP_TO_BE);

            put_be16(blk + 2, land_id);
            /* Recompute BE checksum over the bswapped block so Dolphin's
             * mFRm_ReturnCheckSum validates. */
            blk[0] = 0;
            blk[1] = 0;
            put_be16(blk, pc_checksum_be(blk, sz, 0));
        }
        offset += mCD_KEEP_MAIL_SIZE;

        offset = ALIGN_NEXT(offset, 32);
        {
            u8* blk = others_ptr + offset;
            u32 sz = mCD_KEEP_ORIGINAL_SIZE;
            memcpy(blk, original, sz);
            pc_save_bswap_keep_original((mCD_keep_original_c*)blk, PC_BSWAP_TO_BE);
            blk[0] = 0;
            blk[1] = 0;
            put_be16(blk, pc_checksum_be(blk, sz, 0));
        }
        offset += mCD_KEEP_ORIGINAL_SIZE;

        offset = ALIGN_NEXT(offset, 32);
        {
            u8* blk = others_ptr + offset;
            u32 sz = mCD_KEEP_DIARY_SIZE;
            memcpy(blk, diary, sz);
            pc_save_bswap_keep_diary((mCD_keep_diary_c*)blk, PC_BSWAP_TO_BE);
            blk[0] = 0;
            blk[1] = 0;
            put_be16(blk, pc_checksum_be(blk, sz, 0));
        }
    }

    save_copy = (Save_t*)(file_data + GCI_SAVE_MAIN_OFFSET);
    memcpy(save_copy, save, sizeof(Save_t));

    pc_save_bswap(save_copy, PC_BSWAP_TO_BE);
    {
        u8* chk_ptr = (u8*)&save_copy->save_check.checksum;
        chk_ptr[0] = 0;
        chk_ptr[1] = 0;
    }
    checksum = pc_checksum_be((const u8*)save_copy, sizeof(Save_t), 0);
    put_be16((u8*)&save_copy->save_check.checksum, checksum);

    memcpy(file_data + GCI_SAVE_BACK_OFFSET, file_data + GCI_SAVE_MAIN_OFFSET, sizeof(Save));

    memset(&dir_hdr, 0, sizeof(dir_hdr));
    memcpy(dir_hdr.gameName, "GAFE", 4);
    memcpy(dir_hdr.company, "01", 2);
    dir_hdr.bannerFormat = 0;
    memcpy(dir_hdr.fileName, "DobutsunomoriP_MURA", sizeof("DobutsunomoriP_MURA") - 1);
    {
        time_t unix_now = time(NULL);
        u32 gc_secs = (u32)(unix_now - 946684800LL);
        put_be32((u8*)&dir_hdr.time, gc_secs);
    }
    put_be32((u8*)&dir_hdr.iconAddr, 0xFFFFFFFF);
    put_be16((u8*)&dir_hdr.iconFormat, 0);
    put_be16((u8*)&dir_hdr.iconSpeed, 0);
    dir_hdr.permission = 0x04;
    dir_hdr.copyTimes = 0;
    put_be16((u8*)&dir_hdr.startBlock, 5);
    put_be16((u8*)&dir_hdr.length, (u16)(GCI_FILE_DATA_SIZE / GCI_SECTOR_SIZE));
    put_be32((u8*)&dir_hdr.commentAddr, 0);

    if (!pc_gci_preserve_pending(gci_path, tmp_path, preserved_path)) {
        free(file_data);
        return FALSE;
    }
    fp = pc_fopen(tmp_path, "wb");
    if (!fp) {
        OSReport("[PC] GCI save: failed to open temp file '%s'\n", tmp_path);
        free(file_data);
        return FALSE;
    }

    if (fwrite(&dir_hdr, GCI_HEADER_SIZE, 1, fp) != 1 ||
        fwrite(file_data, GCI_FILE_DATA_SIZE, 1, fp) != 1) {
        OSReport("[PC] GCI save: fwrite failed (disk full?)\n");
        fclose(fp);
        remove(tmp_path);
        free(file_data);
        return FALSE;
    }

    {
        int flush_result = pc_platform_flush_file(fp);
        int close_result = fclose(fp);
        if (!flush_result || close_result != 0) {
            OSReport("[PC] GCI save: flush/close failed; existing saves retained\n");
            free(file_data);
            return FALSE;
        }
    }
    free(file_data);

    if (!pc_gci_remove_if_present(rotation_path) || !pc_gci_rotate_backups(gci_path)) {
        OSReport("[PC] GCI save: backup rotation failed; save replacement aborted\n");
        return FALSE;
    }
    if (rename(tmp_path, gci_path) != 0) {
        OSReport("[PC] GCI save: rename '%s' -> '%s' failed, recovering...\n",
                 tmp_path, gci_path);
        pc_gci_restore_backups(gci_path, 1);
        return FALSE;
    }

    pc_gci_remove_if_present(rotation_path);
    pc_gci_remove_if_present(preserved_path);
    OSReport("[PC] GCI save: written successfully to %s (backups rotated)\n", gci_path);
    return TRUE;
}

static Save_t* pc_gci_select_copy(u8* file_data) {
    int copy;
    for (copy = 0; copy < 2; copy++) {
        Save_t* save = (Save_t*)(file_data + GCI_SAVE_MAIN_OFFSET + copy * sizeof(Save));
        u32 version = get_be32(&save->save_check.version);
        u16 land_id = get_be16(&save->land_info.id);
        u16 check_id = get_be16(&save->save_check.land_id);
        if ((version == 5 || version == mFRm_VERSION) && get_be32(&save->save_check.code) == mFRm_SAVE_ID &&
            mLd_CHECK_LAND_ID(check_id) && check_id == land_id &&
            pc_checksum_be((const u8*)save, sizeof(Save), 0) == 0) {
            if (copy != 0) OSReport("[PC] GCI: main invalid, using embedded backup\n");
            return save;
        }
    }
    OSReport("[PC] GCI: neither main nor embedded backup passes GC validation\n");
    return NULL;
}

static int pc_gci_aux_offsets(const u8* data, u16 land_id, u32 offsets[mCD_ARAM_DATA_NUM]) {
    static const u32 block_sizes[mCD_ARAM_DATA_NUM] = {
        [mCD_ARAM_DATA_ORIGINAL] = mCD_KEEP_ORIGINAL_SIZE,
        [mCD_ARAM_DATA_MAIL] = mCD_KEEP_MAIL_SIZE,
        [mCD_ARAM_DATA_DIARY] = mCD_KEEP_DIARY_SIZE,
    };
    u32 start = ALIGN_NEXT(sizeof(MemcardHeader_c) + 32, 32);
    u16 first_land_id = get_be16(data + start + offsetof(mCD_keep_mail_c, landid));
    int prefer_legacy = first_land_id != land_id;
    int attempt, i;
    for (attempt = 0; attempt < 2; attempt++) {
        int legacy = prefer_legacy ^ attempt;
        u32 offset = ALIGN_NEXT(sizeof(MemcardHeader_c) + 32, 32);
        int first = legacy ? mCD_ARAM_DATA_ORIGINAL : mCD_ARAM_DATA_MAIL;
        int second = legacy ? mCD_ARAM_DATA_MAIL : mCD_ARAM_DATA_ORIGINAL;
        offsets[first] = offset;
        offset += block_sizes[first];
        offsets[second] = offset;
        offset += block_sizes[second];
        offsets[mCD_ARAM_DATA_DIARY] = offset;
        for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
            if (offsets[i] + block_sizes[i] > OTHERS_SIZE ||
                pc_checksum_be(data + offsets[i], block_sizes[i], 0) != 0) break;
        }
        if (i == mCD_ARAM_DATA_NUM) return TRUE;
    }
    /* Reject damaged auxiliary data instead of GC's blank-block fallback, which could erase the only copy. */
    OSReport("[PC] GCI: auxiliary checksums invalid; refusing destructive recovery\n");
    return FALSE;
}

static pc_save_result pc_gci_read_image(const char* path, pc_gci_image* image) {
    FILE* fp = pc_fopen(path, "rb");
    CARDDir header;
    u8* data;
    Save_t* save;
    u32 offsets[mCD_ARAM_DATA_NUM];
    pc_save_result result;

    if (!fp) return errno == ENOENT ? PC_SAVE_MISSING : PC_SAVE_IO_ERROR;
    if (fread(&header, GCI_HEADER_SIZE, 1, fp) != 1) {
        result = ferror(fp) ? PC_SAVE_IO_ERROR : PC_SAVE_INVALID;
        fclose(fp);
        return result;
    }
    if (memcmp(header.gameName, "GAF", 3) != 0 ||
        memcmp(header.fileName, "DobutsunomoriP_MURA", sizeof("DobutsunomoriP_MURA")) != 0 ||
        get_be16(&header.length) != GCI_FILE_DATA_SIZE / GCI_SECTOR_SIZE) {
        fclose(fp);
        return PC_SAVE_INVALID;
    }
    data = (u8*)malloc(GCI_FILE_DATA_SIZE);
    if (!data) {
        fclose(fp);
        return PC_SAVE_IO_ERROR;
    }
    if (fread(data, GCI_FILE_DATA_SIZE, 1, fp) != 1) {
        result = ferror(fp) ? PC_SAVE_IO_ERROR : PC_SAVE_INVALID;
        fclose(fp);
        free(data);
        return result;
    }
    fclose(fp);
    save = pc_gci_select_copy(data);
    if (save == NULL) {
        free(data);
        return PC_SAVE_INVALID;
    }
    if (!pc_gci_aux_offsets(data, get_be16(&save->land_info.id), offsets)) {
        free(data);
        return PC_SAVE_INVALID;
    }
    if (pc_save_bswap_verify_roundtrip((const u8*)save, sizeof(Save_t)) != 0 ||
        pc_save_bswap_verify_roundtrip_mail(data + offsets[mCD_ARAM_DATA_MAIL], sizeof(mCD_keep_mail_c)) != 0 ||
        pc_save_bswap_verify_roundtrip_original(data + offsets[mCD_ARAM_DATA_ORIGINAL], sizeof(mCD_keep_original_c)) != 0 ||
        pc_save_bswap_verify_roundtrip_diary(data + offsets[mCD_ARAM_DATA_DIARY], sizeof(mCD_keep_diary_c)) != 0) {
        OSReport("[PC] GCI: byte-order conversion is not lossless; load aborted\n");
        free(data);
        return PC_SAVE_INVALID;
    }
    pc_save_bswap(save, PC_BSWAP_FROM_BE);
    if (save->save_check.version == 5) {
        save->saved_auto_nwrite_time = save->save_check.time;
    }
    pc_save_bswap_keep_mail((mCD_keep_mail_c*)(data + offsets[mCD_ARAM_DATA_MAIL]), PC_BSWAP_FROM_BE);
    pc_save_bswap_keep_original((mCD_keep_original_c*)(data + offsets[mCD_ARAM_DATA_ORIGINAL]), PC_BSWAP_FROM_BE);
    pc_save_bswap_keep_diary((mCD_keep_diary_c*)(data + offsets[mCD_ARAM_DATA_DIARY]), PC_BSWAP_FROM_BE);
    image->storage = data;
    image->save = save;
    image->mail = (mCD_keep_mail_c*)(data + offsets[mCD_ARAM_DATA_MAIL]);
    image->original = (mCD_keep_original_c*)(data + offsets[mCD_ARAM_DATA_ORIGINAL]);
    image->diary = (mCD_keep_diary_c*)(data + offsets[mCD_ARAM_DATA_DIARY]);
    return PC_SAVE_LOADED;
}

static const char* const pc_gci_pending_suffixes[] = {
    PC_SAVE_PENDING_SUFFIX,
    PC_SAVE_PRESERVED_PENDING_SUFFIX,
    PC_SAVE_LEGACY_PENDING_SUFFIX,
};

static pc_save_result pc_gci_merge_failure(pc_save_result previous, pc_save_result next) {
    if (previous == PC_SAVE_IO_ERROR || next == PC_SAVE_IO_ERROR) return PC_SAVE_IO_ERROR;
    if (previous == PC_SAVE_INVALID || next == PC_SAVE_INVALID) return PC_SAVE_INVALID;
    return PC_SAVE_MISSING;
}

pc_save_result pc_gci_read(const char* base, pc_gci_image* image) {
    char path[PC_GCI_PATH_MAX];
    pc_save_result result = pc_gci_read_image(base, image);
    pc_save_result candidate;
    int i;
    if (result == PC_SAVE_LOADED) return result;

    for (i = 0; i < ARRAY_COUNT(pc_gci_pending_suffixes); i++) {
        if (!pc_gci_sibling_path(path, base, pc_gci_pending_suffixes[i])) return PC_SAVE_IO_ERROR;
        candidate = pc_gci_read_image(path, image);
        if (candidate == PC_SAVE_LOADED) {
            OSReport("[PC] GCI: recovered from '%s'\n", path);
            return candidate;
        }
        result = pc_gci_merge_failure(result, candidate);
    }
    for (i = 1; i < ARRAY_COUNT(pc_gci_rotation_suffixes); i++) {
        if (!pc_gci_sibling_path(path, base, pc_gci_rotation_suffixes[i])) return PC_SAVE_IO_ERROR;
        candidate = pc_gci_read_image(path, image);
        if (candidate == PC_SAVE_LOADED) {
            OSReport("[PC] GCI: recovered from '%s'\n", path);
            return candidate;
        }
        result = pc_gci_merge_failure(result, candidate);
    }
    return result;
}

void pc_gci_free(pc_gci_image* image) {
    free(image->storage);
    memset(image, 0, sizeof(*image));
}

static int pc_gci_is_gci_file(const char* path) {
    FILE* fp;
    u8 game_name[4];
    struct stat st;

    if (stat(path, &st) != 0 || st.st_size < (long)(GCI_HEADER_SIZE + GCI_FILE_DATA_SIZE)) {
        return FALSE;
    }

    fp = pc_fopen(path, "rb");
    if (fp == NULL) {
        return FALSE;
    }
    if (fread(game_name, sizeof(game_name), 1, fp) != 1) {
        fclose(fp);
        return FALSE;
    }
    fclose(fp);
    return memcmp(game_name, "GAF", 3) == 0;
}

/* Stage imports to avoid partial destinations; retain the source for recovery. */
static int pc_gci_copy_gci_if_absent(const char* source, const char* destination) {
    FILE* input;
    FILE* output;
    char import_path[PC_GCI_PATH_MAX];
    u8 buffer[4 * 1024];
    size_t count;
    int ok = TRUE;
    struct stat st;

    if (strcmp(source, destination) == 0 || stat(destination, &st) == 0 ||
        !pc_gci_is_gci_file(source)) {
        return FALSE;
    }
    if (snprintf(import_path, sizeof(import_path), "%s.import", destination) >=
        (int)sizeof(import_path)) {
        return FALSE;
    }

    input = pc_fopen(source, "rb");
    if (input == NULL) {
        return FALSE;
    }
    remove(import_path);
    output = pc_fopen(import_path, "wb");
    if (output == NULL) {
        fclose(input);
        return FALSE;
    }

    while ((count = fread(buffer, 1, sizeof(buffer), input)) != 0) {
        if (fwrite(buffer, 1, count, output) != count) {
            ok = FALSE;
            break;
        }
    }
    if (ferror(input)) ok = FALSE;
    if (!pc_platform_flush_file(output)) ok = FALSE;
    if (fclose(output) != 0) ok = FALSE;
    fclose(input);

    if (!ok || stat(destination, &st) == 0 || rename(import_path, destination) != 0) {
        remove(import_path);
        return FALSE;
    }

    OSReport("[PC] Imported legacy save '%s' -> '%s' (source retained)\n",
             source, destination);
    return TRUE;
}

static void pc_gci_copy_companions(const char* source, const char* destination) {
    char source_path[PC_GCI_PATH_MAX];
    char destination_path[PC_GCI_PATH_MAX];
    int i;
    for (i = 1; i < ARRAY_COUNT(pc_gci_rotation_suffixes); i++) {
        if (!pc_gci_sibling_path(source_path, source, pc_gci_rotation_suffixes[i]) ||
            !pc_gci_sibling_path(destination_path, destination, pc_gci_rotation_suffixes[i])) return;
        pc_gci_copy_gci_if_absent(source_path, destination_path);
    }
    for (i = 0; i < ARRAY_COUNT(pc_gci_pending_suffixes); i++) {
        if (!pc_gci_sibling_path(source_path, source, pc_gci_pending_suffixes[i]) ||
            !pc_gci_sibling_path(destination_path, destination, pc_gci_pending_suffixes[i])) return;
        pc_gci_copy_gci_if_absent(source_path, destination_path);
    }
}

int pc_gci_import(const char* source, const char* destination) {
    if (!pc_gci_copy_gci_if_absent(source, destination)) return FALSE;
    pc_gci_copy_companions(source, destination);
    return TRUE;
}
