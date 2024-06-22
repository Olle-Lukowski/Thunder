include(dependencies.cmake)

add_library(log_sink_file STATIC src/file.c)

target_include_directories(log_sink_file PUBLIC include)

target_link_libraries(log_sink_file PUBLIC ${PLUGIN_log_sink_file_DEPENDENCIES})
