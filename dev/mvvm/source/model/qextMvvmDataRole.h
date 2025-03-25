// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_DATAROLE_H
#define MVVM_MODEL_DATAROLE_H


#include <qextMvvmGlobal.h>

namespace ModelView {

//! Represents pair of data,role for QExtMvvmSessionItemData.

class QEXT_MVVM_API QExtMvvmDataRole {
public:
    QExtMvvmDataRole(QVariant data = QVariant(), int role = -1);
    QVariant m_data;
    int m_role;
    bool operator==(const QExtMvvmDataRole& other) const;
};

} // namespace ModelView

#endif // MVVM_MODEL_DATAROLE_H
