#ifndef _QEXTMVVMDATA1DPLOTCONTROLLER_H
#define _QEXTMVVMDATA1DPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPGraph;

class QEXTMvvmData1DItem;

//! Establishes communication between QCPGraph and QEXTMvvmData1DItem.
//! Provides update of data points on QCPGraph when Graph1DItem is changed.

class QEXT_MVVM_API QEXTMvvmData1DPlotController : public QEXTMvvmItemListener<QEXTMvvmData1DItem>
{
public:
    explicit QEXTMvvmData1DPlotController(QCPGraph* graph);
    ~QEXTMvvmData1DPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

private:
    struct QEXTMvvmData1DPlotControllerImpl;
    QScopedPointer<QEXTMvvmData1DPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMDATA1DPLOTCONTROLLER_H
