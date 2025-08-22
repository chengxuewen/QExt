/***********************************************************************************************************************
**
** Library: QExt
**
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

#ifndef _QEXTOVENTIMER_H
#define _QEXTOVENTIMER_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QDateTime>

class QTimer;
class QExtOvenTimerPrivate;
class QEXT_WIDGETS_API QExtOvenTimer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int duration READ duration WRITE setDuration)

public:
    QExtOvenTimer(QWidget *parent = QEXT_NULLPTR);
    ~QExtOvenTimer();

    int duration() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void timeout();

public Q_SLOTS:
    void setDuration(int secs);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

    void draw(QPainter *painter);

    QScopedPointer<QExtOvenTimerPrivate> dd_ptr;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtOvenTimer)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtOvenTimer)
};

#endif // _QEXTOVENTIMER_H
