#ifndef _QEXTMVVMGRAPHPLOTCONTROLLER_H
#define _QEXTMVVMGRAPHPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCustomPlot;

class QEXTMvvmGraphItem;

//! Establish communication between QCPGraph and QEXTMvvmGraphItem.
//! Provides update on QCPGraph (data points, line style, color, etc) when QEXTMvvmGraphItem is changed.
//! QCPGraph is added to QCustomPlot plottables, when controller is created, and removed from
//! plottables when controller is destroyed.

class QEXT_MVVM_API QEXTMvvmGraphPlotController : public QEXTMvvmItemListener<QEXTMvvmGraphItem>
{
public:
    explicit QEXTMvvmGraphPlotController(QCustomPlot* plot);
    ~QEXTMvvmGraphPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

private:
    struct GraphItemControllerImpl;
    QScopedPointer<GraphItemControllerImpl> p_impl;
};

#endif // _QEXTMVVMGRAPHPLOTCONTROLLER_H
