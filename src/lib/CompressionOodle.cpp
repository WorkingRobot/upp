#include "Compression.h"

#include <oodle2.h>

namespace upp::Detail {
    template<>
    bool Compressor<CompressionMethod::Oodle>::IsValid()
    {
        return true;
    }

    template<>
    int32_t Compressor<CompressionMethod::Oodle>::CompressBound(int32_t UncompressedSize)
    {
        return OodleLZ_GetCompressedBufferSizeNeeded(OodleLZ_Compressor_Invalid, UncompressedSize);
    }

    template<>
    bool Compressor<CompressionMethod::Oodle>::Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize)
    {
        return OodleLZ_Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
    }
}