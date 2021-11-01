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

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmGraphViewportItem;

//! Establishes communications and mutual updates for QEXTMvvmGraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in QEXTMvvmGraphViewportItem.

class QEXT_MVVM_API GraphViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmGraphViewportItem>
{
public:
    explicit GraphViewportPlotController(QCustomPlot* plot);
    ~GraphViewportPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphViewportPlotControllerImpl;
    std::unique_ptr<GraphViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHVIEWPORTPLOTCONTROLLER_H
