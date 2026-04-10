# Fix for i686 multilib - override SDL2::SDL2 target to use 32-bit library
# Supports both Debian (/usr/lib/i386-linux-gnu) and Arch (/usr/lib32) layouts
if(EXISTS /usr/lib/i386-linux-gnu/libSDL2-2.0.so.0)
    set(SDL2_32BIT_LIB /usr/lib/i386-linux-gnu/libSDL2-2.0.so.0)
elseif(EXISTS /usr/lib32/libSDL2-2.0.so.0)
    set(SDL2_32BIT_LIB /usr/lib32/libSDL2-2.0.so.0)
else()
    message(FATAL_ERROR "32-bit SDL2 library not found. Install lib32-sdl2 (Arch) or libsdl2-dev:i386 (Debian).")
endif()
message(STATUS "FixSDL2-i686: Using 32-bit SDL2 at ${SDL2_32BIT_LIB}")

if(TARGET SDL2::SDL2)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION ${SDL2_32BIT_LIB}
        INTERFACE_LINK_LIBRARIES ""
    )
else()
    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION ${SDL2_32BIT_LIB}
        INTERFACE_INCLUDE_DIRECTORIES "/usr/include;/usr/include/SDL2"
    )
endif()
