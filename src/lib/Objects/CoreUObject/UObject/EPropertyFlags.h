#pragma once

#include <stdint.h>

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/CoreUObject/Public/UObject/ObjectMacros.h#L362
    enum class EPropertyFlags : uint64_t {
        CPF_None = 0,

        CPF_Edit = 0x0000000000000001,	///< Property is user-settable in the editor.
        CPF_ConstParm = 0x0000000000000002,	///< This is a constant function parameter
        CPF_BlueprintVisible = 0x0000000000000004,	///< This property can be read by blueprint code
        CPF_ExportObject = 0x0000000000000008,	///< Object can be exported with actor.
        CPF_BlueprintReadOnly = 0x0000000000000010,	///< This property cannot be modified by blueprint code
        CPF_Net = 0x0000000000000020,	///< Property is relevant to network replication.
        CPF_EditFixedSize = 0x0000000000000040,	///< Indicates that elements of an array can be modified, but its size cannot be changed.
        CPF_Parm = 0x0000000000000080,	///< Function/When call parameter.
        CPF_OutParm = 0x0000000000000100,	///< Value is copied out after function call.
        CPF_ZeroConstructor = 0x0000000000000200,	///< memset is fine for construction
        CPF_ReturnParm = 0x0000000000000400,	///< Return value.
        CPF_DisableEditOnTemplate = 0x0000000000000800,	///< Disable editing of this property on an archetype/sub-blueprint
        //CPF_      						= 0x0000000000001000,	///< 
        CPF_Transient = 0x0000000000002000,	///< Property is transient: shouldn't be saved or loaded, except for Blueprint CDOs.
        CPF_Config = 0x0000000000004000,	///< Property should be loaded/saved as permanent profile.
        //CPF_								= 0x0000000000008000,	///< 
        CPF_DisableEditOnInstance = 0x0000000000010000,	///< Disable editing on an instance of this class
        CPF_EditConst = 0x0000000000020000,	///< Property is uneditable in the editor.
        CPF_GlobalConfig = 0x0000000000040000,	///< Load config from base class, not subclass.
        CPF_InstancedReference = 0x0000000000080000,	///< Property is a component references.
        //CPF_								= 0x0000000000100000,	///<
        CPF_DuplicateTransient = 0x0000000000200000,	///< Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.)
        //CPF_								= 0x0000000000400000,	///< 
        //CPF_    							= 0x0000000000800000,	///< 
        CPF_SaveGame = 0x0000000001000000,	///< Property should be serialized for save games, this is only checked for game-specific archives with ArIsSaveGame
        CPF_NoClear = 0x0000000002000000,	///< Hide clear (and browse) button.
        //CPF_  							= 0x0000000004000000,	///<
        CPF_ReferenceParm = 0x0000000008000000,	///< Value is passed by reference; CPF_OutParam and CPF_Param should also be set.
        CPF_BlueprintAssignable = 0x0000000010000000,	///< MC Delegates only.  Property should be exposed for assigning in blueprint code
        CPF_Deprecated = 0x0000000020000000,	///< Property is deprecated.  Read it from an archive, but don't save it.
        CPF_IsPlainOldData = 0x0000000040000000,	///< If this is set, then the property can be memcopied instead of CopyCompleteValue / CopySingleValue
        CPF_RepSkip = 0x0000000080000000,	///< Not replicated. For non replicated properties in replicated structs 
        CPF_RepNotify = 0x0000000100000000,	///< Notify actors when a property is replicated
        CPF_Interp = 0x0000000200000000,	///< interpolatable property for use with matinee
        CPF_NonTransactional = 0x0000000400000000,	///< Property isn't transacted
        CPF_EditorOnly = 0x0000000800000000,	///< Property should only be loaded in the editor
        CPF_NoDestructor = 0x0000001000000000,	///< No destructor
        //CPF_								= 0x0000002000000000,	///<
        CPF_AutoWeak = 0x0000004000000000,	///< Only used for weak pointers, means the export type is autoweak
        CPF_ContainsInstancedReference = 0x0000008000000000,	///< Property contains component references.
        CPF_AssetRegistrySearchable = 0x0000010000000000,	///< asset instances will add properties with this flag to the asset registry automatically
        CPF_SimpleDisplay = 0x0000020000000000,	///< The property is visible by default in the editor details view
        CPF_AdvancedDisplay = 0x0000040000000000,	///< The property is advanced and not visible by default in the editor details view
        CPF_Protected = 0x0000080000000000,	///< property is protected from the perspective of script
        CPF_BlueprintCallable = 0x0000100000000000,	///< MC Delegates only.  Property should be exposed for calling in blueprint code
        CPF_BlueprintAuthorityOnly = 0x0000200000000000,	///< MC Delegates only.  This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.
        CPF_TextExportTransient = 0x0000400000000000,	///< Property shouldn't be exported to text format (e.g. copy/paste)
        CPF_NonPIEDuplicateTransient = 0x0000800000000000,	///< Property should only be copied in PIE
        CPF_ExposeOnSpawn = 0x0001000000000000,	///< Property is exposed on spawn
        CPF_PersistentInstance = 0x0002000000000000,	///< A object referenced by the property is duplicated like a component. (Each actor should have an own instance.)
        CPF_UObjectWrapper = 0x0004000000000000,	///< Property was parsed as a wrapper class like TSubclassOf<T>, FScriptInterface etc., rather than a USomething*
        CPF_HasGetValueTypeHash = 0x0008000000000000,	///< This property can generate a meaningful hash value.
        CPF_NativeAccessSpecifierPublic = 0x0010000000000000,	///< Public native access specifier
        CPF_NativeAccessSpecifierProtected = 0x0020000000000000,	///< Protected native access specifier
        CPF_NativeAccessSpecifierPrivate = 0x0040000000000000,	///< Private native access specifier
        CPF_SkipSerialization = 0x0080000000000000,	///< Property shouldn't be serialized, can still be exported to text
    };
}