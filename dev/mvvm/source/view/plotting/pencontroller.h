// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_PENCONTROLLER_H
#define MVVM_PLOTTING_PENCONTROLLER_H

#include "model/signals/itemlistener.h"
#include <qextMvvmGlobal.h>
#include <memory>

class QCPGraph;

namespace ModelView {

class QExtMvvmPenItem;

//! Establishes communication between QCPGraph and QExtMvvmPenItem.
//! Provides update of QCPGraph's color, line style and width when QExtMvvmPenItem is changed.

class QEXT_MVVM_API QExtMvvmPenController : public QExtMvvmItemListener<QExtMvvmPenItem> {
public:
    explicit QExtMvvmPenController(QCPGraph* graph);
    ~QExtMvvmPenController() override;

protected:
    void subscribe() override;

private:
    struct PenControllerImpl;
    QExtUniquePointer<PenControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_PENCONTROLLER_H
