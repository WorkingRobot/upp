#pragma once

#include "../Crc32.h"

#include <vector>
#include <unordered_map>

namespace upp::Vfs {
    template<typename K, typename V, bool UseMap = false>
    class SmallMap {
    public:
        auto cbegin() const noexcept {
            return Data.cbegin();
        }

        auto begin() const noexcept {
            return Data.begin();
        }

        auto begin() noexcept {
            return Data.begin();
        }

        auto cend() const noexcept {
            return Data.cend();
        }

        auto end() const noexcept {
            return Data.end();
        }

        auto end() noexcept {
            return Data.end();
        }

        auto size() const noexcept {
            return Hashes.size();
        }

        void reserve(int Size) {
            Hashes.reserve(Size);
            Data.reserve(Size);
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

        template<bool CheckIfAlreadyExists>
        V& emplace_back(const K& Key, V&& Value) {
            return emplace_back<CheckIfAlreadyExists>(Key.GetString(), Key.GetSize(), std::move(Value));
        }

        template<bool CheckIfAlreadyExists>
        V& emplace_back(K&& Key, V&& Value) {
            if constexpr (CheckIfAlreadyExists) {
                auto ChildIter = SearchValues(Key.GetString(), Key.GetSize());
                if (ChildIter != end()) {
                    return ChildIter->second;
                }
            }

            Hashes.emplace_back(upp::Crc32(Key.GetString(), Key.GetSize()));
            return Data.emplace_back(std::move(Key), std::move(Value)).second;
        }

        auto SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) {
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

        auto SearchValues(const K& Key) {
            return SearchValues(Key.GetString(), Key.GetSize());
        }

        template<bool CheckIfAlreadyExists>
        void Merge(typename SmallMap&& Other) {
            for (auto& Item : Other.Data) {
                emplace_back<CheckIfAlreadyExists>(Item.first.GetString(), Item.first.GetSize(), std::move(Item.second));
            }
        }

        auto SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) const {
            // Forces a call to the non const SearchValues and converts the return value to a const_iterator
            return ((std::remove_cvref_t<decltype(*this)>*)this)->SearchValues(KeyString, KeyStringSize);
        }

        auto SearchValues(const K& Key) const {
            // Forces a call to the non const SearchValues and converts the return value to a const_iterator
            return ((std::remove_cvref_t<decltype(*this)>*)this)->SearchValues(Key);
        }

    private:
        std::vector<uint32_t> Hashes;
        std::vector<std::pair<K, V>> Data;
    };

    template<typename K, typename V>
    class SmallMap<K, V, true> {
    public:
        auto cbegin() const noexcept {
            return Data.cbegin();
        }

        auto begin() const noexcept {
            return Data.begin();
        }

        auto begin() noexcept {
            return Data.begin();
        }

        auto cend() const noexcept {
            return Data.cend();
        }

        auto end() const noexcept {
            return Data.end();
        }

        auto end() noexcept {
            return Data.end();
        }

        auto size() const noexcept {
            return Data.size();
        }

        void reserve(int Size) {
            Data.reserve(Size);
        }

        template<bool CheckIfAlreadyExists>
        V& emplace_back(const char* KeyString, typename K::SizeT KeyStringSize, V&& Value) {
            return Data.emplace(K(KeyString, KeyStringSize), std::move(Value)).first->second;
        }

        template<bool CheckIfAlreadyExists>
        V& emplace_back(const K& Key, V&& Value) {
            return emplace_back<CheckIfAlreadyExists>(Key.GetString(), Key.GetSize(), std::move(Value));
        }

        template<bool CheckIfAlreadyExists>
        V& emplace_back(K&& Key, V&& Value) {
            return Data.emplace(std::move(Key), std::move(Value)).first->second;
        }

        auto SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) {
            return Data.find(K(KeyString, KeyStringSize));
        }

        auto SearchValues(const K& Key) {
            return Data.find(Key);
        }

        template<bool CheckIfAlreadyExists>
        void Merge(typename SmallMap&& Other) {
            Data.reserve(Data.size() + Other.Data.size());
            Data.merge(std::move(Other.Data));
        }

        template<typename PredT>
        size_t erase_if(PredT Pred) {
            return std::erase_if(Data, Pred);
        }

        auto SearchValues(const char* KeyString, typename K::SizeT KeyStringSize) const {
            // Forces a call to the non const SearchValues and converts the return value to a const_iterator
            return ((std::remove_cvref_t<decltype(*this)>*)this)->SearchValues(KeyString, KeyStringSize);
        }

        auto SearchValues(const K& Key) const {
            // Forces a call to the non const SearchValues and converts the return value to a const_iterator
            return ((std::remove_cvref_t<decltype(*this)>*)this)->SearchValues(Key);
        }

    private:
        std::unordered_map<K, V> Data;
    };
}