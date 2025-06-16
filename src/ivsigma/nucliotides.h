// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "alphabet.h"
#include "delimited_alphabet.h"

namespace ivs {

//                                                             rank, symbol, compl, alts...
struct dna4 : alphabet<rank_char_mappings_with_compl<
                                  rank_char_mapping_with_compl<   0,    'A',   'T', 'a'>,
                                  rank_char_mapping_with_compl<   1,    'C',   'G', 'c'>,
                                  rank_char_mapping_with_compl<   2,    'G',   'C', 'g'>,
                                  rank_char_mapping_with_compl<   3,    'T',   'A', 't', 'U', 'u'>
                                >>
{};
static_assert(alphabet_c<dna4>, "Unit test: is supposed to model an alphabet");

struct dna5 : alphabet<rank_char_mappings_with_compl<
                                  rank_char_mapping_with_compl<   0,    'A',   'T', 'a'>,
                                  rank_char_mapping_with_compl<   1,    'C',   'G', 'c'>,
                                  rank_char_mapping_with_compl<   2,    'G',   'C', 'g'>,
                                  rank_char_mapping_with_compl<   3,    'T',   'A', 't', 'U', 'u'>,
                                  rank_char_mapping_with_compl<   4,    'N',   'N', 'n'>
                            >, char_ambiguous_mappings<
                                  char_ambiguous<'N', 'A', 'C', 'G', 'T'>
                            >>
{};
static_assert(alphabet_c<dna5>, "Unit test: is supposed to model an alphabet");

struct iupac : alphabet<rank_char_mappings_with_compl<
                                  rank_char_mapping_with_compl<   0,   'A',   'T', 'a'>,
                                  rank_char_mapping_with_compl<   1,   'C',   'G', 'c'>,
                                  rank_char_mapping_with_compl<   2,   'G',   'C', 'g'>,
                                  rank_char_mapping_with_compl<   3,   'T',   'A', 't', 'U', 'u'>,
                                  rank_char_mapping_with_compl<   4,   'N',   'N', 'n'>,
                                  rank_char_mapping_with_compl<   5,   'R',   'Y', 'r'>,
                                  rank_char_mapping_with_compl<   6,   'Y',   'R', 'y'>,
                                  rank_char_mapping_with_compl<   7,   'S',   'S', 's'>,
                                  rank_char_mapping_with_compl<   8,   'W',   'W', 'w'>,
                                  rank_char_mapping_with_compl<   9,   'K',   'M', 'k'>,
                                  rank_char_mapping_with_compl<  10,   'M',   'K', 'm'>,
                                  rank_char_mapping_with_compl<  11,   'B',   'V', 'b'>,
                                  rank_char_mapping_with_compl<  12,   'D',   'H', 'd'>,
                                  rank_char_mapping_with_compl<  13,   'H',   'D', 'h'>,
                                  rank_char_mapping_with_compl<  14,   'V',   'B', 'v'>,
                                  rank_char_mapping_with_compl<  15,   '-',   '-', '.'>
                            >, char_ambiguous_mappings<
                                  char_ambiguous<'N', 'A', 'C', 'G', 'T'>,
                                  char_ambiguous<'W', 'A', 'T'>,
                                  char_ambiguous<'S', 'C', 'G'>,
                                  char_ambiguous<'M', 'A', 'C'>,
                                  char_ambiguous<'K', 'G', 'T'>,
                                  char_ambiguous<'R', 'A', 'G'>,
                                  char_ambiguous<'Y', 'C', 'T'>,
                                  char_ambiguous<'B', 'C', 'G', 'T'>,
                                  char_ambiguous<'D', 'A', 'G', 'T'>,
                                  char_ambiguous<'H', 'A', 'C', 'T'>,
                                  char_ambiguous<'V', 'A', 'C', 'G'>
                            >>
{};
static_assert(alphabet_c<iupac>, "Unit test: is supposed to model an alphabet");

struct rna4 : alphabet<rank_char_mappings_with_compl<
                                  rank_char_mapping_with_compl<   0,    'A',   'U', 'a'>,
                                  rank_char_mapping_with_compl<   1,    'C',   'G', 'c'>,
                                  rank_char_mapping_with_compl<   2,    'G',   'C', 'g'>,
                                  rank_char_mapping_with_compl<   3,    'U',   'A', 'u', 'T', 't'>
                            >>
{};
static_assert(alphabet_c<rna4>, "Unit test: is supposed to model an alphabet");

struct rna5 : alphabet<rank_char_mappings_with_compl<
                                  rank_char_mapping_with_compl<   0,    'A',   'U', 'a'>,
                                  rank_char_mapping_with_compl<   1,    'C',   'G', 'c'>,
                                  rank_char_mapping_with_compl<   2,    'G',   'C', 'g'>,
                                  rank_char_mapping_with_compl<   3,    'U',   'A', 'u', 'T', 't'>,
                                  rank_char_mapping_with_compl<   4,    'N',   'N', 'n'>
                            >, char_ambiguous_mappings<
                                  char_ambiguous<'N', 'A', 'C', 'G', 'U'>
                            >>
{};
static_assert(alphabet_c<rna5>, "Unit test: is supposed to model an alphabet");

//                                                    rank, symbol,   alts...
struct dna3bs : alphabet<rank_char_mappings<
                                    rank_char_mapping<   0,    'A',   'a'>,
                                    rank_char_mapping<   1,    'G',   'g'>,
                                    rank_char_mapping<   2,    'T',   't', 'C', 'c', 'U', 'u'>
                                >>
{};
static_assert(alphabet_c<dna3bs>, "Unit test: is supposed to model an alphabet");


struct d_dna4 : delimited_alphabet<dna4> {};
static_assert(alphabet_c<d_dna4>, "Unit test: is supposed to model an alphabet");

struct d_dna5 : delimited_alphabet<dna5> {};
static_assert(alphabet_c<d_dna5>, "Unit test: is supposed to model an alphabet");

struct d_iupac : delimited_alphabet<iupac> {};
static_assert(alphabet_c<d_iupac>, "Unit test: is supposed to model an alphabet");

struct d_rna4 : delimited_alphabet<rna4> {};
static_assert(alphabet_c<d_dna4>, "Unit test: is supposed to model an alphabet");

struct d_rna5 : delimited_alphabet<rna5> {};
static_assert(alphabet_c<d_rna5>, "Unit test: is supposed to model an alphabet");

struct d_dna3bs : delimited_alphabet<dna3bs> {};
static_assert(alphabet_c<d_dna3bs>, "Unit test: is supposed to model an alphabet");

}
