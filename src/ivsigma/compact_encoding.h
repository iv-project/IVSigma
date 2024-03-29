// SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause
#pragma once

#include "concepts.h"

#include <cassert>
#include <cstdint>
#include <cmath>
#include <span>

namespace ivs::detail {

/**
 * Computes a integer processing pow function
 */
template <size_t Sigma>
auto myPow(size_t exp) -> size_t {
    if (exp == 0) return 1;
    if (exp == 1) return Sigma;
    if (Sigma == 0) return 0;
    if (Sigma == 1) return 1;
    auto v = myPow<Sigma>(exp/2);
    v = v*v;
    if (exp % 2 == 1) {
        v = v * Sigma;
    }
    return v;
}

/**
 * computes a compact encoding, limited to 64bit
 * - call 'nextRight(,)' to receive the next hash value.
 * - or call 'nextLeft(,)' to receive the next hash value.
 * for initialization call 'next*(0, x)'
 */
template <size_t Sigma>
struct compact_encoding_gadget {
    size_t const k;
    size_t const maxExp{myPow<Sigma>(k-1)};
    size_t hash{};

    size_t value() const {
//        return hash ^ 0x8F3F73B5CF1C9ADE;
        return hash;
    }
    void nextRight(size_t removeValue, size_t insertValue) {
        hash = (hash - removeValue*maxExp)*Sigma + insertValue;
    }
    void nextLeft(size_t removeValue, size_t insertValue) {
        hash = (hash - removeValue)/Sigma + insertValue*maxExp;
    }
};

template <alphabet_c Alphabet, bool UseCanonicalKmers>
struct compact_encoding {
    std::span<uint8_t const> values;
    size_t const k;
    size_t const seed;

   compact_encoding(std::span<uint8_t const> _values, size_t _k, size_t _seed = 0)
        : values{_values}
        , k{_k}
        , seed{_seed}
    {}

    auto size() const -> size_t {
        if (values.size() < k) return 0;
        return values.size() - k + 1;
    }

    struct iterator {
        compact_encoding const* ptr;

        compact_encoding_gadget<Alphabet::size()> fwdHash;
        compact_encoding_gadget<Alphabet::size()> bwdHash;
        size_t minHash{};
        size_t pos{};

        iterator(compact_encoding const& hash)
            : ptr{&hash}
            , fwdHash{ptr->k}
            , bwdHash{ptr->k}
        {
            if (ptr->k <= ptr->size()) {
                for (size_t i{0}; i < ptr->k; ++i) {
                    auto addValue = ptr->values[i];
                    fwdHash.nextRight(0, addValue);
                    if constexpr (alphabet_with_complement_c<Alphabet>) {
                        bwdHash.nextLeft(0, Alphabet::complement_rank(addValue));
                    }
                }
            }
            pos = ptr->k-1;
            if constexpr (alphabet_with_complement_c<Alphabet> and UseCanonicalKmers) {
                minHash = std::min(fwdHash.value() ^ ptr->seed, bwdHash.value() ^ ptr->seed);
            } else {
                minHash = fwdHash.value() ^ ptr->seed;
            }
        }
        auto operator*() const -> size_t {
            return minHash;
        }
        auto operator++() -> iterator& {
            pos += 1;
            if (pos >= ptr->values.size()) {
                return *this;
            }

            assert(pos < ptr->values.size());

            auto rmValue  = ptr->values[pos-ptr->k];
            auto addValue = ptr->values[pos];
            fwdHash.nextRight(rmValue, addValue);
            if constexpr (alphabet_with_complement_c<Alphabet> and UseCanonicalKmers) {
                bwdHash.nextLeft(Alphabet::complement_rank(rmValue), Alphabet::complement_rank(addValue));
                minHash = std::min(fwdHash.value() ^ ptr->seed, bwdHash.value() ^ ptr->seed);
            } else {
                minHash = fwdHash.value() ^ ptr->seed;
            }
            return *this;
        }
        bool operator==(std::nullptr_t) const {
            return pos >= ptr->values.size();
        }
    };

    friend auto begin(compact_encoding const& index) -> iterator {
        return iterator{index};
    }
    friend auto end(compact_encoding const&) -> std::nullptr_t {
        return nullptr;
    }
};
}

namespace ivs {

template <alphabet_c Alphabet, bool UseCanonicalKmers=true>
using compact_encoding = detail::compact_encoding<Alphabet, UseCanonicalKmers>;

}
