#ifndef _QEXTMVVMCOLORMAPPLOTCONTROLLER_H
#define _QEXTMVVMCOLORMAPPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCustomPlot;
class QCPColorScale;

class QEXTMvvmColorMapItem;

//! Establish communication between QCPColorMap and QEXTMvvmColorMapItem.
//! Provide update on QCPColorMap when QEXTMvvmColorMapItem is changed. QCPColorMap is added to
//! QCustomPlot plottables, when controller is created, and removed from plottables, when controller
//! is destroyed.

class QEXT_MVVM_API QEXTMvvmColorMapPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapItem>
{
public:
    explicit QEXTMvvmColorMapPlotController(QCustomPlot* plot, QCPColorScale* color_scale = nullptr);
    ~QEXTMvvmColorMapPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

private:
    struct ColorMapPlotControllerImpl;
    QScopedPointer<ColorMapPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMCOLORMAPPLOTCONTROLLER_H
