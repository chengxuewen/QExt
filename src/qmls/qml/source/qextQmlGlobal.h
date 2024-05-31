#ifndef _QEXTQMLGLOBAL_H
#define _QEXTQMLGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_QML_LIB    // defined if we are building the lib
#       define QEXT_QML_API QEXT_DECL_EXPORT
#   else
#       define QEXT_QML_API Q_DECL_IMPORT
#   endif
#   define QEXT_QML_HIDDEN QEXT_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_QML_API
#   define QEXT_QML_HIDDEN
#endif

#endif // _QEXTQMLGLOBAL_H
