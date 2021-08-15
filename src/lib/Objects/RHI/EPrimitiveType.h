#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EPrimitiveType : uint32_t {
        // Topology that defines a triangle N with 3 vertex extremities: 3*N+0, 3*N+1, 3*N+2.
        PT_TriangleList,

        // Topology that defines a triangle N with 3 vertex extremities: N+0, N+1, N+2.
        PT_TriangleStrip,

        // Topology that defines a line with 2 vertex extremities: 2*N+0, 2*N+1.
        PT_LineList,

        // Topology that defines a quad N with 4 vertex extremities: 4*N+0, 4*N+1, 4*N+2, 4*N+3.
        // Supported only if GRHISupportsQuadTopology == true.
        PT_QuadList,

        // Topology that defines a point N with a single vertex N.
        PT_PointList,

        // Topology that defines a screen aligned rectangle N with only 3 vertex corners:
        //    3*N + 0 is upper-left corner,
        //    3*N + 1 is upper-right corner,
        //    3*N + 2 is the lower-left corner.
        // Supported only if GRHISupportsRectTopology == true.
        PT_RectList,

        // Tesselation patch list. Supported only if tesselation is supported.
        PT_1_ControlPointPatchList,
        PT_2_ControlPointPatchList,
        PT_3_ControlPointPatchList,
        PT_4_ControlPointPatchList,
        PT_5_ControlPointPatchList,
        PT_6_ControlPointPatchList,
        PT_7_ControlPointPatchList,
        PT_8_ControlPointPatchList,
        PT_9_ControlPointPatchList,
        PT_10_ControlPointPatchList,
        PT_11_ControlPointPatchList,
        PT_12_ControlPointPatchList,
        PT_13_ControlPointPatchList,
        PT_14_ControlPointPatchList,
        PT_15_ControlPointPatchList,
        PT_16_ControlPointPatchList,
        PT_17_ControlPointPatchList,
        PT_18_ControlPointPatchList,
        PT_19_ControlPointPatchList,
        PT_20_ControlPointPatchList,
        PT_21_ControlPointPatchList,
        PT_22_ControlPointPatchList,
        PT_23_ControlPointPatchList,
        PT_24_ControlPointPatchList,
        PT_25_ControlPointPatchList,
        PT_26_ControlPointPatchList,
        PT_27_ControlPointPatchList,
        PT_28_ControlPointPatchList,
        PT_29_ControlPointPatchList,
        PT_30_ControlPointPatchList,
        PT_31_ControlPointPatchList,
        PT_32_ControlPointPatchList,
        PT_Num,
        PT_NumBits = 6
    };
    static_assert((uint32_t)EPrimitiveType::PT_Num <= (1 << 8), "EPrimitiveType doesn't fit in a byte");
    static_assert((uint32_t)EPrimitiveType::PT_Num <= (1 << (uint32_t)EPrimitiveType::PT_NumBits), "PT_NumBits is too small");
}