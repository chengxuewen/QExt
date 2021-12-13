#ifndef _QEXTQMLTHEMEGLOBAL_H
#define _QEXTQMLTHEMEGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_QMLTHEME_LIB // defined if we are building the lib
        #define QEXT_QMLTHEME_API Q_DECL_EXPORT
    #else
        #define QEXT_QMLTHEME_API Q_DECL_IMPORT
    #endif
    #define QEXT_QMLTHEME_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_QMLTHEME_API
    #define QEXT_QMLTHEME_HIDDEN
#endif

#endif // _QEXTQMLTHEMEGLOBAL_H
