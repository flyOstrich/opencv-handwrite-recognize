cmake_minimum_required(VERSION 3.3)
project(untitled)
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp mousedraw.cpp mousedraw.h)
add_executable(untitled ${SOURCE_FILES})
target_link_libraries( untitled ${OpenCV_LIBS} )