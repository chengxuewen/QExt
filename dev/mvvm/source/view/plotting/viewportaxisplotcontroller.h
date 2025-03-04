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
#include <qextMvvmGlobal.h>
#include <memory>

class QCPAxis;

namespace ModelView {

class QExtMvvmViewportAxisItem;

//! Establishes communication between QCPAxis and QExtMvvmViewportAxisItem.
//! Provide mutual update of axis parameters (min, max, title) for two axes representations.

class QEXT_MVVM_API QExtMvvmViewportAxisPlotController : public QExtMvvmItemListener<QExtMvvmViewportAxisItem> {
public:
    explicit QExtMvvmViewportAxisPlotController(QCPAxis* axis);
    ~QExtMvvmViewportAxisPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

public:
    struct AxesPlotControllerImpl;
    QExtUniquePointer<AxesPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_VIEWPORTAXISPLOTCONTROLLER_H
