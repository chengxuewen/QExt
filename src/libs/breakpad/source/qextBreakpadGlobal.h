#ifndef _QEXTBREAKPADGLOBAL_H
#define _QEXTBREAKPADGLOBAL_H

#include <qextGlobal.h>
#include <qextBreakpadConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_BREAKPAD_LIB // defined if we are building the lib
#       define QEXT_BREAKPAD_API Q_DECL_EXPORT
#   else
#       define QEXT_BREAKPAD_API Q_DECL_IMPORT
#   endif
#   define QEXT_BREAKPAD_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_BREAKPAD_API
#   define QEXT_BREAKPAD_HIDDEN
#endif

#endif // _QEXTBREAKPADGLOBAL_H
