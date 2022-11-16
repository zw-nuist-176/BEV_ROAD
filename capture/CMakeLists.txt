cmake_minimum_required(VERSION 3.23)
project(capture)

set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(capture main.cpp lane_detection.cpp lane_detection.h)

target_link_libraries( capture ${OpenCV_LIBS} )