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

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>
#include <memory>

class QCustomPlot;
class QCPColorScale;

namespace ModelView {

class QExtMvvmColorMapItem;

//! Establish communication between QCPColorMap and QExtMvvmColorMapItem.
//! Provide update on QCPColorMap when QExtMvvmColorMapItem is changed. QCPColorMap is added to
//! QCustomPlot plottables, when controller is created, and removed from plottables, when controller
//! is destroyed.

class QEXT_MVVM_API QExtMvvmColorMapPlotController : public QExtMvvmItemListener<QExtMvvmColorMapItem> {
public:
    explicit QExtMvvmColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale = nullptr);
    ~QExtMvvmColorMapPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapPlotControllerImpl;
    QExtUniquePointer<ColorMapPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPPLOTCONTROLLER_H
