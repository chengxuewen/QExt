// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
#define MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCustomPlot;
class QCPColorScale;

namespace ModelView
{

class QEXTMvvmColorMapItem;

//! Establish communication between QCPColorMap and QEXTMvvmColorMapItem.
//! Provide update on QCPColorMap when QEXTMvvmColorMapItem is changed. QCPColorMap is added to
//! QCustomPlot plottables, when controller is created, and removed from plottables, when controller
//! is destroyed.

class QEXT_MVVM_API ColorMapPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapItem>
{
public:
    explicit ColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale = nullptr);
    ~ColorMapPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapPlotControllerImpl;
    std::unique_ptr<ColorMapPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
