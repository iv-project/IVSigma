// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace ivs {

template <typename Alphabet>
concept alphabet_c = requires(Alphabet) {
    { Alphabet::char_to_rank(char{}) } -> std::same_as<uint8_t>;
    { Alphabet::rank_to_char(uint8_t{}) } -> std::same_as<char>;
    { Alphabet::normalize_char(char{}) } -> std::same_as<char>;
    { Alphabet::size() } -> std::same_as<size_t>;
};

template <typename Alphabet>
concept alphabet_with_complement_c = requires(Alphabet) {
    { Alphabet::char_to_rank(char{}) } -> std::same_as<uint8_t>;
    { Alphabet::rank_to_char(uint8_t{}) } -> std::same_as<char>;
    { Alphabet::normalize_char(char{}) } -> std::same_as<char>;
    { Alphabet::size() } -> std::same_as<size_t>;
    { Alphabet::complement_rank(uint8_t{}) } -> std::same_as<uint8_t>;
    { Alphabet::complement_char(char{}) } -> std::same_as<char>;
};


}
