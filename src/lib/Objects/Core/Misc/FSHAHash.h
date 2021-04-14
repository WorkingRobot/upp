#pragma once

#include "../Serialization/FArchive.h"

namespace upp::Objects {
	struct FSHAHash {
		char Hash[20];

		friend FArchive& operator>>(FArchive& Ar, FSHAHash& Value);

		static FSHAHash HashBuffer(const char* Buffer, size_t BufferSize);

		bool VerifyBuffer(const char* Buffer, size_t BufferSize) const;
	};
}