include(dependencies.cmake)

add_library(thunder_windowing_core STATIC
  src/window.c
)

target_include_directories(thunder_windowing_core PUBLIC include)

target_link_libraries(thunder_windowing_core PUBLIC ${PLUGIN_thunder_windowing_core_DEPENDENCIES})
