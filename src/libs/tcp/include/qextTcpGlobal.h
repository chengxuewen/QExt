#ifndef _QEXTTCPGLOBAL_H
#define _QEXTTCPGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_TCP_LIB // defined if we are building the lib
        #define QEXT_TCP_API Q_DECL_EXPORT
    #else
        #define QEXT_TCP_API Q_DECL_IMPORT
    #endif
    #define QEXT_TCP_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_TCP_API
    #define QEXT_TCP_HIDDEN
#endif

#endif // _QEXTTCPGLOBAL_H
