#pragma once
#include <aex/aexint.hpp>
#include <aex/effect_type.hpp>

namespace aex{

static inline constexpr size_t PF_MAX_PARAM_VALUE_LEN = 31;
static inline constexpr size_t PF_MAX_PARAM_DESCRIPTION_LEN = 31;

using PF_ParamValueStr = A_char[PF_MAX_PARAM_VALUE_LEN + 1];
using PF_ParamDescriptionStr = A_char[PF_MAX_PARAM_DESCRIPTION_LEN + 1];

struct PF_LayerDef {
    void* reserved0, * reserved1;
    PF_WorldFlags world_flags;
    PF_PixelPtr data;
    A_long rowbytes;
    A_long width;
    A_long height;
    PF_UnionableRect extent_hint;
    void* platform_ref;
    A_long reserved_long1;
    void* reserved_long4;
    PF_RationalScale pix_aspect_ratio;
    void* reserved_long2;
    A_long origin_x, origin_y;
    A_short reserved_short1,reserved_short2;
    A_long dephault;
};

struct PF_SliderDef {
    PF_ParamValue value;
    PF_ParamValueStr value_str;
    PF_ParamDescriptionStr value_desc;
    PF_ParamValue valid_min, valid_max;
    PF_ParamValue slider_min, slider_max;
    PF_ParamValue dephault;
};

struct PF_FixedSliderDef {
    PF_Fixed value;
    PF_ParamValueStr value_str;
    PF_ParamDescriptionStr value_desc;
};

struct PF_FloatSliderDef {
    PF_FpLong value, phase;
    PF_ParamDescriptionStr value_desc;
    PF_FpShort valid_min, valid_max;
    PF_FpShort slider_min, slider_max;
    PF_FpShort dephault;
    PF_Precision precision;
    PF_ValueDisplayFlags display_flags;
    PF_FSliderFlags fs_flags;
    PF_FpShort curve_tolerance;
    PF_Boolean useExponent;
    PF_FpShort exponent;
};

struct PF_AngleDef {
    PF_Fixed value;
    PF_Fixed dephault;
    PF_Fixed valid_min, valid_max;
};

struct PF_CheckBoxDef {
    PF_ParamValue value;
    PF_Boolean dephault;
    A_char reserved; // padding
    A_short reserved1;
    union {
        const A_char* nameptr;
    } u;
};

struct PF_ColorDef {
    PF_UnionablePixel value, dephault;
};

struct PF_PointDef {
    PF_Fixed x_value, y_value;
    A_char reserved[3];
    PF_Boolean restrict_bounds;
    PF_Fixed x_dephault, y_dephault;
};

struct PF_PopupDef {
    PF_ParamValue value;
    A_short num_choices;
    A_short dephault;
    union {
        const A_char* namesptr;
    } u;
};

struct PF_ArbitraryDef {
    A_short id;
    A_short pad;
    PF_ArbitraryH dephault;
    PF_ArbitraryH value;
    void* refconPV;
};

struct PF_PathDef {
    PF_PathID path_id;
    A_long reserved0;
    A_long dephault;
};

struct PF_ButtonDef {
    PF_ParamValue value;
    union {
        const A_char* namesptr;
    } u;
};

struct PF_Point3DDef {
    PF_FpLong x_value, y_value, z_value;
    PF_FpLong x_dephault, y_dephault, z_dephault;
    char reserved[16];
};

union PF_ParamDefUnion {
    PF_LayerDef ld;
    PF_SliderDef sd;
    PF_FixedSliderDef fd;
    PF_AngleDef ad;
    PF_CheckBoxDef bd;
    PF_ColorDef cd;
    PF_PointDef td;
    PF_PopupDef pd;
    PF_FloatSliderDef fs_d;
    PF_ArbitraryDef arb_d;
    PF_PathDef path_d;
    PF_ButtonDef button_d;
    PF_Point3DDef point3d_d;
};

struct PF_ParamDef {
    static inline constexpr size_t PF_MAX_EFFECT_PARAM_NAME_LEN = 31;
    union {
        A_long id;
        PF_ChangeFlags change_flags;
    } uu;
    PF_ParamUIFlags ui_flags;
    A_short ui_width;
    A_short ui_height;

    PF_ParamType param_type;
    A_char name[PF_MAX_EFFECT_PARAM_NAME_LEN + 1];
    PF_ParamFlags flags;

    A_long unused;
    PF_ParamDefUnion u;
};
using PF_ParamDefPtr = PF_ParamDef*;
using PF_ParamDefH = PF_ParamDef**;
using PF_ParamList = PF_ParamDef**;

using PF_EffectWorld = PF_LayerDef;

struct PF_SampPB {
    PF_Fixed x_radius, y_radius;
    PF_Fixed area;
    PF_EffectWorld* src;
    PF_SampleEdgeBehav samp_behave;
    A_long allow_asynch;
    A_long motion_blur;
    PF_CompositeMode comp_mode;
    PF_PixelPtr mask0;
    A_u_char* fcm_table;
    A_u_char* fcd_table;
    A_long reserved[8];
};

using PF_MaskFlags = A_long;
struct PF_MaskWorld {
    PF_EffectWorld mask;
    PF_Point offset;
    PF_MaskFlags what_is_mask;
};

}
