# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required (VERSION 3.25)

project(ivsigma LANGUAGES CXX VERSION "${IVIO_PROJECT_VERSION}"
            DESCRIPTION "ivsigma -- utilities function for dna4, dna5, aa and many more ... alphabets")

include(cmake/CPM.cmake)
CPMAddPackage("gh:SGSSGene/cpm.dependencies@1.0.0")
CPMLoadDependenciesFile("${CMAKE_CURRENT_SOURCE_DIR}/cpm.dependencies")

include(ivsigma-config.cmake)

if (PROJECT_IS_TOP_LEVEL)
    if(WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /EHsc")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS_EQUAL 12.9)
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
    endif ()

    enable_testing()
    add_subdirectory(docs/snippets)
    add_subdirectory(src/test_ivsigma)
    add_subdirectory(src/test_header)
endif()
