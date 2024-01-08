#ifndef _QEXTQUICKGLOBAL_H
#define _QEXTQUICKGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_QUICK_LIB // defined if we are building the lib
#       define QEXT_QUICK_API Q_DECL_EXPORT
#   else
#       define QEXT_QUICK_API Q_DECL_IMPORT
#   endif
#   define QEXT_QUICK_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_QUICK_API
#   define QEXT_QUICK_HIDDEN
#endif

#endif // _QEXTQUICKGLOBAL_H
