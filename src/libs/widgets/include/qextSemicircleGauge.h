/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTSEMICIRCLEGAUGE_H
#define _QEXTSEMICIRCLEGAUGE_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTSemicircleGaugePrivate;
class QEXT_WIDGETS_API QEXTSemicircleGauge : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(bool animationVisiable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor usedColor READ usedColor WRITE setUsedColor)
    Q_PROPERTY(QColor freeColor READ freeColor WRITE setFreeColor)

    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)

    Q_PROPERTY(bool overlayVisiable READ overlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(PointerStyleType pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyleType
    {
        PointerStyle_Circle = 0,
        PointerStyle_Indicator = 1,
        PointerStyle_IndicatorR = 2,
        PointerStyle_Triangle = 3
    };
    Q_ENUMS(PointerStyleType)

    explicit QEXTSemicircleGauge(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSemicircleGauge();

    double minValue() const;
    double maxValue() const;
    double value() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor usedColor() const;
    QColor freeColor() const;

    QColor scaleColor() const;
    QColor pointerColor() const;
    QColor textColor() const;
    QColor titleColor() const;

    bool overlayVisiable() const;
    QColor overlayColor() const;

    PointerStyleType pointerStyle() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged(double value);

public Q_SLOTS:
    void setRange(double minValue, double maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setScaleMajor(int scaleMajor);

    void setScaleMinor(int scaleMinor);

    void setStartAngle(int startAngle);

    void setEndAngle(int endAngle);

    void setAnimationEnable(bool enable);

    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    void setUsedColor(const QColor &usedColor);

    void setFreeColor(const QColor &freeColor);

    void setScaleColor(const QColor &scaleColor);

    void setPointerColor(const QColor &pointerColor);

    void setTextColor(const QColor &textColor);

    void setTitleColor(const QColor &titleColor);

    void setOverlayVisiable(bool visiable);

    void setOverlayColor(const QColor &overlayColor);

    void setPointerStyle(const PointerStyleType &pointerStyle);

protected:
    void paintEvent(QPaintEvent *);

    void drawArc(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawPointerCircle(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawRoundCircle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawOverlay(QPainter *painter);

    QScopedPointer<QEXTSemicircleGaugePrivate> dd_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSemicircleGauge)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTSemicircleGauge)
};

#endif // _QEXTSEMICIRCLEGAUGE_H
