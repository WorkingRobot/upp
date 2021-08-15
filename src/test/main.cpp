#include "../lib/Objects/Core/Serialization/FFileArchive.h"
#include "../lib/Objects/RHI/FPipelineFileCache.h"
#include "../lib/Providers/UsmapProvider.h"
#include "../lib/Readers/IoReader.h"
#include "../lib/Readers/PakReader.h"
#include "../lib/Vfs/Vfs.h"
#include "../lib/Vfs/DirectoryIterator.h"

#include <future>

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
        static upp::Objects::FAESSchedule KeyInvalid{};
        static upp::Objects::FGuid GuidMain = GuidFromHex("00000000000000000000000000000000");
        static upp::Objects::FAESSchedule KeyMain = KeyFromHex("7DD830C5ACC92FE26653003ABECA10606F3492026A2C971283B2FA6B42DE8422");
        static upp::Objects::FGuid Guid1005 = GuidFromHex("58388BA7BD1643A85EFD49BF26EF5912");
        static upp::Objects::FAESSchedule Key1005 = KeyFromHex("02BBB7DBB2491EC18A083D989504FE123CBADFFFEF972F4285374AB1F80BEF9A");
        if (Guid == GuidMain) {
            return KeyMain;
        }
        if (Guid == Guid1005) {
            return Key1005;
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

void Bench(upp::Vfs::Vfs& Vfs, const char* Path) {
    auto Start = std::chrono::steady_clock::now();
    auto Pkg = Vfs.GetAsset<upp::Objects::FPipelineFileCache>(Path);
    auto End = std::chrono::steady_clock::now();
    printf("%.02f ms\n", (End - Start).count() / 1000000.);
}

int main() {
    upp::Vfs::Vfs Vfs;
    upp::Readers::Error Error;
    KeyChainImpl KeyChain;

    upp::Objects::FFileArchive UsmapAr(R"(J:\misc cold storage\++Fortnite+Release-17.30-CL-17004569-Windows_oo.usmap)");
    Vfs.SetProvider<upp::Providers::UsmapProvider>(UsmapAr);

    std::error_code Code;
    std::deque<upp::Objects::FFileArchive> Archives;
    {
        auto Start = std::chrono::steady_clock::now();
        for (auto& File : std::filesystem::directory_iterator(R"(D:\FortniteGame\Content\Paks\)", Code)) {
            if (File.path().extension() == ".ucas") {
                auto TocPath = File.path();
                TocPath.replace_extension(".utoc");
                if (!std::filesystem::exists(TocPath, Code)) {
                    continue;
                }

                upp::Objects::FFileArchive TocAr(TocPath);
                auto& Ar = Archives.emplace_back(File);
                auto Reader = Vfs.AddReaderIfValid<upp::Readers::IoReader>(Error, Ar, TocAr, KeyChain);
                if (!Reader && Error != upp::Readers::Error::InvalidAesKey) {
                    printf("%s\n", File.path().filename().string().c_str());
                    printf("Error: %d\n", Error);
                }
            }
            else if (File.path().extension() == ".pak") {
                auto& Ar = Archives.emplace_back(File);
                auto Reader = Vfs.AddReaderIfValid<upp::Readers::PakReader>(Error, Ar, KeyChain);
                if (!Reader && Error != upp::Readers::Error::InvalidAesKey) {
                    printf("%s\n", File.path().filename().string().c_str());
                    printf("Error: %d\n", Error);
                }
            }
        }
        auto End = std::chrono::steady_clock::now();
        printf("%.02f ms\n", (End - Start).count() / 1000000.);
    }
    Bench(Vfs, "/FortniteGame/Content/PipelineCaches/Windows/FortniteGame_PCD3D_ES31.stable.upipelinecache");
    Bench(Vfs, "/FortniteGame/Content/PipelineCaches/Windows/FortniteGame_PCD3D_SM5.stable.upipelinecache");
}