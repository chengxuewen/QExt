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

#ifndef _QEXTPROGRESSPIE_H
#define _QEXTPROGRESSPIE_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtProgressBarPrivate;
class QEXT_WIDGETS_API QExtProgressBar : public QWidget
{
	Q_OBJECT	
    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(double step READ step WRITE setStep)
    Q_PROPERTY(double space READ space WRITE setSpace)
    Q_PROPERTY(double radius READ radius WRITE setRadius)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBgColorStart)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBgColorEnd)

    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(QColor barBackgroundColor READ barBackgroundColor WRITE setBarBgColor)
    Q_PROPERTY(QColor barColor READ barColor WRITE setBarColor)

public:
    explicit QExtProgressBar(QWidget *parent = QEXT_NULLPTR);
    ~QExtProgressBar();

    double minValue() const;
    double maxValue() const;
    double value() const;
    int precision() const;

    int step() const;
    int space() const;
    int radius() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor lineColor() const;
    QColor textColor() const;

    QColor barBackgroundColor() const;
    QColor barColor() const;

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

    void setStep(int step);

    void setSpace(int space);

    void setRadius(int radius);

    void setBgColorStart(const QColor &color);
    void setBgColorEnd(const QColor &color);

    void setLineColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setBarBgColor(const QColor &color);
    void setBarColor(const QColor &color);

protected:
	void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
	void drawBar(QPainter *painter);

    QScopedPointer<QExtProgressBarPrivate> dd_ptr;

private:	
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtProgressBar)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtProgressBar)
};

#endif // _QEXTPROGRESSPIE_H
