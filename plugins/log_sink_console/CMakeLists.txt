include(dependencies.cmake)

add_library(log_sink_console STATIC src/console.c)

target_include_directories(log_sink_console PUBLIC include)

target_link_libraries(log_sink_console PUBLIC ${PLUGIN_log_sink_console_DEPENDENCIES})
