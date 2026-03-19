#include "m_card.h"

#include "card.h"
#include "card/CARDBios.h"
#include "card/CARDCheck.h"
#include "card/CARDMount.h"
#include "card/__card.h"
#include "graph.h"
#include "lb_rtc.h"
#include "libultra/libultra.h"
#include "m_actor_type.h"
#include "m_all_grow_ovl.h"
#include "m_event.h"
#include "m_flashrom.h"
#include "m_home.h"
#include "m_island.h"
#include "m_land.h"
#include "m_land_h.h"
#include "m_mail.h"
#include "m_malloc.h"
#include "libc64/sleep.h"
#include "m_common_data.h"
#include "m_font.h"
#include "jsyswrap.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_private.h"
#include "m_private_h.h"
#include "m_quest.h"
#include "m_time.h"
#include "types.h"
#include "zurumode.h"
#include "m_house.h"
#include "m_cockroach.h"
#include "m_start_data_init.h"
#include <string.h>

typedef struct card_bg_info {
    CARDFileInfo fileInfo;
    s32 fileNo;
    int space_proc;
    int tries;
    void* data;
    s32 offset;
    s32 length;
} mCD_bg_info_c;

enum {
    mCD_WBC_CHECK_SLOT,
    mCD_WBC_INIT,
    mCD_WBC_CHECK_FILESYSTEM,
    mCD_WBC_OPEN_FILE,
    mCD_WBC_READ,
    mCD_WBC_WRITE,

    mCD_WBC_FINISHED,
    mCD_WBC_NUM = mCD_WBC_FINISHED
};

enum {
    mCD_SAVEHOME_BG_PROC_GET_AREA,
    mCD_SAVEHOME_BG_PROC_ERASE_DUMMY,
    mCD_SAVEHOME_BG_PROC_CHECK_SLOT,
    mCD_SAVEHOME_BG_PROC_READ_SEND_PRESENT,
    mCD_SAVEHOME_BG_PROC_WRITE_PRESENT,
    mCD_SAVEHOME_BG_PROC_GET_SLOT,
    mCD_SAVEHOME_BG_PROC_CREATE_FILE,
    mCD_SAVEHOME_BG_PROC_CHECK_REPAIR_LAND,
    mCD_SAVEHOME_BG_PROC_REPAIR_LAND,
    mCD_SAVEHOME_BG_PROC_SET_FILE_PERMISSION,
    mCD_SAVEHOME_BG_PROC_SET_DATA,
    mCD_SAVEHOME_BG_PROC_WRITE_MAIN_2,
    mCD_SAVEHOME_BG_PROC_WRITE_BK,
    mCD_SAVEHOME_BG_PROC_SET_OTHERS,
    mCD_SAVEHOME_BG_PROC_WRITE_OTHERS,
    mCD_SAVEHOME_BG_PROC_GET_STATUS_2,
    mCD_SAVEHOME_BG_PROC_SET_STATUS_2,
    mCD_SAVEHOME_BG_PROC_RENAME,

    mCD_SAVEHOME_BG_PROC_NUM
};

static char mCD_file_name[32] = "DobutsunomoriP_MURA";
static int l_mcd_err_debug[mCD_ERROR_NUM] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
static s32 l_mcd_err_result = CARD_RESULT_READY;
static mCD_bg_info_c l_mcd_bg_info;

static void mCD_ClearErrInfo(void) {
    bzero(l_mcd_err_debug, sizeof(l_mcd_err_debug));
    l_mcd_err_result = 0;
}

static void mCD_OnErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = TRUE;
    }
}

static void mCD_OffErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = FALSE;
    }
}

static void mCD_SetErrResult(s32 result) {
    l_mcd_err_result = result;
}

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 250, 100, 250, 255);
    gfxprint_locate8x8(gfxprint, 22, 3);

    if (l_mcd_err_debug[mCD_ERROR_NOT_ENABLED]) {
        gfxprint_printf(gfxprint, "N");
    }

    if (l_mcd_err_debug[mCD_ERROR_AREA]) {
        gfxprint_printf(gfxprint, "A");
    }

    if (l_mcd_err_debug[mCD_ERROR_WRITE]) {
        gfxprint_printf(gfxprint, "W");
    }

    if (l_mcd_err_debug[mCD_ERROR_READ]) {
        gfxprint_printf(gfxprint, "R");
    }

    if (l_mcd_err_debug[mCD_ERROR_CHECKSUM]) {
        gfxprint_printf(gfxprint, "C");
    }

    if (l_mcd_err_debug[mCD_ERROR_OUTDATED]) {
        gfxprint_printf(gfxprint, "O");
    }

    if (l_mcd_err_debug[mCD_ERROR_CREATE]) {
        gfxprint_printf(gfxprint, "c");
    }

    if (l_mcd_err_result != CARD_RESULT_READY) {
        gfxprint_printf(gfxprint, "%d", l_mcd_err_result);
    }
}

static void* mCD_malloc_32(u32 size) {
    return zelda_malloc_align(size, 32);
}

static int mCD_check_card_common(s32* result, s32 req_sector_size, s32 chan) {
    s32 mem_size = 0;
    s32 sector_size = 0;
    int res = mCD_RESULT_BUSY;

    *result = CARDProbeEx(chan, &mem_size, &sector_size);

    if (*result == CARD_RESULT_READY && sector_size == req_sector_size) {
        res = mCD_RESULT_SUCCESS;
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_check_card(s32* result, s32 req_sector_size, s32 chan) {
    int ms = 0;
    int check_common_res = mCD_RESULT_BUSY;
    int res = mCD_RESULT_ERROR;

    while (check_common_res == mCD_RESULT_BUSY && ms < 500) {
        check_common_res = mCD_check_card_common(result, req_sector_size, chan);

        if (check_common_res == mCD_RESULT_BUSY) {
            msleep(1);
            ms++;
        }
    }

    if (check_common_res == mCD_RESULT_SUCCESS) {
        res = mCD_RESULT_SUCCESS;
    }

    return res;
}

static int mCD_check_sector_size(u32 req_sector_size, s32 chan) {
    s32 mem_size = 0;
    s32 sector_size = 0;
    int ms = 0;
    s32 result = CARD_RESULT_BUSY;
    int res = mCD_RESULT_ERROR;

    while (result == CARD_RESULT_BUSY && ms < 500) {
        result = CARDProbeEx((s32)chan, &mem_size, &sector_size);

        if (result == CARD_RESULT_BUSY) {
            msleep(1);
            ms++;
        }
    }

    if (result == CARD_RESULT_READY) {
        if (req_sector_size == sector_size) {
            res = mCD_RESULT_SUCCESS;
        } else {
            res = mCD_RESULT_BUSY;
        }
    }

    return res;
}

static int mCD_get_file_num_com(int chan) {
    CARDFileInfo fileInfo;
    s32 num = 0;
    s32 file_no;

    for (file_no = 0; file_no < CARD_MAX_FILE; file_no++) {
        s32 result = CARDFastOpen((s32)chan, file_no, &fileInfo);

        if (result == CARD_RESULT_READY) {
            num++;
            CARDClose(&fileInfo);
        }
    }

    return num;
}

static int mCD_get_file_num(void* workArea, int chan) {
    int num = 0;
    s32 result;

    if (workArea != NULL && mCD_check_card(&result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
        result = CARDMount((s32)chan, workArea, NULL);

        if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
            result = CARDCheck((s32)chan);
            num = mCD_get_file_num_com(chan);
            CARDUnmount((s32)chan);
        } else if (result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }
    }

    return num;
}

extern void mCD_init_card(void) {
    CARDInit();
}

static void mCD_ClearCardBgInfo(mCD_bg_info_c* bg_info) {
    bzero(bg_info, sizeof(mCD_bg_info_c));
}

static void mCD_StartSetCardBgInfo(void) {
    mCD_ClearCardBgInfo(&l_mcd_bg_info);
}

static int mCD_get_space_bg_get_slot(s32* freeBlocks, mCD_bg_info_c* bg_info, s32 chan, s32* result, void* workArea) {
    int res;

    bg_info->tries++;
    res = mCD_check_card_common(result, mCD_MEMCARD_SECTORSIZE, (s32)chan);
    if (res == mCD_RESULT_SUCCESS && workArea != NULL) {
        *freeBlocks = 0;
        *result = CARDMountAsync((s32)chan, workArea, NULL, NULL);

        if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        } else if (*result != CARD_RESULT_READY && *result != CARD_RESULT_BROKEN) {
            res = mCD_RESULT_ERROR;
        }

        bg_info->tries = 0;
    } else if (res != mCD_RESULT_BUSY) {
        *freeBlocks = 0;
        res = mCD_RESULT_ERROR;
        bg_info->tries = 0;
    } else if (bg_info->tries >= 100) {
        *freeBlocks = 0;
        res = mCD_RESULT_ERROR;
        bg_info->tries = 0;
    }

    return res;
}

static int mCD_get_space_bg_main(s32* freeBlocks, mCD_bg_info_c* bg_info, s32 chan, s32* result, void* workArea) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN) {
        *result = CARDCheck((s32)chan);

        if (*result == CARD_RESULT_READY) {
            s32 freeFiles;

            *result = CARDFreeBlocks((s32)chan, freeBlocks, &freeFiles);
            if (*result == CARD_RESULT_READY) {
                res = mCD_RESULT_SUCCESS;
            } else {
                res = mCD_RESULT_ERROR;
            }
        } else {
            res = mCD_RESULT_ERROR;
        }

        CARDUnmount((s32)chan);
    } else if (*result != CARD_RESULT_BUSY) {
        if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

typedef int (*mCD_GET_SPACE_BG_PROC)(s32*, mCD_bg_info_c*, s32, s32*, void*);
static int mCD_get_space_bg(s32* freeBytes, s32 chan, s32* result, void* workArea) {
    static mCD_GET_SPACE_BG_PROC get_proc[mCD_SPACE_BG_NUM] = { &mCD_get_space_bg_get_slot, &mCD_get_space_bg_main };
    mCD_bg_info_c* bg_info = &l_mcd_bg_info;
    u8 proc_type = bg_info->space_proc;
    int res = mCD_RESULT_BUSY;

    *freeBytes = 0;
    if (proc_type < mCD_SPACE_BG_NUM) {
        int proc_res = (*get_proc[proc_type])(freeBytes, bg_info, chan, result, workArea);

        if (proc_res == mCD_RESULT_SUCCESS) {
            bg_info->space_proc++;

            if (bg_info->space_proc >= mCD_SPACE_BG_NUM) {
                res = mCD_RESULT_SUCCESS;
                mCD_ClearCardBgInfo(bg_info);
            }
        } else if (proc_res != mCD_RESULT_BUSY) {
            res = mCD_RESULT_ERROR;
            mCD_ClearCardBgInfo(bg_info);
        }
    } else {
        res = mCD_RESULT_ERROR;
        mCD_ClearCardBgInfo(bg_info);
    }

    return res;
}

static void mCD_close_and_unmount(CARDFileInfo* fileInfo, s32 chan) {
    CARDClose(fileInfo);
    CARDUnmount(chan);
}

static int mCD_bg_check_slot(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename, s32 data_len,
    u32 length, s32 offset, void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;
    int common_res = mCD_check_card_common(result, mCD_MEMCARD_SECTORSIZE, chan);

    bg_info->tries++;
    if (common_res == mCD_RESULT_SUCCESS) {
        bg_info->space_proc++;
        bg_info->tries = 0;
        res = mCD_RESULT_SUCCESS;
    } else if (common_res != mCD_RESULT_BUSY || bg_info->tries >= 100) {
        bg_info->tries = 0;
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_bg_init_com(mCD_bg_info_c* bg_info, s32 chan, s32* result, void** workArea_p, void** read_p, int read) {
    int res;

    *workArea_p = mCD_malloc_32(CARD_WORKAREA_SIZE);
    if (read == TRUE) {
        *read_p = mCD_malloc_32(mCD_MEMCARD_SECTORSIZE);
    }

    if (*workArea_p != NULL && (read == FALSE || (read == TRUE && *read_p != NULL))) {
        *result = CARDMountAsync((s32)chan, *workArea_p, NULL, NULL);

        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else if (*result == CARD_RESULT_BROKEN) {
            *result = CARDCheckAsync((s32)chan, NULL);

            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc = 3;
                res = mCD_RESULT_SUCCESS;
            } else {
                if (*result == CARD_RESULT_BROKEN || *result == CARD_RESULT_ENCODING) {
                    CARDUnmount((s32)chan);
                }

                res = mCD_RESULT_ERROR;
            }
        } else {
            if (*result == CARD_RESULT_ENCODING) {
                CARDUnmount((s32)chan);
            }

            res = mCD_RESULT_ERROR;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_bg_init(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename, s32 data_len,
                       u32 length, s32 offset, void** workArea_p, void** read_p, CARDStat* stat) {
    return mCD_bg_init_com(bg_info, chan, result, workArea_p, read_p, FALSE);
}

static int mCD_bg_check_filesystem(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                   s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                   CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDCheckAsync((s32)chan, NULL);
        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                  s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                  CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            CARDStat stat;

            bg_info->fileNo = bg_info->fileInfo.fileNo;
            *result = CARDGetStatus((s32)chan, bg_info->fileNo, &stat);
            if (*result == CARD_RESULT_READY && stat.length == length) {
                *result = CARDWriteAsync(&bg_info->fileInfo, data, data_len, offset, NULL);
                if (*result == CARD_RESULT_READY) {
                    bg_info->space_proc++;
                    res = mCD_RESULT_SUCCESS;
                } else {
                    mCD_close_and_unmount(&bg_info->fileInfo, (s32)chan);
                    res = mCD_RESULT_ERROR;
                }
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, (s32)chan);
                res = mCD_RESULT_ERROR;
            }
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_bg_write(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                              s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDWriteAsync(&bg_info->fileInfo, data, data_len, offset, NULL);
        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_bg_cleanup(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result != CARD_RESULT_BUSY) {
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        bg_info->space_proc++;
        res = mCD_RESULT_SUCCESS;
    }

    return res;
}

typedef int (*mCD_BG_PROC)(mCD_bg_info_c*, s32, s32*, void*, const char*, s32, u32, s32, void**, void**, CARDStat*);

/* @unused static int mCD_write_bg(void* data, const char* filename, s32 data_len, u32 length, s32 offset, s32 chan,
 * s32* result) */
static int mCD_write_bg(void* data, const char* filename, s32 data_len, u32 length, s32 offset,
                                         s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC wbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_write_bg_open_file,
        &mCD_write_bg_write,
        &mCD_write_bg_cleanup,
    };
    // clang-format on

    return 0;
}

static int mCD_bg_init_write_comp(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                   s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                   CARDStat* stat) {
    int res = mCD_bg_init_com(bg_info, chan, result, workArea_p, read_p, TRUE);

    if (res == mCD_RESULT_SUCCESS) {
        bg_info->data = data;
        bg_info->offset = offset;
        if (data_len < mCD_MEMCARD_SECTORSIZE) {
            bg_info->length = data_len;
        } else {
            bg_info->length = mCD_MEMCARD_SECTORSIZE;
        }
    }

    return res;
}

static int mCD_write_comp_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                       s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                       CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            CARDStat stat;

            bg_info->fileNo = bg_info->fileInfo.fileNo;
            *result = CARDGetStatus((s32)chan, bg_info->fileNo, &stat);
            if (*result == CARD_RESULT_READY && stat.length == length) {
                bzero(*read_p, mCD_MEMCARD_SECTORSIZE);
                *result = CARDReadAsync(&bg_info->fileInfo, *read_p, bg_info->length, bg_info->offset, NULL);
                if (*result == CARD_RESULT_READY) {
                    bg_info->space_proc++;
                    res = mCD_RESULT_SUCCESS;
                } else {
                    res = mCD_RESULT_ERROR;
                    mCD_close_and_unmount(&bg_info->fileInfo, chan);
                }
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                res = mCD_RESULT_ERROR;
            }
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_comp_bg_read(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                  s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                  CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result == CARD_RESULT_READY) {
        if (mem_cmp((u8*)*read_p, (u8*)bg_info->data, bg_info->length) == 0) {
            *result = CARDWriteAsync(&bg_info->fileInfo, bg_info->data, bg_info->length, bg_info->offset, NULL);
            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc++;
                res = mCD_RESULT_SUCCESS;
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                res = mCD_RESULT_ERROR;
            }
        } else {
            int ofs;

            bg_info->offset += mCD_MEMCARD_SECTORSIZE;
            ofs = bg_info->offset - offset;

            if (ofs >= data_len) {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                bg_info->space_proc = mCD_WBC_FINISHED;
                res = mCD_RESULT_SUCCESS;
            } else {
                if (data_len - ofs < mCD_MEMCARD_SECTORSIZE) {
                    bg_info->length = data_len - ofs; /* Remaining size less than memcard sector size */
                } else {
                    bg_info->length = mCD_MEMCARD_SECTORSIZE;
                }

                bg_info->data = (void*)((uintptr_t)data + ofs);
                bzero(*read_p, mCD_MEMCARD_SECTORSIZE);
                *result = CARDReadAsync(&bg_info->fileInfo, *read_p, bg_info->length, bg_info->offset, NULL);
                if (*result == CARD_RESULT_READY) {
                    bg_info->space_proc = mCD_WBC_READ;
                    res = mCD_RESULT_SUCCESS;
                } else {
                    mCD_close_and_unmount(&bg_info->fileInfo, chan);
                    res = mCD_RESULT_ERROR;
                }
            }
        }
    } else if (*result != CARD_RESULT_BUSY) {
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_comp_bg_write(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                   s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                   CARDStat* stat) {
    int res = mCD_RESULT_BUSY;
    int ofs;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        bg_info->offset += mCD_MEMCARD_SECTORSIZE;
        ofs = bg_info->offset - offset;

        if (ofs >= data_len) {
            mCD_close_and_unmount(&bg_info->fileInfo, chan);
            bg_info->space_proc = mCD_WBC_FINISHED;
            res = mCD_RESULT_SUCCESS;
        } else {
            if (data_len - ofs < mCD_MEMCARD_SECTORSIZE) {
                bg_info->length = data_len - ofs; /* Remaining size less than memcard sector size */
            } else {
                bg_info->length = mCD_MEMCARD_SECTORSIZE;
            }
            bg_info->data = (void*)((uintptr_t)data + ofs);
            bzero(*read_p, mCD_MEMCARD_SECTORSIZE);

            *result = CARDReadAsync(&bg_info->fileInfo, *read_p, bg_info->length, bg_info->offset, NULL);
            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc = mCD_WBC_READ;
                res = mCD_RESULT_SUCCESS;
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                res = mCD_RESULT_ERROR;
            }
        }
    } else if (*result != CARD_RESULT_BUSY) {
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_write_comp_bg(void* data, const char* filename, s32 data_len, u32 length, s32 offset, s32 chan,
                             s32* result) {
    static void* work_p = NULL;
    static void* read_p = NULL;
    // clang-format off
    static mCD_BG_PROC wcbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init_write_comp,
        &mCD_bg_check_filesystem,
        &mCD_write_comp_bg_open_file,
        &mCD_write_comp_bg_read,
        &mCD_write_comp_bg_write,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* bg_info = &l_mcd_bg_info;
    int proc = bg_info->space_proc;

    if (proc >= 0 && proc < mCD_WBC_NUM) {
        int success = (*wcbg_proc[proc])(bg_info, chan, result, data, filename, data_len, length, offset,
                                                        &work_p, &read_p, NULL);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == mCD_WBC_FINISHED) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }

            if (read_p != NULL) {
                zelda_free(read_p);
                read_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        if (read_p != NULL) {
            zelda_free(read_p);
            read_p = NULL;
        }

        mCD_ClearCardBgInfo(bg_info);
        work_p = NULL; // extra set
        res = mCD_RESULT_ERROR;
    }

    /* Debug display for error state */
    if (ZURUMODE2_ENABLED()) {
        if (res == mCD_RESULT_ERROR) {
            mCD_OnErrInfo(mCD_ERROR_WRITE);
            mCD_SetErrResult(*result);
        } else if (res == mCD_RESULT_SUCCESS) {
            mCD_OffErrInfo(mCD_ERROR_WRITE);
            mCD_SetErrResult(*result);
        }
    }

    return res;
}

static int mCD_read_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                 s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                 CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            *result = CARDReadAsync(&bg_info->fileInfo, data, data_len, offset, NULL);

            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc = 4;
                res = mCD_RESULT_SUCCESS;
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                res = mCD_RESULT_ERROR;
            }
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        if (*result == CARD_RESULT_BROKEN || *result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_read_bg_cleanup(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                               s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result != CARD_RESULT_BUSY) {
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        bg_info->space_proc++;
        res = mCD_RESULT_SUCCESS;
    }

    return res;
}

/* @unused */
static int mCD_read_bg(void* data, const char* filename, s32 data_len, u32 length, s32 offset, s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC rbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_read_bg_open_file,
        &mCD_read_bg_cleanup,
    };
    // clang-format on

    return 0;
}

static int mCD_read_fg(void* buf, const char* filename, s32 length, s32 offset, s32 chan, s32* result) {
    void* workArea;
    int res = mCD_RESULT_ERROR;

    if (buf != NULL && IS_ALIGNED((uintptr_t)buf, 32)) {
        int card_res = mCD_check_card(result, mCD_MEMCARD_SECTORSIZE, chan);

        if (card_res == mCD_RESULT_SUCCESS) {
            workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);

            if (workArea != NULL) {
                *result = CARDMount((s32)chan, workArea, NULL);
                if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN) {
                    *result = CARDCheck((s32)chan);
                    if (*result == CARD_RESULT_READY) {
                        CARDFileInfo fileInfo;

                        *result = CARDOpen((s32)chan, filename, &fileInfo);
                        if (*result == CARD_RESULT_READY) {
                            *result = CARDRead(&fileInfo, buf, length, offset);
                            if (*result == CARD_RESULT_READY) {
                                res = mCD_RESULT_SUCCESS;
                            }

                            mCD_close_and_unmount(&fileInfo, chan);
                        } else {
                            CARDUnmount((s32)chan);
                        }
                    } else {
                        CARDUnmount((s32)chan);
                    }
                } else if (*result == CARD_RESULT_ENCODING) {
                    CARDUnmount((s32)chan);
                }

                if (workArea != NULL) {
                    zelda_free(workArea);
                }
            }
        }
    } else {
        *result = CARD_RESULT_FATAL_ERROR;
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_find_fg(const char* filename, void* workArea, s32 chan, s32* result) {
    int res = FALSE;

    if (mCD_check_card(result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS && workArea != NULL) {
        *result = CARDMount((s32)chan, workArea, NULL);
        if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN) {
            *result = CARDCheck((s32)chan);
            if (*result == CARD_RESULT_READY) {
                CARDFileInfo fileInfo;

                *result = CARDOpen((s32)chan, filename, &fileInfo);
                if (*result == CARD_RESULT_READY) {
                    mCD_close_and_unmount(&fileInfo, chan);
                    res = TRUE;
                } else {
                    CARDUnmount((s32)chan);
                }
            } else {
                CARDUnmount((s32)chan);
            }
        } else if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }
    }

    return res;
}

static int mCD_format_bg_mount(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                               s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p, CARDStat* stat) {
    *workArea_p = mCD_malloc_32(CARD_WORKAREA_SIZE);
    if (*workArea_p != NULL) {
        *result = CARDMountAsync(chan, *workArea_p, NULL, NULL);
        if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN || *result == CARD_RESULT_ENCODING) {
            bg_info->space_proc++;
            return mCD_RESULT_SUCCESS;
        } else {
            return mCD_RESULT_ERROR;
        }
    } else {
        return mCD_RESULT_ERROR;
    }
}

static int mCD_format_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                   s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                   CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY || *result == CARD_RESULT_ENCODING || *result == CARD_RESULT_BROKEN) {
        *result = CARDFormatAsync((s32)chan, NULL);
        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_format_bg_cleanup(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                 s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                 CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result != CARD_RESULT_BUSY) {
        res = *result == CARD_RESULT_READY ? mCD_RESULT_SUCCESS : mCD_RESULT_ERROR;
        CARDUnmount((s32)chan);
        bg_info->space_proc++;
    }

    return res;
}

static int mCD_format_bg(s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC fbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_format_bg_mount,
        &mCD_format_bg_open_file,
        &mCD_format_bg_cleanup,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* const bg_info = &l_mcd_bg_info;

    if (bg_info->space_proc >= 0 && bg_info->space_proc < 4) {
        int success = (*fbg_proc[bg_info->space_proc])(&l_mcd_bg_info, chan, result, NULL, NULL, 0, 0, 0, &work_p, NULL, NULL);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 4) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_set_file_status_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data,
                                            const char* filename, s32 data_len, u32 length, s32 offset,
                                            void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            bg_info->fileNo = bg_info->fileInfo.fileNo;
            *result = CARDSetStatusAsync((s32)chan, bg_info->fileNo, stat, NULL);
            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc++;
                res = mCD_RESULT_SUCCESS;
            } else {
                mCD_close_and_unmount(&bg_info->fileInfo, chan);
                res = mCD_RESULT_ERROR;
            }
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_set_file_status_bg_cleanup(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data,
                                          const char* filename, s32 data_len, u32 length, s32 offset, void** workArea_p,
                                          void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result != CARD_RESULT_BUSY) {
        res = *result == CARD_RESULT_READY ? mCD_RESULT_SUCCESS : mCD_RESULT_ERROR;
        mCD_close_and_unmount(&bg_info->fileInfo, chan);
        bg_info->space_proc++;
    }

    return res;
}

static int mCD_set_file_status_bg(CARDStat* stat, const char* filename, s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC ssbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_set_file_status_bg_open_file,
        &mCD_set_file_status_bg_cleanup,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* const bg_info = &l_mcd_bg_info;

    if (bg_info->space_proc >= 0 && bg_info->space_proc < 5) {
        int success =
            (*ssbg_proc[bg_info->space_proc])(bg_info, chan, result, NULL, filename, 0, 0, 0, &work_p, NULL, stat);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 5) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_get_file_status_bg_open_file(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data,
                                            const char* filename, s32 data_len, u32 length, s32 offset,
                                            void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            bg_info->fileNo = bg_info->fileInfo.fileNo;
            *result = CARDGetStatus((s32)chan, bg_info->fileNo, stat);
            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc++;
                res = mCD_RESULT_SUCCESS;
            } else {
                res = mCD_RESULT_ERROR;
            }

            mCD_close_and_unmount(&bg_info->fileInfo, chan);
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_get_file_status_bg(CARDStat* stat, const char* filename, s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC gsbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_get_file_status_bg_open_file,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* const bg_info = &l_mcd_bg_info;

    if (bg_info->space_proc >= 0 && bg_info->space_proc < 4) {
        int success =
            (*gsbg_proc[bg_info->space_proc])(bg_info, chan, result, NULL, filename, 0, 0, 0, &work_p, NULL, stat);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 4) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_create_file_bg_create(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                     s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                     CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDCreateAsync((s32)chan, filename, length, &bg_info->fileInfo, NULL);
        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_create_file_bg_set_not_copy(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data,
                                           const char* filename, s32 data_len, u32 length, s32 offset,
                                           void** workArea_p, void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        CARDDir dir;

        bg_info->fileNo = bg_info->fileInfo.fileNo;
        *result = __CARDGetStatusEx((s32)chan, bg_info->fileNo, &dir);
        if (*result == CARD_RESULT_READY) {
            dir.permission |= data_len;

            /* @bug - missing *result = ? */
            __CARDSetStatusEx((s32)chan, bg_info->fileNo, &dir);
            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc++;
                res = mCD_RESULT_SUCCESS;
            } else {
                res = mCD_RESULT_ERROR;
            }
        } else {
            res = mCD_RESULT_ERROR;
        }

        mCD_close_and_unmount(&bg_info->fileInfo, chan);
    } else if (*result != CARD_RESULT_BUSY) {
        CARDUnmount((s32)chan);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_create_file_bg(const char* filename, s32 perms, u32 length, s32 chan, s32* result, s32* fileNo) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC cbg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_create_file_bg_create,
        &mCD_create_file_bg_set_not_copy,
    };
    // clang-format on

    int res;
    mCD_bg_info_c* bg_info;
    int proc;

    res = mCD_RESULT_BUSY;
    bg_info = &l_mcd_bg_info;
    proc = bg_info->space_proc;
    *fileNo = 0;
    if (proc >= 0 && proc < 5) {
        int success = (*cbg_proc[proc])(bg_info, chan, result, NULL, filename, perms, length, 0, &work_p,
                                                       NULL, NULL);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 5) {
            *fileNo = bg_info->fileNo;
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    /* Debug display for error state */
    if (ZURUMODE2_ENABLED()) {
        if (res == mCD_RESULT_ERROR) {
            mCD_OnErrInfo(mCD_ERROR_CREATE);
            mCD_SetErrResult(*result);
        } else if (res == mCD_RESULT_SUCCESS) {
            mCD_OffErrInfo(mCD_ERROR_CREATE);
            mCD_SetErrResult(*result);
        }
    }

    return res;
}

static int mCD_set_file_permission_bg_set(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data,
                                          const char* filename, s32 data_len, u32 length, s32 offset, void** workArea_p,
                                          void** read_p, CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDOpen((s32)chan, filename, &bg_info->fileInfo);
        if (*result == CARD_RESULT_READY) {
            CARDDir dir;

            bg_info->fileNo = bg_info->fileInfo.fileNo;
            *result = __CARDGetStatusEx((s32)chan, bg_info->fileNo, &dir);
            if (*result == CARD_RESULT_READY) {
                dir.permission |= data_len;

                /* @bug - missing *result = ? */
                __CARDSetStatusEx((s32)chan, bg_info->fileNo, &dir);
                if (*result == CARD_RESULT_READY) {
                    bg_info->space_proc++;
                    res = mCD_RESULT_SUCCESS;
                } else {
                    res = mCD_RESULT_ERROR;
                }
            } else {
                res = mCD_RESULT_ERROR;
            }

            mCD_close_and_unmount(&bg_info->fileInfo, chan);
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        CARDUnmount((s32)chan);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_set_file_permission_bg(const char* filename, s32 perms, s32 chan, s32* result, s32* fileNo) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC sp_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_set_file_permission_bg_set,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* bg_info = &l_mcd_bg_info;
    int proc = bg_info->space_proc;

    if (fileNo != NULL) {
        *fileNo = 0;
    }

    if (proc >= 0 && proc < 4) {
        int success = (*sp_proc[proc])(bg_info, chan, result, NULL, filename, perms, 0, 0, &work_p, NULL, NULL);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 4) {
            if (fileNo != NULL) {
                *fileNo = bg_info->fileNo;
            }
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    /* Debug display for error state */
    if (ZURUMODE2_ENABLED()) {
        if (res == mCD_RESULT_ERROR) {
            mCD_OnErrInfo(mCD_ERROR_CREATE);
            mCD_SetErrResult(*result);
        } else if (res == mCD_RESULT_SUCCESS) {
            mCD_OffErrInfo(mCD_ERROR_CREATE);
            mCD_SetErrResult(*result);
        }
    }

    return res;
}

static int mCD_erase_file_bg_erase(mCD_bg_info_c* bg_info, s32 chan, s32* result, void* data, const char* filename,
                                   s32 data_len, u32 length, s32 offset, void** workArea_p, void** read_p,
                                   CARDStat* stat) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode((s32)chan);
    if (*result == CARD_RESULT_READY) {
        *result = CARDDeleteAsync((s32)chan, filename, NULL);
        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            CARDUnmount((s32)chan);
            res = mCD_RESULT_ERROR;
        }
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_erase_file_bg(const char* filename, s32 chan, s32* result) {
    static void* work_p = NULL;
    // clang-format off
    static mCD_BG_PROC ebg_proc[] = {
        &mCD_bg_check_slot,
        &mCD_bg_init,
        &mCD_bg_check_filesystem,
        &mCD_erase_file_bg_erase,
        &mCD_format_bg_cleanup,
    };
    // clang-format on

    int res = mCD_RESULT_BUSY;
    mCD_bg_info_c* bg_info = &l_mcd_bg_info;
    int proc = bg_info->space_proc;

    if (proc >= 0 && proc < 5) {
        int success = (*ebg_proc[proc])(bg_info, chan, result, NULL, filename, 0, 0, 0, &work_p, NULL, NULL);

        if (success == mCD_RESULT_SUCCESS && bg_info->space_proc == 5) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_SUCCESS;
        } else if (success == mCD_RESULT_ERROR) {
            mCD_ClearCardBgInfo(bg_info);
            res = mCD_RESULT_ERROR;
        }

        if (res != mCD_RESULT_BUSY) {
            if (work_p != NULL) {
                zelda_free(work_p);
                work_p = NULL;
            }
        }
    } else {
        if (work_p != NULL) {
            zelda_free(work_p);
            work_p = NULL;
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_erase_file_fg(const char* filename, s32 chan, s32* result, void* workArea) {
    int res = FALSE;

    if (chan != -1 && workArea != NULL && mCD_check_card(result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
        *result = CARDMount((s32)chan, workArea, NULL);
        if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BUSY) {
            *result = CARDCheck((s32)chan);
            if (*result == CARD_RESULT_READY) {
                *result = CARDDelete((s32)chan, filename);
                if (*result == CARD_RESULT_READY) {
                    res = TRUE;
                }
            }

            CARDUnmount((s32)chan);
        } else if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }
    }

    return res;
}

static int mCD_rename_file_fg(const char* new_filename, const char* filename, s32 chan, s32* result, void* workArea) {
    int res = FALSE;

    if (chan != -1 && workArea != NULL && mCD_check_card(result, mCD_MEMCARD_SECTORSIZE, (s32)chan) == mCD_RESULT_SUCCESS) {
        *result = CARDMount((s32)chan, workArea, NULL);
        if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BUSY) {
            *result = CARDCheck((s32)chan);
            if (*result == CARD_RESULT_READY) {
                *result = CARDRename((s32)chan, filename, new_filename);
                if (*result == CARD_RESULT_READY) {
                    res = TRUE;
                }
            }

            CARDUnmount((s32)chan);
        } else if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)chan);
        }
    }

    return res;
}

static u16 l_mcd_copy_protect = 0xFFFF;

// clang-format off
static u8 l_mcd_font_1[256] ATTRIBUTE_ALIGN(4) = {
    0xa1, 0xbf, 0xc4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc5, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce,
    0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdf, 0xde, 0xe0,
    0xa0, 0x21, 0x94, 0xe1, 0xe2, 0x25, 0x26, 0xb4, 0x28, 0x29, 0x7e, 0x97, 0x82, 0x2d, 0x2e, 0x97,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x97, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0xe3, 0x97, 0xe4, 0xe5, 0x5f,
    0xe7, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0xe8, 0xe9, 0xea, 0xeb, 0x97,
    0x97, 0xec, 0xed, 0xee, 0xef, 0x95, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf8, 0xf9, 0xfa,
    0x96, 0xfb, 0xfc, 0xfd, 0xff, 0xfe, 0xdd, 0x7c, 0xa7, 0x97, 0x97, 0xb6, 0xb5, 0xb3, 0xb2, 0xb9,
    0xaf, 0xac, 0xc6, 0xe6, 0x84, 0xbb, 0xab, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x2f, 0x97,
    0x97, 0x97, 0x97, 0x97, 0x2b, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97,
    0x97, 0xf7, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97,
    0x3b, 0x23, 0xa0, 0xa0, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97,
    0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97,
    0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97, 0x97
};
// clang-format on

static char l_comment_0_str[32] ATTRIBUTE_ALIGN(4) = "Animal Crossing";
static char l_comment_1_str[32] ATTRIBUTE_ALIGN(4) = " Town Data";
static char l_comment_erase_land[32] ATTRIBUTE_ALIGN(4) = "Letters and Designs Data";
static char l_comment_player_0_str[32] ATTRIBUTE_ALIGN(4) = "Animal Crossing";
static char l_comment_player_1_str[32] ATTRIBUTE_ALIGN(4) = " is traveling";
static char l_comment_present_0_str[32] ATTRIBUTE_ALIGN(4) = "Animal Crossing";
static char l_comment_present_1_str[32] ATTRIBUTE_ALIGN(4) = "Bonus Letters:";
static char l_comment_gift_1_str[32] ATTRIBUTE_ALIGN(4) = "Gift Letters:";

static char l_mCD_land_file_name[32] ATTRIBUTE_ALIGN(4) = "DobutsunomoriP_MURA";
static char l_mCD_land_file_name_dummy[32] ATTRIBUTE_ALIGN(4) = "DobutsunomoriP_MURA_d";
static char l_mCD_player_file_name[32] ATTRIBUTE_ALIGN(4) = "DobutsunomoriP_PL_";
static char l_mCD_present_file_name[32] ATTRIBUTE_ALIGN(4) = "DobutsunomoriP_Omake_";

#define l_mCD_land_file_name_len (sizeof("DobutsunomoriP_PL_")-1)

typedef struct {
    const char* filename; /* filename */
    int filesize;         /* size of the entire file */
    int entrysize;        /* size of the sub-entry */
} mCD_file_entry_c;

static mCD_file_entry_c l_mcd_file_table[] = {
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, sizeof(Save) },
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, sizeof(Save) },
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, sizeof(Save) },
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, mCD_MAIL_SAVE_SIZE },
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, mCD_ORIGINAL_SAVE_SIZE },
    { l_mCD_land_file_name, mCD_LAND_SAVE_SIZE, mCD_DIARY_SAVE_SIZE },
    { l_mCD_present_file_name, mCD_PRESENT_SAVE_SIZE, mCD_PRESENT_SAVE_SIZE },
    { l_mCD_player_file_name, mCD_PLAYER_SAVE_SIZE, mCD_PLAYER_SAVE_SIZE },
};

static int l_keepSave_set = FALSE;
static int l_mcd_keep_startCond = 0;
static int l_aram_access_bit = 0;

static void mCD_clear_aram_access_bit(void) {
    l_aram_access_bit = 0;
}

static u32 l_aram_alloc_size_table[mCD_ARAM_DATA_NUM] = {
    ALIGN_NEXT(sizeof(mCD_keep_original_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_mail_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_diary_c), 32),
};
static u32 l_aram_real_size_32_table[mCD_ARAM_DATA_NUM] = {
    ALIGN_NEXT(sizeof(mCD_keep_original_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_mail_c), 32),
    ALIGN_NEXT(sizeof(mCD_keep_diary_c), 32),
};
static void* l_aram_block_p_table[mCD_ARAM_DATA_NUM];

extern void mCD_save_data_aram_malloc(void) {
    int i;

    for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
        l_aram_block_p_table[i] = JC__JKRAllocFromAram(l_aram_alloc_size_table[i]);
    }
}

extern int mCD_save_data_aram_to_main(void* dst, u32 size, u32 idx) {
    int res = FALSE;
    void* aram_block;

    if (idx >= mCD_ARAM_DATA_NUM) {
        idx = 0;
    }

    aram_block = l_aram_block_p_table[idx];
    if (aram_block != NULL) {
        JC__JKRAramToMainRam_block(aram_block, dst, size);
        DCFlushRange(dst, size);
        res = TRUE;
    }

    return res;
}

extern int mCD_save_data_main_to_aram(void* src, u32 size, u32 idx) {
    int res = FALSE;
    void* aram_block;

    if (idx >= mCD_ARAM_DATA_NUM) {
        idx = 0;
    }

    aram_block = l_aram_block_p_table[idx];
    if (aram_block != NULL) {
        DCFlushRange(src, size);
        JC__JKRMainRamToAram_block(src, aram_block, size);
        res = TRUE;
    }

    return res;
}

static u32 mCD_get_aram_save_data_max_size(void) {
    u32 size = 0;
    int i;

    for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
        if (l_aram_alloc_size_table[i] > size) {
            size = l_aram_alloc_size_table[i];
        }
    }

    return size;
}

static void mCD_set_init_mail_data(void* buf) {
    mCD_keep_mail_c* keep_mail = (mCD_keep_mail_c*)buf;
    Mail_c* mail = (Mail_c*)keep_mail->mail;
    int i;
    int j;

    for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++) {
        mem_clear(keep_mail->folder_names[i], sizeof(keep_mail->folder_names[i]), CHAR_SPACE);
        for (j = 0; j < mCD_KEEP_MAIL_COUNT; j++) {
            mMl_clear_mail(mail);
            mail++;
        }
    }
}

static void mCD_set_init_original_data(void* buf) {
    mCD_keep_original_c* keep_original = (mCD_keep_original_c*)buf;
    int i;
    int j;

    for (i = 0; i < mCD_KEEP_ORIGINAL_PAGE_COUNT; i++) {
        mem_clear(keep_original->folder_names[i], sizeof(keep_original->folder_names[i]), CHAR_SPACE);
        for (j = 0; j < mCD_KEEP_ORIGINAL_COUNT; j++) {
            mNW_InitOriginalData(&keep_original->original[i][j]);
        }
    }
}

static void mCD_set_init_diary_data(void* buf) {
    mCD_keep_diary_c* keep_diary = (mCD_keep_diary_c*)buf;
    mDi_entry_c* entry_p;
    int i;
    int j;
    
    for (i = 0; i < mCD_KEEP_DIARY_COUNT; i++) {
        entry_p = keep_diary->entries[i];
        for (j = 0; j < mCD_KEEP_DIARY_ENTRY_COUNT; j++) {
            mDi_init_diary(entry_p);
            entry_p++;
        }
    }
}

typedef void (*mCD_DATA_INIT_PROC)(void*);

extern void mCD_set_aram_save_data(void) {
    static mCD_DATA_INIT_PROC init_proc[] = {
        &mCD_set_init_original_data,
        &mCD_set_init_mail_data,
        &mCD_set_init_diary_data,
    };
    u32 max_size = mCD_get_aram_save_data_max_size();
    u8* buf = (u8*)mCD_malloc_32(max_size);

    if (buf != NULL) {
        int i;

        for (i = 0; i < mCD_ARAM_DATA_NUM; i++) {
            if (l_aram_block_p_table[i] != NULL) {
                bzero(buf, max_size);
                (*init_proc[i])(buf);
                mCD_save_data_main_to_aram(buf, l_aram_real_size_32_table[i], i);
            }
        }

        zelda_free(buf);
        mCD_clear_aram_access_bit();
    }
}

static int mCD_TransErrorCode(s32 result_code) {
    switch (result_code) {
        case CARD_RESULT_READY:
            return mCD_TRANS_ERR_NONE;
        case CARD_RESULT_NOCARD:
        case CARD_RESULT_WRONGDEVICE:
            return mCD_TRANS_ERR_NOCARD;
        case CARD_RESULT_IOERROR:
            return mCD_TRANS_ERR_IOERROR;
        case CARD_RESULT_BROKEN:
        case CARD_RESULT_ENCODING:
            return mCD_TRANS_ERR_BROKEN_WRONGENCODING;
        case CARD_RESULT_NOENT:
        case CARD_RESULT_INSSPACE:
            return mCD_TRANS_ERR_NO_SPACE;
        case CARD_RESULT_EXIST:
        case CARD_RESULT_CANCELED:
        case CARD_RESULT_FATAL_ERROR:
        case CARD_RESULT_NAMETOOLONG:
        case CARD_RESULT_LIMIT:
        case CARD_RESULT_NOPERM:
        case CARD_RESULT_NOFILE:
            return mCD_TRANS_ERR_GENERIC;
        case CARD_RESULT_BUSY:
            return mCD_TRANS_ERR_BUSY;
        default:
            return mCD_TRANS_ERR_GENERIC;
    }
}

static int mCD_TransErrorCode_nes(s32 result_code) {
    switch (result_code) {
        case CARD_RESULT_READY:
            return mCD_TRANS_ERR_NONE;
        case CARD_RESULT_WRONGDEVICE:
            return mCD_TRANS_ERR_WRONGDEVICE;
        case CARD_RESULT_NOCARD:
            return mCD_TRANS_ERR_NOCARD;
        case CARD_RESULT_IOERROR:
            return mCD_TRANS_ERR_IOERROR;
        case CARD_RESULT_BROKEN:
        case CARD_RESULT_ENCODING:
            return mCD_TRANS_ERR_BROKEN_WRONGENCODING;
        case CARD_RESULT_NOENT:
        case CARD_RESULT_INSSPACE:
            return mCD_TRANS_ERR_NO_SPACE;
        case CARD_RESULT_EXIST:
        case CARD_RESULT_CANCELED:
        case CARD_RESULT_FATAL_ERROR:
        case CARD_RESULT_NAMETOOLONG:
        case CARD_RESULT_LIMIT:
        case CARD_RESULT_NOPERM:
        case CARD_RESULT_NOFILE:
            return mCD_TRANS_ERR_GENERIC;
        case CARD_RESULT_BUSY:
            return mCD_TRANS_ERR_BUSY;
        default:
            return mCD_TRANS_ERR_GENERIC;
    }
}

static int mCD_get_offset(int idx) {
    mCD_file_entry_c* entry = l_mcd_file_table;
    int ofs = 0;
    int i;

    if (idx >= mCD_FILE_SAVE_MAIN && idx <= mCD_FILE_SAVE_DIARY) {
        for (i = idx - 1; i >= 0; i--) {
            ofs += entry->entrysize;
            entry++;
        }
    }

    return ofs;
}

static int mCD_get_size(int idx) {
    int size = 0;

    if (idx >= 0 && idx < mCD_FILE_NUM) {
        size = l_mcd_file_table[idx].entrysize;
    }

    return size;
}

static Save l_keepSave;
static mCD_memMgr_c l_memMgr;

static void mCD_ClearMemMgr_com(mCD_memMgr_c* mgr) {
    bzero(mgr, sizeof(mCD_memMgr_c));
    mgr->chan = -1;
    mgr->land_saved = -1;
    mgr->copy_protect = -1;
    mgr->broken_file_idx = -1;
}

static void mCD_ClearMemMgr_com2(mCD_memMgr_c* mgr) {
    if (mgr->workArea != NULL) {
        zelda_free(mgr->workArea);
    }

    if (mgr->cards[0].workArea != NULL) {
        zelda_free(mgr->cards[0].workArea);
    }

    if (mgr->cards[1].workArea != NULL) {
        zelda_free(mgr->cards[1].workArea);
    }

    mCD_ClearMemMgr_com(mgr);
}

static void mCD_ClearKeepLand(void) {
    bzero(&l_keepSave, sizeof(l_keepSave));
    l_keepSave_set = FALSE;
}

static void mCD_ClearMemMgr(void) {
    mCD_ClearMemMgr_com(&l_memMgr);
}

typedef struct {
    PersonalID_c pid;
    char filename[32];
} mCD_cardPrivate_c;

static mCD_cardPrivate_c l_mcd_card_private_table[19];
static mCD_cardPrivate_c l_mcd_card_private;

static void mCD_ClearCardPrivateTable_com(mCD_cardPrivate_c* priv, int count) {
    for (count; count != 0; count--) {
        mPr_ClearPersonalID(&priv->pid);
        mem_clear((u8*)priv->filename, sizeof(priv->filename), 0);
        priv++;
    }
}

static void mCD_ClearCardPrivateTable(void) {
    mCD_ClearCardPrivateTable_com(l_mcd_card_private_table, ARRAY_COUNT(l_mcd_card_private_table));
}

static void mCD_SetCardPrivateTable(mCD_cardPrivate_c* priv, PersonalID_c* pid, char* filename) {
    mPr_CopyPersonalID(&priv->pid, pid);
    bcopy(filename, priv->filename, sizeof(priv->filename));
}

typedef struct {
    u16 checksum;
    Private_c priv;
    Animal_c remove_animal;
    u16 copy_protect;
    u8 _2DEA[54];
} mCD_foreigner_c;

typedef union {
    struct {
        char comment[CARD_COMMENT_SIZE];
        u8 banner[0xC00 + 0x200];
        u8 icon[0x400 * 8 + 0x200];
        mCD_foreigner_c file;
    };
    u8 sector_align[mCD_ALIGN_SECTORSIZE(sizeof(MemcardHeader_c) + sizeof(mCD_foreigner_c))];
} ForeignerFile_c;

static union {
    mCD_foreigner_c file;
    u8 sector_align[mCD_ALIGN_SECTORSIZE(sizeof(mCD_foreigner_c))];
} l_mcd_foreigner_file;

static void mCD_ClearForeignerFile(mCD_foreigner_c* foreigner) {
    bzero(foreigner, sizeof(l_mcd_foreigner_file));
    foreigner->checksum = 0;
    mPr_ClearPrivateInfo(&foreigner->priv);
    mNpc_ClearAnimalInfo(&foreigner->remove_animal);
    foreigner->copy_protect = 0xFFFF;
}

#include "../src/game/m_card_bti.c_inc"

typedef struct {
    u16 code[4];
} mCD_LandProtectCode_c;

static mCD_LandProtectCode_c l_keep_noLandCode;

static void mCD_ClearNoLandProtectCode(mCD_LandProtectCode_c* protect_code) {
    bzero(protect_code, sizeof(mCD_LandProtectCode_c));
}

static int mCD_CheckInitProtectCode(mCD_LandProtectCode_c* protect_code) {
    u16* code_p = protect_code->code;
    int res = FALSE;
    int i;

    for (i = 0; i < 4; i++) {
        if (*code_p != 0) {
            break;
        }

        code_p++;
    }

    if (i == 4) {
        res = TRUE;
    }

    return res;
}

static int mCD_CheckProtectCode(u16* protect_code) {
    int res = FALSE;
    int i;

    if (*protect_code == 0x3C1C) {
        protect_code++;
        for (i = 0; i < 3; i++) {
            if (*protect_code == 0) {
                break;
            }

            protect_code++;
        }

        if (i == 3) {
            res = TRUE;
        }
    }

    return res;
}

static void mCD_MakeProtectCode(mCD_LandProtectCode_c* protect_code) {
    int i;
    u16* code_p = protect_code->code;

    *code_p = mCD_LAND_PROTECT_CODE_MAGIC0;
    code_p++;
    for (i = 0; i < 3; i++) {
        *code_p = RANDOM(0xFFFE);
        *code_p = *code_p + 1;
        code_p++;
    }
}

static int mCD_CompNoLandCode(u16* code0, u16* code1) {
    int res = FALSE;
    
    if (mCD_CheckProtectCode(code0) == TRUE) {
        int i;

        for (i = 0; i < 4; i++) {
            if (*code0 != *code1) {
                break;
            }

            code0++;
            code1++;
        }

        if (i == 4) {
            res = TRUE;
        }
    }

    return res;
}

static void mCD_SetForeignerFile(mCD_foreigner_c* foreigner, Private_c* priv, Animal_c* animal) {
    mPr_CopyPrivateInfo(&foreigner->priv, priv);
    bcopy(animal, &foreigner->remove_animal, sizeof(Animal_c));
    foreigner->checksum = mFRm_GetFlatCheckSum((u16*)foreigner, sizeof(mCD_foreigner_c), foreigner->checksum);
}

static void mCD_clear_all_control(void);

extern void mCD_InitAll(void) {
    mCD_StartSetCardBgInfo();
    mCD_ClearMemMgr();
    mCD_ClearKeepLand();
    mCD_ClearCardPrivateTable();
    mCD_ClearCardPrivateTable_com(&l_mcd_card_private, 1);
    mCD_clear_all_control();
    l_mcd_copy_protect = 0xFFFF;
    mCD_ClearForeignerFile(&l_mcd_foreigner_file.file);
    mCD_ClearNoLandProtectCode(&l_keep_noLandCode);
    mCD_ClearErrInfo();
}

static int mCD_save_file(void* data, int file_idx, s32 chan, s32* result) {
    int res = mCD_RESULT_ERROR;

    if (data != NULL && file_idx >= 0 && file_idx < mCD_FILE_NUM) {
        mCD_file_entry_c* file = &l_mcd_file_table[file_idx];
        int ofs = mCD_get_offset(file_idx);

        res = mCD_write_comp_bg(data, file->filename, file->entrysize, file->filesize, ofs, chan, result);
    }

    return res;
}

static int mCD_load_file(void* buf, int file_idx, s32 chan, s32* result) {
    int res = mCD_RESULT_ERROR;

    if (buf != NULL && file_idx >= 0 && file_idx < mCD_FILE_NUM) {
        mCD_file_entry_c* file = &l_mcd_file_table[file_idx];
        int ofs = mCD_get_offset(file_idx);

        res = mCD_read_fg(buf, file->filename, file->entrysize, ofs, chan, result);
    }

    return res;
}

/* This struct seems to be stubbed */
typedef struct {
    int _00;
    int _04;
    int _08;
    int _0C;
    int _10;
    mCD_LandProtectCode_c protect_code; // assumed?
    int _1C;
    int _20;
    int _24;
    int _28;
    int _2C;
    int _30;
} mCD_wctrl_c;

static mCD_wctrl_c l_mCD_wctrl;

static void mCD_clear_write_control_common(mCD_wctrl_c* write_control) {
    write_control->_00 = 0;
    write_control->_04 = 0;
    write_control->_08 = 0;
    write_control->_0C = 0;
    bzero(&write_control->protect_code, sizeof(mCD_LandProtectCode_c));
    write_control->_1C = 0;
    write_control->_20 = 0;
    write_control->_24 = 0;
    write_control->_28 = 0;
    write_control->_30 = 0;
}

static void mCD_clear_all_control(void) {
    mCD_clear_write_control_common(&l_mCD_wctrl);
}

static int mCD_GetHighPriority_common(mCD_memMgr_c* mgr, int prio0, int prio1) {
    mgr->chan = 0;
    if (prio1 < prio0) {
        mgr->chan = 1;
        prio0 = prio1;
    }

    return prio0;
}

static int mCD_check_Land_exist_com(s32 chan) {
    int res = FALSE;

    if (chan == 0 || chan == 1) {
        CARDFileInfo fileInfo;

        if (CARDOpen(chan, l_mCD_land_file_name, &fileInfo) == CARD_RESULT_READY) {
            res = TRUE;
        }
    }

    return res;
}

static int mCD_check_Land_exist(s32 chan, void* workArea) {
    int res = FALSE;

    if ((chan == 0 || chan == 1) && workArea != NULL) {
        s32 result;

        if (mCD_check_card(&result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
            result = CARDMount((s32)chan, workArea, NULL);
            if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
                result = CARDCheck((s32)chan);
                if (result == CARD_RESULT_READY) {
                    res = mCD_check_Land_exist_com(chan);
                }

                CARDUnmount((s32)chan);
            } else if (result == CARD_RESULT_ENCODING) {
                CARDUnmount((s32)chan);
            }
        }
    }

    return res;
}

static int mCD_CheckFilename(const char* name0, const char* name1, int len) {
    int i = 0;
    int j = 0;
    int res = FALSE;

    while (name0 != NULL && j < len && *name0 != '\0') {
        if (*name0 != *name1) {
            break;
        }

        i++;
        name0++;
        name1++;
        j++;
    }

    if (i == len) {
        res = TRUE;
    }

    return res;
}

static int mCD_CheckPresentFilename(CARDStat* stat) {
    return mCD_CheckFilename(stat->fileName, l_mCD_present_file_name, 21);
}

static int mCD_CheckPresentFileStatus(CARDStat* stat) {
    int res = FALSE;

    if (stat->company[0] == '0' && stat->company[1] == '1') {
        res = mCD_CheckPresentFilename(stat);
    }

    return res;
}

static int mCD_CheckPassportFilename(CARDStat* stat) {
    return mCD_CheckFilename(stat->fileName, l_mCD_player_file_name, 18);
}

static int mCD_CheckPassportFileStatus(CARDStat* stat) {
    int res = FALSE;

    if (stat->company[0] == '0' && stat->company[1] == '1') {
        res = mCD_CheckPassportFilename(stat);
    }

    return res;
}

static int mCD_set_to_num(char* c) {
    int n = 0;
    int num = 0;
    int i = 0;

    if (c != NULL) {
        for (i; i < 3; i++) {
            if (c[i] == '\0') {
                break;
            }

            if (num != 0) {
                num *= 10;
            } else {
                num = 1;
            }
        }

        for (i; i != 0; i--) {
            n += (*c - '0') * num;
            num /= 10;
            c++;
        }
    }

    return n;
}

static int mCD_GetPassportFileIdx(char* filename) {
    return mCD_set_to_num(&filename[18]);
}

static int mCD_CheckPassportFile_slot(s32 chan, void* workArea) {
    int i;
    int res = FALSE;

    if ((chan == 0 || chan == 1) && workArea != NULL) {
        s32 result;

        if (mCD_check_card(&result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
            result = CARDMount((s32)chan, workArea, NULL);
            if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
                result = CARDCheck((s32)chan);
                if (result == CARD_RESULT_READY) {
                    /* Check all files on the memcard */
                    CARDStat stat;

                    for (i = 0; i < CARD_MAX_FILE; i++) {
                        result = CARDGetStatus((s32)chan, i, &stat);
                        if (result == CARD_RESULT_READY) {
                            if (mCD_CheckPassportFileStatus(&stat) == TRUE) {
                                res = TRUE;
                                break;
                            }
                        }
                    }
                }

                CARDUnmount((s32)chan);
            } else if (result == CARD_RESULT_ENCODING) {
                CARDUnmount((s32)chan);
            }
        }
    }

    return res;
}

static int mCD_GetSpaceSlot_bg2(mCD_memMgr_c* mgr, int size) {
    mCD_memMgr_card_info_c* card_info;
    int chan;
    int res;
    u8 _0010;
    
    chan = 0;
    res = mCD_RESULT_BUSY;
    _0010 = mgr->_0010;
    if ((_0010 & 1) == 1) {
        chan = 1;
    }
    card_info = &mgr->cards[chan];

    if (card_info->workArea != NULL) {
        int space_res = mCD_get_space_bg(&card_info->freeBytes, chan, &card_info->result, card_info->workArea);
        if (space_res == mCD_RESULT_SUCCESS) {
            if (card_info->freeBytes >= size) {
                if (mCD_check_Land_exist(chan, card_info->workArea) == TRUE) {
                    card_info->game_result = mCD_TRANS_ERR_LAND_EXIST;
                } else if (mCD_CheckPassportFile_slot(chan, card_info->workArea) == TRUE) {
                    card_info->game_result = mCD_TRANS_ERR_PASSPORT_EXIST;
                } else if (mCD_get_file_num(card_info->workArea, chan) >= CARD_MAX_FILE) {
                    card_info->game_result = mCD_TRANS_ERR_NO_FILES;
                } else {
                    mgr->chan = chan;
                    res = mCD_RESULT_SUCCESS;
                }
            } else {
                card_info->result = CARD_RESULT_INSSPACE;
            }

            mgr->_0010 |= 1 << chan;
        } else if (space_res != mCD_RESULT_BUSY) {
            if (mCD_check_sector_size(mCD_MEMCARD_SECTORSIZE, chan) == FALSE) {
                card_info->game_result = mCD_TRANS_ERR_NOT_MEMCARD;
            }

            mgr->_0010 |= 1 << chan;
        }
    } else {
        _0010 |= 1 << chan;
        mgr->_0010 = _0010;
        res = mCD_RESULT_ERROR;
    }

    if (card_info->game_result != mCD_TRANS_ERR_LAND_EXIST && card_info->game_result != mCD_TRANS_ERR_PASSPORT_EXIST &&
        card_info->game_result != mCD_TRANS_ERR_NOT_MEMCARD && card_info->game_result != mCD_TRANS_ERR_NO_FILES) {
        card_info->game_result = mCD_TransErrorCode_nes(card_info->result);
    }

    /* If no memcard was chosen */
    if (mgr->_0010 == 0b11 && res == mCD_RESULT_BUSY) {
        mCD_GetHighPriority_common(mgr, mgr->cards[0].game_result, mgr->cards[1].game_result);

        if (mgr->chan == -1 || mgr->cards[mgr->chan].game_result != mCD_TRANS_ERR_NONE) {
            res = mCD_RESULT_ERROR;
        } else {
            res = mCD_RESULT_SUCCESS;
        }
    }

    return res;
}

static int mCD_check_noLand_file(mCD_LandProtectCode_c* protect_code, u8* data, s32 chan) {
    int res = FALSE;

    if (data != NULL) {
        s32 result;

        if (mCD_load_file(data, mCD_FILE_SAVE_MISC, chan, &result) == mCD_RESULT_SUCCESS) {
            if (mCD_CheckProtectCode((u16*)(data + mCD_SAVE_DATA_OFS)) == TRUE) {
                if (protect_code != NULL) {
                    bcopy((mCD_LandProtectCode_c*)(data + mCD_SAVE_DATA_OFS), protect_code,
                          sizeof(mCD_LandProtectCode_c));
                }

                res = TRUE;
            }
        }
    }

    return res;
}

static int mCD_GetNoLandSlot_bg(mCD_memMgr_c* mgr) {
    s32 chan = 0;
    mCD_memMgr_card_info_c* card_info;
    int res = mCD_RESULT_BUSY;
    u8 _0010 = mgr->_0010;
    
    if ((_0010 & 1) == 1) {
        chan = 1;
    }

    card_info = &mgr->cards[chan];

    if (card_info->workArea != NULL) {
        static mCD_LandProtectCode_c noLand_code;

        if (mCD_check_noLand_file(&noLand_code, mgr->workArea, chan) == TRUE &&
            mCD_CompNoLandCode(noLand_code.code, l_keep_noLandCode.code) == TRUE) {
            mgr->chan = chan;
            res = mCD_RESULT_SUCCESS;
        } else {
            mgr->_0010 |= 1 << chan;
            card_info->game_result = mCD_TRANS_ERR_INVALID_NOLAND_CODE;
        }
    } else {
        _0010 |= 1 << chan;
        mgr->_0010 = _0010;
        res = mCD_RESULT_ERROR;
    }

    if (card_info->game_result != mCD_TRANS_ERR_INVALID_NOLAND_CODE) {
        card_info->game_result = mCD_TransErrorCode(card_info->result);
    }

    if (mgr->_0010 == 0b11 && res == mCD_RESULT_BUSY) {
        mCD_GetHighPriority_common(mgr, mgr->cards[0].game_result, mgr->cards[1].game_result);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_CheckThisLandSlot(s32* result, s32* game_result, s32 chan, Save_t* buf_save) {
    int res = mCD_RESULT_ERROR;

    if (buf_save != NULL) {
        int i;

        for (i = 0; i < 2; i++) {
            int read_res;

            *result = CARD_RESULT_NOCARD;
            read_res = mCD_read_fg(buf_save, l_mCD_land_file_name, CARD_WORKAREA_SIZE,
                                   mCD_get_offset(mCD_FILE_SAVE_MAIN + i), chan, result);
            if (read_res == mCD_RESULT_SUCCESS) {
                if (mFRm_CheckSaveData_common(&buf_save->save_check, buf_save->land_info.id) == TRUE) {
                    if (mLd_CheckThisLand(buf_save->land_info.name, buf_save->land_info.id) == TRUE) {
                        *game_result = mCD_TRANS_ERR_NONE;
                        res = mCD_RESULT_SUCCESS;
                        break;
                    } else if (mLd_CheckId(buf_save->land_info.id) == TRUE) {
                        *game_result = mCD_TRANS_ERR_OTHER_TOWN;
                        res = mCD_RESULT_BUSY;
                        break;
                    } else {
                        *game_result = mCD_TRANS_ERR_TOWN_INVALID;
                        res = mCD_RESULT_BUSY;
                    }
                } else {
                    *game_result = mCD_TRANS_ERR_TOWN_INVALID;
                    res = mCD_RESULT_BUSY;
                }
            }
        }
    }

    return res;
}

static void mCD_set_1byte(char* c, int idx) {
    *c = l_mcd_font_1[idx];
}

static void mCD_set_number_str(char* str, u8 num) {
    int n = num;
    int f = FALSE;
    int fig_table[3];
    int i;
    
    bzero(fig_table, sizeof(fig_table));
    
    for (i = 0; i < 3; i++) {
        const int remain = n % 10;
        const int div = n / 10;
        
        fig_table[i] = remain;
        n = div;
    }

    for (i = 2; i > 0; i--) {
        if (fig_table[i] > 0 || f == TRUE) {
            *str++ = fig_table[i] + '0';
            f = TRUE;
        }
    }

    *str = fig_table[0] + '0';
}

static void mCD_get_land_comment1(char* comment1, u8* town_name) {
    int n;
    int i;
    int spaces = 0;
    u8* town_name_p;
    char* comment_p;

    town_name_p = town_name;
    mem_clear((u8*)comment1, 32, 0);
    for (i = LAND_NAME_SIZE; i != 0; i--) {
        u8 c = *town_name++;

        if (c != CHAR_SPACE) {
            spaces = 0;
        } else {
            spaces++;
        }
    }

    town_name = town_name_p;
    n = LAND_NAME_SIZE - spaces;
    for (i = 0; i < n; i++) {
        mCD_set_1byte(comment1, *town_name);
        comment1++;
        town_name++;
    }

    comment_p = l_comment_1_str;
    for (i = 0; i < 32; i++) {
        *comment1 = *comment_p;
        if (*comment_p == '\0') {
            break;
        }

        comment1++;
        comment_p++;
    }
}

static void mCD_get_passport_comment1(char* comment1, u8* player_name) {
    int i;
    int n;
    int spaces = 0;
    u8* player_name_p;
    char* comment_p;

    player_name_p = player_name;
    mem_clear((u8*)comment1, 32, 0);
    for (i = LAND_NAME_SIZE; i != 0; i--) {
        u8 c = *player_name++;

        if (c != CHAR_SPACE) {
            spaces = 0;
        } else {
            spaces++;
        }
    }

    player_name = player_name_p;
    n = PLAYER_NAME_LEN - spaces;
    for (i = 0; i < n; i++) {
        mCD_set_1byte(comment1, *player_name);
        comment1++;
        player_name++;
    }

    comment_p = l_comment_player_1_str;
    for (i = 0; i < 32; i++) {
        *comment1 = *comment_p;
        if (*comment_p == '\0') {
            break;
        }

        comment1++;
        comment_p++;
    }
}

static void mCD_get_present_comment1(char* comment1, int num, char* src_comment, int src_len) {
    int i;

    mem_clear((u8*)comment1, 32, 0);
    for (i = 0; i < src_len; i++) {
        *comment1++ = *src_comment++;
    }

    if (num >= 0) {
        num %= 10;
        mCD_set_1byte(comment1, '0' + num);
    }
}

extern int mCD_card_format_bg(s32 chan) {
    s32 result;

    return mCD_format_bg(chan, &result);
}

static int mCD_get_this_land_slot_no(mCD_memMgr_c* mgr) {
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    Save_t* buf_save = (Save_t*)mgr->workArea;
    int res = mCD_RESULT_ERROR;
    int i;

    for (i = 0; i < CARD_NUM_CHANS; i++) {
        card_info[i].result = CARD_RESULT_NOCARD;
        card_info[i].game_result = mCD_TRANS_ERR_NOCARD;
    }

    if (buf_save != NULL) {
        for (i = 0; i < CARD_NUM_CHANS; i++) {
            int t_res = mCD_CheckThisLandSlot(&card_info->result, &card_info->game_result, i, buf_save);

            if (t_res == mCD_RESULT_SUCCESS) {
                mgr->chan = i;
                card_info->game_result = mCD_TRANS_ERR_NONE;
                res = mCD_RESULT_SUCCESS;
                break;
            }

            if (card_info->game_result == mCD_TRANS_ERR_NOCARD || t_res == mCD_RESULT_ERROR) {
                card_info->game_result = mCD_TransErrorCode(card_info->result);
            }

            card_info++;
        }
    }

    return res;
}

static int mCD_get_this_land_slot_no_game_start(mCD_memMgr_c* mgr) {
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    Save_t* buf_save = (Save_t*)mgr->workArea;
    int res = mCD_RESULT_ERROR;
    int i;

    for (i = 0; i < CARD_NUM_CHANS; i++) {
        card_info[i].result = CARD_RESULT_NOCARD;
        card_info[i].game_result = mCD_TRANS_ERR_NOCARD;
    }

    if (buf_save != NULL) {
        for (i = 0; i < CARD_NUM_CHANS; i++) {
            int t_res = mCD_CheckThisLandSlot(&card_info->result, &card_info->game_result, i, buf_save);

            if (t_res == mCD_RESULT_SUCCESS) {
                mgr->chan = i;
                res = mCD_RESULT_SUCCESS;
                break;
            }

            if (card_info->game_result == mCD_TRANS_ERR_NOCARD || t_res == mCD_RESULT_ERROR) {
                card_info->game_result = mCD_TransErrorCode(card_info->result);
            } else {
                card_info->game_result = mCD_TRANS_ERR_WRONG_LAND;
                mgr->chan = i;
            }

            card_info++;
        }
    }

    return res;
}

static int mCD_get_this_land_slot_no_nes(mCD_memMgr_c* mgr) {
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    Save_t* buf_save = (Save_t*)mgr->workArea;
    int res = mCD_RESULT_ERROR;
    int i;

    for (i = 0; i < CARD_NUM_CHANS; i++) {
        card_info[i].result = CARD_RESULT_NOCARD;
        card_info[i].game_result = mCD_TRANS_ERR_NOCARD;
    }

    if (buf_save != NULL) {
        for (i = 0; i < CARD_NUM_CHANS; i++) {
            int t_res = mCD_CheckThisLandSlot(&card_info->result, &card_info->game_result, i, buf_save);

            if (t_res == mCD_RESULT_SUCCESS) {
                mgr->chan = i;
                res = mCD_RESULT_SUCCESS;
                break;
            }

            if (mCD_check_sector_size(mCD_MEMCARD_SECTORSIZE, i) == FALSE) {
                card_info->game_result = mCD_TRANS_ERR_NOT_MEMCARD;
                mgr->chan = i;
            } else if (card_info->game_result == mCD_TRANS_ERR_NOCARD || t_res == mCD_RESULT_ERROR) {
                card_info->game_result = mCD_TransErrorCode_nes(card_info->result);
            }

            card_info++;
        }
    }

    if (res == mCD_RESULT_ERROR) {
        mCD_GetHighPriority_common(mgr, mgr->cards[0].game_result, mgr->cards[1].game_result);
    }

    return res;
}

static int mCD_check_copyProtect(Save_t* buf_save, s32 chan) {
    int i;
    int res = FALSE;

    if (chan != -1 && buf_save != NULL) {
        for (i = 0; i < 2; i++) {
            s32 result;
            int t_res = mCD_read_fg(buf_save, l_mCD_land_file_name, 0x200, mCD_get_offset(mCD_FILE_SAVE_MAIN + i), chan,
                                    &result);

            if (t_res == mCD_RESULT_SUCCESS && buf_save->copy_protect == Common_Get(copy_protect)) {
                res = TRUE;
                break;
            }
        }
    }

    return res;
}

static int mCD_bg_get_area_common(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo, int file_idx, int sound_idx) {
    static u8 sound_table[mCD_HOME_SFX_NUM] = { NA_SE_47, NA_SE_53 };
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    int stages_compl = 0;
    int res = mCD_RESULT_BUSY;

    /* Start playing sound effect if necessary */
    if (mgr->_017C == 0 && sound_idx >= 0 && sound_idx < mCD_HOME_SFX_NUM) {
        sAdo_SysLevStart(sound_table[sound_idx]);
    }

    if (mgr->_017C < 100) {
        int i;

        for (i = 0; i < CARD_NUM_CHANS; i++) {
            if (card_info->workArea == NULL) {
                card_info->workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);
            }

            if (card_info->workArea != NULL) {
                stages_compl++;
            }

            card_info++;
        }

        if (mgr->workArea == NULL) {
            mgr->workArea_size = mCD_get_size(file_idx);
            mgr->workArea = mCD_malloc_32(mgr->workArea_size);
        }

        if (mgr->workArea != NULL) {
            stages_compl++;
        }

        if (stages_compl == 3) {
            fileInfo->proc++;
            res = mCD_RESULT_SUCCESS;
        } else {
            mgr->_017C++;
        }
    } else {
        /* Unable to allocate work area buffers */
        mCD_OnErrInfo(mCD_ERROR_AREA);
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    SoftResetEnable = FALSE;
    return mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, mCD_HOME_SFX_NORMAL);
}

static int mCD_SaveHome_bg_erase_dummy(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    int i;

    for (i = 0; i < CARD_NUM_CHANS; i++) {
        s32 result;

        mCD_erase_file_fg(l_mCD_land_file_name_dummy, i, &result, card_info->workArea);
        card_info++;
    }

    fileInfo->proc++;
    return mCD_RESULT_SUCCESS;
}

static int mCD_send_present(PresentSaveFile_c* present_file, int length) {
    Mail_c* letter = present_file->save.letters;
    int res = FALSE;
    u32 player_no = Common_Get(player_no);
    u16 checksum = mFRm_ReturnCheckSum((u16*)present_file, length);

    if (checksum == 0 && present_file->save.present_count <= mCD_PRESENT_MAX) {
        int i;

        for (i = 0; i < mCD_PRESENT_MAX; i++, letter++) {
            if (mPr_NullCheckPersonalID(&letter->header.recipient.personalID) == TRUE) {
                Private_c* priv;
                mHm_hs_c* house;
                int free_idx;

                if (player_no >= PLAYER_NUM) {
                    break;
                }

                priv = Now_Private;
                if (priv == NULL) {
                    break;
                }

                house = &Save_Get(homes[mHS_get_arrange_idx(player_no)]);
                if (mPr_CheckCmpPersonalID(&priv->player_ID, &house->ownerID) != TRUE) {
                    break;
                }

                free_idx = mMl_chk_mail_free_space(house->mailbox, HOME_MAILBOX_SIZE);
                if (free_idx == -1) {
                    break;
                }

                letter->content.font = mMl_FONT_RECV;
                mPr_CopyPersonalID(&letter->header.recipient.personalID, &priv->player_ID);
                letter->header.recipient.type = mMl_NAME_TYPE_PLAYER;
                mMl_copy_mail(&house->mailbox[free_idx], letter);

                res = TRUE;
                present_file->save.present_count--;
                if (present_file->save.present_count <= 0) {
                    break;
                }
            }
        }
    }

    return res;
}

static int mCD_SaveHome_bg_check_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int res = mCD_RESULT_BUSY;

    if (mgr->cards[0].workArea != NULL && mgr->cards[1].workArea != NULL && mgr->workArea != NULL) {
        if (Save_Get(save_exist) == FALSE) {
            if (mCD_CheckInitProtectCode(&l_keep_noLandCode) == FALSE &&
                mCD_CheckProtectCode(l_keep_noLandCode.code) == TRUE) {
                int slot_res = mCD_GetNoLandSlot_bg(mgr);

                if (slot_res == mCD_RESULT_SUCCESS) {
                    mgr->land_saved = Save_Get(save_exist);
                    mgr->copy_protect = Common_Get(copy_protect);
                    mgr->_0010 = 0b00;
                    fileInfo->proc++;
                    res = mCD_RESULT_SUCCESS;
                } else if (slot_res != mCD_RESULT_BUSY) {
                    res = mCD_RESULT_ERROR;
                }
            } else {
                int space_res = mCD_GetSpaceSlot_bg2(mgr, mCD_LAND_SAVE_SIZE);

                if (space_res == TRUE) {
                    if (mgr->chan != -1) {
                        fileInfo->proc++;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        mgr->_0010 = 0b00;
                        res = mCD_RESULT_SUCCESS;
                    } else {
                        res = mCD_RESULT_ERROR;
                    }
                } else if (space_res != mCD_RESULT_BUSY) {
                    mgr->_0010 = 0b00;
                    res = mCD_RESULT_ERROR;
                }
            }
        } else {
            int land_slot_res = mCD_get_this_land_slot_no_nes(mgr);

            if (land_slot_res == mCD_RESULT_SUCCESS) {
                int chan = mgr->chan;

                if (chan != -1) {
                    if (mCD_check_copyProtect((Save_t*)mgr->workArea, chan) == TRUE) {
                        fileInfo->proc++;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        res = mCD_RESULT_SUCCESS;
                    } else {
                        mgr->cards[chan].game_result = mCD_TRANS_ERR_WRONG_LAND;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        res = mCD_RESULT_ERROR;
                    }
                } else {
                    res = mCD_RESULT_ERROR;
                }
            } else if (land_slot_res != mCD_RESULT_BUSY) {
                res = mCD_RESULT_ERROR;
            }
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_CheckPresentFile(char* filename, s32* fileNo, s32 chan, s32* result, void* workArea) {
    CARDStat stat;
    int file;
    int res = FALSE;

    if (mCD_check_card(result, mCD_MEMCARD_SECTORSIZE, (s32)chan) == mCD_RESULT_SUCCESS) {
        *result = CARDMount((s32)chan, workArea, NULL);
        if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN) {
            *result = CARDCheck((s32)chan);
            if (*result == CARD_RESULT_READY) {
                for (file = *fileNo; file < 32; file++) {
                    *result = CARDGetStatus((s32)chan, file, &stat);
                    if (*result == CARD_RESULT_READY && mCD_CheckPresentFileStatus(&stat) == TRUE) {
                        bcopy(stat.fileName, filename, CARD_FILENAME_MAX);
                        res = TRUE;
                        break;
                    }
                }
            }

            /* @BUG - if CARDCheck fails, file will be undefined */
            *fileNo = file;
            CARDUnmount((s32)chan);
        } else {
            if (*result == CARD_RESULT_ENCODING) {
                CARDUnmount((s32)chan);
            }

            *fileNo = 32;
        }
    } else {
        *fileNo = 32;
    }

    return res;
}

static int mCD_SaveHome_bg_read_send_present(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    static int icon_fileNo[mCD_PRESENT_TYPE_NUM] = { RESOURCE_TEGAMI, RESOURCE_TEGAMI2 };
    static char* comment_p_table[mCD_PRESENT_TYPE_NUM] = { l_comment_present_1_str, l_comment_gift_1_str };
    static int comment_len_table[mCD_PRESENT_TYPE_NUM] = { 14, 13 };
    void* workArea = mgr->workArea;
    mCD_file_entry_c* present_entry;
    mCD_memMgr_card_info_c* card_info;
    int type;
    PresentSaveFile_c* present_buf;
    int icon;

    icon = 0;
    type = mCD_PRESENT_TYPE_BONUS;
    present_entry = &l_mcd_file_table[mCD_FILE_PRESENT];
    if (mgr->cards[0].workArea != NULL && mgr->cards[1].workArea != NULL && workArea != NULL) {
        mgr->chan = -1;
        card_info = &mgr->cards[fileInfo->chan];

        /* Get info about the present save file */
        if (mCD_CheckPresentFile(mgr->filename, &fileInfo->fileNo, fileInfo->chan, &card_info->result,
                                 card_info->workArea) == TRUE) {
            if (mCD_read_fg(workArea, mgr->filename, present_entry->entrysize,
                            mCD_get_offset(mCD_FILE_PRESENT), fileInfo->chan,
                            &card_info->result) == mCD_RESULT_SUCCESS) {
                present_buf = (PresentSaveFile_c*)workArea;
                
                /* Determine if this is a bonus gift file or a 'gift' present file */
                if (mCD_CheckFilename(present_buf->header.comment + 32, l_comment_gift_1_str, 13) == TRUE) {
                    type = mCD_PRESENT_TYPE_GIFT;
                }
                                
                /* Try sending the presents */
                if (mCD_send_present(present_buf, present_entry->entrysize) == TRUE) {
                    mgr->loaded_file_type = mCD_FILE_PRESENT;
                    mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                    mgr->chan = fileInfo->chan;
                    mCD_get_present_comment1(present_buf->header.comment + 32, present_buf->save.present_count,
                                             comment_p_table[type], comment_len_table[type]);
                    if (present_buf->save.present_count == 0) {
                        icon = 1;
                    }
                    mCD_set_bti_data(present_buf->header.icon, icon_fileNo[icon], 0x400, 1, 0x200);
                    present_buf->save.checksum =
                        mFRm_GetFlatCheckSum((u16*)workArea, mgr->workArea_size, present_buf->save.checksum);
                    fileInfo->proc++;
                } else if (present_buf->save.present_count != 0) {
                    mgr->chan = -1;
                    fileInfo->chan = CARD_NUM_CHANS;
                } else {
                    fileInfo->fileNo++;
                    mgr->chan = fileInfo->chan;
                }
            } else if (card_info->result == CARD_RESULT_WRONGDEVICE || card_info->result == CARD_RESULT_NOCARD ||
                       card_info->result == CARD_RESULT_IOERROR || card_info->result == CARD_RESULT_BROKEN ||
                       card_info->result == CARD_RESULT_FATAL_ERROR || card_info->result == CARD_RESULT_LIMIT ||
                       card_info->result == CARD_RESULT_ENCODING) {
                fileInfo->fileNo = 32;
            }
        }

        if (mgr->chan == -1 || fileInfo->fileNo >= 32) {
            fileInfo->proc = mCD_SAVEHOME_BG_PROC_READ_SEND_PRESENT;
            fileInfo->fileNo = 0;
            fileInfo->chan++;
        }

        if (fileInfo->chan >= CARD_NUM_CHANS) {
            fileInfo->proc = mCD_SAVEHOME_BG_PROC_GET_SLOT;
            mgr->chan = -1;
        }

        return mCD_RESULT_SUCCESS;
    } else {
        return mCD_RESULT_ERROR;
    }
}

static int mCD_write_common(mCD_memMgr_c* mgr) {
    int chan = mgr->chan;
    mCD_memMgr_card_info_c* card_info;
    int res;

    if (mgr->workArea != NULL && chan != -1) {
        card_info = &mgr->cards[chan];
        res = mCD_save_file(mgr->workArea, mgr->loaded_file_type, mgr->chan, &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_write_present(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* file_entry;
    int chan = mgr->chan;
    mCD_memMgr_card_info_c* card_info;
    int ofs;
    int ret;
    int write_res;

    if (chan != -1) {
        file_entry = &l_mcd_file_table[mgr->loaded_file_type];
        ofs = mCD_get_offset(mgr->loaded_file_type);
        card_info = &mgr->cards[chan];
        write_res = mCD_write_comp_bg(mgr->workArea, mgr->filename, mgr->workArea_size, file_entry->filesize, ofs,
                                          chan, &card_info->result);

        card_info->game_result = mCD_TransErrorCode(card_info->result);
        if (write_res != mCD_RESULT_BUSY) {
            if (card_info->result == CARD_RESULT_WRONGDEVICE || card_info->result == CARD_RESULT_NOCARD ||
                card_info->result == CARD_RESULT_IOERROR || card_info->result == CARD_RESULT_BROKEN ||
                card_info->result == CARD_RESULT_FATAL_ERROR || card_info->result == CARD_RESULT_LIMIT ||
                card_info->result == CARD_RESULT_ENCODING) {
                fileInfo->chan++;
                fileInfo->fileNo = 0;
            } else {
                fileInfo->fileNo++;
            }

            if (fileInfo->fileNo >= 32) {
                fileInfo->chan++;
            }

            if (fileInfo->chan >= CARD_NUM_CHANS) {
                fileInfo->proc++;
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                mgr->chan = -1;
            } else {
                fileInfo->proc = mCD_SAVEHOME_BG_PROC_READ_SEND_PRESENT;
            }
        }

        card_info->game_result = mCD_TransErrorCode(card_info->result);
        return mCD_RESULT_SUCCESS;
    } else {
        return mCD_RESULT_ERROR;
    }
}

static int mCD_SaveHome_bg_get_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int res = mCD_RESULT_BUSY;

    if (mgr->cards[0].workArea != NULL && mgr->cards[1].workArea != NULL && mgr->workArea != NULL) {
        if (Save_Get(save_exist) == FALSE) {
            if (mCD_CheckInitProtectCode(&l_keep_noLandCode) == FALSE &&
                mCD_CheckProtectCode(l_keep_noLandCode.code) == TRUE) {
                int slot_res = mCD_GetNoLandSlot_bg(mgr);

                if (slot_res == mCD_RESULT_SUCCESS) {
                    mgr->land_saved = Save_Get(save_exist);
                    mgr->copy_protect = Common_Get(copy_protect);
                    mgr->_0010 = 0b00;
                    fileInfo->proc = mCD_SAVEHOME_BG_PROC_SET_FILE_PERMISSION;
                    res = mCD_RESULT_SUCCESS;
                } else if (slot_res != mCD_RESULT_BUSY) {
                    res = mCD_RESULT_ERROR;
                }
            } else {
                int space_res = mCD_GetSpaceSlot_bg2(mgr, mCD_LAND_SAVE_SIZE);

                if (space_res == TRUE) {
                    if (mgr->chan != -1) {
                        fileInfo->proc++;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        mgr->_0010 = 0b00;
                        res = mCD_RESULT_SUCCESS;
                    } else {
                        res = mCD_RESULT_ERROR;
                    }
                } else if (space_res != mCD_RESULT_BUSY) {
                    res = mCD_RESULT_ERROR;
                }
            }
        } else {
            int land_slot_res = mCD_get_this_land_slot_no_nes(mgr);

            if (land_slot_res == mCD_RESULT_SUCCESS) {
                int chan = mgr->chan;

                if (chan != -1) {
                    if (mCD_check_copyProtect((Save_t*)mgr->workArea, chan) == TRUE) {
                        fileInfo->proc = mCD_SAVEHOME_BG_PROC_CHECK_REPAIR_LAND;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        res = mCD_RESULT_SUCCESS;
                    } else {
                        mgr->cards[chan].game_result = mCD_TRANS_ERR_WRONG_LAND;
                        mgr->land_saved = Save_Get(save_exist);
                        mgr->copy_protect = Common_Get(copy_protect);
                        res = mCD_RESULT_ERROR;
                    }
                } else {
                    res = mCD_RESULT_ERROR;
                }
            } else if (land_slot_res != mCD_RESULT_BUSY) {
                res = mCD_RESULT_ERROR;
            }
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_create_file(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int chan = mgr->chan;
    mCD_memMgr_card_info_c* card_info;
    mCD_file_entry_c* entry = &l_mcd_file_table[mCD_FILE_SAVE_MISC];
    int res;

    if (chan != -1) {
        card_info = &mgr->cards[chan];
        mgr->_019C = 1;
        res = mCD_create_file_bg(l_mCD_land_file_name_dummy, CARD_ATTR_NO_MOVE | CARD_ATTR_NO_COPY,
            entry->filesize, chan, &card_info->result, &card_info->fileNo);
        card_info->game_result = mCD_TransErrorCode(card_info->result);
        if (res == mCD_RESULT_SUCCESS) {
            fileInfo->proc = mCD_SAVEHOME_BG_PROC_SET_FILE_PERMISSION;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_check_broken_land(mCD_memMgr_c* mgr) {
    s32 chan = mgr->chan;
    Save_t* save = (Save_t*)mgr->workArea;
    int ok_save_idx = -1;
    int size;
    int res = FALSE;

    if (chan != -1 && save != NULL) {
        int i;
        
        size = mCD_get_size(mCD_FILE_SAVE_MAIN);
        for (i = 0; i < 2; i++) {
            s32 result;

            if (mCD_load_file(save, mCD_FILE_SAVE_MAIN + i, chan, &result) != mCD_RESULT_SUCCESS) {
                break;
            }

            if (mFRm_ReturnCheckSum((u16*)save, size) == 0 &&
                mFRm_CheckSaveData_common(&save->save_check, save->land_info.id)) {
                ok_save_idx = i;
            } else {
                mgr->broken_file_idx = i;
            }
        }

        if (ok_save_idx != -1 && mgr->broken_file_idx != -1 && ok_save_idx != mgr->broken_file_idx) {
            res = TRUE;
        }
    }

    return res;
}

static int mCD_repair_load_land(mCD_memMgr_c* mgr) {
    s32 chan = mgr->chan;
    Save_t* save = (Save_t*)mgr->workArea;
    int res = FALSE;

    if (chan != -1 && save != NULL && mgr->broken_file_idx != -1) {
        s32 result;

        if (mCD_load_file(save, mCD_FILE_SAVE_MAIN + ((~mgr->broken_file_idx) & 1), chan, &result) ==
            mCD_RESULT_SUCCESS) {
            int size = mCD_get_size(mCD_FILE_SAVE_MAIN);

            if (mFRm_ReturnCheckSum((u16*)save, size) == 0 &&
                mFRm_CheckSaveData_common(&save->save_check, save->land_info.id)) {
                res = TRUE;
            }
        }
    }

    return res;
}

static int mCD_repair_land(mCD_memMgr_c* mgr) {
    int chan = mgr->chan;
    Save_t* save = (Save_t*)mgr->workArea;
    int broken_file_idx = mgr->broken_file_idx;

    if (chan != -1 && save != NULL && broken_file_idx != -1) {
        s32 result;

        /* The loaded file is the 'good' version of the save so we just write it back to the broken save */
        return mCD_save_file(save, mCD_FILE_SAVE_MAIN + broken_file_idx, chan, &result);
    } else {
        return mCD_RESULT_ERROR;
    }
}

static int mCD_SaveHome_bg_check_repair_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    if (mCD_check_broken_land(mgr) == TRUE) {
        if (mCD_repair_load_land(mgr) == TRUE) {
            fileInfo->proc++;
        } else {
            fileInfo->proc = mCD_SAVEHOME_BG_PROC_SET_FILE_PERMISSION;
        }
    } else {
        fileInfo->proc = mCD_SAVEHOME_BG_PROC_SET_FILE_PERMISSION;
    }

    return mCD_RESULT_SUCCESS;
}

static int mCD_SaveHome_bg_repair_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int res = mCD_RESULT_BUSY;

    if (mCD_repair_land(mgr)) {
        fileInfo->proc++;
        res = mCD_RESULT_SUCCESS;
    }

    return res;
}

// @unused mCD_SaveHome_bg_set_icon_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo)
static int mCD_SaveHome_bg_set_icon_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
        // clang-format off
        static int icon_fileNo[] = {
            RESOURCE_EKI1, RESOURCE_EKI1_2, RESOURCE_EKI1_3, RESOURCE_EKI1_4, RESOURCE_EKI1_5,
            RESOURCE_EKI2, RESOURCE_EKI2_2, RESOURCE_EKI2_3, RESOURCE_EKI2_4, RESOURCE_EKI2_5,
            RESOURCE_EKI3, RESOURCE_EKI3_2, RESOURCE_EKI3_3, RESOURCE_EKI3_4, RESOURCE_EKI3_5,
        };
    
        static int banner_fileNo[] = { RESOURCE_MURA_SPRING, RESOURCE_MURA_SUMMER, RESOURCE_MURA_FALL, RESOURCE_MURA_WINTER };
        // clang-format on

        u8* buf = (u8*)mgr->workArea;

        if (buf != NULL) {
            mgr->loaded_file_type = mCD_FILE_SAVE_MISC;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
            bzero(buf, mgr->workArea_size);
            bcopy(l_comment_0_str, buf, sizeof(l_comment_0_str));
            mCD_get_land_comment1((char*)buf + sizeof(l_comment_0_str), Save_Get(land_info).name);
            buf = mCD_set_bti_data(buf, icon_fileNo[Save_Get(station_type)], 0xC00, 1, 0x200);
            buf = mCD_set_bti_data(buf, banner_fileNo[Common_Get(time.season)], 0x400, 1, 0x200);
            fileInfo->proc++;
            return mCD_RESULT_SUCCESS;
        }

        return mCD_RESULT_ERROR;
}

static int mCD_get_status_common(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo, const char* filename,
                                 u32 comment_addr, u32 icon_addr, int icon_fmt, int icon_speed, int icon_frames,
                                 int banner_fmt) {
    mCD_memMgr_card_info_c* card_info;
    s32 chan = mgr->chan;
    int res;

    if (chan != -1) {
        card_info = &mgr->cards[chan];
        res = mCD_get_file_status_bg(&card_info->stat, filename, chan, &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            int i;

            card_info->stat.commentAddr = comment_addr;
            card_info->stat.iconAddr = icon_addr;
            for (i = 0; i < icon_frames; i++) {
                card_info->stat.iconFormat =
                    (card_info->stat.iconFormat & ~(CARD_STAT_ICON_MASK << (i * 2))) | (icon_fmt << (i * 2));
                card_info->stat.iconSpeed =
                    (card_info->stat.iconSpeed & ~(CARD_STAT_SPEED_MASK << (i * 2))) | (icon_speed << (i * 2));
            }

            card_info->stat.bannerFormat = (card_info->stat.bannerFormat & ~CARD_STAT_BANNER_MASK) | banner_fmt;
            fileInfo->proc++;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_set_file_permission(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 chan = mgr->chan;
    mCD_file_entry_c* entry = &l_mcd_file_table[mCD_FILE_SAVE_MISC];
    const char* filename = entry->filename;
    mCD_memMgr_card_info_c* card_info;
    int res = mCD_RESULT_BUSY;

    
    if (chan != -1) {
        if (mgr->_019C == 1) {
            filename = l_mCD_land_file_name_dummy;
        }
        card_info = &mgr->cards[chan];
        res = mCD_set_file_permission_bg(filename, CARD_ATTR_NO_MOVE | CARD_ATTR_NO_COPY, chan, &card_info->result,
                                         &card_info->fileNo);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static void mCD_ClearResetCode(void) {
    bzero(&Now_Private->reset_code, sizeof(Now_Private->reset_code));
}

static int mCD_CheckResetCode(Private_c* priv) {
    int res = TRUE;

    if ((priv->state_flags & mPr_FLAG_BIRTHDAY_ACTIVE) != 0) {
        priv->reset_code = 0;
    }

    if (priv->reset_code != 0) {
        res = FALSE;
    }

    return res;
}

static void mCD_SetResetCode(Private_c* priv) {
    priv->reset_code = (u32)RANDOM_F(USHT_MAX_S);
    priv->reset_code++;
}

static void mCD_SetResetInfo(Private_c* priv) {
    Common_Set(reset_flag, FALSE);
    if (mCD_CheckResetCode(priv) == FALSE) {

        /* No reset penalty if zurumode 2 is enabled */
        if (!ZURUMODE2_ENABLED()) {
            Common_Set(reset_flag, TRUE);
        }

        priv->reset_count++;
    }
}

static u16 mCD_get_land_copyProtect(void) {
    u16 code = RANDOM(0xFFF0);
    code++;
    return code;
}

static int mCD_SaveHome_bg_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save = (Save_t*)mgr->workArea;
    Private_c* priv;
    int _04 = fileInfo->_04;
    int copy_protect;
    mActor_name_t* pockets_p;
    int i;

    if (save != NULL) {
        bzero(save, mgr->workArea_size);
        priv = Now_Private;
        mCkRh_SavePlayTime(Common_Get(player_no));

        if (_04 == 0) {
            mCD_ClearResetCode();
            mAGrw_ClearMoneyStoneShineGround();
        } else if (mCD_CheckResetCode(priv) == TRUE) {
            mCD_SetResetCode(priv);
        }

        if (_04 == 0 && priv != NULL) {
            pockets_p = priv->inventory.pockets;

            /* Clear all Wisp spirits in the player's inventory */
            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                if (ITEM_IS_WISP(*pockets_p)) {
                    mPr_SetPossessionItem(priv, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }

                pockets_p++;
            }
        }

        Save_Set(save_exist, TRUE);
        copy_protect = mCD_get_land_copyProtect();
        Common_Set(copy_protect, copy_protect);
        Save_Set(copy_protect, copy_protect);
        Save_Set(travel_hard_time, lbRTC_HardTime());
        bcopy(&Common_Get(save).save, save, sizeof(Save_t));
        save->save_check.version = mFRm_VERSION;
        mFRm_SetSaveCheckData(&save->save_check);
        save->save_check.checksum = mFRm_GetFlatCheckSum((u16*)save, sizeof(Save), save->save_check.checksum);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        fileInfo->proc++;
        return mCD_RESULT_SUCCESS;
    } else {
        return mCD_RESULT_ERROR;
    }
}

static int mCD_SaveHome_bg_write_main_2(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    void* workArea = mgr->workArea;
    mCD_file_entry_c* file_entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN];
    const char* filename = file_entry->filename;
    int chan = mgr->chan;
    int res;
    Save_t* save = (Save_t*)workArea;

    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    if (workArea != NULL && chan != -1) {
        mCD_memMgr_card_info_c* card_info;
        int ofs;

        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        ofs = mCD_get_offset(mgr->loaded_file_type);
        card_info = &mgr->cards[chan];
        res = mCD_write_comp_bg(save, filename, mgr->workArea_size, file_entry->filesize, ofs, chan,
                                &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
            fileInfo->proc++;
        } else if (res != mCD_RESULT_BUSY) {
            res = mCD_RESULT_ERROR;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    void* workArea = mgr->workArea;
    mCD_file_entry_c* file_entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN_BAK];
    const char* filename = file_entry->filename;
    s32 chan = mgr->chan;
    mCD_memMgr_card_info_c* card_info;
    Private_c* priv = Now_Private;
    int res;
    Save_t* save = (Save_t*)workArea;
    int ofs;

    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    if (workArea != NULL && chan != -1) {
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        ofs = mCD_get_offset(mgr->loaded_file_type);
        card_info = &mgr->cards[chan];
        res = mCD_write_comp_bg(save, filename, mgr->workArea_size, file_entry->filesize, ofs, chan,
                                &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            if (fileInfo->_04 == 1) {
                if (Common_Get(player_decoy_flag) == TRUE && priv != NULL) {
                    priv->exists = TRUE;
                }
            } else {
                Common_Set(player_decoy_flag, FALSE);
            }

            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
            fileInfo->proc++;
        } else if (res != mCD_RESULT_BUSY) {
            res = mCD_RESULT_ERROR;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_SaveHome_bg_set_others(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    // clang-format off
    static int icon_fileNo[] = {
        RESOURCE_EKI1, RESOURCE_EKI1_2, RESOURCE_EKI1_3, RESOURCE_EKI1_4, RESOURCE_EKI1_5,
        RESOURCE_EKI2, RESOURCE_EKI2_2, RESOURCE_EKI2_3, RESOURCE_EKI2_4, RESOURCE_EKI2_5,
        RESOURCE_EKI3, RESOURCE_EKI3_2, RESOURCE_EKI3_3, RESOURCE_EKI3_4, RESOURCE_EKI3_5,
    };

    static int banner_fileNo[] = { RESOURCE_MURA_SPRING, RESOURCE_MURA_SUMMER, RESOURCE_MURA_FALL, RESOURCE_MURA_WINTER };

    
    // clang-format on

    u8* data_p = (u8*)mgr->workArea;
    size_t data_size;

    if (data_p != NULL) {
        bzero(data_p, OTHERS_SIZE);
        bcopy(l_comment_0_str, data_p, sizeof(l_comment_0_str));
        mCD_get_land_comment1((char*)data_p + sizeof(l_comment_0_str), Save_Get(land_info).name);
        data_p = mCD_set_bti_data(data_p + CARD_COMMENT_SIZE, banner_fileNo[Common_Get(time.season)], 0xC00, 1, 0x200);
        data_p = mCD_set_bti_data(data_p, icon_fileNo[Save_Get(station_type)], 0x400, 1, 0x200) + 32;

        {
            mCD_keep_mail_c* mail = (mCD_keep_mail_c*)data_p;

            mCD_save_data_aram_to_main(mail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL], mCD_ARAM_DATA_MAIL);
            mail->landid = Save_Get(land_info).id;
            mail->checksum = mFRm_GetFlatCheckSum((u16*)mail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL], mail->checksum);
            data_p += l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL];
            data_size = (sizeof(MemcardHeader_c) + 32) + l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL];
        }

        {
            mCD_keep_original_c* original = (mCD_keep_original_c*)data_p;

            mCD_save_data_aram_to_main(original, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL], mCD_ARAM_DATA_ORIGINAL);
            original->landid = Save_Get(land_info).id;
            original->checksum = mFRm_GetFlatCheckSum((u16*)original, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL],
                                                      original->checksum);
            data_p += l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL];
            data_size += l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL];
        }

        {
            mCD_keep_diary_c* diary = (mCD_keep_diary_c*)data_p;

            mCD_save_data_aram_to_main(diary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY], mCD_ARAM_DATA_DIARY);
            diary->checksum = mFRm_GetFlatCheckSum((u16*)diary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY],
                                                   diary->checksum);
            data_size += l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY];
        }

        data_size = mCD_ALIGN_SECTORSIZE(data_size);
        mgr->workArea_size = data_size;
        fileInfo->proc++;
        return mCD_RESULT_SUCCESS;
    }

    return mCD_RESULT_ERROR;
}

static int mCD_SaveHome_bg_write_others(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    int ret;
    void* workArea = mgr->workArea;
    mCD_file_entry_c* entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN];
    const char* filename = entry->filename;
    int chan = mgr->chan;

    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    if (mgr->workArea != NULL && chan != -1) {
        card_info = &mgr->cards[chan];
        ret = mCD_write_comp_bg(workArea, filename, mgr->workArea_size, OTHERS_SIZE + sizeof(Save) * 2, 0, chan,
                                &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        } else if (ret != mCD_RESULT_BUSY) {
            ret = mCD_RESULT_ERROR;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveHome_bg_get_status_2(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN];
    const char* filename = entry->filename;

    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    return mCD_get_status_common(mgr, fileInfo, filename, 0, CARD_COMMENT_SIZE, CARD_STAT_ICON_C8, CARD_STAT_SPEED_SLOW, 1, CARD_STAT_BANNER_C8);
}

static int mCD_SaveHome_bg_set_status_2(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    int ret;
    mCD_file_entry_c* entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN];
    const char* filename = entry->filename;
    int chan = mgr->chan;

    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    if (chan != -1) {
        card_info = &mgr->cards[chan];
        ret = mCD_set_file_status_bg(&card_info->stat, filename, chan, &card_info->result);
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveHome_bg_rename(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    int ret = mCD_RESULT_ERROR;
    int chan = mgr->chan;

    if (mgr->_019C == 1) {
        if (chan != -1) {
            card_info = &mgr->cards[chan];
            
            if (card_info->workArea != NULL) {
                if (mCD_rename_file_fg(l_mCD_land_file_name, l_mCD_land_file_name_dummy, chan, &card_info->result, card_info->workArea) == TRUE) {
                    fileInfo->proc++;
                    ret = mCD_RESULT_SUCCESS;
                }
            }
        }
    } else {
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    }

    return ret;
}

static int mCD_SaveHome_ChangeErrCode(int err_code) {
    switch (err_code) {
        default:
            break;
        case mCD_TRANS_ERR_TOWN_INVALID:
        case mCD_TRANS_ERR_16:
        case mCD_TRANS_ERR_GENERIC:
            err_code = mCD_TRANS_ERR_NONE;
            break;
        case mCD_TRANS_ERR_OTHER_TOWN:
            err_code = mCD_TRANS_ERR_NOCARD;
            break;
    }

    return err_code;
}

static void mCD_create_famicom_file(int chan) {
    if (mLd_PlayerManKindCheck() == FALSE) {
        famicom_internal_data_save();
    }
}

static void mCD_load_famicom_file(void) {
    if (mLd_PlayerManKindCheck() == FALSE) {
        famicom_internal_data_load();
    }
}

typedef int (*mCD_SAVEHOME_PROC)(mCD_memMgr_c*, mCD_memMgr_fileInfo_c*);

extern int mCD_SaveHome_bg(int param_1, int* chan) {
    // clang-format off
    static mCD_SAVEHOME_PROC save_proc[] = {
        mCD_SaveHome_bg_get_area,
        mCD_SaveHome_bg_erase_dummy,
        mCD_SaveHome_bg_check_slot,
        mCD_SaveHome_bg_read_send_present,
        mCD_SaveHome_bg_write_present,
        mCD_SaveHome_bg_get_slot,
        mCD_SaveHome_bg_create_file,
        mCD_SaveHome_bg_check_repair_land,
        mCD_SaveHome_bg_repair_land,
        mCD_SaveHome_bg_set_file_permission,
        mCD_SaveHome_bg_set_data,
        mCD_SaveHome_bg_write_main_2,
        mCD_SaveHome_bg_write_bk,
        mCD_SaveHome_bg_set_others,
        mCD_SaveHome_bg_write_others,
        mCD_SaveHome_bg_get_status_2,
        mCD_SaveHome_bg_set_status_2,
        mCD_SaveHome_bg_rename,
    };
    // clang-format on
    
    mCD_memMgr_card_info_c* cardInfo;
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    int ret = mCD_TRANS_ERR_BUSY;
    u8 proc = (u8)fileInfo->proc;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 18) {
            int res;
            
            fileInfo->_04 = param_1;
            res = (*save_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 18) {
                    *chan = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                    mCD_ClearNoLandProtectCode(&l_keep_noLandCode);
                }
            } else if (res != mCD_RESULT_BUSY) {
                int cur_chan = mgr->chan;

                if (cur_chan == 0 || cur_chan == 1) {
                    *chan = cur_chan;
                    cardInfo = &mgr->cards[mgr->chan];
                    ret = cardInfo->game_result;
                } else {
                    ret = mCD_TRANS_ERR_NOCARD;
                }

                if (mgr->land_saved != -1) {
                    Save_Set(save_exist, mgr->land_saved);
                }

                if (mgr->copy_protect != -1 && fileInfo->proc < 12) {
                    Common_Set(copy_protect, mgr->copy_protect);
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 18)) {
                if (mgr->_0188 >= 112) {
                    if (res == mCD_RESULT_SUCCESS) {
                        mCD_create_famicom_file(mgr->chan);
                    }

                    sAdo_SysLevStop(NA_SE_47);
                    mCD_ClearMemMgr_com2(mgr);
                } else {

                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    mgr->_0194 = *chan;
                    ret = mCD_TRANS_ERR_BUSY;
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else {
        if (mgr->_0188 >= 112) {
            ret = mgr->_0190;
            *chan = mgr->_0194;
            mCD_ClearMemMgr_com2(mgr);
            if (ret == mCD_TRANS_ERR_NONE) {
                mCD_create_famicom_file(*chan);
            }
            sAdo_SysLevStop(NA_SE_47);
        }
    }

    ret = mCD_SaveHome_ChangeErrCode(ret);
    if (ret != mCD_TRANS_ERR_BUSY) {
        SoftResetEnable = TRUE;
    }
    return ret;
}

static int mCD_TransErrCodeToCond(int err_code) {
    switch (err_code) {
        case mCD_TRANS_ERR_IOERROR:
            return 4;
        case mCD_TRANS_ERR_NOT_MEMCARD:
            return 6;
        case mCD_TRANS_ERR_BROKEN_WRONGENCODING:
        case mCD_TRANS_ERR_REPAIR:
            return 5;
        case mCD_TRANS_ERR_16:
            return 2;
        case mCD_TRANS_ERR_NO_SPACE:
        case mCD_TRANS_ERR_GENERIC:
            return 7;
        case mCD_TRANS_ERR_WRONGDEVICE:
            return 8;
        default:
            return 9;
    }
}

static void mCD_load_set_others_common(mCD_memMgr_c* mgr, mCD_memMgr_card_info_c* card_info, int chan, int diary_flag) {
    u8* data_p = (u8*)mgr->workArea;
    mCD_file_entry_c* entry;

    bzero(data_p, OTHERS_SIZE);

    entry = &l_mcd_file_table[mCD_FILE_SAVE_MISC];
    if (mCD_read_fg(data_p, entry->filename, entry->entrysize, 0, chan, &card_info->result) == mCD_RESULT_SUCCESS) {
        data_p += sizeof(MemcardHeader_c) + 32;
        
        {
            mCD_keep_mail_c* mail = (mCD_keep_mail_c*)data_p;

            if (mFRm_ReturnCheckSum((u16*)mail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL]) == 0) {
                mCD_save_data_main_to_aram(mail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL], mCD_ARAM_DATA_MAIL);
            }

            data_p += l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL];
        }

        {
            mCD_keep_original_c* original = (mCD_keep_original_c*)data_p;

            if (mFRm_ReturnCheckSum((u16*)original, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL]) == 0) {
                mCD_save_data_main_to_aram(original, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL], mCD_ARAM_DATA_ORIGINAL);
            }

            data_p += l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL];
        }

        if (diary_flag) {
            mCD_keep_diary_c* diary = (mCD_keep_diary_c*)data_p;

            if (mFRm_ReturnCheckSum((u16*)diary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY]) == 0) {
                mCD_save_data_main_to_aram(diary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY], mCD_ARAM_DATA_DIARY);
            }
        }
    }
}

extern void mCD_LoadLand(void) {
    static u16 noLand_code[2][8];
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    Save_t* save;
    int noLand_info[2];
    u8 cond[2];
    int flashrom_cond = 9;
    int save_found = FALSE;
    mCD_memMgr_fileInfo_c* save_home_info = &mgr->save_home_info;
    int bad_save_chan;
    int save_chan = -1;
    int type;
    s32 chan;
    int res;

    res = mCD_bg_get_area_common(mgr, save_home_info, mCD_FILE_SAVE_MAIN, 2);
    save = (Save_t*)mgr->workArea;

    if (res == mCD_RESULT_SUCCESS) {
        for (chan = 0; chan < 2; chan++) {
            noLand_info[chan] = 0;
            cond[chan] = 9;
            bad_save_chan = 0;

            for (type = 0; type < 2; type++) {
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN + type; // main -> main backup
                mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                bzero(save, mgr->workArea_size);

                if (mCD_load_file(save, mgr->loaded_file_type, chan, &card_info->result) == mCD_RESULT_SUCCESS) {
                    if (mFRm_CheckSaveData_common(&save->save_check, save->land_info.id)) {
                        if (mFRm_ReturnCheckSum((u16*)save, mgr->workArea_size) == 0 && (save->save_check.version == 6 || save->save_check.version == 5)) {
                            bcopy(save, Common_GetPointer(save), sizeof(Save));
                            save_found = TRUE;
                            Common_Set(copy_protect, Save_Get(copy_protect));
                            cond[chan] = 0;
                            save_chan = chan;
                            if (type == 1) {
                                mCD_OnErrInfo(mCD_ERROR_OUTDATED); // loaded backup
                            } else {
                                mCD_OffErrInfo(mCD_ERROR_OUTDATED); // loaded main
                            }

                            break;
                        } else {
                            cond[chan] = 2;
                        }
                    } else if (cond[chan] == 9) {
                        cond[chan] = 0;
                        bad_save_chan++;
                    }
                } else {
                    if (card_info->result == CARD_RESULT_NOFILE) {
                        if (mCD_find_fg(l_mCD_land_file_name_dummy, card_info->workArea, chan, &card_info->result) == TRUE) {
                            cond[chan] = 0;
                        } else {
                            int res = mCD_RESULT_BUSY;

                            while (res == mCD_RESULT_BUSY) {
                                res = mCD_get_space_bg(&card_info->freeBytes, chan, &card_info->result, card_info->workArea);
                            }

                            if (res == mCD_RESULT_SUCCESS) {
                                if (card_info->freeBytes >= mCD_LAND_SAVE_SIZE) {
                                    if (mCD_CheckPassportFile_slot(chan, card_info->workArea) == TRUE) {
                                        cond[chan] = 1;
                                    } else if (mCD_get_file_num(card_info->workArea, chan) >= CARD_MAX_FILE) {
                                        cond[chan] = 3;
                                    } else {
                                        cond[chan] = 0;
                                    }
                                } else {
                                    cond[chan] = 7;
                                }
                            } else {
                                cond[chan] = mCD_TransErrCodeToCond(mCD_TransErrorCode(card_info->result));
                            }
                        }
                    } else if (mCD_check_sector_size(mCD_MEMCARD_SECTORSIZE, chan) == FALSE) {
                        cond[chan] = 6;
                    } else {
                        cond[chan] = mCD_TransErrCodeToCond(mCD_TransErrorCode_nes(card_info->result));
                    }
                    break;
                }
            }

            if (save_found == TRUE) {
                break;
            }

            if (bad_save_chan == 1 && save_chan == -1) {
                noLand_info[chan] = mCD_check_noLand_file((mCD_LandProtectCode_c*)noLand_code[chan], (u8*)mgr->workArea, chan);
                save_chan = chan;
            }

            card_info++;
        }

        if (save_found == FALSE) {
            if (save_chan != -1) {
                if (noLand_info[save_chan] == TRUE) {
                    bcopy(noLand_code[save_chan], &l_keep_noLandCode, sizeof(l_keep_noLandCode));
                    flashrom_cond = 0;
                    mCD_load_set_others_common(mgr, &mgr->cards[save_chan], save_chan, FALSE);
                } else {
                    flashrom_cond = 2;
                }
            } else {
                if (cond[0] > cond[1]) {
                    flashrom_cond = cond[1];
                    save_chan = 1;
                } else {
                    flashrom_cond = cond[0];
                    save_chan = 0;
                }
            }
        } else {
            flashrom_cond = cond[save_chan];
            mCD_load_set_others_common(mgr, &mgr->cards[save_chan], save_chan, TRUE);
        }
    }

    Common_Set(save_error_type, flashrom_cond);

    if (save_chan != -1) {
        Common_Set(memcard_slot, save_chan);
    } else {
        Common_Set(memcard_slot, 0);
    }

    mCD_ClearMemMgr_com2(mgr);
    
    if (mFRm_CheckSaveData_common(Save_GetPointer(save_check), Save_Get(land_info).id) && Save_Get(save_check).version == 5) {
        bcopy(&Save_Get(save_check).time, Save_GetPointer(saved_auto_nwrite_time), sizeof(lbRTC_time_c));
    }
}

extern void mCD_ReCheckLoadLand(GAME_PLAY* play) {
    int scene = Save_Get(scene_no);
    int bad;

    mCD_LoadLand();
    Save_Set(scene_no, scene);

    switch (Common_Get(save_error_type)) {
        case 0:
            bad = TRUE;
            break;
        default:
            bad = FALSE;
            break;
    }

    if (bad == FALSE) {
        scene = SCENE_PLAYERSELECT_3;
        Common_Set(house_owner_name, RSV_NO);
        Common_Set(last_field_id, RSV_NO);
    } else {
        int res = mFRm_CheckSaveData();
        
        if (res == FALSE) {
            scene = SCENE_PLAYERSELECT;
            Common_Set(house_owner_name, RSV_NO);
            Common_Set(last_field_id, RSV_NO);
        } else {
            int rtc_on = Common_Get(time.rtc_enabled);
            Common_Set(time.rtc_enabled, TRUE);
            mTM_rtcTime_limit_check();
            scene = SCENE_PLAYERSELECT_2;
            Common_Set(time.rtc_enabled, rtc_on);
            mEv_ClearEventInfo();
        }
    }


    play->next_scene_no = scene;
}

static int mCD_EraseLand_ChangeErrCode(int err_code) {
    switch (err_code) {
        case mCD_TRANS_ERR_BROKEN_WRONGENCODING:
        case mCD_TRANS_ERR_REPAIR:
        case mCD_TRANS_ERR_TOWN_INVALID:
        case mCD_TRANS_ERR_16:
        case mCD_TRANS_ERR_GENERIC:
            err_code = mCD_TRANS_ERR_IOERROR;
            break;
        case mCD_TRANS_ERR_NO_SPACE:
        case mCD_TRANS_ERR_OTHER_TOWN:
            err_code = mCD_TRANS_ERR_NOCARD;
            break;
    }

    return err_code;
}

static int mCD_EraseLand_bg_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    return mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 1);
}

static int mCD_EraseLand_bg_get_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info = mgr->cards;
    int res = mCD_RESULT_BUSY;
    
    if (mgr->cards[0].workArea != NULL && mgr->cards[1].workArea != NULL && mgr->workArea != NULL) {
        if (Save_Get(save_exist) == FALSE) {
            res = mCD_RESULT_ERROR;
        } else {
            int slot = mCD_get_this_land_slot_no(mgr);
            
            if (slot == mCD_SLOT_B) {
                if (mgr->chan != -1) {
                    res = mCD_RESULT_SUCCESS;
                    fileInfo->proc++;
                } else {
                    res = mCD_RESULT_ERROR;
                } 
            } else if (slot != mCD_SLOT_A) {
                res = mCD_RESULT_ERROR;
            }
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_EraseLand_bg_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    u8* data_p = (u8*)mgr->workArea;
    int res;

    if (data_p != NULL && mgr->chan != -1) {
        bzero(data_p, CARD_WORKAREA_SIZE);
        bcopy(Common_GetPointer(save), data_p, CARD_WORKAREA_SIZE);
        mFRm_ClearSaveCheckData((mFRm_chk_t*)data_p);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mCD_FILE_SAVE_MAIN);
        card_info = &mgr->cards[mgr->chan];
        card_info->game_result = mCD_TRANS_ERR_NOCARD;
        fileInfo->proc++;
        res = mCD_RESULT_SUCCESS;
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_EraseLand_bg_write_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* entry;
    mCD_memMgr_card_info_c* card_info;
    int res;
    int chan = mgr->chan;
    int ofs;

    if (chan != -1) {
        entry = &l_mcd_file_table[mgr->loaded_file_type];
        ofs = mCD_get_offset(mgr->loaded_file_type);
        card_info = &mgr->cards[chan];
        res = mCD_write_comp_bg(mgr->workArea, entry->filename, mgr->workArea_size, entry->filesize, ofs, chan, &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}


static int mCD_EraseLand_bg_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* entry;
    mCD_memMgr_card_info_c* card_info;
    int res;
    int chan = mgr->chan;
    int ofs;

    if (chan != -1) {
        entry = &l_mcd_file_table[mgr->loaded_file_type];
        ofs = mCD_get_offset(mgr->loaded_file_type);
        card_info = &mgr->cards[chan];
        res = mCD_write_comp_bg(mgr->workArea, entry->filename, mgr->workArea_size, entry->filesize, ofs, chan, &card_info->result);
        card_info->game_result = mCD_TransErrorCode(card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
            bzero(mgr->workArea, mgr->workArea_size);
            mgr->loaded_file_type = mCD_FILE_SAVE_MISC;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_EraseLand_bg_load_icon(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    int res;
    int chan = mgr->chan;

    if (chan != -1) {
        card_info = &mgr->cards[chan];
        res = mCD_load_file(mgr->workArea, mgr->loaded_file_type, chan, &card_info->result);

        if (res == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
            bcopy(l_comment_erase_land, (u8*)mgr->workArea + sizeof(l_comment_0_str), sizeof(l_comment_erase_land));
            mCD_MakeProtectCode((mCD_LandProtectCode_c*)((u8*)mgr->workArea + sizeof(MemcardHeader_c)));
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_EraseLand_bg_write_icon(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int res;
    
    res = mCD_write_common(mgr);

    if (res == mCD_RESULT_SUCCESS) {
        fileInfo->proc++;
    }

    return res;
}

extern int mCD_EraseLand_bg(int* slot) {
    // clang-format off
    static mCD_SAVEHOME_PROC erase_proc[] = {
        mCD_EraseLand_bg_get_area,
        mCD_EraseLand_bg_get_slot,
        mCD_EraseLand_bg_set_data,
        mCD_EraseLand_bg_write_main,
        mCD_EraseLand_bg_write_bk,
        mCD_EraseLand_bg_load_icon,
        mCD_EraseLand_bg_write_icon,
    };
    // clang-format on

    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    mCD_memMgr_card_info_c* card_info;
    int res;
    u8 proc = (u8)fileInfo->proc;
    int ret = mCD_TRANS_ERR_BUSY;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 7) {
            res = (*erase_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 7) {
                    *slot = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                int cur_chan = mgr->chan;

                if (cur_chan == 0 || cur_chan == 1) {
                    *slot = cur_chan;
                    card_info = &mgr->cards[mgr->chan];
                    ret = card_info->game_result;
                } else {
                    ret = mCD_TRANS_ERR_NOCARD;
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 7)) {
                if (mgr->_0188 >= 170) {
                    sAdo_SysLevStop(NA_SE_53);
                    mCD_ClearMemMgr_com2(mgr);
                } else {
                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    mgr->_0194 = *slot;
                    ret = mCD_TRANS_ERR_BUSY;
                    
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else if (mgr->_0188 >= 170) {
        ret = mgr->_0190;
        *slot = mgr->_0194;
        mCD_ClearMemMgr_com2(mgr);
        sAdo_SysLevStop(NA_SE_53);
    }

    return mCD_EraseLand_ChangeErrCode(ret);
}

static int mCD_EraseBrokenLand_bg_get_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    Save_t* save;
    int sel_chan;
    int i;
    s32 chan;
    int type;
    int ret;
    
    save = (Save_t*)mgr->workArea;
    card_info = mgr->cards;
    sel_chan = -1;
    if (mgr->cards[mCD_SLOT_A].workArea != NULL && mgr->cards[mCD_SLOT_B].workArea != NULL && mgr->workArea != NULL) {
        for (chan = 0; chan < 2; chan++) {
            card_info->game_result = mCD_TRANS_ERR_NOCARD;

            for (i = 0, type = 0; type < 2; type++) {
                int size;

                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN + type;
                mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                bzero(save, mgr->workArea_size);

                if (mCD_load_file(save, mgr->loaded_file_type, chan, &card_info->result) == mCD_RESULT_SUCCESS) {
                    if (mFRm_CheckSaveData_common(&save->save_check, save->land_info.id)) {
                        if (mFRm_ReturnCheckSum((u16*)save, mgr->workArea_size) == 0 && (save->save_check.version == 6 || save->save_check.version == 5)) {
                            card_info->game_result = mCD_TRANS_ERR_15;
                            sel_chan = chan;
                            break;
                        } else {
                            i++;
                        }
                    } else {
                        i++;
                    }
                } else {
                    card_info->game_result = mCD_TransErrorCode(card_info->result);
                    break;
                }
            }
                        
            if (i == 2) {
                mgr->chan = chan;
                break;
            }

            card_info++;
        }

        if (mgr->chan != -1) {
            fileInfo->proc++;
            ret = mCD_RESULT_SUCCESS;
        } else {
            if (sel_chan != -1) {
                mgr->chan = sel_chan;
            } else {
                mCD_GetHighPriority_common(mgr, mgr->cards[mCD_SLOT_A].game_result, mgr->cards[mCD_SLOT_B].game_result);
            }
            ret = mCD_RESULT_ERROR;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

extern int mCD_EraseBrokenLand_bg(int* slot) {
    // clang-format off
    static mCD_SAVEHOME_PROC erase_proc[] = {
        mCD_EraseLand_bg_get_area,
        mCD_EraseBrokenLand_bg_get_slot,
        mCD_EraseLand_bg_set_data,
        mCD_EraseLand_bg_write_main,
        mCD_EraseLand_bg_write_bk,
        mCD_EraseLand_bg_load_icon,
        mCD_EraseLand_bg_write_icon,
    };
    // clang-format on

    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    mCD_memMgr_card_info_c* card_info;
    int res;
    u8 proc = (u8)fileInfo->proc;
    int ret = mCD_TRANS_ERR_BUSY;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 7) {
            res = (*erase_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 7) {
                    *slot = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                int cur_chan = mgr->chan;

                if (cur_chan == 0 || cur_chan == 1) {
                    *slot = cur_chan;
                    card_info = &mgr->cards[mgr->chan];
                    ret = card_info->game_result;
                } else {
                    ret = mCD_TRANS_ERR_NOCARD;
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 7)) {
                if (mgr->_0188 >= 170) {
                    sAdo_SysLevStop(NA_SE_53);
                    mCD_ClearMemMgr_com2(mgr);
                } else {
                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    mgr->_0194 = *slot;
                    ret = mCD_TRANS_ERR_BUSY;
                    
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else if (mgr->_0188 >= 170) {
        ret = mgr->_0190;
        *slot = mgr->_0194;
        mCD_ClearMemMgr_com2(mgr);
        sAdo_SysLevStop(NA_SE_53);
    }

    return mCD_EraseLand_ChangeErrCode(ret);
}

extern int mCD_CheckPassportFile(void) {
    void* workArea;
    int ret;
    
    ret = -1;
    workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);
    
    if (workArea != NULL) {
        int i;
        
        for (i = 0; i < 2; i++) {
            if (mCD_CheckPassportFile_slot(i, workArea) == TRUE) {
                ret = i;
                break;
            }
        }
        
        if (workArea != NULL) {
            zelda_free(workArea);
        }
    }
    
    return ret;
}

extern int mCD_CheckBrokenPassportFile(int slot) {
    ForeignerFile_c* foreigner_file;
    void* workArea;
    int i;
    int ret;
    s32 result;
    CARDStat stat;
    CARDFileInfo file_info;
    
    ret = FALSE;
    workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);
    foreigner_file = (ForeignerFile_c*)mCD_malloc_32(mCD_PLAYER_SAVE_SIZE);
    if ((slot == mCD_SLOT_A || slot == mCD_SLOT_B) && workArea != NULL && foreigner_file != NULL && mCD_check_card(&result, mCD_MEMCARD_SECTORSIZE, slot) == TRUE) {
        result = CARDMount((s32)slot, workArea, NULL);
        if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
            result = CARDCheck((s32)slot);
            if (result == CARD_RESULT_READY) {

                for (i = 0; i < CARD_MAX_FILE; i++) {
                    result = CARDGetStatus((s32)slot, i, &stat);

                    if (result == CARD_RESULT_READY && mCD_CheckPassportFileStatus(&stat) == TRUE) {
                        result = CARDOpen((s32)slot, stat.fileName, &file_info);

                        if (result == CARD_RESULT_READY) {
                            result = CARDRead(&file_info, foreigner_file, mCD_PLAYER_SAVE_SIZE, 0);
                            
                            if (result == CARD_RESULT_READY && (mFRm_ReturnCheckSum((u16*)&foreigner_file->file, sizeof(mCD_foreigner_c)) != 0 || mPr_NullCheckPersonalID(&foreigner_file->file.priv.player_ID) == TRUE)) {
                                CARDClose(&file_info);
                                ret = TRUE;
                                break;
                            }

                            CARDClose(&file_info);
                        }
                    }
                }
            }

            CARDUnmount((s32)slot);
        } else if (result == CARD_RESULT_ENCODING) {
            CARDUnmount((s32)slot);
        }

        if (workArea != NULL) {
            zelda_free(workArea);
        }

        if (foreigner_file != NULL) {
            zelda_free(foreigner_file);
        }
    }

    return ret;
}

static int mCD_ErasePassport_bg_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    return mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_PLAYER, 1);
}

static int mCD_ErasePassport_bg_mount_card(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    int res;
    int chan = mgr->chan;

    if (chan != -1) {
        card_info = &mgr->cards[chan];
        if (card_info->workArea != NULL && mCD_check_card(&card_info->result, mCD_MEMCARD_SECTORSIZE, chan) == TRUE) {
            card_info->result = CARDMount((s32)chan, card_info->workArea, NULL);
            if (card_info->result == CARD_RESULT_READY || card_info->result == CARD_RESULT_BROKEN) {
                card_info->result = CARDCheck((s32)chan);
                if (card_info->result == CARD_RESULT_READY) {
                    res = mCD_RESULT_SUCCESS;
                    fileInfo->proc++;
                } else {
                    CARDUnmount((s32)chan);
                    res = mCD_RESULT_ERROR;
                }
            } else {
                if (card_info->result == CARD_RESULT_ENCODING) {
                    CARDUnmount((s32)chan);
                }

                res = mCD_RESULT_ERROR;
            }
        } else {
            res = mCD_RESULT_ERROR;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_ErasePassportFile_bg_get_broken_Passport(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card_info;
    ForeignerFile_c* foreigner_file;
    int ret;
    int i;
    CARDFileInfo file_info;
    int chan;
    int fileNo;
    CARDStat* stat;
    
    foreigner_file = (ForeignerFile_c*)mgr->workArea;
    chan = mgr->chan;
    fileNo = fileInfo->_04;
    ret = mCD_RESULT_BUSY;
    
    if (chan != -1 && foreigner_file != NULL) {
        card_info = &mgr->cards[chan];
        stat = &card_info->stat;
        for (i = fileNo; i < CARD_MAX_FILE; i++) {
            card_info->result = CARDGetStatus((s32)chan, i, stat);

            if (card_info->result == CARD_RESULT_READY && mCD_CheckPassportFileStatus(stat) == TRUE) {
                card_info->result = CARDOpen((s32)chan, stat->fileName, &file_info);

                if (card_info->result == CARD_RESULT_READY) {
                    card_info->result = CARDRead(&file_info, foreigner_file, mCD_PLAYER_SAVE_SIZE, 0);
                    
                    if (card_info->result == CARD_RESULT_READY && (mFRm_ReturnCheckSum((u16*)&foreigner_file->file, sizeof(mCD_foreigner_c)) != 0 || mPr_NullCheckPersonalID(&foreigner_file->file.priv.player_ID) == TRUE)) {
                        fileInfo->_04 = i;
                        CARDClose(&file_info);
                        card_info->result = CARDDeleteAsync((s32)chan, stat->fileName, NULL);
                        if (card_info->result == CARD_RESULT_READY) {
                            ret = mCD_RESULT_SUCCESS;
                            fileInfo->proc++;
                        } else {
                            ret = mCD_RESULT_ERROR;
                        }
                        break;
                    }

                    CARDClose(&file_info);
                }
            }
        }

        if (i == CARD_MAX_FILE) {
            CARDUnmount((s32)chan);
            ret = mCD_RESULT_SUCCESS;
            fileInfo->proc = 4;
        } else {
            if (ret == mCD_RESULT_ERROR) {
                CARDUnmount((s32)chan);
            }
        }
    } else {
        if (chan != -1) {
            CARDUnmount((s32)chan);
        }

        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_ErasePassportFile_bg_erase(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* info;
    int chan = mgr->chan;
    int _04 = fileInfo->_04;
    int ret = mCD_RESULT_BUSY;

    if (chan != -1 && _04 >= 0 && _04 < 127) {
        info = &mgr->cards[chan];
        info->result = CARDGetResultCode(chan);
        if (info->result == CARD_RESULT_READY) {
            fileInfo->_04++;

            if (fileInfo->_04 >= 127) {
                CARDUnmount(chan);
                fileInfo->proc = 4;
            } else {
                fileInfo->proc = 2;
            }

            ret = mCD_RESULT_SUCCESS;
        } else if (info->result != CARD_RESULT_BUSY) {
            CARDUnmount(chan);
            ret = mCD_RESULT_ERROR;
        }
    } else {
        if (chan != -1) {
            CARDUnmount(chan);
        }

        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

extern int mCD_ErasePassportFile_bg(int slot) {
    // clang-format off
    static mCD_SAVEHOME_PROC erase_proc[] = {
        mCD_ErasePassport_bg_get_area,
        mCD_ErasePassport_bg_mount_card,
        mCD_ErasePassportFile_bg_get_broken_Passport,
        mCD_ErasePassportFile_bg_erase,
    };
    // clang-format on

    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    mCD_memMgr_card_info_c* card_info;
    int res;
    u8 proc = (u8)fileInfo->proc;
    int ret = mCD_RESULT_BUSY;

    mgr->_0188++;
    mgr->chan = slot;
    if (mgr->_018C == 0) {
        if (proc < 4) {
            res = (*erase_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 4) {
                    ret = mCD_RESULT_SUCCESS;
                }
            } else if (res != mCD_RESULT_BUSY) {
                ret = mCD_RESULT_ERROR;
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 4)) {
                if (mgr->_0188 >= 170) {
                    sAdo_SysLevStop(NA_SE_53);
                    mCD_ClearMemMgr_com2(mgr);
                } else {
                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    ret = mCD_RESULT_BUSY;
                }
            }
        } else {
            ret = mCD_RESULT_ERROR;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else if (mgr->_0188 >= 170) {
        ret = l_memMgr._0190;
        mCD_ClearMemMgr_com2(mgr);
        sAdo_SysLevStop(NA_SE_53);
    }

    return ret;
}

static int mCD_GameStart_ChangeErrCode(int err_code) {
    switch (err_code) {
        case mCD_TRANS_ERR_BROKEN_WRONGENCODING:
        case mCD_TRANS_ERR_REPAIR:
        case mCD_TRANS_ERR_TOWN_INVALID:
        case mCD_TRANS_ERR_16:
        case mCD_TRANS_ERR_GENERIC:
            err_code = mCD_TRANS_ERR_IOERROR;
            break;

        case mCD_TRANS_ERR_NO_SPACE:
        case mCD_TRANS_ERR_OTHER_TOWN:
            err_code = mCD_TRANS_ERR_NOCARD;
            break;
    }

    return err_code;
}

static void mCD_SetCopyProtect(mCD_foreigner_c* passport) {
    f32 random = fqrand();
    u16 code = (u16)(random * 0xFFFE);

    l_mcd_copy_protect = code;
    passport->copy_protect = code;
    passport->checksum = mFRm_GetFlatCheckSum((u16*)passport, sizeof(mCD_foreigner_c), passport->checksum);
}

static Private_c* mCD_GetSaveFilePrivateP(void) {
    return &l_mcd_foreigner_file.file.priv;
}

static int mCD_InitGameStart_bg_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    static int sound_mode[] = { 2, 0, 0, 0, 0 };
    
    int soundm = 2;

    if (fileInfo->chan >= 0 && fileInfo->chan < 5) {
        soundm = sound_mode[fileInfo->chan];
    }

    fileInfo->_10 = soundm;
    SoftResetEnable = FALSE;
    return mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, soundm);
}

static int mCD_InitGameStart_bg_get_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int _0C = fileInfo->chan;
    int res = mCD_RESULT_BUSY;
    
    if (mgr->cards[0].workArea != NULL && mgr->cards[1].workArea != NULL && mgr->workArea != NULL) {
        if (_0C == 0 || _0C == 2) {
            res = mCD_RESULT_SUCCESS;
            fileInfo->proc = 4;
        } else {
            int slot = mCD_get_this_land_slot_no_game_start(mgr);
            
            if (slot == mCD_SLOT_B) {
                int chan = mgr->chan;

                if (chan != -1) {
                    if (mCD_check_copyProtect((Save_t*)mgr->workArea, chan) == TRUE) {
                        res = mCD_RESULT_SUCCESS;
                        fileInfo->proc++;
                    } else {
                        mCD_memMgr_card_info_c* card_info = mgr->cards;

                        res = mCD_RESULT_ERROR;
                        card_info[chan].game_result = mCD_TRANS_ERR_WRONG_LAND;
                    }
                } else {
                    res = mCD_RESULT_ERROR;
                } 
            } else if (slot != mCD_SLOT_A) {
                res = mCD_RESULT_ERROR;
            }
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_InitGameStart_bg_check_repair_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    if (mCD_check_broken_land(mgr) == TRUE) {
        if (mCD_repair_load_land(mgr) == TRUE) {
            fileInfo->proc++;
        } else {
            fileInfo->proc = 4;
        }
    } else {
        fileInfo->proc = 4;
    }

    return mCD_RESULT_SUCCESS;
}

static int mCD_LoadPrivate_idx(mCD_memMgr_c* mgr, Private_c* priv, Animal_c* animal, int idx) {
    ForeignerFile_c* file;
    mCD_foreigner_c* foreigner;
    void* workArea = mgr->workArea;
    mCD_cardPrivate_c* card_priv;
    int ret = FALSE;

    if (workArea != NULL && idx >= 0 && idx < ARRAY_SIZE(l_mcd_card_private_table, mCD_cardPrivate_c)) {
        card_priv = &l_mcd_card_private_table[idx];
        
        if (!mPr_NullCheckPersonalID(&card_priv->pid)) {
            s32 result;
            int i;
            
            for (i = 0; i < mCD_SLOT_NUM; i++) {
                file = (ForeignerFile_c*)workArea;
                foreigner = &file->file;

                bzero(workArea, sizeof(ForeignerFile_c));

                if (mCD_read_fg(file, card_priv->filename, sizeof(ForeignerFile_c), 0, i, &result) == mCD_RESULT_SUCCESS) {
                    if (mFRm_ReturnCheckSum((u16*)foreigner, sizeof(mCD_foreigner_c)) == 0 &&
                        mPr_CheckCmpPersonalID(&foreigner->priv.player_ID, &card_priv->pid) == TRUE
                    ) {
                        mPr_CopyPrivateInfo(priv, &foreigner->priv);
                        if (animal != NULL) {
                            bcopy(&foreigner->remove_animal, animal, sizeof(Animal_c));
                        }

                        bcopy(foreigner, &l_mcd_foreigner_file.file, sizeof(l_mcd_foreigner_file));
                        ret = TRUE;
                        break;
                    }
                }
            }
        }
    }
    
    return ret;
}

static int mCD_InitGameStart_bg_make_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    GAME* game = gamePT;
    int player_no = fileInfo->_04;
    int private_idx = fileInfo->fileNo;
    int start_cond = fileInfo->chan;
    Private_c* priv;
    Animal_c* in_animal = mNpc_GetInAnimalP();
    mCD_cardPrivate_c* card_priv;
    u16 copy_protect;
    int res = TRUE;
    int ret;


    if (start_cond >= 5) {
        start_cond = 0;
        fileInfo->chan = 0;
    }

    switch (start_cond) {
        case 3:
            priv = mPr_GetForeignerP();
            res = mCD_LoadPrivate_idx(mgr, priv, in_animal, private_idx);
            if (res == TRUE) {
                mPr_LoadPak_and_SetPrivateInfo2(priv, player_no);
                card_priv = &l_mcd_card_private_table[private_idx];
                mCD_SetCardPrivateTable(&l_mcd_card_private, &card_priv->pid, card_priv->filename);
            } 
            break;
        case 4:
            priv = mPr_GetForeignerP();
            mPr_CopyPrivateInfo(priv, &l_mcd_foreigner_file.file.priv);
            if (in_animal != NULL) {
                bcopy(&l_mcd_foreigner_file.file.remove_animal, in_animal, sizeof(Animal_c));
            }
            mPr_LoadPak_and_SetPrivateInfo2(priv, player_no);
            break;
    }

    if (res == TRUE) {
        static int init_mode_table[] = { 0, 2, 1, 3, 3 };

        ret = mSDI_StartDataInit(game, player_no, init_mode_table[start_cond]);
        l_mcd_keep_startCond = start_cond;
        mgr->copy_protect = Common_Get(copy_protect);

        switch (start_cond) {
            case 0:
            case 2:
                fileInfo->proc = 10;
                mgr->chan = mCD_SLOT_A;
                mgr->cards[mCD_SLOT_A].game_result = mCD_TRANS_ERR_NONE;
                Common_Set(copy_protect, Save_Get(copy_protect));
                ret = mCD_RESULT_SUCCESS;
                break;
            case 1:
                priv = Save_GetPointer(private_data[player_no]);
                if (!mPr_NullCheckPersonalID(&priv->player_ID)) {
                    mCD_SetResetInfo(priv);
                    mCD_SetResetCode(priv);

                    if (Common_Get(player_decoy_flag) == TRUE) {
                        priv->exists = FALSE;
                    }
                    
                    fileInfo->proc++;
                    ret = mCD_RESULT_SUCCESS;
                }

                fileInfo->_14 = 0;
                Save_Set(travel_hard_time, lbRTC_HardTime());
                copy_protect = mCD_get_land_copyProtect();
                Common_Set(copy_protect, copy_protect);
                Save_Set(copy_protect, copy_protect);
                break;
            case 3:
            case 4:
                if (mLd_PlayerManKindCheckNo(player_no) == FALSE) {
                    priv = Now_Private;
                    if (priv != NULL) {
                        mCD_SetResetInfo(priv);
                        mCD_SetResetCode(priv);
                        mRmTp_SetDefaultLightSwitchData(3);
                    }

                    if (start_cond == 3) {
                        fileInfo->_14 = 1;
                    } else {
                        fileInfo->_14 = 0;
                    }
                } else {
                    priv = mCD_GetSaveFilePrivateP();
                    if (priv != NULL) {
                        mCD_SetResetInfo(priv);
                        mCD_SetResetCode(priv);
                    }

                    priv = Now_Private;
                    if (priv != NULL) {
                        mCD_SetResetInfo(priv);
                        mCD_SetResetCode(priv);
                    }

                    mCD_SetCopyProtect(&l_mcd_foreigner_file.file);
                    if (start_cond == 3) {
                        fileInfo->_14 = 2;
                    } else {
                        fileInfo->_14 = 0;
                    }
                }

                Save_Set(travel_hard_time, lbRTC_HardTime());
                copy_protect = mCD_get_land_copyProtect();
                Common_Set(copy_protect, copy_protect);
                Save_Set(copy_protect, copy_protect);
                fileInfo->proc++;
                ret = mCD_RESULT_SUCCESS;
                break;
            default:
                ret = mCD_RESULT_ERROR;
                break;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_InitGameStart_bg_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save = (Save_t*)mgr->workArea;

    if (save != NULL) {
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(save, mgr->workArea_size);
        bcopy(Common_GetPointer(save), save, sizeof(Save_t));
        save->save_check.version = 6;
        mFRm_SetSaveCheckData(&save->save_check);
        save->save_check.checksum = mFRm_GetFlatCheckSum((u16*)save, sizeof(Save), save->save_check.checksum);
        bcopy(save, &l_keepSave, sizeof(Save));
        fileInfo->proc++;
        return mCD_RESULT_SUCCESS;
    }

    return mCD_RESULT_ERROR;
}

static void mCD_set_passport_icon(void* data, int sex, int face) {
    // clang-format off
    static int icon_fileNo[][mPr_FACE_TYPE_NUM] = {
        {RESOURCE_BOY1, RESOURCE_BOY2, RESOURCE_BOY3, RESOURCE_BOY4, RESOURCE_BOY5, RESOURCE_BOY6, RESOURCE_BOY7, RESOURCE_BOY8},
        {RESOURCE_GIRL1, RESOURCE_GIRL2, RESOURCE_GIRL3, RESOURCE_GIRL4, RESOURCE_GIRL5, RESOURCE_GIRL6, RESOURCE_GIRL7, RESOURCE_GIRL8},
    };
    // clang-format on

    if (data != NULL) {
        ForeignerFile_c* passport = (ForeignerFile_c*)data;

        bcopy(l_comment_player_0_str, passport->comment, sizeof(l_comment_0_str));
        mCD_get_passport_comment1(&passport->comment[sizeof(l_comment_0_str)], Now_Private->player_ID.player_name);
        mCD_set_bti_data(passport->banner, RESOURCE_ODEKAKE, 0xC00, 1, 0x200);

        if (sex != mPr_SEX_MALE && sex != mPr_SEX_FEMALE) {
            sex = mPr_SEX_MALE;
        }

        if (!(face >= 0 && face < mPr_FACE_TYPE_NUM)) {
            face = mPr_FACE_TYPE0;
        }

        mCD_set_bti_data(passport->icon, icon_fileNo[sex][face], 0x400, 8, 0x200);
    }
}

static int mCD_InitGameStart_bg_write_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    ForeignerFile_c* passport;
    int ret = mCD_write_common(mgr);

    if (ret == mCD_RESULT_SUCCESS) {
        switch (fileInfo->_14) {
            case 1:
                mgr->loaded_file_type = mCD_FILE_PLAYER;
                mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                mgr->chan = ~mgr->chan & 1;
                fileInfo->proc++;
                break;
            case 2:
                bzero(mgr->workArea, mgr->workArea_size);
                passport = (ForeignerFile_c*)mgr->workArea;
                bcopy(&l_mcd_foreigner_file, &passport->file, sizeof(mCD_foreigner_c));
                mCD_set_passport_icon(mgr->workArea, passport->file.priv.gender, passport->file.priv.face);
                mgr->loaded_file_type = mCD_FILE_PLAYER;
                mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                mgr->chan = ~mgr->chan & 1;
                fileInfo->proc = 8;
                break;
            default:
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
                mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                fileInfo->proc = 9;
                break;
        }
    }

    return ret;
}

static int mCD_InitGameStart_erase_passport(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card;
    Save_t* save;
    int chan = mgr->chan;
    s32 result;
    int ret;

    if (chan != -1) {
        card = &mgr->cards[chan];
        ret = mCD_erase_file_bg(l_mcd_card_private.filename, chan, &card->result);
        if (ret == mCD_RESULT_SUCCESS) {
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
            bzero(mgr->workArea, mgr->workArea_size);
            bcopy(&l_keepSave, mgr->workArea, sizeof(Save));
            card->game_result = mCD_TransErrorCode(card->result);
            mgr->chan = ~mgr->chan & 1;
            fileInfo->proc = 9;
            mgr->_01A0 = 1;
        } else if (ret != mCD_RESULT_BUSY) {
            result = card->result;
            card->game_result = mCD_TransErrorCode(result);
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
            bzero(mgr->workArea, mgr->workArea_size);
            mgr->chan = ~mgr->chan & 1;
            chan = mgr->chan;
            card = &mgr->cards[chan];

            if (mCD_load_file(mgr->workArea, mgr->loaded_file_type, chan, &card->result) == mCD_RESULT_SUCCESS) {
                int checksum = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
                
                save = (Save_t*)mgr->workArea;
                
                if (checksum == 0 && mLd_CheckId(save->land_info.id) == TRUE && mLd_CheckThisLand(save->land_info.name, save->land_info.id) == TRUE) {
                    mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                    fileInfo->proc = 9;
                    ret = mCD_RESULT_SUCCESS;
                } else {
                    mgr->chan = ~mgr->chan & 1;
                }
            } else {
                mgr->chan = ~mgr->chan & 1;
            }

            card->game_result = mCD_TransErrorCode(result);
            fileInfo->game_result = card->game_result;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_InitGameStart_write_passport(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int chan = mgr->chan;
    mCD_file_entry_c* entry;
    mCD_memMgr_card_info_c* card;
    Save_t* save;
    int ret;
    s32 result;

    card = &mgr->cards[chan];
    entry = &l_mcd_file_table[mgr->loaded_file_type];
    ret = mCD_write_comp_bg(mgr->workArea, l_mcd_card_private.filename, mgr->workArea_size, entry->filesize, mCD_get_offset(mgr->loaded_file_type), chan, &card->result);
    
    if (ret == mCD_RESULT_SUCCESS) {
        fileInfo->proc++;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(mgr->workArea, mgr->workArea_size);
        bcopy(&l_keepSave, mgr->workArea, sizeof(Save));
        card->game_result = mCD_TransErrorCode(card->result);
        mgr->chan = ~mgr->chan & 1;
        mgr->_01A0 = 1;
    } else if (ret != mCD_RESULT_BUSY) {
        result = card->result;
        card->game_result = mCD_TransErrorCode(result);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(mgr->workArea, mgr->workArea_size);
        mgr->chan = ~mgr->chan & 1;
        chan = mgr->chan;
        card = &mgr->cards[chan];

        if (mCD_load_file(mgr->workArea, mgr->loaded_file_type, chan, &card->result) == mCD_RESULT_SUCCESS) {
            int checksum = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
            
            save = (Save_t*)mgr->workArea;
            
            if (checksum == 0 && mLd_CheckId(save->land_info.id) == TRUE && mLd_CheckThisLand(save->land_info.name, save->land_info.id) == TRUE) {
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                fileInfo->proc++;
                ret = mCD_RESULT_SUCCESS;
            } else {
                mgr->chan = ~mgr->chan & 1;
            }
        } else {
            mgr->chan = ~mgr->chan & 1;
        }

        card->game_result = mCD_TransErrorCode(result);
        fileInfo->game_result = card->game_result;
    }

    return ret;
}

static int mCD_InitGameStart_bg_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Private_c* priv = Now_Private;
    int ret = mCD_write_common(mgr);

    if (mgr->loaded_file_type == mCD_FILE_SAVE_MAIN) {
        if (ret != mCD_RESULT_BUSY) {
            mCD_memMgr_card_info_c* card;

            mgr->chan = ~mgr->chan & 1;
            card = &mgr->cards[mgr->chan];
            card->game_result = fileInfo->game_result;
            if (mgr->copy_protect != -1) {
                Common_Set(copy_protect, mgr->copy_protect);
            }
        }
    } else {
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
            if (Common_Get(player_decoy_flag) == TRUE && priv != NULL && !mPr_NullCheckPersonalID(&priv->player_ID)) {
                priv->exists = TRUE;
                priv->equipment = EMPTY_NO;
            }
        }
    }

    return ret;
}

extern int mCD_InitGameStart_bg(int player_no, int card_private_idx, int start_cond, s32* mounted_chan) {
    // clang-format off
    static mCD_SAVEHOME_PROC start_proc[] = {
        mCD_InitGameStart_bg_get_area,
        mCD_InitGameStart_bg_get_slot,
        mCD_InitGameStart_bg_check_repair_land,
        mCD_SaveHome_bg_repair_land,
        mCD_InitGameStart_bg_make_data,
        mCD_InitGameStart_bg_set_data,
        mCD_InitGameStart_bg_write_main,
        mCD_InitGameStart_erase_passport,
        mCD_InitGameStart_write_passport,
        mCD_InitGameStart_bg_write_bk,
    };
    // clang-format on

    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &l_memMgr.init_game_start_info;
    mCD_memMgr_card_info_c* card;
    u8 proc = fileInfo->proc;
    int res;
    int ret = mCD_TRANS_ERR_BUSY;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 10) {
            fileInfo->_04 = player_no;
            fileInfo->fileNo = card_private_idx;
            fileInfo->chan = start_cond;
            res = (*start_proc[proc])(mgr, fileInfo);
            
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 10) {
                    *mounted_chan = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                if (mgr->_01A0 == 1) {
                    *mounted_chan = mgr->chan;
                    mgr->copy_protect = -1;
                    ret = mCD_TRANS_ERR_NONE;
                } else if (mgr->chan == mCD_SLOT_A || mgr->chan == mCD_SLOT_B) {
                    *mounted_chan = mgr->chan;
                    card = &mgr->cards[mgr->chan];
                    ret = card->game_result;
                    if (ret == mCD_TRANS_ERR_NONE) {
                        ret = mCD_TRANS_ERR_IOERROR;
                    }

                    bzero(Common_Get(npclist), sizeof(Common_Get(npclist)));
                    bzero(Common_Get(island_npclist), sizeof(Common_Get(island_npclist)));
                    bzero(Common_Get(npc_schedule), sizeof(Common_Get(npc_schedule)));
                } else {
                    ret = mCD_TRANS_ERR_IOERROR;
                }

                if (mgr->copy_protect != -1 && fileInfo->proc <= 8) {
                    Common_Set(copy_protect, mgr->copy_protect);
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 10)) {
                if (fileInfo->_10 == 2) {
                    mCD_ClearMemMgr_com2(mgr);
                    mCD_load_famicom_file();
                } else if (mgr->_0188 >= 112) {
                    sAdo_SysLevStop(NA_SE_47);
                    mCD_ClearMemMgr_com2(mgr);
                    if (res == mCD_RESULT_SUCCESS) {
                        mCD_load_famicom_file();
                    }
                } else {
                    mgr->_0190 = ret;
                    mgr->_018C = 1;
                    mgr->_0194 = *mounted_chan;
                    ret = mCD_TRANS_ERR_BUSY;
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else if (mgr->_0188 >= 112) {
        ret = mgr->_0190;
        *mounted_chan = mgr->_0194;
        sAdo_SysLevStop(NA_SE_47);
        mCD_ClearMemMgr_com2(mgr);
        if (ret == mCD_TRANS_ERR_NONE) {
            mCD_load_famicom_file();
        }
    }

    ret = mCD_GameStart_ChangeErrCode(ret);
    if (ret != mCD_TRANS_ERR_BUSY) {
        SoftResetEnable = TRUE;
    }

    return ret;
}

static int mCD_SaveHome_bg_write_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_write_common(mgr);

    if (ret == mCD_RESULT_SUCCESS) {
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        fileInfo->proc++;
    }

    return ret;
}

static int mCD_SaveErasePlayer_bg_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_write_common(mgr);

    if (ret == mCD_RESULT_SUCCESS) {
        fileInfo->proc++;
    }

    return ret;
}

extern int mCD_SaveErasePlayer_bg(int* mounted_chan) {
    // clang-format off
    static mCD_SAVEHOME_PROC start_proc[] = {
        mCD_EraseLand_bg_get_area,
        mCD_EraseLand_bg_get_slot,
        mCD_InitGameStart_bg_set_data,
        mCD_SaveHome_bg_write_main,
        mCD_SaveErasePlayer_bg_write_bk,
    };
    // clang-format on

    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &l_memMgr.init_game_start_info;
    mCD_memMgr_card_info_c* card;
    u8 proc = fileInfo->proc;
    int res;
    int ret = mCD_TRANS_ERR_BUSY;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 5) {
            res = (*start_proc[proc])(mgr, fileInfo);
            
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 5) {
                    *mounted_chan = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                if (mgr->chan == mCD_SLOT_A || mgr->chan == mCD_SLOT_B) {
                    *mounted_chan = mgr->chan;
                    card = &mgr->cards[mgr->chan];
                    ret = card->game_result;
                } else {
                    ret = mCD_TRANS_ERR_NOCARD;
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 5)) {
                if (mgr->_0188 >= 112) {
                    sAdo_SysLevStop(NA_SE_53);
                    mCD_ClearMemMgr_com2(mgr);
                } else {
                    mgr->_0190 = ret;
                    mgr->_018C = 1;
                    mgr->_0194 = *mounted_chan;
                    ret = mCD_TRANS_ERR_BUSY;
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_IOERROR;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else if (mgr->_0188 >= 112) {
        ret = mgr->_0190;
        *mounted_chan = mgr->_0194;
        mCD_ClearMemMgr_com2(mgr);
        sAdo_SysLevStop(NA_SE_53);
    }

    ret = mCD_GameStart_ChangeErrCode(ret);
    return ret;
}

extern int mCD_GetPlayerNum(void) {
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_cardPrivate_c* card_priv = l_mcd_card_private_table;
    s32 chan;
    mCD_memMgr_card_info_c* card;
    CARDStat* stat;
    ForeignerFile_c* foreigner;
    Private_c* priv;
    CARDFileInfo cFileInfo;
    int player_num = -1;
    int count = 0;
    int i;

    mCD_ClearMemMgr_com2(mgr);
    mgr->workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);
    if (mgr->workArea != NULL && mCD_get_this_land_slot_no(mgr) == mCD_RESULT_SUCCESS && mgr->chan != -1) {
        mCD_ClearCardPrivateTable_com(card_priv, ARRAY_COUNT(l_mcd_card_private_table));

        chan = ~mgr->chan & 1;
        card = &mgr->cards[chan];
        stat = &card->stat;
        card->workArea = mCD_malloc_32(CARD_WORKAREA_SIZE);
        if (card->workArea != NULL && mCD_check_card(&card->result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
            card->result = CARDMount(chan, card->workArea, NULL);
            
            if (card->result == CARD_RESULT_READY || card->result == CARD_RESULT_BROKEN) {
                card->result = CARDCheck(chan);

                if (card->result == CARD_RESULT_READY) {
                    for (i = 0; i < CARD_MAX_FILE; i++) {
                        bzero(mgr->workArea, CARD_WORKAREA_SIZE);
                        card->result = CARDGetStatus(chan, i, stat);
                        if (card->result == CARD_RESULT_READY && mCD_CheckPassportFileStatus(stat) == TRUE) {
                            card->result = CARDOpen(chan, stat->fileName, &cFileInfo);
                            if (card->result == CARD_RESULT_READY) {
                                card->result = CARDRead(&cFileInfo, mgr->workArea, sizeof(ForeignerFile_c), 0);
                                
                                if (card->result == CARD_RESULT_READY) {
                                    u16 checksum;
                                    
                                    foreigner = (ForeignerFile_c*)mgr->workArea;
                                    checksum = mFRm_ReturnCheckSum((u16*)&foreigner->file, sizeof(foreigner->file));
                                    priv = &foreigner->file.priv;
                                    if (checksum == 0 && !mPr_NullCheckPersonalID(&priv->player_ID)) {
                                        mCD_SetCardPrivateTable(card_priv, &foreigner->file.priv.player_ID, stat->fileName);
                                        count++;
                                        card_priv++;
                                        
                                        if (count >= (u32)ARRAY_COUNT(l_mcd_card_private_table)) {
                                            CARDClose(&cFileInfo);
                                            break;
                                        }
                                    }
                                }

                                CARDClose(&cFileInfo);
                            }
                        }
                    }
                }

                CARDUnmount(chan);
            } else if (card->result == CARD_RESULT_ENCODING) {
                CARDUnmount(chan);
            }
        }

        player_num = count;
    }

    mCD_ClearMemMgr_com2(mgr);
    return player_num;
}

extern int mCD_GetCardPrivateNameCopy(u8* dst, int idx) {
    int ret = FALSE;

    if (dst != NULL && idx >= 0 && idx < ARRAY_SIZE(l_mcd_card_private_table, mCD_cardPrivate_c)) {
        bcopy(l_mcd_card_private_table[idx].pid.player_name, dst, sizeof(l_mcd_card_private_table[idx].pid.player_name));
        ret = TRUE;
    }

    return ret;
}

extern int mCD_CheckCardPlayerNative(int idx) {
    mCD_cardPrivate_c* card_priv;
    Private_c* priv = Save_Get(private_data);
    int ret = -1;
    int i;

    if (idx >= 0 && idx < ARRAY_SIZE(l_mcd_card_private_table, mCD_cardPrivate_c)) {
        card_priv = &l_mcd_card_private_table[idx];
        if (!mPr_NullCheckPersonalID(&card_priv->pid)) {
            for (i = 0; i < PLAYER_NUM; i++) {
                if (mPr_CheckCmpPersonalID(&card_priv->pid, &priv->player_ID) == TRUE) {
                    ret = i;
                    break;
                }

                priv++;
            }

            if (i == PLAYER_NUM) {
                ret = mPr_FOREIGNER;
            }
        }
    }

    return ret;
}

extern int mCD_GetThisLandSlotNo(void) {
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    int ret = -1;

    if (mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 2) == mCD_RESULT_SUCCESS) {
        if (mCD_get_this_land_slot_no(mgr) == mCD_RESULT_SUCCESS) {
            ret = mgr->chan;
        }
        mCD_ClearMemMgr_com2(mgr);
    }

    return ret;
}

extern int mCD_GetSaveHomeSlotNo(void) {
    int state;
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    int ret = -1;

    if (Save_Get(save_exist) == FALSE) {
        mCD_ClearMemMgr_com2(mgr);

        if (mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 2) == mCD_RESULT_SUCCESS) {
            if (mgr->cards[mCD_SLOT_A].workArea != NULL && mgr->cards[mCD_SLOT_B].workArea != NULL && mgr->workArea != NULL) {
                state = mCD_RESULT_BUSY;

                if (mCD_CheckInitProtectCode(&l_keep_noLandCode) == FALSE && mCD_CheckProtectCode(l_keep_noLandCode.code) == TRUE) {
                    while (state == mCD_RESULT_BUSY) {
                        state = mCD_GetNoLandSlot_bg(mgr);
                    }

                    if (state == mCD_RESULT_SUCCESS) {
                        ret = mgr->chan;
                    }
                } else {
                    while (state == mCD_RESULT_BUSY) {
                        state = mCD_GetSpaceSlot_bg2(mgr, mCD_LAND_SAVE_SIZE);
                    }

                    if (state == mCD_RESULT_SUCCESS) {
                        ret = mgr->chan;
                    }
                }
            }
        }

        mCD_ClearMemMgr_com2(mgr);
    } else {
        ret = mCD_GetThisLandSlotNo();
    }

    return ret;
}

static int mCD_GetLandSlotNo_code_com(mLd_land_info_c* land_info, u16 land_id, PersonalID_c* pid, int* player_no, s32* slot_results) {
    int ret = mCD_RESULT_ERROR;
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &l_memMgr.save_home_info;
    int res;
    s32 result;
    Private_c* priv;
    Save_t* save;
    mLd_land_info_c* save_land_info;
    s32 i;
    int j;
    int k;

    if (player_no != NULL) {
        *player_no = -1;
    }

    if (slot_results != NULL) {
        slot_results[mCD_SLOT_A] = CARD_RESULT_NOCARD;
        slot_results[mCD_SLOT_B] = CARD_RESULT_NOCARD;
    }

    res = mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 2);
    save = (Save_t*)mgr->workArea;
    if (res == mCD_RESULT_SUCCESS) {
        for (i = 0; i < mCD_SLOT_NUM; i++) {
            result = CARD_RESULT_NOCARD;

            if (mCD_check_sector_size(mCD_MEMCARD_SECTORSIZE, i) == FALSE) {
                if (slot_results != NULL) {
                    slot_results[i] = CARD_RESULT_WRONGDEVICE;
                }
            } else {
                for (j = 0; j < 2; j++) {
                    mgr->loaded_file_type = mCD_FILE_SAVE_MAIN + j;
                    mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
                    bzero(save, mgr->workArea_size);
                    res = mCD_load_file(save, mgr->loaded_file_type, i, &result);
                    
                    if (slot_results != NULL) {
                        slot_results[i] = result;
                    }

                    if (res == mCD_RESULT_SUCCESS) {
                        save_land_info = &save->land_info;
                        if (mFRm_CheckSaveData_common(&save->save_check, save_land_info->id) && mLd_CheckCmpLand(save_land_info->name, save_land_info->id, land_info->name, land_id) == TRUE) {
                            if (player_no != NULL) {
                                priv = save->private_data;
                                for (k = 0; k < PLAYER_NUM; k++) {
                                    if (mPr_CheckCmpPersonalID(pid, &priv->player_ID) == TRUE) {
                                        *player_no = k;
                                        break;
                                    }

                                    priv++;
                                }
                            }

                            ret = i;
                            break;
                        }
                    }
                }
            }

            if (ret != -1) {
                break;
            }
        }
    }

    mCD_ClearMemMgr_com2(mgr);
    return ret;
}

extern int mCD_GetThisLandSlotNo_code(int* player_no, s32* slot_card_results) {
    mLd_land_info_c* info = Save_GetPointer(land_info);
    int ret = -1;

    if (player_no != NULL) {
        *player_no = -1;
    }

    if (slot_card_results != NULL) {
        slot_card_results[mCD_SLOT_A] = CARD_RESULT_NOCARD;
        slot_card_results[mCD_SLOT_B] = CARD_RESULT_NOCARD;
    }

    if (Now_Private != NULL) {
        ret = mCD_GetLandSlotNo_code_com(info, info->id, &Now_Private->player_ID, player_no, slot_card_results);
    }

    return ret;
}

static int mCD_CheckStation_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 2);

    if (ret != mCD_RESULT_BUSY) {
        fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
    }

    return ret;
}

static int mCD_CheckStation_check_this_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 chan;
    mCD_memMgr_card_info_c* card;

    mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
    mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);

    if (mCD_get_this_land_slot_no_nes(mgr) == mCD_RESULT_SUCCESS) {
        chan = mgr->chan;
        if (chan != -1) {
            Save_t* save = (Save_t*)mgr->workArea;

            if (mCD_check_copyProtect(save, chan) == TRUE) {
                mgr->chan = ~chan & 1;
                fileInfo->proc++;
                return mCD_RESULT_SUCCESS;
            } else {
                fileInfo->_04 = mCD_TRANS_ERR_WRONG_LAND;
                return mCD_RESULT_ERROR;
            }
        }
    }

    chan = mgr->chan;
    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
    if (chan != -1) {
        s32 result;

        card = &mgr->cards[chan];
        result = card->game_result;
        if (result == mCD_TRANS_ERR_WRONGDEVICE || result == mCD_TRANS_ERR_NOT_MEMCARD) {
            fileInfo->_04 = result;
        }
    }

    return mCD_RESULT_ERROR;
}

static int mCD_CheckStation_check_next_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save;
    int i;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int ret = mCD_RESULT_BUSY; // this initialization is *necessary* to shove mr r29, r4 into the correct location
    int res;

    chan = mgr->chan;
    if (mgr->workArea != NULL && chan != -1) {
        bzero(mgr->workArea, mgr->workArea_size);
        
        card = &mgr->cards[chan];
        card->_8C = 0;
        for (i = 0; i < 2; i++) {
            if (mCD_load_file(mgr->workArea, mCD_FILE_SAVE_MAIN + i, chan, &card->result) == mCD_RESULT_SUCCESS) {
                res = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
                save = (Save_t*)mgr->workArea;
                if (res == 0) {
                    if (mLd_CheckId(save->land_info.id) == TRUE) {
                        if (mLd_CheckThisLand(save->land_info.name, save->land_info.id) == FALSE) {
                            if (l_mcd_keep_startCond == 3 && mLd_PlayerManKindCheck()) {
                                fileInfo->_04 = mCD_TRANS_ERR_TRAVEL_DATA_MISSING;
                                ret = mCD_RESULT_ERROR;
                                break;
                            } else {
                                fileInfo->_04 = mCD_TRANS_ERR_NONE_NEXTLAND;
                                fileInfo->proc = 5;
                                ret = mCD_RESULT_SUCCESS;
                                break;
                            }
                        } else {
                            fileInfo->_04 = mCD_TRANS_ERR_NO_SPACE; // ?? shouldn't this be same land?
                            ret = mCD_RESULT_ERROR;
                        }
                    } else {
                        fileInfo->_04 = mCD_TRANS_ERR_CORRUPT;
                        ret = mCD_RESULT_ERROR;
                    }
                } else {
                    fileInfo->_04 = mCD_TRANS_ERR_CORRUPT;
                    ret = mCD_RESULT_ERROR;
                }
            } else {
                card->_8C++;
                ret = mCD_RESULT_ERROR;
            }
        }

        if (card->_8C == 2) {
            if (mCD_check_sector_size(mCD_MEMCARD_SECTORSIZE, chan) == FALSE) {
                fileInfo->_04 = mCD_TRANS_ERR_NOT_MEMCARD;
                ret = mCD_RESULT_ERROR;
            } else {
                switch (card->result) {
                    case CARD_RESULT_WRONGDEVICE:
                        fileInfo->_04 = mCD_TRANS_ERR_WRONGDEVICE;
                        ret = mCD_RESULT_ERROR;
                        break;
                    case CARD_RESULT_NOCARD:
                        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                        ret = mCD_RESULT_ERROR;
                        break;
                    case CARD_RESULT_IOERROR:
                        fileInfo->_04 = mCD_TRANS_ERR_DAMAGED;
                        ret = mCD_RESULT_ERROR;
                        break;
                    case CARD_RESULT_BROKEN:
                    case CARD_RESULT_ENCODING:
                        fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                        ret = mCD_RESULT_ERROR;
                        break;
                    default:
                        if (mLd_PlayerManKindCheck() && l_mcd_keep_startCond != 4) {
                            fileInfo->proc++;
                        } else {
                            fileInfo->proc = 4;
                        }
                        ret = mCD_RESULT_SUCCESS;
                        break;
                }
            }
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_CheckStation_check_foreigner(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_memMgr_card_info_c* card;
    char* filename;
    s32 chan;
    int ret = mCD_RESULT_BUSY;
    int res;
    ForeignerFile_c* foreignerFile;
    int ofs;

    chan = mgr->chan;
    if (mgr->workArea != NULL && chan != -1) {
        card = &mgr->cards[chan];
        bzero(mgr->workArea, mgr->workArea_size);
        filename = l_mcd_card_private.filename;
        mgr->loaded_file_type = mCD_FILE_PLAYER;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        ofs = mCD_get_offset(mgr->loaded_file_type);
        res = mCD_read_fg(mgr->workArea, filename, mgr->workArea_size, ofs, chan, &card->result);
        foreignerFile = (ForeignerFile_c*)mgr->workArea;
        if (res == mCD_RESULT_SUCCESS && l_mcd_copy_protect == foreignerFile->file.copy_protect) {
            bcopy(filename, mgr->filename, sizeof(mgr->filename));
            fileInfo->_04 = mCD_TRANS_ERR_NONE;
            fileInfo->proc = 5;
            ret = mCD_RESULT_SUCCESS;
        } else {
            if (card->result == CARD_RESULT_WRONGDEVICE) {
                fileInfo->_04 = mCD_TRANS_ERR_WRONGDEVICE;
            } else {
                fileInfo->_04 = mCD_TRANS_ERR_TRAVEL_DATA_MISSING;
            }

            ret = mCD_RESULT_ERROR;
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

#ifdef MUST_MATCH
static inline int mCD_check_card_inline_hack(s32* result_p, s32 req_sector_size, int chan) {
    return mCD_check_card(result_p, req_sector_size, chan);
}
#endif

// @non-matching - equivalent (missing mr instruction)
static int mCD_CheckStation_check_passport(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Private_c* priv;
    Private_c* passport_priv;
    ForeignerFile_c* passport;
    CARDFileInfo cardFileInfo;
    s32 unusedFiles = 0;
    int res;
    int i;
    s32 chan;
    mCD_memMgr_card_info_c* card;
    int ret = mCD_RESULT_BUSY;

    chan = mgr->chan;
    if (mgr->workArea != NULL && chan != -1 && Now_Private != NULL) {
        priv = Now_Private;
        card = &mgr->cards[chan];
        // issue - changing mCD_check_card's `chan` parameter to be s32 fixes this func but breaks several others
#ifdef MUST_MATCH
        if (card->workArea != NULL && mCD_check_card_inline_hack(&card->result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
#else
        if (card->workArea != NULL && mCD_check_card(&card->result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
#endif
            card->result = CARDMount(chan, card->workArea, NULL);
            if (card->result == CARD_RESULT_READY || card->result == CARD_RESULT_BROKEN) {
                card->result = CARDCheck(chan);
                if (card->result == CARD_RESULT_READY) {
                    for (i = 0; i < CARD_MAX_FILE; i++) {
                        bzero(mgr->workArea, sizeof(ForeignerFile_c));
                        card->result = CARDGetStatus((s32)chan, i, &card->stat);
                        if (card->result == CARD_RESULT_READY && mCD_CheckPassportFileStatus(&card->stat) == TRUE) {
                            card->result = CARDOpen((s32)chan, card->stat.fileName, &cardFileInfo);
                            if (card->result == CARD_RESULT_READY) {
                                card->result = CARDRead(&cardFileInfo, mgr->workArea, sizeof(ForeignerFile_c), 0);
                                if (card->result == CARD_RESULT_READY) {
                                    passport = (ForeignerFile_c*)mgr->workArea;
                                    res = mFRm_ReturnCheckSum((u16*)&passport->file, sizeof(passport->file));
                                    passport_priv = &passport->file.priv;

                                    if (res == 0) {
                                        if (mPr_CheckCmpPersonalID(&priv->player_ID, &passport_priv->player_ID) == TRUE) {
                                            bcopy(card->stat.fileName, mgr->filename, sizeof(mgr->filename));
                                            fileInfo->_04 = mCD_TRANS_ERR_TRAVEL_DATA_EXISTS;
                                            fileInfo->proc = 5;
                                            CARDClose(&cardFileInfo);
                                            ret = mCD_RESULT_SUCCESS;
                                            break;
                                        }
                                    }
                                }

                                CARDClose(&cardFileInfo);
                            }
                        }
                    }

                    if (ret == mCD_RESULT_BUSY) {
                        card->result = CARDFreeBlocks(chan, &card->freeBytes, &unusedFiles);
                        if (card->result == CARD_RESULT_READY) {
                            if (card->freeBytes >= l_mcd_file_table[mCD_FILE_PLAYER].filesize) {
                                if (mCD_check_Land_exist_com(chan) == TRUE) {
                                    fileInfo->_04 = mCD_TRANS_ERR_LAND_EXIST;
                                    ret = mCD_RESULT_ERROR;
                                } else if (mCD_get_file_num_com(chan) >= CARD_MAX_FILE) {
                                    fileInfo->_04 = mCD_TRANS_ERR_NO_FILES;
                                    ret = mCD_RESULT_ERROR;
                                } else {
                                    fileInfo->_04 = mCD_TRANS_ERR_NONE;
                                    fileInfo->proc = 5;
                                    ret = mCD_RESULT_SUCCESS;
                                }
                            } else {
                                fileInfo->_04 = mCD_TRANS_ERR_NO_SPACE;
                                ret = mCD_RESULT_ERROR;
                            }
                        } else {
                            fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                            ret = mCD_RESULT_ERROR;
                        }
                    }
                } else {
                    fileInfo->_04 = mCD_TRANS_ERR_DAMAGED;
                    ret = mCD_RESULT_ERROR;
                }

                CARDUnmount(chan);
            } else {
                if (card->result == CARD_RESULT_ENCODING) {
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    CARDUnmount(chan);
                } else {
                    fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                }

                ret = mCD_RESULT_ERROR;
            }
        } else {
            if (card->result == CARD_RESULT_WRONGDEVICE) {
                fileInfo->_04 = mCD_TRANS_ERR_WRONGDEVICE;
            } else {
                fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
            }

            ret = mCD_RESULT_ERROR;
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

typedef int (*mCD_CHECKSTATION_PROC)(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo);

extern int mCD_CheckStation_bg(s32 *chan) {
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->init_game_start_info;
    int res;
    u8 proc;
    int ret = mCD_TRANS_ERR_BUSY;

    proc = fileInfo->proc;
    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
    if (proc < 5) {
        // clang-format off
        static mCD_CHECKSTATION_PROC check_proc[] = {
            mCD_CheckStation_get_area,
            mCD_CheckStation_check_this_land,
            mCD_CheckStation_check_next_land,
            mCD_CheckStation_check_foreigner,
            mCD_CheckStation_check_passport,
        };
        // clang-format on

        res = (*check_proc[proc])(mgr, fileInfo);
        if (res == mCD_RESULT_SUCCESS) {
            if (fileInfo->proc == 5) {
                *chan = mgr->chan;
                ret = fileInfo->_04;
                mCD_ClearMemMgr_com2(mgr);
            }
        } else if (res != mCD_RESULT_BUSY) {
            *chan = mgr->chan;
            ret = fileInfo->_04;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else {
        *chan = mgr->chan;
        ret = mCD_TRANS_ERR_NOCARD;
        mCD_ClearMemMgr_com2(mgr);
    }

    return ret;
}

static int mCD_SaveStation_NextLand_get_area(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save;
    int game_result;
    mCD_memMgr_card_info_c* card;
    int ret;

    ret = mCD_bg_get_area_common(mgr, fileInfo, mCD_FILE_SAVE_MAIN, 0);
    if (ret == mCD_RESULT_SUCCESS) {
        if (mCD_get_this_land_slot_no_nes(mgr) == mCD_RESULT_SUCCESS) {
            save = (Save_t*)mgr->workArea;

            if (mCD_check_copyProtect(save, mgr->chan) == TRUE) {
                SoftResetEnable = FALSE;
            } else {
                fileInfo->_04 = mCD_TRANS_ERR_WRONG_LAND;
                ret = mCD_RESULT_ERROR;
            }
        } else {
            fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
            if (mgr->chan != -1) {
                card = &mgr->cards[mgr->chan];
                game_result = card->game_result;
                if (game_result == mCD_TRANS_ERR_WRONGDEVICE || game_result == mCD_TRANS_ERR_NOT_MEMCARD) {
                    fileInfo->_04 = game_result;
                }
            }

            ret = mCD_RESULT_ERROR;
        }
    } else if (ret != mCD_RESULT_BUSY) {
        fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveStation_NextLand_check_repair_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_RESULT_SUCCESS;

    if (mCD_check_broken_land(mgr) == TRUE) {
        if (mCD_repair_load_land(mgr) == TRUE) {
            fileInfo->proc++;
        } else {
            fileInfo->proc = 3;
            mgr->chan = ~mgr->chan & 1;
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        }
    } else {
        fileInfo->proc = 3;
        mgr->chan = ~mgr->chan & 1;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
    }

    return ret;
}

static int mCD_SaveStatoin_NextLand_repair_land(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_RESULT_BUSY;

    if (mCD_repair_land(mgr)) {
        mgr->chan = ~mgr->chan & 1;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    }

    return ret;
}

static int mCD_SaveStation_NextLand_get_next_land_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int i;
    int ret = mCD_RESULT_BUSY; // this initialization is *necessary* to shove mr r29, r4 into the correct location
    int res;

    chan = mgr->chan;
    if (mgr->workArea != NULL && chan != -1) {
        bzero(mgr->workArea, mgr->workArea_size);
        
        card = &mgr->cards[chan];
        card->_8C = 0;
        for (i = 0; i < 2; i++) {
            if (mCD_load_file(mgr->workArea, mCD_FILE_SAVE_MAIN + i, chan, &card->result) == mCD_RESULT_SUCCESS) {
                res = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
                save = (Save_t*)mgr->workArea;
                if (res == 0) {
                    if (mLd_CheckId(save->land_info.id) == TRUE) {
                        if (mLd_CheckThisLand(save->land_info.name, save->land_info.id) == FALSE) {
                            if (l_mcd_keep_startCond == 3 && mLd_PlayerManKindCheck()) {
                                fileInfo->_04 = mCD_TRANS_ERR_TRAVEL_DATA_MISSING;
                                ret = mCD_RESULT_ERROR;
                                break;
                            } else {
                                fileInfo->proc++;
                                bcopy(save, &l_keepSave, sizeof(Save));
                                l_keepSave_set = TRUE;
                                ret = mCD_RESULT_SUCCESS;
                                break;
                            }
                        } else {
                            fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                            ret = mCD_RESULT_ERROR;
                        }
                    } else {
                        fileInfo->_04 = mCD_TRANS_ERR_CORRUPT;
                        ret = mCD_RESULT_ERROR;
                    }
                } else {
                    fileInfo->_04 = mCD_TRANS_ERR_CORRUPT;
                    ret = mCD_RESULT_ERROR;
                }
            } else {
                card->_8C++;
                ret = mCD_RESULT_ERROR;
            }
        }

        if (card->_8C == 2) {
            switch (card->result) {
                case CARD_RESULT_WRONGDEVICE:
                    fileInfo->_04 = mCD_TRANS_ERR_WRONGDEVICE;
                    break;
                case CARD_RESULT_NOCARD:
                    fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                    break;
                case CARD_RESULT_IOERROR:
                    fileInfo->_04 = mCD_TRANS_ERR_DAMAGED;
                    break;
                case CARD_RESULT_BROKEN:
                case CARD_RESULT_ENCODING:
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    break;
                default:
                    if (l_mcd_keep_startCond == 3) {
                        fileInfo->_04 = mCD_TRANS_ERR_TRAVEL_DATA_MISSING;
                    } else {
                        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                    }
                    break;
            }
            ret = mCD_RESULT_ERROR;
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static union {
    mCD_keep_mail_c mail ATTRIBUTE_ALIGN(32);
    u8 buf[mCD_ALIGN_SECTORSIZE(sizeof(mCD_keep_mail_c))];
} l_keepMail ATTRIBUTE_ALIGN(32);

static union {
    mCD_keep_original_c l_keepOriginal ATTRIBUTE_ALIGN(32);
    u8 buf[mCD_ALIGN_SECTORSIZE(sizeof(mCD_keep_original_c))];
} l_keepOriginal ATTRIBUTE_ALIGN(32);

static union {
    mCD_keep_diary_c l_keepDiary ATTRIBUTE_ALIGN(32);
    u8 buf[mCD_ALIGN_SECTORSIZE(sizeof(mCD_keep_diary_c))];
} l_keepDiary ATTRIBUTE_ALIGN(32);

static int mCD_SaveStation_NextLand_load_others(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    u8* buf = (u8*)mgr->workArea;
    mCD_memMgr_card_info_c* card;
    s32 chan = mgr->chan;
    mCD_file_entry_c* entry;
    int ret = mCD_RESULT_SUCCESS;

    mCD_set_init_mail_data(&l_keepMail);
    mCD_set_init_original_data(&l_keepOriginal);
    mCD_set_init_diary_data(&l_keepDiary);

    if (mgr->workArea != NULL && chan != -1) {
        bzero(buf, sizeof(OthersSave_u));
        card = &mgr->cards[chan];
        entry = &l_mcd_file_table[mCD_FILE_SAVE_MISC];
        if (mCD_read_fg(buf, entry->filename, entry->entrysize, 0, chan, &card->result) == mCD_RESULT_SUCCESS) {
            buf += offsetof(OthersSave_c, keep_mail);

            if (mFRm_ReturnCheckSum((u16*)buf, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL]) == 0) {
                bcopy(buf, &l_keepMail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL]);
            }
            buf += l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL];

            if (mFRm_ReturnCheckSum((u16*)buf, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL]) == 0) {
                // @BUG - this should be &l_keepOriginal
#ifndef BUGFIXES
                bcopy(buf, &l_keepDiary, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL]);
#else
                bcopy(buf, &l_keepOriginal, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL]);
#endif
            }
            buf += l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL];

            if (mFRm_ReturnCheckSum((u16*)buf, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY]) == 0) {
                bcopy(buf, &l_keepDiary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY]);
            }
        }
    }

    mgr->chan = ~chan & 1;
    fileInfo->proc++;
    return ret;
}

static void mCD_CopyKeep(
    mActor_name_t* pockets_p, //
    u8* lotto_ticket_expiry_p, //
    u8* lotto_ticket_mail_storage_p, //
    u32* item_cond_p, //
    u32* wallet_p, //
    mQst_delivery_c* delivery_p, //
    mQst_errand_c* errand_p, //
    Mail_c* mail_p, //
    mPr_catalog_order_c* catalog_orders_p, //
    Anmremail_c* remail_p, //
    mPr_animal_memory_c* animal_memory_p, //
    mActor_name_t* pockets, //
    u8 lotto_ticket_expiry, //
    u8 lotto_ticket_mail_storage, //
    u32 item_cond, //
    u32 wallet, //
    mQst_delivery_c* delivery, //
    mQst_errand_c* errand, //
    Mail_c* mail, //
    mPr_catalog_order_c* catalog_orders, //
    Anmremail_c* remail, //
    mPr_animal_memory_c* animal_memory //
) {
    int i;

    bcopy(pockets, pockets_p, membersize(Private_c, inventory.pockets));
    *item_cond_p = item_cond;
    *lotto_ticket_expiry_p = lotto_ticket_expiry;
    *lotto_ticket_mail_storage_p = lotto_ticket_mail_storage;
    *wallet_p = wallet;

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        mQst_CopyDelivery(delivery_p, delivery);
        delivery_p++;
        delivery++;
    }

    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        mQst_CopyErrand(errand_p, errand);
        errand_p++;
        errand++;
    }

    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        mMl_copy_mail(mail_p, mail);
        mail_p++;
        mail++;
    }

    for (i = 0; i < mPr_CATALOG_ORDER_NUM; i++) {
        catalog_orders_p->item = catalog_orders->item;
        catalog_orders_p->shop_level = catalog_orders->shop_level;
        catalog_orders_p++;
        catalog_orders++;
    }

    bcopy(remail, remail_p, sizeof(Anmremail_c));
    bcopy(animal_memory, animal_memory_p, sizeof(mPr_animal_memory_c));
}

static void mCD_ClearPrivateItem(Private_c* priv, mCD_PrivateItem_c* privItem) {
    if (privItem != NULL) {
        bzero(privItem, sizeof(mCD_PrivateItem_c));
        mCD_CopyKeep(
            // dst
            privItem->items,
            &privItem->ticket_expiry_month,
            &privItem->ticket_storage,
            &privItem->item_cond,
            &privItem->wallet,
            privItem->delivery,
            privItem->errand,
            privItem->mail,
            privItem->catalog_order,
            &privItem->remail,
            &privItem->animal_memory,
            // src
            priv->inventory.pockets,
            priv->inventory.lotto_ticket_expiry_month,
            priv->inventory.lotto_ticket_mail_storage,
            priv->inventory.item_conditions,
            priv->inventory.wallet,
            priv->deliveries,
            priv->errands,
            priv->mail,
            priv->catalog_orders,
            &priv->remail,
            &priv->animal_memory
        );

        privItem->_0FF0 = TRUE;
    }

    bzero(priv->inventory.pockets, membersize(Private_c, inventory.pockets));
    priv->inventory.item_conditions = 0;
    priv->inventory.lotto_ticket_expiry_month = 0;
    priv->inventory.lotto_ticket_mail_storage = 0;
    priv->inventory.wallet = 0;
    mQst_ClearDelivery(priv->deliveries, mPr_DELIVERY_QUEST_NUM);
    mQst_ClearErrand(priv->errands, mPr_ERRAND_QUEST_NUM);
    mMl_clear_mail_box(priv->mail, mPr_INVENTORY_MAIL_COUNT);
    bzero(priv->catalog_orders, sizeof(priv->catalog_orders));
    mPr_ClearAnimalMemory(&priv->animal_memory);
    mNpc_ClearRemail(&priv->remail);
}

static void mCD_ReplaceKeep(Private_c* priv, mCD_PrivateItem_c* privItem) {
    if (privItem != NULL && privItem->_0FF0 == TRUE) {
        mCD_CopyKeep(
            // dst
            priv->inventory.pockets,
            &priv->inventory.lotto_ticket_expiry_month,
            &priv->inventory.lotto_ticket_mail_storage,
            &priv->inventory.item_conditions,
            &priv->inventory.wallet,
            priv->deliveries,
            priv->errands,
            priv->mail,
            priv->catalog_orders,
            &priv->remail,
            &priv->animal_memory,
            // src
            privItem->items,
            privItem->ticket_expiry_month,
            privItem->ticket_storage,
            privItem->item_cond,
            privItem->wallet,
            privItem->delivery,
            privItem->errand,
            privItem->mail,
            privItem->catalog_order,
            &privItem->remail,
            &privItem->animal_memory
        );
    }
}

// TODO: probably fakematch
#if VERSION == VER_GAFU01_00
static int mCD_SaveStation_NextLand_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save;
    Private_c* priv;
    mCD_persistent_data_c* persistant = Common_GetPointer(travel_persistent_data);
    int i;
    mActor_name_t* pocket_p;
    Animal_c* in_animal;
    int j;
    u16 copy_protect;
    s32 chan;
    int ret = mCD_RESULT_BUSY;

    chan = mgr->chan;
    save = (Save_t*)mgr->workArea;
    if (save != NULL && chan != -1) {
        priv = Now_Private;
        mCkRh_SavePlayTime(Common_Get(player_no));
        if (priv != NULL) {
            pocket_p = priv->inventory.pockets;
            for (j = 0; j < mPr_POCKETS_SLOT_COUNT; j++, pocket_p++) {
                if (ITEM_IS_WISP(*pocket_p)) {
                    mPr_SetPossessionItem(priv, j, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }
            }
        }

        mCD_ClearResetCode();
        mHm_KeepHouseSize(Common_Get(player_no));
        in_animal = mNpc_GetInAnimalP();
        mNpc_GetRemoveAnimal(in_animal, TRUE);
        mCD_SetForeignerFile(&l_mcd_foreigner_file.file, priv, in_animal);
        if (mLd_PlayerManKindCheckNo(Common_Get(player_no)) == FALSE) {
            priv->exists = FALSE;
            mCD_ClearPrivateItem(priv, &mgr->private_item);
            mgr->_0198 = 1;
        }

        bcopy(Save_GetPointer(land_info), &persistant->land, sizeof(mLd_land_info_c));
        // priv = Save_Get(private_data);
        for (i = 0; i < PLAYER_NUM; i++) {
            mPr_CopyPersonalID(&persistant->pid[i], &Save_Get(private_data[i]).player_ID);
        }

        mAGrw_ClearMoneyStoneShineGround();
        Save_Set(travel_hard_time, lbRTC_HardTime());
        mgr->copy_protect = Common_Get(copy_protect);
        copy_protect = mCD_get_land_copyProtect();
        Common_Set(copy_protect, copy_protect);
        Save_Set(copy_protect, copy_protect);
        bcopy(Common_GetPointer(save), save, sizeof(Save));
        save->save_check.version = 6;
        mFRm_SetSaveCheckData(&save->save_check);
        save->save_check.checksum = mFRm_GetFlatCheckSum((u16*)save, sizeof(Save), save->save_check.checksum);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}
#else
static int mCD_SaveStation_NextLand_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Save_t* save;
    Private_c* priv;
    mCD_persistent_data_c* persistant = Common_GetPointer(travel_persistent_data);
    mActor_name_t* pocket_p;
    Animal_c* in_animal;
    int i;
    u16 copy_protect;
    s32 chan;
    int ret = mCD_RESULT_BUSY;

    chan = mgr->chan;
    save = (Save_t*)mgr->workArea;
    if (save != NULL && chan != -1) {
        priv = Now_Private;
        mCkRh_SavePlayTime(Common_Get(player_no));
        if (priv != NULL) {
            pocket_p = priv->inventory.pockets;
            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, pocket_p++) {
                if (ITEM_IS_WISP(*pocket_p)) {
                    mPr_SetPossessionItem(priv, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }
            }
        }

        mCD_ClearResetCode();
        mHm_KeepHouseSize(Common_Get(player_no));
        in_animal = mNpc_GetInAnimalP();
        mNpc_GetRemoveAnimal(in_animal, TRUE);
        mCD_SetForeignerFile(&l_mcd_foreigner_file.file, priv, in_animal);
        if (mLd_PlayerManKindCheckNo(Common_Get(player_no)) == FALSE) {
            priv->exists = FALSE;
            mCD_ClearPrivateItem(priv, &mgr->private_item);
            mgr->_0198 = 1;
        }

        bcopy(Save_GetPointer(land_info), &persistant->land, sizeof(mLd_land_info_c));
        // priv = Save_Get(private_data);
        for (i = 0; i < PLAYER_NUM; i++) {
            mPr_CopyPersonalID(&persistant->pid[i], &Save_Get(private_data[i]).player_ID);
        }

        mAGrw_ClearMoneyStoneShineGround();
        Save_Set(travel_hard_time, lbRTC_HardTime());
        mgr->copy_protect = Common_Get(copy_protect);
        copy_protect = mCD_get_land_copyProtect();
        Common_Set(copy_protect, copy_protect);
        Save_Set(copy_protect, copy_protect);
        bcopy(Common_GetPointer(save), save, sizeof(Save));
        save->save_check.version = 6;
        mFRm_SetSaveCheckData(&save->save_check);
        save->save_check.checksum = mFRm_GetFlatCheckSum((u16*)save, sizeof(Save), save->save_check.checksum);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}
#endif

static int mCD_SaveStation_NextLand_write_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 result;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int ret;

    ret = mCD_write_common(mgr);
    if (ret == mCD_RESULT_SUCCESS) {
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        fileInfo->proc++;
    } else if (ret != mCD_RESULT_BUSY) {
        chan = mgr->chan;
        if (chan != -1) {
            card = &mgr->cards[chan];
            result = card->result;

            switch (result) {
                case CARD_RESULT_BROKEN:
                case CARD_RESULT_ENCODING:
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    break;
                case CARD_RESULT_WRONGDEVICE:
                case CARD_RESULT_NOCARD:
                    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
                    break;
                default:
                    fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                    break;
            }
        } else {
            fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
        }
    }

    return ret;
}

static int mCD_SaveStation_NextLand_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 result;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int ret;

    ret = mCD_write_common(mgr);
    if (ret == mCD_RESULT_SUCCESS) {
        fileInfo->proc++;
    } else if (ret != mCD_RESULT_BUSY) {
        chan = mgr->chan;
        if (chan != -1) {
            card = &mgr->cards[chan];
            result = card->result;

            switch (result) {
                case CARD_RESULT_BROKEN:
                case CARD_RESULT_ENCODING:
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    break;
                case CARD_RESULT_WRONGDEVICE:
                case CARD_RESULT_NOCARD:
                    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
                    break;
                default:
                    fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                    break;
            }
        } else {
            fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
        }
    }

    return ret;
}

static int mCD_SaveStation_NextLand_write_others(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* entry;
    const char* filename;
    s32 result;
    mCD_memMgr_card_info_c* card;
    void* workArea;
    s32 chan;
    int ret = mCD_RESULT_BUSY;

    entry = &l_mcd_file_table[mCD_FILE_SAVE_MAIN];
    filename = entry->filename;

    workArea = mgr->workArea;
    chan = mgr->chan;
    if (mgr->_019C == 1) {
        filename = l_mCD_land_file_name_dummy;
    }

    if (mgr->workArea != NULL && chan != -1) {
        card = &mgr->cards[chan];
        ret = mCD_write_comp_bg(workArea, filename, mgr->workArea_size, mCD_LAND_SAVE_SIZE, 0, chan, &card->result);
        card->game_result = mCD_TransErrorCode(card->result);

        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        } else if (ret != mCD_RESULT_BUSY) {
            ret = mCD_RESULT_ERROR;
        }
    } else {
        ret = mCD_RESULT_ERROR;
    }

    if (ret == mCD_RESULT_SUCCESS) {

    } else if (ret != mCD_RESULT_BUSY) {
        chan = mgr->chan;
        if (chan != -1) {
            card = &mgr->cards[chan];
            result = card->result;

            switch (result) {
                case CARD_RESULT_BROKEN:
                case CARD_RESULT_ENCODING:
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    break;
                case CARD_RESULT_WRONGDEVICE:
                case CARD_RESULT_NOCARD:
                    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
                    break;
                default:
                    fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                    break;
            }
        } else {
            fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
        }
    }

    return ret;
}

typedef int (*mCD_SAVESTATION_NEXTLAND_PROC)(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo);

extern int mCD_SaveStation_NextLand_bg(s32* chan) {
    // clang-format off
    static mCD_SAVESTATION_NEXTLAND_PROC save_proc[] = {
        mCD_SaveStation_NextLand_get_area,
        mCD_SaveStation_NextLand_check_repair_land,
        mCD_SaveStatoin_NextLand_repair_land,
        mCD_SaveStation_NextLand_get_next_land_data,
        mCD_SaveStation_NextLand_load_others,
        mCD_SaveStation_NextLand_set_data,
        mCD_SaveStation_NextLand_write_main,
        mCD_SaveStation_NextLand_write_bk,
        mCD_SaveHome_bg_set_others,
        mCD_SaveStation_NextLand_write_others,
    };
    // clang-format on
    
    mCD_memMgr_card_info_c* cardInfo;
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    int ret = mCD_TRANS_ERR_BUSY;
    u8 proc = (u8)fileInfo->proc;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 10) {
            int res;
            
            res = (*save_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 10) {
                    *chan = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                ret= fileInfo->_04;
                *chan = mgr->chan;
                if (ret == 0) {
                    ret = mCD_TRANS_ERR_IOERROR;
                }

                if (mgr->_0198 == 1 && Now_Private != NULL) {
                    Now_Private->exists = TRUE;
                    mCD_ReplaceKeep(Now_Private, &mgr->private_item);
                }

                if (mgr->copy_protect != -1 && fileInfo->proc < 7) {
                    Common_Set(copy_protect, mgr->copy_protect);
                }

                mCD_ClearKeepLand();
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 10)) {
                if (mgr->_0188 >= 112) {
                    sAdo_SysLevStop(NA_SE_47);
                    mCD_ClearMemMgr_com2(mgr);

                    if (res == mCD_RESULT_SUCCESS && mLd_PlayerManKindCheck() == FALSE) {
                        mCD_create_famicom_file(mgr->chan);
                    }
                } else {

                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    mgr->_0194 = *chan;
                    ret = mCD_TRANS_ERR_BUSY;
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else {
        if (mgr->_0188 >= 112) {
            ret = mgr->_0190;
            *chan = mgr->_0194;
            mCD_ClearMemMgr_com2(mgr);
            if (ret == mCD_TRANS_ERR_NONE && mLd_PlayerManKindCheck() == FALSE) {
                mCD_create_famicom_file(*chan);
            }
            sAdo_SysLevStop(NA_SE_47);
        }
    }

    if (ret != mCD_TRANS_ERR_BUSY) {
        SoftResetEnable = TRUE;
    }
    return ret;
}

static int mCD_SaveStation_Passport_check_slot(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret = mCD_RESULT_BUSY;

    if (mLd_PlayerManKindCheck() && l_mcd_keep_startCond != 4) {
        if (mCD_CheckStation_check_foreigner(mgr, fileInfo) == TRUE && fileInfo->_04 == mCD_TRANS_ERR_NONE) {
            fileInfo->fileNo = 1;
            fileInfo->proc = 4;
            ret = mCD_RESULT_SUCCESS;
        } else {
            ret = mCD_RESULT_ERROR;
        }
    } else {
        if (mCD_CheckStation_check_passport(mgr, fileInfo) == TRUE) {
            if (fileInfo->_04 == mCD_TRANS_ERR_TRAVEL_DATA_EXISTS) {
                fileInfo->fileNo = 1;
            } else {
                fileInfo->fileNo = 0;
            }

            fileInfo->proc = 4;
            ret = mCD_RESULT_SUCCESS;
        } else {
            ret = mCD_RESULT_ERROR;
        }
    }

    return ret;
}

static int mCD_SaveStation_Passport_set_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    Private_c* priv;
    Save_t* save;
    mActor_name_t* pocket_p;
    Animal_c* in_animal;
    mCD_persistent_data_c* persistant = Common_GetPointer(travel_persistent_data);
    u16 copy_protect;
    s32 chan;
    int ret = mCD_RESULT_BUSY;
    int i;

    chan = mgr->chan;
    save = (Save_t*)mgr->workArea;
    if (save != NULL && chan != -1) {
        priv = Now_Private;
        mCkRh_SavePlayTime(Common_Get(player_no));
        if (priv != NULL) {
            pocket_p = priv->inventory.pockets;
            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                if (ITEM_IS_WISP(*pocket_p)) {
                    mPr_SetPossessionItem(priv, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }

                pocket_p++;
            }
        }

        mCD_ClearResetCode();
        mHm_KeepHouseSize(Common_Get(player_no));
        in_animal = mNpc_GetInAnimalP();
        mNpc_GetRemoveAnimal(in_animal, TRUE);
        mCD_SetForeignerFile(&l_mcd_foreigner_file.file, priv, in_animal);
        if (mLd_PlayerManKindCheckNo(Common_Get(player_no)) == FALSE) {
            priv->exists = FALSE;
            mCD_ClearPrivateItem(priv, &mgr->private_item);
            mgr->_0198 = 1;
        }

        mAGrw_ClearMoneyStoneShineGround();
        Save_Set(travel_hard_time, lbRTC_HardTime());
        mgr->copy_protect = Common_Get(copy_protect);
        copy_protect = mCD_get_land_copyProtect();
        Common_Set(copy_protect, copy_protect);
        Save_Set(copy_protect, copy_protect);
        bzero(save, sizeof(Save));
        bcopy(Common_GetPointer(save), save, sizeof(Save));
        save->save_check.version = 6;
        mFRm_SetSaveCheckData(&save->save_check);
        save->save_check.checksum = mFRm_GetFlatCheckSum((u16*)save, sizeof(Save), save->save_check.checksum);
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        mgr->chan = ~chan & 1;
        bcopy(save, &l_keepSave, sizeof(Save));
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveStation_Passport_write_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 result;
    Save_t* save;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int res;
    int ret;

    ret = mCD_write_common(mgr);
    if (ret == mCD_RESULT_SUCCESS) {
        bzero(mgr->workArea, mgr->workArea_size);
        mgr->chan = ~mgr->chan & 1;
        mgr->loaded_file_type = mCD_FILE_PLAYER;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);

        if (fileInfo->fileNo == 0) {
            fileInfo->proc++;
        } else {
            fileInfo->proc = 8;
        }
    } else if (ret != mCD_RESULT_BUSY) {
        chan = mgr->chan;
        if (chan != -1) {
            card = &mgr->cards[chan];
            result = card->result;

            switch (result) {
                case CARD_RESULT_BROKEN:
                case CARD_RESULT_ENCODING:
                    fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                    break;
                case CARD_RESULT_WRONGDEVICE:
                case CARD_RESULT_NOCARD:
                    fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
                    break;
                default:
                    fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                    break;
            }
        } else {
            fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
        }

        fileInfo->chan = fileInfo->_04;
        fileInfo->_1C = mgr->chan;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(mgr->workArea, mgr->workArea_size);
        card = &mgr->cards[mgr->chan];
        if (mCD_load_file(mgr->workArea, mgr->loaded_file_type, (s32)mgr->chan, &card->result) == mCD_RESULT_SUCCESS) {
            res = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
            save = (Save_t*)mgr->workArea;
            if (res == 0 && mLd_CheckId(save->land_info.id) == TRUE && mLd_CheckThisLand(save->land_info.name, save->land_info.id) == TRUE) {
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                ret = mCD_RESULT_SUCCESS;
            }
        }

        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc = 12;
        }
    }

    return ret;
}

static int mCD_SaveStation_Passport_rewrite_main(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 result;
    Save_t* save;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int res;
    int ret;

    ret = mCD_RESULT_ERROR;
    chan = mgr->chan;
    if (chan == -1) {
        fileInfo->_04 = 2;
        mCD_get_this_land_slot_no(mgr);
    }

    if (mgr->chan != -1) {
        card = &mgr->cards[chan];
        result = card->result;

        switch (result) {
            case CARD_RESULT_BROKEN:
            case CARD_RESULT_ENCODING:
                fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                break;
            case CARD_RESULT_WRONGDEVICE:
            case CARD_RESULT_NOCARD:
                fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
                break;
            default:
                fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                break;
        }

        fileInfo->chan = fileInfo->_04;
        fileInfo->_1C = mgr->chan;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(mgr->workArea, mgr->workArea_size);
        mgr->chan = ~mgr->chan & 1;
        card = &mgr->cards[mgr->chan];
        if (mCD_load_file(mgr->workArea, mgr->loaded_file_type, (s32)mgr->chan, &card->result) == mCD_RESULT_SUCCESS) {
            res = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
            save = (Save_t*)mgr->workArea;
            if (res == 0 && mLd_CheckId(save->land_info.id) == TRUE && mLd_CheckThisLand(save->land_info.name, save->land_info.id) == TRUE) {
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                fileInfo->proc = 12;
                ret = mCD_RESULT_SUCCESS;
            }
        }
    } else {
        fileInfo->_04 = 2;
    }

    return ret;
}

static int mCD_SaveStation_Passport_make_file_name(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    static u8 cond[CARD_MAX_FILE];
    s32 chan;
    mCD_memMgr_card_info_c* card;
    int count;
    int filename_idx;
    int res;
    int ret;
    int i;

    ret = mCD_RESULT_SUCCESS;
    count = 0;
    filename_idx = 0;
    chan = mgr->chan;
    if (chan == -1) {
        chan = 0;
    }
    card = &mgr->cards[chan];
    
    bzero(cond, sizeof(cond));
    if (mCD_check_card(&card->result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
        card->result = CARDMount(chan, card->workArea, NULL);
        if (card->result == CARD_RESULT_READY || card->result == CARD_RESULT_BROKEN) {
            card->result = CARDCheck(chan);
            if (card->result == CARD_RESULT_READY) {
                for (i = 0; i < CARD_MAX_FILE; i++) {
                    card->result = CARDGetStatus(chan, i, &card->stat);
                    if (card->result == CARD_RESULT_READY && mCD_CheckPassportFileStatus(&card->stat) == TRUE) {
                        int idx = mCD_GetPassportFileIdx(card->stat.fileName);

                        if (idx >= 0 && idx < CARD_MAX_FILE) {
                            cond[idx] = TRUE;
                            count++;
                        }
                    }
                }
            }

            CARDUnmount(chan);
        } else if (card->result == CARD_RESULT_ENCODING) {
            CARDUnmount(chan);
        }

        if (count > 0) {
            for (i = 0; i < CARD_MAX_FILE; i++) {
                if (cond[i] == FALSE) {
                    filename_idx = i;
                    break;
                }
            }
        }
    }

    mem_clear((u8*)mgr->filename, sizeof(mgr->filename), 0);
    bcopy(l_mCD_player_file_name, mgr->filename, l_mCD_land_file_name_len); // 18
    mCD_set_number_str(mgr->filename + l_mCD_land_file_name_len, filename_idx);
    fileInfo->proc++;

    return ret;
}

static int mCD_SaveStation_Passport_create_file(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    mCD_file_entry_c* entry;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int size;
    int ret;

    ret = mCD_RESULT_BUSY;
    chan = mgr->chan;
    entry = &l_mcd_file_table[mCD_FILE_PLAYER];
    if (chan != -1) {
        card = &mgr->cards[chan];
        size = entry->filesize;
        ret = mCD_create_file_bg(mgr->filename, CARD_ATTR_NO_MOVE | CARD_ATTR_NO_COPY, entry->filesize, (s32)chan, &card->result, &card->fileNo);
        card->game_result = mCD_TransErrorCode(card->result);
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        } else if (ret != mCD_RESULT_BUSY) {
            ret = mCD_SaveStation_Passport_rewrite_main(mgr, fileInfo);
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveStation_Passport_set_icon_data(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    static int icon_fileNo[mPr_SEX_NUM][mPr_FACE_TYPE_NUM] = {
        {RESOURCE_BOY1, RESOURCE_BOY2, RESOURCE_BOY3, RESOURCE_BOY4, RESOURCE_BOY5, RESOURCE_BOY6, RESOURCE_BOY7, RESOURCE_BOY8},
        {RESOURCE_GIRL1, RESOURCE_GIRL2, RESOURCE_GIRL3, RESOURCE_GIRL4, RESOURCE_GIRL5, RESOURCE_GIRL6, RESOURCE_GIRL7, RESOURCE_GIRL8},
    };

    mCD_memMgr_card_info_c* card;
    ForeignerFile_c* file;
    int sex;
    int face;
    int ret;

    ret = mCD_RESULT_BUSY;
    file = (ForeignerFile_c*)mgr->workArea;
    if (file != NULL) {
        mgr->loaded_file_type = mCD_FILE_PLAYER;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(file, mgr->workArea_size);
        bcopy(l_comment_player_0_str, file->comment, sizeof(l_comment_player_0_str));
        mCD_get_passport_comment1(file->comment + sizeof(l_comment_player_0_str), Now_Private->player_ID.player_name);
        mCD_set_bti_data(file->banner, RESOURCE_ODEKAKE, 0xC00, 1, 0x200);
        sex = Now_Private->gender;
        face = Now_Private->face;

        if (sex != mPr_SEX_MALE && sex != mPr_SEX_FEMALE) {
            sex = 0;
        }

        if (face < mPr_FACE_TYPE0 || face >= mPr_FACE_TYPE_NUM) {
            face = 0;
        }

        mCD_set_bti_data(file->icon, icon_fileNo[sex][face], 0x400, 8, 0x200);
        bcopy(&l_mcd_foreigner_file.file, &file->file, sizeof(file->file));
        fileInfo->proc++;
        ret = mCD_RESULT_SUCCESS;
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveStation_Passport_write_passport(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 chan;
    s32 result;
    Save_t* save;
    mCD_file_entry_c* entry;
    mCD_memMgr_card_info_c* card;
    int ofs;
    int res;
    int ret;

    ret = mCD_RESULT_BUSY;
    chan = mgr->chan;
    card = &mgr->cards[chan];
    entry = &l_mcd_file_table[mgr->loaded_file_type];
    ofs = mCD_get_offset(mgr->loaded_file_type);
    ret = mCD_write_comp_bg(mgr->workArea, mgr->filename, mgr->workArea_size, entry->filesize, ofs, chan, &card->result);

    if (ret == mCD_RESULT_SUCCESS) {
        fileInfo->proc++;
    } else if (ret != mCD_RESULT_BUSY) {
        result = card->result;
        mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
        mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
        bzero(mgr->workArea, mgr->workArea_size);
        fileInfo->_1C = mgr->chan;
        mgr->chan = ~mgr->chan & 1;
        card = &mgr->cards[mgr->chan];
        if (mCD_load_file(mgr->workArea, mgr->loaded_file_type, mgr->chan, &card->result) == mCD_RESULT_SUCCESS) {
            res = mFRm_ReturnCheckSum((u16*)mgr->workArea, mgr->workArea_size);
            save = (Save_t*)mgr->workArea;
            if (res == 0 && mLd_CheckId(save->land_info.id) == TRUE && mLd_CheckThisLand(save->land_info.name, save->land_info.id) == TRUE) {
                mgr->loaded_file_type = mCD_FILE_SAVE_MAIN;
                ret = mCD_RESULT_SUCCESS;
            }
        }

        switch (result) {
            case CARD_RESULT_BROKEN:
            case CARD_RESULT_ENCODING:
                fileInfo->_04 = mCD_TRANS_ERR_BROKEN_WRONGENCODING;
                break;
            case CARD_RESULT_WRONGDEVICE:
            case CARD_RESULT_NOCARD:
                fileInfo->_04 = mCD_TRANS_ERR_NOCARD;
                break;
            default:
                fileInfo->_04 = mCD_TRANS_ERR_IOERROR;
                break;
        }

        fileInfo->chan = fileInfo->_04;
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        }
    }

    return ret;
}

static int mCD_SaveStation_Passport_get_status(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    int ret;

    ret = mCD_RESULT_BUSY;
    ret = mCD_get_status_common(mgr, fileInfo, mgr->filename, 0, CARD_COMMENT_SIZE, CARD_STAT_ICON_C8, CARD_STAT_SPEED_MIDDLE, 8, CARD_STAT_BANNER_C8);
    if (ret == mCD_RESULT_ERROR) {
        ret = mCD_SaveStation_Passport_rewrite_main(mgr, fileInfo);
    }

    return ret;
}

static int mCD_SaveStation_Passport_set_status(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 chan;
    mCD_memMgr_card_info_c* card;
    int ret;

    ret = mCD_RESULT_BUSY;
    chan = mgr->chan;
    if (chan != -1) {
        card = &mgr->cards[chan];
        ret = mCD_set_file_status_bg(&card->stat, mgr->filename, chan, &card->result);
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc = 12;
            mgr->loaded_file_type = mCD_FILE_SAVE_MAIN_BAK;
            mgr->workArea_size = mCD_get_size(mgr->loaded_file_type);
            bzero(mgr->workArea, mgr->workArea_size);
            bcopy(&l_keepSave, mgr->workArea, sizeof(Save));
            mgr->chan = ~mgr->chan & 1;
            mgr->_01A0 = 1;
        } else if (ret != mCD_RESULT_BUSY) {
            ret = mCD_SaveStation_Passport_rewrite_main(mgr, fileInfo);
        }
    } else {
        fileInfo->_04 = mCD_TRANS_ERR_NO_TOWN_DATA;
        ret = mCD_RESULT_ERROR;
    }

    return ret;
}

static int mCD_SaveStation_Passport_write_bk(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo) {
    s32 result;
    mCD_memMgr_card_info_c* card;
    s32 chan;
    int ret;

    ret = mCD_write_common(mgr);
    if (mgr->loaded_file_type == mCD_FILE_SAVE_MAIN) {
        if (ret != mCD_RESULT_BUSY) {
            fileInfo->_04 = fileInfo->chan;
            mgr->chan = fileInfo->_1C;
            if (mgr->copy_protect != -1) {
                Common_Set(copy_protect, mgr->copy_protect);
            }

            ret = mCD_RESULT_ERROR;
        }
    } else {
        if (ret == mCD_RESULT_SUCCESS) {
            fileInfo->proc++;
        } else if (ret != mCD_RESULT_BUSY) {
            fileInfo->proc = 15;
            ret = mCD_RESULT_SUCCESS;
        }
    }

    return ret;
}

static Private_c l_mcd_keep_private; // @unused

typedef int (*mCD_SAVESTATION_PASSPORT_PROC)(mCD_memMgr_c* mgr, mCD_memMgr_fileInfo_c* fileInfo);

extern int mCD_SaveStation_Passport_bg(s32* chan) {
    // clang-format off
    static mCD_SAVESTATION_PASSPORT_PROC save_proc[] = {
        mCD_SaveStation_NextLand_get_area,
        mCD_SaveStation_NextLand_check_repair_land,
        mCD_SaveStatoin_NextLand_repair_land,
        mCD_SaveStation_Passport_check_slot,
        mCD_SaveStation_Passport_set_data,
        mCD_SaveStation_Passport_write_main,
        mCD_SaveStation_Passport_make_file_name,
        mCD_SaveStation_Passport_create_file,
        mCD_SaveStation_Passport_set_icon_data,
        mCD_SaveStation_Passport_write_passport,
        mCD_SaveStation_Passport_get_status,
        mCD_SaveStation_Passport_set_status,
        mCD_SaveStation_Passport_write_bk,
        mCD_SaveHome_bg_set_others,
        mCD_SaveStation_NextLand_write_others,
    };
    // clang-format on
    
    mCD_memMgr_card_info_c* cardInfo;
    mCD_memMgr_c* mgr = &l_memMgr;
    mCD_memMgr_fileInfo_c* fileInfo = &mgr->save_home_info;
    int ret = mCD_TRANS_ERR_BUSY;
    u8 proc = (u8)fileInfo->proc;

    mgr->_0188++;
    if (mgr->_018C == 0) {
        if (proc < 15) {
            int res;
            
            res = (*save_proc[proc])(mgr, fileInfo);
            if (res == mCD_RESULT_SUCCESS) {
                if (fileInfo->proc == 15) {
                    *chan = mgr->chan;
                    ret = mCD_TRANS_ERR_NONE;
                }
            } else if (res != mCD_RESULT_BUSY) {
                *chan = mgr->chan;

                if (mgr->_01A0 == 1) {
                    mgr->copy_protect = -1;
                    ret = mCD_TRANS_ERR_NONE;
                } else {
                    ret = fileInfo->_04;
                    if (ret == 0) {
                        ret = mCD_TRANS_ERR_IOERROR;
                    }

                    if (mgr->_0198 == 1 && Now_Private != NULL) {
                        Now_Private->exists = TRUE;
                        mCD_ReplaceKeep(Now_Private, &mgr->private_item);
                    }
                }

                if (mgr->copy_protect != -1 && fileInfo->proc < 12) {
                    Common_Set(copy_protect, mgr->copy_protect);
                }
            }

            if (res == mCD_RESULT_ERROR || (res == mCD_RESULT_SUCCESS && fileInfo->proc == 15)) {
                if (mgr->_0188 >= 112) {
                    sAdo_SysLevStop(NA_SE_47);
                    
                    if (res == mCD_RESULT_SUCCESS && mLd_PlayerManKindCheck() == FALSE) {
                        mCD_create_famicom_file(mgr->chan);
                    }
                    mCD_ClearMemMgr_com2(mgr);
                } else {

                    mgr->_018C = 1;
                    mgr->_0190 = ret;
                    mgr->_0194 = *chan;
                    ret = mCD_TRANS_ERR_BUSY;
                    if (mgr->_0190 == mCD_TRANS_ERR_BUSY) {
                        mgr->_0190 = mCD_TRANS_ERR_NOCARD;
                    }
                }
            }
        } else {
            ret = mCD_TRANS_ERR_NONE;
            mCD_ClearMemMgr_com2(mgr);
        }
    } else {
        if (mgr->_0188 >= 112) {
            ret = mgr->_0190;
            *chan = mgr->_0194;
            if (ret == mCD_TRANS_ERR_NONE && mLd_PlayerManKindCheck() == FALSE) {
                mCD_create_famicom_file(*chan);
            }
            mCD_ClearMemMgr_com2(mgr);
            sAdo_SysLevStop(NA_SE_47);
        }
    }

    if (ret != mCD_TRANS_ERR_BUSY) {
        SoftResetEnable = TRUE;
    }
    return ret;
}

extern void mCD_toNextLand(void) {
    mCD_persistent_data_c persis;
    Save_t* save = &l_keepSave.save;
    int scene_no = Save_Get(scene_no);
    int last_scene_no;
    mLd_land_info_c* land_info;
    mActor_name_t last_field_id;
    s16 demo_profile[2];
    Time_c time;
    Transition_c transition;
    int rtc_enabled;

    if (l_keepSave_set == TRUE) {
        land_info = &save->land_info;
        if (mLd_CheckId(land_info->id) == TRUE && mFRm_ReturnCheckSum((u16*)save, sizeof(Save)) == 0) {
            bcopy(Common_GetPointer(travel_persistent_data), &persis, sizeof(persis));
            last_scene_no = Common_Get(last_scene_no);
            last_field_id = Common_Get(last_field_id);
            bcopy(Common_Get(demo_profiles), demo_profile, sizeof(demo_profile));
            bcopy(Common_GetPointer(time), &time, sizeof(time));
            bcopy(Common_GetPointer(transition), &transition, sizeof(transition));
            bzero(&common_data, sizeof(common_data_t));
            
            // restore
            bcopy(&persis, Common_GetPointer(travel_persistent_data), sizeof(persis));
            Common_Set(last_field_id, last_field_id);
            Common_Set(last_scene_no, last_scene_no);
            bcopy(demo_profile, Common_Get(demo_profiles), sizeof(demo_profile));
            bcopy(&time, Common_GetPointer(time), sizeof(time));
            bcopy(&transition, Common_GetPointer(transition), sizeof(transition));
            bcopy(save, Common_GetPointer(save), sizeof(Save));

            Common_Set(copy_protect, Save_Get(copy_protect));
            Save_Set(scene_no, scene_no);
            rtc_enabled = Common_Get(time.rtc_enabled);
            Common_Set(time.rtc_enabled, TRUE);
            mTM_rtcTime_limit_check();
            Common_Set(time.rtc_enabled, rtc_enabled);
            lbRTC_GetTime(Common_GetPointer(time.rtc_time));
            Common_Set(now_private, &l_mcd_foreigner_file.file.priv);
            Common_Set(player_no, mPr_FOREIGNER);
            Common_Set(auto_nwrite_set, FALSE);
            bzero(Common_GetPointer(auto_nwrite_time), sizeof(Common_Get(auto_nwrite_time)));
            Common_Set(ball_pos, ZeroVec);
            mTM_clear_renew_is();
            mEv_ClearEventInfo();
            mEv_toland_clear_common();
            mNpc_ClearInAnimal();
            mNpc_FirstClearGoodbyMail();
            mCD_ClearCardPrivateTable();
            mQst_ClearGrabItemInfo();
            bzero(Common_Get(npc_schedule), sizeof(Common_Get(npc_schedule)));
            mISL_ClearKeepIsland();
            bzero(Common_GetPointer(unused_mail_26522), sizeof(Mail_c));
            Common_Set(_2664E, 0);
            Common_Set(_26650, 0);
            mNpc_ClearCacheName();
            mCD_StartSetCardBgInfo();
            mCD_ClearMemMgr();
            mCD_ClearKeepLand();
            mCD_ClearCardPrivateTable();
            mCD_ClearCardPrivateTable_com(&l_mcd_card_private, 1);
            mCD_clear_all_control();
            l_mcd_copy_protect = -1;
            mCD_ClearNoLandProtectCode(&l_keep_noLandCode);
            mCD_ClearErrInfo();
            if (mFRm_CheckSaveData_common(Save_GetPointer(save_check), Save_Get(land_info).id)) {
                if (Save_Get(save_check).version == 5) {
                    bcopy(&Save_Get(save_check).time, Save_GetPointer(saved_auto_nwrite_time), sizeof(lbRTC_time_c));
                }
            }

            Common_Set(submenu_disabled, TRUE);
            bzero(&l_keepSave, sizeof(Save));
            l_keepSave_set = FALSE;
            
            if (mFRm_ReturnCheckSum((u16*)&l_keepMail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL]) == 0) {
                mCD_save_data_main_to_aram(&l_keepMail, l_aram_real_size_32_table[mCD_ARAM_DATA_MAIL], mCD_ARAM_DATA_MAIL);
            }
            mCD_set_init_mail_data(&l_keepMail);

            if (mFRm_ReturnCheckSum((u16*)&l_keepOriginal, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL]) == 0) {
                mCD_save_data_main_to_aram(&l_keepOriginal, l_aram_real_size_32_table[mCD_ARAM_DATA_ORIGINAL], mCD_ARAM_DATA_ORIGINAL);
            }
            mCD_set_init_original_data(&l_keepOriginal);

            if (mFRm_ReturnCheckSum((u16*)&l_keepDiary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY]) == 0) {
                mCD_save_data_main_to_aram(&l_keepDiary, l_aram_real_size_32_table[mCD_ARAM_DATA_DIARY], mCD_ARAM_DATA_DIARY);
            }
            mCD_set_init_diary_data(&l_keepDiary);
        }
    }
}
