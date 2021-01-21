cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

target_sources(cbsync
    PUBLIC
    "eventposix.hpp" 
    "eventposix.cpp"
    "semaphoreposix.hpp"
    "semaphoreposix.cpp")
    
target_include_directories (cbsync PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
