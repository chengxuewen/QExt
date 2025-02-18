// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
#define MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H

#include "model/signals/itemlistener.h"
#include "qextMVVMGlobal.h"
#include <memory>

class QCPAxis;

namespace ModelView {

class ViewportAxisItem;

//! Establishes communication between QCPAxis and ViewportAxisItem.
//! Provide mutual update of axis parameters (min, max, title) for two axes representations.

class QEXT_MVVM_API ViewportAxisPlotController : public ItemListener<ViewportAxisItem> {
public:
    explicit ViewportAxisPlotController(QCPAxis* axis);
    ~ViewportAxisPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

public:
    struct AxesPlotControllerImpl;
    QExtUniquePointer<AxesPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
