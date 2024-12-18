// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "concepts.h"

#include <cassert>
#include <optional>
#include <ranges>
#include <span>
#include <string>
#include <vector>

namespace ivs {

/********** Functions converting chars to rank **********/

/*! \brief Converts a string to a rank representation
 *
 * \tparam Alphabet describes the used alphabet
 * \param in  string input
 * \param out target string (must have same size as in)
 */
template <alphabet_c Alphabet, uint8_t Unknown = 255>
void convert_char_to_rank(std::span<char const> in, std::span<uint8_t> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template char_to_rank<Unknown>(in[i]);
    }
}

/*! \brief Converts a string to a rank representation
 *
 * \tparam Alphabet describes the used alphabet
 * \param in  string input
 * \return a vector of ranks
 */
template <alphabet_c Alphabet, uint8_t Unknown = 255>
auto convert_char_to_rank(std::span<char const> in) -> std::vector<uint8_t> {
    auto out = std::vector<uint8_t>{};
    out.resize(in.size());
    convert_char_to_rank<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view representing a string in its rank representation
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_c Alphabet, uint8_t Unknown = 255>
auto view_char_to_rank = std::views::transform([](char c) {
    return Alphabet::template char_to_rank<Unknown>(c);
});


/********** Functions converting rank to chars **********/

/*! \brief Converts a rank representation to its string representation
 *
 * \tparam Alphabet describes the used alphabet
 * \param in rank input
 * \param out a string of the rank input (must have same size as in)
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
void convert_rank_to_char(std::span<uint8_t const> in, std::span<char> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template rank_to_char<Unknown>(in[i]);
    }
}

/*! \brief Converts a rank representation to its string representation
 *
 * \tparam Alphabet describes the used alphabet
 * \param in rank input
 * \return a string of the rank input
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
auto convert_rank_to_char(std::span<uint8_t const> in) -> std::string {
    auto out = std::string{};
    out.resize(in.size());
    convert_rank_to_char<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view representing a rank string as a character string
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
auto view_rank_to_char = std::views::transform([](uint8_t c) {
    return Alphabet::template rank_to_char<Unknown>(c);
});

/********** Functions Normalizing chars **********/

/*! \brief Normalizes chars according to the alphabet
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \param out normalized string of input (must have same size as in)
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
void normalize_char(std::span<char const> in, std::span<char> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template normalize_char<Unknown>(in[i]);
    }
}

/*! \brief Normalizes chars according to the alphabet
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \return normalized string of input
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
auto normalize_char(std::span<char const> in) -> std::string {
    auto out = std::string{};
    out.resize(in.size());
    normalize_char<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view representing a normalized string
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_c Alphabet, char Unknown = '\0'>
auto view_normalize_char = std::views::transform([](char c) {
    return Alphabet::template normalize_char<Unknown>(c);
});

/********** Functions complement in rank space **********/

/*! \brief Computes the complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in rank input
 * \param out complement of input (must have same size as in)
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
void complement_rank(std::span<uint8_t const> in, std::span<uint8_t> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template complement_rank<Unknown>(in[i]);
    }
}

/*! \brief Computes the complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in rank input
 * \return complement in rank space
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
auto complement_rank(std::span<uint8_t const> in) -> std::vector<uint8_t> {
    auto out = std::vector<uint8_t>{};
    out.resize(in.size());
    complement_rank<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view of complements
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
auto view_complement_rank = std::views::transform([](uint8_t c) {
    return Alphabet::template complement_rank<Unknown>(c);
});


/********** Functions complement in char space **********/

/*! \brief Computes the complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \param out complement of input (must have same size as in)
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
void complement_char(std::span<char const> in, std::span<char> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template complement_char<Unknown>(in[i]);
    }
}

/*! \brief Computes the complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \return complement string of input
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
auto complement_char(std::span<char const> in) -> std::string {
    auto out = std::string{};
    out.resize(in.size());
    complement_char<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view of complements
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
auto view_complement_char = std::views::transform([](char c) {
    return Alphabet::template complement_char<Unknown>(c);
});

/********** Functions reverse complement in rank space **********/

/*! \brief Computes the reverse complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \param out reverse complement of input (must have same size as in)
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
void reverse_complement_rank(std::span<uint8_t const> in, std::span<uint8_t> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template complement_rank<Unknown>(in[in.size() - i - 1]);
    }
}

/*! \brief Computes the reverse complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in a span of ranks
 * \return reverse complement of in
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
auto reverse_complement_rank(std::span<uint8_t const> in) -> std::vector<uint8_t> {
    auto out = std::vector<uint8_t>{};
    out.resize(in.size());
    reverse_complement_rank<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view of reverse_complements
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_with_complement_c Alphabet, uint8_t Unknown = 255>
auto view_reverse_complement_rank = std::views::reverse | std::views::transform([](uint8_t c) {
    return Alphabet::template complement_rank<Unknown>(c);
});


/********** Functions complement in char space **********/

/*! \brief Computes the reverse complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \param out complement of input (must have same size as in)
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
void reverse_complement_char(std::span<char const> in, std::span<char> out) {
    assert(in.size() == out.size());
    for (auto i{0}; i < ssize(in); ++i) {
        out[i] = Alphabet::template complement_char<Unknown>(in[in.size() - i - 1]);
    }
}

/*! /brief Computes the reverse complement
 *
 * \tparam Alphabet describes the used alphabet
 * \param in string input
 * \return reverse complement string of input
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
auto reverse_complement_char(std::span<char const> in) -> std::string {
    auto out = std::string{};
    out.resize(in.size());
    reverse_complement_char<Alphabet, Unknown>(in, out);
    return out;
}

/*! \brief A view of complements
 *
 * \tparam Alphabet describes the used alphabet
 */
template <alphabet_with_complement_c Alphabet, char Unknown = '\0'>
auto view_reverse_complement_char = std::views::reverse | std::views::transform([](char c) {
    return Alphabet::template complement_char<Unknown>(c);
});

/********** Functions verify **********/

/*! \brief Checks if char is valid (checks for '\0')
 *
 * \param in char input
 * \return if valid returns true, else false
 */
template <char Unknown = '\0'>
auto verify_char(char in) -> bool {
    return in != Unknown;
}

/*! \brief Returns if string is valid (searches for '\0')
 *
 * \param in char input
 * \return std::optional pointing to the wrong entry (if one exists)
 */
template <char Unknown = '\0'>
auto verify_char(std::span<char const> in) -> std::optional<size_t> {
    auto str = std::string_view{in.begin(), in.end()};
    auto pos = str.find(Unknown);
    if (std::string_view::npos == pos) return std::nullopt; // verification successful
    return pos;
}

/*! \brief Checks if rank is valid (checks for 255)
 *
 * \param in rank input
 * \return if valid returns true, else false
 */
template <uint8_t Unknown = 255>
auto verify_rank(uint8_t in) -> bool {
    return in != Unknown;
}

/*! \brief Returns if all ranks are valid (searches for 255)
 *
 * \param in rank input
 * \return std::optional pointing to the wrong entry (if one exists)
 */
template <uint8_t Unknown = 255>
auto verify_rank(std::span<uint8_t const> in) -> std::optional<size_t> {
    auto str = std::basic_string_view<uint8_t>{in.begin(), in.end()};
    auto pos = str.find(Unknown);
    if (std::string_view::npos == pos) return std::nullopt; // verification successful
    return pos;
}

}
