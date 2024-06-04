#ifndef TOOU2D_H
#define TOOU2D_H

#include <QQmlEngine>

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_TOOU2D_LIB    // defined if we are building the lib
#       define QEXT_TOOU2D_API QEXT_DECL_EXPORT
#   else
#       define QEXT_TOOU2D_API Q_DECL_IMPORT
#   endif
#   define QEXT_TOOU2D_HIDDEN QEXT_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_TOOU2D_API
#   define QEXT_TOOU2D_HIDDEN
#endif

class QEXT_TOOU2D_API Toou2D
{
public:
    static void create(QQmlEngine* engine);
    static QString version();
};

#endif // TOOU2D_H
