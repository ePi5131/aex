#pragma once

#include <aex/aexint.hpp>
#include <aex/effect_type.hpp>
#include <aex/flag.hpp>

namespace aex {

enum class PF_OutFlags : A_long{
    None = 0,
    KeepResourceOpen            = 1 <<  0,
    WideTimeInput               = 1 <<  1,
    NonParamVary                = 1 <<  2,
    Reserved6                   = 1 <<  3,
    SequenceDataNeedsFlattening = 1 <<  4,
    IDoDialog                   = 1 <<  5,
    UseOutputExtent             = 1 <<  6,
    SendDoDialog                = 1 <<  7,
    DisplayErrorMessage         = 1 <<  8,
    IExpandBuffer               = 1 <<  9,
    PixIndepandent              = 1 << 10,
    IWriteInputBuffer           = 1 << 11,
    IShrinkBuffer               = 1 << 12,
    WorksInPlace                = 1 << 13,
    Reserved8                   = 1 << 14,
    CustomUI                    = 1 << 15,
    Reserved7                   = 1 << 16,
    RefreshUI                   = 1 << 17,
    NopRender                   = 1 << 18,
    IUseShutterAngle            = 1 << 19,
    IUseAudio                   = 1 << 20,
    IAmObsolete                 = 1 << 21,
    ForceRerender               = 1 << 22,
    PiPLOverridesOutdataOutflags= 1 << 23,
    IHaveExternalDepandecies    = 1 << 24,
    DeepColorAware              = 1 << 25,
    SendUpdateParamsUI          = 1 << 26,
    AudioFloatOnly              = 1 << 27,
    AudioIIR                    = 1 << 28,
    ISynthesizeAudio            = 1 << 29,
    AudioEffectToo              = 1 << 30,
    AudioEffectOnly             = 1 << 31,
};
template<>struct detail::flag::ops_def<PF_OutFlags>{};

enum class PF_OutFlags2 : A_long {
    None = 0,
    SupportsQueryDynamicFlags          = 1 <<  0,
    IUse3DCamera                       = 1 <<  1,
    IUse3DLights                       = 1 <<  2,
    ParamGroupStartCollapsedFlag       = 1 <<  3,
    IAmThreadsafe                      = 1 <<  4,
    CanCombineWithDestination          = 1 <<  5,
    DoesntNeedEmptyPixels              = 1 <<  6,
    RevealsZeroAlpha                   = 1 <<  7,
    PreservesFullyOpaquePixels         = 1 <<  8,
    
    SupportsSmartRender                = 1 << 10,
    Reserved9                          = 1 << 11,
    FloatColorAware                    = 1 << 12,
    IUseColorspaceEnumeration          = 1 << 13,
    IAmDeprecated                      = 1 << 14,
    PProDoNotColorSequenceDataForRender= 1 << 15,
    Reserved10                         = 1 << 16,
    AutomaticWideTimeInput             = 1 << 17,
    IUseTimecode                       = 1 << 18,
    DependsOnUnrefferencedMasks        = 1 << 19,
    OutputIsWatermarked                = 1 << 20,
    IMixGUIDDepandecies                = 1 << 21,
    AE13_5_Threadsafe                  = 1 << 22,
    SupportsGetFlattenedSequenceData   = 1 << 23,
    CustomUIAsyncManager               = 1 << 24,
    SupportsGPURenderF32               = 1 << 25,
    Reserved12                         = 1 << 26,
};
template<>struct detail::flag::ops_def<PF_OutFlags2>{};

struct PF_OutData {
    static inline constexpr size_t PF_MAX_EFFECT_NAME_LEN = 31;
    static inline constexpr size_t PF_MAX_EFFECT_MSG_LEN = 31;
    A_u_long my_version;
    A_char name[PF_MAX_EFFECT_NAME_LEN + 1];
    PF_Handle global_data;
    A_long num_params;
    PF_Handle sequence_data;
    A_long flat_sdata_size;
    PF_Handle frame_data;
    A_long width, height;
    PF_Point origin;
    PF_OutFlags out_flags;
    A_char return_msg[PF_MAX_EFFECT_MSG_LEN + 1];
    A_long start_sampL;
    A_long dur_sampL;
    PF_SoundWorld dest_snd;
    PF_OutFlags2 out_flags2;
};

}
