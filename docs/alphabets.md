<!--
    SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
    SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
    SPDX-License-Identifier: CC-BY-4.0
-->
# Alphabets
The following alphabets are available

| Nucleotide based | Amino acid based | Quality based         |
|------------------|------------------|-----------------------|
| `ivs::dna4`      | `ivs::aa27`      | `ivs::pthred42`       |
| `ivs::dna5`      | `ivs::aa20`      | `ivs::pthred63`       |
| `ivs::rna4`      | `ivs::aa10li`    | `ivs::pthred68solexa` |
| `ivs::rna5`      | `ivs::aa10murphy`| `ivs::pthred94`       |
| `ivs::iupac`     |                  |                       |
| `ivs::dna3bs`    |                  |                       |
| `ivs::d_dna4`    |                  |                       |
| `ivs::d_dna5`    |                  |                       |
| `ivs::d_rna4`    |                  |                       |
| `ivs::d_rna5`    |                  |                       |
| `ivs::d_iupac`   |                  |                       |
| `ivs::d_dna3bs`  |                  |                       |


## Nucleotide based
Alphabets starting with `d_` are alphabets with a additional delimiter `$` as rank 0.
- `#!cpp size_t size()`
- `#!cpp uint8_t char_to_rank(char)`
- `#!cpp char rank_to_char(uint8_t)`
- `#!cpp char normalize_char(char)`
- `#!cpp char complement_char(char)`
- `#!cpp uint8_t complement_rank(uint8_t)`

All functions are guaranteed to not throw.

## Amino acid based
- `#!cpp size_t size()`
- `#!cpp uint8_t char_to_rank(char)`
- `#!cpp char rank_to_char(uint8_t)`
- `#!cpp char normalize_char(char)`

All functions are guaranteed to not throw.

## Quality based
- `#!cpp size_t size()`
- `#!cpp uint8_t char_to_rank(char)`
- `#!cpp char rank_to_char(uint8_t)`
- `#!cpp char normalize_char(char)`

All functions are guaranteed to not throw.
