
#include <qextIconsResource.h>

void QExtIconsResource::initResource()
{
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextIcons);
        onceFlag.leave();
    }
}

QString QExtIconsResource::resource(const QString &style, const QString &iconName, bool isUrl)
{
    QExtIconsResource::initResource();
    return QString("%1:/QExtIcons/%2/%3.svg").arg(isUrl ? "qrc" : "").arg(style).arg(iconName);
}
