#include "FIterator.h"

namespace upp::Objects {
    FIterator::FIterator(const FUnversionedHeader& Header) :
        FragmentItr(Header.Fragments.cbegin()),
        ZeroMaskItr(Header.ZeroMask.cbegin()),
        RemainingFragmentValues(0),
        IsDone(false),
        SchemaIdx(0)
    {
        Skip();
    }

    FIterator& FIterator::operator++()
    {
		if (IsDone) {
			return *this;
		}
		SchemaIdx++;
		RemainingFragmentValues--;
		if (FragmentItr->HasAnyZeroes) {
			ZeroMaskItr++;
		}

		if (RemainingFragmentValues == 0) {
			if (FragmentItr->IsLast) {
				IsDone = true;
				return *this;
			}

			FragmentItr++;
			Skip();
		}
		return *this;
    }

	FIterator::operator bool() const
	{
		return IsValid();
	}

	uint32_t FIterator::GetSchemaIdx() const
	{
		return SchemaIdx;
	}

	bool FIterator::IsValid() const
	{
		return !IsDone;
	}

	bool FIterator::IsNonZero() const
	{
		return !FragmentItr->HasAnyZeroes || !*ZeroMaskItr;
	}

	bool FIterator::ShouldSerialize() const
	{
		return IsValid() && IsNonZero();
	}

	void FIterator::Skip()
	{
		SchemaIdx += FragmentItr->SkipNum;

		while (FragmentItr->ValueNum == 0) {
			if (FragmentItr->IsLast) {
				IsDone = true;
				// Iterator needs data past the last fragment, archive is corrupted
				return;
			}
			FragmentItr++;
			SchemaIdx += FragmentItr->SkipNum;
		}

		RemainingFragmentValues = FragmentItr->ValueNum;
	}
}