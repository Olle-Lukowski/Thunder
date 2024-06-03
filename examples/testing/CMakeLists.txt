include(dependencies.cmake)

add_executable(testing src/main.c)
target_include_directories(testing PUBLIC src)
target_link_libraries(testing PRIVATE ${EXAMPLE_TESTING_DEPENDENCIES})
