# LLM Dialogue Engine — Feasibility Report & Development Plan

## 1. System Architecture

### 1.1 Integration Point

Every dialogue box in the game routes through a single function: `mMsg_ChangeMsgData()`. This is the sole interception point.

```
mMsg_ChangeMsgData(message_window, msg_no)
   → pc_llm_get_dialogue(speaker_actor, context, stock_text)
   → LLM responds within timeout → replace msg_p->text_buf
   → LLM times out (>2s) → fall through to stock dialogue
```

Location: `src/game/m_msg.c` (compiled from decomp). The hook would be a `#ifdef PC_LLM_DIALOGUE` guard inserted into `mMsg_ChangeMsgData()`.

### 1.2 Speaker Identification

The `message_window_s` struct (`include/m_msg.h:181`) carries `client_actor_p` (line 192), an `ACTOR*` pointing to the NPC currently speaking. From this we resolve:

| Data | Source |
|------|--------|
| NPC name | `mNpc_GetNpcWorldNameP(npc_id)` in `include/m_npc.h:422` |
| Personality | `Animal_c.id.looks` — 6 types defined in `include/m_npc_personal_id.h:12-22` |
| Catchphrase | `Animal_c.catchphrase[10]` at `+0x89D` |
| Mood/feeling | `Animal_c.mood` at `+0x8E2` |
| Friendship | `Animal_c.memories[N].friendship` (per-player) |
| Home acre | `Animal_c.home_info.block_x / block_z` at `+0x01-02` |
| Relations | `Animal_c.animal_relations[ANIMAL_NUM_MAX]` at `+0x8F0` |

### 1.3 Personality Mapping

```c
static const char *persona_prompts[] = {
    [mNpc_LOOKS_GIRL]        = "You are cheerful, friendly, and kind. You love flowers and baking.",
    [mNpc_LOOKS_KO_GIRL]     = "You are peppy, excitable, and bubbly. You use lots of exclamation marks!",
    [mNpc_LOOKS_BOY]         = "You are lazy, relaxed, and food-obsessed. You talk about snacks and naps.",
    [mNpc_LOOKS_SPORT_MAN]   = "You are a jock, energetic, and competitive. You reference exercise constantly.",
    [mNpc_LOOKS_GRIM_MAN]    = "You are cranky, old-fashioned, and grumpy but secretly caring.",
    [mNpc_LOOKS_NANIWA_LADY] = "You are snooty, elegant, and gossipy. You care about fashion and status.",
};
```

### 1.4 Prompt Assembly

```
[SYSTEM]
You are {NPC_NAME}, a {PERSONALITY_DESC} villager in Animal Crossing.
Your catchphrase is "{CATCHPHRASE}". You live in {TOWN_NAME}.
It is {SEASON}. The weather is {WEATHER}. It is {TIME_OF_DAY}.
You are feeling {MOOD}.
The player, {PLAYER_NAME}, just approached you.

Previous conversations with {PLAYER_NAME}:
- You said: "{LAST_NPC_LINE}"
- They said: "{LAST_PLAYER_LINE}"
... (up to HISTORY_DEPTH entries)

Rumors you've heard:
- From {NEIGHBOR_A}: "{GOSSIP_ENTRY_A}"
- From {NEIGHBOR_B}: "{GOSSIP_ENTRY_B}"

[USER]
The player says: "{PLAYER_INPUT_OR_IMPLIED_GREETING}"
Respond in character, 1-3 sentences.
```

### 1.5 Stock Text Override Strategy

The game's stock text is used as fallback AND as seed context. When `mMsg_ChangeMsgData` is called with a stock `msg_no`, we:

1. Decode the stock message to ASCII/UTF-8
2. Pass it as `{STOCK_TEXT}` in the prompt alongside the rest of context
3. The LLM generates a variant dialogue **in the same spirit** but with personality flavor
4. On timeout (>2s) or error, the stock message displays unchanged

This means the game still controls conversation flow (quest triggers, branch logic). The LLM replaces only the **surface text**.

---

## 2. Conversation History

### 2.1 Per-NPC Ring Buffer

```c
#define LLM_HISTORY_DEPTH 20
#define LLM_ENTRY_LEN 256
#define LLM_NAME_LEN 16

typedef enum {
    LLM_ROLE_SYSTEM,
    LLM_ROLE_PLAYER,
    LLM_ROLE_NPC,
} LlmEntryRole;

typedef struct {
    char name[LLM_NAME_LEN];
    char text[LLM_ENTRY_LEN];
    LlmEntryRole role;
    lbRTC_time_c timestamp;
    u8 gossip_seed;       // 0=private, 1=spreadable
    mActor_name_t npc_id; // which NPC this entry belongs to (for hearsay attribution)
} LlmHistoryEntry;

typedef struct {
    LlmHistoryEntry entries[LLM_HISTORY_DEPTH];
    s16 head;       // next write position
    s16 count;      // total entries (capped at HISTORY_DEPTH)
    u32 total_msg;  // monotonic counter, used as gossip ID
} LlmHistory;

// Parallel array indexed by animal_idx (0..ANIMAL_NUM_MAX-1)
LlmHistory g_llm_history[ANIMAL_NUM_MAX] = {0};
```

History is stored in a flat binary file (`save/llm_history.bin`) and loaded/saved alongside game saves.

### 2.2 Entry Recording

Whenever `mMsg_ChangeMsgData` is called:

1. If the previous dialogue window is still being displayed (conversation continues): append the decoded stock text as `LLM_ROLE_NPC`, then append the LLM-generated text (if used) alongside.
2. On conversation end (`mMsg_REQUEST_MAIN_DISAPPEAR`): compact any duplicate/adjacent-system entries and write to disk.

### 2.3 History Truncation for Context Window

When building the LLM prompt, truncate history to fit within the provider's context limit (e.g., 4096 tokens for Ollama/Mistral, 128K for Gemini). A simple character-count budget:

```c
#define LLM_CONTEXT_BUDGET 3000  // chars for history section

int llm_build_history_prompt(char *buf, int bufsz, LlmHistory *h, int npc_idx) {
    int pos = 0;
    for (int i = h->count - 1; i >= 0 && pos < LLM_CONTEXT_BUDGET; i--) {
        int idx = (h->head - i - 1 + LLM_HISTORY_DEPTH) % LLM_HISTORY_DEPTH;
        int n = snprintf(buf + pos, bufsz - pos,
            "%s: %s\n", h->entries[idx].name, h->entries[idx].text);
        if (n < 0) break;
        pos += n;
    }
    return pos;
}
```

---

## 3. Gossip / Rumor Propagation

### 3.1 Mechanism

Every N frames (~30 real seconds), the gossip engine runs:

```c
void llm_gossip_tick(void) {
    static int tick_counter = 0;
    if (++tick_counter < 1800) return;          // ~30s at 60fps
    tick_counter = 0;

    for (int i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (g_llm_history[i].count == 0) continue;
        Animal_c *a = mNpc_GetAnimalInfoP(NPC_ID_FROM_IDX(i));
        if (!a || a->removing) continue;

        for (int j = i + 1; j < ANIMAL_NUM_MAX; j++) {
            Animal_c *b = mNpc_GetAnimalInfoP(NPC_ID_FROM_IDX(j));
            if (!b || b->removing) continue;

            float spread_chance = gossip_proximity_chance(a, b);
            if (spread_chance <= 0) continue;

            // For each gossippable entry in a's history:
            for (int k = 0; k < g_llm_history[i].count; k++) {
                LlmHistoryEntry *entry = &g_llm_history[i].entries[k];
                if (!entry->gossip_seed) continue;
                if (rand_float() > spread_chance) continue;

                // Copy as hearsay to b's history
                char rumor[LLM_ENTRY_LEN];
                snprintf(rumor, LLM_ENTRY_LEN, "[Heard from %s] %s",
                         mNpc_GetNpcWorldNameP(a->id.npc_id), entry->text);
                llm_history_append(&g_llm_history[j], LLM_ROLE_SYSTEM,
                                   mNpc_GetNpcWorldNameP(a->id.npc_id),
                                   rumor, a->id.npc_id);
            }
        }
    }
}
```

### 3.2 Proximity Weight

```c
static float gossip_proximity_chance(Animal_c *a, Animal_c *b) {
    int dx = abs((int)a->home_info.block_x - (int)b->home_info.block_x);
    int dz = abs((int)a->home_info.block_z - (int)b->home_info.block_z);

    // Same acre: 50% chance
    if (dx == 0 && dz == 0) return 0.50f;
    // Adjacent acre: 20% chance
    if (dx <= 1 && dz <= 1) return 0.20f;
    // Further: 0%
    return 0.0f;
}
```

### 3.3 Gossip Decay

Gossip entries are marked with the spreading NPC's ID. When the game loads, entries older than 3 in-game days are purged. When an NPC moves out, all their gossip is deleted from every other NPC's history.

### 3.4 Hearsay Chains

Gossip can chain. An entry marked `[Heard from X]` can be re-spread as `[Heard from Y, who heard from X]`. Chain depth capped at 2 to avoid noise.

---

## 4. Provider Abstraction

### 4.1 Interface

```c
typedef void (*LlmCallback)(const char *response, int status, void *userdata);

typedef struct {
    const char *name;
    int (*init)(void);                                // one-time init
    void (*query)(const char *prompt, LlmCallback cb, void *userdata);
    void (*shutdown)(void);
    int context_limit;                                 // max tokens/chars
} LlmProvider;
```

### 4.2 Provider Implementations

| Provider | File | Deps | Notes |
|----------|------|------|-------|
| Ollama | `llm_provider_ollama.c` | POSIX sockets | Local, no API key, easiest test target |
| DeepSeek | `llm_provider_deepseek.c` | OpenSSL + sockets | OpenAI-compatible API |
| Gemini | `llm_provider_gemini.c` | OpenSSL + sockets | Google AI Studio API |
| OpenAI/OpenCode Zen | `llm_provider_openai.c` | OpenSSL + sockets | OpenAI-compatible API |

Each provider is ~150 lines: build JSON POST body, open TLS socket, send HTTP request, parse JSON response line-by-line.

### 4.3 Configuration

Providers configured in `llm.ini` next to the executable:

```ini
[llm]
provider = ollama         ; ollama | openai | gemini | deepseek
endpoint = http://localhost:11434/api/generate
api_key =                 ; empty for ollama
model = mistral:7b
timeout_ms = 3000
max_tokens = 150
temperature = 0.8
enabled = true
```

### 4.4 Async Query Flow

```c
void llm_query_async(const char *prompt, LlmCallback cb, void *userdata) {
    // Launch a thread or use non-blocking socket
    // Store the callback + userdata
    // On completion (or timeout), invoke cb from main thread
    // The message system checks llm_result_ready() each frame
}
```

The dialogue system checks per-frame whether an LLM response has arrived. If yes, it swaps the text buffer. If not, it continues rendering stock text until timeout.

---

## 5. File Layout

```
pc/
├── CMakeLists.txt                    # Add llm/ sources, link OpenSSL
├── src/
│   ├── pc_main.c                     # Call llm_init() on startup
│   └── llm/
│       ├── llm_core.c                # Init, shutdown, config parsing
│       ├── llm_hook.c                # mMsg_ChangeMsgData interception
│       ├── llm_history.c             # Ring buffer CRUD, serialize/deserialize
│       ├── llm_gossip.c              # Propagation tick, proximity calc
│       ├── llm_prompt.c              # Prompt builder from game state
│       ├── llm_provider_ollama.c     # Ollama backend
│       ├── llm_provider_openai.c     # OpenAI/OpenCode Zen backend
│       ├── llm_provider_gemini.c     # Gemini backend
│       ├── llm_provider_deepseek.c   # DeepSeek backend
│       └── llm_util.c               # JSON builder, SHA256, base64 (no external libs)
├── include/
│   └── llm/
│       ├── llm_types.h               # Shared types, config struct
│       └── llm_api.h                 # Public API
└── CMakeLists.txt                    # Updated
```

---

## 6. Linux Build Prerequisites

The CMakeLists.txt already supports Linux (`pc/CMakeLists.txt:22-25`). The 32-bit requirement comes from JSystem casting pointers to `u32` — this is a hard constraint of the decomp, not fixable without a full pointer-width audit of the game code.

```bash
# Ubuntu/Debian
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc-multilib g++-multilib \
                 libsdl2-dev:i386 libgl-dev:i386 \
                 libssl-dev:i386

# Build
mkdir -p pc/build32-linux && cd pc/build32-linux
cmake .. \
    -DCMAKE_C_COMPILER=i686-linux-gnu-gcc \
    -DCMAKE_CXX_COMPILER=i686-linux-gnu-g++ \
    -DPC_LLM_DIALOGUE=ON
make -j$(nproc)
```

---

## 7. Development Plan

### Phase 0: Build Infrastructure (Day 1)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 0.1 | Verify 32-bit Linux build compiles and links | `pc/build32-linux/` | 2h |
| 0.2 | Add `-DPC_LLM_DIALOGUE` CMake option that compiles in `pc/src/llm/*.c` and links OpenSSL | `pc/CMakeLists.txt` | 1h |
| 0.3 | Create directory scaffolding: `pc/src/llm/`, `pc/include/llm/` | — | 15m |
| 0.4 | Add `llm.ini` loading to `pc_main.c` startup | `pc_main.c:398` | 45m |

**Phase 0 exit criteria:** Clean Linux build of existing game (no LLM code yet), CMake option functional.

### Phase 1: Core Types & Ollama Provider (Days 2–3)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 1.1 | Define `llm_types.h`: `LlmHistoryEntry`, `LlmHistory`, `LlmProvider`, `LlmConfig`, provider enum | `pc/include/llm/llm_types.h` | 1h |
| 1.2 | Define `llm_api.h`: public init/shutdown/query/config functions | `pc/include/llm/llm_api.h` | 30m |
| 1.3 | Implement `llm_core.c`: config parsing (`llm.ini` in INI-key=value format), `llm_init()`, `llm_shutdown()` | `pc/src/llm/llm_core.c` | 2h |
| 1.4 | Implement `llm_util.c`: `llm_build_json()` (minimal JSON builder, no external deps), `llm_parse_json_field()` | `pc/src/llm/llm_util.c` | 3h |
| 1.5 | Implement `llm_provider_ollama.c`: POSIX socket to `POST /api/generate`, parse streaming JSON response, invoke callback | `pc/src/llm/llm_provider_ollama.c` | 4h |
| 1.6 | **Integration test:** `main()` calls `llm_query("Hello!", callback)` against running Ollama, prints response | manual test | 1h |

**Phase 1 exit criteria:** Ollama provider connects, sends prompt, receives response, calls callback. No game integration yet.

### Phase 2: History System (Days 4–5)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 2.1 | Implement `llm_history.c`: `llm_history_init()`, `llm_history_append()`, `llm_history_get()`, `llm_history_count()` | `pc/src/llm/llm_history.c` | 2h |
| 2.2 | Add serialization: `llm_history_save()` / `llm_history_load()` — binary dump to `save/llm_history.bin` | `pc/src/llm/llm_history.c` | 2h |
| 2.3 | Add aging: purge entries older than 3 in-game days on load | `pc/src/llm/llm_history.c` | 1h |
| 2.4 | Wire into `pc_main.c`: load on startup, save on shutdown, save on NPC conversation end | `pc/src/pc_main.c`, `pc/src/pc_card.c` | 1h |
| 2.5 | **Unit test:** append/get/save/load round-trip | manual test | 30m |

**Phase 2 exit criteria:** History buffers survive save/load cycle.

### Phase 3: Prompt Builder (Day 5)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 3.1 | Implement `llm_prompt.c`: `llm_build_system_prompt()` — read personality, catchphrase, mood, weather, time | `pc/src/llm/llm_prompt.c` | 3h |
| 3.2 | Implement `llm_build_history_prompt()` — format last N entries with role prefixes | `pc/src/llm/llm_prompt.c` | 1h |
| 3.3 | Implement `llm_build_gossip_prompt()` — format hearsay entries for this NPC | `pc/src/llm/llm_prompt.c` | 1h |
| 3.4 | Implement `llm_build_full_prompt()` — assemble system + history + gossip + player input, respect context budget | `pc/src/llm/llm_prompt.c` | 2h |
| 3.5 | **Test:** call `llm_build_full_prompt()` with hardcoded NPC/player data, print output | manual test | 30m |

**Phase 3 exit criteria:** Full prompt generated with correct personality, history, and gossip.

### Phase 4: Dialogue Hook (Days 6–7)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 4.1 | Implement `llm_hook.c`: `llm_on_msg_change()` — intercepts after stock text decode, triggers async LLM query, stores callback to swap buffer on response | `pc/src/llm/llm_hook.c` | 4h |
| 4.2 | Implement `llm_hook_tick()` — per-frame check: poll for completed LLM response, copy into `msg_p->text_buf.data[]` if ready, record to history | `pc/src/llm/llm_hook.c` | 2h |
| 4.3 | Insert `#ifdef PC_LLM_DIALOGUE` guard into `mMsg_ChangeMsgData()` at `src/game/m_msg.c` — decode stock text, call `llm_on_msg_change()`, fallthrough on timeout | `src/game/m_msg.c` | 2h |
| 4.4 | Add `llm_hook_tick()` call to main game loop (`m_play.c` or `pc_main.c` per-frame) | `src/game/m_play.c` | 30m |
| 4.5 | Add history recording: on `mMsg_REQUEST_MAIN_DISAPPEAR`, flush NPC entry with `gossip_seed=1` | `pc/src/llm/llm_hook.c` | 1h |
| 4.6 | Add stock-text fallback: if `llm_query` doesn't respond within `config.timeout_ms`, display original stock text | `pc/src/llm/llm_hook.c` | 1h |
| 4.7 | **Integration test:** Talk to a villager, see LLM response in dialogue box | play test | 2h |

**Phase 4 exit criteria:** LLM replaces villager dialogue in-game, with graceful stock-text fallback.

### Phase 5: Gossip System (Days 8–9)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 5.1 | Implement `llm_gossip.c`: `llm_gossip_tick()` — periodic scan of NPC pairs, proximity-weighted spread | `pc/src/llm/llm_gossip.c` | 3h |
| 5.2 | Implement hearsay formatting: `[Heard from NPC_NAME] ORIGINAL_TEXT` with chain-depth cap | `pc/src/llm/llm_gossip.c` | 1h |
| 5.3 | Add gossip cleanup on NPC move-out: `llm_gossip_purge_npc(npc_id)` | `pc/src/llm/llm_gossip.c` | 1h |
| 5.4 | Wire `llm_gossip_tick()` into game loop, triggered every 1800 frames (~30s) | `src/game/m_play.c` | 30m |
| 5.5 | **Integration test:** Talk to NPC A, wait, talk to NPC B (neighbor), verify gossip appears in B's prompt | play test | 2h |

**Phase 5 exit criteria:** Gossip spreads between nearby NPCs and surfaces in LLM prompts.

### Phase 6: Remaining Providers (Days 10–11)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 6.1 | Implement `llm_provider_openai.c` — OpenAI-compatible API (also works for OpenCode Zen, vLLM, LM Studio) | `pc/src/llm/llm_provider_openai.c` | 3h |
| 6.2 | Implement `llm_provider_gemini.c` — Google AI Studio API | `pc/src/llm/llm_provider_gemini.c` | 3h |
| 6.3 | Implement `llm_provider_deepseek.c` — DeepSeek API (OpenAI-compatible with different endpoint) | `pc/src/llm/llm_provider_deepseek.c` | 2h |
| 6.4 | Add provider auto-detection from `llm.ini` `provider=` field to `llm_core.c` | `pc/src/llm/llm_core.c` | 1h |
| 6.5 | **Test:** connect to each provider with valid API key, verify response | manual test | 2h |

**Phase 6 exit criteria:** All 4 providers work, switchable via `llm.ini`.

### Phase 7: Polish (Days 12–13)

| # | Task | Files | Effort |
|---|------|-------|--------|
| 7.1 | Add `--llm-verbose` CLI flag: print prompts and responses to stdout | `pc/src/pc_main.c` | 30m |
| 7.2 | Add in-game toggle key (F4): enable/disable LLM dialogue at runtime | `pc/src/llm/llm_hook.c`, `pc_main.c` | 1h |
| 7.3 | Add `--llm-cache` mode: pre-generate dialogues for all NPCs, store in file, use offline | `pc/src/llm/llm_hook.c` | 3h |
| 7.4 | Handle edge cases: NPC with no Animal_c data (special NPCs), empty history, message buffer overflow (>1600 bytes) | `pc/src/llm/llm_hook.c`, `llm_prompt.c` | 2h |
| 7.5 | Write `llm.ini.example` with comments for each provider | `pc/src/llm/llm.ini.example` | 30m |
| 7.6 | Full playtest session: 30 min of normal gameplay, verify no crashes, dialogue feels natural | play test | 2h |

**Phase 7 exit criteria:** Feature is playable, toggleable, fails gracefully. Ready for PR.

---

## 8. Risk Analysis

| Risk | Impact | Mitigation |
|------|--------|------------|
| LLM latency disrupts gameplay | High | 2s timeout + stock-text fallback; async query in thread |
| Message buffer overflow (1600 bytes) | Medium | Truncate LLM response to `mMsg_MSG_BUF_SIZE - 1`, add null terminator |
| 32-bit address space limits memory for LLM context | Low | History kept minimal; full context is downstream at the LLM server |
| OpenSSL dependency bloats 32-bit binary | Medium | Could use raw TLS via BearSSL (~60KB) as lighter alternative |
| NPC data not available when `mMsg_ChangeMsgData` runs | Medium | Guard with null checks; fall back to generic personality-less prompt |
| Conversation state machine timing conflicts | High | Never block in the hook; all LLM work is async, return stock text immediately |

---

## 9. Dependencies

| Dependency | Purpose | Already linked? |
|-----------|---------|-----------------|
| SDL2 | Thread creation for async queries | Yes |
| OpenSSL (libssl + libcrypto) | TLS for HTTPS API calls | No — add to CMake |
| POSIX sockets | HTTP for plain-text Ollama | Yes (system libc) |
| `dl` `pthread` `m` | Dynamic linking, threading, math | Yes (CMakeLists.txt:431) |

OpenSSL is the only new external dependency. For a zero-dependency alternative, BearSSL (single-file, ~60KB compiled) can be vendored into `pc/lib/bearssl/`.

---

## 10. Summary

The game architecture is exceptionally well-suited for this feature. The entire dialogue system funnels through `mMsg_ChangeMsgData()`, the NPC data structures are fully decompiled and documented, and the PC port already has the `TARGET_PC` / `PC_ENHANCEMENTS` preprocessor path for optional features. The gossip system leverages existing data (`animal_relations[]`, home acre positions, `mood`) that already model the social graph.

**Total estimated effort:** ~13 days for a single developer familiar with the codebase.

**Hardest parts:** async HTTP with TLS in a game loop (Phases 4–6), dialogue state machine integration (Phase 4).

**Easiest parts:** data structures (Phase 1), history system (Phase 2), gossip proximity math (Phase 5).

**First thing to build:** the Ollama provider (Phase 1.5–1.6) — no TLS, no API keys, perfect for testing the integration without external dependencies.
