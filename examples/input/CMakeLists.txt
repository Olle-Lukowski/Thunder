include(dependencies.cmake)

add_executable(input src/main.c)
target_link_libraries(input PUBLIC ${EXAMPLE_input_DEPENDENCIES})
