include(dependencies.cmake)

include(FetchContent)

FetchContent_Declare(
  pthread
  GIT_REPOSITORY https://github.com/GerHobbelt/pthread-win32.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(pthread)

add_library(pthread_win32 INTERFACE)
target_link_libraries(pthread_win32 INTERFACE pthreadVC3)
