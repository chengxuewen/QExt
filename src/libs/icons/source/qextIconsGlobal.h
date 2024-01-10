#ifndef _QEXTICONSGLOBAL_H
#define _QEXTICONSGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_ICONS_LIB // defined if we are building the lib
#       define QEXT_ICONS_API Q_DECL_EXPORT
#   else
#       define QEXT_ICONS_API Q_DECL_IMPORT
#   endif
#   define QEXT_ICONS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_ICONS_API
#   define QEXT_ICONS_HIDDEN
#endif

#endif // _QEXTICONSGLOBAL_H
