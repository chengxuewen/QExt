#ifndef _QEXTQMLFRAMELESSHELPERLOADER_H
#define _QEXTQMLFRAMELESSHELPERLOADER_H

#include <qextQmlFramelessHelperGlobal.h>

#include <QQmlEngine>

class QEXT_QMLFRAMELESSHELPER_API QEXTQmlFramelessHelperLoader
{
public:
    static void load(QQmlEngine *engine);

    static void registerTypes(const char *uri);
    static void initQmlEngine(QQmlEngine *engine, const char *uri);

    static QString version();
};

#endif // _QEXTQMLFRAMELESSHELPERLOADER_H
