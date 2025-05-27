# Add GoogleTest from local directory
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)


enable_testing()

# Create test executable
add_executable(shape_tests shape_tests.cpp)

# Link against gtest and your library
target_link_libraries(shape_tests
  PRIVATE
    gtest_main
    shape_lib
    ${OpenCV_LIBS}
)

# Include directories for headers
target_include_directories(shape_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${OpenCV_INCLUDE_DIRS}
)

# Enable automatic test discovery
include(GoogleTest)
gtest_discover_tests(shape_tests)
