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

#ifndef _QEXTMODELITEMTAGS_H
#define _QEXTMODELITEMTAGS_H

#include <qextGlobal.h>
#include <qextModelTagRow.h>

#include <QVector>

class QExtModelItem;
class QExtModelTagInfo;
class QExtModelItemContainer;
class QExtModelItemTagsPrivate;
class QEXT_CORE_API QExtModelItemTags
{
public:
    typedef QVector<QExtModelItemContainer *> Container;
    typedef Container::ConstIterator ConstIterator;
    typedef Container::Iterator Iterator;

    QExtModelItemTags();
    virtual ~QExtModelItemTags();

    // tag
    int itemCount(const QString &tagName) const;

    /**
     * @brief Returns the name of the default tag.
     */
    QString defaultTag() const;
    void setDefaultTag(const QString &name);

    /**
     * @brief Returns true if container with such name exists.
     */
    bool isTag(const QString &name) const;

    void registerTag(const QExtModelTagInfo &tagInfo, bool setAsDefault = false);

    /**
     * @brief Returns true if item can be taken.
     * @param tagRow
     * @return
     */
    bool canTakeItem(const QExtModelTagRow &tagRow) const;
    /**
     * @brief Inserts item in container with given tag name and at given row.
     * Returns true in the case of success. If tag name is empty, default tag will be used.
     * @param item
     * @param tagRow
     * @return
     */
    bool insertItem(QExtModelItem *item, const QExtModelTagRow &tagRow);

    /**
     * @brief Removes item at given row and for given tag, returns it to the user.
     * @param tagRow
     * @return
     */
    QExtModelItem *takeItem(const QExtModelTagRow &tagRow);

    // item access
    QVector<QExtModelItem *> allItems() const;

    /**
     * @brief Returns vector of items in the container with given name.
     * If tag name is empty, default tag will be used.
     * @param tag
     * @return
     */
    QVector<QExtModelItem *> getItems(const QString &tag = "") const;

    /**
     * @brief Returns item at given row of given tag.
     * @param tagRow
     * @return
     */
    QExtModelItem *getItem(const QExtModelTagRow &tagRow) const;

    /**
     * @brief Returns tag name and row of item in container.
     * @param item
     * @return
     */
    QExtModelTagRow tagRowOfItem(QExtModelItem *item) const;

    ConstIterator begin() const;
    ConstIterator end() const;

    int tagsCount() const;

    /**
     * @brief Returns true if given tag corresponds to registered single property tag.
     * @param tag
     * @return
     */
    bool isSinglePropertyTag(const QString &tag) const;

    QExtModelItemContainer &at(int index);

private:
    QScopedPointer<QExtModelItemTagsPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtModelItemTags)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemTags)
};

#endif // _QEXTMODELITEMTAGS_H
