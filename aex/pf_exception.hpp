#pragma once
#include <exception>
#include <string>
#include <unordered_map>

#include <aex/aexint.hpp>

namespace aex {
#   ifdef AEX_USE_CPPEXCEPTION

    class pf_exception : public std::exception {
        PF_Err m_code;
        inline static std::unordered_map<PF_Err, const char*> names = {
            { PF_Err::None, "None" },
            { PF_Err::OutOfMemory , "OutOfMemory" },
            { PF_Err::InternalStructDamaged , "InternalStructDamaged" },
            { PF_Err::InvalidIndex , "InvalidIndex" },
            { PF_Err::UnrecognizedParamType , "UnrecognizedParamType" },
            { PF_Err::InvalidCallback , "InvalidCallback" },
            { PF_Err::BadCallbackParam , "BadCallbackParam" },
            { PF_Err::InterruptCancel , "InterruptCancel" },
            { PF_Err::CannotParseKeyframeText , "CannotParseKeyframeText" },
        };
        inline static const char* unknown_error_name = "Unknown";

        static const char* code_name(PF_Err code) {
            if(auto itr = names.find(code); itr != names.end()){
                return itr->second;
            }
            return unknown_error_name;
        }

    public:
        pf_exception(const std::string_view str):std::exception(str.data()){}
        pf_exception(PF_Err code) : m_code(code), std::exception(code_name(code)) {}
        PF_Err code() const { return m_code; }
    };
#       define AEX_PF_ERR_CHECK(x) do{if((x)!=PF_Err::None)throw pf_exception(x);}while(0)
#       define AEX_NOEXCEPT
#       define AEX_TRY try
#       define AEX_CATCH catch(const pf_exception& e) { return e.code(); }
#   else
#       define AEX_PF_ERR_CHECK(x) do { if((x)!=PF_Err::None) return x; }while(0)
#       define AEX_NOEXCEPT noexcept
#       define AEX_TRY
#       define AEX_CATCH
#   endif

}
