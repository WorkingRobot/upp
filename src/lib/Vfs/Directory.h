#pragma once

#include "CStringKey.h"
#include "File.h"
#include "SmallMap.h"

namespace upp::Vfs {
    template<typename K = CStringKey<true>>
    class Directory {
    public:
        static constexpr char SepChar = '/';

        void MergeDirectory(Directory&& Other) {
            Files.Merge<true>(std::move(Other.Files));
            for (auto& Dir : Other.Directories) {
                CreateDirectory<true>(Dir.first.GetString(), Dir.first.GetSize()).MergeDirectory(std::move(Dir.second));
            }
        }

        // No leading / please
        template<bool CheckIfAlreadyExists>
        Directory& CreateDirectories(const char* MountPoint) {
            if (!*MountPoint) {
                return *this;
            }

            const char* NextSeparator = strchr(MountPoint, SepChar);
            return CreateDirectory<CheckIfAlreadyExists>(MountPoint, NextSeparator - MountPoint).template CreateDirectories<CheckIfAlreadyExists>(NextSeparator + 1);
        }

        template<bool CheckIfAlreadyExists>
        Directory& CreateDirectory(const char* DirectoryName, typename K::SizeT NameSize) {
            return Directories.emplace_back<CheckIfAlreadyExists>(DirectoryName, NameSize, Directory());
        }

        template<bool CheckIfAlreadyExists>
        File& CreateFileAtPath(const char* Path, File&& NewFile) {
            const char* NextSeparator = strchr(Path, SepChar);
            if (NextSeparator) {
                return CreateDirectory<CheckIfAlreadyExists>(Path, NextSeparator - Path).template CreateFileAtPath<CheckIfAlreadyExists>(NextSeparator + 1, std::move(NewFile));
            }
            else {
                return CreateFile<CheckIfAlreadyExists>(Path, strlen(Path), std::move(NewFile));
            }
        }

        template<bool CheckIfAlreadyExists>
        File& CreateFile(const char* FileName, typename K::SizeT NameSize, File&& NewFile) {
            return Files.emplace_back<CheckIfAlreadyExists>(FileName, NameSize, std::move(NewFile));
        }

        const File* TryGetPackage(const char* Path) const {
            const char* Separator = strchr(Path, SepChar);
            if (Separator) {
                auto ChildIter = Directories.SearchValues(Path, Separator - Path);
                if (ChildIter != Directories.end()) {
                    return ChildIter->second.TryGetPackage(Separator + 1);
                }
            }
            else {
                auto ChildIter = Files.SearchValues(Path, strlen(Path));
                if (ChildIter != Files.end()) {
                    return &ChildIter->second;
                }
            }

            return nullptr;
        }

    private:
        SmallMap<K, Directory> Directories;
        SmallMap<K, File> Files;

        template<typename T>
        friend class DirectoryIterator;
        template<typename T>
        friend class RecursiveDirectoryIterator;
    };
}