cmake_minimum_required(VERSION 3.3)
project(opencv-handwrite-recognize)
find_package( OpenCV REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp mouse-draw/mousedraw.cpp mouse-draw/mousedraw.h train/train.cpp train/train.h common.h common.h)
add_executable(opencv-handwrite-recognize ${SOURCE_FILES})
target_link_libraries(opencv-handwrite-recognize ${OpenCV_LIBS} )

