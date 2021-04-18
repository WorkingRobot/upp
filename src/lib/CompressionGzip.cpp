#include "Compression.h"

#include <libdeflate.h>

namespace upp::Detail {
    template<>
    bool Compressor<CompressionMethod::Gzip>::IsValid()
    {
        return true;
    }

    template<>
    int32_t Compressor<CompressionMethod::Gzip>::CompressBound(int32_t UncompressedSize)
    {
        return libdeflate_gzip_compress_bound(nullptr, UncompressedSize);
    }

    template<>
    bool Compressor<CompressionMethod::Gzip>::Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize)
    {
        libdeflate_decompressor* Decompressor = libdeflate_alloc_decompressor();
        libdeflate_result Result = libdeflate_gzip_decompress(Decompressor, CompBuf, CompSize, DecompBuf, DecompSize, nullptr);
        libdeflate_free_decompressor(Decompressor);
        return Result == LIBDEFLATE_SUCCESS;
    }
}