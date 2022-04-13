#ifndef AECONFIG_H
#define AECONFIG_H

#if defined(_WIN32)
#   define AE_OS_WIN

#elif defined(__GNUC__) && defined(__MACH__)
#   include "TargetConditionals.h"
#   if TARGET_OS_MAC
#       if TARGET_OS_IPHONE
#           if TAEGET_OS_IOS || !defined(TARGET_OS_IOS)
#               define AE_OS_IOS
#           endif
#       else
#           define AE_OS_MAC
#       endif

#       if TARGET_OS_SIMURATOR
#           define AE_OS_APPLE_SIM
#       endif
#   endif // if TARGET_OS_MAC

#elif Rez
#   define AE_OS_MAC

#elif defined(__ANDROID__)
#   define AE_OS_ANDROID

#else
#error "unrecognized AE platform"

#endif


#if defined(__i386__) || defined(_M_IX86)
#   define AE_PROC_INTEL
#elif defined(_M_X64) || defined(__amd64__) || defined(__x86_64__)
#   define AE_PROC_INTELx64
#elif defined(__arm64__) || defined(__aarch64__)
#   define AE_PROC_ARM64
#else
#   error "unrecognized AE platform"
#endif


#define AE_LITTLE_ENDIAN

#endif // ifndef AECONFIG_H
