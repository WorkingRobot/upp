#pragma once

#include "../Serialization/FArchive.h"
#include "ETextFlag.h"

namespace upp::Objects {
    struct FTextHistory;

	struct FText {
        std::shared_ptr<FTextHistory> History;
        ETextFlag Flags;

        friend FArchive& operator>>(FArchive& Ar, FText& Value);
	};
}