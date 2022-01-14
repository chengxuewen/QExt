#ifndef _QEXTMVVMMODELDATAROLE_H
#define _QEXTMVVMMODELDATAROLE_H

#include <qextMvvmGlobal.h>

namespace ModelView
{

//! Represents pair of data,role for SessionItemData.

class QEXT_MVVM_API QEXTMvvmDataRole
{
public:
    QEXTMvvmDataRole(QVariant data = QVariant(), int role = -1);
    QVariant m_data;
    int m_role;
    bool operator==(const QEXTMvvmDataRole& other) const;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELDATAROLE_H
