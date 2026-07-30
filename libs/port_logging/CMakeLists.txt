add_library(port_logging STATIC
    src/logging.cpp
)
add_library(port::logging ALIAS port_logging)

target_include_directories(port_logging PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(port_logging PUBLIC
    aurora::core
)
target_compile_features(port_logging PUBLIC cxx_std_20)

if (ANDROID)
    target_link_libraries(port_logging PRIVATE log)
endif ()
