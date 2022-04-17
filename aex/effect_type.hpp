#pragma once
#include <Windows.h>
#include <aex/aexint.hpp>
#include <aex/flag.hpp>

#include <aex/pf_exception.hpp>

namespace aex {

    enum class PF_Cmd : A_long {
        About = 0,
        GlobalSetup,
        Unused0,
        GlobalSetDown,
        ParamsSetUp,
        SequenceSetUp,
        SequenceResetUp,
        SequenceFlatten,
        SequenceSetDown,
        DoDialog,
        FrameSetUp,
        Render,
        FrameSetDown,
        UserChangedParam,
        UpdateParamsUI,
        Event,
        GetExternalDepandencies,
        CompletelyGeneral,
        QueryDynamicFlags,
        AudioRender,
        AudioSetUp,
        AudioSetDown,
        AudioArbitraryCallback,
        SmartPreRender,
        SmartRender,
        Reserved1,
        Reserved2,
        Reserved3,
        GetFlattenedSequenceData,
        TranslateParamasToPrefs,
        Reserved4,
        SmartRenderGPU,
        GPUDeviceSetUP,
        GPUDeviceSetDown,
        PF_NumCmds
    };

    using PF_FpLong = A_FpLong;
    using PF_FpShort = A_FpShort;

#if defined(_WINDOWS_) || defined(__ANDROID__)
    using PF_Fixed = A_long;
    using PF_Boolean = A_char;
    using PF_Handle = void**;
    struct PF_LegacyPoint {
        A_short v, h;
    };
    struct PF_LegacyRect {
        A_short top, left, bottom, right;
    };
#else
    using PF_Fixed = Fixed;
    using PF_Boolean = Boolean;
    using PF_Handle = Handle;
#endif

    using PF_UFixed = A_u_long;

    struct PF_Pixel {
        A_u_char alpha, red, green, blue;
    };

    struct PF_Point {
    #ifdef LPOINT_RENAME_COMPONENTS
        A_long x,y;
    #else
        A_long h,v;
    #endif
    };

    namespace detail { struct PF_ProgressInfo{}; }
    using PF_ProgPtr = detail::PF_ProgressInfo*;
    using PF_ParamIndex = A_long;
    using PF_ChangeFlags = A_long;
    using PF_ParamUIFlags = A_long;
    enum class PF_ParamType : A_long {
        Reserved = -1,
        Layer = 0,
        Slider,
        FixSlider,
        Angle,
        Checkbox,
        Color,
        Point,
        Popup,
        Custom,
        NoData,
        FloatSlider,
        ArbitraryData,
        Path,
        GroupStart,
        GroupEnd,
        Button,
        Reserved2,
        Reserved3,
        Point3D    
    };

    enum class PF_ParamFlags : A_long {
        None = 0,
        Reserved       = 1 << 0,
        CannotTimeVary = 1 << 1,
        Interp         = 1 << 2,
        Reserved2      = 1 << 3,
        Reserved3      = 1 << 4,
        CollapseTwirly = 1 << 5,
        SuperVise      = 1 << 6,
        StartCollapsed = CollapseTwirly,
        UseValueForOldProjects       = 1 << 7,
        LayerParamIsTrackmatte       = 1 << 7,
        ExcludeFromHaveInputsChanged = 1 << 8,
        SkipRevealWhenUnhidden       = 1 << 9,
    };
    template<>struct detail::flag::ops_def<PF_ParamFlags>{};

    using PF_ValueDisplayFlags = A_short;
    enum class PF_FSliderFlags : A_u_long {
        None = 0,
        WantPhase = 1 << 0
    };
    template<>struct aex::detail::flag::ops_def<PF_FSliderFlags>:std::true_type{};
    using PF_Quality = A_long;
    using PF_ParamValue = A_long;
    enum class PF_WorldFlags : A_long {
        Deep      = 1 <<  0,
        Writeable = 1 <<  1,
        Reserved0 = 1 << 24,
        Reserved1 = 1 << 25,
        Reserved2 = 1 << 26,
        Reserved3 = 1 << 27,
        Reserved4 = 1 << 28,
        Reserved5 = 1 << 29,
        Reserved6 = 1 << 30,
        Reserved  = 1 << 31,
    };
    template<>struct aex::detail::flag::ops_def<PF_WorldFlags>:std::true_type{};

    namespace detail { struct PF_PixelOpaque; }
    using PF_PixelOpaquePtr = detail::PF_PixelOpaque*;

    #ifdef PF_DEEP_COLOR_AWARE
        using PF_PixelPtr = PF_PixelOpaquePtr*;
    #else
        using PF_PixelPtr = PF_Pixel*;
    #endif
        
    struct PF_LRect {
        A_long left, top, right, bottom;
    };
    using PF_Rect = PF_LRect;
    using PF_UnionableRect = PF_Rect;

    using PF_UnionablePixel = PF_Pixel;

    struct PF_RationalScale {
        A_long num;
        A_u_long den;
    };
    template<class T>
    T operator*(T x, const PF_RationalScale& y) {
        return x * y.num / y.den;
    }

    struct PF_SpecVersion {
        A_short major, minor;
    };

    struct PF_CustomUIInfo{};
    struct PF_LayerAudio{};
    using PF_SndSamplePtr = void*;

    using PF_ArbitraryH = PF_Handle;

    using PF_PathID = A_u_long;

    using PF_InFlags = A_long;

    using PF_SoundChannels = A_short;
    using PF_SoundFormat = A_short;
    using PF_SoundSampleSize = A_short;

    struct PF_SoundFormatInfo {
        PF_FpLong rateF;
        PF_SoundChannels num_channels;
        PF_SoundFormat format;
        PF_SoundSampleSize sample_size;
    };

    struct PF_SoundWorld {
        PF_SoundFormatInfo fi;
        A_long num_samples;
        void* dataP;
    };


    using PF_ModeFlags = A_long;

    enum class PF_SampleEdgeBehav : A_u_long {
        Zero = 0,
        // Repeat = 1,
        // Wrap = 2,
    };

    enum class PF_XferMode : A_long {
        None = -1,
        Copy,
        Behind,
        InFront,
        Dissolve,
        Add,
        Multiply,
        Screen,
        Overlay,
        SoftLight,
        HardLight,
        Darken,
        Lighren,
        Difference,
        Hue,
        Saturation,
        Color,
        Luminosity,
        MultiplyAlpha,
        MultiplyAlphaLuma,
        MultiplyNotAlpha,
        MultiplyNotAlphaLuma,
        AdditivePremul,
        AlphaAdd,
        ColorDodge,
        ColorBurn,
        Exclusion,
        Difference2,
        ColorDodge2,
        ColorBurn2,
        LinearDodge,
        LinearBurn,
        LinearLight,
        VividLight,
        PinLight,
        HardMix,
        LighterColor,
        DarkerColor,
        Subtract,
        Divide,
        Reserved0,
        Reserved1,
        NumModes
    };
    using PF_TransferMode = PF_XferMode;

    enum class PF_KernelFlags : A_u_long {
        _2D = 0,
        _1D = 1 << 0,

        Unnormalized = 0,
        Normalized = 1 << 1,

        Clamp = 0,
        NoClamp = 1 << 2,

        UseLong = 0,
        UseChar = 1 << 3,
        UseFixed = 1 << 4,
        UseUndefined = 1<<4 | 1<<3,

        Horizontal = 0,
        Vertical = 1 << 5,

        TransparentBorders,
        ReplicateBorders = 1 << 6,

        StraightConvolve = 0,
        AlphaWeightConvolve = 1 << 7,
    };
    template<>struct detail::flag::ops_def<PF_KernelFlags>{};

    struct PF_FloatMatrix {
        PF_FpLong mat[3][3];
    };
    struct PF_ANSICallbacks {
        A_FpLong (*atan)(A_FpLong);
        A_FpLong (*atan2)(A_FpLong, A_FpLong);
        A_FpLong (*ceil)(A_FpLong);
        A_FpLong (*cos)(A_FpLong);
        A_FpLong (*exp)(A_FpLong);
        A_FpLong (*fabs)(A_FpLong);
        A_FpLong (*floor)(A_FpLong);
        A_FpLong (*fmod)(A_FpLong, A_FpLong);
        A_FpLong (*hypot)(A_FpLong, A_FpLong);
        A_FpLong (*log)(A_FpLong);
        A_FpLong (*log10)(A_FpLong);
        A_FpLong (*pow)(A_FpLong, A_FpLong);
        A_FpLong (*sin)(A_FpLong);
        A_FpLong (*sqrt)(A_FpLong);
        A_FpLong (*tan)(A_FpLong);
        int (*sprintf)(A_char*, const A_char*, ...);
        A_char* (*strcpy)(A_char*, const A_char* );
        A_FpLong (*asin)(A_FpLong);
        A_FpLong (*acos)(A_FpLong);
        A_long ansi_procs[1];
    };

    using PF_RGB_Pixel = PF_Fixed[3];
    using PF_HLS_Pixel = PF_Fixed[3];
    using PF_YIQ_Pixel = PF_Fixed[3];

    struct PF_ColorCallbacks {
        PF_Err (*RGBtoHLS)(PF_ProgPtr effect_ref, PF_Pixel* rgb, PF_HLS_Pixel hls);
        PF_Err (*HLStoRGB)(PF_ProgPtr effect_ref, PF_HLS_Pixel hls, PF_Pixel* rgb);
        PF_Err (*RGBtoYIQ)(PF_ProgPtr effect_ref, PF_Pixel* rgb, PF_YIQ_Pixel yiq);
        PF_Err (*YIQtoRGB)(PF_ProgPtr effect_ref, PF_YIQ_Pixel yiq, PF_Pixel* rgb);
        PF_Err (*Luminance)(PF_ProgPtr effect_ref, PF_Pixel* rgb, A_long* lum100);
        PF_Err (*Hue)(PF_ProgPtr effect_ref, PF_Pixel* rgb, A_long* hue);
        PF_Err (*Lightness)(PF_ProgPtr effect_ref, PF_Pixel* rgb, A_long* lightness);
        PF_Err (*Saturation)(PF_ProgPtr effect_ref, PF_Pixel* rgb, A_long* saturation);
    };

    struct PF_Pixel16 {
    #ifdef PF_PIXEL16_RENAME_COMPONENTS
        A_u_short alphaSu, redSu, greenSu, blueSu;
    #else
        A_u_short alpha, red, green, blue;
    #endif
    };

    using PF_IteratePixel8Func = PF_Err(*)(void* refconP, A_long xL, A_long yL, PF_Pixel* inP, PF_Pixel* outP);
    using PF_IteratePixel16Func = PF_Err(*)(void* refconP, A_long xL, A_long yL, PF_Pixel16* inP, PF_Pixel16* outP);

    enum class PF_NewWorldFlags : A_long {
        None = 0,
        ClearPixels = 1 << 0,
        DeepPixels  = 1 << 1,
        Reserved0   = 1 << 2,
        Reservec1   = 1 << 3
    };
    template<> struct detail::flag::ops_def<PF_NewWorldFlags>{};
    struct PF_CompositeMode {
        PF_TransferMode xfer;
        A_long rand_seed;
        A_u_char opacity;
        PF_Boolean rgb_only;
        A_u_short opacitySu;
    };
    using PF_CallbackID = A_long;
    using PF_CallbackFunc = PF_Err(*)(PF_ProgPtr, ...);
    using PF_PlatDataID = A_long;
    using PF_Pixel8 = PF_Pixel;

    enum class PF_Precision : A_short {
        Integer,
        Tenths,
        Hundredths,
        Thousandths,
        TenThousandths,
    };
}
