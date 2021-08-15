#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EShaderPlatform : uint8_t {
        SP_PCD3D_SM5 = 0,
        SP_OPENGL_SM4_REMOVED = 1,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_PS4 = 2,
        SP_OPENGL_PCES2_REMOVED = 3,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_XBOXONE_D3D12 = 4,
        SP_PCD3D_SM4_REMOVED = 5,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_OPENGL_SM5_REMOVED = 6,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_PCD3D_ES2_REMOVED = 7,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_OPENGL_ES2_ANDROID_REMOVED = 8,
        SP_OPENGL_ES2_WEBGL_REMOVED = 9,
        SP_OPENGL_ES2_IOS_REMOVED = 10,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_METAL = 11,
        SP_METAL_MRT = 12,
        SP_OPENGL_ES31_EXT_REMOVED = 13,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        /** Used when running in Feature Level ES3_1 in D3D11. */
        SP_PCD3D_ES3_1 = 14,
        /** Used when running in Feature Level ES3_1 in OpenGL. */
        SP_OPENGL_PCES3_1 = 15,
        SP_METAL_SM5 = 16,
        SP_VULKAN_PCES3_1 = 17,
        SP_METAL_SM5_NOTESS = 18,
        SP_VULKAN_SM4_REMOVED = 19,	// SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_VULKAN_SM5 = 20,
        SP_VULKAN_ES3_1_ANDROID = 21,
        SP_METAL_MACES3_1 = 22,
        SP_METAL_MACES2_REMOVED = 23, // SUPPORT FOR THIS FEATURE LEVEL HAS BEEN ENTIRELY REMOVED.
        SP_OPENGL_ES3_1_ANDROID = 24,
        SP_SWITCH = 25,
        SP_SWITCH_FORWARD = 26,
        SP_METAL_MRT_MAC = 27,
        SP_VULKAN_SM5_LUMIN = 28,
        SP_VULKAN_ES3_1_LUMIN = 29,
        SP_METAL_TVOS = 30,
        SP_METAL_MRT_TVOS = 31,
        /**********************************************************************************/
        /* !! Do not add any new platforms here. Add them below SP_StaticPlatform_Last !! */
        /**********************************************************************************/

        //---------------------------------------------------------------------------------
        /** Pre-allocated block of shader platform enum values for platform extensions */
#define DDPI_NUM_STATIC_SHADER_PLATFORMS 16
        SP_StaticPlatform_First = 32,

        // Pull in the extra shader platform definitions from platform extensions.
        // @todo - when we remove EShaderPlatform, fix up the shader platforms defined in UEBuild[Platform].cs files.
#ifdef DDPI_EXTRA_SHADERPLATFORMS
        DDPI_EXTRA_SHADERPLATFORMS
#endif

        SP_StaticPlatform_Last = (SP_StaticPlatform_First + DDPI_NUM_STATIC_SHADER_PLATFORMS - 1),

        //  Add new platforms below this line, starting from (SP_StaticPlatform_Last + 1)
        //---------------------------------------------------------------------------------
        SP_VULKAN_SM5_ANDROID = SP_StaticPlatform_Last + 1,

        SP_NumPlatforms,
        SP_NumBits = 7,
    };
    static_assert((uint8_t)EShaderPlatform::SP_NumPlatforms <= (1 << (uint8_t)EShaderPlatform::SP_NumBits), "SP_NumPlatforms will not fit on SP_NumBits");
}