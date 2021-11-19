#ifndef _QEXTSTYLETHEMEGLOBAL_H
#define _QEXTSTYLETHEMEGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_STYLETHEME_LIB // defined if we are building the lib
        #define QEXT_STYLETHEM_API Q_DECL_EXPORT
    #else
        #define QEXT_STYLETHEM_API Q_DECL_IMPORT
    #endif
    #define QEXT_STYLETHEM_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_STYLETHEM_API
    #define QEXT_STYLETHEM_HIDDEN
#endif

#endif // _QEXTSTYLETHEMEGLOBAL_H
