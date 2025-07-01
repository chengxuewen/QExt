#ifndef _QEXTLOGGINGGLOBAL_H
#define _QEXTLOGGINGGLOBAL_H

#include <qextGlobal.h>
#include <qextLoggingConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_LOGGING_LIB // defined if we are building the lib
#       define QEXT_LOGGING_API Q_DECL_EXPORT
#   else
#       define QEXT_LOGGING_API Q_DECL_IMPORT
#   endif
#   define QEXT_LOGGING_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_LOGGING_API
#   define QEXT_LOGGING_HIDDEN
#endif

#define QEXT_LOGGING_VERSION_STRING QEXT_VERSION_NAME
#define QEXT_LOGGING_VERSION_MAJOR QEXT_VERSION_MAJOR
#define QEXT_LOGGING_VERSION_MINOR QEXT_VERSION_MINOR
#define QEXT_LOGGING_VERSION_PATCH QEXT_VERSION_PATCH

#if QT_VERSION < QT_VERSION_CHECK(5, 12, 0)
#   error "QExtLogging requires Qt version 5.12.0 or higher"
#endif

#if (defined(Q_CC_MSVC) && _MSC_VER < 1900)
#   error "QExtLogging requires at least msvc version 14 (VS2015) or higher for used c++11 features"
#endif

#if (!defined(Q_CC_CLANG) && defined(Q_CC_GNU) && Q_CC_GNU < 408)
#   error "QExtLogging requires at least gcc version 4.8 or higher for used c++11 features"
#endif

#if (defined(Q_CC_CLANG) && Q_CC_CLANG < 303)
#   error "QExtLogging requires at least clang version 3.3 or higher for used c++11 features"
#endif

/*
   can be used like #if (QEXT_LOGGING_VERSION >= QEXT_LOGGING_VERSION_CHECK(1, 3, 0))
*/
#define QEXT_LOGGING_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

/*
   QEXT_LOGGING_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define QEXT_LOGGING_VERSION QEXT_LOGGING_VERSION_CHECK(QEXT_LOGGING_VERSION_MAJOR, QEXT_LOGGING_VERSION_MINOR, QEXT_LOGGING_VERSION_PATCH)

#endif // _QEXTLOGGINGGLOBAL_H
