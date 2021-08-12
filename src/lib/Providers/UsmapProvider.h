#pragma once

#include "../Objects/Core/Serialization/FArchive.h"
#include "BaseProvider.h"

namespace upp::Providers {
    class UsmapProvider : public BaseProvider {
    public:
        UsmapProvider(Objects::FArchive& Ar);

    private:
        void Serialize(Objects::FArchive& Ar);

        struct LUT;
        void SerializePropData(Objects::FArchive& Ar, PropertyData& PropData, const LUT& LUT);

        void ClonePropData(const PropertyData& Source, PropertyData& PropData, const LUT& LUT);
    };
}