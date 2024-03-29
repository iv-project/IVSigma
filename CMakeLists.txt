# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

# This file is called in the following scenarios
# 1. scenario: this file is at the root of a `cmake ..` call.
#       In this case we assume this project is compiled for packaging or testing.
# 2. scenario: another project is adding this directory via "add_subdirectory".
#       In this case we don't want any tests to be included.
cmake_minimum_required (VERSION 3.14)

# check if this is the main project
if (NOT DEFINED PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    if(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /EHsc")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    endif()
    set(ROOT_PROJECT TRUE)
endif ()

project(ivsigma LANGUAGES CXX VERSION "${IVIO_PROJECT_VERSION}"
            DESCRIPTION "ivsigma -- utilities function for dna4, dna5, aa and many more ... alphabets")

include(cmake/CPM.cmake)
include(ivsigma-config.cmake)

if (${ROOT_PROJECT})
    CPMaddPackage("gh:fmtlib/fmt#10.1.1")
#    CPMaddPackage("gh:catchorg/Catch2#v3.4.0")

    enable_testing()
    add_subdirectory(docs/snippets)
    add_subdirectory(src/test_ivsigma)
    add_subdirectory(src/test_header)
endif()
