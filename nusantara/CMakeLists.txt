# Opsi untuk memperlihatkan waktu eksekusi (ON/OFF)
option(PERLIHATKAN_WAKTU_EKSEKUSI "Memperlihatkan waktu yang di perlukan program untuk di eksekusi sampai selesai." ON)

# Versi proyek
set(NUSANTARA_VERSION_SUFFIX "-dev")
set(NUSANTARA_VERSION "0.0.1${NUSANTARA_VERSION_SUFFIX}")

# Perlihatkan waktu eksekusi
set(PERLIHATKAN_WAKTU_EKSEKUSI ON)

# Atur versi header sesuai template
configure_file(${CMAKE_SOURCE_DIR}/nusantara/include/konfig/konfig.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/include/konfig/konfig.hpp)
configure_file(${CMAKE_SOURCE_DIR}/nusantara/include/konfig/versi.hpp.template ${CMAKE_SOURCE_DIR}/nusantara/include/konfig/versi.hpp)

# SRC FILE
file(GLOB_RECURSE LIB_SOURCES 
  "lib/**/*.cpp" 
  "lib/*.cpp"
)

# Executable
add_executable(nusantara "src/abp/abp_main.cpp" "src/abp/abp.cpp" ${LIB_SOURCES})

# Include folder
set(FOLDER_MUAT_INTERNAL "include")
set(FOLDER_MUAT_EKSTERNAL "${CMAKE_SOURCE_DIR}/libs/argparse/include")

set(
  FOLDER_MUAT_NUSANTARA
  ${FOLDER_MUAT_INTERNAL}
  ${FOLDER_MUAT_EKSTERNAL}
)

# Target include
target_include_directories(nusantara PRIVATE ${FOLDER_MUAT_NUSANTARA})