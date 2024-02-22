#ifndef _QEXTPATTERNSGLOBAL_H
#define _QEXTPATTERNSGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_PATTERN_LIB // defined if we are building the lib
#       define QEXT_PATTERNS_API Q_DECL_EXPORT
#   else
#       define QEXT_PATTERNS_API Q_DECL_IMPORT
#   endif
#   define QEXT_PATTERNS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_PATTERNS_API
#   define QEXT_PATTERNS_HIDDEN
#endif

#endif // _QEXTPATTERNSGLOBAL_H
