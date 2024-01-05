#ifndef _QEXTCOMPONENTSGLOBAL_H
#define _QEXTCOMPONENTSGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_COMPONENTS_LIB // defined if we are building the lib
#       define QEXT_COMPONENTS_API Q_DECL_EXPORT
#   else
#       define QEXT_COMPONENTS_API Q_DECL_IMPORT
#   endif
#   define QEXT_COMPONENTS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_COMPONENTS_API
#   define QEXT_COMPONENTS_HIDDEN
#endif

#endif // _QEXTCOMPONENTSGLOBAL_H
