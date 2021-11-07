#ifndef _QEXTMVVMGRAPHVIEWPORTPLOTCONTROLLER_H
#define _QEXTMVVMGRAPHVIEWPORTPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCustomPlot;

class QEXTMvvmGraphViewportItem;

//! Establishes communications and mutual updates for QEXTMvvmGraphViewportItem and QCutomPlot.
//! Populates custom plot with all graphs found in QEXTMvvmGraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphViewportPlotController : public QEXTMvvmItemListener<QEXTMvvmGraphViewportItem>
{
public:
    explicit QEXTMvvmGraphViewportPlotController(QCustomPlot* plot);
    ~QEXTMvvmGraphViewportPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;

private:
    struct GraphViewportPlotControllerImpl;
    QScopedPointer<GraphViewportPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMGRAPHVIEWPORTPLOTCONTROLLER_H
