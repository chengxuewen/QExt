#ifndef _QEXTBPCONNECTIONSTYLE_H
#define _QEXTBPCONNECTIONSTYLE_H

#include <qextBlueprintGlobal.h>
#include <qextBPStyle.h>

#include <QColor>

class QEXT_BLUEPRINT_API QExtBPConnectionStyle : public QExtBPStyle
{
public:
    QExtBPConnectionStyle();

    QExtBPConnectionStyle(QString jsonText);

    ~QExtBPConnectionStyle() = default;

public:
    static void setConnectionStyle(QString jsonText);

public:
    void loadJson(const QJsonObject &json) override;

    QJsonObject toJson() const override;

public:
    QColor constructionColor() const;
    QColor normalColor() const;
    QColor normalColor(QString typeId) const;
    QColor selectedColor() const;
    QColor selectedHaloColor() const;
    QColor hoveredColor() const;

    float lineWidth() const;
    float constructionLineWidth() const;
    float pointDiameter() const;

    bool useDataDefinedColors() const;

private:
    QColor ConstructionColor;
    QColor NormalColor;
    QColor SelectedColor;
    QColor SelectedHaloColor;
    QColor HoveredColor;

    float LineWidth;
    float ConstructionLineWidth;
    float PointDiameter;

    bool UseDataDefinedColors;
};

#endif // _QEXTBPCONNECTIONSTYLE_H
