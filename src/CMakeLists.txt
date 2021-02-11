cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


string(APPEND 
    CMAKE_EXE_LINKER_FLAGS " -lpthread" " -fcoroutines" " -lrt")

add_subdirectory(./cbparallel)
add_subdirectory(./examples)

add_executable(opencvtest main.cpp)

target_link_libraries(opencvtest 
    cbparallel
    cbexamples)
