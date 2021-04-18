#pragma once

#include <stdint.h>
#include <string.h>

namespace upp {
    enum class CompressionMethod : uint8_t {
        None,
        Zlib,
        Gzip,
        Oodle,
        LZ4
    };

    namespace Detail {
        template<CompressionMethod Method>
        class Compressor {
        public:
            static bool IsValid();

            static int32_t CompressBound(int32_t UncompressedSize);

            static bool Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize);
        };

        template<>
        class Compressor<CompressionMethod::None> {
        public:
            static __forceinline bool IsValid() {
                return true;
            }

            static __forceinline int32_t CompressBound(int32_t UncompressedSize) {
                return UncompressedSize;
            }

            static __forceinline bool Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize) {
                return memcpy_s(DecompBuf, DecompSize, CompBuf, CompSize) == 0;
            }
        };
    }

    class Compression {
    public:
        static __forceinline bool IsValid(CompressionMethod Method) {
            switch (Method)
            {
            case CompressionMethod::None:
                return Detail::Compressor<CompressionMethod::None>::IsValid();
            case CompressionMethod::Zlib:
                return Detail::Compressor<CompressionMethod::Zlib>::IsValid();
            case CompressionMethod::Gzip:
                return Detail::Compressor<CompressionMethod::Gzip>::IsValid();
            case CompressionMethod::Oodle:
                return Detail::Compressor<CompressionMethod::Oodle>::IsValid();
            case CompressionMethod::LZ4:
                return Detail::Compressor<CompressionMethod::LZ4>::IsValid();
            default:
                return 0;
            }
        }

        static __forceinline int32_t CompressBound(CompressionMethod Method, int32_t UncompressedSize) {
            switch (Method)
            {
            case CompressionMethod::None:
                return Detail::Compressor<CompressionMethod::None>::CompressBound(UncompressedSize);
            case CompressionMethod::Zlib:
                return Detail::Compressor<CompressionMethod::Zlib>::CompressBound(UncompressedSize);
            case CompressionMethod::Gzip:
                return Detail::Compressor<CompressionMethod::Gzip>::CompressBound(UncompressedSize);
            case CompressionMethod::Oodle:
                return Detail::Compressor<CompressionMethod::Oodle>::CompressBound(UncompressedSize);
            case CompressionMethod::LZ4:
                return Detail::Compressor<CompressionMethod::LZ4>::CompressBound(UncompressedSize);
            default:
                return 0;
            }
        }

        static __forceinline bool Decompress(CompressionMethod Method, const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize) {
            switch (Method)
            {
            case CompressionMethod::None:
                return Detail::Compressor<CompressionMethod::None>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Zlib:
                return Detail::Compressor<CompressionMethod::Zlib>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Gzip:
                return Detail::Compressor<CompressionMethod::Gzip>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Oodle:
                return Detail::Compressor<CompressionMethod::Oodle>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::LZ4:
                return Detail::Compressor<CompressionMethod::LZ4>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
            default:
                return false;
            }
        }
    };
}