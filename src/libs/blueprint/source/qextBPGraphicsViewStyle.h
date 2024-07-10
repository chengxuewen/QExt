#ifndef _QEXTBPGRAPHICSVIEWSTYLE_H
#define _QEXTBPGRAPHICSVIEWSTYLE_H

#include <qextBlueprintGlobal.h>
#include <qextBPStyle.h>

#include <QColor>

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

#endif // _QEXTBPGRAPHICSVIEWSTYLE_H
