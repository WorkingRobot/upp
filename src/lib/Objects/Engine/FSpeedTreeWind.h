#pragma once

#include "../Core/Serialization/FArchive.h"

namespace upp::Objects {
    struct FSpeedTreeWind {
        static constexpr int NUM_WIND_POINTS_IN_CURVE = 10;
        static constexpr int NUM_BRANCH_LEVELS = 2;
        static constexpr int NUM_LEAF_GROUPS = 2;
        static constexpr int NUM_OSC_COMPONENTS = 10;
        static constexpr int NUM_WIND_OPTIONS = 28;

        struct SBranchWindLevel {
            float		m_afDistance[NUM_WIND_POINTS_IN_CURVE];
            float		m_afDirectionAdherence[NUM_WIND_POINTS_IN_CURVE];
            float		m_afWhip[NUM_WIND_POINTS_IN_CURVE];
            float		m_fTurbulence;
            float		m_fTwitch;
            float		m_fTwitchFreqScale;
        };

        struct SWindGroup {
            float		m_afRippleDistance[NUM_WIND_POINTS_IN_CURVE];
            float		m_afTumbleFlip[NUM_WIND_POINTS_IN_CURVE];
            float		m_afTumbleTwist[NUM_WIND_POINTS_IN_CURVE];
            float		m_afTumbleDirectionAdherence[NUM_WIND_POINTS_IN_CURVE];
            float		m_afTwitchThrow[NUM_WIND_POINTS_IN_CURVE];
            float		m_fTwitchSharpness;
            float		m_fRollMaxScale;
            float		m_fRollMinScale;
            float		m_fRollSpeed;
            float		m_fRollSeparation;
            float		m_fLeewardScalar;
        };

        struct SParams {
            // settings
            float				m_fStrengthResponse;
            float				m_fDirectionResponse;

            float				m_fAnchorOffset;
            float				m_fAnchorDistanceScale;

            // oscillation components
            float				m_afFrequencies[NUM_OSC_COMPONENTS][NUM_WIND_POINTS_IN_CURVE];

            // global motion
            float				m_fGlobalHeight;
            float				m_fGlobalHeightExponent;
            float				m_afGlobalDistance[NUM_WIND_POINTS_IN_CURVE];
            float				m_afGlobalDirectionAdherence[NUM_WIND_POINTS_IN_CURVE];

            // branch motion
            SBranchWindLevel	m_asBranch[NUM_BRANCH_LEVELS];

            // leaf motion
            SWindGroup			m_asLeaf[NUM_LEAF_GROUPS];

            // frond ripple
            float				m_afFrondRippleDistance[NUM_WIND_POINTS_IN_CURVE];
            float				m_fFrondRippleTile;
            float				m_fFrondRippleLightingScalar;

            // rolling
            float				m_fRollingNoiseSize;
            float				m_fRollingNoiseTwist;
            float				m_fRollingNoiseTurbulence;
            float				m_fRollingNoisePeriod;
            float				m_fRollingNoiseSpeed;

            float				m_fRollingBranchFieldMin;
            float				m_fRollingBranchLightingAdjust;
            float				m_fRollingBranchVerticalOffset;
            float				m_fRollingLeafRippleMin;
            float				m_fRollingLeafTumbleMin;

            // gusting
            float				m_fGustFrequency;
            float				m_fGustStrengthMin;
            float				m_fGustStrengthMax;
            float				m_fGustDurationMin;
            float				m_fGustDurationMax;
            float				m_fGustRiseScalar;
            float				m_fGustFallScalar;
        } Params;

        friend FArchive& operator>>(FArchive& Ar, FSpeedTreeWind& Value);
    };
}