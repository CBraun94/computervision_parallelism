cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND 
    CMAKE_EXE_LINKER_FLAGS " -lpthread" " -fcoroutines" " -lrt")

add_library(cbctrl SHARED "")
add_subdirectory(./ctrl)
add_library(cbsync SHARED "")
add_subdirectory(./sync)
add_library(cbtask SHARED "")
add_subdirectory(./task)
add_library(cbthread SHARED "")
add_subdirectory(./thread)
add_library(cbutil SHARED "")
add_subdirectory(./util)

add_library(cbparallel SHARED "")

target_sources(cbparallel
    PUBLIC
    "cbmain.hpp")

target_link_libraries(cbparallel
    cbctrl
    cbsync
    cbtask 
    cbthread
    cbutil
    )

set_target_properties(cbparallel PROPERTIES PUBLIC_HEADER ./include/libcbparallel.hpp)

target_include_directories(cbparallel PRIVATE ctrl)
target_include_directories(cbparallel PRIVATE include)
target_include_directories(cbparallel PRIVATE sync)
target_include_directories(cbparallel PRIVATE task)
target_include_directories(cbparallel PRIVATE thread)
target_include_directories(cbparallel PRIVATE util)

#install(TARGETS cbparallel DESTINATION ${CMAKE_INSTALL_LIBDIR})
#install(FILES libcbparallel.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})    
