cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED PATHS "C:/opencv/build/x64/vc15")
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(cbexamples SHARED "")

target_sources(cbexamples
    PUBLIC
    "example_main.hpp"
    "log.hpp"
    "distortion.hpp"
    "distortion.cpp"
    "example_one.hpp"
    "example_two.hpp"
    "example_three.hpp"
    "example_four.hpp")

target_include_directories (cbexamples PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cbexamples 
    ${OpenCV_LIBS})
