#ifndef _QEXTQMLFRAMELESSHELPERPLUGIN_H
#define _QEXTQMLFRAMELESSHELPERPLUGIN_H

#include <qextQmlFramelessHelperGlobal.h>

#include <QQmlExtensionPlugin>

class QEXT_QMLFRAMELESSHELPER_API QEXTQmlFramelessHelperPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.QEXT.QEXTQmlFramelessHelperPlugin")

public:
    // QQmlExtensionInterface interface
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // _QEXTQMLFRAMELESSHELPERPLUGIN_H
