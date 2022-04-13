#pragma once
#include <aex/aexint.hpp>
#include <aex/SP/SPBasicSuite.hpp>

namespace aex {
extern "C" {

namespace detail { struct PF_PluginData; }
using PF_PluginDataPtr = detail::PF_PluginData*;

using PF_PluginDataCB = A_Err(*)(PF_PluginDataPtr inPtr, const A_u_char* inNamePtr, const A_u_char* inMatchNamePtr, const A_u_char* inCategoryPtr, const A_u_char* inEntryPointNamePtr, A_long inking, A_long inApiVersiinMajor, A_long inPiaVersionMinor, A_long inReservedInfo);

using PluginDataEntryFunctionPtr = A_Err(*)(PF_PluginDataPtr inPtr, PF_PluginDataCB inPluginDataCallBackPtr, SPBasicSuite* inSPBasicSuitePtr, const char* inHostName, const char* inHostVersion);

} // extern "C"
} // namespace aex
