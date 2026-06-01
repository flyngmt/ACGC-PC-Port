# CMake toolchain file for Linux i686 (32-bit) cross-compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Use multilib gcc/g++ instead of cross-compiler
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Force 32-bit compilation. Enable SSE2 for floating point to ensure consistency
# with 64-bit and Windows builds, avoiding x87 excess precision issues that cause
# animation "twitching" and camera positioning bugs.
set(CMAKE_C_FLAGS "-m32 -msse2 -mfpmath=sse" CACHE STRING "")
set(CMAKE_CXX_FLAGS "-m32 -msse2 -mfpmath=sse" CACHE STRING "")
set(CMAKE_EXE_LINKER_FLAGS "-m32" CACHE STRING "")
set(CMAKE_SHARED_LINKER_FLAGS "-m32" CACHE STRING "")

# Tell CMake to look for 32-bit libraries
set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)

# Help CMake find 32-bit libraries
set(CMAKE_LIBRARY_PATH /usr/lib/i386-linux-gnu)
set(CMAKE_FIND_ROOT_PATH /usr/lib/i386-linux-gnu)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)

# Explicitly set library paths for 32-bit linking
# Use runtime libraries (.so.0) since i386 dev packages cause dependency conflicts
set(OPENGL_opengl_LIBRARY /usr/lib/i386-linux-gnu/libOpenGL.so.0 CACHE FILEPATH "")
set(OPENGL_glx_LIBRARY /usr/lib/i386-linux-gnu/libGLX.so.0 CACHE FILEPATH "")

# SDL2 will be fixed by FixSDL2-i686.cmake after find_package() in CMakeLists.txt

# Workaround: SDL2's multiarch wrapper includes <SDL2/_real_SDL_config.h> which
# lives in /usr/include/<arch>/SDL2/. Since we can't install libsdl2-dev:i386
# (causes glib conflicts), we use the x86_64 headers which are arch-independent.
include_directories(BEFORE SYSTEM /usr/include/x86_64-linux-gnu)
