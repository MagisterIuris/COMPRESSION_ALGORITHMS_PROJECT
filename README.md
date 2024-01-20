# Compression Algorithms

This repository contains C++11 implementations of common data compression algorithms.

## License

This project is based on the work of [glampert](https://github.com/glampert), who generously provided the source code. For more details, please visit glampert's original repository: [glampert/compression-algorithms](https://github.com/glampert/compression-algorithms).

## Included Algorithms

### 1. Run Length Encoding (rle.hpp)

Run Length Encoding with support for both 8 and 16 bits run-length words.

### 2. Lempel–Ziv–Welch Compression (lzw.hpp)

Lempel–Ziv–Welch compression implementation with varying code lengths and a maximum dictionary size of 4096 entries.

### 3. Simple Huffman Coding (huffman.hpp)

A simple Huffman Coding implementation with a maximum code length of 64 bits.

### 4. Rice/Golomb Coding (rice.hpp)

Rice/Golomb Coding implementation with optimal code length (8 bits max).

## Usage

These libraries are header-only and self-contained. To use them, include the corresponding `.hpp` file in one source file and define `XYZ_IMPLEMENTATION` to generate the implementation code in that source file. After that, the header file can be used as a normal C++ header. This design follows the same principles as the stb libraries.

## Example

Check out the `tests.cpp` file for usage examples and test cases.

Enjoy you visit !

