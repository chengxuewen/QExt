#ifndef _QEXTKEYBOARDGLOBAL_H
#define _QEXTKEYBOARDGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_KEYBOARD_LIB // defined if we are building the lib
#       define QEXT_KEYBOARD_API Q_DECL_EXPORT
#   else
#       define QEXT_KEYBOARD_API Q_DECL_IMPORT
#   endif
#   define QEXT_KEYBOARD_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_KEYBOARD_API
#   define QEXT_KEYBOARD_HIDDEN
#endif

QT_USE_NAMESPACE

#endif // _QEXTKEYBOARDGLOBAL_H
