#pragma once

#include <aex/version.hpp>
#include <aex/PF_InData.hpp>
#include <aex/PF_OutData.hpp>
#include <aex/PF_PluginData.hpp>
#include <aex/AEGP_SuiteHandler.hpp>

namespace aex{

class Effect {
public:

    Effect(const char* name, const char* match_name, const char* category, const char* entry_name):
        name(reinterpret_cast<const A_u_char*>(name)), match_name(reinterpret_cast<const A_u_char*>(match_name)), category(reinterpret_cast<const A_u_char*>(category)), entry_name(reinterpret_cast<const A_u_char*>(entry_name)),
        in_data(nullptr),out_data(nullptr),params(nullptr),output(nullptr)
        {}

    Effect(const A_u_char* name, const A_u_char* match_name, const A_u_char* category, const A_u_char* entry_name):
        name(name), match_name(match_name), category(category), entry_name(entry_name),
        in_data(nullptr),out_data(nullptr),params(nullptr),output(nullptr)
        {}

    virtual PF_Err Entry(PF_PluginDataPtr inPtr, PF_PluginDataCB inPluginDataCallBackPtr) {
        auto result = inPluginDataCallBackPtr(inPtr, name, match_name, category, entry_name, 'eFKT', 1, 1, 8);
        return result == A_Err::None ? PF_Err::None : PF_Err::InvalidCallback;
    }

    virtual PF_Err Main(PF_Cmd cmd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* params[], PF_LayerDef* output) noexcept {
        this->in_data = in_data;
        this->out_data = out_data;
        this->params = params;
        this->output = output;

        switch(cmd){
        case PF_Cmd::About:
            return About();

        case PF_Cmd::GlobalSetup:
            return GlobalSetUp();

        case PF_Cmd::ParamsSetUp:
            return ParamsSetUp();

        case PF_Cmd::Render:
            return Render();
        }
        return PF_Err::None;
    }

protected:
    const A_u_char* name;
    const A_u_char* match_name;
    const A_u_char* category;
    const A_u_char* entry_name;

    PF_InData* in_data;
    PF_OutData* out_data;
    PF_ParamDef** params;
    PF_LayerDef* output;


    virtual PF_Err About() const noexcept {
        strcpy_s(out_data->return_msg, "provided by aex::Effect");
        return PF_Err::None;
    }

    virtual PF_Err GlobalSetUp() noexcept = 0;

    virtual PF_Err ParamsSetUp() noexcept = 0;

    virtual PF_Err Render() noexcept = 0;


    inline PF_Err AddFloatSlider(const char* name, PF_FpShort valid_min, PF_FpShort valid_max, PF_FpShort slider_min, PF_FpShort slider_max, PF_FpShort curve_tolerance, PF_FpShort dflt, PF_Precision prec, PF_ValueDisplayFlags disp, PF_FSliderFlags what_phase, A_long id) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id
            },
            .param_type = PF_ParamType::FloatSlider,
            .u = {
                .fs_d = {
                    .value = dflt,
                    .valid_min = valid_min,
                    .valid_max = valid_max,
                    .slider_min = slider_min,
                    .slider_max = slider_max,
                    .dephault = dflt,
                    .precision = prec,
                    .display_flags = disp,
                    .curve_tolerance = 0.05f, // AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE
                }
            }
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddFloatSliderX(const char* name, PF_FpShort valid_min, PF_FpShort valid_max, PF_FpShort slider_min, PF_FpShort slider_max, PF_FpShort dflt, PF_Precision prec, PF_ValueDisplayFlags disp, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id
            },
            .param_type = PF_ParamType::FloatSlider,
            .flags = flags,
            .u = {
                .fs_d = {
                    .value = dflt,
                    .valid_min = valid_min,
                    .valid_max = valid_max,
                    .slider_min = slider_min,
                    .slider_max = slider_max,
                    .dephault = dflt,
                    .precision = prec,
                    .display_flags = disp,
                    .curve_tolerance = 0.05f, // AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE
                }
            }
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddCheckBox(const char* name_a, const char* name_b, PF_Boolean dflt, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id
            },
            .param_type = PF_ParamType::Checkbox,
            .flags = flags,
            .u = {
                .bd = {
                    .value = dflt,
                    .dephault = dflt,
                    .u = {
                        .nameptr = name_b
                    },
                }
            },
        };
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddCheckBoxX(const char* name, PF_Boolean dflt, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
        return AddCheckBox(name, "", dflt, flags, id);
    }

    inline PF_Err AddColor(const char* name, A_u_char red, A_u_char green, A_u_char blue, A_long id) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id
            },
            .param_type = PF_ParamType::Color,
            .u = {
                .cd = {
                    .value = {
                        .alpha = 255,
                        .red = red,
                        .green = green,
                        .blue = blue
                    },
                    .dephault = {
                        .alpha = 255,
                        .red = red,
                        .green = green,
                        .blue = blue
                    },
                }
            }
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }
    
};

}
