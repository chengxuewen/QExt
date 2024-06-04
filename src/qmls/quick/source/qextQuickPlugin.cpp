#include <qextQuick.h>
#include <qextQuickConfig.h>

#include <QObject>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>


class QExtQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.QExt.QExtQuickPlugin")
public:
    // QQmlExtensionInterface interface
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};


void QExtQuickPlugin::registerTypes(const char *uri)
{
    QExtQuick::instance()->registerTypes(uri);
}

void QExtQuickPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QExtQuick::instance()->initQmlEngine(engine, uri);
}

#include <qextQuickPlugin.moc>
