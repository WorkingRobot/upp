#include "Compression.h"

namespace upp::Detail {
    template<>
    bool Compressor<CompressionMethod::LZ4>::IsValid()
    {
        return false;
    }

    template<>
    int32_t Compressor<CompressionMethod::LZ4>::CompressBound(int32_t UncompressedSize)
    {
        return 0;
    }

    template<>
    bool Compressor<CompressionMethod::LZ4>::Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize)
    {
        return false;
    }
}