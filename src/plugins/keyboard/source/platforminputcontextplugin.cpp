#include "platforminputcontextplugin.h"
#include <private/qextKeyboardInputContext_p.h>
#include <QDebug>

QPlatformInputContext *PlatformInputContextPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    if (key.compare(key, QStringLiteral("QExtKeyboard"), Qt::CaseInsensitive) == 0)
    {
        qDebug() << "call QExtKeyboard success!";
        return new InputContext;
    }

    return NULL;
}
