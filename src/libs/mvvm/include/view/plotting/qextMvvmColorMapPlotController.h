#ifndef _QEXTMVVMPLOTTINGCOLORMAPPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGCOLORMAPPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCustomPlot;
class QCPColorScale;

namespace ModelView
{

class QEXTMvvmColorMapItem;

//! Establish communication between QCPColorMap and ColorMapItem.
//! Provide update on QCPColorMap when ColorMapItem is changed. QCPColorMap is added to
//! QCustomPlot plottables, when controller is created, and removed from plottables, when controller
//! is destroyed.

class QEXT_MVVM_API QEXTMvvmColorMapPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapItem>
{
public:
    explicit QEXTMvvmColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale = nullptr);
    ~QEXTMvvmColorMapPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct ColorMapPlotControllerImpl;
    std::unique_ptr<ColorMapPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCOLORMAPPLOTCONTROLLER_H
