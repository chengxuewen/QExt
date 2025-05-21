#ifndef _QEXTDAVIEWGLOBAL_H
#define _QEXTDAVIEWGLOBAL_H

#include <qextGlobal.h>
#include <qextPlotConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_DAVIEW_LIB // defined if we are building the lib
#       define QEXT_DAVIEW_API Q_DECL_EXPORT
#   else
#       define QEXT_DAVIEW_API Q_DECL_IMPORT
#   endif
#   define QEXT_DAVIEW_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_DAVIEW_API
#   define QEXT_DAVIEW_HIDDEN
#endif

#endif // _QEXTDAVIEWGLOBAL_H
