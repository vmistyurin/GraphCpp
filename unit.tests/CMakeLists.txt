cmake_minimum_required(VERSION 3.2)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
project(unit.tests)

include(GetProjectFiles)
include(SetCompilerOptions)

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

