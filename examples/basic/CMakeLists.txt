include(dependencies.cmake)

add_executable(basic src/main.c)
target_link_libraries(basic PUBLIC ${EXAMPLE_basic_DEPENDENCIES})
