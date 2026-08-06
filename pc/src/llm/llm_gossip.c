/* llm_gossip.c - rumor propagation between NPCs */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdlib.h>

static int g_gossip_tick_count = 0;

void llm_gossip_tick(void) {
    if (!llm_is_enabled()) return;
    /* ponytail: periodic scan of NPC pairs, propagate gossip entries.
     * Tick every ~30s (1800 frames). For now, no-op stub. */
    g_gossip_tick_count++;
    if (g_gossip_tick_count < 1800) return;
    g_gossip_tick_count = 0;
}

void llm_gossip_purge_npc(int npc_idx) {
    /* ponytail: purge gossip entries from NPC when they move out */
    (void)npc_idx;
}
