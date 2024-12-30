include("${CMAKE_SOURCE_DIR}/cmake/fetch_content.cmake")

if(NOT googletest_POPULATED)
  # GTest Init
  FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/7d76a231b0e29caf86e68d1df858308cd53b2a66.zip
  )
  
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()
