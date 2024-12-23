include_directories("include")

# Mencari semua file .cpp dalam subdirektori libs dan sub-subdirektorinya
file(GLOB_RECURSE SOURCES
"lib/**/*.cpp"
"utils/**/*.cpp"
)

# Mencari semua file .hpp dalam subdirektori includes dan sub-subdirektorinya
file(GLOB_RECURSE HEADERS
"include/**/*.hpp"
)

# Menambahkan sumber file ke dalam target
add_library(nstdcpp STATIC
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(nstdcpp PROPERTIES PREFIX "")
target_include_directories(nstdcpp PUBLIC "include")