#pragma once

#ifdef __APPLE_CC__
#   include "TargetConditionals.h"
#   if TARGET_OS_MAC
#       if TARGET_OS_IPHONE
#           if TARGET_OS_IOS || !defined(TARGET_OS_IOS)
#               ifndef IOS_ENV
#                   define IOS_ENV 1
#               endif
#           endif
#       else
#           ifndef MAC_ENV
#               define MAC_ENV 1
#           endif
#       endif
#   endif
#endif

#ifdef __ANDROID__
#   ifndef ANDROID_ENV
#       define ANDROID_ENV 1
#   endif
#endif

#ifdef __MWERKS__
#   ifdef __INTEL__
#       ifndef WIN_ENV
#           define WIN_ENV 1
#           include <x86_prefix.h>
#       endif
#   else
#       ifndef MAC_ENV
#           define MAC_ENV 1
#       endif
#   endif
#endif

#if defined(_WINDOWS_) || defined(_MSC_VER) || defined(WINDOWS)
#   ifndef WIN_ENV
#       define WIN_ENV 1
#   endif
#endif


#if !(defined(WIN_ENV) || defined(MAC_ENV) || defined(IOS_ENV) || defined(ANDROID_ENV))
#   error ""
#endif

#if defined(WIN_ENV) && defined(MAC_ENV)
#   error ""
#endif
