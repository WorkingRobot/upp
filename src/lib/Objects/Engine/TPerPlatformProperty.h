#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    template<class T>
    struct TPerPlatformProperty {
        bool IsCooked;
        T Default;

        friend FArchive& operator>>(FArchive& Ar, TPerPlatformProperty& Value)
        {
            int bCooked;
            Ar >> bCooked;
            Value.IsCooked = bCooked;
            Ar >> Value.Default;

            return Ar;
        }
    };

    template<>
    struct TPerPlatformProperty<bool> {
        bool IsCooked;
        bool Default;

        friend FArchive& operator>>(FArchive& Ar, TPerPlatformProperty& Value)
        {
            int bCooked;
            Ar >> bCooked;
            Value.IsCooked = bCooked;
            int bDefault;
            Ar >> bDefault;
            Value.Default = bDefault;

            return Ar;
        }
    };

    using FPerPlatformInt = TPerPlatformProperty<int>;
    using FPerPlatformFloat = TPerPlatformProperty<float>;
    using FPerPlatformBool = TPerPlatformProperty<bool>;
}