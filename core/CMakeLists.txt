cmake_minimum_required(VERSION 3.11)
project(graph_core)

include(GetProjectFiles)
include(SetCompilerOptions)

set(CORE_FILES)
get_project_files(CORE_FILES)

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
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost")
	return()
endif()

add_library(${PROJECT_NAME} STATIC ${CORE_FILES})

set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${Boost_INCLUDE_DIRS}"
)