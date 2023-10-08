#ifndef _QEXTSTYLETHEMESGLOBAL_H
#define _QEXTSTYLETHEMESGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_STYLETHEMES_LIB // defined if we are building the lib
        #define QEXT_STYLETHEMS_API Q_DECL_EXPORT
    #else
        #define QEXT_STYLETHEMS_API Q_DECL_IMPORT
    #endif
    #define QEXT_STYLETHEMS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_STYLETHEMS_API
    #define QEXT_STYLETHEMS_HIDDEN
#endif


// Define ACSS_DEBUG_PRINT to enable a lot of debug output
#ifdef ACSS_DEBUG_PRINT
#define ACSS_PRINT(s) qDebug() << s
#else
#define ACSS_PRINT(s)
#endif

// Set ACSS_DEBUG_LEVEL to enable additional debug output and to enable layout
// dumps to qDebug and std::cout after layout changes
#define ACSS_DEBUG_LEVEL 0

#endif // _QEXTSTYLETHEMESGLOBAL_H
