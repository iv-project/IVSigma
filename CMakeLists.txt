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
else()
    set(ROOT_PROJECT FALSE)
endif ()


project(IVSigma)

add_subdirectory(src/ivsigma)

if (${ROOT_PROJECT})
#    find_package (fmt REQUIRED)

#    add_subdirectory(lib/Catch2)
    enable_testing()

    add_subdirectory(snippets)
#    add_subdirectory(src/test_fmindex-collection)
#    add_subdirectory(src/test_search_schemes)
endif()