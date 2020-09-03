cmake_minimum_required(VERSION 2.8)
project(path)

set(CMAKE_CXX_STANDARD 11)

if(WIN32)
add_definitions(-DNOMINMAX)
endif()

include_directories(../../)

set(SOURCE_FILES
    path.cc
    )

set(TARGET path)

add_executable(${TARGET} ${SOURCE_FILES})

if (WIN32)
        target_link_libraries(${TARGET} base)
else (WIN32)
        target_link_libraries(${TARGET} pthread)
endif(WIN32)