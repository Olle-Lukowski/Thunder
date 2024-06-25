include(dependencies.cmake)

add_library(thunder_log_sink_console STATIC src/console.c)

target_include_directories(thunder_log_sink_console PUBLIC include)

target_link_libraries(thunder_log_sink_console PUBLIC ${PLUGIN_thunder_log_sink_console_DEPENDENCIES})
