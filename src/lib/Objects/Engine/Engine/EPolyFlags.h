#pragma once

#include <stdint.h>

namespace upp::Objects {
    enum class EPolyFlags : uint32_t {
        PF_Invisible = 0x00000001,	// Poly is invisible.
        PF_NotSolid = 0x00000008,	// Poly is not solid, doesn't block.
        PF_Semisolid = 0x00000020,	// Poly is semi-solid = collision solid, Csg nonsolid.
        PF_GeomMarked = 0x00000040,	// Geometry mode sometimes needs to mark polys for processing later.
        PF_TwoSided = 0x00000100,	// Poly is visible from both sides.
        PF_Portal = 0x04000000,	// Portal between iZones.

        // Editor flags.
        PF_Memorized = 0x01000000,	// Editor: Poly is remembered.
        PF_Selected = 0x02000000,	// Editor: Poly is selected.
        PF_HiddenEd = 0x08000000,	// Editor: Poly is hidden in the editor at startup.
        PF_Hovered = 0x10000000,	// Editor: Poly is currently hovered over in editor.

        // Internal.
        PF_EdProcessed = 0x40000000,	// FPoly was already processed in editorBuildFPolys.
        PF_EdCut = 0x80000000,	// FPoly has been split by SplitPolyWithPlane.

        // Combinations of flags.
        PF_NoEdit = PF_Memorized | PF_Selected | PF_Hovered | PF_EdProcessed | PF_EdCut,
        PF_NoImport = PF_NoEdit | PF_Memorized | PF_Selected | PF_Hovered | PF_EdProcessed | PF_EdCut,
        PF_AddLast = PF_Semisolid | PF_NotSolid,
        PF_NoAddToBSP = PF_EdCut | PF_EdProcessed | PF_Selected | PF_Hovered | PF_Memorized,
        PF_ModelComponentMask = 0,

        PF_DefaultFlags = 0,
    };
}