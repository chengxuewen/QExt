// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H
#define MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmColorMapViewportItem;

//! Establishes communications and mutual updates for QEXTMvvmColorMapViewportItem and QCutomPlot.
//! Populates custom plot with color map and tracks updates in items.

class QEXT_MVVM_API ColorMapViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapViewportItem>
{
public:
    explicit ColorMapViewportPlotController(QCustomPlot* plot);
    ~ColorMapViewportPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapViewportPlotControllerImpl;
    std::unique_ptr<ColorMapViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H
