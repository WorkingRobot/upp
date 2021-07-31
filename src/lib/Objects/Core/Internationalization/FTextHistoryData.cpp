#include "FTextHistoryData.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::None>& Value)
    {
		int HasCultureInvariantString;
		Ar >> HasCultureInvariantString;
		if (HasCultureInvariantString) {
			Ar >> Value.CultureInvariantString;
		}

		return Ar;
    }

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::Base>& Value)
	{
		Ar >> Value.Namespace;
		Ar >> Value.Key;
		Ar >> Value.SourceString;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::NamedFormat>& Value)
	{
		Ar >> Value.SourceFmt;
		Ar >> Value.Arguments;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::OrderedFormat>& Value)
	{
		Ar >> Value.SourceFmt;
		Ar >> Value.Arguments;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::ArgumentFormat>& Value)
	{
		Ar >> Value.SourceFmt;
		Ar >> Value.Arguments;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsNumber>& Value)
	{
		Ar >> Value.SourceValue;

		int HasFormatOptions;
		Ar >> HasFormatOptions;
		if (HasFormatOptions) {
			Ar >> Value.FormatOptions.emplace();
		}

		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsPercent>& Value)
	{
		Ar >> Value.SourceValue;

		int HasFormatOptions;
		Ar >> HasFormatOptions;
		if (HasFormatOptions) {
			Ar >> Value.FormatOptions.emplace();
		}

		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsCurrency>& Value)
	{
		Ar >> Value.CurrencyCode;
		Ar >> Value.SourceValue;

		int HasFormatOptions;
		Ar >> HasFormatOptions;
		if (HasFormatOptions) {
			Ar >> Value.FormatOptions.emplace();
		}

		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsDate>& Value)
	{
		Ar >> Value.SourceDateTime;
		Ar >> Value.DateStyle;
		Ar >> Value.TimeZone;
		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsTime>& Value)
	{
		Ar >> Value.SourceDateTime;
		Ar >> Value.TimeStyle;
		Ar >> Value.TimeZone;
		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsDateTime>& Value)
	{
		Ar >> Value.SourceDateTime;
		Ar >> Value.DateStyle;
		Ar >> Value.TimeStyle;
		Ar >> Value.TimeZone;
		Ar >> Value.TargetCulture;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::Transform>& Value)
	{
		Ar >> Value.SourceText;
		Ar >> Value.TransformType;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::StringTableEntry>& Value)
	{
		Ar >> Value.TableId;
		Ar >> Value.Key;

		return Ar;
	}

	FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::TextGenerator>& Value)
	{
		Ar >> Value.GeneratorTypeID;

		// https://github.com/WorkingRobot/ZenReader/blob/6093412027ec8930d68d241f9f2cf0158b1db7b4/src/Structs/FTextHistory.h#L285
		// If the data isn't none, read a TArray<uint8>
		// https://github.com/EpicGames/UnrealEngine/blob/8bcc8f7e4836f6449a86052b3502f79f42c6dba3/Engine/Source/Runtime/Core/Private/Internationalization/TextHistory.cpp#L2942

		return Ar;
	}
}