/*************************************************************************************
**
** Library: QExt
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
#include <QScopedPointer>

class QEXTProgressButtonPrivate;
class QEXT_WIDGETS_API QEXTProgressButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QEXTProgressButton(QWidget *parent = 0);
    ~QEXTProgressButton();

    int lineWidth() const;
    QColor lineColor() const;
    int borderWidth() const;
    QColor borderColor() const;
    int borderRadius() const;
    QColor backgroundColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void valueChanged(int value);

public Q_SLOTS:
    void setLineWidth(int width);
    void setLineColor(const QColor &color);

    void setBorderWidth(int width);
    void setBorderColor(const QColor &color);

    void setBorderRadius(int radius);
    void setBackgroundColor(const QColor &color);

private slots:
    void progress();

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawProgress(QPainter *painter);

    QScopedPointer<QEXTProgressButtonPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressButton)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTProgressButton)
};

#endif // _QEXTPROGRESSBUTTON_H
