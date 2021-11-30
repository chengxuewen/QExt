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

#ifndef _QEXTDIAL_H
#define _QEXTDIAL_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTDialPrivate;
class QEXT_WIDGETS_API QEXTDial : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTDial)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTDial)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleMajor READ scaleMajor WRITE setScaleMajor)
    Q_PROPERTY(int scaleMinor READ scaleMinor WRITE setScaleMinor)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool valueVisiable READ valueVisiable WRITE setShowValue)
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

    explicit QEXTDial(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTDial();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleMajor() const;
    int scaleMinor() const;
    int startAngle() const;
    int endAngle() const;

    QColor darkColor() const;
    QColor lightColor() const;
    QColor textColor() const;

    bool valueVisiable() const;
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
    void setStartAngle(int angle);
    void setEndAngle(int angle);

    void setDarkColor(const QColor &color);
    void setLightColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setShowValue(bool visiable);
    void setPointerStyle(const PointerStyleType &style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawBorderCircle(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawPointerCircle(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    void setPressedValue(QPointF point);

    QScopedPointer<QEXTDialPrivate> dd_ptr;
};

#endif // _QEXTDIAL_H
