cmake_minimum_required(VERSION 3.20)

include(cmake/prelude.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

project(
    operatorFunctors
    VERSION 1.0.0
    DESCRIPTION "Improving the readability of simple (captureless) lambdas"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

include(cmake/variables.cmake)
include(cmake/clangformat.cmake)

# ---- Developer mode ----

if(operatorFunctors_DEVELOPER_MODE)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()

