include(dependencies.cmake)

include(FetchContent)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v4
)
FetchContent_MakeAvailable(flecs)

add_library(flecs ALIAS flecs_static)
