#ifndef _QEXTMVVMPLOTTINGDATA1DPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGDATA1DPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPGraph;

namespace ModelView
{

class QEXTMvvmData1DItem;

//! Establishes communication between QCPGraph and Data1DItem.
//! Provides update of data points on QCPGraph when Graph1DItem is changed.

class QEXT_MVVM_API QEXTMvvmData1DPlotController : public QEXTMvvmItemListener<QEXTMvvmData1DItem>
{
public:
    explicit QEXTMvvmData1DPlotController(QCPGraph* graph);
    ~QEXTMvvmData1DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data1DPlotControllerImpl;
    std::unique_ptr<Data1DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGDATA1DPLOTCONTROLLER_H
