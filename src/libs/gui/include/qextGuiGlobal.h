#ifndef _QEXTGUIGLOBAL_H
#define _QEXTGUIGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_GUI_LIB // defined if we are building the lib
        #define QEXT_GUI_API QEXT_DECL_EXPORT
    #else
        #define QEXT_GUI_API QEXT_DECL_IMPORT
    #endif
    #define QEXT_GUI_HIDDEN QEXT_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_GUI_API
    #define QEXT_GUI_HIDDEN
#endif

#endif // _QEXTGUIGLOBAL_H
