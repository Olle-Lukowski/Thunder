include(dependencies.cmake)

add_library(thunder_log_sink_file STATIC src/file.c)

target_include_directories(thunder_log_sink_file PUBLIC include)

target_link_libraries(thunder_log_sink_file PUBLIC ${PLUGIN_thunder_log_sink_file_DEPENDENCIES})
