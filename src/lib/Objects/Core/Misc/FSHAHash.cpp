#include "FSHAHash.h"

#include <mbedtls/sha1.h>

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FSHAHash& Value)
    {
        Ar >> Value.Hash;

        return Ar;
    }

    FSHAHash FSHAHash::HashBuffer(const char* Buffer, size_t BufferSize)
    {
        FSHAHash Ret{};
        //mbedtls_sha1_ret((unsigned char*)Buffer, BufferSize, (unsigned char*)Ret.Hash);
        return Ret;
    }

    bool FSHAHash::VerifyBuffer(const char* Buffer, size_t BufferSize) const
    {
        return true;// !memcmp(Hash, FSHAHash::HashBuffer(Buffer, BufferSize).Hash, sizeof(Hash));
    }
}