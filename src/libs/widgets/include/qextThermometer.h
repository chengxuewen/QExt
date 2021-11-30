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

#ifndef _QEXTTHERMOMETER_H
#define _QEXTTHERMOMETER_H

#include <QWidget>

#include <qextWidgetGlobal.h>

class QEXT_WIDGETS_API QEXTThermometer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)

    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)
    Q_PROPERTY(int longStep READ getLongStep WRITE setLongStep)
    Q_PROPERTY(int shortStep READ getShortStep WRITE setShortStep)
    Q_PROPERTY(int space READ getSpace WRITE setSpace)

    Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
    Q_PROPERTY(double animationStep READ getAnimationStep WRITE setAnimationStep)

    Q_PROPERTY(bool showUserValue READ getShowUserValue WRITE setShowUserValue)
    Q_PROPERTY(double userValue READ getUserValue WRITE setUserValue)
    Q_PROPERTY(QColor userValueColor READ getUserValueColor WRITE setUserValueColor)

    Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
    Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
    Q_PROPERTY(QColor barBgColor READ getBarBgColor WRITE setBarBgColor)
    Q_PROPERTY(QColor barColor READ getBarColor WRITE setBarColor)

    Q_PROPERTY(BarPosition barPosition READ getBarPosition WRITE setBarPosition)
    Q_PROPERTY(TickPosition tickPosition READ getTickPosition WRITE setTickPosition)

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

    explicit QEXTThermometer(QWidget *parent = 0);
    ~QEXTThermometer();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawRuler(QPainter *painter, int type);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    double minValue;
    double maxValue;
    double value;

    int precision;
    int longStep;
    int shortStep;
    int space;

    bool animation;
    double animationStep;

    bool showUserValue;
    double userValue;
    QColor userValueColor;

    QColor bgColorStart;
    QColor bgColorEnd;
    QColor lineColor;
    QColor barBgColor;
    QColor barColor;

    BarPosition barPosition;
    TickPosition tickPosition;

    int barWidth;
    int barHeight;
    int radius;
    int targetX;
    QRectF barRect;
    QRectF circleRect;

    bool reverse;
    double currentValue;
    QTimer *timer;

private slots:
    void updateValue();

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;

    int getPrecision()              const;
    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    bool getShowUserValue()         const;
    double getUserValue()           const;
    QColor getUserValueColor()      const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;
    QColor getBarBgColor()          const;
    QColor getBarColor()            const;

    BarPosition getBarPosition()    const;
    TickPosition getTickPosition()  const;

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

    void setAnimation(bool animation);

    void setAnimationStep(double animationStep);

    void setShowUserValue(bool showUserValue);

    void setUserValue(double userValue);
    void setUserValue(int userValue);

    void setUserValueColor(const QColor &userValueColor);

    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    void setLineColor(const QColor &lineColor);

    void setBarBgColor(const QColor &barBgColor);
    void setBarColor(const QColor &barColor);

    void setBarPosition(const BarPosition &barPosition);

    void setTickPosition(const TickPosition &tickPosition);

Q_SIGNALS:
    void valueChanged(double value);
};

#endif // _QEXTTHERMOMETER_H
