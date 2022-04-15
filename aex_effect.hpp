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

        case PF_Cmd::SmartPreRender:
            return SmartPreRender();

        case PF_Cmd::SmartRender:
            return SmartRender();
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

    virtual PF_Err GlobalSetUp() noexcept { return PF_Err::None; }
    virtual PF_Err ParamsSetUp() noexcept { return PF_Err::None; }
    virtual PF_Err Render() noexcept { return PF_Err::None; }
    virtual PF_Err SmartPreRender() noexcept { return PF_Err::None; };
    virtual PF_Err SmartRender() noexcept { return PF_Err::None; };

    inline PF_Err AddColor(const A_u_char* name, A_u_char red, A_u_char green, A_u_char blue, A_long id) const AEX_NOEXCEPT {
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
    
    inline PF_Err AddArbitrary2(const A_u_char* name, A_short width, A_short height, PF_ParamFlags flags, PF_ParamUIFlags pui_flags, PF_ArbitraryH dflt, A_long id, void* refcon) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id,
            },
            .ui_flags = pui_flags,
            .ui_width = width,
            .ui_height = height,
            .param_type = PF_ParamType::ArbitraryData,
            .flags = flags,
            .u = { .arb_d = {
                .id = id,
                .pad = 0,
                .dephault = dflt,
                .value = NULL,
                .refconPV = refcon
            }},
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddArbitrary(const A_u_char* name, A_short width, A_short height, PF_ParamUIFlags pui_flags, PF_ArbitraryH dflt, A_long id, void* refcon) const AEX_NOEXCEPT {
	    return AddArbitrary2(name, width, height, PF_ParamFlags::None, pui_flags, dflt, id, refcon);
    }

    inline PF_Err AddSlider(const A_u_char* name, PF_ParamValue valid_min, PF_ParamValue valid_max, PF_ParamValue  slider_min, PF_ParamValue slider_max, PF_ParamValue dflt, A_long id) const AEX_NOEXCEPT {
        PF_ParamDef def {
            .uu = {
                .id = id,
            },
            .param_type = PF_ParamType::Slider,
            .u = { .sd = {
                .value = dflt,
                .value_str = "",
                .value_desc = "",
                .valid_min = valid_min,
                .valid_max = valid_max,
                .slider_min = slider_min,
                .slider_max = slider_max,
                .dephault = dflt,
            }}
        };

        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));

        return PF_Err::None;
    }

    template<class T>
    inline PF_Err AddFixed(const A_u_char* name, T valid_min, T valid_max, T slider_min, T slider_max, T dflt, PF_Precision prec, PF_ValueDisplayFlags disp, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
        auto value = static_cast<PF_Fixed>(dflt * 65536.0);
        PF_ParamDef def {
            .uu = {
                .id = id,
            },
            .param_type = PF_ParamType::FixSlider,
            .flags = flags,
            .u = { .fd = {
                .value = value,
                .value_str = "",
                .value_desc = "",
                .valid_min = static_cast<PF_Fixed>(valid_min * 65536.0),
                .valid_max = static_cast<PF_Fixed>(valid_max * 65536.0),
                .slider_min = static_cast<PF_Fixed>(slider_min * 65536.0),
                .slider_max = static_cast<PF_Fixed>(slider_max * 65536.0),
                .dephault = value,
                .precision = prec,
                .display_flags = disp
            }}
        };

		in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline static constexpr float AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE = 0.05f;

    inline PF_Err AddFloatSlider(const A_u_char* name, PF_FpShort valid_min, PF_FpShort valid_max, PF_FpShort slider_min, PF_FpShort slider_max, PF_FpShort curve_tolerance, PF_FpShort dflt, PF_Precision prec, PF_ValueDisplayFlags disp, PF_FSliderFlags what_phase, A_long id) const AEX_NOEXCEPT {
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
                    .curve_tolerance = AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE,
                }
            }
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddFloatSliderX(const A_u_char* name, PF_FpShort valid_min, PF_FpShort valid_max, PF_FpShort slider_min, PF_FpShort slider_max, PF_FpShort dflt, PF_Precision prec, PF_ValueDisplayFlags disp, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
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
                    .curve_tolerance = AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE,
                }
            }
        };
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddFloatExponentialSlider(const A_u_char* name, PF_FpShort valid_min, PF_FpShort valid_max, PF_FpShort slider_min, PF_FpShort slider_max, PF_FpShort curve_tolerance, PF_FpShort dflt, PF_Precision prec, PF_ValueDisplayFlags disp, bool want_phase, PF_FpShort exponent, A_long id) {
        PF_ParamDef def {
            .uu = {
                .id = id,
            },
            .param_type = PF_ParamType::FloatSlider,
            .u = { .fs_d = {
                .value = dflt,
                .valid_min = valid_min,
                .valid_max = valid_max,
                .slider_min = slider_min,
                .slider_max = slider_max,
                .dephault = dflt,
                .precision = prec,
                .display_flags = disp,
                .fs_flags = want_phase ? PF_FSliderFlags::WantPhase : PF_FSliderFlags::None,
                .curve_tolerance = AEFX_AUDIO_DEFAULT_CURVE_TOLERANCE,
               .useExponent = true,
               .exponent = exponent
            }},
        };
        
        in_data->utils->ansi.strcpy(def.name, name);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddCheckBox(const A_u_char* name_a, const char* name_b, PF_Boolean dflt, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
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
        in_data->utils->ansi.strcpy(def.name, name_a);
        AEX_PF_ERR_CHECK(in_data->inter.add_param(in_data->effect_ref, -1, &def));
        return PF_Err::None;
    }

    inline PF_Err AddCheckBoxX(const A_u_char* name, PF_Boolean dflt, PF_ParamFlags flags, A_long id) const AEX_NOEXCEPT {
        return AddCheckBox(name, "", dflt, flags, id);
    }

    // todo: その他パラメータ追加関数の追加

    // AddButton

    // AddAngle

    // AddNull

    // AddPopup

    // AddLayer

    // Add255Slider

    // AddPercente

    // AddPoint

    // AddPoint3D

    // AddTopic

    // AddVersionedFlag

    // AddTopicX

    // AddPopupX

    // AddFloatSliderXDisabled

    // AddPointControl
};

}
