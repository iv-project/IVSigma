#pragma once

#include <cstdint>
#include <concepts>

namespace ivs {

template <typename Alphabet>
concept alphabet_c = requires(Alphabet) {
    { Alphabet::char_to_rank(char{}) } -> std::same_as<uint8_t>;
    { Alphabet::rank_to_char(uint8_t{}) } -> std::same_as<char>;
};

}
