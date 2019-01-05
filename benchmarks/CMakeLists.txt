cmake_minimum_required(VERSION 3.11)
project(benchmarks)

include(GetProjectFiles)
include(SetCompilerOptions)

set(FUNCTIONAL_TESTS_FILES)
get_project_files(FUNCTIONAL_TESTS_FILES)

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

add_executable(${PROJECT_NAME} ${FUNCTIONAL_TESTS_FILES})

set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/core"
    "${Boost_INCLUDE_DIRS}"
)

target_link_libraries(${PROJECT_NAME} graph_core)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

