#ifndef _QEXTGRAPHICSGLOBAL_H
#define _QEXTGRAPHICSGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_GRAPHICS_LIB // defined if we are building the lib
#       define QEXT_GRAPHICS_API Q_DECL_EXPORT
#   else
#       define QEXT_GRAPHICS_API Q_DECL_IMPORT
#   endif
#   define QEXT_GRAPHICS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_GRAPHICS_API
#   define QEXT_GRAPHICS_HIDDEN
#endif

#endif // _QEXTGRAPHICSGLOBAL_H
