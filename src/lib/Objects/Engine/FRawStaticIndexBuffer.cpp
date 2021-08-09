#include "FRawStaticIndexBuffer.h"

namespace upp::Objects {
	// https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/RawIndexBuffer.cpp#L377
    FArchive& operator>>(FArchive& Ar, FRawStaticIndexBuffer& Value)
    {
		int b32Bit;
		Ar >> b32Bit;

		std::vector<char> Data;
		Ar.BulkSerialize(Data);

		int bShouldExpandTo32Bit;
		Ar >> bShouldExpandTo32Bit;

		if (b32Bit) {
			auto& Index = Value.IndexStorage.emplace<std::vector<uint32_t>>();
			Index.resize(Data.size() / sizeof(uint32_t));
			memcpy(Index.data(), Data.data(), Data.size());
		}
		else {
			std::vector<uint16_t> Index;
			Index.resize(Data.size() / sizeof(uint16_t));
			memcpy(Index.data(), Data.data(), Data.size());
			if (bShouldExpandTo32Bit) {
				std::vector<uint32_t> LargeIndex = Value.IndexStorage.emplace<std::vector<uint32_t>>();
				LargeIndex.reserve(Index.size());
				std::copy(Index.begin(), Index.end(), std::back_inserter(LargeIndex));
			}
			else {
				Value.IndexStorage.emplace<std::vector<uint16_t>>(std::move(Index));
			}
		}

		return Ar;
	}
}