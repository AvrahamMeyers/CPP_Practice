add_library(shape_lib STATIC shape_recognition.cpp)

# Point to OpenCV config directory explicitly (optional, only if you don't pass -DOpenCV_DIR)
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/opencv_install/x64/mingw/lib")

find_package(OpenCV REQUIRED)

target_link_libraries(shape_lib PRIVATE ${OpenCV_LIBS})
target_include_directories(shape_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})

add_executable(shape_recognizer main.cpp)
target_link_libraries(shape_recognizer PRIVATE shape_lib)
target_include_directories(shape_recognizer PRIVATE ${OpenCV_INCLUDE_DIRS})

add_custom_command(TARGET shape_recognizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/opencv_install/x64/mingw/bin"
    "$<TARGET_FILE_DIR:shape_recognizer>"
)
