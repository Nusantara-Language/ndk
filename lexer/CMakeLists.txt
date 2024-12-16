include_directories("include")

file(GLOB_RECURSE SOURCES src/*.cc)
add_executable(nlexer ${SOURCES})

add_library(nlexerlib STATIC
    "src/lexer.cc"
    "include/lexer.h"
)

set_target_properties(nlexerlib PROPERTIES PREFIX "")
target_include_directories(nlexerlib PUBLIC "include")