# Add your library
add_library(shape_lib STATIC shape_recognition.cpp)

# Optional: if you later link OpenCV, do it here
# find_package(OpenCV REQUIRED)
# target_link_libraries(shape_lib ${OpenCV_LIBS})
