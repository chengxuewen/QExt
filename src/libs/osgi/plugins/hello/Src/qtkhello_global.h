#ifndef QTKHELLO_GLOBAL_H
#define QTKHELLO_GLOBAL_H

#include <qglobal.h>
#include <QLoggingCategory>

#if defined(QTK_HELLO_LIBRARY)
#  define QTK_HELLO_EXPORT Q_DECL_EXPORT
#else
#  define QTK_HELLO_EXPORT Q_DECL_IMPORT
#endif

#endif // QTKHELLO_GLOBAL_H
