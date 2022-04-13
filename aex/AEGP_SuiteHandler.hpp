#pragma once
#include <type_traits>

#include <aex/effect_type.hpp>
#include <aex/SP/SPBasicSuite.hpp>
#include <aex/pf_exception.hpp>

#include <aex/Suite/Suites.hpp>

namespace aex {

    struct PF_Iterate8Suite1 {
        constexpr inline static const char name[] = "PF Iterate8 Suite";
        constexpr inline static A_long version = 1; // frozen in AE 5.0
        constexpr inline static A_long index = 1;

        PF_Err(*iterate)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
        PF_Err(*iterate_origin)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
        PF_Err(*iterate_lut)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, A_u_char* a_lut0, A_u_char* r_lut0, A_u_char* g_lut0, A_u_char* b_lut0, PF_EffectWorld* dst);
        PF_Err(*iterate_origin_non_clip_src)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
        PF_Err(*iterate_generic)(A_long iterationsL, void* refconPV, PF_Err(*fn_func)(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL));
    };
    struct PF_Iterate16Suite1 {
        constexpr inline static const char name[] = "PF Iterate16 Suite";
        constexpr inline static A_long version = 1; // frozen in AE 5.0
        constexpr inline static A_long index = 1;

        PF_Err(*iterate)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
        PF_Err(*iterate_origin)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
        PF_Err(*iterate_origin_non_clip_src)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
    };

    struct UndefinedSuite {
        constexpr inline static const char name[] = "Dummy Suite";
        constexpr inline static A_long version = -1;
        constexpr inline static A_long index = -1;
    };
    class AEGP_SuiteHandler {
        const SPBasicSuite* i_pica_basicP;
        
        struct Suites {
            UndefinedSuite* keyframe_suite4P;
            UndefinedSuite* stream_suite3P;
            UndefinedSuite* stream_suite4P;
            UndefinedSuite* stream_suite5P;
            UndefinedSuite* marker_suite1P;
            UndefinedSuite* marker_suite2P;
            UndefinedSuite* marker_suite3P;
            UndefinedSuite* comp_suite4P;
            UndefinedSuite* comp_suite5P;
            UndefinedSuite* comp_suite6P;
            UndefinedSuite* comp_suite7P;
            UndefinedSuite* comp_suite8P;
            UndefinedSuite* comp_suite9P;
            UndefinedSuite* comp_suite10P;
            UndefinedSuite* comp_suite11P;
            UndefinedSuite* layer_suite3P;
            UndefinedSuite* layer_suite4P;
            UndefinedSuite* stream_suite2P;
            UndefinedSuite* dynamic_stream_suite2P;
            UndefinedSuite* dynamic_stream_suite3P;
            UndefinedSuite* dynamic_stream_suite4P;
            UndefinedSuite* keyframe_suite3P;
            UndefinedSuite* canvas_suite5P;
            UndefinedSuite* canvas_suite6P;
            UndefinedSuite* canvas_suite7P;
            UndefinedSuite* canvas_suite8P;
            UndefinedSuite* camera_suite2P;
            UndefinedSuite* register_suite5P;
            UndefinedSuite* memory_suite1P;
            UndefinedSuite* item_view_suite1P;
            UndefinedSuite* item_suite9P;
            UndefinedSuite* item_suite8P;
            UndefinedSuite* item_suite7P;
            UndefinedSuite* item_suite6P;
            UndefinedSuite* item_suite5P;
            UndefinedSuite* item_suite1P;
            UndefinedSuite* light_suite1P;
            UndefinedSuite* light_suite2P;
            UndefinedSuite* effect_suite1P;
            UndefinedSuite* effect_suite2P;
            UndefinedSuite* effect_suite3P;
            UndefinedSuite* effect_suite4P;
            UndefinedSuite* mask_suite4P;
            UndefinedSuite* mask_outline_suite1P;
            UndefinedSuite* mask_outline_suite2P;
            UndefinedSuite* mask_outline_suite3P;
            UndefinedSuite* command_suite1P;
            UndefinedSuite* utility_suite3P;
            UndefinedSuite* render_suite1P;
            UndefinedSuite* render_suite2P;
            UndefinedSuite* render_suite3P;
            UndefinedSuite* render_suite4P;
            UndefinedSuite* render_suite5P;
            UndefinedSuite* ansi_callbacks_suite1P;
            UndefinedSuite* handle_suite1P;
            UndefinedSuite* fill_matte_suite1P;
            UndefinedSuite* world_transform_suite1P;
            UndefinedSuite* query_xform_suite2P;
            UndefinedSuite* composite_suite2P;
            UndefinedSuite* world_suite1P;
            UndefinedSuite* pf_interface_suite1P;
            UndefinedSuite* math_suite1P;
            UndefinedSuite* adv_time_suite4P;
            UndefinedSuite* path_query_suite1P;
            UndefinedSuite* path_data_suite1P;
            UndefinedSuite* param_utils_suite3P;
            UndefinedSuite* app_suite4P;
            UndefinedSuite* app_suite5P;
            UndefinedSuite* app_suite6P;
            UndefinedSuite* adv_app_suite2P;
            UndefinedSuite* io_in_suite4P;
            UndefinedSuite* io_out_suite4P;
            UndefinedSuite* persistent_data_suite3P;
            UndefinedSuite* persistent_data_suite4P;
            UndefinedSuite* render_queue_suite1P;
            UndefinedSuite* rq_item_suite2P;
            UndefinedSuite* output_module_suite4P;
            UndefinedSuite* fim_suite3P;
            UndefinedSuite* sampling_8_suite1P;
            UndefinedSuite* sampling_16_suite1P;
            PF_Iterate8Suite1* iterate_8_suite1P;
            PF_Iterate16Suite1* iterate_16_suite1P;
            UndefinedSuite* iterate_float_suite1P;
            UndefinedSuite* collection_suite2P;
            UndefinedSuite* text_document_suite1P;
            UndefinedSuite* sound_data_suite2P;
            UndefinedSuite* aegp_iterate_suite1P;
            UndefinedSuite* text_layer_suite1P;
            UndefinedSuite* artisan_util_suite1P;
            UndefinedSuite* aegp_world_suite2P;
            UndefinedSuite* aegp_world_suite3P;
            UndefinedSuite* render_options_suite1P;
            UndefinedSuite* layer_render_options_suite_1P;
            UndefinedSuite* layer_render_options_suite_2P;
            UndefinedSuite* async_manager_suite1P;
            UndefinedSuite* tracker_suite_1P;
            UndefinedSuite* tracker_utility_suite_1P;
            UndefinedSuite* helper_suite_2P;
            UndefinedSuite* layer_suite_5P;
            UndefinedSuite* layer_suite_6P;
            UndefinedSuite* layer_suite_7P;
            UndefinedSuite* layer_suite_8P;
#ifdef I_NEED_ADM_SUPPORT
            UndefinedSuite* adm_basic_suite_8P;
            UndefinedSuite* adm_dialog_suite_8P;
            UndefinedSuite* adm_dialog_group_suite_3P;
            UndefinedSuite* adm_item_suite_8P;
            UndefinedSuite* adm_list_suite_3P;
            UndefinedSuite* adm_entry_suite_5P;
            UndefinedSuite* adm_notifier_suite_2P;
#endif
            UndefinedSuite* layer_suite_1P;
            UndefinedSuite* mask_suite_1P;
            UndefinedSuite* mask_suite_5P;
            UndefinedSuite* mask_suite_6P;
            UndefinedSuite* stream_suite_1P;
            UndefinedSuite* comp_suite_1P;
            UndefinedSuite* collection_suite_1P;
            UndefinedSuite* keyframe_suite_1P;
            UndefinedSuite* adv_app_suite_1P;
            UndefinedSuite* utility_suite_1P;
            UndefinedSuite* rendre_options_suite_2P;
            UndefinedSuite* proj_suite_5P;
            UndefinedSuite* proj_suite_6P;
            UndefinedSuite* footage_suite_5P;
            UndefinedSuite* rq_item_suite_3P;
            UndefinedSuite* utility_suite_4P;
            UndefinedSuite* color_settings_suite_2P;
            UndefinedSuite* color_settings_suite_1P;
            UndefinedSuite* adv_item_suite_1P;
            UndefinedSuite* render_options_suite_3P;
            UndefinedSuite* color_param_suite_1P;
            UndefinedSuite* sampling_float_suite_1P;
            UndefinedSuite* utility_suite_5P;
            UndefinedSuite* utlilty_suite_6P;
            UndefinedSuite* custom_ui_Suite1P;
            UndefinedSuite* custom_ui_Suite2P;
            UndefinedSuite* custom_ui_theme_suite1P;
            UndefinedSuite* drawing_suite_currentP;
            UndefinedSuite* drawbot_supplier_suite_currentP;
            UndefinedSuite* drawbot_surfave_Suite_currentP;
            UndefinedSuite* drawbot_path_suite_currentP;
            UndefinedSuite* suites_suite_2P;
        };
        mutable Suites i_suites;

#       define AEX_SUITES_LIST \
            AEX_SUITES_PROCESS(iterate_8_suite1P, Iterate8Suite1) \
            AEX_SUITES_PROCESS(iterate_16_suite1P, Iterate16Suite1) \

        template<class T> T* LoadSuite() const {
            void* suiteP;
            auto err = i_pica_basicP->AcquireSuite(T::name, T::version, &suiteP);
            if(err != 0 || suiteP == nullptr) MissingSuiteError();
            return static_cast<T*>(suiteP);
        }
        template<> Suite::Undefined* LoadSuite() const noexcept {
            return nullptr;
        }

        template<class T> void ReleaseSuite() const {
            i_pica_basicP->ReleaseSuite(T::name, T::version);
        }

        template<> void ReleaseSuite<Suite::Undefined>() const {}

        void ReleaseAllSuites() {
#           define AEX_SUITES_PROCESS(NAME) if(i_suites.NAME != nullptr) { ReleaseSuite<std::remove_pointer_t<decltype(i_suites.NAME)>>(); }
            AEX_SUITES_LIST
#           undef AEX_SUITES_PROCESS
        }

#ifdef AEX_USE_CPPEXCEPTION
        void MissingSuiteError() const {
            throw pf_exception(PF_Err::BadCallbackParam);
        }
#else
        // define yourself
        void MissingSuiteError() const noexcept;
#endif

    public:
        AEGP_SuiteHandler(const AEGP_SuiteHandler&) = delete;
        AEGP_SuiteHandler& operator=(const AEGP_SuiteHandler&) { return *this; };
        AEGP_SuiteHandler(const SPBasicSuite* pica_basicp) : i_pica_basicP(pica_basicp), i_suites{} {
            if(!i_pica_basicP) MissingSuiteError();
        }
        ~AEGP_SuiteHandler() {
            //ReleaseAllSuites();
        }
#       define AEX_SUITES_PROCESS(NAME, CALL) decltype(i_suites.NAME) CALL() const { if(i_suites.NAME == nullptr) { i_suites.NAME = static_cast<decltype(i_suites.NAME)>(LoadSuite<std::remove_pointer_t<decltype(i_suites.NAME)>>()); } return i_suites.NAME; }
        AEX_SUITES_LIST
#       undef AEX_SUITES_PROCESS

        const SPBasicSuite* Pica() const { return i_pica_basicP; }

    };
}
