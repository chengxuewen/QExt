#ifndef _QEXTUTILSGLOBAL_H
#define _QEXTUTILSGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_UTILS_LIB // defined if we are building the lib
        #define QEXT_UTILS_API Q_DECL_EXPORT
    #else
        #define QEXT_UTILS_API Q_DECL_IMPORT
    #endif
    #define QEXT_UTILS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_UTILS_API
    #define QEXT_UTILS_HIDDEN
#endif

#endif // _QEXTUTILSGLOBAL_H
