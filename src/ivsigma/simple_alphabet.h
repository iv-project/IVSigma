// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "concepts.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <tuple>

namespace ivs {

template <uint8_t V, char H, char... Tail>
struct rank_char_mapping {
    static constexpr uint8_t rank = V;
    static constexpr char symb = H;
    static constexpr std::array<char, sizeof...(Tail)+1> all_symb = {H, Tail...};
};

template <typename... values>
struct simple_alphabet {
private:

    template <char Unknown>
    static constexpr auto rank_to_char_table_init() {
        auto table = std::array<char, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            table[V::rank] = V::symb;
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table representing conversion from rank to char
    template <char Unknown>
    static constexpr std::array<char, 256> rank_to_char_table{rank_to_char_table_init<Unknown>()};


    template <uint8_t Unknown>
    static constexpr auto char_to_rank_table_init() {
        auto table = std::array<uint8_t, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            for (auto c : V::all_symb) {
                table[c] = V::rank;
            }
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table representing conversion from char to rank
    template <uint8_t Unknown>
    static constexpr std::array<uint8_t, 256> char_to_rank_table{char_to_rank_table_init<Unknown>()};

    template <char Unknown>
    static constexpr auto normalize_char_table_init() {
        auto table = std::array<char, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            for (auto c : V::all_symb) {
                table[c] = V::symb;
            }
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table normalizing a char
    template <char Unknown>
    static constexpr std::array<char, 256> normalize_char_table{normalize_char_table_init<Unknown>()};

public:
    /*! \brief Converts a single char value to a rank value
     *
     * \param c char value
     * \return corresponding rank value
     */
    template <uint8_t Unknown = 255>
    static constexpr auto char_to_rank(char c) noexcept -> uint8_t {
        auto index = static_cast<uint8_t>(c);
        return char_to_rank_table<Unknown>[index];
    }

    /*! \brief Converts a single rank value to a char value
     *
     * \param v a rank value
     * \return corresponding (normalized) char value
     */
    template <char Unknown = '\0'>
    static constexpr auto rank_to_char(uint8_t v) noexcept -> char {
        return rank_to_char_table<Unknown>[v];
    }

    /*! \brief Normalizes a single char
     *
     * \param c char value
     * \return corresponding normalized char value
     */
    template <char Unknown = '\0'>
    static constexpr auto normalize_char(char c) noexcept -> char {
        auto index = static_cast<uint8_t>(c);
        return normalize_char_table<Unknown>[index];
    }

    /*! \brief Returns size of the alphabet
     *
     * \return a size_t representing the size of the alphabet
     */
    static constexpr auto size() noexcept -> size_t {
        return sizeof...(values);
    }
};


template <uint8_t V, char H, char Compl, char... Tail>
struct rank_char_mapping_with_compl {
    static constexpr uint8_t rank = V;
    static constexpr char symb = H;
    static constexpr char complement = Compl;
    static constexpr std::array<char, sizeof...(Tail)+1> all_symb = {H, Tail...};
};

template <typename... values>
struct alphabet_with_compl {
private:
    template <char Unknown>
    static constexpr auto rank_to_char_table_init() {
        auto table = std::array<char, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            table[V::rank] = V::symb;
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table representing conversion from rank to char
    template <char Unknown>
    static constexpr std::array<char, 256> rank_to_char_table{rank_to_char_table_init<Unknown>()};

    template <uint8_t Unknown>
    static constexpr auto char_to_rank_table_init() {
        auto table = std::array<uint8_t, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            for (auto c : V::all_symb) {
                table[c] = V::rank;
            }
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table representing conversion from char to rank
    template <uint8_t Unknown>
    static constexpr std::array<uint8_t, 256> char_to_rank_table{char_to_rank_table_init<Unknown>()};

    template <char Unknown>
    static constexpr auto normalize_char_table_init() {
        auto table = std::array<char, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            for (auto c : V::all_symb) {
                table[c] = V::symb;
            }
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table normalizing a char
    template <char Unknown>
    static constexpr std::array<char, 256> normalize_char_table{normalize_char_table_init<Unknown>()};

    template <uint8_t Unknown>
    static constexpr auto rank_complement_table_init() {
        auto table = std::array<uint8_t, 256>{};
        table.fill(Unknown);
        auto add_values_to_table = [&]<typename V>(V) {
            table[V::rank] = char_to_rank_table<Unknown>[V::complement];
        };
        (add_values_to_table(values{}), ...);
        return table;
    }

    //! Table computing the complement in rank space (rank in, rank out)
    template <uint8_t Unknown>
    static constexpr std::array<uint8_t, 256> rank_complement_table{rank_complement_table_init<Unknown>()};

public:
    /*! \brief Normalizes a single char
     *
     * \param c char value
     * \return corresponding normalized char value
     */
    template <char Unknown = '\0'>
    static constexpr auto normalize_char(char c) noexcept -> char {
        auto index = static_cast<uint8_t>(c);
        return normalize_char_table<Unknown>[index];
    }

    /*! \brief Converts a single char value to a rank value
     *
     * \param c char value
     * \return corresponding rank value
     */
    template <uint8_t Unknown = 255>
    static constexpr auto char_to_rank(char c) noexcept -> uint8_t {
        auto index = static_cast<uint8_t>(c);
        return char_to_rank_table<Unknown>[index];
    }

    /*! \brief Converts a single rank value to a char value
     *
     * \param v a rank value
     * \return corresponding (normalized) char value
     */
    template <char Unknown = '\0'>
    static constexpr auto rank_to_char(uint8_t v) noexcept -> char {
        return rank_to_char_table<Unknown>[v];
    }

    /*! \brief Returns size of the alphabet
     *
     * \return a size_t representing the size of the alphabet
     */
    static constexpr auto size() noexcept -> size_t {
        return sizeof...(values);
    }

    /*! \brief computes complement based on ranks
     *
     * \param r a rank value
     * \return corresponding complement
     */
    template <uint8_t Unknown = 255>
    static constexpr auto complement_rank(uint8_t r) noexcept -> uint8_t {
        return rank_complement_table<Unknown>[r];
    }

    /*! \brief computes complement based on char
     *
     * \param c a char value
     * \return corresponding complement
     */
    template <char Unknown = '\0'>
    static constexpr auto complement_char(char c) noexcept -> char {
        return rank_to_char<Unknown>(complement_rank(char_to_rank(c)));
    }
};

}
