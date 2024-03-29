// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0
#include <ivsigma/ivsigma.h>
#include <iostream>

int main()
{
    auto input = std::string{"ACCACGT"};
    { // Version 1
        auto output = std::vector<uint8_t>{};
        output.resize(input.size());
        ivs::convert_char_to_rank<ivs::dna4>(input, output);
        for (auto r : output) {
            std::cout << (int)r;
        }
        std::cout << '\n';
    }
    { // Version 2
        std::vector<uint8_t> output = ivs::convert_char_to_rank<ivs::dna4>(input);
        for (auto r : output) {
            std::cout << (int)r;
        }
        std::cout << '\n';
    }
    { // Version 3
        auto output_view = input | ivs::view_char_to_rank<ivs::dna4>;
        auto output = std::vector<uint8_t>(output_view.begin(), output_view.end());
        for (auto r : output) {
            std::cout << (int)r;
        }
        std::cout << '\n';
    }
}
