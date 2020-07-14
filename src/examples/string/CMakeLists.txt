cmake_minimum_required(VERSION 2.8)
project(string)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../)

set(SOURCE_FILES
    string.cc
    )

set(TARGET string)

add_executable(${TARGET} ${SOURCE_FILES})

if (WIN32)
        target_link_libraries(${TARGET} ../../../../build/lib/base)
else (WIN32)
        target_link_libraries(${TARGET} pthread)
endif(WIN32)