# Animal Crossing PC Port

A native PC port of Animal Crossing (GameCube), based on the
[ac-decomp](https://github.com/ACreTeam/ac-decomp) decompilation. The original
game code runs natively while [Aurora](https://github.com/dolphin-emu/aurora)
provides the host window/event loop, WebGPU GX renderer, DVD, memory-card,
input, audio, and other GameCube SDK services.

This repository contains no game assets. A legally obtained GAFE01 Rev 0 (USA)
disc image is required; RVZ, ISO, and GCM images are accepted.

## Building and running

Install CMake 3.25 or newer, Ninja, a C/C++20 compiler, and the platform
dependencies required by Aurora. Clone the repository with its submodules,
then configure and build one of the included presets:

```sh
git clone --recurse-submodules https://github.com/flyngmt/ACGC-PC-Port.git
cd ACGC-PC-Port
cmake --preset debug
cmake --build --preset debug
./build/aurora/debug/bin/AnimalCrossing --disc /path/to/game.rvz
```

Use the `relwithdebinfo` preset in both CMake commands for an optimized build
with debug information. The game reads its assets directly from the disc image;
no extraction step is required.

## Controls

Aurora persists controller and keyboard mappings. When no active keyboard
mapping exists for port 0, the port imports a legacy `keybindings.ini` when
present, otherwise it installs these defaults:

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

SDL3 game controllers are supported through Aurora, including hotplug and
persisted mappings.

Press Escape on a keyboard, Back/Select on a controller, or R + Start to open
the Aurora-native host menu. A/B confirm and cancel, the D-pad or left stick
navigates, and L/R changes tabs. The menu pauses gameplay, exposes live video,
audio, gameplay, and dead-zone settings, and includes controller remapping for
all four ports. F1 remains reserved for the optional ImGui diagnostics.

## Command Line Options

| Flag | Description |
|------|-------------|
| `--disc PATH` | Open an RVZ, ISO, or GCM image; defaults to `game.rvz` |
| `--window-size WxH` | Set the initial window size |
| `--widescreen` | Start at 1280x720 instead of 4:3 |
| `--profile [N]` | Show performance diagnostics |
| `--model-viewer [index]` | Launch the model viewer at an optional structure index |
| `--framelimit N` | Set a software frame limit; 0 is uncapped |
| `--no-framelimit` | Run uncapped |
| `--time H[:M[:S]]` | Override the in-game clock |
| `--date M/D[/Y]` | Override the in-game date |
| `--rain [intensity]` | Force light, normal, or heavy rain |
| `--verbose`, `-v` | Enable additional game diagnostics and debug logging |
| `--log-level LEVEL` | Select `debug`, `info`, `warning`, or `error` |
| `--log-dir PATH` | Override the rotating log-file directory |
| `--user-dir PATH` | Override the directory used for configuration, mappings, saves, and logs |

Run `AnimalCrossing --help` for the authoritative option list. Logging defaults
to a rotating `logs` directory below Aurora's per-user Animal Crossing data
directory, with ten files and a combined 100 MiB retention limit.

Host settings are persisted in `config.json` under that same user directory.
On first launch, an existing `settings.ini` and `keybindings.ini` are imported;
canonical JSON and Aurora input mappings take precedence thereafter.

## Current migration status

RVZ boot, memory-card saves, audio, persisted host settings, legacy settings and
input migration, keyboard/controller input and remapping, the RmlUi host menu,
widescreen/live resize, frame limiting, model viewing, texture replacement,
and Aurora ImGui diagnostics are active. The old
SDL2/OpenGL backend has been removed.

Dolphin-format DDS and PNG texture packs remain drop-in compatible. Place the
pack's existing directory tree beneath `texture_pack/` in the working directory
(for example, `texture_pack/GAF/`). Aurora indexes replacement filenames
recursively at startup, loads image data on demand, and can re-index the folder
from Settings > Video > Texture Pack. Legacy texture preload/cache settings are
accepted for configuration compatibility; Aurora owns the replacement cache.

Embedded NES games use the retained fixNES emulation/audio core and a cached
Aurora GX linear-RGBA8 presenter. The Gameplay setting selects 4:3 pillarboxing
or window stretch.

## Save Data

Save files use Aurora's per-user card storage and the standard GCI-compatible
format. Embedded NES common data is stored beside the active card slot as
`DobutsunomoriP_F_SAVE.sav`, with atomic replacement and one `.bak1` fallback.

## Credits

This project would not be possible without the work of the [ACreTeam](https://github.com/ACreTeam) decompilation team. Their complete C decompilation of Animal Crossing is the foundation this port is built on.

## FAQ

See [FAQ](FAQ.md) for more info.
