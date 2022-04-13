#pragma once

#include <aex/pf_exception.hpp>
#include <aex/SP/SPBasicSuite.hpp>

namespace aex {
    namespace Suite {
        
        template<size_t index = 1>struct Iterate8;

        template<>struct Iterate8<1> {
            constexpr inline static const char name[] = "PF Iterate8 Suite";
            constexpr inline static A_long version = 1; // frozen in AE 5.0
            constexpr inline static A_long index = 1;

            PF_Err(*iterate)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
            PF_Err(*iterate_origin)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
            PF_Err(*iterate_lut)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, A_u_char* a_lut0, A_u_char* r_lut0, A_u_char* g_lut0, A_u_char* b_lut0, PF_EffectWorld* dst);
            PF_Err(*iterate_origin_non_clip_src)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel8Func pix_fn, PF_EffectWorld* dst);
            PF_Err(*iterate_generic)(A_long iterationsL, void* refconPV, PF_Err(*fn_func)(void* refconPV, A_long thread_indexL, A_long i, A_long iterationsL));
        };

        template<size_t index> struct Iterate16;

        template<>struct Iterate16<1> {
            constexpr inline static const char name[] = "PF Iterate16 Suite";
            constexpr inline static A_long version = 1; // frozen in AE 5.0
            constexpr inline static A_long index = 1;

            PF_Err(*iterate)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
            PF_Err(*iterate_origin)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
            PF_Err(*iterate_origin_non_clip_src)(PF_InData* in_data, A_long progress_base, A_long progress_final, PF_EffectWorld* src, const PF_Rect* area, const PF_Rect* origin, void* refcon, PF_IteratePixel16Func pix_fn, PF_EffectWorld* dst);
        };

        struct Undefined {
            constexpr inline static const char name[] = "Dummy Suite";
            constexpr inline static A_long version = -1;
            constexpr inline static A_long index = -1;
        };

        template<class S> class Scoper {
            inline static SPBasicSuite* m_bsp;
            inline static S* m_suite_ptr = nullptr;
            inline static size_t m_count = 0u;
        public:
            Scoper(SPBasicSuite* bsp) {
                if (m_count == 0) {
                    m_bsp = bsp;
                    void* suiteP;
                    auto err = m_bsp->AcquireSuite(S::name, S::version, &suiteP);
                    if (err != 0 || suiteP == nullptr) throw A_Err::MissingSuite;
                    m_suite_ptr = static_cast<S*>(suiteP);
                }
                m_count++;
            }
            ~Scoper() {
                if (--m_count > 0) return;
                m_bsp->ReleaseSuite(S::name, S::version);
                m_suite_ptr = nullptr;
            }
            S* operator->() {
                return m_suite_ptr;
            }

#ifdef AEX_USE_CPPEXCEPTION
            static void MissingSuiteError() {
                throw pf_exception(PF_Err::BadCallbackParam);
            }
#else
            static void MissingSuiteError();
#endif
        };
    }
}
