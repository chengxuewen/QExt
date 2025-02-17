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
#include "qextMVVMGlobal.h"
#include <memory>

class QCPGraph;

namespace ModelView {

class PenItem;

//! Establishes communication between QCPGraph and PenItem.
//! Provides update of QCPGraph's color, line style and width when PenItem is changed.

class QEXT_MVVM_API PenController : public ItemListener<PenItem> {
public:
    explicit PenController(QCPGraph* graph);
    ~PenController() override;

protected:
    void subscribe() override;

private:
    struct PenControllerImpl;
    QExtUniquePointer<PenControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_PENCONTROLLER_H
