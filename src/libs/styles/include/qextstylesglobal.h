#ifndef QEXTSTYLESGLOBAL_H
#define QEXTSTYLESGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
# ifdef QEXT_BUILD_STYLES_LIB // defined if we are building the lib
#  define QEXT_STYLES_API Q_DECL_EXPORT
# else
#  define QEXT_STYLES_API Q_DECL_IMPORT
# endif
# define QEXT_STYLES_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
# define QEXT_STYLES_API
# define QEXT_STYLES_HIDDEN
#endif

#endif // QEXTSTYLESGLOBAL_H
