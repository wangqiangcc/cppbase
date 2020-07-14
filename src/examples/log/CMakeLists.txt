cmake_minimum_required(VERSION 2.8)
project(log)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../)

if(WIN32)
add_definitions(-DNOMINMAX)
endif()


set(SOURCE_FILES
    log.cc
    )

set(TARGET log)

add_executable(${TARGET} ${SOURCE_FILES})

if (WIN32)
        target_link_libraries(${TARGET} ../../../../build/lib/base)
else (WIN32)
        target_link_libraries(${TARGET} pthread)
endif(WIN32)