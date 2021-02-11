cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

target_sources(cbutil
    PUBLIC
    "cblog.hpp"
    "cblog.cpp")

target_include_directories (cbutil PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
