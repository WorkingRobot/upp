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

        // ReadCount is the element count, not byte count
        // Micro optimization to simply copy into the vector buffer
        // This is not a specialization of >> std::vector<T> because
        // it's impossible to know if >> does the same thing as a memcpy
        template<class T, std::enable_if_t<std::has_unique_object_representations_v<T>, bool> = true>
        void ReadBuffer(std::vector<T>& Val, size_t ReadCount) {
            Val.resize(ReadCount);
            Read((char*)Val.data(), ReadCount * sizeof(T));
        }

        template<class T, std::enable_if_t<std::has_unique_object_representations_v<T>, bool> = true>
        void ReadBuffer(std::vector<T>& Val) {
            int ReadCount;
            *this >> ReadCount;
            ReadBuffer(Val, ReadCount);
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
            auto o = Tell();
            auto f = fopen(Path, "wb");
            auto b = std::make_unique<char[]>(Size());
            Seek(0, ESeekDir::Beg);
            Read(b.get(), Size());
            fwrite(b.get(), Size(), 1, f);
            fclose(f);
            Seek(o, ESeekDir::Beg);
        }

    protected:
        FArchive(const std::string& Name);

    private:
        std::string Name;
    };
}