#ifndef _QEXTPINYINGLOBAL_H
#define _QEXTPINYINGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_PINYIN_LIB // defined if we are building the lib
#       define QEXT_PINYIN_API Q_DECL_EXPORT
#   else
#       define QEXT_PINYIN_API Q_DECL_IMPORT
#   endif
#   define QEXT_FONTAWESOME_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_PINYIN_API
#   define QEXT_PINYIN_HIDDEN
#endif

#endif // _QEXTPINYINGLOBAL_H
