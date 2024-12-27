# Opsi untuk memperlihatkan waktu eksekusi (ON/OFF)
option(PERLIHATKAN_WAKTU_EKSEKUSI "Memperlihatkan waktu yang di perlukan program untuk di eksekusi sampai selesai." ON)

# Versi proyek
set(NUSANTARA_VERSION_SUFFIX "-dev")
set(NUSANTARA_VERSION "0.0.1${NUSANTARA_VERSION_SUFFIX}")

# Perlihatkan waktu eksekusi
set(PERLIHATKAN_WAKTU_EKSEKUSI ON)

# Atur versi header sesuai template
configure_file(${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/konfig.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/konfig.hpp)
configure_file(${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/versi.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/muat/konfig/versi.hpp)

# SRC FILE
file(GLOB_RECURSE LIB_SOURCES 
  "pustaka/**/*.cpp" 
  "pustaka/*.cpp"
)

# Executable
add_executable(nusantara "program/abp/abp_main.cpp" "program/abp/abp.cpp" ${LIB_SOURCES})
add_executable(tests "program/test/test.cpp" ${LIB_SOURCES})

# Include folder
target_include_directories(tests PRIVATE "muat")
target_include_directories(nusantara PRIVATE "muat")
target_include_directories(nusantara PRIVATE "${CMAKE_SOURCE_DIR}/pustaka_eksternal/muat")
target_include_directories(nusantara PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(nusantara PRIVATE ${CLANG_INCLUDE_DIRS})
target_include_directories(nusantara PRIVATE ${LLD_INCLUDE_DIRS})

# Library folder
link_directories(${LLVM_LIBRARY_DIRS})

# Link library
target_link_libraries(nusantara PRIVATE
# C++
libc++.a
libc++abi.a
libunwind.a
)