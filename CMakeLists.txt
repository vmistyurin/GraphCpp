cmake_minimum_required(VERSION 3.11)
project(GraphCpp.project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(SOLUTION_OUTPUT_BIN_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory("${CMAKE_SOURCE_DIR}/core")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/googletest")
add_subdirectory("${CMAKE_SOURCE_DIR}/deps/gsl")
add_subdirectory("${CMAKE_SOURCE_DIR}/unit_tests")
add_subdirectory("${CMAKE_SOURCE_DIR}/benchmarks")

