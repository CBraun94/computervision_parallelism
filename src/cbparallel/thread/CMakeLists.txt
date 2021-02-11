cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

# set(CBTHREAD_LIBS cbthread "cbtask" PARENT_SCOPE)

target_sources(cbthread
    PUBLIC
    "virtualcbthread.hpp" 
    "virtualcbthread.cpp"
    "cbthread.hpp"
    "cbthread.cpp"
    "cbworker.hpp" 
    "cbworker.cpp"
    "cbpoolworker.hpp"
    "cbpoolworker.cpp"
    "cbthreadpool.hpp"
    "cbthreadpool.cpp")

target_include_directories(cbthread PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(cbthread ${CBTHREAD_LIBS})
