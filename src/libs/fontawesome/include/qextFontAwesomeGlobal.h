#ifndef QEXTFONTAWESOMEGLOBAL_H
#define QEXTFONTAWESOMEGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_FONTAWESOME_LIB // defined if we are building the lib
        #define QEXT_FONTAWESOME_API Q_DECL_EXPORT
    #else
        #define QEXT_FONTAWESOME_API Q_DECL_IMPORT
    #endif
    #define QEXT_FONTAWESOME_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_FONTAWESOME_API
    #define QEXT_FONTAWESOME_HIDDEN
#endif

#endif // QEXTFONTAWESOMEGLOBAL_H
