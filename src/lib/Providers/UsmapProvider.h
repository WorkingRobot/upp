#pragma once

#include "../Objects/Core/Serialization/FArchive.h"
#include "BaseProvider.h"

namespace upp::Providers {
    class UsmapProvider : public BaseProvider {
    public:
        UsmapProvider(Objects::FArchive& Ar);

    private:
        void Serialize(Objects::FArchive& Ar);

        void SerializePropData(Objects::FArchive& Ar, PropertyData& PropData);
    };
}