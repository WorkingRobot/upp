#pragma once

#include "FUnversionedHeader.h"

namespace upp::Objects {
    struct FIterator {
        FIterator(const FUnversionedHeader& Header);

        FIterator& operator++();

        operator bool() const;

        uint32_t GetSchemaIdx() const;

        bool IsValid() const;

        bool IsNonZero() const;

        bool ShouldSerialize() const;

    private:
        void Skip();

        std::vector<FFragment>::const_iterator FragmentItr;
        std::vector<bool>::const_iterator ZeroMaskItr;
        uint32_t RemainingFragmentValues;
        bool IsDone;
        uint32_t SchemaIdx;
    };
}