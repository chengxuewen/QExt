#ifndef QEXTMESSAGEGLOBAL_H
#define QEXTMESSAGEGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_MESSAGE_LIB // defined if we are building the lib
#       define QEXT_MESSAGE_API Q_DECL_EXPORT
#   else
#       define QEXT_MESSAGE_API Q_DECL_IMPORT
#   endif
#   define QEXT_MESSAGE_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_MESSAGE_API
#   define QEXT_MESSAGE_HIDDEN
#endif

#endif // QEXTMESSAGEGLOBAL_H
