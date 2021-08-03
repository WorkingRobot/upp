#pragma once

#include "../Objects/Core/Serialization/FArchive.h"

#include <mutex>

namespace upp::Readers {
    template<class T>
    class ThreadSafeArchive : public T {
        static_assert(std::is_base_of_v<Objects::FArchive, T>, "T must be a derivative of FArchive");

    public:
        template<class... ArgsT>
        ThreadSafeArchive(ArgsT&&... Args) :
            T(std::forward<ArgsT>(Args)...)
        {

        }

        // Only PRead is protected; Read and Seek is inherently not thread safe since it's
        // meant to modify the internal state on purpose (Position, etc)
        // Other const functions like Size or Tell or GetName should already be thread safe
        // This is simply meant as a wrapper to prevent other PRead calls from overlapping
        // on the underlying archive (whose PRead may not be thread safe)
        size_t PRead(char* Data, size_t Size, size_t Offset) override
        {
            std::lock_guard Guard(Mtx);

            return T::PRead(Data, Size, Offset);
        }

    private:
        std::mutex Mtx;
    };

    template<class T>
    ThreadSafeArchive(T&&)->ThreadSafeArchive<T>;
}