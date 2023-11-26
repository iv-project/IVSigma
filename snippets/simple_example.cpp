// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0
#include <ivsigma/ivsigma.h>
#include <iostream>

int main() {
    auto ranks = ivs::convert_char_to_rank<ivs::dna4>("acgt");
    for (uint8_t c : ranks) {
        std::cout << (int)c << "\n";
    }
}
