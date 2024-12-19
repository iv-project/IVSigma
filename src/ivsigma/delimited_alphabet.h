// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "concepts.h"

#include <array>
#include <cstddef>

namespace ivs {

/**
 * An alphabet with an additional initial '$' at rank 0
 */
template <typename Alphabet, bool isAlphabet = alphabet_c<Alphabet>, bool hasCompl = alphabet_with_complement_c<Alphabet>>
struct delimited_alphabet;

template <alphabet_c Alphabet>
struct delimited_alphabet<Alphabet, true, false> {
    //! Table representing conversion from rank to char
    template <char Unknown>
    static constexpr std::array<char, 256> rank_to_char_table{[]() {
        auto table = std::array<char, 256>{};
        for (size_t i{1}; i < 256; ++i) {
            table[i] = Alphabet::template rank_to_char<Unknown>(i-1);
        }
        table[0] = '$';
        return table;
    }()};

    //! Table representing conversion from char to rank
    template <uint8_t Unknown>
    static constexpr std::array<uint8_t, 256> char_to_rank_table{[]() {
        auto table = std::array<uint8_t, 256>{};
        for (size_t i{0}; i < 256; ++i) {
            table[i] = Alphabet::template char_to_rank<Unknown>(i);
            if (table[i] != 255) {
                table[i] += 1;
            }
        }
        table['$'] = 0;
        return table;
    }()};

    //! Table normalizing a char
    template <char Unknown>
    static constexpr std::array<char, 256> normalize_char_table{[]() {
        auto table = std::array<char, 256>{};
        for (size_t i{0}; i < 256; ++i) {
            table[i] = Alphabet::template normalize_char<Unknown>(i);
        }
        return table;
    }()};

public:
    /*! \brief Converts a single char value to a rank value
     *
     * \param c char value
     * \return corresponding rank value
     */
    template <uint8_t Unknown = 255>
    static constexpr auto char_to_rank(char c) noexcept -> uint8_t {
        auto index = static_cast<uint8_t>(c);
        return char_to_rank_table<Unknown>[index];
    }

    /*! \brief Converts a single rank value to a char value
     *
     * \param v a rank value
     * \return corresponding (normalized) char value
     */
    template <char Unknown = '\0'>
    static constexpr auto rank_to_char(uint8_t v) noexcept -> char {
        return rank_to_char_table<Unknown>[v];
    }

    /*! \brief Normalizes a single char
     *
     * \param c char value
     * \return corresponding normalized char value
     */
    template <char Unknown = '\0'>
    static constexpr auto normalize_char(char c) noexcept -> char {
        auto index = static_cast<uint8_t>(c);
        return normalize_char_table<Unknown>[index];
    }

    /*! \brief Returns size of the alphabet
     *
     * \return a size_t representing the size of the alphabet
     */
    static constexpr auto size() noexcept -> size_t {
        return Alphabet::size()+1;
    }
};

template <alphabet_with_complement_c Alphabet>
struct delimited_alphabet<Alphabet, true, true> : delimited_alphabet<Alphabet, true, false>{
private:
    using Parent = delimited_alphabet<Alphabet, true, false>;
    //! Table computing the complement in rank space (rank in, rank out)
    template <uint8_t Unknown>
    static constexpr std::array<uint8_t, 256> rank_complement_table{[]() {
        auto table = std::array<uint8_t, 256>{};
        table.fill(255);
        for (size_t i{0}; i < 255; ++i) {
            table[i+1] = Alphabet::template complement_rank<Unknown>(i)+1;
        }
        table[0] = 0;
        return table;
    }()};

public:
    using Parent::rank_to_char;
    using Parent::char_to_rank;
    using Parent::normalize_char;
    using Parent::size;

    /*! \brief computes complement based on ranks
     *
     * \param r a rank value
     * \return corresponding complement
     */
    template <uint8_t Unknown = 255>
    static constexpr auto complement_rank(uint8_t r) noexcept -> uint8_t {
        return rank_complement_table<Unknown>[r];
    }

    /*! \brief computes complement based on char
     *
     * \param c a char value
     * \return corresponding complement
     */
    template <char Unknown = '\0'>
    static constexpr auto complement_char(char c) noexcept -> char {
        return rank_to_char<Unknown>(complement_rank(char_to_rank(c)));
    }
};

}
