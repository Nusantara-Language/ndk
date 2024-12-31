# Versi cmake
cmake_minimum_required(VERSION 3.31)

# Nama proyek
project(NDK VERSION 0.0.1)

# Opsi untuk tipe build (Debug/Release)
option(CMAKE_BUILD_TYPE "Build type (Debug/Release)" "Release")

# C++ Standar
set(CMAKE_CXX_STANDARD 23)

# Tentukan Linker secara fleksibel
set(CMAKE_LINKER "lld")
# Mengatur ccache
set(CMAKE_C_COMPILER_LAUNCHER "ccache")
set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")

# Tentukan flag tambahan untuk compiler C++
set(CXX_INCLUDE_FOLDER "C:/msys64/clang64/include/c++/v1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-w64-windows-gnu -static -stdlib=libc++ -I${CXX_INCLUDE_FOLDER}") #-O3 -ffast-math -funroll-loops -flto -march=native -fomit-frame-pointer -fdata-sections -ffunction-sections -ftree-vectorize -mtune=native -fno-math-errno -falign-functions -fno-builtin -fstrict-aliasing -fvisibility=hidden

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math -funroll-loops -flto -march=native -fomit-frame-pointer -fdata-sections -ffunction-sections -ftree-vectorize -mtune=native -fno-math-errno -falign-functions -fno-builtin -fstrict-aliasing -fvisibility=hidden")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

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

# Menghapus library prefix
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(NCPP_UNIT_TEST ON)
set(NLEXER_UNIT_TEST ON)
set(NLEXER_STATIC_LIBRAY ON)
set(NLEXER_TKPN ON)

set(NUSANTARA_PROJECT_BUILD 
  ncpp
  nlexer
  nparser
)

include("${CMAKE_SOURCE_DIR}/cmake/nusantara_project_build.cmake")