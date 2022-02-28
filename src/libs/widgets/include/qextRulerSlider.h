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

#ifndef _QEXTRULERSLIDER_H
#define _QEXTRULERSLIDER_H

#include <qextWidgetGlobal.h>

#include <QSlider>

class QEXTRulerSliderPrivate;
class QEXT_WIDGETS_API QEXTRulerSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(int longStep READ longStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ shortStep WRITE setShortStep)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(QColor sliderTopColor READ sliderTopColor WRITE setSliderTopColor)
    Q_PROPERTY(QColor sliderBottomColor READ sliderBottomColor WRITE setSliderBottomColor)

    Q_PROPERTY(QColor tipBackgroundColor READ tipBackgroundColor WRITE setTipBackgroundColor)
    Q_PROPERTY(QColor tipTextColor READ tipTextColor WRITE setTipTextColor)

public:
    explicit QEXTRulerSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTRulerSlider();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int longStep() const;
    int shortStep() const;
    int space() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;
    QColor lineColor() const;

    QColor sliderTopColor() const;
    QColor sliderBottomColor() const;

    QColor tipBackgroundColor() const;
    QColor tipTextColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged(double value);

public Q_SLOTS:
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);

    void setLongStep(int longStep);
    void setShortStep(int shortStep);

    void setSpace(int space);

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    void setLineColor(const QColor &color);

    void setSliderTopColor(const QColor &color);
    void setSliderBottomColor(const QColor &color);

    void setTipBackgroundColor(const QColor &color);
    void setTipTextColor(const QColor &color);

protected:
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawRule(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawTip(QPainter *painter);

    QScopedPointer<QEXTRulerSliderPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRulerSlider)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTRulerSlider)
};

#endif // _QEXTRULERSLIDER_H
