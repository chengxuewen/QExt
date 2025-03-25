// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H
#define MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>
#include <memory>

class QCustomPlot;

namespace ModelView {

class QExtMvvmGraphItem;

//! Establish communication between QCPGraph and QExtMvvmGraphItem.
//! Provides update on QCPGraph (data points, line style, color, etc) when QExtMvvmGraphItem is changed.
//! QCPGraph is added to QCustomPlot plottables, when controller is created, and removed from
//! plottables when controller is destroyed.

class QEXT_MVVM_API QExtMvvmGraphPlotController : public QExtMvvmItemListener<QExtMvvmGraphItem> {
public:
    explicit QExtMvvmGraphPlotController(QCustomPlot* plot);
    ~QExtMvvmGraphPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct GraphItemControllerImpl;
    QExtUniquePointer<GraphItemControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHPLOTCONTROLLER_H
