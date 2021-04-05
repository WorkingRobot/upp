#pragma once

#include "UE4Version.h"

namespace upp::Versions {
    namespace Detail {
        // 01 => UE4
        // 000 => Empty
        // NN => UE4 subversion
        // X => Game
        template<uint8_t Subversion, uint8_t Game = 0>
        constexpr uint32_t GameUE4() {
            static_assert(Game < 16, "Game number must be less than 16");

            return (1 << 24) + (Subversion << 4) + Game;
        }
    }

    enum class EGame : uint32_t {
        UE4_0 = Detail::GameUE4<0>(),
        UE4_1 = Detail::GameUE4<1>(),
        UE4_2 = Detail::GameUE4<2>(),
        UE4_3 = Detail::GameUE4<3>(),
        UE4_4 = Detail::GameUE4<4>(),
        UE4_5 = Detail::GameUE4<5>(),
        UE4_6 = Detail::GameUE4<6>(),
        UE4_7 = Detail::GameUE4<7>(),
        UE4_8 = Detail::GameUE4<8>(),
        UE4_9 = Detail::GameUE4<9>(),
        UE4_10 = Detail::GameUE4<10>(),
        UE4_11 = Detail::GameUE4<11>(),
        UE4_12 = Detail::GameUE4<12>(),
        UE4_13 = Detail::GameUE4<13>(),
        UE4_14 = Detail::GameUE4<14>(),
        UE4_15 = Detail::GameUE4<15>(),
        UE4_16 = Detail::GameUE4<16>(),
        UE4_17 = Detail::GameUE4<17>(),
        UE4_18 = Detail::GameUE4<18>(),
        UE4_19 = Detail::GameUE4<19>(),
        UE4_20 = Detail::GameUE4<20>(),
        UE4_21 = Detail::GameUE4<21>(),
        UE4_22 = Detail::GameUE4<22>(),
        UE4_23 = Detail::GameUE4<23>(),
        UE4_24 = Detail::GameUE4<24>(),
        UE4_25 = Detail::GameUE4<25>(),
        UE4_26 = Detail::GameUE4<26>(),
        UE4_27 = Detail::GameUE4<27>(),

        UE4_Last,
        UE4_Latest = UE4_Last - 1,

        Borderlands3 = Detail::GameUE4<20, 1>(),
        Valorant = Detail::GameUE4<24, 1>(),
    };

    namespace Detail {
        constexpr uint8_t GetSubversion(EGame Game) {
            return ((uint32_t)Game >> 5) & 0xFF;
        }
    }

    constexpr UE4Version GetVersion(EGame Game) {
        switch (Detail::GetSubversion(Game))
        {
        case 0:
            return UE4Version::PRIVATE_REMOTE_ROLE;
        case 1:
            return UE4Version::UNDO_BREAK_MATERIALATTRIBUTES_CHANGE;
        case 2:
            return UE4Version::FIX_MATERIAL_COORDS;
        case 3:
            return UE4Version::FIX_MATERIAL_PROPERTY_OVERRIDE_SERIALIZE;
        case 4:
            return UE4Version::BLUEPRINT_USE_SCS_ROOTCOMPONENT_SCALE;
        case 5:
            return UE4Version::RENAME_CAMERA_COMPONENT_CONTROL_ROTATION;
        case 6:
            return UE4Version::MOVEMENTCOMPONENT_AXIS_SETTINGS;
        case 7:
            return UE4Version::AFTER_MERGING_ADD_MODIFIERS_RUNTIME_GENERATION_TO_4_7;
        case 8:
            return UE4Version::SERIALIZE_BLUEPRINT_EVENTGRAPH_FASTCALLS_IN_UFUNCTION;
        case 9:
            return UE4Version::APEX_CLOTH_TESSELLATION;
        case 10:
            return UE4Version::APEX_CLOTH_TESSELLATION;
        case 11:
            return UE4Version::STREAMABLE_TEXTURE_MIN_MAX_DISTANCE;
        case 12:
            return UE4Version::NAME_HASHES_SERIALIZED;
        case 13:
            return UE4Version::INSTANCED_STEREO_UNIFORM_REFACTOR;
        case 14:
            return UE4Version::TemplateIndex_IN_COOKED_EXPORTS;
        case 15:
            return UE4Version::ADDED_SEARCHABLE_NAMES;
        case 16:
            return UE4Version::ADDED_SWEEP_WHILE_WALKING_FLAG;
        case 17:
            return UE4Version::ADDED_SWEEP_WHILE_WALKING_FLAG;
        case 18:
            return UE4Version::ADDED_SOFT_OBJECT_PATH;
        case 19:
            return UE4Version::ADDED_PACKAGE_SUMMARY_LOCALIZATION_ID;
        case 20:
            return UE4Version::ADDED_PACKAGE_SUMMARY_LOCALIZATION_ID;
        case 21:
            return UE4Version::FIX_WIDE_STRING_CRC;
        case 22:
            return UE4Version::FIX_WIDE_STRING_CRC;
        case 23:
            return UE4Version::FIX_WIDE_STRING_CRC;
        case 24:
            return UE4Version::ADDED_PACKAGE_OWNER;
        case 25:
            return UE4Version::ADDED_PACKAGE_OWNER;
        case 26:
            return UE4Version::CORRECT_LICENSEE_FLAG;
        default:
            return UE4Version::Latest;
        }
    }
}