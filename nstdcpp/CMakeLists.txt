include_directories("include")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_library(nstdcpp STATIC
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(nstdcpp PROPERTIES PREFIX "")
target_include_directories(nstdcpp PUBLIC "include")