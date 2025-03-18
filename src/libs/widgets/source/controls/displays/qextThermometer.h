/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#ifndef _QEXTTHERMOMETER_H
#define _QEXTTHERMOMETER_H

#include <QWidget>

#include <qextWidgetGlobal.h>

class QExtThermometerPrivate;
class QEXT_WIDGETS_API QExtThermometer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)

    Q_PROPERTY(int precision READ precision WRITE setPrecision)
    Q_PROPERTY(int longStep READ longStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ shortStep WRITE setShortStep)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(bool animationEnable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(double animationStep READ animationStep WRITE setAnimationStep)

    Q_PROPERTY(bool userValueVisible READ userValueVisible WRITE setUserValueVisible)
    Q_PROPERTY(double userValue READ userValue WRITE setUserValue)
    Q_PROPERTY(QColor userValueColor READ userValueColor WRITE setUserValueColor)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBgColorStart)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBackgroundColor READ barBackgroundColor WRITE setBarBackgroundColor)
    Q_PROPERTY(QColor barColor READ barColor WRITE setBarColor)

    Q_PROPERTY(BarPosition barPosition READ barPosition WRITE setBarPosition)
    Q_PROPERTY(TickPosition tickPosition READ tickPosition WRITE setTickPosition)

public:
    enum BarPosition {
        BarPosition_Left = 0,
        BarPosition_Right = 1,
        BarPosition_Center = 2
    };
    Q_ENUMS(BarPosition)

    enum TickPosition {
        TickPosition_Null = 0,
        TickPosition_Left = 1,
        TickPosition_Right = 2,
        TickPosition_Both = 3
    };
    Q_ENUMS(TickPosition)

    explicit QExtThermometer(QWidget *parent = QEXT_NULLPTR);
    ~QExtThermometer();

    double minValue() const;
    double maxValue() const;
    double value() const;

    int precision() const;
    int longStep() const;
    int shortStep() const;
    int space() const;

    bool animationEnable() const;
    double animationStep() const;

    bool userValueVisible() const;
    double userValue() const;
    QColor userValueColor() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;
    QColor lineColor() const;
    QColor barBackgroundColor() const;
    QColor barColor() const;

    BarPosition barPosition() const;
    TickPosition tickPosition() const;

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

    void setAnimationEnable(bool enable);

    void setAnimationStep(double animationStep);

    void setUserValueVisible(bool visiable);

    void setUserValue(double userValue);
    void setUserValue(int userValue);

    void setUserValueColor(const QColor &color);

    void setBgColorStart(const QColor &color);
    void setBgColorEnd(const QColor &color);

    void setLineColor(const QColor &color);

    void setBarBackgroundColor(const QColor &color);
    void setBarColor(const QColor &color);

    void setBarPosition(const BarPosition &position);

    void setTickPosition(const TickPosition &position);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawBarBackground(QPainter *painter);
    void drawRuler(QPainter *painter, int type);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QExtThermometerPrivate> dd_ptr;

private slots:
    void updateValue();

private:
    QEXT_DISABLE_COPY_MOVE(QExtThermometer)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtThermometer)
};

#endif // _QEXTTHERMOMETER_H
