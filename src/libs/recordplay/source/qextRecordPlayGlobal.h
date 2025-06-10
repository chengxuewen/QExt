#ifndef _QEXTRECORDERPLAYGLOBAL_H
#define _QEXTRECORDERPLAYGLOBAL_H

#include <qextGlobal.h>
#include <qextRecordPlayConfig.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_RECORDPLAY_LIB // defined if we are building the lib
#       define QEXT_RECORDPLAY_API Q_DECL_EXPORT
#   else
#       define QEXT_RECORDPLAY_API Q_DECL_IMPORT
#   endif
#   define QEXT_RECORDPLAY_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_RECORDPLAY_API
#   define QEXT_RECORDPLAY_HIDDEN
#endif

#endif // _QEXTRECORDERPLAYGLOBAL_H
