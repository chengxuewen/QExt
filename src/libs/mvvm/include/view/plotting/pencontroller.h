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

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCPGraph;

namespace ModelView
{

class QEXTMvvmPenItem;

//! Establishes communication between QCPGraph and QEXTMvvmPenItem.
//! Provides update of QCPGraph's color, line style and width when QEXTMvvmPenItem is changed.

class QEXT_MVVM_API PenController : public QEXTMvvmItemListener<QEXTMvvmPenItem>
{
public:
    explicit PenController(QCPGraph* graph);
    ~PenController() override;

protected:
    void subscribe() override;

private:
    struct PenControllerImpl;
    std::unique_ptr<PenControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_PENCONTROLLER_H
