#pragma once

#include <stdint.h>
#include <string.h>

namespace upp {
    enum class CompressionMethod : uint8_t {
        None,
        Zlib,
        Gzip,
        Oodle,
        LZ4,
        Brotli
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
        template<CompressionMethod Method>
        static __forceinline bool IsValid() {
            return Detail::Compressor<Method>::IsValid();
        }

        static __forceinline bool IsValid(CompressionMethod Method) {
            switch (Method)
            {
            case CompressionMethod::None:
                return IsValid<CompressionMethod::None>();
            case CompressionMethod::Zlib:
                return IsValid<CompressionMethod::Zlib>();
            case CompressionMethod::Gzip:
                return IsValid<CompressionMethod::Gzip>();
            case CompressionMethod::Oodle:
                return IsValid<CompressionMethod::Oodle>();
            case CompressionMethod::LZ4:
                return IsValid<CompressionMethod::LZ4>();
            case CompressionMethod::Brotli:
                return IsValid<CompressionMethod::Brotli>();
            default:
                return false;
            }
        }

        template<CompressionMethod Method>
        static __forceinline int32_t CompressBound(int32_t UncompressedSize) {
            return Detail::Compressor<Method>::CompressBound(UncompressedSize);
        }

        static __forceinline int32_t CompressBound(CompressionMethod Method, int32_t UncompressedSize) {
            switch (Method)
            {
            case CompressionMethod::None:
                return CompressBound<CompressionMethod::None>(UncompressedSize);
            case CompressionMethod::Zlib:
                return CompressBound<CompressionMethod::Zlib>(UncompressedSize);
            case CompressionMethod::Gzip:
                return CompressBound<CompressionMethod::Gzip>(UncompressedSize);
            case CompressionMethod::Oodle:
                return CompressBound<CompressionMethod::Oodle>(UncompressedSize);
            case CompressionMethod::LZ4:
                return CompressBound<CompressionMethod::LZ4>(UncompressedSize);
            case CompressionMethod::Brotli:
                return CompressBound<CompressionMethod::Brotli>(UncompressedSize);
            default:
                return 0;
            }
        }

        template<CompressionMethod Method>
        static __forceinline bool Decompress(const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize) {
            return Detail::Compressor<Method>::Decompress(CompBuf, CompSize, DecompBuf, DecompSize);
        }

        static __forceinline bool Decompress(CompressionMethod Method, const char* CompBuf, int32_t CompSize, char* DecompBuf, int32_t DecompSize) {
            switch (Method)
            {
            case CompressionMethod::None:
                return Decompress<CompressionMethod::None>(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Zlib:
                return Decompress<CompressionMethod::Zlib>(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Gzip:
                return Decompress<CompressionMethod::Gzip>(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Oodle:
                return Decompress<CompressionMethod::Oodle>(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::LZ4:
                return Decompress<CompressionMethod::LZ4>(CompBuf, CompSize, DecompBuf, DecompSize);
            case CompressionMethod::Brotli:
                return Decompress<CompressionMethod::Brotli>(CompBuf, CompSize, DecompBuf, DecompSize);
            default:
                return false;
            }
        }
    };
}