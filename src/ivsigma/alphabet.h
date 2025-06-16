// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "concepts.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>
#include <tuple>

namespace ivs {

template <uint8_t V, char H, char... Tail>
struct rank_char_mapping {
    static constexpr uint8_t rank = V;
    static constexpr char symb = H;
    static constexpr std::array<char, sizeof...(Tail)+1> all_symb = {H, Tail...};

    static constexpr bool is_rank_char_mapping = true;
};

template <typename T>
concept rank_char_mapping_c = T::is_rank_char_mapping;

template <rank_char_mapping_c ...T>
using rank_char_mappings = std::tuple<T...>;

template <char H, char...Tail>
struct char_ambiguous {
    static constexpr char symb = H;

    static constexpr std::array<char, sizeof...(Tail)> all_symb = {Tail...};

    static constexpr bool is_char_ambiguous = true;
};

template <typename T>
concept char_ambiguous_c = T::is_char_ambiguous;

template <char_ambiguous_c ...T>
using char_ambiguous_mappings = std::tuple<T...>;


template <typename mappings, typename T = char_ambiguous_mappings<>>
struct alphabet;

template <rank_char_mapping_c... values, char_ambiguous_c... ambiguous_mappings>
struct alphabet<rank_char_mappings<values...>, char_ambiguous_mappings<ambiguous_mappings...>> {
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

    /*! \brief returns a array of ambiguous rank values
     */
    static constexpr auto ambiguous_bases() noexcept -> std::array<uint8_t, sizeof...(ambiguous_mappings)> {
        auto res = std::array<uint8_t, sizeof...(ambiguous_mappings)>{};
        res = {char_to_rank(ambiguous_mappings::symb)...};
        return res;
    }

    /*! \brief returns a vector of rank values that the given base could stand for
     */
    static constexpr auto base_alternatives(uint8_t rank) noexcept -> std::vector<uint8_t> {
        auto res = std::vector<uint8_t>{};

        auto add_values_to_table = [&]<typename V>(V) {
            if (char_to_rank(V::symb) != rank) return;

            for (auto c : V::all_symb) {
                res.push_back(char_to_rank(c));
            }
        };
        (add_values_to_table(ambiguous_mappings{}), ...);

        return res;
    }
};


template <uint8_t V, char H, char Compl, char... Tail>
struct rank_char_mapping_with_compl {
    static constexpr uint8_t rank = V;
    static constexpr char symb = H;
    static constexpr char complement = Compl;
    static constexpr std::array<char, sizeof...(Tail)+1> all_symb = {H, Tail...};

    static constexpr bool is_rank_char_mapping_with_compl = true;
};

template <typename T>
concept rank_char_mapping_with_compl_c = T::is_rank_char_mapping_with_compl;

template <rank_char_mapping_with_compl_c ...T>
using rank_char_mappings_with_compl = std::tuple<T...>;


template <rank_char_mapping_with_compl_c... values, char_ambiguous_c... ambiguous_mappings>
struct alphabet<rank_char_mappings_with_compl<values...>, char_ambiguous_mappings<ambiguous_mappings...>> {
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

    /*! \brief returns a array of ambiguous rank values
     */
    static constexpr auto ambiguous_bases() noexcept -> std::array<uint8_t, sizeof...(ambiguous_mappings)> {
        auto res = std::array<uint8_t, sizeof...(ambiguous_mappings)>{};
        res = {char_to_rank(ambiguous_mappings::symb)...};
        return res;
    }

    /*! \brief returns a vector of rank values that the given base could stand for
     */
    static constexpr auto base_alternatives(uint8_t rank) noexcept -> std::vector<uint8_t> {
        auto res = std::vector<uint8_t>{};

        auto add_values_to_table = [&]<typename V>(V) {
            if (char_to_rank(V::symb) != rank) return;

            for (auto c : V::all_symb) {
                res.push_back(char_to_rank(c));
            }
        };
        (add_values_to_table(ambiguous_mappings{}), ...);

        return res;
    }
};

}
