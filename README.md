<!--
    SPDX-FileCopyrightText: 2006-2023, Knut Reinert & Freie Universität Berlin
    SPDX-FileCopyrightText: 2016-2023, Knut Reinert & MPI für molekulare Genetik
    SPDX-License-Identifier: CC-BY-4.0
-->
# IVSigma
A c++20 library for bioinformatics. It provides functionality to work on nucleotide alphabets (e.g. dna4, dna5, rna4, ...), amino acid based alphabets and many more.

**IVSigma** stands for 4th version, and **Sigma** as the Greek letter Σ which is typically used to represent
alphabets as used in **bioinformatics**, such as Σ={A, C, G, T, N}

## Documentation/API Reference
Checkout the [documentation](https://iv-project.github.io/IVSigma/) for more information.

## Usage CMake
To use this package with cmake you must add this repository via `find_package` and add a `target_link_libraries`.
e.g:
```cmake
find_package(ivsigma PATHS lib/IVSigma)
add_executable(your_exec file1.cpp)
target_link_libraries(your_exec PUBLIC ivsigma::ivsigma)
```


## Example

Here a quick example on how to convert dna5 data into rank space:

```c++
int main() {
    auto input  = std::string{"ACGnACGt"};
    auto output = ivs::convert_char_to_rank<ivs::dna5>(input);
    fmt::print("{} => {}\n", input, output);
    // prints: "ACGnACGt => [0, 1, 2, 4, 0, 1, 2, 3]"
}
```
