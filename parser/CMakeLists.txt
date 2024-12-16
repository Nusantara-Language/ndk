include_directories("include")

file(GLOB_RECURSE SOURCES src/*.cc)
add_executable(nparser ${SOURCES})

target_link_libraries(nparser PRIVATE nstdcpp)
target_link_libraries(nparser PRIVATE nlexerlib)