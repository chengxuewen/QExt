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

#ifndef _QEXTMODELITEMCONTAINER_H
#define _QEXTMODELITEMCONTAINER_H

#include <qextGlobal.h>
#include <qextModelTagInfo.h>

#include <QVector>

class QExtModelItem;
class QExtModelTagInfo;
class QExtModelItemContainerPrivate;
class QEXT_CORE_API QExtModelItemContainer
{
public:
    typedef QVector<QExtModelItem *> Container;
    typedef Container::ConstIterator ConstIterator;
    typedef Container::Iterator Iterator;

    QExtModelItemContainer(const QExtModelTagInfo &tagInfo);
    virtual ~QExtModelItemContainer();

    bool isEmpty() const;
    int itemCount() const;

    QVector<QExtModelItem *> items() const;
    QExtModelItem *itemAt(int index) const;
    QExtModelItem *takeItem(int index);
    bool insertItem(QExtModelItem * item, int index);

    bool canTakeItem(int index) const;
    int indexOfItem(QExtModelItem *item) const;
    bool canInsertItem(const QExtModelItem *item, int index) const;

    QString name() const;
    QExtModelTagInfo tagInfo() const;

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    QScopedPointer<QExtModelItemContainerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtModelItemContainer)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemContainer)
};

#endif // _QEXTMODELITEMCONTAINER_H
