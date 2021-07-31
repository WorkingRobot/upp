#include "IoReader.h"

#include "../Objects/CoreUObject/Serialization/FExportBundleEntry.h"
#include "../Objects/CoreUObject/Serialization/FExportBundleHeader.h"
#include "../Objects/CoreUObject/Serialization/FExportMapEntry.h"
#include "../Objects/CoreUObject/Serialization/FPackageSummary.h"
#include "../Vfs/Vfs.h"
#include "../Align.h"

namespace upp::Readers {
    using namespace Objects;

    struct FArc {
        int32_t FromExportBundleIdx;
        int32_t ToExportBundleIdx;

        friend FArchive& operator>>(FArchive& Ar, FArc& Value)
        {
            Ar >> Value.FromExportBundleIdx;
            Ar >> Value.ToExportBundleIdx;

            return Ar;
        }
    };

    struct FImportedPackage {
        FPackageId ImportedPackageId;
        std::vector<FArc> ExternalArcs;

        friend FArchive& operator>>(FArchive& Ar, FImportedPackage& Value)
        {
            Ar >> Value.ImportedPackageId;
            Ar.ReadBuffer(Value.ExternalArcs);

            return Ar;
        }
    };

    std::unique_ptr<UPackage> IoReader::ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs)
    {
        FContainerHeader Header;
        GetHeader(Header);
        auto& GlobalData = Vfs.GetGlobalData();
        auto Ret = std::make_unique<UPackage>();

        FPackageId Id{ ChunkIds[AssetIdx].GetId() };
        auto Itr = std::find(Header.PackageIds.begin(), Header.PackageIds.end(), Id);
        if (Itr == Header.PackageIds.end()) {
            return nullptr;
        }
        auto Dist = std::distance(Header.PackageIds.begin(), Itr);
        auto& Entry = Header.StoreEntries[Dist];

        auto AssetArPtr = OpenFile(AssetIdx);
        if (AssetArPtr == nullptr) {
            return nullptr;
        }
        auto& AssetAr = *AssetArPtr;

        // https://github.com/EpicGames/UnrealEngine/blob/5df54b7ef1714f28fb5da319c3e83d96f0bedf08/Engine/Source/Runtime/CoreUObject/Private/Serialization/AsyncLoading2.cpp#L3415
        FPackageSummary Summary;
        AssetAr >> Summary;
        
        std::vector<std::string> NameMap;
        AssetAr.Seek(Summary.NameMapNamesOffset, ESeekDir::Beg);
        Vfs::GlobalData::ReadNameMap(AssetAr, Summary.NameMapHashesSize, NameMap);

        std::vector<FPackageObjectIndex> ImportMap;
        AssetAr.Seek(Summary.ImportMapOffset, ESeekDir::Beg);
        AssetAr.ReadBuffer(ImportMap, (Summary.ExportMapOffset - Summary.ImportMapOffset) / sizeof(FPackageObjectIndex));

        std::vector<FExportMapEntry> ExportMap;
        AssetAr.Seek(Summary.ExportMapOffset, ESeekDir::Beg);
        AssetAr.ReadBuffer(ExportMap, Entry.ExportCount);
        Ret->Exports.resize(Entry.ExportCount);

        std::vector<FExportBundleHeader> BundleHeaders;
        std::vector<FExportBundleEntry> BundleEntries;
        AssetAr.Seek(Summary.ExportBundlesOffset, ESeekDir::Beg);
        AssetAr.ReadBuffer(BundleHeaders, Entry.ExportBundleCount);
        AssetAr.ReadBuffer(BundleEntries, Entry.ExportCount * (int32_t)EExportCommandType::Count);

        // https://github.com/EpicGames/UnrealEngine/blob/5df54b7ef1714f28fb5da319c3e83d96f0bedf08/Engine/Source/Runtime/CoreUObject/Private/Serialization/AsyncLoading2.cpp#L3190
        std::vector<FImportedPackage> GraphData;
        AssetAr.Seek(Summary.GraphDataOffset, ESeekDir::Beg);
        AssetAr >> GraphData;

        // https://github.com/EpicGames/UnrealEngine/blob/5df54b7ef1714f28fb5da319c3e83d96f0bedf08/Engine/Source/Runtime/CoreUObject/Private/Serialization/AsyncLoading2.cpp#L3508
        size_t ExportOffset = Summary.GraphDataOffset + Summary.GraphDataSize;
        for (auto& BundleHeader : BundleHeaders) {
            for (int Idx = 0; Idx < BundleHeader.EntryCount; ++Idx) {
                auto& Bundle = BundleEntries[BundleHeader.FirstEntryIndex + Idx];
                auto& Export = ExportMap[Bundle.LocalExportIndex];
                if (Bundle.CommandType == EExportCommandType::Serialize) {
                    //auto& ExportObject = Ret->Exports[Bundle.LocalExportIndex];

                    auto& ObjectName = NameMap[Export.ObjectName.Index];

                    std::string ClassName;

                    // https://github.com/FabianFG/CUE4Parse/blob/9567177dbc2a05a5bc2edbe864896117ff6fdbf6/CUE4Parse/UE4/Assets/IoPackage.cs#L252
                    auto Type = Export.ClassIndex.GetType();
                    if (Export.ClassIndex.IsExport()) {
                        ClassName = GlobalData.GetName(GlobalData.GetEntry(Export.ClassIndex).ObjectName);
                    }
                    else if (Export.ClassIndex.IsScriptImport()) {
                        ClassName = GlobalData.GetName(GlobalData.GetEntry(Export.ClassIndex).ObjectName);
                    }
                    else {
                        ClassName = "None";
                    }

                    //bool Unversioned = ((uint32_t)Summary.PackageFlags & (uint32_t)EPackageFlags::PKG_UnversionedProperties) != 0;
                    AssetAr.Seek(ExportOffset, ESeekDir::Beg);
                    Ret->Exports[Bundle.LocalExportIndex] = UObject::SerializeUnversioned(AssetAr, ClassName, Vfs);
                    // TODO: https://github.com/FabianFG/CUE4Parse/blob/08d4b68f379aedc7a87934107fab43ece94f3fa9/CUE4Parse/UE4/Assets/Exports/UObject.cs#L77
                    //printf("%s %s %zu %zu\n", ObjectName.c_str(), ClassName.c_str(), ExportOffset, Export.CookedSerialOffset);
                    ExportOffset += Export.CookedSerialSize;
                }
            }
        }

        return Ret;
    }
}