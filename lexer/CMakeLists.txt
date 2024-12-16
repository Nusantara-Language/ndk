include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE INCLUDES include/*.hpp)
add_executable(nlexer ${SOURCES})

add_library(nlexerlib STATIC
    ${SOURCES}
    ${INCLUDES}
)

set_target_properties(nlexerlib PROPERTIES PREFIX "")
target_include_directories(nlexerlib PUBLIC "include")