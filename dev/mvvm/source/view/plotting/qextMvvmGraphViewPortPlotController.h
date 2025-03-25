// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
#define MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>
#include <memory>

class QCustomPlot;

namespace ModelView {

class QExtMvvmGraphViewportItem;

//! Establishes communications and mutual updates for QExtMvvmGraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in QExtMvvmGraphViewportItem.

class QEXT_MVVM_API QExtMvvmGraphViewportPlotController : public QExtMvvmItemListener<QExtMvvmGraphViewportItem> {
public:
    explicit QExtMvvmGraphViewportPlotController(QCustomPlot* plot);
    ~QExtMvvmGraphViewportPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphViewportPlotControllerImpl;
    QExtUniquePointer<GraphViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
