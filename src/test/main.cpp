#include "../lib/Objects/Core/Serialization/FFileArchive.h"
#include "../lib/Providers/UsmapProvider.h"
#include "../lib/Readers/IoReader.h"
#include "../lib/Vfs/Vfs.h"
#include "../lib/Vfs/DirectoryIterator.h"

class KeyChainImpl : public upp::IKeyChain {
    static upp::Objects::FGuid GuidFromHex(const char Hex[32]) {
        upp::Objects::FGuid Ret{};
        char ConvBuf[9]{};
        char* End = nullptr;
        for (uint32_t i = 0; i < 4; ++i) {
            memcpy(ConvBuf, Hex + i * 8, 8);
            ((uint32_t*)&Ret)[i] = strtoul(ConvBuf, &End, 16);
        }
        return Ret;
    }

    static upp::Objects::FAESKey KeyFromHex(const char Hex[64]) {
        upp::Objects::FAESKey Ret{};
        char ConvBuf[3]{};
        char* End = nullptr;
        for (uint32_t i = 0; i < sizeof(Ret.Key); ++i) {
            ConvBuf[0] = Hex[i * 2];
            ConvBuf[1] = Hex[i * 2 + 1];
            Ret.Key.m256i_u8[i] = strtol(ConvBuf, &End, 16);
        }
        return Ret;
    }

    const upp::Objects::FAESSchedule& GetKey(const upp::Objects::FGuid& Guid) const
    {
        // pakchunk9 = c078e51f6ec259767bf61fee58cd3c4c367e487d9dfd9ef1c2d504bbc97360ee
        // pakchunk0 = AB32BAB083F7D923A33AA768BC64B64BF62488948BD49FE61D95343492252558
        static upp::Objects::FAESSchedule KeyInvalid{};
        static upp::Objects::FGuid GuidMain = GuidFromHex("00000000000000000000000000000000");
        static upp::Objects::FAESSchedule KeyMain = KeyFromHex("447BBFD835ADFFF5BE68CFE5D93BF3A27A4641656A8C7F7F5051104F6C73E25E");
        static upp::Objects::FGuid Guid1006 = GuidFromHex("58388BA7BD1643A85EFD49BF26EF5912");
        static upp::Objects::FAESSchedule Key1006 = KeyFromHex("02BBB7DBB2491EC18A083D989504FE123CBADFFFEF972F4285374AB1F80BEF9A");
        if (Guid == GuidMain) {
            return KeyMain;
        }
        if (Guid == Guid1006) {
            return Key1006;
        }
        return KeyInvalid;
    }
};

void Iterate(const std::string& Path, const upp::Vfs::Directory<upp::Vfs::CStringKey<true>>& Dir) {
    for (auto& Itr : upp::Vfs::DirectoryIterator(Dir)) {
        if (Itr.IsDirectory()) {
            Iterate(Path + "/" + Itr.GetName().GetString(), *Itr.GetDirectory());
        }
        else {
            printf("%s/%s %u-%u\n", Path.c_str(), Itr.GetName().GetString(), Itr.GetFile()->GetReaderIdx(), Itr.GetFile()->GetFileIdx());
        }
    }
}

int main() {
    upp::Vfs::Vfs Vfs;
    upp::Readers::Error Error;
    KeyChainImpl KeyChain;

    upp::Objects::FFileArchive UsmapAr(R"(J:\misc cold storage\++Fortnite+Release-17.21-CL-16967001-Windows_oo.usmap)");
    Vfs.SetProvider<upp::Providers::UsmapProvider>(UsmapAr);

    std::error_code Code;
    {
        auto Start = std::chrono::steady_clock::now();
        for (auto& File : std::filesystem::directory_iterator(R"(D:\FortniteGame\Content\Paks\)", Code)) {
            if (File.path().extension() == ".utoc") {
                auto CasPath = File.path();
                CasPath.replace_extension(".ucas");
                if (!std::filesystem::exists(CasPath, Code)) {
                    continue;
                }

                upp::Objects::FFileArchive TocAr(File);
                upp::Objects::FFileArchive Ar(CasPath);
                printf("%s\n", File.path().filename().string().c_str());
                auto Reader = Vfs.AddReaderIfValid<upp::Readers::IoReader>(Error, Ar, TocAr, KeyChain);
                if (!Reader) {
                    printf("Error: %d\n", Error);
                }
            }
            
        }
        auto End = std::chrono::steady_clock::now();
        printf("%.02f ms\n", (End - Start).count() / 1000000.);
    }
    Iterate("", Vfs.GetRootDirectory());

    // /Game/Athena/Items/Cosmetics/Dances/EID_Quantity_39X5D
    // /Game/Catalog/NewDisplayAssets/DAv2_EID_Quantity_39X5D
    //Vfs.GetPackage("/FortniteGame/Content/Packages/Fortress_Sky/SkyDome/Master/S_SkyDome01");
    
    for (int i = 0; i < 5000; ++i) {
        auto Start = std::chrono::steady_clock::now();
        auto Pkg = Vfs.GetPackage("/Game/Weapons/WeaponSkins/Wraps/Textures/BuffCatFan/T_Wrap_BuffCatFan_Decal");
        auto End = std::chrono::steady_clock::now();
        printf("%.02f ms\n", (End - Start).count() / 1000000.);
    }
    return 0;

    Iterate("", Vfs.GetRootDirectory()); 

    for (auto& Entry : upp::Vfs::RecursiveDirectoryIterator(Vfs.GetRootDirectory())) {
        if (!Entry.IsFile()) {
            continue;
        }

        auto ArPtr = Vfs.GetFile(*Entry.GetFile());
        if (ArPtr) {
            auto f = fopen((std::to_string(Entry.GetFile()->GetReaderIdx()) + "-" + std::to_string(Entry.GetFile()->GetFileIdx()) + ".f").c_str(), "wb");
            auto buf = std::make_unique<char[]>(ArPtr->Size());
            ArPtr->Read(buf.get(), ArPtr->Size());
            fwrite(buf.get(), 1, ArPtr->Size(), f);
            fclose(f);
        }
        else {
            printf("Could not open %u\n", Entry.GetFile()->GetFileIdx());
        }
    }
}