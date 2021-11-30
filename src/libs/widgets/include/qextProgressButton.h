/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTPROGRESSBUTTON_H
#define _QEXTPROGRESSBUTTON_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXT_WIDGETS_API QEXTProgressButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)
    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

public:
    explicit QEXTProgressButton(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawProgress(QPainter *painter);

private:
    int lineWidth;
    QColor lineColor;
    int borderWidth;
    QColor borderColor;
    int borderRadius;
    QColor bgColor;

    double value;
    int status;
    int tempWidth;
    QTimer *timer;

public:
    int getLineWidth()      const;
    QColor getLineColor()   const;
    int getBorderWidth()    const;
    QColor getBorderColor() const;
    int getBorderRadius()   const;
    QColor getBgColor()     const;

    QSize sizeHint()        const;
    QSize minimumSizeHint() const;

private slots:
    void progress();

public Q_SLOTS:
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);

    void setBorderWidth(int borderWidth);
    void setBorderColor(const QColor &borderColor);

    void setBorderRadius(int borderRadius);
    void setBgColor(const QColor &bgColor);

Q_SIGNALS:
    void valueChanged(int value);
};

#endif // _QEXTPROGRESSBUTTON_H
