#pragma once

#include "../Crc32.h"

namespace upp::Vfs {
    template<typename K, typename V>
    class SmallMap {
    public:
        typename std::vector<std::pair<K, V>>::const_iterator begin() const noexcept {
            return Data.begin();
        }

        typename std::vector<std::pair<K, V>>::iterator begin() noexcept {
            return Data.begin();
        }

        typename std::vector<std::pair<K, V>>::const_iterator end() const noexcept {
            return Data.end();
        }

        typename std::vector<std::pair<K, V>>::iterator end() noexcept {
            return Data.end();
        }

        template<bool CheckIfAlreadyExists>
        V& emplace_back(const char* KeyString, typename K::SizeT KeyStringSize, V&& Value) {
            if constexpr (CheckIfAlreadyExists) {
                auto ChildIter = SearchValues(KeyString, KeyStringSize);
                if (ChildIter != end()) {
                    return ChildIter->second;
                }
            }

            Hashes.emplace_back(upp::Crc32(KeyString, KeyStringSize));
            return Data.emplace_back(K(KeyString, KeyStringSize), std::move(Value)).second;
        }

        typename std::vector<std::pair<K, V>>::iterator SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) {
            if (Hashes.size() != 0) {
                uint32_t TargetHash = upp::Crc32(KeyString, KeyStringSize);
                for (int Idx = 0; Idx < Hashes.size(); ++Idx) {
                    if (TargetHash == Hashes[Idx]) {
                        auto& Key = Data[Idx].first;
                        if (Key.GetSize() == KeyStringSize && !memcmp(Key.GetString(), KeyString, KeyStringSize)) [[likely]] {
                            return Data.begin() + Idx;
                        }
                    }
                }
            }

            return end();
        }

        template<bool CheckIfAlreadyExists>
        void Merge(typename SmallMap<K, V>&& Other) {
            for (auto& Item : Other.Data) {
                emplace_back<CheckIfAlreadyExists>(Item.first.GetString(), Item.first.GetSize(), std::move(Item.second));
            }
        }

        typename std::vector<std::pair<K, V>>::const_iterator SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) const {
            // Forces a call to the non const SearchValues and converts the return value to a const_iterator
            return ((std::remove_cvref_t<decltype(*this)>*)this)->SearchValues(KeyString, KeyStringSize);
        }

    private:
        std::vector<uint32_t> Hashes;
        std::vector<std::pair<K, V>> Data;
    };
}