cmake_minimum_required(VERSION 3.11)
project(unit_tests)

include(GetProjectFiles)
include(SetCompilerOptions)

option(USE_ALL_TESTS "Use all tests, included slow, helpers and utils tests" OFF)
if (USE_ALL_TESTS)
    add_definitions(-DUSE_ALL_TESTS)
endif()

option(USE_SLOW_TESTS "Use very slow tests, like graph equality test" OFF)
if (USE_SLOW_TESTS)
    add_definitions(-DUSE_SLOW_TESTS)
endif()

option(USE_UTILS_TESTS "Use utils tests, like checgh_symmetrical_matrix" OFF)
if (USE_UTILS_TESTS)
    add_definitions(-DUSE_UTILS_TESTS)
endif()

option(USE_HELPERS_TESTS "Use tests for tests helpers" OFF)
if (USE_HELPERS_TESTS)
    add_definitions(-DUSE_HELPERS_TESTS)
endif()

set(TESTS_FILES)
get_project_files(TESTS_FILES)

add_executable(${PROJECT_NAME} ${TESTS_FILES})

set_compiler_options()

target_compile_definitions(${PROJECT_NAME} PUBLIC GTEST_LANG_CXX11)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/core/include"
    "${CMAKE_SOURCE_DIR}/core/src"
    "${CMAKE_SOURCE_DIR}/deps/googletest/include"
)

target_link_libraries(${PROJECT_NAME} graph_core)
target_link_libraries(${PROJECT_NAME} gtest)
