cmake_minimum_required(VERSION 2.8)

project(event C) 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
message("Current build type is : ${CMAKE_BUILD_TYPE}")
message("path is  : ${PROJECT_SOURCE_DIR}")
message("sysmtem name is  : ${CMAKE_SYSTEM_NAME}")

# compiler flags.
if (UNIX)
    set(CMAKE_CXX_FLAGS
        -ggdb
        -Wall
        -Wextra 
        -Woverloaded-virtual
        -Wno-unused-parameter
        -Wno-missing-field-initializers 
    )
elseif(WIN32)
    set(CMAKE_CXX_FLAGS 
        /Zi 
        /nologo  
        /EHsc 
        /GS 
        /Gd 
        /GR 
        /GF 
        /fp:precise 
        /Zc:wchar_t 
        /Zc:forScope 
        /errorReport:queue
        /FC
        /W3 
        /WX- 
        /wd4351 /wd4355 /wd4396 /wd4503 /wd4819 /wd4100 /wd4121 /wd4125 
        /wd4127 /wd4130 /wd4131 /wd4189 /wd4201 /wd4238 /wd4244 /wd4245 
        /wd4310 /wd4428 /wd4481 /wd4505 /wd4510 /wd4512 /wd4530 /wd4610 
        /wd4611 /wd4701 /wd4702 /wd4706 /wd4018 /wd4091 /wd4996 /wd4251
    )

	if(${MSVC_VERSION} GREATER 1700)
		LIST(APPEND CMAKE_CXX_FLAGS
			/d2Zi+ 
			)
	endif()
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()


include_directories(
	${PROJECT_SOURCE_DIR}/
	${PROJECT_SOURCE_DIR}/../../../
)

if (APPLE)
set(CMAKE_MACOSX_RPATH 1)
endif()

if (UNIX)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 ")
endif()

add_compile_options(-DHAVE_CONFIG_H)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../../../../build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../../../../build/bin)

set(SOURCES 
buffer.c
evbuffer.c
evdns.c
event.c
event_tagging.c
evrpc.c
evutil.c
http.c
log.c
poll.c
select.c
signal.c
strlcpy.c
)


IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	include_directories( ${PROJECT_SOURCE_DIR}/linux )

	LIST(APPEND SOURCES
	epoll.c
    )
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	# Windows
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	include_directories( ${PROJECT_SOURCE_DIR}/freebsd )

	LIST(APPEND SOURCES
	kqueue.c
    )
ELSEIF ()
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	include_directories( ${PROJECT_SOURCE_DIR}/mac )

	LIST(APPEND SOURCES
	kqueue.c
    )
ELSE ()
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

source_group_by_dir(SOURCES)
add_library(event SHARED ${SOURCES})


if (WIN32)
        target_link_libraries(event Netapi32 PowrProf Setupapi Version Dbghelp Ws2_32 Shlwapi)
else (WIN32)
        target_link_libraries(event dl pthread)
endif(WIN32)
