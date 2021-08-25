#ifndef QEXTSERIALPORTGLOBAL_H
#define QEXTSERIALPORTGLOBAL_H

#include <qextglobal.h>

/********************************************************************************
   QEXT Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED_LIBS // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_SERIALPORT_LIB // defined if we are building the lib
#       define QEXT_SERIALPORT_API Q_DECL_EXPORT
#   else
#       define QEXT_SERIALPORT_API Q_DECL_IMPORT
#   endif
#   define QEXT_SERIALPORT_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_SERIALPORT_API
#   define QEXT_SERIALPORT_HIDDEN
#endif

#endif // QEXTSERIALPORTGLOBAL_H
