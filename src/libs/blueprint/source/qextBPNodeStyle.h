#ifndef _QEXTBPNODESTYLE_H
#define _QEXTBPNODESTYLE_H

#include <qextBlueprintGlobal.h>
#include <qextBPStyle.h>

#include <QColor>

class QEXT_BLUEPRINT_API QExtBPNodeStyle : public QExtBPStyle
{
public:
    QExtBPNodeStyle();

    QExtBPNodeStyle(QString jsonText);

    QExtBPNodeStyle(const QJsonObject &json);

    virtual ~QExtBPNodeStyle() = default;

    static void setNodeStyle(QString jsonText);

    void loadJson(const QJsonObject &json) override;

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

#endif // _QEXTBPNODESTYLE_H

