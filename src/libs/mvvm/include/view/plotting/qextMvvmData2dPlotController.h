#ifndef _QEXTMVVMDATA2DPLOTCONTROLLER_H
#define _QEXTMVVMDATA2DPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPColorMap;

class QEXTMvvmData2DItem;

//! Establish communication between QCPColorMap and QEXTMvvmData2DItem.
//! Provide update of data points on QCPColorMap when Graph2DItem is changed.

class QEXT_MVVM_API QEXTMvvmData2DPlotController : public QEXTMvvmItemListener<QEXTMvvmData2DItem>
{
public:
    explicit QEXTMvvmData2DPlotController(QCPColorMap* color_map);
    ~QEXTMvvmData2DPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

private:
    struct QEXTMvvmData2DPlotControllerImpl;
    QScopedPointer<QEXTMvvmData2DPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMDATA2DPLOTCONTROLLER_H
