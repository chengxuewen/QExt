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

#ifndef _QEXTBREATHINGLIGHT_H
#define _QEXTBREATHINGLIGHT_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QObject>

class QEXTBreathingLightPrivate;
class QEXT_WIDGETS_API QEXTBreathingLight : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(int interval READ interval WRITE setInterval)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    explicit QEXTBreathingLight(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTBreathingLight();

    int step() const;
    int interval() const;
    QColor backgroundColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public slots:
    void setStep(const int &step);
    void setInterval(const int &interval);
    void setBackgroundColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);

    QScopedPointer<QEXTBreathingLightPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTBreathingLight)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTBreathingLight)
};

#endif // _QEXTBREATHINGLIGHT_H
