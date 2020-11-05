cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

target_sources(cbtask
    PUBLIC
    "cbtask.hpp"
    "cbtask.cpp"
    "cbtaskanonymous.hpp"
    "cbtaskanonymous.cpp"
    "cbtaskfor.hpp"
    "cbtaskfor.cpp")

    target_include_directories (cbtask PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
