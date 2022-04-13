#pragma once
#include <cstdint>

#include <aex/macro.hpp>

#ifdef A_INTERNAL
#error AfterEffectsSDK潰す
#endif

namespace aex{

using A_long = std::int32_t;
using A_u_long = std::uint32_t;
using A_char = char;
using A_FpLong = double;
using A_FpShort = float;
enum class A_Err : A_long {
    None,
    Generic,
    Struct,
    Parameter,
    Alloc,
    WrongThread,
    ConstProjectModification,
    MissingSuite = 13
};
using A_Handle = void*;
using A_Fixed = A_long;
using A_UFixed = A_u_long;

enum class PF_Err : A_long{
    None = 0,
    OutOfMemory = 4,
    FirstErr = 512,
    InternalStructDamaged = FirstErr,
    InvalidIndex,
    UnrecognizedParamType,
    InvalidCallback,
    BadCallbackParam,
    InterruptCancel,
    CannotParseKeyframeText
};

#if AEX_DETAIL_IS_MWERKS_OR_GNUC
    // metrowerks codewarrior and XCode/GCC
    using A_short = std::int16_t;
    using A_u_short = std::uint16_t;
    using A_u_char = std::uint8_t;
    using A_Boolean = std::uint8_t;
    using A_intptr_t = std::intptr_t;

#else // if AEX_DETAIL_IS_MWERKS_OR_GNUC
    // windows
    using A_short = short;
    using A_u_short = unsigned short;
    using A_u_char = unsigned char;
    using A_Boolean = unsigned char;

#ifdef _WIN64
    using A_Intptr_t = __int64;
#else // ifdef _WIN64
    using A_Intptr_t = std::int32_t;
#endif // ifdef _WIN64

#endif // if AEX_DETAIL_IS_MWERKS_OR_GNUC

using A_short = short;
using PF_Field = A_long;

#ifdef _MSC_VER
    // Visual C++
    using A_u_longlong = uint64_t;
#endif // ifdef _MSC_VER

#if AEX_DETAIL_IS_MWERKS_OR_GNUC
    using A_u_longlong = unsigned __int64;
#endif // if AEX_DETAIL_IS_MWERKS_OR_GNUC

#pragma pack(push, aexalign, 8)

struct A_Time {
    A_long value;
    A_u_long scale;
};

struct A_Ratio {
    A_long num;
    A_u_long den;
};

struct A_FloatPoint {
    A_FpLong x, y;
};

struct A_FloatPoint3 {
    A_FpLong x, y, z;
};

struct A_FloatRect {
    A_FpLong left, top, right, bottom;
};

struct A_Matrix3 {
    A_FpLong mat[3][3];
};

struct A_Matrix4 {
    A_FpLong mat[4][4];
};

struct A_LegacyRect {
    A_short top, left, bottom, right;
};

struct A_LRect {
    A_long left, top, right, bottom;
};

using A_Rect = A_LRect;

struct A_LPoint {
    A_long x, y;
};

struct A_FloatPolar {
    A_FpLong raduis, angle;
};

using A_HandleSize = A_u_longlong;

struct A_Color {
    A_FpLong alpha, red, green, blue;
};

#pragma pack(pop, aexalign)

struct A_Version {
    A_short majorS, minorS;
};

namespace detail{ struct Up_OpaqueMem; }
using AEGP_MemHandle = detail::Up_OpaqueMem**;

using A_UTF16Char = A_u_short;

#if AEX_DETAIL_IS_MWERKS_OR_GNUC
    using A_LegacyEnumType = A_char;
#else
    using A_LegacyEnumType = A_long;
#endif

} // namespace aex
