# Animal Crossing PC Port

A native PC port of Animal Crossing (GameCube) built on top of the [ac-decomp](https://github.com/ACreTeam/ac-decomp) decompilation project.

The game's original C code runs natively on PC, with a custom translation layer replacing the GameCube's GX graphics API with OpenGL 3.3.

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

- **Animal Crossing (USA) disc image** (ISO, GCM, or CISO format)
- **CMake** 3.16+
- **SDL2** development libraries
- **GCC** (required on 64-bit platforms; Clang is supported on 32-bit only)

### Build Steps

### Windows (MSYS2)

1. Install **MSYS2** (https://www.msys2.org/)

2. Open **MSYS2 MINGW32** and install dependencies:
   ```bash
   pacman -S mingw-w64-i686-gcc mingw-w64-i686-cmake mingw-w64-i686-SDL2 mingw-w64-i686-make
   ```

3. Clone and build:
   ```bash
   git clone https://github.com/flyngmt/ACGC-PC-Port.git
   cd ACGC-PC-Port
   ./build_pc.sh
   ```

4. Place your disc image in `pc/build32/bin/rom/` and run:
   ```bash
   pc/build32/bin/AnimalCrossing.exe
   ```

### macOS (Apple Silicon & Intel)

1. Install dependencies:
   ```bash
   brew install gcc sdl2 cmake
   ```

2. Clone and build:
   ```bash
   git clone https://github.com/flyngmt/ACGC-PC-Port.git
   cd ACGC-PC-Port/pc
   mkdir build && cd build
   cmake .. -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15
   make -j$(sysctl -n hw.ncpu)
   ```
   > Adjust `gcc-15`/`g++-15` to match your installed GCC version (`ls /opt/homebrew/bin/gcc-*`).

3. Place your disc image in `build/bin/rom/` and run:
   ```bash
   build/bin/AnimalCrossing
   ```

### Linux (x86_64 / ARM64)

1. Install dependencies:
   ```bash
   # Arch/CachyOS/Manjaro
   sudo pacman -S gcc cmake sdl2

   # Debian/Ubuntu
   sudo apt install gcc g++ cmake libsdl2-dev

   # Fedora
   sudo dnf install gcc gcc-c++ cmake SDL2-devel
   ```

2. Clone and build:
   ```bash
   git clone https://github.com/flyngmt/ACGC-PC-Port.git
   cd ACGC-PC-Port/pc
   mkdir build && cd build
   cmake ..
   make -j$(nproc)
   ```

3. Place your disc image in `build/bin/rom/` and run:
   ```bash
   build/bin/AnimalCrossing
   ```

### Disc Image

The game reads all assets directly from the disc image at startup. No extraction or preprocessing step is needed. Place your disc image (`.iso`, `.gcm`, or `.ciso`) in the `rom/` folder next to the executable — the file can be named anything. The game also checks the `orig/` folder and the current directory.

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

Graphics settings are stored in `settings.ini` (next to the executable) and can be edited manually or through the in-game options menu:

- Resolution (up to 4K)
- Fullscreen toggle
- VSync
- MSAA (anti-aliasing)
- Texture Loading/Caching (No need to enable if you aren't using a texture pack)

## Texture Packs

Custom textures can be placed in the `texture_pack/` folder next to the executable. Dolphin-compatible format (XXHash64, DDS).

I highly recommend the following texture pack from the talented artists of Animal Crossing community.

[HD Texture Pack](https://forums.dolphin-emu.org/Thread-animal-crossing-hd-texture-pack-version-23-feb-22nd-2026)

## Save Data

Save files are stored in the `save/` folder next to the executable, using the standard GCI format. Compatible with Dolphin emulator saves — place a Dolphin GCI export in the save directory to import an existing save.

## Credits

This project would not be possible without the work of the [ACreTeam](https://github.com/ACreTeam) decompilation team. Their complete C decompilation of Animal Crossing is the foundation this port is built on.

## AI Notice

AI tools such as Claude were used in this project (PC port code only).
