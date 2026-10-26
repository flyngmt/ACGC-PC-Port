#ifndef PC_GCI_DIR_H
#define PC_GCI_DIR_H

#include <dolphin/card.h>

#define PC_GCI_BLOCK_SIZE 0x2000
#define PC_GCI_TOWN_FILE_NAME "DobutsunomoriP_MURA"

#ifdef __cplusplus
extern "C" {
#endif

void pc_gci_init_dir(CARDDir* dir, const char* file_name, u32 data_size, u32 icon_addr, u16 icon_format,
                     u16 icon_speed, u32 comment_addr);
int pc_gci_dir_has_name(const CARDDir* dir, const char* file_name);
int pc_gci_data_offset(const CARDDir* dir, u32* offset);

#ifdef __cplusplus
}
#endif

#endif
