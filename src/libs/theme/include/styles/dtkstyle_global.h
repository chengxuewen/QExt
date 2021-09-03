#ifndef DTKSTYLE_GLOBAL_H
#define DTKSTYLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DTK_STYLE_LIBRARY)
#  define DTK_STYLE_EXPORT Q_DECL_EXPORT
#else
#  define DTK_STYLE_EXPORT Q_DECL_IMPORT
#endif

#endif // DTKSTYLE_GLOBAL_H
