#include "IoReader.h"

#include "../Objects/Core/IO/FIoArchive.h"
#include "../Objects/CoreUObject/Serialization/FExportBundleEntry.h"
#include "../Objects/CoreUObject/Serialization/FExportBundleHeader.h"
#include "../Objects/CoreUObject/Serialization/FExportMapEntry.h"
#include "../Objects/CoreUObject/Serialization/FPackageSummary.h"
#include "../Vfs/Vfs.h"
#include "../Align.h"
#include "NameMappedArchive.h"

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

    const std::string& GetName(const FMappedName& Name, const Vfs::GlobalData& GlobalData, const UPackage& Package)
    {
        return Name.IsGlobal() ? GlobalData.GetName(Name) : Package.NameMap[Name.GetIndex()];
    }

    std::unique_ptr<UPackage> IoReader::ExportPackage(uint32_t AssetIdx, Vfs::Vfs& Vfs)
    {
        auto& Header = *GetHeader();
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
        if (!AssetArPtr) {
            return nullptr;
        }
        FIoArchive& AssetAr = (FIoArchive&)*AssetArPtr;

        // https://github.com/EpicGames/UnrealEngine/blob/5df54b7ef1714f28fb5da319c3e83d96f0bedf08/Engine/Source/Runtime/CoreUObject/Private/Serialization/AsyncLoading2.cpp#L3415
        FPackageSummary Summary;
        AssetAr >> Summary;
        
        AssetAr.Seek(Summary.NameMapNamesOffset, ESeekDir::Beg);
        Vfs::GlobalData::ReadNameMap(AssetAr, Summary.NameMapHashesSize, Ret->NameMap);

        AssetAr.Seek(Summary.ImportMapOffset, ESeekDir::Beg);
        AssetAr.ReadBuffer(Ret->ImportMap, (Summary.ExportMapOffset - Summary.ImportMapOffset) / sizeof(FPackageObjectIndex));

        AssetAr.Seek(Summary.ExportMapOffset, ESeekDir::Beg);
        AssetAr.ReadBuffer(Ret->ExportMap, Entry.ExportCount);
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

        FSerializeCtx Ctx(Vfs, Id, Ret->ImportMap, Ret->ExportMap);
        NameMappedArchive ExportAr(Ret->NameMap, std::move(AssetAr));

        // https://github.com/EpicGames/UnrealEngine/blob/5df54b7ef1714f28fb5da319c3e83d96f0bedf08/Engine/Source/Runtime/CoreUObject/Private/Serialization/AsyncLoading2.cpp#L3508
        size_t ExportOffset = Summary.GraphDataOffset + Summary.GraphDataSize;
        for (auto& BundleHeader : BundleHeaders) {
            for (int Idx = 0; Idx < BundleHeader.EntryCount; ++Idx) {
                auto& Bundle = BundleEntries[BundleHeader.FirstEntryIndex + Idx];
                auto& Export = Ret->ExportMap[Bundle.LocalExportIndex];
                if (Bundle.CommandType == EExportCommandType::Serialize) {
                    auto& ObjectName = ExportAr.GetName(Export.ObjectName.Index);

                    std::string ClassName;

                    // https://github.com/FabianFG/CUE4Parse/blob/9567177dbc2a05a5bc2edbe864896117ff6fdbf6/CUE4Parse/UE4/Assets/IoPackage.cs#L252
                    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Developer/IoStoreUtilities/Private/IoStoreUtilities.cpp#L1660
                    if (Export.ClassIndex.IsScriptImport()) {
                        ClassName = GlobalData.GetName(GlobalData.GetEntry(Export.ClassIndex).ObjectName);
                    }
                    else if (Export.ClassIndex.IsExport()) {
                        ClassName = GetName(Ret->ExportMap[Export.ClassIndex.GetValue()].ObjectName, GlobalData, *Ret);
                    }
                    else if (Export.ClassIndex.IsPackageImport()) {
                        for (int Idx = 0; Idx < Entry.ImportedPackagesCount; ++Idx) {
                            Vfs::File File;
                            if (Vfs.FindChunk(FIoChunkId(Header.ImportedPackages[Entry.ImportedPackagesIdx + Idx].Id, 0, EIoChunkType::ExportBundleData), File)) {
                                // TODO: Possibly slim this down to allow "minimal" reads to not parse the package data (and only get the maps)
                                auto Pkg = Vfs.GetPackage(File);
                                for (auto& PkgExport : Pkg->ExportMap) {
                                    if (PkgExport.GlobalImportIndex == Export.ClassIndex) {
                                        ClassName = GetName(PkgExport.ObjectName, GlobalData, *Pkg);
                                        break;
                                    }
                                }
                                if (!ClassName.empty()) {
                                    break;
                                }
                            }
                        }
                    }

                    if (ClassName.empty()) {
                        ClassName = "None";
                    }

                    ExportAr.Seek(ExportOffset, ESeekDir::Beg);
                    Ret->Exports[Bundle.LocalExportIndex] = UObject::SerializeUnversioned(ExportAr, ClassName, Ctx, (uint32_t)Export.ObjectFlags & (uint32_t)EObjectFlags::RF_ClassDefaultObject);
#ifdef _DEBUG
                    if (ExportAr.Tell() != ExportOffset + Export.CookedSerialSize) {
                        printf("%s - %lld bytes left\n", ClassName.c_str(), (ExportOffset + Export.CookedSerialSize) - ExportAr.Tell());
                    }
#endif
                    ExportOffset += Export.CookedSerialSize;
                }
            }
        }

        return Ret;
    }
}