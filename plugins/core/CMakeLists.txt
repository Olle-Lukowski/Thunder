include(dependencies.cmake)

add_library(core STATIC src/main.c)
target_include_directories(core PUBLIC include)

target_link_libraries(core PUBLIC ${PLUGIN_core_DEPENDENCIES})

