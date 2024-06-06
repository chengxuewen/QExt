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

#ifndef _QEXTMODELITEMDATA_H
#define _QEXTMODELITEMDATA_H

#include <qextGlobal.h>
#include <qextVariantUtils.h>

#include <QVector>

/**
 * @brief Represents pair of data,role for QExtModelItemData.
 */
class QEXT_CORE_API QExtModelItemDataRole
{
public:
    QExtModelItemDataRole(const QVariant &data = QVariant(), int role = -1) : m_data(data), m_role(role) {}
    virtual ~QExtModelItemDataRole() {}

    bool operator==(const QExtModelItemDataRole &other) const
    {
        return m_role == other.m_role && QExtVariantUtils::isTheSame(m_data, other.m_data);
    }

    QVariant m_data;
    int m_role;
};

/**
 * @brief Handles data roles for SessionItem.
 */
class QExtModelItemDataPrivate;
class QEXT_CORE_API QExtModelItemData
{
public:
    typedef QVector<QExtModelItemDataRole> Container;
    typedef Container::ConstIterator ConstIterator;
    typedef Container::Iterator Iterator;

    QExtModelItemData();
    virtual ~QExtModelItemData();

    QVector<int> roles() const;

    /**
     * @brief Returns true if item has data with given role.
     * @param role
     * @return
     */
    bool hasData(int role) const;
    QVariant data(int role) const;
    /**
     * @brief Sets the data for given role. Returns true if data was changed.
     * If variant is invalid, corresponding role will be removed.
     * @param value
     * @param role
     * @return
     */
    bool setData(const QVariant &value, int role);

    ConstIterator begin() const;
    ConstIterator end() const;

private:
    QScopedPointer<QExtModelItemDataPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtModelItemData)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemData)
};

#endif // _QEXTMODELITEMDATA_H
