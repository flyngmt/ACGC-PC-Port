# Linux Build Guide

This port compiles and runs on 32-bit Linux via a native i686 toolchain.

## Requirements

- **Linux** (any modern distro — Ubuntu, Debian, Arch, Fedora)
- **GCC 32-bit toolchain** (i686)
- **CMake** (3.16+)
- **SDL2** (32-bit, with dev headers)
- **GLAD2** (bundled — no install needed)
- **Animal Crossing (USA) disc image** (ISO, GCM, or CISO format)
- **Wine** (optional — for running the Windows LLM providers)

## Install Dependencies

### Ubuntu / Debian

```bash
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc-14-i686-linux-gnu g++-14-i686-linux-gnu cmake \
                 libsdl2-dev:i386
```

### Arch Linux

```bash
# Enable multilib in /etc/pacman.conf, then:
sudo pacman -S gcc cmake lib32-sdl2
```

### Fedora

```bash
sudo dnf install gcc cmake glibc-devel.i686 libstdc++-devel.i686 \
                 SDL2-devel.i686
```

## Build

### Native multilib (`gcc -m32`)

On distros with multilib enabled (32-bit libs in `/usr/lib32`), no cross-toolchain
is needed:

```bash
cd pc

# Configure (only needed once)
cmake -B build32-linux -G "Unix Makefiles" \
      -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" \
      -DCMAKE_BUILD_TYPE=Debug

# Build (use -j for parallel jobs)
cmake --build build32-linux -j$(nproc)
```

### i686 cross-toolchain (`Toolchain-linux32.cmake`)

If you prefer a dedicated i686 cross compiler instead of native multilib:

```bash
cd pc

cmake -B build32-linux -G "Unix Makefiles" \
      -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-linux32.cmake \
      -DCMAKE_BUILD_TYPE=Debug

cmake --build build32-linux -j$(nproc)
```

Output: `build32-linux/bin/AnimalCrossing`

## Run

1. Place your disc image in `build32-linux/bin/rom/`
   ```bash
   mkdir -p build32-linux/bin/rom
   cp /path/to/your/disc.iso build32-linux/bin/rom/
   ```

2. Run the game:
   ```bash
   cd build32-linux/bin
   ./AnimalCrossing --verbose
   ```

3. On first run, `llm.ini` is auto-generated with defaults. Edit it to configure the LLM provider.

## CLI Flags

| Flag | Effect |
|------|--------|
| `--verbose` / `-v` | Enable diagnostic output |
| `--no-framelimit` | Disable 60fps cap |
| `--time HOUR` | Override in-game hour (0-23) |

## LLM Dialogue System

The LLM dialogue engine is compiled in by default (`PC_LLM_DIALOGUE` define in CMakeLists.txt), but **disabled at runtime** (`enabled = 0` in `llm.ini`) so the game runs exactly like stock until you opt in.

**Providers**: `ollama`, `openai` (OpenCode Zen compatible), `gemini`, `deepseek`

On first run, a default `llm.ini` is created next to the binary. Edit it to set `enabled = 1`, pick your provider, API key, and model.

To compile without the LLM engine entirely, configure with `-DPC_LLM_DIALOGUE=OFF`.

See `pc/DOCUMENTATION.md` for the full dialogue system reference.

## Cross-Compiling for Windows from Linux

```bash
cd pc

# Requires MinGW 32-bit toolchain (i686-w64-mingw32)
cmake -B build32-win -G "Unix Makefiles" \
      -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-mingw32.cmake \
      -DCMAKE_BUILD_TYPE=Debug

cmake --build build32-win -j$(nproc)
```

The Windows build can also be tested with Wine:
```bash
cd build32-win/bin
wine AnimalCrossing.exe --verbose
```

## 32-bit Note

**Must compile as 32-bit.** The decomp code casts pointers to `u32` everywhere. 64-bit builds will crash in JKRHeap.

## Troubleshooting

**`pc_platform.h` not found**: Ensure you're building from the `pc/` directory with CMake. The include paths are set up in `CMakeLists.txt`.

**Missing SDL2**: Install 32-bit SDL2 dev package. CMake will report the error.

**Disc image not found**: Place your `.iso`/`.gcm`/`.ciso` in `build32-linux/bin/rom/` or `orig/`. The loader scans both directories.

**LLM not working**: Check `llm.ini` exists and `enabled = 1` (it defaults to `0`). For Gemini, ensure `api_key` is set.
