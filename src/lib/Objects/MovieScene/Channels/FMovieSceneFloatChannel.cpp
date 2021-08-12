#include "FMovieSceneFloatChannel.h"

namespace upp::Objects {
    FArchive& operator>>(FArchive& Ar, FMovieSceneFloatChannel& Value)
    {
        Ar >> Value.PreInfinityExtrap;
        Ar >> Value.PostInfinityExtrap;

        {
            int SerializedElementSize;
            Ar >> SerializedElementSize;
            if (SerializedElementSize != sizeof(FFrameNumber)) {
                Ar >> Value.Times;
            }
            else {
                int NewArrayNum;
                Ar >> NewArrayNum;
                Value.Times.resize(NewArrayNum);
                Ar.Read((char*)Value.Times.data(), NewArrayNum * SerializedElementSize);
            }
        }
        {
            int SerializedElementSize;
            Ar >> SerializedElementSize;
            if (SerializedElementSize != sizeof(FMovieSceneFloatValue)) {
                Ar >> Value.Values;
            }
            else {
                int NewArrayNum;
                Ar >> NewArrayNum;
                Value.Values.resize(NewArrayNum);
                Ar.Read((char*)Value.Values.data(), NewArrayNum * SerializedElementSize);
            }
        }

        Ar >> Value.DefaultValue;
        int bHasDefaultValue;
        Ar >> bHasDefaultValue;
        Value.HasDefaultValue = bHasDefaultValue;
        Ar >> Value.TickResolution.Numerator;
        Ar >> Value.TickResolution.Denominator;
        int Padding;
        Ar >> Padding;
        return Ar;
    }
}