#ifndef _QEXTMAPGLOBAL_H
#define _QEXTMAPGLOBAL_H

#include <qextGlobal.h>
#include <qextMapConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_MAP_LIB // defined if we are building the lib
#       define QEXT_MAP_API Q_DECL_EXPORT
#   else
#       define QEXT_MAP_API Q_DECL_IMPORT
#   endif
#   define QEXT_MAP_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_MAP_API
#   define QEXT_MAP_HIDDEN
#endif

#endif // _QEXTMAPGLOBAL_H
