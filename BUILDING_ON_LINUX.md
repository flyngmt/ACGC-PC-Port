# Building on Linux

This guide details how to build both the native 32-bit Linux version and the cross-compiled Windows version of the port from a Linux host machine.

---

## 1. Building the Native Linux Version

The native version runs as a 32-bit x86 ELF binary.

### Requirements & Package Installation

#### Ubuntu / Debian (Ubuntu 22.04 / 24.04+)
1. Enable 32-bit architecture support:
   ```bash
   sudo dpkg --add-architecture i386
   sudo apt update
   ```
2. Install the 32-bit compiler and library headers:
   ```bash
   sudo apt install gcc-multilib g++-multilib cmake libsdl2-dev:i386
   ```

#### Arch Linux
1. Enable the `[multilib]` repository in `/etc/pacman.conf`.
2. Install dependencies:
   ```bash
   sudo pacman -S gcc cmake lib32-sdl2
   ```

#### Fedora
Install the 32-bit development libraries:
```bash
sudo dnf install gcc gcc-c++ cmake glibc-devel.i686 libstdc++-devel.i686 SDL2-devel.i686
```

---

### Compilation Steps

1. Configure the build directory for multilib native compilation (forcing `-m32` targeting):
   ```bash
   cd pc
   cmake -B build32-linux -G "Unix Makefiles" \
         -DCMAKE_C_FLAGS="-m32" -DCMAKE_CXX_FLAGS="-m32" \
         -DCMAKE_BUILD_TYPE=Debug
   ```

2. Compile the binary:
   ```bash
   cmake --build build32-linux -j$(nproc)
   ```

The compiled binary will be placed at `pc/build32-linux/bin/AnimalCrossing`.

---

## 2. Cross-Compiling the Windows Version from Linux

You can compile a 32-bit Windows `.exe` directly from your Linux host using the MinGW-w64 cross-compiler.

### Requirements & Package Installation

#### Ubuntu / Debian
1. Install the MinGW compiler suite:
   ```bash
   sudo apt install mingw-w64
   ```
2. Install the MinGW SDL2 package or download pre-built MinGW libraries:
   * **Automatic (if available):**
     ```bash
     sudo apt install mingw-w64-i686-dev
     ```
   * **Manual (Recommended):** Download the standard MinGW development package from the [SDL2 Releases Page](https://github.com/libsdl-org/SDL/releases) (e.g., `SDL2-devel-2.xx.x-mingw.tar.gz`), extract it, and copy the `i686-w64-mingw32` files into your system cross-compiler path (typically `/usr/i686-w64-mingw32/`).

#### Arch Linux
Install MinGW and MinGW-SDL2 from the official repos / AUR:
```bash
sudo pacman -S mingw-w64-gcc mingw-w64-binutils
yay -S mingw-w64-sdl2
```

#### Fedora
Install MinGW cross-compiler and MinGW-SDL2 library packages:
```bash
sudo dnf install mingw32-gcc mingw32-gcc-c++ mingw32-binutils mingw32-SDL2
```

---

### Compilation Steps

1. Configure the build directory using the provided MinGW 32-bit toolchain configuration:
   ```bash
   cd pc
   cmake -B build32-win -G "Unix Makefiles" \
         -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-mingw32.cmake \
         -DCMAKE_BUILD_TYPE=Debug
   ```

2. Compile the binary:
   ```bash
   cmake --build build32-win -j$(nproc)
   ```

The compiled binary will be placed at `pc/build32-win/bin/AnimalCrossing.exe`.

---

## 3. Running the Game

To load assets, the game requires a game image.

1. Create a `rom/` folder in the same directory as the executable:
   * **Linux:** `pc/build32-linux/bin/rom/`
   * **Windows:** `pc/build32-win/bin/rom/`
2. Place a copy of your **Animal Crossing (USA) disc image** (`.iso`, `.gcm`, or `.ciso`) inside that `rom/` folder.
3. Run the executable:
   * **On Linux:**
     ```bash
     cd pc/build32-linux/bin
     ./AnimalCrossing --verbose
     ```
   * **On Windows (or via Wine on Linux):**
     ```bash
     cd pc/build32-win/bin
     wine AnimalCrossing.exe --verbose
     ```

---

## Troubleshooting

* **Must compile as 32-bit:** The decompiled code assumes 32-bit pointer sizes. A 64-bit target will fail at runtime.
* **Conflicting declarations for `fsqrt`:** If you encounter compiling errors with standard system header libraries regarding `fsqrt`, ensure you are building on the latest repository commit where the custom float functions have been renamed to `decomp_fsqrt` to prevent namespace collisions.
