cmake_minimum_required(VERSION 3.16)
project(ac_pc C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Do NOT set a default build type. Any optimization level (-O1, -O2) exposes
# undefined behavior in decomp code causing crashes. An empty build type gives
# GCC's default (-O0) which works correctly. The NDEBUG define below ensures
# asserts stay disabled regardless of build type.

# Options
option(PC_CONSOLE "Show console window (disables -mwindows, useful for debugging)" OFF)

# =============================================================================
# Platform info
# =============================================================================
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Building as 64-bit (pointer size = 8 bytes)")
else()
    message(STATUS "Building as 32-bit (pointer size = 4 bytes)")
endif()

# Allow mixed C/C++ linkage
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_EXTENSIONS ON)

# =============================================================================
# Compiler definitions
# =============================================================================
add_compile_definitions(
    TARGET_PC
    VERSION=0
    F3DEX_GBI_2
    NDEBUG
    BUGFIXES       # Fix original game bugs (buffer overflows, etc.) that crash on modern platforms
    _LANGUAGE_C    # Required for N64 GBI/ultratypes headers
    PC_ENHANCEMENTS   # Optional visual improvements (MSAA, etc). Remove to get pure PC port.
    KEYBOARD_TYPING   # Physical keyboard typing in text editor. Remove for platforms without keyboards.
)
if(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

# Common compiler flags (applied to all sources)
if(MSVC)
    add_compile_options(/W0)
else()
    add_compile_options(
        -fno-strict-aliasing
        -fwrapv
    )
endif()

# =============================================================================
# Include paths
# =============================================================================
set(DECOMP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

include_directories(
    ${DECOMP_ROOT}/include
    # NOTE: Do NOT add ${DECOMP_ROOT}/include/libc here!
    # Having both include/ and include/libc/ in the path breaks #include_next
    # chains in the decomp's shadow headers (e.g. libc/string.h). Without it,
    # #include "string.h" etc. resolve directly to system headers on PC.
    ${DECOMP_ROOT}/src
    # Project root needed for includes like "src/actor/npc/event/file.c_inc"
    ${DECOMP_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
    # .inc assets are loaded at runtime from disc image (no build/GAFE01_00 needed)
)

# =============================================================================
# Find SDL2
# =============================================================================
# Try system SDL2 first, then fall back to platform-specific locations
if(WIN32)
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/cmake" CACHE PATH "SDL2 cmake dir")
endif()
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    # Try pkg-config (works on both Linux and MSYS2)
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(SDL2 QUIET sdl2)
    endif()
endif()
if(NOT SDL2_FOUND)
    if(WIN32)
        # Windows-specific fallback paths
        # MSYS2 32-bit location
        set(SDL2_MSYS2_DIR "C:/msys64/mingw32")
        if(EXISTS "${SDL2_MSYS2_DIR}/include/SDL2/SDL.h")
            set(SDL2_FOUND TRUE)
            set(SDL2_INCLUDE_DIRS "${SDL2_MSYS2_DIR}/include/SDL2")
            set(SDL2_LIBRARIES "${SDL2_MSYS2_DIR}/lib/libSDL2.a")
        else()
            # Downloaded SDL2 MinGW dev package (32-bit)
            set(SDL2_DOWNLOAD_DIR "${DECOMP_ROOT}/../SDL2-2.30.10/i686-w64-mingw32")
            if(EXISTS "${SDL2_DOWNLOAD_DIR}/include/SDL2/SDL.h")
                set(SDL2_FOUND TRUE)
                set(SDL2_INCLUDE_DIRS "${SDL2_DOWNLOAD_DIR}/include/SDL2")
                set(SDL2_LIBRARIES "${SDL2_DOWNLOAD_DIR}/lib/libSDL2.a")
            else()
                # Last resort: vendored SDL2 in lib/
                set(SDL2_LOCAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
                if(EXISTS "${SDL2_LOCAL_DIR}/include/SDL.h")
                    set(SDL2_FOUND TRUE)
                    set(SDL2_INCLUDE_DIRS "${SDL2_LOCAL_DIR}/include")
                    set(SDL2_LIBRARIES "${SDL2_LOCAL_DIR}/lib/libSDL2.a")
                endif()
            endif()
        endif()
    endif()

    if(NOT SDL2_FOUND)
        message(FATAL_ERROR
            "SDL2 not found!\n"
            "  macOS:         brew install sdl2\n"
            "  Linux:         sudo apt install libsdl2-dev  (Debian/Ubuntu)\n"
            "                 sudo dnf install SDL2-devel   (Fedora)\n"
            "  Windows/MSYS2: pacman -S mingw-w64-i686-SDL2\n"
            "  Or download SDL2 development libraries to ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2")
    endif()
endif()
include_directories(${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2 include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

# Fix SDL2 target for 32-bit Linux multilib builds
if(UNIX AND NOT APPLE AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    include(cmake/FixSDL2-i686.cmake)
endif()

# =============================================================================
# GLAD (OpenGL 3.3 loader - generated by glad2)
# =============================================================================
add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/src/gl.c
)
target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
)

# =============================================================================
# Collect game source files
# =============================================================================
file(GLOB_RECURSE GAME_C_SOURCES CONFIGURE_DEPENDS
    "${DECOMP_ROOT}/src/*.c"
)
file(GLOB_RECURSE GAME_CXX_SOURCES CONFIGURE_DEPENDS
    "${DECOMP_ROOT}/src/*.cpp"
)

# Exclude files that conflict with PC port or are platform-specific
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/AUS/.*")  # AUS-specific versions

# Exclude all Dolphin SDK hardware abstraction (we replace with pc_*.c stubs)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/gx/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/os/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/vi/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/pad/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/card/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/dvd/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/ai/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/ar/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/dsp/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/exi/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/si/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/db/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/mtx/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/base/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/gba/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/amcstubs/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/OdemuExi2/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/dolphin/odenotstub/.*")

# Exclude PPC-specific runtime/compiler support (Metrowerks CodeWarrior)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/TRK_MINNOW_DOLPHIN/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/Runtime\\.PPCEABI\\.H/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/MSL_C\\.PPCEABI\\.bare\\.H/.*")

# Bootdata: Include window/logo model display lists (gam_win1.c, gam_win2.c, gam_win3.c, logo_nin.c)
# These provide Gfx[] arrays used by initial_menu.c for UI windows and Nintendo logo.

# Include ALL data files now that .inc assets are extracted from ROM
# (build/GAFE01_00/include/ is in the include path)
file(GLOB_RECURSE DATA_C_SOURCES CONFIGURE_DEPENDS "${DECOMP_ROOT}/src/data/*.c")
list(APPEND GAME_C_SOURCES ${DATA_C_SOURCES})

# f_furniture.c #includes all 696 src/furniture/*.c files as a single TU (like GC build).
# Exclude the individual files to avoid duplicate symbol definitions.
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/src/furniture/.*")

# Exclude duplicate data files (subdirectory verbose versions conflict with top-level)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/src/data/model/obj_e_boat/.*")

# Exclude template/include .c files that are #included from other files
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ac_npc_shop_common\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ac_animal_logo_misc\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/m_item_debug\\.c$")

# Exclude NPC anime data fragments (no headers, #included from other NPC files)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/actor/npc/.*_anime\\.c$")

# Exclude Dolphin OS sources that conflict with PC stubs
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/osreport\\.c$")
# audio.c now included (jaudio_NES provides Na_* functions)

# Exclude Famicom/NES emulator (contains PPC inline assembly)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/Famicom/.*")

# Exclude MSL_C library sources (using system libc on PC)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/MSL_C/.*")

# jaudio_NES: Include audio engine, exclude GBA-specific files
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/jaudio_NES/internal/dsp_cardunlock\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/jaudio_NES/internal/dsp_GBAKey\\.c$")

# libc64: Include most files (qrand, math64, sleep, etc.)
# Exclude malloc.c (redefines system malloc/free which crashes CRT on PC)
# Keep __osMalloc.c (game code uses __osMalloc* directly via m_malloc.c)
# Exclude sprintf.c/aprintf.c (they need _Printf from libultra xprintf)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/malloc\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/sprintf\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/aprintf\\.c$")

# libultra: Exclude most (we have pc_os.c replacements), but keep xprintf for libc64
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libultra/.*")

# Exclude PPC-specific files
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ReconfigBATs\\.c$")

# Exclude GC-specific entry point (PC has its own main)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/executor\\.c$")

# ROM asset .inc files now available in build/GAFE01_00/include/assets/
# All previously-excluded files are now compiled with real data.

# Exclude ef_effect_lib.c (has no #includes, pure function definitions without type context)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ef_effect_lib\\.c$")

# Exclude m_card.c (needs Dolphin CARD system headers with non-standard include paths)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/m_card\\.c$")

# Also filter C++ sources
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/AUS/.*")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/dolphin/.*")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/TRK_MINNOW_DOLPHIN/.*")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/Runtime\\.PPCEABI\\.H/.*")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/MSL_C\\.PPCEABI\\.bare\\.H/.*")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/Famicom/.*")

# Exclude emu64_print.cpp (it's #included directly from emu64.c, not a standalone file)
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/emu64_print\\.cpp$")

# libjsys: jsyswrapper_ext.cpp and jsyswrapper_main.cpp are #included from jsyswrapper.cpp
# so exclude them from standalone compilation (just like emu64_utility.c)
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/jsyswrapper_ext\\.cpp$")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/jsyswrapper_main\\.cpp$")

# =============================================================================
# PC port source files
# =============================================================================
set(PC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_gx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_gx_tev.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_gx_texture.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_os.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_dvd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_pad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_typing.c
    ${DECOMP_ROOT}/src/static/dolphin/pad/Padclamp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_card.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_vi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_audio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_aram.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_misc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_mtx.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_m_card.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_save_bswap.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_model_viewer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_texture_pack.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_keybindings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_stubs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_stubs_cpp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_assets.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pc_disc.c
)

# Rename game's main() to ac_entry() to avoid conflict with PC main() and game_main(GAME*)
set_source_files_properties(
    "${DECOMP_ROOT}/src/main.c"
    PROPERTIES COMPILE_DEFINITIONS "main=ac_entry"
)

# Rename boot.c's main() to avoid conflict with PC main()
set_source_files_properties(
    "${DECOMP_ROOT}/src/static/boot.c"
    PROPERTIES COMPILE_DEFINITIONS "main=boot_main"
)

# Exclude emu64_utility.c (it's #included from emu64.c, not a standalone file)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/emu64_utility\\.c$")

# These .c files contain C++ code (classes, namespaces, ::) - compile as C++
# Only files that truly need C++ (std::, extern "C", etc.) - NOT just for nullptr
set_source_files_properties(
    "${DECOMP_ROOT}/src/static/libforest/emu64/emu64.c"
    # ja_calc.c uses std::sinf, std::sqrtf
    "${DECOMP_ROOT}/src/static/jaudio_NES/internal/ja_calc.c"
    # sample.c: reinterpret_cast replaced with C cast under TARGET_PC, no longer needs C++
    # jammain_2.c uses extern "C"
    "${DECOMP_ROOT}/src/static/jaudio_NES/internal/jammain_2.c"
    # game64.c includes .c_inc with extern "C" (OSAttention.c_inc)
    "${DECOMP_ROOT}/src/static/jaudio_NES/game/game64.c"
    PROPERTIES LANGUAGE CXX
)

# =============================================================================
# Per-source warning settings
# =============================================================================
# Decomp code: suppress all warnings (fires heavily on decompiled code)
# Clang treats some decomp patterns as errors even with -w:
# -Wno-return-type: missing return values in non-void functions
# -Wno-initializer-overrides: GBI macros use designated initializers with overlapping fields
set(DECOMP_WARN_FLAGS "-w;-fpermissive;-Wno-return-type;-Wno-error=return-type")
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    list(APPEND DECOMP_WARN_FLAGS "-Wno-c99-designator" "-Wno-initializer-overrides")
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        message(FATAL_ERROR
            "64-bit builds require GCC (Clang rejects pointer-to-u32 truncation in GBI static initializers).\n"
            "  macOS:  brew install gcc && cmake .. -DCMAKE_C_COMPILER=gcc-15 -DCMAKE_CXX_COMPILER=g++-15\n"
            "          (adjust version number to match installed GCC, e.g. gcc-14/g++-14)\n"
            "  Linux:  GCC is typically the default compiler.")
    endif()
endif()
set_source_files_properties(${GAME_C_SOURCES} ${GAME_CXX_SOURCES}
    PROPERTIES COMPILE_OPTIONS "${DECOMP_WARN_FLAGS}"
)

# PC port code: enable warnings to catch bugs in code we control
set(PC_C_SOURCES ${PC_SOURCES})
list(FILTER PC_C_SOURCES EXCLUDE REGEX "\\.cpp$")
set(PC_CXX_SOURCES ${PC_SOURCES})
list(FILTER PC_CXX_SOURCES INCLUDE REGEX "\\.cpp$")
# Note: -Wno-comment/-Wno-unused-function/-Wno-builtin-declaration-mismatch suppress
# warnings from decomp headers (types.h, gfxprint.h, OSRtc.h, libultra.h) that we can't modify.
set(PC_WARN_SUPPRESS "-Wno-unused-parameter;-Wno-sign-compare;-Wno-comment;-Wno-unused-function")
if(NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
    list(APPEND PC_WARN_SUPPRESS "-Wno-builtin-declaration-mismatch")
endif()
set_source_files_properties(${PC_C_SOURCES}
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;${PC_WARN_SUPPRESS}"
)
set_source_files_properties(${PC_CXX_SOURCES}
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;${PC_WARN_SUPPRESS};-fpermissive"
)

# =============================================================================
# Windows resource file (sets process name in Task Manager)
# =============================================================================
if(WIN32)
    set(RC_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/app.rc")
endif()

# =============================================================================
# Build executable
# =============================================================================
add_executable(ac_pc
    ${PC_SOURCES}
    ${GAME_C_SOURCES}
    ${GAME_CXX_SOURCES}
    ${RC_FILE}
)

# Link SDL2 without SDL2main (we define SDL_MAIN_HANDLED)
if(TARGET SDL2::SDL2)
    target_link_libraries(ac_pc glad SDL2::SDL2)
else()
    list(FILTER SDL2_LIBRARIES EXCLUDE REGEX "SDL2main")
    target_link_libraries(ac_pc glad ${SDL2_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(ac_pc opengl32 winmm imm32 version setupapi)
elseif(APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(ac_pc OpenGL::GL "-framework Cocoa" "-framework IOKit" pthread m)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(ac_pc OpenGL::GL dl pthread m)
endif()

set_target_properties(ac_pc PROPERTIES
    OUTPUT_NAME "AnimalCrossing"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy shader files to output directory (loaded at runtime, with embedded fallback)
add_custom_command(TARGET ac_pc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.frag"
        "${CMAKE_BINARY_DIR}/bin/shaders/"
    COMMENT "Copying shader files to bin/shaders/"
)

# Copy SDL2.dll next to executable so users don't need it on PATH
if(WIN32)
    find_file(SDL2_DLL_PATH SDL2.dll PATHS
        "${SDL2_MSYS2_DIR}/bin"
        "${SDL2_DOWNLOAD_DIR}/bin"
        "${SDL2_LOCAL_DIR}/bin"
        "$ENV{MINGW_PREFIX}/bin"
    )
    if(SDL2_DLL_PATH)
        add_custom_command(TARGET ac_pc POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL2_DLL_PATH}" "${CMAKE_BINARY_DIR}/bin/"
            COMMENT "Copying SDL2.dll to bin/"
        )
    endif()
endif()

# Static link MinGW runtime (no libgcc_s_dw2-1.dll, libstdc++-6.dll, libwinpthread-1.dll)
# Strip version.o from winpthread to prevent its version resource from overriding app.rc
if(MINGW)
    find_file(WINPTHREAD_LIB libwinpthread.a PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES} /mingw32/lib NO_DEFAULT_PATH)
    if(NOT WINPTHREAD_LIB)
        find_file(WINPTHREAD_LIB libwinpthread.a)
    endif()
    set(WINPTHREAD_STRIPPED "${CMAKE_CURRENT_BINARY_DIR}/libwinpthread_stripped.a")
    if(WINPTHREAD_LIB AND NOT EXISTS "${WINPTHREAD_STRIPPED}")
        file(COPY_FILE ${WINPTHREAD_LIB} ${WINPTHREAD_STRIPPED})
        execute_process(COMMAND ${CMAKE_AR} d "${WINPTHREAD_STRIPPED}" version.o)
        message(STATUS "Stripped version.o from winpthread: ${WINPTHREAD_STRIPPED}")
    endif()
    target_link_options(ac_pc PRIVATE -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive "${WINPTHREAD_STRIPPED}" -Wl,-Bdynamic,--no-whole-archive)
endif()

# Hide console window on Windows (GUI subsystem)
# Use -DPC_CONSOLE=ON to keep the console visible for debugging
if(WIN32 AND NOT PC_CONSOLE)
    target_link_options(ac_pc PRIVATE -mwindows)
endif()

# =============================================================================
# Install rules (cmake --install . --prefix <dest>)
# =============================================================================
install(TARGETS ac_pc RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
    DESTINATION bin/shaders
    FILES_MATCHING PATTERN "*.vert" PATTERN "*.frag"
)
