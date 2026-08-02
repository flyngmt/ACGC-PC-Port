# CMake toolchain file for MinGW i686 (32-bit) cross-compilation from Linux
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

if(NOT DEFINED MINGW32)
    set(MINGW32 C:/msys64/mingw32)
endif()

# Compilers
set(CMAKE_C_COMPILER   ${MINGW32}/bin/i686-w64-mingw32-gcc.exe)
set(CMAKE_CXX_COMPILER ${MINGW32}/bin/i686-w64-mingw32-g++.exe)
set(CMAKE_RC_COMPILER  ${MINGW32}/bin/windres.exe)

# Linker / binutils
set(CMAKE_LINKER       ${MINGW32}/i686-w64-mingw32/bin/ld.exe)
set(CMAKE_AR           ${MINGW32}/i686-w64-mingw32/bin/ar.exe)
set(CMAKE_RANLIB       ${MINGW32}/i686-w64-mingw32/bin/ranlib.exe)
set(CMAKE_STRIP        ${MINGW32}/i686-w64-mingw32/bin/strip.exe)

# Sysroot / search paths
set(CMAKE_FIND_ROOT_PATH ${MINGW32})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  # don't look here for tools
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # only look here for libs
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # only look here for headers
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)   # only look here for packages