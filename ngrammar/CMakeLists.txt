find_package(antlr4-runtime REQUIRED)

file(GLOB_RECURSE SRC_FILES
  "src/**/*.cpp"
  "src/**/*.h"
  "src/*.cpp"
  "src/*.h"
)

add_library(ngrammar ${SRC_FILES})

target_compile_definitions(ngrammar PRIVATE 
    ANTLR4CPP_STATIC 
    ANTLR4_USE_THREAD_LOCAL_CACHE
)

target_include_directories(ngrammar PUBLIC
    antlr4_static
    "src"
)

target_link_libraries(ngrammar PRIVATE 
    antlr4_static
)
