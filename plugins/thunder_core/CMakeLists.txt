include(dependencies.cmake)

add_library(thunder_core STATIC src/main.c)
target_include_directories(thunder_core PUBLIC include)

target_link_libraries(thunder_core PUBLIC ${PLUGIN_thunder_core_DEPENDENCIES})

