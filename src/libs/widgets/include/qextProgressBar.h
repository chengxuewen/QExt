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

#ifndef _QEXTPROGRESSPIE_H
#define _QEXTPROGRESSPIE_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXT_WIDGETS_API QEXTProgressBar : public QWidget
{
	Q_OBJECT	
	Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
	Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
	Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

	Q_PROPERTY(double step READ getStep WRITE setStep)
	Q_PROPERTY(double space READ getSpace WRITE setSpace)
	Q_PROPERTY(double radius READ getRadius WRITE setRadius)

	Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
	Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)

	Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
	Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

	Q_PROPERTY(QColor barBgColor READ getBarBgColor WRITE setBarBgColor)
	Q_PROPERTY(QColor barColor READ getBarColor WRITE setBarColor)

public:
    explicit QEXTProgressBar(QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent *);
	void drawBg(QPainter *painter);
	void drawBar(QPainter *painter);

private:	
    double minValue;
    double maxValue;
    double value;
    int precision;

    int step;
    int space;
    int radius;

    QColor bgColorStart;
    QColor bgColorEnd;

    QColor lineColor;
    QColor textColor;

    QColor barBgColor;
    QColor barColor;

public:	
	double getMinValue()            const;
	double getMaxValue()            const;
    double getValue()               const;
	int getPrecision()              const;

	int getStep()                   const;
	int getSpace()                  const;
	int getRadius()                 const;

	QColor getBgColorStart()        const;
	QColor getBgColorEnd()          const;

	QColor getLineColor()           const;
	QColor getTextColor()           const;

	QColor getBarBgColor()          const;
	QColor getBarColor()            const;

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

	void setStep(int step);

	void setSpace(int space);

	void setRadius(int radius);

	void setBgColorStart(const QColor &bgColorStart);
	void setBgColorEnd(const QColor &bgColorEnd);

	void setLineColor(QColor lineColor);

	void setTextColor(QColor textColor);

	void setBarBgColor(QColor barBgColor);
	void setBarColor(QColor barColor);

Q_SIGNALS:
	void valueChanged(double value);
};

#endif // _QEXTPROGRESSPIE_H
