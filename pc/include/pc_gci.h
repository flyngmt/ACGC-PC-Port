#ifndef PC_GCI_H
#define PC_GCI_H

#include "m_common_data.h"
#include "m_card.h"

#define PC_GCI_PATH_MAX 1024
#define PC_GCI_FILENAME "DobutsunomoriP_MURA.gci"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PC_SAVE_LOADED,
    PC_SAVE_MISSING,
    PC_SAVE_INVALID,
    PC_SAVE_IO_ERROR
} pc_save_result;

typedef struct {
    void* storage;
    Save_t* save;
    mCD_keep_mail_c* mail;
    mCD_keep_original_c* original;
    mCD_keep_diary_c* diary;
} pc_gci_image;

pc_save_result pc_gci_read(const char* path, pc_gci_image* image);
void pc_gci_free(pc_gci_image* image);

int pc_gci_write(const char* path, const Save_t* save, const mCD_keep_mail_c* mail,
                 const mCD_keep_original_c* original, const mCD_keep_diary_c* diary);

int pc_gci_import(const char* source, const char* destination);
int pc_gci_is_town_file(const char* path);

#ifdef __cplusplus
}
#endif

#endif
