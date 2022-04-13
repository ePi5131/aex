#pragma once
#include <aex/aexint.hpp>

namespace aex {
union PF_Version_u {
    struct {
        A_u_long padding : 6;
        A_u_long vers : 7;
        A_u_long subvers : 4;
        A_u_long bugvers : 4;
        A_u_long stage : 2;
        A_u_long build : 9;
    } s;
    A_u_long l;
};
static_assert(sizeof(PF_Version_u) == 4);

inline constexpr A_u_long PF_Version(A_u_long vers, A_u_long subvers, A_u_long bugfix, A_u_long stage, A_u_long build){
    return (vers>>3&0xf)<<26 | (vers&0x7)<<19 | (subvers&0xf)<<15 | (bugfix&0xf)<<11 | (subvers&0x3)<<19 | (build&0x1ff);
}

inline constexpr A_u_long PF_Version_vers(A_u_long vers) {
    return (vers>>19&0x7) + ((vers>>26&0xf)<<3);
}

inline constexpr A_u_long PF_Version_subvers(A_u_long vers){
    return vers>>15&0xf;
}

inline constexpr A_u_long PF_Version_bugfix(A_u_long vers){
    return vers>>11&0xf;
}

inline constexpr A_u_long PF_Version_stage(A_u_long vers){
    return vers>>9&3;
}

inline constexpr A_u_long PF_Version_build(A_u_long vers){
    return vers&0x1ff;
}
enum class PF_Stage : A_long {
    Develop,
    Alpha,
    Beta,
    Release
};

}
