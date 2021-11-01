#ifndef _QEXTMVVMDATAROLE_H
#define _QEXTMVVMDATAROLE_H

#include <qextMvvmVariant.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

//! Represents pair of data,role for QEXTMvvmSessionItemData.

class QEXT_MVVM_API QEXTMvvmDataRole
{
public:
    QEXTMvvmDataRole(QEXTMvvmVariant data = QEXTMvvmVariant(), int role = -1);
    QEXTMvvmVariant m_data;
    int m_role;
    bool operator==(const QEXTMvvmDataRole& other) const;
};

} // namespace ModelView

#endif // _QEXTMVVMDATAROLE_H
