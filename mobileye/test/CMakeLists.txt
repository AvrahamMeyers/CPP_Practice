cmake_minimum_required(VERSION 3.31)

set(This Tests)

set(Sources
    Tests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    PRIVATE
    GTest::gtest_main
    Mobileye
)

include(GoogleTest)  
gtest_discover_tests(${This})