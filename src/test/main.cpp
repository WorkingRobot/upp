#include "../lib/Objects/Core/Serialization/FFileArchive.h"
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
        static upp::Objects::FAESSchedule Key = KeyFromHex("1522C5C59FD8B9964F10B23DD55BB0255F51D8ABEF1CE7B6BBBBE3239AE18929");
        static upp::Objects::FGuid Guid1000 = GuidFromHex("08788A9DA34F4164ADA4F09FBF698CC3");
        static upp::Objects::FAESSchedule Key1000 = KeyFromHex("0E5851ADD0460CD0035003118F8A00530C11DA3DF736BD99360D825378B5FCF8");
        if (Guid == Guid1000) {
            return Key1000;
        }
        return Key;
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
    upp::Objects::FFileArchive TocAr(R"(D:\FortniteGame\Content\Paks\pakchunk0-WindowsClient.utoc)");
    upp::Objects::FFileArchive Ar(R"(D:\FortniteGame\Content\Paks\pakchunk0-WindowsClient.ucas)");
    upp::Objects::FFileArchive TocAr1000(R"(D:\FortniteGame\Content\Paks\pakchunk1000-WindowsClient.utoc)");
    upp::Objects::FFileArchive Ar1000(R"(D:\FortniteGame\Content\Paks\pakchunk1000-WindowsClient.ucas)");
    upp::Vfs::Vfs Vfs;
    upp::Readers::Error Error;
    KeyChainImpl KeyChain;
    {
        auto Reader = Vfs.AddReaderIfValid<upp::Readers::IoReader>(Error, Ar, TocAr, KeyChain);
        if (!Reader) {
            printf("Error: %d\n", Error);
            return 0;
        }
    }
    {
        auto Reader = Vfs.AddReaderIfValid<upp::Readers::IoReader>(Error, Ar1000, TocAr1000, KeyChain);
        if (!Reader) {
            printf("Error 1000: %d\n", Error);
            return 0;
        }
    }
    
    // Iterate("", Vfs.GetRootDirectory()); return 0;

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