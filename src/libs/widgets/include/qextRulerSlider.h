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

class QEXT_WIDGETS_API QEXTRulerSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(int longStep READ getLongStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ getShortStep WRITE setShortStep)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)

    Q_PROPERTY(QColor sliderColorTop READ getSliderColorTop WRITE setSliderColorTop)
    Q_PROPERTY(QColor sliderColorBottom READ getSliderColorBottom WRITE setSliderColorBottom)

    Q_PROPERTY(QColor tipBgColor READ getTipBgColor WRITE setTipBgColor)
    Q_PROPERTY(QColor tipTextColor READ getTipTextColor WRITE setTipTextColor)

public:
    explicit QEXTRulerSlider(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawRule(QPainter *painter);
    void drawSlider(QPainter *painter);
    void drawTip(QPainter *painter);

private:
    double minValue;
    double maxValue;
    double value;
    int precision;

    int longStep;
    int shortStep;
    int space;

    QColor bgColorStart;
    QColor bgColorEnd;
    QColor lineColor;

    QColor sliderColorTop;
    QColor sliderColorBottom;

    QColor tipBgColor;
    QColor tipTextColor;

    bool pressed;
    double currentValue;

    double longLineHeight;
    double shortLineHeight;
    double sliderTopHeight;
    double sliderBottomHeight;

    QPointF sliderLastPot;
    QPointF sliderTopPot;
    QPointF sliderLeftPot;
    QPointF sliderRightPot;

    QRectF sliderRect;
    QRectF tipRect;
    QPointF lineLeftPot;
    QPointF lineRightPot;

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    int getPrecision()              const;

    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;

    QColor getSliderColorTop()      const;
    QColor getSliderColorBottom()   const;

    QColor getTipBgColor()          const;
    QColor getTipTextColor()        const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

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

    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    void setLineColor(const QColor &lineColor);

    void setSliderColorTop(const QColor &sliderColorTop);
    void setSliderColorBottom(const QColor &sliderColorBottom);

    void setTipBgColor(const QColor &tipBgColor);
    void setTipTextColor(const QColor &tipTextColor);

Q_SIGNALS:
    void valueChanged(double value);
};

#endif // _QEXTRULERSLIDER_H
