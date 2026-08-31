#!/bin/bash
# buildwin_gcc152.sh - Build the Windows (MINGW32) port with the KNOWN-GOOD
# configuration that fixes the character geometry "crunch" regression.
#
# This is the configuration documented in AGENTS.md ("Crunch fix"):
#   * GCC 15.2.0 cross-toolchain  (ExternalResources/toolchains/mingw-w64-15.2)
#   * -march=pentium4 codegen baseline (matches MSYS2-era upstream builds)
#   * base-asset guard + Yaz0 decode fix + embedded orig/GAFE01_00 base data
#
# Usage:   ./buildwin_gcc152.sh
# Output:  pc/build_mingw_gcc152_p4/bin/AnimalCrossing.exe
#
# Runtime: copy that whole bin/ folder; put a BASE GAFE01 disc (and optionally
# the Deluxe GADEXX disc) in bin/rom/. bin/orig/GAFE01_00/ is embedded base
# data used whenever no base disc is reachable.

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/pc/build_mingw_gcc152_p4"
TOOLCHAIN="$SCRIPT_DIR/pc/cmake/Toolchain-mingw32-gcc152.cmake"

if [ ! -f "$SCRIPT_DIR/ExternalResources/toolchains/mingw-w64-15.2/usr/bin/i686-w64-mingw32-gcc" ] \
   && [ ! -f "$HOME/.local/mingw-w64-15.2/usr/bin/i686-w64-mingw32-gcc" ]; then
    echo "ERROR: GCC 15.2 toolchain missing — see pc/cmake/Toolchain-mingw32-gcc152.cmake"
    echo "header for restore instructions."
    exit 1
fi

# --- CMake configure ---
if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
    echo "=== Configuring CMake (GCC 15.2 + pentium4) ==="
    cmake -S "$SCRIPT_DIR/pc" -B "$BUILD_DIR" \
        -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" \
        -DCMAKE_C_FLAGS="-march=pentium4" \
        -DCMAKE_CXX_FLAGS="-march=pentium4"
fi

# --- Build ---
echo "=== Building (crunch-fix configuration) ==="
cmake --build "$BUILD_DIR" -j"$(nproc)"

BIN_DIR="$BUILD_DIR/bin"
mkdir -p "$BIN_DIR/rom" "$BIN_DIR/save" "$BIN_DIR/texture_pack"

# --- Bundle runtime DLL + embedded base data (extracted from the base iso) ---
if [ -f /usr/i686-w64-mingw32/bin/SDL2.dll ]; then
    cp -f /usr/i686-w64-mingw32/bin/SDL2.dll "$BIN_DIR/SDL2.dll"
elif [ ! -f "$BIN_DIR/SDL2.dll" ]; then
    echo "WARNING: SDL2.dll not found — copy it next to AnimalCrossing.exe"
fi

if [ ! -f "$BIN_DIR/orig/GAFE01_00/files/foresta.rel.szs" ]; then
    ISO="$SCRIPT_DIR/orig/GAFE01_00/Animal Crossing (USA).iso"
    if [ -f "$ISO" ]; then
        echo "=== Extracting embedded base data (orig/GAFE01_00) ==="
        python3 "$SCRIPT_DIR/pc/tools/extract_base_data.py" "$ISO" "$BIN_DIR/orig/GAFE01_00"
    else
        echo "WARNING: base iso not found at '$ISO' —"
        echo "  without bin/orig/GAFE01_00/ AND a base disc, the game cannot boot."
    fi
fi

echo ""
echo "=== Build complete: $BIN_DIR/AnimalCrossing.exe ==="
echo "Place base (GAFE01) disc in $BIN_DIR/rom/ ; Deluxe (GADEXX) disc optional."
