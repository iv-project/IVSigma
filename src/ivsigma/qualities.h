// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "alphabet.h"

#include <cstddef>

namespace ivs {

template <size_t Size, char Offset>
struct ranged_alphabet {
    /*! \brief Converts a single char value to a rank value
     *
     * \param c char value
     * \return corresponding rank value
     */
    template <uint8_t Unknown = 255>
    static constexpr auto char_to_rank(char c) noexcept -> uint8_t {
        if (c < Offset or c-Offset > Size) {
            return Unknown;
        }
        return c - Offset;
    }

    /*! \brief Converts a single rank value to a char value
     *
     * \param v a rank value
     * \return corresponding (normalized) char value
     */
    template <char Unknown = '\0'>
    static constexpr auto rank_to_char(uint8_t v) noexcept -> char {
        if (v > Size) return Unknown;
        return v + Offset;
    }
};


using pthred42       = ranged_alphabet<42, '!'>;
using pthred63       = ranged_alphabet<63, '!'>;
using pthred68solexa = ranged_alphabet<68, ';'>;
using pthred94       = ranged_alphabet<94, '!'>;

}
