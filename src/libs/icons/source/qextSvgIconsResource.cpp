//
// Created by cxw on 2024/1/11.
//

#include <qextSvgIconsResource.h>

#include <QDebug>

QString QExtSvgIconsResource::svgResource(QExtSvgIconsResource::IconEnum icon, StyleEnum style, bool isUrl)
{
    Q_INIT_RESOURCE(qextIcons);
    static QMetaEnum metaEnum = QMetaEnum::fromType<IconEnum>();
    QString iconEnumString = metaEnum.valueToKey(icon);
    const QStringList split = iconEnumString.split("_");
    if (split.size() >= 4)
    {
        const QString prefix = QString("%1_%2_%3_").arg(split.at(0)).arg(split.at(1)).arg(split.at(2));
        const QString iconName = iconEnumString.remove(prefix);
        return QString("%1:/QExtIcons/svgs/%2/%3/%4_%5.svg")
            .arg(isUrl ? "qrc" : "").arg(split.at(1)).arg(split.at(2)).arg(iconName)
            .arg(QExtSvgIconsResource::styleEnumString(style));
    }
    qWarning() << QString("QExtSvgIconsResource svgResource %1 parse failed!").arg(iconEnumString);
    return "";
}

const char *QExtSvgIconsResource::styleEnumString(int style)
{
    switch (style)
    {
    case Style_Filled:
        return "filled";
    case Style_Rounded:
        return "rounded";
    default:
        return "";
    }
    return "";
}
