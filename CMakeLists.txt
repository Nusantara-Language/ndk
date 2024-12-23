# Versi cmake
cmake_minimum_required(VERSION 3.31)

# Nama proyek
project(nusantara VERSION 0.0.1)

# Opsi untuk tipe build (Debug/Release)
option(CMAKE_BUILD_TYPE "Build type (Debug/Release)" "Debug")

# C++ Standar
set(CMAKE_CXX_STANDARD 23)

# Tentukan Compiler dan Linker secara fleksibel
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_LINKER "lld")

# Tentukan flag tambahan untuk compiler C++
set(CXX_INCLUDE_FOLDER "C:/msys64/clang64/include/c++/v1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-w64-windows-gnu -static -stdlib=libc++ -I${CXX_INCLUDE_FOLDER} -O3 -ffast-math -funroll-loops -flto -march=native -fomit-frame-pointer -fdata-sections -ffunction-sections -ftree-vectorize -mtune=native -fno-math-errno -falign-functions -fno-builtin -fstrict-aliasing -fvisibility=hidden")

# Linker flags
set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -fuse-ld=lld")

# Export compile command untuk clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Folder hasil build
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INCLUDE_DIRECTORY ${CMAKE_BINARY_DIR}/include)

# Output direktori berdasarkan build type
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_INCLUDE_DIRECTORY_DEBUG ${CMAKE_INCLUDE_DIRECTORY})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_INCLUDE_DIRECTORY_RELEASE ${CMAKE_INCLUDE_DIRECTORY})

# Sub folder proyek
add_subdirectory(nstdcpp)
add_subdirectory(nusantara)