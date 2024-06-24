include(dependencies.cmake)

add_executable(window src/main.c)
target_link_libraries(window PUBLIC ${EXAMPLE_window_DEPENDENCIES})
