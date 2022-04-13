#pragma once

#include <cstdint>
#include <aex/SP/SPConfig.hpp>

#if defined(MAC_ENV) || defined(IOS_ENV)
#   if defined(__GNUC__)
#       define SPAPI
#   else
#       define SPAPI pascal
#   endif
#endif

#if defined(WIN_ENV) || defined(ANDROID_ENV)
#   define SPAPI
#endif

namespace aex {

using SPUInt8 = std::uint8_t;
using SPUInt16 = std::uint16_t;
using SPUInt32 = std::uint32_t;
using SPInt32 = std::int32_t;


#if defined(MAC_ENV) || defined(IOS_ENV) || defined(ANDROID_ENV)
using SPBoolean = unsigned char;
#endif

#ifdef WIN_ENV
using SPBoolean = int;
#endif

using SPErr = int;

inline constexpr auto kASNoError                       = 0x00000000L;
inline constexpr auto kASUnimplementedError            = '!IMP';
inline constexpr auto kASUserCanceledError             = 'stop';

inline constexpr auto kSPNoError                       = 0x00000000L;
inline constexpr auto kSPUnimplementedError            = '!IMP';
inline constexpr auto kSPUserCanceledError             = 'stop';
inline constexpr auto kSPOperationInterrupted          = 'intr';
inline constexpr auto kSPLogicError                    = 'fbar';

inline constexpr auto kSPCantAcquirePluginError        = '!Acq';
inline constexpr auto kSPCantReleasePluginError        = '!Rel';
inline constexpr auto kSPPluginAlreadyReleaseError     = 'AlRl';

inline constexpr auto kSPAdapterAlreadyExistsError     = 'AdEx';
inline constexpr auto kSPBadAdapterListIteratorError   = 'BdAL';

inline constexpr auto kSPBadParameterError             = 'Parm';

inline constexpr auto kSPCantChangeBlockDebugNowError  = '!Now';
inline constexpr auto kSPBlockDebugNotEnabledError     = '!Nbl';

inline constexpr auto kSPOutOfMemoryError              = 0xFFFFFF6cL;
inline constexpr auto kSPBlockSizeOutOfRangeError      = 'BkRg';

inline constexpr auto kSPPluginCachesFlushResponse     = 'pFls';
inline constexpr auto kSPPluginCouldntFlushResponse    = kSPNoError;

inline constexpr auto kSPTroubleAddingFilesError       = 'TAdd';
inline constexpr auto kSPBadFileListIteratorError      = 'BFIt';

inline constexpr auto kSPTroubleInitializingError      = 'TIni';
inline constexpr auto kHostCanceledStartupPluginsError = 'H!St';

inline constexpr auto kSPNotASweerPerPluginError       = 'NSPP';
inline constexpr auto kSPAlreadyInSPCallerError        = 'AISC';

inline constexpr auto kSPUnknownAdapterError           = '?Adp';
inline constexpr auto kSPBadPluginListIteratorError    = 'PiLI';
inline constexpr auto kSPBadPluginHost                 = 'PiH0';
inline constexpr auto kSPCantAddHostPluginError        = 'AdHo';
inline constexpr auto kSPPluginNotFound                = 'P!Fd';
inline constexpr auto kSPCorruptPiPLError              = 'CPPL';
inline constexpr auto kSPBadPropertyListIteratorError  = 'BPrI';

inline constexpr auto kSPSuiteNotFoundError            = 'S!Fd';
inline constexpr auto kSPSuiteAlreadyExistsError       = 'SExi';
inline constexpr auto kSPSuiteAlreadyReleasedError     = 'SRel';
inline constexpr auto kSPBadSuiteListIteratorError     = 'SLIt';
inline constexpr auto kSPBaduiteInternalVersionError   = 'SIVs';

}
