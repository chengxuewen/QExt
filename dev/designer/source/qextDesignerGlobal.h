#ifndef _QEXTDESIGNERGLOBAL_H
#define _QEXTDESIGNERGLOBAL_H

#include <qextGlobal.h>
#include <qextMemory.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_DESIGNER_LIB // defined if we are building the lib
#       define QEXT_DESIGNER_API Q_DECL_EXPORT
#   else
#       define QEXT_DESIGNER_API Q_DECL_IMPORT
#   endif
#   define QEXT_DESIGNER_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_DESIGNER_API
#   define QEXT_DESIGNER_HIDDEN
#endif

#endif // _QEXTDESIGNERGLOBAL_H
