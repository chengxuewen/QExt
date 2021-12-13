#ifndef _QEXTQMLVLCLOADER_H
#define _QEXTQMLVLCLOADER_H

#include <qextQmlVLCGlobal.h>

#include <QQmlEngine>

class QEXT_QMLVLC_API QEXTQmlVLCLoader
{
public:
    static void load(QQmlEngine *engine);

    static void registerTypes(const char *uri);
    static void initQmlEngine(QQmlEngine *engine, const char *uri);

    static QString version();
};

#endif // _QEXTQMLVLCLOADER_H
