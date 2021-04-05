#include "../lib/UE4/Pak/FileReader.h"
#include "../lib/UE4/Readers/FFileArchive.h"

int main() {
    upp::UE4::Readers::FFileArchive Ar(R"(D:\FortniteGame\Content\Paks\pakchunk0-WindowsClient.pak)");
    upp::UE4::Pak::FileReader Reader(Ar);
    printf("%d\n", Ar.GetError());
}