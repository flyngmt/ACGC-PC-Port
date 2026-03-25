# Fix for i686 multilib - override SDL2::SDL2 target to use 32-bit library
message(STATUS "FixSDL2-i686: Checking for SDL2 target...")
if(TARGET SDL2::SDL2)
    message(STATUS "Found SDL2::SDL2 target, overriding to use 32-bit library")
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION /usr/lib/i386-linux-gnu/libSDL2-2.0.so.0
        INTERFACE_LINK_LIBRARIES ""
    )
else()
    message(STATUS "SDL2::SDL2 target not found, creating it")
    add_library(SDL2::SDL2 UNKNOWN IMPORTED)
    set_target_properties(SDL2::SDL2 PROPERTIES
        IMPORTED_LOCATION /usr/lib/i386-linux-gnu/libSDL2-2.0.so.0
        INTERFACE_INCLUDE_DIRECTORIES "/usr/include;/usr/include/SDL2"
    )
endif()
