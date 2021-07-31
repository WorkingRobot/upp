#pragma once

#include "../Misc/FDateTime.h"
#include "../Serialization/FArchive.h"
#include "../UObject/FName.h"
#include "EDateTimeStyle.h"
#include "ETextHistoryType.h"
#include "ETransformType.h"
#include "FFormatNamedArguments.h"
#include "FNumberFormattingOptions.h"
#include "FText.h"

namespace upp::Objects {
    template<ETextHistoryType Type>
    struct FTextHistoryData;

    template<>
    struct FTextHistoryData<ETextHistoryType::None>
    {
        std::string CultureInvariantString;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::None>& Value);
    };

    template<>
    struct FTextHistoryData<ETextHistoryType::Base>
    {
        std::string Namespace;
        std::string Key;
        std::string SourceString;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::Base>& Value);
    };

	template<>
	struct FTextHistoryData<ETextHistoryType::NamedFormat> {
		FText SourceFmt;
		FFormatNamedArguments Arguments;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::NamedFormat>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::OrderedFormat> {
		FText SourceFmt;
		FFormatNamedArguments Arguments;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::OrderedFormat>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::ArgumentFormat> {
		FText SourceFmt;
		std::vector<FFormatArgumentValue> Arguments;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::ArgumentFormat>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsNumber> {
		FFormatArgumentValue SourceValue;
		// FModel skips FormatOptions and provides a std::string TimeZone (?)
		std::optional<FNumberFormattingOptions> FormatOptions;
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsNumber>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsPercent> {
		FFormatArgumentValue SourceValue;
		// FModel skips FormatOptions and provides a std::string TimeZone (?)
		std::optional<FNumberFormattingOptions> FormatOptions;
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsPercent>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsCurrency> {
		std::string CurrencyCode;
		FFormatArgumentValue SourceValue;
		// FModel skips FormatOptions and provides a std::string TimeZone (?)
		std::optional<FNumberFormattingOptions> FormatOptions;
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsCurrency>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsDate> {
		FDateTime SourceDateTime;
		EDateTimeStyle DateStyle;
		std::string TimeZone;
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsDate>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsTime> {
		FDateTime SourceDateTime;
		EDateTimeStyle TimeStyle;
		std::string TimeZone;
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsTime>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::AsDateTime> {
		FDateTime SourceDateTime;
		EDateTimeStyle DateStyle;
		EDateTimeStyle TimeStyle;

		std::string TimeZone;

		// UE4 converts the string into an FCulturePtr
		// https://github.com/EpicGames/UnrealEngine/blob/bf95c2cbc703123e08ab54e3ceccdd47e48d224a/Engine/Source/Runtime/Core/Private/Internationalization/TextHistory.cpp#L2188
		std::string TargetCulture;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::AsDateTime>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::Transform> {
		FText SourceText;
		ETransformType TransformType;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::Transform>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::StringTableEntry> {
		FName TableId;
		std::string Key;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::StringTableEntry>& Value);
	};

	template<>
	struct FTextHistoryData<ETextHistoryType::TextGenerator> {
		FName GeneratorTypeID;

		friend FArchive& operator>>(FArchive& Ar, FTextHistoryData<ETextHistoryType::TextGenerator>& Value);
	};
}