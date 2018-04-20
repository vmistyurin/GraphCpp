cmake_minimum_required(VERSION 3.11)
project(graph_core)

include(GetProjectFiles)
include(SetCompilerOptions)

set(CORE_FILES)
get_project_files(CORE_FILES)

set(BOOST_COMPONENTS)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost::preprocessor")
	return()
endif()

add_library(${PROJECT_NAME} STATIC ${CORE_FILES})

set_compiler_options()

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY INCLUDE_DIRECTORIES 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${Boost_INCLUDE_DIRS}"
)