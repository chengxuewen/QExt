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

#ifndef _QEXTRANGESLIDER_H
#define _QEXTRANGESLIDER_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTRangeSliderPrivate;
class QEXT_WIDGETS_API QEXTRangeSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(int leftValue READ leftValue WRITE setLeftValue)
    Q_PROPERTY(int rightValue READ rightValue WRITE setRightValue)

    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(bool horizontal READ horizontal WRITE setHorizontal)
    Q_PROPERTY(bool isTextVisiable READ isTextVisiable WRITE setTextVisiable)

    Q_PROPERTY(QColor usedColor READ usedColor WRITE setUsedColor)
    Q_PROPERTY(QColor freeColor READ freeColor WRITE setFreeColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor rangeTextColor READ rangeTextColor WRITE setRangeTextColor)
    Q_PROPERTY(QColor sliderColor READ sliderColor WRITE setSliderColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)

    Q_PROPERTY(SliderStyle sliderStyle READ sliderStyle WRITE setSliderStyle)
    Q_PROPERTY(SliderBgPercent sliderBgPercent READ sliderBgPercent WRITE setSliderBackgroundPercent)
    Q_PROPERTY(SliderPercent sliderPercent READ sliderPercent WRITE setSliderPercent)

public:
    enum SliderStyle
    {
        SliderStyle_Line = 0,
        SliderStyle_Circle = 1
    };
    Q_ENUMS(SliderStyle)

    enum SliderBgPercent
    {
        SliderBgPercent_0_1 = 1,
        SliderBgPercent_0_2 = 2,
        SliderBgPercent_0_3 = 3,
        SliderBgPercent_0_4 = 4,
        SliderBgPercent_0_5 = 5,
        SliderBgPercent_0_6 = 6,
        SliderBgPercent_0_7 = 7,
        SliderBgPercent_0_8 = 8,
        SliderBgPercent_0_9 = 9,
        SliderBgPercent_1_0 = 10
    };
    Q_ENUMS(SliderBgPercent)

    enum SliderPercent
    {
        SliderPercent_0_1 = 1,
        SliderPercent_0_2 = 2,
        SliderPercent_0_3 = 3,
        SliderPercent_0_4 = 4,
        SliderPercent_0_5 = 5
    };
    Q_ENUMS(SliderPercent)

    explicit QEXTRangeSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTRangeSlider();

    int minValue() const;
    int maxValue() const;
    int leftValue() const;
    int rightValue() const;

    int borderWidth() const;
    bool horizontal() const;
    bool isTextVisiable() const;

    QColor usedColor() const;
    QColor freeColor() const;
    QColor textColor() const;
    QColor rangeTextColor() const;
    QColor sliderColor() const;
    QColor borderColor() const;

    SliderStyle sliderStyle() const;
    SliderBgPercent sliderBgPercent() const;
    SliderPercent sliderPercent() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged(int leftValue, int rightValue);

public Q_SLOTS:
    void setRange(int minValue, int maxValue);

    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    void setCurrentRange(int leftValue, int rightValue);
    void setLeftValue(int leftValue);
    void setRightValue(int rightValue);

    void setBorderWidth(int borderWidth);

    void setHorizontal(bool horizontal);

    void setTextVisiable(bool visiable);

    void setUsedColor(const QColor &color);

    void setFreeColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setRangeTextColor(const QColor &color);

    void setSliderColor(const QColor &color);

    void setBorderColor(const QColor &color);

    void setSliderStyle(const SliderStyle &sliderStyle);

    void setSliderBackgroundPercent(const SliderBgPercent &percent);

    void setSliderPercent(const SliderPercent &percent);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawSliderBackground(QPainter *painter);
    void drawSliderLine(QPainter *painter);
    void drawSliderCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTRangeSliderPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTRangeSlider)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTRangeSlider)
};

#endif // _QEXTRANGESLIDER_H
