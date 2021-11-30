/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2017 逆风微光(QQ:787701109)
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

#ifndef _QEXTSELECTSLIDER_H
#define _QEXTSELECTSLIDER_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTSelectSliderPrivate;
class QEXT_WIDGETS_API QEXTSelectSlider : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTSelectSlider)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTSelectSlider)

    Q_PROPERTY(int m_minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(int m_maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(int m_leftValue READ leftValue WRITE setLeftValue)
    Q_PROPERTY(int m_rightValue READ rightValue WRITE setRightValue)

    Q_PROPERTY(int m_rangeValue READ rangeValue WRITE setRangeValue)
    Q_PROPERTY(int m_step READ step WRITE setStep)

    Q_PROPERTY(int m_borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(bool m_horizontal READ horizontal WRITE setHorizontal)

    Q_PROPERTY(QColor m_usedColor READ usedColor WRITE setUsedColor)
    Q_PROPERTY(QColor m_freeColor READ freeColor WRITE setFreeColor)
    Q_PROPERTY(QColor m_textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor m_rangeTextColor READ rangeTextColor WRITE setRangeTextColor)
    Q_PROPERTY(QColor m_sliderColor READ sliderColor WRITE setSliderColor)
    Q_PROPERTY(QColor m_borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor m_buttonNormalColor READ buttonNormalColor WRITE setButtonNormalColor)
    Q_PROPERTY(QColor m_buttonPressColor READ buttonPressColor WRITE setButtonPressColor)

public:
    explicit QEXTSelectSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSelectSlider();

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawButton(QPainter *painter);
    void drawSlider(QPainter *painter);
    void updateUI();

    QScopedPointer<QEXTSelectSliderPrivate> dd_ptr;

private:

public:
    int minValue() const;
    int maxValue() const;
    int leftValue() const;
    int rightValue() const;

    int rangeValue() const;
    int step() const;

    int borderWidth() const;
    bool horizontal() const;

    QColor usedColor() const;
    QColor freeColor() const;
    QColor textColor() const;
    QColor rangeTextColor() const;
    QColor sliderColor() const;
    QColor borderColor() const;
    QColor buttonNormalColor() const;
    QColor buttonPressColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setRange(int minValue, int maxValue);

    void setMinValue(int minValue);
    void setMaxValue(int maxValue);

    void setCurrentRange(int leftValue, int rightValue);
    void setLeftValue(int leftValue);
    void setRightValue(int rightValue);

    void setRangeValue(int rangeValue);

    void setStep(int step);

    void setBorderWidth(int borderWidth);

    void setHorizontal(bool horizontal);

    void setUsedColor(const QColor &usedColor);

    void setFreeColor(const QColor &freeColor);

    void setTextColor(const QColor &textColor);

    void setRangeTextColor(const QColor &rangeTextColor);

    void setSliderColor(const QColor &sliderColor);

    void setBorderColor(const QColor &borderColor);

    void setButtonNormalColor(const QColor &btnNormalColor);

    void setButtonPressColor(const QColor &btnPressColor);

Q_SIGNALS:
    void valueChanged(int leftValue, int rightValue);
    void rangeChanged(int rangeValue);
};

#endif // _QEXTSELECTSLIDER_H
