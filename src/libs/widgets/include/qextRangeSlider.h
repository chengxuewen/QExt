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

class QEXT_WIDGETS_API QEXTRangeSlider : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(int leftValue READ getLeftValue WRITE setLeftValue)
    Q_PROPERTY(int rightValue READ getRightValue WRITE setRightValue)

    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth)
    Q_PROPERTY(bool horizontal READ getHorizontal WRITE setHorizontal)
    Q_PROPERTY(bool showText READ getShowText WRITE setShowText)

    Q_PROPERTY(QColor usedColor READ getUsedColor WRITE setUsedColor)
    Q_PROPERTY(QColor freeColor READ getFreeColor WRITE setFreeColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor rangeTextColor READ getRangeTextColor WRITE setRangeTextColor)
    Q_PROPERTY(QColor sliderColor READ getSliderColor WRITE setSliderColor)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)

    Q_PROPERTY(SliderStyle sliderStyle READ getSliderStyle WRITE setSliderStyle)
    Q_PROPERTY(SliderBgPercent sliderBgPercent READ getSliderBgPercent WRITE setSliderBgPercent)
    Q_PROPERTY(SliderPercent sliderPercent READ getSliderPercent WRITE setSliderPercent)

public:
    enum SliderStyle
    {
        SliderStyle_Line = 0,       //线条状风格
        SliderStyle_Circle = 1      //圆形状风格
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

    explicit QEXTRangeSlider(QWidget *parent = 0);
    ~QEXTRangeSlider();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawSliderBg(QPainter *painter);
    void drawSliderLine(QPainter *painter);
    void drawSliderCircle(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    int minValue;
    int maxValue;
    int leftValue;
    int rightValue;

    int borderWidth;
    bool horizontal;
    bool showText;

    QColor usedColor;
    QColor freeColor;
    QColor textColor;
    QColor rangeTextColor;
    QColor sliderColor;
    QColor borderColor;

    SliderStyle sliderStyle;
    SliderBgPercent sliderBgPercent;
    SliderPercent sliderPercent;

    bool leftPressed;
    bool rightPressed;

    int sliderLen;
    QRect leftSliderRect;
    QRect rightSliderRect;

public:
    int getMinValue()               const;
    int getMaxValue()               const;
    int getLeftValue()              const;
    int getRightValue()             const;

    int getBorderWidth()            const;
    bool getHorizontal()            const;
    bool getShowText()              const;

    QColor getUsedColor()           const;
    QColor getFreeColor()           const;
    QColor getTextColor()           const;
    QColor getRangeTextColor()      const;
    QColor getSliderColor()         const;
    QColor getBorderColor()         const;

    SliderStyle getSliderStyle()    const;
    SliderBgPercent getSliderBgPercent()const;
    SliderPercent getSliderPercent()const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setRange(int minValue, int maxValue);

    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    void setCurrentRange(int leftValue, int rightValue);
    void setLeftValue(int leftValue);
    void setRightValue(int rightValue);

    void setBorderWidth(int borderWidth);

    void setHorizontal(bool horizontal);

    void setShowText(bool showText);

    void setUsedColor(const QColor &usedColor);

    void setFreeColor(const QColor &freeColor);

    void setTextColor(const QColor &textColor);

    void setRangeTextColor(const QColor &rangeTextColor);

    void setSliderColor(const QColor &sliderColor);

    void setBorderColor(const QColor &borderColor);

    void setSliderStyle(const SliderStyle &sliderStyle);

    void setSliderBgPercent(const SliderBgPercent &sliderBgPercent);

    void setSliderPercent(const SliderPercent &sliderPercent);

Q_SIGNALS:
    void valueChanged(int leftValue, int rightValue);
};

#endif // _QEXTRANGESLIDER_H
