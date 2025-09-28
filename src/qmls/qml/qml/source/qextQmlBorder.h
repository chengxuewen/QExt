/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#ifndef _QEXTQMLBORDER_H
#define _QEXTQMLBORDER_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QColor>
#include <QObject>

class QExtQmlBorderPrivate;
class QEXT_QML_API QExtQmlBorder : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal leftWidth READ leftWidth WRITE setLeftWidth NOTIFY leftWidthChanged)
    Q_PROPERTY(qreal rightWidth READ rightWidth WRITE setRightWidth NOTIFY rightWidthChanged)
    Q_PROPERTY(qreal topWidth READ topWidth WRITE setTopWidth NOTIFY topWidthChanged)
    Q_PROPERTY(qreal bottomWidth READ bottomWidth WRITE setBottomWidth NOTIFY bottomWidthChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)

public:
    explicit QExtQmlBorder(QObject *parent = nullptr);
    ~QExtQmlBorder();

    QColor color() const;
    qreal width() const;
    qreal leftWidth() const;
    qreal rightWidth() const;
    qreal topWidth() const;
    qreal bottomWidth() const;
    bool isValid() const;

Q_SIGNALS:
    void colorChanged();
    void widthChanged();
    void leftWidthChanged();
    void rightWidthChanged();
    void topWidthChanged();
    void bottomWidthChanged();
    void validChanged();

public Q_SLOTS:
    void setColor(QColor color);
    void setWidth(qreal width);
    void setLeftWidth(qreal leftWidth);
    void setRightWidth(qreal rightWidth);
    void setTopWidth(qreal topWidth);
    void setBottomWidth(qreal bottomWidth);

protected:
    QScopedPointer<QExtQmlBorderPrivate> dd_ptr;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlBorder)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlBorder)
};

#endif // _QEXTQMLBORDER_H
