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

#ifndef _QEXTMODELTAGINFO_H
#define _QEXTMODELTAGINFO_H

#include <qextGlobal.h>

#include <QStringList>
#include <QSharedDataPointer>

class QExtModelTagInfoPrivate;
class QEXT_CORE_API QExtModelTagInfo
{
public:
    QExtModelTagInfo();
    QExtModelTagInfo(const QExtModelTagInfo &other);
    QExtModelTagInfo(const QString &name, int min, int max, const QStringList &modelTypes);
    virtual ~QExtModelTagInfo();

    QExtModelTagInfo &operator =(const QExtModelTagInfo &other);
    void swap(QExtModelTagInfo &other) noexcept;

    int min() const;
    int max() const;
    QString name() const;
    QStringList modelTypes() const;

    bool isSinglePropertyTag() const;
    bool isValidChild(const QString &child) const;

    bool operator==(const QExtModelTagInfo &other) const;
    bool operator!=(const QExtModelTagInfo &other) const;

    //! Constructs universal tag intended for unlimited amount of various items.
    static QExtModelTagInfo universalTag(const QString &name, const QStringList &modelTypes = QStringList());

    //! Constructs tag intended for single property.
    static QExtModelTagInfo propertyTag(const QString &name, const QString &modelType);

private:
    QScopedPointer<QExtModelTagInfoPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtModelTagInfo)
};

#endif // _QEXTMODELTAGINFO_H
