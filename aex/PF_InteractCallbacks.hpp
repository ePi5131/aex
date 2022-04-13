#pragma once
#include <aex/aexint.hpp>
#include <aex/effect_type.hpp>
#include <aex/PF_ParamDef.hpp>

namespace aex {

struct PF_InteractCallbacks {
    PF_Err (*checkout_param)(
        PF_ProgPtr effect_ref,
        PF_ParamIndex index,
        A_long what_time,
        A_long time_step,
        A_u_long time_scale,
        PF_ParamDef* param
    );
    PF_Err (*checkin_param)(
        PF_ProgPtr effect_ref,
        PF_ParamDef* param
    );
    PF_Err (*add_param)(
        PF_ProgPtr effect_ref,
        PF_ParamIndex index,
        PF_ParamDefPtr def
    );
    PF_Err (*abort)(PF_ProgPtr effect_ref);
    PF_Err (*progress)(PF_ProgPtr effect_ref, A_long current, A_long total);
    PF_Err (*register_ui)(PF_ProgPtr effect_ref, PF_CustomUIInfo* cust_info);
    PF_Err (*checkout_layer_audio)(
        PF_ProgPtr effect_ref,
        PF_ParamIndex index,
        A_long atart_time,
        A_long duration,
        A_u_long time_scale,
        PF_UFixed rate,
        A_long bytes_per_sample,
        A_long num_channels,
        A_long fmt_signed,
        PF_LayerAudio* audio
    );
    PF_Err (*checkin_layer_audio)(
        PF_ProgPtr effect_ref,
        PF_LayerAudio audio
    );
    PF_Err (*get_audio_data)(
        PF_ProgPtr effect_ref,
        PF_LayerAudio audio,
        PF_SndSamplePtr* data0,
        A_long *num_samples0,
        PF_UFixed* rate0,
        A_long* bytes_per_sample0,
        A_long* num_channels0,
        A_long* fmt_signed0
    );
    void* reserved_str[3];
    void* reserved[10];
};

}
