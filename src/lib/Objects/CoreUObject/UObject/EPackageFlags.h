#pragma once

#include <stdint.h>

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/94d91f5af6206c563300b2279227161bcb1b7ddf/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h#L103
    enum class EPackageFlags : uint32_t {
        PKG_None                          = 0x00000000,
        PKG_NewlyCreated                  = 0x00000001,
        PKG_ClientOptional                = 0x00000002,
        PKG_ServerSideOnly                = 0x00000004,
        PKG_CompiledIn                    = 0x00000010,
        PKG_ForDiffing                    = 0x00000020,
        PKG_EditorOnly                    = 0x00000040,
        PKG_Developer                     = 0x00000080,
        PKG_UncookedOnly                  = 0x00000100,
        PKG_UnversionedProperties         = 0x00002000,
        PKG_ContainsMapData               = 0x00004000,
        PKG_Compiling                     = 0x00010000,
        PKG_ContainsMap                   = 0x00020000,
        PKG_RequiresLocalizationGather    = 0x00040000,
        PKG_PlayInEditor                  = 0x00100000,
        PKG_ContainsScript                = 0x00200000,
        PKG_DisallowExport                = 0x00400000,
        PKG_DynamicImports                = 0x10000000,
        PKG_RuntimeGenerated              = 0x20000000,
        PKG_ReloadingForCooker            = 0x40000000,
        PKG_FilterEditorOnly              = 0x80000000,
    };
}