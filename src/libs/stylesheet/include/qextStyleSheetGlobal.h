#ifndef _QEXTSTYLESHEETGLOBAL_H
#define _QEXTSTYLESHEETGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_STYLESHEET_LIB // defined if we are building the lib
        #define QEXT_STYLESHEET_API Q_DECL_EXPORT
    #else
        #define QEXT_STYLESHEET_API Q_DECL_IMPORT
    #endif
    #define QEXT_STYLESHEET_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_STYLESHEET_API
    #define QEXT_STYLESHEET_HIDDEN
#endif

#endif // _QEXTSTYLESHEETGLOBAL_H
