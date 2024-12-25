# Menambahkan direktori-pendukung ke dalam cakupan proyek
include_directories("muat")

# Mencari semua file .cpp dalam subdirektori libs dan sub-subdirektorinya
file(GLOB_RECURSE SOURCES
  "pustaka/**/*.cpp"
  "pustaka/*.cpp"
  "alat/**/*.cpp"
  "alat/*.cpp"
)

# Mencari semua file .hpp dalam subdirektori includes dan sub-subdirektorinya
file(GLOB_RECURSE HEADERS
  "muat/**/*.hpp"
  "muat/*.hpp"
)

# Membuat objek lib yang statis (tidak dapat diubah) dan menambahkan file C++ dan header ke dalam objek tersebut
add_library(nstdcpp STATIC 
    # Menambahkan semua file .cpp yang dtemukan melalui GLOB_RECURSE ke dalam objek nstdcpp
    ${SOURCES}
    # Menambahkan semua file .hpp yang ditemukan melalui GLOB_RECURSE ke dalam objek nstdcpp
    ${HEADERS}
)

# Menetapkan properti target nstdcpp sehingga prefix direktori tidak diterapkan
set_target_properties(nstdcpp PROPERTIES PREFIX "")

# Mengatur direktori include publik untuk target nstdcpp menjadi direktori "include"
target_include_directories(nstdcpp PUBLIC "muat")