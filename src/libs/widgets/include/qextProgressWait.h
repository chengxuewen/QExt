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

#ifndef _QEXTPROGRESSWAIT_H
#define _QEXTPROGRESSWAIT_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXT_WIDGETS_API QEXTProgressWait : public QWidget
{
    Q_OBJECT

	Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)
	Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)

	Q_PROPERTY(int currentValue READ getCurrentValue WRITE setCurrentValue)
	Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
	Q_PROPERTY(int interval READ getInterval WRITE setInterval)

    Q_PROPERTY(Style barStyle READ getBarStyle WRITE setBarStyle)
	Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
	Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)

public:
    enum Style {
        Style_Line = 0,
        Style_Dot,
	};
    Q_ENUMS(Style)

    QEXTProgressWait(QWidget *parent = 0);
    ~QEXTProgressWait();

protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);

    void drawLine(QPainter *painter);
    void drawDot(QPainter *painter);

	void drawArc(QPainter *painter);
	void drawPie(QPainter *painter);
	void drawRing(QPainter *painter);
	void drawSingleCircle(QPainter *painter);
	void drawDoubleCircle(QPainter *painter);
    void drawValue(QPainter *painter);

private:
    bool clockWise;
    bool showPercent;
    int currentValue;
    int maxValue;
    int interval;

    int minRadius;
    int maxRadius;
    int offsetRadius;
    int leftRadius;
    int rightRadius;
    bool leftIncrease;
    bool rightIncrease;

    Style barStyle;
    QColor background;
    QColor foreground;
    QColor textColor;

    QTimer *timer;

private:
	double degreesToRadians(double value);

private slots:
	void updateValue();

public:
	bool getClockWise()             const;
	bool getShowPercent()           const;
	int getCurrentValue()           const;
	int getMaxValue()               const;
	int getInterval()               const;

    Style getBarStyle()          const;
	QColor getBackground()          const;
	QColor getForeground()          const;
    QColor getTextColor()           const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	void setClockWise(bool clockWise);

	void setShowPercent(bool showPercent);

	void setCurrentValue(int currentValue);

	void setMaxValue(int maxValue);

	void setInterval(int interval);

    void setBarStyle(const Style &barStyle);

	void setBackground(const QColor &background);

	void setForeground(const QColor &foreground);

    void setTextColor(const QColor &textColor);
};

#endif // _QEXTPROGRESSWAIT_H
