/****************************************************************************
**
** Library: QExtQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef _QEXTQUICKBORDERGADGET_H
#define _QEXTQUICKBORDERGADGET_H

#include <qextQuickGlobal.h>

#include <QColor>
#include <QObject>

class QExtQuickBorderGadgetPrivate;
class QEXT_QUICK_API QExtQuickBorderGadget : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtQuickBorderGadget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickBorderGadget)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal leftWidth READ leftWidth WRITE setLeftWidth NOTIFY leftWidthChanged)
    Q_PROPERTY(qreal rightWidth READ rightWidth WRITE setRightWidth NOTIFY rightWidthChanged)
    Q_PROPERTY(qreal topWidth READ topWidth WRITE setTopWidth NOTIFY topWidthChanged)
    Q_PROPERTY(qreal bottomWidth READ bottomWidth WRITE setBottomWidth NOTIFY bottomWidthChanged)
    Q_PROPERTY(bool valid READ isValid NOTIFY validChanged)

public:
    explicit QExtQuickBorderGadget(QObject *parent = QEXT_NULLPTR);
    ~QExtQuickBorderGadget();

    QColor color() const;
    qreal width() const;
    qreal leftWidth() const;
    qreal rightWidth() const;
    qreal topWidth() const;
    qreal bottomWidth() const;
    bool isValid() const;

signals:
    void colorChanged();
    void widthChanged();
    void leftWidthChanged();
    void rightWidthChanged();
    void topWidthChanged();
    void bottomWidthChanged();
    void validChanged();

private slots:
    void setColor(QColor color);
    void setWidth(qreal width);
    void setLeftWidth(qreal leftWidth);
    void setRightWidth(qreal rightWidth);
    void setTopWidth(qreal topWidth);
    void setBottomWidth(qreal bottomWidth);

protected:
    QScopedPointer<QExtQuickBorderGadgetPrivate> dd_ptr;
};

#endif // _QEXTQUICKBORDERGADGET_H
