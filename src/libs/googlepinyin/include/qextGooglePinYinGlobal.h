#ifndef _QEXTGOOGLEPINYINGLOBAL_H
#define _QEXTGOOGLEPINYINGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_GOOGLEPINYIN_LIB // defined if we are building the lib
        #define QEXT_GOOGLEPINYIN_API Q_DECL_EXPORT
    #else
        #define QEXT_GOOGLEPINYIN_API Q_DECL_IMPORT
    #endif
    #define QEXT_FONTAWESOME_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_GOOGLEPINYIN_API
    #define QEXT_GOOGLEPINYIN_HIDDEN
#endif

#endif // _QEXTGOOGLEPINYINGLOBAL_H
