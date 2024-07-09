#pragma once

#include <QtGui/QColor>

#include <qextBlueprintGlobal.h>
#include "Style.hpp"

class QEXT_BLUEPRINT_API QExtBPNodeStyle : public QExtBPStyle
{
public:
    QExtBPNodeStyle();

    QExtBPNodeStyle(QString jsonText);

    QExtBPNodeStyle(QJsonObject const &json);

    virtual ~QExtBPNodeStyle() = default;

public:
    static void setNodeStyle(QString jsonText);

public:
    void loadJson(QJsonObject const &json) override;

    QJsonObject toJson() const override;

public:
    QColor NormalBoundaryColor;
    QColor SelectedBoundaryColor;
    QColor GradientColor0;
    QColor GradientColor1;
    QColor GradientColor2;
    QColor GradientColor3;
    QColor ShadowColor;
    QColor FontColor;
    QColor FontColorFaded;

    QColor ConnectionPointColor;
    QColor FilledConnectionPointColor;

    QColor WarningColor;
    QColor ErrorColor;

    float PenWidth;
    float HoveredPenWidth;

    float ConnectionPointDiameter;

    float Opacity;
};
