cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

target_sources(cbctrl
    PUBLIC
    "cbctrl.hpp"
    "cbctrl.cpp")

target_include_directories (cbctrl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
