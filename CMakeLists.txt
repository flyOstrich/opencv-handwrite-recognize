cmake_minimum_required(VERSION 3.3)
project(opencv-handwrite-recognize)
find_package( OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp mousedraw.cpp mousedraw.h train.cpp)
add_executable(opencv-handwrite-recognize ${SOURCE_FILES})
target_link_libraries(opencv-handwrite-recognize ${OpenCV_LIBS} )

