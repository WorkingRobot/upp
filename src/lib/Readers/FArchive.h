#pragma once

#include "../Versions/EGame.h"
#include "SeekDirection.h"

#include <string>
#include <vector>

namespace upp::Readers {
    class FArchive {
        // Impl functions
    public:
        virtual size_t Read(char* Data, size_t Size) = 0;

        virtual size_t Size() const = 0;

        virtual size_t Tell() const = 0;

        virtual size_t Seek(ptrdiff_t Offset, SeekDir Direction) = 0;

        // Defined errors
    public:
        enum class Error : uint32_t {
            None,
            FileDoesNotExist,
            CannotSeek,
            InvalidMagic,
            UnsupportedFrozenIndex
        };

        // Public functions
    public:
        bool HasError() const;

        Error GetError() const;

        void SetError(Error NewError);

        void ClearError();

        Versions::EGame GetGame() const;

        const std::string& GetName() const;

        // Stream operations
    public:
        FArchive& operator>>(bool& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(char& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(int8_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(int16_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(int32_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(int64_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(uint8_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(uint16_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(uint32_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(uint64_t& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(float& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        FArchive& operator>>(double& Val) {
            Read((char*)&Val, sizeof(Val));
            return *this;
        }

        template<class T>
        FArchive& operator>>(T& Val) {
            Read((char*)&Val, sizeof(std::underlying_type_t<T>));
            return *this;
        }

        template<class T, uint32_t Size>
        FArchive& operator>>(T(&Val)[Size]) {
            for (uint32_t i = 0; i < Size; ++i) {
                *this >> Val[i];
            }
            return *this;
        }

        template<class K, class V>
        FArchive& operator>>(std::pair<K, V>& Val) {
            *this >> Val.first;
            *this >> Val.second;
            return *this;
        }

        template<class T>
        FArchive& operator>>(std::vector<T>& Val) {
            int SerializeNum;
            *this >> SerializeNum;
            Val.reserve(SerializeNum);
            for (int i = 0; i < SerializeNum; ++i) {
                *this >> Val.emplace_back();
            }
            return *this;
        }

    protected:
        FArchive(Versions::EGame Game, const std::string& Name);

    private:
        Versions::EGame Game;
        std::string Name;
        Error StoredError;
    };
}