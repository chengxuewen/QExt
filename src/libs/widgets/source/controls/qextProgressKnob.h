/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTPROGRESSKNOB_H
#define _QEXTPROGRESSKNOB_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QVariant>

class QPropertyAnimation;
class QExtProgressKnobPrivate;
class QEXT_WIDGETS_API QExtProgressKnob : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(QColor progressBackgroundColor READ progressBackgroundColor WRITE setProgressBackgroundColor)
    Q_PROPERTY(QColor circleStartColor READ circleStartColor WRITE setCircleStartColor)
    Q_PROPERTY(QColor circleEndColor READ circleEndColor WRITE setCircleEndColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(bool pointerVisible READ pointerVisible WRITE setPointerVisible)
    Q_PROPERTY(bool valueVisible READ valueVisible WRITE setValueVisible)
    Q_PROPERTY(PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
	enum PointerStyle {
        PointerStyle_Circle = 0,
        PointerStyle_Indicator,
        PointerStyle_IndicatorR,
        PointerStyle_Triangle
	};
    Q_ENUMS(PointerStyle)

    explicit QExtProgressKnob(QWidget *parent = QEXT_NULLPTR);
    ~QExtProgressKnob();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int startAngle() const;
    int endAngle() const;

    QColor backgroundColor() const;
    QColor progressColor() const;
    QColor progressBackgroundColor() const;
    QColor circleStartColor() const;
    QColor circleEndColor() const;
    QColor textColor() const;

    bool pointerVisible() const;
    bool valueVisible() const;
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

    void setStartAngle(int angle);
    void setEndAngle(int angle);

    void setBackgroundColor(const QColor &color);

    void setProgressColor(const QColor &color);
    void setProgressBackgroundColor(const QColor &color);

    void setCircleStartColor(const QColor &color);
    void setCircleEndColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setPointerVisible(bool visiable);
    void setValueVisible(bool visiable);
    void setPointerStyle(PointerStyle style);

Q_SIGNALS:
    void valueChanged(int value);

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
	void drawColorPie(QPainter *painter);
	void drawCoverCircle(QPainter *painter);
	void drawCircle(QPainter *painter);
	void drawPointerCircle(QPainter *painter);
	void drawPointerIndicator(QPainter *painter);
	void drawPointerIndicatorR(QPainter *painter);
	void drawPointerTriangle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QExtProgressKnobPrivate> dd_ptr;

private slots:
    void setEasingCurve();
    void updateRadius(QVariant radius);

private:
    void setPressedValue(QPointF pressedPoint);

    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtProgressKnob)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtProgressKnob)
};

#endif // _QEXTPROGRESSKNOB_H
