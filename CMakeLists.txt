cmake_minimum_required(VERSION 3.31)

set(This Mobileye)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)



set(Sources
    find_line_in_image.cpp
)

add_library(${This} STATIC ${Sources})

add_subdirectory(test)