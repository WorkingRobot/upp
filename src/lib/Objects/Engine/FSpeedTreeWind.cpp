#include "FSpeedTreeWind.h"

#include "../Core/Math/FVector.h"

namespace upp::Objects {
    // https://github.com/EpicGames/UnrealEngine/blob/c3caf7b6bf12ae4c8e09b606f10a09776b4d1f38/Engine/Source/Runtime/Engine/Private/SpeedTreeWind.cpp#L748
    FArchive& operator>>(FArchive& Ar, FSpeedTreeWind& Value)
    {
#define SERIALIZE_CURVE(Name) for (int CurveIndex = 0; CurveIndex < FSpeedTreeWind::NUM_WIND_POINTS_IN_CURVE; ++CurveIndex) { Ar >> Value.Params.Name[CurveIndex]; }

		Ar >> Value.Params.m_fStrengthResponse;
		Ar >> Value.Params.m_fDirectionResponse;

		Ar >> Value.Params.m_fAnchorOffset;
		Ar >> Value.Params.m_fAnchorDistanceScale;

		for (int OscIndex = 0; OscIndex < FSpeedTreeWind::NUM_OSC_COMPONENTS; ++OscIndex)
		{
			SERIALIZE_CURVE(m_afFrequencies[OscIndex]);
		}

		Ar >> Value.Params.m_fGlobalHeight;
		Ar >> Value.Params.m_fGlobalHeightExponent;
		SERIALIZE_CURVE(m_afGlobalDistance);
		SERIALIZE_CURVE(m_afGlobalDirectionAdherence);

		for (int BranchIndex = 0; BranchIndex < FSpeedTreeWind::NUM_BRANCH_LEVELS; ++BranchIndex)
		{
			SERIALIZE_CURVE(m_asBranch[BranchIndex].m_afDistance);
			SERIALIZE_CURVE(m_asBranch[BranchIndex].m_afDirectionAdherence);
			SERIALIZE_CURVE(m_asBranch[BranchIndex].m_afWhip);
			Ar >> Value.Params.m_asBranch[BranchIndex].m_fTurbulence;
			Ar >> Value.Params.m_asBranch[BranchIndex].m_fTwitch;
			Ar >> Value.Params.m_asBranch[BranchIndex].m_fTwitchFreqScale;
		}

		for (int LeafIndex = 0; LeafIndex < FSpeedTreeWind::NUM_LEAF_GROUPS; ++LeafIndex)
		{
			SERIALIZE_CURVE(m_asLeaf[LeafIndex].m_afRippleDistance);
			SERIALIZE_CURVE(m_asLeaf[LeafIndex].m_afTumbleFlip);
			SERIALIZE_CURVE(m_asLeaf[LeafIndex].m_afTumbleTwist);
			SERIALIZE_CURVE(m_asLeaf[LeafIndex].m_afTumbleDirectionAdherence);
			SERIALIZE_CURVE(m_asLeaf[LeafIndex].m_afTwitchThrow);
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fTwitchSharpness;
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fRollMaxScale;
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fRollMinScale;
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fRollSpeed;
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fRollSeparation;
			Ar >> Value.Params.m_asLeaf[LeafIndex].m_fLeewardScalar;
		}

		SERIALIZE_CURVE(m_afFrondRippleDistance);
		Ar >> Value.Params.m_fFrondRippleTile;
		Ar >> Value.Params.m_fFrondRippleLightingScalar;

		Ar >> Value.Params.m_fRollingNoiseSize;
		Ar >> Value.Params.m_fRollingNoiseTwist;
		Ar >> Value.Params.m_fRollingNoiseTurbulence;
		Ar >> Value.Params.m_fRollingNoisePeriod;
		Ar >> Value.Params.m_fRollingNoiseSpeed;
		Ar >> Value.Params.m_fRollingBranchFieldMin;
		Ar >> Value.Params.m_fRollingBranchLightingAdjust;
		Ar >> Value.Params.m_fRollingBranchVerticalOffset;
		Ar >> Value.Params.m_fRollingLeafRippleMin;
		Ar >> Value.Params.m_fRollingLeafTumbleMin;

		Ar >> Value.Params.m_fGustFrequency;
		Ar >> Value.Params.m_fGustStrengthMin;
		Ar >> Value.Params.m_fGustStrengthMax;
		Ar >> Value.Params.m_fGustDurationMin;
		Ar >> Value.Params.m_fGustDurationMax;
		Ar >> Value.Params.m_fGustRiseScalar;
		Ar >> Value.Params.m_fGustFallScalar;

#define SERIALIZE_OPTION(Name) { int bOption; Ar >> bOption; }

		SERIALIZE_OPTION(GLOBAL_WIND);
		SERIALIZE_OPTION(GLOBAL_PRESERVE_SHAPE);

		SERIALIZE_OPTION(BRANCH_SIMPLE_1);
		SERIALIZE_OPTION(BRANCH_DIRECTIONAL_1);
		SERIALIZE_OPTION(BRANCH_DIRECTIONAL_FROND_1);
		SERIALIZE_OPTION(BRANCH_TURBULENCE_1);
		SERIALIZE_OPTION(BRANCH_WHIP_1);
		SERIALIZE_OPTION(BRANCH_OSC_COMPLEX_1);

		SERIALIZE_OPTION(BRANCH_SIMPLE_2);
		SERIALIZE_OPTION(BRANCH_DIRECTIONAL_2);
		SERIALIZE_OPTION(BRANCH_DIRECTIONAL_FROND_2);
		SERIALIZE_OPTION(BRANCH_TURBULENCE_2);
		SERIALIZE_OPTION(BRANCH_WHIP_2);
		SERIALIZE_OPTION(BRANCH_OSC_COMPLEX_2);

		SERIALIZE_OPTION(LEAF_RIPPLE_VERTEX_NORMAL_1);
		SERIALIZE_OPTION(LEAF_RIPPLE_COMPUTED_1);
		SERIALIZE_OPTION(LEAF_TUMBLE_1);
		SERIALIZE_OPTION(LEAF_TWITCH_1);
		SERIALIZE_OPTION(LEAF_OCCLUSION_1);

		SERIALIZE_OPTION(LEAF_RIPPLE_VERTEX_NORMAL_2);
		SERIALIZE_OPTION(LEAF_RIPPLE_COMPUTED_2);
		SERIALIZE_OPTION(LEAF_TUMBLE_2);
		SERIALIZE_OPTION(LEAF_TWITCH_2);
		SERIALIZE_OPTION(LEAF_OCCLUSION_2);

		SERIALIZE_OPTION(FROND_RIPPLE_ONE_SIDED);
		SERIALIZE_OPTION(FROND_RIPPLE_TWO_SIDED);
		SERIALIZE_OPTION(FROND_RIPPLE_ADJUST_LIGHTING);

		SERIALIZE_OPTION(ROLLING);

		FVector BranchAnchor;
		float MaxBranchLength;

		Ar >> BranchAnchor;
		Ar >> MaxBranchLength;

#undef SERIALIZE_OPTION
#undef SERIALIZE_CURVE

        return Ar;
    }
}