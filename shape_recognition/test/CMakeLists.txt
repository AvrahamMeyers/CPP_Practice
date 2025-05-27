# Add the test executable
add_executable(shape_tests shape_tests.cpp)

# Link to gtest, gtest_main, and your library
target_link_libraries(shape_tests
  shape_lib
  gtest
  gtest_main
)

# Tell CTest about the tests
include(GoogleTest)
gtest_discover_tests(shape_tests)
