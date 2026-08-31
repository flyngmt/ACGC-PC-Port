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

## Building from Source

Only needed if you want to modify the code. Otherwise, use the [pre-built release](https://github.com/flyngmt/ACGC-PC-Port/releases) above.

### Windows Instructions:

#### Requirements

- **MSYS2** (https://www.msys2.org/)
- **Animal Crossing (USA) disc image** (ISO, GCM, or CISO format)

#### MSYS2 Packages

Open **MSYS2 MINGW32** from your Start menu and install:

```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-cmake mingw-w64-i686-SDL2 mingw-w64-i686-make
```

#### Build Steps

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

### Linux Cross Compile Instructions
#### Requirements

- **Animal Crossing (USA) disc image** (ISO, GCM, or CISO format)

- **And the repo:**
   ```bash
   git clone https://github.com/flyngmt/ACGC-PC-Port.git
   cd ACGC-PC-Port
   ```
   
   **AND**
#### Packages
You need to use Mingw GCC 15.2 (newer versions seem to introduce a graphical regression) and you need some other older packages as well. If you cross compile from some other systems you may be fine using the existing mingw toolchain, but if you can't you will need to build a separate environment. To build an environment for compiling and building the program follow these instructions:

Download from the Arch Linux Archive, and extract each .pkg.tar.zst into ExternalResources/toolchains/mingw-w64-15.2/ so the tree looks like ExternalResources/toolchains/mingw-w64-15.2/usr/{bin,lib,i686-w64-mingw32,...}:
   [Mingw w64 gcc 15.2](https://archive.archlinux.org/packages/m/mingw-w64-gcc/mingw-w64-gcc-15.2.0-1-x86_64.pkg.tar.zst) ,
   [Mingw w64 binutils 2.45](https://archive.archlinux.org/packages/m/mingw-w64-binutils/mingw-w64-binutils-2.45-1-x86_64.pkg.tar.zst) ,
   [Mingw w64 crt 14](https://archive.archlinux.org/packages/m/mingw-w64-crt/mingw-w64-crt-14.0.0-1-any.pkg.tar.zst) ,
   [Mingw w64 headers 14](https://archive.archlinux.org/packages/m/mingw-w64-headers/mingw-w64-headers-14.0.0-1-any.pkg.tar.zst) , 
   [Mingw w64 winpthreads 14](https://archive.archlinux.org/packages/m/mingw-w64-winpthreads/mingw-w64-winpthreads-14.0.0-1-any.pkg.tar.zst)
   
#### Build Steps

1. Make sure youve got all the required packages

2. Run the correct toolchain in pc/cmake/*
   ```bash
   cmake -S pc -B pc/build_32 -march=pentium4 -DCMAKE_TOOLCHAIN_FILE="$(pwd)/pc/cmake/Toolchain-mingw32.cmake">
   ```
   Then
   ```bash
   cmake --build pc/build_32 -j"$(nproc)"
   ```
   if you have the right packages installed **OR**
   ``` 
   cmake -S pc -B pc/build_32 -march=pentium4  -DCMAKE_TOOLCHAIN_FILE="$(pwd)/pc/cmake/Toolchain-mingw32-gcc152.cmake"
   ```
   Then
   ```
   cmake --build pc/build_32 -j"$(nproc)"
   ```
   if you made a separate environment for compilation packages in ExternalResources.

4. Place your image in the rom folder.

5. Launch the game .exe through a recent version of wine or proton.
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

## Credits

This project would not be possible without the work of the [ACreTeam](https://github.com/ACreTeam) decompilation team. Their complete C decompilation of Animal Crossing is the foundation this port is built on.

## AI Notice

AI tools such as Claude were used in this project (PC port code only).

## FAQ

See [FAQ](FAQ.md) for more info.
