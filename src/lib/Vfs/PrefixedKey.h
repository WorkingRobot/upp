#pragma once

#include <memory>

namespace upp::Vfs {
    template<bool IsSmall>
    class PrefixedKey {
    public:
        using SizeT = typename std::conditional_t<IsSmall, uint8_t, uint16_t>;

        PrefixedKey(const char* String, SizeT Size) :
            Data(new char[sizeof(SizeT) + Size])
        {
            *(SizeT*)Data.get() = Size;
            memcpy(Data.get() + sizeof(SizeT), String, Size);
        }

        PrefixedKey(std::unique_ptr<char[]>&& Data) :
            Data(std::move(Data))
        {

        }

        PrefixedKey(PrefixedKey&& Old) : Data(std::move(Old.Data)) {}

        SizeT GetSize() const {
            return *(SizeT*)Data.get();
        }

        const char* GetString() const {
            return Data.get() + sizeof(SizeT);
        }

    private:
        std::unique_ptr<char[]> Data;
    };
}