#ifndef _QEXTPLOTGLOBAL_H
#define _QEXTPLOTGLOBAL_H

#include <qextGlobal.h>
#include <qextPlotConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_PLOT_LIB // defined if we are building the lib
#       define QEXT_PLOT_API Q_DECL_EXPORT
#   else
#       define QEXT_PLOT_API Q_DECL_IMPORT
#   endif
#   define QEXT_PLOT_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_PLOT_API
#   define QEXT_PLOT_HIDDEN
#endif

#endif // _QEXTPLOTGLOBAL_H
