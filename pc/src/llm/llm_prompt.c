/* llm_prompt.c - prompt builder from game state, NPC persona, and memory */
#include "pc_platform.h"
#include "llm/llm_api.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static const char *persona_descs[] = {
    [0] = "cheerful and kind. You love flowers, baking, and helping neighbors. You speak warmly.",
    [1] = "peppy and excitable. You are bubbly and energetic. You love fashion magazines, pop stars, and daydreaming about fame. Use exclamation marks.",
    [2] = "lazy and relaxed. You love food, naps, comic books, and talking about bugs you found under your bed.",
    [3] = "athletic and competitive. You are a jock obsessed with exercise, protein shakes, and your bicep measurements.",
    [4] = "cranky and old-fashioned. You are grumpy but secretly caring. You complain about young people, loud music, and rising prices.",
    [5] = "snooty and elegant. You care about fashion, high society, and interior design. You gossip about everyone but mean well deep down.",
};

/* --- memory sentiment tracking --- */

static void memory_ensure_dir(void) {
    mkdir("memory"
#ifdef _WIN32
    );
#else
    , 0755);
#endif
}

/* Read Likes/Hates from memory/<npc>_sent.txt */
static int memory_read_sentiments(const char *npc_name,
                                   char *likes, int likes_sz,
                                   char *hates, int hates_sz) {
    char path[256];
    snprintf(path, sizeof(path), "memory/%s_sent.txt", npc_name);
    likes[0] = '\0'; hates[0] = '\0';
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;
    char line[512];
    if (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "like:", 5) == 0) {
            strncpy(likes, line + 5, likes_sz - 1);
            likes[likes_sz - 1] = '\0';
            char *nl = strchr(likes, '\n'); if (nl) *nl = '\0';
        }
    }
    if (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "hate:", 5) == 0) {
            strncpy(hates, line + 5, hates_sz - 1);
            hates[hates_sz - 1] = '\0';
            char *nl = strchr(hates, '\n'); if (nl) *nl = '\0';
        }
    }
    fclose(fp);
    return 0;
}

/* Write updated Likes/Hates to memory/<npc>_sent.txt */
static void memory_write_sentiments(const char *npc_name,
                                     const char *likes, const char *hates) {
    char path[256];
    snprintf(path, sizeof(path), "memory/%s_sent.txt", npc_name);
    memory_ensure_dir();
    FILE *fp = fopen(path, "w");
    if (!fp) return;
    fprintf(fp, "like:%s\nhate:%s\n", likes ? likes : "", hates ? hates : "");
    fclose(fp);
}
static int sentiment_has(const char *list, const char *name) {
    if (!list || !list[0] || !name || !name[0]) return 0;
    char buf[256];
    strncpy(buf, list, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    char *tok = strtok(buf, ",");
    while (tok) {
        while (*tok == ' ') tok++;
        if (strcmp(tok, name) == 0) return 1;
        tok = strtok(NULL, ",");
    }
    return 0;
}

/* Add 'name' to the comma-separated 'list', avoid duplicates */
static void sentiment_add(char *list, int list_sz, const char *name) {
    if (!list || !name || sentiment_has(list, name)) return;
    int len = strlen(list);
    int need = strlen(name) + (len > 0 ? 2 : 0) + 1;
    if (len + need >= list_sz) return;
    if (len > 0) { strcat(list, ", "); }
    strcat(list, name);
}

/* Get a relationship sentence for the given other NPC.
 * Returns 0 if no existing sentiment, 1 for like, -1 for hate. */
static int memory_get_sentiment(const char *npc_name, const char *other,
                                 char *out, int out_sz) {
    char likes[256], hates[256];
    memory_read_sentiments(npc_name, likes, sizeof(likes), hates, sizeof(hates));
    if (sentiment_has(likes, other)) {
        snprintf(out, out_sz,
                 "You're fond of %s. Mention something you appreciate about them.",
                 other);
        return 1;
    }
    if (sentiment_has(hates, other)) {
        snprintf(out, out_sz,
                 "%s has been on your mind. Mention a small quirk or habit of theirs.",
                 other);
        return -1;
    }
    return 0;
}

/* Assign and save a new random sentiment. Returns 1 for like, -1 for hate. */
static int memory_assign_sentiment(const char *npc_name, const char *other,
                                    char *out, int out_sz) {
    char likes[256], hates[256];
    memory_read_sentiments(npc_name, likes, sizeof(likes), hates, sizeof(hates));

    int is_like = (rand() & 1);
    if (is_like) {
        sentiment_add(likes, sizeof(likes), other);
        snprintf(out, out_sz,
                 "You're fond of %s. Mention something you appreciate about them.",
                 other);
    } else {
        sentiment_add(hates, sizeof(hates), other);
        snprintf(out, out_sz,
                 "%s has been on your mind. Mention a small quirk or habit of theirs.",
                 other);
    }
    memory_write_sentiments(npc_name, likes, hates);
    return is_like ? 1 : -1;
}

/* --- memory sampling for prompt injection --- */

#define MEMORY_MAX_ENTRIES 256
static int memory_collect(const char *npc_name, char entries[MEMORY_MAX_ENTRIES][256],
                           int max_entries) {
    char path[256];
    snprintf(path, sizeof(path), "memory/%s.txt", npc_name);
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;
    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), fp) && count < max_entries) {
        if (strncmp(line, "Likes=", 6) == 0 ||
            strncmp(line, "Hates=", 6) == 0 ||
            strncmp(line, "like:", 5) == 0 ||
            strncmp(line, "hate:", 5) == 0) continue;
        if (line[0] == '[') {
            strncpy(entries[count], line, 255);
            entries[count][255] = '\0';
            char *nl = strchr(entries[count], '\n');
            if (nl) *nl = '\0';
            count++;
        }
    }
    fclose(fp);
    return count;
}

/* Sample memories: last 2, random 2 from last 10, 1 random from all.
 * Appends to 'out'. Returns number of memories injected. */
static int memory_inject(const char *npc_name, char *out, int out_sz) {
    char entries[MEMORY_MAX_ENTRIES][256];
    int n = memory_collect(npc_name, entries, MEMORY_MAX_ENTRIES);
    if (n < 2) return 0;

    int pos = 0;
    int injected = 0;

    /* last 2 */
    for (int i = n - 2; i < n && i >= 0; i++) {
        if (i < 0) continue;
        char *bracket = strchr(entries[i], ']');
        if (bracket) {
            pos += snprintf(out + pos, out_sz - pos,
                            "You once said:%s\n", bracket + 1);
            injected++;
        }
    }

    /* random 2 from last 10 */
    int recent_start = (n > 10) ? n - 10 : 0;
    int recent_count = n - recent_start;
    for (int j = 0; j < 2 && recent_count > 0; j++) {
        int ri = recent_start + (rand() % recent_count);
        char *bracket = strchr(entries[ri], ']');
        if (bracket) {
            pos += snprintf(out + pos, out_sz - pos,
                            "You once said:%s\n", bracket + 1);
            injected++;
        }
    }

    /* 1 random from all history */
    int ri = rand() % n;
    char *bracket = strchr(entries[ri], ']');
    if (bracket) {
        pos += snprintf(out + pos, out_sz - pos,
                        "You once said:%s\n", bracket + 1);
        injected++;
    }

    return injected;
}

/* --- resident selection --- */

static int pick_random_resident(char *dst, int dstsz, const char *residents, int count,
                                 const char *npc_name) {
    if (!residents || count <= 0) return 0;
    const char *candidates[64] = {0};
    int n = 0;
    char list[2048];
    strncpy(list, residents, sizeof(list) - 1);
    list[sizeof(list) - 1] = '\0';
    char *tok = strtok(list, ",");
    while (tok && n < 64) {
        while (*tok == ' ') tok++;
        if (strcmp(tok, npc_name) != 0)
            candidates[n++] = tok;
        tok = strtok(NULL, ",");
    }
    if (n == 0) return 0;
    strncpy(dst, candidates[rand() % n], dstsz - 1);
    dst[dstsz - 1] = '\0';
    return 1;
}

const char *llm_persona_desc(int personality) {
    if (personality < 0 || personality > 5) return persona_descs[0];
    return persona_descs[personality];
}

int llm_build_prompt(char *buf, int bufsz,
                      const char *npc_name, int personality,
                      const char *catchphrase,
                      const char *town_name, const char *player_name,
                      const char *weather, const char *season,
                      const char *time_of_day, int mood,
                      LlmHistory *history, LlmHistory *gossip_sources,
                      int gossip_count, const char *stock_text,
                      const char *town_residents, int resident_count) {
    int pos = 0;
    (void)mood;

    int r = rand() % 100;
    int hobbies_pct   = g_llm_config.topic_hobbies_pct;
    int relations_pct = g_llm_config.topic_relations_pct;

    char topic[384] = "";
    if (r < hobbies_pct) {
        snprintf(topic, sizeof(topic), "Talk about your hobbies or what you're doing today.");
    } else if (r < hobbies_pct + relations_pct) {
        /* 70% one villager, 30% two villagers */
        int count = (rand() % 10) < 7 ? 1 : 2;
        char a_name[32] = "", b_name[32] = "";

        int a_ok = pick_random_resident(a_name, sizeof(a_name), town_residents, resident_count, npc_name);
        int b_ok = (count == 2 && a_ok)
            ? pick_random_resident(b_name, sizeof(b_name), town_residents, resident_count, npc_name) : 0;

        const char *a = a_ok ? a_name : NULL;
        const char *b = b_ok ? b_name : NULL;
        if (a && b && strcmp(a, b) != 0) {
            char sa[256], sb[256];
            if (!memory_get_sentiment(npc_name, a, sa, sizeof(sa)))
                memory_assign_sentiment(npc_name, a, sa, sizeof(sa));
            if (!memory_get_sentiment(npc_name, b, sb, sizeof(sb)))
                memory_assign_sentiment(npc_name, b, sb, sizeof(sb));
            snprintf(topic, sizeof(topic),
                     "Talk about %s and %s. What's going on between them?",
                     a, b);
        } else if (a) {
            char sentiment[256];
            if (!memory_get_sentiment(npc_name, a, sentiment, sizeof(sentiment)))
                memory_assign_sentiment(npc_name, a, sentiment, sizeof(sentiment));
            snprintf(topic, sizeof(topic), "%s", sentiment);
        } else {
            snprintf(topic, sizeof(topic), "Talk about someone else in town.");
        }
    } else {
        snprintf(topic, sizeof(topic), "Make casual small talk or share a random observation.");
    }

    pos += snprintf(buf + pos, bufsz - pos,
        "You are %s, a %s villager in Animal Crossing. "
        "Your catchphrase is \"%s\". You live in %s. "
        "It is %s. The weather is %s. It is %s. "
        "Speak as this character. %s "
        "Reply in 1-2 short sentences under 90 characters. "
        "Never break character. Use your catchphrase occasionally.\n",
        npc_name, llm_persona_desc(personality), catchphrase, town_name,
        season, weather, time_of_day, topic);

    if (g_llm_config.prompt_extra[0]) {
        pos += snprintf(buf + pos, bufsz - pos, "%s\n", g_llm_config.prompt_extra);
    }

    /* memory injection: sample past conversations */
    if ((rand() % 100) < g_llm_config.memory_influence_pct) {
        char mem[512] = "";
        if (memory_inject(npc_name, mem, sizeof(mem)) > 0) {
            pos += snprintf(buf + pos, bufsz - pos, "Past conversations:\n%s\n", mem);
        }
    }

    pos += snprintf(buf + pos, bufsz - pos, "\n");

    if (history && history->count > 0) {
        pos += snprintf(buf + pos, bufsz - pos, "Recent conversation:\n");
        int shown = 0, max_chars = bufsz / 4;
        for (int i = history->count - 1; i >= 0 && pos < max_chars; i--) {
            int idx = (history->head - i - 1 + LLM_HISTORY_DEPTH) % LLM_HISTORY_DEPTH;
            const char *role = history->entries[idx].role == LLM_ROLE_PLAYER ? player_name :
                               history->entries[idx].role == LLM_ROLE_NPC ? npc_name : history->entries[idx].name;
            pos += snprintf(buf + pos, bufsz - pos, "%s: %s\n",
                           role, history->entries[idx].text);
            shown++;
        }
        if (shown > 0) pos += snprintf(buf + pos, bufsz - pos, "\n");
    }

    if (gossip_sources && gossip_count > 0) {
        pos += snprintf(buf + pos, bufsz - pos, "Rumors you've heard in town:\n");
        for (int i = 0; i < gossip_count && i < 3; i++) {
            if (gossip_sources[i].count > 0) {
                int idx = (gossip_sources[i].head - 1 + LLM_HISTORY_DEPTH) % LLM_HISTORY_DEPTH;
                pos += snprintf(buf + pos, bufsz - pos, "- %s: \"%s\"\n",
                               gossip_sources[i].entries[idx].name,
                               gossip_sources[i].entries[idx].text);
            }
        }
        pos += snprintf(buf + pos, bufsz - pos, "\n");
    }

    if (stock_text && stock_text[0]) {
        pos += snprintf(buf + pos, bufsz - pos, "%s says: %s\n\nResponse:", player_name, stock_text);
    } else {
        pos += snprintf(buf + pos, bufsz - pos, "%s is talking to you.\n\nResponse:", player_name);
    }

    buf[pos] = '\0';
    return pos;
}
