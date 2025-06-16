// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "alphabet.h"

namespace ivs {

//                                                        rank, symbol,   alts...
struct aa10li : alphabet<    rank_char_mappings<
                                        rank_char_mapping<   0,    'A',   'a', 'S', 's', 'T', 't', 'X', 'x'>,
                                        rank_char_mapping<   1,    'B',   'b', 'D', 'd', 'E', 'e', 'Q', 'q', 'Z', 'z'>,
                                        rank_char_mapping<   2,    'C',   'c', 'U', 'u'>,
                                        rank_char_mapping<   3,    'F',   'f', 'W', 'w', 'Y', 'y', '*'>,
                                        rank_char_mapping<   4,    'G',   'g'>,
                                        rank_char_mapping<   5,    'H',   'h', 'N', 'n'>,
                                        rank_char_mapping<   6,    'I',   'i', 'V', 'v'>,
                                        rank_char_mapping<   7,    'J',   'j', 'L', 'l', 'M', 'm'>,
                                        rank_char_mapping<   8,    'K',   'k', 'O', 'o', 'R', 'r'>,
                                        rank_char_mapping<   9,    'P',   'p'>
                                    >>
{};
static_assert(alphabet_c<aa10li>, "Unit test: is supposed to model an alphabet");

struct aa10murphy : alphabet<rank_char_mappings<
                                        rank_char_mapping<   0,    'A',   'a'>,
                                        rank_char_mapping<   1,    'B',   'b', 'D', 'd', 'E', 'e', 'N', 'n', 'Q', 'q', 'Z', 'z'>,
                                        rank_char_mapping<   2,    'C',   'c', 'U', 'u'>,
                                        rank_char_mapping<   3,    'F',   'f', 'W', 'w', 'Y', 'y', '*'>,
                                        rank_char_mapping<   4,    'G',   'g'>,
                                        rank_char_mapping<   5,    'H',   'h'>,
                                        rank_char_mapping<   6,    'I',   'i', 'J', 'j', 'L', 'l', 'M', 'm', 'V', 'v'>,
                                        rank_char_mapping<   7,    'K',   'k', 'O', 'o', 'R', 'r'>,
                                        rank_char_mapping<   8,    'P',   'p'>,
                                        rank_char_mapping<   9,    'S',   's', 'T', 't', 'X', 'x'>
                                    >>
{};
static_assert(alphabet_c<aa10murphy>, "Unit test: is supposed to model an alphabet");

struct aa20 : alphabet<      rank_char_mappings<
                                        rank_char_mapping<   0,    'A',   'a'>,
                                        rank_char_mapping<   1,    'C',   'c', 'U', 'u'>,
                                        rank_char_mapping<   2,    'D',   'd', 'B', 'b'>,
                                        rank_char_mapping<   3,    'E',   'e', 'Z', 'z'>,
                                        rank_char_mapping<   4,    'F',   'f'>,
                                        rank_char_mapping<   5,    'G',   'g'>,
                                        rank_char_mapping<   6,    'H',   'h'>,
                                        rank_char_mapping<   7,    'I',   'i'>,
                                        rank_char_mapping<   8,    'K',   'k'>,
                                        rank_char_mapping<   9,    'L',   'l', 'J', 'j', 'O', 'o'>,
                                        rank_char_mapping<  10,    'M',   'm'>,
                                        rank_char_mapping<  11,    'N',   'n'>,
                                        rank_char_mapping<  12,    'P',   'p'>,
                                        rank_char_mapping<  13,    'Q',   'q'>,
                                        rank_char_mapping<  14,    'R',   'r'>,
                                        rank_char_mapping<  15,    'S',   's', 'X', 'x'>,
                                        rank_char_mapping<  16,    'T',   't'>,
                                        rank_char_mapping<  17,    'V',   'v'>,
                                        rank_char_mapping<  18,    'W',   'w', '*'>,
                                        rank_char_mapping<  19,    'Y',   'y'>
                                    >>
{};
static_assert(alphabet_c<aa20>, "Unit test: is supposed to model an alphabet");

struct aa27 : alphabet<      rank_char_mappings<
                                        rank_char_mapping<   0,    'A',   'a'>,
                                        rank_char_mapping<   1,    'C',   'c'>,
                                        rank_char_mapping<   2,    'D',   'd'>,
                                        rank_char_mapping<   3,    'E',   'e'>,
                                        rank_char_mapping<   4,    'F',   'f'>,
                                        rank_char_mapping<   5,    'G',   'g'>,
                                        rank_char_mapping<   6,    'H',   'h'>,
                                        rank_char_mapping<   7,    'I',   'i'>,
                                        rank_char_mapping<   8,    'K',   'k'>,
                                        rank_char_mapping<   9,    'L',   'l'>,
                                        rank_char_mapping<  10,    'M',   'm'>,
                                        rank_char_mapping<  11,    'N',   'n'>,
                                        rank_char_mapping<  12,    'P',   'p'>,
                                        rank_char_mapping<  13,    'Q',   'q'>,
                                        rank_char_mapping<  14,    'R',   'r'>,
                                        rank_char_mapping<  15,    'S',   's'>,
                                        rank_char_mapping<  16,    'T',   't'>,
                                        rank_char_mapping<  17,    'V',   'v'>,
                                        rank_char_mapping<  18,    'W',   'w'>,
                                        rank_char_mapping<  19,    'Y',   'y'>,
                                        rank_char_mapping<  20,    'U',   'u'>,
                                        rank_char_mapping<  21,    'B',   'b'>,
                                        rank_char_mapping<  22,    'Z',   'z'>,
                                        rank_char_mapping<  23,    'J',   'j'>,
                                        rank_char_mapping<  24,    'O',   'o'>,
                                        rank_char_mapping<  25,    'X',   'x'>,
                                        rank_char_mapping<  26,    '*'>
                                    >>
{};
static_assert(alphabet_c<aa27>, "Unit test: is supposed to model an alphabet");

}
