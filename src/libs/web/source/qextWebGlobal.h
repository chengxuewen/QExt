#ifndef _QEXTWEBGLOBAL_H
#define _QEXTWEBGLOBAL_H

#include <qextGlobal.h>

#include <QColor>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_WEB_LIB // defined if we are building the lib
#       define QEXT_WEB_API Q_DECL_EXPORT
#   else
#       define QEXT_WEB_API Q_DECL_IMPORT
#   endif
#   define QEXT_WEB_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_WEB_API
#   define QEXT_WEB_HIDDEN
#endif

#endif // _QEXTWEBGLOBAL_H
