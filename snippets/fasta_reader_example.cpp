// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <ivsigma/ivsigma.h>

int main() {
    auto input  = std::string{"ACGnACGt"};
    auto output = ivs::convert_char_to_rank<ivs::dna5>(input);
    fmt::print("{} => {}\n", input, output);
}
