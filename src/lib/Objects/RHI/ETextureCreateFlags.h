#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class ETextureCreateFlags : uint32_t {
        TexCreate_None = 0,

        // Texture can be used as a render target
        TexCreate_RenderTargetable = 1 << 0,
        // Texture can be used as a resolve target
        TexCreate_ResolveTargetable = 1 << 1,
        // Texture can be used as a depth-stencil target.
        TexCreate_DepthStencilTargetable = 1 << 2,
        // Texture can be used as a shader resource.
        TexCreate_ShaderResource = 1 << 3,
        // Texture is encoded in sRGB gamma space
        TexCreate_SRGB = 1 << 4,
        // Texture data is writable by the CPU
        TexCreate_CPUWritable = 1 << 5,
        // Texture will be created with an un-tiled format
        TexCreate_NoTiling = 1 << 6,
        // Texture will be used for video decode
        TexCreate_VideoDecode = 1 << 7,
        // Texture that may be updated every frame
        TexCreate_Dynamic = 1 << 8,
        // Texture will be used as a render pass attachment that will be read from
        TexCreate_InputAttachmentRead = 1 << 9,
        /** Texture represents a foveation attachment */
        TexCreate_Foveation = 1 << 10,
        // Disable automatic defragmentation if the initial texture memory allocation fails.
        TexCreate_DisableAutoDefrag = 1 << 10,
        // This texture has no GPU or CPU backing. It only exists in tile memory on TBDR GPUs (i.e., mobile).
        TexCreate_Memoryless = 1 << 11,
        // Create the texture with the flag that allows mip generation later, only applicable to D3D11
        TexCreate_GenerateMipCapable = 1 << 12,
        // The texture can be partially allocated in fastvram
        TexCreate_FastVRAMPartialAlloc = 1 << 13,
        // Do not create associated shader resource view, only applicable to D3D11 and D3D12
        TexCreate_DisableSRVCreation = 1 << 14,
        // Do not allow Delta Color Compression (DCC) to be used with this texture
        TexCreate_DisableDCC = 1 << 15,
        // UnorderedAccessView (DX11 only)
        // Warning: Causes additional synchronization between draw calls when using a render target allocated with this flag, use sparingly
        // See: GCNPerformanceTweets.pdf Tip 37
        TexCreate_UAV = 1 << 16,
        // Render target texture that will be displayed on screen (back buffer)
        TexCreate_Presentable = 1 << 17,
        // Texture data is accessible by the CPU
        TexCreate_CPUReadback = 1 << 18,
        // Texture was processed offline (via a texture conversion process for the current platform)
        TexCreate_OfflineProcessed = 1 << 19,
        // Texture needs to go in fast VRAM if available (HINT only)
        TexCreate_FastVRAM = 1 << 20,
        // by default the texture is not showing up in the list - this is to reduce clutter, using the FULL option this can be ignored
        TexCreate_HideInVisualizeTexture = 1 << 21,
        // Texture should be created in virtual memory, with no physical memory allocation made
        // You must make further calls to RHIVirtualTextureSetFirstMipInMemory to allocate physical memory
        // and RHIVirtualTextureSetFirstMipVisible to map the first mip visible to the GPU
        TexCreate_Virtual = 1 << 22,
        // Creates a RenderTargetView for each array slice of the texture
        // Warning: if this was specified when the resource was created, you can't use SV_RenderTargetArrayIndex to route to other slices!
        TexCreate_TargetArraySlicesIndependently = 1 << 23,
        // Texture that may be shared with DX9 or other devices
        TexCreate_Shared = 1 << 24,
        // RenderTarget will not use full-texture fast clear functionality.
        TexCreate_NoFastClear = 1 << 25,
        // Texture is a depth stencil resolve target
        TexCreate_DepthStencilResolveTarget = 1 << 26,
        // Flag used to indicted this texture is a streamable 2D texture, and should be counted towards the texture streaming pool budget.
        TexCreate_Streamable = 1 << 27,
        // Render target will not FinalizeFastClear; Caches and meta data will be flushed, but clearing will be skipped (avoids potentially trashing metadata)
        TexCreate_NoFastClearFinalize = 1 << 28,
        // Hint to the driver that this resource is managed properly by the engine for Alternate-Frame-Rendering in mGPU usage.
        TexCreate_AFRManual = 1 << 29,
        // Workaround for 128^3 volume textures getting bloated 4x due to tiling mode on PS4
        TexCreate_ReduceMemoryWithTilingMode = 1 << 30,
        /** Texture should be allocated from transient memory. */
        TexCreate_Transient = 1u << 31
    };
}