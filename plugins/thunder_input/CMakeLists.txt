include(dependencies.cmake)

add_library(thunder_input STATIC
  src/module.c
)

target_include_directories(thunder_input PUBLIC include)

target_link_libraries(thunder_input PUBLIC ${PLUGIN_thunder_input_DEPENDENCIES})
