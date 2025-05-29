#ifndef _QEXTLUAGLOBAL_H
#define _QEXTLUAGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_LUA_LIB // defined if we are building the lib
#       define QEXT_LUA_API Q_DECL_EXPORT
#   else
#       define QEXT_LUA_API Q_DECL_IMPORT
#   endif
#   define QEXT_LUA_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_LUA_API
#   define QEXT_LUA_HIDDEN
#endif

#endif // _QEXTLUAGLOBAL_H
