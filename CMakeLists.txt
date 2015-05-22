cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(posmotri)
set(POSMOTRI_VERSION 0.2.4)
add_definitions( -DPOSMOTRI_VERSION="${POSMOTRI_VERSION}" )

SET( CMAKE_MODULE_PATH ${posmotri_SOURCE_DIR}/cmake )

add_custom_target(dist
    COMMAND git archive --prefix=${PROJECT_NAME}.${VERSION}/ HEAD
        | bzip2 > ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.${VERSION}.tar.bz2
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")
set(CMAKE_CXX_FLAGS "$ENV{CPPFLAGS} ${CMAKE_CXX_FLAGS} -ffast-math")

include(CheckIncludeFile)
include(CheckLibraryExists)

add_subdirectory(src)

