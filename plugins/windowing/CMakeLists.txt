include(dependencies.cmake)

add_library(windowing STATIC
  src/module.c
)

target_include_directories(windowing PUBLIC include)

target_link_libraries(windowing PUBLIC ${PLUGIN_windowing_DEPENDENCIES})
