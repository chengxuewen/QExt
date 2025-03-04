// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
#define MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmViewItem;

//! Base class to construct row of QExtMvvmViewItem's from given QExtMvvmSessionItem.
//! Used in context of AbstractViewModel while exposing QExtMvvmSessionModel to Qt.

class QEXT_MVVM_API QExtMvvmRowStrategyInterface {
public:
    virtual ~QExtMvvmRowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<QExtUniquePointer<QExtMvvmViewItem>> constructRow(QExtMvvmSessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
