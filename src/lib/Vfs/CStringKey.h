#pragma once

#include <memory>
#include <string>

namespace upp::Vfs {
    template<bool IsSmall>
    class CStringKey {
    public:
        using SizeT = typename std::conditional_t<IsSmall, uint8_t, uint16_t>;

        CStringKey(const char* String, SizeT Size) :
            Data(new char[Size + 1])
        {
            memcpy(Data.get(), String, Size);
            Data[Size] = '\0';
        }

        CStringKey(std::unique_ptr<char[]>&& Data) :
            Data(std::move(Data))
        {

        }

        CStringKey(CStringKey&& Old) : Data(std::move(Old.Data)) {}

        SizeT GetSize() const {
            return strlen(Data.get());
        }

        const char* GetString() const {
            return Data.get();
        }

        bool compare(const char* Str, SizeT Size) const {
            return GetSize() == Size && memcmp(Str, GetString(), Size) == 0;
        }

        operator std::string() const {
            return { GetString(), GetSize() };
        }

    private:
        std::unique_ptr<char[]> Data;
    };
}