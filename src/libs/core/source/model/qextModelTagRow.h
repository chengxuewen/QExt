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

#ifndef _QEXTMODELTAGROW_H
#define _QEXTMODELTAGROW_H

#include <qextGlobal.h>

class QEXT_CORE_API QExtModelTagRow
{
public:
    QExtModelTagRow() : tag(""), row(-1) {}
    QExtModelTagRow(const QString &name, int row = -1) : tag(name), row(row) {}
    QExtModelTagRow(const QExtModelTagRow &other) : tag(other.tag), row(other.row) {}
    virtual ~QExtModelTagRow();

    QExtModelTagRow &operator=(const QExtModelTagRow &other);

    bool operator==(const QExtModelTagRow &other) const;
    bool operator!=(const QExtModelTagRow &other) const { return !(*this == other); }

    /**
     * @brief Constructs new tagrow representing next row in given tag.
     * No validity check.
     * @return
     */
    QExtModelTagRow next() const { return QExtModelTagRow(tag, row + 1); }

    /**
     * @brief Constructs new tagrow representing previous row in given tag.
     * No validity check.
     * @return
     */
    QExtModelTagRow prev() const { return QExtModelTagRow(tag, row - 1); }

    /**
     * @brief Returns TagRow corresponding to the append to tagName.
     * If tagName =="" the default name will be used in SessionItemTags context.
     * @param tagName
     * @return
     */
    static QExtModelTagRow append(const QString &tagName = {}) { return QExtModelTagRow(tagName, -1); }

    /**
     * @brief Returns TagRow corresponding to prepending to tagName.
     * If tagName =="" the default name will be used in SessionItemTags context.
     * @param tagName
     * @return
     */
    static QExtModelTagRow prepend(const QString &tagName = {}) { return QExtModelTagRow(tagName, 0); }

    QString tag;
    int row;
};

#endif // _QEXTMODELTAGROW_H
