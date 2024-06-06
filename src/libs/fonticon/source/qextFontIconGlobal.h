#ifndef _QEXTFONTICONGLOBAL_H
#define _QEXTFONTICONGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_FONTICON_LIB // defined if we are building the lib
#       define QEXT_FONTICON_API Q_DECL_EXPORT
#   else
#       define QEXT_FONTICON_API Q_DECL_IMPORT
#   endif
#   define QEXT_FONTICON_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_FONTICON_API
#   define QEXT_FONTICON_HIDDEN
#endif

#endif // _QEXTFONTICONGLOBAL_H
