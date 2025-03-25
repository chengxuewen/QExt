// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
#define MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItem;

//! Base class for strategies to find children, actual or fictional, of a given item.
//! The reported vector of children might be different from the actual children of a given item.
//! The strategy is used in the context of AbstractViewModel while exposing QExtMvvmSessionModel to Qt.
//! Thanks to this strategy QExtMvvmViewModel decides which items to visit.

class QEXT_MVVM_API QExtMvvmChildrenStrategyInterface {
public:
    virtual ~QExtMvvmChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual std::vector<QExtMvvmSessionItem*> children(const QExtMvvmSessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
