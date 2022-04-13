#pragma once

#include <aex/SP/SPType.hpp>

#pragma pack(push, aexalign, 8)

namespace aex{
extern "C" {

inline constexpr auto kSPBasicSuite = "SP Basic Suite";
inline constexpr auto kSPBasicSuiteVersion = 4;

struct SPBasicSuite {
    SPAPI SPErr (*AcquireSuite)(const char* name, int version, /*const*/ void** suite);
    SPAPI SPErr (*ReleaseSuite)(const char* name, int version);
    SPAPI SPBoolean (*IsEqual)(const char* token1, const char* token2);
    SPAPI SPErr (*AllocateBlock)(std::size_t size, void** block);
    SPAPI SPErr (*FreeBlock)(void* block);
    SPAPI SPErr (*ReallocateBlock)(void* block, std::size_t newSize, void** newblock);
    SPAPI SPErr (*Undefined)();
};


} // extern "C"
} // namespace aex

#pragma pack(pop, aexalign)
