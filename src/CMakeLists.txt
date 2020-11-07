cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED PATHS "C:/opencv/build/x64/vc15")
include_directories(${OpenCV_INCLUDE_DIRS})

string(APPEND 
    CMAKE_EXE_LINKER_FLAGS " -lpthread" " -fcoroutines" " -lrt")

add_library(cbtask "")
add_subdirectory(./task)
add_library(cbthread "")
add_subdirectory(./thread)
add_library(cbsync "")
add_subdirectory(./sync)

add_executable(opencvtest main.cpp)

target_link_libraries(opencvtest 
    ${OpenCV_LIBS} 
    cbtask 
    cbthread
    cbsync)

 target_sources(opencvtest
    PRIVATE
    "distortion.hpp"
    "distortion.cpp"
    "example_one.hpp"
    "example_two.hpp"
    "example_three.hpp"
    "example_four.hpp"
    "log.hpp")
