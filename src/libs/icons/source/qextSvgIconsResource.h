//
// Created by cxw on 2024/1/11.
//

#ifndef _QEXTSVGICONSRESOURCE_H
#define _QEXTSVGICONSRESOURCE_H

#include <qextIconsGlobal.h>

#include <QObject>
#include <QMetaEnum>

class QExtSvgIconsResource : public QObject
{
Q_OBJECT
public:
    enum StyleEnum
    {
        Style_Filled = 0,
        Style_Rounded
    };
    Q_ENUM(StyleEnum);

    enum IconEnum
    {
        Icon_arrows_caret_back,
        Icon_arrows_caret_collapse,
        Icon_arrows_caret_expand,
        Icon_arrows_caret_forward,
    };
    Q_ENUM(IconEnum);

    explicit QExtSvgIconsResource(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}

    static QString svgResource(IconEnum icon, StyleEnum style = Style_Filled, bool isUrl = false);

    static QString svgUrl(IconEnum icon, StyleEnum style)
    {
        return QExtSvgIconsResource::svgResource(icon, style, true);
    }
    static QString svgPath(IconEnum icon, StyleEnum style)
    {
        return QExtSvgIconsResource::svgResource(icon, style, true);
    }
    static QMetaEnum iconMetaEnum() { return QMetaEnum::fromType<IconEnum>(); };

    static const char *styleEnumString(int style);
};

#endif //_QEXTSVGICONSRESOURCE_H
