#ifndef PC_TOWN_SELECT_H
#define PC_TOWN_SELECT_H

#ifdef __cplusplus
extern "C" {
#endif

#define PC_CARD_TOWN_MAX 64
#define PC_CARD_TOWN_NAME_SIZE 8

typedef struct {
    const char* file;
    unsigned char name[PC_CARD_TOWN_NAME_SIZE];
    int usable;
} pc_card_town_entry;

int pc_card_b_refresh_towns(void);
int pc_card_b_town_count(void);
const pc_card_town_entry* pc_card_b_town(int index);
int pc_card_b_select_town(int index);

int pc_card_b_scan_town_files(void);
int pc_card_b_town_base(char* output, int output_size);
int pc_card_b_is_legacy_town(void);

enum {
    PC_TOWN_SELECT_PENDING,
    PC_TOWN_SELECT_CHOSEN,
    PC_TOWN_SELECT_CANCELLED,
};

int pc_town_select_open(void);
int pc_town_select_poll(int* index);

#ifdef __cplusplus
}
#endif

#endif
