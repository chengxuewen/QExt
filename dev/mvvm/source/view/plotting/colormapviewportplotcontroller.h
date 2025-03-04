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

#include "model/signals/itemlistener.h"
#include <qextMvvmGlobal.h>
#include <memory>

class QCustomPlot;

namespace ModelView {

class QExtMvvmColorMapViewportItem;

//! Establishes communications and mutual updates for QExtMvvmColorMapViewportItem and QCutomPlot.
//! Populates custom plot with color map and tracks updates in items.

class QEXT_MVVM_API QExtMvvmColorMapViewportPlotController : public QExtMvvmItemListener<QExtMvvmColorMapViewportItem> {
public:
    explicit QExtMvvmColorMapViewportPlotController(QCustomPlot* plot);
    ~QExtMvvmColorMapViewportPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapViewportPlotControllerImpl;
    QExtUniquePointer<ColorMapViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPVIEWPORTPLOTCONTROLLER_H
