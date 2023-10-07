/*************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTIPADDRESS_H
#define _QEXTIPADDRESS_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTIpAddressEditPrivate;
class QEXT_WIDGETS_API QEXTIpAddressEdit : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString iP READ iP WRITE setIP NOTIFY ipChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor dotColor READ dotColor WRITE setDotColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)

public:
    explicit QEXTIpAddressEdit(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIpAddressEdit();

    QString iP() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor dotColor() const;
    QColor borderColor() const;
    int borderRadius() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setIP(const QString &ip);
    void clear();

    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setDotColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setBorderRadius(int radius);

signals:
    void ipChanged(const QString &ip);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

    QScopedPointer<QEXTIpAddressEditPrivate> dd_ptr;

private Q_SLOTS:
    void textChanged(const QString &text);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTIpAddressEdit)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTIpAddressEdit)
};

#endif // _QEXTIPADDRESS_H
