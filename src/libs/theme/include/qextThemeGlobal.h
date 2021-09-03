#ifndef QEXTTHEMEGLOBAL_H
#define QEXTTHEMEGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_THEME_LIB // defined if we are building the lib
        #define QEXT_THEME_API Q_DECL_EXPORT
    #else
        #define QEXT_THEME_API Q_DECL_IMPORT
    #endif
    #define QEXT_THEME_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_THEME_API
    #define QEXT_THEME_HIDDEN
#endif

#endif // QEXTTHEMEGLOBAL_H
