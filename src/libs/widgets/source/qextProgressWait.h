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

#ifndef _QEXTPROGRESSWAIT_H
#define _QEXTPROGRESSWAIT_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtProgressWaitPrivate;
class QEXT_WIDGETS_API QExtProgressWait : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool clockWise READ clockWise WRITE setClockWise)
    Q_PROPERTY(bool showPercent READ showPercent WRITE setShowPercent)

    Q_PROPERTY(int currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(int interval READ interval WRITE setInterval)

    Q_PROPERTY(Style barStyle READ barStyle WRITE setBarStyle)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

public:
    enum Style {
        Style_Line = 0,
        Style_Dot,
	};
    Q_ENUMS(Style)

    QExtProgressWait(QWidget *parent = QEXT_NULLPTR);
    ~QExtProgressWait();

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

    QScopedPointer<QExtProgressWaitPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtProgressWait)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtProgressWait)

private:
	double degreesToRadians(double value);

private slots:
	void updateValue();

public:
    bool clockWise() const;
    bool showPercent() const;
    int currentValue() const;
    int maxValue() const;
    int interval() const;

    Style barStyle() const;
    QColor backgroundColor() const;
    QColor foregroundColor() const;
    QColor textColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
	void setClockWise(bool clockWise);

	void setShowPercent(bool showPercent);

	void setCurrentValue(int currentValue);

	void setMaxValue(int maxValue);

	void setInterval(int interval);

    void setBarStyle(const Style &barStyle);

    void setBackgroundColor(const QColor &color);

    void setForegroundColor(const QColor &color);

    void setTextColor(const QColor &color);
};

#endif // _QEXTPROGRESSWAIT_H
