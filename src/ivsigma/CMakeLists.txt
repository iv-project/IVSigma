cmake_minimum_required (VERSION 3.14)

project(ivsigma)

add_library(ivsigma INTERFACE)
add_library(ivsigma::ivsigma ALIAS ivsigma)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
)

