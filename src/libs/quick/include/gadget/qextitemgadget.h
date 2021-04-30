/****************************************************************************
**
** Library: QEXTQuick
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

#ifndef QEXTITEMGADGET_H
#define QEXTITEMGADGET_H

#include <qextquickglobal.h>

#include <qextobject.h>

#include <QObject>

class QEXTItemGadgetPrivate;
class QEXT_QUICK_API QEXTItemGadget : public QObject, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit QEXTItemGadget(QObject *parent = QEXT_NULLPTR);
    ~QEXTItemGadget();

    qreal width() const;
    qreal height() const;

signals:
    void widthChanged(const qreal &width);
    void heightChanged(const qreal &height);

private slots:
    void setWidth(const qreal &width);
    void setHeight(const qreal &height);

private:
    QEXT_DECLARE_PRIVATE(QEXTItemGadget)
    QEXT_DISABLE_COPY_MOVE(QEXTItemGadget)
};

#endif // QEXTITEMGADGET_H
