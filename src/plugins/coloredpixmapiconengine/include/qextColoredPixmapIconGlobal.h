#ifndef _QEXTCOLOREDPIXMAPICONGLOBAL_H
#define _QEXTCOLOREDPIXMAPICONGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_COLOREDPIXMAPICON_LIB // defined if we are building the lib
        #define QEXT_COLOREDPIXMAPICON_API Q_DECL_EXPORT
    #else
        #define QEXT_COLOREDPIXMAPICON_API Q_DECL_IMPORT
    #endif
    #define QEXT_COLOREDPIXMAPICON_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_COLOREDPIXMAPICON_API
    #define QEXT_COLOREDPIXMAPICON_HIDDEN
#endif

#endif // _QEXTCOLOREDPIXMAPICONGLOBAL_H
