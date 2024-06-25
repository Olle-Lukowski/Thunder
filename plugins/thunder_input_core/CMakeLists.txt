include(dependencies.cmake)

add_library(thunder_input_core STATIC
  src/input.c
)

target_include_directories(thunder_input_core PUBLIC include)

target_link_libraries(thunder_input_core PUBLIC ${PLUGIN_thunder_input_core_DEPENDENCIES})
