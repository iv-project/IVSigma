# SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required (VERSION 3.25)

project(ivsigma)

add_library(ivsigma INTERFACE)
add_library(ivsigma::ivsigma ALIAS ivsigma)

target_include_directories(ivsigma INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(ivsigma INTERFACE cxx_std_20)
