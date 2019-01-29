cmake_minimum_required(VERSION 3.11)
project(unit_tests)

include(GetProjectFiles)
include(SetCompilerOptions)

if(DEFINED BOOST_ROOT)    
    message(STATUS "BOOST_ROOT taken from command-line parameters")
elseif(DEFINED ENV{BOOST_ROOT})
    message(STATUS "BOOST_ROOT taken from environment variable")
    set(BOOST_ROOT $ENV{BOOST_ROOT})
else()
    message(STATUS "BOOST_ROOT not defined")
endif()

set(BOOST_COMPONENTS)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost MODULE COMPONENTS filesystem REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

option(USE_ALL_TESTS "Use all tests, included slow, helpers and utils tests" OFF)
if (USE_ALL_TESTS)
    add_definitions(-DUSE_SLOW_TESTS)
    add_definitions(-DUSE_UTILS_TESTS)
    add_definitions(-DUSE_HELPERS_TESTS)
endif()

option(USE_SLOW_TESTS "Use very slow tests, like graph equality test" OFF)
if (USE_SLOW_TESTS)
    add_definitions(-DUSE_SLOW_TESTS)
endif()

option(USE_UTILS_TESTS "Use utils tests, like check_symmetrical_matrix" OFF)
if (USE_UTILS_TESTS)
    add_definitions(-DUSE_UTILS_TESTS)
endif()

option(USE_HELPERS_TESTS "Use tests for tests helpers" OFF)
if (USE_HELPERS_TESTS)
    add_definitions(-DUSE_HELPERS_TESTS)
endif()

add_definitions(-DTEST_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/test_data/")

set(TESTS_FILES)
get_project_files(TESTS_FILES)

add_executable(${PROJECT_NAME} ${TESTS_FILES})

set_compiler_options()

target_compile_definitions(${PROJECT_NAME} PUBLIC GTEST_LANG_CXX11)

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/core"
    "${CMAKE_SOURCE_DIR}/deps/googletest/include"
    "${Boost_INCLUDE_DIRS}"
)

target_link_libraries(${PROJECT_NAME} graph_core)
target_link_libraries(${PROJECT_NAME} gtest)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

