# ZoomDB is a SQL database management system.
# Copyright (c) 2024, Niz <mn@furzoom.com>, Furzoom.com
# https://furzoom.com
# https://github.com/deiio/zoomdb
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

PROJECT(ZoomDB CXX)

SET(CXX_FLAGS
    -g
    -Wall
    -Wextra
    -Werror
    -Wconversion
    -Wold-style-cast
    -Wpointer-arith
    -Wshadow
    -Wwrite-strings
)

STRING(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

OPTION(ZOOMDB_ASAN "enable sanitizer?" OFF)
if(ZOOMDB_ASAN)
    SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fsanitize=address")
endif()

SET(CMAKE_CXX_FLAGS_DEBUG "-O0")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED on)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

SET(BUILD_TYPE "DEBUG")
IF(CMAKE_BUILD_TYPE)
    STRING(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
ENDIF()
IF(BUILD_TYPE STREQUAL "DEBUG")
    SET(CMAKE_VERBOSE_MAKEFILE ON)
ENDIF()

MESSAGE(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

INCLUDE_DIRECTORIES(src/include)
INCLUDE_DIRECTORIES(third_party/libpg_query)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(third_party)
ADD_SUBDIRECTORY(test)