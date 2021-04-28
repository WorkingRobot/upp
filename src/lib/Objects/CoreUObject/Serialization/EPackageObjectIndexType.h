#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EPackageObjectIndexType : uint8_t {
		Export,
		ScriptImport,
		PackageImport,
		Null,
		TypeCount = Null,
    };
}