#ifndef _QEXTMVVMCOLORMAPVIEWPORTPLOTCONTROLLER_H
#define _QEXTMVVMCOLORMAPVIEWPORTPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCustomPlot;

class QEXTMvvmColorMapViewportItem;

//! Establishes communications and mutual updates for QEXTMvvmColorMapViewportItem and QCutomPlot.
//! Populates custom plot with color map and tracks updates in items.

class QEXT_MVVM_API QEXTMvvmColorMapViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmColorMapViewportItem>
{
public:
    explicit QEXTMvvmColorMapViewportPlotController(QCustomPlot* plot);
    ~QEXTMvvmColorMapViewportPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

private:
    struct ColorMapViewportPlotControllerImpl;
    QScopedPointer<ColorMapViewportPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMCOLORMAPVIEWPORTPLOTCONTROLLER_H
