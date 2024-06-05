/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#ifndef _QEXTQUICKITEMGADGET_H
#define _QEXTQUICKITEMGADGET_H

#include <qextQuickControlsGlobal.h>

#include <QObject>

class QExtQuickItemGadgetPrivate;
class QEXT_QUICKCONTROLS_API QExtQuickItemGadget : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtQuickItemGadget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickItemGadget)

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit QExtQuickItemGadget(QObject *parent = QEXT_NULLPTR);
    ~QExtQuickItemGadget();

    qreal width() const;
    qreal height() const;

signals:
    void widthChanged(const qreal &width);
    void heightChanged(const qreal &height);

private slots:
    void setWidth(const qreal &width);
    void setHeight(const qreal &height);

protected:
    QScopedPointer<QExtQuickItemGadgetPrivate> dd_ptr;
};

#endif // _QEXTQUICKITEMGADGET_H
