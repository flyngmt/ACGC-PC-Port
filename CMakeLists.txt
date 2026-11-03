cmake_minimum_required(VERSION 3.25)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
            "Build type options: Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif ()

include(extern/borealis/cmake/DetectVersion.cmake)
borealis_detect_version()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
project(acgc VERSION ${BOREALIS_APP_VERSION} LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DECOMP_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(PC_ROOT "${DECOMP_ROOT}/pc")

# Adjust CMAKE_SYSTEM_PROCESSOR on Windows to match compiler target
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    if (CMAKE_C_COMPILER_ARCHITECTURE_ID MATCHES "^ARM64")
        set(CMAKE_SYSTEM_PROCESSOR "ARM64")
    elseif (CMAKE_C_COMPILER_ARCHITECTURE_ID STREQUAL "x64")
        set(CMAKE_SYSTEM_PROCESSOR "AMD64")
    elseif (CMAKE_C_COMPILER_ARCHITECTURE_ID STREQUAL "X86")
        set(CMAKE_SYSTEM_PROCESSOR "X86")
    endif ()
endif ()

# Decompiled code assumes char is signed, but some compilers default to unsigned char (ARM, Android, etc.)
if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU" OR (MSVC AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    add_compile_options(-fsigned-char)
endif ()

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
if (ENABLE_SANITIZERS)
    if (CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC" AND
            CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/fsanitize=address,undefined>)
        add_link_options(/fsanitize=address,undefined /INCREMENTAL:NO)
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "ProgramDatabase")
        foreach (_lang C CXX)
            foreach (_rtc_flag /RTC1 /RTCc /RTCs /RTCu)
                string(REPLACE "${_rtc_flag}" "" CMAKE_${_lang}_FLAGS_DEBUG "${CMAKE_${_lang}_FLAGS_DEBUG}")
            endforeach ()
        endforeach ()
    elseif (CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "GNU" AND
            CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        add_compile_options(
                $<$<COMPILE_LANGUAGE:C,CXX,OBJC,OBJCXX>:-fsanitize=address,undefined>
                $<$<COMPILE_LANGUAGE:C,CXX,OBJC,OBJCXX>:-fno-omit-frame-pointer>
        )
        add_link_options(-fsanitize=address,undefined)
    else ()
        message(FATAL_ERROR "ENABLE_SANITIZERS requires GNU-like or MSVC-like C/C++ compiler frontends")
    endif ()
    add_compile_definitions(NDEBUG_SANITIZER) # Avoids absl issue with SwissTable debug code
    message(STATUS "metaforce: Enabled sanitizers")
endif ()

set(AURORA_ENABLE_DVD ON CACHE BOOL "" FORCE)
set(AURORA_ENABLE_CARD ON CACHE BOOL "" FORCE)
set(AURORA_ENABLE_RMLUI ON CACHE BOOL "" FORCE)
add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)
if (ANDROID AND TARGET _cargo-build_nod)
    # NDK r30+ requires a versioned target triple
    # TODO: move into aurora or nod
    corrosion_set_env_vars(nod "TARGET_CFLAGS=--target=${CMAKE_C_COMPILER_TARGET}")
endif ()
if (APPLE AND TARGET nod-static)
    # TODO: temp workaround until corrosion-rs/corrosion@2522f7abad
    set_property(TARGET nod-static PROPERTY INTERFACE_LINK_DIRECTORIES "")
endif ()
set(BOREALIS_ENABLE_UI ON CACHE BOOL "" FORCE)
add_subdirectory(extern/borealis EXCLUDE_FROM_ALL)

include(FetchContent)
find_package(nlohmann_json 3.11 QUIET)
if (NOT TARGET nlohmann_json::nlohmann_json)
    FetchContent_Declare(nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
        URL_HASH SHA256=42f6e95cad6ec532fd372391373363b62a14af6d771056dbfc86160e6dfff7aa
        DOWNLOAD_EXTRACT_TIMESTAMP FALSE
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif ()

# Allow mixed C/C++ linkage
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_EXTENSIONS ON)

# =============================================================================
# Compiler definitions
# =============================================================================
option(MOUSE_INPUT "Enable mouse input for game menus" ON)
if (MOUSE_INPUT)
    add_compile_definitions(MOUSE_INPUT)
endif ()

add_compile_definitions(
    TARGET_PC=1
    VERSION=0
    F3DEX_GBI_2
    NDEBUG
    BUGFIXES        # Fix OOB reads in letter scoring tables (m_mail_check_ovl.c).
    PC_ENHANCEMENTS # Enable PC quality-of-life and visual improvements.
    _LANGUAGE_C    # Required for N64 GBI/ultratypes headers
)

if (MSVC)
    add_compile_options(
        $<$<COMPILE_LANGUAGE:C,CXX>:/bigobj>
        $<$<COMPILE_LANGUAGE:C,CXX>:/utf-8>
    )

    # MSVC's Debug defaults include /RTC1, which is incompatible with /O2 used by fixNES
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        foreach (lang C CXX)
            foreach (debug_flag /Od /RTC1)
                string(REPLACE "${debug_flag}" "" CMAKE_${lang}_FLAGS_DEBUG "${CMAKE_${lang}_FLAGS_DEBUG}")
            endforeach ()
        endforeach ()
        set(ACGC_DEBUG_OPTIONS
            $<$<COMPILE_LANGUAGE:C,CXX>:/Od>
            $<$<COMPILE_LANGUAGE:C,CXX>:/RTC1>
        )
    endif ()
else ()
    add_compile_options(
        -fno-strict-aliasing
        -fwrapv
    )
endif ()

# =============================================================================
# Include paths
# =============================================================================
include_directories(
    ${PC_ROOT}/lib/kyureki
    ${DECOMP_ROOT}/include
    ${DECOMP_ROOT}/src
    # Project root needed for includes like "src/actor/npc/event/file.c_inc"
    ${DECOMP_ROOT}
    ${PC_ROOT}/include
    ${PC_ROOT}/include/acgc/ui
    ${PC_ROOT}/lib/fixnes
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

# The PC calendar uses astronomy instead of the console's finite date tables.
list(REMOVE_ITEM GAME_C_SOURCES "${DECOMP_ROOT}/src/lb_reki.c")
set(KYUREKI_SOURCES
    ${PC_ROOT}/lib/kyureki/kyureki.c
    ${PC_ROOT}/lib/kyureki/astro_builtin.c
    ${PC_ROOT}/lib/kyureki/lb_reki_adapter.c
)
if (MSVC)
    set_source_files_properties(${KYUREKI_SOURCES} PROPERTIES COMPILE_OPTIONS /fp:precise)
else ()
    set_source_files_properties(${KYUREKI_SOURCES} PROPERTIES COMPILE_OPTIONS -fno-fast-math)
endif ()

# Exclude PPC-specific runtime/compiler support (Metrowerks CodeWarrior)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/TRK_MINNOW_DOLPHIN/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/Runtime\\.PPCEABI\\.H/.*")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/MSL_C\\.PPCEABI\\.bare\\.H/.*")

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

# Exclude the matching console reporter; the host adapter routes reports to the
# active process output and will be folded into the shared logging slice.
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/osreport\\.c$")

# jaudio_NES: Include audio engine, exclude GBA-specific files
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/jaudio_NES/internal/dsp_cardunlock\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/jaudio_NES/internal/dsp_GBAKey\\.c$")

# libc64: Include most files (qrand, math64, sleep, etc.)
# Exclude malloc.c (redefines system malloc/free which crashes CRT on PC)
# Keep __osMalloc.c (game code uses __osMalloc* directly via m_malloc.c)
# Exclude the console sprintf implementation. The PC vaprintf adapter below
# uses the host formatter and forwards the result through the original callback.
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/malloc\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/sprintf\\.c$")
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libc64/aprintf\\.c$")

# libultra: most hardware-facing N64 sources remain excluded, but the game's
# controller conversion, timer bridge, and small host-safe helpers work on top
# of Aurora's OS/PAD implementations and should not be replaced by no-op stubs.
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/libultra/.*")
file(GLOB LIBULTRA_GU_SOURCES CONFIGURE_DEPENDS "${DECOMP_ROOT}/src/static/libultra/gu/*.c")
set(LIBULTRA_HOST_SOURCES
    ${DECOMP_ROOT}/src/static/libultra/controller.c
    ${DECOMP_ROOT}/src/static/libultra/contquery.c
    ${DECOMP_ROOT}/src/static/libultra/contreaddata.c
    ${DECOMP_ROOT}/src/static/libultra/contsetch.c
    ${DECOMP_ROOT}/src/static/libultra/destroythread.c
    ${DECOMP_ROOT}/src/static/libultra/getthreadid.c
    ${DECOMP_ROOT}/src/static/libultra/initialize.c
    ${DECOMP_ROOT}/src/static/libultra/settimer.c
    ${DECOMP_ROOT}/src/static/libultra/timerintr.c
    ${DECOMP_ROOT}/src/static/libc64/aprintf.c
)
list(APPEND GAME_C_SOURCES ${LIBULTRA_GU_SOURCES} ${LIBULTRA_HOST_SOURCES})

# Exclude PPC-specific files
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ReconfigBATs\\.c$")

# Exclude GC-specific entry point (PC has its own main)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/executor\\.c$")

# Exclude ef_effect_lib.c (has no #includes, pure function definitions without type context)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/ef_effect_lib\\.c$")

# Exclude m_card.c (needs Dolphin CARD system headers with non-standard include paths)
list(FILTER GAME_C_SOURCES EXCLUDE REGEX ".*/m_card\\.c$")

# Also filter C++ sources
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/Runtime\\.PPCEABI\\.H/.*")

# Exclude emu64_print.cpp (it's #included directly from emu64.c, not a standalone file)
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/emu64_print\\.cpp$")

# libjsys: jsyswrapper_ext.cpp and jsyswrapper_main.cpp are #included from jsyswrapper.cpp
# so exclude them from standalone compilation (just like emu64_utility.c)
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/jsyswrapper_ext\\.cpp$")
list(FILTER GAME_CXX_SOURCES EXCLUDE REGEX ".*/jsyswrapper_main\\.cpp$")

# =============================================================================
# Host support sources retained while game-specific endian and libultra work is
# migrated. Dolphin SDK implementations come exclusively from Aurora.
# =============================================================================
set(PC_SOURCES
    ${PC_ROOT}/src/acgc_controller_ports.cpp
    ${PC_ROOT}/src/acgc_data.cpp
    ${PC_ROOT}/src/acgc_disc.cpp
    ${PC_ROOT}/src/acgc_input_profiles.cpp
    ${PC_ROOT}/src/acgc_legacy_input.cpp
    ${PC_ROOT}/src/acgc_settings.cpp
    ${PC_ROOT}/src/acgc_texture_replacements.cpp
    ${PC_ROOT}/src/aurora_debug.cpp
    ${PC_ROOT}/src/aurora_main.cpp
    ${PC_ROOT}/src/aurora_mouse_cursor.cpp
    ${PC_ROOT}/src/aurora_platform.cpp
    ${PC_ROOT}/src/aurora_widescreen.cpp
    ${PC_ROOT}/src/aurora_vi.cpp
    ${PC_ROOT}/src/ui/adjust_arrows.cpp
    ${PC_ROOT}/src/ui/bool_button.cpp
    ${PC_ROOT}/src/ui/controller_config.cpp
    ${PC_ROOT}/src/ui/localization.cpp
    ${PC_ROOT}/src/ui/menu_bar.cpp
    ${PC_ROOT}/src/ui/number_button.cpp
    ${PC_ROOT}/src/ui/overlay.cpp
    ${PC_ROOT}/src/ui/prelaunch.cpp
    ${PC_ROOT}/src/ui/scrolling_background.cpp
    ${PC_ROOT}/src/ui/settings.cpp
    ${PC_ROOT}/src/ui/theme.cpp
    ${PC_ROOT}/src/ui/theme_mirror.cpp
    ${PC_ROOT}/src/ui/touch_controls.cpp
    ${PC_ROOT}/src/ui/touch_controls_editor.cpp
    ${PC_ROOT}/src/ui/touch_layout.cpp
    ${PC_ROOT}/src/ui/town_select.cpp
    ${PC_ROOT}/src/ui/ui.cpp
    ${PC_ROOT}/src/pc_audio.c
    ${PC_ROOT}/src/pc_clock.c
    ${PC_ROOT}/src/pc_gci.c
    ${PC_ROOT}/src/pc_m_card.c
    ${PC_ROOT}/src/acgc_game_pointer.cpp
    ${PC_ROOT}/src/acgc_game_pointer_host.cpp
    ${PC_ROOT}/src/pc_save_bswap.c
    ${PC_ROOT}/src/pc_nes_fixnes.c
    ${PC_ROOT}/src/pc_assets.c
    ${PC_ROOT}/src/pc_emu64_geometry_cache.cpp
    ${PC_ROOT}/src/acgc_game_editor.cpp
    ${PC_ROOT}/src/acgc_game_editor_host.cpp
    ${PC_ROOT}/src/acgc_game_text.cpp
)

# =============================================================================
# fixNES — vendored NES emulator (MIT License, by FIX94)
# =============================================================================
set(FIXNES_DIR ${PC_ROOT}/lib/fixnes)
file(GLOB FIXNES_MAPPER_SOURCES ${FIXNES_DIR}/mapper/*.c)
set(FIXNES_SOURCES
    ${FIXNES_DIR}/cpu.c
    ${FIXNES_DIR}/ppu.c
    ${FIXNES_DIR}/apu.c
    ${FIXNES_DIR}/mem.c
    ${FIXNES_DIR}/input.c
    ${FIXNES_DIR}/mapper.c
    ${FIXNES_DIR}/mapperList.c
    ${FIXNES_DIR}/vrc_irq.c
    ${FIXNES_DIR}/audio.c
    ${FIXNES_DIR}/fm2play.c
    ${FIXNES_DIR}/audio_fds.c
    ${FIXNES_DIR}/audio_mmc5.c
    ${FIXNES_DIR}/audio_vrc6.c
    ${FIXNES_DIR}/audio_vrc7.c
    ${FIXNES_DIR}/audio_n163.c
    ${FIXNES_DIR}/audio_s5b.c
    ${FIXNES_MAPPER_SOURCES}
)
# fixNES compile flags: optimize for performance (third-party code, no decomp UB),
# enable inlining (critical for cycle-by-cycle emulation), lower APU frequency
if (MSVC)
    set(FIXNES_COMPILE_OPTIONS "/W0;/O2")
    set(PC_NES_COMPILE_OPTIONS "/W4;/O2;/wd4100")
else ()
    set(FIXNES_COMPILE_OPTIONS "-w;-O2")
    set(PC_NES_COMPILE_OPTIONS "-Wall;-Wextra;-O2;-Wno-unused-parameter")
endif ()
set_source_files_properties(${FIXNES_SOURCES}
    PROPERTIES
    COMPILE_OPTIONS "${FIXNES_COMPILE_OPTIONS}"
    COMPILE_DEFINITIONS "COL_TEX_BSWAP;COL_GL_BSWAP;DO_INLINE_ATTRIBS=1"
)
# Also optimize the fixNES wrapper (frame loop is hot)
# Note: DO NOT set DO_INLINE_ATTRIBS here — the always_inline functions (cpuCycle etc)
# are in separate TUs and can't be inlined across files. They'll be inlined within
# their own .c files where -O2 + DO_INLINE_ATTRIBS is set.
set_source_files_properties(${PC_ROOT}/src/pc_nes_fixnes.c
    PROPERTIES
    COMPILE_OPTIONS "${PC_NES_COMPILE_OPTIONS}"
    COMPILE_DEFINITIONS ""
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
    # jammain_2.c uses extern "C"
    "${DECOMP_ROOT}/src/static/jaudio_NES/internal/jammain_2.c"
    # game64.c includes .c_inc with extern "C" (OSAttention.c_inc)
    "${DECOMP_ROOT}/src/static/jaudio_NES/game/game64.c"
    PROPERTIES LANGUAGE CXX
)

# =============================================================================
# Per-source warning settings
# =============================================================================
# Keep warnings useful by separating code ownership: decompiled matching code
# is warning-noisy by construction, while maintained host code below builds at
# the toolchain's high warning level.
if (MSVC)
    set(DECOMP_WARN_FLAGS "/W0;${ACGC_DEBUG_OPTIONS}")
else ()
    set(DECOMP_WARN_FLAGS "-w;-fpermissive")
    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        # Modern Clang diagnoses the decomp's original bare returns in non-void C
        # functions as errors even with -w. Metrowerks accepted these sources.
        list(APPEND DECOMP_WARN_FLAGS "-Wno-return-mismatch" "-Wno-implicit-int")
    endif ()
endif ()
set_source_files_properties(${GAME_C_SOURCES} ${GAME_CXX_SOURCES}
    PROPERTIES COMPILE_OPTIONS "${DECOMP_WARN_FLAGS}"
)
if (MSVC)
    # MSVC exposes the standard C11 <stdatomic.h> implementation behind this
    # opt-in switch. Only the audio command queue uses it.
    set_property(SOURCE "${DECOMP_ROOT}/src/static/jaudio_NES/internal/sub_sys.c"
        APPEND PROPERTY COMPILE_OPTIONS /experimental:c11atomics
    )
endif ()

# PC port code: enable warnings to catch bugs in code we control
set(PC_C_SOURCES ${PC_SOURCES})
list(FILTER PC_C_SOURCES EXCLUDE REGEX "\\.cpp$")
# pc_nes_fixnes.c has its own warning and optimization policy above.
list(REMOVE_ITEM PC_C_SOURCES ${PC_ROOT}/src/pc_nes_fixnes.c)
set(PC_CXX_SOURCES ${PC_SOURCES})
list(FILTER PC_CXX_SOURCES INCLUDE REGEX "\\.cpp$")
# The suppressions cover warnings from decomp headers (types.h, gfxprint.h,
# OSRtc.h, libultra.h) that we can't modify. Use /W4 rather than /Wall on MSVC:
# the latter enables every off-by-default compiler warning.
if (MSVC)
    set(PC_C_WARN_FLAGS "/W4;/wd4018;/wd4100;/wd4138;/wd4505;${ACGC_DEBUG_OPTIONS}")
    set(PC_CXX_WARN_FLAGS "${PC_C_WARN_FLAGS}")
else ()
    set(PC_WARN_SUPPRESS "-Wno-unused-parameter;-Wno-sign-compare;-Wno-comment;-Wno-unused-function")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        list(APPEND PC_WARN_SUPPRESS "-Wno-builtin-declaration-mismatch")
    endif ()
    set(PC_C_WARN_FLAGS "-Wall;-Wextra;${PC_WARN_SUPPRESS}")
    set(PC_CXX_WARN_FLAGS "${PC_C_WARN_FLAGS};-fpermissive")
endif ()
set_source_files_properties(${PC_C_SOURCES}
    PROPERTIES COMPILE_OPTIONS "${PC_C_WARN_FLAGS}"
)
set_source_files_properties(${PC_CXX_SOURCES}
    PROPERTIES COMPILE_OPTIONS "${PC_CXX_WARN_FLAGS}"
)

# =============================================================================
# Windows resource file (sets process name in Task Manager)
# =============================================================================
if(WIN32)
    set(ACGC_WINDOWS_ROOT "${DECOMP_ROOT}/platforms/windows")
    set(ACGC_WINDOWS_ICON "${ACGC_WINDOWS_ROOT}/Nookery.ico")
    set(ACGC_WINDOWS_MANIFEST "${ACGC_WINDOWS_ROOT}/nookery.manifest")
    set(RC_FILE "${CMAKE_CURRENT_BINARY_DIR}/nookery.rc")
    configure_file("${ACGC_WINDOWS_ROOT}/nookery.rc.in" "${RC_FILE}" @ONLY)
    set_source_files_properties("${RC_FILE}" PROPERTIES
        OBJECT_DEPENDS "${ACGC_WINDOWS_ICON};${ACGC_WINDOWS_MANIFEST}")
endif()

# =============================================================================
# Build executable
# =============================================================================
set(ACGC_APPLICATION_SOURCES
    ${KYUREKI_SOURCES}
    ${PC_SOURCES}
    ${FIXNES_SOURCES}
    ${GAME_C_SOURCES}
    ${GAME_CXX_SOURCES}
    ${RC_FILE}
)

if (ANDROID)
    add_library(acgc SHARED ${ACGC_APPLICATION_SOURCES})
else ()
    add_executable(acgc ${ACGC_APPLICATION_SOURCES})
endif ()
borealis_configure_android_application(acgc)

if (UNIX)
    target_link_libraries(acgc PRIVATE m)
endif ()

if (WIN32)
    if (MSVC)
        target_link_options(acgc PRIVATE /MANIFEST:NO)
    endif ()
    set_target_properties(acgc PROPERTIES WIN32_EXECUTABLE TRUE)
endif ()

target_link_libraries(acgc PRIVATE
    TracyClient
    nlohmann_json::nlohmann_json
    borealis::cli
    borealis::config
    borealis::crash
    borealis::data
    borealis::disc
    borealis::file_select
    borealis::log
    borealis::ui
    borealis::update
    aurora::card
    aurora::core
    aurora::dvd
    aurora::gx
    aurora::main
    aurora::mtx
    aurora::os
    aurora::pad
    aurora::si
    aurora::vi
)

set_target_properties(acgc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
if (NOT ANDROID)
    set_target_properties(acgc PROPERTIES OUTPUT_NAME "Nookery")
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(ACGC_MACOS_ROOT "${DECOMP_ROOT}/platforms/macos")
    target_sources(acgc PRIVATE "${ACGC_MACOS_ROOT}/Nookery.icns")
    set_source_files_properties("${ACGC_MACOS_ROOT}/Nookery.icns" PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_target_properties(acgc PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Nookery"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.flyngmt.nookery"
        MACOSX_BUNDLE_BUNDLE_VERSION "${BOREALIS_APP_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${BOREALIS_APP_SHORT_VERSION}"
        MACOSX_BUNDLE_INFO_PLIST "${ACGC_MACOS_ROOT}/Info.plist.in"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
    set(ACGC_RESOURCE_DEST "$<TARGET_BUNDLE_CONTENT_DIR:acgc>/Resources/res")
elseif (IOS)
    set(ACGC_IOS_ROOT "${DECOMP_ROOT}/platforms/ios")
    set(ACGC_IOS_ASSETS_DIR "${CMAKE_CURRENT_BINARY_DIR}/ios_assets")
    file(GLOB_RECURSE ACGC_IOS_ASSET_FILES CONFIGURE_DEPENDS "${ACGC_IOS_ROOT}/Assets.xcassets/*")
    add_custom_command(
        OUTPUT "${ACGC_IOS_ASSETS_DIR}/Assets.car"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ACGC_IOS_ASSETS_DIR}"
        COMMAND xcrun actool --compile "${ACGC_IOS_ASSETS_DIR}"
            --platform iphoneos
            --minimum-deployment-target "${CMAKE_OSX_DEPLOYMENT_TARGET}"
            --target-device iphone --target-device ipad
            --app-icon AppIcon
            --output-partial-info-plist "${ACGC_IOS_ASSETS_DIR}/partial-Info.plist"
            "${ACGC_IOS_ROOT}/Assets.xcassets"
        DEPENDS ${ACGC_IOS_ASSET_FILES}
        COMMENT "Compiling Nookery iOS asset catalog"
        VERBATIM
    )
    target_sources(acgc PRIVATE "${ACGC_IOS_ASSETS_DIR}/Assets.car")
    set_source_files_properties("${ACGC_IOS_ASSETS_DIR}/Assets.car" PROPERTIES
        GENERATED TRUE
        MACOSX_PACKAGE_LOCATION Resources
    )
    set_target_properties(acgc PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Nookery"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.flyngmt.nookery"
        MACOSX_BUNDLE_BUNDLE_VERSION "${BOREALIS_APP_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${BOREALIS_APP_SHORT_VERSION}"
        MACOSX_BUNDLE_INFO_PLIST "${ACGC_IOS_ROOT}/Info.plist.in"
        XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
    )
    set(ACGC_RESOURCE_DEST "$<TARGET_BUNDLE_CONTENT_DIR:acgc>/res")
else ()
    set(ACGC_RESOURCE_DEST "$<TARGET_FILE_DIR:acgc>/res")
endif ()

include(extern/aurora/cmake/AuroraCopyRuntimeDLLs.cmake)
aurora_copy_runtime_dlls(acgc)

if (NOT ANDROID)
    file(GLOB_RECURSE ACGC_RESOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false
        "${PC_ROOT}/res/*"
    )
    set(ACGC_RESOURCE_STAMP "${CMAKE_CURRENT_BINARY_DIR}/acgc-resources.stamp")
    add_custom_command(
        OUTPUT "${ACGC_RESOURCE_STAMP}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PC_ROOT}/res"
            "${ACGC_RESOURCE_DEST}"
        COMMAND ${CMAKE_COMMAND} -E touch "${ACGC_RESOURCE_STAMP}"
        DEPENDS ${ACGC_RESOURCE_FILES}
        COMMENT "Copying Animal Crossing UI resources"
        VERBATIM
    )
    add_custom_target(acgc_resources ALL DEPENDS "${ACGC_RESOURCE_STAMP}")
    add_dependencies(acgc acgc_resources)

    if (WIN32)
        set(ACGC_USER_FOLDERS save/card_a save/card_b texture_pack nes_roms)
    endif ()
    foreach (folder IN LISTS ACGC_USER_FOLDERS)
        add_custom_command(TARGET acgc POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:acgc>/${folder}"
            VERBATIM
        )
    endforeach ()
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND NOT CMAKE_GENERATOR STREQUAL "Xcode")
    add_custom_command(TARGET acgc POST_BUILD
        COMMAND /usr/bin/codesign --force --sign - "$<TARGET_BUNDLE_DIR:acgc>"
        COMMENT "Ad-hoc signing Nookery.app"
        VERBATIM
    )
endif ()

# =============================================================================
# Packaging logic
# =============================================================================
function(get_target_output_name target result_var)
    get_target_property(output_name ${target} OUTPUT_NAME)
    if (NOT output_name)
        set(${result_var} "${target}" PARENT_SCOPE)
    else ()
        set(${result_var} "${output_name}" PARENT_SCOPE)
    endif ()
endfunction()
function(get_target_prefix target result_var)
    set(${result_var} "" PARENT_SCOPE)
    if (APPLE)
        # Have to recreate some bundle logic here, since CMake can't tell us
        get_target_property(is_bundle ${target} MACOSX_BUNDLE)
        if (is_bundle)
            get_target_output_name(${target} output_name)
            if (CMAKE_SYSTEM_NAME STREQUAL Darwin)
                set(${result_var} "${output_name}.app/Contents/MacOS/" PARENT_SCOPE)
            else ()
                set(${result_var} "${output_name}.app/" PARENT_SCOPE)
            endif ()
        endif ()
    endif ()
endfunction()
get_target_property(_acgc_bundle acgc MACOSX_BUNDLE)
list(APPEND BINARY_TARGETS acgc)
set(EXTRA_TARGETS "")
if (TARGET crashpad_handler)
    list(APPEND EXTRA_TARGETS crashpad_handler)
endif ()
install(TARGETS ${BINARY_TARGETS} ${EXTRA_TARGETS} DESTINATION ${CMAKE_INSTALL_PREFIX})
aurora_install_runtime_dlls(acgc ${CMAKE_INSTALL_PREFIX})
if (NOT _acgc_bundle AND NOT ANDROID)
    install(DIRECTORY ${PC_ROOT}/res DESTINATION ${CMAKE_INSTALL_PREFIX})
    foreach (folder IN LISTS ACGC_USER_FOLDERS)
        install(DIRECTORY DESTINATION ${CMAKE_INSTALL_PREFIX}/${folder})
    endforeach ()
endif ()
if (CMAKE_BUILD_TYPE STREQUAL Debug OR CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    set(DEBUG_FILES_LIST "")
    foreach (target IN LISTS BINARY_TARGETS EXTRA_TARGETS)
        get_target_output_name(${target} output_name)
        if (WIN32)
            install(FILES $<TARGET_PDB_FILE:${target}> DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
        elseif (APPLE)
            get_target_prefix(${target} target_prefix)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND rm -fr \"$<TARGET_FILE_NAME:${target}>.dSYM\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND dsymutil \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND strip -S \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
            if (NOT target_prefix STREQUAL "")
                install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND mv \"${target_prefix}$<TARGET_FILE_NAME:${target}>.dSYM\" .)")
            endif ()
        elseif (UNIX)
            get_target_prefix(${target} target_prefix)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND objcopy --only-keep-debug \"${target_prefix}$<TARGET_FILE_NAME:${target}>\" \"${target_prefix}$<TARGET_FILE_NAME:${target}>.dbg\")")
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND objcopy --strip-debug --add-gnu-debuglink=$<TARGET_FILE_NAME:${target}>.dbg \"${target_prefix}$<TARGET_FILE_NAME:${target}>\")")
        endif ()
        list(APPEND DEBUG_FILES_LIST "${output_name}")
    endforeach ()
    # This is a terrible hack to only run this on CI
    # until I turn this into a script or something
    if (DEFINED ENV{GITHUB_ENV})
        if (WIN32)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".pdb")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND 7z a -t7z \"${CMAKE_INSTALL_PREFIX}/debug.7z\" ${DEBUG_FILES})")
        elseif (APPLE)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".dSYM")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND tar acfv \"${CMAKE_INSTALL_PREFIX}/debug.tar.xz\" ${DEBUG_FILES})")
        elseif (UNIX)
            list(TRANSFORM DEBUG_FILES_LIST APPEND ".dbg")
            list(JOIN DEBUG_FILES_LIST " " DEBUG_FILES)
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND tar -I \"xz -9 -T0\" -cvf \"${CMAKE_INSTALL_PREFIX}/debug.tar.xz\" ${DEBUG_FILES})")
        endif ()
    endif ()
endif ()
foreach (target IN LISTS BINARY_TARGETS)
    get_target_prefix(${target} target_prefix)
    foreach (extra_target IN LISTS EXTRA_TARGETS)
        get_target_prefix(${extra_target} extra_prefix)
        if (NOT "${target_prefix}" STREQUAL "${extra_prefix}")
            # Copy extra target to target prefix
            install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND cp \"${extra_prefix}$<TARGET_FILE_NAME:${extra_target}>\" \"${target_prefix}$<TARGET_FILE_NAME:${extra_target}>\")")
        endif ()
    endforeach ()
endforeach ()
if (_acgc_bundle AND CMAKE_SYSTEM_NAME STREQUAL Darwin)
    install(CODE "execute_process(WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\" COMMAND codesign --force --sign - \"$<TARGET_BUNDLE_DIR_NAME:acgc>\" COMMAND_ERROR_IS_FATAL ANY)")
endif ()
