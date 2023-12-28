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

#ifndef _QEXTICONBUTTON_H
#define _QEXTICONBUTTON_H

#include <qextWidgetGlobal.h>

#include <QPushButton>
#include <QSize>

class QExtIconButtonPrivate;
class QEXT_WIDGETS_API QExtIconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor)

public:
    QExtIconButton(const QIcon &icon, QWidget *parent = QEXT_NULLPTR);
    explicit QExtIconButton(QWidget *parent = QEXT_NULLPTR);
    ~QExtIconButton();

    QSize sizeHint() const QEXT_OVERRIDE;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setIconColor(const QColor &color);
    QColor iconColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    QExtIconButton(QExtIconButtonPrivate &d, QWidget *parent = QEXT_NULLPTR);

    bool event(QEvent *event) QEXT_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) QEXT_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *event) QEXT_OVERRIDE;

    const QScopedPointer<QExtIconButtonPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtIconButton)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtIconButton)
};

#endif // _QEXTICONBUTTON_H
