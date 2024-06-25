include(dependencies.cmake)

add_library(thunder_log STATIC src/log.c)

target_include_directories(thunder_log PUBLIC include)

target_link_libraries(thunder_log PUBLIC ${PLUGIN_thunder_log_DEPENDENCIES})
