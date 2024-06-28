#include <private/qextKeyboardInputContext_p.h>
#include <qpa/qplatforminputcontextplugin_p.h>
#include <QDebug>

class  QExtKeyboardInputContextPlugin: public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "QExtKeyboard.json")
public:
    QPlatformInputContext *create(const QString& key, const QStringList &paramList);
};

QPlatformInputContext *QExtKeyboardInputContextPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    if (key.compare(key, QStringLiteral("QExtKeyboard"), Qt::CaseInsensitive) == 0)
    {
        qDebug() << "QExtKeyboard Plugin load success!";
        return new QExtKeyboardInputContext;
    }
    return NULL;
}

#include <qextKeyboardInputContextPlugin.moc>
