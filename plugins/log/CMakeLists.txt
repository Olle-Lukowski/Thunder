include(dependencies.cmake)

add_library(log STATIC src/log.c)

target_include_directories(log PUBLIC include)

target_link_libraries(log PUBLIC ${PLUGIN_log_DEPENDENCIES})
