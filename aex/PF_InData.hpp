#pragma once

#include <aex/aexint.hpp>
#include <aex/effect_type.hpp>
#include <aex/PF_ParamDef.hpp>
#include <aex/PF_InteractCallbacks.hpp>
#include <aex/SP/SPBasicSuite.hpp>

namespace aex {

struct PF_InData;

struct PF_UtilCallbacks{
    PF_Err (*begin_sampling)(PF_ProgPtr effect_ref, PF_Quality qual, PF_ModeFlags mf, PF_SampPB* params);
    PF_Err (*subpixel_sample)(PF_ProgPtr effect_ref, PF_Fixed x, PF_Fixed y, const PF_SampPB* params, PF_Pixel* dst_pixel);
    PF_Err (*area_sample)(PF_ProgPtr effect_ref, PF_Fixed x, PF_Fixed y, const PF_SampPB* params, PF_Pixel* dst_pixel);
    void* get_batch_func_is_deprecated;
    PF_Err (*end_sampling)(PF_ProgPtr effect_ref, PF_Quality qual, PF_ModeFlags mf, PF_SampPB* params);
    PF_Err (*composite_rect)(PF_ProgPtr effect_ref, PF_Rect* src_rect, A_long src_opacity, PF_EffectWorld* source_wld, A_long dest_x, A_long dest_y, PF_Field field_rdr, PF_XferMode xfer_mode, PF_EffectWorld* dest_wld);
    PF_Err (*blend)(PF_ProgPtr effect_ref, const PF_EffectWorld* src1, const PF_EffectWorld* src2, PF_Fixed ratio, PF_EffectWorld* dst);
    PF_Err (*convolve)(PF_ProgPtr effect_ref, PF_EffectWorld* src, const PF_Rect* area, PF_KernelFlags flags, void* a_kernel, void* r_kernel, void* g_kernel, void* b_kernel, PF_EffectWorld* dst);
    PF_Err (*copy)(PF_ProgPtr effect_ref, PF_EffectWorld* src, PF_EffectWorld* dst, PF_Rect* erc_r, PF_Rect* dst_r);
    PF_Err (*fill)(PF_ProgPtr effect_ref, const PF_Pixel* color, const PF_Rect* dst_rect, PF_EffectWorld* world);
    PF_Err (*gaussian_kernel)(PF_ProgPtr effect_ref, A_FpLong kRadius, PF_KernelFlags flags, A_FpLong multiplier, A_long* diameter, void* kernel);
    PF_Err (*iterate)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*premultiply)(PF_ProgPtr effect_ref, A_long forward, PF_EffectWorld* dst);
    PF_Err (*premultiply_color)(PF_ProgPtr effect_ref, PF_EffectWorld* src, const PF_Pixel* color, A_long forward, PF_EffectWorld* dst);
    PF_Err (*new_world)(PF_ProgPtr effect_ref, A_long width, A_long height, PF_NewWorldFlags flags, PF_EffectWorld* world);
    PF_Err (*dispose_world)(PF_ProgPtr effect_ref, PF_EffectWorld* world);
    PF_Err (*iterate_origin)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Point* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*iterate_lut)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, A_u_char* a_lut0, A_u_char* r_lut0, A_u_char* g_lut0, A_u_char* b_lut0, PF_EffectWorld* dst);
    PF_Err (*transfer_rect)(PF_ProgPtr effect_ref, PF_Quality quality, PF_ModeFlags m_flags, PF_Field field, const PF_Rect* src_rec, const PF_EffectWorld* src_world, const PF_CompositeMode* comp_mode, const PF_MaskWorld* mask_world0, A_long dest_x, A_long dest_y, PF_EffectWorld* dst_world);    PF_Err (*transform_world)(PF_ProgPtr effect_ret, PF_Quality quality, PF_ModeFlags m_flags, PF_Field, const PF_EffectWorld* src_world, const PF_CompositeMode* comp_mode, const PF_MaskWorld* mask_world0, const PF_FloatMatrix* matrices, A_long num_matrices, PF_Boolean src2dst_matrix, const PF_Rect* dest_rect, PF_EffectWorld* dst_world);
    PF_Err (*host_new_handle)(A_u_longlong size);
    void* (*host_lock_handle)(PF_Handle pf_handle);
    void (*host_unlock_handle)(PF_Handle pf_handle);
    void (*host_dispose_handle)(PF_Handle pf_handle);
    PF_Err (*get_callback_addr)(PF_ProgPtr effect_ref, PF_Quality quality, PF_ModeFlags mode_flags, PF_CallbackID which_callback, PF_CallbackFunc* fn_ptr);
    PF_Err (*app)(PF_ProgPtr, A_long, ...);
    PF_ANSICallbacks ansi;
    PF_ColorCallbacks colorCB;
    PF_Err (*get_platform_data)(PF_ProgPtr effect_ref, PF_PlatDataID which, void* data);
    A_u_longlong (*host_get_handle_size)(PF_Handle pf_handle);
    PF_Err (*itrrate_origin_non_clip_src)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Point* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*iterate_generic)(A_long iterationsL, void* refconPV, PF_Err (*fn_func)(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL));
    PF_Err (*host_resize_handle)(A_u_longlong new_sizeL, PF_Handle* handlePH);
    PF_Err (*subpixel_sample16)(PF_ProgPtr effect_ref, PF_Fixed x, PF_Fixed y, const PF_SampPB* params, PF_Pixel16* dst_pixel);
    PF_Err (*area_sample16)(PF_ProgPtr effect_ref, PF_Fixed x, PF_Fixed y, const PF_SampPB* params, PF_Pixel16* dst_pixel);
    PF_Err (*fill16)(PF_ProgPtr effect_ref, const PF_Pixel16* color, const PF_Rect* dst_rect, PF_EffectWorld* world);
    PF_Err (*premultiply_color16)(PF_ProgPtr effect_ref, PF_EffectWorld* src, const PF_Pixel16* color, A_long forward, PF_EffectWorld* dst);
    PF_Err (*iterate16)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*iterate_origin16)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Point* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*iterate_origin_non_clip_src16)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Point* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
    PF_Err (*get_pixel_data8)(PF_EffectWorld* worldP, PF_PixelPtr pixelP0, PF_Pixel8** pixPP);
    PF_Err (*get_pixel_data16)(PF_EffectWorld* worldP, PF_PixelPtr pixelP0, PF_Pixel16** pixPP);
    A_long reserved[1];
};

struct PF_InData {
    PF_InteractCallbacks inter;
    PF_UtilCallbacks* utils;
    PF_ProgPtr effect_ref;
    PF_Quality quality;
    PF_SpecVersion version;
    A_long serial_num;
    A_long appl_id;
    A_long num_params;
    A_long reserved;
    A_long what_cpu;
    A_long what_fpu;
    A_long current_time;
    A_long time_step;
    A_long total_time;
    A_long local_time_step;
    A_u_long time_scale;
    PF_Field field;
    PF_Fixed shutter_angle;
    A_long width;
    A_long height;
    PF_Rect extent_hint;
    A_long output_origin_x;
    A_long output_origin_y;
    PF_RationalScale downsample_x;
    PF_RationalScale downsample_y;
    PF_RationalScale pixel_aspect_ratio;
    PF_InFlags in_flags;
    PF_Handle global_data;
    PF_Handle sequence_data;
    PF_Handle frame_data;
    A_long start_sampL;
    A_long dur_sampL;
    A_long total_sampL;
    PF_SoundWorld src_snd;
    SPBasicSuite* pica_basicP;
    A_long pre_effect_source_origin_x;
    A_long pre_effect_source_origin_y;
    PF_Fixed shutter_phase;
};

} // namespace aex
