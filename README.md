# Animal Crossing PC Port

A native PC port of Animal Crossing (GameCube) built on top of the [ac-decomp](https://github.com/ACreTeam/ac-decomp) decompilation project.

The game's original C code runs natively on x86, with a custom translation layer replacing the GameCube's GX graphics API with OpenGL 3.3.

This repository does not contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions: GAFE01_00: Rev 0 (USA)

## Quick Start (Pre-built Release)

Pre-built releases are available on the [Releases](https://github.com/flyngmt/ACGC-PC-Port/releases) page. No build tools required.

1. Download and extract the latest release zip
2. Place your disc image in the `rom/` folder
3. Run `AnimalCrossing.exe`

The game reads all assets directly from the disc image at startup. No extraction or preprocessing step is needed.

## Building from Source

Only needed if you want to modify the code. Otherwise, use the [pre-built release](https://github.com/flyngmt/ACGC-PC-Port/releases) above.

### Requirements

- **MSYS2** (https://www.msys2.org/)
- **Animal Crossing (USA) disc image** (ISO, GCM, or CISO format)

### MSYS2 Packages

Open **MSYS2 MINGW32** from your Start menu and install:

```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-cmake mingw-w64-i686-SDL2 mingw-w64-i686-make
```

### Build Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/flyngmt/ACGC-PC-Port.git
   cd ACGC-PC-Port
   ```

2. Build (from **MSYS2 MINGW32** shell):
   ```bash
   ./build_pc.sh
   ```

3. Place your disc image in the `rom/` folder:
   ```
   pc/build32/bin/rom/YourGame.ciso
   ```

4. Run:
   ```bash
   pc/build32/bin/AnimalCrossing.exe
   ```

### Linux

See the dedicated [Building on Linux Guide](BUILDING_ON_LINUX.md) for native Linux compilation.

## Controls

Keyboard bindings are customizable via `keybindings.ini` (next to the executable). Mouse buttons (Mouse1/Mouse2/Mouse3) can also be assigned.

### Keyboard (defaults)

| Key | Action |
|-----|--------|
| WASD | Move (left stick) |
| Arrow Keys | Camera (C-stick) |
| Space | A button |
| Left Shift | B button |
| Enter | Start |
| X | X button |
| Y | Y button |
| Q / E | L / R triggers |
| Z | Z trigger |
| I / J / K / L | D-pad (up/left/down/right) |

### Gamepad

SDL2 game controllers are supported with automatic hotplug detection. Button mapping follows the standard GameCube layout.

## Command Line Options

| Flag | Description |
|------|-------------|
| `--verbose` | Enable diagnostic logging |
| `--no-framelimit` | Disable frame limiter (unlocked FPS) |
| `--model-viewer [index]` | Launch debug model viewer (structures, NPCs, fish) |
| `--time HOUR` | Override in-game hour (0-23) |

## Settings

Graphics settings are stored in `settings.ini` and can be edited manually or through the in-game options menu:

- Resolution (up to 4K)
- Fullscreen toggle
- VSync
- MSAA (anti-aliasing)
- Texture Loading/Caching (No need to enable if you aren't using a texture pack)

## Texture Packs

Custom textures can be placed in `texture_pack/`. Dolphin-compatible format (XXHash64, DDS).

I highly recommend the following texture pack from the talented artists of Animal Crossing community.

[HD Texture Pack](https://forums.dolphin-emu.org/Thread-animal-crossing-hd-texture-pack-version-23-feb-22nd-2026)

## Save Data

Save files are stored in `save/` using the standard GCI format, compatible with Dolphin emulator saves. Place a Dolphin GCI export in the save directory to import an existing save.

## LLM Dialogue Engine

Villagers can deliver AI-generated dialogue instead of stock text, with persistent memories, per-NPC sentiments, and configurable personality-driven topic selection.

### How It Works

- **Fresh conversations** have a configurable chance (`chat_chance` in `llm.ini`) of being replaced by LLM-generated text
- **Personality-aware**: each villager type (cheerful, peppy, lazy, jock, cranky, snooty) gets a custom persona in the prompt
- **Topic distribution**: configurable split between hobbies, relationships with other villagers, and small talk
- **Persistent memory**: all LLM responses are saved to `memory/<NPC>.txt` and occasionally injected back into prompts for continuity
- **Sentiment tracking**: villagers develop persistent likes/dislikes toward other residents, stored in `memory/<NPC>_sent.txt`
- **Real town residents**: the system gathers actual villagers and special NPCs (Tom Nook, Mayor) from your save data for authentic relationship seeding

### Configuration

On first run, `llm.ini` is auto-generated next to the binary with all defaults. Supported providers: `ollama` (local), `gemini`, `openai` (OpenCode Zen compatible), `deepseek`.

| Key | Default | Description |
|-----|---------|-------------|
| `provider` | `ollama` | LLM backend (`ollama`, `gemini`, `openai`, `deepseek`) |
| `endpoint` | *(depends)* | API endpoint URL (Optional/ignored for `gemini` integration) |
| `api_key` | *(empty)* | API authorization key |
| `model` | *(depends)* | LLM model name |
| `timeout_ms` | `3000` | Connection timeout in milliseconds (Raise to `10000`+ for slower/free models) |
| `enabled` | `1` | Master toggle |
| `chat_chance` | `20` | % chance LLM replaces a greeting |
| `topic_hobbies_pct` | `50` | % chance of hobby/interest topics |
| `topic_relations_pct` | `20` | % chance of talking about other villagers |
| `topic_smalltalk_pct` | `30` | % chance of casual small talk |
| `memory_influence_pct` | `25` | % chance past memories are injected |
| `prompt_extra` | *(empty)* | Extra text appended to every LLM prompt |

The LLM falls back gracefully to stock dialogue on failure — the game never breaks.

### Full Reference

See `pc/DOCUMENTATION.md` for the complete dialogue system architecture, message state machine, control code reference, and implementation roadmap.

## Credits

This project would not be possible without the work of the [ACreTeam](https://github.com/ACreTeam) decompilation team. Their complete C decompilation of Animal Crossing is the foundation this port is built on.

## AI Notice

AI tools such as Claude were used in this project (PC port code only).

## FAQ

See [FAQ](FAQ.md) for more info.
