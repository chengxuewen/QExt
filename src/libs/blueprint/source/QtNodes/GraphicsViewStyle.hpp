#pragma once

#include <QtGui/QColor>

#include <qextBlueprintGlobal.h>
#include "Style.hpp"

class QEXT_BLUEPRINT_API QExtBPGraphicsViewStyle : public QExtBPStyle
{
public:
    QExtBPGraphicsViewStyle();

    QExtBPGraphicsViewStyle(QString jsonText);

    ~QExtBPGraphicsViewStyle() = default;

public:
    static void setStyle(QString jsonText);

private:
    void loadJson(QJsonObject const &json) override;

    QJsonObject toJson() const override;

public:
    QColor BackgroundColor;
    QColor FineGridColor;
    QColor CoarseGridColor;
};
