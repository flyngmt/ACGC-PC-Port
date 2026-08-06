# Animal Crossing PC Port — Developer Documentation

PC port of Animal Crossing GameCube built on top of a 99.52% complete C decompilation.

## Architecture Overview

The game's rendering has 3 tiers:

```
Game code (N64 display lists) → emu64 (DL interpreter) → GX (GameCube GPU API) → [OpenGL]
```

We replace **only tier 3** (GX → OpenGL 3.3). The emu64 layer and game code stay as-is, with `#ifdef TARGET_PC` guards where platform differences require it.

### Boot Chain

```
main() [pc_main.c]
  → pc_settings_load()          # load settings.ini
  → pc_platform_init()          # SDL2, GL 3.3, GLAD
  → pc_disc_init()              # find & open disc image (CISO/ISO/GCM)
  → pc_assets_init()            # extract DOL/REL from disc, load all ~2500 assets
  → pc_texture_pack_init()      # scan texture_pack/ for HD replacements
  → ac_entry()                  # game's main.c: sets HotStartEntry = &entry
  → boot_main()                 # boot.c: OSInit, DVD, archives
    → entry() → mainproc() → graph_proc()   # THE MAIN LOOP

graph_proc() loops over scenes via game_dlftbls[]:
  first_game → second_game → trademark → select (title demo)
  → player_select (scene 19) → play (gameplay)
  OR: --model-viewer → model_viewer_init (scene 10)

Each frame: graph_main()
  → game_main() → scene->exec()         # builds N64 display lists
  → graph_task_set00() → emu64_taskstart()  # processes DLs → GX → GL
  → VIWaitForRetrace()                   # SDL swap + event pump + frame pacing
```

## Runtime Asset Loading

The original decomp compiles ~16,400 binary `.inc` files directly into the executable. The PC port instead loads assets at runtime from a GameCube disc image, eliminating the need for the decomp's asset extraction pipeline.

### Pipeline

```
User provides disc image (.ciso/.iso/.gcm)
  → pc_disc_init() opens and parses GCM filesystem
  → pc_assets_init() extracts main.dol + foresta.rel.szs into memory
  → ~2500 assets loaded from DOL/REL data at their original ROM offsets
  → Byte-swap applied per asset (SWAP_NONE/SWAP_U16/SWAP_U32/SWAP_VTX)
  → Source files use lazy-load pattern for function-local static data
```

### Code Generation

`pc/tools/gen_runtime_assets.py` (632 lines) scans all `src/*.c` files for `#include "assets/*.inc"` patterns and:

1. **Transforms source files in-place**: replaces inline `#include` with sized-array declarations and lazy-load code under `#ifdef TARGET_PC`
2. **Generates `pc/src/pc_assets.c`** (~30K lines): central loader with asset table mapping ~2500 assets to their ROM offsets, byte-swap types, and source (DOL or REL)
3. **Generates `pc/include/pc_assets.h`**: public API (`pc_assets_init`, `pc_load_asset`)
4. **Copies `.bin` fallback files** to `pc/build32/bin/assets/` for non-disc-image builds

### Fallback Chain

1. **Primary**: Disc image in `rom/`, `orig/`, or current directory
2. **Secondary**: Pre-extracted DOL + REL files in `orig/GAFE01_00/`
3. **Tertiary**: Individual `.bin` files in `assets/`

### Disc Image Support

`pc/src/pc_disc.c` handles CISO (block-mapped, 32KB headers), ISO, and GCM (raw) formats. Includes Yaz0 decompression for compressed REL files. Parses the GCM's File System Table for DVD path lookups.

## File Reference

### PC Port Layer (what we wrote)

#### Core

| File | Purpose |
|------|---------|
| `pc/src/pc_main.c` | Entry point, SDL2/GL init, CLI flags, DPI scaling |
| `pc/src/pc_gx.c` | GX → OpenGL: all GX API functions, vertex submission, state, draw dispatch, dirty-flag uniform system |
| `pc/src/pc_gx_tev.c` | TEV shader: GLSL program loading, uniform upload |
| `pc/src/pc_gx_texture.c` | 10 GC texture format decoders, 2048-entry cache with FNV-1a |
| `pc/src/pc_os.c` | Dolphin OS: memory arena, timers, calendar time, message queues, thread stubs |
| `pc/src/pc_mtx.c` | C matrix math replacing PPC paired-singles assembly |
| `pc/src/pc_misc.c` | HW register arrays, EXI/SI/PPC stubs, malloc wrappers, trig |

#### Asset Loading

| File | Purpose |
|------|---------|
| `pc/src/pc_disc.c` | GC disc image I/O (CISO/ISO/GCM), FST parsing, Yaz0 decompression |
| `pc/src/pc_dvd.c` | DVD filesystem emulation: entry table, disc-backed and file-backed I/O |
| `pc/src/pc_assets.c` | Auto-generated: ROM extraction, asset table, per-file loaders, byte-swap |
| `pc/tools/gen_runtime_assets.py` | Source scanner: transforms .inc includes to runtime loads, generates pc_assets.c |

#### I/O and Storage

| File | Purpose |
|------|---------|
| `pc/src/pc_card.c` | Memory card API → local file save/load |
| `pc/src/pc_m_card.c` | Memory card manager: GCI save/load, village generation, ARAM data blocks |
| `pc/src/pc_save_bswap.c` | GCI save file bidirectional LE↔BE byte-swap (Dolphin-compatible) |
| `pc/src/pc_pad.c` | Keyboard + SDL2 gamepad input (GC button format) |
| `pc/src/pc_audio.c` | SDL2 audio: 32kHz s16 stereo, dedicated producer thread + SPSC ring buffer |
| `pc/src/pc_vi.c` | Video interface → SDL swap, timer-based 60fps pacing with spin-wait |
| `pc/src/pc_aram.c` | 16MB ARAM buffer, bump allocator, DMA → memcpy |

#### Enhancements

| File | Purpose |
|------|---------|
| `pc/src/pc_settings.c` | Runtime `settings.ini` parser/writer (resolution up to 4K, fullscreen, vsync, MSAA) |
| `pc/src/pc_texture_pack.c` | Dolphin-compatible HD texture pack loader (XXHash64 matching, DDS, preloading) |
| `pc/src/pc_model_viewer.c` | Debug model viewer: 75 building/structure models, orbit camera |

#### Support

| File | Purpose |
|------|---------|
| `pc/src/pc_stubs.c` | Remaining link stubs (GBA, famicom, libultra, threads) |
| `pc/src/pc_stubs_cpp.cpp` | JSystem C++ vtable stubs |
| `pc/src/pc_fontdata.c` | Embedded font (byte-swapped for LE) |
| `pc/shaders/default.vert` | GLSL vertex shader (runtime-loaded, required) |
| `pc/shaders/default.frag` | GLSL fragment shader (runtime-loaded, uniform-driven TEV stages with bias/scale/clamp/swap) |

#### Headers

| File | Purpose |
|------|---------|
| `pc/include/pc_platform.h` | Platform config, 32-bit guard, SDL2/GL includes, crash API, widescreen defs |
| `pc/include/pc_gx_internal.h` | PCGXState, PCGXVertex, PCGXTevStage, indirect texture structs |
| `pc/include/pc_save_bswap.h` | GCI save byte-swap API |
| `pc/include/pc_model_viewer.h` | Model viewer struct and init/cleanup |
| `pc/include/pc_bswap.h` | `pc_bswap16/32/64` macros + array swap helpers |
| `pc/include/pc_settings.h` | Settings struct and load/save/apply API |
| `pc/include/pc_texture_pack.h` | Texture pack init/lookup/shutdown API |
| `pc/include/pc_disc.h` | Disc image I/O and FST lookup API |
| `pc/include/pc_assets.h` | Asset loader init and per-asset load API |
| `pc/include/pc_types.h` | Platform type definitions |
| `pc/include/pc_diag.h` | Diagnostic output macros (PC_DIAG) |

### Critical Decomp Modifications

These are the most-modified files from the upstream decompilation:

| File | Why |
|------|-----|
| `src/static/libforest/emu64/emu64.c` | Texture cache routing, TEXEL1, vertex colors, fog guard, per-stage texture binding, widescreen NOOPTag handling |
| `include/libforest/gbi_extensions.h` | 30 GBI bitfield structs reversed for LE x86 |
| `src/static/libforest/emu64/emu64_utility.c` | seg2k0 proximity heuristic, N64Mtx byte-swap |
| `src/static/boot.c` | Arena init, REL skip, actable endian swap |
| `src/graph.c` | Frame loop diagnostics, model viewer routing |
| `src/padmgr.c` | GC→N64 button conversion, once-per-frame guard |
| `src/game/m_play.c` | Scene transition diagnostics, fog BG fix, widescreen stretch markers |
| `src/game/m_player_lib.c` | Player palette byte-swap from ARAM |
| `src/game/m_field_make.c` | FG data u16 byte-swap (3 swap sites) |
| `src/game/m_room_type.c` | Room wall/floor palette u16 byte-swap |
| `src/game/m_scene.c` | Scene_Word_u endianness fix |
| `src/sys_matrix.c` | Matrix_MtxtoMtxF endian swap, suMtxMakeTS/SRT/SRT_ZXY fixes |
| `src/game/m_npc.c` | Title demo animal slot cleanup: clear before write, skip sentinel entries |
| `src/game/m_trademark.c` | Clear npclist before demo repopulation, sentinel entry for demo_npc_list |
| `src/actor/npc/ac_npc_think_wander.c_inc` | Clamp `looks` before indexing decide_boarder[] (latent OOB bug) |
| `src/game.c` | Frame timing and game exec dispatch |
| `src/jaudio_NES/na_combo.c` | Melody sequence u16 offset byte-swap |

About ~100 decomp files total are modified. Most changes are small `#ifdef TARGET_PC` blocks for byte-swapping or platform adaptation.

## Rendering Pipeline

### Vertex Submission

Deferred commit model. A position call commits the *previous* vertex. Auto-flush via `pc_gx_flush_if_begin_complete()` when expected vertex count is reached (handles missing GXEnd). Explicit GXEnd calls added at end of dl_G_TRIN/dl_G_QUADN/dl_G_TRI2 to prevent batches from flushing after viewport changes.

VAO attribute pointers and quad-to-triangle EBO are set up once at init, not per draw.

### SHARED vs NONSHARED Vertices

- **SHARED** (GX_PNMTX0, slot 0): pre-transformed at load time for seamless character joints
- **NONSHARED** (GX_PNMTX1, slot 1): transformed by GX matrix each frame

Do NOT force all vertices to NONSHARED — it breaks character joint seams.

### TEV Pipeline

Up to 3 stages, KONST colors, swap tables, per-stage texture binding. Single GLSL program with uniform-driven stages. Shaders loaded from `pc/shaders/` at runtime (required — no embedded fallback).

Per-stage uniforms:
- **Bias**: ADDHALF (+0.5), SUBHALF (-0.5) applied after TEV blend
- **Scale**: SCALE_2 (x2), SCALE_4 (x4), DIVIDE_2 (x0.5) applied after bias
- **Clamp**: per-channel clamp to [0,1] at output register write
- **Output register**: stages can write to PREV, REG0, REG1, or REG2
- **Swap tables**: 4 configurable tables (ivec4 channel remap), per-stage selection for texture and rasterizer colors

### Texture Cache

2048-entry cache keyed by (ptr, w, h, fmt, tlut_name, content_hash). ~100% hit rate at steady state. 10 GC texture formats decoded: I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, CI4, CI8, CI14x2, CMPR (S3TC).

Stale GL texture IDs are cleaned up on cache eviction to prevent GPU resource leaks.

### Uniform Dirty-Flag System

`pc_gx.c` uses per-uniform dirty flags to skip redundant `glUniform*` calls. Flags are set when GX state changes and cleared after upload. Reduces GL call overhead by ~12%.

### Widescreen (3-state system)

Controlled by `g_pc_widescreen_stretch`:
- **0 (hor+)**: full-window viewport, FOV-corrected projection. Default, resets each frame.
- **1 (stretch)**: full-window, no correction. For fullscreen transitions/inventory backgrounds.
- **2 (pillarbox)**: centered 4:3 viewport with black bars. For inventory UI alignment.

m_play.c inserts NOOPTag markers in POLY_OPA display lists to toggle between states. emu64 reads these during DL processing. Frustum culling bounds are widened for hor+ to prevent side-of-screen popping.

## Endianness

All ROM/ARAM data is big-endian. Multi-byte fields must be byte-swapped after loading.

Pattern: `#ifdef TARGET_PC` byte-swap block right after `_JW_GetResourceAram` call.

Known swap sites:
- RARC archives (JKRAramArchive.cpp)
- FG data: 3 sites in m_field_make.c
- Messages: mMsg_Get_BodyParam
- Player palettes: m_player_lib.c
- Room wall/floor palettes: m_room_type.c
- N64Mtx s16 pairs: emu64_utility.c
- Scene_Word_u: m_scene.c
- Billboard matrices: sys_matrix.c (Matrix_MtxtoMtxF, suMtxMakeTS/SRT/SRT_ZXY)
- NPC clothing: ac_npc_cloth.c_inc (both DMA paths)
- Raw binary actables: 6 files swapped once at boot via mFM_InitActableEndian()
- Melody sequences: na_combo.c (u16 offsets)
- TLUT palettes: clock face, furniture, museum items (fd629a59)
- ADSR phase bitfield: stereo pan/reverb flags (d6e4b1ae)

**Cannot centralize**: ARAM data has mixed layouts (u8 textures, u16 palettes, u32 offsets). A bulk swap at the `_JW_GetResourceAram` layer would corrupt byte-level data.

**EFB-copied textures** are generated in little-endian format on PC, unlike ROM-sourced textures which are big-endian. Endianness fixes to texture decoders must account for both paths.

## Audio

jaudio_NES engine compiled and linked (59 source files, ~23K lines). SDL2 backend at 32kHz s16 stereo. rspsim software DSP processes ADPCM/RESAMP/ENVMIX.

All effects enabled: reverb, comb filter, Haas effect, Dolby surround.

### Threaded Architecture

Audio production runs on a dedicated SDL thread, matching the GC's `neosproc` thread model:

- **Game thread**: `Na_GameFrame()` queues audio commands via thread-safe message queues (SDL_mutex-protected `Z_osSendMesg`/`Z_osRecvMesg`)
- **Audio producer thread**: Loops calling `pc_audio_process_frame()` → `CreateAudioTask` → `RspStart2` (rspsim), writes samples into SPSC ring buffer (32768 samples = ~512ms)
- **SDL callback thread**: Reads from ring buffer → speakers

This decoupling prevents OS thread preemption of the game thread from causing audio dropouts. Frame pacing uses timer-based 60fps with spin-wait (no longer tied to audio buffer fill level).

### Known audio issue

Subtle bass distortion in specific rooms (museum dinosaur room). Present since early audio implementation. Root cause likely in A_CMD_UNK3 implementation accuracy (reverse-engineered from table data, no original microcode reference).

## Save System

GCI format only (64-byte CARDDir header + 0x72000 raw data). Bidirectional LE↔BE byte-swap for all ~300+ multi-byte fields.

- Save file: `save/DobutsunomoriP_MURA.gci`
- Also scans for Dolphin naming format (`8P-GAFE-...`)
- Backup rotation: up to 3 `.bak` files on each save
- Recovery: tries temp file, then backups if main save is missing
- Compatible with Dolphin emulator (can import/export saves)

## Enhancement Features

Compiled under `PC_ENHANCEMENTS` define (enabled by default in CMakeLists.txt).

### Settings (`settings.ini`)

```ini
[Graphics]
window_width = 1280
window_height = 720
fullscreen = 0          # 0=windowed, 1=fullscreen, 2=borderless
vsync = 0
msaa = 4                # 0/2/4/8
```

Auto-generated with defaults on first run. Resolution presets up to 4K supported. Custom resolutions can be set in the .ini file. DPI-aware on Windows (respects system scaling).

### HD Texture Packs

Drop Dolphin-compatible HD texture packs into `texture_pack/` directory. Uses XXHash64 for matching (identical algorithm to Dolphin). Supports DDS files with BC7, BC1, BC3, or uncompressed RGBA.

Filename format: `tex1_{W}x{H}_{hash}[_{tlut_hash}]_{fmt}.dds`

Wildcard palette support: `tex1_WxH_DATAHASH_$_FMT.dds` matches any palette variant.

### 4x MSAA

Anti-aliasing via multisampled framebuffer. Configurable in `settings.ini` (0/2/4/8 samples).

## LLM Dialogue System (`#ifdef PC_LLM_DIALOGUE`)

Replaces villager greeting text with LLM-generated responses in real time. The system hooks into the game's message window at page-load time, submits an async request, and applies the response when ready.

### Message System Architecture

The message window (`mMsg_Window_c`) is a singleton with 8 state machine states:

```
HIDE → APPEAR (18-frame zoom-in) → CURSOL (text crawl) → NORMAL (wait for A) → DISAPPEAR → HIDE
```

Messages are loaded from ROM by `msg_no` (0x0000–0x3F91). Each page ends with a control code:

| Code | Meaning |
|------|---------|
| `0x7F 0x00` | `LAST` — dialogue ends on A press |
| `0x7F 0x01` | `CONTINUE` — advances to `continue_msg_no` on A press |
| `0x7F 0x5B XX` | `MSG_TIME_END` — timed auto-advance |

Key structs:

| Field | Purpose |
|-------|---------|
| `mMsg_Window_c.continue_msg_no` | Next msg_no to load when page advances. Set by `SET_NEXT_MESSAGE_*` control codes during CURSOL. Defaults to -1. |
| `mMsg_Window_c.continue_cancel_flag` | If TRUE, `CONTINUE` behaves like `LAST` (disappears). |
| `mMsg_Window_c.lock_continue` | Blocks A button advancement in NORMAL state. |
| `mMsg_Window_c.client_actor_p` | The NPC speaking. |
| `mMsg_Window_c.choice_window` | Embedded `mChoice_c` — choice UI with up to 6 option strings. |
| `mMsg_Data_c.msg_no` | Current message index. |
| `mMsg_Data_c.msg_len` | Byte count of the active message page. |
| `mMsg_Data_c.text_buf` | 1600-byte buffer holding raw game-font-encoded message + control codes. |

### Dialogue Sequence Types

**Type 1: Simple greeting (LAST)**
```
Page 1: "Hey Pluto! Nice weather." [0x7F 0x00 LAST]
A press → DISAPPEAR → HIDE. NPC exits talk state.
```

**Type 2: Greeting with embedded choices (CONTINUE)**
```
Page 1: "What do you need?" [0x7F 0x18 ...choice IDs... 0x7F 0x0D SET_SELECT_WINDOW] [0x7F 0x01]
  Control codes in the text buffer:
    SET_SELECT_STRING_2/3/4 → loads 2–4 choice strings by ROM string ID
    SET_NEXT_MESSAGE_0..3   → wires each choice index to a response msg_no
    SET_SELECT_WINDOW        → activates choice UI overlay
A press → choice window opens → player picks → ChangeMsgData(chosen msg_no) → Page 2
Page 2: Response to chosen option [0x7F 0x00 LAST]
```

**Type 3: Multi-page CONTINUE chain**
```
Page 1 → [0x7F 0x01] → Page 2 → [0x7F 0x01] → Page 3 → [0x7F 0x00 LAST]
```
Scripted talks (save-load greeting, cutscenes, NPC intros). Filtered out by hook — only player-initiated conversations reach the LLM.

**Type 4: Quest offer dialogue**
```
Page 1: Greeting with quest context [0x7F 0x01]
Page 2: Functional prompt "Will you help?" [len < 80] → skipped by gate
Page 3: Quest details [len varies, may or may not be replaced]
```

**Type 5: Functional messages (skipped)**
```
Pages with len < 80: "What do you need?", "Yes"/"No" prompts, quest dialog,
post-greeting choice text, determination strings.
```
Always skipped by the `FUNCTIONAL_MSG_MAX` gate.

### Where the LLM Hook Fires (Two Hook Points)

Both fire *before* CURSOL processes any control codes:

| Hook point | Location | When |
|------------|----------|------|
| `mMsg_MainSetup_Appear` (line 42) | `m_msg_appear.c_inc` | First page of every dialogue |
| `mMsg_ChangeMsgData` (line 386) | `m_msg_main.c_inc` | Every subsequent page advance |

Both guarded by `#ifdef PC_LLM_DIALOGUE`.

### Hook Guard Conditions

In order, each message page is tested:

1. `!llm_is_enabled()` — master toggle
2. Player not in `mPlayer_INDEX_TALK` — filters scripted talks (cutscenes, save-load greetings). Scripted talks use different player indexes.
3. No actor / non-villager NPC (`NAME_TYPE_NPC`) — filters special NPCs (shopkeepers, train station, museum).
4. `!msg_is_conversational_start()` — **principled classification** (see below). Replaces the old heuristic `stock_len < 80`. Uses `continue_msg_no == 0xFFFF` as the signal for a fresh conversation start — no `SET_NEXT_MESSAGE_*` code has ever fired.
5. Previous LLM job still in flight — prevents queue pile-up.

### Message Classification: Greeting vs. Functional

The old `stock_len < 80` gate caught functional messages by accident (they happen to be short). The principled approach uses the message window's `continue_msg_no` field, which encodes whether this page was reached via a choice/scripted transition.

#### Classification Signals Available at Hook Time

| Signal | Location | At greeting start | At functional/choice follow-up |
|--------|----------|-------------------|-------------------------------|
| `continue_msg_no` | `msg_p->continue_msg_no` | `0xFFFF` (initial, never set) | valid msg_no (set by previous page's SET_NEXT_MESSAGE) |
| `determination_len` | `msg_p->choice_window.data.determination_len` | 0 | > 0 (player just picked a choice) |
| `choice_window.main_index` | `msg_p->choice_window.main_index` | `HIDE` (0) | may be `NORMAL` if choice window still visible |
| `SET_SELECT_WINDOW` in stock text | Scan `0x7F 0x0D` in `msg_data->text_buf.data` | Present if greeting has choices | Usually absent (choices consumed) |
| `SET_NEXT_MESSAGE_F/0-5` in stock text | Scan `0x7F 0x0E-0x14` | Present if greeting branches by choice | Usually absent |
| `SET_FORCE_NEXT` in stock text | Scan `0x7F 0x1C` | Absent | May be present (auto-advance) |
| `lock_continue` | `msg_p->lock_continue` | FALSE | TRUE if game is blocking input |
| `force_next` | `msg_p->force_next` | FALSE | TRUE if SET_FORCE_NEXT just fired |

#### Why `continue_msg_no == 0xFFFF` Works

`continue_msg_no` starts at `0xFFFF` (`m_msg_main.c_inc:458`). The only way it changes is when a `SET_NEXT_MESSAGE_*` control code (0x7F 0x0E-0x14) fires during CURSOL text processing, setting it to a real `msg_no`. This means:

- **`0xFFFF`**: No scripted transition has occurred. The player just pressed A near an NPC. This is a conversational greeting page.
- **Valid msg_no (≥0, <MSG_MAX)**: A previous page's CURSOL processed `SET_NEXT_MESSAGE_*` and the player pressed A on CONTINUE. This page was reached via a choice or scripted transition — it's a functional follow-up.
- **`-1`**: A `SET_NEXT_MESSAGE` was consumed (`m_msg_normal.c_inc:64` resets after `ChangeMsgData` returns — after our hook fires).

The hook fires inside `mMsg_ChangeMsgData` (second hook point), **before** the `-1` reset. So `continue_msg_no` still holds the value that triggered this page load. At the first hook point (`mMsg_MainSetup_Appear`), no CURSOL has run yet, so it's still `0xFFFF`.

#### Classification Logic

```c
static int msg_is_conversational_start(mMsg_Window_c *msg_p) {
    /* 0xFFFF: fresh conversation, no SET_NEXT_MESSAGE fired yet */
    if (msg_p->continue_msg_no != 0xFFFF) return 0;
    /* Determination set: player just picked a choice */
    if (msg_p->choice_window.data.determination_len > 0) return 0;
    return 1;
}
```

A greeting with embedded choices (Type 2) still passes this check — `continue_msg_no` is `0xFFFF` because no CURSOL has run yet to set it, and `determination_len` is 0 because no choice has been selected yet. The choice strings are still extracted via `msg_extract_choices()`.

### Stuck-Dialogue Bug (Fixed)

**Root cause**: The LLM replacement text ("...") contains zero control codes. When the stock message had `CONTINUE` (0x7F 0x01) as its end code, the old code preserved it. But `continue_msg_no` was never set by any `SET_NEXT_MESSAGE_*` code (our "..." has none), so it stays -1.

In `m_msg_normal.c_inc:53-65`, when the player presses A:
```c
if (CONTINUE && !cancel_flag) {
    if (continue_msg_no is valid) → load next page
    // else: no fall-through. Nothing happens. Stuck.
}
```

**Fix**: Always write `mFont_CONT_CODE_LAST` (0x7F 0x00) for LLM-replaced text. The `mPlayer_INDEX_TALK` guard already filters scripted multi-page talks; for player-initiated conversations, `LAST` is always safe. The NPC's `talk_end_check_proc()` sees the window disappear and exits cleanly.

### Choice Detection

`msg_extract_choices()` in `pc/src/llm/llm_hook.c` scans the stock text buffer for:

| Control code | Opcode | Purpose |
|-------------|--------|---------|
| `0x7F 0x0D` | `SET_SELECT_WINDOW` | Marks message as having player choices |
| `0x7F 0x18` | `SET_SELECT_STRING_2` | 2 choice strings, 4 bytes of 16-bit ROM IDs |
| `0x7F 0x19` | `SET_SELECT_STRING_3` | 3 choice strings, 6 bytes of IDs |
| `0x7F 0x1A` | `SET_SELECT_STRING_4` | 4 choice strings, 8 bytes of IDs |

String IDs are resolved to game-font text via `mChoice_Load_ChoseStringFromRom()`, decoded to ASCII with `decode_game_str()`, and appended to the prompt as `[Player response options: option1, option2, ...]`. This gives the LLM context about what the player will choose from.

### Game Font Encoding

Bytes `0x20–0x7E` are ASCII 1:1 (established in `pc/src/pc_typing.c:40-51`). Kana (`0x80–0xCC`) and control codes (`0x7F` prefix, `0x00–0x7E` operands) are not ASCII-mappable. The `decode_game_str()` helper maps everything outside `0x20–0x7E` to space and trims trailing spaces.

### Prompt Builder

`llm_build_prompt()` in `pc/src/llm/llm_prompt.c` assembles the full LLM context from:

```
System prompt: "You are {name}, a {persona_desc[looks]} villager in Animal Crossing.
Your catchphrase is "{catchphrase}". You live in {town}.
It is {season}. The weather is {weather}. It is {time_of_day}.
Speak as this character. Reply in 1-3 short sentences.
Never break character. Use your catchphrase occasionally."

Conversation history: (per-NPC ring buffer, last N exchanges)
Gossip: (rumors from other villagers)
Player input: "{player_name} says: {stock_text}\n\nResponse:"
```

Personality descriptions map `mNpc_LOOKS_*` indices:
| Index | Type | Description |
|-------|------|-------------|
| 0 | Normal (female) | cheerful and kind, loves flowers and baking |
| 1 | Peppy (female) | bubbly and energetic, uses exclamation marks |
| 2 | Lazy (male) | loves food, naps, and talking about bugs |
| 3 | Jock (male) | athletic and competitive, references exercise |
| 4 | Cranky (male) | grumpy but secretly caring, complains fondly |
| 5 | Snooty (female) | cares about fashion and status, gossips but means well |

History and gossip are wired in the builder signature but not yet plumbed from the hook (passed as NULL/0).

### Async Job Flow

```
llm_hook_on_msg_change()
  → Decode game strings, build prompt via llm_build_prompt()
  → Save stock text to g_stock_text, g_stock_len
  → Write "..." + LAST into text_buf.data
  → llm_submit_job() → background thread → HTTP request

llm_hook_tick() (every frame)
  → llm_tick_jobs() → checks if response arrived

llm_hook_apply_response()
  → Stale guard: msg_no must still match
  → Word-wrap LLM text to 4 lines, 176 units wide
  → Write into text_buf.data + LAST end code

llm_hook_on_job_failed()
  → Restore original g_stock_text (game-encoded, exact length)
```

### File Reference

| File | Purpose |
|------|---------|
| `pc/src/llm/llm_hook.c` | Dialogue interception: hook points, text encode/decode, choice extraction, async job submission |
| `pc/src/llm/llm_prompt.c` | Prompt builder: system prompt, persona table, history, gossip, player input |
| `pc/src/llm/llm_core.c` | LLM backend: provider init, HTTP/TLS, job queue, ollama/openai/gemini/deepseek |
| `pc/src/llm/llm_gossip.c` | Background gossip generation between NPCs |
| `pc/src/llm/llm_config.c` | llm.ini config parser |
| `pc/include/llm/llm_api.h` | Public API declarations |
| `pc/include/llm/llm_types.h` | LlmJob, LlmHistory, LlmConfig, LlmProvider structs |

Key game files:

| File | Role |
|------|------|
| `src/game/m_msg_main.c_inc` | Message loading, `ChangeMsgData`, control code detection |
| `src/game/m_msg_cursol.c_inc` | Text crawl, all ~110 control code handlers, choice wiring |
| `src/game/m_msg_normal.c_inc` | Page advancement logic, CONTINUE/LAST handling |
| `src/game/m_msg_appear.c_inc` | Initial message load, first LLM hook point |
| `src/actor/npc/ac_npc_act_talk.c_inc` | NPC talk action state machine |
| `src/actor/npc/ac_npc_talk.c_inc` | NPC talk trigger, setup/end |
| `src/game/m_player_main_talk.c_inc` | Player talk state (`mPlayer_INDEX_TALK`) |

### Implementation Roadmap

Ordered by dependency — each phase builds on the previous.

#### Phase 1: Principled Message Classification (next)

Replace the heuristic `stock_len < 80` gate with `msg_is_conversational_start()` using `continue_msg_no == 0xFFFF`. This correctly identifies greeting pages vs. choice/scripted follow-ups by checking whether `SET_NEXT_MESSAGE_*` codes have ever fired.

**Files changed**: `pc/src/llm/llm_hook.c`
- Add `msg_is_conversational_start()` — checks `msg_p->continue_msg_no` and `msg_p->choice_window.data.determination_len`
- Remove `FUNCTIONAL_MSG_MAX` gate, call `msg_is_conversational_start()` instead
- `msg_p` is already the second parameter to our hook — no signature changes needed

**Dialogue type impact**:
| Type | Old gate | New gate | Result |
|------|---------|---------|--------|
| 1. Simple greeting | `len ≥ 80` passes | `continue_msg_no == 0xFFFF` passes | Same — LLM'd |
| 2. Greeting + choices | `len ≥ 80` passes | `continue_msg_no == 0xFFFF` passes | Same — LLM'd with choice context |
| 3. Choice prompt page | `len < 80` skips | `continue_msg_no` is valid msg_no (was set by greeting's SET_NEXT_MESSAGE) → skips | Same — skipped, now principled |
| 4. Response-to-choice page | sometimes passes (len ≥ 80) | `continue_msg_no` is valid msg_no → skips | **Fixed** — no more LLM on choice responses |
| 5. Quest offer follow-up | `len < 80` skips | `continue_msg_no` is valid → skips | Same — skipped, now principled |
| 6. Mid-conversation greeting from a different NPC | N/A | Each NPC's conversation window is independent; first page still has `0xFFFF` | Works correctly |

#### Phase 2: Post-Choice Response Context

When a greeting has choices and the player picks one, the response page currently passes as a greeting (since `continue_msg_no` was set). Phase 1 correctly skips it, but we lose the opportunity to LLM the response. Phase 2 adds: capture which choice was selected, pass it as context to the NEXT hook call.

**Files changed**: `pc/src/llm/llm_hook.c`, possibly `pc/include/llm/llm_types.h`
- Add `g_last_chosen_text[64]` — stores the decoded text of the selected choice
- In `llm_hook_on_msg_change`: if `determination_len > 0`, decode the determination string
- Pass as `stock_text` append: `[Player chose: "{g_last_chosen_text}"]`
- Clear after one use

**Hook point**: Same — `llm_hook_on_msg_change` fires on the response page (which reaches `mMsg_ChangeMsgData` via `SET_NEXT_MESSAGE`). We know the player's choice because `determination_len > 0` and the determination string is in the choice window.

#### Phase 3: Conversation History

Plumb the `LlmHistory` ring buffer through the hook. Track per-NPC conversation exchanges across talk sessions.

**Files changed**: `pc/src/llm/llm_hook.c`, `pc/src/llm/llm_prompt.c`
- On conversation end (`llm_hook_on_conversation_end`): append the exchange to `g_llm_history[npc_idx]`
- On conversation start: pass `&g_llm_history[npc_idx]` instead of NULL to `llm_build_prompt`
- `llm_build_prompt` already walks the ring buffer and formats recent exchanges
- Clear history when the NPC moves out (handled by existing `llm_history_clear`)

**Dialogue type impact**:
| Type | Without history | With history |
|------|----------------|--------------|
| Repeat greeting | Generates generic hello | References previous conversation: "You're back! Still looking for butterflies?" |
| Post-choice | Empty context | References what was just said |
| Multi-NPC | Isolated per NPC | Each NPC has independent memory |

#### Phase 4: Gossip Integration

Wire the gossip system into the prompt. Background `llm_gossip_tick()` generates rumors between NPCs. Pass them to `llm_build_prompt`.

**Files changed**: `pc/src/llm/llm_hook.c`, `pc/src/llm/llm_gossip.c`
- In `llm_hook_on_msg_change`: pass `g_llm_history` array + gossip pointers instead of NULL
- Gossip system already populates per-NPC `LlmHistory` entries with `gossip_seed` and `gossip_id`
- Prompt builder already renders gossip as "Rumors you've heard in town: ..."

#### Phase 5: Multi-Turn Conversations

Instead of ending the conversation after one LLM response (LAST), keep it going for 2-3 exchanges. The LLM response page triggers another page automatically.

**Files changed**: `pc/src/llm/llm_hook.c`, `pc/src/llm/llm_prompt.c`
- Detect when the LLM response naturally prompts a reply question
- Use `SET_NEXT_MESSAGE_F` with a dummy msg_no to trigger a second hook → second LLM call
- Or: pre-generate 2-3 pages of text, write them as sequential pages via CONTINUE

**Complexity**: High. Requires managing `continue_msg_no` explicitly and handling the script chain.

#### Phase 6: Mood & Emotion System

Use the `mood` field (currently captured but `(void)` in the builder) to influence LLM tone and NPC animation.

**Files changed**: `pc/src/llm/llm_prompt.c`, `pc/src/llm/llm_hook.c`
- Add mood to system prompt: "You are feeling {happy/sad/angry/neutral} today."
- Parse LLM response for emotion tags, trigger appropriate NPC demo orders

#### Phase 7: Quest-Aware Dialogue

Detect quest offer dialogues and include quest details in prompt context.

**Files changed**: `pc/src/llm/llm_hook.c`
- Check `QUEST_MANAGER_ACTOR.talk_type` for `aQMgr_TALK_KIND_QUEST`
- If quest mode: extract quest text, item names, pass to prompt
- The quest manager's `msg_start[]` array has message IDs for quest states


## Input

Keyboard mapping:
- **WASD** = analog stick
- **Arrow keys** = C-stick
- **Space** = A, **LShift** = B, **Enter** = Start
- **IJKL** = D-pad
- **Q/E** = L/R triggers, **Z** = Z trigger
- **F3** = toggle frame limiter
- **ESC** = quit

SDL2 gamepad with hotplug, analog sticks (deadzone 500), triggers, D-pad, and rumble.

PADRead returns GC button format. Conversion to N64 format happens in `padmgr_UpdatePC()`.

## Fault Handling

The PC port does not install a VEH/signal crash recovery handler. Faults are allowed to propagate to the OS/debugger.
Actor profile validation remains in `m_actor.c` to skip NULL/invalid profiles before dispatch.

## Build System

32-bit MinGW GCC 15.x (i686) + CMake + SDL2 2.30.10 + GLAD2 (GL 3.3 Core).

**Must compile as 32-bit** — decomp code casts pointers to u32 everywhere.

### Quick Start

```bash
# 1. Place disc image in pc/build32/bin/rom/
# 2. Build (from MSYS2 MINGW32 shell):
./build_pc.sh

# 3. Run:
pc/build32/bin/AnimalCrossing.exe --verbose
```

`build_pc.sh` handles CMake configuration and build in one step.

### Cross-Compilation

| Toolchain | File | Target |
|-----------|------|--------|
| Linux i686 | `pc/cmake/Toolchain-linux32.cmake` | Native Linux 32-bit |
| MinGW from Linux | `pc/cmake/Toolchain-mingw32.cmake` | Windows 32-bit cross-compile |

### CLI Flags

| Flag | Effect |
|------|--------|
| `--verbose` / `-v` | Enable diagnostic output |
| `--no-framelimit` | Disable the frame limiter |
| `--model-viewer [N]` | Launch model viewer (optional start index) |
| `--time HOUR` | Override in-game hour (0-23) |
| `--help` / `-h` | Show help |

## Platform Support

| Platform | Status |
|----------|--------|
| Windows (MinGW i686) | Primary target, fully tested |
| Linux (i686) | Compiles and links, mmap arena |

Linux support uses POSIX equivalents: `mmap()` instead of `VirtualAlloc()`, `mkdir()` guards for directory creation.

## Common Pitfalls

- **32-bit required**: 64-bit builds crash in JKRHeap (pointer→u32 casts).
- **`__attribute__((weak))`** doesn't work on MinGW/PE. Use regular definitions.
- **libc64/malloc.c** is excluded — it redefines system malloc and crashes the CRT.
- **NDEBUG must always be defined**: decomp asserts have side effects. Without NDEBUG, assert macros run and cause texture corruption.
- **Optimization must be -O0**: any optimization (-O1+) exposes UB in decomp code (infinite spawn loops, crashes).
- **windows.h macros**: always `#undef near` / `#undef far` after including.
- **GC address space**: emu64 uses 0x80000000-0x83000000 range. Guard with TARGET_PC.
- **glClear respects write masks**: must set glDepthMask(GL_TRUE) + glColorMask(all TRUE) before glClear.
- **seg2k0 collision**: PC heap pointers can collide with N64 segment addresses. Fixed with proximity heuristic + VirtualAlloc/mmap arena at >=0x10000000.
- **`#included .c` files**: emu64_utility.c, emu64_print.cpp, jsyswrapper_ext.cpp, jsyswrapper_main.cpp, ac_animal_logo_misc.c, m_item_debug.c, ac_npc_shop_common.c — these are compiled as part of their parent file, not standalone.
- **Title demo OOB**: `demo_npc_list` has 14 valid entries but `mNpc_SetAnimalTitleDemo` loops 15 times. On GC, the garbage 15th read was benign; on PC it produced invalid NPC `looks` → OOB crash in wander logic. Fixed with sentinel entry, slot clearing, and looks clamp.
- **EFB-copied textures are LE**: ROM textures are BE, but EFB copies are generated in LE on PC. Texture decoder endianness fixes must not break EFB copies.
