#ifndef _QEXTQMLVLCGLOBAL_H
#define _QEXTQMLVLCGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_QMLVLC_LIB // defined if we are building the lib
        #define QEXT_QMLVLC_API Q_DECL_EXPORT
    #else
        #define QEXT_QMLVLC_API Q_DECL_IMPORT
    #endif
    #define QEXT_QMLVLC_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_QMLVLC_API
    #define QEXT_QMLVLC_HIDDEN
#endif

#endif // _QEXTQMLVLCGLOBAL_H
