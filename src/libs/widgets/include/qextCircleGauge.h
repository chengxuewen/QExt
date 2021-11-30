/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTCIRCLEGAUGE_H
#define _QEXTCIRCLEGAUGE_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTCircleGaugePrivate;
class QEXT_WIDGETS_API QEXTCircleGauge : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTCircleGauge)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTCircleGauge)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(bool animationEnable READ animationEnable WRITE setAnimation)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor outerCircleColor READ outerCircleColor WRITE setOuterCircleColor)
    Q_PROPERTY(QColor innerCircleColor READ innerCircleColor WRITE setInnerCircleColor)

    Q_PROPERTY(QColor pieColorStart READ pieColorStart WRITE setPieColorStart)
    Q_PROPERTY(QColor pieColorMid READ pieColorMid WRITE setPieColorMid)
    Q_PROPERTY(QColor pieColorEnd READ pieColorEnd WRITE setPieColorEnd)

    Q_PROPERTY(QColor coverCircleColor READ coverCircleColor WRITE setCoverCircleColor)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)
    Q_PROPERTY(QColor centerCircleColor READ centerCircleColor WRITE setCenterCircleColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool overlayVisiable READ overlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(int circleWidth READ circleWidth WRITE setCircleWidth)
    Q_PROPERTY(PieStyleType pieStyle READ pieStyle WRITE setPieStyle)
    Q_PROPERTY(PointerStyleType pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PieStyleType
    {
        PieStyle_Three = 0,
        PieStyle_Current = 1
    };
    Q_ENUMS(PieStyleType)

    enum PointerStyleType
    {
        PointerStyle_Circle = 0,
        PointerStyle_Indicator = 1,
        PointerStyle_IndicatorR = 2,
        PointerStyle_Triangle = 3
    };
    Q_ENUMS(PointerStyleType)

    explicit QEXTCircleGauge(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTCircleGauge();

public:
    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor outerCircleColor() const;
    QColor innerCircleColor() const;

    QColor pieColorStart() const;
    QColor pieColorMid() const;
    QColor pieColorEnd() const;

    QColor coverCircleColor() const;
    QColor scaleColor() const;
    QColor pointerColor() const;
    QColor centerCircleColor() const;
    QColor textColor() const;

    bool overlayVisiable() const;
    QColor overlayColor() const;

    int circleWidth() const;
    PieStyleType pieStyle() const;
    PointerStyleType pointerStyle() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);

    void setScaleMajor(int scaleMajor);
    void setScaleMinor(int scaleMinor);
    void setStartAngle(int startAngle);
    void setEndAngle(int endAngle);

    void setAnimation(bool animation);
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    void setOuterCircleColor(const QColor &color);
    void setInnerCircleColor(const QColor &color);

    void setPieColorStart(const QColor &color);
    void setPieColorMid(const QColor &color);
    void setPieColorEnd(const QColor &color);

    void setCoverCircleColor(const QColor &color);
    void setScaleColor(const QColor &color);
    void setPointerColor(const QColor &color);
    void setCenterCircleColor(const QColor &color);
    void setTextColor(const QColor &color);

    void setOverlayVisiable(bool visiable);
    void setOverlayColor(const QColor &color);

    void setCircleWidth(int width);
    void setPieStyle(const PieStyleType &style);
    void setPointerStyle(const PointerStyleType &style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawOuterCircle(QPainter *painter);
    void drawInnerCircle(QPainter *painter);
    void drawColorPie(QPainter *painter);
    void drawCoverCircle(QPainter *painter);
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

    QScopedPointer<QEXTCircleGaugePrivate> dd_ptr;

private slots:
    void updateValue(const QVariant &value);
};

#endif // _QEXTCIRCLEGAUGE_H
