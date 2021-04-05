#pragma once

#include "../../../Readers/FArchive.h"

namespace upp::Objects {
	struct FSHAHash {
		char Hash[20];

		friend Readers::FArchive& operator>>(Readers::FArchive& InputStream, FSHAHash& Value) {
			InputStream >> Value.Hash;

			return InputStream;
		}
	};
}