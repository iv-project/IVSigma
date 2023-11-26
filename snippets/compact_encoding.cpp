// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0
#include <ivsigma/ivsigma.h>
#include <iostream>

int main()
{
    std::vector<uint8_t> input = ivs::convert_char_to_rank<ivs::dna4>("GCGACGTAC");
    for (auto enc : ivs::compact_encoding<ivs::dna4>(input, /*._k=*/ 3)) {
        std::cout << enc << ' ';
    }
    std::cout << '\n';
}
