cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND 
    CMAKE_EXE_LINKER_FLAGS " -lpthread" " -fcoroutines" " -lrt")

add_library(cbtask "")
add_subdirectory(./task)
add_library(cbthread "")
add_subdirectory(./thread)
add_library(cbsync "")
add_subdirectory(./sync)

add_library(cbparallel SHARED cbtaskmanager.hpp)

target_link_libraries(cbparallel
    cbtask 
    cbthread
    cbsync)
