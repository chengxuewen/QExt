#ifndef _QEXTQUICKPLUGIN_H
#define _QEXTQUICKPLUGIN_H

#include <qextQuickGlobal.h>

#include <QQmlExtensionPlugin>

class QEXT_QUICK_API QEXTQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.QEXT.QEXTQuickPlugin")

public:
    // QQmlExtensionInterface interface
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // _QEXTQUICKPLUGIN_H
