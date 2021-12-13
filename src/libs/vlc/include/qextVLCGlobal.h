#ifndef _QEXTVLCGLOBAL_H
#define _QEXTVLCGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_VLC_LIB // defined if we are building the lib
        #define QEXT_VLC_API Q_DECL_EXPORT
    #else
        #define QEXT_VLC_API Q_DECL_IMPORT
    #endif
    #define QEXT_VLC_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_VLC_API
    #define QEXT_VLC_HIDDEN
#endif

#endif // _QEXTVLCGLOBAL_H
