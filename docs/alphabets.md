<!--
    SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
    SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
    SPDX-License-Identifier: CC-BY-4.0
-->
# Alphabets
The following alphabets are available

| Nucleotide based | Amino acid based | Quality based         |
|------------------|------------------|-----------------------|
|  `ivs::dna2`     | `ivs::aa27`      | `ivs::pthred42`       |
|  `ivs::dna4`     | `ivs::aa20`      | `ivs::pthred63`       |
|  `ivs::dna5`     | `ivs::aa10li`    | `ivs::pthred68solexa` |
|  `ivs::rna4`     | `ivs::aa10murphy`| `ivs::pthred94`       |
|  `ivs::rna5`     |                  |                       |
|  `ivs::iupac`    |                  |                       |
|  `ivs::dna3bs`   |                  |                       |
|  `ivs::d_dna4`   |                  |                       |
|  `ivs::d_dna5`   |                  |                       |
|  `ivs::d_rna4`   |                  |                       |
|  `ivs::d_rna5`   |                  |                       |
|  `ivs::d_iupac`  |                  |                       |
|  `ivs::d_dna3bs` |                  |                       |


## Common functionality
- All functions are guaranteed to not throw.
- Alphabets starting with `d_` are alphabets with a additional delimiter `$` as rank 0.
- `#!cpp static size_t size()`

    Returns the number of elements of the alphabet.

- `#!cpp static uint8_t char_to_rank(char c)`

    Converts ASCII symbol `c` to an ranked `uint8_t` representation (0 ≤ r < size()).
    Invalid ASCII symbols will return value 255.

- `#!cpp static char rank_to_char(uint8_t r)`

    Converts the ranked value `r` to its ACSII corresponding value. Value r must be fulfill (0 ≤ r < size()).

- `#!cpp static char normalize_char(char c)`

    Normalizes the ASCII value `c`. Normalizing depends on the alphabet. Typically this includes
    representing the value in captial letter.



## Nucleotide based
Additionall functionality for Nucleotide based values:

- `#!cpp static char complement_char(char c)`

    Computes the complement of the ASCII value `c`. Example given: the complement of dna4 for 'A' is 'T'.

- `#!cpp static uint8_t complement_rank(uint8_t)`

    Computes the complement in rank space. Example given: the complement of dna4 of rank value 0 is 3. (A -> T).

## Ambigous bases
Some alphabets have ambiguous bases. Like in dna5 the letter 'N' can stand for 'A', 'C', 'G' or 'T'.
For this we provide a sepecial functionality:

- `#!cpp static auto ambigous_bases() -> std::array<uint8_t, /*alphabet dependent*/>`

    Returns an array of bases that are ambiguous.

- `#!cpp static auto base_alternatives(uint8_t base) -> std::vector<uint8_t>`

    Returns a list of values that `base` could stand for.
