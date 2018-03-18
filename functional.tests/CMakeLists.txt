cmake_minimum_required(VERSION 3.2)
project(functional.tests)

include(GetProjectFiles)
include(SetCompilerOptions)

set(FUNCTIONAL_TESTS_FILES)
get_project_files(FUNCTIONAL_TESTS_FILES)

add_executable(${PROJECT_NAME} ${FUNCTIONAL_TESTS_FILES})

set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/core/include"
    "${CMAKE_SOURCE_DIR}/core/src"
)

target_link_libraries(${PROJECT_NAME} graph_core)

