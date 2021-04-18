#include "Compression.h"

#include <libdeflate.h>

namespace upp::Detail {
    template<>
    bool Compressor<CompressionMethod::Zlib>::IsValid()
    {
        return true;
    }

    template<>
    int32_t Compressor<CompressionMethod::Zlib>::CompressBound(int32_t UncompressedSize)
    {
        return libdeflate_zlib_compress_bound(nullptr, UncompressedSize);
    }

    template<>
    bool Compressor<CompressionMethod::Zlib>::Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize)
    {
        libdeflate_decompressor* Decompressor = libdeflate_alloc_decompressor();
        libdeflate_result Result = libdeflate_zlib_decompress(Decompressor, CompBuf, CompSize, DecompBuf, DecompSize, nullptr);
        libdeflate_free_decompressor(Decompressor);
        return Result == LIBDEFLATE_SUCCESS;
    }
}