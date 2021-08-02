#pragma once

#include <memory>
#include <string>

namespace upp::Objects {
	struct FName {
        uint32_t Index;
        uint32_t Number;
        const std::string* String;

        FName() = default;

        operator const std::string&() const;

        bool IsNone() const;
	};
}