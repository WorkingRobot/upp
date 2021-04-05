#pragma once

#include "../../../Readers/FArchive.h"

namespace upp::Objects {
	struct FAESKey {
		char Key[32];

		friend Readers::FArchive& operator>>(Readers::FArchive& InputStream, FAESKey& Value) {
			InputStream >> Value.Key;

			return InputStream;
		}

		bool IsValid() const
		{
			// https://stackoverflow.com/questions/1493936#comment1346424_1493988
			return Key[0] == 0 && !memcmp(Key, Key + 1, sizeof(Key) - 1);
		}
	};
}