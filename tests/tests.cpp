#define LZW_IMPLEMENTATION
#include "lzw.hpp"

#define HUFFMAN_IMPLEMENTATION
#include "huffman.hpp"

#define RICE_IMPLEMENTATION
#include "rice.hpp"

#include <cstring>
#include <iostream>
#include <vector>
#include <chrono>

#include "lenna_tga.hpp"
#include "random_512.hpp"
#include "shakespeare.h"
#include "moby.h"

static void Test_LZW_Compression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    lzw::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);
    std::cout << "LZW compressed size bytes   = " << compressedSizeBytes << "\n";
    std::cout << "LZW compression ratio = " << static_cast<double>(sampleSize) / static_cast<double>(compressedSizeBytes) << "\n";
    LZW_MFREE(compressedData);
}

static void Test_LZW_Decompression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    lzw::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);

    std::vector<std::uint8_t> uncompressedBuffer(sampleSize, 0);
    const int uncompressedSize = lzw::easyDecode(compressedData, compressedSizeBytes, compressedSizeBits, uncompressedBuffer.data(), uncompressedBuffer.size());

    bool successful = true;
    if (uncompressedSize != sampleSize)
    {
        std::cerr << "LZW DECOMPRESSION ERROR! Size mismatch!\n";
        successful = false;
    }
    if (std::memcmp(uncompressedBuffer.data(), sampleData, sampleSize) != 0)
    {
        std::cerr << "LZW DECOMPRESSION ERROR! Data corrupted!\n";
        successful = false;
    }

    if (successful)
    {
        std::cout << "LZW decompression successful!\n";
    }

    LZW_MFREE(compressedData);
}

static void Test_LZW_Comp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 compression...\n";
    Test_LZW_Compression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 compression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga compression...\n";
    Test_LZW_Compression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga compression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare compression...\n";
    Test_LZW_Compression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare compression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby compression...\n";
    Test_LZW_Compression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby compression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

static void Test_LZW_Decomp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 decompression...\n";
    Test_LZW_Decompression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 decompression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga decompression...\n";
    Test_LZW_Decompression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga decompression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare decompression...\n";
    Test_LZW_Decompression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare decompression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby decompression...\n";
    Test_LZW_Decompression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby decompression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

static void Test_Huffman_Compression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    huffman::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);
    std::cout << "Huffman compressed size bytes   = " << compressedSizeBytes << "\n";
    std::cout << "Huffman compression ratio = " << static_cast<double>(sampleSize) / static_cast<double>(compressedSizeBytes) << "\n";
    HUFFMAN_MFREE(compressedData);
}

static void Test_Huffman_Decompression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    huffman::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);

    std::vector<std::uint8_t> uncompressedBuffer(sampleSize, 0);
    const int uncompressedSize = huffman::easyDecode(compressedData, compressedSizeBytes, compressedSizeBits, uncompressedBuffer.data(), uncompressedBuffer.size());

    bool successful = true;
    if (uncompressedSize != sampleSize)
    {
        std::cerr << "HUFFMAN DECOMPRESSION ERROR! Size mismatch!\n";
        successful = false;
    }
    if (std::memcmp(uncompressedBuffer.data(), sampleData, sampleSize) != 0)
    {
        std::cerr << "HUFFMAN DECOMPRESSION ERROR! Data corrupted!\n";
        successful = false;
    }

    if (successful)
    {
        std::cout << "Huffman decompression successful!\n";
    }

    HUFFMAN_MFREE(compressedData);
}

static void Test_Huffman_Comp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 compression...\n";
    Test_Huffman_Compression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 compression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga compression...\n";
    Test_Huffman_Compression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga compression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare compression...\n";
    Test_Huffman_Compression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare compression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby compression...\n";
    Test_Huffman_Compression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby compression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

static void Test_Huffman_Decomp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 decompression...\n";
    Test_Huffman_Decompression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 decompression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga decompression...\n";
    Test_Huffman_Decompression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga decompression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare decompression...\n";
    Test_Huffman_Decompression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare decompression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby decompression...\n";
    Test_Huffman_Decompression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby decompression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

static void Test_Rice_Compression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    rice::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);
    std::cout << "Rice compressed size bytes   = " << compressedSizeBytes << "\n";
    std::cout << "Rice compression ratio = " << static_cast<double>(sampleSize) / static_cast<double>(compressedSizeBytes) << "\n";
    RICE_MFREE(compressedData);
}

static void Test_Rice_Decompression(const std::uint8_t *sampleData, const int sampleSize)
{
    int compressedSizeBytes = 0;
    int compressedSizeBits = 0;
    std::uint8_t *compressedData = nullptr;
    rice::easyEncode(sampleData, sampleSize, &compressedData, &compressedSizeBytes, &compressedSizeBits);

    std::vector<std::uint8_t> uncompressedBuffer(sampleSize, 0);
    const int uncompressedSize = rice::easyDecode(compressedData, compressedSizeBytes, compressedSizeBits, uncompressedBuffer.data(), uncompressedBuffer.size());

    bool successful = true;
    if (uncompressedSize != sampleSize)
    {
        std::cerr << "RICE DECOMPRESSION ERROR! Size mismatch!\n";
        successful = false;
    }
    if (

            std::memcmp(uncompressedBuffer.data(), sampleData, sampleSize) != 0)
    {
        std::cerr << "RICE DECOMPRESSION ERROR! Data corrupted!\n";
        successful = false;
    }

    if (successful)
    {
        std::cout << "Rice decompression successful!\n";
    }

    RICE_MFREE(compressedData);
}

static void Test_Rice_Comp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 compression...\n";
    Test_Rice_Compression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 compression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga compression...\n";
    Test_Rice_Compression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga compression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare compression...\n";
    Test_Rice_Compression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare compression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby compression...\n";
    Test_Rice_Compression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby compression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

static void Test_Rice_Decomp()
{
    const auto startTimeC = std::chrono::system_clock::now();

    std::cout << "> Testing random512 decompression...\n";
    Test_Rice_Decompression(random512, sizeof(random512));
    const auto endTimeC1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC1 = endTimeC1 - startTimeC;
    std::cout << ">>> random512 decompression tests completed in " << elapsedSecondsC1.count() << " seconds.\n";

    std::cout << "> Testing lenna.tga decompression...\n";
    Test_Rice_Decompression(lennaTgaData, sizeof(lennaTgaData));
    const auto endTimeC2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC2 = endTimeC2 - startTimeC;
    std::cout << ">>> lenna.tga decompression tests completed in " << elapsedSecondsC2.count() << " seconds.\n";

    std::cout << "> Testing shakespeare decompression...\n";
    Test_Rice_Decompression(shakespeare, sizeof(shakespeare));
    const auto endTimeC3 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC3 = endTimeC3 - startTimeC;
    std::cout << ">>> shakespeare decompression tests completed in " << elapsedSecondsC3.count() << " seconds.\n";

    std::cout << "> Testing moby decompression...\n";
    Test_Rice_Decompression(moby, sizeof(moby));
    const auto endTimeC4 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsC4 = endTimeC4 - startTimeC;
    std::cout << ">>> moby decompression tests completed in " << elapsedSecondsC4.count() << " seconds.\n";
}

#define TESTCOMP(func)                                                                                         \
    do {                                                                                                   \
        std::cout << ">>> Testing " << #func << " compression.\n";                                       \
        const auto startTimeC = std::chrono::system_clock::now();                                          \
        Test_##func##_Comp();                                           \
        const auto endTimeC = std::chrono::system_clock::now();                                            \
        std::chrono::duration<double> elapsedSecondsC = endTimeC - startTimeC;                             \
        std::cout << ">>> " << #func << " compression tests completed in " << elapsedSecondsC.count() << " seconds.\n"; \
        std::cout << std::endl;                                                                            \
    } while (0,0)

#define TESTDECOMP(func)                                                                                         \
    do {                                                                                                   \
        std::cout << ">>> Testing " << #func << " decompression.\n";                                       \
        const auto startTimeC = std::chrono::system_clock::now();                                          \
        Test_##func##_Decomp();                                           \
        const auto endTimeC = std::chrono::system_clock::now();                                            \
        std::chrono::duration<double> elapsedSecondsC = endTimeC - startTimeC;                             \
        std::cout << ">>> " << #func << " decompression tests completed in " << elapsedSecondsC.count() << " seconds.\n"; \
        std::cout << std::endl;                                                                            \
    } while (0,0)

int main()
{
    std::cout << "\nRunning unit tests for the compression algorithms...\n\n";
    TESTCOMP(LZW);
    TESTDECOMP(LZW);
    TESTCOMP(Huffman);
    TESTDECOMP(Huffman);
    TESTCOMP(Rice);
    TESTDECOMP(Rice);
}
