#ifndef _QEXTMVVMPLOTTINGDATA2DPLOTCONTROLLER_H
#define _QEXTMVVMPLOTTINGDATA2DPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPColorMap;

namespace ModelView
{

class QEXTMvvmData2DItem;

//! Establish communication between QCPColorMap and Data2DItem.
//! Provide update of data points on QCPColorMap when Graph2DItem is changed.

class QEXT_MVVM_API QEXTMvvmData2DPlotController : public QEXTMvvmItemListener<QEXTMvvmData2DItem>
{
public:
    explicit QEXTMvvmData2DPlotController(QCPColorMap* color_map);
    ~QEXTMvvmData2DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data2DPlotControllerImpl;
    std::unique_ptr<Data2DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGDATA2DPLOTCONTROLLER_H
