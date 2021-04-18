#include "../lib/Objects/Core/Serialization/FFileArchive.h"
#include "../lib/Readers/PakReader.h"
#include "../lib/Vfs/Vfs.h"
#include "../lib/Vfs/DirectoryIterator.h"

class KeyChainImpl : public upp::IKeyChain {
    static upp::Objects::FAESKey FromHex(const char Hex[64]) {
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
        static upp::Objects::FAESSchedule Key = FromHex("AB32BAB083F7D923A33AA768BC64B64BF62488948BD49FE61D95343492252558");
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
    upp::Objects::FFileArchive Ar(R"(J:\Code\Visual Studio 2017\Projects\FortniteDownloader\DownloaderApp2\bin\Debug\netcoreapp3.1\FortniteGame\Content\Paks\pakchunk0-WindowsClient.pak)");
    upp::Vfs::Vfs Vfs;
    upp::Readers::Error Error;
    KeyChainImpl KeyChain;
    auto Reader = Vfs.AddReaderIfValid<upp::Readers::PakReader>(Error, Ar, KeyChain);
    if (!Reader) {
        printf("Error: %d\n", Error);
        return 0;
    }
    
    // Iterate("", Vfs.GetRootDirectory()); return 0;

    for (auto& Entry : upp::Vfs::RecursiveDirectoryIterator(Vfs.GetRootDirectory())) {
        if (!Entry.IsFile()) {
            continue;
        }

        auto ArPtr = Vfs.GetFile(*Entry.GetFile());
        if (ArPtr) {
            auto f = fopen((std::to_string(Entry.GetFile()->GetFileIdx()) + ".f").c_str(), "wb");
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