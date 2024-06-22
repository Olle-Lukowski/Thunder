cmake_minimum_required(VERSION 3.10)
project(Thunder)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SELECTED_PLUGINS "" CACHE STRING "List of plugins to build")
set(EXAMPLES "" CACHE STRING "List of examples to build")

set_property(GLOBAL PROPERTY RESOLVED_PLUGINS "")

# Helper function to load dependencies
function(load_dependencies plugin)
  get_property(RESOLVED_PLUGINS GLOBAL PROPERTY RESOLVED_PLUGINS)
  include(${CMAKE_SOURCE_DIR}/plugins/${plugin}/dependencies.cmake)
  foreach(dependency IN LISTS PLUGIN_${plugin}_DEPENDENCIES)
    list(FIND RESOLVED_PLUGINS dependency resolved_index)
    if(resolved_index EQUAL -1)
      load_dependencies(${dependency})
      get_property(RESOLVED_PLUGINS GLOBAL PROPERTY RESOLVED_PLUGINS)
    endif()
  endforeach()

  list(APPEND RESOLVED_PLUGINS ${plugin})
  set_property(GLOBAL PROPERTY RESOLVED_PLUGINS ${RESOLVED_PLUGINS})
endfunction()

# Helper function to load example dependencies
function(load_example_dependencies example)
  get_property(RESOLVED_PLUGINS GLOBAL PROPERTY RESOLVED_PLUGINS)
  include(${CMAKE_SOURCE_DIR}/examples/${example}/dependencies.cmake)
  foreach(dependency IN LISTS EXAMPLE_${example}_DEPENDENCIES)
    list(FIND RESOLVED_PLUGINS dependency resolved_index)
    if(resolved_index EQUAL -1)
      load_dependencies(${dependency})
      get_property(RESOLVED_PLUGINS GLOBAL PROPERTY RESOLVED_PLUGINS)
    endif()
  endforeach()

  set_property(GLOBAL PROPERTY RESOLVED_PLUGINS ${RESOLVED_PLUGINS})
endfunction()

# Load the dependencies for each example
foreach(example IN LISTS EXAMPLES)
  load_example_dependencies(${example})
endforeach()

# Resolve dependencies for each selected plugin
foreach(plugin IN LISTS SELECTED_PLUGINS)
  load_dependencies(${plugin})
endforeach()

# print the resolved plugins
get_property(RESOLVED_PLUGINS GLOBAL PROPERTY RESOLVED_PLUGINS)
# to ensure we don't add a plugin twice
list(REMOVE_DUPLICATES RESOLVED_PLUGINS)

message(STATUS "Selected plugins: ${RESOLVED_PLUGINS}")

foreach(plugin IN LISTS RESOLVED_PLUGINS)
  add_subdirectory(${CMAKE_SOURCE_DIR}/plugins/${plugin})
endforeach()

foreach(example IN LISTS EXAMPLES)
  add_subdirectory(${CMAKE_SOURCE_DIR}/examples/${example})
endforeach()

