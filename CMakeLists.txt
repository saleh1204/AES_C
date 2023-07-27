cmake_minimum_required (VERSION 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(AES C)

option(BUILD_TESTS "Build test programs" OFF)
###############################################################################
# Set build features
set(CMAKE_BUILD_TYPE Release)
###############################################################################
# Set output binary location
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
###############################################################################
# Set Compiler Flags
set(CMAKE_C_FLAGS "-O0 -Wall -fpic")
###############################################################################
# Set Compiler Standard
set(CMAKE_C_STANDARD 11)
###############################################################################
# Subdirectories
add_subdirectory(src)
if(BUILD_TESTS)
  add_subdirectory(tests)
endif(BUILD_TESTS)


