#ifndef _QEXTMVVMITEMDATA_H
#define _QEXTMVVMITEMDATA_H

#include <qextMvvmDataRole.h>
#include <qextMvvmGlobal.h>

#include <QVariant>

#include <QVector>

//! Handles data roles for QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmItemData
{
public:
    using container_type = QVector<QEXTMvvmDataRole>;
    using const_iterator = container_type::const_iterator;

    QVector<int> roles() const;

    QVariant data(int role) const;

    bool setData(const QVariant& value, int role);

    const_iterator begin() const;
    const_iterator end() const;

    bool hasData(int role) const;

private:
    container_type m_values;
};


#endif // _QEXTMVVMITEMDATA_H
