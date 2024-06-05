#include <qextQuickControls.h>

#include <QObject>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class QExtQuickControlsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    // QQmlExtensionInterface interface
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};


void QExtQuickControlsPlugin::registerTypes(const char *uri)
{
    QExtQuickControls::instance()->registerTypes(uri);
}

void QExtQuickControlsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QExtQuickControls::instance()->initQmlEngine(engine, uri);
}

#include <qextQuickControlsPlugin.moc>
