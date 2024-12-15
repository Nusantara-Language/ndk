if(CMAKE_CURRENT_SOURCE_DIR STREQUAL "${PROJECT_SOURCE_DIR}")

cmake_minimum_required(VERSION 3.31)

project(sleeplib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_COMPILER "C:/msys64/clang64/bin/clang")
set(CMAKE_CXX_COMPILER "C:/msys64/clang64/bin/clang++")
set(CMAKE_LINKER "C:/msys64/clang64/bin/lld")
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -stdlib=libc++ -IC:/msys64/clang64/include/c++/v1 -LC:/msys64/clang64/lib/clang/19/lib/windows")

endif()

include_directories("include")

file(GLOB_RECURSE SOURCES src/*.cc)

add_library(sleeplib STATIC
    "src/sleep.cc"
    "include/sleep.h"
)

set_target_properties(sleeplib PROPERTIES PREFIX "")
target_include_directories(sleeplib PUBLIC "include")