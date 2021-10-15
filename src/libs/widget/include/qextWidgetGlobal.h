#ifndef _QEXTWIDGETGLOBAL_H
#define _QEXTWIDGETGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_WIDGET_LIB // defined if we are building the lib
        #define QEXT_WIDGET_API Q_DECL_EXPORT
    #else
        #define QEXT_WIDGET_API Q_DECL_IMPORT
    #endif
    #define QEXT_WIDGET_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_WIDGET_API
    #define QEXT_WIDGET_HIDDEN
#endif

#endif // _QEXTWIDGETGLOBAL_H
