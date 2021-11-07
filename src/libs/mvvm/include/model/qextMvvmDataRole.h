#ifndef _QEXTMVVMDATAROLE_H
#define _QEXTMVVMDATAROLE_H

#include <qextMvvmGlobal.h>

#include <QVariant>

//! Represents pair of data,role for QEXTMvvmItemData.

class QEXT_MVVM_API QEXTMvvmDataRole
{
public:
    QEXTMvvmDataRole(QVariant data = QVariant(), int role = -1);
    QVariant m_data;
    int m_role;
    bool operator==(const QEXTMvvmDataRole& other) const;
};


#endif // _QEXTMVVMDATAROLE_H
