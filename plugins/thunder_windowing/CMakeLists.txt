include(dependencies.cmake)

add_library(thunder_windowing STATIC
  src/module.c
)

target_include_directories(thunder_windowing PUBLIC include)

target_link_libraries(thunder_windowing PUBLIC ${PLUGIN_thunder_windowing_DEPENDENCIES})
