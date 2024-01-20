**Compression Algorithms**

C++11 implementations of common data compression algorithms.

License:
Thanks to glampert, for providing us with the source code, for more details, please visit glampert's repository : https://github.com/glampert/compression-algorithms

    rle.hpp: Run Length Encoding with either 8 or 16 bits run-length words.
    lzw.hpp: Lempel–Ziv–Welch compression with varying code lengths and a 4096 max entries dictionary.
    huffman.hpp: Simple Huffman Coding with 64-bits max code length.
    rice.hpp: Rice/Golomb Coding with optimal code length (8 bits max).

These libraries are header only and self contained. You have to include the .hpp in one source file and define XYZ_IMPLEMENTATION to generate the implementation code in that source file. After that, the header file can be used as a normal C++ header. This is the same design of the stb libraries.

See tests.cpp for some usage examples.
