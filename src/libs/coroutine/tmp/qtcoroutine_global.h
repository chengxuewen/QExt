#ifndef QTCOROUTINE_GLOBAL_H
#define QTCOROUTINE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <qextglobal.h>

#ifdef QEXT_BUILD_SHARED_LIBS
#   ifdef QEXT_BUILD_COROUTINE_LIB
#       define QTCOROUTINE_EXPORT Q_DECL_EXPORT
#   else
#       define QTCOROUTINE_EXPORT Q_DECL_IMPORT
#   endif
#else
#   define QTCOROUTINE_EXPORT
#endif

#endif // QTCOROUTINE_GLOBAL_H
