// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0
#include <ivsigma/ivsigma.h>
#include <iostream>

int main()
{
    auto input = std::string{"AaCcGgTtUu"};
    { // Version 1
        auto output = std::string{};
        output.resize(input.size());
        ivs::normalize_char<ivs::dna4>(input, output);
        std::cout << output << '\n';
    }
    { // Version 2
        std::string output = ivs::normalize_char<ivs::dna4>(input);
        std::cout << output << '\n';
    }
    { // Version 3
        auto output_view = input | ivs::view_normalize_char<ivs::dna4>;
        auto output = std::string(output_view.begin(), output_view.end());
        std::cout << output << '\n';
    }
}
