# Toolchain: mingw-w64 GCC 15.2.0 (i686) — the configuration that FIXES the
# character geometry "crunch" regression.
#
# WHY: GCC 16.x (and even era-matched Arch-cross GCC 15.2 with i386 codegen
# baseline) was ruled out empirically; the crunch root cause was base-asset
# data sourcing (see AGENTS.md "Crunch fix"). This toolchain replicates the
# known-good upstream v0.9.3 build environment (MSYS2-era GCC 15.2,
# --with-arch=pentium4 codegen baseline) and is used together with
# -march=pentium4 and the base-data guard fixes.
#
# SEARCH ORDER:
#   1. <repo>/ExternalResources/toolchains/mingw-w64-15.2/usr   (canonical)
#   2. ~/.local/mingw-w64-15.2/usr                              (legacy)
#

set(_TC_CANDIDATES
    "${CMAKE_CURRENT_LIST_DIR}/../../ExternalResources/toolchains/mingw-w64-15.2/usr"
    "$ENV{HOME}/.local/mingw-w64-15.2/usr"
)
set(_MINGW152_ROOT "")
foreach(_c ${_TC_CANDIDATES})
    if(EXISTS "${_c}/bin/i686-w64-mingw32-gcc")
        set(_MINGW152_ROOT "${_c}")
        break()
    endif()
endforeach()
if("${_MINGW152_ROOT}" STREQUAL "")
    message(FATAL_ERROR
        "GCC 15.2 mingw toolchain not found.\n"
        "Expected one of:\n"
        "  ${_TC_CANDIDATES}\n"
        "Restore it per the instructions at the top of this file.")
endif()

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_C_COMPILER   "${_MINGW152_ROOT}/bin/i686-w64-mingw32-gcc")
set(CMAKE_CXX_COMPILER "${_MINGW152_ROOT}/bin/i686-w64-mingw32-g++")
if(EXISTS "${_MINGW152_ROOT}/bin/i686-w64-mingw32-windres")
    set(CMAKE_RC_COMPILER "${_MINGW152_ROOT}/bin/i686-w64-mingw32-windres")
else()
    set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)
endif()

# extracted sysroot first; system mingw sysroot second (SDL2 headers/libs)
set(CMAKE_FIND_ROOT_PATH
    "${_MINGW152_ROOT}/i686-w64-mingw32"
    "/usr/i686-w64-mingw32")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
