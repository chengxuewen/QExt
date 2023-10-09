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

#ifndef _QEXTLED_H
#define _QEXTLED_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QObject>
#include <QSize>
#include <QColor>

class QExtLedPrivate;
class QEXT_WIDGETS_API QExtLed : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool state READ isOn WRITE setOn NOTIFY stateChanged)

public:
    explicit QExtLed(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QExtLed();

    QColor color() const;
    bool isOn() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

Q_SIGNALS:
    void colorChanged(QColor ledColor);
    void stateChanged(bool on);

public Q_SLOTS:
    void setColor(const QColor &color);
    void setOn(bool on);
    void turnOn();
    void turnOff();
    void toggle();

protected:
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    QScopedPointer<QExtLedPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtLed)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtLed)
};

#endif // _QEXTLED_H
