#pragma once

#include "Directory.h"

#include <stack>

namespace upp::Vfs {
    template<typename K>
    class DirectoryEntry {
    public:
        DirectoryEntry() noexcept = default;
        DirectoryEntry(const DirectoryEntry&) = default;
        DirectoryEntry(DirectoryEntry&&) noexcept = default;

        explicit DirectoryEntry(const K& Name, const Directory<K>& Data) :
            Name(&Name),
            Data(&Data),
            IsADirectory(true)
        {
            
        }

        explicit DirectoryEntry(const K& Name, const File& Data) :
            Name(&Name),
            Data(&Data),
            IsADirectory(false)
        {

        }

        DirectoryEntry& operator=(const DirectoryEntry&) = default;
        DirectoryEntry& operator=(DirectoryEntry&&) noexcept = default;

        ~DirectoryEntry() = default;

        const K& GetName() const {
            return *Name;
        }

        bool IsDirectory() const {
            return IsADirectory;
        }

        bool IsFile() const {
            return !IsADirectory;
        }

        const Directory<K>* GetDirectory() const {
            return IsDirectory() ? (const Directory<K>*)Data : nullptr;
        }

        const File* GetFile() const {
            return IsFile() ? (const File*)Data : nullptr;
        }

    private:
        const K* Name;
        const void* Data;
        bool IsADirectory;
    };

    template<typename K = CStringKey<true>>
    class DirectoryIterator {
    public:
        using value_type = typename DirectoryEntry<K>;
        using difference_type = ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::input_iterator_tag;

        DirectoryIterator() noexcept = default;
        DirectoryIterator(const DirectoryIterator&) noexcept = default;
        DirectoryIterator(DirectoryIterator&&) noexcept = default;

        explicit DirectoryIterator(const Directory<K>& Dir) :
            Dir(&Dir),
            DirItr(Dir.Directories.begin()),
            FileItr(Dir.Files.begin())
        {
            RefreshEntry();
        }

        DirectoryIterator& operator=(const DirectoryIterator&) noexcept = default;
        DirectoryIterator& operator=(DirectoryIterator&&) noexcept = default;

        ~DirectoryIterator() noexcept = default;

        const value_type& operator*() const {
            return Entry;
        }

        const value_type* operator->() const {
            return &Entry;
        }

        DirectoryIterator& Increment() {
            if (!Dir) {
                return *this;
            }

            if (DirItr != Dir->Directories.end()) {
                ++DirItr;
            }
            else if (FileItr != Dir->Files.end()) {
                ++FileItr;
            }

            RefreshEntry();

            return *this;
        }

        DirectoryIterator& operator++() {
            return Increment();
        }

        DirectoryIterator operator++(int) {
            DirectoryIterator Proxy(*this);
            Increment();
            return Proxy;
        }

        [[nodiscard]] bool operator==(const DirectoryIterator& Other) const noexcept {
            if (IsAtEnd() && Other.IsAtEnd()) {
                return true;
            }
            return Dir == Other.Dir && DirItr == Other.DirItr && FileItr == Other.FileItr;
        }

        [[nodiscard]] bool operator!=(const DirectoryIterator& Other) const noexcept {
            return !(*this == Other);
        }

    private:
        bool IsAtEnd() const noexcept {
            return Dir == nullptr || (DirItr == Dir->Directories.end() && FileItr == Dir->Files.end());
        }

        void RefreshEntry() {
            if (DirItr != Dir->Directories.end()) {
                Entry = DirectoryEntry<K>(DirItr->first, DirItr->second);
            }
            else if (FileItr != Dir->Files.end()) {
                Entry = DirectoryEntry<K>(FileItr->first, FileItr->second);
            }
            else {
                Entry = DirectoryEntry<K>();
            }
        }

        DirectoryEntry<K> Entry;
        const Directory<K>* Dir;
        decltype(Directory<K>::Directories.cbegin()) DirItr;
        decltype(Directory<K>::Files.cbegin()) FileItr;
    };

    template<typename K>
    [[nodiscard]] inline DirectoryIterator<K> begin(DirectoryIterator<K> Iter) noexcept {
        return Iter;
    }

    template<typename K>
    [[nodiscard]] inline DirectoryIterator<K> end(DirectoryIterator<K>) noexcept {
        return {};
    }

    template<typename K = CStringKey<true>>
    class RecursiveDirectoryIterator {
    public:
        using value_type = typename DirectoryEntry<K>;
        using difference_type = ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::input_iterator_tag;

        RecursiveDirectoryIterator() noexcept = default;
        RecursiveDirectoryIterator(const RecursiveDirectoryIterator&) noexcept = default;
        RecursiveDirectoryIterator(RecursiveDirectoryIterator&&) noexcept = default;

        explicit RecursiveDirectoryIterator(const Directory<K>& Dir) :
            Dir(&Dir),
            IsRecursionPending(true)
        {
            Stack.emplace(Dir);
        }

        RecursiveDirectoryIterator& operator=(const RecursiveDirectoryIterator&) noexcept = default;
        RecursiveDirectoryIterator& operator=(RecursiveDirectoryIterator&&) noexcept = default;

        ~RecursiveDirectoryIterator() noexcept = default;

        const value_type& operator*() const {
            return *Stack.top();
        }

        const value_type* operator->() const {
            return &*Stack.top();
        }

        // Exclude the top element, the root directory has 0 depth
        int Depth() const {
            return Stack.size() - 1;
        }

        bool RecursionPending() const {
            return IsRecursionPending;
        }

        RecursiveDirectoryIterator& Increment() {
            if (Stack.empty()) {
                return *this;
            }

            if (Stack.top()->IsDirectory() && IsRecursionPending) {
                Stack.emplace(*Stack.top()->GetDirectory());
            }
            else {
                ++Stack.top();
            }

            IsRecursionPending = true;

            while (true) {
                if (Stack.top() != end(Stack.top())) {
                    break;
                }

                Stack.pop();

                if (Stack.empty()) {
                    break;
                }
                ++Stack.top();
            }

            return *this;
        }

        RecursiveDirectoryIterator& operator++() {
            return Increment();
        }

        RecursiveDirectoryIterator operator++(int) {
            RecursiveDirectoryIterator Proxy(*this);
            Increment();
            return Proxy;
        }

        void Pop() {
            Stack.pop();
        }

        void DisableRecursionPending() {
            IsRecursionPending = false;
        }

        [[nodiscard]] bool operator==(const RecursiveDirectoryIterator& Other) const noexcept {
            if (IsAtEnd() && Other.IsAtEnd()) {
                return true;
            }
            return Dir == Other.Dir && Stack == Other.Stack;
        }

        [[nodiscard]] bool operator!=(const RecursiveDirectoryIterator& Other) const noexcept {
            return !(*this == Other);
        }

    private:
        bool IsAtEnd() const noexcept {
            return Stack.empty();
        }

        const Directory<K>* Dir;
        std::stack<DirectoryIterator<K>> Stack;
        bool IsRecursionPending;
    };

    template<typename K>
    [[nodiscard]] inline RecursiveDirectoryIterator<K> begin(RecursiveDirectoryIterator<K> Iter) noexcept {
        return Iter;
    }

    template<typename K>
    [[nodiscard]] inline RecursiveDirectoryIterator<K> end(RecursiveDirectoryIterator<K>) noexcept {
        return {};
    }
}