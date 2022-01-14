#ifndef _QEXTMVVMPLOTTINGGRAPHPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGGRAPHPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCustomPlot;

namespace ModelView
{

class QEXTMvvmGraphItem;

//! Establish communication between QCPGraph and GraphItem.
//! Provides update on QCPGraph (data points, line style, color, etc) when GraphItem is changed.
//! QCPGraph is added to QCustomPlot plottables, when controller is created, and removed from
//! plottables when controller is destroyed.

class QEXT_MVVM_API QEXTMvvmGraphPlotController : public QEXTMvvmItemListener<QEXTMvvmGraphItem>
{
public:
    explicit QEXTMvvmGraphPlotController(QCustomPlot* plot);
    ~QEXTMvvmGraphPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct GraphItemControllerImpl;
    std::unique_ptr<GraphItemControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGGRAPHPLOTCONTROLLER_H
