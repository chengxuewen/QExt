#ifndef _QEXTMVVMPLOTTINGCOLORMAPVIEWPORTPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGCOLORMAPVIEWPORTPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmColorMapViewportItem;

//! Establishes communications and mutual updates for ColorMapViewportItem and QCutomPlot.
//! Populates custom plot with color map and tracks updates in items.

class QEXT_MVVM_API QEXTMvvmColorMapViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapViewportItem>
{
public:
    explicit QEXTMvvmColorMapViewportPlotController(QCustomPlot* plot);
    ~QEXTMvvmColorMapViewportPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapViewportPlotControllerImpl;
    std::unique_ptr<ColorMapViewportPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCOLORMAPVIEWPORTPLOTCONTROLLER_H
