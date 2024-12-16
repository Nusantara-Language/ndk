cmake_minimum_required(VERSION 3.31)

project(nusantara)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_COMPILER "C:/msys64/clang64/bin/clang")
set(CMAKE_CXX_COMPILER "C:/msys64/clang64/bin/clang++")
set(CMAKE_LINKER "C:/msys64/clang64/bin/lld")
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -fuse-ld=lld")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-w64-windows-gnu -static -stdlib=libc++ -IC:/msys64/clang64/include/c++/v1")
# Optional Arg -LC:/msys64/clang64/lib/clang/19/lib/windows

add_subdirectory("lib/sleep")
add_subdirectory(lexer)
add_subdirectory(parser)


