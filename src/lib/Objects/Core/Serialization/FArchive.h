#pragma once

#include "../UObject/FName.h"
#include "ESeekDir.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace upp::Objects {
    class FArchive {
        // Impl functions
    public:
        virtual size_t Read(char* Data, size_t Size) = 0;

        virtual size_t Size() const = 0;

        virtual size_t Tell() const = 0;

        virtual size_t Seek(ptrdiff_t Offset, ESeekDir Direction) = 0;

        virtual size_t PRead(char* Data, size_t Size, size_t Offset)
        {
            // Not using a mutex here because there's no reason to add extra overhead (instead, use a wrapper or override it yourself)
            auto Pos = Tell();
            Seek(Offset, ESeekDir::Beg);
            auto Ret = Read(Data, Size);
            Seek(Pos, ESeekDir::Beg);
            return Ret;
        }

        // Public functions
    public:
        virtual ~FArchive() = default;

        const std::string& GetName() const;

        // Stream operations
    public:
        // When porting code, remember that bools are actually 4 bytes, not 1 (in UE)
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

        virtual FArchive& operator>>(FName& Val) {
            *this >> Val.Index;
            *this >> Val.Number;

            return *this;
        }

        FArchive& operator>>(std::string& Val) {
            // > 0 for ANSICHAR, < 0 for UCS2CHAR serialization
            int SaveNum;
            *this >> SaveNum;

            if (SaveNum == 0) {
                Val.clear();
                return *this;
            }

            if (SaveNum < 0) // LoadUCS2Char
            {
                // If SaveNum cannot be negated due to integer overflow, Ar is corrupted.
                if (SaveNum == std::numeric_limits<int>::min()) {
                    // Tried to read FString with an invalid length
                    return *this;
                }

                SaveNum = -SaveNum;

                std::wstring StringData(SaveNum, '\0');
                Read((char*)StringData.data(), SaveNum * sizeof(char16_t));
                Val = std::filesystem::path(StringData).string();
            }
            else {
                Val.resize(SaveNum - 1);
                Read(Val.data(), SaveNum);
            }

            return *this;
        }

        template<class T>
        FArchive& operator>>(T& Val) {
            Read((char*)&Val, sizeof(std::underlying_type_t<T>));
            return *this;
        }

        template<class T, uint32_t Size, std::enable_if_t<std::is_arithmetic_v<T>, bool> = true>
        FArchive& operator>>(T(&Val)[Size]) {
            Read((char*)Val, Size * sizeof(T));

            return *this;
        }

        template<class T, uint32_t Size, std::enable_if_t<!std::is_arithmetic_v<T>, bool> = true>
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

        // ReadCount is the element count, not byte count
        // Micro optimization to simply copy into the vector buffer
        // This is not a specialization of >> std::vector<T> because
        // it's impossible to know if >> does the same thing as a memcpy
        // This does not use std::has_unique_object_representations_v<T>
        // because it doesn't work on floats, so it's up to you to use this
        template<class T>
        void ReadBuffer(std::vector<T>& Val, size_t ReadCount) {
            Val.resize(ReadCount);
            Read((char*)Val.data(), ReadCount * sizeof(T));
        }

        template<class T>
        void ReadBuffer(std::vector<T>& Val) {
            int ReadCount;
            *this >> ReadCount;
            ReadBuffer(Val, ReadCount);
        }

        // https://github.com/EpicGames/UnrealEngine/blob/93ac332d31ed59b186e1b29ad58e9cc395af12b2/Engine/Source/Runtime/Core/Public/Containers/Array.h#L1251
        template<class T>
        void BulkSerialize(std::vector<T>& Val) {
            int SerializedElementSize;
            *this >> SerializedElementSize;
#ifdef _DEBUG
            if (SerializedElementSize != sizeof(T)) {
                _CrtDbgBreak();
            }
#endif
            ReadBuffer(Val);
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

        // More optimized version of std::vector<char> in a more useful container
        FArchive& operator>>(std::unique_ptr<char[]>& Val) {
            int SerializeNum;
            *this >> SerializeNum;
            Val = std::make_unique<char[]>(SerializeNum);
            Read(Val.get(), SerializeNum);
            return *this;
        }

        void Dump(const char* Path) {
            auto b = std::make_unique<char[]>(Size());
            PRead(b.get(), Size(), 0);

            auto f = fopen(Path, "wb");
            fwrite(b.get(), Size(), 1, f);
            fclose(f);
        }

    protected:
        FArchive(const std::string& Name);

    private:
        std::string Name;
    };
}