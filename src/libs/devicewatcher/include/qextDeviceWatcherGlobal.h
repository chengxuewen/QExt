#ifndef _QEXTDEVICEWATCHERGLOBAL_H
#define _QEXTDEVICEWATCHERGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_DEVICEWATCHER_LIB // defined if we are building the lib
        #define QEXT_DEVICEWATCHER_API Q_DECL_EXPORT
    #else
        #define QEXT_DEVICEWATCHER_API Q_DECL_IMPORT
    #endif
    #define QEXT_DEVICEWATCHER_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_DEVICEWATCHER_API
    #define QEXT_DEVICEWATCHER_HIDDEN
#endif

#endif // _QEXTDEVICEWATCHERGLOBAL_H
