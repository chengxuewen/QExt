#ifndef QEXTCONTROLGLOBAL_H
#define QEXTCONTROLGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
# ifdef QEXT_BUILD_CONTROL_LIB // defined if we are building the lib
#  define QEXT_CONTROL_API Q_DECL_EXPORT
# else
#  define QEXT_CONTROL_API Q_DECL_IMPORT
# endif
# define QEXT_CONTROL_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
# define QEXT_CONTROL_API
# define QEXT_CONTROL_HIDDEN
#endif

#endif // QEXTCONTROLGLOBAL_H
