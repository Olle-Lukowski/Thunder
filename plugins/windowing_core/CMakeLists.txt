include(dependencies.cmake)

add_library(windowing_core STATIC
  src/window.c
)

target_include_directories(windowing_core PUBLIC include)

target_link_libraries(windowing_core PUBLIC ${PLUGIN_windowing_core_DEPENDENCIES})
