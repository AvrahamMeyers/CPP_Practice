cmake_minimum_required(VERSION 3.14)
project(ShapeRecognition)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header directory
include_directories(include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(external/googletest)
enable_testing()
add_subdirectory(test)
