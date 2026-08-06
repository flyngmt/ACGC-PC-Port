/* llm_history.c - NPC conversation ring buffer with save/load */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>

void llm_history_init(LlmHistory *h) {
    memset(h, 0, sizeof(*h));
}

void llm_history_append(LlmHistory *h, const char *name, const char *text,
                          int role, int gossip_seed, uint16_t npc_id) {
    int pos = h->head;
    strncpy(h->entries[pos].name, name, LLM_NAME_LEN - 1);
    h->entries[pos].name[LLM_NAME_LEN - 1] = '\0';
    strncpy(h->entries[pos].text, text, LLM_ENTRY_LEN - 1);
    h->entries[pos].text[LLM_ENTRY_LEN - 1] = '\0';
    h->entries[pos].role = role;
    h->entries[pos].gossip_seed = gossip_seed;
    h->entries[pos].npc_id = npc_id;
    h->entries[pos].gossip_id = h->next_gossip_id++;

    h->head = (h->head + 1) % LLM_HISTORY_DEPTH;
    if (h->count < LLM_HISTORY_DEPTH) h->count++;
}

void llm_history_clear(LlmHistory *h) {
    memset(h, 0, sizeof(*h));
}

int llm_history_save(const char *path, LlmHistory *histories, int count) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;
    /* simple binary dump: count, then each history struct */
    if (fwrite(&count, sizeof(count), 1, fp) != 1) { fclose(fp); return -1; }
    if (fwrite(histories, sizeof(LlmHistory), (size_t)count, fp) != (size_t)count) {
        fclose(fp); return -1;
    }
    fclose(fp);
    return 0;
}

int llm_history_load(const char *path, LlmHistory *histories, int count) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return -1;
    int stored_count = 0;
    if (fread(&stored_count, sizeof(stored_count), 1, fp) != 1) { fclose(fp); return -1; }
    int n = stored_count < count ? stored_count : count;
    if (n > 0) {
        memset(histories, 0, (size_t)count * sizeof(LlmHistory));
        if (fread(histories, sizeof(LlmHistory), (size_t)n, fp) != (size_t)n) {
            fclose(fp); return -1;
        }
    }
    fclose(fp);
    return 0;
}
