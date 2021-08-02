#include "EPixelFormat.h"

#include "../../Crc32.h"

namespace upp::Objects {
    EPixelFormat GetPixelFormat(const std::string& Format)
    {
        switch (Crc32(Format))
        {
#define CASE(Name) case Crc32(#Name): return EPixelFormat::##Name

            CASE(PF_Unknown);
            CASE(PF_A32B32G32R32F);
            CASE(PF_B8G8R8A8);
            CASE(PF_G8);
            CASE(PF_G16);
            CASE(PF_DXT1);
            CASE(PF_DXT3);
            CASE(PF_DXT5);
            CASE(PF_UYVY);
            CASE(PF_FloatRGB);
            CASE(PF_FloatRGBA);
            CASE(PF_DepthStencil);
            CASE(PF_ShadowDepth);
            CASE(PF_R32_FLOAT);
            CASE(PF_G16R16);
            CASE(PF_G16R16F);
            CASE(PF_G16R16F_FILTER);
            CASE(PF_G32R32F);
            CASE(PF_A2B10G10R10);
            CASE(PF_A16B16G16R16);
            CASE(PF_D24);
            CASE(PF_R16F);
            CASE(PF_R16F_FILTER);
            CASE(PF_BC5);
            CASE(PF_V8U8);
            CASE(PF_A1);
            CASE(PF_FloatR11G11B10);
            CASE(PF_A8);
            CASE(PF_R32_UINT);
            CASE(PF_R32_SINT);
            CASE(PF_PVRTC2);
            CASE(PF_PVRTC4);
            CASE(PF_R16_UINT);
            CASE(PF_R16_SINT);
            CASE(PF_R16G16B16A16_UINT);
            CASE(PF_R16G16B16A16_SINT);
            CASE(PF_R5G6B5_UNORM);
            CASE(PF_R8G8B8A8);
            CASE(PF_A8R8G8B8);
            CASE(PF_BC4);
            CASE(PF_R8G8);
            CASE(PF_ATC_RGB);
            CASE(PF_ATC_RGBA_E);
            CASE(PF_ATC_RGBA_I);
            CASE(PF_X24_G8);
            CASE(PF_ETC1);
            CASE(PF_ETC2_RGB);
            CASE(PF_ETC2_RGBA);
            CASE(PF_R32G32B32A32_UINT);
            CASE(PF_R16G16_UINT);
            CASE(PF_ASTC_4x4);
            CASE(PF_ASTC_6x6);
            CASE(PF_ASTC_8x8);
            CASE(PF_ASTC_10x10);
            CASE(PF_ASTC_12x12);
            CASE(PF_BC6H);
            CASE(PF_BC7);
            CASE(PF_R8_UINT);
            CASE(PF_L8);
            CASE(PF_XGXR8);
            CASE(PF_R8G8B8A8_UINT);
            CASE(PF_R8G8B8A8_SNORM);
            CASE(PF_R16G16B16A16_UNORM);
            CASE(PF_R16G16B16A16_SNORM);
            CASE(PF_PLATFORM_HDR_0);
            CASE(PF_PLATFORM_HDR_1);
            CASE(PF_PLATFORM_HDR_2);
            CASE(PF_NV12);
            CASE(PF_R32G32_UINT);
            CASE(PF_ETC2_R11_EAC);
            CASE(PF_ETC2_RG11_EAC);
            CASE(PF_R8);

#undef CASE
        default:
            return EPixelFormat::PF_Unknown;
        }
    }
}