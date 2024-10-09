#ifndef _QEXTRPCGLOBAL_H
#define _QEXTRPCGLOBAL_H

#include <qextGlobal.h>

#include <QColor>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_RPC_LIB // defined if we are building the lib
#       define QEXT_RPC_API Q_DECL_EXPORT
#   else
#       define QEXT_RPC_API Q_DECL_IMPORT
#   endif
#   define QEXT_RPC_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_RPC_API
#   define QEXT_RPC_HIDDEN
#endif

#endif // _QEXTRPCGLOBAL_H
