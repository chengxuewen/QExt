#ifndef _QEXTQMLVLCPLUGIN_H
#define _QEXTQMLVLCPLUGIN_H

#include <qextQmlVLCGlobal.h>

#include <QQmlExtensionPlugin>

class QEXT_QMLVLC_API QEXTQmlVLCPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.QExt.QEXTQmlVLCPlugin")

public:
    // QQmlExtensionInterface interface
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // _QEXTQMLVLCPLUGIN_H
