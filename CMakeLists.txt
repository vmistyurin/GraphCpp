cmake_minimum_required(VERSION 2.8)
project(fltk_test)

include(ExternalProject)
ExternalProject_Add(GTEST
  GIT_REPOSITORY https://github.com/google/googletest.git
  UPDATE_COMMAND ""
  SOURCE_DIR GTEST
  BINARY_DIR GTEST_BUILD
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/GTEST_INSTALL
)
set(GTEST_DIR ${CMAKE_BINARY_DIR}/GTEST_INSTALL)

add_executable(fltk_test WIN32 main.cpp)
add_dependencies(fltk_test GTEST)

# Use appropriate SuperBuild instead
include_directories(${GTEST_DIR}/include)
#target_link_libraries(fltk_test ${FLTK_DIR}/lib/fltkd.lib)