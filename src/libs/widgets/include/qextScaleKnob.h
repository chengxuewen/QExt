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

#ifndef _QEXTSCALEKNOB_H
#define _QEXTSCALEKNOB_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTScaleKnobPrivate;
class QEXT_WIDGETS_API QEXTScaleKnob : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int scaleStep READ scaleStep WRITE setScaleStep)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor percentColor READ percentColor WRITE setPercentColor)

    Q_PROPERTY(bool isRangeBisectionEnable READ isRangeBisectionEnable WRITE setRangeBisectionEnable)
    Q_PROPERTY(bool isValueVisiable READ isValueVisiable WRITE setValueVisiable)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    enum PointerStyle
    {
        PointerStyle_Line = 0,
        PointerStyle_Indicator = 1,
        PointerStyle_IndicatorR = 2,
        PointerStyle_Triangle = 3
    };
    Q_ENUMS(PointerStyle)

    explicit QEXTScaleKnob(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTScaleKnob();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int scaleStep() const;
    int startAngle() const;
    int endAngle() const;

    QColor borderColor() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor percentColor() const;

    bool isRangeBisectionEnable() const;
    bool isValueVisiable() const;
    PointerStyle pointerStyle() const;

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

    void setScaleStep(int step);

    void setStartAngle(int angle);

    void setEndAngle(int angle);

    void setBorderColor(const QColor &color);

    void setBackgroundColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setPercentColor(const QColor &color);

    void setRangeBisectionEnable(bool enable);

    void setValueVisiable(bool visiable);

    void setPointerStyle(const PointerStyle &style);

Q_SIGNALS:
    void valueChanged(double value);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawScale(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawPointerLine(QPainter *painter);
    void drawPointerIndicator(QPainter *painter);
    void drawPointerIndicatorR(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawValue(QPainter *painter);

    void setPressedValue(QPointF pressedPoint);

    QScopedPointer<QEXTScaleKnobPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTScaleKnob)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTScaleKnob)
};

#endif // _QEXTSCALEKNOB_H
