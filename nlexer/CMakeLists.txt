option(NLEXER_NTKN "Opsi untuk membuild tkpn (token processor)" OFF)
option(NLEXER_STATIC_LIBRAY "Opsi untuk membuild nlexer static library" OFF)
option(NLEXER_UNIT_TEST "Opsi untuk membuild unit test nlexer" OFF)

file(GLOB_RECURSE LIB_SRC_FILES
    "lib/**/*.cc"
    "lib/*.cc"
)

# NLexer Library
if(NLEXER_STATIC_LIBRAY)
    add_library(libnlexer STATIC
        ${LIB_SRC_FILES}
    )

    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")

    target_include_directories(libnlexer PUBLIC
        "include"
    )

    target_link_libraries(libnlexer PRIVATE 
        ncpp
        ngrammar
    )
endif()

# NLexer
add_executable(nlexer "src/nlexer.cc")

target_link_libraries(nlexer PRIVATE
    libnlexer
)

# NTkn
if(NLEXER_NTKN)
    add_executable(ntkn "src/ntkn.cc")
    target_link_libraries(ntkn PRIVATE ncpp)
endif()

# NLexer Unit Test
if(NLEXER_UNIT_TEST)
    include("${CMAKE_SOURCE_DIR}/cmake/gtest.cmake")

    file(GLOB_RECURSE TEST_FILES
        "tests/**/*.cc"
        "tests/*.cc"
    )

    add_executable(nlexer_tests ${TEST_FILES})

    target_include_directories(nlexer_tests PRIVATE
        GoogleTest
    )

    target_link_libraries(nlexer_tests PRIVATE
        libnlexer
        GTest::gtest_main
    )
endif()